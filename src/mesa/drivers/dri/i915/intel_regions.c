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

/* Provide additional functionality on top of bufmgr buffers:
 *   - 2d semantics and blit operations
 *   - refcounting of buffers for multiple images in a buffer.
 *   - refcounting of buffer mappings.
 *   - some logic for moving the buffers to the best memory pools for
 *     given operations.
 *
 * Most of this is to make it easier to implement the fixed-layout
 * mipmap tree required by intel hardware in the face of GL's
 * programming interface where each image can be specifed in random
 * order and it isn't clear what layout the tree should have until the
 * last moment.
 */

#include "intel_context.h"
#include "intel_regions.h"
#include "intel_batchbuffer.h"
#include "bufmgr.h"

/* XXX: Thread safety?
 */
GLubyte *intel_region_map(struct intel_context *intel, struct intel_region *region)
{
   if (!region->map_refcount++) {
      region->map = bmMapBuffer(intel->bm, region->buffer, 0);
   }

   return region->map;
}

void intel_region_unmap(struct intel_context *intel, 
			struct intel_region *region)
{
   if (!--region->map_refcount) {
      bmUnmapBuffer(intel->bm, region->buffer);
   }
}

struct intel_region *intel_region_alloc( struct intel_context *intel, 
					 GLuint cpp,
					 GLuint pitch, 
					 GLuint height )
{
   struct intel_region *region = calloc(sizeof(*region), 1);

   region->cpp = cpp;
   region->pitch = pitch;
   region->height = height; 	/* needed? */
   region->refcount = 1;

   bmGenBuffers(intel->bm, 1, &region->buffer);
   bmBufferData(intel->bm, region->buffer, pitch * cpp * height, NULL, 0);

   return region;
}

struct intel_region *intel_region_reference( struct intel_region *region )
{
   region->refcount++;
   return region;
}

void intel_region_release( struct intel_context *intel,
			   struct intel_region *region )
{
   if (--region->refcount) {
      assert(region->map_refcount == 0);
      bmDeleteBuffers(intel->bm, 1, &region->buffer);
      free(region);
   }
}


static void _mesa_copy_rect( GLubyte *dst,
			     GLuint cpp,
			     GLuint dst_pitch,
			     GLuint dst_x, 
			     GLuint dst_y,
			     GLuint width,
			     GLuint height,
			     GLubyte *src,
			     GLuint src_x,
			     GLuint src_y,
			     GLuint src_pitch )
{
   GLuint i;

   dst_pitch *= cpp;
   src_pitch *= cpp;
   dst += dst_x * cpp;
   src += src_x * cpp;
   dst += dst_y * dst_pitch;
   src += src_y * dst_pitch;
   width *= cpp;

   if (width == dst_pitch && 
       width == src_pitch)
      memcpy(dst, src, height * width);
   else {
      for (i = 0; i < height; i++) {
	 memcpy(dst, src, width);
	 dst += dst_pitch;
	 src += src_pitch;
      }
   }
}



/* Could make color a char * to handle deeper buffers.
 */
static void _mesa_fill_rect( GLubyte *dst,
			     GLuint cpp,
			     GLuint dst_pitch,
			     GLuint dst_x, 
			     GLuint dst_y,
			     GLuint width,
			     GLuint height,
			     GLuint color )
{
   GLuint i,j;

   switch (cpp) {
   case 1:
      dst += dst_x;
      dst += dst_y * dst_pitch;
      for (i = 0; i < height; i++) { 
	 memset(dst, color, width);
	 dst += dst_pitch;
      }
      break;
   case 2: {
      GLushort color_short = color & 0xffff;
      GLushort *dst_short = (GLushort *)dst;
      dst_short += dst_x;
      dst_short += dst_y * dst_pitch;

      for (i = 0; i < height; i++) { 
	 for (j = 0; j < width; j++) 
	    dst_short[j] = color_short;
      }
      break;
   }
   case 4: {
      GLuint *dst_int = (GLuint *)dst;
      dst_int += dst_x;
      dst_int += dst_y * dst_pitch;

      for (i = 0; i < height; i++) { 
	 for (j = 0; j < width; j++) 
	    dst_int[j] = color;
      }
      break;
   }
   default:
      assert(0);
      return;
   }
}



/* Upload data to a rectangular sub-region.  Lots of choices how to do this:
 *
 * - memcpy by span to current destination
 * - upload data as new buffer and blit
 *
 * Currently always memcpy.
 */
void intel_region_data(struct intel_context *intel, 
		       struct intel_region *dest,
		       GLuint destx, GLuint desty,
		       void *src, GLuint src_pitch,
		       GLuint srcx, GLuint srcy,
		       GLuint width, GLuint height)
{
   LOCK_HARDWARE(intel);
   
   _mesa_copy_rect(intel_region_map(intel, dest),
		   dest->cpp,
		   dest->pitch,
		   destx, desty,
		   destx + width, desty + height,
		   src,
		   srcx, srcy,
		   src_pitch);      

   intel_region_unmap(intel, dest);

   UNLOCK_HARDWARE(intel);
   
}
			  
/* Copy rectangular sub-regions. Need better logic about when to
 * push buffers into AGP - will currently do so whenever possible.
 */
void intel_region_copy( struct intel_context *intel,
			struct intel_region *dest,
			GLuint destx, GLuint desty,
			struct intel_region *src,
			GLuint srcx, GLuint srcy,
			GLuint width, GLuint height )
{
   unsigned dst_offset;
   unsigned src_offset;

   assert(src->cpp == dest->cpp);

   LOCK_HARDWARE(intel);
   bmClearBufferList(intel->bm);
   bmAddBuffer(intel->bm, dest->buffer, BM_WRITE, NULL, &dst_offset);
   bmAddBuffer(intel->bm, src->buffer, BM_READ, NULL, &src_offset);

   /* What I really want to do is query if both buffers are already
    * uploaded:
    */
   if (bmValidateBufferList(intel->bm, BM_NO_EVICT|BM_NO_UPLOAD)) {
      intelEmitCopyBlitLocked(intel,
			      dest->cpp,
			      src->pitch,
			      src_offset,
			     dest->pitch,			      
			     dst_offset, 
			     srcx, srcy,
			     destx, desty,
			     width, height);

      bmReleaseValidatedBuffers(intel->bm);
   }
   else {
      _mesa_copy_rect(intel_region_map(intel, dest),
		      dest->cpp,
		      dest->pitch,
		      destx, desty,
		      width, height,
		      intel_region_map(intel, src),
		      srcx, srcy,
		      src->pitch);      

      intel_region_unmap(intel, dest);
      intel_region_unmap(intel, src);      
   }
   
   UNLOCK_HARDWARE(intel);
}

/* Fill a rectangular sub-region.  Need better logic about when to
 * push buffers into AGP - will currently do so whenever possible.
 */
void intel_region_fill( struct intel_context *intel,
			struct intel_region *dest,
			GLuint destx, GLuint desty,
			GLuint width, GLuint height,
			GLuint color )
{
   unsigned dst_offset;
   LOCK_HARDWARE(intel);

   bmClearBufferList(intel->bm);
   bmAddBuffer(intel->bm, dest->buffer, BM_WRITE, NULL, &dst_offset);

   if (bmValidateBufferList(intel->bm, BM_NO_EVICT)) {
      intelEmitFillBlitLocked(intel,
			      dest->cpp,
			      dest->pitch,
			      dst_offset, 
			      destx, desty,
			      width, height,
			      color );

      bmReleaseValidatedBuffers(intel->bm);
   }
   else {
      _mesa_fill_rect(intel_region_map(intel, dest),
		      dest->cpp,
		      dest->pitch,
		      destx, desty,
		      destx + width, desty + height,
		      color);      

      intel_region_unmap(intel, dest);
   }
   
   UNLOCK_HARDWARE(intel);

}

