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

#include "intel_screen.h"
#include "intel_context.h"
#include "intel_blit.h"
#include "intel_fbo.h"
#include "intel_tris.h"
#include "intel_regions.h"
#include "intel_batchbuffer.h"
#include "context.h"
#include "framebuffer.h"
#include "swrast/swrast.h"

GLboolean intel_intersect_cliprects( drm_clip_rect_t *dst,
				     const drm_clip_rect_t *a,
				     const drm_clip_rect_t *b )
{
   GLint bx = b->x1;
   GLint by = b->y1;
   GLint bw = b->x2 - bx;
   GLint bh = b->y2 - by;

   if (bx < a->x1) bw -= a->x1 - bx, bx = a->x1;
   if (by < a->y1) bh -= a->y1 - by, by = a->y1;
   if (bx + bw > a->x2) bw = a->x2 - bx;
   if (by + bh > a->y2) bh = a->y2 - by;
   if (bw <= 0) return GL_FALSE;
   if (bh <= 0) return GL_FALSE;

   dst->x1 = bx;
   dst->y1 = by;
   dst->x2 = bx + bw;
   dst->y2 = by + bh;

   return GL_TRUE;
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
#if 0 /* XXX FBO */
   switch (ctx->ReadBuffer->_ColorReadBufferIndex) {
   case BUFFER_FRONT_LEFT:
      return intel->front_region;
   case BUFFER_BACK_LEFT:
      return intel->back_region;
   default:
      assert(0);
      return NULL;
   }
#else
   struct intel_renderbuffer *irb = intel_renderbuffer(ctx->ReadBuffer->_ColorReadBuffer);
   return irb->region;
#endif
}



static void intelBufferSize(GLframebuffer *buffer,
			    GLuint *width, 
			    GLuint *height)
{
   GET_CURRENT_CONTEXT(ctx);
   struct intel_context *intel = intel_context(ctx);
   /* Need to lock to make sure the driDrawable is uptodate.  This
    * information is used to resize Mesa's software buffers, so it has
    * to be correct.
    */
   LOCK_HARDWARE(intel);
   if (intel->driDrawable) {
      *width = intel->driDrawable->w;
      *height = intel->driDrawable->h;
   }
   else {
      *width = 0;
      *height = 0;
   }
   UNLOCK_HARDWARE(intel);
}



/**
 * Update the following fields for rendering to a user-created FBO:
 *   intel->numClipRects
 *   intel->pClipRects
 *   intel->drawX
 *   intel->drawY
 */
static void intelSetRenderbufferClipRects( struct intel_context *intel )
{
   ASSERT(intel->ctx.DrawBuffer->Width > 0);
   ASSERT(intel->ctx.DrawBuffer->Height > 0);
   intel->fboRect.x1 = 0;
   intel->fboRect.y1 = 0;
   intel->fboRect.x2 = intel->ctx.DrawBuffer->Width;
   intel->fboRect.y2 = intel->ctx.DrawBuffer->Height;
   intel->numClipRects = 1;
   intel->pClipRects = &intel->fboRect;
   intel->drawX = 0;
   intel->drawY = 0;
}


/**
 * As above, but for rendering to front buffer of a window.
 * \sa intelSetRenderbufferClipRects
 */
static void intelSetFrontClipRects( struct intel_context *intel )
{
   __DRIdrawablePrivate *dPriv = intel->driDrawable;

   if (!dPriv) return;

   intel->numClipRects = dPriv->numClipRects;
   intel->pClipRects = dPriv->pClipRects;
   intel->drawX = dPriv->x;
   intel->drawY = dPriv->y;
}


/**
 * As above, but for rendering to back buffer of a window.
 */
static void intelSetBackClipRects( struct intel_context *intel )
{
   __DRIdrawablePrivate *dPriv = intel->driDrawable;

   if (!dPriv) return;

   if (intel->sarea->pf_enabled == 0 && dPriv->numBackClipRects == 0) {
      /* use the front clip rects */
      intel->numClipRects = dPriv->numClipRects;
      intel->pClipRects = dPriv->pClipRects;
      intel->drawX = dPriv->x;
      intel->drawY = dPriv->y;
   } else {
      /* use the back clip rects */
      intel->numClipRects = dPriv->numBackClipRects;
      intel->pClipRects = dPriv->pBackClipRects;
      intel->drawX = dPriv->backX;
      intel->drawY = dPriv->backY;
      
      if (dPriv->numBackClipRects == 1 &&
	  dPriv->x == dPriv->backX &&
	  dPriv->y == dPriv->backY) {
      
	 /* Repeat the calculation of the back cliprect dimensions here
	  * as early versions of dri.a in the Xserver are incorrect.  Try
	  * very hard not to restrict future versions of dri.a which
	  * might eg. allocate truly private back buffers.
	  */
	 int x1, y1;
	 int x2, y2;
	 
	 x1 = dPriv->x;
	 y1 = dPriv->y;      
	 x2 = dPriv->x + dPriv->w;
	 y2 = dPriv->y + dPriv->h;
	 
	 if (x1 < 0) x1 = 0;
	 if (y1 < 0) y1 = 0;
	 if (x2 > intel->intelScreen->width) x2 = intel->intelScreen->width;
	 if (y2 > intel->intelScreen->height) y2 = intel->intelScreen->height;

	 if (x1 == dPriv->pBackClipRects[0].x1 &&
	     y1 == dPriv->pBackClipRects[0].y1) {

	    dPriv->pBackClipRects[0].x2 = x2;
	    dPriv->pBackClipRects[0].y2 = y2;
	 }
      }
   }
}


/**
 * This will be called whenever the currently bound window is moved/resized.
 * XXX: actually, it seems to NOT be called when the window is only moved (BP).
 */
void intelWindowMoved( struct intel_context *intel )
{
   GLcontext *ctx = &intel->ctx;

   if (!intel->ctx.DrawBuffer) {
      /* when would this happen? -BP */
      intelSetFrontClipRects( intel );
   }
   else if (intel->ctx.DrawBuffer->Name != 0) {
      /* drawing to user-created FBO - do nothing */
   }
   else {
      /* drawing to a window */
      switch (intel->ctx.DrawBuffer->_ColorDrawBufferMask[0]) {
      case BUFFER_BIT_FRONT_LEFT:
	 intelSetFrontClipRects( intel );
	 break;
      case BUFFER_BIT_BACK_LEFT:
	 intelSetBackClipRects( intel );
	 break;
      default:
	 /* glDrawBuffer(GL_NONE or GL_FRONT_AND_BACK): software fallback */
	 intelSetFrontClipRects( intel );
      }

      /* this update Mesa's notion of window size */
      _mesa_resize_framebuffer(ctx, ctx->DrawBuffer,
                               intel->driDrawable->w, intel->driDrawable->h);
   }

   /* Update hardware scissor */
   ctx->Driver.Scissor( ctx, ctx->Scissor.X, ctx->Scissor.Y,
                        ctx->Scissor.Width, ctx->Scissor.Height );
}



/* A true meta version of this would be very simple and additionally
 * machine independent.  Maybe we'll get there one day.
 */
static void intelClearWithTris(struct intel_context *intel, 
			       GLbitfield mask,
			       GLboolean all,
			       GLint cx, GLint cy, 
			       GLint cw, GLint ch)
{
   GLcontext *ctx = &intel->ctx;
   drm_clip_rect_t clear;

   if (INTEL_DEBUG & DEBUG_DRI)
      _mesa_printf("%s 0x%x\n", __FUNCTION__, mask);

   LOCK_HARDWARE(intel);

   /* XXX FBO: was: intel->driDrawable->numClipRects */
   if (intel->numClipRects) {

      intel->vtbl.install_meta_state(intel);

      /* note: regardless of 'all', cx, cy, cw, ch are correct */
      clear.x1 = cx;
      clear.y1 = cy;
      clear.x2 = cx + cw;
      clear.y2 = cy + ch;

      /* Back and stencil cliprects are the same.  Try and do both
       * buffers at once:
       * XXX FBO: This is broken for FBO depth/stencil buffers!
       */
      if (mask & (BUFFER_BIT_BACK_LEFT|BUFFER_BIT_STENCIL|BUFFER_BIT_DEPTH)) { 
	 intel->vtbl.meta_draw_region(intel, 
				      intel->back_region,
				      intel->depth_region );

	 if (mask & BUFFER_BIT_BACK_LEFT)
	    intel->vtbl.meta_color_mask(intel, GL_TRUE );
	 else
	    intel->vtbl.meta_color_mask(intel, GL_FALSE );

	 if (mask & BUFFER_BIT_STENCIL) 
	    intel->vtbl.meta_stencil_replace( intel, 
					      intel->ctx.Stencil.WriteMask[0], 
					      intel->ctx.Stencil.Clear);
	 else
	    intel->vtbl.meta_no_stencil_write(intel);

	 if (mask & BUFFER_BIT_DEPTH) 
	    intel->vtbl.meta_depth_replace( intel );
	 else
	    intel->vtbl.meta_no_depth_write(intel);
      
	 /* XXX: Using INTEL_BATCH_NO_CLIPRECTS here is dangerous as the
	  * drawing origin may not be correctly emitted.
	  */
	 intel_meta_draw_quad(intel, 
			      clear.x1, clear.x2, 
			      clear.y1, clear.y2, 
			      intel->ctx.Depth.Clear,
			      intel->ClearColor, 
			      0, 0, 0, 0);
      }

      /* Front may have different cliprects: 
       */
      if (mask & BUFFER_BIT_FRONT_LEFT) {
	 intel->vtbl.meta_no_depth_write(intel);
	 intel->vtbl.meta_no_stencil_write(intel);
	 intel->vtbl.meta_color_mask(intel, GL_TRUE );
	 intel->vtbl.meta_draw_region(intel, 
				      intel->front_region,
				      intel->depth_region);

	 /* XXX: Using INTEL_BATCH_NO_CLIPRECTS here is dangerous as the
	  * drawing origin may not be correctly emitted.
	  */
	 intel_meta_draw_quad(intel, 
			      clear.x1, clear.x2, 
			      clear.y1, clear.y2, 
			      0,
			      intel->ClearColor, 
			      0, 0, 0, 0);
      }

      /*
       * User-created RGBA renderbuffers
       */
      if (mask & (BUFFER_BIT_COLOR0 |
                  BUFFER_BIT_COLOR1 |
                  BUFFER_BIT_COLOR2 |
                  BUFFER_BIT_COLOR3)) {
         struct intel_region *depth_region = NULL;
         GLuint buf;

         ASSERT(ctx->Const.MaxColorAttachments == 4); /* XXX FBO fix */

         for (buf = BUFFER_COLOR0; buf <= BUFFER_COLOR3; buf++) {
            const GLbitfield bufBit = 1 << buf;
            if (mask & bufBit) {
               struct intel_renderbuffer *irb =
                  intel_renderbuffer(ctx->DrawBuffer->
                                     Attachment[buf].Renderbuffer);
               ASSERT(irb);
               ASSERT(irb->region);

               /* XXX move these three calls outside loop? */
               intel->vtbl.meta_no_depth_write(intel);
               intel->vtbl.meta_no_stencil_write(intel);
               intel->vtbl.meta_color_mask(intel, GL_TRUE );
               intel->vtbl.meta_draw_region(intel, irb->region, depth_region);

               /* XXX: Using INTEL_BATCH_NO_CLIPRECTS here is dangerous as the
                * drawing origin may not be correctly emitted.
                */
               intel_meta_draw_quad(intel, 
                                    clear.x1, clear.x2, 
                                    clear.y1, clear.y2, 
                                    0,
                                    intel->ClearColor, 
                                    0, 0, 0, 0);
            }
         }
      }

      intel->vtbl.leave_meta_state( intel );
      intel_batchbuffer_flush( intel->batch );
   }
   UNLOCK_HARDWARE(intel);
}




/**
 * Called by ctx->Driver.Clear.
 */
static void intelClear(GLcontext *ctx, 
		       GLbitfield mask, 
		       GLboolean all,
		       GLint cx, GLint cy, 
		       GLint cw, GLint ch)
{
   struct intel_context *intel = intel_context( ctx );
   const GLuint colorMask = *((GLuint *) &ctx->Color.ColorMask);
   GLbitfield tri_mask = 0;
   GLbitfield blit_mask = 0;
   GLbitfield swrast_mask = 0;

   if (0)
      fprintf(stderr, "%s\n", __FUNCTION__);


   /* HW color buffers (front, back, aux, generic FBO, etc) */
   if (colorMask == ~0) {
      /* clear all R,G,B,A */
      blit_mask |= (mask & BUFFER_BITS_COLOR);
   }
   else {
      /* glColorMask in effect */
      tri_mask |= (mask & BUFFER_BITS_COLOR);
   }

   /* HW stencil */
   if (intel->hw_stencil && (mask & BUFFER_BIT_STENCIL)) {
      if ((ctx->Stencil.WriteMask[0] & 0xff) != 0xff) {
         /* not clearing all stencil bits, so use triangle clearing */
	 tri_mask |= BUFFER_BIT_STENCIL;
      } 
      else {
         /* clearing all stencil bits, use blitting */
	 blit_mask |= BUFFER_BIT_STENCIL;
      }
   }

   /* HW depth */
   if (mask & BUFFER_BIT_DEPTH) {
      /* clear depth with whatever method is used for stencil (see above) */
      if (tri_mask & BUFFER_BIT_STENCIL)
	 tri_mask |= BUFFER_BIT_DEPTH;
      else 
	 blit_mask |= BUFFER_BIT_DEPTH;
   }

   /* SW fallback clearing */
   swrast_mask = mask & ~tri_mask & ~blit_mask;

   intelFlush( ctx ); /* XXX intelClearWithBlit also does this */

   if (blit_mask)
      intelClearWithBlit( ctx, blit_mask, all, cx, cy, cw, ch );

   if (tri_mask) 
      intelClearWithTris( intel, tri_mask, all, cx, cy, cw, ch);

   if (swrast_mask)
      _swrast_Clear( ctx, swrast_mask, all, cx, cy, cw, ch );
}







/* Flip the front & back buffers
 */
static void intelPageFlip( const __DRIdrawablePrivate *dPriv )
{
#if 0
   struct intel_context *intel;
   int tmp, ret;

   if (INTEL_DEBUG & DEBUG_IOCTL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   assert(dPriv);
   assert(dPriv->driContextPriv);
   assert(dPriv->driContextPriv->driverPrivate);

   intel = (struct intel_context *) dPriv->driContextPriv->driverPrivate;

   intelFlush( &intel->ctx );
   LOCK_HARDWARE( intel );

   if (dPriv->pClipRects) {
      *(drm_clip_rect_t *)intel->sarea->boxes = dPriv->pClipRects[0];
      intel->sarea->nbox = 1;
   }

   ret = drmCommandNone(intel->driFd, DRM_I830_FLIP); 
   if (ret) {
      fprintf(stderr, "%s: %d\n", __FUNCTION__, ret);
      UNLOCK_HARDWARE( intel );
      exit(1);
   }

   tmp = intel->sarea->last_enqueue;
   intelRefillBatchLocked( intel );
   UNLOCK_HARDWARE( intel );


   intelSetDrawBuffer( &intel->ctx, intel->ctx.Color.DriverDrawBuffer );
#endif
}


void intelSwapBuffers( __DRIdrawablePrivate *dPriv )
{
   if (dPriv->driContextPriv && dPriv->driContextPriv->driverPrivate) {
      struct intel_context *intel;
      GLcontext *ctx;
      intel = (struct intel_context *) dPriv->driContextPriv->driverPrivate;
      ctx = &intel->ctx;
      if (ctx->Visual.doubleBufferMode) {
	 _mesa_notifySwapBuffers( ctx );  /* flush pending rendering comands */
	 if ( 0 /*intel->doPageFlip*/ ) { /* doPageFlip is never set !!! */
	    intelPageFlip( dPriv );
	 } else {
	    intelCopyBuffer( dPriv );
	 }
      }
   } else {
      /* XXX this shouldn't be an error but we can't handle it for now */
      fprintf(stderr, "%s: drawable has no context!\n", __FUNCTION__);
   }
}


/**
 * Called via glDrawBuffer, glBindFramebufferEXT, MakeCurrent, and from
 * various places within the driver.
 * Note: mode parameter is not used.
 */
static void
intelDrawBuffer(GLcontext *ctx, GLenum mode)
{
   struct intel_context *intel = intel_context(ctx);
   struct intel_renderbuffer *irb;
   struct intel_region *colorRegion, *depthRegion;
   int front = 0; /* drawing to front color buffer? */
 
   if (!ctx->DrawBuffer) {
      /* this can happen during the initial context initialization */
      return;
   }

   /* Do this here, note core Mesa, since this function is called from
    * many places within the driver.
    */
   if (ctx->NewState & (_NEW_BUFFERS | _NEW_COLOR | _NEW_PIXEL)) {
      /* this updates the DrawBuffer->_NumColorDrawBuffers fields, etc */
      _mesa_update_framebuffer(ctx);
      /* this updates the DrawBuffer's Width/Height if it's a FBO */
      _mesa_update_draw_buffer_bounds(ctx);
   }

   /*
    * How many color buffers are we drawing into?
    */
   if (ctx->DrawBuffer->_NumColorDrawBuffers[0] != 1
#if 0
       /* XXX FBO temporary - always use software rendering */
       || ctx->DrawBuffer->Name != 0
#endif
    ) {
      /* writing to 0 or 2 or 4 color buffers */
      /*_mesa_debug(ctx, "Software rendering\n");*/
      FALLBACK( intel, INTEL_FALLBACK_DRAW_BUFFER, GL_TRUE );
      front = 1; /* might not have back color buffer */
   }
   else {
      /* draw to exactly one color buffer */
      /*_mesa_debug(ctx, "Hardware rendering\n");*/
      FALLBACK( intel, INTEL_FALLBACK_DRAW_BUFFER, GL_FALSE );
      if (ctx->DrawBuffer->_ColorDrawBufferMask[0] == BUFFER_BIT_FRONT_LEFT) {
         front = 1;
      }
   }

   /*
    * Get the intel_renderbuffer we're drawing into.
    * And set up cliprects.
    */
   if (ctx->DrawBuffer->Name == 0) {
      /* drawing to window system buffer */
      if (intel->sarea->pf_current_page == 1 ) {
         /* page flipped back/front */
         front ^= 1;
      }
      if (front) {
         intelSetFrontClipRects( intel );
         irb = intel_renderbuffer(ctx->DrawBuffer->
                                  Attachment[BUFFER_FRONT_LEFT].Renderbuffer);
      }
      else {
         intelSetBackClipRects( intel );
         irb = intel_renderbuffer(ctx->DrawBuffer->
                                  Attachment[BUFFER_BACK_LEFT].Renderbuffer);
      }
   }
   else {
      /* drawing to user-created FBO */
      intelSetRenderbufferClipRects(intel);
      irb = intel_renderbuffer(ctx->DrawBuffer->_ColorDrawBuffers[0][0]);
      ASSERT(irb);
   }

   /*
    * Get color buffer region.
    */
   if (irb && irb->region)
      colorRegion = irb->region;
   else
      colorRegion = NULL;

   /*
    * Unbind old color region, bind new region
    */
   if (intel->draw_region != colorRegion) {
      intel_region_release(intel, &intel->draw_region);
      intel_region_reference(&intel->draw_region, colorRegion);
   }

   /*
    * Get depth buffer region
    */
   irb = intel_renderbuffer(ctx->DrawBuffer->_DepthBuffer);
   if (irb && irb->region)
      depthRegion = irb->region;
   else
      depthRegion = NULL;

   /*
    * Unbind old depth region, bind new region
    */
   if (intel->depth_region != depthRegion) {
      intel_region_release(intel, &intel->depth_region);
      intel_region_reference(&intel->depth_region, depthRegion);
   }

   intel->vtbl.set_draw_region( intel, colorRegion, depthRegion );
}


static void intelReadBuffer( GLcontext *ctx, GLenum mode )
{
   /* Nothing.
    * The functions which do framebuffer reads (glReadPixels, glCopyPixels,
    * etc. are all set just by using ctx->ReadBuffer->_ColorReadBuffer.
    */
}



void intelInitBufferFuncs( struct dd_function_table *functions )
{
   functions->Clear = intelClear;
   functions->GetBufferSize = intelBufferSize;
   functions->ResizeBuffers = _mesa_resize_framebuffer;
   functions->DrawBuffer = intelDrawBuffer;
   functions->ReadBuffer = intelReadBuffer;
}
