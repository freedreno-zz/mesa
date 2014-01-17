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

#ifndef IR3_DCE_H_
#define IR3_DCE_H_

#include "ir3.h"

/*
 * Copy Propagate:
 */

static struct ir3_instruction *
ir3_instr_cp(struct ir3_instruction *instr, uint32_t mark)
{
	unsigned i;

	/* NOTE this might remove some necessary copies, for example
	 * replicating a result to an output register or texture
	 * sample src (ie. basically anywhere you have a requirement
	 * for consecutive registers).  Probably this is easiest to
	 * just fix up in the instruction scheduling and register
	 * assignment
	 */

	if ((instr->category == 1) &&
			(instr->cat1.src_type == instr->cat1.dst_type)) {
		struct ir3_register *src = instr->regs[1];
		if ((src->flags & IR3_REG_SSA) &&
			/* TODO: propagate abs/neg modifiers if possible */
			!(src->flags & (IR3_REG_ABS | IR3_REG_NEGATE)))
			return ir3_instr_cp(src->instr, mark);
	}

	/* if we've already visited this instruction, bail now: */
	if (ir3_instr_check_mark(instr, mark))
		return instr;

	/* walk down the graph from each src: */
	for (i = 1; i < instr->regs_count; i++) {
		struct ir3_register *src = instr->regs[i];
		if (src->flags & IR3_REG_SSA)
			src->instr = ir3_instr_cp(src->instr, mark);
	}

	return instr;
}

static void ir3_block_cp(struct ir3_block *block)
{
	uint32_t mark = ir3_block_get_mark(block);
	unsigned i;

	for (i = 0; i < block->noutputs; i++)
		if (block->outputs[i])
			block->outputs[i] = ir3_instr_cp(block->outputs[i], mark);
}

#endif /* IR3_DCE_H_ */
