/* -*- mode: C; c-file-style: "k&r"; tab-width 4; indent-tabs-mode: t; -*- */

/*
 * Copyright (C) 2012 Rob Clark <robclark@freedesktop.org>
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

#include "pipe/p_state.h"
#include "util/u_string.h"
#include "util/u_memory.h"
#include "util/u_inlines.h"
#include "util/u_format.h"
#include "tgsi/tgsi_dump.h"
#include "tgsi/tgsi_parse.h"

#include "fd3_program.h"
#include "fd3_compiler.h"
#include "fd3_texture.h"
#include "fd3_util.h"

static void
delete_shader(struct fd3_shader_stateobj *so)
{
	ir3_shader_destroy(so->ir);
	free(so->bin);
	free(so);
}

static struct fd3_shader_stateobj *
create_shader(enum shader_t type, const struct pipe_shader_state *cso)
{
	struct fd3_shader_stateobj *so = CALLOC_STRUCT(fd3_shader_stateobj);
	int ret;

	if (!so)
		return NULL;

	so->type = type;

	if (fd_mesa_debug & FD_DBG_DISASM) {
		DBG("dump tgsi: type=%d", so->type);
		tgsi_dump(cso->tokens, 0);
	}

	ret = fd3_compile_shader(so, cso->tokens);
	if (ret) {
		debug_error("compile failed!");
		goto fail;
	}

	so->bin = ir3_shader_assemble(so->ir, &so->info);
	if (!so->bin) {
		debug_error("assemble failed!");
		goto fail;
	}

	if (fd_mesa_debug & FD_DBG_DISASM) {
		DBG("disassemble: type=%d", so->type);
		disasm_a3xx(so->bin, so->info.sizedwords, 0, so->type);
	}

	return so;

fail:
	delete_shader(so);
	return NULL;
}

static void *
fd_fp_state_create(struct pipe_context *pctx,
		const struct pipe_shader_state *cso)
{
	struct fd3_shader_stateobj *so = create_shader(SHADER_FRAGMENT, cso);
	if (!so)
		return NULL;
	return so;
}

static void
fd_fp_state_delete(struct pipe_context *pctx, void *hwcso)
{
	struct fd3_shader_stateobj *so = hwcso;
	delete_shader(so);
}

static void
fd_fp_state_bind(struct pipe_context *pctx, void *hwcso)
{
	struct fd_context *ctx = fd_context(pctx);
	ctx->prog.fp = hwcso;
	ctx->prog.dirty |= FD_SHADER_DIRTY_FP;
	ctx->dirty |= FD_DIRTY_PROG;
}

static void *
fd_vp_state_create(struct pipe_context *pctx,
		const struct pipe_shader_state *cso)
{
	struct fd3_shader_stateobj *so = create_shader(SHADER_VERTEX, cso);
	if (!so)
		return NULL;
	return so;
}

static void
fd_vp_state_delete(struct pipe_context *pctx, void *hwcso)
{
	struct fd3_shader_stateobj *so = hwcso;
	delete_shader(so);
}

static void
fd_vp_state_bind(struct pipe_context *pctx, void *hwcso)
{
	struct fd_context *ctx = fd_context(pctx);
	ctx->prog.vp = hwcso;
	ctx->prog.dirty |= FD_SHADER_DIRTY_VP;
	ctx->dirty |= FD_DIRTY_PROG;
}

void
fd3_program_emit(struct fd_ringbuffer *ring,
		struct fd_program_stateobj *prog)
{
/*
	struct ir3_shader_info *vsi =
		&((struct fd3_shader_stateobj *)prog->vp)->info;
	struct ir3_shader_info *fsi =
		&((struct fd3_shader_stateobj *)prog->fp)->info;
	uint8_t vs_gprs, fs_gprs, vs_export;

TODO
*/
}

/* Creates shader:
 *    EXEC ADDR(0x2) CNT(0x1)
 *       (S)FETCH:	SAMPLE	R0.xyzw = R0.xyx CONST(0) LOCATION(CENTER)
 *    ALLOC PARAM/PIXEL SIZE(0x0)
 *    EXEC_END ADDR(0x3) CNT(0x1)
 *          ALU:	MAXv	export0 = R0, R0	; gl_FragColor
 *    NOP
 */
static struct fd3_shader_stateobj *
create_blit_fp(void)
{
	struct fd3_shader_stateobj *so = create_shader(SHADER_FRAGMENT);
	struct ir2_cf *cf;
	struct ir2_instruction *instr;

	if (!so)
		return NULL;

	so->ir = ir2_shader_create();

	cf = ir2_cf_create(so->ir, EXEC);

	instr = ir2_instr_create_tex_fetch(cf, 0);
	ir2_reg_create(instr, 0, "xyzw", 0);
	ir2_reg_create(instr, 0, "xyx", 0);
	instr->sync = true;

	cf = ir2_cf_create_alloc(so->ir, SQ_PARAMETER_PIXEL, 0);
	cf = ir2_cf_create(so->ir, EXEC_END);

	instr = ir2_instr_create_alu(cf, MAXv, ~0);
	ir2_reg_create(instr, 0, NULL, IR2_REG_EXPORT);
	ir2_reg_create(instr, 0, NULL, 0);
	ir2_reg_create(instr, 0, NULL, 0);

	return assemble(so);
}

/* Creates shader:
*     EXEC ADDR(0x3) CNT(0x2)
*           FETCH:	VERTEX	R1.xy01 = R0.x FMT_32_32_FLOAT UNSIGNED STRIDE(8) CONST(26, 1)
*           FETCH:	VERTEX	R2.xyz1 = R0.x FMT_32_32_32_FLOAT UNSIGNED STRIDE(12) CONST(26, 0)
*     ALLOC POSITION SIZE(0x0)
*     EXEC ADDR(0x5) CNT(0x1)
*           ALU:	MAXv	export62 = R2, R2	; gl_Position
*     ALLOC PARAM/PIXEL SIZE(0x0)
*     EXEC_END ADDR(0x6) CNT(0x1)
*           ALU:	MAXv	export0 = R1, R1
*     NOP
 */
static struct fd3_shader_stateobj *
create_blit_vp(void)
{
	struct fd3_shader_stateobj *so = create_shader(SHADER_VERTEX);
	struct ir2_cf *cf;
	struct ir2_instruction *instr;

	if (!so)
		return NULL;

	so->ir = ir2_shader_create();

	cf = ir2_cf_create(so->ir, EXEC);

	instr = ir2_instr_create_vtx_fetch(cf, 26, 1, FMT_32_32_FLOAT, false, 8);
	instr->fetch.is_normalized = true;
	ir2_reg_create(instr, 1, "xy01", 0);
	ir2_reg_create(instr, 0, "x", 0);

	instr = ir2_instr_create_vtx_fetch(cf, 26, 0, FMT_32_32_32_FLOAT, false, 12);
	instr->fetch.is_normalized = true;
	ir2_reg_create(instr, 2, "xyz1", 0);
	ir2_reg_create(instr, 0, "x", 0);

	cf = ir2_cf_create_alloc(so->ir, SQ_POSITION, 0);
	cf = ir2_cf_create(so->ir, EXEC);

	instr = ir2_instr_create_alu(cf, MAXv, ~0);
	ir2_reg_create(instr, 62, NULL, IR2_REG_EXPORT);
	ir2_reg_create(instr, 2, NULL, 0);
	ir2_reg_create(instr, 2, NULL, 0);

	cf = ir2_cf_create_alloc(so->ir, SQ_PARAMETER_PIXEL, 0);
	cf = ir2_cf_create(so->ir, EXEC_END);

	instr = ir2_instr_create_alu(cf, MAXv, ~0);
	ir2_reg_create(instr, 0, NULL, IR2_REG_EXPORT);
	ir2_reg_create(instr, 1, NULL, 0);
	ir2_reg_create(instr, 1, NULL, 0);

	return assemble(so);
}

/* Creates shader:
 *    ALLOC PARAM/PIXEL SIZE(0x0)
 *    EXEC_END ADDR(0x1) CNT(0x1)
 *          ALU:	MAXv	export0 = C0, C0	; gl_FragColor
 */
static struct fd3_shader_stateobj *
create_solid_fp(void)
{
	struct fd3_shader_stateobj *so = create_shader(SHADER_FRAGMENT);
	struct ir2_cf *cf;
	struct ir2_instruction *instr;

	if (!so)
		return NULL;

	so->ir = ir2_shader_create();

	cf = ir2_cf_create_alloc(so->ir, SQ_PARAMETER_PIXEL, 0);
	cf = ir2_cf_create(so->ir, EXEC_END);

	instr = ir2_instr_create_alu(cf, MAXv, ~0);
	ir2_reg_create(instr, 0, NULL, IR2_REG_EXPORT);
	ir2_reg_create(instr, 0, NULL, IR2_REG_CONST);
	ir2_reg_create(instr, 0, NULL, IR2_REG_CONST);

	return assemble(so);
}

/* Creates shader:
 *    EXEC ADDR(0x3) CNT(0x1)
 *       (S)FETCH:	VERTEX	R1.xyz1 = R0.x FMT_32_32_32_FLOAT
 *                           UNSIGNED STRIDE(12) CONST(26, 0)
 *    ALLOC POSITION SIZE(0x0)
 *    EXEC ADDR(0x4) CNT(0x1)
 *          ALU:	MAXv	export62 = R1, R1	; gl_Position
 *    ALLOC PARAM/PIXEL SIZE(0x0)
 *    EXEC_END ADDR(0x5) CNT(0x0)
 */
static struct fd3_shader_stateobj *
create_solid_vp(void)
{
	struct fd3_shader_stateobj *so = create_shader(SHADER_VERTEX);
	struct ir2_cf *cf;
	struct ir2_instruction *instr;

	if (!so)
		return NULL;

	so->ir = ir2_shader_create();

	cf = ir2_cf_create(so->ir, EXEC);

	instr = ir2_instr_create_vtx_fetch(cf, 26, 0, FMT_32_32_32_FLOAT, false, 12);
	ir2_reg_create(instr, 1, "xyz1", 0);
	ir2_reg_create(instr, 0, "x", 0);

	cf = ir2_cf_create_alloc(so->ir, SQ_POSITION, 0);
	cf = ir2_cf_create(so->ir, EXEC);

	instr = ir2_instr_create_alu(cf, MAXv, ~0);
	ir2_reg_create(instr, 62, NULL, IR2_REG_EXPORT);
	ir2_reg_create(instr, 1, NULL, 0);
	ir2_reg_create(instr, 1, NULL, 0);

	cf = ir2_cf_create_alloc(so->ir, SQ_PARAMETER_PIXEL, 0);
	cf = ir2_cf_create(so->ir, EXEC_END);

	return assemble(so);
}

void
fd3_prog_init(struct pipe_context *pctx)
{
	struct fd_context *ctx = fd_context(pctx);

	pctx->create_fs_state = fd_fp_state_create;
	pctx->bind_fs_state = fd_fp_state_bind;
	pctx->delete_fs_state = fd_fp_state_delete;

	pctx->create_vs_state = fd_vp_state_create;
	pctx->bind_vs_state = fd_vp_state_bind;
	pctx->delete_vs_state = fd_vp_state_delete;

	ctx->solid_prog.fp = create_solid_fp();
	ctx->solid_prog.vp = create_solid_vp();
	ctx->blit_prog.fp = create_blit_fp();
	ctx->blit_prog.vp = create_blit_vp();
}

void
fd3_prog_fini(struct pipe_context *pctx)
{
	struct fd_context *ctx = fd_context(pctx);

	delete_shader(ctx->solid_prog.vp);
	delete_shader(ctx->solid_prog.fp);
	delete_shader(ctx->blit_prog.vp);
	delete_shader(ctx->blit_prog.fp);
}
