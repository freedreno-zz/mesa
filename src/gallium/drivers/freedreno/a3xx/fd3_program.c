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

/* once the compiler is good enough, we should construct TGSI in the
 * core freedreno driver, and then let the a2xx/a3xx parts compile
 * the internal shaders from TGSI the same as regular shaders.  This
 * would be the first step towards handling most of clear (and the
 * gmem<->mem blits) from the core via normal state changes and shader
 * state objects.
 *
 * (Well, there would still be some special bits, because there are
 * some registers that don't get set for normal draw, but this should
 * be relatively small and could be handled via callbacks from core
 * into a2xx/a3xx..)
 */
static struct fd3_shader_stateobj *
create_internal_shader(enum shader_t type, struct ir3_shader *ir)
{
	struct fd3_shader_stateobj *so = CALLOC_STRUCT(fd3_shader_stateobj);

	if (!so)
		return NULL;

	so->type = type;
	so->ir = ir;

	so->bin = ir3_shader_assemble(so->ir, &so->info);
	assert(so->bin);

	return so;
}

/* Creates shader:
 *    (sy)(ss)(rpt1)bary.f (ei)r0.z, (r)0, r0.x
 *    (rpt5)nop
 *    sam (f32)(xyzw)r0.x, r0.z, s#0, t#0
 *    (sy)(rpt3)cov.f32f16 hr0.x, (r)r0.x
 *    end
 */
static struct fd3_shader_stateobj *
create_blit_fp(void)
{
	struct ir3_shader *ir = ir3_shader_create();
	struct ir3_instruction *instr;

	/* (sy)(ss)(rpt1)bary.f (ei)r0.z, (r)0, r0.x */
	instr = ir3_instr_create(ir, 2, OPC_BARY_F);
	instr->flags = IR3_INSTR_SY | IR3_INSTR_SS;
	instr->repeat = 1;

	ir3_reg_create(instr, regid(0,2), IR3_REG_HALF |  /* (ei)r0.z */
			IR3_REG_EI);
	ir3_reg_create(instr, 0, IR3_REG_R |              /* (r)0 */
			IR3_REG_IMMED)->iim_val = 0;
	ir3_reg_create(instr, regid(0,0), 0);             /* r0.x */

	/* (rpt5)nop */
	instr = ir3_instr_create(ir, 0, OPC_NOP);
	instr->repeat = 5;

	/* sam (f32)(xyzw)r0.x, r0.z, s#0, t#0 */
	instr = ir3_instr_create(ir, 5, OPC_SAM);
	instr->cat5.samp = 0;
	instr->cat5.tex  = 0;
	instr->cat5.type = TYPE_F32;

	ir3_reg_create(instr, regid(0,0),                 /* (xyzw)r0.x */
			0)->wrmask = 0xf;
	ir3_reg_create(instr, regid(0,2), 0);             /* r0.z */

	/* (sy)(rpt3)cov.f32f16 hr0.x, (r)r0.x */
	instr = ir3_instr_create(ir, 1, 0);  /* mov/cov instructions have no opc */
	instr->flags = IR3_INSTR_SY;
	instr->repeat = 3;
	instr->cat1.src_type = TYPE_F32;
	instr->cat1.dst_type = TYPE_F16;

	ir3_reg_create(instr, regid(0,0), IR3_REG_HALF);  /* hr0.x */
	ir3_reg_create(instr, regid(0,0), IR3_REG_R);     /* (r)r0.x */

	/* end */
	instr = ir3_instr_create(ir, 0, OPC_END);

	return create_internal_shader(SHADER_FRAGMENT, ir);
}

/* Creates shader:
 *    (sy)(ss)end
 */
static struct fd3_shader_stateobj *
create_blit_vp(void)
{
	struct ir3_shader *ir = ir3_shader_create();
	struct ir3_instruction *instr;

	/* (sy)(ss)end */
	instr = ir3_instr_create(ir, 0, OPC_END);
	instr->flags = IR3_INSTR_SY | IR3_INSTR_SS;

	return create_internal_shader(SHADER_VERTEX, ir);
}

/* Creates shader:
 *    (sy)(ss)(rpt3)mov.f16f16 hr0.x, (r)hc0.x
 *    end
 */
static struct fd3_shader_stateobj *
create_solid_fp(void)
{
	struct ir3_shader *ir = ir3_shader_create();
	struct ir3_instruction *instr;

	/* (sy)(ss)(rpt3)mov.f16f16 hr0.x, (r)hc0.x */
	instr = ir3_instr_create(ir, 1, 0);  /* mov/cov instructions have no opc */
	instr->flags = IR3_INSTR_SY | IR3_INSTR_SS;
	instr->repeat = 3;
	instr->cat1.src_type = TYPE_F16;
	instr->cat1.dst_type = TYPE_F16;

	ir3_reg_create(instr, regid(0,0), IR3_REG_HALF);  /* hr0.x */
	ir3_reg_create(instr, regid(0,0), IR3_REG_HALF |  /* (r)hc0.x */
			IR3_REG_CONST | IR3_REG_R);

	/* end */
	instr = ir3_instr_create(ir, 0, OPC_END);

	return create_internal_shader(SHADER_FRAGMENT, ir);
}

/* Creates shader:
 *    (sy)(ss)end
 */
static struct fd3_shader_stateobj *
create_solid_vp(void)
{
	struct ir3_shader *ir = ir3_shader_create();
	struct ir3_instruction *instr;

	/* (sy)(ss)end */
	instr = ir3_instr_create(ir, 0, OPC_END);
	instr->flags = IR3_INSTR_SY | IR3_INSTR_SS;

	return create_internal_shader(SHADER_VERTEX, ir);
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
