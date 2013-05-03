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

#include "pipe/p_state.h"
#include "util/u_string.h"
#include "util/u_memory.h"
#include "util/u_helpers.h"

#include "freedreno_resource.h"

#include "fd3_emit.h"
#include "fd3_blend.h"
#include "fd3_context.h"
#include "fd3_program.h"
#include "fd3_rasterizer.h"
#include "fd3_texture.h"
#include "fd3_util.h"
#include "fd3_zsa.h"

static void
emit_constants(struct fd_ringbuffer *ring,
		enum adreno_state_block state_block,
		struct fd_constbuf_stateobj *constbuf,
		struct fd3_shader_stateobj *shader)
{
}

static void
emit_textures(struct fd_ringbuffer *ring,
		enum adreno_state_block state_block,
		struct fd_texture_stateobj *tex)
{
}

void
fd3_emit_vertex_bufs(struct fd_ringbuffer *ring,
		struct fd_program_stateobj *prog,
		struct fd3_vertex_buf *vbufs, uint32_t n)
{
	struct fd3_shader_stateobj *vp = prog->vp;
	uint32_t i;

	assert(n == vp->inputs_count);

	for (i = 0; i < vp->inputs_count; i++) {
		struct pipe_resource *prsc = vbufs[i].prsc;
		struct fd_resource *rsc = fd_resource(prsc);
		enum a3xx_vtx_fmt fmt = fd3_pipe2vtx(prsc->format);
		bool switchnext = (i != (vp->inputs_count - 1));
		uint32_t s = vbufs[i].stride;

		OUT_PKT0(ring, REG_A3XX_VFD_FETCH(i), 2);
		OUT_RING(ring, A3XX_VFD_FETCH_INSTR_0_FETCHSIZE(s - 1) |
				A3XX_VFD_FETCH_INSTR_0_BUFSTRIDE(s) |
				COND(switchnext, A3XX_VFD_FETCH_INSTR_0_SWITCHNEXT) |
				A3XX_VFD_FETCH_INSTR_0_INDEXCODE(i) |
				A3XX_VFD_FETCH_INSTR_0_STEPRATE(1));
		OUT_RELOC(ring, rsc->bo, vbufs[i].offset, 0);

		OUT_PKT0(ring, REG_A3XX_VFD_DECODE_INSTR(i), 1);
		OUT_RING(ring, A3XX_VFD_DECODE_INSTR_CONSTFILL |
				A3XX_VFD_DECODE_INSTR_WRITEMASK(vp->inputs[i].compmask) |
				A3XX_VFD_DECODE_INSTR_FORMAT(fmt) |
				A3XX_VFD_DECODE_INSTR_REGID(vp->inputs[i].regid) |
				A3XX_VFD_DECODE_INSTR_SHIFTCNT(s) |
				A3XX_VFD_DECODE_INSTR_LASTCOMPVALID |
				COND(switchnext, A3XX_VFD_DECODE_INSTR_SWITCHNEXT));
	}

	/* we have this sometimes, not others.. perhaps we could be clever
	 * and figure out actually when we need to invalidate cache:
	 */
	OUT_PKT0(ring, REG_A3XX_UCHE_CACHE_INVALIDATE0_REG, 2);
	OUT_RING(ring, A3XX_UCHE_CACHE_INVALIDATE0_REG_ADDR(0));
	OUT_RING(ring, A3XX_UCHE_CACHE_INVALIDATE1_REG_ADDR(0) |
			A3XX_UCHE_CACHE_INVALIDATE1_REG_OPCODE(INVALIDATE) |
			A3XX_UCHE_CACHE_INVALIDATE1_REG_ENTIRE_CACHE);
}

void
fd3_emit_state(struct fd_context *ctx, uint32_t dirty)
{
	struct fd_ringbuffer *ring = ctx->ring;

	if (dirty & FD_DIRTY_SAMPLE_MASK) {
		OUT_PKT0(ring, REG_A3XX_RB_MSAA_CONTROL, 1);
		OUT_RING(ring, A3XX_RB_MSAA_CONTROL_DISABLE |
				A3XX_RB_MSAA_CONTROL_SAMPLES(MSAA_ONE) |
				A3XX_RB_MSAA_CONTROL_SAMPLE_MASK(ctx->sample_mask));
	}

	if (dirty & (FD_DIRTY_ZSA | FD_DIRTY_STENCIL_REF)) {
		struct fd3_zsa_stateobj *zsa = fd3_zsa_stateobj(ctx->zsa);
		struct pipe_stencil_ref *sr = &ctx->stencil_ref;

		/* use RMW (read-modify-write) to update this since the
		 * GMEM/binning code is deciding on the bin-width potentially
		 * after this is emitted:
		 */
		OUT_PKT3(ring, CP_REG_RMW, 3);
		OUT_RING(ring, REG_A3XX_RB_RENDER_CONTROL);
		OUT_RING(ring, A3XX_RB_RENDER_CONTROL_BIN_WIDTH__MASK);
		OUT_RING(ring, zsa->rb_render_control);

		OUT_PKT0(ring, REG_A3XX_RB_DEPTH_CONTROL, 1);
		OUT_RING(ring, zsa->rb_depth_control);

		OUT_PKT0(ring, REG_A3XX_RB_STENCIL_CONTROL, 1);
		OUT_RING(ring, zsa->rb_stencil_control);

		OUT_PKT0(ring, REG_A3XX_RB_STENCILREFMASK, 2);
		OUT_RING(ring, zsa->rb_stencilrefmask |
				A3XX_RB_STENCILREFMASK_STENCILREF(sr->ref_value[0]));
		OUT_RING(ring, zsa->rb_stencilrefmask_bf |
				A3XX_RB_STENCILREFMASK_BF_STENCILREF(sr->ref_value[1]));
	}

	if (dirty & FD_DIRTY_RASTERIZER) {
		struct fd3_rasterizer_stateobj *rasterizer =
				fd3_rasterizer_stateobj(ctx->rasterizer);

		OUT_PKT0(ring, REG_A3XX_GRAS_SU_MODE_CONTROL, 1);
		OUT_RING(ring, rasterizer->gras_su_mode_control);

		OUT_PKT0(ring, REG_A3XX_GRAS_SU_POINT_MINMAX, 2);
		OUT_RING(ring, rasterizer->gras_su_point_minmax);
		OUT_RING(ring, rasterizer->gras_su_point_size);

		OUT_PKT0(ring, REG_A3XX_GRAS_SU_POLY_OFFSET_SCALE, 2);
		OUT_RING(ring, rasterizer->gras_su_poly_offset_scale);
		OUT_RING(ring, rasterizer->gras_su_poly_offset_offset);
	}

	if (dirty & (FD_DIRTY_RASTERIZER | FD_DIRTY_PROG)) {
		struct fd3_rasterizer_stateobj *rasterizer =
				fd3_rasterizer_stateobj(ctx->rasterizer);
		struct fd3_shader_stateobj *vp = ctx->prog.vp;

		OUT_PKT0(ring, REG_A3XX_PC_PRIM_VTX_CNTL, 1);
		OUT_RING(ring, rasterizer->pc_prim_vtx_cntl |
				A3XX_PC_PRIM_VTX_CNTL_STRIDE_IN_VPC(vp->stride_in_vpc));
	}

	if (dirty & FD_DIRTY_SCISSOR) {
		OUT_PKT0(ring, REG_A3XX_GRAS_SC_WINDOW_SCISSOR_TL, 2);
		OUT_RING(ring, A3XX_GRAS_SC_WINDOW_SCISSOR_TL_X(ctx->scissor.minx) |
				A3XX_GRAS_SC_WINDOW_SCISSOR_TL_Y(ctx->scissor.miny));
		OUT_RING(ring, A3XX_GRAS_SC_WINDOW_SCISSOR_BR_X(ctx->scissor.maxx) |
				A3XX_GRAS_SC_WINDOW_SCISSOR_BR_Y(ctx->scissor.maxy));

		ctx->max_scissor.minx = MIN2(ctx->max_scissor.minx, ctx->scissor.minx);
		ctx->max_scissor.miny = MIN2(ctx->max_scissor.miny, ctx->scissor.miny);
		ctx->max_scissor.maxx = MAX2(ctx->max_scissor.maxx, ctx->scissor.maxx);
		ctx->max_scissor.maxy = MAX2(ctx->max_scissor.maxy, ctx->scissor.maxy);
	}

	if (dirty & FD_DIRTY_VIEWPORT) {
		OUT_PKT0(ring, REG_A3XX_GRAS_CL_VPORT_XOFFSET, 6);
		OUT_RING(ring, A3XX_GRAS_CL_VPORT_XOFFSET(ctx->viewport.translate[0]));
		OUT_RING(ring, A3XX_GRAS_CL_VPORT_XSCALE(ctx->viewport.scale[0]));
		OUT_RING(ring, A3XX_GRAS_CL_VPORT_YOFFSET(ctx->viewport.translate[1]));
		OUT_RING(ring, A3XX_GRAS_CL_VPORT_YSCALE(ctx->viewport.scale[1]));
		OUT_RING(ring, A3XX_GRAS_CL_VPORT_ZOFFSET(ctx->viewport.translate[2]));
		OUT_RING(ring, A3XX_GRAS_CL_VPORT_ZSCALE(ctx->viewport.scale[2]));
	}

	if (dirty & (FD_DIRTY_PROG | FD_DIRTY_CONSTBUF)) {
		struct fd_program_stateobj *prog = &ctx->prog;

		emit_constants(ring,  SB_VERT_SHADER,
				&ctx->constbuf[PIPE_SHADER_VERTEX],
				(prog->dirty & FD_SHADER_DIRTY_VP) ? prog->vp : NULL);
		emit_constants(ring, SB_FRAG_SHADER,
				&ctx->constbuf[PIPE_SHADER_FRAGMENT],
				(prog->dirty & FD_SHADER_DIRTY_FP) ? prog->fp : NULL);
	}

	if (dirty & FD_DIRTY_PROG)
		fd3_program_emit(ring, &ctx->prog);

	if (dirty & FD_DIRTY_BLEND) {
		struct fd3_blend_stateobj *blend = fd3_blend_stateobj(ctx->blend);
		uint32_t i;

		for (i = 0; i < ARRAY_SIZE(blend->rb_mrt); i++) {
			OUT_PKT0(ring, REG_A3XX_RB_MRT_CONTROL(i), 1);
			OUT_RING(ring, blend->rb_mrt[i].control);

			OUT_PKT0(ring, REG_A3XX_RB_MRT_BLEND_CONTROL(i), 1);
			OUT_RING(ring, blend->rb_mrt[i].blend_control);
		}
	}

	if (dirty & FD_DIRTY_VERTTEX)
		emit_textures(ring, SB_VERT_TEX, &ctx->verttex);

	if (dirty & FD_DIRTY_FRAGTEX)
		emit_textures(ring, SB_FRAG_TEX, &ctx->fragtex);

	ctx->dirty &= ~dirty;
}

/* emit per-context initialization:
 */
void
fd3_emit_setup(struct fd_context *ctx)
{
	struct fd3_context *fd3_ctx = fd3_context(&ctx->base);
	struct fd_ringbuffer *ring = ctx->ring;

	OUT_PKT3(ring, CP_REG_RMW, 3);
	OUT_RING(ring, REG_A3XX_RBBM_CLOCK_CTL);
	OUT_RING(ring, 0xfffcffff);
	OUT_RING(ring, 0x00000000);

	OUT_PKT3(ring, CP_INVALIDATE_STATE, 1);
	OUT_RING(ring, 0x00007fff);

	OUT_PKT0(ring, REG_A3XX_SP_VS_PVT_MEM_CTRL_REG, 2);
	OUT_RING(ring, 0x08000001);                  /* SP_VS_PVT_MEM_CTRL_REG */
	OUT_RELOC(ring, fd3_ctx->vs_pvt_mem, 0, 0);  /* SP_VS_PVT_MEM_ADDR_REG */

	OUT_PKT0(ring, REG_A3XX_SP_FS_PVT_MEM_CTRL_REG, 2);
	OUT_RING(ring, 0x08000001);                  /* SP_FS_PVT_MEM_CTRL_REG */
	OUT_RELOC(ring, fd3_ctx->fs_pvt_mem, 0, 0);  /* SP_FS_PVT_MEM_ADDR_REG */

	OUT_PKT0(ring, REG_A3XX_PC_VERTEX_REUSE_BLOCK_CNTL, 1);
	OUT_RING(ring, 0x0000000b);                  /* PC_VERTEX_REUSE_BLOCK_CNTL */

	OUT_PKT0(ring, REG_A3XX_RB_MSAA_CONTROL, 2);
	OUT_RING(ring, A3XX_RB_MSAA_CONTROL_DISABLE |
			A3XX_RB_MSAA_CONTROL_SAMPLES(MSAA_ONE) |
			A3XX_RB_MSAA_CONTROL_SAMPLE_MASK(0xffff));
	OUT_RING(ring, 0x00000000);        /* UNKNOWN_20C3 */

	OUT_PKT0(ring, REG_A3XX_GRAS_CL_GB_CLIP_ADJ, 1);
	OUT_RING(ring, A3XX_GRAS_CL_GB_CLIP_ADJ_HORZ(0) |
			A3XX_GRAS_CL_GB_CLIP_ADJ_VERT(0));

	OUT_PKT0(ring, REG_A3XX_UNKNOWN_0C81, 1);
	OUT_RING(ring, 0x00000001);        /* UNKNOWN_0C81 */

	OUT_PKT0(ring, REG_A3XX_TPL1_TP_VS_TEX_OFFSET, 1);
	OUT_RING(ring, A3XX_TPL1_TP_VS_TEX_OFFSET_SAMPLEROFFSET(0) |
			A3XX_TPL1_TP_VS_TEX_OFFSET_MEMOBJOFFSET(0) |
			A3XX_TPL1_TP_VS_TEX_OFFSET_BASETABLEPTR(0));

	OUT_PKT0(ring, REG_A3XX_TPL1_TP_FS_TEX_OFFSET, 1);
	OUT_RING(ring, A3XX_TPL1_TP_FS_TEX_OFFSET_SAMPLEROFFSET(16) |
			A3XX_TPL1_TP_FS_TEX_OFFSET_MEMOBJOFFSET(16) |
			A3XX_TPL1_TP_FS_TEX_OFFSET_BASETABLEPTR(224));

	OUT_PKT0(ring, REG_A3XX_VPC_VARY_CYLWRAP_ENABLE_0, 2);
	OUT_RING(ring, 0x00000000);        /* VPC_VARY_CYLWRAP_ENABLE_0 */
	OUT_RING(ring, 0x00000000);        /* VPC_VARY_CYLWRAP_ENABLE_1 */

	OUT_PKT0(ring, REG_A3XX_UNKNOWN_0E43, 1);
	OUT_RING(ring, 0x00000001);        /* UNKNOWN_0E43 */

	OUT_PKT0(ring, REG_A3XX_UNKNOWN_0F03, 1);
	OUT_RING(ring, 0x00000001);        /* UNKNOWN_0F03 */

	OUT_PKT0(ring, REG_A3XX_UNKNOWN_0EE0, 1);
	OUT_RING(ring, 0x00000003);        /* UNKNOWN_0EE0 */

	OUT_PKT0(ring, REG_A3XX_UNKNOWN_0C3D, 1);
	OUT_RING(ring, 0x00000001);        /* UNKNOWN_0C3D */

	OUT_PKT0(ring, REG_A3XX_HLSQ_CONST_VSPRESV_RANGE_REG, 2);
	OUT_RING(ring, A3XX_HLSQ_CONST_VSPRESV_RANGE_REG_STARTENTRY(0) |
			A3XX_HLSQ_CONST_VSPRESV_RANGE_REG_ENDENTRY(0));
	OUT_RING(ring, A3XX_HLSQ_CONST_FSPRESV_RANGE_REG_STARTENTRY(0) |
			A3XX_HLSQ_CONST_FSPRESV_RANGE_REG_ENDENTRY(0));

	OUT_PKT0(ring, REG_A3XX_UCHE_CACHE_MODE_CONTROL_REG, 1);
	OUT_RING(ring, 0x00000001);        /* UCHE_CACHE_MODE_CONTROL_REG */

	OUT_PKT0(ring, REG_A3XX_VSC_SIZE_ADDRESS, 1);
	OUT_RELOC(ring, fd3_ctx->vsc_size_mem, 0, 0); /* VSC_SIZE_ADDRESS */

	fd_ringbuffer_flush(ring);
	fd_ringmarker_mark(ctx->draw_start);
}
