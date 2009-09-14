/**************************************************************************
 * 
 * Copyright (C) 2009 Chia-I Wu <olvaffe@gmail.com>
 * All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 **************************************************************************/

#include "main/mtypes.h"
#include "main/teximage.h"

#include "intel_context.h"
#include "intel_fbo.h"
#include "intel_tex.h"

#include "intel_eglimage.h"
#include "main/eglimage.h"

#include "EGL/internal/eglimage_dri.h"


#if FEATURE_OES_EGL_image


/* move to intel_fbo.c */
static void
copy_renderbuffer(struct intel_renderbuffer *dst,
                  struct intel_renderbuffer *src)
{
   dst->Base.Width          = src->Base.Width;
   dst->Base.Height         = src->Base.Height;
   dst->Base.InternalFormat = src->Base.InternalFormat;
   dst->Base._ActualFormat  = src->Base._ActualFormat;
   dst->Base._BaseFormat    = src->Base._BaseFormat;

   dst->Base.ColorEncoding  = src->Base.ColorEncoding;
   dst->Base.ComponentType  = src->Base.ComponentType;

   dst->Base.RedBits        = src->Base.RedBits;
   dst->Base.GreenBits      = src->Base.GreenBits;
   dst->Base.BlueBits       = src->Base.BlueBits;
   dst->Base.AlphaBits      = src->Base.AlphaBits;
   dst->Base.IndexBits      = src->Base.IndexBits;
   dst->Base.DepthBits      = src->Base.DepthBits;
   dst->Base.StencilBits    = src->Base.StencilBits;
   dst->Base.NumSamples     = src->Base.NumSamples;

   dst->Base.DataType       = src->Base.DataType;

   intel_renderbuffer_set_region(dst, src->region);
}

static __DRIEGLImage *
get_image(GLcontext *ctx, GLeglImageOES image)
{
   __DRIEGLImage *driImage;

   driImage = _eglClientGetImageData((__DRIEGLImageHandle) image);
   if (!driImage || driImage->magic != __DRI_EGL_IMAGE_MAGIC) {
      _mesa_error(ctx, GL_INVALID_VALUE,
                  "glEGLImageTargetTexture2DOES(image=0x%x)", image);
      return NULL;
   }

   return driImage;
}

void
intelEGLImageTargetRenderbufferStorage(GLcontext *ctx,
                                          struct gl_renderbuffer *rb,
                                          GLeglImageOES image)
{
   struct intel_renderbuffer *irb = intel_renderbuffer(rb);
   __DRIEGLImage *driImage;
   struct intel_framebuffer *image_fb;
   struct intel_renderbuffer *image_rb;

   driImage = get_image(ctx, image);
   if (!driImage)
      return;

   image_fb = driImage->drawable->driverPrivate;
   image_rb = image_fb->color_rb[0];

   copy_renderbuffer(irb, image_rb);
}


void
intelEGLImageTargetTexture2D(GLcontext *ctx,
                                struct gl_texture_object *texObj,
                                GLeglImageOES image)
{
   struct intel_context *intel = intel_context(ctx);
   __DRIEGLImage *driImage;
   GLint glx_texture_format;

   driImage = get_image(ctx, image);
   if (!driImage)
      return;

   /* only level == 0 is supported */
   if (driImage->level) {
      _mesa_error(ctx, GL_INVALID_OPERATION,
                  "glEGLImageTargetTexture2DOES(level=%d)", driImage->level);
      return;
   }

   glx_texture_format = (driImage->texture_format_rgba)
      ? GLX_TEXTURE_FORMAT_RGBA_EXT : GLX_TEXTURE_FORMAT_RGB_EXT;

   /* TODO refactor intelSetTexBuffer2 to avoid lock... */
   _mesa_unlock_texture(ctx, texObj);
   intelSetTexBuffer2(intel->driContext, texObj->Target, glx_texture_format,
                      driImage->drawable);
   _mesa_lock_texture(ctx, texObj);
}


#endif /* FEATURE_OES_EGL_image */
