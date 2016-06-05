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

#include "util/u_inlines.h"
#include "util/u_memory.h"

#include "rsq_context.h"
#include "rsq_resource.h"
#include "rsq_screen.h"

static boolean rsq_can_create_resource(struct pipe_screen *pscreen,
                                       const struct pipe_resource *templat)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->can_create_resource(screen->drv, templat);
}

static void rsc_resource_destroy(struct pipe_screen *pscrean,
                                 struct pipe_resource *prsc)
{
   struct rsq_resource *rsc = rsq_resource(prsc);
   pipe_resource_reference(&rsc->drv, NULL);
   free(rsc);
}

/* (re)allocate backing driver prsc */
static void get_driver_resource(struct rsq_resource *rsc)
{
   struct rsq_screen *screen = rsq_screen(rsc->base.screen);

   pipe_resource_reference(&rsc->drv, NULL);

   /* allocate a new buffer from driver: */
   rsc->drv = screen->drv->resource_create(screen->drv, &rsc->base);
   rsc->seqno = screen->rsc_cnt++;
}

static struct rsq_resource * rsq_resource_new(struct pipe_screen *pscreen,
                                              const struct pipe_resource *tmpl)
{
   struct rsq_resource *rsc = CALLOC_STRUCT(rsq_resource);

   if (!rsc)
      return NULL;

   rsc->base = *tmpl;
   rsc->base.screen = pscreen;

   pipe_reference_init(&rsc->base.reference, 1);

   return rsc;
}

static struct pipe_resource * rsq_resource_create(struct pipe_screen *pscreen,
                                                  const struct pipe_resource *tmpl)
{
   struct rsq_resource *rsc = rsq_resource_new(pscreen, tmpl);

   if (!rsc)
      return NULL;

   get_driver_resource(rsc);

   if (!rsc->drv)
      goto fail;

   return &rsc->base;

fail:
   rsc_resource_destroy(pscreen, &rsc->base);
   return NULL;
}

static struct pipe_resource *
rsq_resource_from_handle(struct pipe_screen *pscreen,
                         const struct pipe_resource *tmpl,
                         struct winsys_handle *handle,
                         unsigned usage)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   struct rsq_resource *rsc = rsq_resource_new(pscreen, tmpl);

   if (!rsc)
      return NULL;

   rsc->external = true;

   struct pipe_resource *drv;
   drv = screen->drv->resource_from_handle(screen->drv, tmpl, handle, usage);

   if (!drv)
      goto fail;

   pipe_resource_reference(&rsc->drv, drv);

   return &rsc->base;

fail:
   rsc_resource_destroy(pscreen, &rsc->base);
   return NULL;
}

static boolean rsq_resource_get_handle(struct pipe_screen *pscreen,
                                       struct pipe_resource *prsc,
                                       struct winsys_handle *handle,
                                       unsigned usage)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   struct rsq_resource *rsc = rsq_resource(prsc);

   rsc->external = true;

   return screen->drv->resource_get_handle(screen->drv, rsc->drv, handle, usage);
}


void rsq_resource_screen_init(struct pipe_screen *pscreen)
{
   struct rsq_screen *screen = rsq_screen(pscreen);

   SCR_INIT(can_create_resource);
   pscreen->resource_create = rsq_resource_create;
   pscreen->resource_destroy = rsc_resource_destroy;
   pscreen->resource_from_handle = rsq_resource_from_handle;
   pscreen->resource_get_handle = rsq_resource_get_handle;
}

/* TODO
 * For now just trivial implementation of transfer_map and friends
 * that always flushes the current batch and passes down to drv..
 * once we have resequencing we will want to be more clever..
 */

static void * rsq_transfer_map(struct pipe_context *pctx,
                               struct pipe_resource *prsc,
                               unsigned level,
                               unsigned usage,  /* a combination of PIPE_TRANSFER_x */
                               const struct pipe_box *box,
                               struct pipe_transfer **out_transfer)
{
   struct rsq_context *ctx = rsq_context(pctx);

   pctx->flush(pctx, NULL, 0);

   return ctx->drv->transfer_map(ctx->drv, unwrap(prsc), level, usage,
                                 box, out_transfer);
}

static void rsq_transfer_flush_region(struct pipe_context *pctx,
                                      struct pipe_transfer *transfer,
                                      const struct pipe_box *box)
{
   struct rsq_context *ctx = rsq_context(pctx);
   ctx->drv->transfer_flush_region(ctx->drv, transfer, box);
}

static void rsq_transfer_unmap(struct pipe_context *pctx,
                               struct pipe_transfer *transfer)
{
   struct rsq_context *ctx = rsq_context(pctx);
   ctx->drv->transfer_unmap(ctx->drv, transfer);
}

static void rsq_transfer_inline_write(struct pipe_context *pctx,
                                      struct pipe_resource *prsc,
                                      unsigned level,
                                      unsigned usage, /* a combination of PIPE_TRANSFER_x */
                                      const struct pipe_box *box,
                                      const void *data,
                                      unsigned stride,
                                      unsigned layer_stride)
{
   struct rsq_context *ctx = rsq_context(pctx);

   pctx->flush(pctx, NULL, 0);

   ctx->drv->transfer_inline_write(ctx->drv, unwrap(prsc), level, usage, box,
                                   data, stride, layer_stride);
}

static void rsq_flush_resource(struct pipe_context *pctx,
                               struct pipe_resource *prsc)
{
   struct rsq_context *ctx = rsq_context(pctx);
   struct rsq_resource *rsc = rsq_resource(prsc);

   rsq_context_emit(pctx);

   ctx->drv->flush_resource(ctx->drv, rsc->drv);
}

void rsq_resource_context_init(struct pipe_context *pctx)
{
   struct rsq_context *ctx = rsq_context(pctx);

   CTX_INIT(transfer_map);
   CTX_INIT(transfer_flush_region);
   CTX_INIT(transfer_unmap);
   CTX_INIT(transfer_inline_write);
   CTX_INIT(flush_resource);
//   CTX_INIT(invalidate_resource);
}
