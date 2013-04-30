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


#include "fd2_context.h"
#include "fd2_blend.h"
#include "fd2_clear.h"
#include "fd2_draw.h"
#include "fd2_emit.h"
#include "fd2_gmem.h"
#include "fd2_program.h"
#include "fd2_rasterizer.h"
#include "fd2_texture.h"
#include "fd2_zsa.h"

static void
fd2_context_destroy(struct pipe_context *pctx)
{
	fd2_prog_fini(pctx);
	fd_context_destroy(pctx);
}

struct pipe_context *
fd2_context_create(struct pipe_screen *pscreen, void *priv)
{
	struct fd2_context *fd2_ctx = CALLOC_STRUCT(fd2_context);
	struct pipe_context *pctx;

	if (!fd2_ctx)
		return NULL;

	pctx = &fd2_ctx->base.base;

	pctx->destroy = fd2_context_destroy;
	pctx->create_blend_state = fd2_blend_state_create;
	pctx->create_rasterizer_state = fd2_rasterizer_state_create;
	pctx->create_depth_stencil_alpha_state = fd2_zsa_state_create;

	fd2_clear_init(pctx);
	fd2_draw_init(pctx);
	fd2_gmem_init(pctx);
	fd2_texture_init(pctx);
	fd2_prog_init(pctx);

	pctx = fd_context_init(&fd2_ctx->base, pscreen, priv);
	if (!pctx)
		return NULL;

	fd2_emit_setup(&fd2_ctx->base);

	return pctx;
}
