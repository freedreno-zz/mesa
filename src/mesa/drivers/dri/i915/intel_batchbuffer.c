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
