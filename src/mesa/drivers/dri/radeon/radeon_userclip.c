/* $XFree86: xc/lib/GL/mesa/src/drv/radeon/radeon_state.c,v 1.5 2002/09/16 18:05:20 eich Exp $ */
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
 *
 * Authors:
 *    Gareth Hughes <gareth@valinux.com>
 *    Keith Whitwell <keith@tungstengraphics.com>
 */

#include "glheader.h"
#include "imports.h"
#include "api_arrayelt.h"
#include "mmath.h"
#include "enums.h"
#include "colormac.h"


#include "radeon_context.h"
#include "radeon_ioctl.h"
#include "radeon_state.h"
#include "radeon_tcl.h"
#include "radeon_tex.h"
#include "radeon_vtxfmt.h"

void radeonClipPlane( GLcontext *ctx, GLenum plane, const GLfloat *eq )
{
   GLint p = (GLint) plane - (GLint) GL_CLIP_PLANE0;
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLint *ip = (GLint *)ctx->Transform._ClipUserPlane[p];

   RADEON_STATECHANGE( rmesa, ucp[p] );
   rmesa->hw.ucp[p].cmd[UCP_X] = ip[0];
   rmesa->hw.ucp[p].cmd[UCP_Y] = ip[1];
   rmesa->hw.ucp[p].cmd[UCP_Z] = ip[2];
   rmesa->hw.ucp[p].cmd[UCP_W] = ip[3];
}

void radeonUpdateClipPlanes( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint p;

   for (p = 0; p < ctx->Const.MaxClipPlanes; p++) {
      if (ctx->Transform.ClipPlanesEnabled & (1 << p)) {
	 GLint *ip = (GLint *)ctx->Transform._ClipUserPlane[p];

	 RADEON_STATECHANGE( rmesa, ucp[p] );
	 rmesa->hw.ucp[p].cmd[UCP_X] = ip[0];
	 rmesa->hw.ucp[p].cmd[UCP_Y] = ip[1];
	 rmesa->hw.ucp[p].cmd[UCP_Z] = ip[2];
	 rmesa->hw.ucp[p].cmd[UCP_W] = ip[3];
      }
   }
}

void radeonInitUserClip( GLcontext *ctx )
{
   int i;
   ctx->Driver.ClipPlane = radeonClipPlane;

   for (i = 0 ; i < 6; i++)
      ctx->Driver.ClipPlane( ctx, GL_CLIP_PLANE0 + i, NULL );
}
