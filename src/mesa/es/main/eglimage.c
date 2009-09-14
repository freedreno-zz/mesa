/*
 * Copyright (C) 2009 Chia-I Wu <olvaffe@gmail.com>
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "main/mtypes.h"
#include "main/context.h"
#include "main/teximage.h"
#include "main/texstate.h"
#include "main/imports.h"
#include "glapi/dispatch.h"

#include "eglimage.h"


#if FEATURE_OES_EGL_image


void GLAPIENTRY
_mesa_EGLImageTargetRenderbufferStorageOES(GLenum target, GLeglImageOES image)
{
   GET_CURRENT_CONTEXT(ctx);
   struct gl_renderbuffer *rb;

   if (!ctx->Extensions.OES_EGL_image) {
      _mesa_error(ctx, GL_INVALID_OPERATION,
                  "glEGLImageTargetRenderbufferStorageOES(unsupported)");
      return;
   }

   if (target != GL_RENDERBUFFER) {
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "glEGLImageTargetRenderbufferStorage(target=0x%x)", target);
      return;
   }

   rb = ctx->CurrentRenderbuffer;
   if (!rb) {
      _mesa_error(ctx, GL_INVALID_OPERATION,
                  "glEGLImageTargetRenderbufferStorageOES(no bound rb)");
      return;
   }

   FLUSH_VERTICES(ctx, _NEW_BUFFERS);

   ASSERT(ctx->Driver.EGLImageTargetRenderbufferStorage);
   ctx->Driver.EGLImageTargetRenderbufferStorage(ctx, rb, image);
   /* invalidate fbo? */
}

void GLAPIENTRY _mesa_EGLImageTargetTexture2DOES(GLenum target, GLeglImageOES image)
{
   GET_CURRENT_CONTEXT(ctx);
   struct gl_texture_unit *texUnit;
   struct gl_texture_object *texObj;

   if (!ctx->Extensions.OES_EGL_image) {
      _mesa_error(ctx, GL_INVALID_OPERATION,
                  "glEGLImageTargetTexture2DOES(unsupported)");
      return;
   }

   if (target != GL_TEXTURE_2D) {
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "glEGLImageTargetTexture2D(target=0x%x)", target);
      return;
   }

   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   texUnit = _mesa_get_current_tex_unit(ctx);
   texObj = _mesa_select_tex_object(ctx, texUnit, target);

   _mesa_lock_texture(ctx, texObj);

   ASSERT(ctx->Driver.EGLImageTargetTexture2D);
   ctx->Driver.EGLImageTargetTexture2D(ctx, texObj ,image);

   /* invalidate state and fbo?*/
   /* fbo? */
   texObj->_Complete = GL_FALSE;
   ctx->NewState |= _NEW_TEXTURE;

   _mesa_unlock_texture(ctx, texObj);
}


void
_mesa_init_eglimage_dispatch(struct _glapi_table *disp)
{
   SET_EGLImageTargetRenderbufferStorageOES(disp,
         _mesa_EGLImageTargetRenderbufferStorageOES);
   SET_EGLImageTargetTexture2DOES(disp, _mesa_EGLImageTargetTexture2DOES);
}


#endif /* FEATURE_OES_EGL_image */
