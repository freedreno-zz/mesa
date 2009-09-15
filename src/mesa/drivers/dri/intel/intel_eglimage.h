/**************************************************************************
 * 
 * Copyright (C) 2009 Chia-I Wu <olvaffe@gmail.com>
 * All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, * distribute, sub license, and/or sell copies of the Software, and to
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

#ifndef INTEL_EGLIMAGE_H
#define INTEL_EGLIMAGE_H

#include "main/mtypes.h"

/* main/eglimage.h might not exist */
#if FEATURE_OES_EGL_image

#ifndef GL_OES_EGL_image
typedef void *GLeglImageOES;
#endif

#include "main/eglimage.h"

extern void
intelEGLImageTargetRenderbufferStorage(GLcontext *ctx,
                                       struct gl_renderbuffer *rb,
                                       GLeglImageOES image);

extern void
intelEGLImageTargetTexture2D(GLcontext *ctx,
                             struct gl_texture_object *texObj,
                             GLeglImageOES image);

#else
#define _MESA_INIT_EGLIMAGE_FUNCTIONS(driver, impl) do { } while (0)
#endif /* FEATURE_OES_EGL_image */

static INLINE void
intelInitEGLImageFuncs(struct dd_function_table *functions)
{
   _MESA_INIT_EGLIMAGE_FUNCTIONS(functions, intel);
}

#endif /* INTEL_EGLIMAGE_H */
