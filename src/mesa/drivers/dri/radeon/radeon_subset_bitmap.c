/**
 * \file radeon_subset_bitmap.c
 * \brief Bitmap drawing.
 * 
 * \author Keith Whitwell <keith@tungstengraphics.com>
 */

/*
 * Copyright 2003       ATI Technologies Inc., Ontario, Canada, and
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
#include "mtypes.h"
#include "colormac.h"
#include "context.h"
#include "enums.h"
#include "imports.h"
#include "image.h"
#include "mmath.h"
#include "macros.h"
#include "state.h"

#include "radeon_context.h"
#include "radeon_ioctl.h"
#include "radeon_state.h"
#include "radeon_subset.h"

/**
 * \brief Cope with depth operations by drawing individual pixels as points
 *
 * \param ctx GL context.
 * \param px x coordinate of the bitmap corner.
 * \param py y coordinate of the bitmap corner.
 * \param width bitmap width.
 * \param height bitmap height.
 * \param unpack unpacking pixel attributes.
 * \param bitmap bitmap pointer.
 * 
 * Clips the bitmap coordinates and adjusts for windows coordinates. Draws the
 * bitmap with glPoints(), turning off TCL and hardware viewport transformation
 * to emit raw pixel coordinates. Finally fires any outstanding vertices and
 * restores TCL, viewport, texture and color states.
 */
void
radeonPointsBitmap(  GLsizei width, GLsizei height,
		     GLfloat xorig, GLfloat yorig, 
		     GLfloat xmove, GLfloat ymove,
		     const GLubyte *bitmap )
{
   GET_CURRENT_CONTEXT(ctx);
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLfloat saved_color[4], saved_tex0[2];
   GLint row, col;
   GLuint orig_se_cntl;
   GLuint h;
   const struct gl_pixelstore_attrib *unpack = &ctx->Unpack;
   GLint skipRows = unpack->SkipRows;
   GLint skipPixels = unpack->SkipPixels;
   GLint px = IFLOOR(ctx->Current.RasterPos[0] - xorig);
   GLint py = IFLOOR(ctx->Current.RasterPos[1] - yorig);


   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (width < 0 || height < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glBitmap(width or height < 0)" );
      return;
   }

   if (!ctx->Current.RasterPosValid)
      return;

   if (ctx->NewState) 
      _mesa_update_state(ctx);

   /* update raster position */
   ctx->Current.RasterPos[0] += xmove;
   ctx->Current.RasterPos[1] += ymove;

   /* horizontal clipping */
   if (px < 0) {
      skipPixels -= px;
      width += px;
      px = 0;
   }
   if (px + width > (GLint) ctx->ReadBuffer->Width)
      width -= (px + width - (GLint) ctx->ReadBuffer->Width);
   if (width <= 0)
      return;

   /* vertical clipping */
   if (py < 0) {
      skipRows -= py;
      height += py;
      py = 0;
   }
   if (py + height > (GLint) ctx->ReadBuffer->Height)
      height -= (py + height - (GLint) ctx->ReadBuffer->Height);
   if (height <= 0)
      return;


   /* Turn off tcl and the hw viewport transformation so that we can
    * emit raw pixel coordinates:
    */
   radeonSubsetVtxEnableTCL( rmesa, GL_FALSE );
   RADEON_STATECHANGE( rmesa, set );
   orig_se_cntl = rmesa->hw.set.cmd[SET_SE_CNTL];
   rmesa->hw.set.cmd[SET_SE_CNTL] &= ~(RADEON_VPORT_XY_XFORM_ENABLE |
				       RADEON_VPORT_Z_XFORM_ENABLE);


   /* Adjust for window coordinates, flip y values:
    */
   h = rmesa->dri.drawable->h + rmesa->dri.drawable->y - 1;
   px += rmesa->dri.drawable->x;

   /* Save current color, texcoord to restore later:
    */
   COPY_4V( saved_color, ctx->Current.Attrib[VERT_ATTRIB_COLOR0] );
   COPY_2V( saved_tex0, ctx->Current.Attrib[VERT_ATTRIB_TEX0] );

   /* Just use the GL entrypoints to talk to radeon_subset_vtx.c:
    */
   glBegin( GL_POINTS );
   glColor4fv( ctx->Current.RasterColor );
   glTexCoord2fv( ctx->Current.RasterTexCoords[0] );

   for (row=0; row<height; row++) {
      GLuint y = h - (py + row);
      const GLubyte *src = (const GLubyte *) 
	 _mesa_image_address( unpack, bitmap, width, height, 
			      GL_COLOR_INDEX, GL_BITMAP, 0, row, 0 );

      /* Msb first */
      GLubyte mask = 128U >> (unpack->SkipPixels & 0x7);
      for (col=0; col<width; col++) {
	 if (*src & mask) {
	    glVertex2f( px+col, y );
	 }
	 src += mask & 1;
	 mask = ((mask << 7) & 0xff) | (mask >> 1);
      }
      /* get ready for next row */
      if (mask != 128)
	 src++;
   }
   
   glEnd();
   glColor4fv( saved_color );
   glTexCoord2fv( saved_tex0 );

   /* Fire outstanding vertices, restore state
    */
   RADEON_STATECHANGE( rmesa, set );
   rmesa->hw.set.cmd[SET_SE_CNTL] = orig_se_cntl;
   radeonSubsetVtxEnableTCL( rmesa, GL_TRUE );

}
