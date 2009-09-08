/*
 * Mesa 3-D graphics library
 * Version:  6.5
 *
 * Copyright (C) 1999-2006  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

/**
 * \file swrast/swrast_features.h
 * \brief Public interface to the software rasterization functions.
 * \author Keith Whitwell <keith@tungstengraphics.com>
 */

#ifndef SWRAST_FEATURES_H
#define SWRAST_FEATURES_H

#include "main/mtypes.h"


#if FEATURE_accum

extern void
_swrast_Accum(GLcontext *ctx, GLenum op, GLfloat value);

#endif


/*
 * Imaging fallbacks (a better solution should be found, perhaps
 * moving all the imaging fallback code to a new module)
 */
#if FEATURE_convolve

extern void
_swrast_CopyConvolutionFilter2D(GLcontext *ctx, GLenum target,
				GLenum internalFormat,
				GLint x, GLint y, GLsizei width,
				GLsizei height);

extern void
_swrast_CopyConvolutionFilter1D(GLcontext *ctx, GLenum target,
				GLenum internalFormat,
				GLint x, GLint y, GLsizei width);

#endif


#if FEATURE_colortable

extern void
_swrast_CopyColorSubTable( GLcontext *ctx,GLenum target, GLsizei start,
			   GLint x, GLint y, GLsizei width);

extern void
_swrast_CopyColorTable( GLcontext *ctx,
			GLenum target, GLenum internalformat,
			GLint x, GLint y, GLsizei width);

#endif


#if FEATURE_drawpix

extern void
_swrast_Bitmap( GLcontext *ctx,
		GLint px, GLint py,
		GLsizei width, GLsizei height,
		const struct gl_pixelstore_attrib *unpack,
		const GLubyte *bitmap );

extern void
_swrast_CopyPixels( GLcontext *ctx,
		    GLint srcx, GLint srcy,
		    GLint destx, GLint desty,
		    GLsizei width, GLsizei height,
		    GLenum type );

extern void
_swrast_DrawPixels( GLcontext *ctx,
		    GLint x, GLint y,
		    GLsizei width, GLsizei height,
		    GLenum format, GLenum type,
		    const struct gl_pixelstore_attrib *unpack,
		    const GLvoid *pixels );

#else /* FEATURE_drawpix */

static INLINE void
_swrast_Bitmap( GLcontext *ctx,
		GLint px, GLint py,
		GLsizei width, GLsizei height,
		const struct gl_pixelstore_attrib *unpack,
		const GLubyte *bitmap )
{
   ASSERT_NO_FEATURE();
}

static INLINE void
_swrast_CopyPixels( GLcontext *ctx,
		    GLint srcx, GLint srcy,
		    GLint destx, GLint desty,
		    GLsizei width, GLsizei height,
		    GLenum type )
{
   ASSERT_NO_FEATURE();
}

static INLINE void
_swrast_DrawPixels( GLcontext *ctx,
		    GLint x, GLint y,
		    GLsizei width, GLsizei height,
		    GLenum format, GLenum type,
		    const struct gl_pixelstore_attrib *unpack,
		    const GLvoid *pixels )
{
   ASSERT_NO_FEATURE();
}

#endif


#endif /* SWRAST_FEATURES_H */
