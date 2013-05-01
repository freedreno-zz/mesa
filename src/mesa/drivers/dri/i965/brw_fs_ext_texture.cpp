/*
 * Copyright © 2013 Intel Corporation
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Topi Pohjolainen <topi.pohjolainen@intel.com>
 *
 */

/** @file brw_fs_ext_texture.cpp
 *
 * This file implements the generation of FS LIR for converting YUV samples into
 * RGB as part of single GLSL texture sampling instruction. The implementation
 * follows the one found in "brw_wm_fp.c::precalc_tex()".
 *
 *   B = 1.164(Y - 16)                  + 2.018(U - 128)
 *   G = 1.164(Y - 16) - 0.813(V - 128) - 0.391(U - 128)
 *   R = 1.164(Y - 16) + 1.596(V - 128)
 * 
 * Implementation in 'brw_wm_fp.c':
 *
 * Need to emit YUV texture conversions by hand. Probably need to do this here
 * - the alternative is in execution unit emisson time , but the conversion
 * requires allocating a temporary variable which one doesn't have the facility
 * to do that late in the compilation.
 * 
 * CONST C0 = { -.0625, -.5, -.5, 1.164 }
 * CONST C1 = { 1.596, -0.813, 2.018, -.391 }
 * YUV     = TEX ...
 * YUV.xyz = ADD YUV,     C0
 * YUV.x   = MUL YUV.x,   C0.w
 * RGB.xyz = MAD YUV.zzy, C1,   YUV.x
 * RGB.y   = MAD YUV.y,   C1.w, RGB.y
 */
extern "C" {

#include <sys/types.h>

#include "main/macros.h"
#include "brw_context.h"
}
#include "brw_shader.h"
#include "brw_fs.h"

struct fs_reg_const_float4 : public fs_reg {
   fs_reg_const_float4(fs_visitor *v, float f1, float f2, float f3, float f4) :
      fs_reg(v, glsl_type::vec4_type)
   {
      fs_reg tmp = *this;

      v->emit(BRW_OPCODE_MOV, tmp, fs_reg(f1));
      ++tmp.reg_offset;
      v->emit(BRW_OPCODE_MOV, tmp, fs_reg(f2));
      ++tmp.reg_offset;
      v->emit(BRW_OPCODE_MOV, tmp, fs_reg(f3));
      ++tmp.reg_offset;
      v->emit(BRW_OPCODE_MOV, tmp, fs_reg(f4));
   }
};

static fs_reg
add_mul_yuv_c0(fs_visitor *v, const fs_reg& yuv)
{
   /**
    * Whereas original uses 16/256 = .0625, 128/256 = .5, here one uses the
    * divider of 255 corresponding to the range [0,255]. The multiplier of 1.164
    * in turn corresponds to treating Y-components being in the range of
    * [16,235] (219 steps).
    */
   fs_reg_const_float4 c0(v, -16.0f/255, -128.0f/255, -128.0f/255, 255.0/219);
   fs_reg res(v, glsl_type::vec4_type);
   fs_reg tmp_res(res);
   fs_reg tmp_yuv(yuv);

   /* YUV.xyz = ADD YUV, C0 */
   for (unsigned i = 0; i < 3; ++i) {
      v->emit(BRW_OPCODE_ADD, tmp_res, tmp_yuv, c0);
      tmp_yuv.reg_offset++;
      c0.reg_offset++;
      tmp_res.reg_offset++;
   }

   /* YUV.x = MUL YUV.x, C0.w */
   tmp_res.reg_offset = 0;
   v->emit(BRW_OPCODE_MUL, tmp_res, tmp_res, c0);

   return res;
}

static fs_reg
mad_yuv_c1(fs_visitor *v, const fs_reg& yuv)
{
   /**
    * The multipliers are result of treating V- and U-components having range
    * of [16,240] (224 steps).
    */
   fs_reg_const_float4 c1(v, 1.402 * 255.0 / 224, -0.714 * 255.0 / 224,
                             1.772 * 255.0 / 224, -0.344 * 255.0 / 224);
   fs_reg res(v, glsl_type::vec4_type);
   fs_reg tmp_res(res);
   fs_reg tmp_uv(yuv);
   fs_reg tmp_y(yuv);

   /* RGB.x = MAD YUV.x, C1.x, YUV.z */
   tmp_uv.reg_offset = 2;
   v->emit(BRW_OPCODE_MAD, tmp_res, tmp_y, c1, tmp_uv);
   c1.reg_offset++;
   tmp_res.reg_offset++;

   /* RGB.y = MAD YUV.x, C1.y, YUV.z */
   v->emit(BRW_OPCODE_MAD, tmp_res, tmp_y, c1, tmp_uv);
   c1.reg_offset++;
   tmp_res.reg_offset++;

   /* RGB.z = MAD YUV.x, C1.z, YUV.y */
   tmp_uv.reg_offset = 1;
   v->emit(BRW_OPCODE_MAD, tmp_res, tmp_y, c1, tmp_uv);
   c1.reg_offset++;

   /* RGB.y = MAD RGB.y, C1.w, YUV.y */
   tmp_res.reg_offset = 1;
   v->emit(BRW_OPCODE_MAD, tmp_res, tmp_res, c1, tmp_uv);

   /* Specification says that alpha is to be set to 255 if not available */
   tmp_res.reg_offset = 3;
   v->emit(BRW_OPCODE_MOV, tmp_res, fs_reg(1.0f));

   return res;
}

static const struct intel_texture_image *
resolve_tex_img(const struct gl_context *ctx, const GLbitfield *used, int unit)
{
   if (!(used[unit] & (1 << TEXTURE_EXTERNAL_INDEX)))
      return 0;

   const struct gl_texture_object *obj =
      ctx->Texture.Unit[unit].CurrentTex[TEXTURE_EXTERNAL_INDEX];

   if (!obj)
      return 0;

   return (const struct intel_texture_image *)obj->Image[0][obj->BaseLevel];
}

static fs_inst *
emit_texture_gen(fs_visitor *visitor, ir_texture *ir, int gen,
		 fs_reg& dst, fs_reg& coord, int sampler,
		 int surf_index_offset)
{
   fs_reg shadow_c;
   fs_reg lod;
   fs_reg lod2;
   fs_inst *inst;

   if (gen >= 7) {
      inst = visitor->emit_texture_gen7(ir, dst, coord, shadow_c, lod, lod2, 0);
   } else if (gen >= 5) {
      inst = visitor->emit_texture_gen5(ir, dst, coord, shadow_c, lod, lod2, 0);
   } else {
      inst = visitor->emit_texture_gen4(ir, dst, coord, shadow_c, lod, lod2);
   }

   /* The header is set up by generate_tex() when necessary. */
   inst->src[0] = reg_undef;
   inst->sampler = sampler;
   inst->surf_index_offset = surf_index_offset;

   return inst;
}

static void
yuv420_chroma(fs_visitor *v, ir_texture *ir, int gen, fs_reg& yuv,
              fs_reg& coord, int sampler,
              unsigned chroma_src_i, unsigned chroma_dst_i)
{
   fs_reg tmp_yuv_dst(yuv);
   fs_reg c = fs_reg(v, glsl_type::vec4_type);

   emit_texture_gen(v, ir, gen, c, coord, sampler, chroma_src_i);

   tmp_yuv_dst.reg_offset += chroma_dst_i;
   v->emit(BRW_OPCODE_MOV, tmp_yuv_dst, c);
}

static void
nv12_chroma(fs_visitor *v, ir_texture *ir, int gen, fs_reg& yuv,
            fs_reg& coord, int sampler)
{
   fs_reg tmp_yuv_dst(yuv);
   fs_reg uv = fs_reg(v, glsl_type::vec4_type);

   emit_texture_gen(v, ir, gen, uv, coord, sampler, 1);

   tmp_yuv_dst.reg_offset++;
   v->emit(BRW_OPCODE_MOV, tmp_yuv_dst, uv);

   tmp_yuv_dst.reg_offset++;
   uv.reg_offset++;
   v->emit(BRW_OPCODE_MOV, tmp_yuv_dst, uv);
}

/* Consider the YUV format in question and fetch the different components from
 * single plane in case of packed formats or from separate planes in case of
 * planar formats.
 * The components are then packed into one register allowing one to use the same
 * conversion logic independent on the component layout in the texture being
 * sampled. Naturally one could write texture format aware converters and
 * possibly improve the performance by reducing the amount of instructions. Here
 * things are, however, rather kept simple.
 */
bool
fs_visitor::emit_texture_external(ir_texture *ir, fs_reg& coordinate,
				  int sampler)
{
   const struct intel_texture_image *img = resolve_tex_img(ctx,
                                              fp->Base.TexturesUsed,
                                              fp->Base.SamplerUnits[sampler]);

   if (img && !img->ext_format)
      return false;

   /**
    * "Sampling an external texture which is not associated with any EGLImage
    *  sibling will return a sample value of (0,0,0,1)." 
    */
   if (!img) {
      swizzle_result(ir, fs_reg_const_float4(this, 0, 0, 0, 1), sampler);
      return true;
   }

   fs_reg yuv = fs_reg(this, glsl_type::vec4_type);
   emit_texture_gen(this, ir, intel->gen, yuv, coordinate, sampler, 0);

   switch (img->ext_format->fourcc) {
   case __DRI_IMAGE_FOURCC_YUV420:
      yuv420_chroma(this, ir, intel->gen, yuv, coordinate, sampler, 1, 1);
      yuv420_chroma(this, ir, intel->gen, yuv, coordinate, sampler, 2, 2);
      break;
   case __DRI_IMAGE_FOURCC_YVU420:
      yuv420_chroma(this, ir, intel->gen, yuv, coordinate, sampler, 1, 2);
      yuv420_chroma(this, ir, intel->gen, yuv, coordinate, sampler, 2, 1);
      break;
   case __DRI_IMAGE_FOURCC_NV12:
      nv12_chroma(this, ir, intel->gen, yuv, coordinate, sampler);
      break;
   default:
      return false;
   }

   fs_reg rgb = mad_yuv_c1(this, add_mul_yuv_c0(this, yuv));

   swizzle_result(ir, rgb, sampler);

   return true;
}
