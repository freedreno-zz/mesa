/* $Id: rastpos.c,v 1.3.2.1 2000/02/21 16:31:55 brianp Exp $ */

/*
 * Mesa 3-D graphics library
 * Version:  3.1
 * 
 * Copyright (C) 1999  Brian Paul   All Rights Reserved.
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





#ifdef PC_HEADER
#include "all.h"
#else
#ifndef XFree86Server
#include <assert.h>
#include <math.h>
#else
#include "GL/xf86glx.h"
#endif
#include "clip.h"
#include "context.h"
#include "feedback.h"
#include "light.h"
#include "macros.h"
#include "matrix.h"
#include "mmath.h"
#include "rastpos.h"
#include "shade.h"
#include "types.h"
#include "xform.h"
#endif


/*
 * Caller:  context->API.RasterPos4f
 */
void gl_RasterPos4f( GLcontext *ctx,
                     GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
   GLfloat v[4], eye[4], clip[4], ndc[3], d;

   /* KW: Added this test, which is in the spec.  We can't do this
    *     outside begin/end any more because the ctx->Current values
    *     aren't uptodate during that period. 
    */
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH( ctx, "glRasterPos" );

   if (ctx->NewState)
      gl_update_state( ctx );

   ASSIGN_4V( v, x, y, z, w );
   TRANSFORM_POINT( eye, ctx->ModelView.m, v );

   /* raster color */
   if (ctx->Light.Enabled) 
   {
      /*GLfloat *vert;*/
      GLfloat *norm, eyenorm[3];
      GLfloat *objnorm = ctx->Current.Normal;

	  /* Not needed???
      vert = (ctx->NeedEyeCoords ? eye : v);
	  */

      if (ctx->NeedEyeNormals) {
	 GLfloat *inv = ctx->ModelView.inv;
	 TRANSFORM_NORMAL( eyenorm, objnorm, inv );
	 norm = eyenorm;
      } else {
	 norm = objnorm;
      }

      gl_shade_rastpos( ctx, v, norm, 
			ctx->Current.RasterColor,
			&ctx->Current.RasterIndex );

   }
   else {
      /* use current color or index */
      if (ctx->Visual->RGBAflag) {
	 UBYTE_RGBA_TO_FLOAT_RGBA(ctx->Current.RasterColor, 
				  ctx->Current.ByteColor);
      }
      else {
	 ctx->Current.RasterIndex = ctx->Current.Index;
      }
   }

   /* compute raster distance */
   ctx->Current.RasterDistance = (GLfloat)
                      GL_SQRT( eye[0]*eye[0] + eye[1]*eye[1] + eye[2]*eye[2] );

   /* apply projection matrix:  clip = Proj * eye */
   TRANSFORM_POINT( clip, ctx->ProjectionMatrix.m, eye );

   /* clip to view volume */
   if (gl_viewclip_point( clip )==0) {
      ctx->Current.RasterPosValid = GL_FALSE;
      return;
   }

   /* clip to user clipping planes */
   if ( ctx->Transform.AnyClip &&
	gl_userclip_point(ctx, clip) == 0) 
   {
      ctx->Current.RasterPosValid = GL_FALSE;
      return;
   }

   /* ndc = clip / W */
   ASSERT( clip[3]!=0.0 );
   d = 1.0F / clip[3];
   ndc[0] = clip[0] * d;
   ndc[1] = clip[1] * d;
   ndc[2] = clip[2] * d;

   ctx->Current.RasterPos[0] = (ndc[0] * ctx->Viewport.WindowMap.m[MAT_SX] + 
				ctx->Viewport.WindowMap.m[MAT_TX]);
   ctx->Current.RasterPos[1] = (ndc[1] * ctx->Viewport.WindowMap.m[MAT_SY] + 
				ctx->Viewport.WindowMap.m[MAT_TY]);
   ctx->Current.RasterPos[2] = (ndc[2] * ctx->Viewport.WindowMap.m[MAT_SZ] + 
				ctx->Viewport.WindowMap.m[MAT_TZ]) / DEPTH_SCALE;
   ctx->Current.RasterPos[3] = clip[3];
   ctx->Current.RasterPosValid = GL_TRUE;

   /* FOG??? */

   {
      GLuint texSet;
      for (texSet=0; texSet<MAX_TEXTURE_UNITS; texSet++) {
         COPY_4FV( ctx->Current.RasterMultiTexCoord[texSet],
                  ctx->Current.Texcoord[texSet] );
      }
   }

   if (ctx->RenderMode==GL_SELECT) {
      gl_update_hitflag( ctx, ctx->Current.RasterPos[2] );
   }

}



/*
 * This is a MESA extension function.  Pretty much just like glRasterPos
 * except we don't apply the modelview or projection matrices; specify a
 * window coordinate directly.
 * Caller:  context->API.WindowPos4fMESA pointer.
 */
void gl_windowpos( GLcontext *ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH( ctx, "glWindowPosMESA" );

   /* set raster position */
   ctx->Current.RasterPos[0] = x;
   ctx->Current.RasterPos[1] = y;
   ctx->Current.RasterPos[2] = CLAMP( z, 0.0F, 1.0F );
   ctx->Current.RasterPos[3] = w;

   ctx->Current.RasterPosValid = GL_TRUE;
   ctx->Current.RasterDistance = 0.0F;

   /* raster color = current color or index */
   if (ctx->Visual->RGBAflag) {
      UBYTE_RGBA_TO_FLOAT_RGBA(ctx->Current.RasterColor, 
                               ctx->Current.ByteColor);
   }
   else {
      ctx->Current.RasterIndex = ctx->Current.Index;
   }

   /* raster texcoord = current texcoord */
   {
      GLuint texSet;
      for (texSet=0; texSet<MAX_TEXTURE_UNITS; texSet++) {
         COPY_4FV( ctx->Current.RasterMultiTexCoord[texSet],
                  ctx->Current.Texcoord[texSet] );
      }
   }

   if (ctx->RenderMode==GL_SELECT) {
      gl_update_hitflag( ctx, ctx->Current.RasterPos[2] );
   }
}
