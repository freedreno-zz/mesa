/*
 * Mesa 3-D graphics library
 * Version:  5.1
 *
 * Copyright (C) 1999-2003  Brian Paul   All Rights Reserved.
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
 * Authors:
 *    Keith Whitwell <keith@tungstengraphics.com>
 */

#include "glheader.h"
#include "api_eval.h"
#include "context.h"
#include "macros.h"
#include "math/m_eval.h"
#include "t_vtx_api.h"
#include "t_pipeline.h"

GLboolean *_tnl_translate_edgeflag( GLcontext *ctx, const GLfloat *data,
				    GLuint count, GLuint stride )
{
   GLboolean *ef = 0;
   GLuint i;
   
   for (i = 0 ; i < count ; i++, data += stride)
      ef[i] = (data[0] == 1.0);

   return ef;
}


/* Some nasty stuff still hanging on here.  
 *
 * TODO - remove VB->ColorPtr, etc and just use the AttrPtr's.
 */
static void _tnl_vb_bind_vtx( GLcontext *ctx )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx);
   struct vertex_buffer *VB = &tnl->vb;
   struct tnl_vertex_arrays *tmp = &tnl->vtx_inputs;
   GLfloat *data = tnl->vtx.buffer;
   GLuint count = tnl->vtx.initial_counter - tnl->vtx.counter;
   GLuint attr, i;

   /* Setup constant data in the VB.
    */
   VB->Count = count;
   VB->Primitive = tnl->vtx.prim;
   VB->PrimitiveCount = tnl->vtx.prim_count;
   VB->Elts = NULL;
   VB->NormalLengthPtr = NULL;

   for (attr = 0; attr <= _TNL_ATTRIB_INDEX ; attr++) {
      if (tnl->vtx.attrsz[attr]) {
	 tmp->Attribs[attr].count = count;
	 tmp->Attribs[attr].data = (GLfloat (*)[4]) data;
	 tmp->Attribs[attr].start = data;
	 tmp->Attribs[attr].size = tnl->vtx.attrsz[attr];
	 tmp->Attribs[attr].stride = tnl->vtx.vertex_size * sizeof(GLfloat);
	 VB->AttribPtr[attr] = &tmp->Attribs[attr];
	 data += tnl->vtx.attrsz[attr];
      }
      else {
	 VB->AttribPtr[attr] = &tnl->current.Attribs[attr];
      }
   }

   
   /* Copy and translate EdgeFlag to a contiguous array of GLbooleans
    */
   if (tnl->vtx.attrsz[_TNL_ATTRIB_EDGEFLAG]) {
      VB->EdgeFlag = _tnl_translate_edgeflag( ctx, data, count,
					      tnl->vtx.vertex_size );
      data++;
   }

   /* Legacy pointers -- remove one day.
    */
   VB->ObjPtr = VB->AttribPtr[_TNL_ATTRIB_POS];
   VB->NormalPtr = VB->AttribPtr[_TNL_ATTRIB_NORMAL];
   VB->ColorPtr[0] = VB->AttribPtr[_TNL_ATTRIB_COLOR0];
   VB->IndexPtr[0] = VB->AttribPtr[_TNL_ATTRIB_INDEX];
   VB->SecondaryColorPtr[0] = VB->AttribPtr[_TNL_ATTRIB_COLOR1];

   for (i = 0; i < ctx->Const.MaxTextureCoordUnits; i++) {
      VB->TexCoordPtr[i] = VB->AttribPtr[_TNL_ATTRIB_TEX0 + i];
   }
}





/*
 * NOTE: Need to have calculated primitives by this point -- do it on the fly.
 * NOTE: Old 'parity' issue is gone.
 */
static GLuint _tnl_copy_vertices( GLcontext *ctx )
{
   TNLcontext *tnl = TNL_CONTEXT( ctx );
   GLuint nr = tnl->vtx.prim[tnl->vtx.prim_count-1].count;
   GLuint ovf, i;
   GLuint sz = tnl->vtx.vertex_size;
   GLfloat *dst = tnl->vtx.copied.buffer;
   GLfloat *src = (tnl->vtx.buffer + 
		   tnl->vtx.prim[tnl->vtx.prim_count-1].start * 
		   tnl->vtx.vertex_size);


   switch( ctx->Driver.CurrentExecPrimitive )
   {
   case GL_POINTS:
      return 0;
   case GL_LINES:
      ovf = nr&1;
      for (i = 0 ; i < ovf ; i++)
	 memcpy( dst+i*sz, src+(nr-ovf+i)*sz, sz * sizeof(GLfloat) );
      return i;
   case GL_TRIANGLES:
      ovf = nr%3;
      for (i = 0 ; i < ovf ; i++)
	 memcpy( dst+i*sz, src+(nr-ovf+i)*sz, sz * sizeof(GLfloat) );
      return i;
   case GL_QUADS:
      ovf = nr&3;
      for (i = 0 ; i < ovf ; i++)
	 memcpy( dst+i*sz, src+(nr-ovf+i)*sz, sz * sizeof(GLfloat) );
      return i;
   case GL_LINE_STRIP:
      if (nr == 0) 
	 return 0;
      else {
	 memcpy( dst, src+(nr-1)*sz, sz * sizeof(GLfloat) );
	 return 1;
      }
   case GL_LINE_LOOP:
   case GL_TRIANGLE_FAN:
   case GL_POLYGON:
      if (nr == 0) 
	 return 0;
      else if (nr == 1) {
	 memcpy( dst, src+0, sz * sizeof(GLfloat) );
	 return 1;
      } else {
	 memcpy( dst, src+0, sz * sizeof(GLfloat) );
	 memcpy( dst+sz, src+(nr-1)*sz, sz * sizeof(GLfloat) );
	 return 2;
      }
   case GL_TRIANGLE_STRIP:
   case GL_QUAD_STRIP:
      switch (nr) {
      case 0: ovf = 0; break;
      case 1: ovf = 1; break;
      default: ovf = 2 + (nr&1); break;
      }
      for (i = 0 ; i < ovf ; i++)
	 memcpy( dst+i*sz, src+(nr-ovf+i)*sz, sz * sizeof(GLfloat) );
      return i;
   case GL_POLYGON+1:
      return 0;
   default:
      assert(0);
      return 0;
   }
}






/**
 * Execute the buffer and save copied verts.
 */
void _tnl_flush_vtx( GLcontext *ctx )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx);

   if (!tnl->vtx.prim_count) 
      return;

   tnl->vtx.copied.nr = _tnl_copy_vertices( ctx ); 
   
   if (tnl->pipeline.build_state_changes)
      _tnl_validate_pipeline( ctx );

   _tnl_vb_bind_vtx( ctx );

   /* Invalidate all stored data before and after run:
    */
   tnl->pipeline.run_input_changes |= tnl->pipeline.inputs;
   tnl->Driver.RunPipeline( ctx );
   tnl->pipeline.run_input_changes |= tnl->pipeline.inputs;
}





