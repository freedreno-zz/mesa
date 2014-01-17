/* -*- mode: C; c-file-style: "k&r"; tab-width 4; indent-tabs-mode: t; -*- */

/*
 * Copyright (C) 2014 Rob Clark <robclark@freedesktop.org>
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

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <err.h>

#include "tgsi/tgsi_parse.h"
#include "tgsi/tgsi_text.h"
#include "tgsi/tgsi_dump.h"

#include "fd3_compiler.h"
#include "fd3_program.h"

#include "freedreno_lowering.h"

#include "instr-a3xx.h"
#include "ir3.h"

int
fd3_compile_shader_new(struct fd3_shader_stateobj *so,
		const struct tgsi_token *tokens);

/* a nice hack to make a standalone compiler (assembler) for testing */

static void
read_file(const char *filename, void **ptr, size_t *size)
{
	int fd, ret;
	struct stat st;

	*ptr = MAP_FAILED;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		errx(1, "couldn't open `%s'", filename);

	ret = fstat(fd, &st);
	if (ret)
		errx(1, "couldn't stat `%s'", filename);

	*size = st.st_size;
	*ptr = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (*ptr == MAP_FAILED)
		errx(1, "couldn't map `%s'", filename);

	close(fd);
}


int main(int argc, char **argv)
{
	int i;
	for (i = 1; i < argc; i++) {
		const char *filename = argv[i];
		struct tgsi_token tokens[1000], *toks;
		struct tgsi_parse_context parse;
		struct fd3_shader_stateobj so;
		void *ptr;
		size_t size;

		read_file(filename, &ptr, &size);

		if (!tgsi_text_translate(ptr, tokens, Elements(tokens)))
			errx(1, "could not parse `%s'", filename);

		toks = fd_transform_lowering(tokens);
		if (!toks)
			toks = tokens;

		tgsi_parse_init(&parse, toks);
		switch(parse.FullHeader.Processor.Processor) {
		case TGSI_PROCESSOR_FRAGMENT:
			so.type = SHADER_FRAGMENT;
			break;
		case TGSI_PROCESSOR_VERTEX:
			so.type = SHADER_VERTEX;
			break;
		case TGSI_PROCESSOR_COMPUTE:
			so.type = SHADER_COMPUTE;
			break;
		}

		fd3_compile_shader_new(&so, toks);
	}
}
