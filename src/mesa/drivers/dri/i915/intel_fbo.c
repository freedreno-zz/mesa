/**************************************************************************
 * 
 * Copyright 2006 Tungsten Graphics, Inc., Cedar Park, Texas.
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


#include "imports.h"
#include "mtypes.h"
#include "bufferobj.h"

#include "intel_context.h"
#include "intel_buffer_objects.h"
#include "intel_bufmgr.h"
#include "intel_fbo.h"


static struct gl_framebuffer *
intel_new_framebuffer(GLcontext *ctx, GLuint name)
{
   return NULL;
}


static struct gl_renderbuffer *
intel_new_renderbuffer(GLcontext *ctx, GLuint name)
{
   return NULL;
}


static void
intel_framebuffer_renderbuffer(GLcontext *ctx, 
                               struct gl_framebuffer *fb,
                               GLenum attachment,
                               struct gl_renderbuffer *rb)
{
}


static void
intel_renderbuffer_texture(GLcontext *ctx,
                           struct gl_renderbuffer_attachment *att,
                           struct gl_texture_object *texObj,
                           GLenum texTarget, GLuint level, GLuint zoffset)
{
}


static void
intel_finish_render_texture(GLcontext *ctx,
                            struct gl_texture_object *texObj,
                            GLuint face, GLuint level)
{

}


/**
 * Do one-time context initializations related to GL_EXT_framebuffer_object.
 */
void
intel_fbo_init( struct intel_context *intel )
{
   GLcontext *ctx = &intel->ctx;

   ctx->Driver.NewFramebuffer = intel_new_framebuffer;
   ctx->Driver.NewRenderbuffer = intel_new_renderbuffer;
   ctx->Driver.FramebufferRenderbuffer = intel_framebuffer_renderbuffer;
   ctx->Driver.RenderbufferTexture = intel_renderbuffer_texture;
   ctx->Driver.FinishRenderTexture = intel_finish_render_texture;
}
