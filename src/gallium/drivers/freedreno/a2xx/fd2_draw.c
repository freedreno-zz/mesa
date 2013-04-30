/* -*- mode: C; c-file-style: "k&r"; tab-width 4; indent-tabs-mode: t; -*- */

/*
 * Copyright (C) 2012-2013 Rob Clark <robclark@freedesktop.org>
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
#include "util/u_prim.h"

#include "freedreno_context.h"
#include "freedreno_state.h"
#include "freedreno_resource.h"
#include "freedreno_util.h"
#include "fd2_draw.h"
#include "fd2_emit.h"
#include "fd2_zsa.h"


static void
emit_cacheflush(struct fd_ringbuffer *ring)
{
	unsigned i;

	for (i = 0; i < 12; i++) {
		OUT_PKT3(ring, CP_EVENT_WRITE, 1);
		OUT_RING(ring, CACHE_FLUSH);
	}
}

static void
emit_vertexbufs(struct fd_context *ctx)
{
	struct fd_vertex_stateobj *vtx = ctx->vtx;
	struct fd_vertexbuf_stateobj *vertexbuf = &ctx->vertexbuf;
	struct fd2_vertex_buf bufs[PIPE_MAX_ATTRIBS];
	unsigned i;

	if (!vtx->num_elements)
		return;

	for (i = 0; i < vtx->num_elements; i++) {
		struct pipe_vertex_element *elem = &vtx->pipe[i];
		struct pipe_vertex_buffer *vb =
				&vertexbuf->vb[elem->vertex_buffer_index];
		bufs[i].offset = vb->buffer_offset;
		bufs[i].size = fd_bo_size(fd_resource(vb->buffer)->bo);
		bufs[i].prsc = vb->buffer;
	}

	// NOTE I believe the 0x78 (or 0x9c in solid_vp) relates to the
	// CONST(20,0) (or CONST(26,0) in soliv_vp)

	fd2_emit_vertex_bufs(ctx->ring, 0x78, bufs, vtx->num_elements);
}

static void
fd2_draw(struct fd_context *ctx, const struct pipe_draw_info *info)
{
	struct fd_ringbuffer *ring = ctx->ring;

	if (ctx->dirty & FD_DIRTY_VTXBUF)
		emit_vertexbufs(ctx);

	fd2_emit_state(ctx, ctx->dirty);

	OUT_PKT3(ring, CP_SET_CONSTANT, 2);
	OUT_RING(ring, CP_REG(REG_A2XX_VGT_INDX_OFFSET));
	OUT_RING(ring, info->start);

	OUT_PKT3(ring, CP_SET_CONSTANT, 2);
	OUT_RING(ring, CP_REG(REG_A2XX_VGT_VERTEX_REUSE_BLOCK_CNTL));
	OUT_RING(ring, 0x0000003b);

	OUT_PKT0(ring, REG_A2XX_TC_CNTL_STATUS, 1);
	OUT_RING(ring, A2XX_TC_CNTL_STATUS_L2_INVALIDATE);

	OUT_PKT3(ring, CP_WAIT_FOR_IDLE, 1);
	OUT_RING(ring, 0x0000000);

	OUT_PKT3(ring, CP_SET_CONSTANT, 3);
	OUT_RING(ring, CP_REG(REG_A2XX_VGT_MAX_VTX_INDX));
	OUT_RING(ring, info->max_index);        /* VGT_MAX_VTX_INDX */
	OUT_RING(ring, info->min_index);        /* VGT_MIN_VTX_INDX */

	fd_draw_emit(info, &ctx->indexbuf, ring);

	OUT_PKT3(ring, CP_SET_CONSTANT, 2);
	OUT_RING(ring, CP_REG(REG_A2XX_UNKNOWN_2010));
	OUT_RING(ring, 0x00000000);

	emit_cacheflush(ring);
}

void
fd2_draw_init(struct pipe_context *pctx)
{
	struct fd_context *ctx = fd_context(pctx);
	ctx->draw = fd2_draw;
}
