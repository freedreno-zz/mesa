%{
/*
 * Copyright © 2009 Intel Corporation
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "main/mtypes.h"
#include "main/imports.h"
#include "program/program.h"
#include "program/prog_parameter.h"
#include "program/prog_parameter_layout.h"
#include "program/prog_statevars.h"
#include "program/prog_instruction.h"

#include "program/symbol_table.h"

extern void *yy_scan_string(char *);
extern void yy_delete_buffer(void *);
};

extern int yylex(union YYSTYPE*, struct YYLTYPE*, void*);

#include "glsl_types.h"
#include "ir.h"
#include "program/program_parser.h"

static ir_rvalue *saturate_value(void *mem_ctx, unsigned saturate_mode,
    ir_rvalue *expr);

static ir_rvalue *generate_rhs_for_write_mask(void *mem_ctx,
    unsigned write_mask, ir_rvalue *v);

static ir_assignment *emit_vector_assignment(void *mem_ctx,
    ir_dereference *dst, unsigned write_mask, unsigned saturate_mode,
    ir_rvalue *v);

static ir_assignment *emit_scalar_assignment(void *mem_ctx,
    ir_dereference *dst, unsigned write_mask, unsigned saturate_mode,
    ir_rvalue *sc);

static ir_texture *texture_instruction_common(struct asm_parser_state *state,
    enum ir_texture_opcode opcode, ir_rvalue *tex_coord, unsigned unit,
    const glsl_type *sampler_type, struct YYLTYPE *sampler_loc);

static bool declare_variable(struct asm_parser_state *state, ir_variable *var,
    enum asm_type t, struct YYLTYPE *locp);

static int add_state_reference(struct gl_program_parameter_list *param_list,
    const gl_state_index tokens[STATE_LENGTH]);

static int initialize_symbol_from_state(struct gl_program *prog,
    struct asm_symbol *param_var, const unsigned tokens[STATE_LENGTH]);

static int initialize_symbol_from_param(struct gl_program *prog,
    struct asm_symbol *param_var, const unsigned tokens[STATE_LENGTH]);

static int yyparse(struct asm_parser_state *state);

static char *make_error_string(const char *fmt, ...);

static void yyerror(struct YYLTYPE *locp, struct asm_parser_state *state,
    const char *s);

static int validate_inputs(struct YYLTYPE *locp,
    struct asm_parser_state *state);

#define YYLLOC_DEFAULT(Current, Rhs, N)					\
   do {									\
      if (YYID(N)) {							\
	 (Current).first_line = YYRHSLOC(Rhs, 1).first_line;		\
	 (Current).first_column = YYRHSLOC(Rhs, 1).first_column;	\
	 (Current).position = YYRHSLOC(Rhs, 1).position;		\
	 (Current).last_line = YYRHSLOC(Rhs, N).last_line;		\
	 (Current).last_column = YYRHSLOC(Rhs, N).last_column;		\
      } else {								\
	 (Current).first_line = YYRHSLOC(Rhs, 0).last_line;		\
	 (Current).last_line = (Current).first_line;			\
	 (Current).first_column = YYRHSLOC(Rhs, 0).last_column;		\
	 (Current).last_column = (Current).first_column;		\
	 (Current).position = YYRHSLOC(Rhs, 0).position			\
	    + (Current).first_column;					\
      }									\
   } while(YYID(0))

#define YYLEX_PARAM state->scanner
%}

%pure-parser
%locations
%parse-param { struct asm_parser_state *state }
%error-verbose
%lex-param { void *scanner }

%union {
   ir_instruction *inst;
   struct asm_symbol temp_sym;
   struct asm_swizzle_mask swiz_mask;
   struct prog_dst_register dst_reg;
   char *string;
   unsigned result;
   unsigned attrib;
   int integer;
   float real;
   unsigned state[STATE_LENGTH];
   int negate;

   ir_variable *var;
   ir_rvalue *rvalue;

   struct asm_opcode opcode;

   struct {
      ir_dereference *deref;
      unsigned write_mask;
   } lvalue;

   const glsl_type *type;

   struct {
      unsigned swz;
      unsigned rgba_valid:1;
      unsigned xyzw_valid:1;
      unsigned negate:1;
   } ext_swizzle;
}

%token ARBvp_10 ARBfp_10

/* Tokens for assembler pseudo-ops */
%token <integer> ADDRESS
%token ALIAS ATTRIB
%token OPTION OUTPUT
%token PARAM
%token <integer> TEMP
%token END

 /* Tokens for instructions */
%token <opcode> BIN_OP BINSC_OP SAMPLE_OP SCALAR_OP VECTOR_OP
%token <opcode> ARL KIL CMP_OP DP3_OP DP4_OP DPH_OP DST_OP
%token <opcode> LRP_OP MAD_OP MOV_OP PACK_OP
%token <opcode> RFL_OP SCS_OP SET_OP SFL_OP STR_OP SWZ_OP
%token <opcode> TEX_OP TXB_OP TXD_OP TXP_OP UNPACK_OP X2D_OP XPD_OP

%token <integer> INTEGER
%token <real> REAL

%token AMBIENT ATTENUATION
%token BACK
%token CLIP COLOR
%token DEPTH DIFFUSE DIRECTION
%token EMISSION ENV EYE
%token FOG FOGCOORD FRAGMENT FRONT
%token HALF
%token INVERSE INVTRANS
%token LIGHT LIGHTMODEL LIGHTPROD LOCAL
%token MATERIAL MAT_PROGRAM MATRIX MATRIXINDEX MODELVIEW MVP
%token NORMAL
%token OBJECT
%token PALETTE PARAMS PLANE POINT_TOK POINTSIZE POSITION PRIMARY PROGRAM PROJECTION
%token RANGE RESULT ROW
%token SCENECOLOR SECONDARY SHININESS SIZE_TOK SPECULAR SPOT STATE
%token TEXCOORD TEXENV TEXGEN TEXGEN_Q TEXGEN_R TEXGEN_S TEXGEN_T TEXTURE TRANSPOSE
%token TEXTURE_UNIT TEX_1D TEX_2D TEX_3D TEX_CUBE TEX_RECT
%token TEX_SHADOW1D TEX_SHADOW2D TEX_SHADOWRECT
%token TEX_ARRAY1D TEX_ARRAY2D TEX_ARRAYSHADOW1D TEX_ARRAYSHADOW2D 
%token VERTEX VTXATTRIB
%token WEIGHT

%token <string> IDENTIFIER USED_IDENTIFIER
%type <string> string
%token <swiz_mask> MASK4 MASK3 MASK2 MASK1 SWIZZLE
%token DOT_DOT
%token DOT

%type <inst> instruction ALU_instruction TexInstruction
%type <inst> ARL_instruction VECTORop_instruction
%type <inst> SCALARop_instruction BINSCop_instruction BINop_instruction
%type <inst> TRIop_instruction TXD_instruction SWZ_instruction SAMPLE_instruction
%type <inst> KIL_instruction

%type <var> dstReg
%type <lvalue> maskedDstReg
%type <rvalue> maskedAddrReg
%type <rvalue> srcReg scalarUse scalarSrcReg swizzleSrcReg
%type <swiz_mask> scalarSuffix swizzleSuffix extendedSwizzle
%type <ext_swizzle> extSwizComp extSwizSel
%type <swiz_mask> optionalMask

%type <rvalue> progParamArray
%type <integer> addrRegRelOffset addrRegPosOffset addrRegNegOffset
%type <rvalue> progParamArrayMem progParamArrayAbs progParamArrayRel
%type <var> addrReg
%type <swiz_mask> addrComponent addrWriteMask

%type <dst_reg> ccMaskRule ccTest ccMaskRule2 ccTest2 optionalCcMask

%type <result> resultBinding resultColBinding
%type <integer> optFaceType optColorType
%type <integer> optResultFaceType optResultColorType

%type <integer> optTexImageUnitNum texImageUnitNum
%type <integer> optTexCoordUnitNum texCoordUnitNum
%type <integer> optLegacyTexUnitNum legacyTexUnitNum
%type <integer> texImageUnit
%type <type> texTarget
%type <integer> vtxAttribNum

%type <attrib> attribBinding vtxAttribItem fragAttribItem

%type <temp_sym> paramSingleInit paramSingleItemDecl
%type <integer> optArraySize

%type <state> stateSingleItem stateMultipleItem
%type <state> stateMaterialItem
%type <state> stateLightItem stateLightModelItem stateLightProdItem
%type <state> stateTexGenItem stateFogItem stateClipPlaneItem statePointItem
%type <state> stateMatrixItem stateMatrixRow stateMatrixRows
%type <state> stateTexEnvItem stateDepthItem

%type <state> stateLModProperty
%type <state> stateMatrixName optMatrixRows

%type <integer> stateMatProperty
%type <integer> stateLightProperty stateSpotProperty
%type <integer> stateLightNumber stateLProdProperty
%type <integer> stateTexGenType stateTexGenCoord
%type <integer> stateTexEnvProperty
%type <integer> stateFogProperty
%type <integer> stateClipPlaneNum
%type <integer> statePointProperty

%type <integer> stateOptMatModifier stateMatModifier stateMatrixRowNum
%type <integer> stateOptModMatNum stateModMatNum statePaletteMatNum 
%type <integer> stateProgramMatNum

%type <integer> ambDiffSpecProperty

%type <state> programSingleItem progEnvParam progLocalParam
%type <state> programMultipleItem progEnvParams progLocalParams

%type <temp_sym> paramMultipleInit paramMultInitList paramMultipleItem
%type <rvalue> paramSingleItemUse

%type <integer> progEnvParamNum progLocalParamNum
%type <state> progEnvParamNums progLocalParamNums

%type <rvalue> paramConstDecl paramConstUse
%type <rvalue> paramConstScalarDecl paramConstScalarUse paramConstVector
%type <real> signedFloatConstant
%type <negate> optionalSign

%{
extern int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param,
    void *yyscanner);
%}

%%

program: language optionSequence statementSequence END
	;

language: ARBvp_10
	{
	   if (state->prog->Target != GL_VERTEX_PROGRAM_ARB) {
	      yyerror(& @1, state, "invalid fragment program header");

	   }
	   state->mode = ARB_vertex;
	}
	| ARBfp_10
	{
	   if (state->prog->Target != GL_FRAGMENT_PROGRAM_ARB) {
	      yyerror(& @1, state, "invalid vertex program header");
	   }
	   state->mode = ARB_fragment;

	   state->option.TexRect =
	      (state->ctx->Extensions.NV_texture_rectangle != GL_FALSE);
	}
	;

optionSequence: optionSequence option
	|
	;

option: OPTION string ';'
	{
	   int valid = 0;

	   if (state->mode == ARB_vertex) {
	      valid = _mesa_ARBvp_parse_option(state, $2);
	   } else if (state->mode == ARB_fragment) {
	      valid = _mesa_ARBfp_parse_option(state, $2);
	   }


	   free($2);

	   if (!valid) {
	      const char *const err_str = (state->mode == ARB_vertex)
		 ? "invalid ARB vertex program option"
		 : "invalid ARB fragment program option";

	      yyerror(& @2, state, err_str);
	      YYERROR;
	   }
	}
	;

statementSequence: statementSequence statement
	|
	;

statement: instruction ';'
	{
	   if ($1 != NULL) {
	      state->ir.push_tail($1);
	      state->prog->NumInstructions++;
	   }
	}
	| namingStatement ';'
	;

instruction: ALU_instruction
	{
	   $$ = $1;
	   state->prog->NumAluInstructions++;
	}
	| TexInstruction
	{
	   $$ = $1;
	   state->prog->NumTexInstructions++;
	}
	;

ALU_instruction: ARL_instruction
	| VECTORop_instruction
	| SCALARop_instruction
	| BINSCop_instruction
	| BINop_instruction
	| TRIop_instruction
	| SWZ_instruction
	;

TexInstruction: SAMPLE_instruction
	| KIL_instruction
	| TXD_instruction
	;

ARL_instruction: ARL maskedAddrReg ',' scalarSrcReg
	{
	   ir_expression *f2i =
	      new(state) ir_expression(ir_unop_f2i, glsl_type::int_type, $4);

	   $$ = new(state) ir_assignment($2, f2i, NULL);
	}
	;

VECTORop_instruction: VECTOR_OP maskedDstReg ',' swizzleSrcReg
	{
	   ir_rvalue *expr =
	      new(state) ir_expression($1.opcode, $4->type, $4);

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, expr);
	}
	| MOV_OP maskedDstReg ',' swizzleSrcReg
	{
	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, $4);
	}
	| PACK_OP maskedDstReg ',' swizzleSrcReg
	{
	   /* FINISHME: Add support for "pack" opcodes.
	    */
	   $$ = NULL;
	}
	;

SCALARop_instruction: SCALAR_OP maskedDstReg ',' scalarSrcReg
	{
	   ir_rvalue *expr = new(state) ir_expression($1.opcode, $4->type, $4);

	   $$ = emit_scalar_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, expr);
	}
	| SCS_OP maskedDstReg ',' scalarSrcReg
	{
	   ir_rvalue *const angle = $4;

	   /* The ARB_fragment_program spec says, "The z and w components of
	    * the result vector are undefined."  We'll simplify this by leaving
	    * those components unmodified.
	    */
	   $2.write_mask &= WRITEMASK_XY;

	   /* The only known architecture that implements an actual SCS
	    * instruction is i965.  However, the driver doesn't use it.  For
	    * that reason, emit SCS as separate instances of
	    * ir_unop_sin_reduced and ir_unop_cos_reduced.
	    *
	    * Note that if the program contains an instruction like
	    *
	    *     SCS  d.wz, s.x;
	    *
	    * no code will be emitted.
	    */
	   if (($2.write_mask & WRITEMASK_X) != 0) {
	      ir_rvalue *const sin_expr =
		 new(state) ir_expression(ir_unop_sin_reduced,
					  glsl_type::float_type, angle);
	      ir_instruction *const inst =
		 emit_vector_assignment(state,
					$2.deref->clone(state, NULL),
					WRITEMASK_X,
					$1.saturate_mode,
					sin_expr);
	      state->ir.push_tail(inst);
	   }

	   if (($2.write_mask & WRITEMASK_Y) != 0) {
	      ir_rvalue *const cos_expr =
		 new(state) ir_expression(ir_unop_cos_reduced,
					  glsl_type::float_type, angle);
	      ir_instruction *const inst =
		 emit_vector_assignment(state,
					$2.deref->clone(state, NULL),
					WRITEMASK_Y,
					$1.saturate_mode,
					cos_expr);
	      state->ir.push_tail(inst);
	   }

	   $$ = NULL;
	}
	| UNPACK_OP maskedDstReg ',' scalarSrcReg
	{
	   /* FINISHME: Add support for "unpack" opcodes.
	    */
	   $$ = NULL;
	}
	;

BINSCop_instruction: BINSC_OP maskedDstReg ',' scalarSrcReg ',' scalarSrcReg
	{
	   assert($1.opcode == ir_binop_pow);

	   ir_rvalue *expr =
	      new(state) ir_expression($1.opcode, $4->type, $4, $6);

	   $$ = emit_scalar_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, expr);
	}
	;

BINop_instruction: BIN_OP maskedDstReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   ir_rvalue *expr =
	      new(state) ir_expression($1.opcode, $4->type, $4, $6);

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, expr);
	}
	| DP3_OP maskedDstReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   /* Apply vec3 swizzles to the operands.
	    */
	   ir_rvalue *op0 = new(state) ir_swizzle($4, 0, 1, 2, 3, 3);
	   ir_rvalue *op1 = new(state) ir_swizzle($6, 0, 1, 2, 3, 3);

	   ir_rvalue *expr =
	      new(state) ir_expression(ir_binop_dot, glsl_type::float_type,
				       op0, op1);

	   $$ = emit_scalar_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, expr);
	}
	| DP4_OP maskedDstReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   ir_rvalue *expr =
	      new(state) ir_expression(ir_binop_dot, glsl_type::float_type,
				       $4, $6);

	   $$ = emit_scalar_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, expr);
	}
	| DPH_OP maskedDstReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   /* The first operand is replaced with vec4(op0.xyz, 1).  Note that
	    * the operand is only cloned for two of the parameters of the
	    * ir_quadop_vector operation.  This is intentional.
	    */
	   ir_rvalue *const op0 =
	      new(state) ir_expression(ir_quadop_vector,
				       glsl_type::vec4_type,
				       new(state) ir_swizzle($4,
							     0, 0, 0, 0, 1),
				       new(state) ir_swizzle($4->clone(state, NULL),
							     1, 0, 0, 0, 1),
				       new(state) ir_swizzle($4->clone(state, NULL),
							     2, 0, 0, 0, 1),
				       new(state) ir_constant(1.0F));

	   ir_rvalue *expr =
	      new(state) ir_expression(ir_binop_dot, glsl_type::float_type,
				       op0, $6);

	   $$ = emit_scalar_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, expr);
	}
	| DST_OP maskedDstReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   /* The ARB_vertex_program spec says that DST does:
	    *    tmp0 = VectorLoad(op0);
	    *    tmp1 = VectorLoad(op1);
	    *    result.x = 1.0;
	    *    result.y = tmp0.y * tmp1.y;
	    *    result.z = tmp0.z;
	    *    result.w = tmp1.w;
	    *
	    * This is implemented as:
	    *
	    *    result = vec4(1.0, op0.y, op0.z, 1.0)
	    *           * vec4(1.0, op1.y, 1.0,   op1.w);
	    */
	   ir_rvalue *const op0 =
	      new(state) ir_expression(ir_quadop_vector,
				       glsl_type::vec4_type,
				       new(state) ir_constant(1.0F),
				       new(state) ir_swizzle($4,
							     1, 0, 0, 0, 1),
				       new(state) ir_swizzle($4->clone(state, NULL),
							     2, 0, 0, 0, 1),
				       new(state) ir_constant(1.0F));
	   ir_rvalue *const op1 =
	      new(state) ir_expression(ir_quadop_vector,
				       glsl_type::vec4_type,
				       new(state) ir_constant(1.0F),
				       new(state) ir_swizzle($6,
							     1, 0, 0, 0, 1),
				       new(state) ir_constant(1.0F),
				       new(state) ir_swizzle($6->clone(state, NULL),
							     3, 0, 0, 0, 1));
	   ir_rvalue *expr =
	      new(state) ir_expression(ir_binop_mul, glsl_type::vec4_type,
				       op0, op1);

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, expr);
	}
	| RFL_OP maskedDstReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   /* The NV_fragment_program spec says that RFL does:
	    *
	    *    axis = VectorLoad(op0);
	    *    direction = VectorLoad(op1);
	    *    tmp.w = (axis.x * axis.x + axis.y * axis.y +
	    *             axis.z * axis.z);
	    *    tmp.x = (axis.x * direction.x + axis.y * direction.y +
	    *             axis.z * direction.z);
	    *    tmp.x = 2.0 * tmp.x;
	    *    tmp.x = tmp.x / tmp.w;
	    *    result.x = tmp.x * axis.x - direction.x;
	    *    result.y = tmp.x * axis.y - direction.y;
	    *    result.z = tmp.x * axis.z - direction.z;
	    *
	    *  tmp.x = 2.0 * dot(axis, direction) / dot(axis, axis)
	    */
	   ir_rvalue *const axis =
	      new(state) ir_swizzle($4, 0, 1, 2, 3, 3);
	   ir_rvalue *const direction =
	      new(state) ir_swizzle($6, 0, 1, 2, 3, 3);

	   ir_rvalue *denom =
	      new(state) ir_expression(ir_binop_dot, glsl_type::float_type,
				       axis, axis);

	   ir_rvalue *numer =
	      new(state) ir_expression(ir_binop_dot, glsl_type::float_type,
				       axis, direction);
	   ir_rvalue *tmp =
	      new(state) ir_expression(ir_binop_div, glsl_type::float_type,
				       numer, denom);

	   ir_constant *two = new(state) ir_constant(2.0f);

	   ir_rvalue *scale =
	      new(state) ir_expression(ir_binop_mul, glsl_type::float_type,
				       two, tmp);
	   ir_rvalue *scale_swiz =
	      new(state) ir_swizzle(scale, 0, 0, 0, 0, 3);

	   ir_rvalue *mul =
	      new(state) ir_expression(ir_binop_mul, glsl_type::vec3_type,
				       scale_swiz, axis);
	   ir_rvalue *sub =
	      new(state) ir_expression(ir_binop_sub, glsl_type::vec3_type,
				       mul, direction);

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, sub);
	}
	| SET_OP maskedDstReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   ir_rvalue *cmp =
	      new(state) ir_expression($1.opcode, glsl_type::bvec4_type,
				       $4, $6);
	   ir_rvalue *b2f =
	      new(state) ir_expression(ir_unop_b2f, glsl_type::vec4_type, cmp);

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, b2f);
	}
	| SFL_OP maskedDstReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   /* SFL - "set on false" always returns a vector of 0.0.
	    */
	   ir_rvalue *zero = ir_constant::zero(state, glsl_type::float_type);

	   $$ = emit_scalar_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, zero);
	}
	| STR_OP maskedDstReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   /* STR - "set on true" always returns a vector of 1.0.
	    */
	   ir_rvalue *const one = new(state) ir_constant(1.0F);

	   $$ = emit_scalar_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, one);
	}
	| XPD_OP maskedDstReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   /* The ARB_vertex_program spec says that XPD does:
	    *    tmp0 = VectorLoad(op0);
	    *    tmp1 = VectorLoad(op1);
	    *    result.x = tmp0.y * tmp1.z - tmp0.z * tmp1.y;
	    *    result.y = tmp0.z * tmp1.x - tmp0.x * tmp1.z;
	    *    result.z = tmp0.x * tmp1.y - tmp0.y * tmp1.x;
	    *
	    * No known hardware implements XPD as a native instruction.
	    * Instead generate the obvious sequence of multiplies and
	    * subtracts.
	    */
	   ir_expression *const mul1 =
	      new(state) ir_expression(ir_binop_mul, glsl_type::vec3_type,
				       new(state) ir_swizzle($4, 1, 2, 0, 0, 3),
				       new(state) ir_swizzle($6, 2, 0, 1, 0, 3));
	   ir_expression *const mul2 =
	      new(state) ir_expression(ir_binop_mul, glsl_type::vec3_type,
				       new(state) ir_swizzle($4, 2, 0, 1, 0, 3),
				       new(state) ir_swizzle($6, 1, 2, 0, 0, 3));
	   ir_expression *const sub =
	      new(state) ir_expression(ir_binop_sub, glsl_type::vec3_type,
				       mul1, mul2);

	   /* Since we're only generating three values, limit the write mask
	    * to at most .xyz.
	    */
	   $$ = emit_vector_assignment(state, $2.deref,
				       $2.write_mask & WRITEMASK_XYZ,
				       $1.saturate_mode, sub);
	}
	;

TRIop_instruction: CMP_OP maskedDstReg ','
                   swizzleSrcReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   /* The ARB_fragment_program spec says that CMP does:
	    *
	    *    tmp0 = VectorLoad(op0);
	    *    tmp1 = VectorLoad(op1);
	    *    tmp2 = VectorLoad(op2);
	    *    result.x = (tmp0.x < 0.0) ? tmp1.x : tmp2.x;
	    *    result.y = (tmp0.y < 0.0) ? tmp1.y : tmp2.y;
	    *    result.z = (tmp0.z < 0.0) ? tmp1.z : tmp2.z;
	    *    result.w = (tmp0.w < 0.0) ? tmp1.w : tmp2.w;
	    *
	    * This is acomplished using two conditional assignments.  For most
	    * backends, this will result in two CMP instructions being
	    * generated.  This will look like:
	    *
	    *    CMP    dst, op0, op1, dst;
	    *    CMP    dst, op0, dst, op2;
	    *
	    * The peephole optimizer should be able to combine these into a
	    * single CMP instruction.
	    */
	   ir_rvalue *const cmp_rhs =
	      generate_rhs_for_write_mask(state, $2.write_mask, $4);
	   const glsl_type *const cmp_type =
	      glsl_type::get_instance(GLSL_TYPE_BOOL,
				      cmp_rhs->type->vector_elements, 1);
	   ir_rvalue *const cmp_expr =
	      new(state) ir_expression(ir_binop_less, cmp_type, cmp_rhs,
				       ir_constant::zero(state, cmp_rhs->type));
	   ir_rvalue *const not_expr =
	      new(state) ir_expression(ir_binop_gequal, cmp_type,
				       cmp_rhs->clone(state, NULL),
				       ir_constant::zero(state, cmp_rhs->type));

	   ir_rvalue *const op1 =
	      saturate_value(state, $1.saturate_mode,
			     generate_rhs_for_write_mask(state, $2.write_mask,
							 $6));
	   ir_rvalue *const op2 =
	      saturate_value(state, $1.saturate_mode,
			     generate_rhs_for_write_mask(state, $2.write_mask,
							 $8));

	   ir_instruction *inst;

	   inst = new(state) ir_assignment($2.deref,
					   op1,
					   cmp_expr,
					   $2.write_mask);
	   state->ir.push_tail(inst);

	   inst = new(state) ir_assignment($2.deref->clone(state, NULL),
					   op2,
					   not_expr,
					   $2.write_mask);
	   state->ir.push_tail(inst);

	   $$ = NULL;
	}
	| MAD_OP maskedDstReg ','
                   swizzleSrcReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   ir_rvalue *mul =
	      new(state) ir_expression(ir_binop_mul, $4->type, $4, $6);
	   ir_rvalue *expr =
	      new(state) ir_expression(ir_binop_add, mul->type, mul, $8);

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, expr);
	}
	| LRP_OP maskedDstReg ','
                   swizzleSrcReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   /* The ARB_fragment_program spec says that LRP does:
	    *
	    *    tmp0 = VectorLoad(op0);
	    *    tmp1 = VectorLoad(op1);
	    *    tmp2 = VectorLoad(op2);
	    *    result.x = tmp0.x * tmp1.x + (1 - tmp0.x) * tmp2.x;
	    *    result.y = tmp0.y * tmp1.y + (1 - tmp0.y) * tmp2.y;
	    *    result.z = tmp0.z * tmp1.z + (1 - tmp0.z) * tmp2.z;
	    *    result.w = tmp0.w * tmp1.w + (1 - tmp0.w) * tmp2.w;
	    *
	    * The per-component math can be rearranged slightly:
	    *
	    *    result.x = (tmp0.x * tmp1.x) + tmp2.x - (tmp0.x * tmp2.x);
	    *
	    *    result.x = (tmp0.x * tmp1.x) - (tmp0.x * tmp2.x) + tmp2.x;
	    *
	    *    result.x = tmp0.x * (tmp1.x - tmp2.x) + tmp2.x;
	    *
	    * Becomes:
	    *
	    *    SUB tmp, op1, op2;
	    *    MAD result, op0, tmp, op2;
	    */
	   ir_rvalue *sub =
	      new(state) ir_expression(ir_binop_sub, $6->type, $6, $8);
	   ir_rvalue *mul =
	      new(state) ir_expression(ir_binop_mul, $4->type, $4, sub);
	   ir_rvalue *expr =
	      new(state) ir_expression(ir_binop_add, mul->type, mul, $8);

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, expr);
	}
	| X2D_OP maskedDstReg ','
                   swizzleSrcReg ',' swizzleSrcReg ',' swizzleSrcReg
	{
	   /* The NV_fragment_program spec says that X2D does:
	    *
	    *    tmp0 = VectorLoad(op0);
	    *    tmp1 = VectorLoad(op1);
	    *    tmp2 = VectorLoad(op2);
	    *    result.x = tmp0.x + tmp1.x * tmp2.x + tmp1.y * tmp2.y;
	    *    result.y = tmp0.y + tmp1.x * tmp2.z + tmp1.y * tmp2.w;
	    *    result.z = tmp0.x + tmp1.x * tmp2.x + tmp1.y * tmp2.y;
	    *    result.w = tmp0.y + tmp1.x * tmp2.z + tmp1.y * tmp2.w;
	    *
	    * Notice that result.x == result.z and result.y == result.w.
	    *
	    * This can be rewritten as:
	    *
	    *    tmp3 = (tmp0 + (tmp1.xx * tmp2.xz + tmp1.yy * tmp2.yw))
	    *    result = tmp3.xyxy
	    *
	    * Becomes:
	    *
	    *    MAD tmp, op1.xxxx, op2.xzxz, op0.xyxy;
	    *    MAD result, op1.yyyy, op2.ywyw, tmp;
	    */
	   ir_rvalue *const op0 = $4;
	   ir_rvalue *const op1 = $6;
	   ir_rvalue *const op2 = $8;

	   ir_rvalue *op1_xxxx =
	      new(state) ir_swizzle(op1, 0, 0, 0, 0, 4);
	   ir_rvalue *op1_yyyy =
	      new(state) ir_swizzle(op1, 1, 1, 1, 1, 4);
	   ir_rvalue *op2_xzxz =
	      new(state) ir_swizzle(op2, 0, 2, 0, 2, 4);
	   ir_rvalue *op2_ywyw =
	      new(state) ir_swizzle(op2, 1, 3, 1, 3, 4);
	   ir_rvalue *op0_xyxy =
	      new(state) ir_swizzle(op0, 0, 1, 0, 1, 4);

	   ir_rvalue *mul1 =
	      new(state) ir_expression(ir_binop_mul, glsl_type::vec4_type,
				       op1_xxxx, op2_xzxz);
	   ir_rvalue *expr1 =
	      new(state) ir_expression(ir_binop_add, glsl_type::vec4_type,
				       mul1, op0_xyxy);

	   ir_rvalue *mul2 =
	      new(state) ir_expression(ir_binop_mul, glsl_type::vec4_type,
				       op1_yyyy, op2_ywyw);
	   ir_rvalue *expr2 =
	      new(state) ir_expression(ir_binop_add, glsl_type::vec4_type,
				       mul2, expr1);

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, expr2);
	}
	;

SAMPLE_instruction: TEX_OP maskedDstReg ',' swizzleSrcReg ',' texImageUnit ',' texTarget
	{
	   ir_texture *const tex =
	      texture_instruction_common(state, ir_tex, $4, $6, $8, & @8);

	   if (tex == NULL)
	      YYERROR;

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, tex);
	}
	| TXP_OP maskedDstReg ',' swizzleSrcReg ',' texImageUnit ',' texTarget
	{
	   ir_texture *const tex =
	      texture_instruction_common(state, ir_tex, $4, $6, $8, & @8);

	   if (tex == NULL)
	      YYERROR;

	   /* FINISHME: Set projector.  Right now there is now way for the
	    * FINISHME: lexer to communicate the TXP opcode to the parser.
	    */

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, tex);
	}
	| TXB_OP maskedDstReg ',' swizzleSrcReg ',' texImageUnit ',' texTarget
	{
	   ir_texture *const tex =
	      texture_instruction_common(state, ir_txb, $4, $6, $8, & @8);

	   if (tex == NULL)
	      YYERROR;

	   tex->lod_info.bias = new(state) ir_swizzle($4, 3, 3, 3, 3, 1);

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, tex);
	}
	;

KIL_instruction: KIL swizzleSrcReg
	{
	   ir_constant *zero = ir_constant::zero(state, glsl_type::vec4_type);

	   ir_expression *cmp =
	      new(state) ir_expression(ir_binop_less, glsl_type::bvec4_type,
				       $2, zero);

	   ir_expression *any =
	      new(state) ir_expression(ir_unop_any, glsl_type::bool_type, cmp);

	   $$ = new(state) ir_discard(any);
	}
	| KIL ccTest
	{
	   /* FINISHME: Add support for NV-style condition codes.
	    */
	   $$ = NULL;
	}
	;

TXD_instruction: TXD_OP maskedDstReg ',' swizzleSrcReg ',' swizzleSrcReg ',' swizzleSrcReg ',' texImageUnit ',' texTarget
	{
	   ir_texture *const tex =
	      texture_instruction_common(state, ir_txd, $4, $10, $12, & @12);

	   if (tex == NULL)
	      YYERROR;

	   tex->lod_info.grad.dPdx = $6;
	   tex->lod_info.grad.dPdx = $8;

	   $$ = emit_vector_assignment(state, $2.deref, $2.write_mask,
				       $1.saturate_mode, tex);
	}
	;

texImageUnit: TEXTURE_UNIT optTexImageUnitNum
	{
	   $$ = $2;
	}
	;

texTarget: TEX_1D
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_1D,
						false, false, GLSL_TYPE_FLOAT);
	}
	| TEX_2D
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_2D,
						false, false, GLSL_TYPE_FLOAT);
	}
	| TEX_3D
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_3D,
						false, false, GLSL_TYPE_FLOAT);
	}
	| TEX_CUBE
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_CUBE,
						false, false, GLSL_TYPE_FLOAT);
	}
	| TEX_RECT
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_RECT,
						false, false, GLSL_TYPE_FLOAT);
	}
	| TEX_SHADOW1D
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_1D,
						true, false, GLSL_TYPE_FLOAT);
	}
	| TEX_SHADOW2D
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_2D,
						true, false, GLSL_TYPE_FLOAT);
	}
	| TEX_SHADOWRECT
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_RECT,
						true, false, GLSL_TYPE_FLOAT);
	}
	| TEX_ARRAY1D
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_1D,
						false, true, GLSL_TYPE_FLOAT);
	}
	| TEX_ARRAY2D
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_2D,
						false, true, GLSL_TYPE_FLOAT);
	}
	| TEX_ARRAYSHADOW1D
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_1D,
						true, true, GLSL_TYPE_FLOAT);
	}
	| TEX_ARRAYSHADOW2D
	{
	   $$ = glsl_type::get_sampler_instance(GLSL_SAMPLER_DIM_1D,
						true, true, GLSL_TYPE_FLOAT);
	}
	;

SWZ_instruction: SWZ_OP maskedDstReg ',' srcReg ',' extendedSwizzle
	{
	   /* FIXME: Is this correct?  Should the extenedSwizzle be applied
	    * FIXME: to the existing swizzle?
	    */
#if 0
	   $4.Base.Swizzle = $6.swizzle;
	   $4.Base.Negate = $6.mask;

	   $$ = asm_instruction_copy_ctor(& $1, & $2, & $4, NULL, NULL);
#else
	   $$ = NULL;
#endif
	}
	;

scalarSrcReg: optionalSign scalarUse
	{
	   if ($1) {
	      $$ = new(state) ir_expression(ir_unop_neg, $2->type, $2);
	   } else {
	      $$ = $2;
	   }
	}
	| optionalSign '|' scalarUse '|'
	{
	   $$ = $3;

	   if (!state->option.NV_fragment) {
	      yyerror(& @2, state, "unexpected character '|'");
	      YYERROR;
	   }

	   ir_expression *abs_expr =
	      new(state) ir_expression(ir_unop_abs, $3->type, $3);

	   if ($1) {
	      $$ = new(state) ir_expression(ir_unop_neg, abs_expr->type,
					    abs_expr);
	   } else {
	      $$ = abs_expr;
	   }
	}
	;

scalarUse:  srcReg scalarSuffix
	{
	   $$ = new(state) ir_swizzle($1, GET_SWZ($2.swizzle, 0), 0, 0, 0, 1);
	}
	| paramConstScalarUse
	{
	   $$ = $1;
	}
	;

swizzleSrcReg: optionalSign srcReg swizzleSuffix
	{
	   const unsigned swz[4] = {
	      GET_SWZ($3.swizzle, 0), GET_SWZ($3.swizzle, 1),
	      GET_SWZ($3.swizzle, 2), GET_SWZ($3.swizzle, 3)
	   };

	   ir_rvalue *swz_expr = new(state) ir_swizzle($2, swz, 4);

	   if ($1) {
	      $$ = new(state) ir_expression(ir_unop_neg, swz_expr->type,
					    swz_expr);
	   } else {
	      $$ = swz_expr;
	   }
	}
	| optionalSign '|' srcReg swizzleSuffix '|'
	{
	   const unsigned swz[4] = {
	      GET_SWZ($4.swizzle, 0), GET_SWZ($4.swizzle, 1),
	      GET_SWZ($4.swizzle, 2), GET_SWZ($4.swizzle, 3)
	   };

	   ir_rvalue *swz_expr = new(state) ir_swizzle($3, swz, 4);
	   ir_expression *abs_expr =
	      new(state) ir_expression(ir_unop_abs, swz_expr->type, swz_expr);

	   if ($1) {
	      $$ = new(state) ir_expression(ir_unop_neg, swz_expr->type,
					    abs_expr);
	   } else {
	      $$ = abs_expr;
	   }
	}
	;

maskedDstReg: dstReg optionalMask optionalCcMask
	{
	   if ($1->mode == ir_var_out) {
	      /* Technically speaking, this should check that it is in
	       * vertex program mode.  However, PositionInvariant can never be
	       * set in fragment program mode, so it is somewhat irrelevant.
	       */
	      if (state->option.PositionInvariant
	       && ($1->location == VERT_RESULT_HPOS)) {
		 yyerror(& @1, state, "position-invariant programs cannot "
			 "write position");
		 YYERROR;
	      }

	      state->prog->OutputsWritten |= BITFIELD64_BIT($1->location);
	   }

	   $$.deref = new(state) ir_dereference_variable($1);
	   $$.write_mask = $2.mask;

	   /* FINISHME: Handle conditional write masks! */
	}
	;

maskedAddrReg: addrReg addrWriteMask
	{
	   /* FINISHME: Once NV_vertex_program2_option is supported the
	    * FINISHME: addrWriteMask will need to be used.  The right answer
	    * FINISHME: is probably to convert it to a swizzle and let the
	    * FINISHME: ARL/ARR/ARA convert the swizzle into a mask.
	    */
	   $$ = new(state) ir_dereference_variable($1);
	}
	;

extendedSwizzle: extSwizComp ',' extSwizComp ',' extSwizComp ',' extSwizComp
	{
	   const unsigned xyzw_valid =
	      ($1.xyzw_valid << 0)
	      | ($3.xyzw_valid << 1)
	      | ($5.xyzw_valid << 2)
	      | ($7.xyzw_valid << 3);
	   const unsigned rgba_valid =
	      ($1.rgba_valid << 0)
	      | ($3.rgba_valid << 1)
	      | ($5.rgba_valid << 2)
	      | ($7.rgba_valid << 3);

	   /* All of the swizzle components have to be valid in either RGBA
	    * or XYZW.  Note that 0 and 1 are valid in both, so both masks
	    * can have some bits set.
	    *
	    * We somewhat deviate from the spec here.  It would be really hard
	    * to figure out which component is the error, and there probably
	    * isn't a lot of benefit.
	    */
	   if ((rgba_valid != 0x0f) && (xyzw_valid != 0x0f)) {
	      yyerror(& @1, state, "cannot combine RGBA and XYZW swizzle "
		      "components");
	      YYERROR;
	   }

	   $$.swizzle = MAKE_SWIZZLE4($1.swz, $3.swz, $5.swz, $7.swz);
	   $$.mask = ($1.negate) | ($3.negate << 1) | ($5.negate << 2)
	      | ($7.negate << 3);
	}
	;

extSwizComp: optionalSign extSwizSel
	{
	   $$ = $2;
	   $$.negate = ($1) ? 1 : 0;
	}
	;

extSwizSel: INTEGER
	{
	   if (($1 != 0) && ($1 != 1)) {
	      yyerror(& @1, state, "invalid extended swizzle selector");
	      YYERROR;
	   }

	   $$.swz = ($1 == 0) ? SWIZZLE_ZERO : SWIZZLE_ONE;

	   /* 0 and 1 are valid for both RGBA swizzle names and XYZW
	    * swizzle names.
	    */
	   $$.xyzw_valid = 1;
	   $$.rgba_valid = 1;
	}
	| string
	{
	   char s;

	   if (strlen($1) > 1) {
	      yyerror(& @1, state, "invalid extended swizzle selector");
	      YYERROR;
	   }

	   s = $1[0];
	   free($1);

	   switch (s) {
	   case 'x':
	      $$.swz = SWIZZLE_X;
	      $$.xyzw_valid = 1;
	      break;
	   case 'y':
	      $$.swz = SWIZZLE_Y;
	      $$.xyzw_valid = 1;
	      break;
	   case 'z':
	      $$.swz = SWIZZLE_Z;
	      $$.xyzw_valid = 1;
	      break;
	   case 'w':
	      $$.swz = SWIZZLE_W;
	      $$.xyzw_valid = 1;
	      break;

	   case 'r':
	      $$.swz = SWIZZLE_X;
	      $$.rgba_valid = 1;
	      break;
	   case 'g':
	      $$.swz = SWIZZLE_Y;
	      $$.rgba_valid = 1;
	      break;
	   case 'b':
	      $$.swz = SWIZZLE_Z;
	      $$.rgba_valid = 1;
	      break;
	   case 'a':
	      $$.swz = SWIZZLE_W;
	      $$.rgba_valid = 1;
	      break;

	   default:
	      yyerror(& @1, state, "invalid extended swizzle selector");
	      YYERROR;
	      break;
	   }
	}
	;

srcReg: USED_IDENTIFIER /* temporaryReg | progParamSingle */
	{
	   ir_variable *const var = (ir_variable *)
	      _mesa_symbol_table_find_symbol(state->st, 0, $1);

	   free($1);

	   if (var == NULL) {
	      yyerror(& @1, state, "invalid operand variable");
	      YYERROR;
	   }

	   switch (ir_variable_mode(var->mode)) {
	   case ir_var_auto:
	   case ir_var_temporary:
	      break;

	   case ir_var_uniform:
	      if (var->type->is_array()) {
		 yyerror(& @1, state, "non-array access to array PARAM");
		 YYERROR;
	      }
	      break;

	   case ir_var_in:
	      state->prog->InputsRead |= (1U << var->location);
	      if (!validate_inputs(& @1, state)) {
		 YYERROR;
	      }
	      break;

	   case ir_var_out:
	   case ir_var_inout:
	      yyerror(& @1, state, "invalid operand variable");
	      YYERROR;
	   }

	   $$ = new(state) ir_dereference_variable(var);
	}
	| attribBinding
	{
#if 0
	   set_src_reg(& $$, PROGRAM_INPUT, $1);
	   state->prog->InputsRead |= (1U << $$.Base.Index);

	   if (!validate_inputs(& @1, state)) {
	      YYERROR;
	   }
#else
	   $$ = NULL;
#endif
	}
	| progParamArray '[' progParamArrayMem ']'
	{
	   ir_constant *c = $3->as_constant();
	   if ((c != NULL) && (c->value.u[0] >= $1->type->length)) {
	      yyerror(& @3, state, "out of bounds array access");
	      YYERROR;
	   }

	   $$ = new(state) ir_dereference_array($1, $3);
	}
	| paramSingleItemUse
	{
	   $$ = $1;
	}
	;

dstReg: resultBinding
	{
#if 0
	   set_dst_reg(& $$, PROGRAM_OUTPUT, $1);
#else
	   $$ = NULL;
#endif
	}
	| USED_IDENTIFIER /* temporaryReg | vertexResultReg */
	{
	   ir_variable *const var = (ir_variable *)
	      _mesa_symbol_table_find_symbol(state->st, 0, $1);

	   free($1);

	   if (var == NULL) {
	      yyerror(& @1, state, "invalid operand variable");
	      YYERROR;
	   } else if ((var->mode != ir_var_auto)
		      && (var->mode != ir_var_out)
		      && (var->mode != ir_var_inout)
		      && (var->mode != ir_var_temporary)) {
	      yyerror(& @1, state, "invalid operand variable");
	      YYERROR;
	   } else {
	      $$ = var;
	   }
	}
	;

progParamArray: USED_IDENTIFIER
	{
	   ir_variable *const var = (ir_variable *)
	      _mesa_symbol_table_find_symbol(state->st, 0, $1);

	   free($1);

	   if (var == NULL) {
	      yyerror(& @1, state, "invalid operand variable");
	      YYERROR;
	   } else if (!var->type->is_array()) {
	      yyerror(& @1, state, "array access to non-PARAM variable");
	      YYERROR;
	   } else {
	      $$ = new(state) ir_dereference_variable(var);
	   }
	}
	;

progParamArrayMem: progParamArrayAbs | progParamArrayRel;

progParamArrayAbs: INTEGER
	{
	   $$ = new(state) ir_constant(int($1));
	}
	;

progParamArrayRel: addrReg addrComponent addrRegRelOffset
	{
	   /* FINISHME: Add support for 4-component address registers.
	    */
	   ir_dereference_variable *deref =
	      new(state) ir_dereference_variable($1);

	   if ($3 != 0) {
	      ir_constant *c = new(state) ir_constant(int($3));

	      $$ = new(state) ir_expression(ir_binop_add, glsl_type::int_type,
					    deref, c);
	   } else {
	      $$ = deref;
	   }
	}
	;

addrRegRelOffset:              { $$ = 0; }
	| '+' addrRegPosOffset { $$ = $2; }
	| '-' addrRegNegOffset { $$ = -$2; }
	;

addrRegPosOffset: INTEGER
	{
	   if (($1 < 0) || ($1 > (state->limits->MaxAddressOffset - 1))) {
              char s[100];
              _mesa_snprintf(s, sizeof(s),
                             "relative address offset too large (%d)", $1);
	      yyerror(& @1, state, s);
	      YYERROR;
	   } else {
	      $$ = $1;
	   }
	}
	;

addrRegNegOffset: INTEGER
	{
	   if (($1 < 0) || ($1 > state->limits->MaxAddressOffset)) {
              char s[100];
              _mesa_snprintf(s, sizeof(s),
                             "relative address offset too large (%d)", $1);
	      yyerror(& @1, state, s);
	      YYERROR;
	   } else {
	      $$ = $1;
	   }
	}
	;

addrReg: USED_IDENTIFIER
	{
	   ir_variable *const var = (ir_variable *)
	      _mesa_symbol_table_find_symbol(state->st, 0, $1);

	   free($1);

	   if (var == NULL) {
	      yyerror(& @1, state, "invalid array member");
	      YYERROR;
	   } else if (!var->type->is_integer()) {
	      yyerror(& @1, state,
		      "invalid variable for indexed array access");
	      YYERROR;
	   } else {
	      $$ = var;
	   }
	}
	;

addrComponent: MASK1
	{
	   if ($1.mask != WRITEMASK_X) {
	      yyerror(& @1, state, "invalid address component selector");
	      YYERROR;
	   } else {
	      $$ = $1;
	   }
	}
	;

addrWriteMask: MASK1
	{
	   if ($1.mask != WRITEMASK_X) {
	      yyerror(& @1, state,
		      "address register write mask must be \".x\"");
	      YYERROR;
	   } else {
	      $$ = $1;
	   }
	}
	;

scalarSuffix: MASK1;

swizzleSuffix: MASK1
	| MASK4
	| SWIZZLE
	|              { $$.swizzle = SWIZZLE_NOOP; $$.mask = WRITEMASK_XYZW; }
	;

optionalMask: MASK4 | MASK3 | MASK2 | MASK1 
	|              { $$.swizzle = SWIZZLE_NOOP; $$.mask = WRITEMASK_XYZW; }
	;

optionalCcMask: '(' ccTest ')'
	{
	   $$ = $2;
	}
	| '(' ccTest2 ')'
	{
	   $$ = $2;
	}
	|
	{
	   $$.CondMask = COND_TR;
	   $$.CondSwizzle = SWIZZLE_NOOP;
	   $$.CondSrc = 0;
	}
	;

ccTest: ccMaskRule swizzleSuffix
	{
	   $$ = $1;
	   $$.CondSwizzle = $2.swizzle;
	}
	;

ccTest2: ccMaskRule2 swizzleSuffix
	{
	   $$ = $1;
	   $$.CondSwizzle = $2.swizzle;
	}
	;

ccMaskRule: IDENTIFIER
	{
	   const int cond = _mesa_parse_cc($1);
	   if ((cond == 0) || ($1[2] != '\0')) {
	      char *const err_str =
		 make_error_string("invalid condition code \"%s\"", $1);

	      yyerror(& @1, state, (err_str != NULL)
		      ? err_str : "invalid condition code");

	      if (err_str != NULL) {
		 free(err_str);
	      }

	      YYERROR;
	   }

	   $$.CondMask = cond;
	   $$.CondSwizzle = SWIZZLE_NOOP;
	   $$.CondSrc = 0;
	}
	;

ccMaskRule2: USED_IDENTIFIER
	{
	   const int cond = _mesa_parse_cc($1);
	   if ((cond == 0) || ($1[2] != '\0')) {
	      char *const err_str =
		 make_error_string("invalid condition code \"%s\"", $1);

	      yyerror(& @1, state, (err_str != NULL)
		      ? err_str : "invalid condition code");

	      if (err_str != NULL) {
		 free(err_str);
	      }

	      YYERROR;
	   }

	   $$.CondMask = cond;
	   $$.CondSwizzle = SWIZZLE_NOOP;
	   $$.CondSrc = 0;
	}
	;

namingStatement: ATTRIB_statement
	| PARAM_statement
	| TEMP_statement
	| ADDRESS_statement
	| OUTPUT_statement
	| ALIAS_statement
	;

ATTRIB_statement: ATTRIB IDENTIFIER '=' attribBinding
	{
	   /* Each attribute location can be bound to at most one user-defined
	    * name.  Verify that this run has not been violated.
	    */
	   state->InputsBound |= (1U << $4);
	   if (!validate_inputs(& @4, state)) {
	      YYERROR;
	   }

	   ir_variable *v =
	      new(state) ir_variable(glsl_type::vec4_type, $2, ir_var_in);

	   v->explicit_location = true;
	   v->location = $4;

	   if (!declare_variable(state, v, at_attrib, & @2)) {
	      YYERROR;
	   }

	   state->ir.push_tail(v);
	}
	;

attribBinding: VERTEX vtxAttribItem
	{
	   $$ = $2;
	}
	| FRAGMENT fragAttribItem
	{
	   $$ = $2;
	}
	;

vtxAttribItem: POSITION
	{
	   $$ = VERT_ATTRIB_POS;
	}
	| WEIGHT vtxOptWeightNum
	{
	   $$ = VERT_ATTRIB_WEIGHT;
	}
	| NORMAL
	{
	   $$ = VERT_ATTRIB_NORMAL;
	}
	| COLOR optColorType
	{
	   if (!state->ctx->Extensions.EXT_secondary_color) {
	      yyerror(& @2, state, "GL_EXT_secondary_color not supported");
	      YYERROR;
	   }

	   $$ = VERT_ATTRIB_COLOR0 + $2;
	}
	| FOGCOORD
	{
	   if (!state->ctx->Extensions.EXT_fog_coord) {
	      yyerror(& @1, state, "GL_EXT_fog_coord not supported");
	      YYERROR;
	   }

	   $$ = VERT_ATTRIB_FOG;
	}
	| TEXCOORD optTexCoordUnitNum
	{
	   $$ = VERT_ATTRIB_TEX0 + $2;
	}
	| MATRIXINDEX '[' vtxWeightNum ']'
	{
	   yyerror(& @1, state, "GL_ARB_matrix_palette not supported");
	   YYERROR;
	}
	| VTXATTRIB '[' vtxAttribNum ']'
	{
	   $$ = VERT_ATTRIB_GENERIC0 + $3;
	}
	;

vtxAttribNum: INTEGER
	{
	   if ((unsigned) $1 >= state->limits->MaxAttribs) {
	      yyerror(& @1, state, "invalid vertex attribute reference");
	      YYERROR;
	   }

	   $$ = $1;
	}
	;

vtxOptWeightNum:  | '[' vtxWeightNum ']';
vtxWeightNum: INTEGER;

fragAttribItem: POSITION
	{
	   $$ = FRAG_ATTRIB_WPOS;
	}
	| COLOR optColorType
	{
	   $$ = FRAG_ATTRIB_COL0 + $2;
	}
	| FOGCOORD
	{
	   $$ = FRAG_ATTRIB_FOGC;
	}
	| TEXCOORD optTexCoordUnitNum
	{
	   $$ = FRAG_ATTRIB_TEX0 + $2;
	}
	;

PARAM_statement: PARAM_singleStmt | PARAM_multipleStmt;

PARAM_singleStmt: PARAM IDENTIFIER paramSingleInit
	{
#if 0
	   ir_variable *v =
	      new(state) ir_variable(glsl_type::vec4_type, $2, ir_var_uniform);

	   struct asm_symbol *const s =
	      declare_variable(state, $2, at_param, & @2);

	   if (s == NULL) {
	      free($2);
	      YYERROR;
	   } else {
	      s->param_binding_type = $3.param_binding_type;
	      s->param_binding_begin = $3.param_binding_begin;
	      s->param_binding_length = $3.param_binding_length;
              s->param_binding_swizzle = $3.param_binding_swizzle;
	      s->param_is_array = 0;
	   }
#endif
	}
	;

PARAM_multipleStmt: PARAM IDENTIFIER '[' optArraySize ']' paramMultipleInit
	{
#if 0
	   if (($4 != 0) && ((unsigned) $4 != $6.param_binding_length)) {
	      free($2);
	      yyerror(& @4, state, 
		      "parameter array size and number of bindings must match");
	      YYERROR;
	   } else {
	      struct asm_symbol *const s =
		 declare_variable(state, $2, $6.type, & @2);

	      if (s == NULL) {
		 free($2);
		 YYERROR;
	      } else {
		 s->param_binding_type = $6.param_binding_type;
		 s->param_binding_begin = $6.param_binding_begin;
		 s->param_binding_length = $6.param_binding_length;
                 s->param_binding_swizzle = SWIZZLE_XYZW;
		 s->param_is_array = 1;
	      }
	   }
#endif
	}
	;

optArraySize:
	{
	   $$ = 0;
	}
	| INTEGER
        {
	   if (($1 < 1) || ((unsigned) $1 > state->limits->MaxParameters)) {
	      yyerror(& @1, state, "invalid parameter array size");
	      YYERROR;
	   } else {
	      $$ = $1;
	   }
	}
	;

paramSingleInit: '=' paramSingleItemDecl
	{
	   $$ = $2;
	}
	;

paramMultipleInit: '=' '{' paramMultInitList '}'
	{
	   $$ = $3;
	}
	;

paramMultInitList: paramMultipleItem
	| paramMultInitList ',' paramMultipleItem
	{
	   $1.param_binding_length += $3.param_binding_length;
	   $$ = $1;
	}
	;

paramSingleItemDecl: stateSingleItem
	{
	   memset(& $$, 0, sizeof($$));
	   $$.param_binding_begin = ~0;
	   initialize_symbol_from_state(state->prog, & $$, $1);
	}
	| programSingleItem
	{
	   memset(& $$, 0, sizeof($$));
	   $$.param_binding_begin = ~0;
	   initialize_symbol_from_param(state->prog, & $$, $1);
	}
	| paramConstDecl
	{
	   memset(& $$, 0, sizeof($$));
#if 0
	   $$.param_binding_begin = ~0;
	   initialize_symbol_from_const(state->prog, & $$, & $1, GL_TRUE);
#endif
	}
	;

paramSingleItemUse: stateSingleItem
	{
#if 0
	   memset(& $$, 0, sizeof($$));
	   $$.param_binding_begin = ~0;
	   initialize_symbol_from_state(state->prog, & $$, $1);
#else
	   $$ = NULL;
#endif
	}
	| programSingleItem
	{
#if 0
	   memset(& $$, 0, sizeof($$));
	   $$.param_binding_begin = ~0;
	   initialize_symbol_from_param(state->prog, & $$, $1);
#else
	   $$ = NULL;
#endif
	}
	| paramConstUse
	{
	   $$ = $1;
	}
	;

paramMultipleItem: stateMultipleItem
	{
	   memset(& $$, 0, sizeof($$));
	   $$.param_binding_begin = ~0;
	   initialize_symbol_from_state(state->prog, & $$, $1);
	}
	| programMultipleItem
	{
	   memset(& $$, 0, sizeof($$));
	   $$.param_binding_begin = ~0;
	   initialize_symbol_from_param(state->prog, & $$, $1);
	}
	| paramConstDecl
	{
	   memset(& $$, 0, sizeof($$));
#if 0
	   $$.param_binding_begin = ~0;
	   initialize_symbol_from_const(state->prog, & $$, & $1, GL_FALSE);
#endif
	}
	;

stateMultipleItem: stateSingleItem        { memcpy($$, $1, sizeof($$)); }
	| STATE stateMatrixRows           { memcpy($$, $2, sizeof($$)); }
	;

stateSingleItem: STATE stateMaterialItem  { memcpy($$, $2, sizeof($$)); }
	| STATE stateLightItem            { memcpy($$, $2, sizeof($$)); }
	| STATE stateLightModelItem       { memcpy($$, $2, sizeof($$)); }
	| STATE stateLightProdItem        { memcpy($$, $2, sizeof($$)); }
	| STATE stateTexGenItem           { memcpy($$, $2, sizeof($$)); }
	| STATE stateTexEnvItem           { memcpy($$, $2, sizeof($$)); }
	| STATE stateFogItem              { memcpy($$, $2, sizeof($$)); }
	| STATE stateClipPlaneItem        { memcpy($$, $2, sizeof($$)); }
	| STATE statePointItem            { memcpy($$, $2, sizeof($$)); }
	| STATE stateMatrixRow            { memcpy($$, $2, sizeof($$)); }
	| STATE stateDepthItem            { memcpy($$, $2, sizeof($$)); }
	;

stateMaterialItem: MATERIAL optFaceType stateMatProperty
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = STATE_MATERIAL;
	   $$[1] = $2;
	   $$[2] = $3;
	}
	;

stateMatProperty: ambDiffSpecProperty
	{
	   $$ = $1;
	}
	| EMISSION
	{
	   $$ = STATE_EMISSION;
	}
	| SHININESS
	{
	   $$ = STATE_SHININESS;
	}
	;

stateLightItem: LIGHT '[' stateLightNumber ']' stateLightProperty
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = STATE_LIGHT;
	   $$[1] = $3;
	   $$[2] = $5;
	}
	;

stateLightProperty: ambDiffSpecProperty
	{
	   $$ = $1;
	}
	| POSITION
	{
	   $$ = STATE_POSITION;
	}
	| ATTENUATION
	{
	   if (!state->ctx->Extensions.EXT_point_parameters) {
	      yyerror(& @1, state, "GL_ARB_point_parameters not supported");
	      YYERROR;
	   }

	   $$ = STATE_ATTENUATION;
	}
	| SPOT stateSpotProperty
	{
	   $$ = $2;
	}
	| HALF
	{
	   $$ = STATE_HALF_VECTOR;
	}
	;

stateSpotProperty: DIRECTION
	{
	   $$ = STATE_SPOT_DIRECTION;
	}
	;

stateLightModelItem: LIGHTMODEL stateLModProperty
	{
	   $$[0] = $2[0];
	   $$[1] = $2[1];
	}
	;

stateLModProperty: AMBIENT
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = STATE_LIGHTMODEL_AMBIENT;
	}
	| optFaceType SCENECOLOR
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = STATE_LIGHTMODEL_SCENECOLOR;
	   $$[1] = $1;
	}
	;

stateLightProdItem: LIGHTPROD '[' stateLightNumber ']' optFaceType stateLProdProperty
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = STATE_LIGHTPROD;
	   $$[1] = $3;
	   $$[2] = $5;
	   $$[3] = $6;
	}
	;

stateLProdProperty: ambDiffSpecProperty;

stateTexEnvItem: TEXENV optLegacyTexUnitNum stateTexEnvProperty
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = $3;
	   $$[1] = $2;
	}
	;

stateTexEnvProperty: COLOR
	{
	   $$ = STATE_TEXENV_COLOR;
	}
	;

ambDiffSpecProperty: AMBIENT
	{
	   $$ = STATE_AMBIENT;
	}
	| DIFFUSE
	{
	   $$ = STATE_DIFFUSE;
	}
	| SPECULAR
	{
	   $$ = STATE_SPECULAR;
	}
	;

stateLightNumber: INTEGER
	{
	   if ((unsigned) $1 >= state->MaxLights) {
	      yyerror(& @1, state, "invalid light selector");
	      YYERROR;
	   }

	   $$ = $1;
	}
	;

stateTexGenItem: TEXGEN optTexCoordUnitNum stateTexGenType stateTexGenCoord
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = STATE_TEXGEN;
	   $$[1] = $2;
	   $$[2] = $3 + $4;
	}
	;

stateTexGenType: EYE
	{
	   $$ = STATE_TEXGEN_EYE_S;
	}
	| OBJECT
	{
	   $$ = STATE_TEXGEN_OBJECT_S;
	}
	;
stateTexGenCoord: TEXGEN_S
	{
	   $$ = STATE_TEXGEN_EYE_S - STATE_TEXGEN_EYE_S;
	}
	| TEXGEN_T
	{
	   $$ = STATE_TEXGEN_EYE_T - STATE_TEXGEN_EYE_S;
	}
	| TEXGEN_R
	{
	   $$ = STATE_TEXGEN_EYE_R - STATE_TEXGEN_EYE_S;
	}
	| TEXGEN_Q
	{
	   $$ = STATE_TEXGEN_EYE_Q - STATE_TEXGEN_EYE_S;
	}
	;

stateFogItem: FOG stateFogProperty
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = $2;
	}
	;

stateFogProperty: COLOR
	{
	   $$ = STATE_FOG_COLOR;
	}
	| PARAMS
	{
	   $$ = STATE_FOG_PARAMS;
	}
	;

stateClipPlaneItem: CLIP '[' stateClipPlaneNum ']' PLANE
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = STATE_CLIPPLANE;
	   $$[1] = $3;
	}
	;

stateClipPlaneNum: INTEGER
	{
	   if ((unsigned) $1 >= state->MaxClipPlanes) {
	      yyerror(& @1, state, "invalid clip plane selector");
	      YYERROR;
	   }

	   $$ = $1;
	}
	;

statePointItem: POINT_TOK statePointProperty
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = $2;
	}
	;

statePointProperty: SIZE_TOK
	{
	   $$ = STATE_POINT_SIZE;
	}
	| ATTENUATION
	{
	   $$ = STATE_POINT_ATTENUATION;
	}
	;

stateMatrixRow: stateMatrixItem ROW '[' stateMatrixRowNum ']'
	{
	   $$[0] = $1[0];
	   $$[1] = $1[1];
	   $$[2] = $4;
	   $$[3] = $4;
	   $$[4] = $1[2];
	}
	;

stateMatrixRows: stateMatrixItem optMatrixRows
	{
	   $$[0] = $1[0];
	   $$[1] = $1[1];
	   $$[2] = $2[2];
	   $$[3] = $2[3];
	   $$[4] = $1[2];
	}
	;

optMatrixRows:
	{
	   $$[2] = 0;
	   $$[3] = 3;
	}
	| ROW '[' stateMatrixRowNum DOT_DOT stateMatrixRowNum ']'
	{
	   /* It seems logical that the matrix row range specifier would have
	    * to specify a range or more than one row (i.e., $5 > $3).
	    * However, the ARB_vertex_program spec says "a program will fail
	    * to load if <a> is greater than <b>."  This means that $3 == $5
	    * is valid.
	    */
	   if ($3 > $5) {
	      yyerror(& @3, state, "invalid matrix row range");
	      YYERROR;
	   }

	   $$[2] = $3;
	   $$[3] = $5;
	}
	;

stateMatrixItem: MATRIX stateMatrixName stateOptMatModifier
	{
	   $$[0] = $2[0];
	   $$[1] = $2[1];
	   $$[2] = $3;
	}
	;

stateOptMatModifier: 
	{
	   $$ = 0;
	}
	| stateMatModifier
	{
	   $$ = $1;
	}
	;

stateMatModifier: INVERSE 
	{
	   $$ = STATE_MATRIX_INVERSE;
	}
	| TRANSPOSE 
	{
	   $$ = STATE_MATRIX_TRANSPOSE;
	}
	| INVTRANS
	{
	   $$ = STATE_MATRIX_INVTRANS;
	}
	;

stateMatrixRowNum: INTEGER
	{
	   if ($1 > 3) {
	      yyerror(& @1, state, "invalid matrix row reference");
	      YYERROR;
	   }

	   $$ = $1;
	}
	;

stateMatrixName: MODELVIEW stateOptModMatNum
	{
	   $$[0] = STATE_MODELVIEW_MATRIX;
	   $$[1] = $2;
	}
	| PROJECTION
	{
	   $$[0] = STATE_PROJECTION_MATRIX;
	   $$[1] = 0;
	}
	| MVP
	{
	   $$[0] = STATE_MVP_MATRIX;
	   $$[1] = 0;
	}
	| TEXTURE optTexCoordUnitNum
	{
	   $$[0] = STATE_TEXTURE_MATRIX;
	   $$[1] = $2;
	}
	| PALETTE '[' statePaletteMatNum ']'
	{
	   yyerror(& @1, state, "GL_ARB_matrix_palette not supported");
	   YYERROR;
	}
	| MAT_PROGRAM '[' stateProgramMatNum ']'
	{
	   $$[0] = STATE_PROGRAM_MATRIX;
	   $$[1] = $3;
	}
	;

stateOptModMatNum:
	{
	   $$ = 0;
	}
	| '[' stateModMatNum ']'
	{
	   $$ = $2;
	}
	;
stateModMatNum: INTEGER
	{
	   /* Since GL_ARB_vertex_blend isn't supported, only modelview matrix
	    * zero is valid.
	    */
	   if ($1 != 0) {
	      yyerror(& @1, state, "invalid modelview matrix index");
	      YYERROR;
	   }

	   $$ = $1;
	}
	;
statePaletteMatNum: INTEGER
	{
	   /* Since GL_ARB_matrix_palette isn't supported, just let any value
	    * through here.  The error will be generated later.
	    */
	   $$ = $1;
	}
	;
stateProgramMatNum: INTEGER
	{
	   if ((unsigned) $1 >= state->MaxProgramMatrices) {
	      yyerror(& @1, state, "invalid program matrix selector");
	      YYERROR;
	   }

	   $$ = $1;
	}
	;

stateDepthItem: DEPTH RANGE
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = STATE_DEPTH_RANGE;
	}
	;


programSingleItem: progEnvParam | progLocalParam;

programMultipleItem: progEnvParams | progLocalParams;

progEnvParams: PROGRAM ENV '[' progEnvParamNums ']'
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = state->state_param_enum;
	   $$[1] = STATE_ENV;
	   $$[2] = $4[0];
	   $$[3] = $4[1];
	}
	;

progEnvParamNums: progEnvParamNum
	{
	   $$[0] = $1;
	   $$[1] = $1;
	}
	| progEnvParamNum DOT_DOT progEnvParamNum
	{
	   $$[0] = $1;
	   $$[1] = $3;
	}
	;

progEnvParam: PROGRAM ENV '[' progEnvParamNum ']'
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = state->state_param_enum;
	   $$[1] = STATE_ENV;
	   $$[2] = $4;
	   $$[3] = $4;
	}
	;

progLocalParams: PROGRAM LOCAL '[' progLocalParamNums ']'
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = state->state_param_enum;
	   $$[1] = STATE_LOCAL;
	   $$[2] = $4[0];
	   $$[3] = $4[1];
	}

progLocalParamNums: progLocalParamNum
	{
	   $$[0] = $1;
	   $$[1] = $1;
	}
	| progLocalParamNum DOT_DOT progLocalParamNum
	{
	   $$[0] = $1;
	   $$[1] = $3;
	}
	;

progLocalParam: PROGRAM LOCAL '[' progLocalParamNum ']'
	{
	   memset($$, 0, sizeof($$));
	   $$[0] = state->state_param_enum;
	   $$[1] = STATE_LOCAL;
	   $$[2] = $4;
	   $$[3] = $4;
	}
	;

progEnvParamNum: INTEGER
	{
	   if ((unsigned) $1 >= state->limits->MaxEnvParams) {
	      yyerror(& @1, state, "invalid environment parameter reference");
	      YYERROR;
	   }
	   $$ = $1;
	}
	;

progLocalParamNum: INTEGER
	{
	   if ((unsigned) $1 >= state->limits->MaxLocalParams) {
	      yyerror(& @1, state, "invalid local parameter reference");
	      YYERROR;
	   }
	   $$ = $1;
	}
	;



paramConstDecl: paramConstScalarDecl | paramConstVector;
paramConstUse: paramConstScalarUse | paramConstVector;

paramConstScalarDecl: signedFloatConstant
	{
	   ir_constant_data d = { { 0 } };
	   d.f[0] = $1;
	   d.f[1] = $1;
	   d.f[2] = $1;
	   d.f[3] = $1;

	   $$ = new(state) ir_constant(glsl_type::vec4_type, &d);
	}
	;

paramConstScalarUse: REAL
	{
	   $$ = new(state) ir_constant(float($1));
	}
	| INTEGER
	{
	   $$ = new(state) ir_constant(float($1));
	}
	;

paramConstVector: '{' signedFloatConstant '}'
	{
	   ir_constant_data d = { { 0 } };
	   d.f[0] = $2;
	   d.f[1] = 0.0f;
	   d.f[2] = 0.0f;
	   d.f[3] = 1.0f;

	   $$ = new(state) ir_constant(glsl_type::vec4_type, &d);
	}
	| '{' signedFloatConstant ',' signedFloatConstant '}'
	{
	   ir_constant_data d = { { 0 } };
	   d.f[0] = $2;
	   d.f[1] = $4;
	   d.f[2] = 0.0f;
	   d.f[3] = 1.0f;

	   $$ = new(state) ir_constant(glsl_type::vec4_type, &d);
	}
	| '{' signedFloatConstant ',' signedFloatConstant ','
              signedFloatConstant '}'
	{
	   ir_constant_data d = { { 0 } };
	   d.f[0] = $2;
	   d.f[1] = $4;
	   d.f[2] = $6;
	   d.f[3] = 1.0f;

	   $$ = new(state) ir_constant(glsl_type::vec4_type, &d);
	}
	| '{' signedFloatConstant ',' signedFloatConstant ','
              signedFloatConstant ',' signedFloatConstant '}'
	{
	   ir_constant_data d = { { 0 } };
	   d.f[0] = $2;
	   d.f[1] = $4;
	   d.f[2] = $6;
	   d.f[3] = $8;

	   $$ = new(state) ir_constant(glsl_type::vec4_type, &d);
	}
	;

signedFloatConstant: optionalSign REAL
	{
	   $$ = ($1) ? -$2 : $2;
	}
	| optionalSign INTEGER
	{
	   $$ = (float)(($1) ? -$2 : $2);
	}
	;

optionalSign: '+'        { $$ = false; }
	| '-'            { $$ = true;  }
	|                { $$ = false; }
	;

TEMP_statement: optVarSize TEMP { $<integer>$ = $2; } varNameList
	;

optVarSize: string
	{
	   /* NV_fragment_program_option defines the size qualifiers in a
	    * fairly broken way.  "SHORT" or "LONG" can optionally be used
	    * before TEMP or OUTPUT.  However, neither is a reserved word!
	    * This means that we have to parse it as an identifier, then check
	    * to make sure it's one of the valid values.  *sigh*
	    *
	    * In addition, the grammar in the extension spec does *not* allow
	    * the size specifier to be optional, but all known implementations
	    * do.
	    */
	   if (!state->option.NV_fragment) {
	      yyerror(& @1, state, "unexpected IDENTIFIER");
	      YYERROR;
	   }

	   if (strcmp("SHORT", $1) == 0) {
	   } else if (strcmp("LONG", $1) == 0) {
	   } else {
	      char *const err_str =
		 make_error_string("invalid storage size specifier \"%s\"",
				   $1);

	      yyerror(& @1, state, (err_str != NULL)
		      ? err_str : "invalid storage size specifier");

	      if (err_str != NULL) {
		 free(err_str);
	      }

	      YYERROR;
	   }
	}
	|
	{
	}
	;

ADDRESS_statement: ADDRESS { $<integer>$ = $1; } varNameList
	;

varNameList: varNameList ',' IDENTIFIER
	{
	   const glsl_type *type = (asm_type($<integer>0) == at_address)
	      ? glsl_type::int_type : glsl_type::vec4_type;

	   ir_variable *v = new(state) ir_variable(type, $3, ir_var_auto);

	   if (!declare_variable(state, v, (asm_type) $<integer>0, & @3)) {
	      YYERROR;
	   }

	   state->ir.push_tail(v);
	}
	| IDENTIFIER
	{
	   const glsl_type *type = (asm_type($<integer>0) == at_address)
	      ? glsl_type::int_type : glsl_type::vec4_type;

	   ir_variable *v = new(state) ir_variable(type, $1, ir_var_auto);

	   if (!declare_variable(state, v, (asm_type) $<integer>0, & @1)) {
	      YYERROR;
	   }
	}
	;

OUTPUT_statement: optVarSize OUTPUT IDENTIFIER '=' resultBinding
	{
	   ir_variable *v =
	      new(state) ir_variable(glsl_type::vec4_type, $3, ir_var_out);

	   v->explicit_location = true;
	   v->location = $5;

	   if (!declare_variable(state, v, at_output, & @3)) {
	      YYERROR;
	   }

	   state->ir.push_tail(v);
	}
	;

resultBinding: RESULT POSITION
	{
	   if (state->mode == ARB_vertex) {
	      $$ = VERT_RESULT_HPOS;
	   } else {
	      yyerror(& @2, state, "invalid program result name");
	      YYERROR;
	   }
	}
	| RESULT FOGCOORD
	{
	   if (state->mode == ARB_vertex) {
	      $$ = VERT_RESULT_FOGC;
	   } else {
	      yyerror(& @2, state, "invalid program result name");
	      YYERROR;
	   }
	}
	| RESULT resultColBinding
	{
	   $$ = $2;
	}
	| RESULT POINTSIZE
	{
	   if (state->mode == ARB_vertex) {
	      $$ = VERT_RESULT_PSIZ;
	   } else {
	      yyerror(& @2, state, "invalid program result name");
	      YYERROR;
	   }
	}
	| RESULT TEXCOORD optTexCoordUnitNum
	{
	   if (state->mode == ARB_vertex) {
	      $$ = VERT_RESULT_TEX0 + $3;
	   } else {
	      yyerror(& @2, state, "invalid program result name");
	      YYERROR;
	   }
	}
	| RESULT DEPTH
	{
	   if (state->mode == ARB_fragment) {
	      $$ = FRAG_RESULT_DEPTH;
	   } else {
	      yyerror(& @2, state, "invalid program result name");
	      YYERROR;
	   }
	}
	;

resultColBinding: COLOR optResultFaceType optResultColorType
	{
	   $$ = $2 + $3;
	}
	;

optResultFaceType:
	{
	   $$ = (state->mode == ARB_vertex)
	      ? (int) VERT_RESULT_COL0
	      : (int) FRAG_RESULT_COLOR;
	}
	| FRONT
	{
	   if (state->mode == ARB_vertex) {
	      $$ = VERT_RESULT_COL0;
	   } else {
	      yyerror(& @1, state, "invalid program result name");
	      YYERROR;
	   }
	}
	| BACK
	{
	   if (state->mode == ARB_vertex) {
	      $$ = VERT_RESULT_BFC0;
	   } else {
	      yyerror(& @1, state, "invalid program result name");
	      YYERROR;
	   }
	}
	;

optResultColorType:
	{
	   $$ = 0; 
	}
	| PRIMARY
	{
	   if (state->mode == ARB_vertex) {
	      $$ = 0;
	   } else {
	      yyerror(& @1, state, "invalid program result name");
	      YYERROR;
	   }
	}
	| SECONDARY
	{
	   if (state->mode == ARB_vertex) {
	      $$ = 1;
	   } else {
	      yyerror(& @1, state, "invalid program result name");
	      YYERROR;
	   }
	}
	;

optFaceType:    { $$ = 0; }
	| FRONT	{ $$ = 0; }
	| BACK  { $$ = 1; }
	;

optColorType:       { $$ = 0; }
	| PRIMARY   { $$ = 0; }
	| SECONDARY { $$ = 1; }
	;

optTexCoordUnitNum:                { $$ = 0; }
	| '[' texCoordUnitNum ']'  { $$ = $2; }
	;

optTexImageUnitNum:                { $$ = 0; }
	| '[' texImageUnitNum ']'  { $$ = $2; }
	;

optLegacyTexUnitNum:               { $$ = 0; }
	| '[' legacyTexUnitNum ']' { $$ = $2; }
	;

texCoordUnitNum: INTEGER
	{
	   if ((unsigned) $1 >= state->MaxTextureCoordUnits) {
	      yyerror(& @1, state, "invalid texture coordinate unit selector");
	      YYERROR;
	   }

	   $$ = $1;
	}
	;

texImageUnitNum: INTEGER
	{
	   if ((unsigned) $1 >= state->MaxTextureImageUnits) {
	      yyerror(& @1, state, "invalid texture image unit selector");
	      YYERROR;
	   }

	   $$ = $1;
	}
	;

legacyTexUnitNum: INTEGER
	{
	   if ((unsigned) $1 >= state->MaxTextureUnits) {
	      yyerror(& @1, state, "invalid texture unit selector");
	      YYERROR;
	   }

	   $$ = $1;
	}
	;

ALIAS_statement: ALIAS IDENTIFIER '=' USED_IDENTIFIER
	{
	   struct asm_symbol *exist = (struct asm_symbol *)
	      _mesa_symbol_table_find_symbol(state->st, 0, $2);
	   struct asm_symbol *target = (struct asm_symbol *)
	      _mesa_symbol_table_find_symbol(state->st, 0, $4);

	   free($4);

	   if (exist != NULL) {
	      char m[1000];
	      _mesa_snprintf(m, sizeof(m), "redeclared identifier: %s", $2);
	      free($2);
	      yyerror(& @2, state, m);
	      YYERROR;
	   } else if (target == NULL) {
	      free($2);
	      yyerror(& @4, state,
		      "undefined variable binding in ALIAS statement");
	      YYERROR;
	   } else {
	      _mesa_symbol_table_add_symbol(state->st, 0, $2, target);
	   }
	}
	;

string: IDENTIFIER
	| USED_IDENTIFIER
	;

%%

ir_rvalue *
saturate_value(void *mem_ctx, unsigned saturate_mode, ir_rvalue *expr)
{
   switch (saturate_mode) {
   case SATURATE_OFF:
      return expr;

   case SATURATE_ZERO_ONE: {
      ir_rvalue *zero = ir_constant::zero(mem_ctx, expr->type);
      ir_expression *min_expr =
	 new(mem_ctx) ir_expression(ir_binop_min, expr->type, expr, zero);
      ir_constant_data d = { { 0 } };

      d.f[0] = 1.0F;
      d.f[1] = 1.0F;
      d.f[2] = 1.0F;
      d.f[3] = 1.0F;

      ir_rvalue *one = new(mem_ctx) ir_constant(expr->type, &d);

      ir_expression *max_expr =
	 new(mem_ctx) ir_expression(ir_binop_max, expr->type, min_expr, one);

      return max_expr;
   }

   default:
      assert(!"Should not get here.");
      return expr;
   }
}

static unsigned
count_bits(unsigned x)
{
   /* Determine how many bits are set in the write mask.  A swizzle
    * must be generated to splat the generated scalar component across
    * all the enabled write bits.
    */
   unsigned bits = 0;
   for (unsigned i = 0; i < 4; i++) {
      if ((x & (1U << i)) != 0)
	 bits++;
   }

   return bits;
}

ir_rvalue *
generate_rhs_for_write_mask(void *mem_ctx, unsigned write_mask, ir_rvalue *v)
{
   const unsigned bits = count_bits(write_mask);
   assert((bits > 0) && (bits <= 4));
   if (bits != 4)
      v =  new(mem_ctx) ir_swizzle(v, 0, 1, 2, 3, bits);

   return v;
}

ir_assignment *
emit_vector_assignment(void *mem_ctx, ir_dereference *dst, unsigned write_mask,
		       unsigned saturate_mode, ir_rvalue *v)
{
   ir_rvalue *rhs =
      saturate_value(mem_ctx, saturate_mode,
		     generate_rhs_for_write_mask(mem_ctx, write_mask, v));

   return new(mem_ctx) ir_assignment(dst, rhs, NULL, write_mask);
}

ir_assignment *
emit_scalar_assignment(void *mem_ctx, ir_dereference *dst, unsigned write_mask,
		       unsigned saturate_mode, ir_rvalue *sc)
{
   assert(sc->type->is_scalar());

   /* Determine how many bits are set in the write mask.  A swizzle
    * must be generated to splat the generated scalar component across
    * all the enabled write bits.
    */
   const unsigned bits = count_bits(write_mask);
   assert((bits > 0) && (bits <= 4));
   if (bits > 1)
      sc =  new(mem_ctx) ir_swizzle(sc, 0, 0, 0, 0, bits);

   return new(mem_ctx) ir_assignment(dst,
				     saturate_value(mem_ctx, saturate_mode, sc),
				     NULL, write_mask);
}

ir_texture *
texture_instruction_common(struct asm_parser_state *state,
			   enum ir_texture_opcode opcode, ir_rvalue *tex_coord,
			   unsigned unit, const glsl_type *sampler_type,
			   struct YYLTYPE *sampler_loc)
{
   char name[16];

   snprintf(name, sizeof(name), "$sampler-%02d", unit);
   ir_variable *sampler = (ir_variable *)
      _mesa_symbol_table_find_symbol(state->st, 0, name);

   if (sampler == NULL) {
      sampler = new(state) ir_variable(sampler_type, name, ir_var_uniform);
      state->ir.push_head(sampler);
   }

   /* If this texture unit was previously accessed using either a
    * different texture target or a different shadow mode, generate an
    * error.
    */
   if (sampler->type != sampler_type) {
      yyerror(sampler_loc, state,
	      "multiple targets used on one texture image unit");
      return NULL;
   }

   ir_texture *const tex = new(state) ir_texture(opcode);

   tex->sampler = new(state) ir_dereference_variable(sampler);

   unsigned count = 0;
   switch (tex->sampler->type->sampler_dimensionality) {
   case GLSL_SAMPLER_DIM_1D:
      count = 1;
      break;
   case GLSL_SAMPLER_DIM_2D:
   case GLSL_SAMPLER_DIM_RECT:
      count = 2;
      break;
   case GLSL_SAMPLER_DIM_3D:
   case GLSL_SAMPLER_DIM_CUBE:
      count = 3;
      break;
   }

   if (tex->sampler->type->sampler_array)
      count++;

   tex->coordinate = new(state) ir_swizzle(tex_coord, 0, 1, 2, 3, count);

   if (tex->sampler->type->sampler_shadow) {
      tex->shadow_comparitor =
	 new(state) ir_swizzle(tex_coord, 2, 2, 2, 2, 1);
   }

   return tex;
}

/**
 * Validate the set of inputs used by a program
 *
 * Validates that legal sets of inputs are used by the program.  In this case
 * "used" included both reading the input or binding the input to a name using
 * the \c ATTRIB command.
 *
 * \return
 * \c true if the combination of inputs used is valid, \c false otherwise.
 */
int
validate_inputs(struct YYLTYPE *locp, struct asm_parser_state *state)
{
   const int inputs = state->prog->InputsRead | state->InputsBound;

   if (((inputs & 0x0ffff) & (inputs >> 16)) != 0) {
      yyerror(locp, state, "illegal use of generic attribute and name attribute");
      return 0;
   }

   return 1;
}


bool
declare_variable(struct asm_parser_state *state, ir_variable *var,
		 enum asm_type t, struct YYLTYPE *locp)
{
   if (_mesa_symbol_table_find_symbol(state->st, 0, var->name) != NULL) {
      yyerror(locp, state, "redeclared identifier");
      return false;
   } else {
      switch (t) {
      case at_temp:
	 if (state->prog->NumTemporaries >= state->limits->MaxTemps) {
	    yyerror(locp, state, "too many temporaries declared");
	    return false;
	 }

	 state->prog->NumTemporaries++;
	 break;

      case at_address:
	 if (state->prog->NumAddressRegs >= state->limits->MaxAddressRegs) {
	    yyerror(locp, state, "too many address registers declared");
	    return false;
	 }

	 state->prog->NumAddressRegs++;
	 break;

      default:
	 break;
      }

      _mesa_symbol_table_add_symbol(state->st, 0, var->name, var);
   }

   return true;
}


int add_state_reference(struct gl_program_parameter_list *param_list,
			const gl_state_index tokens[STATE_LENGTH])
{
   const GLuint size = 4; /* XXX fix */
   char *name;
   GLint index;

   name = _mesa_program_state_string(tokens);
   index = _mesa_add_parameter(param_list, PROGRAM_STATE_VAR, name,
                               size, GL_NONE, NULL, tokens, 0x0);
   param_list->StateFlags |= _mesa_program_state_flags(tokens);

   /* free name string here since we duplicated it in add_parameter() */
   free(name);

   return index;
}


int
initialize_symbol_from_state(struct gl_program *prog,
			     struct asm_symbol *param_var, 
			     const unsigned tokens[STATE_LENGTH])
{
   int idx = -1;
   gl_state_index state_tokens[STATE_LENGTH];


   memcpy(state_tokens, tokens, sizeof(state_tokens));

   param_var->type = at_param;
   param_var->param_binding_type = PROGRAM_STATE_VAR;

   /* If we are adding a STATE_MATRIX that has multiple rows, we need to
    * unroll it and call add_state_reference() for each row
    */
   if ((state_tokens[0] == STATE_MODELVIEW_MATRIX ||
	state_tokens[0] == STATE_PROJECTION_MATRIX ||
	state_tokens[0] == STATE_MVP_MATRIX ||
	state_tokens[0] == STATE_TEXTURE_MATRIX ||
	state_tokens[0] == STATE_PROGRAM_MATRIX)
       && (state_tokens[2] != state_tokens[3])) {
      int row;
      const int first_row = state_tokens[2];
      const int last_row = state_tokens[3];

      for (row = first_row; row <= last_row; row++) {
	 state_tokens[2] = state_tokens[3] = (gl_state_index) row;

	 idx = add_state_reference(prog->Parameters, state_tokens);
	 if (param_var->param_binding_begin == ~0U) {
	    param_var->param_binding_begin = idx;
            param_var->param_binding_swizzle = SWIZZLE_XYZW;
         }

	 param_var->param_binding_length++;
      }
   }
   else {
      idx = add_state_reference(prog->Parameters, state_tokens);
      if (param_var->param_binding_begin == ~0U) {
	 param_var->param_binding_begin = idx;
         param_var->param_binding_swizzle = SWIZZLE_XYZW;
      }
      param_var->param_binding_length++;
   }

   return idx;
}


int
initialize_symbol_from_param(struct gl_program *prog,
			     struct asm_symbol *param_var, 
			     const unsigned tokens[STATE_LENGTH])
{
   int idx = -1;
   gl_state_index state_tokens[STATE_LENGTH];


   memcpy(state_tokens, tokens, sizeof(state_tokens));

   assert((state_tokens[0] == STATE_VERTEX_PROGRAM)
	  || (state_tokens[0] == STATE_FRAGMENT_PROGRAM));
   assert((state_tokens[1] == STATE_ENV)
	  || (state_tokens[1] == STATE_LOCAL));

   /*
    * The param type is STATE_VAR.  The program parameter entry will
    * effectively be a pointer into the LOCAL or ENV parameter array.
    */
   param_var->type = at_param;
   param_var->param_binding_type = PROGRAM_STATE_VAR;

   /* If we are adding a STATE_ENV or STATE_LOCAL that has multiple elements,
    * we need to unroll it and call add_state_reference() for each row
    */
   if (state_tokens[2] != state_tokens[3]) {
      int row;
      const int first_row = state_tokens[2];
      const int last_row = state_tokens[3];

      for (row = first_row; row <= last_row; row++) {
	 state_tokens[2] = state_tokens[3] = (gl_state_index) row;

	 idx = add_state_reference(prog->Parameters, state_tokens);
	 if (param_var->param_binding_begin == ~0U) {
	    param_var->param_binding_begin = idx;
            param_var->param_binding_swizzle = SWIZZLE_XYZW;
         }
	 param_var->param_binding_length++;
      }
   }
   else {
      idx = add_state_reference(prog->Parameters, state_tokens);
      if (param_var->param_binding_begin == ~0U) {
	 param_var->param_binding_begin = idx;
         param_var->param_binding_swizzle = SWIZZLE_XYZW;
      }
      param_var->param_binding_length++;
   }

   return idx;
}


char *
make_error_string(const char *fmt, ...)
{
   int length;
   char *str;
   va_list args;


   /* Call vsnprintf once to determine how large the final string is.  Call it
    * again to do the actual formatting.  from the vsnprintf manual page:
    *
    *    Upon successful return, these functions return the number of
    *    characters printed  (not including the trailing '\0' used to end
    *    output to strings).
    */
   va_start(args, fmt);
   length = 1 + vsnprintf(NULL, 0, fmt, args);
   va_end(args);

   str = (char *) malloc(length);
   if (str) {
      va_start(args, fmt);
      vsnprintf(str, length, fmt, args);
      va_end(args);
   }

   return str;
}


void
yyerror(YYLTYPE *locp, struct asm_parser_state *state, const char *s)
{
   char *err_str;


   err_str = make_error_string("glProgramStringARB(%s)\n", s);
   if (err_str) {
      _mesa_error(state->ctx, GL_INVALID_OPERATION, "%s", err_str);
      free(err_str);
   }

   err_str = make_error_string("line %u, char %u: error: %s\n",
			       locp->first_line, locp->first_column, s);
   _mesa_set_program_error(state->ctx, locp->position, err_str);

   if (err_str) {
      free(err_str);
   }
}


GLboolean
_mesa_parse_arb_program(struct gl_context *ctx, GLenum target, const GLubyte *str,
			GLsizei len, struct asm_parser_state *state)
{
   struct asm_instruction *inst;
   unsigned i;
   GLubyte *strz;
   GLboolean result = GL_FALSE;
   void *temp;
   struct asm_symbol *sym;

   state->ctx = ctx;
   state->prog->Target = target;
   state->prog->Parameters = _mesa_new_parameter_list();

   /* Make a copy of the program string and force it to be NUL-terminated.
    */
   strz = (GLubyte *) malloc(len + 1);
   if (strz == NULL) {
      _mesa_error(ctx, GL_OUT_OF_MEMORY, "glProgramStringARB");
      return GL_FALSE;
   }
   memcpy (strz, str, len);
   strz[len] = '\0';

   state->prog->String = strz;

   state->st = _mesa_symbol_table_ctor();

   state->limits = (target == GL_VERTEX_PROGRAM_ARB)
      ? & ctx->Const.VertexProgram
      : & ctx->Const.FragmentProgram;

   state->MaxTextureImageUnits = ctx->Const.MaxTextureImageUnits;
   state->MaxTextureCoordUnits = ctx->Const.MaxTextureCoordUnits;
   state->MaxTextureUnits = ctx->Const.MaxTextureUnits;
   state->MaxClipPlanes = ctx->Const.MaxClipPlanes;
   state->MaxLights = ctx->Const.MaxLights;
   state->MaxProgramMatrices = ctx->Const.MaxProgramMatrices;

   state->state_param_enum = (target == GL_VERTEX_PROGRAM_ARB)
      ? STATE_VERTEX_PROGRAM : STATE_FRAGMENT_PROGRAM;

   _mesa_set_program_error(ctx, -1, NULL);

   _mesa_program_lexer_ctor(& state->scanner, state, (const char *) str, len);
   yyparse(state);
   _mesa_program_lexer_dtor(state->scanner);


   if (ctx->Program.ErrorPos != -1) {
      goto error;
   }

   if (! _mesa_layout_parameters(state)) {
      struct YYLTYPE loc;

      loc.first_line = 0;
      loc.first_column = 0;
      loc.position = len;

      yyerror(& loc, state, "invalid PARAM usage");
      goto error;
   }


   
   /* Add one instruction to store the "END" instruction.
    */
   state->prog->Instructions =
      _mesa_alloc_instructions(state->prog->NumInstructions + 1);
   inst = state->inst_head;
   for (i = 0; i < state->prog->NumInstructions; i++) {
      struct asm_instruction *const temp = inst->next;

      state->prog->Instructions[i] = inst->Base;
      inst = temp;
   }

   /* Finally, tag on an OPCODE_END instruction */
   {
      const GLuint numInst = state->prog->NumInstructions;
      _mesa_init_instructions(state->prog->Instructions + numInst, 1);
      state->prog->Instructions[numInst].Opcode = OPCODE_END;
   }
   state->prog->NumInstructions++;

   state->prog->NumParameters = state->prog->Parameters->NumParameters;
   state->prog->NumAttributes = _mesa_bitcount(state->prog->InputsRead);

   /*
    * Initialize native counts to logical counts.  The device driver may
    * change them if program is translated into a hardware program.
    */
   state->prog->NumNativeInstructions = state->prog->NumInstructions;
   state->prog->NumNativeTemporaries = state->prog->NumTemporaries;
   state->prog->NumNativeParameters = state->prog->NumParameters;
   state->prog->NumNativeAttributes = state->prog->NumAttributes;
   state->prog->NumNativeAddressRegs = state->prog->NumAddressRegs;

   result = GL_TRUE;

error:
   for (inst = state->inst_head;
	inst != NULL;
	inst = (struct asm_instruction *) temp) {
      temp = inst->next;
      free(inst);
   }

   state->inst_head = NULL;
   state->inst_tail = NULL;

   for (sym = state->sym; sym != NULL; sym = (struct asm_symbol *) temp) {
      temp = sym->next;

      free((void *) sym->name);
      free(sym);
   }
   state->sym = NULL;

   _mesa_symbol_table_dtor(state->st);
   state->st = NULL;

   return result;
}
