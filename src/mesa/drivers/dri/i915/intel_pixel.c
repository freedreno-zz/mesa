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
 * next paragraph) shall be included in all copies or substantial portionsalloc
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

#include "swrast/swrast.h"

#include "intel_context.h"
#include "intel_pixel.h"
#include "intel_regions.h"


GLboolean intel_check_blit_fragment_ops( const GLcontext *ctx )
{
   return !(ctx->Color.AlphaEnabled || 
	    ctx->Depth.Test ||
	    ctx->Fog.Enabled ||
	    ctx->Scissor.Enabled ||
	    ctx->Stencil.Enabled ||
	    !ctx->Color.ColorMask[0] ||
	    !ctx->Color.ColorMask[1] ||
	    !ctx->Color.ColorMask[2] ||
	    !ctx->Color.ColorMask[3] ||
	    ctx->Color.ColorLogicOpEnabled ||
	    ctx->Texture._EnabledUnits);
}

/* The intel_region struct doesn't really do enough to capture the
 * format of the pixels in the region.  For now this code assumes that
 * the region is a display surface and hence is either ARGB8888 or
 * RGB565.
 */
GLboolean intel_check_blit_format( struct intel_region *region,
				   GLenum type, GLenum format )
{
   if (region->cpp == 4 &&
       type == GL_UNSIGNED_INT_8_8_8_8_REV &&        
       format == GL_BGRA ) {
      return GL_TRUE;
   }
   
   if (region->cpp == 2 && 
       type == GL_UNSIGNED_SHORT_5_6_5_REV && 
       format == GL_BGR ) {
      return GL_TRUE;
   }
   
   fprintf(stderr, "%s: request doesn't match pixel format\n", __FUNCTION__);
   return GL_FALSE;
}


GLboolean intel_clip_to_framebuffer( GLcontext *ctx,
				     const GLframebuffer *buffer,
				     GLint *x, GLint *y,
				     GLsizei *width, GLsizei *height )
{
   /* left clipping */
   if (*x < buffer->_Xmin) {
      *width -= (buffer->_Xmin - *x);
      *x = buffer->_Xmin;
   }

   /* right clipping */
   if (*x + *width > buffer->_Xmax)
      *width -= (*x + *width - buffer->_Xmax - 1);

   if (*width <= 0)
      return GL_FALSE;

   /* bottom clipping */
   if (*y < buffer->_Ymin) {
      *height -= (buffer->_Ymin - *y);
      *y = buffer->_Ymin;
   }

   /* top clipping */
   if (*y + *height > buffer->_Ymax)
      *height -= (*y + *height - buffer->_Ymax - 1);

   if (*height <= 0)
      return GL_FALSE;

   return GL_TRUE;
}



GLboolean intel_clip_to_drawable( GLcontext *ctx,
				  const __DRIdrawablePrivate *dPriv,
				  GLint *x, GLint *y,
				  GLsizei *width, GLsizei *height )
{
   /* left clipping */
   if (*x < dPriv->x) {
      *width -= (dPriv->x - *x);
      *x = dPriv->x;
   }

   /* right clipping */
   if (*x + *width > dPriv->x + dPriv->w)
      *width -= (*x + *width) - (dPriv->x + dPriv->w);

   if (*width <= 0)
      return GL_FALSE;

   /* bottom clipping */
   if (*y < dPriv->y) {
      *height -= (dPriv->y - *y);
      *y = dPriv->y;
   }

   /* top clipping */
   if (*y + *height > dPriv->y + dPriv->h)
      *height -= (*y + *height) - (dPriv->y + dPriv->w);

   if (*height <= 0)
      return GL_FALSE;

   return GL_TRUE;
}


GLboolean intel_clip_to_region( GLcontext *ctx,
				const struct intel_region *region,
				GLint *x, GLint *y,
				GLsizei *width, GLsizei *height )
{
   /* left clipping */
   if (*x < 0) {
      *width -= (0 - *x);
      *x = 0;
   }

   /* right clipping */
   if (*x + *width > region->pitch)
      *width -= (*x + *width) - region->pitch;

   if (*width <= 0)
      return GL_FALSE;

   /* bottom clipping */
   if (*y < 0) {
      *height -= (0 - *y);
      *y = 0;
   }

   /* top clipping */
   if (*y + *height > region->height)
      *height -= (*y + *height) - region->height;

   if (*height <= 0)
      return GL_FALSE;

   return GL_TRUE;
}




void intelInitPixelFuncs( struct dd_function_table *functions )
{
   functions->Accum = _swrast_Accum;
   functions->Bitmap = _swrast_Bitmap;
   functions->CopyPixels = intelCopyPixels;
   functions->ReadPixels = intelReadPixels;  
   functions->DrawPixels = intelDrawPixels; 
}

