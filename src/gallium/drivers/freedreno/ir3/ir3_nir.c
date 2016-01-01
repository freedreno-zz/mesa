/* -*- mode: C; c-file-style: "k&r"; tab-width 4; indent-tabs-mode: t; -*- */

/*
 * Copyright (C) 2015 Rob Clark <robclark@freedesktop.org>
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


#include "freedreno_util.h"

#include "ir3_nir.h"
#include "ir3_compiler.h"
#include "ir3_shader.h"

#include "nir/tgsi_to_nir.h"

struct nir_shader *
ir3_tgsi_to_nir(const struct tgsi_token *tokens)
{
	static const nir_shader_compiler_options options = {
			.lower_fpow = true,
			.lower_fsat = true,
			.lower_scmp = true,
			.lower_flrp = true,
			.lower_ffract = true,
			.native_integers = true,
	};
	return tgsi_to_nir(tokens, &options);
}

/* for given shader key, are any steps handled in nir? */
bool
ir3_key_lowers_nir(const struct ir3_shader_key *key)
{
	return key->fsaturate_s | key->fsaturate_t | key->fsaturate_r |
			key->vsaturate_s | key->vsaturate_t | key->vsaturate_r |
			key->ucp_enables | key->color_two_side;
}

#define OPT(nir, pass, ...) ({                             \
   bool this_progress = false;                             \
   NIR_PASS(this_progress, nir, pass, ##__VA_ARGS__);      \
   this_progress;                                          \
})

#define OPT_V(nir, pass, ...) NIR_PASS_V(nir, pass, ##__VA_ARGS__)

struct nir_shader *
ir3_optimize_nir(struct ir3_shader *shader, nir_shader *s,
		const struct ir3_shader_key *key)
{
	struct nir_lower_tex_options tex_options = {
			.lower_rect = 0,
	};
	bool progress;

	if (key) {
		switch (shader->type) {
		case SHADER_FRAGMENT:
		case SHADER_COMPUTE:
			tex_options.saturate_s = key->fsaturate_s;
			tex_options.saturate_t = key->fsaturate_t;
			tex_options.saturate_r = key->fsaturate_r;
			break;
		case SHADER_VERTEX:
			tex_options.saturate_s = key->vsaturate_s;
			tex_options.saturate_t = key->vsaturate_t;
			tex_options.saturate_r = key->vsaturate_r;
			break;
		}
	}

	if (shader->compiler->gpu_id >= 400) {
		/* a4xx seems to have *no* sam.p */
		tex_options.lower_txp = ~0;  /* lower all txp */
	} else {
		/* a3xx just needs to avoid sam.p for 3d tex */
		tex_options.lower_txp = (1 << GLSL_SAMPLER_DIM_3D);
	}

	if (fd_mesa_debug & FD_DBG_DISASM) {
		debug_printf("----------------------\n");
		nir_print_shader(s, stdout);
		debug_printf("----------------------\n");
	}

	OPT_V(s, nir_opt_global_to_local);
	OPT_V(s, nir_convert_to_ssa);

	if (key) {
		if (s->stage == MESA_SHADER_VERTEX) {
			OPT_V(s, nir_lower_clip_vs, key->ucp_enables);
		} else if (s->stage == MESA_SHADER_FRAGMENT) {
			OPT_V(s, nir_lower_clip_fs, key->ucp_enables);
		}
		if (key->color_two_side) {
			OPT_V(s, nir_lower_two_sided_color);
		}
	}

	OPT_V(s, nir_lower_tex, &tex_options);
	OPT_V(s, nir_lower_idiv);
	OPT_V(s, nir_lower_load_const_to_scalar);

	do {
		progress = false;

		OPT_V(s, nir_lower_vars_to_ssa);
		OPT_V(s, nir_lower_alu_to_scalar);
		OPT_V(s, nir_lower_phis_to_scalar);

		progress |= OPT(s, nir_copy_prop);
		progress |= OPT(s, nir_opt_dce);
		progress |= OPT(s, nir_opt_cse);
		progress |= OPT(s, ir3_nir_lower_if_else);
		progress |= OPT(s, nir_opt_algebraic);
		progress |= OPT(s, nir_opt_constant_folding);

	} while (progress);

	OPT_V(s, nir_remove_dead_variables);

	if (fd_mesa_debug & FD_DBG_DISASM) {
		debug_printf("----------------------\n");
		nir_print_shader(s, stdout);
		debug_printf("----------------------\n");
	}

	nir_sweep(s);

	return s;
}
