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

#include "glheader.h"
#include "enums.h"
#include "mtypes.h"
#include "macros.h"
#include "swrast/swrast.h"

#include "intel_screen.h"
#include "intel_context.h"
#include "intel_ioctl.h"
#include "intel_batchbuffer.h"
#include "intel_blit.h"
#include "intel_regions.h"
#include "intel_pixel.h"
#include "bufmgr.h"




static GLboolean do_texture_copypixels( GLcontext *ctx,
					GLint srcx, GLint srcy, 
					GLsizei width, GLsizei height,
					GLint dstx, GLint dsty, 
					GLenum type )
{
   return GL_FALSE;
}


/**
 * CopyPixels with the blitter.  Don't support zooming, pixel transfer, etc.
 */
static GLboolean do_blit_copypixels( GLcontext *ctx,
				     GLint srcx, GLint srcy, 
				     GLsizei width, GLsizei height,
				     GLint dstx, GLint dsty, 
				     GLenum type )
{
   struct intel_context *intel = intel_context( ctx );
   struct intel_region *dst = intel_drawbuf_region( intel );
   struct intel_region *src = NULL;

   /* Copypixels can be more than a straight copy.  Ensure all the
    * extra operations are disabled:
    */
   if (!intel_check_color_per_fragment_ops(ctx) ||
       ctx->Pixel.ZoomX != 1.0F || 
       ctx->Pixel.ZoomY != 1.0F)
      return GL_FALSE;

   switch (type) {
   case GL_COLOR:
      src = intel_readbuf_region( intel );
      break;
   case GL_DEPTH:
      /* Don't think this is really possible execpt at 16bpp, when we have no stencil.
       */
      if (intel->intelScreen->cpp == 2)
	 src = intel->depth_region;
      break;
   case GL_STENCIL:
      /* Don't think this is really possible. 
       */
      break;
   case GL_DEPTH_STENCIL_EXT:
      /* Does it matter whether it is stencil/depth or depth/stencil?
       */
      src = intel->depth_region;
      break;
   default:
      break;
   }

   if (!src || !dst) 
      return GL_FALSE;



   intelFlush( &intel->ctx );
   LOCK_HARDWARE( intel );
   {
      __DRIdrawablePrivate *dPriv = intel->driDrawable;
      drm_clip_rect_t *box = dPriv->pClipRects;
      GLint nbox = dPriv->numClipRects;
      GLint delta_x = srcx - dstx;
      GLint delta_y = srcy - dsty;
      GLuint i;

      if (!intel_clip_to_framebuffer(ctx, ctx->DrawBuffer, &dstx, &dsty, &width, &height)) 
	 goto out;

      /* Update source for clipped dest.  Need to also clip the source rect.
       */
      srcx = dstx + delta_x;
      srcy = dsty + delta_y;

      if (!intel_clip_to_framebuffer(ctx, ctx->DrawBuffer, &srcx, &srcy, &width, &height)) 
	 goto out;

      /* Update dest for clipped source:
       */
      dstx = srcx - delta_x;
      dsty = srcy - delta_y;


      srcy = dPriv->h - srcy - height; 	/* convert from gl to hardware coords */
      dsty = dPriv->h - dsty - height; 	/* convert from gl to hardware coords */
      srcx += dPriv->x;
      dstx += dPriv->x;
      srcy += dPriv->y;
      dsty += dPriv->y;


      /* Could do slightly more clipping: Eg, take the intersection of
       * the existing set of cliprects and those cliprects translated
       * by delta_x, delta_y:
       * 
       * This code will not overwrite other windows, but will
       * introduce garbage when copying from obscured window regions.
       */
      for (i = 0 ; i < nbox ; i++ )
      {
	 GLint bx = box[i].x1;
	 GLint by = box[i].y1;
	 GLint bw = box[i].x2 - bx;
	 GLint bh = box[i].y2 - by;

	 if (bx < dstx) bw -= dstx - bx, bx = dstx;
	 if (by < dsty) bh -= dsty - by, by = dsty;
	 if (bx + bw > dstx + width) bw = dstx + width - bx;
	 if (by + bh > dsty + height) bh = dsty + height - by;
	 if (bw <= 0) continue;
	 if (bh <= 0) continue;

	 intelEmitCopyBlit( intel,
			    dst->cpp,
			    src->pitch, src->buffer, 0,
			    dst->pitch, dst->buffer, 0,
			    bx + delta_x, by - delta_y, /* srcx, srcy */
			    bx, by, /* dstx, dsty */
			    bw, bh );
      }
   }
 out:
   intel_batchbuffer_flush( intel->batch );
   UNLOCK_HARDWARE( intel );
   return GL_TRUE;
}


void intelCopyPixels( GLcontext *ctx,
		      GLint srcx, GLint srcy, 
		      GLsizei width, GLsizei height,
		      GLint destx, GLint desty, 
		      GLenum type )
{
   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   if (do_blit_copypixels( ctx, srcx, srcy, width, height, destx, desty, type))
      return;

   if (do_texture_copypixels( ctx, srcx, srcy, width, height, destx, desty, type))
      return;

   _mesa_printf("fallback to _swrast_CopyPixels\n");
   _swrast_CopyPixels( ctx, srcx, srcy, width, height, destx, desty, type);
}


