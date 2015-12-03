/*
 * Copyright © 2014 Intel Corporation
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
 *    Connor Abbott (cwabbott0@gmail.com)
 *    Jason Ekstrand (jason@jlekstrand.net)
 *
 */

/*
 * This lowering pass converts references to input/output variables with
 * loads/stores to actual input/output intrinsics.
 */

#include "nir.h"
#include "nir_builder.h"

struct lower_io_state {
   nir_builder builder;
   void *mem_ctx;
   int (*type_size)(const struct glsl_type *type);
   nir_variable_mode mode;
};

void
nir_assign_var_locations(struct exec_list *var_list, unsigned *size,
                         int (*type_size)(const struct glsl_type *))
{
   unsigned location = 0;

   nir_foreach_variable(var, var_list) {
      /*
       * UBO's have their own address spaces, so don't count them towards the
       * number of global uniforms
       */
      if ((var->data.mode == nir_var_uniform || var->data.mode == nir_var_shader_storage) &&
          var->interface_type != NULL)
         continue;

      var->data.driver_location = location;
      location += type_size(var->type);
   }

   *size = location;
}

/**
 * Returns true if we're processing a stage whose inputs are arrays indexed
 * by a vertex number (such as geometry shader inputs).
 */
static bool
is_per_vertex_input(struct lower_io_state *state, nir_variable *var)
{
   gl_shader_stage stage = state->builder.shader->stage;

   return var->data.mode == nir_var_shader_in && !var->data.patch &&
          (stage == MESA_SHADER_TESS_CTRL ||
           stage == MESA_SHADER_TESS_EVAL ||
           stage == MESA_SHADER_GEOMETRY);
}

static bool
is_per_vertex_output(struct lower_io_state *state, nir_variable *var)
{
   gl_shader_stage stage = state->builder.shader->stage;
   return var->data.mode == nir_var_shader_out && !var->data.patch &&
          stage == MESA_SHADER_TESS_CTRL;
}

static nir_ssa_def *
get_io_offset(nir_builder *b, nir_deref_var *deref,
              nir_ssa_def **vertex_index,
              int (*type_size)(const struct glsl_type *))
{
   nir_deref *tail = &deref->deref;

   /* For per-vertex input arrays (i.e. geometry shader inputs), keep the
    * outermost array index separate.  Process the rest normally.
    */
   if (vertex_index != NULL) {
      tail = tail->child;
      assert(tail->deref_type == nir_deref_type_array);
      nir_deref_array *deref_array = nir_deref_as_array(tail);

      nir_ssa_def *vtx = nir_imm_int(b, deref_array->base_offset);
      if (deref_array->deref_array_type == nir_deref_array_type_indirect) {
         vtx = nir_iadd(b, vtx, nir_ssa_for_src(b, deref_array->indirect, 1));
      }
      *vertex_index = vtx;
   }

   /* Just emit code and let constant-folding go to town */
   nir_ssa_def *offset = nir_imm_int(b, 0);

   while (tail->child != NULL) {
      const struct glsl_type *parent_type = tail->type;
      tail = tail->child;

      if (tail->deref_type == nir_deref_type_array) {
         nir_deref_array *deref_array = nir_deref_as_array(tail);
         unsigned size = type_size(tail->type);

         offset = nir_iadd(b, offset,
                           nir_imm_int(b, size * deref_array->base_offset));

         if (deref_array->deref_array_type == nir_deref_array_type_indirect) {
            nir_ssa_def *mul =
               nir_imul(b, nir_imm_int(b, size),
                        nir_ssa_for_src(b, deref_array->indirect, 1));

            offset = nir_iadd(b, offset, mul);
         }
      } else if (tail->deref_type == nir_deref_type_struct) {
         nir_deref_struct *deref_struct = nir_deref_as_struct(tail);

         unsigned field_offset = 0;
         for (unsigned i = 0; i < deref_struct->index; i++) {
            field_offset += type_size(glsl_get_struct_field(parent_type, i));
         }
         offset = nir_iadd(b, offset, nir_imm_int(b, field_offset));
      }
   }

   return offset;
}

static nir_intrinsic_op
load_op(struct lower_io_state *state,
        nir_variable_mode mode, bool per_vertex)
{
   nir_intrinsic_op op;
   switch (mode) {
   case nir_var_shader_in:
      op = per_vertex ? nir_intrinsic_load_per_vertex_input :
                        nir_intrinsic_load_input;
      break;
   case nir_var_shader_out:
      op = per_vertex ? nir_intrinsic_load_per_vertex_output :
                        nir_intrinsic_load_output;
      break;
   case nir_var_uniform:
      op = nir_intrinsic_load_uniform;
      break;
   default:
      unreachable("Unknown variable mode");
   }
   return op;
}

static bool
nir_lower_io_block(nir_block *block, void *void_state)
{
   struct lower_io_state *state = void_state;

   nir_builder *b = &state->builder;

   nir_foreach_instr_safe(block, instr) {
      if (instr->type != nir_instr_type_intrinsic)
         continue;

      nir_intrinsic_instr *intrin = nir_instr_as_intrinsic(instr);

      if (intrin->intrinsic != nir_intrinsic_load_var &&
          intrin->intrinsic != nir_intrinsic_store_var)
         continue;

      nir_variable_mode mode = intrin->variables[0]->var->data.mode;

      if (state->mode != nir_var_all && state->mode != mode)
         continue;

      if (mode != nir_var_shader_in &&
          mode != nir_var_shader_out &&
          mode != nir_var_uniform)
         continue;

      b->cursor = nir_before_instr(instr);

      switch (intrin->intrinsic) {
      case nir_intrinsic_load_var: {
         bool per_vertex =
            is_per_vertex_input(state, intrin->variables[0]->var) ||
            is_per_vertex_output(state, intrin->variables[0]->var);

         nir_ssa_def *offset;
         nir_ssa_def *vertex_index;

         offset = get_io_offset(b, intrin->variables[0],
                                per_vertex ? &vertex_index : NULL,
                                state->type_size);

         nir_intrinsic_instr *load =
            nir_intrinsic_instr_create(state->mem_ctx,
                                       load_op(state, mode, per_vertex));
         load->num_components = intrin->num_components;

         unsigned location = intrin->variables[0]->var->data.driver_location;
         if (mode == nir_var_uniform) {
            load->const_index[0] = location;
         } else {
            offset = nir_iadd(b, offset, nir_imm_int(b, location));
         }

         if (per_vertex)
            load->src[0] = nir_src_for_ssa(vertex_index);

         load->src[per_vertex ? 1 : 0] = nir_src_for_ssa(offset);

         if (intrin->dest.is_ssa) {
            nir_ssa_dest_init(&load->instr, &load->dest,
                              intrin->num_components, NULL);
            nir_ssa_def_rewrite_uses(&intrin->dest.ssa,
                                     nir_src_for_ssa(&load->dest.ssa));
         } else {
            nir_dest_copy(&load->dest, &intrin->dest, state->mem_ctx);
         }

         nir_instr_insert_before(&intrin->instr, &load->instr);
         nir_instr_remove(&intrin->instr);
         break;
      }

      case nir_intrinsic_store_var: {
         assert(mode == nir_var_shader_out);

         nir_ssa_def *offset;
         nir_ssa_def *vertex_index;

         bool per_vertex =
            is_per_vertex_output(state, intrin->variables[0]->var);

         offset = get_io_offset(b, intrin->variables[0],
                                per_vertex ? &vertex_index : NULL,
                                state->type_size);

         unsigned location = intrin->variables[0]->var->data.driver_location;
         offset = nir_iadd(b, offset, nir_imm_int(b, location));

         nir_intrinsic_op store_op =
            per_vertex ? nir_intrinsic_store_per_vertex_output :
                         nir_intrinsic_store_output;

         nir_intrinsic_instr *store = nir_intrinsic_instr_create(state->mem_ctx,
                                                                 store_op);
         store->num_components = intrin->num_components;

         nir_src_copy(&store->src[0], &intrin->src[0], store);

         if (per_vertex)
            store->src[1] = nir_src_for_ssa(vertex_index);

         store->src[per_vertex ? 2 : 1] = nir_src_for_ssa(offset);

         nir_instr_insert_before(&intrin->instr, &store->instr);
         nir_instr_remove(&intrin->instr);
         break;
      }

      default:
         break;
      }
   }

   return true;
}

static void
nir_lower_io_impl(nir_function_impl *impl,
                  nir_variable_mode mode,
                  int (*type_size)(const struct glsl_type *))
{
   struct lower_io_state state;

   nir_builder_init(&state.builder, impl);
   state.mem_ctx = ralloc_parent(impl);
   state.mode = mode;
   state.type_size = type_size;

   nir_foreach_block(impl, nir_lower_io_block, &state);

   nir_metadata_preserve(impl, nir_metadata_block_index |
                               nir_metadata_dominance);
}

void
nir_lower_io(nir_shader *shader, nir_variable_mode mode,
             int (*type_size)(const struct glsl_type *))
{
   nir_foreach_overload(shader, overload) {
      if (overload->impl)
         nir_lower_io_impl(overload->impl, mode, type_size);
   }
}

/**
 * Return the indirect source for a load/store indirect intrinsic.
 */
nir_src *
nir_get_io_offset_src(nir_intrinsic_instr *instr)
{
   switch (instr->intrinsic) {
   case nir_intrinsic_load_input:
   case nir_intrinsic_load_output:
   case nir_intrinsic_load_uniform:
      return &instr->src[0];
   case nir_intrinsic_load_per_vertex_input:
   case nir_intrinsic_load_per_vertex_output:
   case nir_intrinsic_store_output:
      return &instr->src[1];
   case nir_intrinsic_store_per_vertex_output:
      return &instr->src[2];
   default:
      return NULL;
   }
}

/**
 * Return the vertex index source for a load/store per_vertex intrinsic.
 */
nir_src *
nir_get_io_vertex_index_src(nir_intrinsic_instr *instr)
{
   switch (instr->intrinsic) {
   case nir_intrinsic_load_per_vertex_input:
   case nir_intrinsic_load_per_vertex_output:
      return &instr->src[0];
   case nir_intrinsic_store_per_vertex_output:
      return &instr->src[1];
   default:
      return NULL;
   }
}
