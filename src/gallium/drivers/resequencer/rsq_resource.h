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

#ifndef RSQ_RESOURCE_H
#define RSQ_RESOURCE_H

#include "pipe/p_state.h"

struct rsq_resource {
   struct pipe_resource base;

   struct pipe_resource *drv;     /* wrapped driver's resource */
   unsigned seqno;
   bool external;                 /* external resources cannot be shadowed */
};

static inline struct rsq_resource * rsq_resource(struct pipe_resource *prsc)
{
   return (struct rsq_resource *)prsc;
}

void rsq_resource_screen_init(struct pipe_screen *pscreen);
void rsq_resource_context_init(struct pipe_context *pctx);


static inline struct pipe_resource * unwrap(struct pipe_resource *prsc)
{
   if (!prsc)
      return NULL;
   return rsq_resource(prsc)->drv;
}

static inline unsigned seqno(struct pipe_resource *prsc)
{
   if (!prsc)
      return 0;
   return rsq_resource(prsc)->seqno;
}

#endif /* RSQ_RESOURCE_H */
