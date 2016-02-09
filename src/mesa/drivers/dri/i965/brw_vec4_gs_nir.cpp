/*
 * Copyright © 2015 Intel Corporation
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
 */

#include "brw_vec4_gs_visitor.h"

namespace brw {

void
vec4_gs_visitor::nir_setup_inputs()
{
}

void
vec4_gs_visitor::nir_setup_system_value_intrinsic(nir_intrinsic_instr *instr)
{
   dst_reg *reg;

   switch (instr->intrinsic) {
   case nir_intrinsic_load_primitive_id:
      /* We'll just read g1 directly; don't create a temporary. */
      break;

   case nir_intrinsic_load_invocation_id:
      reg = &this->nir_system_values[SYSTEM_VALUE_INVOCATION_ID];
      if (reg->file == BAD_FILE)
         *reg = *this->make_reg_for_system_value(SYSTEM_VALUE_INVOCATION_ID,
                                                 glsl_type::int_type);
      break;

   default:
      vec4_visitor::nir_setup_system_value_intrinsic(instr);
   }

}

void
vec4_gs_visitor::nir_emit_intrinsic(nir_intrinsic_instr *instr)
{
   dst_reg dest;
   src_reg src;

   switch (instr->intrinsic) {
   case nir_intrinsic_load_per_vertex_input: {
      /* The EmitNoIndirectInput flag guarantees our vertex index will
       * be constant.  We should handle indirects someday.
       */
      nir_const_value *vertex = nir_src_as_const_value(instr->src[0]);
      nir_const_value *offset = nir_src_as_const_value(instr->src[1]);

      /* Make up a type...we have no way of knowing... */
      const glsl_type *const type = glsl_type::ivec(instr->num_components);

      src = src_reg(ATTR, BRW_VARYING_SLOT_COUNT * vertex->u[0] +
                          nir_intrinsic_base(instr) + offset->u[0],
                    type);
      dest = get_nir_dest(instr->dest, src.type);
      dest.writemask = brw_writemask_for_size(instr->num_components);
      emit(MOV(dest, src));
      break;
   }

   case nir_intrinsic_load_input:
      unreachable("nir_lower_io should have produced per_vertex intrinsics");

   case nir_intrinsic_emit_vertex_with_counter: {
      this->vertex_count =
         retype(get_nir_src(instr->src[0], 1), BRW_REGISTER_TYPE_UD);
      gs_emit_vertex(nir_intrinsic_stream_id(instr));
      break;
   }

   case nir_intrinsic_end_primitive_with_counter:
      this->vertex_count =
         retype(get_nir_src(instr->src[0], 1), BRW_REGISTER_TYPE_UD);
      gs_end_primitive();
      break;

   case nir_intrinsic_set_vertex_count:
      this->vertex_count =
         retype(get_nir_src(instr->src[0], 1), BRW_REGISTER_TYPE_UD);
      break;

   case nir_intrinsic_load_primitive_id:
      assert(gs_prog_data->include_primitive_id);
      dest = get_nir_dest(instr->dest, BRW_REGISTER_TYPE_D);
      emit(MOV(dest, retype(brw_vec4_grf(1, 0), BRW_REGISTER_TYPE_D)));
      break;

   case nir_intrinsic_load_invocation_id: {
      src_reg invocation_id =
         src_reg(nir_system_values[SYSTEM_VALUE_INVOCATION_ID]);
      assert(invocation_id.file != BAD_FILE);
      dest = get_nir_dest(instr->dest, invocation_id.type);
      emit(MOV(dest, invocation_id));
      break;
   }

   default:
      vec4_visitor::nir_emit_intrinsic(instr);
   }
}
}
