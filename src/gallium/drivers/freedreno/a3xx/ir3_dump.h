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

#ifndef IR3_DUMP_H_
#define IR3_DUMP_H_

#include "ir3.h"

#define PTRID(x) ((uint64_t)(unsigned long)(x))

static void dump_instr_name(struct ir3_instruction *instr)
{
	if (instr->category == 1) {
		static const char *type[] = {
				[TYPE_F16] = "f16",
				[TYPE_F32] = "f32",
				[TYPE_U16] = "u16",
				[TYPE_U32] = "u32",
				[TYPE_S16] = "s16",
				[TYPE_S32] = "s32",
				[TYPE_U8]  = "u8",
				[TYPE_S8]  = "s8",
		};
		if (instr->cat1.src_type == instr->cat1.dst_type)
			printf("mov");
		else
			printf("cov");
		printf(".%s%s", type[instr->cat1.src_type], type[instr->cat1.dst_type]);
	} else {
		printf("%s", ir3_instr_name(instr));
		if (instr->flags & IR3_INSTR_3D)
			printf(".3d");
		if (instr->flags & IR3_INSTR_A)
			printf(".a");
		if (instr->flags & IR3_INSTR_O)
			printf(".o");
		if (instr->flags & IR3_INSTR_P)
			printf(".p");
		if (instr->flags & IR3_INSTR_S)
			printf(".s");
		if (instr->flags & IR3_INSTR_S2EN)
			printf(".s2en");
	}
}

static void dump_reg_name(struct ir3_register *reg)
{
	if ((reg->flags & IR3_REG_ABS) && (reg->flags & IR3_REG_NEGATE))
		printf("(absneg)");
	else if (reg->flags & IR3_REG_NEGATE)
		printf("(neg)");
	else if (reg->flags & IR3_REG_ABS)
		printf("(abs)");

	if (reg->flags & IR3_REG_IMMED) {
		printf("imm[%f,%d,0x%x]", reg->fim_val, reg->iim_val, reg->iim_val);
	} else if (!(reg->flags & IR3_REG_SSA)){
		if (reg->flags & IR3_REG_HALF)
			printf("h");
		if (reg->flags & IR3_REG_CONST)
			printf("c%u.%c", reg_num(reg), "xyzw"[reg_comp(reg)]);
		else
			printf("r%u.%c", reg_num(reg), "xyzw"[reg_comp(reg)]);
	}
}

static void ir3_instr_dump(struct ir3_instruction *instr, uint32_t mark,
		struct ir3_block *block /* XXX instr should have ptr back to enclosing blk probably! */);

static void dump_instr(struct ir3_instruction *instr, uint32_t mark,
		struct ir3_block *block /* XXX instr should have ptr back to enclosing blk probably! */)
{
if (!instr) { printf("error [label=\"XXX %d\"];\n", __LINE__); return; }// ??? XXX

	/* some meta-instructions need to be handled specially: */
	if (instr->category == -1) {
		if (instr->opc == OPC_META_FO) {
			struct ir3_register *reg = instr->regs[1];
			dump_instr(reg->instr, mark, block);
		} else if (instr->opc == OPC_META_FI) {
			unsigned i;
			for (i = 1; i < instr->regs_count; i++) {
				struct ir3_register *reg = instr->regs[i];
				if (reg->flags & IR3_REG_SSA)
					dump_instr(reg->instr, mark, block);
			}
		}
	} else {
		ir3_instr_dump(instr, mark, block);
	}
}

static void dump_link(struct ir3_instruction *instr,
		struct ir3_block *block, const char *target)
{
	/* some meta-instructions need to be handled specially: */
	if (instr->category == -1) {
		if (instr->opc == OPC_META_INPUT) {
			printf("input%lx:<in%u>:w -> %s\n", PTRID(block),
					instr->regs[0]->num, target);
		} else if (instr->opc == OPC_META_FO) {
			struct ir3_register *reg = instr->regs[1];
			dump_link(reg->instr, block, target);
			printf("[label=\".%c\"]\n", "xyzw"[instr->meta.off & 0x3]);
		} else if (instr->opc == OPC_META_FI) {
			unsigned i;

			/* recursively dump all parents and links */
			for (i = 1; i < instr->regs_count; i++) {
				struct ir3_register *reg = instr->regs[i];
				if (reg->flags & IR3_REG_SSA) {
					dump_link(reg->instr, block, target);
					printf("[label=\".%c\"]\n", "xyzw"[(i - 1) & 0x3]);
				}
			}
		}
	} else {
		printf("instr%lx:<dst0> -> %s\n", PTRID(instr), target);
	}
}

static void ir3_instr_dump(struct ir3_instruction *instr, uint32_t mark,
		struct ir3_block *block /* XXX instr should have ptr back to enclosing blk probably! */)
{
	unsigned i;

	/* if we've already visited this instruction, bail now: */
	if (ir3_instr_check_mark(instr, mark))
		return;

	printf("instr%lx [shape=record,style=filled,fillcolor=lightgrey,label=\"{",
			PTRID(instr));
	dump_instr_name(instr);

	/* destination register: */
	printf("|<dst0>");

	/* source register(s): */
	for (i = 1; i < instr->regs_count; i++) {
		struct ir3_register *reg = instr->regs[i];

		printf("|");

		if (reg->flags & IR3_REG_SSA)
			printf("<src%u> ", (i - 1));

		dump_reg_name(reg);
	}

	printf("}\"];\n");

	/* and recursively dump dependent instructions: */
	for (i = 1; i < instr->regs_count; i++) {
		struct ir3_register *reg = instr->regs[i];
		char target[32];  /* link target */

		if (!(reg->flags & IR3_REG_SSA))
			continue;

		snprintf(target, sizeof(target), "instr%lx:<src%u>",
				PTRID(instr), (i - 1));

		dump_instr(reg->instr, mark, block);
		dump_link(reg->instr, block, target);
	}
}

static void ir3_block_dump(struct ir3_block *block)
{
	uint32_t mark = ir3_block_get_mark(block);
	unsigned i;

	printf("subgraph block%lx {\n", PTRID(block));

	/* draw inputs: */
	printf("input%lx [shape=record,label=\"inputs", PTRID(block));
	for (i = 0; i < block->ninputs; i++)
		printf("|<in%u> i%u.%c", i, (i >> 2), "xyzw"[i & 0x3]);
	printf("\"];\n");

	/* draw instruction graph: */
	for (i = 0; i < block->noutputs; i++)
		dump_instr(block->outputs[i], mark, block);

	/* draw outputs: */
	printf("output%lx [shape=record,label=\"outputs", PTRID(block));
	for (i = 0; i < block->noutputs; i++)
		printf("|<out%u> o%u.%c", i, (i >> 2), "xyzw"[i & 0x3]);
	printf("\"];\n");

	/* and links to outputs: */
	for (i = 0; i < block->noutputs; i++) {
		char target[32];  /* link target */

		snprintf(target, sizeof(target), "output%lx:<out%u>",
				PTRID(block), i);

		/* NOTE: there could be outputs that are never assigned,
		 * so skip them
		 */
		if (!block->outputs[i])
			continue;

		dump_link(block->outputs[i], block, target);
	}

	printf("}\n");
}

static void ir3_shader_dump(struct ir3_shader *shader,
		struct ir3_block *block /* XXX maybe 'block' ptr should move to ir3_shader? */)
{
	printf("digraph G {\n");
	printf("rankdir=RL;\n");
	printf("nodesep=0.25;\n");
	printf("ranksep=1.5;\n");
	ir3_block_dump(block);
	printf("}\n");
}

#endif /* IR3_DUMP_H_ */
