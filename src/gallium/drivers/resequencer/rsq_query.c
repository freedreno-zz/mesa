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

#include "rsq_context.h"
#include "rsq_query.h"
#include "rsq_screen.h"

/* TODO how should queries work?  I guess we need to emit cmds to start/
 * stop queries into the batch?
 */


static int rsq_get_driver_query_info(struct pipe_screen *pscreen,
                                     unsigned index,
                                     struct pipe_driver_query_info *info)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->get_driver_query_info(screen->drv, index, info);
}

static int rsq_get_driver_query_group_info(struct pipe_screen *pscreen,
                                           unsigned index,
                                           struct pipe_driver_query_group_info *info)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   return screen->drv->get_driver_query_group_info(screen->drv, index, info);
}

static void rsq_query_memory_info(struct pipe_screen *pscreen,
                                  struct pipe_memory_info *info)
{
   struct rsq_screen *screen = rsq_screen(pscreen);
   screen->drv->query_memory_info(screen->drv, info);
}

void rsq_query_screen_init(struct pipe_screen *pscreen)
{
   struct rsq_screen *screen = rsq_screen(pscreen);

   SCR_INIT(get_driver_query_info);
   SCR_INIT(get_driver_query_group_info);
   pscreen->query_memory_info = rsq_query_memory_info;
}


static void rsq_render_condition(struct pipe_context *pctx,
                                 struct pipe_query *pquery,
                                 boolean condition,
                                 uint mode)
{
   // TODO
}

static struct pipe_query * rsq_create_query(struct pipe_context *pctx,
                                            unsigned query_type,
                                            unsigned index)
{
   // TODO
   return NULL;
}

static struct pipe_query *rsq_create_batch_query(struct pipe_context *pctx,
                                                 unsigned num_queries,
                                                 unsigned *query_types)
{
   // TODO
   return NULL;
}

static void rsq_destroy_query(struct pipe_context *pctx,
                              struct pipe_query *pquery)
{

}

static boolean rsq_begin_query(struct pipe_context *pctx,
                               struct pipe_query *pquery)
{
   // TODO
   return false;
}

static boolean rsq_end_query(struct pipe_context *pctx,
                             struct pipe_query *pquery)
{
   // TODO
   return false;
}

static boolean rsq_get_query_result(struct pipe_context *pctx,
                                    struct pipe_query *pquery,
                                    boolean wait,
                                    union pipe_query_result *result)
{
   // TODO
   return false;
}

static void rsq_get_query_result_resource(struct pipe_context *pctx,
                                          struct pipe_query *pquery,
                                          boolean wait,
                                          enum pipe_query_value_type result_type,
                                          int index,
                                          struct pipe_resource *resource,
                                          unsigned offset)
{
   // TODO
}

static void rsq_set_active_query_state(struct pipe_context *pctx, boolean enable)
{
   // TODO
}

void rsq_query_context_init(struct pipe_context *pctx)
{
   struct rsq_context *ctx = rsq_context(pctx);

   CTX_INIT(render_condition);
   CTX_INIT(create_query);
   CTX_INIT(create_batch_query);
   CTX_INIT(destroy_query);
   CTX_INIT(begin_query);
   CTX_INIT(end_query);
   CTX_INIT(get_query_result);
   CTX_INIT(get_query_result_resource);
   CTX_INIT(set_active_query_state);
}
