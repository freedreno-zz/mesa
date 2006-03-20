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
#include "fbobject.h"
#include "framebuffer.h"
#include "renderbuffer.h"
#include "context.h"
#include "texformat.h"

#include "intel_context.h"
#include "intel_bufmgr.h"
#include "intel_fbo.h"
#include "intel_mipmap_tree.h"
#include "intel_regions.h"
#include "intel_span.h"


#define MAGIC 0x12345678

/* XXX FBO: move this to intel_context.h (inlined) */
struct intel_renderbuffer *intel_renderbuffer( struct gl_renderbuffer *rb )
{
   struct intel_renderbuffer *irb = (struct intel_renderbuffer *) rb;
   if (irb) {
      assert(irb->Magic == 0x12345678);
   }
   return irb;
}


/**
 * Create a new framebuffer object.
 */
static struct gl_framebuffer *
intel_new_framebuffer(GLcontext *ctx, GLuint name)
{
   /* there's no intel_framebuffer at this time, just use Mesa's class */
   return _mesa_new_framebuffer(ctx, name);
}


static void
intel_delete_renderbuffer(struct gl_renderbuffer *rb)
{
   GET_CURRENT_CONTEXT(ctx);
   struct intel_context *intel = intel_context(ctx);
   struct intel_renderbuffer *irb = intel_renderbuffer(rb);

   if (intel && irb->region) {
      intel_region_release(intel, &irb->region);
   }

   _mesa_free(irb);
}



/**
 * Return a pointer to a specific pixel in a renderbuffer.
 * Note: y=0=bottom.
 * Called via gl_renderbuffer::GetPointer().
 */
static void *
intel_get_pointer(GLcontext *ctx, struct gl_renderbuffer *rb,
                  GLint x, GLint y)
{
   struct intel_renderbuffer *irb = intel_renderbuffer(rb);

   /* Actually, we could _always_ return NULL from this function and
    * be OK.  The swrast code would just use the Get/Put routines as needed.
    * But by really implementing this function there's a chance for better
    * performance.
    */
   if (irb->region && irb->region->map) {
      int offset;
      y = irb->region->height - y - 1;
      offset = (y * irb->region->pitch + x) * irb->region->cpp;
      return (void *) (irb->region->map + offset);
   }
   else {
      return NULL;
   }
}



/**
 * Called via glRenderbufferStorageEXT() to set the format and allocate
 * storage for a user-created renderbuffer.
 */
static GLboolean
intel_alloc_storage(GLcontext *ctx, struct gl_renderbuffer *rb,
                    GLenum internalFormat,
                    GLuint width, GLuint height)
{
   struct intel_context *intel = intel_context(ctx);
   struct intel_renderbuffer *irb = intel_renderbuffer(rb);
   const GLenum format = _mesa_base_fbo_format(ctx, internalFormat);
   GLboolean softwareBuffer = GL_FALSE;
   int cpp;

   ASSERT(rb->Name != 0);

   /* defaults */
   rb->RedBits =
   rb->GreenBits =
   rb->BlueBits =
   rb->AlphaBits =
   rb->IndexBits =
   rb->DepthBits =
   rb->StencilBits = 0;

   /* Always assume 32-bit pixels for now */
   switch (format) {
   case GL_RGB:
   case GL_RGBA:
      rb->InternalFormat = GL_RGBA8;
      rb->DataType = GL_UNSIGNED_BYTE;
      rb->RedBits = 8;
      rb->GreenBits = 8;
      rb->BlueBits = 8;
      rb->AlphaBits = 8;
      cpp = 4;
      break;
   case GL_DEPTH_COMPONENT:
      rb->InternalFormat = GL_DEPTH24_STENCIL8_EXT;
      rb->DataType = GL_UNSIGNED_BYTE;
      rb->DepthBits = 24;
      cpp = 4;
      break;
   case GL_STENCIL_INDEX:
      rb->InternalFormat = GL_STENCIL_INDEX8_EXT;
      rb->DataType = GL_UNSIGNED_BYTE;
      rb->StencilBits = 8;
      cpp = 1;
      softwareBuffer = GL_TRUE;
      /* XXX software buffer? */
      break;
   case GL_DEPTH_STENCIL_EXT:
      rb->InternalFormat = GL_DEPTH24_STENCIL8_EXT;
      rb->DataType = GL_UNSIGNED_INT;
      rb->DepthBits = 24;
      rb->StencilBits = 8;
      cpp = 4;
      break;
   default:
      _mesa_problem(ctx, "Unexpected format in intel_alloc_storage");
      return GL_FALSE;
   }

   intelFlush(ctx);

   /* free old region */
   if (irb->region) {
      /*LOCK_HARDWARE(intel);*/
      intel_region_release(intel, &irb->region);
      /*UNLOCK_HARDWARE(intel);*/
   }


   if (softwareBuffer) {
      return _mesa_soft_renderbuffer_storage(ctx, rb, internalFormat,
                                             width, height);
   }
   else {
      /* hardware renderbuffer */
      /* alloc new region */
      assert(width > 1);
      assert(height > 1);
      _mesa_debug(ctx, "Allocating %d x %d Intel RBO\n", width, height);
      /*LOCK_HARDWARE(intel);*/
      irb->region = intel_region_alloc(intel, cpp, width, height);
      /*UNLOCK_HARDWARE(intel);*/
      if (!irb->region)
         return GL_FALSE; /* out of memory? */
   }

   rb->Width = width;
   rb->Height = height;

   /* This sets the Get/PutRow/Value functions */
   intel_set_span_functions(&irb->Base);

   return GL_TRUE;
}



/**
 * Called for each hardware renderbuffer when a _window_ is resized.
 * Just update fields.
 * Not use for user-created renderbuffers!
 */
static GLboolean
intel_alloc_storage_window(GLcontext *ctx, struct gl_renderbuffer *rb,
                           GLenum internalFormat,
                           GLuint width, GLuint height)
{
   rb->Width = width;
   rb->Height = height;
   rb->InternalFormat = internalFormat;
   return GL_TRUE;
}



/**
 * Create a new intel_renderbuffer which corresponds to an on-screen window,
 * not a user-created renderbuffer.
 * \param width  the screen width
 * \param height  the screen height
 */
struct intel_renderbuffer *
intel_create_renderbuffer(GLenum intFormat, GLsizei width, GLsizei height,
                          int offset, int pitch, int cpp, void *map)
{
   GET_CURRENT_CONTEXT(ctx);
   struct intel_context *intel = intel_context(ctx);
   
   struct intel_renderbuffer *irb;
   const GLuint name = 0;

   irb = CALLOC_STRUCT(intel_renderbuffer);
   if (!irb) {
      _mesa_error(ctx, GL_OUT_OF_MEMORY, "creating renderbuffer");
      return NULL;
   }

   irb->Magic = MAGIC; /* XXX FBO temporary */

   _mesa_init_renderbuffer(&irb->Base, name);

   switch (intFormat) {
   case GL_RGB5:
      irb->Base._BaseFormat = GL_RGBA;
      irb->Base.RedBits = 5;
      irb->Base.GreenBits = 6;
      irb->Base.BlueBits = 5;
      irb->Base.DataType = GL_UNSIGNED_BYTE;
      cpp = 2;
      break;
   case GL_RGBA8:
      irb->Base._BaseFormat = GL_RGBA;
      irb->Base.RedBits = 8;
      irb->Base.GreenBits = 8;
      irb->Base.BlueBits = 8;
      irb->Base.AlphaBits = 8;
      irb->Base.DataType = GL_UNSIGNED_BYTE;
      cpp = 4;
      break;
   case GL_STENCIL_INDEX8_EXT:
      irb->Base._BaseFormat = GL_STENCIL_INDEX;
      irb->Base.StencilBits = 8;
      irb->Base.DataType = GL_UNSIGNED_BYTE;
      cpp = 1;
      break;
   case GL_DEPTH_COMPONENT16:
      irb->Base._BaseFormat = GL_DEPTH_COMPONENT;
      irb->Base.DepthBits = 16;
      irb->Base.DataType = GL_UNSIGNED_SHORT;
      cpp = 2;
      break;
   case GL_DEPTH_COMPONENT24:
      irb->Base._BaseFormat = GL_DEPTH_COMPONENT;
      irb->Base.DepthBits = 24;
      irb->Base.DataType = GL_UNSIGNED_INT;
      cpp = 4;
      break;
   case GL_DEPTH24_STENCIL8_EXT:
      irb->Base._BaseFormat = GL_DEPTH_STENCIL_EXT;
      irb->Base.DepthBits = 24;
      irb->Base.StencilBits = 8;
      irb->Base.DataType = GL_UNSIGNED_INT;
      cpp = 4;
      break;
   default:
      _mesa_problem(NULL, "Unexpected intFormat in intel_create_renderbuffer");
      return NULL;
   }

   irb->Base.InternalFormat = intFormat;

   /* intel-specific methods */
   irb->Base.Delete = intel_delete_renderbuffer;
   irb->Base.AllocStorage = intel_alloc_storage_window;
   irb->Base.GetPointer = intel_get_pointer;
   /* This sets the Get/PutRow/Value functions */
   intel_set_span_functions(&irb->Base);

   irb->pfMap = map;
   irb->pfPitch = pitch;

#if 00
   irb->region = intel_region_create_static(intel,
                                            DRM_MM_TT,
                                            offset,
                                            map,
                                            cpp,
                                            width, height);
#endif

   return irb;
}




/**
 * Create a new renderbuffer object.
 * Typically called via glBindRenderbufferEXT().
 */
static struct gl_renderbuffer *
intel_new_renderbuffer(GLcontext *ctx, GLuint name)
{
   /*struct intel_context *intel = intel_context(ctx);*/
   struct intel_renderbuffer *irb;

   irb = CALLOC_STRUCT(intel_renderbuffer);
   if (!irb) {
      _mesa_error(ctx, GL_OUT_OF_MEMORY, "creating renderbuffer");
      return NULL;
   }

   irb->Magic = MAGIC;

   _mesa_init_renderbuffer(&irb->Base, name);

   /* intel-specific methods */
   irb->Base.Delete = intel_delete_renderbuffer;
   irb->Base.AllocStorage = intel_alloc_storage;
   irb->Base.GetPointer = intel_get_pointer;

   return &irb->Base;
}


/**
 * Called via glBindFramebufferEXT().
 */
static void
intel_bind_framebuffer(GLcontext *ctx, GLenum target,
                       struct gl_framebuffer *fb)
{
   _mesa_debug(ctx, "%s %d\n", __FUNCTION__, fb->Name);

   if (target == GL_FRAMEBUFFER_EXT || target == GL_DRAW_FRAMEBUFFER_EXT) {
#if 00
      struct intel_context *intel = intel_context(ctx);
      struct gl_renderbuffer *rbColor, *rbDepth;
      struct intel_renderbuffer *irbColor, *irbDepth;
      struct intel_region *colorRegion, *depthRegion;

      /* XXX check that _ColorDrawBuffers[] is up to date? */
      rbColor = intel->ctx.DrawBuffer->_ColorDrawBuffers[0][0];
      rbDepth = intel->ctx.DrawBuffer->_DepthBuffer;

      irbColor = intel_renderbuffer(rbColor);
      irbDepth = intel_renderbuffer(rbDepth);

      if (irbColor && irbColor->region)
         colorRegion = irbColor->region;
      else
         colorRegion = NULL;

      if (irbDepth && irbDepth->region)
         depthRegion = irbDepth->region;
      else
         depthRegion = NULL;

      /* XXX FBO */
      intel->vtbl.set_draw_region(intel, colorRegion, depthRegion);
#else
      ctx->Driver.DrawBuffer(ctx, 0); /* second param is ignored */
      /* Integer depth range depends on depth buffer bits */
      ctx->Driver.DepthRange(ctx, ctx->Viewport.Near, ctx->Viewport.Far);
#endif
   }
   else {
      /* don't need to do anything if target == GL_READ_FRAMEBUFFER_EXT */
   }
}


/**
 * Called via glFramebufferRenderbufferEXT().
 */
static void
intel_framebuffer_renderbuffer(GLcontext *ctx, 
                               struct gl_framebuffer *fb,
                               GLenum attachment,
                               struct gl_renderbuffer *rb)
{
   _mesa_debug(ctx, "Intel FramebufferRenderbuffer %u %u\n",
               fb->Name, rb->Name);

   _mesa_framebuffer_renderbuffer(ctx, fb, attachment, rb);



}


static struct intel_renderbuffer *
intel_wrap_texture(GLcontext *ctx, struct gl_texture_image *texImage)
{
   const GLuint name = ~0; /* XXX OK? */
   struct intel_renderbuffer *irb;

   /* make an intel_renderbuffer to wrap the texture image */
   irb = CALLOC_STRUCT(intel_renderbuffer);
   if (!irb) {
      _mesa_error(ctx, GL_OUT_OF_MEMORY, "glFramebufferTexture");
      return NULL;
   }

   _mesa_init_renderbuffer(&irb->Base, name);
   irb->Magic = MAGIC; /* XXX FBO temporary */
   irb->Base.Width = texImage->Width;
   irb->Base.Height = texImage->Height;
   irb->Base.InternalFormat = texImage->InternalFormat; /* XXX fix? */
   irb->Base._BaseFormat = texImage->TexFormat->BaseFormat;
   irb->Base.DataType = GL_UNSIGNED_BYTE; /* FBO XXX fix */
   irb->Base.RedBits = texImage->TexFormat->RedBits;
   irb->Base.GreenBits = texImage->TexFormat->GreenBits;
   irb->Base.BlueBits = texImage->TexFormat->BlueBits;
   irb->Base.AlphaBits = texImage->TexFormat->AlphaBits;
   irb->Base.DepthBits = texImage->TexFormat->DepthBits;

   irb->Base.Delete = intel_delete_renderbuffer;
   /* XXX span funcs */

   return irb;
}


/**
 * Called via glFramebufferTexture[123]DEXT().
 */
static void
intel_renderbuffer_texture(GLcontext *ctx,
                           struct gl_framebuffer *fb,
                           struct gl_renderbuffer_attachment *att)
{
   struct gl_texture_image *newImage
      = att->Texture->Image[att->CubeMapFace][att->TextureLevel];

   struct intel_renderbuffer *irb
      = intel_renderbuffer(att->Renderbuffer);

   struct intel_texture_image *intel_image;

   (void) fb;

   ASSERT(newImage);

   if (!irb) {
      irb = intel_wrap_texture(ctx, newImage);
      if (!irb) {
         _mesa_error(ctx, GL_OUT_OF_MEMORY, "render to texture");
         return;
      }
      att->Renderbuffer = &irb->Base;
   }

   irb->Base.RefCount++;

   intel_image = intel_texture_image(newImage);

   intel_region_reference(&irb->region, intel_image->mt->region);

   if (newImage->TexFormat == &_mesa_texformat_argb8888) {
      _mesa_debug(ctx, "Render to texture OK\n");
   }
   else {
      _mesa_debug(ctx, "Render to texture BAD FORMAT\n");
   }

   ctx->Driver.DrawBuffer(ctx, 0); /* second param is ignored */


}


/**
 * Called by Mesa when rendering to a texture is done.
 */
static void
intel_finish_render_texture(GLcontext *ctx,
                           struct gl_renderbuffer_attachment *att)
{
   struct intel_context *intel = intel_context(ctx);
   struct intel_renderbuffer *irb
      = intel_renderbuffer(att->Renderbuffer);

   assert(irb);

   intel_region_release(intel, &irb->region);

   irb->Base.RefCount--;

   _mesa_debug(ctx, "intel_finish_render_texture, refcount=%d\n", irb->Base.RefCount);

   /* should never hit zero here */
   assert(irb->Base.RefCount > 0);

}


/**
 * Do one-time context initializations related to GL_EXT_framebuffer_object.
 */
void
intel_fbo_init( struct intel_context *intel )
{
   intel->ctx.Driver.NewFramebuffer = intel_new_framebuffer;
   intel->ctx.Driver.NewRenderbuffer = intel_new_renderbuffer;
   intel->ctx.Driver.BindFramebuffer = intel_bind_framebuffer;
   intel->ctx.Driver.FramebufferRenderbuffer = intel_framebuffer_renderbuffer;
   intel->ctx.Driver.RenderbufferTexture = intel_renderbuffer_texture;
   intel->ctx.Driver.FinishRenderTexture = intel_finish_render_texture;
}
