/**
 * \file radeon_subset_readpix.c
 * 
 * \author Keith Whitwell <keith@tungstengraphics.com>
 * \author Brian Paul <brian@tungstengraphics.com>
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
#include "enums.h"
#include "imports.h"
#include "mmath.h"
#include "macros.h"

#include "radeon_context.h"
#include "radeon_ioctl.h"
#include "radeon_state.h"
#include "radeon_subset.h"

#define READ_RGBA_16( rgba, ptr )		\
do {						\
    GLushort p = *(GLushort *)ptr;		\
    rgba[0] = ((p >> 8) & 0xf8) * 255 / 0xf8;	\
    rgba[1] = ((p >> 3) & 0xfc) * 255 / 0xfc;	\
    rgba[2] = ((p << 3) & 0xf8) * 255 / 0xf8;	\
    rgba[3] = 0xff;				\
} while (0)

#define READ_RGBA_32( rgba, ptr )		\
do {						\
   GLuint p = *(GLuint *)ptr;			\
   rgba[0] = (p >> 16) & 0xff;			\
   rgba[1] = (p >>  8) & 0xff;			\
   rgba[2] = (p >>  0) & 0xff;			\
   rgba[3] = (p >> 24) & 0xff;			\
} while (0)

static void ReadRGBASpan( const GLcontext *ctx,
			       GLuint n, GLint x, GLint y,
			       GLubyte rgba[][4])
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   radeonScreenPtr radeonScreen = rmesa->radeonScreen;
   __DRIdrawablePrivate *dPriv = rmesa->dri.drawable;
   GLuint pitch = radeonScreen->frontPitch * radeonScreen->cpp;
   char *ptr = (char *)(rmesa->dri.screen->pFB +
			rmesa->state.pixel.readOffset +
			((dPriv->x + x) * radeonScreen->cpp) +
			((dPriv->y + (dPriv->h - y - 1)) * pitch));
   GLint i = 0;

   if (radeonScreen->cpp == 4)
      for (i = 0; i < n; i++, ptr += 4)
	 READ_RGBA_32( rgba[i], ptr );
   else
      for (i = 0; i < n; i++, ptr += 2)
	 READ_RGBA_16( rgba[i], ptr );
}



/**
 * \brief Optimized glReadPixels 
 *
 * For particular pixel formats GL_UNSIGNED_BYTE, GL_RGBA when pixel scaling,
 * biasing and mapping are disabled.
 */
void radeonReadPixels( GLcontext *ctx,
		       GLint x, GLint y,
		       GLsizei width, GLsizei height,
		       GLenum format, GLenum type,
		       const struct gl_pixelstore_attrib *packing,
		       GLvoid *pixels )
{
   GLint srcX = x;
   GLint srcY = y;
   GLint readWidth = width;           /* actual width read */
   GLint readHeight = height;         /* actual height read */
   GLint skipRows = packing->SkipRows;
   GLint skipPixels = packing->SkipPixels;
   GLint rowLength;

   /* can't do scale, bias, mapping, etc */
   assert(!ctx->_ImageTransferState);

   /* can't do fancy pixel packing */
   assert (packing->Alignment == 1 &&
	   !packing->SwapBytes &&
	   !packing->LsbFirst);


   if (packing->RowLength > 0)
      rowLength = packing->RowLength;
   else
      rowLength = width;

   /* horizontal clipping */
   if (srcX < 0) {
      skipPixels -= srcX;
      readWidth += srcX;
      srcX = 0;
   }
   if (srcX + readWidth > (GLint) ctx->ReadBuffer->Width)
      readWidth -= (srcX + readWidth - (GLint) ctx->ReadBuffer->Width);
   if (readWidth <= 0)
      return;

   /* vertical clipping */
   if (srcY < 0) {
      skipRows -= srcY;
      readHeight += srcY;
      srcY = 0;
   }
   if (srcY + readHeight > (GLint) ctx->ReadBuffer->Height)
      readHeight -= (srcY + readHeight - (GLint) ctx->ReadBuffer->Height);
   if (readHeight <= 0)
      return;

   /*
    * Ready to read!
    * The window region at (destX, destY) of size (readWidth, readHeight)
    * will be read back.
    * We'll write pixel data to buffer pointed to by "pixels" but we'll
    * skip "skipRows" rows and skip "skipPixels" pixels/row.
    */
   if (format == GL_RGBA && type == GL_UNSIGNED_BYTE) {
      GLchan *dest = (GLchan *) pixels 
	 + (skipRows * rowLength + skipPixels) * 4;
      GLint row;

      for (row=0; row<readHeight; row++) {
	 ReadRGBASpan(ctx, readWidth, srcX, srcY, (GLchan (*)[4]) dest);
	 dest += rowLength * 4;
	 srcY++;
      }
   }
   else {
      /* can't do this format/type combination */
      assert(0);
   }
}
