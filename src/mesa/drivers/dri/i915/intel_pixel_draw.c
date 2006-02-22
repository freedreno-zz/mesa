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



static GLboolean do_texture_draw_pixels( struct intel_context *intel,
					 GLint x, GLint y, 
					 GLsizei width, GLsizei height,
					 GLenum format, GLenum type,
					 const struct gl_pixelstore_attrib *unpack,
					 const GLvoid *pixels )
{
#if 0
   GLint pitch = unpack->RowLength ? unpack->RowLength : width;
   __DRIdrawablePrivate *dPriv = intel->driDrawable;
   int textureFormat;
   GLenum glTextureFormat;

   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);


   if (	ctx->_ImageTransferState ||
	unpack->SwapBytes ||
	unpack->LsbFirst ||
	ctx->Texture._EnabledUnits ||
	ctx->FragmentProgram._Enabled) {
      fprintf(stderr, "%s: cannot use texture path\n", __FUNCTION__);
      return GL_FALSE;
   }
   
   glGenTextures();
   glTextureImage2D();
   glBindTexture();
   glEnable(GL_TEXTURE_RECTANGLE_NV);
   
   glDisable(GL_POLYGON_STIPPLE);
   glDisable(GL_CULL);

   _mesa_install_vp_passthrough(ctx);
   _mesa_push_current(ctx);
   
   if (intel->Fallback)
      goto Fail;

   glBegin(GL_QUADS);
   glVertex3f();
   glTexCoord2f();
   glVertex3f();
   glTexCoord2f();
   glVertex3f();
   glTexCoord2f();
   glVertex3f();
   glTexCoord2f();
   glEnd();
   glFinish(); 
   
   ASSIGN_4V(ctx->Current.Atrrib[VERT_ATTRIB_TEX0], tex0);

 fail:
   glDisable(GL_TEXTURE_RECTANGLE_NV);
   glDeleteTextures();
   glBindTexture(old);


#endif
   return GL_FALSE;
}





/* Pros:  
 *   - no waiting for idle before updating framebuffer.
 *   
 * Cons:
 *   - if upload is by memcpy, this may actually be slower than fallback path.
 *   - uploads the whole image even if destination is clipped
 *   
 * Need to benchmark.
 */
static GLboolean do_blit_draw_pixels( struct intel_context *intel,
				      GLint x, GLint y, 
				      GLsizei width, GLsizei height,
				      GLenum format, GLenum type,
				      const struct gl_pixelstore_attrib *unpack,
				      const GLvoid *pixels )
{
#if 0
   struct intel_region *dest = intel_drawbuf_region(intel);
   struct intel_region *src = NULL;

   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   if (!src || !dest)
      return GL_FALSE;

   if (!intel_check_blit_format(dest, src)) 
      return GL_FALSE;

   if (!intel_check_blit_fragment_ops(ctx)) 
      return GL_FALSE;

   if (ctx->Pixel.ZoomX != 1.0F)
      return GL_FALSE;

   if (ctx->Pixel.ZoomY == -1.0F)
      y -= height;			
   else if (ctx->Pixel.ZoomY == 1.0F) {
      src_pitch = -src_pitch;
      src_y += height;
   }
   else
      return GL_FALSE;


   if (unpack->BufferObj->Name) {
      src = intel_bufferobj_unpack_region(intel, unpack, 
					  width, height, 
					  format, type, 
					  unpack->BufferObj);
      src_offset = (unsigned long)pixels;
   }
   else {
      src = intel_client_unpack_region(intel, unpack, 
				       width, height, 
				       format, type, pixels);
      src_offset = 0;
   }


   intelFlush( &intel->ctx );
   LOCK_HARDWARE( intel );
   {
      __DRIdrawablePrivate *dPriv = intel->driDrawable;
      int nbox = dPriv->numClipRects;
      drm_clip_rect_t *box = dPriv->pClipRects;
      drm_clip_rect_t rect;
      int i;
      
      y = dPriv->h - y - height; 	/* convert from gl to hardware coords */
      x += dPriv->x;
      y += dPriv->y;


      for (i = 0 ; i < nbox ; i++ )
      {
	 if (!intel_intersect_cliprects(rect, db_rect, &box[i]))
	    continue;

	 intelEmitCopyBlit( intel,
			    intel->intelScreen->cpp,
			    src->pitch, src->buffer, src_offset,
			    dst->pitch, dst->buffer, 0,
			    rect->x1 - x, 
			    rect->y1 - y,
			    rect->x1, 
			    rect->y1,
			    rect->x2 - rect->x1,
			    rect->y2 - rect->y1 );
      }
   }

   intel_release_unpack_region( intel, src );
   fence = intel_batchbuffer_flush( intel->batch );
   UNLOCK_HARDWARE( intel );

   bmWaitFence(intel->bm, fence);
   intel_region_release(intel, &src);
#endif
   
   return GL_FALSE;
}



void intelDrawPixels( GLcontext *ctx,
		      GLint x, GLint y, 
		      GLsizei width, GLsizei height,
		      GLenum format, 
		      GLenum type,
		      const struct gl_pixelstore_attrib *unpack,
		      const GLvoid *pixels )
{
   struct intel_context *intel = intel_context(ctx);

   if (INTEL_DEBUG & DEBUG_PIXEL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   if (do_texture_draw_pixels( intel, x, y, width, height, format, type,
			       unpack, pixels ))
      return;

   if (do_blit_draw_pixels( intel, x, y, width, height, format, type,
			    unpack, pixels ))
      return;

   _swrast_DrawPixels( ctx, x, y, width, height, format, type,
		       unpack, pixels );
}

