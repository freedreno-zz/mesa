/* $XFree86$ */
/**************************************************************************

Copyright 2000, 2001 ATI Technologies Inc., Ontario, Canada, and
                     Tungsten Graphics Inc., Cedar Park, Texas.

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
#include "api_noop.h"
#include "api_arrayelt.h"
#include "context.h"
#include "mmath.h"
#include "mtypes.h"
#include "enums.h"
#include "glapi.h"
#include "colormac.h"
#include "light.h"
#include "state.h"

#include "radeon_context.h"
#include "radeon_state.h"
#include "radeon_ioctl.h"
#include "radeon_tex.h"
#include "radeon_tcl.h"
#include "radeon_vtxfmt.h"

struct radeon_vb vb;

static void radeonFlushVertices( GLcontext *, GLuint );


void radeon_copy_to_current( GLcontext *ctx ) 
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   assert(ctx->Driver.NeedFlush & FLUSH_UPDATE_CURRENT);
   assert(vb.context == ctx);

   ctx->Current.Attrib[VERT_ATTRIB_COLOR0][0] = vb.floatcolorptr[0];
   ctx->Current.Attrib[VERT_ATTRIB_COLOR0][1] = vb.floatcolorptr[1];
   ctx->Current.Attrib[VERT_ATTRIB_COLOR0][2] = vb.floatcolorptr[2];
   ctx->Current.Attrib[VERT_ATTRIB_COLOR0][3] = vb.floatcolorptr[3];

   if (rmesa->vb.vertex_format & RADEON_CP_VC_FRMT_ST0) {
      ctx->Current.Attrib[VERT_ATTRIB_TEX0][0] = vb.texcoordptr[0][0];
      ctx->Current.Attrib[VERT_ATTRIB_TEX0][1] = vb.texcoordptr[0][1];
      ctx->Current.Attrib[VERT_ATTRIB_TEX0][2] = 0.0F;
      ctx->Current.Attrib[VERT_ATTRIB_TEX0][3] = 1.0F;
   }

   ctx->Driver.NeedFlush &= ~FLUSH_UPDATE_CURRENT;
}


static void flush_prims( radeonContextPtr rmesa )
{
   int i,j;
   struct radeon_dma_region tmp = rmesa->dma.current;
   
   tmp.buf->refcount++;
   tmp.aos_size = vb.vertex_size;
   tmp.aos_stride = vb.vertex_size;
   tmp.aos_start = GET_START(&tmp);

   rmesa->dma.current.ptr = rmesa->dma.current.start += 
      (vb.initial_counter - vb.counter) * vb.vertex_size * 4; 

   rmesa->tcl.vertex_format = rmesa->vb.vertex_format;
   rmesa->tcl.aos_components[0] = &tmp;
   rmesa->tcl.nr_aos_components = 1;
   rmesa->dma.flush = 0;

   for (i = 0 ; i < rmesa->vb.nrprims; i++) {
      radeonEmitPrimitive( vb.context,
			   rmesa->vb.primlist[i].start,
			   rmesa->vb.primlist[i].end,
			   rmesa->vb.primlist[i].prim );
   }

   rmesa->vb.nrprims = 0;
   radeonReleaseDmaRegion( rmesa, &tmp, __FUNCTION__ );
}


static void start_prim( radeonContextPtr rmesa, GLuint mode )
{
   if (RADEON_DEBUG & DEBUG_VFMT)
      fprintf(stderr, "%s %d\n", __FUNCTION__, vb.initial_counter - vb.counter);

   rmesa->vb.primlist[rmesa->vb.nrprims].start = vb.initial_counter-vb.counter;
   rmesa->vb.primlist[rmesa->vb.nrprims].prim = mode;
}

static void note_last_prim( radeonContextPtr rmesa, GLuint flags )
{
   if (RADEON_DEBUG & DEBUG_VFMT)
      fprintf(stderr, "%s %d\n", __FUNCTION__, vb.initial_counter - vb.counter);

   if (rmesa->vb.prim[0] != GL_POLYGON+1) {
      rmesa->vb.primlist[rmesa->vb.nrprims].prim |= flags;
      rmesa->vb.primlist[rmesa->vb.nrprims].end = (vb.initial_counter - 
						   vb.counter);

      if (++(rmesa->vb.nrprims) == RADEON_MAX_PRIMS)
	 flush_prims( rmesa );
   }
}


static void copy_vertex( radeonContextPtr rmesa, GLuint n, GLfloat *dst )
{
   GLuint i;
   GLfloat *src = 
      (GLfloat *)(rmesa->dma.current.address + 
		  rmesa->dma.current.ptr + 
		  (rmesa->vb.primlist[rmesa->vb.nrprims].start + n) * 
		  vb.vertex_size * 4);

   for (i = 0 ; i < vb.vertex_size; i++) {
      dst[i] = src[i];
   }
}

static GLuint copy_dma_verts( radeonContextPtr rmesa, GLfloat (*tmp)[15] )
{
   GLuint ovf, i;
   GLuint nr = ((vb.initial_counter - vb.counter) -
		rmesa->vb.primlist[rmesa->vb.nrprims].start);

   if (RADEON_DEBUG & DEBUG_VFMT)
      fprintf(stderr, "%s %d verts\n", __FUNCTION__, nr);

   switch( rmesa->vb.prim[0] )
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
   case GL_QUADS:
      ovf = nr&3;
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
      ovf = MIN2( nr-1, 2 );
      if (nr > 2) ovf += nr&1;
      for (i = 0 ; i < ovf ; i++)
	 copy_vertex( rmesa, nr-ovf+i, tmp[i] );
      return i;
   default:
      assert(0);
      return 0;
   }
}



static void wrap_buffer( void )
{
   GLcontext *ctx = vb.context;
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLfloat tmp[3][15];
   GLuint i, nrverts;

   if (RADEON_DEBUG & (DEBUG_VFMT|DEBUG_PRIMS))
      fprintf(stderr, "%s %d\n", __FUNCTION__, vb.initial_counter - vb.counter);

   /* Don't wrap buffers on an odd numbered vertex:
    */
   if ((((vb.initial_counter - vb.counter) -  
	 rmesa->vb.primlist[rmesa->vb.nrprims].start) & 1)) {
      vb.counter++;
      vb.initial_counter++;
      return;
   }

   /* Copy vertices out of dma:
    */
   if (rmesa->vb.prim[0] == GL_POLYGON+1) 
      nrverts = 0;
   else {
      nrverts = copy_dma_verts( rmesa, tmp );

      if (RADEON_DEBUG & DEBUG_VFMT)
	 fprintf(stderr, "%d vertices to copy\n", nrverts);
   
      /* Finish the prim at this point:
       */
      note_last_prim( rmesa, 0 );
   }

   /* Fire any buffered primitives
    */
   flush_prims( rmesa );

   /* Get new buffer
    */
   radeonRefillCurrentDmaRegion( rmesa );

   /* Reset counter, dmaptr
    */
   vb.dmaptr = (int *)(rmesa->dma.current.ptr + rmesa->dma.current.address);
   vb.counter = (rmesa->dma.current.end - rmesa->dma.current.ptr) / 
      (vb.vertex_size * 4);
   vb.counter--;
   vb.initial_counter = vb.counter;
   vb.notify = wrap_buffer;

   rmesa->dma.flush = flush_prims;

   /* Restart wrapped primitive:
    */
   if (rmesa->vb.prim[0] != GL_POLYGON+1)
      start_prim( rmesa, rmesa->vb.prim[0] );

   /* Reemit saved vertices
    */
   for (i = 0 ; i < nrverts; i++) {
      memcpy( vb.dmaptr, tmp[i], vb.vertex_size * 4 );
      vb.dmaptr += vb.vertex_size;
      vb.counter--;
   }
}





void radeonVtxfmtInvalidate( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT( ctx );

   rmesa->vb.recheck = GL_TRUE;
   rmesa->vb.fell_back = GL_FALSE;
}




static void radeonVtxfmtValidate( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT( ctx );
   GLuint ind = (RADEON_CP_VC_FRMT_Z |
		 RADEON_CP_VC_FRMT_FPCOLOR | 
		 RADEON_CP_VC_FRMT_FPALPHA);

   if (RADEON_DEBUG & DEBUG_VFMT)
      fprintf(stderr, "%s\n", __FUNCTION__);

   if (ctx->Driver.NeedFlush)
      ctx->Driver.FlushVertices( ctx, ctx->Driver.NeedFlush );
	 
   if (ctx->Texture.Unit[0]._ReallyEnabled) 
      ind |= RADEON_CP_VC_FRMT_ST0;

   if (RADEON_DEBUG & (DEBUG_VFMT|DEBUG_STATE))
      fprintf(stderr, "%s: format: 0x%x\n", __FUNCTION__, ind );

   RADEON_NEWPRIM(rmesa);
   rmesa->vb.vertex_format = ind;
   rmesa->vb.prim = &ctx->Driver.CurrentExecPrimitive;
   vb.vertex_size = 3;

   /* Would prefer to use ubyte floats in the vertex:
    */
   vb.vertex_size += 4;
   vb.floatcolorptr = &vb.vertex[vb.vertex_size].f;
   vb.floatcolorptr[0] = ctx->Current.Attrib[VERT_ATTRIB_COLOR0][0];
   vb.floatcolorptr[1] = ctx->Current.Attrib[VERT_ATTRIB_COLOR0][1];
   vb.floatcolorptr[2] = ctx->Current.Attrib[VERT_ATTRIB_COLOR0][2];
   vb.floatcolorptr[3] = ctx->Current.Attrib[VERT_ATTRIB_COLOR0][3];
   
   if (ind & RADEON_CP_VC_FRMT_ST0) {
      vb.texcoordptr[0] = &vb.vertex[vb.vertex_size].f;
      vb.vertex_size += 2;
      vb.texcoordptr[0][0] = ctx->Current.Attrib[VERT_ATTRIB_TEX0][0];
      vb.texcoordptr[0][1] = ctx->Current.Attrib[VERT_ATTRIB_TEX0][1];   
   } 
   else
      vb.texcoordptr[0] = ctx->Current.Attrib[VERT_ATTRIB_TEX0];

   rmesa->vb.recheck = GL_FALSE;
}





/* Begin/End
 */
static void radeon_Begin( GLenum mode )
{
   GLcontext *ctx = vb.context;
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   
   if (RADEON_DEBUG & DEBUG_VFMT)
      fprintf(stderr, "%s\n", __FUNCTION__);

   if (mode > GL_POLYGON) {
      _mesa_error( ctx, GL_INVALID_ENUM, "glBegin" );
      return;
   }

   if (rmesa->vb.prim[0] != GL_POLYGON+1) {
      _mesa_error( ctx, GL_INVALID_OPERATION, "glBegin" );
      return;
   }
   
   if (ctx->NewState) 
      _mesa_update_state( ctx );

   if (rmesa->NewGLState)
      radeonValidateState( ctx );

   if (rmesa->vb.recheck) 
      radeonVtxfmtValidate( ctx );

   if (rmesa->dma.flush && vb.counter < 12) {
      if (RADEON_DEBUG & DEBUG_VFMT)
	 fprintf(stderr, "%s: flush almost-empty buffers\n", __FUNCTION__);
      flush_prims( rmesa );
   }

   /* Do we need to grab a new dma region for the vertices?
    */
   if (!rmesa->dma.flush) {
      if (rmesa->dma.current.ptr + 12*vb.vertex_size*4 > 
	  rmesa->dma.current.end) {
	 RADEON_NEWPRIM( rmesa );
	 radeonRefillCurrentDmaRegion( rmesa );
      }

      vb.dmaptr = (int *)(rmesa->dma.current.address + rmesa->dma.current.ptr);
      vb.counter = (rmesa->dma.current.end - rmesa->dma.current.ptr) / 
	 (vb.vertex_size * 4);
      vb.counter--;
      vb.initial_counter = vb.counter;
      vb.notify = wrap_buffer;
      rmesa->dma.flush = flush_prims;
      vb.context->Driver.NeedFlush |= FLUSH_STORED_VERTICES;
   }
   
   
   rmesa->vb.prim[0] = mode;
   start_prim( rmesa, mode | PRIM_BEGIN );
}



static void radeon_End( void )
{
   GLcontext *ctx = vb.context;
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   if (RADEON_DEBUG & DEBUG_VFMT)
      fprintf(stderr, "%s\n", __FUNCTION__);

   if (rmesa->vb.prim[0] == GL_POLYGON+1) {
      _mesa_error( ctx, GL_INVALID_OPERATION, "glEnd" );
      return;
   }
	  
   note_last_prim( rmesa, PRIM_END );
   rmesa->vb.prim[0] = GL_POLYGON+1;
}





static void radeonFlushVertices( GLcontext *ctx, GLuint flags )
{
   radeonContextPtr rmesa = RADEON_CONTEXT( ctx );

   if (RADEON_DEBUG & DEBUG_VFMT)
      fprintf(stderr, "%s\n", __FUNCTION__);

   assert(rmesa->vb.installed);
   assert(vb.context == ctx);

   if (flags & FLUSH_UPDATE_CURRENT) {
      radeon_copy_to_current( ctx );
      if (RADEON_DEBUG & DEBUG_VFMT)
	 fprintf(stderr, "reinstall on update_current\n");
      _mesa_install_exec_vtxfmt( ctx, &rmesa->vb.vtxfmt );
      ctx->Driver.NeedFlush &= ~FLUSH_UPDATE_CURRENT;
   }

   if (flags & FLUSH_STORED_VERTICES) {
      radeonContextPtr rmesa = RADEON_CONTEXT( ctx );
      assert (rmesa->dma.flush == 0 ||
	      rmesa->dma.flush == flush_prims);
      if (rmesa->dma.flush == flush_prims)
	 flush_prims( RADEON_CONTEXT( ctx ) );
      ctx->Driver.NeedFlush &= ~FLUSH_STORED_VERTICES;
   }
}



/* Code each function once, let the compiler optimize away the inline
 * calls:
 */
static __inline__ void radeon_Vertex3f( GLfloat x, GLfloat y, GLfloat z )
{
   int i;

   *vb.dmaptr++ = *(int *)&x;
   *vb.dmaptr++ = *(int *)&y;
   *vb.dmaptr++ = *(int *)&z;

   for (i = 3; i < vb.vertex_size; i++)
      *vb.dmaptr++ = vb.vertex[i].i;
   
   if (--vb.counter == 0)
      vb.notify();
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
   GLfloat *dest = vb.texcoordptr[0];
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
   radeonContextPtr rmesa = RADEON_CONTEXT( ctx );
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


   vb.context = ctx;
   rmesa->vb.enabled = 1;
   rmesa->vb.prim = &ctx->Driver.CurrentExecPrimitive;
   rmesa->vb.primflags = 0;


   ctx->Driver.CurrentExecPrimitive = PRIM_OUTSIDE_BEGIN_END;
   radeonVtxfmtValidate( ctx );
   assert( rmesa->vb.installed );
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

