/**
 * \file radeon_context.c
 * \brief Device specific context initialization.
 * 
 * \author Kevin E. Martin <martin@valinux.com>
 * \author Gareth Hughes <gareth@valinux.com>
 * \author Keith Whitwell <keith@tungstengraphics.com>
 */

/*
 * Copyright 2000, 2001 ATI Technologies Inc., Ontario, Canada, and
 *                      VA Linux Systems Inc., Fremont, California.
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
 * ATI, VA LINUX SYSTEMS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* $XFree86: xc/lib/GL/mesa/src/drv/radeon/radeon_context.c,v 1.4 2002/09/10 00:39:39 dawes Exp $ */

#include "glheader.h"
#include "imports.h"
#include "api_arrayelt.h"
#include "context.h"
#include "simple_list.h"
#include "matrix.h"
#include "extensions.h"

#include "radeon_context.h"
#include "radeon_ioctl.h"
#include "radeon_state.h"

#if _HAVE_FULL_GL
#include "radeon_tcl.h"
#include "radeon_vtxfmt.h"
#include "radeon_tex.h"
#include "radeon_span.h"
#include "radeon_maos.h"
#else
#include "radeon_subset.h"
#endif

#if defined(USE_X86_ASM)
#include "X86/common_x86_asm.h"
#endif

#define RADEON_DATE	"20021125"

#ifndef RADEON_DEBUG
int RADEON_DEBUG = (0);
#endif


/**
 * \brief Return the width and height of the given buffer.
 *
 * \param buffer frame buffer. Not used.
 * \param width will hold the width of the buffer.
 * \param height will hold the height of the buffer.
 * 
 * Returns the width and height of the current drawable while holding the
 * hardware lock.
 */
static void radeonGetBufferSize( GLframebuffer *buffer,
				 GLuint *width, GLuint *height )
{
   GET_CURRENT_CONTEXT(ctx);
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   LOCK_HARDWARE( rmesa );
   *width  = rmesa->dri.drawable->w;
   *height = rmesa->dri.drawable->h;
   UNLOCK_HARDWARE( rmesa );
}

/**
 * \brief Return various strings for glGetString().
 *
 * \param ctx GL context.
 * \param name name of the string to return.
 *
 * \param pointer to a static string describing the aspect specified by \p
 * name.
 *
 * \sa glGetString().
 *
 * Returns the wanted string, appending miscellaneous information (such as AGP
 * mode, processor abilities, TCL support, etc.) for the GL_RENDERER aspect.
 */
static const GLubyte *radeonGetString( GLcontext *ctx, GLenum name )
{
   static char buffer[128];

   switch ( name ) {
   case GL_VENDOR:
      return (GLubyte *)"Tungsten Graphics, Inc.";

   case GL_RENDERER:
      sprintf( buffer, "Mesa DRI Radeon SUBSET " RADEON_DATE);

      return (GLubyte *)buffer;

   default:
      return NULL;
   }
}


/**
 * \brief Device specific extension names exported by the R100 driver.
 *
 * \note None in the case of the subset driver.
 */
static const char * const radeon_extensions[] =
{
#if _HAVE_FULL_GL
    "GL_ARB_multisample",
    "GL_ARB_multitexture",
    "GL_ARB_texture_border_clamp",
    "GL_ARB_texture_compression",
    "GL_ARB_texture_env_add",
    "GL_ARB_texture_env_combine",
    "GL_ARB_texture_env_dot3",
    "GL_ARB_texture_mirrored_repeat",
    "GL_EXT_blend_logic_op",
    "GL_EXT_blend_subtract",
/*    "GL_EXT_fog_coord", */
    "GL_EXT_secondary_color",
    "GL_EXT_texture_env_add",
    "GL_EXT_texture_env_combine",
    "GL_EXT_texture_env_dot3",
    "GL_EXT_texture_filter_anisotropic",
    "GL_EXT_texture_lod_bias",
    "GL_ATI_texture_mirror_once",
    "GL_IBM_texture_mirrored_repeat",
    "GL_NV_blend_square",
    "GL_SGIS_generate_mipmap",
    "GL_SGIS_texture_border_clamp",
#endif
    NULL
};

/**
 * \brief Initialize the extensions supported by this driver.
 *
 * \param ctx GL context.
 *
 * Enables the imaging extensions plus every extension specified in in the
 * ::radeon_extensions table.
 */
static void radeonInitExtensions( GLcontext *ctx )
{
   unsigned   i;
   _mesa_enable_imaging_extensions( ctx );

   for ( i = 0 ; radeon_extensions[i] != NULL ; i++ ) {
      _mesa_enable_extension( ctx, radeon_extensions[i] );
   }
}


/**
 * \brief Resize the buffers.
 *
 * \param buffer frame buffer to be resized.
 * 
 * Informs the software rasterizer (if enabled at compile time) of the buffer
 * resizing.
 */
static void ResizeBuffers( GLframebuffer *buffer )
{
#if _HAVE_SWRAST
   _swrast_alloc_buffers( buffer );
#endif
}


/**
 * \brief Initialize the driver miscellaneous function callbacks.
 *
 * \param ctx GL context.
 */
static void radeonInitDriverFuncs( GLcontext *ctx )
{
    ctx->Driver.GetBufferSize		= radeonGetBufferSize;
    ctx->Driver.GetString		= radeonGetString;
    ctx->Driver.ResizeBuffers           = ResizeBuffers;
    ctx->Driver.Error			= NULL;
    ctx->Driver.DrawPixels		= NULL;
#if !_HAVE_SWRAST
    ctx->Driver.Bitmap			= radeonPointsBitmap;
    ctx->Driver.ReadPixels		= radeonReadPixels;
#endif
}



/**
 * \brief Create the device specific context.
 *
 * \param glVisual visual information.
 * \param driContextPriv DRI specific context data.
 * \param sharedContextPrivate shared context.
 * 
 * \return GL_TRUE if successful, or GL_FALSE otherwise.
 *
 * Allocates a Radeon context and initializes it, adding a Mesa context. Fills
 * in with information from the Radeon specific screen data in
 * __DRIscreenPrivateRec::private, such as the SAREA pointer, DMA buffers
 * addresses and texture heaps.
 *
 * Calls the \c radeonInit* functions to populate the driver callback
 * functions. Among these are radeonInitState(), radeonInitExtensions(),
 * radeonInitDriverFuncs(), radeonInitIoctlFuncs(), radeonInitStateFuncs(),
 * radeonInitTextureFuncs() and radeonInitSelect().
 *
 * If compiled with debug support, reads the RADEON_DEBUG environment variable
 * and sets the debugging flags accordingly.
 */
static GLboolean
radeonCreateContext( const __GLcontextModes *glVisual,
                     __DRIcontextPrivate *driContextPriv,
                     void *sharedContextPrivate)
{
   __DRIscreenPrivate *sPriv = driContextPriv->driScreenPriv;
   radeonScreenPtr radeonScreen = (radeonScreenPtr)(sPriv->private);
   radeonContextPtr rmesa;
   GLcontext *ctx, *shareCtx;
   int i, nr;

   assert(glVisual);
   assert(driContextPriv);
   assert(radeonScreen);

   /* Allocate the Radeon context */
   rmesa = (radeonContextPtr) CALLOC( sizeof(*rmesa) );
   if ( !rmesa )
      return GL_FALSE;

   /* Allocate the Mesa context */
   if (sharedContextPrivate)
      shareCtx = ((radeonContextPtr) sharedContextPrivate)->glCtx;
   else
      shareCtx = NULL;
   rmesa->glCtx = _mesa_create_context(glVisual, shareCtx, (void *) rmesa,
				       GL_TRUE);
   if (!rmesa->glCtx) {
      FREE(rmesa);
      return GL_FALSE;
   }
   driContextPriv->driverPrivate = rmesa;

   /* Init radeon context data */
   rmesa->dri.context = driContextPriv;
   rmesa->dri.screen = sPriv;
   rmesa->dri.drawable = NULL; /* Set by XMesaMakeCurrent */
   rmesa->dri.hwContext = driContextPriv->hHWContext;
   rmesa->dri.hwLock = &sPriv->pSAREA->lock;
   rmesa->dri.fd = sPriv->fd;

   /* If we don't have 1.3, fallback to the 1.1 interfaces.
    */
   if (getenv("RADEON_COMPAT") || sPriv->drmMinor < 3 ) 
      rmesa->dri.drmMinor = 1;
   else
      rmesa->dri.drmMinor = sPriv->drmMinor;

   rmesa->radeonScreen = radeonScreen;
   rmesa->sarea = (RADEONSAREAPrivPtr)((GLubyte *)sPriv->pSAREA +
				       radeonScreen->sarea_priv_offset);


   rmesa->dma.buf0_address = rmesa->radeonScreen->buffers->list[0].address;

   for ( i = 0 ; i < radeonScreen->numTexHeaps ; i++ ) {
      make_empty_list( &rmesa->texture.objects[i] );
      rmesa->texture.heap[i] = mmInit( 0, radeonScreen->texSize[i] );
      rmesa->texture.age[i] = -1;
   }
   rmesa->texture.numHeaps = radeonScreen->numTexHeaps;
   make_empty_list( &rmesa->texture.swapped );

   rmesa->lost_context = 1;
   
   rmesa->tcl.tcl_flag = RADEON_CP_VC_CNTL_TCL_ENABLE;

   /* KW: Set the maximum texture size small enough that we can
    * guarentee that both texture units can bind a maximal texture
    * and have them both in on-card memory at once.
    * Test for 2 textures * 4 bytes/texel * size * size.
    */
   ctx = rmesa->glCtx;

#if _HAVE_FULL_GL
   nr = 2;
#else
   nr = 1;
#endif

   ctx->Const.MaxTextureUnits = nr;
   if (radeonScreen->texSize[RADEON_CARD_HEAP] >= nr * 4 * 2048 * 2048) {
      ctx->Const.MaxTextureLevels = 12; /* 2048x2048 */
   }
   else if (radeonScreen->texSize[RADEON_CARD_HEAP] >= nr * 4 * 1024 * 1024) {
      ctx->Const.MaxTextureLevels = 11; /* 1024x1024 */
   }
   else if (radeonScreen->texSize[RADEON_CARD_HEAP] >= nr * 4 * 512 * 512) {
      ctx->Const.MaxTextureLevels = 10; /* 512x512 */
   }
   else {
      ctx->Const.MaxTextureLevels = 9; /* 256x256 */
   }

   ctx->Const.MaxTextureMaxAnisotropy = 16.0;

   /* No wide points.
    */
   ctx->Const.MinPointSize = 1.0;
   ctx->Const.MinPointSizeAA = 1.0;
   ctx->Const.MaxPointSize = 1.0;
   ctx->Const.MaxPointSizeAA = 1.0;

   ctx->Const.MinLineWidth = 1.0;
   ctx->Const.MinLineWidthAA = 1.0;
   ctx->Const.MaxLineWidth = 10.0;
   ctx->Const.MaxLineWidthAA = 10.0;
   ctx->Const.LineWidthGranularity = 0.0625;

#if _HAVE_SWRAST
   radeonCreateSwrastContext( ctx );
#endif
#if _HAVE_SWTNL
   radeonCreateTnlContext( ctx );
#endif

   radeonInitState( rmesa );


#if _HAVE_TEXGEN
   radeonInitTexTransform( ctx );
#endif
#if _HAVE_LIGHTING
   radeonInitLightStateFuncs( ctx );
#endif
   radeonInitExtensions( ctx );
   radeonInitDriverFuncs( ctx );
   radeonInitIoctlFuncs( ctx );
   radeonInitStateFuncs( ctx );
#if _HAVE_SWRAST
   radeonInitSpanFuncs( ctx );
#endif
   radeonInitTextureFuncs( ctx );
#if _HAVE_SWTNL
   radeonInitSwtcl( ctx );
#endif
#if !_HAVE_FULL_GL
   radeonInitSelect( ctx );
#endif

   rmesa->do_irqs = (rmesa->radeonScreen->irq && !getenv("RADEON_NO_IRQS"));
   rmesa->irqsEmitted = 0;
   rmesa->iw.irq_seq = -1;

   rmesa->do_usleeps = !getenv("RADEON_NO_USLEEPS");
   
#if DO_DEBUG
   if (getenv("RADEON_DEBUG"))
   {
      const char *debug = getenv("RADEON_DEBUG");
      if (strstr(debug, "fall")) 
         RADEON_DEBUG |= DEBUG_FALLBACKS;

      if (strstr(debug, "tex")) 
         RADEON_DEBUG |= DEBUG_TEXTURE;

      if (strstr(debug, "ioctl")) 
         RADEON_DEBUG |= DEBUG_IOCTL;

      if (strstr(debug, "prim")) 
         RADEON_DEBUG |= DEBUG_PRIMS;

      if (strstr(debug, "vert")) 
         RADEON_DEBUG |= DEBUG_VERTS;

      if (strstr(debug, "state")) 
         RADEON_DEBUG |= DEBUG_STATE;

      if (strstr(debug, "code")) 
         RADEON_DEBUG |= DEBUG_CODEGEN;

      if (strstr(debug, "vfmt") || strstr(debug, "vtxf")) 
         RADEON_DEBUG |= DEBUG_VFMT;

      if (strstr(debug, "verb")) 
         RADEON_DEBUG |= DEBUG_VERBOSE;

      if (strstr(debug, "dri")) 
         RADEON_DEBUG |= DEBUG_DRI;

      if (strstr(debug, "dma")) 
         RADEON_DEBUG |= DEBUG_DMA;

      if (strstr(debug, "san")) 
         RADEON_DEBUG |= DEBUG_SANITY;
   }
#endif

#if _HAVE_SWRAST && _HAVE_SWTNL
   if (getenv("RADEON_NO_RAST")) {
      fprintf(stderr, "disabling 3D acceleration\n");
      FALLBACK(rmesa, RADEON_FALLBACK_DISABLE, 1); 
   }
   else if (getenv("RADEON_TCL_FORCE_ENABLE")) {
      fprintf(stderr, "Enabling TCL support...  this will probably crash\n");
      fprintf(stderr, "         your card if it isn't capable of TCL!\n");
      rmesa->radeonScreen->chipset |= RADEON_CHIPSET_TCL;
   } else if (getenv("RADEON_TCL_FORCE_DISABLE") ||
	    rmesa->dri.drmMinor < 3 ||
	    !(rmesa->radeonScreen->chipset & RADEON_CHIPSET_TCL)) {
      rmesa->radeonScreen->chipset &= ~RADEON_CHIPSET_TCL;
      fprintf(stderr, "disabling TCL support\n");
      TCL_FALLBACK(rmesa->glCtx, RADEON_TCL_FALLBACK_TCL_DISABLE, 1); 
   }

   if (rmesa->radeonScreen->chipset & RADEON_CHIPSET_TCL) {
      if (!getenv("RADEON_NO_VTXFMT"))
	 radeonVtxfmtInit( ctx );
      _tnl_need_dlist_norm_lengths( ctx, GL_FALSE );
   }
#else
   radeonVtxfmtInit( ctx );
#endif

   return GL_TRUE;
}


/**
 * \brief Destroy the device specific context data.
 *
 * \param driContextPriv DRI specific context data.
 *
 * If destroying the currently bound context, fires the vertices and unbinds it
 * first.
 *
 * Frees the radeon context resources, freeing the Mesa context. Frees the
 * private texture object from the shared context data if its reference count
 * reaches zero.
 */
static void
radeonDestroyContext( __DRIcontextPrivate *driContextPriv )
{
   GET_CURRENT_CONTEXT(ctx);
   radeonContextPtr rmesa = (radeonContextPtr) driContextPriv->driverPrivate;
   radeonContextPtr current = ctx ? RADEON_CONTEXT(ctx) : NULL;

   /* check if we're deleting the currently bound context */
   if (rmesa == current) {
      RADEON_FIREVERTICES( rmesa );
      _mesa_make_current2(NULL, NULL, NULL);
   }

   /* Free radeon context resources */
   assert(rmesa); /* should never be null */
   if ( rmesa ) {
      if (rmesa->glCtx->Shared->RefCount == 1) {
         /* This share group is about to go away, free our private
          * texture object data.
          */
         radeonTexObjPtr t, next_t;
         int i;

         for ( i = 0 ; i < rmesa->texture.numHeaps ; i++ ) {
            foreach_s ( t, next_t, &rmesa->texture.objects[i] ) {
               radeonDestroyTexObj( rmesa, t );
            }
            mmDestroy( rmesa->texture.heap[i] );
	    rmesa->texture.heap[i] = NULL;
         }

         foreach_s ( t, next_t, &rmesa->texture.swapped ) {
            radeonDestroyTexObj( rmesa, t );
         }
      }


#if _HAVE_SWRAST
      _swsetup_DestroyContext( rmesa->glCtx );
      _swrast_DestroyContext( rmesa->glCtx );
#endif
#if _HAVE_SWTNL
      _tnl_DestroyContext( rmesa->glCtx );
      _ac_DestroyContext( rmesa->glCtx );
      radeonDestroySwtcl( rmesa->glCtx );
      radeonReleaseArrays( rmesa->glCtx, ~0 );
#endif

      if (rmesa->dma.current.buf) {
	 radeonReleaseDmaRegion( rmesa, &rmesa->dma.current, __FUNCTION__ );
	 radeonFlushCmdBuf( rmesa, __FUNCTION__ );
      }

#if _HAVE_FULL_GL
      if (!rmesa->TclFallback & RADEON_TCL_FALLBACK_TCL_DISABLE)
	 if (!getenv("RADEON_NO_VTXFMT"))
	    radeonVtxfmtDestroy( rmesa->glCtx );
#endif

      /* free the Mesa context */
      rmesa->glCtx->DriverCtx = NULL;
      _mesa_destroy_context( rmesa->glCtx );

      if (rmesa->state.scissor.pClipRects) {
	 FREE(rmesa->state.scissor.pClipRects);
	 rmesa->state.scissor.pClipRects = 0;
      }

      FREE( rmesa );
   }

}


/**
 * \brief Create and initialize the Mesa and device specific pixmap buffer
 * data.
 *
 * \param driScrnPriv DRI specific screen data.
 * \param driDrawPriv DRI specific drawable data.
 * \param mesaVis visual.
 * \param isPixmap must be GL_FALSE. Not implemented.
 *
 * Calls _mesa_create_framebuffer() to create the framebuffer.
 */
static GLboolean
radeonCreateBuffer( __DRIscreenPrivate *driScrnPriv,
                    __DRIdrawablePrivate *driDrawPriv,
                    const __GLcontextModes *mesaVis,
                    GLboolean isPixmap )
{
   if (isPixmap) {
      return GL_FALSE; /* not implemented */
   }
   else {
      GLboolean swDepth = GL_FALSE;
      GLboolean swAlpha = GL_FALSE;
      GLboolean swAccum = mesaVis->accumRedBits > 0;
      GLboolean swStencil = (mesaVis->stencilBits > 0 &&
			     mesaVis->depthBits != 24);

#if !_HAVE_SWRAST
      /* Don't allow these if we don't have fallback support.
       */
      swAccum = swStencil = GL_FALSE;
#endif

      driDrawPriv->driverPrivate = (void *)
         _mesa_create_framebuffer( mesaVis,
                                   swDepth,
                                   swStencil,
                                   swAccum,
                                   swAlpha );
      return (driDrawPriv->driverPrivate != NULL);
   }
}


/**
 * \brief Destroy device specific pixmap data.
 *
 * \param driDrawPriv DRI specific drawable data.
 *
 * Calls _mesa_destroy_framebuffer() to destroy Mesa framebuffer.
 */
static void
radeonDestroyBuffer(__DRIdrawablePrivate *driDrawPriv)
{
   _mesa_destroy_framebuffer((GLframebuffer *) (driDrawPriv->driverPrivate));
}


/**
 * \brief Swap buffers.
 *
 * \param dPriv DRI specific drawable data.
 *
 * If in double buffer mode then it dispatches the call to radeonCopyBuffer()
 * or radeonPageFlip() if page flipping is also enabled.
 */
static void
radeonSwapBuffers( __DRIdrawablePrivate *dPriv )
{

   if (dPriv->driContextPriv && dPriv->driContextPriv->driverPrivate) {
      radeonContextPtr rmesa;
      GLcontext *ctx;
      rmesa = (radeonContextPtr) dPriv->driContextPriv->driverPrivate;
      ctx = rmesa->glCtx;
      if (ctx->Visual.doubleBufferMode) {
         _mesa_notifySwapBuffers( ctx );  /* flush pending rendering comands */

         if ( rmesa->doPageFlip ) {
            radeonPageFlip( dPriv );
         }
         else {
            radeonCopyBuffer( dPriv );
         }
      }
   }
   else {
      /* XXX this shouldn't be an error but we can't handle it for now */
      _mesa_problem(NULL, "radeonSwapBuffers: drawable has no context!\n");
   }
}


/**
 * \brief Set the current context.
 * 
 * \param driContextPriv DRI specific context data to be activated. 
 * \param driDrawPriv DRI specific drawable data, to which the context is to be
 * associated for writing.
 * \param driReadPriv DRI specific drawable data, to which the context is to be
 * associated for reading.
 *
 * \return GL_TRUE on success, or GL_FALSE on failure.
 *
 * If drawables differ form the current ones then update the window and
 * viewport information.  Calls _mesa_make_current2() to set the context.
 */
static GLboolean
radeonMakeCurrent( __DRIcontextPrivate *driContextPriv,
                   __DRIdrawablePrivate *driDrawPriv,
                   __DRIdrawablePrivate *driReadPriv )
{
   if ( driContextPriv ) {
      radeonContextPtr newRadeonCtx = 
	 (radeonContextPtr) driContextPriv->driverPrivate;

      if (RADEON_DEBUG & DEBUG_DRI)
	 fprintf(stderr, "%s ctx %p\n", __FUNCTION__, newRadeonCtx->glCtx);

      if ( newRadeonCtx->dri.drawable != driDrawPriv ) {
	 newRadeonCtx->dri.drawable = driDrawPriv;
	 radeonUpdateWindow( newRadeonCtx->glCtx );
	 radeonUpdateViewportOffset( newRadeonCtx->glCtx );
      }

      _mesa_make_current2( newRadeonCtx->glCtx,
			   (GLframebuffer *) driDrawPriv->driverPrivate,
			   (GLframebuffer *) driReadPriv->driverPrivate );

      if ( !newRadeonCtx->glCtx->Viewport.Width ) {
	 _mesa_set_viewport( newRadeonCtx->glCtx, 0, 0,
			     driDrawPriv->w, driDrawPriv->h );
      }

#if _HAVE_FULL_GL
      if (newRadeonCtx->vb.enabled) 
	 radeonVtxfmtMakeCurrent( newRadeonCtx->glCtx ); 
#endif

   } else {
      if (RADEON_DEBUG & DEBUG_DRI)
	 fprintf(stderr, "%s ctx %p\n", __FUNCTION__, NULL);
      _mesa_make_current( 0, 0 );
   }

   if (RADEON_DEBUG & DEBUG_DRI)
      fprintf(stderr, "End %s\n", __FUNCTION__);
   return GL_TRUE;
}


/**
 * \brief Unbind context from its buffer.
 *
 * \param driContextPriv DRI specifc context data.
 *
 * \returns always GL_TRUE.
 *
 * Calls radeonVtxfmtUnbindContext().
 */
static GLboolean
radeonUnbindContext( __DRIcontextPrivate *driContextPriv )
{
   radeonContextPtr rmesa = (radeonContextPtr) driContextPriv->driverPrivate;

   if (RADEON_DEBUG & DEBUG_DRI)
      fprintf(stderr, "%s ctx %p\n", __FUNCTION__, rmesa->glCtx);

   radeonVtxfmtUnbindContext( rmesa->glCtx );
   return GL_TRUE;
}


/**
 * \brief Open/close fullscreen mode.
 * 
 * \note Fullscreen mode isn't used for much - it could be a way to shrink
 * front/back buffers and get more texture memory if the client has changed the
 * video resolution.
 * 
 * \par
 * Pageflipping is now done automatically whenever there is a single 3D client.
 * 
 * \param driContextPriv DRI specific context data. Not used.
 * 
 * \return always GL_TRUE.
 *
 * This function is a no-op.
 */
static GLboolean
radeonOpenCloseFullScreen( __DRIcontextPrivate *driContextPriv )
{
   return GL_TRUE;
}



void
__driRegisterExtensions( void )
{
   /* See r200 driver for info */
}



/**
 * \brief Initialize the driver specific screen private data.
 *
 * \param sPriv DRI specific screen data.
 * 
 * \return GL_TRUE on success or GL_FALSE on faillure.
 * 
 * Calls radeonCreateScreen() and if it fails calls radeonDestroyScreen()
 * before returning.
 */
static GLboolean
radeonInitDriver( __DRIscreenPrivate *sPriv )
{
   sPriv->private = (void *) radeonCreateScreen( sPriv );
   if ( !sPriv->private ) {
      radeonDestroyScreen( sPriv );
      return GL_FALSE;
   }

   return GL_TRUE;
}


/**
 * \brief Driver interface structure
 *
 * Holds the DRI driver callbacks.
 */
static struct __DriverAPIRec radeonAPI = {
   radeonInitDriver,
   radeonDestroyScreen,
   radeonCreateContext,
   radeonDestroyContext,
   radeonCreateBuffer,
   radeonDestroyBuffer,
   radeonSwapBuffers,
   radeonMakeCurrent,
   radeonUnbindContext,
   radeonOpenCloseFullScreen,
   radeonOpenCloseFullScreen
};



/**
 * \brief Bootstrap function for the driver.
 *
 * The \e __driCreateScreen name is the symbol that libGL.so fetches.
 * 
 * \return pointer to a ::__DRIscreenPrivate structure.
 *
 * Calls __driUtilCreateScreen() with ::radeonAPI.
 */
void *__driCreateScreen(Display *dpy, int scrn, __DRIscreen *psc,
                        int numConfigs, __GLXvisualConfig *config)
{
   __DRIscreenPrivate *psp;
   psp = __driUtilCreateScreen(dpy, scrn, psc, numConfigs, config, &radeonAPI);
   return (void *) psp;
}
