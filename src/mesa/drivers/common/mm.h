/**
 * \file mm.h
 * \brief Memory block management.
 */

/*
 * Copyright (C) 1999 Keith Whitwell
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * KEITH WHITWELL, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef MM_INC
#define MM_INC

/**
 * \brief Memory block/heap.
 */
struct mem_block_t {
  struct mem_block_t *next; /**< \brief pointer to next block in the heap */
  struct mem_block_t *heap; /**< \brief pointer to the heap (first block) */
  int ofs;                  /**< \brief offset */
  int size;                 /**< \brief size */
  int align;                /**< \brief alignment */
  int free:1;               /**< \brief free flag */
  int reserved:1;           /**< \brief reserved flag */
};

/**
 * \brief Memory block.
 */
typedef struct mem_block_t TMemBlock;

/**
 * \brief Memory block pointer.
 */
typedef struct mem_block_t *PMemBlock;

/**
 * \brief Memory heap.
 * 
 * \note A heap is just the first block in a chain 
 */
typedef struct mem_block_t memHeap_t;

/**
 * \brief Get Memory block size.
 */
static __inline__ int mmBlockSize(PMemBlock b)
{ return b->size; }

/**
 * \brief Get Memory block offset.
 */
static __inline__ int mmOffset(PMemBlock b)
{ return b->ofs; }

memHeap_t *mmInit( int ofs, int size );

PMemBlock  mmAllocMem( memHeap_t *heap, int size, int align2, 
		       int startSearch );

int  mmFreeMem( PMemBlock b );

void mmDestroy( memHeap_t *heap );

void mmDumpMemInfo( memHeap_t *heap );

#endif
