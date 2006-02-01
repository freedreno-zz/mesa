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


#include <stdio.h>
#include <errno.h>

#include "mtypes.h"
#include "context.h"
#include "enums.h"

#include "intel_reg.h"
#include "intel_batchbuffer.h"
#include "intel_context.h"

#include "bufmgr.h"




/*
 * Copy the back buffer to the front buffer. 
 */
void intelCopyBuffer( const __DRIdrawablePrivate *dPriv ) 
{
   intelContextPtr intel;

   if (0)
      fprintf(stderr, "%s\n", __FUNCTION__);

   assert(dPriv);
   assert(dPriv->driContextPriv);
   assert(dPriv->driContextPriv->driverPrivate);

   intel = (intelContextPtr) dPriv->driContextPriv->driverPrivate;

   intelFlush( &intel->ctx );
   LOCK_HARDWARE( intel );
   intelInstallBatchBuffer(intel);   
   intelValidateBuffers( intel );

   {
      intelScreenPrivate *intelScreen = intel->intelScreen;
      __DRIdrawablePrivate *dPriv = intel->driDrawable;
      int nbox = dPriv->numClipRects;
      drm_clip_rect_t *pbox = dPriv->pClipRects;
      int pitch = intelScreen->front.pitch;
      int cpp = intelScreen->cpp;
      int i;
      GLuint CMD, BR13;
      BATCH_LOCALS;

      switch(cpp) {
      case 2: 
	 BR13 = (pitch * cpp) | (0xCC << 16) | (1<<24);
	 CMD = XY_SRC_COPY_BLT_CMD;
	 break;
      case 4:
	 BR13 = (pitch * cpp) | (0xCC << 16) | (1<<24) | (1<<25);
	 CMD = (XY_SRC_COPY_BLT_CMD | XY_SRC_COPY_BLT_WRITE_ALPHA |
		XY_SRC_COPY_BLT_WRITE_RGB);
	 break;
      default:
	 BR13 = (pitch * cpp) | (0xCC << 16) | (1<<24);
	 CMD = XY_SRC_COPY_BLT_CMD;
	 break;
      }

      for (i = 0 ; i < nbox; i++, pbox++) 
      {
	 if (pbox->x1 > pbox->x2 ||
	     pbox->y1 > pbox->y2 ||
	     pbox->x2 > intelScreen->width ||
	     pbox->y2 > intelScreen->height)
	    continue;
 
	 BEGIN_BATCH( 8);
	 OUT_BATCH( CMD );
	 OUT_BATCH( BR13 );
	 OUT_BATCH( (pbox->y1 << 16) | pbox->x1 );
	 OUT_BATCH( (pbox->y2 << 16) | pbox->x2 );

	 if (intel->sarea->pf_current_page == 0) 
	    OUT_BATCH( intelScreen->front.offset );
	 else
	    OUT_BATCH( intelScreen->back.offset );			

	 OUT_BATCH( (pbox->y1 << 16) | pbox->x1 );
	 OUT_BATCH( BR13 & 0xffff );

	 if (intel->sarea->pf_current_page == 0) 
	    OUT_BATCH( intelScreen->back.offset );			
	 else
	    OUT_BATCH( intelScreen->front.offset );

	 ADVANCE_BATCH();
      }
   }
   intelFlushBatchLocked( intel, GL_TRUE, GL_TRUE, GL_TRUE );
   assert(intel->buffer_list == NULL);

   UNLOCK_HARDWARE( intel );
}




void intelEmitFillBlitLocked( intelContextPtr intel,
			      GLuint cpp,
			      GLshort dst_pitch,
			      GLuint dst_offset,
			      GLshort x, GLshort y, 
			      GLshort w, GLshort h,
			      GLuint color )
{
   GLuint BR13, CMD;
   BATCH_LOCALS;

   dst_pitch *= cpp;

   switch(cpp) {
   case 1: 
   case 2: 
   case 3: 
      BR13 = dst_pitch | (0xF0 << 16) | (1<<24);
      CMD = XY_COLOR_BLT_CMD;
      break;
   case 4:
      BR13 = dst_pitch | (0xF0 << 16) | (1<<24) | (1<<25);
      CMD = (XY_COLOR_BLT_CMD | XY_COLOR_BLT_WRITE_ALPHA |
	     XY_COLOR_BLT_WRITE_RGB);
      break;
   default:
      return;
   }

   BEGIN_BATCH( 6);
   OUT_BATCH( CMD );
   OUT_BATCH( BR13 );
   OUT_BATCH( (y << 16) | x );
   OUT_BATCH( ((y+h) << 16) | (x+w) );
   OUT_BATCH( dst_offset );
   OUT_BATCH( color );
   ADVANCE_BATCH();
}


/* Copy BitBlt
 */
void intelEmitCopyBlitLocked( intelContextPtr intel,
			      GLuint cpp,
			      GLshort src_pitch,
			      GLuint  src_offset,
			      GLshort dst_pitch,
			      GLuint  dst_offset,
			      GLshort src_x, GLshort src_y,
			      GLshort dst_x, GLshort dst_y,
			      GLshort w, GLshort h )
{
   GLuint CMD, BR13;
   int dst_y2 = dst_y + h;
   int dst_x2 = dst_x + w;
   BATCH_LOCALS;


   if (0)
      _mesa_printf("%s src:0x%x/%d %d,%d dst:0x%x/%d %d,%d sz:%dx%d\n",
		   __FUNCTION__,
		   src_offset, src_pitch, src_x, src_y,
		   dst_offset, dst_pitch, dst_x, dst_y,
		   w,h);

   src_pitch *= cpp;
   dst_pitch *= cpp;

   switch(cpp) {
   case 1: 
   case 2: 
   case 3: 
      BR13 = dst_pitch | (0xCC << 16) | (1<<24);
      CMD = XY_SRC_COPY_BLT_CMD;
      break;
   case 4:
      BR13 = dst_pitch | (0xCC << 16) | (1<<24) | (1<<25);
      CMD = (XY_SRC_COPY_BLT_CMD | XY_SRC_COPY_BLT_WRITE_ALPHA |
	     XY_SRC_COPY_BLT_WRITE_RGB);
      break;
   default:
      return;
   }

   if (dst_y2 < dst_y ||
       dst_x2 < dst_x) {
      return;
   }

   BEGIN_BATCH( 12);
   OUT_BATCH( CMD );
   OUT_BATCH( BR13 );
   OUT_BATCH( (dst_y << 16) | dst_x );
   OUT_BATCH( (dst_y2 << 16) | dst_x2 );
   OUT_BATCH( dst_offset );	
   OUT_BATCH( (src_y << 16) | src_x );
   OUT_BATCH( src_pitch );
   OUT_BATCH( src_offset ); 
   ADVANCE_BATCH();
}



void intelClearWithBlit(GLcontext *ctx, GLbitfield flags, GLboolean all,
		      GLint cx1, GLint cy1, GLint cw, GLint ch)
{
   intelContextPtr intel = INTEL_CONTEXT( ctx );
   intelScreenPrivate *intelScreen = intel->intelScreen;
   GLuint clear_depth, clear_color;
   GLint cx, cy;
   GLint pitch = intelScreen->front.pitch;
   GLint cpp = intelScreen->cpp;
   GLint i;
   GLuint BR13, CMD, D_CMD;
   BATCH_LOCALS;

   
   clear_color = intel->ClearColor;
   clear_depth = 0;

   if (flags & BUFFER_BIT_DEPTH) {
      clear_depth = (GLuint)(ctx->Depth.Clear * intel->ClearDepth);
   }

   if (flags & BUFFER_BIT_STENCIL) {
      clear_depth |= (ctx->Stencil.Clear & 0xff) << 24;
   }

   switch(cpp) {
   case 2: 
      BR13 = (0xF0 << 16) | (pitch * cpp) | (1<<24);
      D_CMD = CMD = XY_COLOR_BLT_CMD;
      break;
   case 4:
      BR13 = (0xF0 << 16) | (pitch * cpp) | (1<<24) | (1<<25);
      CMD = (XY_COLOR_BLT_CMD |
	     XY_COLOR_BLT_WRITE_ALPHA | 
	     XY_COLOR_BLT_WRITE_RGB);
      D_CMD = XY_COLOR_BLT_CMD;
      if (flags & BUFFER_BIT_DEPTH) D_CMD |= XY_COLOR_BLT_WRITE_RGB;
      if (flags & BUFFER_BIT_STENCIL) D_CMD |= XY_COLOR_BLT_WRITE_ALPHA;
      break;
   default:
      BR13 = (0xF0 << 16) | (pitch * cpp) | (1<<24);
      D_CMD = CMD = XY_COLOR_BLT_CMD;
      break;
   }

   intelFlush( &intel->ctx );
   LOCK_HARDWARE( intel );
   intelInstallBatchBuffer(intel);   
   intelValidateBuffers( intel );
   {
      /* flip top to bottom */
      cy = intel->driDrawable->h-cy1-ch;
      cx = cx1 + intel->drawX;
      cy += intel->drawY;

      /* adjust for page flipping */
      if ( intel->sarea->pf_current_page == 1 ) {
	 GLuint tmp = flags;

	 flags &= ~(BUFFER_BIT_FRONT_LEFT | BUFFER_BIT_BACK_LEFT);
	 if ( tmp & BUFFER_BIT_FRONT_LEFT ) flags |= BUFFER_BIT_BACK_LEFT;
	 if ( tmp & BUFFER_BIT_BACK_LEFT )  flags |= BUFFER_BIT_FRONT_LEFT;
      }

      for (i = 0 ; i < intel->numClipRects ; i++) 
      { 	 
	 drm_clip_rect_t *box = &intel->pClipRects[i];	 
	 drm_clip_rect_t b;

	 if (!all) {
	    GLint x = box[i].x1;
	    GLint y = box[i].y1;
	    GLint w = box[i].x2 - x;
	    GLint h = box[i].y2 - y;

	    if (x < cx) w -= cx - x, x = cx; 
	    if (y < cy) h -= cy - y, y = cy;
	    if (x + w > cx + cw) w = cx + cw - x;
	    if (y + h > cy + ch) h = cy + ch - y;
	    if (w <= 0) continue;
	    if (h <= 0) continue;

	    b.x1 = x;
	    b.y1 = y;
	    b.x2 = x + w;
	    b.y2 = y + h;      
	 } else {
	    b = *box;
	 }


	 if (b.x1 > b.x2 ||
	     b.y1 > b.y2 ||
	     b.x2 > intelScreen->width ||
	     b.y2 > intelScreen->height)
	    continue;

	 if ( flags & BUFFER_BIT_FRONT_LEFT ) {	    
	    BEGIN_BATCH( 6);	    
	    OUT_BATCH( CMD );
	    OUT_BATCH( BR13 );
	    OUT_BATCH( (b.y1 << 16) | b.x1 );
	    OUT_BATCH( (b.y2 << 16) | b.x2 );
	    OUT_BATCH( intelScreen->front.offset );
	    OUT_BATCH( clear_color );
	    ADVANCE_BATCH();
	 }

	 if ( flags & BUFFER_BIT_BACK_LEFT ) {
	    BEGIN_BATCH( 6); 
	    OUT_BATCH( CMD );
	    OUT_BATCH( BR13 );
	    OUT_BATCH( (b.y1 << 16) | b.x1 );
	    OUT_BATCH( (b.y2 << 16) | b.x2 );
	    OUT_BATCH( intelScreen->back.offset );
	    OUT_BATCH( clear_color );
	    ADVANCE_BATCH();
	 }

	 if ( flags & (BUFFER_BIT_STENCIL | BUFFER_BIT_DEPTH) ) {
	    BEGIN_BATCH( 6);
	    OUT_BATCH( D_CMD );
	    OUT_BATCH( BR13 );
	    OUT_BATCH( (b.y1 << 16) | b.x1 );
	    OUT_BATCH( (b.y2 << 16) | b.x2 );
	    OUT_BATCH( intelScreen->depth.offset );
	    OUT_BATCH( clear_depth );
	    ADVANCE_BATCH();
	 }      
      }
   }
   intelFlushBatchLocked( intel, GL_TRUE, GL_FALSE, GL_TRUE );
   UNLOCK_HARDWARE( intel );
}




void intelDestroyBatchBuffer( struct intel_context *intel )
{
}


void intelInstallBatchBuffer( struct intel_context *intel )
{
   assert(!intel->batch.ptr);

   intel->alloc.current++;
   intel->alloc.current %= INTEL_ALLOC_NR;

   DBG("%s: %d\n", __FUNCTION__, intel->alloc.current);

   intel->batch.size = INTEL_ALLOC_SIZE;
   intel->batch.space = intel->batch.size;
   intel->batch.start_offset = 0;

   intel->batch.ptr = bmMapBuffer( intel->bm, 
				   intel->alloc.buffer[intel->alloc.current],
				   BM_WRITE | BM_MEM_AGP );


   assert(!intel->buffer_list);
   intel->buffer_list = bmNewBufferList();
      
   /* Add the batchbuffer 
    */
   bmAddBuffer(intel->buffer_list,
	       intel->alloc.buffer[intel->alloc.current],
	       BM_READ,
	       NULL,
	       &intel->batch.start_offset);


   if (0) {
      static int foo;
      if (foo++ > 10) {
	 _mesa_printf("foo\n");
	 exit(1);
      }
   }
}

void intelInitBatchBuffer( struct intel_context *intel )
{
   GLint i;

   _mesa_printf("%s: %d\n", __FUNCTION__, intel->alloc.current);
   bmGenBuffers(intel->bm,
		INTEL_ALLOC_NR,
		intel->alloc.buffer);

   for (i = 0; i < INTEL_ALLOC_NR; i++)
      bmBufferData(intel->bm, 
		   intel->alloc.buffer[i],
		   INTEL_ALLOC_SIZE,
		   NULL,
		   BM_MEM_AGP);
		

}


void intelValidateBuffers( struct intel_context *intel )
{
   if (!bmValidateBufferList(intel->bm, intel->buffer_list, BM_MEM_AGP))
      assert(0);
}
