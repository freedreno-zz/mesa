/* $XFree86$ */
/**************************************************************************

Copyright 2000, 2001 ATI Technologies Inc., Ontario, Canada, and
                     Tungsten Graphics Inc., Austin, Texas.

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
ATI, TUNGSTEN GRAPHICS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

/*
 * Authors:
 *   Keith Whitwell <keith@tungstengraphics.com>
 *
 */

#include "glheader.h"
#include "imports.h"
#include "mmath.h"
#include "mtypes.h"
#include "enums.h"

#include "radeon_context.h"
#include "radeon_state.h"
#include "radeon_ioctl.h"
#include "radeon_tex.h"
#include "radeon_tcl.h"


/* KW: Import a version of radeon_tcl.c plus t_dd_dmatmp2.h here.
 *
 * This is all just to support radeon_subset_vtx.c, and is pretty
 * heavyweight for that purpose -- it shouldn't be hard to get the
 * code there to turn quads into triangles, etc, in a lot less code.
 */



#define HAVE_POINTS      1
#define HAVE_LINES       1
#define HAVE_LINE_LOOP   0
#define HAVE_LINE_STRIPS 1
#define HAVE_TRIANGLES   1
#define HAVE_TRI_STRIPS  1
#define HAVE_TRI_STRIP_1 0
#define HAVE_TRI_FANS    1
#define HAVE_QUADS       0
#define HAVE_QUAD_STRIPS 0
#define HAVE_POLYGONS    1
#define HAVE_ELTS        1


#define HW_POINTS           RADEON_CP_VC_CNTL_PRIM_TYPE_POINT
#define HW_LINES            RADEON_CP_VC_CNTL_PRIM_TYPE_LINE
#define HW_LINE_LOOP        0
#define HW_LINE_STRIP       RADEON_CP_VC_CNTL_PRIM_TYPE_LINE_STRIP
#define HW_TRIANGLES        RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_LIST
#define HW_TRIANGLE_STRIP_0 RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_STRIP
#define HW_TRIANGLE_STRIP_1 0
#define HW_TRIANGLE_FAN     RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_FAN
#define HW_QUADS            0
#define HW_QUAD_STRIP       0
#define HW_POLYGON          RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_FAN



#define LOCAL_VARS radeonContextPtr rmesa = RADEON_CONTEXT(ctx)
#define ELTS_VARS  GLushort *dest

#define ELT_INIT(prim, hw_prim) \
   radeonTclPrimitive( ctx, prim, hw_prim | RADEON_CP_VC_CNTL_PRIM_WALK_IND )

#define GET_ELTS() rmesa->tcl.Elts


#define NEW_PRIMITIVE()  RADEON_NEWPRIM( rmesa )
#define NEW_BUFFER()  radeonRefillCurrentDmaRegion( rmesa )

/* Don't really know how many elts will fit in what's left of cmdbuf,
 * as there is state to emit, etc:
 */
/* Testing on isosurf shows a maximum around here.  Don't know if it's
 * the card or driver or kernel module that is causing the behaviour.
 */
#define GET_CURRENT_VB_MAX_ELTS() 300
#define GET_SUBSEQUENT_VB_MAX_ELTS() 300

#define RESET_STIPPLE() do {			\
   RADEON_STATECHANGE( rmesa, lin );		\
   radeonEmitState( rmesa );			\
} while (0)

#define AUTO_STIPPLE( mode )  do {		\
   RADEON_STATECHANGE( rmesa, lin );		\
   if (mode)					\
      rmesa->hw.lin.cmd[LIN_RE_LINE_PATTERN] |=	\
	 RADEON_LINE_PATTERN_AUTO_RESET;	\
   else						\
      rmesa->hw.lin.cmd[LIN_RE_LINE_PATTERN] &=	\
	 ~RADEON_LINE_PATTERN_AUTO_RESET;	\
   radeonEmitState( rmesa );			\
} while (0)


/* How do you extend an existing primitive?
 */
#define ALLOC_ELTS(nr)							\
do {									\
   if (rmesa->dma.flush == radeonFlushElts &&				\
       rmesa->store.cmd_used + nr*2 < RADEON_CMD_BUF_SZ) {		\
									\
      dest = (GLushort *)(rmesa->store.cmd_buf + 			\
			  rmesa->store.cmd_used);			\
      rmesa->store.cmd_used += nr*2;					\
   }									\
   else {								\
      if (rmesa->dma.flush)						\
	 rmesa->dma.flush( rmesa );					\
									\
      radeonEmitAOS( rmesa,						\
	  	     rmesa->tcl.aos_components,				\
		     rmesa->tcl.nr_aos_components,			\
		     0 );						\
									\
      dest = radeonAllocEltsOpenEnded( rmesa,				\
				       rmesa->tcl.vertex_format,	\
				       rmesa->tcl.hw_primitive,		\
				       nr );				\
   }									\
} while (0) 



/* TODO: Try to extend existing primitive if both are identical,
 * discreet and there are no intervening state changes.  (Somewhat
 * duplicates changes to DrawArrays code)
 */
static void EMIT_PRIM( GLcontext *ctx, 
		       GLenum prim, 
		       GLuint hwprim, 
		       GLuint start, 
		       GLuint count)	
{
   radeonContextPtr rmesa = RADEON_CONTEXT( ctx );
   radeonTclPrimitive( ctx, prim, hwprim );
   
   radeonEmitAOS( rmesa,
		  rmesa->tcl.aos_components,
		  rmesa->tcl.nr_aos_components,
		  start );
   
   /* Why couldn't this packet have taken an offset param?
    */
   radeonEmitVbufPrim( rmesa,
		       rmesa->tcl.vertex_format,
		       rmesa->tcl.hw_primitive,
		       count - start );
}



#define EMIT_ELT(offset, x) (dest)[offset] = (GLushort) (x)
#define EMIT_TWO_ELTS(offset, x, y)  *(GLuint *)(dest+offset) = ((y)<<16)|(x);
#define INCR_ELTS( nr ) dest += nr
#define RELEASE_ELT_VERTS() 
#define TAG(x) tcl_##x




/**********************************************************************/
/*                  Render whole begin/end objects                    */
/**********************************************************************/


static void TAG(emit_consecutive_elts)( GLcontext *ctx, GLuint start, GLuint nr )
{
   GLint i;
   LOCAL_VARS;
   ELTS_VARS;

   ALLOC_ELTS( nr );

   for ( i = 0 ; i+1 < nr ; i+=2, start += 2 ) {
      EMIT_TWO_ELTS( 0, start, start+1 );
      INCR_ELTS( 2 );
   }
   if (i < nr) {
      EMIT_ELT( 0, start );
      INCR_ELTS( 1 );
   }
}


static void TAG(render_points_verts)( GLcontext *ctx,
				      GLuint start,
				      GLuint count,
				      GLuint flags )
{
   if (start < count) {
      LOCAL_VARS;
      EMIT_PRIM( ctx, GL_POINTS, HW_POINTS, start, count );
   }
}

static void TAG(render_lines_verts)( GLcontext *ctx,
				     GLuint start,
				     GLuint count,
				     GLuint flags )
{
   LOCAL_VARS;
   count -= (count-start) & 1;

   if (start+1 >= count)
      return;

   if ((flags & PRIM_BEGIN) && ctx->Line.StippleFlag) {
      RESET_STIPPLE();
      AUTO_STIPPLE( GL_TRUE );
   }
      
   EMIT_PRIM( ctx, GL_LINES, HW_LINES, start, count );

   if ((flags & PRIM_END) && ctx->Line.StippleFlag)
      AUTO_STIPPLE( GL_FALSE );
}


static void TAG(render_line_strip_verts)( GLcontext *ctx,
					  GLuint start,
					  GLuint count,
					  GLuint flags )
{
   LOCAL_VARS;

   if (start+1 >= count)
      return;

   if ((flags & PRIM_BEGIN) && ctx->Line.StippleFlag)
      RESET_STIPPLE();

   EMIT_PRIM( ctx, GL_LINE_STRIP, HW_LINE_STRIP, start, count );
}


static void TAG(render_line_loop_verts)( GLcontext *ctx,
					 GLuint start,
					 GLuint count,
					 GLuint flags )
{
   LOCAL_VARS;
   GLuint j, nr;

   if (flags & PRIM_BEGIN) {
      j = start;
      if (ctx->Line.StippleFlag)
	 RESET_STIPPLE( );
   }
   else
      j = start + 1;

   if (flags & PRIM_END) {

      int dmasz = GET_SUBSEQUENT_VB_MAX_ELTS();
      int currentsz;

      if (start+1 >= count)
	 return;

      ELT_INIT( GL_LINE_STRIP, HW_LINE_STRIP );

      currentsz = GET_CURRENT_VB_MAX_ELTS();

      if (currentsz < 8) {
	 NEW_BUFFER();
	 currentsz = dmasz;
      }

      /* Ensure last vertex doesn't wrap:
       */
      currentsz--;
      dmasz--;

      for ( ; j + 1 < count;  ) {
	 nr = MIN2( currentsz, count - j );
	 if (j + nr < count) {
	    TAG(emit_consecutive_elts)( ctx, j, nr );
	    currentsz = dmasz;
	    j += nr - 1;
	    NEW_BUFFER();
	 }
	 else if (nr) {
	    ELTS_VARS;
	    int i;

	    ALLOC_ELTS( nr + 1 );
	    for ( i = 0 ; i+1 < nr ; i+=2, j += 2 ) {
	       EMIT_TWO_ELTS( 0, j, j+1 );
	       INCR_ELTS( 2 );
	    }
	    if (i < nr) {
	       EMIT_ELT( 0, j ); j++;
	       INCR_ELTS( 1 );
	    }
	    EMIT_ELT( 0, start );
	    INCR_ELTS( 1 );
	    NEW_BUFFER();
	 }
	 else {
	    fprintf(stderr, "warining nr==0\n");
	 }
      }   
   } else {
      TAG(render_line_strip_verts)( ctx, j, count, flags );
   }
}


static void TAG(render_triangles_verts)( GLcontext *ctx,
					 GLuint start,
					 GLuint count,
					 GLuint flags )
{
   LOCAL_VARS;

   count -= (count-start)%3;

   if (start+2 >= count) {
      return;
   }

   EMIT_PRIM( ctx, GL_TRIANGLES, HW_TRIANGLES, start, count );
}



static void TAG(render_tri_strip_verts)( GLcontext *ctx,
					 GLuint start,
					 GLuint count,
					 GLuint flags )
{
   LOCAL_VARS;

   if (start + 2 >= count)
      return;

   EMIT_PRIM( ctx, GL_TRIANGLE_STRIP, HW_TRIANGLE_STRIP_0, start, count );
}

static void TAG(render_tri_fan_verts)( GLcontext *ctx,
				       GLuint start,
				       GLuint count,
				       GLuint flags )
{
   LOCAL_VARS;

   if (start+2 >= count) 
      return;

   EMIT_PRIM( ctx, GL_TRIANGLE_FAN, HW_TRIANGLE_FAN, start, count );
}


static void TAG(render_poly_verts)( GLcontext *ctx,
				    GLuint start,
				    GLuint count,
				    GLuint flags )
{
   LOCAL_VARS;

   if (start+2 >= count) 
      return;

   EMIT_PRIM( ctx, GL_POLYGON, HW_POLYGON, start, count );
}

static void TAG(render_quad_strip_verts)( GLcontext *ctx,
					  GLuint start,
					  GLuint count,
					  GLuint flags )
{
   LOCAL_VARS;

   count -= (count-start) & 1;

   if (start+3 >= count) 
      return;


   EMIT_PRIM( ctx, GL_TRIANGLE_STRIP, HW_TRIANGLE_STRIP_0, start, count );
}


static void TAG(render_quads_verts)( GLcontext *ctx,
				     GLuint start,
				     GLuint count,
				     GLuint flags )
{
   LOCAL_VARS;
   count -= (count-start)%4;

   if (start+3 >= count) 
      return;

   {
      /* Hardware doesn't have a quad primitive type -- simulate it
       * using indexed vertices and the triangle primitive: 
       */
      LOCAL_VARS;
      int dmasz = GET_SUBSEQUENT_VB_MAX_ELTS();
      int currentsz;
      GLuint j, nr;

      ELT_INIT( GL_TRIANGLES, HW_TRIANGLES );
      currentsz = GET_CURRENT_VB_MAX_ELTS();

      /* Adjust for rendering as triangles:
       */
      currentsz = (currentsz/6)*4;
      dmasz = (dmasz/6)*4;

      if (currentsz < 8) {
	 NEW_BUFFER();
	 currentsz = dmasz;
      }

      for (j = start; j < count; j += nr ) {
	 ELTS_VARS;
	 GLint quads, i;
	 nr = MIN2( currentsz, count - j );
	 quads = nr/4;

	 ALLOC_ELTS( quads*6 );

	 for ( i = j ; i < j+quads*4 ; i+=4 ) {
	    EMIT_TWO_ELTS( 0, (i+0), (i+1) );
	    EMIT_TWO_ELTS( 2, (i+3), (i+1) );
	    EMIT_TWO_ELTS( 4, (i+2), (i+3) );
	    INCR_ELTS( 6 );
	 }

	 if (nr == currentsz) {
	    NEW_BUFFER();
	    currentsz = dmasz;
	 }
      }
   }
}

static void TAG(render_noop)( GLcontext *ctx,
			      GLuint start,
			      GLuint count,
			      GLuint flags )
{
}




static render_func TAG(render_tab_verts)[GL_POLYGON+2] =
{
   TAG(render_points_verts),
   TAG(render_lines_verts),
   TAG(render_line_loop_verts),
   TAG(render_line_strip_verts),
   TAG(render_triangles_verts),
   TAG(render_tri_strip_verts),
   TAG(render_tri_fan_verts),
   TAG(render_quads_verts),
   TAG(render_quad_strip_verts),
   TAG(render_poly_verts),
   TAG(render_noop),
};




/**********************************************************************/
/*                          External entrypoints                     */
/**********************************************************************/

void radeonEmitPrimitive( GLcontext *ctx, 
			  GLuint first,
			  GLuint last,
			  GLuint flags )
{
   tcl_render_tab_verts[flags&PRIM_MODE_MASK]( ctx, first, last, flags );
}


void radeonFallback( GLcontext *ctx, GLuint bit, GLboolean mode )
{
   if (mode)
      fprintf(stderr, "Warning: hit nonexistant fallback path!\n");
}

void radeonTclFallback( GLcontext *ctx, GLuint bit, GLboolean mode )
{
   if (mode)
      fprintf(stderr, "Warning: hit nonexistant fallback path!\n");
}

void radeonTclPrimitive( GLcontext *ctx, 
			 GLenum prim,
			 int hw_prim )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint se_cntl;
   GLuint newprim = hw_prim | rmesa->tcl.tcl_flag;

   RADEON_NEWPRIM( rmesa );
   rmesa->tcl.hw_primitive = newprim;

   se_cntl = rmesa->hw.set.cmd[SET_SE_CNTL];
   se_cntl &= ~RADEON_FLAT_SHADE_VTX_LAST;

   if (prim == GL_POLYGON && (ctx->_TriangleCaps & DD_FLATSHADE)) 
      se_cntl |= RADEON_FLAT_SHADE_VTX_0;
   else
      se_cntl |= RADEON_FLAT_SHADE_VTX_LAST;

   if (se_cntl != rmesa->hw.set.cmd[SET_SE_CNTL]) {
      RADEON_STATECHANGE( rmesa, set );
      rmesa->hw.set.cmd[SET_SE_CNTL] = se_cntl;
   }
}

void radeonSubsetVtxEnableTCL( radeonContextPtr rmesa,
			       GLboolean flag )
{
   if (flag)
      rmesa->tcl.tcl_flag = RADEON_CP_VC_CNTL_TCL_ENABLE;
   else
      rmesa->tcl.tcl_flag = 0;
      
}
