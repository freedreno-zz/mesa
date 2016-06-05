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

#include "util/u_memory.h"

#include "rsq_batch.h"
#include "rsq_context.h"
#include "rsq_draw.h"
#include "rsq_state.h"

static struct rsq_batch_chunk * chunk_alloc(struct rsq_context *ctx)
{
   struct rsq_batch_chunk *chunk = util_slab_alloc(&ctx->slab);
   chunk->rd_idx = chunk->wr_idx = 0;
   chunk->next = NULL;
   return chunk;
}

struct rsq_batch * rsq_batch_create(struct rsq_context *ctx)
{
   struct rsq_batch *batch = CALLOC_STRUCT(rsq_batch);

   if (!batch)
      return NULL;

   pipe_reference_init(&batch->reference, 1);
   batch->ctx = ctx;

   batch->first = batch->current = chunk_alloc(ctx);

   return batch;
}

void _rsq_batch_destroy(struct rsq_batch *batch)
{
   struct rsq_batch_chunk *current = batch->first;

   while (current) {
      struct rsq_batch_chunk *next = current->next;
      util_slab_free(&batch->ctx->slab, current);
      current = next;
   }

   free(batch);
}

void * rsq_batch_emit_buf(struct rsq_batch *batch, unsigned sz)
{
   struct rsq_batch_chunk *chunk = batch->current;
   void *ptr;

   if ((chunk->wr_idx + sz) > sizeof(chunk->buf)) {
      struct rsq_batch_chunk *n = chunk_alloc(batch->ctx);
      chunk->next = n;
      chunk = batch->current = n;
   }

   ptr = &chunk->buf[chunk->wr_idx];
   chunk->wr_idx += sz;

   return ptr;
}

void * rsq_batch_consume_buf(struct rsq_batch *batch, unsigned sz)
{
   struct rsq_batch_chunk *chunk = batch->current;
   void *ptr;

   ptr = &chunk->buf[chunk->rd_idx];
   chunk->rd_idx += sz;

   /* this should only happen if we have mismatched emit's and consumes: */
   debug_assert(chunk->rd_idx <= chunk->wr_idx);

   if (chunk->rd_idx == chunk->wr_idx)
      batch->current = chunk->next;

   return ptr;
}

void rsq_batch_flush(struct rsq_batch *batch)
{
   if (!batch || batch->flushed)
      return;

   /* TODO if we had out-of-order already, this is where we'd need
    * to recursively flush our dependencies..
    */

   /* reset position to beginning: */
   batch->current = batch->first;

   if (batch->current->wr_idx == 0)
      return;

   while (batch->current) {
      enum rsq_state_id id = rsq_batch_consume_uint(batch);
      switch (id) {
      case rsq_string_marker_cmd:
         rsq_replay_emit_string_marker(batch);
         break;
      case rsq_draw_cmd:
         rsq_replay_draw_vbo(batch);
         break;
      case rsq_clear_cmd:
         rsq_replay_clear(batch);
         break;
      case rsq_launch_grid_cmd:
         rsq_replace_launch_grid(batch);
         break;
      case rsq_copy_region_cmd:
         rsq_replay_copy_region(batch);
         break;
      case rsq_blit_cmd:
         rsq_replay_blit(batch);
         break;
      default:
         rsq_context_replay(batch, id);
         break;
      }
   }

   batch->flushed = true;
}
