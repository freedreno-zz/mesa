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
#include "bufmgr.h"

static GLboolean
check_color( GLcontext *ctx, GLenum type, GLenum format,
	     const struct gl_pixelstore_attrib *packing,
	     const void *pixels, GLint sz, GLint pitch )
{
   intelContextPtr intel = INTEL_CONTEXT(ctx);
   GLuint cpp = intel->intelScreen->cpp;

   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   if (	(pitch & 63) ||
	ctx->_ImageTransferState ||
	packing->SwapBytes ||
	packing->LsbFirst) {
      if (INTEL_DEBUG & DEBUG_PIXEL)
	 fprintf(stderr, "%s: failed 1\n", __FUNCTION__);
      return GL_FALSE;
   }

   if ( type == GL_UNSIGNED_INT_8_8_8_8_REV && 
	cpp == 4 && 
	format == GL_BGRA ) {
      if (INTEL_DEBUG & DEBUG_PIXEL)
	 fprintf(stderr, "%s: passed 2\n", __FUNCTION__);
      return GL_TRUE;
   }

   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s: failed\n", __FUNCTION__);

   return GL_FALSE;
}

GLboolean intel_check_color_per_fragment_ops( const GLcontext *ctx )
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

static GLboolean
intelTryReadPixels( GLcontext *ctx,
		  GLint x, GLint y, GLsizei width, GLsizei height,
		  GLenum format, GLenum type,
		  const struct gl_pixelstore_attrib *pack,
		  GLvoid *pixels )
{
   intelContextPtr intel = INTEL_CONTEXT(ctx);
   GLint size = 0;
   GLint pitch = pack->RowLength ? pack->RowLength : width;

   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   /* Only accelerate reading to agp buffers.
    */
   if ( 1 ) {
      if (INTEL_DEBUG & DEBUG_PIXEL)
	 fprintf(stderr, "%s: dest not agp\n", __FUNCTION__);
      return GL_FALSE;
   }

   /* Need GL_PACK_INVERT_MESA to cope with upsidedown results from
    * blitter:
    */
   if (!pack->Invert) {
      if (INTEL_DEBUG & DEBUG_PIXEL)
	 fprintf(stderr, "%s: MESA_PACK_INVERT not set\n", __FUNCTION__);
      return GL_FALSE;
   }

   if (!check_color(ctx, type, format, pack, pixels, size, pitch))
      return GL_FALSE;

   switch ( intel->intelScreen->cpp ) {
   case 4:
      break;
   default:
      return GL_FALSE;
   }


   /* Although the blits go on the command buffer, need to do this and
    * fire with lock held to guarentee cliprects and drawOffset are
    * correct.
    *
    * This is an unusual situation however, as the code which flushes
    * a full command buffer expects to be called unlocked.  As a
    * workaround, immediately flush the buffer on aquiring the lock.
    */
   intelFlush( &intel->ctx );
   LOCK_HARDWARE( intel );
   {
      __DRIdrawablePrivate *dPriv = intel->driDrawable;
      int nbox = dPriv->numClipRects;
      int src_offset = intel->drawOffset;
      int src_pitch = intel->intelScreen->front.pitch;
      int dst_offset = 0;
      drm_clip_rect_t *box = dPriv->pClipRects;
      int i;

      if (!intel_clip_to_framebuffer(ctx, ctx->ReadBuffer, &x, &y, &width, &height)) {
	 UNLOCK_HARDWARE( intel );
	 if (INTEL_DEBUG & DEBUG_PIXEL)
	    fprintf(stderr, "%s totally clipped -- nothing to do\n",
		    __FUNCTION__);
	 return GL_TRUE;
      }


      y = dPriv->h - y - height;
      x += dPriv->x;
      y += dPriv->y;


      if (INTEL_DEBUG & DEBUG_PIXEL)
	 fprintf(stderr, "readpixel blit src_pitch %d dst_pitch %d\n",
		 src_pitch, pitch);

      for (i = 0 ; i < nbox ; i++)
      {
	 GLint bx = box[i].x1;
	 GLint by = box[i].y1;
	 GLint bw = box[i].x2 - bx;
	 GLint bh = box[i].y2 - by;
	 
	 if (bx < x) bw -= x - bx, bx = x;
	 if (by < y) bh -= y - by, by = y;
	 if (bx + bw > x + width) bw = x + width - bx;
	 if (by + bh > y + height) bh = y + height - by;
	 if (bw <= 0) continue;
	 if (bh <= 0) continue;

	 intelEmitCopyBlitLocked( intel,
			    intel->intelScreen->cpp,
			    src_pitch, src_offset,
			    pitch, dst_offset,
			    bx, by,
			    bx - x, by - y,
			    bw, bh );
      }
   }
   UNLOCK_HARDWARE( intel );
   intelFinish( &intel->ctx );

   return GL_TRUE;
}

static void
intelReadPixels( GLcontext *ctx,
		 GLint x, GLint y, GLsizei width, GLsizei height,
		 GLenum format, GLenum type,
		 const struct gl_pixelstore_attrib *pack,
		 GLvoid *pixels )
{
   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   if (!intelTryReadPixels( ctx, x, y, width, height, format, type, pack, 
			   pixels))
      _swrast_ReadPixels( ctx, x, y, width, height, format, type, pack, 
			  pixels);
}




static void do_draw_pix( GLcontext *ctx,
			 GLint x, GLint y, GLsizei width, GLsizei height,
			 GLint pitch,
			 const void *pixels,
			 GLuint dest )
{
   intelContextPtr intel = INTEL_CONTEXT(ctx);
   __DRIdrawablePrivate *dPriv = intel->driDrawable;
   drm_clip_rect_t *box = dPriv->pClipRects;
   int nbox = dPriv->numClipRects;
   int i;
   int src_offset = 0;
   int src_pitch = pitch;

   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   intelFlush( &intel->ctx );
   LOCK_HARDWARE( intel );
   if (ctx->DrawBuffer)
   {
      y -= height;			/* cope with pixel zoom */
   
      if (!intel_clip_to_framebuffer(ctx, ctx->DrawBuffer,
			  &x, &y, &width, &height)) {
	 UNLOCK_HARDWARE( intel );
	 return;
      }

      y = dPriv->h - y - height; 	/* convert from gl to hardware coords */
      x += dPriv->x;
      y += dPriv->y;


      for (i = 0 ; i < nbox ; i++ )
      {
	 GLint bx = box[i].x1;
	 GLint by = box[i].y1;
	 GLint bw = box[i].x2 - bx;
	 GLint bh = box[i].y2 - by;

	 if (bx < x) bw -= x - bx, bx = x;
	 if (by < y) bh -= y - by, by = y;
	 if (bx + bw > x + width) bw = x + width - bx;
	 if (by + bh > y + height) bh = y + height - by;
	 if (bw <= 0) continue;
	 if (bh <= 0) continue;

	 intelEmitCopyBlitLocked( intel,
			    intel->intelScreen->cpp,
			    src_pitch, src_offset,
			    intel->intelScreen->front.pitch,
			      intel->drawOffset,
			    bx - x, by - y,
			    bx, by,
			    bw, bh );
      }
   }
   UNLOCK_HARDWARE( intel );
   intelFinish( &intel->ctx );
}




static GLboolean
intelTryDrawPixels( GLcontext *ctx,
		  GLint x, GLint y, GLsizei width, GLsizei height,
		  GLenum format, GLenum type,
		  const struct gl_pixelstore_attrib *unpack,
		  const GLvoid *pixels )
{
   intelContextPtr intel = INTEL_CONTEXT(ctx);
   GLint pitch = unpack->RowLength ? unpack->RowLength : width;
   GLuint dest;
   GLuint cpp = intel->intelScreen->cpp;
   GLint size = width * pitch * cpp;

   /* XXX: Need to adjust pixels pointer for unpack->skip pixels/rows
    * offsets.
    */

   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   switch (format) {
   case GL_RGB:
   case GL_RGBA:
   case GL_BGRA:
      dest = intel->drawOffset;

      /* Planemask doesn't have full support in blits.
       */
      if (!ctx->Color.ColorMask[RCOMP] ||
	  !ctx->Color.ColorMask[GCOMP] ||
	  !ctx->Color.ColorMask[BCOMP] ||
	  !ctx->Color.ColorMask[ACOMP]) {
	 if (INTEL_DEBUG & DEBUG_PIXEL)
	    fprintf(stderr, "%s: planemask\n", __FUNCTION__);
	 return GL_FALSE;	
      }

      /* Can't do conversions on agp reads/draws. 
       */
      if ( 1 ) {
	 if (INTEL_DEBUG & DEBUG_PIXEL)
	    fprintf(stderr, "%s: not agp memory\n", __FUNCTION__);
	 return GL_FALSE;
      }

      if (!check_color(ctx, type, format, unpack, pixels, size, pitch)) {
	 return GL_FALSE;
      }
      if (!intel_check_color_per_fragment_ops(ctx)) {
	 return GL_FALSE;
      }
      if (!ctx->Current.RasterPosValid)
	 return GL_FALSE;

      if (ctx->Pixel.ZoomX != 1.0F ||
	  ctx->Pixel.ZoomY != -1.0F)
	 return GL_FALSE;
      break;

   default:
      return GL_FALSE;
   }

   if ( 0 )
   {
      do_draw_pix( ctx, x, y, width, height, pitch, pixels,
		   dest );
      return GL_TRUE;
   }
   else if (0)
   {
      /* Pixels is in regular memory -- get dma buffers and perform
       * upload through them.  No point doing this for regular uploads
       * but once we remove some of the restrictions above (colormask,
       * pixelformat conversion, zoom?, etc), this could be a win.
       */
   }
   else
      return GL_FALSE;
}

static void
intelDrawPixels( GLcontext *ctx,
		 GLint x, GLint y, GLsizei width, GLsizei height,
		 GLenum format, GLenum type,
		 const struct gl_pixelstore_attrib *unpack,
		 const GLvoid *pixels )
{
   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   if (!intelTryDrawPixels( ctx, x, y, width, height, format, type,
			  unpack, pixels ))
      _swrast_DrawPixels( ctx, x, y, width, height, format, type,
			  unpack, pixels );
}


struct intel_region *intel_drawbuf_region( struct intel_context *intel )
{
   switch (intel->ctx.DrawBuffer->_ColorDrawBufferMask[0]) {
   case BUFFER_BIT_FRONT_LEFT:
      return intel->front_region;
   case BUFFER_BIT_BACK_LEFT:
      return intel->back_region;
   default:
      /* Not necessary to fallback - could handle either NONE or
       * FRONT_AND_BACK cases below.
       */
      return NULL;		
   }
}

struct intel_region *intel_readbuf_region( struct intel_context *intel )
{
   GLcontext *ctx = &intel->ctx;

   /* This will have to change to support EXT_fbo's, but is correct
    * for now:
    */
   switch (ctx->ReadBuffer->_ColorReadBufferIndex) {
   case BUFFER_FRONT_LEFT:
      return intel->front_region;
   case BUFFER_BACK_LEFT:
      return intel->back_region;
   default:
      assert(0);
      return NULL;
   }
}






/**
 * Implement glCopyPixels for the front color buffer (or back buffer Pixmap)
 * for the color buffer.  Don't support zooming, pixel transfer, etc.
 * We do support copying from one window to another, ala glXMakeCurrentRead.
 */
static GLboolean intelTryCopyPixels( GLcontext *ctx,
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
       ctx->_ImageTransferState ||
       ctx->Pixel.ZoomX != 1.0F || 
       ctx->Pixel.ZoomY != 1.0F)
      return GL_FALSE;

   switch (type) {
   case GL_COLOR:
      src = intel_readbuf_region( intel );
      /* No readbuffer, copypixels is a noop: 
       */
      if (!src)
	 return GL_TRUE;
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
   intelInstallBatchBuffer( intel );
   {
      __DRIdrawablePrivate *dPriv = intel->driDrawable;
      drm_clip_rect_t *box = dPriv->pClipRects;
      GLint nbox = dPriv->numClipRects;
      GLint delta_x = srcx - dstx;
      GLint delta_y = srcy - dsty;
      GLuint dst_offset = 0;
      GLuint src_offset = 0;
      GLuint i;

#if 0
      dsty -= height;			/* cope with pixel zoom */
      srcy -= height;			/* cope with pixel zoom */
#endif
      if (!ctx->DrawBuffer)
	 goto out;

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


      bmAddBuffer(intel->buffer_list, dst->buffer, BM_NO_EVICT|BM_NO_UPLOAD|BM_WRITE, 
		  NULL, &dst_offset);
      bmAddBuffer(intel->buffer_list, src->buffer, BM_NO_EVICT|BM_NO_UPLOAD|BM_READ, 
		  NULL, &src_offset);

      if (!bmValidateBufferList(intel->bm, intel->buffer_list, BM_MEM_AGP)) 
	 goto out;
      
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

	 assert(dst_offset == intel->drawOffset);

	 intelEmitCopyBlitLocked( intel,
				  dst->cpp,
				  src->pitch, src_offset,
				  dst->pitch, dst_offset,
				  bx + delta_x, by - delta_y, /* srcx, srcy */
				  bx, by, /* dstx, dsty */
				  bw, bh );
      }
   }
 out:
   intelFlushBatchLocked( intel, GL_TRUE, GL_FALSE, GL_FALSE);
   UNLOCK_HARDWARE( intel );
   return GL_TRUE;
}


static void
intelCopyPixels( GLcontext *ctx,
		 GLint srcx, GLint srcy, GLsizei width, GLsizei height,
		 GLint destx, GLint desty, GLenum type )
{
   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   if (!intelTryCopyPixels( ctx, srcx, srcy, width, height, destx, desty, type)) {
/*       if (INTEL_DEBUG & DEBUG_FALLBACKS) */
	 _mesa_printf("fallback to _swrast_CopyPixels\n");
      _swrast_CopyPixels( ctx, srcx, srcy, width, height, destx, desty, type);
   }
}



void intelInitPixelFuncs( struct dd_function_table *functions )
{
   /* Pixel path fallbacks.
    */
   functions->Accum = _swrast_Accum;
   functions->Bitmap = _swrast_Bitmap;

   if (getenv("INTEL_NO_BLITS") == 0) {
      functions->CopyPixels = intelCopyPixels;
      functions->ReadPixels = intelReadPixels;  
      functions->DrawPixels = intelDrawPixels; 
   }
   else {
      functions->CopyPixels = _swrast_CopyPixels;
      functions->ReadPixels = _swrast_ReadPixels;
      functions->DrawPixels = _swrast_DrawPixels;
   }
}
