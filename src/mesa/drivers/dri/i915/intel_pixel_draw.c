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

#include "glheader.h"
#include "enums.h"
#include "image.h"
#include "mtypes.h"
#include "macros.h"
#include "bufferobj.h"
#include "swrast/swrast.h"

#include "intel_screen.h"
#include "intel_context.h"
#include "intel_ioctl.h"
#include "intel_batchbuffer.h"
#include "intel_blit.h"
#include "intel_regions.h"
#include "intel_pixel.h"
#include "intel_buffer_objects.h"
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
 *
 * Given the questions about performance, implement for pbo's only.
 * This path is definitely a win if the pbo is already in agp.  If it
 * turns out otherwise, we can add the code necessary to upload client
 * data to agp space before performing the blit.  (Though it may turn
 * out to be better/simpler just to use the texture engine).
 */
static GLboolean do_blit_draw_pixels( struct intel_context *intel,
				      GLint x, GLint y, 
				      GLsizei width, GLsizei height,
				      GLenum format, GLenum type,
				      const struct gl_pixelstore_attrib *unpack,
				      const GLvoid *pixels )
{
   GLcontext *ctx = &intel->ctx;
   struct intel_region *dest = intel_drawbuf_region(intel);
   struct intel_buffer_object *src = intel_buffer_object(unpack->BufferObj);
   GLuint src_offset;
   GLuint rowLength;
   GLuint fence;
   
   if (INTEL_DEBUG & DEBUG_PIXEL)
      _mesa_printf("%s\n", __FUNCTION__);
   
   
   if (!dest)
      return GL_FALSE;

   if (src) {
      /* This validation should be done by core mesa:
       */
      if (!_mesa_validate_pbo_access(2, unpack, width, height, 1,
                                     format, type, pixels)) {
         _mesa_error(ctx, GL_INVALID_OPERATION, "glDrawPixels");
	 _mesa_printf("%s - _mesa_validate_pbo_access\n", __FUNCTION__);

         return GL_TRUE;
      }
   }
   else {
      /* PBO only for now:
       */
/*       _mesa_printf("%s - not PBO\n", __FUNCTION__); */
      return GL_FALSE;
   }
   
   if (!intel_check_blit_format(dest, format, type)) {
      _mesa_printf("%s - bad format for blit\n", __FUNCTION__);
      return GL_FALSE;
   }

   if (!intel_check_blit_fragment_ops(ctx)) {
      _mesa_printf("%s - bad GL fragment state for blit\n", __FUNCTION__);
      return GL_FALSE;
   }

   if (ctx->Pixel.ZoomX != 1.0F) {
      _mesa_printf("%s - bad PixelZoomX for blit\n", __FUNCTION__);
      return GL_FALSE;
   }


   if (unpack->RowLength > 0)
      rowLength = unpack->RowLength;
   else
      rowLength = width;

   if (ctx->Pixel.ZoomY == -1.0F) {
      return GL_FALSE;		/* later */
      y -= height;
   }
   else if (ctx->Pixel.ZoomY == 1.0F) {
      rowLength = -rowLength;
   }
   else {
      _mesa_printf("%s - bad PixelZoomY for blit\n", __FUNCTION__);
      return GL_FALSE;
   }

   src_offset = (GLuint) _mesa_image_address(2, unpack, pixels, width, height,
					     format, type, 0, 0, 0);

   intelFlush( &intel->ctx );
   LOCK_HARDWARE( intel );
   {
      __DRIdrawablePrivate *dPriv = intel->driDrawable;
      int nbox = dPriv->numClipRects;
      drm_clip_rect_t *box = dPriv->pClipRects;
      drm_clip_rect_t rect;
      drm_clip_rect_t dest_rect;
      int i;
      
      dest_rect.x1 = dPriv->x + x;
      dest_rect.y1 = dPriv->y + dPriv->h - (y + height);
      dest_rect.x2 = dest_rect.x1 + width;
      dest_rect.y2 = dest_rect.y1 + height;

      for (i = 0 ; i < nbox ; i++ )
      {
	 if (!intel_intersect_cliprects(&rect, &dest_rect, &box[i]))
	    continue;

	 intelEmitCopyBlit( intel,
			    dest->cpp,
			    rowLength, 
			    intel_bufferobj_buffer(src), src_offset,
			    dest->pitch, 
			    dest->buffer, 0,
			    rect.x1 - dest_rect.x1, 
			    rect.y2 - dest_rect.y2,
			    rect.x1, 
			    rect.y1,
			    rect.x2 - rect.x1,
			    rect.y2 - rect.y1 );
      }
   }

   fence = intel_batchbuffer_flush( intel->batch );
   UNLOCK_HARDWARE( intel );

   bmFinishFence(intel->bm, fence);   

   if (INTEL_DEBUG & DEBUG_PIXEL)
      _mesa_printf("%s - DONE\n", __FUNCTION__);

   return GL_TRUE;
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

   if (do_texture_draw_pixels( intel, x, y, width, height, format, type,
			       unpack, pixels ))
      return;

   if (do_blit_draw_pixels( intel, x, y, width, height, format, type,
			    unpack, pixels ))
      return;

   if (INTEL_DEBUG & DEBUG_PIXEL)
      _mesa_printf("%s: fallback to swrast\n", __FUNCTION__);

   _swrast_DrawPixels( ctx, x, y, width, height, format, type,
		       unpack, pixels );
}

