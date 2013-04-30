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

#include "freedreno_state.h"
#include "freedreno_resource.h"

#include "fd3_gmem.h"
#include "fd3_context.h"
#include "fd3_emit.h"
#include "fd3_program.h"
#include "fd3_util.h"
#include "fd3_zsa.h"

/* transfer from gmem to system memory (ie. normal RAM) */

static void
fd3_emit_tile_gmem2mem(struct fd_context *ctx, uint32_t xoff, uint32_t yoff,
		uint32_t bin_w, uint32_t bin_h)
{
}

/* transfer from system memory to gmem */

static void
fd3_emit_tile_mem2gmem(struct fd_context *ctx, uint32_t xoff, uint32_t yoff,
		uint32_t bin_w, uint32_t bin_h)
{
}

/* before mem2gmem */
static void
fd3_emit_tile_prep(struct fd_context *ctx, uint32_t xoff, uint32_t yoff,
		uint32_t bin_w, uint32_t bin_h)
{
}

/* before IB to rendering cmds: */
static void
fd3_emit_tile_renderprep(struct fd_context *ctx, uint32_t xoff, uint32_t yoff,
		uint32_t bin_w, uint32_t bin_h)
{
}

void
fd3_gmem_init(struct pipe_context *pctx)
{
	struct fd_context *ctx = fd_context(pctx);

	ctx->emit_tile_prep = fd3_emit_tile_prep;
	ctx->emit_tile_mem2gmem = fd3_emit_tile_mem2gmem;
	ctx->emit_tile_renderprep = fd3_emit_tile_renderprep;
	ctx->emit_tile_gmem2mem = fd3_emit_tile_gmem2mem;
}
