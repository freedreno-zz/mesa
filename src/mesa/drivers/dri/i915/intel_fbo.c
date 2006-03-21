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
#include "intel_buffers.h"
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
intel_alloc_renderbuffer_storage(GLcontext *ctx, struct gl_renderbuffer *rb,
                                 GLenum internalFormat,
                                 GLuint width, GLuint height)
{
   struct intel_context *intel = intel_context(ctx);
   struct intel_renderbuffer *irb = intel_renderbuffer(rb);
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

   switch (internalFormat) {
   case GL_R3_G3_B2:
   case GL_RGB4:
   case GL_RGB5:
      rb->InternalFormat = GL_RGB5;
      rb->DataType = GL_UNSIGNED_BYTE;
      rb->RedBits = 5;
      rb->GreenBits = 6;
      rb->BlueBits = 5;
      cpp = 2;
      break;
   case GL_RGB:
   case GL_RGB8:
   case GL_RGB10:
   case GL_RGB12:
   case GL_RGB16:
   case GL_RGBA:
   case GL_RGBA2:
   case GL_RGBA4:
   case GL_RGB5_A1:
   case GL_RGBA8:
   case GL_RGB10_A2:
   case GL_RGBA12:
   case GL_RGBA16:
      rb->InternalFormat = GL_RGBA8;
      rb->DataType = GL_UNSIGNED_BYTE;
      rb->RedBits = 8;
      rb->GreenBits = 8;
      rb->BlueBits = 8;
      rb->AlphaBits = 8;
      cpp = 4;
      break;
   case GL_STENCIL_INDEX:
   case GL_STENCIL_INDEX1_EXT:
   case GL_STENCIL_INDEX4_EXT:
   case GL_STENCIL_INDEX8_EXT:
   case GL_STENCIL_INDEX16_EXT:
      rb->InternalFormat = GL_STENCIL_INDEX8_EXT;
      rb->DataType = GL_UNSIGNED_BYTE;
      rb->StencilBits = 8;
      cpp = 1;
      softwareBuffer = GL_TRUE;
      /* XXX software buffer? */
      break;
   case GL_DEPTH_COMPONENT16:
      rb->InternalFormat = GL_DEPTH_COMPONENT16;
      rb->DataType = GL_UNSIGNED_SHORT;
      rb->DepthBits = 16;
      cpp = 2;
      break;
   case GL_DEPTH_COMPONENT:
   case GL_DEPTH_COMPONENT24:
   case GL_DEPTH_COMPONENT32:
      rb->InternalFormat = GL_DEPTH24_STENCIL8_EXT;
      rb->DataType = GL_UNSIGNED_INT_24_8_EXT;
      rb->DepthBits = 24;
      cpp = 4;
      break;
   case GL_DEPTH_STENCIL_EXT:
   case GL_DEPTH24_STENCIL8_EXT:
      rb->InternalFormat = GL_DEPTH24_STENCIL8_EXT;
      rb->DataType = GL_UNSIGNED_INT_24_8_EXT;
      rb->DepthBits = 24;
      rb->StencilBits = 8;
      cpp = 4;
      break;
   default:
      _mesa_problem(ctx, "Unexpected format in intel_alloc_renderbuffer_storage");
      return GL_FALSE;
   }

   intelFlush(ctx);

   /* free old region */
   if (irb->region) {
      /*LOCK_HARDWARE(intel);*/
      intel_region_release(intel, &irb->region);
      /*UNLOCK_HARDWARE(intel);*/
   }

   /* allocate new memory region/renderbuffer */
   if (softwareBuffer) {
      return _mesa_soft_renderbuffer_storage(ctx, rb, internalFormat,
                                             width, height);
   }
   else {
      /* alloc hardware renderbuffer */
      _mesa_debug(ctx, "Allocating %d x %d Intel RBO\n", width, height);
      /*LOCK_HARDWARE(intel);*/
      irb->region = intel_region_alloc(intel, cpp, width, height);
      /*UNLOCK_HARDWARE(intel);*/
      if (!irb->region)
         return GL_FALSE; /* out of memory? */

      rb->Width = width;
      rb->Height = height;

      /* This sets the Get/PutRow/Value functions */
      intel_set_span_functions(&irb->Base);

      return GL_TRUE;
   }
}



/**
 * Called for each hardware renderbuffer when a _window_ is resized.
 * Just update fields.
 * Not used for user-created renderbuffers!
 */
static GLboolean
intel_alloc_window_storage(GLcontext *ctx, struct gl_renderbuffer *rb,
                           GLenum internalFormat,
                           GLuint width, GLuint height)
{
   ASSERT(rb->Name == 0);
   rb->Width = width;
   rb->Height = height;
   rb->InternalFormat = internalFormat;
   return GL_TRUE;
}


static GLboolean
intel_nop_alloc_storage(GLcontext *ctx, struct gl_renderbuffer *rb,
                        GLenum internalFormat,
                        GLuint width, GLuint height)
{
   _mesa_problem(ctx, "intel_op_alloc_storage should never be called.");
   return GL_FALSE;
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
      irb->Base.DataType = GL_UNSIGNED_INT_24_8_EXT;
      cpp = 4;
      break;
   default:
      _mesa_problem(NULL, "Unexpected intFormat in intel_create_renderbuffer");
      return NULL;
   }

   irb->Base.InternalFormat = intFormat;

   /* intel-specific methods */
   irb->Base.Delete = intel_delete_renderbuffer;
   irb->Base.AllocStorage = intel_alloc_window_storage;
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
   irb->Base.AllocStorage = intel_alloc_renderbuffer_storage;
   irb->Base.GetPointer = intel_get_pointer;
   /* span routines set in alloc_storage function */

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
      intel_draw_buffer(ctx, fb);
      /* Integer depth range depends on depth buffer bits */
      ctx->Driver.DepthRange(ctx, ctx->Viewport.Near, ctx->Viewport.Far);
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
   intel_draw_buffer(ctx, fb);
}


/**
 * When glFramebufferTexture[123]D is called this function sets up the
 * gl_renderbuffer wrapp around the texture image.
 * This will have the region info needed for hardware rendering.
 */
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

   if (texImage->TexFormat == &_mesa_texformat_argb8888) {
      irb->Base.InternalFormat = GL_RGBA8;
      irb->Base._BaseFormat = GL_RGBA;
      _mesa_debug(ctx, "Render to RGBA8 texture OK\n");
   }
   else if (texImage->TexFormat == &_mesa_texformat_rgb565) {
      irb->Base.InternalFormat = GL_RGB5;
      irb->Base._BaseFormat = GL_RGB;
      _mesa_debug(ctx, "Render to RGB5 texture OK\n");
   }
   else if (texImage->TexFormat == &_mesa_texformat_depth_component16) {
      irb->Base.InternalFormat = GL_DEPTH_COMPONENT16;
      irb->Base._BaseFormat = GL_DEPTH_COMPONENT;
      _mesa_debug(ctx, "Render to DEPTH16 texture OK\n");
   }
   else {
      _mesa_debug(ctx, "Render to texture BAD FORMAT\n");
      /* XXX will need to use software rendering! */
   }

   irb->Base.Width = texImage->Width;
   irb->Base.Height = texImage->Height;
   irb->Base.DataType = GL_UNSIGNED_BYTE; /* FBO XXX fix */
   irb->Base.RedBits = texImage->TexFormat->RedBits;
   irb->Base.GreenBits = texImage->TexFormat->GreenBits;
   irb->Base.BlueBits = texImage->TexFormat->BlueBits;
   irb->Base.AlphaBits = texImage->TexFormat->AlphaBits;
   irb->Base.DepthBits = texImage->TexFormat->DepthBits;

   irb->Base.Delete = intel_delete_renderbuffer;
   irb->Base.AllocStorage = intel_nop_alloc_storage;
   intel_set_span_functions(&irb->Base);

   return irb;
}


/**
 * Called via glFramebufferTexture[123]DEXT() to prepare for rendering
 * into texture memory.
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

   /* hook into the region */
   /* XXX mipmap level / cube face */
   intel_image = intel_texture_image(newImage);
   intel_region_reference(&irb->region, intel_image->mt->region);

   intel_draw_buffer(ctx, fb);
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

   _mesa_debug(ctx, "intel_finish_render_texture, refcount=%d\n",
               irb->Base.RefCount);

   /* should never hit zero here */
   assert(irb->Base.RefCount > 0);
}


/**
 * Do one-time context initializations related to GL_EXT_framebuffer_object.
 * Hook in device driver functions.
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
