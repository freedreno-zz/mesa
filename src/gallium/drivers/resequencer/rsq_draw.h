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

#ifndef RSQ_DRAW_H
#define RSQ_DRAW_H

#include "pipe/p_context.h"

struct rsq_batch;

void rsq_replay_emit_string_marker(struct rsq_batch *batch);
void rsq_replay_draw_vbo(struct rsq_batch *batch);
void rsq_replay_clear(struct rsq_batch *batch);
void rsq_replace_launch_grid(struct rsq_batch *batch);
void rsq_replay_copy_region(struct rsq_batch *batch);
void rsq_replay_blit(struct rsq_batch *batch);

void rsq_draw_context_init(struct pipe_context *pctx);

#endif /* RSQ_DRAW_H */
