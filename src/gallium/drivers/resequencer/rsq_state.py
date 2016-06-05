#! /usr/bin/env python
#
# Copyright (c) 2016 Red Hat
# 
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import mako.template
import sys

#
# CSO state:
#
class CSO(object):
   __type_template = mako.template.Template("""
% if not s.manual:
/* refcounted container to track matching driver state: */
struct rsq_${s.typename}_state {
   struct pipe_reference reference;
   void *drv;
};
% else:
struct rsq_${s.typename}_state;
% endif
""")

   __id_template = mako.template.Template("""
% for name in s.statenames:
   rsq_${name}_id,
% endfor
""")

   __funcs_template = mako.template.Template("""
% for name in s.statenames:
static inline void rsq_${name}_ref(struct pipe_context *pctx,
                        struct rsq_${s.typename}_state **ptr,
                        struct rsq_${s.typename}_state *val)
{
   if (pipe_reference(&(*ptr)->reference, &val->reference)) {
      struct rsq_context *ctx = rsq_context(pctx);
      ctx->drv->delete_${name}_state(ctx->drv, (*ptr)->drv);
      free(*ptr);
   }
   *ptr = val;
}
% if not s.manual:
static void * rsq_create_${name}_state(struct pipe_context *pctx,
                        const struct pipe_${s.typename}_state *s)
{
   struct rsq_context *ctx = rsq_context(pctx);
   struct rsq_${s.typename}_state *so = CALLOC_STRUCT(rsq_${s.typename}_state);
   if (!so)
      return NULL;
   so->drv = ctx->drv->create_${name}_state(ctx->drv, s);
   if (!so->drv) {
      free(so);
      return NULL;
   }
   pipe_reference_init(&so->reference, 1);
   return so;
}
% endif
static void rsq_bind_${name}_state${"" if s.length is None else "s"}(struct pipe_context *pctx,
% if s.per_shader_stage:
                        unsigned stage,
% endif
% if s.length:
                        unsigned start, unsigned num, void **s)
% else:
                        void *s)
% endif
{
   struct rsq_context *ctx = rsq_context(pctx);
   ctx->state.dirty |= (1 << rsq_${name}_id);
% if s.length:
   debug_assert((start + num) < ${s.length});
   for (unsigned i = 0; i < num; i++) {
      ctx->state.${name}${"[stage]" if s.per_shader_stage else ""}[i + start] = s[i];
      ctx->state.dirty_${name}${'[stage]' if s.per_shader_stage else ''} |= (1 << (i + start));
      ctx->state.valid_${name}${'[stage]' if s.per_shader_stage else ''} |= (1 << (i + start));
   }
% else:
   ctx->state.${name} = s;
% endif
% if s.per_shader_stage:
   ctx->state.dirty_${name}_shader |= (1 << stage);
   ctx->state.valid_${name}_shader |= (1 << stage);
% endif
}
static void rsq_delete_${name}_state(struct pipe_context *pctx, void *s)
{
   struct rsq_${s.typename}_state *so = s;
   rsq_${name}_ref(pctx, &so, NULL);
   free(so);
}
% endfor
""")

   __setup_template = mako.template.Template("""
% for name in s.statenames:
   CTX_INIT(create_${name}_state);
   CTX_INIT(bind_${name}_state${"" if s.length is None else "s"});
   CTX_INIT(delete_${name}_state);
% endfor
""")

   __state_template = mako.template.Template("""
% for name in s.statenames:
% if s.per_shader_stage:
   unsigned short valid_${name}_shader;
   unsigned short dirty_${name}_shader;
% endif
% if s.length:
   unsigned dirty_${name}${'[PIPE_SHADER_TYPES]' if s.per_shader_stage else ''};
   unsigned valid_${name}${'[PIPE_SHADER_TYPES]' if s.per_shader_stage else ''};
% endif
   struct rsq_${s.typename}_state *${name}
% if s.per_shader_stage:
   [PIPE_SHADER_TYPES]
% endif
% if s.length is not None:
   [${s.length}]
% endif
   ;
% endfor
""")

   __emit_template = mako.template.Template("""
% for name in s.statenames:
   if (ctx->state.dirty & (1 << rsq_${name}_id)) {
% if s.per_shader_stage:
      shader_mask = ctx->state.dirty_${name}_shader;
      while((shader = util_last_bit(shader_mask) - 1) >= 0) {
% endif
% if s.length:
         idx_mask = ctx->state.dirty_${name}${'[shader]' if s.per_shader_stage else ''};
         while ((idx = util_last_bit(idx_mask) - 1) >= 0) {
            struct rsq_${s.typename}_state **ptr;
            rsq_batch_emit_uint(ctx->batch, rsq_${name}_id);
% if s.per_shader_stage:
            rsq_batch_emit_uint(ctx->batch, shader);
% endif:
            rsq_batch_emit_uint(ctx->batch, idx);
            ptr = rsq_batch_emit_buf(ctx->batch, sizeof(*ptr));
            *ptr = NULL;
            rsq_${name}_ref(pctx, ptr, ctx->state.${name}${'[shader]' if s.per_shader_stage else ''}[idx]);
            idx_mask &= ~(1 << idx);
         }
         ctx->state.dirty_${name}${'[shader]' if s.per_shader_stage else ''} = 0;
% else:
         struct rsq_${s.typename}_state **ptr;
         rsq_batch_emit_uint(ctx->batch, rsq_${name}_id);
         ptr = rsq_batch_emit_buf(ctx->batch, sizeof(*ptr));
         *ptr = NULL;
         rsq_${name}_ref(pctx, ptr, ctx->state.${name}${'[shader]' if s.per_shader_stage else ''});
% endif
% if s.per_shader_stage:
         shader_mask &= ~(1 << shader);
      }
      ctx->state.dirty_${name}_shader = 0;
% endif
   }
% endfor
""")

   __replay_template = mako.template.Template("""
% for name in s.statenames:
   case rsq_${name}_id: {
% if s.per_shader_stage:
      unsigned stage = rsq_batch_consume_uint(batch);
% endif
% if s.length:
      static const struct pipe_${s.typename}_state *nullstate = NULL;
      unsigned i = rsq_batch_consume_uint(batch);
% endif
      struct rsq_${s.typename}_state **ptr = rsq_batch_consume_buf(batch, sizeof(*ptr));
      ctx->drv->bind_${name}_state${'s' if s.length else ''}(ctx->drv,
% if s.per_shader_stage:
                                   stage,
% endif
% if s.length:
                                   i, 1, *ptr ? &(*ptr)->drv : (void **)&nullstate);
% else:
                                   *ptr ? (*ptr)->drv : NULL);
% endif
      rsq_${name}_ref(&ctx->base, ptr, NULL);
      break;
   }
% endfor
""")

   def __init__(self, typename, statenames=None, length=None,
                per_shader_stage=False, manual=False):
      self.typename = typename
      if statenames:
         self.statenames = statenames
      else:
         self.statenames = [ typename ]
      self.length = length
      self.per_shader_stage = per_shader_stage
      self.manual = manual

   def render_type(self):
      return self.__type_template.render(s=self)

   def render_id(self):
      return self.__id_template.render(s=self)

   def render_funcs(self):
      return self.__funcs_template.render(s=self)

   def render_setup(self):
      return self.__setup_template.render(s=self)

   def render_state(self):
      return self.__state_template.render(s=self)

   def render_emit(self):
      return self.__emit_template.render(s=self)

   def render_replay(self):
      return self.__replay_template.render(s=self)



#
# Non-CSO state:
#
class Param(object):
   __funcs_template = mako.template.Template("""
static void rsq_set_${s.statename}(struct pipe_context *pctx,
% if s.per_shader_stage:
                        unsigned stage,
% endif
% if s.cb_hack:
                        unsigned start,
% elif s.length:
                        unsigned start, unsigned num,
% endif
                        ${"const " if not s.cs_hack else ""}${s.typename} val)
{
   struct rsq_context *ctx = rsq_context(pctx);
% if s.cb_hack:
   const unsigned num = 1;
% endif
   ctx->state.dirty |= (1 << rsq_${s.statename}_id);
% if s.length:
   debug_assert((start + num) < ${s.length});
   for (unsigned i = 0; i < num; i++) {
      ${s.copy_command("ctx->state." + s.statename + ("[stage]" if s.per_shader_stage else "") + "[i + start]", "&val[i]")};
      ctx->state.dirty_${s.statename}${'[stage]' if s.per_shader_stage else ''} |= (1 << (i + start));
      ctx->state.valid_${s.statename}${'[stage]' if s.per_shader_stage else ''} |= (1 << (i + start));
   }
% else:
   ${s.copy_command("ctx->state." + s.statename + ("[stage]" if s.per_shader_stage else ""), "val")};
% endif
% if s.per_shader_stage:
   ctx->state.dirty_${s.statename}_shader |= (1 << stage);
   ctx->state.valid_${s.statename}_shader |= (1 << stage);
% endif
% if s.statename is "framebuffer_state":
   rsq_context_update_batch(pctx, val);
% endif
}
""")

   __setup_template = mako.template.Template("""
   CTX_INIT(set_${s.statename});
""")

   __state_template = mako.template.Template("""
% if s.per_shader_stage:
   unsigned short valid_${s.statename}_shader;
   unsigned short dirty_${s.statename}_shader;
% endif
% if s.length:
   unsigned dirty_${s.statename}${'[PIPE_SHADER_TYPES]' if s.per_shader_stage else ''};
   unsigned valid_${s.statename}${'[PIPE_SHADER_TYPES]' if s.per_shader_stage else ''};
% endif
% if s.has_resources:
   unsigned seqno_${s.statename}
% if s.per_shader_stage:
   [PIPE_SHADER_TYPES]
% endif
% if s.length:
   [${s.length}]
% endif
   ;
% endif
   ${s.typename.replace(" *", "")} ${s.statename}
% if s.per_shader_stage:
   [PIPE_SHADER_TYPES]
% endif
% if s.length:
   [${s.length}]
% endif
   ;
""")

   __emit_template = mako.template.Template("""
% if s.has_resources:
   /* detect if state is dirty due to resource shadowing: */
   if (unlikely(ctx->dirty_clone)) {
% if s.per_shader_stage:
      shader_mask = ctx->state.valid_${s.statename}_shader;
      while((shader = util_last_bit(shader_mask) - 1) >= 0) {
% endif
% if s.length:
         idx_mask = ctx->state.valid_${s.statename}${'[shader]' if s.per_shader_stage else ''};
         while ((idx = util_last_bit(idx_mask) - 1) >= 0) {
% endif
            seqno = rsq_${s.basename}_seqno(
                      &ctx->state.${s.statename}${'[shader]' if s.per_shader_stage else ''}
                      ${'[idx]' if s.length else ''});
            if (ctx->state.seqno_${s.statename}${'[shader]' if s.per_shader_stage else ''}
                   ${'[idx]' if s.length else ''} != seqno) {
% if s.length:
               ctx->state.dirty_${s.statename}${'[shader]' if s.per_shader_stage else ''} |= (1 << idx);
% endif
% if s.per_shader_stage:
               ctx->state.dirty_${s.statename}_shader |= (1 << shader);
% endif
               ctx->state.dirty |= (1 << rsq_${s.statename}_id);
               ctx->state.seqno_${s.statename}${'[shader]' if s.per_shader_stage else ''}${'[idx]' if s.length else ''} = seqno;
            }
% if s.length:
            idx_mask &= ~(1 << idx);
         }
% endif
% if s.per_shader_stage:
         shader_mask &= ~(1 << shader);
      }
% endif
   }
% endif

   if (ctx->state.dirty & (1 << rsq_${s.statename}_id)) {
% if s.per_shader_stage:
      shader_mask = ctx->state.dirty_${s.statename}_shader;
      while((shader = util_last_bit(shader_mask) - 1) >= 0) {
% endif
% if s.length:
         idx_mask = ctx->state.dirty_${s.statename}${'[shader]' if s.per_shader_stage else ''};
         while ((idx = util_last_bit(idx_mask) - 1) >= 0) {
            ${s.typename.replace(" *", "")} *ptr;
            rsq_batch_emit_uint(ctx->batch, rsq_${s.statename}_id);
% if s.per_shader_stage:
            rsq_batch_emit_uint(ctx->batch, shader);
% endif:
            rsq_batch_emit_uint(ctx->batch, idx);
            ptr = rsq_batch_emit_buf(ctx->batch, sizeof(*ptr));
% if s.has_resources:
            rsq_export_${s.basename}(ptr, &ctx->state.${s.statename}${'[shader]' if s.per_shader_stage else ''}[idx]);
% else:
            *ptr = ctx->state.${s.statename}${'[shader]' if s.per_shader_stage else ''}[idx];
% endif
            idx_mask &= ~(1 << idx);
         }
         ctx->state.dirty_${s.statename}${'[shader]' if s.per_shader_stage else ''} = 0;
% else:
         ${s.typename.replace(" *", "")} *ptr;
         rsq_batch_emit_uint(ctx->batch, rsq_${s.statename}_id);
         ptr = rsq_batch_emit_buf(ctx->batch, sizeof(*ptr));
% if s.has_resources:
         rsq_export_${s.basename}(ptr, &ctx->state.${s.statename}${'[shader]' if s.per_shader_stage else ''});
% else:
         *ptr = ctx->state.${s.statename}${'[shader]' if s.per_shader_stage else ''};
% endif
% endif
% if s.per_shader_stage:
         shader_mask &= ~(1 << shader);
      }
      ctx->state.dirty_${s.statename}_shader = 0;
% endif
   }
""")

   __replay_template = mako.template.Template("""
   case rsq_${s.statename}_id: {
% if s.per_shader_stage:
      unsigned stage = rsq_batch_consume_uint(batch);
% endif
% if s.length:
      unsigned i = rsq_batch_consume_uint(batch);
% endif
      ${s.typename.replace(" *", "")} *ptr = rsq_batch_consume_buf(batch, sizeof(*ptr));
      ctx->drv->set_${s.statename}(ctx->drv,
% if s.per_shader_stage:
                                   stage,
% endif
% if s.length:
                                   i, ${'1,' if not s.cb_hack else ''} ptr);
% else:
                                   ${'*' if not s.typename.endswith("*") else ''}ptr);
% endif
% if s.has_resources:
      util_copy_${s.basename}(ptr, NULL);
% endif
      break;
   }
""")

   def __init__(self, statename, typename=None, length=None,
                has_resources=False, per_shader_stage=False):
      self.statename = statename
      if typename:
         self.typename = typename
      else:
         self.typename = "struct pipe_" + statename + " *"
      self.length = length

      # XXX special hack.. TODO fix gallium API to be more uniform..
      self.cb_hack = statename is "constant_buffer"
      self.cs_hack = statename is "compute_resource"

      if length is not None and not self.cb_hack:
         self.statename = self.statename + "s"
      self.has_resources = has_resources
      self.per_shader_stage = per_shader_stage
      self.basename = self.typename.replace("struct pipe_", "").replace(" ", "").replace("*", "")

   def copy_command(self, dst, src):
      if self.has_resources:
         return "util_copy_" + self.basename + "(&" + dst + ", val ? " + src + " : NULL)"
      elif self.typename.endswith("*"):
         return dst + " = *" + src
      else:
         return dst + " = " + src

   def render_type(self):
      return ""

   def render_id(self):
      return "rsq_" + self.statename + "_id,"

   def render_funcs(self):
      return self.__funcs_template.render(s=self)

   def render_setup(self):
      return self.__setup_template.render(s=self)

   def render_state(self):
      return self.__state_template.render(s=self)

   def render_emit(self):
      return self.__emit_template.render(s=self)

   def render_replay(self):
      return self.__replay_template.render(s=self)

state = [
   CSO("blend"),
   CSO("sampler", length="PIPE_MAX_SAMPLERS", per_shader_stage=True),
   CSO("rasterizer"),
   CSO("depth_stencil_alpha"),
   CSO("shader", [ "fs", "vs", "gs", "tcs", "tes" ]),
   CSO("compute"),
   CSO("vertex_elements", manual=True),  # create/bind/destroy handled manually..
   Param("blend_color"),
   Param("stencil_ref"),
   Param("sample_mask", "unsigned"),
   Param("min_samples", "unsigned"),
   Param("clip_state"),
   Param("constant_buffer", length="PIPE_MAX_CONSTANT_BUFFERS", has_resources=True, per_shader_stage=True),
   Param("framebuffer_state", has_resources=True),
   Param("polygon_stipple", "struct pipe_poly_stipple *"),
   Param("scissor_state", length="PIPE_MAX_VIEWPORTS"),
   Param("viewport_state", length="PIPE_MAX_VIEWPORTS"),
   Param("tess_state"),
   Param("shader_buffer", length="PIPE_MAX_SHADER_BUFFERS", has_resources=True, per_shader_stage=True),
   Param("shader_image", "struct pipe_image_view *", length="PIPE_MAX_SHADER_IMAGES", has_resources=True, per_shader_stage=True),
   Param("vertex_buffer", length="PIPE_MAX_SHADER_INPUTS", has_resources=True),
   Param("index_buffer", has_resources=True),
   Param("compute_resource", "struct pipe_surface **", length="PIPE_MAX_SHADER_IMAGES", has_resources=True),
]

__state_c_template = mako.template.Template("""
/* GENERATED FILE - DO NOT EDIT */
#include "pipe/p_context.h"
#include "pipe/p_state.h"
#include "util/u_framebuffer.h"
#include "util/u_memory.h"
#include "util/u_inlines.h"

#include "rsq_batch.h"
#include "rsq_context.h"
#include "rsq_state.h"
#include "rsq_state_helpers.h"

% for s in state:
   ${s.render_funcs()}
% endfor

void rsq_state_context_init(struct pipe_context *pctx)
{
   struct rsq_context *ctx = rsq_context(pctx);

   debug_assert(rsq_state_count < (8 * sizeof(rsq_context(pctx)->state.dirty)));

% for s in state:
   ${s.render_setup()}
% endfor
}

void rsq_state_emit(struct pipe_context *pctx)
{
   struct rsq_context *ctx = rsq_context(pctx);
   unsigned seqno, shader_mask, idx_mask;
   int idx, shader;

% for s in state:
   ${s.render_emit()}
% endfor

   ctx->state.dirty = 0;
}

void rsq_state_dirty(struct pipe_context *pctx)
{
   struct rsq_context *ctx = rsq_context(pctx);
   ctx->state.dirty = ~0;
}

void rsq_state_replay(struct rsq_batch *batch, enum rsq_state_id id)
{
   struct rsq_context *ctx = batch->ctx;
   switch (id) {
% for s in state:
   ${s.render_replay()}
% endfor
   default:
      unreachable("invalid state id");
   }
}
""")

__state_h_template = mako.template.Template("""
/* GENERATED FILE - DO NOT EDIT */
#ifndef RSQ_STATE_H
#define RSQ_STATE_H

#include "pipe/p_context.h"
#include "pipe/p_state.h"

enum rsq_state_id {
% for s in state:
   ${s.render_id()}
% endfor

   /* handled specially, since it doesn't fit the mold: */
   rsq_sampler_view_id,
   rsq_stream_output_target_id,

   rsq_state_count,

   /* it is convenient to use the same header for draw/blit/etc: */
   rsq_string_marker_cmd,
   rsq_draw_cmd,
   rsq_clear_cmd,
   rsq_launch_grid_cmd,
   rsq_copy_region_cmd,
   rsq_blit_cmd,
};

% for s in state:
   ${s.render_type()}
% endfor

struct rsq_state {
   unsigned dirty;
% for s in state:
   ${s.render_state()}
% endfor
};

void rsq_state_context_init(struct pipe_context *pctx);
void rsq_state_emit(struct pipe_context *pctx);
void rsq_state_dirty(struct pipe_context *pctx);

struct rsq_batch;
void rsq_state_replay(struct rsq_batch *batch, enum rsq_state_id id);

#endif /* RSQ_STATE_H */
""")

if sys.argv[1] == "-c":
   print(__state_c_template.render(state=state))
elif sys.argv[1] == "-h":
   print(__state_h_template.render(state=state))
else:
   print("unknown arg: " + sys.argv[1])
