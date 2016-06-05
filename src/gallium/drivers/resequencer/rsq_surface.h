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

#ifndef RSQ_SURFACE_H
#define RSQ_SURFACE_H

#include "pipe/p_state.h"

struct rsq_surface {
   struct pipe_surface base;

   struct pipe_surface *drv;      /* driver's surface */

   unsigned rsc_seqno;

   /* Each surface gets an incrementing sequence # which is used in the
    * sanitized fb state key into batch hashtable.  This avoids using
    * pointer values in a key (since a surface could be destroyed and
    * re-allocated with the same pointer address:
    */
   unsigned seqno;
};

static inline struct rsq_surface * rsq_surface(struct pipe_surface *psurf)
{
   return (struct rsq_surface *)psurf;
}

unsigned rsq_surface_validate(struct pipe_surface *psurf);

struct pipe_surface* rsq_create_surface(struct pipe_context *pctx,
                                        struct pipe_resource *ptex,
                                        const struct pipe_surface *surf_tmpl);
void rsq_surface_destroy(struct pipe_context *pctx, struct pipe_surface *psurf);


static inline unsigned seqno_surf(struct pipe_surface *psurf)
{
   if (!psurf)
      return 0;
   return rsq_surface_validate(psurf);
}

static inline struct pipe_surface * unwrap_surf(struct pipe_surface *psurf)
{
   if (!psurf)
      return NULL;
   /* NOTE: assumes seqno_surf()/rsq_surface_validate() already called: */
   return rsq_surface(psurf)->drv;
}

#endif /* RSQ_SURFACE_H */
