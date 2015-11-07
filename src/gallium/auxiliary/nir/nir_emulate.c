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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "nir/nir_emulate.h"

#include "glsl/nir/nir_builder.h"

typedef struct {
   nir_shader *shader;
   nir_builder b;
   unsigned flags;
} emu_state;

static nir_variable *
find_output(emu_state *state, unsigned drvloc)
{
   foreach_list_typed(nir_variable, var, node, &state->shader->outputs) {
      if (var->data.driver_location == drvloc)
         return var;
   }
   return NULL;
}

static bool
is_color_output(emu_state *state, nir_variable *out)
{
   switch (state->shader->stage) {
   case MESA_SHADER_VERTEX:
   case MESA_SHADER_GEOMETRY:
      switch (out->data.location) {
      case VARYING_SLOT_COL0:
      case VARYING_SLOT_COL1:
      case VARYING_SLOT_BFC0:
      case VARYING_SLOT_BFC1:
         return true;
      default:
         return false;
      }
      break;
   case MESA_SHADER_FRAGMENT:
      switch (out->data.location) {
      case FRAG_RESULT_COLOR:
         return true;
      default:
         return false;
      }
      break;
   default:
      return false;
   }
}

static void
emu_intrinsic(emu_state *state, nir_intrinsic_instr *intr)
{
   nir_variable *out;
   nir_builder *b = &state->b;
   nir_ssa_def *s;

   assert(state->flags & TGSI_EMU_CLAMP_COLOR_OUTPUTS);

   if (intr->intrinsic != nir_intrinsic_store_output)
      return;

   out = find_output(state, intr->const_index[0]);

   /* NOTE: 'out' can be null for types larger than vec4,
    * but these will never be color out's so we can ignore
    */

   if (out && is_color_output(state, out)) {
      b->cursor = nir_before_instr(&intr->instr);
      s = nir_ssa_for_src(b, intr->src[0], intr->num_components);
      s = nir_fsat(b, s);
      nir_instr_rewrite_src(&intr->instr, &intr->src[0], nir_src_for_ssa(s));
   }
}

static bool
emu_block(nir_block *block, void *_state)
{
   emu_state *state = _state;

   /* early return if we don't need per-instruction lowering: */
   if (!(state->flags & TGSI_EMU_CLAMP_COLOR_OUTPUTS))
      return false;

   nir_foreach_instr_safe(block, instr) {
      if (instr->type == nir_instr_type_intrinsic)
         emu_intrinsic(state, nir_instr_as_intrinsic(instr));
   }

   return true;
}
static void
emu_impl(emu_state *state, nir_function_impl *impl)
{
   nir_builder_init(&state->b, impl);

   nir_foreach_block(impl, emu_block, state);
   nir_metadata_preserve(impl, nir_metadata_block_index |
                               nir_metadata_dominance);
}

void nir_emulate(nir_shader *shader, unsigned flags)
{
   emu_state state = {
      .shader = shader,
      .flags = flags,
   };

   assert(flags != 0);
   assert(flags == TGSI_EMU_CLAMP_COLOR_OUTPUTS);  // todo others..

   nir_foreach_overload(shader, overload) {
      if (overload->impl)
         emu_impl(&state, overload->impl);
   }
}
