
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
 */

/* Author:
 *    Keith Whitwell <keith@tungstengraphics.com>
 */

#include "mtypes.h"
#include "t_pipeline.h"
#include "t_save_api.h"

/* Some nasty stuff still hanging on here.  
 *
 * TODO - remove VB->ColorPtr, etc and just use the AttrPtr's.
 */
static void _tnl_bind_vertex_list( GLcontext *ctx,
				    struct tnl_vertex_list *node )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx);
   struct vertex_buffer *VB = &tnl->vb;
   struct tnl_vertex_arrays *tmp = &tnl->save_inputs;
   GLfloat *data = node->buffer;
   GLuint attr, i;

   /* Setup constant data in the VB.
    */
   VB->Count = node->count;
   VB->Primitive = node->prim;
   VB->PrimitiveCount = node->prim_count;
   VB->Elts = NULL;
   VB->NormalLengthPtr = NULL;
   VB->ColorPtr[1] = NULL;
   VB->SecondaryColorPtr[1] = NULL;
   VB->IndexPtr[1] = NULL;


   for (attr = 0; attr < _TNL_ATTRIB_EVALFLAG; attr++) {
      if (node->attrsz[attr]) {
	 tmp->Attribs[attr].count = node->count;
	 tmp->Attribs[attr].data = (GLfloat (*)[4]) data;
	 tmp->Attribs[attr].start = data;
	 tmp->Attribs[attr].size = node->attrsz[attr];
	 tmp->Attribs[attr].stride = node->vertex_size * sizeof(GLfloat);
	 VB->AttribPtr[attr] = &tmp->Attribs[attr];
	 data += node->attrsz[attr];
      }
      else {
	 VB->AttribPtr[attr] = &tnl->current.Attribs[attr];
      }
   }

   /* Index and edgeflag require special treatment, as usual:
    */
   if (node->attrsz[_TNL_ATTRIB_INDEX]) {
      tmp->Index.count = node->count;
      tmp->Index.data = data;
      tmp->Index.start = data;
      tmp->Index.stride = node->vertex_size * sizeof(GLfloat);
      VB->IndexPtr[0] = &tmp->Index;
      data++;
   }
   
   /* Copy edgeflag to a contiguous array?
    */
   if (node->attrsz[_TNL_ATTRIB_EDGEFLAG]) {
      VB->EdgeFlag = _tnl_translate_edgeflag( ctx, data, node->vertex_size );
      data++;
   }

   /* Legacy pointers -- remove one day.
    */
   VB->ObjPtr = VB->AttribPtr[_TNL_ATTRIB_POS];
   VB->NormalPtr = VB->AttribPtr[_TNL_ATTRIB_NORMAL];
   VB->ColorPtr[0] = VB->AttribPtr[_TNL_ATTRIB_COLOR0];
   VB->SecondaryColorPtr[0] = VB->AttribPtr[_TNL_ATTRIB_COLOR1];

   for (i = 0; i < ctx->Const.MaxTextureCoordUnits; i++) {
      VB->TexCoordPtr[i] = VB->AttribPtr[_TNL_ATTRIB_TEX0 + i];
   }
}



/**
 * Execute the buffer and save copied verts.
 */
void _tnl_playback_vertex_list( GLcontext *ctx, struct tnl_vertex_list *node )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx);

   if (!node->prim_count) 
      return;

   if (tnl->pipeline.build_state_changes)
      _tnl_validate_pipeline( ctx );

   _tnl_bind_vertex_list( ctx, node );

   /* Invalidate all stored data before and after run:
    */
   tnl->pipeline.run_input_changes |= tnl->pipeline.inputs;
   tnl->Driver.RunPipeline( ctx );
   tnl->pipeline.run_input_changes |= tnl->pipeline.inputs;

   /* Copy to current?
    */
}





