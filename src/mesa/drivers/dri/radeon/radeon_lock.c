/* $XFree86: xc/lib/GL/mesa/src/drv/radeon/radeon_lock.c,v 1.4 2002/02/22 21:45:00 dawes Exp $ */
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
#include "radeon_context.h"
#include "radeon_lock.h"
#include "radeon_state.h"
#include "radeon_ioctl.h"

#if _HAVE_FULL_GL
#include "radeon_tex.h"
#else
#include "radeon_subset.h"
#endif

#if DEBUG_LOCKING
char *prevLockFile = NULL;
int prevLockLine = 0;
#endif

void radeonUpdateViewportOffset( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   __DRIdrawablePrivate *dPriv = rmesa->dri.drawable;
   GLfloat xoffset = (GLfloat)dPriv->x;
   GLfloat yoffset = (GLfloat)dPriv->y + dPriv->h;
   const GLfloat *v = ctx->Viewport._WindowMap.m;

   GLfloat tx = v[MAT_TX] + xoffset;
   GLfloat ty = (- v[MAT_TY]) + yoffset;

   if ( rmesa->hw.vpt.cmd[VPT_SE_VPORT_XOFFSET] != *(GLuint *)&tx ||
	rmesa->hw.vpt.cmd[VPT_SE_VPORT_YOFFSET] != *(GLuint *)&ty )
   {
      /* Note: this should also modify whatever data the context reset
       * code uses...
       */
      rmesa->hw.vpt.cmd[VPT_SE_VPORT_XOFFSET] = *(GLuint *)&tx;
      rmesa->hw.vpt.cmd[VPT_SE_VPORT_YOFFSET] = *(GLuint *)&ty;
      
      /* update polygon stipple x/y screen offset */
      {
         GLuint stx, sty;
         GLuint m = rmesa->hw.msc.cmd[MSC_RE_MISC];

         m &= ~(RADEON_STIPPLE_X_OFFSET_MASK |
                RADEON_STIPPLE_Y_OFFSET_MASK);

         /* add magic offsets, then invert */
         stx = 31 - ((rmesa->dri.drawable->x - 1) & RADEON_STIPPLE_COORD_MASK);
         sty = 31 - ((rmesa->dri.drawable->y + rmesa->dri.drawable->h - 1)
                     & RADEON_STIPPLE_COORD_MASK);

         m |= ((stx << RADEON_STIPPLE_X_OFFSET_SHIFT) |
               (sty << RADEON_STIPPLE_Y_OFFSET_SHIFT));

         if ( rmesa->hw.msc.cmd[MSC_RE_MISC] != m ) {
            RADEON_STATECHANGE( rmesa, msc );
	    rmesa->hw.msc.cmd[MSC_RE_MISC] = m;
         }
      }
   }

   radeonUpdateScissor( ctx );
}


/* Turn on/off page flipping according to the flags in the sarea:
 */
static void
radeonUpdatePageFlipping( radeonContextPtr rmesa )
{
   int use_back;

   if (rmesa->dri.drmMinor < 3)
      return;

   rmesa->doPageFlip = rmesa->sarea->pfAllowPageFlip;
   rmesa->doPageFlip = 0;

   use_back = (rmesa->glCtx->Color._DrawDestMask == BACK_LEFT_BIT);
   use_back ^= (rmesa->sarea->pfCurrentPage == 1);

   if ( use_back ) {
	 rmesa->state.color.drawOffset = rmesa->radeonScreen->backOffset;
	 rmesa->state.color.drawPitch  = rmesa->radeonScreen->backPitch;
   } else {
	 rmesa->state.color.drawOffset = rmesa->radeonScreen->frontOffset;
	 rmesa->state.color.drawPitch  = rmesa->radeonScreen->frontPitch;
   }

   RADEON_STATECHANGE( rmesa, ctx );
   rmesa->hw.ctx.cmd[CTX_RB3D_COLOROFFSET] = rmesa->state.color.drawOffset;
   rmesa->hw.ctx.cmd[CTX_RB3D_COLORPITCH]  = rmesa->state.color.drawPitch;
}


static void validate_drawable( radeonContextPtr rmesa )
{
   __DRIdrawablePrivate *dPriv = rmesa->dri.drawable;

   fprintf(stderr, "%s\n", __FUNCTION__);

   /* The window might have moved, so we might need to get new clip
    * rects.
    *
    * NOTE: This releases and regrabs the hw lock to allow the X server
    * to respond to the DRI protocol request for new drawable info.
    * Since the hardware state depends on having the latest drawable
    * clip rects, all state checking must be done _after_ this call.
    */
   DRI_VALIDATE_DRAWABLE_INFO( sPriv, dPriv );

   if ( rmesa->lastStamp != dPriv->lastStamp ) {
      radeonUpdatePageFlipping( rmesa );

      if (rmesa->glCtx->Color._DrawDestMask == BACK_LEFT_BIT)
         radeonSetCliprects( rmesa, GL_BACK_LEFT );
      else
         radeonSetCliprects( rmesa, GL_FRONT_LEFT );
      radeonUpdateViewportOffset( rmesa->glCtx );
      rmesa->lastStamp = dPriv->lastStamp;
   }
}


/* Update the hardware state.  This is called if another context has
 * grabbed the hardware lock, which includes the X server.  This
 * function also updates the driver's window state after the X server
 * moves, resizes or restacks a window -- the change will be reflected
 * in the drawable position and clip rects.  Since the X server grabs
 * the hardware lock when it changes the window state, this routine will
 * automatically be called after such a change.
 */
void radeonGetLock( radeonContextPtr rmesa, GLuint flags )
{
   RADEONSAREAPrivPtr sarea = rmesa->sarea;
   int i;


   while (1) {
      drmGetLock( rmesa->dri.fd, rmesa->dri.hwContext, flags );

      validate_drawable( rmesa );

      fprintf(stderr, "%s %d\n", __FUNCTION__, rmesa->numClipRects);

      if (rmesa->numClipRects)
	 break;

      drmUnlock( rmesa->dri.fd, rmesa->dri.hwContext );
      
      sleep(10);
   }


   if ( sarea->ctxOwner != rmesa->dri.hwContext ) {
      sarea->ctxOwner = rmesa->dri.hwContext;

      for ( i = 0 ; i < rmesa->texture.numHeaps ; i++ ) {
	 if ( rmesa->texture.heap[i] && 
	      sarea->texAge[i] != rmesa->texture.age[i] ) {
	    radeonAgeTextures( rmesa, i );
	 }
      }
   }
}


extern void __miniglx_release_vt( void );

/* In the current miniglx, cliprects can change while the lock is
 * held...  Probably need to fix this.
 */
void radeonUnlock( radeonContextPtr rmesa )
{
   fprintf(stderr, "%s\n", __FUNCTION__);

   drmUnlock( rmesa->dri.fd, rmesa->dri.hwContext );

   validate_drawable( rmesa );

   /* This only happens if the VT switch was requested inside the
    * locked region.
    */
   if (!rmesa->numClipRects)
      __miniglx_release_vt();
      
}
