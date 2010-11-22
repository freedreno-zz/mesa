/*
 * Copyright © 2010 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * \file lower_instructions.cpp
 *
 * Many GPUs lack native instructions for certain expression operations, and
 * must replace them with some other expression tree.  This pass lowers some
 * of the most common cases, allowing the lowering code to be implemented once
 * rather than in each driver backend.
 *
 * Currently supported transformations:
 * - SUB_TO_ADD_NEG
 * - DIV_TO_MUL_RCP
 * - EXP_TO_EXP2
 * - EXP_TO_POW
 * - POW_TO_EXP2
 * - LOG_TO_LOG2
 * - MOD_TO_FRACT
 * - LIT_TO_POW_FLAT
 *
 * SUB_TO_ADD_NEG:
 * ---------------
 * Breaks an ir_binop_sub expression down to add(op0, neg(op1))
 *
 * This simplifies expression reassociation, and for many backends
 * there is no subtract operation separate from adding the negation.
 * For backends with native subtract operations, they will probably
 * want to recognize add(op0, neg(op1)) or the other way around to
 * produce a subtract anyway.
 *
 * DIV_TO_MUL_RCP:
 * ---------------
 * Breaks an ir_unop_div expression down to op0 * (rcp(op1)).
 *
 * Many GPUs don't have a divide instruction (945 and 965 included),
 * but they do have an RCP instruction to compute an approximate
 * reciprocal.  By breaking the operation down, constant reciprocals
 * can get constant folded.
 *
 * EXP_TO_EXP2 and LOG_TO_LOG2:
 * ----------------------------
 * Many GPUs don't have a base e log or exponent instruction, but they
 * do have base 2 versions, so this pass converts exp and log to exp2
 * and log2 operations.
 *
 * EXP_TO_POW:
 * -----------
 * Few if any GPUs have an instruction for e**x, but they may have an x**y
 * instruction.  For these GPUs, convert \c ir_unop_exp to a \c ir_binop_pow
 * with an immediate value of e for the first parameter.
 *
 * POW_TO_EXP2:
 * -----------
 * Many older GPUs don't have an x**y instruction.  For these GPUs, convert
 * x**y to 2**(y * log2(x)).
 *
 * MOD_TO_FRACT:
 * -------------
 * Breaks an ir_unop_mod expression down to (op1 * fract(op0 / op1))
 *
 * Many GPUs don't have a MOD instruction (945 and 965 included), and
 * if we have to break it down like this anyway, it gives an
 * opportunity to do things like constant fold the (1.0 / op1) easily.
 *
 * LIT_TO_POW_FLAT:
 * ----------------
 * Lower the LIT instruction into a sequence of equivalent instructions.
 *
 * New GPUs have removed support for the CISC-like LIT instruction.  Instead,
 * this must be implemented using a sequence of simpler instructions.  Even some
 * older GPUs, such as i915, lack support for a LIT instruction.  This version
 * of the lowering pass lowers \c ir_unop_lit to a sequence of IR that does
 * \b not include an if-statement.  In the future it may be beneficial to add
 * a version of the lowering pass that generates an if-statement.
 */

#include "main/core.h" /* for M_LOG2E */
#include "glsl_types.h"
#include "ir.h"
#include "ir_optimization.h"

class lower_instructions_visitor : public ir_hierarchical_visitor {
public:
   lower_instructions_visitor(unsigned lower)
      : progress(false), lower(lower) { }

   ir_visitor_status visit_leave(ir_expression *);

   bool progress;

private:
   unsigned lower; /** Bitfield of which operations to lower */

   void sub_to_add_neg(ir_expression *);
   void div_to_mul_rcp(ir_expression *);
   void mod_to_fract(ir_expression *);
   void exp_to_exp2(ir_expression *);
   void exp_to_pow(ir_expression *);
   void pow_to_exp2(ir_expression *);
   void log_to_log2(ir_expression *);
   void lit_to_pow_flat(ir_expression *ir);
};

/**
 * Determine if a particular type of lowering should occur
 */
#define lowering(x) (this->lower & x)

bool
lower_instructions(exec_list *instructions, unsigned what_to_lower)
{
   lower_instructions_visitor v(what_to_lower);

   visit_list_elements(&v, instructions);
   return v.progress;
}

void
lower_instructions_visitor::sub_to_add_neg(ir_expression *ir)
{
   ir->operation = ir_binop_add;
   ir->operands[1] = new(ir) ir_expression(ir_unop_neg, ir->operands[1]->type,
					   ir->operands[1], NULL);
   this->progress = true;
}

void
lower_instructions_visitor::div_to_mul_rcp(ir_expression *ir)
{
   if (!ir->operands[1]->type->is_integer()) {
      /* New expression for the 1.0 / op1 */
      ir_rvalue *expr;
      expr = new(ir) ir_expression(ir_unop_rcp,
				   ir->operands[1]->type,
				   ir->operands[1],
				   NULL);

      /* op0 / op1 -> op0 * (1.0 / op1) */
      ir->operation = ir_binop_mul;
      ir->operands[1] = expr;
   } else {
      /* Be careful with integer division -- we need to do it as a
       * float and re-truncate, since rcp(n > 1) of an integer would
       * just be 0.
       */
      ir_rvalue *op0, *op1;
      const struct glsl_type *vec_type;

      vec_type = glsl_type::get_instance(GLSL_TYPE_FLOAT,
					 ir->operands[1]->type->vector_elements,
					 ir->operands[1]->type->matrix_columns);

      if (ir->operands[1]->type->base_type == GLSL_TYPE_INT)
	 op1 = new(ir) ir_expression(ir_unop_i2f, vec_type, ir->operands[1], NULL);
      else
	 op1 = new(ir) ir_expression(ir_unop_u2f, vec_type, ir->operands[1], NULL);

      op1 = new(ir) ir_expression(ir_unop_rcp, op1->type, op1, NULL);

      vec_type = glsl_type::get_instance(GLSL_TYPE_FLOAT,
					 ir->operands[0]->type->vector_elements,
					 ir->operands[0]->type->matrix_columns);

      if (ir->operands[0]->type->base_type == GLSL_TYPE_INT)
	 op0 = new(ir) ir_expression(ir_unop_i2f, vec_type, ir->operands[0], NULL);
      else
	 op0 = new(ir) ir_expression(ir_unop_u2f, vec_type, ir->operands[0], NULL);

      op0 = new(ir) ir_expression(ir_binop_mul, vec_type, op0, op1);

      ir->operation = ir_unop_f2i;
      ir->operands[0] = op0;
      ir->operands[1] = NULL;
   }

   this->progress = true;
}

void
lower_instructions_visitor::exp_to_exp2(ir_expression *ir)
{
   ir_constant *log2_e = new(ir) ir_constant(float(M_LOG2E));

   ir->operation = ir_unop_exp2;
   ir->operands[0] = new(ir) ir_expression(ir_binop_mul, ir->operands[0]->type,
					   ir->operands[0], log2_e);
   this->progress = true;
}

void
lower_instructions_visitor::exp_to_pow(ir_expression *ir)
{
   ir->operation = ir_binop_pow;
   ir->operands[1] = ir->operands[0];
   ir->operands[0] = new(ir) ir_constant(float(M_E));
   this->progress = true;
}

void
lower_instructions_visitor::pow_to_exp2(ir_expression *ir)
{
   ir_expression *const log2_x =
      new(ir) ir_expression(ir_unop_log2, ir->operands[0]->type,
			    ir->operands[0]);

   ir->operation = ir_unop_exp2;
   ir->operands[0] = new(ir) ir_expression(ir_binop_mul, ir->operands[1]->type,
					   ir->operands[1], log2_x);
   ir->operands[1] = NULL;
   this->progress = true;
}

void
lower_instructions_visitor::log_to_log2(ir_expression *ir)
{
   ir->operation = ir_binop_mul;
   ir->operands[0] = new(ir) ir_expression(ir_unop_log2, ir->operands[0]->type,
					   ir->operands[0], NULL);
   ir->operands[1] = new(ir) ir_constant(float(1.0 / M_LOG2E));
   this->progress = true;
}

void
lower_instructions_visitor::mod_to_fract(ir_expression *ir)
{
   ir_variable *temp = new(ir) ir_variable(ir->operands[1]->type, "mod_b",
					   ir_var_temporary);
   this->base_ir->insert_before(temp);

   ir_assignment *const assign =
      new(ir) ir_assignment(new(ir) ir_dereference_variable(temp),
			    ir->operands[1], NULL);

   this->base_ir->insert_before(assign);

   ir_expression *const div_expr =
      new(ir) ir_expression(ir_binop_div, ir->operands[0]->type,
			    ir->operands[0],
			    new(ir) ir_dereference_variable(temp));

   /* Don't generate new IR that would need to be lowered in an additional
    * pass.
    */
   if (lowering(DIV_TO_MUL_RCP))
      div_to_mul_rcp(div_expr);

   ir_rvalue *expr = new(ir) ir_expression(ir_unop_fract,
					   ir->operands[0]->type,
					   div_expr,
					   NULL);

   ir->operation = ir_binop_mul;
   ir->operands[0] = new(ir) ir_dereference_variable(temp);
   ir->operands[1] = expr;
   this->progress = true;
}

void
lower_instructions_visitor::lit_to_pow_flat(ir_expression *ir)
{
   ir_instruction *inst;

   /* The ARB_vertex_program spec says that LIT does:
    *
    *    tmp = VectorLoad(op0);
    *    if (tmp.x < 0) tmp.x = 0;
    *    if (tmp.y < 0) tmp.y = 0;
    *    if (tmp.w < -(128.0-epsilon)) tmp.w = -(128.0-epsilon);
    *    else if (tmp.w > 128-epsilon) tmp.w = 128-epsilon;
    *    result.x = 1.0;
    *    result.y = tmp.x;
    *    result.z = (tmp.x > 0) ? RoughApproxPower(tmp.y, tmp.w) : 0.0;
    *    result.w = 1.0;
    *
    * This can be lowered to:
    *
    *    tmp.yzw = max(vec3(0.0, 0.0, -(128.0 - epsilon)), op0.xyw);
    *    tmp.w = min(128.0 - epsilon, tmp.w);
    *    tmp.z = pow(tmp.z, tmp.w);
    *    tmp.xw = vec2(1.0, 1.0);
    *    if (tmp.y <= 0)
    *        tmp.z = 0;
    */

   ir_variable *const tmp_var =
      new(ir) ir_variable(glsl_type::vec4_type, "lit_tmp", ir_var_temporary);
   this->base_ir->insert_before(tmp_var);

   /* Generate 'tmp.yzw = max(vec3(0.0, 0.0, -(128.0 - epsilon)), op0.xyw);'
    * The "other" API defined the minimum and maximum values used here as the
    * values that can be represented in an 8.8 fixed-point value.
    */
   ir_constant_data clamp_data = { { 0 } };
   clamp_data.f[2] = (float) -(double(0x7fff) / 256.0);

   ir_expression *const max_expr =
      new(ir) ir_expression(ir_binop_max, glsl_type::vec3_type,
			    new(ir) ir_constant(glsl_type::vec3_type,
						&clamp_data),
			    new(ir) ir_swizzle(ir->operands[0], 0, 1, 3, 0, 3));
   inst = new(ir) ir_assignment(new(ir) ir_dereference_variable(tmp_var),
				max_expr, NULL, 0x0E);
   this->base_ir->insert_before(inst);

   /* Generate 'tmp.w = min(128.0 - epsilon, tmp.w);'
    */
   ir_rvalue *const tmp_w =
      new(ir) ir_swizzle(new(ir) ir_dereference_variable(tmp_var),
			 3, 3, 3, 3, 1);
   ir_expression *const min_expr =
      new(ir) ir_expression(ir_binop_min, glsl_type::float_type,
			    new(ir) ir_constant(-clamp_data.f[2]),
			    tmp_w);
   inst = new(ir) ir_assignment(new(ir) ir_dereference_variable(tmp_var),
				min_expr, NULL, (1U << 3));
   this->base_ir->insert_before(inst);

   /* Generate 'tmp.z = pow(tmp.z, tmp.w);'
    */
   ir_rvalue *const tmp_z =
      new(ir) ir_swizzle(new(ir) ir_dereference_variable(tmp_var),
			 2, 2, 2, 2, 1);
   ir_expression *const pow_expr =
      new(ir) ir_expression(ir_binop_pow, glsl_type::float_type,
			    tmp_z, tmp_w->clone(ir, NULL));

   inst = new(ir) ir_assignment(new(ir) ir_dereference_variable(tmp_var),
				pow_expr,
				NULL,
				(1U << 2));
   this->base_ir->insert_before(inst);

   /* Generate 'tmp.xw = vec2(1.0, 1.0);'
    */
   ir_constant_data output_data = { { 0 } };
   output_data.f[0] = 1.0F;
   output_data.f[1] = 1.0F;

   inst = new(ir) ir_assignment(new(ir) ir_dereference_variable(tmp_var),
				new(ir) ir_constant(glsl_type::vec2_type,
						    &output_data),
				NULL,
				0x09);
   this->base_ir->insert_before(inst);

   /* Generate 'if (tmp.y <= 0) tmp.z = 0;'
    */
   ir_rvalue *const tmp_y =
      new(ir) ir_swizzle(new(ir) ir_dereference_variable(tmp_var),
			 1, 1, 1, 1, 1);
   ir_expression *const cmp_expr =
      new(ir) ir_expression(ir_binop_lequal,
			    glsl_type::bool_type,
			    tmp_y,
			    new(ir) ir_constant(0.0F));

   inst = new(ir) ir_assignment(new(ir) ir_dereference_variable(tmp_var),
				new(ir) ir_constant(0.0F),
				cmp_expr,
				(1U << 2));
   this->base_ir->insert_before(inst);

   /* FINISHME: Convert lower_instructions_visitor to an ir_rvalue_visitor so
    * FINISHME: that this ugly hack can be removed.
    */
   ir->operation = ir_binop_add;
   ir->operands[0] = new(ir) ir_dereference_variable(tmp_var);
   ir->operands[1] = ir_constant::zero(ir, glsl_type::vec4_type);

   this->progress = true;
}

ir_visitor_status
lower_instructions_visitor::visit_leave(ir_expression *ir)
{
   switch (ir->operation) {
   case ir_unop_lit:
      if (lowering(LIT_TO_POW_FLAT))
	 lit_to_pow_flat(ir);
      break;

   case ir_binop_sub:
      if (lowering(SUB_TO_ADD_NEG))
	 sub_to_add_neg(ir);
      break;

   case ir_binop_div:
      if (lowering(DIV_TO_MUL_RCP))
	 div_to_mul_rcp(ir);
      break;

   case ir_unop_exp:
      if (lowering(EXP_TO_POW))
	 exp_to_pow(ir);
      else if (lowering(EXP_TO_EXP2))
	 exp_to_exp2(ir);
      break;

   case ir_unop_log:
      if (lowering(LOG_TO_LOG2))
	 log_to_log2(ir);
      break;

   case ir_binop_mod:
      if (lowering(MOD_TO_FRACT))
	 mod_to_fract(ir);
      break;

   case ir_binop_pow:
      if (lowering(POW_TO_EXP2))
	 pow_to_exp2(ir);
      break;

   default:
      return visit_continue;
   }

   return visit_continue;
}
