
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
#include "colormac.h"
#include "context.h"
#include "macros.h"
#include "imports.h"
#include "mtypes.h"
#include "math/m_eval.h"

#include "t_context.h"
#include "t_imm_debug.h"
#include "t_imm_eval.h"
#include "t_imm_exec.h"
#include "t_imm_fixup.h"
#include "t_imm_alloc.h"



static const GLubyte dirty_flags[5] = {
   0,				/* not possible */
   VEC_DIRTY_0,
   VEC_DIRTY_1,
   VEC_DIRTY_2,
   VEC_DIRTY_3
};


static void eval1_4f( GLvector4f *dest,
		      GLfloat coord[][4],
		      const GLuint *flags,
		      GLuint dimension,
		      const struct gl_1d_map *map )
{
   const GLfloat u1 = map->u1;
   const GLfloat du = map->du;
   GLfloat (*to)[4] = dest->data;
   GLuint i;

   for (i = 0 ; i < count ; i++)
      if (flags[i] == TNL_EVAL_COORD1) {
	 GLfloat u = (coord[i][0] - u1) * du;
	 ASSIGN_4V(to[i], 0,0,0,1);
	 _math_horner_bezier_curve(map->Points, to[i], u,
				   dimension, map->Order);
      }

   dest->size = MAX2(dest->size, dimension);
   dest->flags |= dirty_flags[dimension];
}



static void eval2_auto_normal( GLvector4f *pos_ptr,
			       GLvector4f *norm_ptr,
			       GLfloat coord[][4],
			       GLuint *flags,
			       GLuint dimension,
			       const struct gl_2d_map *map )
{
   const GLfloat u1 = map->u1;
   const GLfloat du = map->du;
   const GLfloat v1 = map->v1;
   const GLfloat dv = map->dv;
   GLfloat (*pos)[4] = pos_ptr->data;
   GLfloat (*normal)[4] = norm_ptr->data;
   GLuint i;

   for (i = 0 ; i < count ; i++)
      if (flags[i] == TNL_EVAL_COORD2) {
	 GLfloat u = (coord[i][0] - u1) * du;
	 GLfloat v = (coord[i][1] - v1) * dv;
	 GLfloat du[4], dv[4];

	 ASSIGN_4V(pos[i], 0,0,0,1);
	 _math_de_casteljau_surf(map->Points, pos[i], du, dv, u, v, dimension,
				 map->Uorder, map->Vorder);

	 if (dimension == 4) {
	    du[0] = du[0]*pos[i][3] - du[3]*pos[i][0];
	    du[1] = du[1]*pos[i][3] - du[3]*pos[i][1];
	    du[2] = du[2]*pos[i][3] - du[3]*pos[i][2];
	 
	    dv[0] = dv[0]*pos[i][3] - dv[3]*pos[i][0];
	    dv[1] = dv[1]*pos[i][3] - dv[3]*pos[i][1];
	    dv[2] = dv[2]*pos[i][3] - dv[3]*pos[i][2];
	 }

	 CROSS3(normal[i], du, dv);
	 NORMALIZE_3FV(normal[i]);
	 normal[i][3] = 1;	/* fill in final value */      
      }

   pos_ptr->size = MAX2(pos_ptr->size, dimension);
   pos_ptr->flags |= dirty_flags[dimension];
}


static void eval2_4f( GLvector4f *dest,
		      GLfloat coord[][4],
		      const GLuint *flags,
		      GLuint dimension,
		      const struct gl_2d_map *map )
{
   const GLfloat u1 = map->u1;
   const GLfloat du = map->du;
   const GLfloat v1 = map->v1;
   const GLfloat dv = map->dv;
   GLfloat (*to)[4] = dest->data;
   GLuint i;

   for (i = 0 ; i < count ; i++)
      if (flags[i] == TNL_EVAL_COORD2) {
	 GLfloat u = (coord[i][0] - u1) * du;
	 GLfloat v = (coord[i][1] - v1) * dv;

	 _math_horner_bezier_surf(map->Points, to[i], u, v, dimension,
				  map->Uorder, map->Vorder);
      }

   dest->size = MAX2(dest->size, dimension);
   dest->flags |= dirty_flags[dimension];
}




static void copy_4f( GLfloat to[][4], const GLfloat *from, 
		     GLuint sz, GLuint stride, GLuint count )
{
   GLuint i;

   switch (sz) {
   case 1:
      for (i = 0 ; i < count ; i++, STRIDE_F(from, stride))
	 ASSIGN_4FV( to[i], from[0], 0, 0, 1 );
      return;
   case 2:
      for (i = 0 ; i < count ; i++, STRIDE_F(from, stride))
	 ASSIGN_4FV( to[i], from[0], from[1], 0, 1 );
      return;
   case 3:
      for (i = 0 ; i < count ; i++, STRIDE_F(from, stride))
	 ASSIGN_4FV( to[i], from[0], from[1], from[2], 1 );
      return;
   case 4:
      for (i = 0 ; i < count ; i++, STRIDE_F(from, stride))
	 COPY_4FV( to[i], from );
      return;
   default:
      return;
   }
}



static void clear_active_eval1( TNLcontext *tnl, GLuint attr ) 
{
   tnl->eval._ActiveMap1Attrib[attr].map = 0;
}


static void set_active_eval1( TNLcontext *tnl, GLuint attr, GLuint dim, 
			      struct _mesa_eval_map *map )
{
   if (!tnl->eval._ActiveMap1Attrib[attr].map) {
      tnl->eval._ActiveMap1Attrib[attr].map = map;
      tnl->eval._ActiveMap1Attrib[attr].dimension = dim;
   }
} 
      


/* This looks a lot like a pipeline stage, but for various reasons is
 * better handled outside the pipeline, and considered the final stage
 * of fixing up an immediate struct for execution.
 *
 * Really want to cache the results of this function in display lists,
 * at least for EvalMesh commands.
 */
void _tnl_update_eval( GLcontext *ctx )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx);
   GLuint attr;

   /* Vertex program maps have priority over conventional attribs */

   for (attr = 0; attr < VERT_ATTRIB_MAX; attr++) {
      clear_active_eval1( tnl, attr );
      clear_active_eval2( tnl, attr );
   }

   if (ctx->VertexProgram.Enabled) {
      for (attr = 0; attr < VERT_ATTRIB_MAX; attr++) {
	 if (ctx->Eval.Map1Attrib[attr]) 
	    set_active_eval1( tnl, attr, 4, &ctx->EvalMap.Map1Attrib[attr] );

	 if (ctx->Eval.Map2Attrib[attr]) 
	    set_active_eval2( tnl, attr, 4, &ctx->EvalMap.Map2Attrib[attr] );
      }
   }

   if (ctx->Eval.Map1Color4) 
      set_active_eval1( tnl, VERT_ATTRIB_COLOR0, 4, &ctx->EvalMap.Map1Color4 );
      
   if (ctx->Eval.Map2Color4) 
      set_active_eval2( tnl, VERT_ATTRIB_COLOR0, 4, &ctx->EvalMap.Map2Color4 );

   if (ctx->Eval.Map1TextureCoord4) 
      set_active_eval1( tnl, VERT_ATTRIB_TEX0, 4, &ctx->EvalMap.Map1Texture4 );
   else if (ctx->Eval.Map1TextureCoord3) 
      set_active_eval1( tnl, VERT_ATTRIB_TEX0, 3, &ctx->EvalMap.Map1Texture3 );
   else if (ctx->Eval.Map1TextureCoord2) 
      set_active_eval1( tnl, VERT_ATTRIB_TEX0, 2, &ctx->EvalMap.Map1Texture2 );
   else if (ctx->Eval.Map1TextureCoord1) 
      set_active_eval1( tnl, VERT_ATTRIB_TEX0, 1, &ctx->EvalMap.Map1Texture1 );

   if (ctx->Eval.Map2TextureCoord4) 
      set_active_eval2( tnl, VERT_ATTRIB_TEX0, 4, &ctx->EvalMap.Map2Texture4 );
   else if (ctx->Eval.Map2TextureCoord3) 
      set_active_eval2( tnl, VERT_ATTRIB_TEX0, 3, &ctx->EvalMap.Map2Texture3 );
   else if (ctx->Eval.Map2TextureCoord2) 
      set_active_eval2( tnl, VERT_ATTRIB_TEX0, 2, &ctx->EvalMap.Map2Texture2 );
   else if (ctx->Eval.Map2TextureCoord1) 
      set_active_eval2( tnl, VERT_ATTRIB_TEX0, 1, &ctx->EvalMap.Map2Texture1 );

   if (ctx->Eval.Map1Normal) 
      set_active_eval1( tnl, VERT_ATTRIB_NORMAL, 3, &ctx->EvalMap.Map1Normal );

   if (ctx->Eval.Map2Normal) 
      set_active_eval2( tnl, VERT_ATTRIB_NORMAL, 3, &ctx->EvalMap.Map2Normal );

   if (ctx->Eval.Map1Vertex4) 
      set_active_eval1( tnl, VERT_ATTRIB_POS, 4, &ctx->EvalMap.Map1Vertex4 );
   else if (ctx->Eval.Map1Vertex3) 
      set_active_eval1( tnl, VERT_ATTRIB_POS, 3, &ctx->EvalMap.Map1Vertex3 );

   if (ctx->Eval.Map2Vertex4) 
      set_active_eval2( tnl, VERT_ATTRIB_POS, 4, &ctx->EvalMap.Map2Vertex4 );
   else if (ctx->Eval.Map2Vertex3) 
      set_active_eval2( tnl, VERT_ATTRIB_POS, 3, &ctx->EvalMap.Map2Vertex3 );
}



void _tnl_eval_immediate( GLcontext *ctx )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx);
   struct tnl_vertex_arrays *tmp = &tnl->imm_inputs;
   GLuint *flags = IM->Flag + IM->CopyStart;
   GLuint orflag = IM->OrFlag;
   GLuint any_eval1 = orflag & _TNL_BIT_EVAL_C1;
   GLuint any_eval2 = orflag & _TNL_BIT_EVAL_C2;
   GLuint all_eval = andflag & (_TNL_BIT_EVAL_C1|_TNL_BIT_EVAL_C2);
   GLuint all_eval1 = andflag & _TNL_BIT_EVAL_C1;
   GLuint all_eval2 = andflag & _TNL_BIT_EVAL_C1;
   GLuint req = 0;
   GLfloat (*coord)[4] = IM->Attrib[VERT_ATTRIB_POS] + IM->CopyStart;
   GLuint attr;

   if (!store)
      store = tnl->eval.im = _tnl_alloc_immediate( ctx );

   assert (tnl->eval.EvalNewState == 0);

   /* All non-position attributes */
   for (attr = 1; attr < VERT_ATTRIB_MAX; attr++) {
      if (any_eval1 && ctx->Eval._ActiveMap1Attrib[attr].map) {
	 eval1_4f( &tmp->Attribs[attr], coord, flags, 
		   ctx->Eval._ActiveMap1Attrib[attr].dimension,
		   ctx->Eval._ActiveMap1Attrib[attr].map );
      }

      if (any_eval2 && ctx->Eval._ActiveMap2Attrib[attr].map) {
	 eval2_4f( &tmp->Attribs[attr], coord, flags,
		   ctx->Eval._ActiveMap2Attrib[attr].dimension,
		   ctx->Eval._ActiveMap2Attrib[attr].map );
      }
   }

   /* Index */
   if (req & _TNL_BIT_INDEX) {

      if (copycount)
	 copy_1f( store->Index + IM->CopyStart, tmp->Index.data, copycount );

      tmp->Index.data = store->Index + IM->CopyStart;
      tmp->Index.start = store->Index + IM->CopyStart;

      if (ctx->Eval.Map1Index && any_eval1) {
	 eval1_1f( &tmp->Index, coord, flags, &ctx->EvalMap.Map1Index );
      }

      if (ctx->Eval.Map2Index && any_eval2) {
	 eval2_1f( &tmp->Index, coord, flags, &ctx->EvalMap.Map2Index );
      }
   }


   /* Position */
   if (1) {
      /* Copy required for mixed eval/vert usage?
       */
      if (copycount) {
	 copy_4f( store->Attrib[VERT_ATTRIB_POS], 
		  im->Attrib[VERT_ATTRIB_POS], 
		  copycount );
      }

      tmp->Attribs[0].data = store->Attrib[0] + IM->CopyStart;
      tmp->Attribs[0].start = (GLfloat *) tmp->Attribs[0].data;
      tmp->Attribs[0].size = 0;

      if (any_eval1 && ctx->Eval._ActiveMap1Attrib[0].map) {
	 eval1_4f( &tmp->Attribs[0], coord, flags, 
		   ctx->Eval._ActiveMap1Attrib[0].dimension,
		   ctx->Eval._ActiveMap1Attrib[0].map );
      }

      if (any_eval2 && ctx->Eval._ActiveMap2Attrib[0].map) {
	 if (ctx->Eval.AutoNormal)
	    eval2_auto_normal( &tmp->Attribs[0], 
			       &tmp->Attribs[VERT_ATTRIB_NORMAL], coord, flags, 
			       ctx->Eval._ActiveMap1Attrib[0].dimension,
			       ctx->Eval._ActiveMap1Attrib[0].map );
	 else
	    eval2_4f( &tmp->Attribs[0], coord, flags, 
		      ctx->Eval._ActiveMap1Attrib[0].dimension,
		      ctx->Eval._ActiveMap1Attrib[0].map );
      }
   }
}
