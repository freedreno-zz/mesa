/*
 * Copyright © 2016 Red Hat
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef RSQ_BATCH_H
#define RSQ_BATCH_H

#include "util/u_inlines.h"

struct rsq_batch_chunk {
   unsigned rd_idx, wr_idx;
   struct rsq_batch_chunk *next;
   uint8_t buf[4096];             /* TODO what is a reasonable size? */
};

struct rsq_batch {
   struct pipe_reference reference;
   struct rsq_context *ctx;
   bool flushed;
   struct rsq_batch_chunk *current, *first;
};

struct rsq_batch * rsq_batch_create(struct rsq_context *ctx);
void _rsq_batch_destroy(struct rsq_batch *batch);

static inline void
rsq_batch_reference(struct rsq_batch **ptr, struct rsq_batch *batch)
{
   if (pipe_reference(&(*ptr)->reference, &batch->reference))
      _rsq_batch_destroy(*ptr);
   *ptr = batch;
}

void *rsq_batch_emit_buf(struct rsq_batch *batch, unsigned sz);

static inline void rsq_batch_emit_uint(struct rsq_batch *batch, unsigned val)
{
   unsigned *ptr = rsq_batch_emit_buf(batch, sizeof(*ptr));
   *ptr = val;
}

void *rsq_batch_consume_buf(struct rsq_batch *batch, unsigned sz);

static inline unsigned rsq_batch_consume_uint(struct rsq_batch *batch)
{
   unsigned *ptr = rsq_batch_consume_buf(batch, sizeof(*ptr));
   return *ptr;
}

void rsq_batch_flush(struct rsq_batch *batch);

#endif /* RSQ_BATCH_H */
