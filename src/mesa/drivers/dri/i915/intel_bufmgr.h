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

#ifndef BUFMGR_H
#define BUFMGR_H

#include "intel_context.h"


/* The buffer manager context.  Opaque.
 */
struct bufmgr;
struct buffer;

struct bufmgr *bm_intel_Attach(struct intel_context *intel);

#define BM_BATCHBUFFER      0x10000000	/* for map - pointer will be accessed
					 * without dri lock */

/* Stick closely to ARB_vbo semantics - they're well defined and
 * understood, and drivers can just pass the calls through without too
 * much thunking.
 */
void bmGenBuffers(struct intel_context *, 
		  const char *name, 
		  unsigned n, struct buffer **buffers,
		  unsigned flags);

void bmDeleteBuffers(struct intel_context *, unsigned n, struct buffer **buffers);

/* The driver has more intimate knowledge of the hardare than a GL
 * client would, so flags here is more proscriptive than the usage
 * values in the ARB_vbo interface:
 */
void bmBufferData(struct intel_context *,
		  struct buffer *buffer,
		  unsigned size, const void *data, unsigned flags);

void bmBufferSubData(struct intel_context *,
		     struct buffer *buffer,
		     unsigned offset, unsigned size, const void *data);

void bmBufferGetSubData(struct intel_context *,
			struct buffer *buffer,
			unsigned offset, unsigned size, void *data);

void *bmMapBuffer(struct intel_context *, struct buffer *buffer, unsigned access);

void bmUnmapBuffer(struct intel_context *, struct buffer *buffer);

/* To be called prior to emitting commands to hardware which reference
 * these buffers.  
 *
 * NewBufferList() and AddBuffer() build up a list of buffers to be
 * validated.  The buffer list provides information on where the
 * buffers should be placed and whether their contents need to be
 * preserved on copying.  The offset data elements are return values
 * from this function telling the driver exactly where the buffers are
 * currently located.
 *
 * ValidateBufferList() performs the actual validation and returns the
 * buffer pools and offsets within the pools.
 *
 * FenceBufferList() must be called to set fences and other
 * housekeeping before unlocking after a successful call to
 * ValidateBufferList(). The buffer manager knows how to emit and test
 * fences directly through the drm and without callbacks to the
 * driver.
 */
struct _drmMMBufList *bmNewBufferList(void);

int bmAddBuffer(struct intel_context *,
		struct _drmMMBufList *list,
		struct buffer *buffer,
		unsigned flags,
		unsigned *pool_return, unsigned long *offset_return);

int bmValidateBufferList(struct intel_context *,
			 struct _drmMMBufList *, unsigned flags);

unsigned bmFenceBufferList(struct intel_context *, struct _drmMMBufList *);

void bmFreeBufferList(struct _drmMMBufList *);

int bmScanBufferList(struct intel_context *,
		     struct _drmMMBufList *list, struct buffer *buffer);

/* This functionality is used by the buffer manager, not really sure
 * if we need to be exposing it in this way, probably libdrm will
 * offer equivalent calls.
 *
 * For now they can stay, but will likely change/move before final:
 */
unsigned bmSetFence(struct intel_context *);
int bmTestFence(struct intel_context *, unsigned fence);
void bmFinishFence(struct intel_context *, unsigned fence);
unsigned bmInitFence(struct intel_context *);
void bmSetShared(struct intel_context *, struct buffer *buffer,
		 unsigned flags, unsigned long offset, void *virtual);

#endif
