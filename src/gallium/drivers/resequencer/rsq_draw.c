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

static void rsq_emit_string_marker(struct pipe_context *pctx,
                                    const char *string, int len)
{
   // TODO this needs to be written to batch..
}

void rsq_replay_emit_string_marker(struct rsq_batch *batch)
{
   // TODO
}

static void rsq_draw_vbo(struct pipe_context *pctx,
                         const struct pipe_draw_info *info)
{
   struct rsq_context *ctx = rsq_context(pctx);
   struct pipe_draw_info *ptr;

   /* TODO: */
   debug_assert(!info->count_from_stream_output);
   debug_assert(!info->indirect);
   debug_assert(!info->indirect_params);

   rsq_context_emit(pctx);

   rsq_batch_emit_uint(ctx->batch, rsq_draw_cmd);
   ptr = rsq_batch_emit_buf(ctx->batch, sizeof(*ptr));
   *ptr = *info;
}

void rsq_replay_draw_vbo(struct rsq_batch *batch)
{
   struct rsq_context *ctx = batch->ctx;
   struct pipe_draw_info *ptr;

   ptr = rsq_batch_consume_buf(batch, sizeof(*ptr));

   ctx->drv->draw_vbo(ctx->drv, ptr);
}

struct rsq_clear_state {
   union pipe_color_union color;
   double depth;
   unsigned buffers;
   unsigned stencil;
};

static void rsq_clear(struct pipe_context *pctx,
                      unsigned buffers,
                      const union pipe_color_union *color,
                      double depth,
                      unsigned stencil)
{
   struct rsq_context *ctx = rsq_context(pctx);
   struct rsq_clear_state *ptr;

   /* TODO probably most state doesn't need to be emitted.. but things like
    * framebuffer state do.  Perhaps it is useful to pass a state-mask?
    */
   rsq_context_emit(pctx);

   rsq_batch_emit_uint(ctx->batch, rsq_clear_cmd);
   ptr = rsq_batch_emit_buf(ctx->batch, sizeof(*ptr));
   ptr->color = *color;
   ptr->depth = depth;
   ptr->buffers = buffers;
   ptr->stencil = stencil;
}

void rsq_replay_clear(struct rsq_batch *batch)
{
   struct rsq_context *ctx = batch->ctx;
   struct rsq_clear_state *ptr;

   ptr = rsq_batch_consume_buf(batch, sizeof(*ptr));

   ctx->drv->clear(ctx->drv, ptr->buffers, &ptr->color, ptr->depth, ptr->stencil);
}

static void rsq_launch_grid(struct pipe_context *pctx,
                            const struct pipe_grid_info *info)
{
   // TODO ... pipe_grid_info::input needs to be a pipe_resource!!!
}

void rsq_replace_launch_grid(struct rsq_batch *batch)
{
   // TODO
}

struct rsq_copy_region_state {
   struct pipe_box src_box;
   struct pipe_resource *dst;
   struct pipe_resource *src;
   unsigned dst_level, dstx, dsty, dstz;
   unsigned src_level;
};

static void rsq_resource_copy_region(struct pipe_context *pctx,
                                     struct pipe_resource *dst,
                                     unsigned dst_level,
                                     unsigned dstx, unsigned dsty, unsigned dstz,
                                     struct pipe_resource *src,
                                     unsigned src_level,
                                     const struct pipe_box *src_box)
{
   struct rsq_context *ctx = rsq_context(pctx);
   struct rsq_copy_region_state *ptr;

   // TODO: rsq_context_update_batch(pctx, fake_framebuffer_state);

   rsq_batch_emit_uint(ctx->batch, rsq_copy_region_cmd);
   ptr = rsq_batch_emit_buf(ctx->batch, sizeof(*ptr));
   ptr->src_box = *src_box;
   ptr->dst = NULL;
   pipe_resource_reference(&ptr->dst, unwrap(dst));
   ptr->src = NULL;
   pipe_resource_reference(&ptr->src, unwrap(src));
   ptr->dst_level = dst_level;
   ptr->dstx = dstx;
   ptr->dsty = dsty;
   ptr->dstz = dstz;
   ptr->src_level = src_level;
}

void rsq_replay_copy_region(struct rsq_batch *batch)
{
   struct rsq_context *ctx = batch->ctx;
   struct rsq_copy_region_state *ptr;

   ptr = rsq_batch_consume_buf(batch, sizeof(*ptr));

   ctx->drv->resource_copy_region(ctx->drv, ptr->dst, ptr->dst_level,
                                  ptr->dstx, ptr->dsty, ptr->dstz,
                                  ptr->src, ptr->src_level, &ptr->src_box);

   pipe_resource_reference(&ptr->dst, NULL);
   pipe_resource_reference(&ptr->src, NULL);
}

static void rsq_blit(struct pipe_context *pctx,
                     const struct pipe_blit_info *info)
{
   struct rsq_context *ctx = rsq_context(pctx);
   struct pipe_blit_info *ptr;

   // TODO: rsq_context_update_batch(pctx, fake_framebuffer_state);

   rsq_batch_emit_uint(ctx->batch, rsq_blit_cmd);
   ptr = rsq_batch_emit_buf(ctx->batch, sizeof(*ptr));
   *ptr = *info;
   ptr->dst.resource = NULL;
   pipe_resource_reference(&ptr->dst.resource, unwrap(info->dst.resource));
   ptr->src.resource = NULL;
   pipe_resource_reference(&ptr->src.resource, unwrap(info->src.resource));
}

void rsq_replay_blit(struct rsq_batch *batch)
{
   struct rsq_context *ctx = batch->ctx;
   struct pipe_blit_info *ptr;

   ptr = rsq_batch_consume_buf(batch, sizeof(*ptr));

   ctx->drv->blit(ctx->drv, ptr);

   pipe_resource_reference(&ptr->dst.resource, NULL);
   pipe_resource_reference(&ptr->src.resource, NULL);
}

static void rsq_flush(struct pipe_context *pctx,
                      struct pipe_fence_handle **fence,
                      unsigned flags)
{
   struct rsq_context *ctx = rsq_context(pctx);

   /* flush current and dependent batches: */
   rsq_batch_flush(ctx->batch);

   rsq_batch_reference(&ctx->batch, NULL);
   ctx->batch = rsq_batch_create(ctx);

   ctx->drv->flush(ctx->drv, fence, flags);
}

void rsq_draw_context_init(struct pipe_context *pctx)
{
   struct rsq_context *ctx = rsq_context(pctx);

   CTX_INIT(emit_string_marker);
   CTX_INIT(flush);
   CTX_INIT(draw_vbo);
   CTX_INIT(clear);
   CTX_INIT(launch_grid);
   CTX_INIT(resource_copy_region);
   CTX_INIT(blit);

//   CTX_INIT(clear_render_target);
//   CTX_INIT(clear_depth_stencil);
//   CTX_INIT(clear_buffer);
}
