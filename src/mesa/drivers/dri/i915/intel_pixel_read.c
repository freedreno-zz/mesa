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




static GLboolean
do_texture_readpixels( GLcontext *ctx,
			GLint x, GLint y, GLsizei width, GLsizei height,
			GLenum format, GLenum type,
			const struct gl_pixelstore_attrib *pack,
			struct intel_region *dest_region )
{
#if 0
   struct intel_context *intel = intel_context(ctx);
   intelScreenPrivate *screen = intel->intelScreen;
   GLint pitch = pack->RowLength ? pack->RowLength : width;
   __DRIdrawablePrivate *dPriv = intel->driDrawable;
   int textureFormat;
   GLenum glTextureFormat;
   int destFormat, depthFormat, destPitch;
   drm_clip_rect_t tmp;

   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);


   if (	ctx->_ImageTransferState ||
	pack->SwapBytes ||
	pack->LsbFirst ||
	!pack->Invert) {
      fprintf(stderr, "%s: check_color failed\n", __FUNCTION__);
      return GL_FALSE;
   }

   intel->vtbl.meta_texrect_source(intel, intel_readbuf_region(intel));

   if (!intel->vtbl.meta_render_dest(intel,
				     dest_region,
				     type, format))
   {
      fprintf(stderr, "%s: couldn't set dest %s/%s\n",
	      __FUNCTION__,
	      _mesa_lookup_enum_by_nr(type),
	      _mesa_lookup_enum_by_nr(format));
      return GL_FALSE;
   }

   LOCK_HARDWARE( intel );
   intel->vtbl.install_meta_state(intel);
   intel->vtbl.meta_no_depth_stencil_write(intel);

   if (!driClipRectToFramebuffer(ctx->ReadBuffer, &x, &y, &width, &height)) {
      UNLOCK_HARDWARE( intel );
      SET_STATE(i830, state);
      fprintf(stderr, "%s: cliprect failed\n", __FUNCTION__);
      return GL_TRUE;
   }

   y = dPriv->h - y - height;
   x += dPriv->x;
   y += dPriv->y;


   /* Set the frontbuffer up as a large rectangular texture.
    */
   intel->vtbl.meta_tex_rect_source( intel,
				     src_region,
				     textureFormat ); 
   
   
   intel->vtbl.meta_texture_blend_replace( i830, glTextureFormat ); 


   /* Set the 3d engine to draw into the destination region:
    */

   intel->vtbl.meta_draw_region(intel, dest_region); 
   intel->vtbl.meta_draw_format(intel, destFormat, depthFormat ); /* ?? */


   /* Draw a single quad, no cliprects:
    */
   intel->vtbl.meta_disable_cliprects(intel);

   intel->vtbl.draw_quad(intel, 
			 0, width, 0, height, 
			 0x00ff00ff, 
			 x, x+width, 
			 y, y+height );

   intel->vtbl.leave_meta_state(intel);
   UNLOCK_HARDWARE( intel );

   intel_region_wait_fence( ctx, dest_region ); /* required by GL */
   return GL_TRUE;
#endif

   return GL_FALSE;
}




static GLboolean do_blit_readpixels( GLcontext *ctx,
				     GLint x, GLint y, GLsizei width, GLsizei height,
				     GLenum format, GLenum type,
				     const struct gl_pixelstore_attrib *pack,
				     GLvoid *pixels )
{
#if 0
   struct intel_context *intel = intel_context(ctx);
   GLint pitch = pack->RowLength ? pack->RowLength : width;
   struct intel_region *src = intel_readbuf_region(intel);
   struct intel_client_region *dst = intel_client_pack_region(intel,
							      pack, 
							      pixels);

   if (ctx->_ImageTransferState ||
       pack->SwapBytes ||
       pack->LsbFirst) {
      fprintf(stderr, "%s: failed 1\n", __FUNCTION__);
      return GL_FALSE;
   }

   /* Need GL_PACK_INVERT_MESA to cope with upsidedown results from
    * blitter:
    */
   if (!pack->Invert) {
      fprintf(stderr, "%s: MESA_PACK_INVERT not set\n", __FUNCTION__);
      return GL_FALSE;
   }

   if (!intel_check_blit_format(src, format, type))
      return GL_FALSE;

   /* Although the blits go on the command buffer, need to do this and
    * fire with lock held to guarentee cliprects are correct.
    */
   intelFlush( &intel->ctx );
   LOCK_HARDWARE( intel );
   {
      __DRIdrawablePrivate *dPriv = intel->driDrawable;
      int nbox = dPriv->numClipRects;
      drm_clip_rect_t *box = dPriv->pClipRects;
      int i;

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

	 intelEmitCopyBlit( intel,
			    src->cpp,
			    src->pitch, src->buffer, 0,
			    dst->pitch, dst->buffer, 0,
			    bx, by,
			    bx - x, by - y,
			    bw, bh );
      }

      intel_batchbuffer_flush(intel->batch);
      intel_client_region_release(intel, dst);
   }
   UNLOCK_HARDWARE( intel );
   return GL_TRUE;
#endif

   return GL_FALSE;
}

void
intelReadPixels( GLcontext *ctx,
		 GLint x, GLint y, GLsizei width, GLsizei height,
		 GLenum format, GLenum type,
		 const struct gl_pixelstore_attrib *pack,
		 GLvoid *pixels )
{
   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   intelFlush( ctx );

   if (do_blit_readpixels(ctx, x, y, width, height, format, type, pack, pixels))
      return;

   if (do_texture_readpixels(ctx, x, y, width, height, format, type, pack, pixels))
      return;

   _swrast_ReadPixels( ctx, x, y, width, height, format, type, pack, pixels);
}

