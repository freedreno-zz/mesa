/* $XFree86: xc/lib/GL/mesa/src/drv/radeon/radeon_texstate.c,v 1.3 2002/09/16 18:05:21 eich Exp $ */
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
 *   Kevin E. Martin <martin@valinux.com>
 *   Gareth Hughes <gareth@valinux.com>
 *
 */

#include "glheader.h"
#include "imports.h"
#include "colormac.h"
#include "context.h"
#include "enums.h"
#include "macros.h"
#include "mmath.h"
#include "texformat.h"

#include "radeon_context.h"
#include "radeon_state.h"
#include "radeon_ioctl.h"
#include "radeon_tex.h"
#include "radeon_tcl.h"

/* GL_EXT_texture_env_combine support
 */

/* The color tables have combine functions for GL_SRC_COLOR,
 * GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA and GL_ONE_MINUS_SRC_ALPHA.
 */
static GLuint radeon_texture_color[][RADEON_MAX_TEXTURE_UNITS] =
{
   {
      RADEON_COLOR_ARG_A_T0_COLOR,
      RADEON_COLOR_ARG_A_T1_COLOR,
      RADEON_COLOR_ARG_A_T2_COLOR
   },
   {
      RADEON_COLOR_ARG_A_T0_COLOR | RADEON_COMP_ARG_A,
      RADEON_COLOR_ARG_A_T1_COLOR | RADEON_COMP_ARG_A,
      RADEON_COLOR_ARG_A_T2_COLOR | RADEON_COMP_ARG_A
   },
   {
      RADEON_COLOR_ARG_A_T0_ALPHA,
      RADEON_COLOR_ARG_A_T1_ALPHA,
      RADEON_COLOR_ARG_A_T2_ALPHA
   },
   {
      RADEON_COLOR_ARG_A_T0_ALPHA | RADEON_COMP_ARG_A,
      RADEON_COLOR_ARG_A_T1_ALPHA | RADEON_COMP_ARG_A,
      RADEON_COLOR_ARG_A_T2_ALPHA | RADEON_COMP_ARG_A
   },
};

static GLuint radeon_tfactor_color[] =
{
   RADEON_COLOR_ARG_A_TFACTOR_COLOR,
   RADEON_COLOR_ARG_A_TFACTOR_COLOR | RADEON_COMP_ARG_A,
   RADEON_COLOR_ARG_A_TFACTOR_ALPHA,
   RADEON_COLOR_ARG_A_TFACTOR_ALPHA | RADEON_COMP_ARG_A
};

static GLuint radeon_primary_color[] =
{
   RADEON_COLOR_ARG_A_DIFFUSE_COLOR,
   RADEON_COLOR_ARG_A_DIFFUSE_COLOR | RADEON_COMP_ARG_A,
   RADEON_COLOR_ARG_A_DIFFUSE_ALPHA,
   RADEON_COLOR_ARG_A_DIFFUSE_ALPHA | RADEON_COMP_ARG_A
};

static GLuint radeon_previous_color[] =
{
   RADEON_COLOR_ARG_A_CURRENT_COLOR,
   RADEON_COLOR_ARG_A_CURRENT_COLOR | RADEON_COMP_ARG_A,
   RADEON_COLOR_ARG_A_CURRENT_ALPHA,
   RADEON_COLOR_ARG_A_CURRENT_ALPHA | RADEON_COMP_ARG_A
};

/* The alpha tables only have GL_SRC_ALPHA and GL_ONE_MINUS_SRC_ALPHA.
 */
static GLuint radeon_texture_alpha[][RADEON_MAX_TEXTURE_UNITS] =
{
   {
      RADEON_ALPHA_ARG_A_T0_ALPHA,
      RADEON_ALPHA_ARG_A_T1_ALPHA,
      RADEON_ALPHA_ARG_A_T2_ALPHA
   },
   {
      RADEON_ALPHA_ARG_A_T0_ALPHA | RADEON_COMP_ARG_A,
      RADEON_ALPHA_ARG_A_T1_ALPHA | RADEON_COMP_ARG_A,
      RADEON_ALPHA_ARG_A_T2_ALPHA | RADEON_COMP_ARG_A
   },
};

static GLuint radeon_tfactor_alpha[] =
{
   RADEON_ALPHA_ARG_A_TFACTOR_ALPHA,
   RADEON_ALPHA_ARG_A_TFACTOR_ALPHA | RADEON_COMP_ARG_A
};

static GLuint radeon_primary_alpha[] =
{
   RADEON_ALPHA_ARG_A_DIFFUSE_ALPHA,
   RADEON_ALPHA_ARG_A_DIFFUSE_ALPHA | RADEON_COMP_ARG_A
};

static GLuint radeon_previous_alpha[] =
{
   RADEON_ALPHA_ARG_A_CURRENT_ALPHA,
   RADEON_ALPHA_ARG_A_CURRENT_ALPHA | RADEON_COMP_ARG_A
};


/* Extract the arg from slot A, shift it into the correct argument slot
 * and set the corresponding complement bit.
 */
#define RADEON_COLOR_ARG( n, arg )					\
do {									\
   color_combine |=							\
      ((color_arg[n] & RADEON_COLOR_ARG_MASK)				\
       << RADEON_COLOR_ARG_##arg##_SHIFT);				\
   color_combine |=							\
      ((color_arg[n] >> RADEON_COMP_ARG_SHIFT)				\
       << RADEON_COMP_ARG_##arg##_SHIFT);				\
} while (0)

#define RADEON_ALPHA_ARG( n, arg )					\
do {									\
   alpha_combine |=							\
      ((alpha_arg[n] & RADEON_ALPHA_ARG_MASK)				\
       << RADEON_ALPHA_ARG_##arg##_SHIFT);				\
   alpha_combine |=							\
      ((alpha_arg[n] >> RADEON_COMP_ARG_SHIFT)				\
       << RADEON_COMP_ARG_##arg##_SHIFT);				\
} while (0)


GLboolean radeonUpdateTextureEnvCombine( GLcontext *ctx, int unit )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   const struct gl_texture_unit *texUnit = &ctx->Texture.Unit[unit];
   GLuint color_arg[3], alpha_arg[3];
   GLuint i, numColorArgs = 0, numAlphaArgs = 0;
   GLuint color_combine, alpha_combine;

   /* Don't cache these results.
    */
   rmesa->state.texture.unit[unit].format = 0;
   rmesa->state.texture.unit[unit].envMode = 0;

   /* Step 0:
    * Calculate how many arguments we need to process.
    */
   switch ( texUnit->CombineModeRGB ) {
   case GL_REPLACE:
      numColorArgs = 1;
      break;
   case GL_MODULATE:
   case GL_ADD:
   case GL_ADD_SIGNED:
   case GL_SUBTRACT:
   case GL_DOT3_RGB:
   case GL_DOT3_RGBA:
   case GL_DOT3_RGB_EXT:
   case GL_DOT3_RGBA_EXT:
      numColorArgs = 2;
      break;
   case GL_INTERPOLATE:
      numColorArgs = 3;
      break;
   default:
      return GL_FALSE;
   }

   switch ( texUnit->CombineModeA ) {
   case GL_REPLACE:
      numAlphaArgs = 1;
      break;
   case GL_MODULATE:
   case GL_ADD:
   case GL_ADD_SIGNED:
   case GL_SUBTRACT:
      numAlphaArgs = 2;
      break;
   case GL_INTERPOLATE:
      numAlphaArgs = 3;
      break;
   default:
      return GL_FALSE;
   }

   /* Step 1:
    * Extract the color and alpha combine function arguments.
    */
   for ( i = 0 ; i < numColorArgs ; i++ ) {
      const GLuint op = texUnit->CombineOperandRGB[i] - GL_SRC_COLOR;
      ASSERT(op >= 0);
      ASSERT(op <= 3);
      switch ( texUnit->CombineSourceRGB[i] ) {
      case GL_TEXTURE:
	 color_arg[i] = radeon_texture_color[op][unit];
	 break;
      case GL_CONSTANT:
	 color_arg[i] = radeon_tfactor_color[op];
	 break;
      case GL_PRIMARY_COLOR:
	 color_arg[i] = radeon_primary_color[op];
	 break;
      case GL_PREVIOUS:
	 color_arg[i] = radeon_previous_color[op];
	 break;
      default:
	 return GL_FALSE;
      }
   }

   for ( i = 0 ; i < numAlphaArgs ; i++ ) {
      const GLuint op = texUnit->CombineOperandA[i] - GL_SRC_ALPHA;
      ASSERT(op >= 0);
      ASSERT(op <= 1);
      switch ( texUnit->CombineSourceA[i] ) {
      case GL_TEXTURE:
	 alpha_arg[i] = radeon_texture_alpha[op][unit];
	 break;
      case GL_CONSTANT:
	 alpha_arg[i] = radeon_tfactor_alpha[op];
	 break;
      case GL_PRIMARY_COLOR:
	 alpha_arg[i] = radeon_primary_alpha[op];
	 break;
      case GL_PREVIOUS:
	 alpha_arg[i] = radeon_previous_alpha[op];
	 break;
      default:
	 return GL_FALSE;
      }
   }

   /* Step 2:
    * Build up the color and alpha combine functions.
    */
   switch ( texUnit->CombineModeRGB ) {
   case GL_REPLACE:
      color_combine = (RADEON_COLOR_ARG_A_ZERO |
		       RADEON_COLOR_ARG_B_ZERO |
		       RADEON_BLEND_CTL_ADD |
		       RADEON_CLAMP_TX);
      RADEON_COLOR_ARG( 0, C );
      break;
   case GL_MODULATE:
      color_combine = (RADEON_COLOR_ARG_C_ZERO |
		       RADEON_BLEND_CTL_ADD |
		       RADEON_CLAMP_TX);
      RADEON_COLOR_ARG( 0, A );
      RADEON_COLOR_ARG( 1, B );
      break;
   case GL_ADD:
      color_combine = (RADEON_COLOR_ARG_B_ZERO |
		       RADEON_COMP_ARG_B |
		       RADEON_BLEND_CTL_ADD |
		       RADEON_CLAMP_TX);
      RADEON_COLOR_ARG( 0, A );
      RADEON_COLOR_ARG( 1, C );
      break;
   case GL_ADD_SIGNED:
      color_combine = (RADEON_COLOR_ARG_B_ZERO |
		       RADEON_COMP_ARG_B |
		       RADEON_BLEND_CTL_ADDSIGNED |
		       RADEON_CLAMP_TX);
      RADEON_COLOR_ARG( 0, A );
      RADEON_COLOR_ARG( 1, C );
      break;
   case GL_SUBTRACT:
      color_combine = (RADEON_COLOR_ARG_B_ZERO |
		       RADEON_COMP_ARG_B |
		       RADEON_BLEND_CTL_SUBTRACT |
		       RADEON_CLAMP_TX);
      RADEON_COLOR_ARG( 0, A );
      RADEON_COLOR_ARG( 1, C );
      break;
   case GL_INTERPOLATE:
      color_combine = (RADEON_BLEND_CTL_BLEND |
		       RADEON_CLAMP_TX);
      RADEON_COLOR_ARG( 0, B );
      RADEON_COLOR_ARG( 1, A );
      RADEON_COLOR_ARG( 2, C );
      break;

   case GL_DOT3_RGB:
   case GL_DOT3_RGBA:
      if ( texUnit->CombineScaleShiftRGB 
	   != (RADEON_SCALE_1X >> RADEON_SCALE_SHIFT) )
      {
	 return GL_FALSE;
      }
      /* FALLTHROUGH */

   case GL_DOT3_RGB_EXT:
   case GL_DOT3_RGBA_EXT:
      color_combine = (RADEON_COLOR_ARG_C_ZERO |
		       RADEON_BLEND_CTL_DOT3 |
		       RADEON_CLAMP_TX);
      RADEON_COLOR_ARG( 0, A );
      RADEON_COLOR_ARG( 1, B );
      break;
   default:
      return GL_FALSE;
   }

   switch ( texUnit->CombineModeA ) {
   case GL_REPLACE:
      alpha_combine = (RADEON_ALPHA_ARG_A_ZERO |
		       RADEON_ALPHA_ARG_B_ZERO |
		       RADEON_BLEND_CTL_ADD |
		       RADEON_CLAMP_TX);
      RADEON_ALPHA_ARG( 0, C );
      break;
   case GL_MODULATE:
      alpha_combine = (RADEON_ALPHA_ARG_C_ZERO |
		       RADEON_BLEND_CTL_ADD |
		       RADEON_CLAMP_TX);
      RADEON_ALPHA_ARG( 0, A );
      RADEON_ALPHA_ARG( 1, B );
      break;
   case GL_ADD:
      alpha_combine = (RADEON_ALPHA_ARG_B_ZERO |
		       RADEON_COMP_ARG_B |
		       RADEON_BLEND_CTL_ADD |
		       RADEON_CLAMP_TX);
      RADEON_ALPHA_ARG( 0, A );
      RADEON_ALPHA_ARG( 1, C );
      break;
   case GL_ADD_SIGNED:
      alpha_combine = (RADEON_ALPHA_ARG_B_ZERO |
		       RADEON_COMP_ARG_B |
		       RADEON_BLEND_CTL_ADDSIGNED |
		       RADEON_CLAMP_TX);
      RADEON_ALPHA_ARG( 0, A );
      RADEON_ALPHA_ARG( 1, C );
      break;
   case GL_SUBTRACT:
      alpha_combine = (RADEON_COLOR_ARG_B_ZERO |
		       RADEON_COMP_ARG_B |
		       RADEON_BLEND_CTL_SUBTRACT |
		       RADEON_CLAMP_TX);
      RADEON_ALPHA_ARG( 0, A );
      RADEON_ALPHA_ARG( 1, C );
      break;
   case GL_INTERPOLATE:
      alpha_combine = (RADEON_BLEND_CTL_BLEND |
		       RADEON_CLAMP_TX);
      RADEON_ALPHA_ARG( 0, B );
      RADEON_ALPHA_ARG( 1, A );
      RADEON_ALPHA_ARG( 2, C );
      break;
   default:
      return GL_FALSE;
   }

   if ( (texUnit->CombineModeRGB == GL_DOT3_RGB_EXT)
	|| (texUnit->CombineModeRGB == GL_DOT3_RGB_ARB) ) {
      alpha_combine |= RADEON_DOT_ALPHA_DONT_REPLICATE;
   }

   /* Step 3:
    * Apply the scale factor.  The EXT version of the DOT3 extension does
    * not support the scale factor, but the ARB version (and the version in
    * OpenGL 1.3) does.  The catch is that the Radeon only supports a 1X
    * multiplier in hardware w/the ARB version.
    */
   if ( texUnit->CombineModeRGB != GL_DOT3_RGB_EXT &&
	texUnit->CombineModeRGB != GL_DOT3_RGBA_EXT &&
	texUnit->CombineModeRGB != GL_DOT3_RGB &&
	texUnit->CombineModeRGB != GL_DOT3_RGBA ) {
      color_combine |= (texUnit->CombineScaleShiftRGB << RADEON_SCALE_SHIFT);
      alpha_combine |= (texUnit->CombineScaleShiftA << RADEON_SCALE_SHIFT);
   }
   else
   {
      color_combine |= RADEON_SCALE_4X;
      alpha_combine |= RADEON_SCALE_4X;
   }

   /* All done!
    */
   return GL_TRUE;
}
