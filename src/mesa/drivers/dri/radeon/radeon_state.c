/**
 * \file radeon_state.c
 * \brief State management.
 * 
 * \author Gareth Hughes <gareth@valinux.com>
 * \author Keith Whitwell <keith@tungstengraphics.com>
 */

/*
 * Copyright 2000, 2001 VA Linux Systems Inc., Fremont, California.
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/* $XFree86: xc/lib/GL/mesa/src/drv/radeon/radeon_state.c,v 1.5 2002/09/16 18:05:20 eich Exp $ */

#include "glheader.h"
#include "imports.h"
#include "api_arrayelt.h"
#include "mmath.h"
#include "enums.h"
#include "context.h"
#include "colormac.h"

#if _HAVE_SWTNL
#include "array_cache/acache.h"
#include "tnl/tnl.h"
#include "tnl/t_pipeline.h"
#endif
#if _HAVE_SWRAST
#include "swrast/swrast.h"
#include "swrast_setup/swrast_setup.h"
#endif

#include "radeon_context.h"
#include "radeon_ioctl.h"
#include "radeon_state.h"

#if _HAVE_FULL_GL
#include "radeon_tex.h"
#include "radeon_vtxfmt.h"
#else
#include "radeon_subset.h"
#endif




#define MODEL_PROJ 0
#define MODEL      1
#define MODEL_IT   2
#define TEXMAT_0   3
#define TEXMAT_1   4
#define TEXMAT_2   5


/***************************************************************/
/** \name Alpha blending
 */
/*@{*/

/**
 * \brief Specify the alpha test function
 *
 * \param ctx GL context.
 * \param func alpha comparison function.
 * \param ref reference alpha value.
 *
 * \sa glAlphaFunc().
 *
 * Calculates the appropriate new value of the RADEON_PP_MISC register and
 * informs the state change.
 */
static void radeonAlphaFunc( GLcontext *ctx, GLenum func, GLfloat ref )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   int pp_misc = rmesa->hw.ctx.cmd[CTX_PP_MISC];
   GLubyte refByte;

   CLAMPED_FLOAT_TO_UBYTE(refByte, ref);

   RADEON_STATECHANGE( rmesa, ctx );

   pp_misc &= ~(RADEON_ALPHA_TEST_OP_MASK | RADEON_REF_ALPHA_MASK);
   pp_misc |= (refByte & RADEON_REF_ALPHA_MASK);

   switch ( func ) {
   case GL_NEVER:
      pp_misc |= RADEON_ALPHA_TEST_FAIL;
      break;
   case GL_LESS:
      pp_misc |= RADEON_ALPHA_TEST_LESS;
      break;
   case GL_EQUAL:
      pp_misc |= RADEON_ALPHA_TEST_EQUAL;
      break;
   case GL_LEQUAL:
      pp_misc |= RADEON_ALPHA_TEST_LEQUAL;
      break;
   case GL_GREATER:
      pp_misc |= RADEON_ALPHA_TEST_GREATER;
      break;
   case GL_NOTEQUAL:
      pp_misc |= RADEON_ALPHA_TEST_NEQUAL;
      break;
   case GL_GEQUAL:
      pp_misc |= RADEON_ALPHA_TEST_GEQUAL;
      break;
   case GL_ALWAYS:
      pp_misc |= RADEON_ALPHA_TEST_PASS;
      break;
   }

   rmesa->hw.ctx.cmd[CTX_PP_MISC] = pp_misc;
}

#if _HAVE_FULL_GL
static void radeonBlendEquation( GLcontext *ctx, GLenum mode )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint b = rmesa->hw.ctx.cmd[CTX_RB3D_BLENDCNTL] & ~RADEON_COMB_FCN_MASK;
   GLboolean fallback = GL_FALSE;

   switch ( mode ) {
   case GL_FUNC_ADD:
   case GL_LOGIC_OP:
      b |= RADEON_COMB_FCN_ADD_CLAMP;
      break;

   case GL_FUNC_SUBTRACT:
      b |= RADEON_COMB_FCN_SUB_CLAMP;
      break;

   default:
      fallback = GL_TRUE;
      break;
   }

   FALLBACK( rmesa, RADEON_FALLBACK_BLEND_EQ, fallback );
   if ( !fallback ) {
      RADEON_STATECHANGE( rmesa, ctx );
      rmesa->hw.ctx.cmd[CTX_RB3D_BLENDCNTL] = b;
      if ( ctx->Color.ColorLogicOpEnabled ) {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] |=  RADEON_ROP_ENABLE;
      } else {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] &= ~RADEON_ROP_ENABLE;
      }
   }
}
#endif

/**
 * \brief Specify the blending factors.
 * 
 * \param ctx GL context.
 * \param sfactor source factor.
 * \param dfactor destination factor.
 * 
 * Calculates the appropriate new value of the RADEON_RB3D_BLENDCNTL register and informs of the state change.
 *
 * If the final state not supported by the hardward it fallbacks to software
 * rendering.
 */
static void radeonBlendFunc( GLcontext *ctx, GLenum sfactor, GLenum dfactor )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint b = rmesa->hw.ctx.cmd[CTX_RB3D_BLENDCNTL] & 
      ~(RADEON_SRC_BLEND_MASK | RADEON_DST_BLEND_MASK);
   GLboolean fallback = GL_FALSE;

   switch ( ctx->Color.BlendSrcRGB ) {
   case GL_ZERO:
      b |= RADEON_SRC_BLEND_GL_ZERO;
      break;
   case GL_ONE:
      b |= RADEON_SRC_BLEND_GL_ONE;
      break;
   case GL_DST_COLOR:
      b |= RADEON_SRC_BLEND_GL_DST_COLOR;
      break;
   case GL_ONE_MINUS_DST_COLOR:
      b |= RADEON_SRC_BLEND_GL_ONE_MINUS_DST_COLOR;
      break;
   case GL_SRC_COLOR:
      b |= RADEON_SRC_BLEND_GL_SRC_COLOR;
      break;
   case GL_ONE_MINUS_SRC_COLOR:
      b |= RADEON_SRC_BLEND_GL_ONE_MINUS_SRC_COLOR;
      break;
   case GL_SRC_ALPHA:
      b |= RADEON_SRC_BLEND_GL_SRC_ALPHA;
      break;
   case GL_ONE_MINUS_SRC_ALPHA:
      b |= RADEON_SRC_BLEND_GL_ONE_MINUS_SRC_ALPHA;
      break;
   case GL_DST_ALPHA:
      b |= RADEON_SRC_BLEND_GL_DST_ALPHA;
      break;
   case GL_ONE_MINUS_DST_ALPHA:
      b |= RADEON_SRC_BLEND_GL_ONE_MINUS_DST_ALPHA;
      break;
   case GL_SRC_ALPHA_SATURATE:
      b |= RADEON_SRC_BLEND_GL_SRC_ALPHA_SATURATE;
      break;
#if _HAVE_FULL_GL
   case GL_CONSTANT_COLOR:
   case GL_ONE_MINUS_CONSTANT_COLOR:
   case GL_CONSTANT_ALPHA:
   case GL_ONE_MINUS_CONSTANT_ALPHA:
      fallback = GL_TRUE;
      break;
#endif
   }

   switch ( ctx->Color.BlendDstRGB ) {
   case GL_ZERO:
      b |= RADEON_DST_BLEND_GL_ZERO;
      break;
   case GL_ONE:
      b |= RADEON_DST_BLEND_GL_ONE;
      break;
   case GL_SRC_COLOR:
      b |= RADEON_DST_BLEND_GL_SRC_COLOR;
      break;
   case GL_ONE_MINUS_SRC_COLOR:
      b |= RADEON_DST_BLEND_GL_ONE_MINUS_SRC_COLOR;
      break;
   case GL_SRC_ALPHA:
      b |= RADEON_DST_BLEND_GL_SRC_ALPHA;
      break;
   case GL_ONE_MINUS_SRC_ALPHA:
      b |= RADEON_DST_BLEND_GL_ONE_MINUS_SRC_ALPHA;
      break;
   case GL_DST_COLOR:
      b |= RADEON_DST_BLEND_GL_DST_COLOR;
      break;
   case GL_ONE_MINUS_DST_COLOR:
      b |= RADEON_DST_BLEND_GL_ONE_MINUS_DST_COLOR;
      break;
   case GL_DST_ALPHA:
      b |= RADEON_DST_BLEND_GL_DST_ALPHA;
      break;
   case GL_ONE_MINUS_DST_ALPHA:
      b |= RADEON_DST_BLEND_GL_ONE_MINUS_DST_ALPHA;
      break;
#if _HAVE_FULL_GL
   case GL_CONSTANT_COLOR:
   case GL_ONE_MINUS_CONSTANT_COLOR:
   case GL_CONSTANT_ALPHA:
   case GL_ONE_MINUS_CONSTANT_ALPHA:
      fallback = GL_TRUE;
      break;
#endif
   }

#if _HAVE_SWRAST
   FALLBACK( rmesa, RADEON_FALLBACK_BLEND_FUNC, fallback );
#endif

   if ( !fallback ) {
      RADEON_STATECHANGE( rmesa, ctx );
      rmesa->hw.ctx.cmd[CTX_RB3D_BLENDCNTL] = b;
   }
}


/**
 * Alias for radeonBlendFunc()
 */
static void radeonBlendFuncSeparate( GLcontext *ctx,
				     GLenum sfactorRGB, GLenum dfactorRGB,
				     GLenum sfactorA, GLenum dfactorA )
{
   radeonBlendFunc( ctx, sfactorRGB, dfactorRGB );
}

/*@}*/


/***************************************************************/
/** \name Depth testing
 */
/*@{*/

#if _HAVE_FULL_GL
/**
 * \brief Specify the function for depth comparisons.
 *
 * \param ctx GL context.
 * \param func depth comparison function.
 *
 * \sa glDepthFunc().
 *
 * Calculates the appropriate new value of the RADEON_RB3D_ZSTENCILCNTL
 * register and informs of the state change.
 */
static void radeonDepthFunc( GLcontext *ctx, GLenum func )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   RADEON_STATECHANGE( rmesa, ctx );
   rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] &= ~RADEON_Z_TEST_MASK;

   switch ( ctx->Depth.Func ) {
   case GL_NEVER:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_Z_TEST_NEVER;
      break;
   case GL_LESS:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_Z_TEST_LESS;
      break;
   case GL_EQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_Z_TEST_EQUAL;
      break;
   case GL_LEQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_Z_TEST_LEQUAL;
      break;
   case GL_GREATER:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_Z_TEST_GREATER;
      break;
   case GL_NOTEQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_Z_TEST_NEQUAL;
      break;
   case GL_GEQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_Z_TEST_GEQUAL;
      break;
   case GL_ALWAYS:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_Z_TEST_ALWAYS;
      break;
   }
}

/**
 * \brief Enable or disable depth buffering.
 *
 * \param ctx GL context
 * \param flag whether depth buferring is enabled or not.
 *
 * \sa glDepthBuffer().
 *
 * Calculates the appropriate new value of the RADEON_RB3D_ZSTENCILCNTL
 * register and informs of the state change.
 */
static void radeonDepthMask( GLcontext *ctx, GLboolean flag )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   RADEON_STATECHANGE( rmesa, ctx );

   if ( ctx->Depth.Mask ) {
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |=  RADEON_Z_WRITE_ENABLE;
   } else {
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] &= ~RADEON_Z_WRITE_ENABLE;
   }
}

/**
 * \brief Specify the clear value for the depth buffer.
 *
 * \param d depth value to be used when clering the depth buffer.
 *
 * \sa glClearDepth().
 * 
 * Calculates the new value of RADEON_RB3D_ZSTENCILCNTL register. It's not
 * necessary to inform of the sate change.
 */
static void radeonClearDepth( GLcontext *ctx, GLclampd d )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint format = (rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] &
		    RADEON_DEPTH_FORMAT_MASK);

   switch ( format ) {
   case RADEON_DEPTH_FORMAT_16BIT_INT_Z:
      rmesa->state.depth.clear = d * 0x0000ffff;
      break;
   case RADEON_DEPTH_FORMAT_24BIT_INT_Z:
      rmesa->state.depth.clear = d * 0x00ffffff;
      break;
   }
}
#endif

/*@}*/


/***************************************************************/
/** \name Scissoring
 */
/*@{*/

/**
 * \brief Intersection of two cliprects.
 *
 * \param out resulting clirect.
 * \param a fist cliprect.
 * \param b second cliprect.
 * 
 * \return GL_TRUE if the cliprects intersect, or GL_FALSE otherwise.
 */
static GLboolean intersect_rect( XF86DRIClipRectPtr out,
				 XF86DRIClipRectPtr a,
				 XF86DRIClipRectPtr b )
{
   *out = *a;
   if ( b->x1 > out->x1 ) out->x1 = b->x1;
   if ( b->y1 > out->y1 ) out->y1 = b->y1;
   if ( b->x2 < out->x2 ) out->x2 = b->x2;
   if ( b->y2 < out->y2 ) out->y2 = b->y2;
   if ( out->x1 >= out->x2 ) return GL_FALSE;
   if ( out->y1 >= out->y2 ) return GL_FALSE;
   return GL_TRUE;
}


void radeonRecalcScissorRects( radeonContextPtr rmesa )
{
   XF86DRIClipRectPtr out;
   int i;

   /* Grow cliprect store?
    */
   if (rmesa->state.scissor.numAllocedClipRects < rmesa->numClipRects) {
      while (rmesa->state.scissor.numAllocedClipRects < rmesa->numClipRects) {
	 rmesa->state.scissor.numAllocedClipRects += 1;	/* zero case */
	 rmesa->state.scissor.numAllocedClipRects *= 2;
      }

      if (rmesa->state.scissor.pClipRects)
	 FREE(rmesa->state.scissor.pClipRects);

      rmesa->state.scissor.pClipRects = 
	 MALLOC( rmesa->state.scissor.numAllocedClipRects * 
		 sizeof(XF86DRIClipRectRec) );

      if (!rmesa->state.scissor.numAllocedClipRects) {
	 rmesa->state.scissor.numAllocedClipRects = 0;
	 return;
      }
   }
   
   out = rmesa->state.scissor.pClipRects;
   rmesa->state.scissor.numClipRects = 0;

   for ( i = 0 ; i < rmesa->numClipRects ;  i++ ) {
      if ( intersect_rect( out, 
			   &rmesa->pClipRects[i], 
			   &rmesa->state.scissor.rect ) ) {
	 rmesa->state.scissor.numClipRects++;
	 out++;
      }
   }
}


void radeonUpdateScissor( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   if ( rmesa->dri.drawable ) {
      __DRIdrawablePrivate *dPriv = rmesa->dri.drawable;
      int x1,x2,y1,y2;

      if (ctx->_RotateMode) {
	  x1 = dPriv->w - ctx->Scissor.Y - ctx->Scissor.Height;
	  x2 = dPriv->w - ctx->Scissor.Y;
	  y1 = dPriv->h - ctx->Scissor.X - ctx->Scissor.Width;
	  y2 = dPriv->h - ctx->Scissor.X;
      }
      else {
	  x1 = ctx->Scissor.X;
	  x2 = ctx->Scissor.X + ctx->Scissor.Width;
	  y1 = dPriv->h - ctx->Scissor.Y - ctx->Scissor.Height;
	  y2 = dPriv->h - ctx->Scissor.Y;
      }

      rmesa->state.scissor.rect.x1 = x1 + dPriv->x;
      rmesa->state.scissor.rect.x2 = x2 + dPriv->x;
      rmesa->state.scissor.rect.y1 = y1 + dPriv->y;
      rmesa->state.scissor.rect.y2 = y2 + dPriv->y;

      radeonRecalcScissorRects( rmesa );
   }
}


static void radeonScissor( GLcontext *ctx,
			   GLint x, GLint y, GLsizei w, GLsizei h )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   if ( ctx->Scissor.Enabled ) {
      RADEON_FIREVERTICES( rmesa );	/* don't pipeline cliprect changes */
      radeonUpdateScissor( ctx );
   }

}

/*@}*/


/***************************************************************/
/** \name Culling
 */
/*@{*/

/**
 * \brief Specify whether culling should be made.
 *
 * \param ctx GL context.
 * \param unused not used.
 *
 * \note the Cull mode is already stored in the GL context.
 *
 * \sa glCullFace().
 *
 * Calculates the new values of the RADEON_SET_SE_CNTL and
 * RADEON_TCL_UCP_VERT_BLEND_CTL registers and informs of the state change if
 * they are different.
 */
static void radeonCullFace( GLcontext *ctx, GLenum unused )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint s = rmesa->hw.set.cmd[SET_SE_CNTL];
   GLuint t = rmesa->hw.tcl.cmd[TCL_UCP_VERT_BLEND_CTL];

   s |= RADEON_FFACE_SOLID | RADEON_BFACE_SOLID;
   t &= ~(RADEON_CULL_FRONT | RADEON_CULL_BACK);

   if ( ctx->Polygon.CullFlag ) {
      switch ( ctx->Polygon.CullFaceMode ) {
      case GL_FRONT:
	 s &= ~RADEON_FFACE_SOLID;
	 t |= RADEON_CULL_FRONT;
	 break;
      case GL_BACK:
	 s &= ~RADEON_BFACE_SOLID;
	 t |= RADEON_CULL_BACK;
	 break;
      case GL_FRONT_AND_BACK:
	 s &= ~(RADEON_FFACE_SOLID | RADEON_BFACE_SOLID);
	 t |= (RADEON_CULL_FRONT | RADEON_CULL_BACK);
	 break;
      }
   }

   if ( rmesa->hw.set.cmd[SET_SE_CNTL] != s ) {
      RADEON_STATECHANGE(rmesa, set );
      rmesa->hw.set.cmd[SET_SE_CNTL] = s;
   }

   if ( rmesa->hw.tcl.cmd[TCL_UCP_VERT_BLEND_CTL] != t ) {
      RADEON_STATECHANGE(rmesa, tcl );
      rmesa->hw.tcl.cmd[TCL_UCP_VERT_BLEND_CTL] = t;
   }
}

/**
 * \brief Specify orientation of front-facing polygons.
 *
 * \param ctx GL context.
 * \param mode orientation.
 * 
 * \sa glFrontFace().
 *
 * Calculates the new values of the RADEON_SET_SE_CNTL and
 * RADEON_TCL_UCP_VERT_BLEND_CTL registers and informs of the state change.
 */
static void radeonFrontFace( GLcontext *ctx, GLenum mode )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   RADEON_STATECHANGE( rmesa, set );
   rmesa->hw.set.cmd[SET_SE_CNTL] &= ~RADEON_FFACE_CULL_DIR_MASK;

   RADEON_STATECHANGE( rmesa, tcl );
   rmesa->hw.tcl.cmd[TCL_UCP_VERT_BLEND_CTL] &= ~RADEON_CULL_FRONT_IS_CCW;

   switch ( mode ) {
   case GL_CW:
      rmesa->hw.set.cmd[SET_SE_CNTL] |= RADEON_FFACE_CULL_CW;
      break;
   case GL_CCW:
      rmesa->hw.set.cmd[SET_SE_CNTL] |= RADEON_FFACE_CULL_CCW;
      rmesa->hw.tcl.cmd[TCL_UCP_VERT_BLEND_CTL] |= RADEON_CULL_FRONT_IS_CCW;
      break;
   }
}

/*@}*/


/***************************************************************/
/** \name Line state
 */
/*@{*/

/**
 * \brief Specify the line width.
 *
 * \param ctx GL context.
 * \param widthf width of rasterized lines.
 *
 * \sa glLineWidth().
 * 
 * Calculates the new values of the RADEON_LIN_SE_LINE_WIDTH and
 * RADEON_SET_SE_CNTL registers and informs of the state change.
 */
static void radeonLineWidth( GLcontext *ctx, GLfloat widthf )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   RADEON_STATECHANGE( rmesa, lin );
   RADEON_STATECHANGE( rmesa, set );

   /* Line width is stored in U6.4 format.
    */
   rmesa->hw.lin.cmd[LIN_SE_LINE_WIDTH] = (GLuint)(widthf * 16.0);
   if ( widthf > 1.0 ) {
      rmesa->hw.set.cmd[SET_SE_CNTL] |=  RADEON_WIDELINE_ENABLE;
   } else {
      rmesa->hw.set.cmd[SET_SE_CNTL] &= ~RADEON_WIDELINE_ENABLE;
   }
}

/**
 * \brief Specify the line stipple pattern.
 *
 * \param ctx GL context.
 * \param factor scale factor.
 * \param pattern bit pattern.
 *
 * \sa glLineStipple().
 *
 * Calculates the new values of the RADEON_LIN_RE_LINE_PATTERN register and
 * informs of the state change.
 */ 
static void radeonLineStipple( GLcontext *ctx, GLint factor, GLushort pattern )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   RADEON_STATECHANGE( rmesa, lin );
   rmesa->hw.lin.cmd[LIN_RE_LINE_PATTERN] = 
      ((((GLuint)factor & 0xff) << 16) | ((GLuint)pattern));
}

/*@}*/


/***************************************************************/
/** \name Masks
 */
/*@{*/

/**
 * \brief Specify the masking of frame buffer color components.
 *
 * \param ctx GL context.
 * \param r whether the red component should be written.
 * \param g whether the green component should be written.
 * \param b whether the blue component should be written.
 * \param a whether the alpha component should be written.
 *
 * \sa glColorMask().
 *
 * Calculates the new value of the RADEON_MSK_RB3D_PLANEMASK register and
 * informs of the state change if it varies.
 */
static void radeonColorMask( GLcontext *ctx,
			     GLboolean r, GLboolean g,
			     GLboolean b, GLboolean a )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint mask = radeonPackColor( rmesa->radeonScreen->cpp,
				  ctx->Color.ColorMask[RCOMP],
				  ctx->Color.ColorMask[GCOMP],
				  ctx->Color.ColorMask[BCOMP],
				  ctx->Color.ColorMask[ACOMP] );

   if ( rmesa->hw.msk.cmd[MSK_RB3D_PLANEMASK] != mask ) {
      RADEON_STATECHANGE( rmesa, msk );
      rmesa->hw.msk.cmd[MSK_RB3D_PLANEMASK] = mask;
   }
}

/*@}*/


/***************************************************************/
/** \name Polygon state
 */
/*@{*/

#if _HAVE_FULL_GL
static void radeonPolygonOffset( GLcontext *ctx,
				 GLfloat factor, GLfloat units )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLfloat constant = units * rmesa->state.depth.scale;

   RADEON_STATECHANGE( rmesa, zbs );
   rmesa->hw.zbs.cmd[ZBS_SE_ZBIAS_FACTOR]   = *(GLuint *)&factor;
   rmesa->hw.zbs.cmd[ZBS_SE_ZBIAS_CONSTANT] = *(GLuint *)&constant;
}

static void radeonPolygonStipple( GLcontext *ctx, const GLubyte *mask )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint i;
   drmRadeonStipple stipple;

   /* Must flip pattern upside down.
    */
   for ( i = 0 ; i < 32 ; i++ ) {
      rmesa->state.stipple.mask[31 - i] = ((GLuint *) mask)[i];
   }

   /* TODO: push this into cmd mechanism
    */
   RADEON_FIREVERTICES( rmesa );
   LOCK_HARDWARE( rmesa );

   /* FIXME: Use window x,y offsets into stipple RAM.
    */
   stipple.mask = rmesa->state.stipple.mask;
   drmCommandWrite( rmesa->dri.fd, DRM_RADEON_STIPPLE, 
                    &stipple, sizeof(drmRadeonStipple) );
   UNLOCK_HARDWARE( rmesa );
}
#endif

static void radeonShadeModel( GLcontext *ctx, GLenum mode )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint s = rmesa->hw.set.cmd[SET_SE_CNTL];

   s &= ~(RADEON_DIFFUSE_SHADE_MASK |
	  RADEON_ALPHA_SHADE_MASK |
	  RADEON_SPECULAR_SHADE_MASK |
	  RADEON_FOG_SHADE_MASK);

   switch ( mode ) {
   case GL_FLAT:
      s |= (RADEON_DIFFUSE_SHADE_FLAT |
	    RADEON_ALPHA_SHADE_FLAT |
	    RADEON_SPECULAR_SHADE_FLAT |
	    RADEON_FOG_SHADE_FLAT);
      break;
   case GL_SMOOTH:
      s |= (RADEON_DIFFUSE_SHADE_GOURAUD |
	    RADEON_ALPHA_SHADE_GOURAUD |
	    RADEON_SPECULAR_SHADE_GOURAUD |
	    RADEON_FOG_SHADE_GOURAUD);
      break;
   default:
      return;
   }

   if ( rmesa->hw.set.cmd[SET_SE_CNTL] != s ) {
      RADEON_STATECHANGE( rmesa, set );
      rmesa->hw.set.cmd[SET_SE_CNTL] = s;
   }
}

/*@}*/


/***************************************************************/
/** \name Stencil
 */
/*@{*/

/**
 * \brief Specify the stencil testing function.
 *
 * \param ctx GL context.
 * \param func test function.
 * \param ref reference value for the stencil test.
 * \param mask bit mask to be ANDed with both the reference and stored values
 * when the test is done.
 * 
 * \sa glStencilFunc().
 *
 * Calculates the new value of the RADEON_CTX_RB3D_ZSTENCILCNTL and
 * RADEON_MSK_RB3D_STENCILREFMASK registers and informs of the state change.
 */
static void radeonStencilFunc( GLcontext *ctx, GLenum func,
			       GLint ref, GLuint mask )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint refmask = ((ctx->Stencil.Ref[0] << RADEON_STENCIL_REF_SHIFT) |
		     (ctx->Stencil.ValueMask[0] << RADEON_STENCIL_MASK_SHIFT));

   RADEON_STATECHANGE( rmesa, ctx );
   RADEON_STATECHANGE( rmesa, msk );

   rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] &= ~RADEON_STENCIL_TEST_MASK;
   rmesa->hw.msk.cmd[MSK_RB3D_STENCILREFMASK] &= ~(RADEON_STENCIL_REF_MASK|
						   RADEON_STENCIL_VALUE_MASK);

   switch ( ctx->Stencil.Function[0] ) {
   case GL_NEVER:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_TEST_NEVER;
      break;
   case GL_LESS:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_TEST_LESS;
      break;
   case GL_EQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_TEST_EQUAL;
      break;
   case GL_LEQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_TEST_LEQUAL;
      break;
   case GL_GREATER:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_TEST_GREATER;
      break;
   case GL_NOTEQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_TEST_NEQUAL;
      break;
   case GL_GEQUAL:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_TEST_GEQUAL;
      break;
   case GL_ALWAYS:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_TEST_ALWAYS;
      break;
   }

   rmesa->hw.msk.cmd[MSK_RB3D_STENCILREFMASK] |= refmask;
}

/**
 * \brief Specify the stencil writing mask.
 *
 * \param ctx GL context.
 * \param mask bit mask to control the writing of the bits in the stencil plane.
 * 
 * \sa glStencilMask().
 *
 * Calculates the new value of the RADEON_MSK_RB3D_STENCILREFMASK register and
 * informs of the state change.
 */
static void radeonStencilMask( GLcontext *ctx, GLuint mask )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   RADEON_STATECHANGE( rmesa, msk );
   rmesa->hw.msk.cmd[MSK_RB3D_STENCILREFMASK] &= ~RADEON_STENCIL_WRITE_MASK;
   rmesa->hw.msk.cmd[MSK_RB3D_STENCILREFMASK] |=
      (ctx->Stencil.WriteMask[0] << RADEON_STENCIL_WRITEMASK_SHIFT);
}

/**
 * \brief Specify the stencil test actions.
 *
 * \param ctx GL context.
 * \param fail action to take when the stencil test fails.
 * \param zfail action to take when the stencil test passes, but the depth test
 * fails.
 * \param zpass action to take when both the stencil test and the depth test
 * fail.
 * 
 * \sa glStencilOp().
 *
 * Calculates the new value of the RADEON_CTX_RB3D_ZSTENCILCNTL register and
 * informs of the state change.
 */
static void radeonStencilOp( GLcontext *ctx, GLenum fail,
			     GLenum zfail, GLenum zpass )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   RADEON_STATECHANGE( rmesa, ctx );
   rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] &= ~(RADEON_STENCIL_FAIL_MASK |
					       RADEON_STENCIL_ZFAIL_MASK |
					       RADEON_STENCIL_ZPASS_MASK);
   switch ( ctx->Stencil.FailFunc[0] ) {
   case GL_KEEP:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_FAIL_KEEP;
      break;
   case GL_ZERO:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_FAIL_ZERO;
      break;
   case GL_REPLACE:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_FAIL_REPLACE;
      break;
   case GL_INCR:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_FAIL_INC;
      break;
   case GL_DECR:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_FAIL_DEC;
      break;
   case GL_INVERT:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_FAIL_INVERT;
      break;
   }

#if _HAVE_FULL_GL
   switch ( ctx->Stencil.ZFailFunc[0] ) {
   case GL_KEEP:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZFAIL_KEEP;
      break;
   case GL_ZERO:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZFAIL_ZERO;
      break;
   case GL_REPLACE:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZFAIL_REPLACE;
      break;
   case GL_INCR:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZFAIL_INC;
      break;
   case GL_DECR:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZFAIL_DEC;
      break;
   case GL_INVERT:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZFAIL_INVERT;
      break;
   }

   switch ( ctx->Stencil.ZPassFunc[0] ) {
   case GL_KEEP:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZPASS_KEEP;
      break;
   case GL_ZERO:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZPASS_ZERO;
      break;
   case GL_REPLACE:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZPASS_REPLACE;
      break;
   case GL_INCR:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZPASS_INC;
      break;
   case GL_DECR:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZPASS_DEC;
      break;
   case GL_INVERT:
      rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZPASS_INVERT;
      break;
   }
#else
   rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZFAIL_KEEP;
   rmesa->hw.ctx.cmd[CTX_RB3D_ZSTENCILCNTL] |= RADEON_STENCIL_ZPASS_KEEP;
#endif
}

/**
 * \brief Specify the clear value for the stencil buffer.
 *
 * \param ctx GL context.
 * \param s the index used when the stencil buffer is used. Not used.
 *
 * Sets the new value of stencil clear register with the value stored in the GL
 * context.
 */
static void radeonClearStencil( GLcontext *ctx, GLint s )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   rmesa->state.stencil.clear = 
      ((GLuint) ctx->Stencil.Clear |
       (0xff << RADEON_STENCIL_MASK_SHIFT) |
       (ctx->Stencil.WriteMask[0] << RADEON_STENCIL_WRITEMASK_SHIFT));
}

/*@}*/


/***************************************************************/
/** \name Window position and viewport transformation
 */
/*@{*/

/*
 * To correctly position primitives:
 */
#define SUBPIXEL_X 0.125
#define SUBPIXEL_Y 0.125

void radeonUpdateWindow( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   __DRIdrawablePrivate *dPriv = rmesa->dri.drawable;
   const GLfloat n = ctx->Viewport.Near;
   const GLfloat f = ctx->Viewport.Far;
   const GLfloat x = (GLfloat) ctx->Viewport.X;
   const GLfloat y = (GLfloat) ctx->Viewport.Y;
   const GLfloat width = (GLfloat) ctx->Viewport.Width;
   const GLfloat height = (GLfloat) ctx->Viewport.Height;
   GLfloat wx = (GLfloat)dPriv->x;
   GLfloat ww = (GLfloat)dPriv->w;
   GLfloat wy = (GLfloat)dPriv->y;
   GLfloat wh = (GLfloat)dPriv->h;
   GLfloat sx,sy,sz, tx,ty,tz;

   if (ctx->_RotateMode) {
      sx = height / 2.0F;
      tx = wx - sx + ww - y + SUBPIXEL_X;
      sy = - width / 2.0F;
      ty = wy + sy + wh - x + SUBPIXEL_Y;
      sz = ctx->DepthMaxF * ((f - n) / 2.0F) * rmesa->state.depth.scale;
      tz = ctx->DepthMaxF * ((f - n) / 2.0F + n) * rmesa->state.depth.scale;
   }
   else {

      sx = width / 2.0F;
      tx = wx + sx + x + SUBPIXEL_X;
      sy = -height / 2.0F;
      ty = wy + sy + wh - y + SUBPIXEL_Y;
      sz = ctx->DepthMaxF * ((f - n) / 2.0F) * rmesa->state.depth.scale;
      tz = ctx->DepthMaxF * ((f - n) / 2.0F + n) * rmesa->state.depth.scale;
   }

   RADEON_FIREVERTICES( rmesa );
   RADEON_STATECHANGE( rmesa, vpt );

   if (0) fprintf(stderr, "%s: %f %f %f %f\n", __FUNCTION__, sx, tx, sy, ty);

   rmesa->hw.vpt.cmd[VPT_SE_VPORT_XSCALE]  = *(GLuint *)&sx;
   rmesa->hw.vpt.cmd[VPT_SE_VPORT_XOFFSET] = *(GLuint *)&tx;
   rmesa->hw.vpt.cmd[VPT_SE_VPORT_YSCALE]  = *(GLuint *)&sy;
   rmesa->hw.vpt.cmd[VPT_SE_VPORT_YOFFSET] = *(GLuint *)&ty;
   rmesa->hw.vpt.cmd[VPT_SE_VPORT_ZSCALE]  = *(GLuint *)&sz;
   rmesa->hw.vpt.cmd[VPT_SE_VPORT_ZOFFSET] = *(GLuint *)&tz;

}


/**
 * \brief Set the viewport.
 *
 * \param x \e x position of the lower left corner of the viewport rectangle.
 * Not used.
 * \param y \e y position of the lower left corner of the viewport rectangle.
 * Not used.
 * \param width width of the viewport rectangle. Not used.
 * \param height height of the viewport rectangle. Not used.
 *
 * \sa glViewport().
 * 
 * Fires the vertices and updates the window.
 */
static void radeonViewport( GLcontext *ctx,
			    GLint x, GLint y, GLsizei width, GLsizei height )
{
   /* Don't pipeline viewport changes, conflict with window offset
    * setting below.  Could apply deltas to rescue pipelined viewport
    * values, or keep the originals hanging around.
    */
   RADEON_FIREVERTICES( RADEON_CONTEXT(ctx) );
   radeonUpdateWindow( ctx );
}


#if _HAVE_FULL_GL
/**
 * \brief Specify the depth range.
 *
 * \param ctx GL context.
 * \param nearval near clipping plane coordinate. Not used.
 * \param farval far clipping plane coordinate. Not used.
 *
 * \sa glDepthRange().
 * 
 * Just calls radeonUpdateWindow().
 */
static void radeonDepthRange( GLcontext *ctx, GLclampd nearval,
			      GLclampd farval )
{
   radeonUpdateWindow( ctx );
}
#endif

/*@}*/


/***************************************************************/
/** \name Miscellaneous
 */
/*@{*/

/**
 * \brief Specify the clear value of the color buffers.
 *
 * \param ctx GL context.
 * \param color red, green, blue and alpha values used when clering the color buffers.
 *
 * \sa glClearColor().
 *
 * Stores the clear color value in the driver state.
 */
static void radeonClearColor( GLcontext *ctx, const GLfloat color[4] )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLubyte c[4];
   CLAMPED_FLOAT_TO_UBYTE(c[0], color[0]);
   CLAMPED_FLOAT_TO_UBYTE(c[1], color[1]);
   CLAMPED_FLOAT_TO_UBYTE(c[2], color[2]);
   CLAMPED_FLOAT_TO_UBYTE(c[3], color[3]);
   rmesa->state.color.clear = radeonPackColor( rmesa->radeonScreen->cpp,
					       c[0], c[1], c[2], c[3] );
}


static GLuint radeon_rop_tab[] = {
   RADEON_ROP_CLEAR,
   RADEON_ROP_AND,
   RADEON_ROP_AND_REVERSE,
   RADEON_ROP_COPY,
   RADEON_ROP_AND_INVERTED,
   RADEON_ROP_NOOP,
   RADEON_ROP_XOR,
   RADEON_ROP_OR,
   RADEON_ROP_NOR,
   RADEON_ROP_EQUIV,
   RADEON_ROP_INVERT,
   RADEON_ROP_OR_REVERSE,
   RADEON_ROP_COPY_INVERTED,
   RADEON_ROP_OR_INVERTED,
   RADEON_ROP_NAND,
   RADEON_ROP_SET,
};

/**
 * \brief Specify a logical pixel operation for color rendering.
 *
 * \param ctx GL context.
 * \param opcode logical operation.
 *
 * \sa glLogicOp().
 *
 * Calculates the new value of RADEON_MSK_RB3D_ROPCNTL and informs of the state
 * change.
 */
static void radeonLogicOpCode( GLcontext *ctx, GLenum opcode )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint rop = (GLuint)opcode - GL_CLEAR;

   ASSERT( rop < 16 );

   RADEON_STATECHANGE( rmesa, msk );
   rmesa->hw.msk.cmd[MSK_RB3D_ROPCNTL] = radeon_rop_tab[rop];
}

void radeonSetCliprects( radeonContextPtr rmesa, GLenum mode )
{
   __DRIdrawablePrivate *dPriv = rmesa->dri.drawable;
   
   fprintf(stderr, "%s\n", __FUNCTION__);
   
   switch ( mode ) {
   case GL_FRONT_LEFT:
      rmesa->numClipRects = dPriv->numClipRects;
      rmesa->pClipRects = (XF86DRIClipRectPtr)dPriv->pClipRects;
      break;
   case GL_BACK_LEFT:
      /* Can't ignore 2d windows if we are page flipping.
       */
      if ( dPriv->numBackClipRects == 0 || rmesa->doPageFlip ) {
	 rmesa->numClipRects = dPriv->numClipRects;
	 rmesa->pClipRects = (XF86DRIClipRectPtr)dPriv->pClipRects;
      }
      else {
	 rmesa->numClipRects = dPriv->numBackClipRects;
	 rmesa->pClipRects = (XF86DRIClipRectPtr)dPriv->pBackClipRects;
      }
      break;
   case GL_NONE:
      rmesa->numClipRects = 0;
      rmesa->pClipRects = 0;
      break;
   default:
      fprintf(stderr, "bad mode in radeonSetCliprects\n");
      return;
   }

   fprintf(stderr, "%s: %d cliprects\n", __FUNCTION__, rmesa->numClipRects);

   if (rmesa->state.scissor.enabled)
      radeonRecalcScissorRects( rmesa );
}

/**
 * \brief Specify which color buffers to be drawn into.
 *
 * \param ctx GL context.
 * \param mode which color buffers to be drawn into.
 *
 * \sa glDrawBuffer().
 *
 * Fires the vertices and sets the cliprects via radeonSetCliprects() according with the mode.
 *
 * Updates the value of radeon_colorbuffer_state::drawOffset and
 * radeon_colorbuffer_state::drawPitch to point to the back or front color
 * buffer.
 */
static void radeonDrawBuffer( GLcontext *ctx, GLenum mode )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   if (RADEON_DEBUG & DEBUG_DRI)
      fprintf(stderr, "%s %s\n", __FUNCTION__,
	      _mesa_lookup_enum_by_nr( mode ));

   RADEON_FIREVERTICES(rmesa);	/* don't pipeline cliprect changes */

#if _HAVE_SWRAST
   FALLBACK( rmesa, RADEON_FALLBACK_DRAW_BUFFER, GL_FALSE );
#endif

   /*
    * _DrawDestMask is easier to cope with than <mode>.
    */
   switch ( ctx->Color._DrawDestMask ) {
   case FRONT_LEFT_BIT:
      radeonSetCliprects( rmesa, GL_FRONT_LEFT );
      break;
   case BACK_LEFT_BIT:
      radeonSetCliprects( rmesa, GL_BACK_LEFT );
      break;
   case GL_NONE:
      radeonSetCliprects( rmesa, GL_NONE );
      break;
#if _HAVE_FULL_GL
   default:
      /* GL_FRONT_AND_BACK or stereo left&right, etc */
      FALLBACK( rmesa, RADEON_FALLBACK_DRAW_BUFFER, GL_TRUE );
      return;
#endif
   }

   {
      int use_back;

      use_back = (rmesa->glCtx->Color._DrawDestMask == BACK_LEFT_BIT);
      use_back ^= (rmesa->sarea->pfCurrentPage == 1);

      if ( ctx->Visual.doubleBufferMode && use_back ) {
	 rmesa->state.color.drawOffset = rmesa->radeonScreen->backOffset;
	 rmesa->state.color.drawPitch  = rmesa->radeonScreen->backPitch;
      } else {
	 rmesa->state.color.drawOffset = rmesa->radeonScreen->frontOffset;
	 rmesa->state.color.drawPitch  = rmesa->radeonScreen->frontPitch;
      }

      rmesa->state.pixel.readOffset = rmesa->state.color.drawOffset;
      rmesa->state.pixel.readPitch  = rmesa->state.color.drawPitch;
   }

#if _HAVE_SWRAST
   /* We want to update the s/w rast state too so that r200SetBuffer()
    * gets called.
    */
   _swrast_DrawBuffer(ctx, mode);
#endif

   RADEON_STATECHANGE( rmesa, ctx );
   rmesa->hw.ctx.cmd[CTX_RB3D_COLOROFFSET] = (rmesa->state.color.drawOffset &
					    RADEON_COLOROFFSET_MASK);
   rmesa->hw.ctx.cmd[CTX_RB3D_COLORPITCH] = rmesa->state.color.drawPitch;
}

static void radeonReadBuffer( GLcontext *ctx, GLenum mode )
{
}

/*@}*/


/***************************************************************/
/** \name State enable/disable
 */
/*@{*/

/**
 * \brief Enable or disable a GL capability.
 *
 * \param cap GL capability.
 * \param state whether to enable or disable the capability.
 *
 * \sa glEnable() and glDisable().
 * 
 * Changes the apropriate registers and state variables, informing of the state
 * change if necessary.
 */
static void radeonEnable( GLcontext *ctx, GLenum cap, GLboolean state )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   if ( RADEON_DEBUG & DEBUG_STATE )
      fprintf( stderr, "%s( %s = %s )\n", __FUNCTION__,
	       _mesa_lookup_enum_by_nr( cap ),
	       state ? "GL_TRUE" : "GL_FALSE" );

   switch ( cap ) {
      /* Fast track this one...
       */
   case GL_TEXTURE_1D:
   case GL_TEXTURE_2D:
   case GL_TEXTURE_3D:
      RADEON_FIREVERTICES( rmesa );
      break;

   case GL_ALPHA_TEST:
      RADEON_STATECHANGE( rmesa, ctx );
      if (state) {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] |= RADEON_ALPHA_TEST_ENABLE;
      } else {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] &= ~RADEON_ALPHA_TEST_ENABLE;
      }
      break;

   case GL_BLEND:
      RADEON_STATECHANGE( rmesa, ctx );
      if (state) {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] |=  RADEON_ALPHA_BLEND_ENABLE;
      } else {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] &= ~RADEON_ALPHA_BLEND_ENABLE;
      }
      if ( ctx->Color.ColorLogicOpEnabled ) {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] |=  RADEON_ROP_ENABLE;
      } else {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] &= ~RADEON_ROP_ENABLE;
      }
      break;

#if _HAVE_USERCLIP
   case GL_CLIP_PLANE0:
   case GL_CLIP_PLANE1:
   case GL_CLIP_PLANE2:
   case GL_CLIP_PLANE3:
   case GL_CLIP_PLANE4:
   case GL_CLIP_PLANE5: {
      GLuint p = cap-GL_CLIP_PLANE0;
      RADEON_STATECHANGE( rmesa, tcl );
      if (state) {
	 rmesa->hw.tcl.cmd[TCL_UCP_VERT_BLEND_CTL] |= (RADEON_UCP_ENABLE_0<<p);
	 radeonClipPlane( ctx, cap, NULL );
      }
      else {
	 rmesa->hw.tcl.cmd[TCL_UCP_VERT_BLEND_CTL] &= ~(RADEON_UCP_ENABLE_0<<p);
      }
      break;
   }
#endif

   case GL_CULL_FACE:
      radeonCullFace( ctx, 0 );
      break;

#if _HAVE_FULL_GL
   case GL_DEPTH_TEST:
      RADEON_STATECHANGE(rmesa, ctx );
      if ( state ) {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] |=  RADEON_Z_ENABLE;
      } else {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] &= ~RADEON_Z_ENABLE;
      }
      break;

   case GL_DITHER:
      RADEON_STATECHANGE(rmesa, ctx );
      if ( state ) {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] |=  RADEON_DITHER_ENABLE;
      } else {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] &= ~RADEON_DITHER_ENABLE;
      }
      break;
#endif

   case GL_LINE_SMOOTH:
      RADEON_STATECHANGE( rmesa, ctx );
      if ( state ) {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] |=  RADEON_ANTI_ALIAS_LINE;
      } else {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] &= ~RADEON_ANTI_ALIAS_LINE;
      }
      break;

   case GL_LINE_STIPPLE:
      RADEON_STATECHANGE( rmesa, ctx );
      if ( state ) {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] |=  RADEON_PATTERN_ENABLE;
      } else {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] &= ~RADEON_PATTERN_ENABLE;
      }
      break;

   case GL_COLOR_LOGIC_OP:
      RADEON_STATECHANGE( rmesa, ctx );
      if ( state ) {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] |=  RADEON_ROP_ENABLE;
      } else {
	 rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] &= ~RADEON_ROP_ENABLE;
      }
      break;

#if _HAVE_LIGHTING      
   case GL_NORMALIZE:
      RADEON_STATECHANGE( rmesa, tcl );
      if ( state ) {
	 rmesa->hw.tcl.cmd[TCL_LIGHT_MODEL_CTL] |=  RADEON_NORMALIZE_NORMALS;
      } else {
	 rmesa->hw.tcl.cmd[TCL_LIGHT_MODEL_CTL] &= ~RADEON_NORMALIZE_NORMALS;
      }
      break;
#endif

#if _HAVE_FULL_GL
   case GL_POLYGON_OFFSET_POINT:
      if (rmesa->dri.drmMinor == 1) {
	 radeonChooseRenderState( ctx );
      } 
      else {
	 RADEON_STATECHANGE( rmesa, set );
	 if ( state ) {
	    rmesa->hw.set.cmd[SET_SE_CNTL] |=  RADEON_ZBIAS_ENABLE_POINT;
	 } else {
	    rmesa->hw.set.cmd[SET_SE_CNTL] &= ~RADEON_ZBIAS_ENABLE_POINT;
	 }
      }
      break;

   case GL_POLYGON_OFFSET_LINE:
      if (rmesa->dri.drmMinor == 1) {
	 radeonChooseRenderState( ctx );
      } 
      else {
	 RADEON_STATECHANGE( rmesa, set );
	 if ( state ) {
	    rmesa->hw.set.cmd[SET_SE_CNTL] |=  RADEON_ZBIAS_ENABLE_LINE;
	 } else {
	    rmesa->hw.set.cmd[SET_SE_CNTL] &= ~RADEON_ZBIAS_ENABLE_LINE;
	 }
      }
      break;

   case GL_POLYGON_OFFSET_FILL:
      if (rmesa->dri.drmMinor == 1) {
	 radeonChooseRenderState( ctx );
      } 
      else {
	 RADEON_STATECHANGE( rmesa, set );
	 if ( state ) {
	    rmesa->hw.set.cmd[SET_SE_CNTL] |=  RADEON_ZBIAS_ENABLE_TRI;
	 } else {
	    rmesa->hw.set.cmd[SET_SE_CNTL] &= ~RADEON_ZBIAS_ENABLE_TRI;
	 }
      }
      break;
#endif

   case GL_POLYGON_SMOOTH:
      RADEON_STATECHANGE( rmesa, ctx );
      if ( state ) {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] |=  RADEON_ANTI_ALIAS_POLY;
      } else {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] &= ~RADEON_ANTI_ALIAS_POLY;
      }
      break;

#if _HAVE_FULL_GL
   case GL_POLYGON_STIPPLE:
      RADEON_STATECHANGE(rmesa, ctx );
      if ( state ) {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] |=  RADEON_STIPPLE_ENABLE;
      } else {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] &= ~RADEON_STIPPLE_ENABLE;
      }
      break;

   case GL_RESCALE_NORMAL_EXT: {
      GLboolean tmp = ctx->_NeedEyeCoords ? state : !state;
      RADEON_STATECHANGE( rmesa, tcl );
      if ( tmp ) {
	 rmesa->hw.tcl.cmd[TCL_LIGHT_MODEL_CTL] |=  RADEON_RESCALE_NORMALS;
      } else {
	 rmesa->hw.tcl.cmd[TCL_LIGHT_MODEL_CTL] &= ~RADEON_RESCALE_NORMALS;
      }
      break;
   }
#endif

   case GL_SCISSOR_TEST:
      RADEON_FIREVERTICES( rmesa );
      rmesa->state.scissor.enabled = state;
      radeonUpdateScissor( ctx );
      break;

   case GL_STENCIL_TEST:
      if ( rmesa->state.stencil.hwBuffer ) {
	 RADEON_STATECHANGE( rmesa, ctx );
	 if ( state ) {
	    rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] |=  RADEON_STENCIL_ENABLE;
	 } else {
	    rmesa->hw.ctx.cmd[CTX_RB3D_CNTL] &= ~RADEON_STENCIL_ENABLE;
	 }
      }
#if _HAVE_SWRAST 
      else {
	 FALLBACK( rmesa, RADEON_FALLBACK_STENCIL, state );
      }
#endif
      break;

#if _HAVE_TEXGEN
   case GL_TEXTURE_GEN_Q:
   case GL_TEXTURE_GEN_R:
   case GL_TEXTURE_GEN_S:
   case GL_TEXTURE_GEN_T:
      /* Picked up in radeonUpdateTextureState.
       */
      rmesa->recheck_texgen[ctx->Texture.CurrentUnit] = GL_TRUE; 
      break;
#endif

#if _HAVE_LIGHTING
   case GL_FOG:
      RADEON_STATECHANGE(rmesa, ctx );
      if ( state ) {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] |= RADEON_FOG_ENABLE;
	 ctx->Driver.Fogfv( ctx, GL_FOG_MODE, 0 );
      } else {
	 rmesa->hw.ctx.cmd[CTX_PP_CNTL] &= ~RADEON_FOG_ENABLE;
	 RADEON_STATECHANGE(rmesa, tcl);
	 rmesa->hw.tcl.cmd[TCL_UCP_VERT_BLEND_CTL] &= ~RADEON_TCL_FOG_MASK;
      }
      radeonUpdateSpecular( ctx ); /* for PK_SPEC */
      if (rmesa->TclFallback) 
	 radeonChooseVertexState( ctx );
      break;

   case GL_LIGHT0:
   case GL_LIGHT1:
   case GL_LIGHT2:
   case GL_LIGHT3:
   case GL_LIGHT4:
   case GL_LIGHT5:
   case GL_LIGHT6:
   case GL_LIGHT7: {
      GLuint p, flag;
      RADEON_STATECHANGE(rmesa, tcl);
      p = cap - GL_LIGHT0;
      if (p&1) 
	 flag = (RADEON_LIGHT_1_ENABLE |
		 RADEON_LIGHT_1_ENABLE_AMBIENT | 
		 RADEON_LIGHT_1_ENABLE_SPECULAR);
      else
	 flag = (RADEON_LIGHT_0_ENABLE |
		 RADEON_LIGHT_0_ENABLE_AMBIENT | 
		 RADEON_LIGHT_0_ENABLE_SPECULAR);

      if (state)
	 rmesa->hw.tcl.cmd[p/2 + TCL_PER_LIGHT_CTL_0] |= flag;
      else
	 rmesa->hw.tcl.cmd[p/2 + TCL_PER_LIGHT_CTL_0] &= ~flag;

      /* 
       */
      update_light_colors( ctx, p );
      break;
   }

   case GL_LIGHTING:
      RADEON_STATECHANGE(rmesa, tcl);
      radeonUpdateSpecular(ctx);
      check_twoside_fallback( ctx );
      break;

   case GL_COLOR_MATERIAL:
      radeonColorMaterial( ctx, 0, 0 );
      if (!state) 
	 radeonUpdateMaterial( ctx );
      break;

   case GL_COLOR_SUM_EXT:
      radeonUpdateSpecular ( ctx );
      break;

#endif /* _HAVE_LIGHTING */

   default:
      return;
   }
}

/*@}*/


/***************************************************************/
/** \name Deferred state management - matrices, textures, other?
 */
/*@{*/

/**
 * \brief Upload a transformation matrix.
 *
 * \param rmesa Radeon driver context.
 * \param src source transformation matrix.
 * \param idx index of the transformation matrix to upload.
 *
 * Transposes and updates the matrix in the driver context and informs of the
 * state change.
 */
void radeonUploadMatrix( radeonContextPtr rmesa, GLfloat *src, int idx )
{
   float *dest = ((float *)RADEON_DB_STATE( mat[idx] ))+MAT_ELT_0;
   int i;


   for (i = 0 ; i < 4 ; i++) {
      *dest++ = src[i];
      *dest++ = src[i+4];
      *dest++ = src[i+8];
      *dest++ = src[i+12];
   }

   RADEON_DB_STATECHANGE( rmesa, &rmesa->hw.mat[idx] );
}

/**
 * \brief Upload a transposed transformation matrix.
 *
 * Same as radeonUploadMatrix() but without the need to transpose.
 */
void radeonUploadMatrixTranspose( radeonContextPtr rmesa, GLfloat *src, 
				  int idx )
{
   float *dest = ((float *)RADEON_DB_STATE( mat[idx] ))+MAT_ELT_0;
   memcpy(dest, src, 16*sizeof(float));
   RADEON_DB_STATECHANGE( rmesa, &rmesa->hw.mat[idx] );
}


#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  product[(col<<2)+row]


static void matmul4( GLfloat *product, const GLfloat *a, const GLfloat *b )
{
   GLint i;
   for (i = 0; i < 4; i++) {
      const GLfloat ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
      P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
      P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
      P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
      P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
   }
}

static const GLfloat rot[16] = {
   0, 1, 0, 0,
   -1, 0, 0, 0,
   0, 0, 1, 0,
   0, 0, 0, 1 
};


void radeonValidateState( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint new_state = rmesa->NewGLState;

   if (new_state & _NEW_TEXTURE) {
      radeonUpdateTextureState( ctx );
      new_state |= rmesa->NewGLState; /* may add TEXTURE_MATRIX */
   }

   /* Need an event driven matrix update?
    */
   if (new_state & (_NEW_MODELVIEW|_NEW_PROJECTION)) {
      if (ctx->_RotateMode) {
	 GLfloat tmp[16];
	 matmul4( tmp, rot, ctx->_ModelProjectMatrix.m );
	 radeonUploadMatrix( rmesa, tmp, MODEL_PROJ );
      }
      else {
	 radeonUploadMatrix( rmesa, ctx->_ModelProjectMatrix.m, MODEL_PROJ );
      }
   }

   /* Need these for lighting (shouldn't upload otherwise)
    */
   if (new_state & (_NEW_MODELVIEW)) {
      radeonUploadMatrix( rmesa, ctx->ModelviewMatrixStack.Top->m, MODEL );
      radeonUploadMatrixTranspose( rmesa, ctx->ModelviewMatrixStack.Top->inv, 
				   MODEL_IT );
   }

   /* Does this need to be triggered on eg. modelview for
    * texgen-derived objplane/eyeplane matrices?
    */
#if _HAVE_TEXGEN
   if (new_state & _NEW_TEXTURE_MATRIX) {
      radeonUpdateTextureMatrix( ctx );
   }      
#endif

#if _HAVE_LIGHTING
   if (new_state & (_NEW_LIGHT|_NEW_MODELVIEW|_MESA_NEW_NEED_EYE_COORDS)) {
      radeonUpdateLighting( ctx );
   }
#endif

   /* emit all active clip planes if projection matrix changes.
    */
#if _HAVE_USERCLIP
   if (new_state & (_NEW_PROJECTION)) {
      if (ctx->Transform.ClipPlanesEnabled) 
	 radeonUpdateClipPlanes( ctx );
   }
#endif


   rmesa->NewGLState = 0;
}


static void radeonInvalidateState( GLcontext *ctx, GLuint new_state )
{
#if _HAVE_SWRAST
   _swrast_InvalidateState( ctx, new_state );
   _swsetup_InvalidateState( ctx, new_state );
#endif
#if _HAVE_SWTNL
   _ac_InvalidateState( ctx, new_state );
   _tnl_InvalidateState( ctx, new_state );
   _ae_invalidate_state( ctx, new_state );
#endif
   RADEON_CONTEXT(ctx)->NewGLState |= new_state;
   radeonVtxfmtInvalidate( ctx );
}



/**
 * \brief Initialize the driver's state functions.
 *
 * \param ctx GL context.
 * 
 * Called by radeonCreateContext() to fill the driver's state functions 
 * with those living in this file.
 */
void radeonInitStateFuncs( GLcontext *ctx )
{
   ctx->Driver.UpdateState		= radeonInvalidateState;

   ctx->Driver.DrawBuffer		= radeonDrawBuffer;
   ctx->Driver.ReadBuffer		= radeonReadBuffer;

   ctx->Driver.AlphaFunc		= radeonAlphaFunc;
   ctx->Driver.BlendFunc		= radeonBlendFunc;
   ctx->Driver.BlendFuncSeparate	= radeonBlendFuncSeparate;
   ctx->Driver.ClearColor		= radeonClearColor;
   ctx->Driver.ClearIndex		= NULL;
   ctx->Driver.ClearStencil		= radeonClearStencil;
   ctx->Driver.ColorMask		= radeonColorMask;
   ctx->Driver.CullFace			= radeonCullFace;

#if _HAVE_FULL_GL
   ctx->Driver.BlendEquation		= radeonBlendEquation;
   ctx->Driver.ClearDepth		= radeonClearDepth;
   ctx->Driver.DepthFunc		= radeonDepthFunc;
   ctx->Driver.DepthMask		= radeonDepthMask;
   ctx->Driver.DepthRange		= radeonDepthRange;
   if (RADEON_CONTEXT(ctx)->dri.drmMinor > 1)
      ctx->Driver.PolygonOffset		= radeonPolygonOffset;

   ctx->Driver.PolygonStipple		= radeonPolygonStipple;
#endif

   ctx->Driver.Enable			= radeonEnable;
   ctx->Driver.FrontFace		= radeonFrontFace;
   ctx->Driver.Hint			= NULL;
   ctx->Driver.IndexMask		= NULL;
   ctx->Driver.LineStipple              = radeonLineStipple;
   ctx->Driver.LineWidth                = radeonLineWidth;
   ctx->Driver.LogicOpcode		= radeonLogicOpCode;
   ctx->Driver.Scissor			= radeonScissor;
   ctx->Driver.ShadeModel		= radeonShadeModel;
   ctx->Driver.StencilFunc		= radeonStencilFunc;
   ctx->Driver.StencilMask		= radeonStencilMask;
   ctx->Driver.StencilOp		= radeonStencilOp;
   ctx->Driver.Viewport			= radeonViewport; 
}

/*@}*/
