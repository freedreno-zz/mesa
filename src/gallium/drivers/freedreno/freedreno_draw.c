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
#include "util/u_prim.h"

#include "freedreno_draw.h"
#include "freedreno_context.h"
#include "freedreno_state.h"
#include "freedreno_resource.h"
#include "freedreno_util.h"


static enum pc_di_primtype
mode2primtype(unsigned mode)
{
	switch (mode) {
	case PIPE_PRIM_POINTS:         return DI_PT_POINTLIST;
	case PIPE_PRIM_LINES:          return DI_PT_LINELIST;
	case PIPE_PRIM_LINE_STRIP:     return DI_PT_LINESTRIP;
	case PIPE_PRIM_TRIANGLES:      return DI_PT_TRILIST;
	case PIPE_PRIM_TRIANGLE_STRIP: return DI_PT_TRISTRIP;
	case PIPE_PRIM_TRIANGLE_FAN:   return DI_PT_TRIFAN;
	case PIPE_PRIM_QUADS:          return DI_PT_QUADLIST;
	case PIPE_PRIM_QUAD_STRIP:     return DI_PT_QUADSTRIP;
	case PIPE_PRIM_POLYGON:        return DI_PT_POLYGON;
	}
	DBG("unsupported mode: (%s) %d", u_prim_name(mode), mode);
	assert(0);
	return DI_PT_NONE;
}

static enum pc_di_index_size
size2indextype(unsigned index_size)
{
	switch (index_size) {
	case 1: return INDEX_SIZE_8_BIT;
	case 2: return INDEX_SIZE_16_BIT;
	case 4: return INDEX_SIZE_32_BIT;
	}
	DBG("unsupported index size: %d", index_size);
	assert(0);
	return INDEX_SIZE_IGN;
}

/* this is same for a2xx/a3xx, so split into helper: */
void
fd_draw_emit(const struct pipe_draw_info *info, struct pipe_index_buffer *idx,
		struct fd_ringbuffer *ring)
{
	struct fd_bo *idx_bo = NULL;
	enum pc_di_index_size idx_type = INDEX_SIZE_IGN;
	enum pc_di_src_sel src_sel;
	uint32_t idx_size, idx_offset;

	if (info->indexed) {
		assert(!idx->user_buffer);

		idx_bo = fd_resource(idx->buffer)->bo;
		idx_type = size2indextype(idx->index_size);
		idx_size = idx->index_size * info->count;
		idx_offset = idx->offset;
		src_sel = DI_SRC_SEL_DMA;
	} else {
		idx_bo = NULL;
		idx_type = INDEX_SIZE_IGN;
		idx_size = 0;
		idx_offset = 0;
		src_sel = DI_SRC_SEL_AUTO_INDEX;
	}

	OUT_PKT3(ring, CP_DRAW_INDX, info->indexed ? 5 : 3);
	OUT_RING(ring, 0x00000000);        /* viz query info. */
	OUT_RING(ring, DRAW(mode2primtype(info->mode),
			src_sel, idx_type, IGNORE_VISIBILITY));
	OUT_RING(ring, info->count);       /* NumIndices */
	if (info->indexed) {
		OUT_RELOC(ring, idx_bo, idx_offset, 0);
		OUT_RING (ring, idx_size);
	}
}

static void
fd_draw_vbo(struct pipe_context *pctx, const struct pipe_draw_info *info)
{
	struct fd_context *ctx = fd_context(pctx);
	struct pipe_framebuffer_state *fb = &ctx->framebuffer;
	unsigned buffers;

	/* if we supported transform feedback, we'd have to disable this: */
	if (((ctx->scissor.maxx - ctx->scissor.minx) *
			(ctx->scissor.maxy - ctx->scissor.miny)) == 0) {
		return;
	}

	ctx->needs_flush = true;

	fd_resource(fb->cbufs[0]->texture)->dirty = true;

	/* figure out the buffers we need: */
	buffers = FD_BUFFER_COLOR;
	if (fd_depth_enabled(ctx)) {
		buffers |= FD_BUFFER_DEPTH;
		fd_resource(fb->zsbuf->texture)->dirty = true;
	}
	if (fd_stencil_enabled(ctx)) {
		buffers |= FD_BUFFER_STENCIL;
		fd_resource(fb->zsbuf->texture)->dirty = true;
	}

	/* any buffers that haven't been cleared, we need to restore: */
	ctx->restore |= buffers & (FD_BUFFER_ALL & ~ctx->cleared);
	/* and any buffers used, need to be resolved: */
	ctx->resolve |= buffers;

	ctx->draw(ctx, info);
}

void
fd_draw_init(struct pipe_context *pctx)
{
	pctx->draw_vbo = fd_draw_vbo;
}
