/*
 * Copyright (c) 2012 Rob Clark <robdclark@gmail.com>
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

#include "ir3.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>

#include "freedreno_util.h"
#include "instr-a3xx.h"

#define CHUNK_SZ 1020

struct ir3_heap_chunk {
	struct ir3_heap_chunk *next;
	uint32_t heap[CHUNK_SZ];
};

static void grow_heap(struct ir3 *shader)
{
	struct ir3_heap_chunk *chunk = calloc(1, sizeof(*chunk));
	chunk->next = shader->chunk;
	shader->chunk = chunk;
	shader->heap_idx = 0;
}

/* simple allocator to carve allocations out of an up-front allocated heap,
 * so that we can free everything easily in one shot.
 */
void * ir3_alloc(struct ir3 *shader, int sz)
{
	void *ptr;

	sz = align(sz, 4) / 4;

	if ((shader->heap_idx + sz) > CHUNK_SZ)
		grow_heap(shader);

	ptr = &shader->chunk->heap[shader->heap_idx];
	shader->heap_idx += sz;

	return ptr;
}

struct ir3 * ir3_create(unsigned nin, unsigned nout)
{
	struct ir3 *shader =
			calloc(1, sizeof(struct ir3));
	grow_heap(shader);

	shader->ninputs = nin;
	shader->inputs = ir3_alloc(shader, sizeof(shader->inputs[0]) * nin);

	shader->noutputs = nout;
	shader->outputs = ir3_alloc(shader, sizeof(shader->outputs[0]) * nout);

	list_inithead(&shader->cf_list);

	return shader;
}

void ir3_destroy(struct ir3 *shader)
{
	while (shader->chunk) {
		struct ir3_heap_chunk *chunk = shader->chunk;
		shader->chunk = chunk->next;
		free(chunk);
	}
	free(shader->indirects);
	free(shader->predicates);
	free(shader->baryfs);
	free(shader);
}

#define iassert(cond) do { \
	if (!(cond)) { \
		assert(cond); \
		return -1; \
	} } while (0)

static uint32_t reg(struct ir3_register *reg, struct ir3_info *info,
		uint32_t repeat, uint32_t valid_flags)
{
	reg_t val = { .dummy32 = 0 };

	if (reg->flags & ~valid_flags) {
		debug_printf("; INVALID FLAGS: %x vs %x\n",
				reg->flags, valid_flags);
	}

	if (!(reg->flags & IR3_REG_R))
		repeat = 0;

	if (reg->flags & IR3_REG_IMMED) {
		val.iim_val = reg->iim_val;
	} else {
		unsigned components;

		if (reg->flags & IR3_REG_RELATIV) {
			components = reg->size;
			val.dummy10 = reg->offset;
		} else {
			components = util_last_bit(reg->wrmask);
			val.comp = reg->num & 0x3;
			val.num  = reg->num >> 2;
		}

		int16_t max = (reg->num + repeat + components - 1) >> 2;

		if (reg->flags & IR3_REG_CONST) {
			info->max_const = MAX2(info->max_const, max);
		} else if (val.num == 63) {
			/* ignore writes to dummy register r63.x */
		} else if ((max != REG_A0) && (max != REG_P0)) {
			if (reg->flags & IR3_REG_HALF) {
				info->max_half_reg = MAX2(info->max_half_reg, max);
			} else {
				info->max_reg = MAX2(info->max_reg, max);
			}
		}
	}

	return val.dummy32;
}

static int emit_cat0(struct ir3_instruction *instr, void *ptr,
		struct ir3_info *info)
{
	instr_cat0_t *cat0 = ptr;

	cat0->immed    = instr->cat0.immed;
	cat0->repeat   = instr->repeat;
	cat0->ss       = !!(instr->flags & IR3_INSTR_SS);
	cat0->inv      = instr->cat0.inv;
	cat0->comp     = instr->cat0.comp;
	cat0->opc      = instr->opc;
	cat0->jmp_tgt  = !!(instr->flags & IR3_INSTR_JP);
	cat0->sync     = !!(instr->flags & IR3_INSTR_SY);
	cat0->opc_cat  = 0;

	return 0;
}

static uint32_t type_flags(type_t type)
{
	return (type_size(type) == 32) ? 0 : IR3_REG_HALF;
}

static int emit_cat1(struct ir3_instruction *instr, void *ptr,
		struct ir3_info *info)
{
	struct ir3_register *dst = instr->regs[0];
	struct ir3_register *src = instr->regs[1];
	instr_cat1_t *cat1 = ptr;

	iassert(instr->regs_count == 2);
	iassert(!((dst->flags ^ type_flags(instr->cat1.dst_type)) & IR3_REG_HALF));
	iassert((src->flags & IR3_REG_IMMED) ||
			!((src->flags ^ type_flags(instr->cat1.src_type)) & IR3_REG_HALF));

	if (src->flags & IR3_REG_IMMED) {
		cat1->iim_val = src->iim_val;
		cat1->src_im  = 1;
	} else if (src->flags & IR3_REG_RELATIV) {
		cat1->off       = reg(src, info, instr->repeat,
				IR3_REG_R | IR3_REG_CONST | IR3_REG_HALF | IR3_REG_RELATIV);
		cat1->src_rel   = 1;
		cat1->src_rel_c = !!(src->flags & IR3_REG_CONST);
	} else {
		cat1->src  = reg(src, info, instr->repeat,
				IR3_REG_R | IR3_REG_CONST | IR3_REG_HALF);
		cat1->src_c     = !!(src->flags & IR3_REG_CONST);
	}

	cat1->dst      = reg(dst, info, instr->repeat,
			IR3_REG_RELATIV | IR3_REG_EVEN |
			IR3_REG_R | IR3_REG_POS_INF | IR3_REG_HALF);
	cat1->repeat   = instr->repeat;
	cat1->src_r    = !!(src->flags & IR3_REG_R);
	cat1->ss       = !!(instr->flags & IR3_INSTR_SS);
	cat1->ul       = !!(instr->flags & IR3_INSTR_UL);
	cat1->dst_type = instr->cat1.dst_type;
	cat1->dst_rel  = !!(dst->flags & IR3_REG_RELATIV);
	cat1->src_type = instr->cat1.src_type;
	cat1->even     = !!(dst->flags & IR3_REG_EVEN);
	cat1->pos_inf  = !!(dst->flags & IR3_REG_POS_INF);
	cat1->jmp_tgt  = !!(instr->flags & IR3_INSTR_JP);
	cat1->sync     = !!(instr->flags & IR3_INSTR_SY);
	cat1->opc_cat  = 1;

	return 0;
}

static int emit_cat2(struct ir3_instruction *instr, void *ptr,
		struct ir3_info *info)
{
	struct ir3_register *dst = instr->regs[0];
	struct ir3_register *src1 = instr->regs[1];
	struct ir3_register *src2 = instr->regs[2];
	instr_cat2_t *cat2 = ptr;
	unsigned absneg = ir3_cat2_absneg(instr->opc);

	iassert((instr->regs_count == 2) || (instr->regs_count == 3));

	if (src1->flags & IR3_REG_RELATIV) {
		iassert(src1->num < (1 << 10));
		cat2->rel1.src1      = reg(src1, info, instr->repeat,
				IR3_REG_RELATIV | IR3_REG_CONST | IR3_REG_R |
				IR3_REG_HALF | absneg);
		cat2->rel1.src1_c    = !!(src1->flags & IR3_REG_CONST);
		cat2->rel1.src1_rel  = 1;
	} else if (src1->flags & IR3_REG_CONST) {
		iassert(src1->num < (1 << 12));
		cat2->c1.src1   = reg(src1, info, instr->repeat,
				IR3_REG_CONST | IR3_REG_R | IR3_REG_HALF);
		cat2->c1.src1_c = 1;
	} else {
		iassert(src1->num < (1 << 11));
		cat2->src1 = reg(src1, info, instr->repeat,
				IR3_REG_IMMED | IR3_REG_R | IR3_REG_HALF |
				absneg);
	}
	cat2->src1_im  = !!(src1->flags & IR3_REG_IMMED);
	cat2->src1_neg = !!(src1->flags & (IR3_REG_FNEG | IR3_REG_SNEG | IR3_REG_BNOT));
	cat2->src1_abs = !!(src1->flags & (IR3_REG_FABS | IR3_REG_SABS));
	cat2->src1_r   = !!(src1->flags & IR3_REG_R);

	if (src2) {
		iassert((src2->flags & IR3_REG_IMMED) ||
				!((src1->flags ^ src2->flags) & IR3_REG_HALF));

		if (src2->flags & IR3_REG_RELATIV) {
			iassert(src2->num < (1 << 10));
			cat2->rel2.src2      = reg(src2, info, instr->repeat,
					IR3_REG_RELATIV | IR3_REG_CONST | IR3_REG_R |
					IR3_REG_HALF | absneg);
			cat2->rel2.src2_c    = !!(src2->flags & IR3_REG_CONST);
			cat2->rel2.src2_rel  = 1;
		} else if (src2->flags & IR3_REG_CONST) {
			iassert(src2->num < (1 << 12));
			cat2->c2.src2   = reg(src2, info, instr->repeat,
					IR3_REG_CONST | IR3_REG_R | IR3_REG_HALF);
			cat2->c2.src2_c = 1;
		} else {
			iassert(src2->num < (1 << 11));
			cat2->src2 = reg(src2, info, instr->repeat,
					IR3_REG_IMMED | IR3_REG_R | IR3_REG_HALF |
					absneg);
		}

		cat2->src2_im  = !!(src2->flags & IR3_REG_IMMED);
		cat2->src2_neg = !!(src2->flags & (IR3_REG_FNEG | IR3_REG_SNEG | IR3_REG_BNOT));
		cat2->src2_abs = !!(src2->flags & (IR3_REG_FABS | IR3_REG_SABS));
		cat2->src2_r   = !!(src2->flags & IR3_REG_R);
	}

	cat2->dst      = reg(dst, info, instr->repeat,
			IR3_REG_R | IR3_REG_EI | IR3_REG_HALF);
	cat2->repeat   = instr->repeat;
	cat2->ss       = !!(instr->flags & IR3_INSTR_SS);
	cat2->ul       = !!(instr->flags & IR3_INSTR_UL);
	cat2->dst_half = !!((src1->flags ^ dst->flags) & IR3_REG_HALF);
	cat2->ei       = !!(dst->flags & IR3_REG_EI);
	cat2->cond     = instr->cat2.condition;
	cat2->full     = ! (src1->flags & IR3_REG_HALF);
	cat2->opc      = instr->opc;
	cat2->jmp_tgt  = !!(instr->flags & IR3_INSTR_JP);
	cat2->sync     = !!(instr->flags & IR3_INSTR_SY);
	cat2->opc_cat  = 2;

	return 0;
}

static int emit_cat3(struct ir3_instruction *instr, void *ptr,
		struct ir3_info *info)
{
	struct ir3_register *dst = instr->regs[0];
	struct ir3_register *src1 = instr->regs[1];
	struct ir3_register *src2 = instr->regs[2];
	struct ir3_register *src3 = instr->regs[3];
	unsigned absneg = ir3_cat3_absneg(instr->opc);
	instr_cat3_t *cat3 = ptr;
	uint32_t src_flags = 0;

	switch (instr->opc) {
	case OPC_MAD_F16:
	case OPC_MAD_U16:
	case OPC_MAD_S16:
	case OPC_SEL_B16:
	case OPC_SEL_S16:
	case OPC_SEL_F16:
	case OPC_SAD_S16:
	case OPC_SAD_S32:  // really??
		src_flags |= IR3_REG_HALF;
		break;
	default:
		break;
	}

	iassert(instr->regs_count == 4);
	iassert(!((src1->flags ^ src_flags) & IR3_REG_HALF));
	iassert(!((src2->flags ^ src_flags) & IR3_REG_HALF));
	iassert(!((src3->flags ^ src_flags) & IR3_REG_HALF));

	if (src1->flags & IR3_REG_RELATIV) {
		iassert(src1->num < (1 << 10));
		cat3->rel1.src1      = reg(src1, info, instr->repeat,
				IR3_REG_RELATIV | IR3_REG_CONST | IR3_REG_R |
				IR3_REG_HALF | absneg);
		cat3->rel1.src1_c    = !!(src1->flags & IR3_REG_CONST);
		cat3->rel1.src1_rel  = 1;
	} else if (src1->flags & IR3_REG_CONST) {
		iassert(src1->num < (1 << 12));
		cat3->c1.src1   = reg(src1, info, instr->repeat,
				IR3_REG_CONST | IR3_REG_R | IR3_REG_HALF);
		cat3->c1.src1_c = 1;
	} else {
		iassert(src1->num < (1 << 11));
		cat3->src1 = reg(src1, info, instr->repeat,
				IR3_REG_R | IR3_REG_HALF | absneg);
	}

	cat3->src1_neg = !!(src1->flags & (IR3_REG_FNEG | IR3_REG_SNEG | IR3_REG_BNOT));
	cat3->src1_r   = !!(src1->flags & IR3_REG_R);

	cat3->src2     = reg(src2, info, instr->repeat,
			IR3_REG_CONST | IR3_REG_R | IR3_REG_HALF | absneg);
	cat3->src2_c   = !!(src2->flags & IR3_REG_CONST);
	cat3->src2_neg = !!(src2->flags & (IR3_REG_FNEG | IR3_REG_SNEG | IR3_REG_BNOT));
	cat3->src2_r   = !!(src2->flags & IR3_REG_R);


	if (src3->flags & IR3_REG_RELATIV) {
		iassert(src3->num < (1 << 10));
		cat3->rel2.src3      = reg(src3, info, instr->repeat,
				IR3_REG_RELATIV | IR3_REG_CONST | IR3_REG_R |
				IR3_REG_HALF | absneg);
		cat3->rel2.src3_c    = !!(src3->flags & IR3_REG_CONST);
		cat3->rel2.src3_rel  = 1;
	} else if (src3->flags & IR3_REG_CONST) {
		iassert(src3->num < (1 << 12));
		cat3->c2.src3   = reg(src3, info, instr->repeat,
				IR3_REG_CONST | IR3_REG_R | IR3_REG_HALF);
		cat3->c2.src3_c = 1;
	} else {
		iassert(src3->num < (1 << 11));
		cat3->src3 = reg(src3, info, instr->repeat,
				IR3_REG_R | IR3_REG_HALF | absneg);
	}

	cat3->src3_neg = !!(src3->flags & (IR3_REG_FNEG | IR3_REG_SNEG | IR3_REG_BNOT));
	cat3->src3_r   = !!(src3->flags & IR3_REG_R);

	cat3->dst      = reg(dst, info, instr->repeat, IR3_REG_R | IR3_REG_HALF);
	cat3->repeat   = instr->repeat;
	cat3->ss       = !!(instr->flags & IR3_INSTR_SS);
	cat3->ul       = !!(instr->flags & IR3_INSTR_UL);
	cat3->dst_half = !!((src_flags ^ dst->flags) & IR3_REG_HALF);
	cat3->opc      = instr->opc;
	cat3->jmp_tgt  = !!(instr->flags & IR3_INSTR_JP);
	cat3->sync     = !!(instr->flags & IR3_INSTR_SY);
	cat3->opc_cat  = 3;

	return 0;
}

static int emit_cat4(struct ir3_instruction *instr, void *ptr,
		struct ir3_info *info)
{
	struct ir3_register *dst = instr->regs[0];
	struct ir3_register *src = instr->regs[1];
	instr_cat4_t *cat4 = ptr;

	iassert(instr->regs_count == 2);

	if (src->flags & IR3_REG_RELATIV) {
		iassert(src->num < (1 << 10));
		cat4->rel.src      = reg(src, info, instr->repeat,
				IR3_REG_RELATIV | IR3_REG_CONST | IR3_REG_FNEG |
				IR3_REG_FABS | IR3_REG_R | IR3_REG_HALF);
		cat4->rel.src_c    = !!(src->flags & IR3_REG_CONST);
		cat4->rel.src_rel  = 1;
	} else if (src->flags & IR3_REG_CONST) {
		iassert(src->num < (1 << 12));
		cat4->c.src   = reg(src, info, instr->repeat,
				IR3_REG_CONST | IR3_REG_FNEG | IR3_REG_FABS |
				IR3_REG_R | IR3_REG_HALF);
		cat4->c.src_c = 1;
	} else {
		iassert(src->num < (1 << 11));
		cat4->src = reg(src, info, instr->repeat,
				IR3_REG_IMMED | IR3_REG_FNEG | IR3_REG_FABS |
				IR3_REG_R | IR3_REG_HALF);
	}

	cat4->src_im   = !!(src->flags & IR3_REG_IMMED);
	cat4->src_neg  = !!(src->flags & IR3_REG_FNEG);
	cat4->src_abs  = !!(src->flags & IR3_REG_FABS);
	cat4->src_r    = !!(src->flags & IR3_REG_R);

	cat4->dst      = reg(dst, info, instr->repeat, IR3_REG_R | IR3_REG_HALF);
	cat4->repeat   = instr->repeat;
	cat4->ss       = !!(instr->flags & IR3_INSTR_SS);
	cat4->ul       = !!(instr->flags & IR3_INSTR_UL);
	cat4->dst_half = !!((src->flags ^ dst->flags) & IR3_REG_HALF);
	cat4->full     = ! (src->flags & IR3_REG_HALF);
	cat4->opc      = instr->opc;
	cat4->jmp_tgt  = !!(instr->flags & IR3_INSTR_JP);
	cat4->sync     = !!(instr->flags & IR3_INSTR_SY);
	cat4->opc_cat  = 4;

	return 0;
}

static int emit_cat5(struct ir3_instruction *instr, void *ptr,
		struct ir3_info *info)
{
	struct ir3_register *dst = instr->regs[0];
	struct ir3_register *src1 = instr->regs[1];
	struct ir3_register *src2 = instr->regs[2];
	struct ir3_register *src3 = instr->regs[3];
	instr_cat5_t *cat5 = ptr;

	iassert(!((dst->flags ^ type_flags(instr->cat5.type)) & IR3_REG_HALF));

	if (src1) {
		cat5->full = ! (src1->flags & IR3_REG_HALF);
		cat5->src1 = reg(src1, info, instr->repeat, IR3_REG_HALF);
	}


	if (instr->flags & IR3_INSTR_S2EN) {
		if (src2) {
			iassert(!((src1->flags ^ src2->flags) & IR3_REG_HALF));
			cat5->s2en.src2 = reg(src2, info, instr->repeat, IR3_REG_HALF);
		}
		if (src3) {
			iassert(src3->flags & IR3_REG_HALF);
			cat5->s2en.src3 = reg(src3, info, instr->repeat, IR3_REG_HALF);
		}
		iassert(!(instr->cat5.samp | instr->cat5.tex));
	} else {
		iassert(!src3);
		if (src2) {
			iassert(!((src1->flags ^ src2->flags) & IR3_REG_HALF));
			cat5->norm.src2 = reg(src2, info, instr->repeat, IR3_REG_HALF);
		}
		cat5->norm.samp = instr->cat5.samp;
		cat5->norm.tex  = instr->cat5.tex;
	}

	cat5->dst      = reg(dst, info, instr->repeat, IR3_REG_R | IR3_REG_HALF);
	cat5->wrmask   = dst->wrmask;
	cat5->type     = instr->cat5.type;
	cat5->is_3d    = !!(instr->flags & IR3_INSTR_3D);
	cat5->is_a     = !!(instr->flags & IR3_INSTR_A);
	cat5->is_s     = !!(instr->flags & IR3_INSTR_S);
	cat5->is_s2en  = !!(instr->flags & IR3_INSTR_S2EN);
	cat5->is_o     = !!(instr->flags & IR3_INSTR_O);
	cat5->is_p     = !!(instr->flags & IR3_INSTR_P);
	cat5->opc      = instr->opc;
	cat5->jmp_tgt  = !!(instr->flags & IR3_INSTR_JP);
	cat5->sync     = !!(instr->flags & IR3_INSTR_SY);
	cat5->opc_cat  = 5;

	return 0;
}

static int emit_cat6(struct ir3_instruction *instr, void *ptr,
		struct ir3_info *info)
{
	struct ir3_register *dst  = instr->regs[0];
	struct ir3_register *src1 = instr->regs[1];
	struct ir3_register *src2 = (instr->regs_count >= 3) ? instr->regs[2] : NULL;
	instr_cat6_t *cat6 = ptr;

	iassert(instr->regs_count >= 2);

	if (instr->cat6.offset || instr->opc == OPC_LDG) {
		instr_cat6a_t *cat6a = ptr;

		cat6->has_off = true;

		cat6a->dst = reg(dst, info, instr->repeat, IR3_REG_R | IR3_REG_HALF);
		cat6a->src1 = reg(src1, info, instr->repeat, IR3_REG_IMMED);
		cat6a->src1_im = !!(src1->flags & IR3_REG_IMMED);
		if (src2) {
			cat6a->src2 = reg(src2, info, instr->repeat, IR3_REG_IMMED);
			cat6a->src2_im = !!(src2->flags & IR3_REG_IMMED);
		}
		cat6a->off = instr->cat6.offset;
	} else {
		instr_cat6b_t *cat6b = ptr;

		cat6->has_off = false;

		cat6b->dst = reg(dst, info, instr->repeat, IR3_REG_R | IR3_REG_HALF);
		cat6b->src1 = reg(src1, info, instr->repeat, IR3_REG_IMMED);
		cat6b->src1_im = !!(src1->flags & IR3_REG_IMMED);
		if (src2) {
			cat6b->src2 = reg(src2, info, instr->repeat, IR3_REG_IMMED);
			cat6b->src2_im = !!(src2->flags & IR3_REG_IMMED);
		}
	}

	cat6->type     = instr->cat6.type;
	cat6->opc      = instr->opc;
	cat6->jmp_tgt  = !!(instr->flags & IR3_INSTR_JP);
	cat6->sync     = !!(instr->flags & IR3_INSTR_SY);
	cat6->opc_cat  = 6;

	return 0;
}

static int (*emit[])(struct ir3_instruction *instr, void *ptr,
		struct ir3_info *info) = {
	emit_cat0, emit_cat1, emit_cat2, emit_cat3, emit_cat4, emit_cat5, emit_cat6,
};

struct assemble_ctx {
	struct ir3_info *info;
	uint32_t *dwords;
};

static bool
assemble_block_cb(struct ir3_block *block, void *state)
{
	struct assemble_ctx *ctx = state;

	list_for_each_entry (struct ir3_instruction, instr, &block->instr_list, node) {
		int ret = emit[instr->category](instr, ctx->dwords, ctx->info);
		if (ret)
			return false;
		ctx->info->instrs_count += 1 + instr->repeat;
		ctx->dwords += 2;
	}

	return true;
}

/* This is slightly annoying, since we need to know number of
 * actual instructions before the main assemble pass.  We should
 * probably try to make sched or one of the other passes give us
 * this info.
 */
static bool
count_block_cb(struct ir3_block *block, void *state)
{
	struct assemble_ctx *ctx = state;

	list_for_each_entry (struct ir3_instruction, instr, &block->instr_list, node) {
		ctx->info->sizedwords += 2;
	}

	return true;
}

void * ir3_assemble(struct ir3 *shader, struct ir3_info *info,
		uint32_t gpu_id)
{
	struct assemble_ctx ctx = {
		.info = info,
	};
	uint32_t *ptr;

	info->max_reg       = -1;
	info->max_half_reg  = -1;
	info->max_const     = -1;
	info->instrs_count  = 0;

	ir3_foreach_block(shader, count_block_cb, &ctx);

	/* need a integer number of instruction "groups" (sets of 16
	 * instructions on a4xx or sets of 4 instructions on a3xx),
	 * so pad out w/ NOPs if needed: (NOTE each instruction is 64bits)
	 */
	if (gpu_id >= 400) {
		info->sizedwords = align(info->sizedwords, 16 * 2);
	} else {
		info->sizedwords = align(info->sizedwords, 4 * 2);
	}

	ptr = ctx.dwords = calloc(4, info->sizedwords);

	if (! ir3_foreach_block(shader, assemble_block_cb, &ctx))
		goto fail;

	return ptr;

fail:
	free(ptr);
	return NULL;
}

static struct ir3_register * reg_create(struct ir3 *shader,
		int num, int flags)
{
	struct ir3_register *reg =
			ir3_alloc(shader, sizeof(struct ir3_register));
	reg->wrmask = 1;
	reg->flags = flags;
	reg->num = num;
	return reg;
}

static void insert_instr(struct ir3_block *block,
		struct ir3_instruction *instr)
{
	struct ir3 *shader = block->base.shader;
#ifdef DEBUG
	static uint32_t serialno = 0;
	instr->serialno = ++serialno;
#endif
	list_addtail(&instr->node, &block->instr_list);

	if (is_input(instr))
		array_insert(shader->baryfs, instr);
}

static void cf_init(struct ir3_cf *cf, struct ir3 *shader,
		unsigned type)
{
#ifdef DEBUG
	static uint32_t serialno = 0;
	cf->serialno = ++serialno;
#endif
	cf->type = type;
	cf->shader = shader;
	list_inithead(&cf->node);
}

struct ir3_block * ir3_block_create(struct ir3 *shader)
{
	struct ir3_block *block = ir3_alloc(shader, sizeof(*block));
	cf_init(&block->base, shader, IR3_CF_BLOCK);
	list_inithead(&block->instr_list);
	return block;
}

struct ir3_conditional *ir3_cond_create(struct ir3 *shader,
		struct ir3_instruction *condition)
{
	struct ir3_conditional *cond = ir3_alloc(shader, sizeof(*cond));
	cf_init(&cond->base, shader, IR3_CF_COND);
	cond->condition = condition;
	list_inithead(&cond->then_list);
	list_inithead(&cond->else_list);
	return cond;
}

struct ir3_loop *ir3_loop_create(struct ir3 *shader)
{
	struct ir3_loop *loop = ir3_alloc(shader, sizeof(*loop));
	cf_init(&loop->base, shader, IR3_CF_LOOP);
	list_inithead(&loop->body_list);
	return loop;
}

static struct ir3_instruction *instr_create(struct ir3_block *block, int nreg)
{
	struct ir3_instruction *instr;
	unsigned sz = sizeof(*instr) + (nreg * sizeof(instr->regs[0]));
	char *ptr = ir3_alloc(block->base.shader, sz);

	instr = (struct ir3_instruction *)ptr;
	ptr  += sizeof(*instr);
	instr->regs = (struct ir3_register **)ptr;

#ifdef DEBUG
	instr->regs_max = nreg;
#endif

	return instr;
}

struct ir3_instruction * ir3_instr_create2(struct ir3_block *block,
		int category, opc_t opc, int nreg)
{
	struct ir3_instruction *instr = instr_create(block, nreg);
	instr->block = block;
	instr->category = category;
	instr->opc = opc;
	insert_instr(block, instr);
	return instr;
}

struct ir3_instruction * ir3_instr_create(struct ir3_block *block,
		int category, opc_t opc)
{
	/* NOTE: we could be slightly more clever, at least for non-meta,
	 * and choose # of regs based on category.
	 */
	return ir3_instr_create2(block, category, opc, 4);
}

/* only used by old compiler: */
struct ir3_instruction * ir3_instr_clone(struct ir3_instruction *instr)
{
	struct ir3_instruction *new_instr = instr_create(instr->block,
			instr->regs_count);
	struct ir3_register **regs;
	unsigned i;

	regs = new_instr->regs;
	*new_instr = *instr;
	new_instr->regs = regs;

	insert_instr(instr->block, new_instr);

	/* clone registers: */
	new_instr->regs_count = 0;
	for (i = 0; i < instr->regs_count; i++) {
		struct ir3_register *reg = instr->regs[i];
		struct ir3_register *new_reg =
				ir3_reg_create(new_instr, reg->num, reg->flags);
		*new_reg = *reg;
	}

	return new_instr;
}

struct ir3_register * ir3_reg_create(struct ir3_instruction *instr,
		int num, int flags)
{
	struct ir3 *shader = instr->block->base.shader;
	struct ir3_register *reg = reg_create(shader, num, flags);
#ifdef DEBUG
	debug_assert(instr->regs_count < instr->regs_max);
#endif
	instr->regs[instr->regs_count++] = reg;
	return reg;
}

static bool foreach_cf_list(struct list_head *cf_list, ir3_foreach_cf_cb cb, void *state);

static bool
foreach_cond(struct ir3_conditional *cond, ir3_foreach_cf_cb cb, void *state)
{
	return cb(&cond->base, state) &&
			foreach_cf_list(&cond->then_list, cb, state) &&
			foreach_cf_list(&cond->else_list, cb, state);
}

static bool
foreach_loop(struct ir3_loop *loop, ir3_foreach_cf_cb cb, void *state)
{
	return cb(&loop->base, state) &&
			foreach_cf_list(&loop->body_list, cb, state);
}

static bool
foreach_cf_node(struct ir3_cf *cf, ir3_foreach_cf_cb cb, void *state)
{
	switch (cf->type) {
	case IR3_CF_BLOCK: return cb(cf, state);
	case IR3_CF_COND:  return foreach_cond(ir3_conditional(cf), cb, state);
	case IR3_CF_LOOP:  return foreach_loop(ir3_loop(cf), cb, state);
	default:
		unreachable("invalid CF node type");
		return false;
	}
}

static bool
foreach_cf_list(struct list_head *cf_list, ir3_foreach_cf_cb cb, void *state)
{
	list_for_each_entry (struct ir3_cf, cf, cf_list, node)
		if (!foreach_cf_node(cf, cb, state))
			return false;
	return true;
}

bool ir3_foreach_cf(struct ir3 *shader, ir3_foreach_cf_cb cb, void *state)
{
	return foreach_cf_list(&shader->cf_list, cb, state);
}

struct foreach_block_state {
	void *state;
	ir3_foreach_block_cb *cb;
};

static bool foreach_block_cf_cb(struct ir3_cf *cf, void *state)
{
	struct foreach_block_state *cbstate = state;
	if (cf->type == IR3_CF_BLOCK)
		return cbstate->cb(ir3_block(cf), cbstate->state);
	return true;
}

bool
ir3_foreach_block(struct ir3 *shader, ir3_foreach_block_cb cb, void *state)
{
	struct foreach_block_state cbstate = {
		.state = state,
		.cb = cb,
	};
	return ir3_foreach_cf(shader, foreach_block_cf_cb, &cbstate);
}

void ir3_block_clear_mark(struct ir3_block *block)
{
	list_for_each_entry (struct ir3_instruction, instr, &block->instr_list, node)
		instr->flags &= ~IR3_INSTR_MARK;
}

static bool
clear_mark_cb(struct ir3_block *block, void *state)
{
	ir3_block_clear_mark(block);
	return true;
}

void ir3_clear_mark(struct ir3 *shader)
{
	ir3_foreach_block(shader, clear_mark_cb, NULL);
}
