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

#ifndef INTEL_BATCHBUFFER_H
#define INTEL_BATCHBUFFER_H

#include "intel_context.h"
#include "intel_ioctl.h"


#define BATCH_LOCALS	GLubyte *batch_ptr;

#define VERBOSE 0


#define BEGIN_BATCH(n)							\
do {									\
   if (VERBOSE) fprintf(stderr, 					\
			"BEGIN_BATCH(%d) in %s, %d dwords free\n",	\
			(n), __FUNCTION__, intel->batch.space/4);	\
   assert(intel->locked); \
   if (intel->batch.space < (n)*4)					\
      intelFlushBatch(intel, GL_TRUE);					\
   batch_ptr = intel->batch.ptr;					\
} while (0)

#define OUT_BATCH(n)					\
do {							\
   *(GLuint *)batch_ptr = (n);				\
   if (VERBOSE) fprintf(stderr, " -- %08x at %s/%d\n", (n), __FILE__, __LINE__);	\
   batch_ptr += 4;					\
} while (0)

#define ADVANCE_BATCH()						\
do {								\
   if (VERBOSE) fprintf(stderr, "ADVANCE_BATCH()\n");		\
   intel->batch.space -= (batch_ptr - intel->batch.ptr);	\
   intel->batch.ptr = batch_ptr;				\
   assert(intel->batch.space >= 0);				\
} while(0)

extern void intelInitBatchBuffer( struct intel_context *intel );
extern void intelDestroyBatchBuffer( struct intel_context *intel );

void intelInstallBatchBuffer( struct intel_context *intel );


void intelValidateBuffers( struct intel_context *intel );

#endif
