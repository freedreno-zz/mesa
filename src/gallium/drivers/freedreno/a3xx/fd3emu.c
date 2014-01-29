/* -*- mode: C; c-file-style: "k&r"; tab-width 4; indent-tabs-mode: t; -*- */

/*
 * Copyright (C) 2014 Rob Clark <robclark@freedesktop.org>
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

/* A simple emulator for shader program, for testing purposes. */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#include "instr-a3xx.h"
#include "disasm.h"

void fd3_emu_run(void *instrs, uint32_t instrs_count,
		float *consts, uint32_t consts_size,
		float *regs, uint32_t regs_size);

typedef union {
	float f;
	uint32_t u;
	int32_t i;
} regval_t;

struct fd3_emu_regstate {
	instr_t *instr; /* the last writer */
	uint32_t cycle; /* cycle # of assignment */
};

struct fd3_emu_ctx {
	uint32_t  pc;
	uint32_t  cycle;

	/* cycle count of last sfu/tex pipeline sync (ss)/(sy): */
	uint32_t  last_ss, last_sy;

	instr_t  *cur;

	/* last input instruction: */
	instr_t  *last_input;

	instr_t  *instrs;
	uint32_t  instrs_count;
	regval_t *consts;
	uint32_t  consts_count;
	regval_t *regs;
	uint32_t  regs_count;

	/* special regs: */
	regval_t  a0[4], p0[4];

	/* maps GPR to assigner info: */
	struct fd3_emu_regstate regstate[256];

	bool verbose;

	bool error, killed;
};

static void emu_error(struct fd3_emu_ctx *ctx, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
}

static void emu_fatal(struct fd3_emu_ctx *ctx, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
	ctx->error = true;
}

#define emu_assert(ctx, cond) do { \
		if (!(cond)) emu_fatal(ctx, "%s:%d: error: "#cond, __func__, __LINE__); \
	} while (0)

#define emu_check(ctx, cond, fmt, ...) do { \
		if (!(cond)) emu_error(ctx, "cyc:%04u pc:%04u - "fmt, (ctx)->cycle, (ctx)->pc - 1, ##__VA_ARGS__); \
	} while (0)

struct fd3_regsrc {
	reg_t   src;
	uint8_t full   : 1;
	uint8_t r      : 1;
	uint8_t c      : 1;
	uint8_t im     : 1;
	uint8_t neg    : 1;
	uint8_t abs    : 1;
	uint8_t rel    : 1;
};


static unsigned regidx(reg_t reg)
{
	return (4 * reg.num) + reg.comp;
}

static bool is_alu(instr_t *instr)
{
	return (1 <= instr->opc_cat) && (instr->opc_cat <= 3);
}

static bool is_sfu(instr_t *instr)
{
	return (instr->opc_cat == 4);
}

static bool is_tex(instr_t *instr)
{
	return (instr->opc_cat == 5);
}

static bool is_input(instr_t *instr)
{
	return (instr->opc_cat == 2) && (instr->cat2.opc == OPC_BARY_F);
}

/* calculate required # of delay slots between the instruction that
 * assigns a value and the one that consumes
 */
static int delayslots(instr_t *assigner, instr_t *consumer, unsigned n)
{
	/* worst case is cat1-3 (alu) -> cat4/5 needing 6 cycles, normal
	 * alu -> alu needs 3 cycles, cat4 -> alu and texture fetch
	 * handled with sync bits
	 */

	if (is_sfu(assigner) || is_tex(assigner))
		return 0;

	if (is_alu(assigner) && (is_sfu(consumer) || is_tex(consumer))) {
		return 6;
	} else if ((consumer->opc_cat == 3) && (n == 2)) {
		/* special case, 3rd src to cat3 not required on first cycle */
		return 1;
	} else {
		return 3;
	}
}

static regval_t read_src(struct fd3_emu_ctx *ctx, int n, struct fd3_regsrc rs)
{
	int idx = regidx(rs.src);
	regval_t r;

	assert(rs.full);  // TODO half
	assert(!rs.r);

	if (rs.im) {
		r.i = rs.src.iim_val;
	} else if (rs.c) {
		emu_check(ctx, idx < ctx->consts_count,
				"invalid const: %u (of %u)", idx, ctx->consts_count);
		r = ctx->consts[idx];
	} else if (rs.src.num == REG_P0) {
		r = ctx->p0[rs.src.comp];
	} else if (rs.src.num == REG_A0) {
		r = ctx->a0[rs.src.comp];
	} else {
		struct fd3_emu_regstate *s = &ctx->regstate[idx];
		unsigned delay;

// XXX this probably isn't quite what we want for rel addr..

		emu_check(ctx, idx < ctx->regs_count,
				"invalid reg: %u (of %u)", idx, ctx->regs_count);
		r = ctx->regs[idx];

		if (s->instr) {  /* input registers have no assigner */
			/* check sync constraints: */
			if (is_sfu(s->instr)) {
				emu_check(ctx, ctx->last_ss > s->cycle,
						"missing sync with sfu");
			} else if (is_tex(s->instr)) {
				emu_check(ctx, ctx->last_sy > s->cycle,
						"missing sync with tex");
			}

			/* check timing constraints: */
			delay = delayslots(s->instr, ctx->cur, n);
			emu_check(ctx, ctx->cycle >= (s->cycle + delay),
					"insufficient delay slots: %u (needed %u)",
					(ctx->cycle - s->cycle), delay);
		}
	}

	if (rs.rel) {
		unsigned u = r.f;
		if (rs.c) {
printf("c%d\n", u + idx);
			r = ctx->consts[u + idx];
		} else {
printf("r%d\n", u + idx);
			r = ctx->regs[u + idx];
		}
	}

	if (rs.neg)
		r.f = -r.f;

	if (rs.abs)
		r.f = fabs(r.f);

	if (ctx->verbose)
		printf("  src%d: %08x %f\n", n, r.u, r.f);

	return r;
}

struct fd3_regdst {
	reg_t   dst;
	uint8_t full   : 1;
	uint8_t rel    : 1;
};

static void write_dst(struct fd3_emu_ctx *ctx, regval_t r, struct fd3_regdst rd)
{
	int idx = regidx(rd.dst);

	emu_assert(ctx, !rd.rel);

	if (ctx->verbose)
		printf("  dst:  %08x %f\n", r.u, r.f);

	// TODO track the required delay cycles for p0/a0..
	if (rd.dst.num == REG_P0) {
		ctx->p0[rd.dst.comp] = r;
	} else if (rd.dst.num == REG_A0) {
		ctx->a0[rd.dst.comp] = r;
	} else {
printf("%04u: dst: %d\n", ctx->pc, rd.dst.num);
		emu_assert(ctx, rd.full);  // TODO half
		emu_check(ctx, idx < ctx->regs_count,
				"invalid reg: %u (of %u)", idx, ctx->regs_count);

		ctx->regs[idx] = r;

		ctx->regstate[idx].instr = ctx->cur;
		ctx->regstate[idx].cycle = ctx->cycle;
	}
}

static void
emu_run_cat0(struct fd3_emu_ctx *ctx, instr_cat0_t *cat0)
{
	switch (cat0->opc) {
	case OPC_NOP:
		break;
	case OPC_BR:
		if (ctx->p0[cat0->comp].u)
			ctx->pc += cat0->immed - 1;
		break;
	case OPC_JUMP:
		ctx->pc += cat0->immed - 1;
		break;
	case OPC_KILL:
		if (ctx->p0[cat0->comp].u)
			ctx->killed = true;
		break;
	default:
		emu_fatal(ctx, "unhandled cat0 opc: %u", cat0->opc);
		break;
	}
}

static void
emu_run_cat1(struct fd3_emu_ctx *ctx, instr_cat1_t *cat1)
{
	regval_t dst, src;

	emu_assert(ctx, !cat1->even);
	emu_assert(ctx, !cat1->pos_inf);

	if (cat1->src_im) {
		src.f = cat1->fim_val;
	} else if (cat1->src_rel && !cat1->src_c) {
		emu_assert(ctx, 0); // TODO
	} else {
		src = read_src(ctx, 0, (struct fd3_regsrc){
			.src  = (reg_t)cat1->src,
			.full = type_size(cat1->src_type) == 32,
			.r    = cat1->src_r,
			.c    = cat1->src_c,
			.im   = cat1->src_im,
			.rel  = cat1->src_rel,
		});
	}

	if (cat1->src_type == cat1->dst_type) {
		dst.f = src.f;
	} else if (type_float(cat1->src_type) &&
			type_uint(cat1->dst_type)) {
		dst.u = src.f;
	} else if (type_float(cat1->src_type) &&
			type_sint(cat1->dst_type)) {
		dst.i = src.f;
	} else if (type_uint(cat1->src_type) &&
			type_sint(cat1->dst_type)) {
		dst.i = src.u;
	} else if (type_uint(cat1->src_type) &&
			type_float(cat1->dst_type)) {
		dst.i = src.f;
	} else if (type_sint(cat1->src_type) &&
			type_float(cat1->dst_type)) {
		dst.f = src.i;
	} else if (type_sint(cat1->src_type) &&
			type_uint(cat1->dst_type)) {
		dst.f = src.u;
	} else {
		emu_assert(ctx, 0); // TODO
	}

	write_dst(ctx, dst, (struct fd3_regdst){
		.dst  = (reg_t)(cat1->dst),
		.full = type_size(cat1->dst_type) == 32,
		.rel  = cat1->dst_rel,
	});
}

static void
emu_run_cat2(struct fd3_emu_ctx *ctx, instr_cat2_t *cat2)
{
	struct fd3_regsrc src2rs;
	regval_t dst, src1, src2;

	if (cat2->c1.src1_c) {
		src1 = read_src(ctx, 0, (struct fd3_regsrc){
			.src  = (reg_t)cat2->c1.src1,
			.full = cat2->full,
			.r    = cat2->src1_r,
			.c    = cat2->c1.src1_c,
			.im   = cat2->src1_im,
			.neg  = cat2->src1_neg,
			.abs  = cat2->src1_abs,
		});
	} else if (cat2->rel1.src1_rel) {
		src1 = read_src(ctx, 0, (struct fd3_regsrc){
			.src  = (reg_t)cat2->rel1.src1,
			.full = cat2->full,
			.r    = cat2->src1_r,
			.c    = cat2->rel1.src1_c,
			.im   = cat2->src1_im,
			.neg  = cat2->src1_neg,
			.abs  = cat2->src1_abs,
			.rel  = cat2->rel1.src1_rel,
		});
	} else {
		src1 = read_src(ctx, 0, (struct fd3_regsrc){
			.src  = (reg_t)cat2->src1,
			.full = cat2->full,
			.r    = cat2->src1_r,
			.im   = cat2->src1_im,
			.neg  = cat2->src1_neg,
			.abs  = cat2->src1_abs,
		});
	}

	if (cat2->c2.src2_c) {
		src2rs = (struct fd3_regsrc){
			.src  = (reg_t)cat2->c2.src2,
			.full = cat2->full,
			.r    = cat2->src2_r,
			.c    = cat2->c2.src2_c,
			.im   = cat2->src2_im,
			.neg  = cat2->src2_neg,
			.abs  = cat2->src2_abs,
		};
	} else if (cat2->rel2.src2_rel) {
		src2rs = (struct fd3_regsrc){
			.src  = (reg_t)cat2->rel2.src2,
			.full = cat2->full,
			.r    = cat2->src2_r,
			.c    = cat2->rel2.src2_c,
			.im   = cat2->src2_im,
			.neg  = cat2->src2_neg,
			.abs  = cat2->src2_abs,
			.rel  = cat2->rel2.src2_rel,
		};
	} else {
		src2rs = (struct fd3_regsrc){
			.src  = (reg_t)(cat2->src2),
			.full = cat2->full,
			.r    = cat2->src2_r,
			.im   = cat2->src2_im,
			.neg  = cat2->src2_neg,
			.abs  = cat2->src2_abs,
		};
	}

	switch (cat2->opc) {
	case OPC_ABSNEG_F:
	case OPC_FLOOR_F:
		/* no src2 */
		break;
	default:
		src2 = read_src(ctx, 1, src2rs);
	}

	switch (cat2->opc) {
	case OPC_ADD_F:
		dst.f = src1.f + src2.f;
		break;
	case OPC_MIN_F:
		dst.f = fminf(src1.f, src2.f);
		break;
	case OPC_MAX_F:
		dst.f = fmaxf(src1.f, src2.f);
		break;
	case OPC_MUL_F:
		dst.f = src1.f * src2.f;
		break;
	case OPC_MUL_S:
		dst.i = src1.i * src2.i;
		break;
	case OPC_CMPS_F:
		switch (cat2->cond) {
		case 0:	dst.u = (src1.f <  src2.f) ? 1 : 0;	break;
		case 1:	dst.u = (src1.f <= src2.f) ? 1 : 0;	break;
		case 2:	dst.u = (src1.f >  src2.f) ? 1 : 0;	break;
		case 3:	dst.u = (src1.f >= src2.f) ? 1 : 0;	break;
		case 4:	dst.u = (src1.f == src2.f) ? 1 : 0;	break;
		case 5:	dst.u = (src1.f != src2.f) ? 1 : 0;	break;
		default:
			emu_fatal(ctx, "unhandled cat2 cond: %u", cat2->cond);
		}
		break;
	case OPC_ABSNEG_F:
		/* seems to basically just be a type of mov which can do
		 * (abs) and/or (neg)..
		 */
		dst.f = src1.f;
		break;
	case OPC_FLOOR_F:
		dst.f = floorf(src1.f);
		break;
	case OPC_TRUNC_F:
		dst.f = truncf(src1.f);
		break;
	case OPC_ADD_S:
		dst.i = src1.i + src2.i;
		break;
	case OPC_BARY_F:
		dst.i = (src1.i + 1) * (src2.i + 1);
		/* bary.f seems to read r0.xy */
		src2rs.src.dummy12++;
		src2 = read_src(ctx, 1, src2rs);
		dst.i *= src2.i;
		break;
	default:
		emu_fatal(ctx, "unhandled cat2 opc: %u", cat2->opc);
		break;
	}

	write_dst(ctx, dst, (struct fd3_regdst){
		.dst  = (reg_t)(cat2->dst),
		.full = cat2->full ^ cat2->dst_half,
	});
}

static void
emu_run_cat3(struct fd3_emu_ctx *ctx, instr_cat3_t *cat3)
{
	regval_t dst, src1, src2, src3;
	bool full = instr_cat3_full(cat3);

	if (cat3->c1.src1_c) {
		src1 = read_src(ctx, 0, (struct fd3_regsrc){
			.src  = (reg_t)cat3->c1.src1,
			.full = full,
			.r    = cat3->src1_r,
			.c    = cat3->c1.src1_c,
			.neg  = cat3->src1_neg,
		});
	} else if (cat3->rel1.src1_rel) {
		src1 = read_src(ctx, 0, (struct fd3_regsrc){
			.src  = (reg_t)cat3->rel1.src1,
			.full = full,
			.r    = cat3->src1_r,
			.c    = cat3->rel1.src1_c,
			.neg  = cat3->src1_neg,
			.rel  = cat3->rel1.src1_rel,
		});
	} else {
		src1 = read_src(ctx, 0, (struct fd3_regsrc){
			.src  = (reg_t)cat3->src1,
			.full = full,
			.r    = cat3->src1_r,
			.neg  = cat3->src1_neg,
		});
	}

	src2 = read_src(ctx, 1, (struct fd3_regsrc){
		.src  = (reg_t)cat3->src2,
		.full = full,
		.r    = cat3->src2_r,
		.neg  = cat3->src2_neg,
	});

	if (cat3->c2.src3_c) {
		src3 = read_src(ctx, 2, (struct fd3_regsrc){
			.src  = (reg_t)cat3->c2.src3,
			.full = full,
			.r    = cat3->src3_r,
			.c    = cat3->c2.src3_c,
			.neg  = cat3->src3_neg,
		});
	} else if (cat3->rel2.src3_rel) {
		src3 = read_src(ctx, 2, (struct fd3_regsrc){
			.src  = (reg_t)cat3->rel2.src3,
			.full = full,
			.r    = cat3->src3_r,
			.c    = cat3->rel2.src3_c,
			.neg  = cat3->src3_neg,
			.rel  = cat3->rel2.src3_rel,
		});
	} else {
		src3 = read_src(ctx, 2, (struct fd3_regsrc){
			.src  = (reg_t)cat3->src3,
			.full = full,
			.r    = cat3->src3_r,
			.neg  = cat3->src3_neg,
		});
	}

	switch (cat3->opc) {
	case OPC_MAD_F32:
		dst.f = (src1.f * src2.f) + src3.f;
		break;
	case OPC_SEL_F32:
		dst.f = (src2.i >= 0) ? src3.f : src1.f;
		break;
	case OPC_SEL_B32:
		dst.f = src2.u ? src3.f : src1.f;
		break;
	default:
		emu_fatal(ctx, "unhandled cat3 opc: %u", cat3->opc);
		break;
	}

	write_dst(ctx, dst, (struct fd3_regdst){
		.dst  = (reg_t)(cat3->dst),
		.full = full ^ cat3->dst_half,
	});
}

static void
emu_run_cat4(struct fd3_emu_ctx *ctx, instr_cat4_t *cat4)
{
	regval_t dst, src;

	if (cat4->c.src_c) {
		src = read_src(ctx, 0, (struct fd3_regsrc){
			.src  = (reg_t)cat4->c.src,
			.full = cat4->full,
			.r    = cat4->src_r,
			.c    = cat4->c.src_c,
			.im   = cat4->src_im,
			.neg  = cat4->src_neg,
			.abs  = cat4->src_abs,
		});
	} else if (cat4->rel.src_rel) {
		src = read_src(ctx, 0, (struct fd3_regsrc){
			.src  = (reg_t)cat4->rel.src,
			.full = cat4->full,
			.r    = cat4->src_r,
			.c    = cat4->rel.src_c,
			.im   = cat4->src_im,
			.neg  = cat4->src_neg,
			.abs  = cat4->src_abs,
			.rel  = cat4->rel.src_rel,
		});
	} else {
		src = read_src(ctx, 0, (struct fd3_regsrc){
			.src  = (reg_t)cat4->src,
			.full = cat4->full,
			.r    = cat4->src_r,
			.im   = cat4->src_im,
			.neg  = cat4->src_neg,
			.abs  = cat4->src_abs,
		});
	}

	switch (cat4->opc) {
	case OPC_RCP:	dst.f = 1.0 / src.f;		break;
	case OPC_RSQ:	dst.f = 1.0 / sqrtf(src.f);	break;
	case OPC_LOG2:	dst.f = cosf(src.f);		break;
	case OPC_EXP2:	dst.f = exp2(src.f);		break;
	case OPC_SIN:	dst.f = sinf(src.f);		break;
	case OPC_COS:	dst.f = cosf(src.f);		break;
	case OPC_SQRT:	dst.f = sqrtf(src.f);		break;
	default:
		emu_fatal(ctx, "unhandled cat4 opc: %u", cat4->opc);
		break;
	}

	write_dst(ctx, dst, (struct fd3_regdst){
		.dst  = (reg_t)(cat4->dst),
		.full = cat4->full ^ cat4->dst_half,
	});
}

static void
emu_run_cat5(struct fd3_emu_ctx *ctx, instr_cat5_t *cat5)
{
	unsigned i, srccomp = 2;
	regval_t dst[4];

	switch (cat5->opc) {
	case OPC_SAM:
		break;
	default:
		emu_fatal(ctx, "unhandled cat5 opc: %u", cat5->opc);
		break;
	}


	if (cat5->is_p)
		srccomp++;

	if (cat5->is_3d)
		srccomp++;

	for (i = 0; i < 4; i++) {
		unsigned j = (i % srccomp);
		regval_t src;

		src = read_src(ctx, 0, (struct fd3_regsrc){
			.src  = (reg_t)(cat5->src1 + j),
			.full = cat5->full,
		});

		dst[i].u = src.u + cat5->norm.samp + cat5->norm.tex;
	}

	for (i = 0; i < 4; i++) {
		if (!(cat5->wrmask & (1 << i)))
			continue;

		write_dst(ctx, dst[i], (struct fd3_regdst){
			.dst  = (reg_t)(cat5->dst + i),
			.full = (type_size(cat5->type) == 32),
		});
	}
}

static void
emu_run(struct fd3_emu_ctx *ctx)
{
	instr_t *last_instr = NULL;

	while ((ctx->pc < ctx->instrs_count) && !ctx->error) {
		instr_t *instr = &ctx->instrs[ctx->pc++];

		if (ctx->verbose) {
			printf("----------\n%04u: ", ctx->pc-1);
			disasm_a3xx((uint32_t *)instr, sizeof(instr) / 4, -1, 0);
		}

		if (last_instr) {
			emu_check(ctx, !(is_sfu(last_instr) && is_sfu(instr)),
					"two sfu in a row");
		} else {
			emu_check(ctx, instr->ss, "needs (ss) on first instruction");
			emu_check(ctx, instr->sync, "needs (sy) on first instruction");
		}

		// XXX not sure if we need to keep different cycle counters for
		// XXX tex/alu/sfu, or just tex vs alu/sfu??
		if (!is_tex(instr))
			ctx->cycle++;

		ctx->cur = instr;

		if (is_input(instr)) {
			if (ctx->last_input) {
				emu_check(ctx, !ctx->last_input->cat2.ei,
						"(ei) set before last input");
			}
			ctx->last_input = instr;
		}

		if ((1 <= instr->opc_cat) && (instr->opc_cat <= 4))
			if (instr->ss)
				ctx->last_ss = ctx->cycle;
		if (instr->sync)
			ctx->last_sy = ctx->cycle;

		/* special handling for 'end' instruction: */
		if ((instr->opc_cat == 0) && (instr->cat0.opc == OPC_END))
			return;

		switch (instr->opc_cat) {
		case 0:	emu_run_cat0(ctx, &instr->cat0);	break;
		case 1:	emu_run_cat1(ctx, &instr->cat1);	break;
		case 2:	emu_run_cat2(ctx, &instr->cat2);	break;
		case 3:	emu_run_cat3(ctx, &instr->cat3);	break;
		case 4:	emu_run_cat4(ctx, &instr->cat4);	break;
		case 5:	emu_run_cat5(ctx, &instr->cat5);	break;
		default:
			emu_fatal(ctx, "unhandled instruction category: %d", instr->opc_cat);
			break;
		}

		last_instr = instr;
	}

	if (ctx->last_input) {
		emu_check(ctx, ctx->last_input->cat2.ei,
				"(ei) not set on last input");
	}

	emu_error(ctx, "execution continued past end of program!");
}

void
fd3_emu_run(void *instrs, uint32_t instrs_count,
		float *consts, uint32_t consts_count,
		float *regs, uint32_t regs_count)
{
	struct fd3_emu_ctx ctx = {
			.instrs = instrs,
			.instrs_count = instrs_count,
			.consts = (regval_t *)consts,
			.consts_count = consts_count,
			.regs = (regval_t *)regs,
			.regs_count = regs_count,
//			.verbose = true,
	};
	emu_run(&ctx);
}
