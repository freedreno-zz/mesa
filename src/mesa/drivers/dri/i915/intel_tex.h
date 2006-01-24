/**************************************************************************
 * 
 * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.
 * All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 **************************************************************************/

#ifndef INTELTEX_INC
#define INTELTEX_INC

#include "mtypes.h"
#include "intel_context.h"
#include "texmem.h"


void intelInitTextureFuncs( struct dd_function_table *functions );

const struct gl_texture_format *
intelChooseTextureFormat( GLcontext *ctx, GLint internalFormat,
                          GLenum format, GLenum type );

void intelTexImage2D(GLcontext *ctx, 
		     GLenum target, GLint level,
		     GLint internalFormat,
		     GLint width, GLint height, GLint border,
		     GLenum format, GLenum type, const void *pixels,
		     const struct gl_pixelstore_attrib *packing,
		     struct gl_texture_object *texObj,
		     struct gl_texture_image *texImage);

void intelTexSubImage2D(GLcontext *ctx,
			GLenum target,
			GLint level,
			GLint xoffset, GLint yoffset,
			GLsizei width, GLsizei height,
			GLenum format, GLenum type,
			const GLvoid *pixels,
			const struct gl_pixelstore_attrib *packing,
			struct gl_texture_object *texObj,
			struct gl_texture_image *texImage);

void intelTexImage1D(GLcontext *ctx, 
		     GLenum target, GLint level,
		     GLint internalFormat,
		     GLint width, GLint border,
		     GLenum format, GLenum type, const void *pixels,
		     const struct gl_pixelstore_attrib *packing,
		     struct gl_texture_object *texObj,
		     struct gl_texture_image *texImage);

void intelTexSubImage1D(GLcontext *ctx,
			GLenum target,
			GLint level,
			GLint xoffset,
			GLsizei width,
			GLenum format, GLenum type,
			const GLvoid *pixels,
			const struct gl_pixelstore_attrib *packing,
			struct gl_texture_object *texObj,
			struct gl_texture_image *texImage);

GLuint intel_validate_mipmap_tree( struct intel_context *intel,
				   struct intel_texture_object *intelObj );




#endif
