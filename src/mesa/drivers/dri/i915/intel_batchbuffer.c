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

#include "intel_batchbuffer.h"
#include "intel_ioctl.h"
#include "bufmgr.h"

/* Relocations in kernel space:
 *    - pass dma buffer seperately
 *    - memory manager knows how to patch
 *    - pass list of dependent buffers
 *    - pass relocation list
 *
 * Either:
 *    - get back an offset for buffer to fire
 *    - memory manager knows how to fire buffer
 *
 * Really want the buffer to be AGP and pinned.
 *
 */

/* Cliprect fence: The highest fence protecting a dma buffer
 * containing explicit cliprect information.  Like the old drawable
 * lock but irq-driven.  X server must wait for this fence to expire
 * before changing cliprects [and then doing sw rendering?].  For
 * other dma buffers, the scheduler will grab current cliprect info
 * and mix into buffer.  X server must hold the lock while changing
 * cliprects???  Make per-drawable.  Need cliprects in shared memory
 * -- beats storing them with every cmd buffer in the queue.
 *
 * ==> X server must wait for this fence to expire before touching the
 * framebuffer with new cliprects.
 *
 * ==> Cliprect-dependent buffers associated with a
 * cliprect-timestamp.  All of the buffers associated with a timestamp
 * must go to hardware before any buffer with a newer timestamp.
 *
 * ==> Dma should be queued per-drawable for correct X/GL
 * synchronization.  Or can fences be used for this?
 *
 * Applies to: Blit operations, metaops, X server operations -- X
 * server automatically waits on its own dma to complete before
 * modifying cliprects ???
 */				

static void intel_dump_batchbuffer( unsigned offset,
				    int *ptr,
				    int count )
{
   int i;
   fprintf(stderr, "\n\n\nSTART BATCH (%d dwords):\n", count/4);
   for (i = 0; i < count/4; i += 4) 
      fprintf(stderr, "0x%x:\t0x%08x 0x%08x 0x%08x 0x%08x\n", 
	      offset + i*4, ptr[i], ptr[i+1], ptr[i+2], ptr[i+3]);
   fprintf(stderr, "END BATCH\n\n\n");
}


static void intel_batchbuffer_reset( struct intel_batchbuffer *batch )
{
   bmBufferData(batch->bm,
		batch->buffer,
		BATCH_SZ,
		NULL,
		0);
		
   if (!batch->list) 
      batch->list = bmNewBufferList();

   batch->list->nr = 0;
   batch->nr_relocs = 0;
   batch->flags = 0;

   bmAddBuffer( batch->list,
		batch->buffer,
		0,
		NULL,
		&batch->offset[batch->list->nr]);

   batch->map = bmMapBuffer(batch->bm, batch->buffer, 
			    BM_MEM_AGP|BM_MEM_LOCAL|BM_CLIENT|BM_WRITE);
   batch->ptr = batch->map;
}

/*======================================================================
 * Public functions
 */
struct intel_batchbuffer *intel_batchbuffer_alloc( struct intel_context *intel )
{
   struct intel_batchbuffer *batch = calloc(sizeof(*batch), 1);

   batch->intel = intel;
   batch->bm = intel->bm;

   bmGenBuffers(intel->bm, 1, &batch->buffer);
   intel_batchbuffer_reset( batch );
   return batch;
}

void intel_batchbuffer_free( struct intel_batchbuffer *batch )
{
   if (batch->map)
      bmUnmapBuffer(batch->bm, batch->buffer);
   
   free(batch);
}

/* TODO: Push this whole function into bufmgr.
 */
static void do_flush_locked( struct intel_batchbuffer *batch,
			     GLuint used,
			     GLboolean ignore_cliprects)
{
   GLuint *ptr;
   GLuint i;

   bmValidateBufferList( batch->bm, 
			 batch->list,
			 BM_MEM_AGP );

   /* Apply the relocations.  This nasty map indicates to me that the
    * whole task should be done internally by the memory manager, and
    * that dma buffers probably need to be pinned within agp space.
    */
   ptr = (GLuint *)bmMapBuffer(batch->bm, batch->buffer, 
			       BM_NO_MOVE|BM_NO_UPLOAD|
			       BM_NO_EVICT|BM_MEM_AGP|
			       BM_WRITE);

   for (i = 0; i < batch->nr_relocs; i++) {
      struct buffer_reloc *r = &batch->reloc[i];

      DBG("apply fixup at offset 0x%x, elem %d (buf %d, offset 0x%x), delta 0x%x\n",
	  r->offset, r->elem, batch->list->elem[r->elem].buffer,
	  batch->offset[r->elem], r->delta);

      ptr[r->offset/4] = batch->offset[r->elem] + r->delta;
   }

   if (0)
      intel_dump_batchbuffer( 0, ptr, used );



   bmUnmapBuffer(batch->bm, batch->buffer);


   /* Fire the batch buffer, which was uploaded above:
    */
   intel_batch_ioctl(batch->intel, 
		     batch->offset[0],
		     used,
		     ignore_cliprects);
   
   batch->last_fence = bmFenceBufferList(batch->bm, batch->list);
}



GLuint intel_batchbuffer_flush( struct intel_batchbuffer *batch )
{
   struct intel_context *intel = batch->intel;
   GLuint used = batch->ptr - batch->map;

   if (used == 0) 
      return batch->last_fence;

   /* Add the MI_BATCH_BUFFER_END: 
    */
   if (intel_batchbuffer_space(batch) & 4) {
      ((int *)batch->ptr)[0] = MI_BATCH_BUFFER_END;
      used += 4;
   }
   else {
      ((int *)batch->ptr)[0] = 0;
      ((int *)batch->ptr)[1] = MI_BATCH_BUFFER_END;
      used += 8;
   }

   bmUnmapBuffer(batch->bm, batch->buffer);
   batch->ptr = NULL;
   batch->map = NULL;

   /* TODO: Just pass the relocation list and dma buffer up to the
    * kernel.
    */
   if (!intel->locked)
   {
      assert(!(batch->flags & INTEL_BATCH_NO_CLIPRECTS));

      LOCK_HARDWARE(intel);
      do_flush_locked(batch, used, GL_FALSE);
      UNLOCK_HARDWARE(intel);
   }
   else {
      assert(!(batch->flags & INTEL_BATCH_CLIPRECTS));

      do_flush_locked(batch, used, GL_TRUE);
   }

   /* Reset the buffer:
    */
   intel_batchbuffer_reset( batch );
   return batch->last_fence;
}

void intel_batchbuffer_finish( struct intel_batchbuffer *batch )
{   
   bmFinishFence(batch->bm, 
		 intel_batchbuffer_flush(batch));
}
   

/*  This is the only way buffers get added to the validate list.
 */
GLboolean intel_batchbuffer_emit_reloc( struct intel_batchbuffer *batch,
					GLuint buffer,
					GLuint flags,
					GLuint delta )
{
   GLuint i;

   assert(batch->nr_relocs <= MAX_RELOCS);

   for (i = 0; i < batch->list->nr; i++) 
      if (buffer == batch->list->elem[i].buffer)
	 break;

   if (i == batch->list->nr) {
      if (i == BM_LIST_MAX)
	 return GL_FALSE;

      bmAddBuffer(batch->list,
		  buffer,
		  flags,
		  NULL,
		  &batch->offset[i]);
   }

   {
      struct buffer_reloc *r = &batch->reloc[batch->nr_relocs++];
      r->offset = batch->ptr - batch->map;
      r->delta = delta;
      r->elem = i;
   }

   batch->ptr += 4;
   return GL_TRUE;
}



void intel_batchbuffer_data(struct intel_batchbuffer *batch,
			    const void *data,
			    GLuint bytes,
			    GLuint flags)
{
   assert((bytes & 3) == 0);
   intel_batchbuffer_require_space(batch, bytes, flags);
   __memcpy(batch->ptr, data, bytes);
   batch->ptr += bytes;
}

