/**
 * \file radeon_subset_vtx.c
 *
 * \author Keith Whitwell <keith@tungstengraphics.com>
 */

/*
 * Copyright 2000, 2001 ATI Technologies Inc., Ontario, Canada, and
 *                      Tungsten Graphics Inc., Cedar Park, Texas.
 * 
 * All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * ATI, TUNGSTEN GRAPHICS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

/* $XFree86$ */

#include "glheader.h"
#include "imports.h"
#include "api_noop.h"
#include "context.h"
#include "mmath.h"
#include "mtypes.h"
#include "enums.h"
#include "glapi.h"
#include "colormac.h"
#include "state.h"

#include "radeon_context.h"
#include "radeon_state.h"
#include "radeon_ioctl.h"
#include "radeon_tex.h"
#include "radeon_subset.h"

union vertex_dword { float f; int i; };
#define MAX_VERTEX_DWORDS 10	/* xyzw rgba st */

static struct {

   /* Notification mechanism.  These are treated as a stack to allow
    * us to do things like build quads in temporary storage and then
    * emit them as triangles:
    */
   struct {
      GLint vertspace;
      GLint initial_vertspace;
      GLint *dmaptr;
      void (*notify)( void );
   } stack[2];


   /* Storage for current vertex:
    */
   union vertex_dword vertex[MAX_VERTEX_DWORDS];

   /* Temporary storage for quads, etc:
    */
   union vertex_dword vertex_store[MAX_VERTEX_DWORDS * 4];

   /* Pointers to either vertex or ctx->Current.Attrib, depending on
    * whether color/texture participates in the current vertex:
    */
   GLfloat *floatcolorptr;
   GLfloat *texcoordptr;

   /* Pointer to the context.
    */
   GLcontext *context;		

   /* Active prim (may differ from ctx->Driver.CurrentExecPrimitive)
    */
   GLenum prim;
   GLuint vertex_format;
   GLint vertex_size;
   GLboolean recheck;
} vb;


static void radeonFlushVertices( GLcontext *, GLuint );


static struct { int start, incr, hwprim, lnprim, ptprim; } prims[10] = {
   { 1, 1, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_POINT, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_POINT,
     RADEON_CP_VC_CNTL_PRIM_TYPE_POINT},
   { 2, 2, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE,
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE }, 
   { 2, 1, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE_STRIP,
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE_STRIP,
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE_STRIP },
   { 2, 1, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE_STRIP, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE_STRIP,
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE_STRIP },
   { 3, 3, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_LIST, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE,
     RADEON_CP_VC_CNTL_PRIM_TYPE_POINT },
   { 3, 1, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_STRIP, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE,
     RADEON_CP_VC_CNTL_PRIM_TYPE_POINT },
   { 3, 1,
     RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_FAN, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE,
     RADEON_CP_VC_CNTL_PRIM_TYPE_POINT }, 
   { 4, 4, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_LIST, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE,
     RADEON_CP_VC_CNTL_PRIM_TYPE_POINT },
   { 4, 2, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_STRIP, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE,
     RADEON_CP_VC_CNTL_PRIM_TYPE_POINT }, 
   { 3, 1, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_FAN, 
     RADEON_CP_VC_CNTL_PRIM_TYPE_LINE_STRIP,
     RADEON_CP_VC_CNTL_PRIM_TYPE_POINT }, 
};

static void finish_prim( radeonContextPtr rmesa )
{
   GLuint prim_end = vb.stack[0].initial_vertspace - vb.stack[0].vertspace;
   GLuint hwprim = 0;
   
   /* Too few vertices? (eg: 2 vertices for a triangles prim?)
    */
   if (prim_end < prims[vb.prim].start) 
      return;

   /* Drop redundant vertices off end of primitive.  (eg: 5 vertices
    * for triangles prim?)
    */
   prim_end -= (prim_end - prims[vb.prim].start) % prims[vb.prim].incr;

   radeonEmitVertexAOS( rmesa, vb.vertex_size, GET_START(&rmesa->dma.current) );

   switch (vb.context->Polygon.FrontMode) {
   case GL_LINE: hwprim = prims[vb.prim].lnprim; break;
   case GL_POINT: hwprim = prims[vb.prim].ptprim; break;
   case GL_FILL: hwprim = prims[vb.prim].hwprim; break;
   default: return;
   }

   radeonEmitVbufPrim( rmesa, vb.vertex_format,
		       hwprim | rmesa->tcl.tcl_flag, 
		       prim_end );

   rmesa->dma.current.ptr = 
      rmesa->dma.current.start += prim_end * vb.vertex_size * 4; 
}



static void copy_vertex( radeonContextPtr rmesa, GLuint n, GLfloat *dst )
{
   GLuint i;
   GLfloat *src = (GLfloat *)(rmesa->dma.current.address + 
			      rmesa->dma.current.ptr + 
			      n * vb.vertex_size * 4);

   for (i = 0 ; i < vb.vertex_size; i++) 
      dst[i] = src[i];
}


static GLuint copy_dma_verts( radeonContextPtr rmesa, 
			      GLfloat (*tmp)[MAX_VERTEX_DWORDS] )
{
   GLuint ovf, i;
   GLuint nr = vb.stack[0].initial_vertspace - vb.stack[0].vertspace;

   switch( vb.prim )
   {
   case GL_POINTS:
      return 0;
   case GL_LINES:
      ovf = nr&1;
      for (i = 0 ; i < ovf ; i++)
	 copy_vertex( rmesa, nr-ovf+i, tmp[i] );
      return i;
   case GL_TRIANGLES:
      ovf = nr%3;
      for (i = 0 ; i < ovf ; i++)
	 copy_vertex( rmesa, nr-ovf+i, tmp[i] );
      return i;
   case GL_LINE_STRIP:
      if (nr == 0) 
	 return 0;
      copy_vertex( rmesa, nr-1, tmp[0] );
      return 1;
   case GL_LINE_LOOP:
   case GL_TRIANGLE_FAN:
   case GL_POLYGON:
      if (nr == 0) 
	 return 0;
      else if (nr == 1) {
	 copy_vertex( rmesa, 0, tmp[0] );
	 return 1;
      } else {
	 copy_vertex( rmesa, 0, tmp[0] );
	 copy_vertex( rmesa, nr-1, tmp[1] );
	 return 2;
      }
   case GL_TRIANGLE_STRIP:
      ovf = MIN2( nr-1, 2 );
      for (i = 0 ; i < ovf ; i++)
	 copy_vertex( rmesa, nr-ovf+i, tmp[i] );
      return i;
   case GL_QUAD_STRIP:
   case GL_QUADS:
   default:
      return 0;
   }
}

static void notify_wrap_buffer( void );

static void reset_notify( void )
{
   radeonContextPtr rmesa = RADEON_CONTEXT( vb.context );

   vb.stack[0].dmaptr = (int *)(rmesa->dma.current.address +
				rmesa->dma.current.ptr);
   vb.stack[0].vertspace = ((rmesa->dma.current.end - rmesa->dma.current.ptr) / 
			    (vb.vertex_size * 4));
   vb.stack[0].vertspace &= ~1;	/* even numbers only -- avoid tristrip parity */
   vb.stack[0].initial_vertspace = vb.stack[0].vertspace;
   vb.stack[0].notify = notify_wrap_buffer;
}      

static void notify_wrap_buffer( void )
{
   GLcontext *ctx = vb.context;
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLfloat tmp[3][MAX_VERTEX_DWORDS];
   GLuint i, nrverts = 0;

   fprintf(stderr, "%s\n", __FUNCTION__);

   /* Copy vertices out of dma:
    */
   nrverts = copy_dma_verts( rmesa, tmp );
   finish_prim( rmesa );

   /* Get new buffer
    */
   radeonRefillCurrentDmaRegion( rmesa );

   /* Reset vertspace[0], dmaptr
    */
   reset_notify();

   /* Reemit saved vertices
    */
   for (i = 0 ; i < nrverts; i++) {
      memcpy( vb.stack[0].dmaptr, tmp[i], vb.vertex_size * 4 );
      vb.stack[0].dmaptr += vb.vertex_size;
      vb.stack[0].vertspace--;
   }
}

static void notify_noop( void )
{
   vb.stack[0].dmaptr = (int *)vb.vertex;
   vb.stack[0].notify = notify_noop;
   vb.stack[0].vertspace = 1;
}

static void pop_notify( void )
{
   vb.stack[0] = vb.stack[1];
}

static void push_notify( void (*notify)( void ), int space, 
			 union vertex_dword *store )
{
   vb.stack[1] = vb.stack[0];
   vb.stack[0].notify = notify;
   vb.stack[0].initial_vertspace = space;
   vb.stack[0].vertspace = space;
   vb.stack[0].dmaptr = (int *)store;
}


/* Emit a stored vertex (in vb.vertex_store) to dma.
 */
static void emit_vertex( int v )
{
   int i, *tmp = (int *)vb.vertex_store + v * vb.vertex_size;
   
   for (i = 0 ; i < vb.vertex_size ; i++) 
      *vb.stack[0].dmaptr++ = *tmp++;

   if (--vb.stack[0].vertspace == 0)
      vb.stack[0].notify();
}

static void emit_tri( int v0, int v1, int v2 )
{
   assert (vb.context->Polygon.FrontMode == GL_LINE);
   assert (vb.prim == GL_LINES);
   emit_vertex( v0 ); emit_vertex( v1 );
   emit_vertex( v1 ); emit_vertex( v2 );
   emit_vertex( v2 ); emit_vertex( v0 );
}

/* Emit a quad (in vb.vertex_store) to dma as two triangles.
 */
static void emit_quad( int v0, int v1, int v2, int v3 )
{
   if (vb.context->Polygon.FrontMode == GL_LINE) {
      emit_vertex( v0 ); emit_vertex( v1 );
      emit_vertex( v1 ); emit_vertex( v2 );
      emit_vertex( v2 ); emit_vertex( v3 );
      emit_vertex( v3 ); emit_vertex( v0 );
   } 
   else {
      emit_vertex( v0 ); emit_vertex( v1 ); emit_vertex( v3 );
      emit_vertex( v1 ); emit_vertex( v2 ); emit_vertex( v3 );
   }
}

/* Every fourth vertex in a quad primitive, this is called to emit:
 */
static void notify_quad( void )
{
   pop_notify();
   emit_quad( 0, 1, 2, 3 );
   push_notify( notify_quad, 4, vb.vertex_store );
}

/* After the 4th vertex, emit either a quad or a flipped quad each two
 * vertices:
 */
static void notify_qstrip1( void );
static void notify_qstrip0( void )
{
   pop_notify();
   emit_quad( 0, 1, 3, 2 );
   push_notify( notify_qstrip1, 2, vb.vertex_store );
}

static void notify_qstrip1( void )
{
   pop_notify();
   emit_quad( 3, 2, 0, 1 );
   push_notify( notify_qstrip0, 2, vb.vertex_store + 2*vb.vertex_size );
}

/* Emit the saved vertex (but hang on to it for later).  Continue
 * processing this primitive as a linestrip.
 */
static void notify_lineloop0( void )
{
   pop_notify();
   emit_vertex(0);
}

/* Need to decompose tristrip & trifan to tris for unfilled line modes
 */
static void notify_tristrip1( void );
static void notify_tristrip2( void );
static void notify_tristrip0( void )
{
   pop_notify();
   emit_tri( 0, 1, 2 );
   push_notify( notify_tristrip1, 1, vb.vertex_store );
}

static void notify_tristrip1( void )
{
   pop_notify();
   emit_tri( 1, 0, 2 );
   push_notify( notify_tristrip2, 1, vb.vertex_store + 1*vb.vertex_size );
}

static void notify_tristrip2( void )
{
   pop_notify();
   emit_tri( 1, 0, 2 );
   push_notify( notify_tristrip0, 1, vb.vertex_store + 2*vb.vertex_size );
}


static void notify_trifan1( void );
static void notify_trifan0( void )
{
   pop_notify();
   emit_tri( 0, 1, 2 );
   push_notify( notify_trifan1, 1, vb.vertex_store + 1*vb.vertex_size );
}

static void notify_trifan1( void )
{
   pop_notify();
   emit_tri( 0, 2, 1 );
   push_notify( notify_trifan0, 1, vb.vertex_store + 2*vb.vertex_size );
}

/* Emit lines in GL_LINE fill mode
 */
static void notify_tri( void )
{
   pop_notify();
   emit_tri( 0, 1, 2 );
   push_notify( notify_tri, 3, vb.vertex_store );
}



void radeonVtxfmtInvalidate( GLcontext *ctx )
{
   vb.recheck = GL_TRUE;
}


static void radeonVtxfmtValidate( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT( ctx );
   GLuint ind = (RADEON_CP_VC_FRMT_Z |
		 RADEON_CP_VC_FRMT_FPCOLOR | 
		 RADEON_CP_VC_FRMT_FPALPHA);

   if (ctx->Driver.NeedFlush)
      ctx->Driver.FlushVertices( ctx, ctx->Driver.NeedFlush );

   if (ctx->Texture.Unit[0]._ReallyEnabled) 
      ind |= RADEON_CP_VC_FRMT_ST0;

   RADEON_NEWPRIM(rmesa);
   vb.vertex_format = ind;
   vb.vertex_size = 3;

   /* Would prefer to use ubyte floats in the vertex:
    */
   vb.floatcolorptr = &vb.vertex[vb.vertex_size].f;
   vb.vertex_size += 4;
   vb.floatcolorptr[0] = ctx->Current.Attrib[VERT_ATTRIB_COLOR0][0];
   vb.floatcolorptr[1] = ctx->Current.Attrib[VERT_ATTRIB_COLOR0][1];
   vb.floatcolorptr[2] = ctx->Current.Attrib[VERT_ATTRIB_COLOR0][2];
   vb.floatcolorptr[3] = ctx->Current.Attrib[VERT_ATTRIB_COLOR0][3];
   
   if (ind & RADEON_CP_VC_FRMT_ST0) {
      vb.texcoordptr = &vb.vertex[vb.vertex_size].f;
      vb.vertex_size += 2;
      vb.texcoordptr[0] = ctx->Current.Attrib[VERT_ATTRIB_TEX0][0];
      vb.texcoordptr[1] = ctx->Current.Attrib[VERT_ATTRIB_TEX0][1];   
   } 
   else
      vb.texcoordptr = ctx->Current.Attrib[VERT_ATTRIB_TEX0];

   vb.recheck = GL_FALSE;
   ctx->Driver.NeedFlush = FLUSH_UPDATE_CURRENT;
}


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



/* Begin/End
 */
static void radeon_Begin( GLenum mode )
{
   GLcontext *ctx = vb.context;
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint se_cntl;
   
   if (mode > GL_POLYGON) {
      _mesa_error( ctx, GL_INVALID_ENUM, "glBegin" );
      return;
   }

   if (ctx->Driver.CurrentExecPrimitive != GL_POLYGON+1) {
      _mesa_error( ctx, GL_INVALID_OPERATION, "glBegin" );
      return;
   }
   
   if (ctx->NewState) 
      _mesa_update_state( ctx );

   if (rmesa->NewGLState)
      radeonValidateState( ctx );

   if (vb.recheck) 
      radeonVtxfmtValidate( ctx );

   /* Do we need to grab a new dma region for the vertices?
    */
   if (rmesa->dma.current.ptr + 12*vb.vertex_size*4 > rmesa->dma.current.end) {
      RADEON_NEWPRIM( rmesa );
      radeonRefillCurrentDmaRegion( rmesa );
   }

   reset_notify();
   vb.prim = ctx->Driver.CurrentExecPrimitive = mode;
   se_cntl = rmesa->hw.set.cmd[SET_SE_CNTL] | RADEON_FLAT_SHADE_VTX_LAST;

   if (ctx->Line.StippleFlag && 
       (ctx->Polygon.FrontMode == GL_LINE || 
	mode == GL_LINES || 
	mode == GL_LINE_LOOP ||
	mode == GL_LINE_STRIP))
      RESET_STIPPLE();

   switch( mode ) {
   case GL_LINES:
      if (ctx->Line.StippleFlag) 
	 AUTO_STIPPLE( GL_TRUE );
      break;
   case GL_LINE_LOOP:
      vb.prim = GL_LINE_STRIP;
      push_notify( notify_lineloop0, 1, vb.vertex_store );
      break;
   case GL_TRIANGLES:
      if (ctx->Polygon.FrontMode == GL_LINE) {
	 vb.prim = GL_LINES;
	 push_notify( notify_tri, 3, vb.vertex_store );
      }
      break;
   case GL_TRIANGLE_STRIP:
      if (ctx->Polygon.FrontMode == GL_LINE) {
	 vb.prim = GL_LINES;
	 push_notify( notify_tristrip0, 3, vb.vertex_store );
      }
      break;
   case GL_TRIANGLE_FAN:
      if (ctx->Polygon.FrontMode == GL_LINE) {
	 vb.prim = GL_LINES;
	 push_notify( notify_trifan0, 3, vb.vertex_store );
      }
      break;
   case GL_QUADS:
      if (ctx->Polygon.FrontMode == GL_LINE) 
	 vb.prim = GL_LINES;
      else
	 vb.prim = GL_TRIANGLES;
      push_notify( notify_quad, 4, vb.vertex_store );
      break;
   case GL_QUAD_STRIP:
      if (ctx->Polygon.FrontMode == GL_LINE) {
	 push_notify( notify_qstrip0, 4, vb.vertex_store );
      }
      else if (ctx->_TriangleCaps & DD_FLATSHADE) {
	 vb.prim = GL_TRIANGLES;
	 push_notify( notify_qstrip0, 4, vb.vertex_store );
      }
      break;
   case GL_POLYGON:
      if (ctx->_TriangleCaps & DD_FLATSHADE)
	 se_cntl &= ~RADEON_FLAT_SHADE_VTX_LAST;
      if (ctx->Polygon.FrontMode == GL_LINE) 
	 push_notify( notify_lineloop0, 1, vb.vertex_store );
      break;
   default:
      break;
   }

   if (se_cntl != rmesa->hw.set.cmd[SET_SE_CNTL]) {
      RADEON_STATECHANGE( rmesa, set );
      rmesa->hw.set.cmd[SET_SE_CNTL] = se_cntl;
   }
}



static void radeon_End( void )
{
   GLcontext *ctx = vb.context;
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   if (ctx->Driver.CurrentExecPrimitive == GL_POLYGON+1) {
      _mesa_error( ctx, GL_INVALID_OPERATION, "glEnd" );
      return;
   }

   /* Need to finish a line loop?
    */
   if (ctx->Driver.CurrentExecPrimitive == GL_LINE_LOOP) 
      emit_vertex( 0 );

   /* Need to pop off quads/quadstrip/etc notification?
    */
   if (vb.stack[0].notify != notify_wrap_buffer)
      pop_notify();

   finish_prim( rmesa );

   if (ctx->Driver.CurrentExecPrimitive == GL_LINES && ctx->Line.StippleFlag) 
      AUTO_STIPPLE( GL_FALSE );
	  
   ctx->Driver.CurrentExecPrimitive = GL_POLYGON+1;
   notify_noop();
}


static void radeonFlushVertices( GLcontext *ctx, GLuint flags )
{
   if (flags & FLUSH_UPDATE_CURRENT) {
      ctx->Current.Attrib[VERT_ATTRIB_COLOR0][0] = vb.floatcolorptr[0];
      ctx->Current.Attrib[VERT_ATTRIB_COLOR0][1] = vb.floatcolorptr[1];
      ctx->Current.Attrib[VERT_ATTRIB_COLOR0][2] = vb.floatcolorptr[2];
      ctx->Current.Attrib[VERT_ATTRIB_COLOR0][3] = vb.floatcolorptr[3];

      if (vb.vertex_format & RADEON_CP_VC_FRMT_ST0) {
	 ctx->Current.Attrib[VERT_ATTRIB_TEX0][0] = vb.texcoordptr[0];
	 ctx->Current.Attrib[VERT_ATTRIB_TEX0][1] = vb.texcoordptr[1];
	 ctx->Current.Attrib[VERT_ATTRIB_TEX0][2] = 0.0F;
	 ctx->Current.Attrib[VERT_ATTRIB_TEX0][3] = 1.0F;
      }
   }

   ctx->Driver.NeedFlush &= ~FLUSH_STORED_VERTICES;
}


/* Code each function once, let the compiler optimize away the inline
 * calls:
 */
static __inline__ void radeon_Vertex3f( GLfloat x, GLfloat y, GLfloat z )
{
   int i;

   *vb.stack[0].dmaptr++ = *(int *)&x;
   *vb.stack[0].dmaptr++ = *(int *)&y;
   *vb.stack[0].dmaptr++ = *(int *)&z;

   for (i = 3; i < vb.vertex_size; i++) 
      *vb.stack[0].dmaptr++ = vb.vertex[i].i;

   if (--vb.stack[0].vertspace == 0)
      vb.stack[0].notify();
}

static __inline__  void radeon_Color4f( GLfloat r, GLfloat g,
					GLfloat b, GLfloat a )
{
   GLfloat *dest = vb.floatcolorptr;
   dest[0] = r;
   dest[1] = g;
   dest[2] = b;
   dest[3] = a;
}

static __inline__ void radeon_TexCoord2f( GLfloat s, GLfloat t )
{
   GLfloat *dest = vb.texcoordptr;
   dest[0] = s;
   dest[1] = t;
}

/* Rely on __inline__ to make these efficient:
 */
static void radeon_Vertex3fv( const GLfloat *v )
{
   radeon_Vertex3f( v[0], v[1], v[2] );
}

static void radeon_Vertex2f( GLfloat x, GLfloat y )
{
   radeon_Vertex3f( x, y, 0 );
}

static void radeon_Vertex2fv( const GLfloat *v )
{
   radeon_Vertex3f( v[0], v[1], 0 );
}

static void radeon_Color4fv( const GLfloat *v )
{
   radeon_Color4f( v[0], v[1], v[2], v[3] );
}

static void radeon_Color3f( GLfloat r, GLfloat g, GLfloat b )
{
   radeon_Color4f( r, g, b, 1.0 );
}

static void radeon_Color3fv( const GLfloat *v )
{
   radeon_Color4f( v[0], v[1], v[2], 1.0 );
}

static void radeon_TexCoord2fv( const GLfloat *v )
{
   radeon_TexCoord2f( v[0], v[1] );
}


void radeonVtxfmtInit( GLcontext *ctx )
{
   struct _glapi_table *exec = ctx->Exec;

   exec->Color3f = radeon_Color3f;
   exec->Color3fv = radeon_Color3fv;
   exec->Color4f = radeon_Color4f;
   exec->Color4fv = radeon_Color4fv;
   exec->TexCoord2f = radeon_TexCoord2f;
   exec->TexCoord2fv = radeon_TexCoord2fv;
   exec->Vertex2f = radeon_Vertex2f;
   exec->Vertex2fv = radeon_Vertex2fv;
   exec->Vertex3f = radeon_Vertex3f;
   exec->Vertex3fv = radeon_Vertex3fv;
   exec->Begin = radeon_Begin;
   exec->End = radeon_End;
   exec->Rectf = _mesa_noop_Rectf;

   vb.context = ctx;
   
   ctx->Driver.FlushVertices = radeonFlushVertices;
   ctx->Driver.CurrentExecPrimitive = GL_POLYGON+1;
   radeonVtxfmtValidate( ctx );
   notify_noop();
}


void radeonVtxfmtUnbindContext( GLcontext *ctx )
{
}

void radeonVtxfmtMakeCurrent( GLcontext *ctx )
{
}

void radeonVtxfmtDestroy( GLcontext *ctx )
{
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

/**
 * Called by radeonPointsBitmap to disable TCL.
 */
void radeonSubsetVtxEnableTCL( radeonContextPtr rmesa, GLboolean flag )
{
   rmesa->tcl.tcl_flag = flag ? RADEON_CP_VC_CNTL_TCL_ENABLE : 0;
}
