/*
 * Copyright © 2015 Red Hat
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Rob Clark <robclark@freedesktop.org>
 */

#include "nir.h"
#include "nir_builder.h"

#define MAX_CLIP_PLANES 8

/* Generates the lowering code for user-clip-planes, generating CLIPDIST
 * from UCP[n] + CLIPVERTEX or POSITION.  Additionally, an optional pass
 * for fragment shaders to insert conditional kill's based on the inter-
 * polated CLIPDIST
 *
 * NOTE: should be run after nir_lower_outputs_to_temporaries() (or at
 * least in scenarios where you can count on each output written once
 * and only once).
 */


static nir_variable *
create_clipdist_var(nir_shader *shader, unsigned drvloc,
                    bool output, gl_varying_slot slot)
{
   nir_variable *var = rzalloc(shader, nir_variable);

   var->data.driver_location = drvloc;
   var->type = glsl_vec4_type();
   var->data.mode = output ? nir_var_shader_out : nir_var_shader_in;
   var->name = ralloc_asprintf(var, "clipdist_%d", drvloc);
   var->data.index = 0;
   var->data.location = slot;

   if (output) {
      exec_list_push_tail(&shader->outputs, &var->node);
   }
   else {
      exec_list_push_tail(&shader->inputs, &var->node);
   }
   return var;
}

static void
store_clipdist_output(nir_builder *b, nir_variable *out, nir_ssa_def **val)
{
   nir_intrinsic_instr *store;

   store = nir_intrinsic_instr_create(b->shader, nir_intrinsic_store_output);
   store->num_components = 4;
   store->const_index[0] = out->data.driver_location;
   store->src[0].ssa = nir_vec4(b, val[0], val[1], val[2], val[3]);
   store->src[0].is_ssa = true;
   nir_builder_instr_insert(b, &store->instr);
}

static void
load_clipdist_input(nir_builder *b, nir_variable *in, nir_ssa_def **val)
{
   nir_intrinsic_instr *load;

   load = nir_intrinsic_instr_create(b->shader, nir_intrinsic_load_input);
   load->num_components = 4;
   load->const_index[0] = in->data.driver_location;
   nir_ssa_dest_init(&load->instr, &load->dest, 4, NULL);
   nir_builder_instr_insert(b, &load->instr);

   val[0] = nir_channel(b, &load->dest.ssa, 0);
   val[1] = nir_channel(b, &load->dest.ssa, 1);
   val[2] = nir_channel(b, &load->dest.ssa, 2);
   val[3] = nir_channel(b, &load->dest.ssa, 3);
}

struct find_output_state
{
   unsigned drvloc;
   nir_ssa_def *def;
};

static bool
find_output_in_block(nir_block *block, void *void_state)
{
   struct find_output_state *state = void_state;
   nir_foreach_instr(block, instr) {

      if (instr->type == nir_instr_type_intrinsic) {
         nir_intrinsic_instr *intr = nir_instr_as_intrinsic(instr);
         if ((intr->intrinsic == nir_intrinsic_store_output) &&
             intr->const_index[0] == state->drvloc) {
            assert(state->def == NULL);
            assert(intr->src[0].is_ssa);
            state->def = intr->src[0].ssa;
         }
      }

#if !defined(DEBUG)
      /* for debug builds, scan entire shader to assert
       * if output is written multiple times.  For release
       * builds just assume all is well and bail when we
       * find first:
       */
      if (state->def)
         return false;
#endif
   }

   return true;
}

/* TODO: maybe this would be a useful helper?
 * NOTE: assumes each output is written exactly once (and unconditionally)
 * so if needed nir_lower_outputs_to_temporaries()
 */
static nir_ssa_def *
find_output(nir_shader *shader, unsigned drvloc)
{
   struct find_output_state state = {
      .drvloc = drvloc,
   };

   nir_foreach_overload(shader, overload) {
      if (overload->impl) {
         nir_foreach_block_reverse(overload->impl,
                                   find_output_in_block, &state);
      }
   }

   return state.def;
}

/*
 * VS lowering
 */

static void
lower_clip_vs(nir_function_impl *impl, unsigned ucp_enables,
              nir_ssa_def *cv, nir_variable **out)
{
   nir_ssa_def *clipdist[MAX_CLIP_PLANES];
   nir_builder b;

   nir_builder_init(&b, impl);

   /* NIR should ensure that, even in case of loops/if-else, there
    * should be only a single predecessor block to end_block, which
    * makes the perfect place to insert the clipdist calculations.
    *
    * NOTE: in case of early return's, these would have to be lowered
    * to jumps to end_block predecessor in a previous pass.  Not sure
    * if there is a good way to sanity check this, but for now the
    * users of this pass don't support sub-routines.
    */
   assert(impl->end_block->predecessors->entries == 1);
   b.cursor = nir_after_cf_list(&impl->body);

   for (int plane = 0; plane < MAX_CLIP_PLANES; plane++) {
      if (ucp_enables & (1 << plane)) {
         nir_intrinsic_instr *ucp;

         /* insert intrinsic to fetch ucp[plane]: */
         ucp = nir_intrinsic_instr_create(b.shader,
                                          nir_intrinsic_load_user_clip_plane);
         ucp->num_components = 4;
         ucp->const_index[0] = plane;
         nir_ssa_dest_init(&ucp->instr, &ucp->dest, 4, NULL);
         nir_builder_instr_insert(&b, &ucp->instr);

         /* calculate clipdist[plane] - dot(ucp, cv): */
         clipdist[plane] = nir_fdot4(&b, &ucp->dest.ssa, cv);
      }
      else {
         /* 0.0 == don't-clip == disabled: */
         clipdist[plane] = nir_imm_float(&b, 0.0);
      }
   }

   if (ucp_enables & 0x0f)
      store_clipdist_output(&b, out[0], &clipdist[0]);
   if (ucp_enables & 0xf0)
      store_clipdist_output(&b, out[1], &clipdist[4]);

   nir_metadata_preserve(impl, nir_metadata_dominance);
}

/* ucp_enables is bitmask of enabled ucp's.  Actual ucp values are
 * passed in to shader via user_clip_plane system-values
 */
void
nir_lower_clip_vs(nir_shader *shader, unsigned ucp_enables)
{
   int clipvertex = -1;
   int position = -1;
   int maxloc = -1;
   nir_ssa_def *cv;
   nir_variable *out[2];

   if (!ucp_enables)
      return;

   /* find clipvertex/position outputs: */
   foreach_list_typed(nir_variable, var, node, &shader->outputs) {
      int loc = var->data.driver_location;

      /* keep track of last used driver-location.. we'll be
       * appending CLIP_DIST0/CLIP_DIST1 after last existing
       * output:
       */
      maxloc = MAX2(maxloc, loc);

      switch (var->data.location) {
      case VARYING_SLOT_POS:
         position = loc;
         break;
      case VARYING_SLOT_CLIP_VERTEX:
         clipvertex = loc;
         break;
      case VARYING_SLOT_CLIP_DIST0:
      case VARYING_SLOT_CLIP_DIST1:
         /* if shader is already writing CLIPDIST, then
          * there should be no user-clip-planes to deal
          * with.
          */
         return;
      }
   }

   if (clipvertex != -1)
      cv = find_output(shader, clipvertex);
   else if (position != -1)
      cv = find_output(shader, position);
   else
      return;

   /* insert CLIPDIST outputs: */
   if (ucp_enables & 0x0f)
      out[0] =
         create_clipdist_var(shader, ++maxloc, true, VARYING_SLOT_CLIP_DIST0);
   if (ucp_enables & 0xf0)
      out[1] =
         create_clipdist_var(shader, ++maxloc, true, VARYING_SLOT_CLIP_DIST1);

   nir_foreach_overload(shader, overload) {
      if (!strcmp(overload->function->name, "main"))
         lower_clip_vs(overload->impl, ucp_enables, cv, out);
   }
}

/*
 * FS lowering
 */

static void
lower_clip_fs(nir_function_impl *impl, unsigned ucp_enables,
              nir_variable **in)
{
   nir_ssa_def *clipdist[MAX_CLIP_PLANES];
   nir_builder b;

   nir_builder_init(&b, impl);
   b.cursor = nir_before_cf_list(&impl->body);

   if (ucp_enables & 0x0f)
      load_clipdist_input(&b, in[0], &clipdist[0]);
   if (ucp_enables & 0xf0)
      load_clipdist_input(&b, in[1], &clipdist[4]);

   for (int plane = 0; plane < MAX_CLIP_PLANES; plane++) {
      if (ucp_enables & (1 << plane)) {
         nir_intrinsic_instr *discard;
         nir_ssa_def *cond;

         cond = nir_flt(&b, clipdist[plane], nir_imm_float(&b, 0.0));

         discard = nir_intrinsic_instr_create(b.shader,
                                              nir_intrinsic_discard_if);
         discard->src[0] = nir_src_for_ssa(cond);
         nir_builder_instr_insert(&b, &discard->instr);
      }
   }
}

/* insert conditional kill based on interpolated CLIPDIST
 */
void
nir_lower_clip_fs(nir_shader *shader, unsigned ucp_enables)
{
   nir_variable *in[2];
   int maxloc = -1;

   if (!ucp_enables)
      return;

   foreach_list_typed(nir_variable, var, node, &shader->inputs) {
      int loc = var->data.driver_location;

      /* keep track of last used driver-location.. we'll be
       * appending CLIP_DIST0/CLIP_DIST1 after last existing
       * input:
       */
      maxloc = MAX2(maxloc, loc);
   }

   /* The shader won't normally have CLIPDIST inputs, so we
    * must add our own:
    */
   /* insert CLIPDIST outputs: */
   if (ucp_enables & 0x0f)
      in[0] =
         create_clipdist_var(shader, ++maxloc, false,
                             VARYING_SLOT_CLIP_DIST0);
   if (ucp_enables & 0xf0)
      in[1] =
         create_clipdist_var(shader, ++maxloc, false,
                             VARYING_SLOT_CLIP_DIST1);

   nir_foreach_overload(shader, overload) {
      if (!strcmp(overload->function->name, "main"))
         lower_clip_fs(overload->impl, ucp_enables, in);
   }
}
