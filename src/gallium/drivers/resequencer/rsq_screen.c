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

#include "rsq_context.h"
#include "rsq_fence.h"
#include "rsq_resource.h"
#include "rsq_screen.h"
#include "rsq_query.h"


static void rsq_screen_destroy(struct pipe_screen *pscreen)
{
   struct rsq_screen *screen = rsq_screen(pscreen);

   screen->drv->destroy(screen->drv);

   free(screen);
}

static const char * rsq_screen_get_name(struct pipe_screen *pscreen)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->get_name(screen->drv);
}

static const char * rsq_screen_get_vendor(struct pipe_screen *pscreen)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->get_vendor(screen->drv);
}

static const char * rsq_screen_get_device_vendor(struct pipe_screen *pscreen)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->get_device_vendor(screen->drv);
}

static int
rsq_screen_get_param(struct pipe_screen *pscreen, enum pipe_cap param)
{
   struct rsq_screen *screen = rsq_screen(pscreen);

   /* NOTE: we need pipe_resources, since user buffer ptrs are likely
    * to be invalid by the time we actually flush rendering:
    */
   switch (param) {
   case PIPE_CAP_USER_CONSTANT_BUFFERS:
   case PIPE_CAP_USER_VERTEX_BUFFERS:
   case PIPE_CAP_USER_INDEX_BUFFERS:
      return 0;
   default:
      return screen->drv->get_param(screen->drv, param);
   }
}

static float rsq_screen_get_paramf(struct pipe_screen *pscreen,
                                   enum pipe_capf param)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->get_paramf(screen->drv, param);
}

static int rsq_screen_get_shader_param(struct pipe_screen *pscreen,
                                       unsigned shader,
                                       enum pipe_shader_cap param)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->get_shader_param(screen->drv, shader, param);
}

static int rsq_get_video_param(struct pipe_screen *pscreen,
                               enum pipe_video_profile profile,
                               enum pipe_video_entrypoint entrypoint,
                               enum pipe_video_cap param)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->get_video_param(screen->drv, profile, entrypoint, param);
}

static int rsq_get_compute_param(struct pipe_screen *pscreen,
                                 enum pipe_shader_ir ir_type,
                                 enum pipe_compute_cap param,
                                 void *ret)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->get_compute_param(screen->drv, ir_type, param, ret);
}

static uint64_t rsq_get_timestamp(struct pipe_screen *pscreen)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->get_timestamp(screen->drv);
}

static boolean rsq_is_format_supported(struct pipe_screen *pscreen,
                                       enum pipe_format format,
                                       enum pipe_texture_target target,
                                       unsigned sample_count,
                                       unsigned bindings)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->is_format_supported(screen->drv, format, target,
                                           sample_count, bindings);
}

static boolean rsq_is_video_format_supported(struct pipe_screen *pscreen,
                                             enum pipe_format format,
                                             enum pipe_video_profile profile,
                                             enum pipe_video_entrypoint entrypoint)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->is_video_format_supported(screen->drv, format, profile,
                                                 entrypoint);
}

static const void * rsq_get_compiler_options(struct pipe_screen *pscreen,
                                             enum pipe_shader_ir ir,
                                             unsigned shader)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->get_compiler_options(screen->drv, ir, shader);
}


struct pipe_screen * rsq_wrap(struct pipe_screen *drv,
                              const struct rsq_funcs *funcs)
{
   struct rsq_screen *screen = CALLOC_STRUCT(rsq_screen);

   if (!screen)
      return NULL;

   screen->funcs = funcs;
   screen->drv = drv;

   struct pipe_screen *pscreen = &screen->base;

   pscreen->destroy = rsq_screen_destroy;

   pscreen->get_name = rsq_screen_get_name;
   pscreen->get_vendor = rsq_screen_get_vendor;
   pscreen->get_device_vendor = rsq_screen_get_device_vendor;
   pscreen->get_param = rsq_screen_get_param;
   pscreen->get_paramf = rsq_screen_get_paramf;
   pscreen->get_shader_param = rsq_screen_get_shader_param;
   pscreen->get_video_param = rsq_get_video_param;
   pscreen->get_compute_param = rsq_get_compute_param;
   SCR_INIT(get_timestamp);
   pscreen->context_create = rsq_context_create;
   pscreen->is_format_supported = rsq_is_format_supported;
   pscreen->is_video_format_supported = rsq_is_video_format_supported;

   rsq_resource_screen_init(pscreen);

//XXX   SCR_INIT(flush_frontbuffer);

   rsq_fence_screen_init(pscreen);

   rsq_query_screen_init(pscreen);

   pscreen->get_compiler_options = rsq_get_compiler_options;

   return pscreen;
}
