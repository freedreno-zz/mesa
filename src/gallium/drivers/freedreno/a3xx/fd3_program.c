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

void
fd3_prog_init(struct pipe_context *pctx)
{
	pctx->create_fs_state = fd_fp_state_create;
	pctx->bind_fs_state = fd_fp_state_bind;
	pctx->delete_fs_state = fd_fp_state_delete;

	pctx->create_vs_state = fd_vp_state_create;
	pctx->bind_vs_state = fd_vp_state_bind;
	pctx->delete_vs_state = fd_vp_state_delete;
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
