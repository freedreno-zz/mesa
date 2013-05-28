/* -*- mode: C; c-file-style: "k&r"; tab-width 4; indent-tabs-mode: t; -*- */

/*
 * Copyright (C) 2013 Rob Clark <robclark@freedesktop.org>
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
 *
 * Authors:
 *    Rob Clark <robclark@freedesktop.org>
 */

/**
 * This module converts primitive types supported by GL but not supported by
 * GLES.  It is intended to help out hw designed for GLES, by remapping
 * draw primitives, using an index buffer:
 *
 *   PIPE_PRIM_QUADS -> PIPE_PRIM_TRIANGLES
 *   others.. tbd..
 *
 */

#include "pipe/p_state.h"

#include "util/u_primconvert.h"
#include "util/u_memory.h"
#include "util/u_inlines.h"

struct primconvert_context {
	struct pipe_context *pipe;
	struct pipe_index_buffer saved_ib;

	// TODO we could cache/recycle the indexbuf created to translate prims..
};


struct primconvert_context *util_primconvert_create(struct pipe_context *pipe)
{
	struct primconvert_context *pc = CALLOC_STRUCT(primconvert_context);
	if (!pc)
		return NULL;
	pc->pipe = pipe;
	return pc;
}

void util_primconvert_destroy(struct primconvert_context *pc)
{
	util_primconvert_save_index_buffer(pc, NULL);
	free(pc);
}

void util_primconvert_save_index_buffer(struct primconvert_context *pc,
		const struct pipe_index_buffer *ib)
{
	if (ib) {
		pipe_resource_reference(&pc->saved_ib.buffer, ib->buffer);
		pc->saved_ib.index_size = ib->index_size;
		pc->saved_ib.offset = ib->offset;
		pc->saved_ib.user_buffer = ib->user_buffer;
	} else {
		pipe_resource_reference(&pc->saved_ib.buffer, NULL);
	}
}

typedef uint16_t (*unpack_idx_t)(const void *src, unsigned i, struct pipe_draw_info *info);
typedef void (*convert_t)(uint16_t *dst, const void *src, unpack_idx_t unpack,
		unsigned start, unsigned end, struct pipe_draw_info *info);

static uint16_t unpack_idx_1(const void *src, unsigned i, struct pipe_draw_info *info)
{
	uint16_t val = ((uint8_t *)src)[i];
	info->min_index = MIN2(info->min_index, val);
	info->max_index = MAX2(info->max_index, val);
	return val;
}

static uint16_t unpack_idx_2(const void *src, unsigned i, struct pipe_draw_info *info)
{
	uint16_t val = ((uint16_t *)src)[i];
	info->min_index = MIN2(info->min_index, val);
	info->max_index = MAX2(info->max_index, val);
	return val;
}

static uint16_t unpack_idx_4(const void *src, unsigned i, struct pipe_draw_info *info)
{
	uint16_t val = ((uint32_t *)src)[i];
	info->min_index = MIN2(info->min_index, val);
	info->max_index = MAX2(info->max_index, val);
	return val;
}

static void convert_quads(uint16_t *dst, const void *src, unpack_idx_t unpack,
		unsigned start, unsigned end, struct pipe_draw_info *info)
{
	unsigned i;
	if (src) {
		info->max_index = ~0;
		info->min_index = 0;
		for (i = start; (i + 3) < end; i += 4) {
			*(dst++) = unpack(src, i+0, info);
			*(dst++) = unpack(src, i+1, info);
			*(dst++) = unpack(src, i+2, info);
			*(dst++) = unpack(src, i+0, info);
			*(dst++) = unpack(src, i+2, info);
			*(dst++) = unpack(src, i+3, info);
		}
	} else {
		info->min_index = start;
		for (i = start; (i + 3) < end; i += 4) {
			*(dst++) = i+0;
			*(dst++) = i+1;
			*(dst++) = i+2;
			*(dst++) = i+0;
			*(dst++) = i+2;
			*(dst++) = i+3;
		}
		info->max_index = i + 3;
	}
}

void util_primconvert_draw_vbo(struct primconvert_context *pc,
		const struct pipe_draw_info *info)
{
	struct pipe_index_buffer *ib = &pc->saved_ib;
	struct pipe_index_buffer new_ib = {0};
	struct pipe_draw_info new_info = {0};
	struct pipe_transfer *src_transfer = NULL, *dst_transfer = NULL;
	convert_t convert;
	unpack_idx_t unpack;
	const void *src;
	void *dst;

	switch (info->mode) {
	case PIPE_PRIM_QUADS:
		convert = convert_quads;
		new_info.mode = PIPE_PRIM_TRIANGLES;
		new_info.start = 0;
		new_info.count = 6 * align(info->count, 4) / 4;
		new_info.indexed = true;
		break;
	default:
		// TODO .. others..
		assert(0);
		return;
	}

	if (info->indexed) {
		switch (ib->index_size) {
		case 1:
			unpack = unpack_idx_1;
			break;
		case 2:
			unpack = unpack_idx_2;
			break;
		case 4:
			unpack = unpack_idx_4;
			break;
		default:
			assert(0);
			return;
		}
		src = ib->user_buffer;
		if (!src) {
			src = pipe_buffer_map(pc->pipe, ib->buffer,
					PIPE_TRANSFER_READ, &src_transfer);
		}
	} else {
		unpack = NULL;
		src = NULL;
	}

	/* create new index buffer: */
	new_ib.index_size = 2;
	new_ib.offset = 0;

	// TODO check pipe caps to see if we want to upload index buffer or not..
	new_ib.buffer = pipe_buffer_create(pc->pipe->screen,
			PIPE_BIND_INDEX_BUFFER, PIPE_USAGE_IMMUTABLE, 2 * new_info.count);
	dst = pipe_buffer_map(pc->pipe, new_ib.buffer, PIPE_TRANSFER_WRITE, &dst_transfer);

	/* generate index buffer to remap vertices: */
	convert(dst, src, unpack, info->start, info->start + info->count, &new_info);

	if (src_transfer)
		pipe_buffer_unmap(pc->pipe, src_transfer);

	if (dst_transfer)
		pipe_buffer_unmap(pc->pipe, dst_transfer);

	/* bind new index buffer: */
	pc->pipe->set_index_buffer(pc->pipe, &new_ib);

	/* to the translated draw: */
	pc->pipe->draw_vbo(pc->pipe, &new_info);

	/* and then restore saved ib: */
	pc->pipe->set_index_buffer(pc->pipe, ib);

	pipe_resource_reference(&new_ib.buffer, NULL);

}
