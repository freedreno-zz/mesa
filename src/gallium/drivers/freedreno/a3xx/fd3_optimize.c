/* -*- mode: C; c-file-style: "k&r"; tab-width 4; indent-tabs-mode: t; -*- */

/*
 * Copyright (C) 2013 Rob Clark <robclark@freedesktop.org>
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
 *
 * Authors:
 *    Rob Clark <robclark@freedesktop.org>
 */


#include "fd3_compiler.h"
#include "fd3_util.h"

#include "instr-a3xx.h"
#include "ir3.h"

#define REG(so, n) (struct ir3_register){ \
		.flags  = ((so)->half_precision) ? IR3_REG_HALF : 0, \
		.num    = (n), \
		.wrmask = TGSI_WRITEMASK_XYZW, \
	}

struct fd3_optimize_context {
	struct fd3_shader_stateobj *so;
	struct ir3_register outputs[16];
	struct ir3_register inputs[16];    /* only used for vertex shaders */
};

/* TODO make this FD_MESA_DEBUG flag: */
#define DEBUG_OPT
#ifndef DEBUG_OPT
#  undef debug_printf
#  define debug_printf(...) do { } while (0)
#endif

static void dump_info(struct fd3_optimize_context *ctx, const char *name)
{
#ifdef DEBUG_OPT
	struct fd3_shader_stateobj *so = ctx->so;
	struct ir3_shader_info info;
	uint32_t *bin;
	const char *type = (so->type == SHADER_VERTEX) ? "VERT" : "FRAG";

	// for debug, dump some before/after info:
	bin = ir3_shader_assemble(so->ir, &info);
	if (fd_mesa_debug & FD_DBG_DISASM) {
		unsigned i;
		debug_printf("%s: %s: disasm:\n", type, name);
		disasm_a3xx(bin, info.sizedwords, 0, so->type);
		debug_printf("%s: %s: outputs:", type, name);
		for (i = 0; i < so->outputs_count; i++)
			debug_printf(" r%d.%c", reg_num(&ctx->outputs[i]), "xyzw"[reg_comp(&ctx->outputs[i])]);
		debug_printf("\n");
		if (so->type == SHADER_VERTEX) {
			debug_printf("%s: %s: inputs:", type, name);
			for (i = 0; i < so->inputs_count; i++)
				debug_printf(" r%d.%c", reg_num(&ctx->inputs[i]), "xyzw"[reg_comp(&ctx->inputs[i])]);
			debug_printf("\n");
		}
	}
	debug_printf("%s: %s: %u instructions, %d half, %d full\n\n",
			type, name, info.instrs_count, info.max_half_reg + 1, info.max_reg + 1);
	free(bin);
#endif
}

static boolean opc_eq(const struct ir3_instruction *instr,
		int category, opc_t opc)
{
	return (instr->category == category) && (instr->opc == opc);
}

static boolean reg_gpr(struct ir3_register *r)
{
	if (r->flags & (IR3_REG_CONST | IR3_REG_IMMED | IR3_REG_RELATIV))
		return false;
	if ((reg_num(r) == REG_A0) || (reg_num(r) == REG_P0))
		return false;
	return true;
}

/* check that the register exists, is a GPR and is not special (a0/p0) */
static struct ir3_register * reg_check(struct ir3_instruction *instr, unsigned n)
{
	if ((n < instr->regs_count) && reg_gpr(instr->regs[n]))
		return instr->regs[n];
	return NULL;
}

/* test if two registers are exactly equal (incl wrmask) */
static boolean reg_eq(struct ir3_register *a, struct ir3_register *b)
{
	return ((a->flags & IR3_REG_HALF) == (b->flags & IR3_REG_HALF)) &&
			(a->num == b->num) &&
			(a->wrmask == b->wrmask);
}

static boolean __reg_masks(struct ir3_register *a, struct ir3_register *b,
		uint32_t *amask, uint32_t *bmask)
{
	if ((MAX2(a->num, b->num) - MIN2(a->num, b->num)) >= 32)
		return false;

	if (a->num > b->num) {
		*amask = a->wrmask << (a->num - b->num);
		*bmask = b->wrmask;
	} else {
		*amask = a->wrmask;
		*bmask = b->wrmask << (b->num - a->num);
	}

	return true;
}

/* test if two registers overlap (intersecting wrmask) */
static boolean reg_intersect(struct ir3_register *a, struct ir3_register *b)
{
	uint32_t amask, bmask;
	if (!__reg_masks(a, b, &amask, &bmask))
		return false;
	return !!(amask & bmask);
}

/* test if register a contains completely reg b: */
static boolean reg_contains(struct ir3_register *a, struct ir3_register *b)
{
	uint32_t amask, bmask;
	if (!__reg_masks(a, b, &amask, &bmask))
		return false;

	return (amask & bmask) && !(bmask & ~amask);
}

#define REG_MARK 0x4000000

static unsigned wrmask(struct ir3_register *reg, struct ir3_register *target)
{
	int shift = ((target->num & ~REG_MARK) - (reg->num & ~REG_MARK));
	unsigned wrmask = (target->wrmask << 4);
	if (shift >= 0)
		return wrmask << (shift & 0x3);
	else
		return wrmask >> (-shift & 0x3);
}

static boolean valid_mov(struct ir3_instruction *instr)
{
	return (instr->repeat == 0) &&
			(instr->category == 1) && /* mov */
			(instr->cat1.src_type == instr->cat1.dst_type) &&
			reg_check(instr, 0) && reg_check(instr, 1);
}

/* figure out if specified register is used as a src for subsequent
 * instructions.  This runs on the SSA form, so it only has to check
 * if the register appears as a src
 */
static boolean is_live(struct fd3_optimize_context *ctx, unsigned start,
		struct ir3_register *dst)
{
	struct fd3_shader_stateobj *so = ctx->so;
	struct ir3_shader *ir = so->ir;
	unsigned i, j;

	for (i = start; i < ir->instrs_count; i++) {
		struct ir3_instruction *instr = ir->instrs[i];

		/* check the src regs: */
		for (j = 1; j < instr->regs_count; j++) {
			struct ir3_register *r = reg_check(instr, j);
			if (r && reg_intersect(r, dst))
				return true;
		}
	}

	/* also need to check outputs: */
	for (i = 0; i < so->outputs_count; i++)
		if (reg_intersect(&ctx->outputs[i], dst))
			return true;

	return false;
}

/* For each mov where src_type == dst_type, and src does not have (abs)
 * or (neg), and not a relative address, (ie. any move that results in
 * dst having same value as src) rename any rD.d appearing as src in
 * subsequent instruction until rS.s or rD.d is overwritten.
 *
 * NOTE: we wouldn't need the rS.s or rD.d overwritten check except for
 * the edge cases where the first rename to_ssa gives us something which
 * is not purely SSA do to consecutive register constraints.  See the
 * comment in register_rename_one().
 *
 * NOTE: skip if src is const or dst is a0/p0.. or rS.s==rD.d from an
 * earlier rename.
 */
static void copy_propagate(struct fd3_optimize_context *ctx)
{
	struct fd3_shader_stateobj *so = ctx->so;
	struct ir3_shader *ir = so->ir;
	int i, j, k;

	for (i = 0; i < ir->instrs_count; i++) {
		struct ir3_instruction *instr = ir->instrs[i];
		struct ir3_register *src = instr->regs[1];
		struct ir3_register *dst = instr->regs[0];

		if (!valid_mov(instr))
			continue;

		/* skip if rS.s == rD.d from an earlier rename: */
		if (dst->num == src->num)
			continue;

		/* skip if rS.s is abs/neg/relative: */
		if (src->flags & (IR3_REG_ABS | IR3_REG_NEGATE | IR3_REG_RELATIV))
			continue;

		/* skip if rD.d is relative: */
		if (dst->flags & IR3_REG_RELATIV)
			continue;

		for (j = i + 1; j < ir->instrs_count; j++) {
			struct ir3_instruction *instr2 = ir->instrs[j];
			struct ir3_register *r;

			if (instr2->regs_count == 0)
				continue;

			/* if any src matches original rD.d, replace with rS.s: */
			for (k = 1; k < instr2->regs_count; k++)
				if ((r = reg_check(instr2, k)) && reg_eq(r, dst))
					r->num = src->num;

			/* if instruction writes rS.s or rD.d, done: */
			r = reg_check(instr2, 0);
			if (r && (reg_intersect(r, src) || reg_intersect(r, dst)))
				break;
		}
	}
}

/* Dead code eliminate.  Replace instructions where rD.c is not read
 * or mov's with no effect (src_type == dst_type && rD.c == rS.c).
 * Be sure to consider output's.
 *
 * NOTE: work backwards to eliminate everything in one pass (so we
 * don't preserve an instruction depended on by a later instruction
 * that can be eliminated).
 */
static void dead_code_eliminate(struct fd3_optimize_context *ctx)
{
	struct ir3_shader *ir = ctx->so->ir;
	int i;

	for (i = ir->instrs_count - 1; i >= 0; i--) {
		struct ir3_instruction *instr = ir->instrs[i];
		struct ir3_register *src = instr->regs[1];
		struct ir3_register *dst = instr->regs[0];
		boolean eliminate = false;

		if (valid_mov(instr) && (src->num == dst->num)) {
			eliminate = true;
		} else if ((instr->category != 0) && reg_gpr(dst)) {
			eliminate = !is_live(ctx, i + 1, dst);
		}

		if (eliminate) {
			/* TODO it would be nice to be clever about moving ss/sy
			 * flags.. for now just keep them in place on the nop
			 * that we replace this instruction with, and in the next
			 * step we avoid drop'ing nop's with flags:
			 */
			instr->category = 0;
			instr->opc = OPC_NOP;
			instr->flags &= (IR3_INSTR_SS | IR3_INSTR_SY | IR3_INSTR_JP);
			instr->regs_count = 0;
			memset(&instr->cat0, 0, sizeof(instr->cat0));
		}
	}

}

/* figure out required delay for specified instruction and register,
 * searching back to find where the register was assigned, and calculating
 * number of delay slots required to insert.
 */
static int required_delay(struct ir3_instruction *instr,
		struct ir3_register *reg, int end)
{
	struct ir3_shader *ir = instr->shader;
	struct ir3_instruction *assigner = NULL;
	int i, distance = 0, delay;

	boolean is_alu(struct ir3_instruction *instr)
	{
		return (1 <= instr->category) && (instr->category <= 3);
	}

	boolean is_sfu(struct ir3_instruction *instr)
	{
		return (instr->category == 4);
	}

	boolean is_tex(struct ir3_instruction *instr)
	{
		return (instr->category == 5);
	}

	if (!reg_gpr(reg))
		return 0;

	/* worst case is cat1-3 (alu) -> cat4 needing 6 cycles, normal
	 * alu -> alu needs 3 cycles, cat4 -> alu and texture fetch
	 * handles with sync bits:
	 */
	for (i = end - 1; (i >= 0) && (distance <= 6); i--) {
		struct ir3_instruction *instr2 = ir->instrs[i];
		struct ir3_register *dst = reg_check(instr2, 0);

		if (dst && reg_intersect(dst, reg)) {
			assigner = instr2;
			break;
		}

		distance += 1 + instr2->repeat;
	}

	/* if assigner is too far back, no delay needed: */
	if (!assigner)
		return 0;

	/* if assigner is cat4 (sfu) or cat5 (samp) then no delay, it
	 * is handled w/ sync flags:
	 */
	if (is_sfu(assigner) || is_tex(assigner))
		return 0;

	if (is_alu(assigner) && (is_sfu(instr) || is_tex(instr))) {
		delay = 6;
	} else if ((instr->category == 3) && (reg == instr->regs[3])) {
		/* special case, 3rd src to cat3 not required on first cycle */
		delay = 1;
	} else {
		delay = 3;
	}

	return MAX2(0, delay - distance);
}

/* This pass ensures removes unnecessary nops and adds nops when necessary
 * to make the instruction scheduling legal.
 *
 * Ideally, once this is clever enough to deal w/ >1 basic block (ie. jumps/
 * branches) we would not insert nop's in the tgsi to ir pass, and just
 * handle all the scheduling details here even if the other optimization
 * passes are disabled.  But for now we aren't that clever and need to do
 * the pessimistic nop insertion in the tgsi->ir pass so that we can give
 * up and use the output of the first pass if we run into something we can't
 * handle.
 *
 * TODO we should handle (sy)/(sx) sync bits here too (in addition to (ei)
 * end-input bit).
 */
static void legalize_it(struct fd3_optimize_context *ctx)
{
	struct ir3_shader *ir = ctx->so->ir;
	struct ir3_instruction *last_input = NULL;
	int i, j;

	for (i = 0; i < ir->instrs_count; i++) {
		struct ir3_instruction *instr = ir->instrs[i];

		if (opc_eq(instr, 2, OPC_BARY_F))
			last_input = instr;

		if (opc_eq(instr, 0, OPC_NOP)) {
			/* we can't actually eliminate if (sy) or (ss) set, we
			 * aren't clever enough..
			 */
			if (!instr->flags) {
				ir3_instr_del(ir, i);
				i--;
			}
		} else if (instr->category != 0) {
			int delay = 0;

			for (j = 1; j < instr->regs_count; j++) {
				struct ir3_register *reg = instr->regs[j];
				delay = MAX2(delay, required_delay(instr, reg, i));
			}

			if (delay > 0) {
				ir3_instr_insert(ir, i, 0, OPC_NOP)->repeat = (delay - 1);
				i++;
			}
		}
	}

	/* we might have deleted the bary.f with (ei) flag in the dead-code
	 * step.. and, well, eventually we wouldn't even bother with adding
	 * that flag in the tgsi->ir pass but instead handle it here in the
	 * legalize step:
	 */
	if (last_input)
		last_input->regs[0]->flags |= IR3_REG_EI;
}

/* Figure out if there are any more restrictive usages of the register
 * we want to rename.  For example:
 *
 *    sam (f32)(xyzw)r6.x, ...               <-- write r6.xyzw
 *    sam.p (f32)(xyzw)r4.x, r6.x, s#0, t#0  <-- read  r6.xyz
 *    sam (f32)(xyzw)r5.x, r6.x, ....        <-- read  r6.xy
 * => add.f r7.x, r6.x, ...                  <-- read  r6.x
 *
 * when we are renaming r6.x we need to account for the earlier
 * instructions needing r6.xy/r6.xyz/r6.xyzw
 */
static int calculate_rename(struct fd3_optimize_context *ctx, int end,
		struct ir3_register *reg, struct ir3_register *newreg)
{
	struct fd3_shader_stateobj *so = ctx->so;
	struct ir3_shader *ir = so->ir;
	unsigned rmask, wmask;
	int i, j, shift, start = end;

	rmask = reg->wrmask << 4;
	wmask = reg->wrmask << 4;

	/* if at the end, we need to rename outputs too: */
	if (end == ir->instrs_count) {
		for (i = 0; i < so->outputs_count; i++) {
			struct ir3_register *out = &ctx->outputs[i];
			if (reg_intersect(out, reg)) {
				rmask |= wrmask(reg, out);
				wmask |= wrmask(reg, out);
			}
		}
	}

	for (i = MIN2(end, ir->instrs_count - 1); i >= 0; i--) {
		struct ir3_instruction *instr = ir->instrs[i];
		struct ir3_register *dst = reg_check(instr, 0);

		/* dst register.. note: on the staring point for the rename
		 * process all the src register but not the dst.  This is
		 * to catch the case that same src register appears in
		 * multiple src positions on the instruction where we start
		 * renaming from:
		 */
		if ((i != end) && dst && reg_intersect(dst, reg)) {
			rmask |= wrmask(reg, dst);
			wmask &= ~wrmask(reg, dst);
			start = i;
			if (!wmask)
				break;
		}

		/* src registers: */
		for (j = 1; j < instr->regs_count; j++) {
			struct ir3_register *src = reg_check(instr, j);

			if (src && reg_intersect(src, reg)) {
				rmask |= wrmask(reg, src);
				wmask |= wrmask(reg, src);
			}
		}
	}

	/* if we haven't found assignment yet for all the components, then
	 * also check inputs:
	 */
	if ((so->type == SHADER_VERTEX) && wmask) {
		for (i = 0; i < so->inputs_count; i++) {
			struct ir3_register *in = &ctx->inputs[i];
			if (reg_intersect(in, reg)) {
				rmask |= wrmask(reg, in);
				wmask &= ~wrmask(reg, in);
				start = -1;
			}
		}
	}

	/* At this point rmask should represent the most restrictive constraint.
	 * Then do renaming, continue backwards until all components are
	 * overwritten.
	 *
	 * Note that the most restrictive constraint might be more restrictive
	 * than 'reg' passed in:
	 */
	*newreg = *reg;
	shift = ffs(rmask) - 1;
	newreg->num = (reg->num & ~REG_MARK) - (4 - shift);
	if (reg->num & REG_MARK)
		newreg->num |= REG_MARK;
	newreg->wrmask = rmask >> shift;

	return start;
}

static void register_rename_one(struct fd3_optimize_context *ctx, int end,
		struct ir3_register *reg, unsigned newnum)
{
	struct fd3_shader_stateobj *so = ctx->so;
	struct ir3_shader *ir = so->ir;
	/* NOTE: shift masks up by 4 or we can loose bits by >> in wrmask(): */
	unsigned rmask = reg->wrmask << 4;
	int i, j;

	void rename(struct ir3_register *target)
	{
		/* if renaming consecutive registers (ie. r6.xyz), and
		 * the single target (src/dst) register we are renaming
		 * here is a subset of that (ie. r6.y) the preserve the
		 * relative offset:
		 */
		target->num = newnum + (target->num & ~REG_MARK) - (reg->num & ~REG_MARK);
	}

	/* if at the end, we need to rename outputs too: */
	if (end == ir->instrs_count) {
		for (i = 0; i < so->outputs_count; i++) {
			struct ir3_register *out = &ctx->outputs[i];
			if (reg_intersect(out, reg)) {
				if (!reg_eq(out, reg))
					rmask |= wrmask(reg, out);
				rename(out);
			}
		}
	}

	for (i = MIN2(end, ir->instrs_count - 1); i >= 0; i--) {
		struct ir3_instruction *instr = ir->instrs[i];
		struct ir3_register *dst = reg_check(instr, 0);

		if ((i != end) && dst && reg_intersect(dst, reg)) {
			rmask &= ~wrmask(reg, dst);
			rename(dst);
			if (!rmask)
				break;
		}

		/* process all the src registers: */
		for (j = 1; j < instr->regs_count; j++) {
			struct ir3_register *src = reg_check(instr, j);

			if (src && reg_intersect(src, reg)) {

				if (!reg_eq(src, reg)) {
					/* NOTE: this is to handle cases like:
					 *
					 *   10:  ...
					 *   11:  sam.p (f32)(xyzw)r4.x, r6.xyz, s#0, t#0
					 *   12:  mov r6.x, ...
					 *   13:  sam.p (f32)(xyzw)r4.x, r6.xyz, s#0, t#0
					 *   14:  ...
					 *
					 * working backwards, from 11, we need to rename the
					 * previous write to r6.x even though r6.x was written
					 * at 12.
					 *
					 * NOTE: this will result in something not purely SSA,
					 * so some special care is needed in copy_propagate()
					 */
					rmask |= wrmask(reg, src);
				}

				rename(src);
			}
		}
	}

	/* and if necessary, inputs: */
	if ((so->type == SHADER_VERTEX) && rmask) {
		for (i = 0; i < so->inputs_count; i++) {
			struct ir3_register *in = &ctx->inputs[i];
			if (reg_intersect(in, reg)) {
				rmask &= ~wrmask(reg, in);
				rename(in);
			}
		}
	}
}

/* live means read before written */
static void compute_liveregs(struct fd3_optimize_context *ctx,
		int start, int pre, regmask_t *liveregs)
{
	struct fd3_shader_stateobj *so = ctx->so;
	struct ir3_shader *ir = so->ir;
	regmask_t written;
	unsigned i, j;

	regmask_init(liveregs);
	regmask_init(&written);

	if (start < 0) {
		/* At the beginning, all the inputs are live.  This is to
		 * prevent assigning inputs (when not all components are
		 * used) to overlapping vec4's and having the hw clobber
		 * some of the input components.  We could be more clever
		 * and instead set VFD_DECODE[n].INSTR.WRITEMASK properly
		 * instead, probably..
		 */
		for (i = 0; i < so->inputs_count; i++) {
			struct ir3_register *r = &ctx->inputs[i];
			if (!(r->num & REG_MARK))
				regmask_set(liveregs, r);
		}

		start = 0;
	}

	for (i = start; i < ir->instrs_count; i++) {
		struct ir3_instruction *instr = ir->instrs[i];
		struct ir3_register *r;

		/* check first src's read: */
		for (j = 1; j < instr->regs_count; j++) {
			r = reg_check(instr, j);
			if (!(r && !(r->num & REG_MARK)))
				continue;
			regmask_set_if_not(liveregs, r, &written);
		}

		/* then dst written (but not on start instr): */
		r = reg_check(instr, 0);
		if (r && !(r->num & REG_MARK)) {
			if (i > pre) {
				regmask_set(&written, r);
			} else {
				/* anything written before the first reference (the
				 * rename starting point) and last reference is also
				 * live.. we don't want to pick a register # that
				 * gets clobbered!
				 */
				regmask_set(liveregs, r);
			}
		}
	}

	/* be sure to account for output registers too: */
	for (i = 0; i < so->outputs_count; i++) {
		struct ir3_register *r = &ctx->outputs[i];
		if (!(r->num & REG_MARK))
			regmask_set_if_not(liveregs, r, &written);
	}
}

static int lowest_available(struct fd3_optimize_context *ctx,
		regmask_t *liveregs, unsigned wrmask)
{
	struct fd3_shader_stateobj *so = ctx->so;
	unsigned i;

	for (i = 0; i < MAX_REG*4; i++) {
		struct ir3_register reg = REG(so, i);
		reg.wrmask = wrmask;
		if (!regmask_get(liveregs, &reg))
			return  i;
	}

	return -1;
}

/**
 * Rename registers taking into account consecutive register constraints
 * for shader outputs and for cat5 (texture sample) instruction src and
 * dst.
 *
 * This is done twice, once at the beginning to convert into SSA(ish)
 * form, with each register assigned only once.  Then other optimization
 * passes are run on the SSA form, and at the end we run register rename
 * again to assign the final register values.
 *
 * Note that for vertex shaders (which don't use bary instructions but
 * instead expect the shader core to have already placed attributes into
 * specified registers) we need to take into account inputs as well.  For
 * frag shaders with bary instructions, we can ignore this because we can
 * fetch input components into arbitrary scalar registers.
 */
static void register_rename(struct fd3_optimize_context *ctx, boolean to_ssa)
{
	struct fd3_shader_stateobj *so = ctx->so;
	struct ir3_shader *ir = so->ir;
	int i, j;
	/* for to_ssa case, start at r1.x so we don't clobber r0.xy: */
	int next_idx = regid(1,0);

	void rename_from(int end, struct ir3_register *reg)
	{
		struct ir3_register newreg;
		int start =  calculate_rename(ctx, end, reg, &newreg);

		if (to_ssa) {
			register_rename_one(ctx, end, &newreg, next_idx);
			next_idx += util_last_bit(newreg.wrmask);
		} else {
			/* at this point, no subsequent instructions or outputs
			 * should have REG_MARK set, so safe to use regmask_t..
			 */
			regmask_t liveregs;
			compute_liveregs(ctx, start, end, &liveregs);
			register_rename_one(ctx, end, &newreg,
					lowest_available(ctx, &liveregs, newreg.wrmask));
		}
	}

	/* first mark all registers as needing renaming: */
	if (so->type == SHADER_VERTEX)
		for (i = 0; i < so->inputs_count; i++)
			ctx->inputs[i].num |= REG_MARK;     /* inputs always GPR */

	for (i = 0; i < ir->instrs_count; i++) {
		struct ir3_instruction *instr = ir->instrs[i];
		for (j = 0; j < instr->regs_count; j++) {
			struct ir3_register *r = reg_check(instr, j);
			/* we can't rename r0.xy in src for bary.f: */
			if (opc_eq(instr, 2, OPC_BARY_F) && (j > 0))
				break;
			if (r)
				r->num |= REG_MARK;
		}
	}

	for (i = 0; i < so->outputs_count; i++)
		ctx->outputs[i].num |= REG_MARK;     /* outputs always GPR */

	/* then rename registers which are not already renamed! */
	for (i = 0; i < so->outputs_count; i++) {
		struct ir3_register *reg = &ctx->outputs[i];
		rename_from(ir->instrs_count, reg);
	}

	for (i = ir->instrs_count - 1; i >= 0; i--) {
		struct ir3_instruction *instr = ir->instrs[i];
		/* consider only src registers: */
		for (j = 1; j < instr->regs_count; j++) {
			struct ir3_register *reg = reg_check(instr, j);
			if (reg && (reg->num & REG_MARK))
				rename_from(i, reg);
		}
	}

	/* at this point, any register w/ REG_MARK still set is definitely
	 * dead.. probably we can ignore and just let dead code elimination
	 * clean up the mess..
	 */
}

void fd3_optimize_run(struct fd3_shader_stateobj *so)
{
	struct fd3_optimize_context ctx = {
			.so = so,
	};
	int i;

	for (i = 0; i < so->outputs_count; i++)
		ctx.outputs[i] = REG(so, so->outputs[i].regid);

	if (so->type == SHADER_VERTEX)
		for (i = 0; i < so->inputs_count; i++)
			ctx.inputs[i] = REG(so, so->inputs[i].regid);

	debug_printf("------------------------------------------------------------\n");
	dump_info(&ctx, "before");

	/* rename into SSA(ish) form: */
	register_rename(&ctx, true);

	copy_propagate(&ctx);
	dead_code_eliminate(&ctx);

	/* rename back to final registers: */
	register_rename(&ctx, false);

	legalize_it(&ctx);

	dump_info(&ctx, " after");
	debug_printf("------------------------------------------------------------\n");

	for (i = 0; i < so->outputs_count; i++)
		so->outputs[i].regid = ctx.outputs[i].num;

	if (so->type == SHADER_VERTEX)
		for (i = 0; i < so->inputs_count; i++)
			so->inputs[i].regid = ctx.inputs[i].num;
}
