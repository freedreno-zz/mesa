/* $XFree86$ */
/**************************************************************************

Copyright 2000, 2001 ATI Technologies Inc., Ontario, Canada, and
                     VA Linux Systems Inc., Fremont, California.

All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
on the rights to use, copy, modify, merge, publish, distribute, sub
license, and/or sell copies of the Software, and to permit persons to whom
the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice (including the next
paragraph) shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
ATI, VA LINUX SYSTEMS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

/*
 * Authors:
 *   Keith Whitwell <keith@tungstengraphics.com>
 *
 */

#ifndef __RADEON_SWTCL_H__
#define __RADEON_SWTCL_H__

#include "mtypes.h"
#include "swrast/swrast.h"

/* Flags for software fallback cases */
/* See correponding strings in radeon_swtcl.c */
#define RADEON_FALLBACK_TEXTURE		0x0001
#define RADEON_FALLBACK_DRAW_BUFFER	0x0002
#define RADEON_FALLBACK_STENCIL		0x0004
#define RADEON_FALLBACK_RENDER_MODE	0x0008
#define RADEON_FALLBACK_BLEND_EQ	0x0010
#define RADEON_FALLBACK_BLEND_FUNC	0x0020
#define RADEON_FALLBACK_DISABLE 	0x0040

/* Use the templated vertex format:
 */
#define COLOR_IS_RGBA
#define TAG(x) radeon##x
#include "tnl_dd/t_dd_vertex.h"
#undef TAG

typedef void (*radeon_tri_func)( radeonContextPtr,
				 radeonVertex *,
				 radeonVertex *,
				 radeonVertex * );

typedef void (*radeon_line_func)( radeonContextPtr,
				  radeonVertex *,
				  radeonVertex * );

typedef void (*radeon_point_func)( radeonContextPtr,
				   radeonVertex * );


/* radeon_swtcl.c
 */
struct radeon_swtcl_info {
   GLuint SetupIndex;
   GLuint SetupNewInputs;
   GLuint RenderIndex;
   GLuint vertex_size;
   GLuint vertex_stride_shift;
   GLuint vertex_format;
   char *verts;

   /* Fallback rasterization functions
    */
   radeon_point_func draw_point;
   radeon_line_func draw_line;
   radeon_tri_func draw_tri;

   GLuint hw_primitive;
   GLenum render_primitive;
   GLuint numverts;

   struct radeon_dma_region indexed_verts;
};

extern void radeonCreateTnlContext( GLcontext *ctx );
extern void radeonInitSwtcl( GLcontext *ctx );
extern void radeonDestroySwtcl( GLcontext *ctx );

extern void radeonChooseRenderState( GLcontext *ctx );
extern void radeonChooseVertexState( GLcontext *ctx );

extern void radeonCheckTexSizes( GLcontext *ctx );

extern void radeonBuildVertices( GLcontext *ctx, GLuint start, GLuint count,
				 GLuint newinputs );

extern void radeonPrintSetupFlags(char *msg, GLuint flags );


extern void radeon_emit_contiguous_verts( GLcontext *ctx,
					  GLuint start,
					  GLuint count );

extern void radeon_emit_indexed_verts( GLcontext *ctx,
				       GLuint start,
				       GLuint count );

extern void radeon_translate_vertex( GLcontext *ctx, 
				     const radeonVertex *src, 
				     SWvertex *dst );

extern void radeon_print_vertex( GLcontext *ctx, const radeonVertex *v );

extern void radeon_import_float_colors( GLcontext *ctx );
extern void radeon_import_float_spec_colors( GLcontext *ctx );



#endif
