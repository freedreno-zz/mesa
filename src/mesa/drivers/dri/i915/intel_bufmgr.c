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

#include "simple_list.h"
#include "mm.h"
#include "imports.h"
#include "glthread.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <drm.h>

#define FILE_DEBUG_FLAG DEBUG_BUFMGR

/* The buffer manager is really part of the gl_shared_state struct.
 * TODO: Organize for the bufmgr to be created/deleted with the shared
 * state and stored within the DriverData of that struct.  Currently
 * there are no mesa callbacks for this.
 */
struct buffer {
   drmMMBuf drm_buf;
   const char *name;
   int refcount;
};


#define BM_MAX 16
static struct bufmgr
{
   _glthread_Mutex mutex;	/**< for thread safety */
   int refcount;
   int driFd;

   unsigned buf_nr;			/* for generating ids */
   drmMMPool batchPool;
   drmFence initFence;
} bufmgr_pool[BM_MAX];

static int nr_bms;

#define LOCK(bm) _glthread_LOCK_MUTEX(bm->mutex)
#define UNLOCK(bm) _glthread_UNLOCK_MUTEX(bm->mutex)

static void
bmError(int val, const char *file, const char *function, int line)
{
   _mesa_printf("Fatal video memory manager error \"%s\".\n"
		"Check kernel logs or set the LIBGL_DEBUG\n"
		"environment variable to \"verbose\" for more info.\n"
		"Detected in file %s, line %d, function %s.\n",
		strerror(-val), file, line, function);
#ifndef NDEBUG
   exit(-1);
#else
   abort();
#endif
}

#define BM_CKFATAL(val)					       \
  do{							       \
    int tstVal = (val);					       \
    if (tstVal) 					       \
      bmError(tstVal, __FILE__, __FUNCTION__, __LINE__);       \
  } while(0);

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
   GLuint i;

   for (i = 0; i < nr_bms; i++)
      if (bufmgr_pool[i].driFd == intel->driFd) {
	 bufmgr_pool[i].refcount++;
	 _mesa_printf("retrieive old bufmgr for fd %d\n",
		      bufmgr_pool[i].driFd);
	 return &bufmgr_pool[i];
      }

   if (nr_bms < BM_MAX) {
      struct bufmgr *bm = &bufmgr_pool[nr_bms++];

      _mesa_printf("create new bufmgr for fd %d\n", intel->driFd);
      bm->driFd = intel->driFd;
      bm->refcount = 1;
      _glthread_INIT_MUTEX(bm->mutex);

      drmGetLock(bm->driFd, intel->hHWContext, 0);
      BM_CKFATAL(drmMMAllocBufferPool(bm->driFd, mmPoolRing, 0,
				      DRM_MM_TT | DRM_MM_NO_EVICT |
				      DRM_MM_READ | DRM_MM_EXE |
				      BM_BATCHBUFFER, 1024 * 1024, 4096,
				      &bm->batchPool));

      
      BM_CKFATAL(drmEmitFence(bm->driFd, 0, &bm->initFence));
      drmUnlock(bm->driFd, intel->hHWContext);
      return bm;
   }

   _mesa_printf("failed to create new bufmgr for fd %d\n", intel->driFd);
   return NULL;
}

void
bmGenBuffers(struct intel_context *intel, 
	     const char *name,
	     unsigned n, struct buffer **buffers, unsigned flags)
{
   struct bufmgr *bm = intel->bm;

   LOCK(bm);
   {
      unsigned i;
      unsigned bFlags =
	    (flags) ? flags : DRM_MM_TT | DRM_MM_VRAM | DRM_MM_SYSTEM;

      for (i = 0; i < n; i++) {
	 struct buffer *buf = calloc(sizeof(*buf), 1);

	 BM_CKFATAL(drmMMInitBuffer(bm->driFd, bFlags, 12, &buf->drm_buf));
	 buf->refcount = 1;
	 buf->name = name;
	 buffers[i] = buf;
      }
   }
   UNLOCK(bm);
}

void
bmSetShared(struct intel_context *intel, struct buffer *buffer, unsigned flags,
	    unsigned long offset, void *virtual)
{
   struct bufmgr *bm = intel->bm;

   LOCK(bm);
   {
      buffer->drm_buf.flags = DRM_MM_NO_EVICT | DRM_MM_SHARED
	    | DRM_MM_WRITE | DRM_MM_READ;
      buffer->drm_buf.flags |= flags & DRM_MM_MEMTYPE_MASK;
      buffer->drm_buf.offset = offset;
      buffer->drm_buf.virtual = virtual;
      BM_CKFATAL(drmMMAllocBuffer(bm->driFd, 0, NULL, 0, &buffer->drm_buf));
   }
   UNLOCK(bm);
}

void
bmDeleteBuffers(struct intel_context *intel, unsigned n, struct buffer **buffers)
{
   struct bufmgr *bm = intel->bm;

   LOCK(bm);
   {
      unsigned i;

      for (i = 0; i < n; i++) {
	 struct buffer *buf = buffers[i];

	 if (buf) 
	    BM_CKFATAL(drmMMFreeBuffer(bm->driFd, &buf->drm_buf));
      }
   }
   UNLOCK(bm);
}

/* If buffer size changes, free and reallocate.  Otherwise update in
 * place.
 */

void
bmBufferData(struct intel_context *intel,
	     struct buffer *buffer, unsigned size, const void *data, unsigned flags)
{
   struct bufmgr *bm = intel->bm;

   LOCK(bm);
   {
      drmMMBuf *buf = &buffer->drm_buf;

      DBG("bmBufferData %d sz 0x%x data: %p\n", buffer, size, data);

      assert(buf);
      assert(!buf->mapped);
      assert(size);

      if (buf->flags & BM_BATCHBUFFER) {
	 BM_CKFATAL(drmMMFreeBuffer(bm->driFd, buf));
	 BM_CKFATAL(drmMMAllocBuffer
		    (bm->driFd, size, &bm->batchPool, 1, buf));
      } else if (!(buf->flags & DRM_MM_SHARED)) {

	 if (buf->block && (buf->size < size || drmBufIsBusy(bm->driFd, buf))) {
	    BM_CKFATAL(drmMMFreeBuffer(bm->driFd, buf));
	 }
	 if (!buf->block) {
	    BM_CKFATAL(drmMMAllocBuffer(bm->driFd, size, NULL, 0, buf));
	 }

      }

      if (data != NULL) {

	 memcpy(drmMMMapBuffer(bm->driFd, buf), data, size);
	 drmMMUnmapBuffer(bm->driFd, buf);

      }
   }
   UNLOCK(bm);
}

/* Update the buffer in place, in whatever space it is currently resident:
 */
void
bmBufferSubData(struct intel_context *intel,
		struct buffer *buffer,
		unsigned offset, unsigned size, const void *data)
{
   struct bufmgr *bm = intel->bm;

   LOCK(bm);
   {
      drmMMBuf *buf = &buffer->drm_buf;

      DBG("bmBufferSubdata %d offset 0x%x sz 0x%x\n", buffer, offset, size);

      assert(buf);
      drmBufWaitBusy(bm->driFd, buf);

      if (size) {
	 memcpy((unsigned char *) drmMMMapBuffer(bm->driFd, buf) + offset,
                data, size);
	 drmMMUnmapBuffer(bm->driFd, buf);
      }
   }
   UNLOCK(bm);
}

/* Extract data from the buffer:
 */
void
bmBufferGetSubData(struct intel_context *intel,
		   struct buffer *buffer,
		   unsigned offset, unsigned size, void *data)
{
   struct bufmgr *bm = intel->bm;

   LOCK(bm);
   {
      drmMMBuf *buf = &buffer->drm_buf;

      DBG("bmBufferSubdata %d offset 0x%x sz 0x%x\n", buffer, offset, size);

      assert(buf);
      drmBufWaitBusy(bm->driFd, buf);

      if (size) {
	 memcpy(data,
                (unsigned char *) drmMMMapBuffer(bm->driFd, buf) + offset,
                size);
	 drmMMUnmapBuffer(bm->driFd, buf);
      }
   }
   UNLOCK(bm);
}

/* Return a pointer to whatever space the buffer is currently resident in:
 */
void *
bmMapBuffer(struct intel_context *intel, 
	    struct buffer *buffer, unsigned flags)
{
   struct bufmgr *bm = intel->bm;
   void *retval;

   LOCK(bm);
   {
      drmMMBuf *buf = &buffer->drm_buf;

      DBG("bmMapBuffer %d\n", buffer);
      DBG("Map: Block is 0x%x\n", &buf->block);

      assert(buf);
      /* assert(!buf->mapped); */

      drmBufWaitBusy(bm->driFd, buf);

      retval = drmMMMapBuffer(bm->driFd, buf);
   }
   UNLOCK(bm);

   return retval;
}

void
bmUnmapBuffer(struct intel_context *intel, 
	      struct buffer *buffer)
{
   struct bufmgr *bm = intel->bm;

   LOCK(bm);
   {
      drmMMBuf *buf = &buffer->drm_buf;

      if (!buf)
	 goto out;

      DBG("bmUnmapBuffer %d\n", buffer);

      drmMMUnmapBuffer(bm->driFd, buf);
   }
 out:
   UNLOCK(bm);
}

/* Build the list of buffers to validate.  Note that the buffer list
 * isn't a shared structure so we don't need mutexes when manipulating
 * it.  
 *
 * XXX: need refcounting for drmMMBuf structs so that they can't be
 * deleted while on these lists.
 */
struct _drmMMBufList *
bmNewBufferList(void)
{
   return drmMMInitListHead();
}

int
bmAddBuffer(struct intel_context *intel,
	    struct _drmMMBufList *list,
	    struct buffer *buffer,
	    unsigned flags,
	    unsigned *memtype_return, unsigned long *offset_return)
{
   assert(buffer);
   return drmMMBufListAdd(list, &buffer->drm_buf, 0, flags, memtype_return, offset_return);
}

void
bmFreeBufferList(struct _drmMMBufList *list)
{
   drmMMFreeBufList(list);
}

int
bmScanBufferList(struct intel_context *intel,
		 struct _drmMMBufList *list, struct buffer *buffer)
{
   return drmMMScanBufList(list, &buffer->drm_buf);
}

/* To be called prior to emitting commands to hardware which reference
 * these buffers.  The buffer_usage list provides information on where
 * the buffers should be placed and whether their contents need to be
 * preserved on copying.  The offset and pool data elements are return
 * values from this function telling the driver exactly where the
 * buffers are currently located.
 */

int
bmValidateBufferList(struct intel_context *intel,
		     struct _drmMMBufList *list, unsigned flags)
{
   BM_CKFATAL(drmMMValidateBuffers(intel->driFd, list));
   return 0;
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
bmFenceBufferList(struct intel_context *intel, struct _drmMMBufList *list)
{
   drmFence fence;

   BM_CKFATAL(drmMMFenceBuffers(intel->driFd, list));
   BM_CKFATAL(drmEmitFence(intel->driFd, 0, &fence));

   return fence.fenceSeq;
}

/* This functionality is used by the buffer manager, not really sure
 * if we need to be exposing it in this way, probably libdrm will
 * offer equivalent calls.
 *
 * For now they can stay, but will likely change/move before final:
 */
unsigned
bmSetFence(struct intel_context *intel)
{
   drmFence dFence;

   BM_CKFATAL(drmEmitFence(intel->driFd, 0, &dFence));

   return dFence.fenceSeq;
}

int
bmTestFence(struct intel_context *intel, unsigned fence)
{
   drmFence dFence;
   int retired;

   dFence.fenceType = 0;
   dFence.fenceSeq = fence;
   BM_CKFATAL(drmTestFence(intel->driFd, dFence, 0, &retired));
   return retired;
}

void
bmFinishFence(struct intel_context *intel, unsigned fence)
{
   drmFence dFence;
   dFence.fenceType = 0;
   dFence.fenceSeq = fence;
   BM_CKFATAL(drmWaitFence(intel->driFd, dFence));
   intel->bm->initFence = dFence;
}

unsigned
bmInitFence(struct intel_context *intel)
{
   return intel->bm->initFence.fenceSeq;
}
