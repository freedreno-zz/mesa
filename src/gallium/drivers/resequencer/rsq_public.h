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

#ifndef RSQ_PUBLIC_H
#define RSQ_PUBLIC_H

#include "pipe/p_state.h"

/**
 * Public interface interface for resequencer layer.
 *
 * The resequencer layer reorders state updates, draws, etc, for better
 * efficiency on tiling GPUs.  Many GL apps/games which are not properly
 * optimized for tilers will do things like unnecessary render target
 * switches or mid-batch texture uploads.
 *
 * This is solved by tracking dependencies between rendering to surfaces
 * and use of those surfaces, and replaying the sequence of state updates
 * and draws to the driver in a more optimal order.
 *
 * The resequencer can also clone/shadow resources to avoid flushes.  For
 * example, a mid-batch texture upload can clone the pipe_resource (so
 * an existing rsq_resource now refers to a new driver pipe_resource).
 */

struct rsq_funcs {
   /**
    * Would read and/or write to buffer cause a flush/stall?  This is
    * used to make decisions about cloning/ghosting resources.
    */
   bool (*is_busy)(struct pipe_resource *prsc, bool write);

   /**
    * Inform driver about start of blit.  This is needed so that driver
    * can do proper query accounting.
    */
   void (*blit_begin)(struct pipe_context *pctx);

   /**
    * Inform driver about end of blit.
    */
   void (*blit_end)(struct pipe_context *pctx);
};

struct pipe_screen * rsq_wrap(struct pipe_screen *pscreen,
                              const struct rsq_funcs *funcs);

#endif /* RSQ_PUBLIC_H */
