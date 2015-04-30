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

#include "pipe/p_shader_tokens.h"
#include "util/u_math.h"

#include "freedreno_util.h"

#include "ir3.h"

/*
 * Legalize:
 *
 * We currently require that scheduling ensures that we have enough nop's
 * in all the right places.  The legalize step mostly handles fixing up
 * instruction flags ((ss)/(sy)/(ei)), and collapses sequences of nop's
 * into fewer nop's w/ rpt flag.
 */

struct ir3_legalize_ctx {
	struct ir3_block *block;
	bool has_samp;
	int max_bary;
};

static void legalize(struct ir3_legalize_ctx *ctx)
{
	struct ir3_block *block = ctx->block;
	struct ir3_instruction *last_input = NULL;
	struct ir3_instruction *last_rel = NULL;
	struct list_head instr_list;
	regmask_t needs_ss_war;       /* write after read */
	regmask_t needs_ss;
	regmask_t needs_sy;

	regmask_init(&needs_ss_war);
	regmask_init(&needs_ss);
	regmask_init(&needs_sy);

	/* remove all the instructions from the list, we'll be adding
	 * them back in as we go
	 */
	list_replace(&block->instr_list, &instr_list);
	list_inithead(&block->instr_list);

	list_for_each_entry_safe (struct ir3_instruction, n, &instr_list, node) {
		struct ir3_register *reg;
		unsigned i;

		if (is_meta(n))
			continue;

		if (is_input(n)) {
			struct ir3_register *inloc = n->regs[1];
			assert(inloc->flags & IR3_REG_IMMED);
			ctx->max_bary = MAX2(ctx->max_bary, inloc->iim_val);
		}

		/* NOTE: consider dst register too.. it could happen that
		 * texture sample instruction (for example) writes some
		 * components which are unused.  A subsequent instruction
		 * that writes the same register can race w/ the sam instr
		 * resulting in undefined results:
		 */
		for (i = 0; i < n->regs_count; i++) {
			reg = n->regs[i];

			if (reg_gpr(reg)) {

				/* TODO: we probably only need (ss) for alu
				 * instr consuming sfu result.. need to make
				 * some tests for both this and (sy)..
				 */
				if (regmask_get(&needs_ss, reg)) {
					n->flags |= IR3_INSTR_SS;
					regmask_init(&needs_ss);
				}

				if (regmask_get(&needs_sy, reg)) {
					n->flags |= IR3_INSTR_SY;
					regmask_init(&needs_sy);
				}
			}

			/* TODO: is it valid to have address reg loaded from a
			 * relative src (ie. mova a0, c<a0.x+4>)?  If so, the
			 * last_rel check below should be moved ahead of this:
			 */
			if (reg->flags & IR3_REG_RELATIV)
				last_rel = n;
		}

		if (n->regs_count > 0) {
			reg = n->regs[0];
			if (regmask_get(&needs_ss_war, reg)) {
				n->flags |= IR3_INSTR_SS;
				regmask_init(&needs_ss_war); // ??? I assume?
			}

			if (last_rel && (reg->num == regid(REG_A0, 0))) {
				last_rel->flags |= IR3_INSTR_UL;
				last_rel = NULL;
			}
		}

		/* cat5+ does not have an (ss) bit, if needed we need to
		 * insert a nop to carry the sync flag.  Would be kinda
		 * clever if we were aware of this during scheduling, but
		 * this should be a pretty rare case:
		 */
		if ((n->flags & IR3_INSTR_SS) && (n->category >= 5)) {
			struct ir3_instruction *nop;
			nop = ir3_NOP(block);
			nop->flags |= IR3_INSTR_SS;
			n->flags &= ~IR3_INSTR_SS;
		}

		/* need to be able to set (ss) on first instruction: */
		if (list_empty(&block->instr_list) && (n->category >= 5))
			ir3_NOP(block);

		if (is_nop(n) && !list_empty(&block->instr_list)) {
			struct ir3_instruction *last = list_last_entry(&block->instr_list,
					struct ir3_instruction, node);
			if (is_nop(last) && (last->repeat < 5)) {
				last->repeat++;
				last->flags |= n->flags;
				continue;
			}
		}

		list_addtail(&n->node, &block->instr_list);

		if (is_sfu(n))
			regmask_set(&needs_ss, n->regs[0]);

		if (is_tex(n)) {
			/* this ends up being the # of samp instructions.. but that
			 * is ok, everything else only cares whether it is zero or
			 * not.  We do this here, rather than when we encounter a
			 * SAMP decl, because (especially in binning pass shader)
			 * the samp instruction(s) could get eliminated if the
			 * result is not used.
			 */
			ctx->has_samp = true;
			regmask_set(&needs_sy, n->regs[0]);
		} else if (is_mem(n)) {
			regmask_set(&needs_sy, n->regs[0]);
		}

		/* both tex/sfu appear to not always immediately consume
		 * their src register(s):
		 */
		if (is_tex(n) || is_sfu(n) || is_mem(n)) {
			foreach_src(reg, n) {
				if (reg_gpr(reg))
					regmask_set(&needs_ss_war, reg);
			}
		}

		if (is_input(n))
			last_input = n;
	}

	if (last_input) {
		/* special hack.. if using ldlv to bypass interpolation,
		 * we need to insert a dummy bary.f on which we can set
		 * the (ei) flag:
		 */
		if (is_mem(last_input) && (last_input->opc == OPC_LDLV)) {
			struct ir3_instruction *baryf;

			/* (ss)bary.f (ei)r63.x, 0, r0.x */
			baryf = ir3_instr_create(block, 2, OPC_BARY_F);
			baryf->flags |= IR3_INSTR_SS;
			ir3_reg_create(baryf, regid(63, 0), 0);
			ir3_reg_create(baryf, 0, IR3_REG_IMMED)->iim_val = 0;
			ir3_reg_create(baryf, regid(0, 0), 0);

			/* insert the dummy bary.f after last_input: */
			list_add(&baryf->node, &last_input->node);

			last_input = baryf;
		}
		last_input->regs[0]->flags |= IR3_REG_EI;
	}

	if (last_rel)
		last_rel->flags |= IR3_INSTR_UL;

	/* create/add 'end' instruction: */
	ir3_instr_create(block, 0, OPC_END);

	list_first_entry(&block->instr_list, struct ir3_instruction, node)
		->flags |= IR3_INSTR_SS | IR3_INSTR_SY;
}

void ir3_block_legalize(struct ir3_block *block,
		bool *has_samp, int *max_bary)
{
	struct ir3_legalize_ctx ctx = {
			.block = block,
			.max_bary = -1,
	};

	legalize(&ctx);

	*has_samp = ctx.has_samp;
	*max_bary = ctx.max_bary;
}
