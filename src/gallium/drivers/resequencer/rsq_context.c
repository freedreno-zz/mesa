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
#include "rsq_resource.h"
#include "rsq_state.h"
#include "rsq_surface.h"
#include "rsq_query.h"

static void rsq_context_destroy(struct pipe_context *pctx)
{
   struct rsq_context *ctx = rsq_context(pctx);

   rsq_batch_flush(ctx->batch);
   rsq_batch_reference(&ctx->batch, NULL);

   ctx->drv->destroy(ctx->drv);

   util_slab_destroy(&ctx->slab);

   free(ctx);
}

static void rsq_set_debug_callback(struct pipe_context *pctx,
                                   const struct pipe_debug_callback *cb)
{
   struct rsq_context *ctx = rsq_context(pctx);
   ctx->drv->set_debug_callback(ctx->drv, cb);
}

static void rsq_get_sample_position(struct pipe_context *pctx,
                                    unsigned sample_count,
                                    unsigned sample_index,
                                    float *out_value)
{
   struct rsq_context *ctx = rsq_context(pctx);
   ctx->drv->get_sample_position(ctx->drv, sample_count, sample_index, out_value);
}

static enum pipe_reset_status rsq_get_device_reset_status(struct pipe_context *pctx)
{
   /* presumably this is async to rendering and doesn't require flushing? */
   struct rsq_context *ctx = rsq_context(pctx);
   return ctx->drv->get_device_reset_status(ctx->drv);
}

static void rsq_dump_debug_state(struct pipe_context *pctx, FILE *stream,
                                 unsigned flags)
{
   struct rsq_context *ctx = rsq_context(pctx);
   ctx->drv->dump_debug_state(ctx->drv, stream, flags);
}

/*
 * Handle sampler-views manually since it doesn't quite fit the CSO mold.
 * Perhaps should be refactored to be a normal CSO?
 */

struct rsq_sampler_view {
   struct pipe_sampler_view base;
   unsigned seqno;
   struct pipe_sampler_view *drv;
};

static inline struct rsq_sampler_view *
rsq_sampler_view(struct pipe_sampler_view *pview)
{
   return (struct rsq_sampler_view *)pview;
}

static struct pipe_sampler_view *
rsq_create_sampler_view(struct pipe_context *pctx,
                        struct pipe_resource *texture,
                        const struct pipe_sampler_view *templat)
{
   struct rsq_sampler_view *view = CALLOC_STRUCT(rsq_sampler_view);
   if (!view)
      return NULL;
   view->base = *templat;
   pipe_reference_init(&view->base.reference, 1);
   pipe_reference(NULL, &texture->reference);
   view->base.texture = texture;
   view->base.context = pctx;
   return &view->base;
}

static void rsq_sampler_view_destroy(struct pipe_context *pctx,
                                     struct pipe_sampler_view *pview)
{
   struct rsq_sampler_view *view = rsq_sampler_view(pview);
   pipe_sampler_view_reference(&view->drv, NULL);
   free(view);
}

static struct pipe_sampler_view *
rsq_sampler_view_validate(struct pipe_sampler_view *pview)
{
   struct rsq_sampler_view *view = rsq_sampler_view(pview);

   if (!pview)
      return NULL;

   if (view->seqno != seqno(pview->texture))
      pipe_sampler_view_reference(&view->drv, NULL);

   if (!view->drv) {
      struct rsq_context *ctx = rsq_context(pview->context);
      view->drv = ctx->drv->create_sampler_view(ctx->drv,
                                                unwrap(pview->texture),
                                                pview);
      view->seqno = seqno(pview->texture);
   }

   return view->drv;
}

static void rsq_set_sampler_views(struct pipe_context *pctx, unsigned shader,
                                  unsigned start_slot, unsigned num_views,
                                  struct pipe_sampler_view **pviews)
{
   struct rsq_context *ctx = rsq_context(pctx);

   debug_assert(start_slot == 0);

   for (unsigned i = 0; i < num_views; i++) {
      pipe_sampler_view_reference(&ctx->sampler_view[shader][i], pviews[i]);
      ctx->dirty_sampler_view[shader] |= (1 << i);
      if (pviews[i])
         ctx->valid_sampler_view[shader] |= (1 << i);
      else
         ctx->valid_sampler_view[shader] &= ~(1 << i);
   }

   ctx->state.dirty |= (1 << rsq_sampler_view_id);
   ctx->dirty_sampler_view_shader |= (1 << shader);
   if (ctx->valid_sampler_view[shader])
      ctx->valid_sampler_view_shader |= (1 << shader);
   else
      ctx->valid_sampler_view_shader &= ~(1 << shader);
}

/*
 * Handle stream-output-target manually since it doesn't quite fit the
 * CSO mold..  perhaps should be refactored into a normal CSO?
 */

struct rsq_stream_output_target {
   struct pipe_stream_output_target base;
   unsigned seqno;
   struct pipe_stream_output_target *drv;
};

static inline struct rsq_stream_output_target *
rsq_stream_output_target(struct pipe_stream_output_target *ptarget)
{
   return (struct rsq_stream_output_target *)ptarget;
}

static struct pipe_stream_output_target *
rsq_create_stream_output_target(struct pipe_context *pctx,
                                struct pipe_resource *prsc,
                                unsigned buffer_offset,
                                unsigned buffer_size)
{
   struct rsq_stream_output_target *target = CALLOC_STRUCT(rsq_stream_output_target);
   if (!target)
      return NULL;
   pipe_reference_init(&target->base.reference, 1);
   pipe_resource_reference(&target->base.buffer, prsc);
   target->base.context = pctx;
   target->base.buffer_offset = buffer_offset;
   target->base.buffer_size = buffer_size;
   return &target->base;
}

static void rsq_stream_output_target_destroy(struct pipe_context *pctx,
                                             struct pipe_stream_output_target *ptarget)
{
   struct rsq_stream_output_target *target = rsq_stream_output_target(ptarget);
   pipe_so_target_reference(&target->drv, NULL);
   free(target);
}

static struct pipe_stream_output_target *
rsq_stream_output_target_validate(struct pipe_stream_output_target *ptarget)
{
   struct rsq_stream_output_target *target = rsq_stream_output_target(ptarget);

   if (!ptarget)
      return NULL;

   if (target->seqno != seqno(ptarget->buffer))
      pipe_so_target_reference(&target->drv, NULL);

   if (!target->drv) {
      struct rsq_context *ctx = rsq_context(ptarget->context);
      target->drv = ctx->drv->create_stream_output_target(ctx->drv,
                                                          unwrap(ptarget->buffer),
                                                          ptarget->buffer_offset,
                                                          ptarget->buffer_size);
      target->seqno = seqno(ptarget->buffer);
   }

   return target->drv;
}

static void rsq_set_stream_output_targets(struct pipe_context *pctx,
                                          unsigned num_targets,
                                          struct pipe_stream_output_target **ptargets,
                                          const unsigned *offsets)
{
   struct rsq_context *ctx = rsq_context(pctx);
   unsigned i;

   for (i = 0; i < num_targets; i++) {
      pipe_so_target_reference(&ctx->so_targets[i], ptargets[i]);
      ctx->so_offsets[i] = offsets[i];
   }

   for ( ; i < ARRAY_SIZE(ctx->so_targets); i++)
      pipe_so_target_reference(&ctx->so_targets[i], NULL);

   ctx->nr_so_targets = num_targets;
   ctx->state.dirty |= (1 << rsq_stream_output_target_id);
}

/**
 * Emit state.  This serializes all the dirty state into the current batch,
 * for example prior to emitting a draw cmd.  This includes state which is
 * implicitly dirty due to a shadowed resource.
 */
void rsq_context_emit(struct pipe_context *pctx)
{
   struct rsq_context *ctx = rsq_context(pctx);
   unsigned idx_mask, shader_mask;
   int idx, shader;

   /* detect if state is dirty due to resource shadowing: */
   if (unlikely(ctx->dirty_clone)) {
      shader_mask = ctx->valid_sampler_view_shader;
      while ((shader = util_last_bit(shader_mask) - 1) >= 0) {
         idx_mask = ctx->valid_sampler_view[shader];
         while ((idx = util_last_bit(idx_mask) - 1) >= 0) {
            struct pipe_sampler_view *pview = ctx->sampler_view[shader][idx];
            if (!pview)
               continue;
            struct rsq_sampler_view *view = rsq_sampler_view(pview);
            if (view->seqno != seqno(pview->texture)) {
               ctx->dirty_sampler_view_shader |= (1 << shader);
               ctx->dirty_sampler_view[shader] |= (1 << idx);
               ctx->state.dirty |= (1 << rsq_sampler_view_id);
               break;
            }
            idx_mask &= ~(1 << idx);
         }
         shader_mask &= ~(1 << shader);
      }
   }

   if (ctx->state.dirty & (1 << rsq_sampler_view_id)) {
      shader_mask = ctx->dirty_sampler_view_shader;
      while ((shader = util_last_bit(shader_mask) - 1) >= 0) {
         idx_mask = ctx->dirty_sampler_view[shader];
         while ((idx = util_last_bit(idx_mask) - 1) >= 0) {
            struct pipe_sampler_view **ptr;
            struct pipe_sampler_view *pview =
               rsq_sampler_view_validate(ctx->sampler_view[shader][idx]);

            rsq_batch_emit_uint(ctx->batch, rsq_sampler_view_id);
            rsq_batch_emit_uint(ctx->batch, shader);
            rsq_batch_emit_uint(ctx->batch, idx);
            ptr = rsq_batch_emit_buf(ctx->batch, sizeof(*ptr));
            *ptr = NULL;
            pipe_sampler_view_reference(ptr, pview);

            idx_mask &= ~(1 << idx);
         }
         ctx->dirty_sampler_view[shader] = 0;
         shader_mask &= ~(1 << shader);
      }
      ctx->dirty_sampler_view_shader = 0;
   }

   /* detect if state is dirty due to resource shadowing: */
   if (unlikely(ctx->dirty_clone)) {
      for (unsigned idx = 0; idx < ctx->nr_so_targets; idx++) {
         struct pipe_stream_output_target *ptarget = ctx->so_targets[idx];
         if (!ptarget)
            continue;
         struct rsq_stream_output_target *target = rsq_stream_output_target(ptarget);
         if (target->seqno != seqno(ptarget->buffer)) {
            ctx->state.dirty |= (1 << rsq_stream_output_target_id);
            break;
         }
      }
   }

   if (ctx->state.dirty & (1 << rsq_stream_output_target_id)) {
      struct pipe_stream_output_target **ptr;
      unsigned *offsets;

      rsq_batch_emit_uint(ctx->batch, rsq_stream_output_target_id);
      rsq_batch_emit_uint(ctx->batch, ctx->nr_so_targets);

      ptr = rsq_batch_emit_buf(ctx->batch, sizeof(*ptr) * ctx->nr_so_targets);
      for (unsigned idx = 0; idx < ctx->nr_so_targets; idx++) {
         struct pipe_stream_output_target *ptarget =
            rsq_stream_output_target_validate(ctx->so_targets[idx]);
         ptr[idx] = NULL;
         pipe_so_target_reference(&ptr[idx], ptarget);
      }

      offsets = rsq_batch_emit_buf(ctx->batch, sizeof(*offsets) * ctx->nr_so_targets);
      memcpy(offsets, ctx->so_offsets, sizeof(*offsets) * ctx->nr_so_targets);
   }

   /* Most of it is handled by the generated code: */
   rsq_state_emit(pctx);

   ctx->dirty_clone = false;
}

void rsq_context_replay(struct rsq_batch *batch, enum rsq_state_id id)
{
   struct rsq_context *ctx = batch->ctx;

   switch (id) {
   /* specially handled state: */
   case rsq_sampler_view_id: {
      unsigned shader = rsq_batch_consume_uint(batch);
      unsigned idx = rsq_batch_consume_uint(batch);
      struct pipe_sampler_view **ptr = rsq_batch_consume_buf(batch, sizeof(*ptr));

      ctx->drv->set_sampler_views(ctx->drv, shader, idx, 1, ptr);
      pipe_sampler_view_reference(ptr, NULL);

      break;
   }
   case rsq_stream_output_target_id: {
      unsigned nr_so_targets = rsq_batch_consume_uint(batch);
      struct pipe_stream_output_target **ptr =
         rsq_batch_consume_buf(ctx->batch, sizeof(*ptr) * nr_so_targets);
      unsigned *offsets =
         rsq_batch_consume_buf(ctx->batch, sizeof(*offsets) * nr_so_targets);

      ctx->drv->set_stream_output_targets(ctx->drv, nr_so_targets,
                                          ptr, offsets);

      for (unsigned idx; idx < nr_so_targets; idx++)
         pipe_so_target_reference(&ptr[idx], NULL);

      break;
   }
   default:
      rsq_state_replay(batch, id);
   }
}

/**
 * Update current batch when framebuffer state has changed
 */
void rsq_context_update_batch(struct pipe_context *pctx,
                              const struct pipe_framebuffer_state *pfb)
{
   struct rsq_context *ctx = rsq_context(pctx);

   /* TODO, no out of order yet, otherwise we'd use *pfb as key
    * into hashtable
    *
    * TODO we might need to sanitize the key w/ surf seqno's?
    * At least if the batch is not holding a ref to the surface..
    */

   rsq_batch_flush(ctx->batch);
   rsq_batch_reference(&ctx->batch, NULL);

   ctx->batch = rsq_batch_create(ctx);
}

struct pipe_context * rsq_context_create(struct pipe_screen *pscreen,
                                         void *priv, unsigned flags)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   struct rsq_context *ctx = CALLOC_STRUCT(rsq_context);

   if (!ctx)
      return NULL;

   ctx->drv = screen->drv->context_create(screen->drv, ctx, flags);
   if (!ctx->drv) {
      free(ctx);
      return NULL;
   }

   ctx->screen = screen;

   struct pipe_context *pctx = &ctx->base;
   pctx->priv = priv;
   pctx->screen = pscreen;
   pctx->destroy = rsq_context_destroy;

   CTX_INIT(set_debug_callback);
   CTX_INIT(get_sample_position);
   CTX_INIT(get_device_reset_status);
   CTX_INIT(dump_debug_state);

   pctx->create_surface = rsq_create_surface;
   pctx->surface_destroy = rsq_surface_destroy;

   CTX_INIT(create_stream_output_target);
   CTX_INIT(stream_output_target_destroy);
   CTX_INIT(set_stream_output_targets);

   CTX_INIT(create_sampler_view);
   CTX_INIT(sampler_view_destroy);
   CTX_INIT(set_sampler_views);

//   CTX_INIT(texture_barrier);
//   CTX_INIT(memory_barrier);

//   CTX_INIT(create_video_codec);
//   CTX_INIT(create_video_buffer);

   rsq_draw_context_init(pctx);
   rsq_resource_context_init(pctx);
   rsq_query_context_init(pctx);
   rsq_state_context_init(pctx);

   util_slab_create(&ctx->slab, sizeof(struct rsq_batch_chunk),
                    16, UTIL_SLAB_SINGLETHREADED);

   return pctx;
}
