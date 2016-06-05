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
#include "rsq_surface.h"

/* (re)allocate backing driver surface: */
static void get_driver_surface(struct pipe_surface *psurf)
{
   struct rsq_surface *surf = rsq_surface(psurf);
   struct rsq_context *ctx = rsq_context(psurf->context);
   struct rsq_resource *rsc = rsq_resource(psurf->texture);

   pipe_surface_reference(&surf->drv, NULL);

   surf->drv = ctx->drv->create_surface(ctx->drv, rsc->drv, psurf);
   surf->rsc_seqno = rsc->seqno;
   surf->seqno = ctx->surf_cnt++;
}

unsigned rsq_surface_validate(struct pipe_surface *psurf)
{
   struct rsq_surface *surf = rsq_surface(psurf);

   /* recreate driver surface if backing resource has been shadowed: */
   if (rsq_resource(psurf->texture)->seqno != surf->rsc_seqno)
      get_driver_surface(psurf);

   return surf->seqno;
}

struct pipe_surface* rsq_create_surface(struct pipe_context *pctx,
                                        struct pipe_resource *ptex,
                                        const struct pipe_surface *surf_tmpl)
{
   struct rsq_surface *surf;

   /* TODO we almost certainly want a sort of cache to avoid creating duplicate
    * surfaces for the same rsc + surf_tmpl.  Cache needs to be big enough for
    * 2x max mip-levels, I think.   After rendering is flushed to driver would
    * be a good time to clean cache to avoid hanging on to ref's to resources
    * too long.
    */

   surf = CALLOC_STRUCT(rsq_surface);

   if (!surf)
      return NULL;

   struct pipe_surface *psurf = &surf->base;
   unsigned level = surf_tmpl->u.tex.level;

   *psurf = *surf_tmpl;

   pipe_reference_init(&psurf->reference, 1);
   pipe_resource_reference(&psurf->texture, ptex);
   psurf->context = pctx;
   psurf->format = surf_tmpl->format;
   psurf->width = u_minify(ptex->width0, level);
   psurf->height = u_minify(ptex->height0, level);
   psurf->u.tex.level = level;
   psurf->u.tex.first_layer = surf_tmpl->u.tex.first_layer;
   psurf->u.tex.last_layer = surf_tmpl->u.tex.last_layer;

   get_driver_surface(psurf);
   if (!surf->drv) {
      pipe_resource_reference(&psurf->texture, NULL);
      free(surf);
      return NULL;
   }

   return &surf->base;
}

void rsq_surface_destroy(struct pipe_context *pctx, struct pipe_surface *psurf)
{
   struct rsq_surface *surf = rsq_surface(psurf);

   pipe_surface_reference(&surf->drv, NULL);
   pipe_resource_reference(&psurf->texture, NULL);

   FREE(psurf);
}
