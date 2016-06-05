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

#ifndef RSQ_STATE_HELPERS_H
#define RSQ_STATE_HELPERS_H

#include "rsq_resource.h"
#include "rsq_surface.h"

/* helpers for the auto-generated state code */

static inline void util_copy_surface(struct pipe_surface **dst,
                                     struct pipe_surface **src)
{
   pipe_surface_reference(dst, *src);
}

/* a few of the state objects handled manually: */

struct rsq_vertex_elements_state {
   struct pipe_reference reference;
   void *drv;
};

static inline void *
rsq_create_vertex_elements_state(struct pipe_context *pctx,
                                 unsigned num_elements,
                                 const struct pipe_vertex_element *elems)
{
   struct rsq_context *ctx = rsq_context(pctx);
   struct rsq_vertex_elements_state *so = CALLOC_STRUCT(rsq_vertex_elements_state);
   if (!so)
      return NULL;
   so->drv = ctx->drv->create_vertex_elements_state(ctx->drv, num_elements, elems);
   if (!so->drv) {
      free(so);
      return NULL;
   }
   pipe_reference_init(&so->reference, 1);
   return so;
}

/*
 * Seqno/export helpers.. any state that directly or indirectly
 * references a pipe_surface gets a sequence # which is defined
 * of the MAX of the sequence # of any referenced rsq_resource-s.
 * If a resource is shadowed then it's seqno is bumped, so this
 * lets us know when we need to apply otherwise clean state to
 * underlying driver.
 *
 * The export helpers act like util_copy_${state}() except that
 * they replace the rsq_resource's in the src struct with driver
 * resource.
 */

static inline unsigned
rsq_constant_buffer_seqno(const struct pipe_constant_buffer *cb)
{
   debug_assert(!cb->user_buffer);
   return seqno(cb->buffer);
}

static inline void
rsq_export_constant_buffer(struct pipe_constant_buffer *dst,
                           const struct pipe_constant_buffer *src)
{
   dst->buffer = NULL;
   pipe_resource_reference(&dst->buffer, unwrap(src->buffer));
   dst->buffer_offset = src->buffer_offset;
   dst->buffer_size = src->buffer_size;
   dst->user_buffer = src->user_buffer;
}


static inline unsigned
rsq_shader_buffer_seqno(const struct pipe_shader_buffer *sb)
{
   return seqno(sb->buffer);
}

static inline void
rsq_export_shader_buffer(struct pipe_shader_buffer *dst,
                         const struct pipe_shader_buffer *src)
{
   dst->buffer = NULL;
   pipe_resource_reference(&dst->buffer, unwrap(src->buffer));
   dst->buffer_offset = src->buffer_offset;
   dst->buffer_size = src->buffer_size;
}


static inline unsigned
rsq_image_view_seqno(const struct pipe_image_view *cb)
{
   return seqno(cb->resource);
}

static inline void
rsq_export_image_view(struct pipe_image_view *dst,
                      const struct pipe_image_view *src)
{
   dst->resource = NULL;
   pipe_resource_reference(&dst->resource, unwrap(src->resource));
   dst->format = src->format;
   dst->access = src->access;
   dst->u = src->u;
}


static inline unsigned
rsq_vertex_buffer_seqno(const struct pipe_vertex_buffer *vb)
{
   debug_assert(!vb->user_buffer);
   return seqno(vb->buffer);
}

static inline void
rsq_export_vertex_buffer(struct pipe_vertex_buffer *dst,
                         const struct pipe_vertex_buffer *src)
{
   dst->stride = src->stride;
   dst->buffer_offset = src->buffer_offset;
   dst->buffer = NULL;
   pipe_resource_reference(&dst->buffer, unwrap(src->buffer));
   dst->user_buffer = src->user_buffer;
}


static inline unsigned
rsq_index_buffer_seqno(const struct pipe_index_buffer *ib)
{
   debug_assert(!ib->user_buffer);
   return seqno(ib->buffer);
}

static inline void
rsq_export_index_buffer(struct pipe_index_buffer *dst,
                        const struct pipe_index_buffer *src)
{
   dst->index_size = src->index_size;
   dst->offset = src->offset;
   dst->buffer = NULL;
   pipe_resource_reference(&dst->buffer, unwrap(src->buffer));
   dst->user_buffer = src->user_buffer;
}


static inline unsigned
rsq_surface_seqno(struct pipe_surface **surf)
{
   return seqno_surf(*surf);
}

static inline void rsq_export_surface(struct pipe_surface **dst,
                                      struct pipe_surface **src)
{
   *dst = NULL;
   pipe_surface_reference(dst, unwrap_surf(*src));
}


static inline unsigned
rsq_framebuffer_state_seqno(const struct pipe_framebuffer_state *pfb)
{
   unsigned i, n = 0;
   for (i = 0; i < pfb->nr_cbufs; i++)
      n = MAX2(n, seqno_surf(pfb->cbufs[i]));
   n = MAX2(n, seqno_surf(pfb->zsbuf));
   return n;
}

static inline void
rsq_export_framebuffer_state(struct pipe_framebuffer_state *dst,
                             const struct pipe_framebuffer_state *src)
{
   unsigned i;

   dst->width = src->width;
   dst->height = src->height;

   dst->samples = src->samples;
   dst->layers  = src->layers;

   for (i = 0; i < src->nr_cbufs; i++) {
      dst->cbufs[i] = NULL;
      pipe_surface_reference(&dst->cbufs[i], unwrap_surf(src->cbufs[i]));
   }

   /* Set remaining dest cbuf pointers to NULL */
   for ( ; i < ARRAY_SIZE(dst->cbufs); i++)
      dst->cbufs[i] = NULL;

   dst->nr_cbufs = src->nr_cbufs;

   dst->zsbuf = NULL;
   pipe_surface_reference(&dst->zsbuf, unwrap_surf(src->zsbuf));
}

#endif /* RSQ_STATE_HELPERS_H */
