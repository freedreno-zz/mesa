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
	struct fd_ringbuffer *ring = ctx->ring;
	struct pipe_framebuffer_state *pfb = &ctx->framebuffer;
	struct fd_gmem_stateobj *gmem = &ctx->gmem;
	int i;

	uint32_t x1 = xoff;
	uint32_t y1 = yoff;
	uint32_t x2 = xoff + bin_w - 1;
	uint32_t y2 = yoff + bin_h - 1;

	if ((xoff == 0) && (yoff == 0)) {
		OUT_PKT0(ring, REG_A3XX_VSC_BIN_SIZE, 1);
		OUT_RING(ring, A3XX_VSC_BIN_SIZE_WIDTH(bin_w) |
				A3XX_VSC_BIN_SIZE_HEIGHT(bin_h));
	}

	OUT_PKT3(ring, CP_SET_BIN, 3);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, CP_SET_BIN_1_X1(x1) | CP_SET_BIN_1_Y1(y1));
	OUT_RING(ring, CP_SET_BIN_2_X2(x2) | CP_SET_BIN_2_Y2(y2));

	OUT_PKT3(ring, CP_REG_RMW, 3);
	OUT_RING(ring, REG_A3XX_RB_RENDER_CONTROL);
	OUT_RING(ring, ~A3XX_RB_RENDER_CONTROL_BIN_WIDTH__MASK);
	OUT_RING(ring, A3XX_RB_RENDER_CONTROL_BIN_WIDTH(bin_w));

	for (i = 0; i < 4; i++) {
		enum a3xx_color_format format = 0;
		uint32_t stride = 0;

		if (i < pfb->nr_cbufs) {
			struct pipe_surface *psurf = pfb->cbufs[i];
			struct fd_resource *res = fd_resource(psurf->texture);

			format = fd3_pipe2color(psurf->format);
			stride = res->pitch * res->cpp;
		}

		OUT_PKT0(ring, REG_A3XX_RB_MRT_BUF_INFO(i), 2);
		OUT_RING(ring, A3XX_RB_MRT_BUF_INFO_COLOR_FORMAT(format) |
				A3XX_RB_MRT_BUF_INFO_COLOR_TILE_MODE(TILE_32X32) |
				A3XX_RB_MRT_BUF_INFO_COLOR_BUF_PITCH(stride));
		OUT_RING(ring, A3XX_RB_MRT_BUF_BASE_COLOR_BUF_BASE(0));

		OUT_PKT0(ring, REG_A3XX_SP_FS_IMAGE_OUTPUT_REG(i), 1);
		OUT_RING(ring, A3XX_SP_FS_IMAGE_OUTPUT_REG_MRTFORMAT(format));
	}

	/* setup scissor/offset for current tile: */
	OUT_PKT0(ring, REG_A3XX_PA_SC_WINDOW_OFFSET, 1);
	OUT_RING(ring, A3XX_PA_SC_WINDOW_OFFSET_X(xoff) |
			A3XX_PA_SC_WINDOW_OFFSET_Y(yoff));

	OUT_PKT0(ring, REG_A3XX_GRAS_SC_WINDOW_SCISSOR_TL, 2);
	OUT_RING(ring, A3XX_GRAS_SC_WINDOW_SCISSOR_TL_X(0) |
			A3XX_GRAS_SC_WINDOW_SCISSOR_TL_Y(0));
	OUT_RING(ring, A3XX_GRAS_SC_WINDOW_SCISSOR_BR_X(pfb->width - 1) |
			A3XX_GRAS_SC_WINDOW_SCISSOR_BR_Y(pfb->height - 1));

	OUT_PKT0(ring, REG_A3XX_GRAS_SC_SCREEN_SCISSOR_TL, 2);
	OUT_RING(ring, A3XX_GRAS_SC_SCREEN_SCISSOR_TL_X(x1) |
			A3XX_GRAS_SC_SCREEN_SCISSOR_TL_Y(y1));
	OUT_RING(ring, A3XX_GRAS_SC_SCREEN_SCISSOR_BR_X(x2) |
			A3XX_GRAS_SC_SCREEN_SCISSOR_BR_Y(y2));
}

/* before IB to rendering cmds: */
static void
fd3_emit_tile_renderprep(struct fd_context *ctx, uint32_t xoff, uint32_t yoff,
		uint32_t bin_w, uint32_t bin_h)
{
	/* TODO probably some of tile_prep() needs to move in here.. */
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
