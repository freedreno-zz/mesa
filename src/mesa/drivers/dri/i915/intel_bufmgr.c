/**************************************************************************
 * 
 * Copyright 2006 Tungsten Graphics, Inc., Steamboat Springs, CO.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE 
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 * 
 * 
 **************************************************************************/

#include "intel_bufmgr.h"

#include "intel_context.h"
#include "intel_ioctl.h"

#include "hash.h"
#include "simple_list.h"
#include "mm.h"
#include "imports.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <drm.h>

struct _mesa_HashTable;
struct bufmgr
{
   struct intel_context *intel;
   struct _mesa_HashTable *hash;

   unsigned buf_nr;			/* for generating ids */
   drmMMPool batchPool;
};

/***********************************************************************
 * Public functions
 */

/* The initialization functions are skewed in the fake implementation.
 * This call would be to attach to an existing manager, rather than to
 * create a local one.
 */

struct bufmgr *
bm_intel_Attach(struct intel_context *intel)
{
   struct bufmgr *bm = (struct bufmgr *)calloc(sizeof(*bm), 1);

   bm->intel = intel;
   bm->hash = _mesa_NewHashTable();

   drmGetLock(bm->intel->driFd, bm->intel->hHWContext, 0);
   assert(!drmMMAllocBufferPool(bm->intel->driFd, mmPoolRing, 0,
				BM_BATCHBUFFER | DRM_MM_TT |
				DRM_MM_NO_EVICT ,
				1024 * 1024, 4096, &bm->batchPool));

   drmUnlock(bm->intel->driFd, bm->intel->hHWContext);
   return bm;
}

void
bmGenBuffers(struct bufmgr *bm, unsigned n, unsigned *buffers, unsigned flags)
{
   unsigned i;
   unsigned bFlags =
	 (flags) ? flags : DRM_MM_TT | DRM_MM_VRAM | DRM_MM_SYSTEM;
   for (i = 0; i < n; i++) {
      drmMMBuf *buf = calloc(sizeof(*buf), 1);

      assert(!drmMMInitBuffer(bm->intel->driFd, bFlags, 12, buf));
      buf->client_priv = ++bm->buf_nr;
      buffers[i] = buf->client_priv;
      _mesa_HashInsert(bm->hash, buffers[i], buf);
   }
}

void
bmSetShared(struct bufmgr *bm, unsigned buffer, unsigned flags,
	    unsigned long offset, void *virtual)
{
   drmMMBuf *buf = _mesa_HashLookup(bm->hash, buffer);

   buf->flags = DRM_MM_NO_EVICT | DRM_MM_NO_MOVE | DRM_MM_SHARED;
   buf->flags |= flags & DRM_MM_MEMTYPE_MASK;
   buf->offset = offset;
   buf->virtual = virtual;
   assert(!drmMMAllocBuffer(bm->intel->driFd, 0, NULL, 0, buf));
}

void
bmDeleteBuffers(struct bufmgr *bm, unsigned n, unsigned *buffers)
{
   unsigned i;

   assert(0);
   for (i = 0; i < n; i++) {
      drmMMBuf *buf = _mesa_HashLookup(bm->hash, buffers[i]);

      drmMMFreeBuffer(bm->intel->driFd, buf);
   }
}

/* If buffer size changes, free and reallocate.  Otherwise update in
 * place.
 */

void
bmBufferData(struct bufmgr *bm,
	     unsigned buffer, unsigned size, const void *data, unsigned flags)
{
   drmMMBuf *buf = (drmMMBuf *) _mesa_HashLookup(bm->hash, buffer);

   DBG("bmBufferData %d sz 0x%x data: %p\n", buffer, size, data);

   assert(!buf->mapped);

   if (buf->flags & BM_BATCHBUFFER) {

      assert(!drmMMFreeBuffer(bm->intel->driFd, buf));
      assert(!drmMMAllocBuffer(bm->intel->driFd, size, &bm->batchPool, 1,
			       buf));

   } else if (!(buf->flags & DRM_MM_SHARED)) {

      if (buf->size < size || drmBufIsBusy(bm->intel->driFd, buf)) {
	 assert(!drmMMFreeBuffer(bm->intel->driFd, buf));
      }
      if (!buf->block) {
	 assert(!drmMMAllocBuffer(bm->intel->driFd, size, NULL, 0, buf));
      }

   }

   if (data != NULL) {

      memcpy(bmMapBuffer(bm, buf->client_priv, flags), data, size);
      bmUnmapBuffer(bm, buf->client_priv);

   }
}

/* Update the buffer in place, in whatever space it is currently resident:
 */
void
bmBufferSubData(struct bufmgr *bm,
		unsigned buffer,
		unsigned offset, unsigned size, const void *data)
{
   drmMMBuf *buf = (drmMMBuf *) _mesa_HashLookup(bm->hash, buffer);

   DBG("bmBufferSubdata %d offset 0x%x sz 0x%x\n", buffer, offset, size);

   drmBufWaitBusy(bm->intel->driFd, buf);

   if (size) {
      memcpy(bmMapBuffer(bm, buf->client_priv, 0) + offset, data, size);
      bmUnmapBuffer(bm, buf->client_priv);
   }
}

/* Extract data from the buffer:
 */
void
bmBufferGetSubData(struct bufmgr *bm,
		   unsigned buffer,
		   unsigned offset, unsigned size, void *data)
{
   drmMMBuf *buf = (drmMMBuf *) _mesa_HashLookup(bm->hash, buffer);

   DBG("bmBufferSubdata %d offset 0x%x sz 0x%x\n", buffer, offset, size);

   drmBufWaitBusy(bm->intel->driFd, buf);

   if (size) {
      memcpy(data, bmMapBuffer(bm, buf->client_priv, 0) + offset, size);
      bmUnmapBuffer(bm, buf->client_priv);
   }
}

/* Return a pointer to whatever space the buffer is currently resident in:
 */
void *
bmMapBuffer(struct bufmgr *bm, unsigned buffer, unsigned flags)
{
   drmMMBuf *buf = (drmMMBuf *) _mesa_HashLookup(bm->hash, buffer);

   DBG("bmMapBuffer %d\n", buffer);
   DBG("Map: Block is 0x%x\n", &buf->block);

   assert(!buf->mapped);
   return drmMMMapBuffer(bm->intel->driFd, buf);
}

void
bmUnmapBuffer(struct bufmgr *bm, unsigned buffer)
{
   drmMMBuf *buf = (drmMMBuf *) _mesa_HashLookup(bm->hash, buffer);

   if (!buf)
      return;

   DBG("bmUnmapBuffer %d\n", buffer);

   drmMMUnmapBuffer(bm->intel->driFd, buf);
}

/* Build the list of buffers to validate:
 */
struct _drmMMBufList *
bmNewBufferList(void)
{
   return drmMMInitListHead();
}

int
bmAddBuffer(struct bufmgr *bm,
	    struct _drmMMBufList *list,
	    unsigned buffer,
	    unsigned flags,
	    unsigned *memtype_return, unsigned long *offset_return)
{
   drmMMBuf *buf = (drmMMBuf *) _mesa_HashLookup(bm->hash, buffer);

   return drmMMBufListAdd(list, buf, 0, flags, memtype_return, offset_return);
}

void
bmFreeBufferList(struct _drmMMBufList *list)
{
   drmMMFreeBufList(list);
}

int
bmScanBufferList(struct bufmgr *bm,
		 struct _drmMMBufList *list, unsigned buffer)
{
   drmMMBuf *buf = (drmMMBuf *) _mesa_HashLookup(bm->hash, buffer);

   return drmMMScanBufList(list, buf);
}

/* To be called prior to emitting commands to hardware which reference
 * these buffers.  The buffer_usage list provides information on where
 * the buffers should be placed and whether their contents need to be
 * preserved on copying.  The offset and pool data elements are return
 * values from this function telling the driver exactly where the
 * buffers are currently located.
 */

int
bmValidateBufferList(struct bufmgr *bm,
		     struct _drmMMBufList *list, unsigned flags)
{
   return drmMMValidateBuffers(bm->intel->driFd, list);
}

/* After commands are emitted but before unlocking, this must be
 * called so that the buffer manager can correctly age the buffers.
 * The buffer manager keeps track of the list of validated buffers, so
 * already knows what to apply the fence to.
 *
 * The buffer manager knows how to emit and test fences directly
 * through the drm and without callbacks or whatever into the driver.
 */
unsigned
bmFenceBufferList(struct bufmgr *bm, struct _drmMMBufList *list)
{
   drmFence fence;

   assert(!drmMMFenceBuffers(bm->intel->driFd, list));
   assert(!drmEmitFence(bm->intel->driFd, 0, &fence));

   return fence.fenceSeq;
}

/* This functionality is used by the buffer manager, not really sure
 * if we need to be exposing it in this way, probably libdrm will
 * offer equivalent calls.
 *
 * For now they can stay, but will likely change/move before final:
 */
unsigned
bmSetFence(struct bufmgr *bm)
{
   drmFence dFence;

   assert(!drmEmitFence(bm->intel->driFd, 0, &dFence));

   return dFence.fenceSeq;
}

int
bmTestFence(struct bufmgr *bm, unsigned fence)
{
   drmFence dFence = { 0, fence };
   int retired;

   assert(!drmTestFence(bm->intel->driFd, dFence, 0, &retired));
   return retired;
}

void
bmFinishFence(struct bufmgr *bm, unsigned fence)
{
   drmFence dFence = { 0, fence };
   assert(!drmWaitFence(bm->intel->driFd, dFence));
}
