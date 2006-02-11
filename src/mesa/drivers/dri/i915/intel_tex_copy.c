/**************************************************************************
 * 
 * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.
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

#include "mtypes.h"
#include "enums.h"
#include "teximage.h"
#include "swrast/swrast.h"

#include "intel_screen.h"
#include "intel_context.h"
#include "intel_batchbuffer.h"
#include "intel_mipmap_tree.h"
#include "intel_regions.h"
#include "intel_tex.h"
#include "intel_blit.h"
#include "bufmgr.h"

/* Do the best we can using the blitter.  A future project is to use
 * the texture engine and fragment programs for these copies.
 */

static struct intel_region *get_teximage_source( struct intel_context *intel,
						 GLenum internalFormat )
{
   if (0)
      _mesa_printf("%s %s\n", __FUNCTION__, 
		   _mesa_lookup_enum_by_nr(internalFormat));

   switch (internalFormat) {
   case GL_DEPTH_COMPONENT:
   case GL_DEPTH_COMPONENT16_ARB:
      if (intel->intelScreen->cpp == 2)
	 return intel->depth_region;
      return NULL;
   case GL_DEPTH24_STENCIL8_EXT:
   case GL_DEPTH_STENCIL_EXT:
      if (intel->intelScreen->cpp == 4)
	 return intel->depth_region;
      return NULL;
   case GL_RGBA:
      return intel_readbuf_region( intel );
   case GL_RGB:
      if (intel->intelScreen->cpp == 2)
	 return intel_readbuf_region( intel );
      return NULL;
   default:
      return NULL;
   }
}

static GLboolean check_copytex_fragment_ops( const GLcontext *ctx )
{
   return GL_TRUE;

   return !(ctx->Color.AlphaEnabled || 
/* 	    ctx->Depth.Test || */
	    ctx->Fog.Enabled ||
/* 	    ctx->Scissor.Enabled || */
	    ctx->Stencil.Enabled ||
	    !ctx->Color.ColorMask[0] ||
	    !ctx->Color.ColorMask[1] ||
	    !ctx->Color.ColorMask[2] ||
	    !ctx->Color.ColorMask[3] ||
	    ctx->Color.ColorLogicOpEnabled ||
	    ctx->Texture._EnabledUnits);
}


static GLboolean do_copy_texsubimage( struct intel_context *intel,
				      struct intel_texture_image *intelImage,
				      GLenum internalFormat,
				      GLint dstx, GLint dsty,
				      GLint x, GLint y,
				      GLsizei width, GLsizei height )
{
   GLcontext *ctx = &intel->ctx;
   struct intel_region *src = get_teximage_source(intel, internalFormat);
   GLuint ret = GL_TRUE;

   if (!intelImage->mt || !src)
      return GL_FALSE;
 
   if (!check_copytex_fragment_ops( ctx ))
      return GL_FALSE;
 

   LOCK_HARDWARE(intel);
   intelInstallBatchBuffer(intel);
   {
      __DRIdrawablePrivate *dPriv = intel->driDrawable;
      GLuint image_offset = intel_miptree_image_offset(intelImage->mt, 
						       intelImage->face,
						       intelImage->level);
      GLuint dst_offset = 0;
      GLuint src_offset = 0;
      GLint orig_x = x;
      GLint orig_y = y;

      if (!intel_clip_to_framebuffer(ctx, ctx->DrawBuffer, &x, &y, &width, &height)) {
	 ret = GL_TRUE;
	 goto out;
      }

      /* Update dst for clipped src.  Need to also clip the source rect.
       */
      dstx = x - orig_x;
      dsty = y - orig_y;

      y = dPriv->h - y - height; 	/* convert from gl to hardware coords */
      x += dPriv->x;
      y += dPriv->y;


      bmAddBuffer(intel->buffer_list, 
		  intelImage->mt->region->buffer, 
		  BM_WRITE, NULL, &dst_offset);

      bmAddBuffer(intel->buffer_list, 
		  src->buffer, 
		  BM_READ, NULL, &src_offset);

      if (!bmValidateBufferList(intel->bm, intel->buffer_list, BM_MEM_AGP)) {
	 ret = GL_FALSE;
	 goto out;
      }
      
      intelEmitCopyBlitLocked( intel,
			       intelImage->mt->cpp,
			       src->pitch, src_offset,
			       intelImage->mt->pitch, 
			       dst_offset + image_offset,
			       x, y, 
			       dstx, dsty,
			       width, height );
   out:
      intelFlushBatchLocked( intel, GL_TRUE, GL_FALSE, GL_FALSE);
   }
   

   UNLOCK_HARDWARE(intel);
   if (!ret)
      return GL_FALSE;

#if 0
   /* GL_SGIS_generate_mipmap -- this can be accelerated now.
    */
   if (level == texObj->BaseLevel && 
       texObj->GenerateMipmap) {
      intel_generate_mipmap(ctx, target,
                            &ctx->Texture.Unit[ctx->Texture.CurrentUnit],
                            texObj);
   }
#endif

   return GL_TRUE;
}





void intelCopyTexImage1D( GLcontext *ctx, GLenum target, GLint level,
			  GLenum internalFormat,
			  GLint x, GLint y, GLsizei width,
			  GLint border )
{
   struct gl_texture_unit *texUnit = &ctx->Texture.Unit[ctx->Texture.CurrentUnit];
   struct gl_texture_object *texObj = _mesa_select_tex_object(ctx, texUnit, target);
   struct gl_texture_image *texImage = _mesa_select_tex_image(ctx, texUnit, target, level);

   if (border)
      goto fail;

   /* Setup or redefine the texture object, mipmap tree and texture
    * image.  Don't populate yet.  
    */
   ctx->Driver.TexImage1D(ctx, target, level, internalFormat,
			  width, border,
			  GL_RGBA, CHAN_TYPE, NULL,
			  &ctx->DefaultPacking, texObj, texImage);

   if (!do_copy_texsubimage(intel_context(ctx), 
			    intel_texture_image(texImage),
			    internalFormat,
			    0, 0,
			    x, y, 
			    width, 1))
       goto fail;

   return;

 fail:
   _swrast_copy_teximage1d( ctx, target, level, internalFormat, x, y,
			    width, border );
}

void intelCopyTexImage2D( GLcontext *ctx, GLenum target, GLint level,
			  GLenum internalFormat,
			  GLint x, GLint y, GLsizei width, GLsizei height,
			  GLint border )
{
   struct gl_texture_unit *texUnit = &ctx->Texture.Unit[ctx->Texture.CurrentUnit];
   struct gl_texture_object *texObj = _mesa_select_tex_object(ctx, texUnit, target);
   struct gl_texture_image *texImage = _mesa_select_tex_image(ctx, texUnit, target, level);

   if (border)
      goto fail;

   /* Setup or redefine the texture object, mipmap tree and texture
    * image.  Don't populate yet.  
    */
   ctx->Driver.TexImage2D(ctx, target, level, internalFormat,
			  width, height, border,
			  GL_RGBA, CHAN_TYPE, NULL,
			  &ctx->DefaultPacking, texObj, texImage);


   if (!do_copy_texsubimage(intel_context(ctx), 
			    intel_texture_image(texImage),
			    internalFormat,
			    0, 0,
			    x, y, 
			    width, height))
       goto fail;

   return;

 fail:
   _swrast_copy_teximage2d( ctx, target, level, internalFormat, x, y,
			    width, height, border );
}


void intelCopyTexSubImage1D( GLcontext *ctx, GLenum target, GLint level,
			     GLint xoffset,
			     GLint x, GLint y, GLsizei width )
{
   struct gl_texture_unit *texUnit = &ctx->Texture.Unit[ctx->Texture.CurrentUnit];
   struct gl_texture_image *texImage = _mesa_select_tex_image(ctx, texUnit, target, level);
   GLenum internalFormat = texImage->InternalFormat;

   /* Need to check texture is compatible with source format. 
    */

   if (!do_copy_texsubimage(intel_context(ctx), 
			    intel_texture_image(texImage),
			    internalFormat,
			    xoffset, 0,
			    x, y, width, 1)) {
      _swrast_copy_texsubimage1d( ctx, target, level, 
				  xoffset, x, y, width );
   }
}



void intelCopyTexSubImage2D( GLcontext *ctx, GLenum target, GLint level,
			     GLint xoffset, GLint yoffset,
			     GLint x, GLint y, GLsizei width, GLsizei height )
{
   struct gl_texture_unit *texUnit = &ctx->Texture.Unit[ctx->Texture.CurrentUnit];
   struct gl_texture_image *texImage = _mesa_select_tex_image(ctx, texUnit, target, level);
   GLenum internalFormat = texImage->InternalFormat;


   /* Need to check texture is compatible with source format. 
    */

   if (!do_copy_texsubimage(intel_context(ctx), 
			    intel_texture_image(texImage),
			    internalFormat,
			    xoffset, yoffset,
			    x, y, width, height)) {
      _swrast_copy_texsubimage2d( ctx, target, level,
				  xoffset, yoffset,
				  x, y, width, height );
   }
}
