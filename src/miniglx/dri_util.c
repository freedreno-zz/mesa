

#include <assert.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/fb.h>
#include "GL/miniglx.h"
#include "miniglxP.h"


#include "sarea.h"
#include "dri_util.h"


/**
 * \brief Print message to \c stderr if the \c LIBGL_DEBUG environment variable
 * is set.
 * 
 * \note Called from drivers.
 */
void
__driUtilMessage(const char *f, ...)
{
    va_list args;

    if (getenv("LIBGL_DEBUG")) {
        fprintf(stderr, "libGL error: \n");
        va_start(args, f);
        vfprintf(stderr, f, args);
        va_end(args);
        fprintf(stderr, "\n");
    }
}


/*****************************************************************/

/**
 * Return pointer to the #__GLXvisualConfig specified by dpy, scrn and vid.
 * Return NULL if not found.
 */
static __GLXvisualConfig *
__driFindGlxConfig(Display *dpy, int scrn, VisualID vid)
{
    __GLXvisualConfig *glxConfigs;
    int numConfigs, i;

    numConfigs = dpy->numConfigs;
    glxConfigs = dpy->configs;

    for (i = 0; i < numConfigs; i++) {
        if (glxConfigs[i].vid == vid) {
            return glxConfigs + i;
        }
    }
    return NULL;
}


/**
 * This function comes from programs/Xserver/GL/glx/glxcmds.c
 */
static void
__glXFormatGLModes(__GLcontextModes *modes, const __GLXvisualConfig *config)
{
    memset(modes, 0, sizeof(__GLcontextModes));

    modes->rgbMode = (config->rgba != 0);
    modes->colorIndexMode = !(modes->rgbMode);
    modes->doubleBufferMode = (config->doubleBuffer != 0);
    modes->stereoMode = (config->stereo != 0);

    modes->haveAccumBuffer = ((config->accumRedSize +
			       config->accumGreenSize +
			       config->accumBlueSize +
			       config->accumAlphaSize) > 0);
    modes->haveDepthBuffer = (config->depthSize > 0);
    modes->haveStencilBuffer = (config->stencilSize > 0);

    modes->redBits = config->redSize;
    modes->greenBits = config->greenSize;
    modes->blueBits = config->blueSize;
    modes->alphaBits = config->alphaSize;
    modes->redMask = config->redMask;
    modes->greenMask = config->greenMask;
    modes->blueMask = config->blueMask;
    modes->alphaMask = config->alphaMask;
    modes->rgbBits = config->bufferSize;
    modes->indexBits = config->bufferSize;

    modes->accumRedBits = config->accumRedSize;
    modes->accumGreenBits = config->accumGreenSize;
    modes->accumBlueBits = config->accumBlueSize;
    modes->accumAlphaBits = config->accumAlphaSize;
    modes->depthBits = config->depthSize;
    modes->stencilBits = config->stencilSize;

    modes->numAuxBuffers = 0;	/* XXX: should be picked up from the visual */

    modes->level = config->level;
}


/*****************************************************************/

static Bool driUnbindContext(Display *dpy, int scrn,
                             GLXDrawable draw, GLXContext gc,
                             int will_rebind)
{
    __DRIscreen *pDRIScreen;
    __DRIdrawable *pdraw;
    __DRIcontextPrivate *pcp;
    __DRIscreenPrivate *psp;
    __DRIdrawablePrivate *pdp;

    if (gc == NULL || draw == None) 
	return GL_FALSE;

    if (!(pDRIScreen = __glXFindDRIScreen(dpy, scrn))) 
	return GL_FALSE;

    if (!(psp = (__DRIscreenPrivate *)pDRIScreen->private)) 
	return GL_FALSE;

    if (!(pdraw = &draw->driDrawable))
	return GL_FALSE;

    pcp = (__DRIcontextPrivate *)gc->driContext.private;
    pdp = (__DRIdrawablePrivate *)pdraw->private;

    /* Let driver unbind drawable from context */
    (*psp->DriverAPI.UnbindContext)(pcp);

    if (pdp->refcount == 0) 
	return GL_FALSE;

    --pdp->refcount;

    return GL_TRUE;
}


static Bool driBindContext(Display *dpy, int scrn,
                            GLXDrawable draw,
                            GLXContext gc)
{
    __DRIscreen *pDRIScreen;
    __DRIdrawable *pdraw;
    __DRIdrawablePrivate *pdp;
    __DRIscreenPrivate *psp;
    __DRIcontextPrivate *pcp;

    /*
    ** Assume error checking is done properly in glXMakeCurrent before
    ** calling driBindContext.
    */
    if (gc == NULL || draw == None) 
	return GL_FALSE;

    if (!(pDRIScreen = __glXFindDRIScreen(dpy, scrn))) 
	return GL_FALSE;

    if (!(psp = (__DRIscreenPrivate *)pDRIScreen->private)) 
	return GL_FALSE;


    pdraw = &draw->driDrawable;
    pdp = (__DRIdrawablePrivate *) pdraw->private;

    /* Bind the drawable to the context */
    pcp = (__DRIcontextPrivate *)gc->driContext.private;
    pcp->driDrawablePriv = pdp;
    pdp->driContextPriv = pcp;
    pdp->refcount++;

    /* Call device-specific MakeCurrent */
    (*psp->DriverAPI.MakeCurrent)(pcp, pdp, pdp);

    return GL_TRUE;
}



/*****************************************************************/

void __driUtilUpdateDrawableInfo(__DRIdrawablePrivate *pdp)
{
   /* nothing to do, should never be called, but is referenced
    * as an external symbol from client drivers
    */
}

/*****************************************************************/

/**
 * Called directly from glXSwapBuffers().
 */
static void driSwapBuffers( Display *dpy, void *drawablePrivate )
{
    __DRIdrawablePrivate *dPriv = (__DRIdrawablePrivate *) drawablePrivate;
    dPriv->swapBuffers(dPriv);
    (void) dpy;
}


static void driDestroyDrawable(Display *dpy, void *drawablePrivate)
{
    __DRIdrawablePrivate *pdp = (__DRIdrawablePrivate *) drawablePrivate;
    __DRIscreenPrivate *psp = pdp->driScreenPriv;
    int scrn = psp->myNum;

    if (pdp) {
        (*psp->DriverAPI.DestroyBuffer)(pdp);
	if (pdp->pClipRects)
	    free(pdp->pClipRects);
	free(pdp);
    }
}


static void *driCreateDrawable(Display *dpy, int scrn,
                                     GLXDrawable draw,
                                     VisualID vid, __DRIdrawable *pdraw)
{
    __DRIscreen *pDRIScreen;
    __DRIscreenPrivate *psp;
    __DRIdrawablePrivate *pdp;
    __GLXvisualConfig *config;
    __GLcontextModes modes;

    pdp = (__DRIdrawablePrivate *)malloc(sizeof(__DRIdrawablePrivate));
    if (!pdp) {
	return NULL;
    }

    pdp->draw = draw;
    pdp->refcount = 0;
    pdp->pStamp = &pdp->lastStamp; /* cliprects will never change */
    pdp->lastStamp = 0;
    pdp->index = 0;
    pdp->numBackClipRects = 0;
    pdp->pBackClipRects = NULL;
    pdp->display = dpy;
    pdp->screen = scrn;

    /* Initialize with the invarient window dimensions and cliprects here.
     */
    pdp->x = 0;
    pdp->y = 0;
    pdp->w = pdp->draw->w;
    pdp->h = pdp->draw->h;
    pdp->numClipRects = 1;
    pdp->pClipRects = (XF86DRIClipRectPtr) malloc(sizeof(XF86DRIClipRectRec));
    (pdp->pClipRects)[0].x1 = 0;
    (pdp->pClipRects)[0].y1 = 0;
    (pdp->pClipRects)[0].x2 = pdp->draw->w;
    (pdp->pClipRects)[0].y2 = pdp->draw->h;

    if (!(pDRIScreen = __glXFindDRIScreen(dpy, scrn))) {
	free(pdp);
	return NULL;
    } else if (!(psp = (__DRIscreenPrivate *)pDRIScreen->private)) {
	free(pdp);
	return NULL;
    }
    pdp->driScreenPriv = psp;
    pdp->driContextPriv = 0;

    config = __driFindGlxConfig(dpy, scrn, vid);
    if (!config)
        return NULL;

    /* convert GLXvisualConfig struct to GLcontextModes struct */
    __glXFormatGLModes(&modes, config);

    if (!(*psp->DriverAPI.CreateBuffer)(psp, pdp, &modes, GL_FALSE)) {
       free(pdp);
       return NULL;
    }

    pdraw->destroyDrawable = driDestroyDrawable;
    pdraw->swapBuffers = driSwapBuffers;  /* called by glXSwapBuffers() */
    pdp->swapBuffers = psp->DriverAPI.SwapBuffers;

    return (void *) pdp;
}

static __DRIdrawable *driGetDrawable(Display *dpy, GLXDrawable draw,
					 void *screenPrivate)
{
    return &draw->driDrawable;
}


/*****************************************************************/

static void driDestroyContext(Display *dpy, int scrn, void *contextPrivate)
{
    __DRIcontextPrivate  *pcp   = (__DRIcontextPrivate *) contextPrivate;
    __DRIscreenPrivate   *psp = NULL;
    __DRIdrawablePrivate *pdp;

    if (pcp) {
	(*pcp->driScreenPriv->DriverAPI.DestroyContext)(pcp);
        psp = pcp->driDrawablePriv->driScreenPriv;
	if (psp->fd) {
	   printf(">>> drmDestroyContext(0x%x)\n", (int) pcp->hHWContext);
	   drmDestroyContext(psp->fd, pcp->hHWContext);
	}
	free(pcp);
    }
}

static void *driCreateContext(Display *dpy, XVisualInfo *vis,
                              void *sharedPrivate,
                              __DRIcontext *pctx)
{
   __DRIscreen *pDRIScreen;
   __DRIcontextPrivate *pcp;
   __DRIcontextPrivate *pshare = (__DRIcontextPrivate *) sharedPrivate;
   __DRIscreenPrivate *psp;
   __GLXvisualConfig *config;
   __GLcontextModes modes;
   void *shareCtx;

   if (!(pDRIScreen = __glXFindDRIScreen(dpy, 0))) 
      return NULL;
    
   if (!(psp = (__DRIscreenPrivate *)pDRIScreen->private)) 
      return NULL;

   pcp = (__DRIcontextPrivate *)malloc(sizeof(__DRIcontextPrivate));
   if (!pcp) {
      return NULL;
   }

   pcp->display = dpy;
   pcp->driScreenPriv = psp;
   pcp->driDrawablePriv = NULL;

   if (psp->fd) {
      if (drmCreateContext(psp->fd, &pcp->hHWContext)) {
	 fprintf(stderr, ">>> drmCreateContext failed\n");
	 free(pcp);
	 return NULL;
      }
   }


   /* Setup a __GLcontextModes struct corresponding to vis->visualid
    * and create the rendering context.
    */
   config = __driFindGlxConfig(dpy, 0, vis->visualid);
   if (!config)
      return NULL;

   __glXFormatGLModes(&modes, config);
   shareCtx = pshare ? pshare->driverPrivate : NULL;
   if (!(*psp->DriverAPI.CreateContext)(&modes, pcp, shareCtx)) {
      if (psp->fd) 
	 (void) drmDestroyContext(psp->fd, pcp->hHWContext);
      free(pcp);
      return NULL;
   }

   pctx->destroyContext = driDestroyContext;
   pctx->bindContext    = driBindContext;
   pctx->unbindContext  = driUnbindContext;

   return pcp;
}

/*****************************************************************/

static void driDestroyScreen(Display *dpy, int scrn, void *screenPrivate)
{
    __DRIscreenPrivate *psp = (__DRIscreenPrivate *) screenPrivate;
    
    if (psp) {
	if (psp->DriverAPI.DestroyScreen)
	    (*psp->DriverAPI.DestroyScreen)(psp);

	if (psp->fd) 
	   (void)drmClose(psp->fd);

	free(psp->pDevPriv);
	free(psp);
    }
}


__DRIscreenPrivate *
__driUtilCreateScreen(Display *dpy, int scrn, __DRIscreen *psc,
                      int numConfigs, __GLXvisualConfig *config,
                      const struct __DriverAPIRec *driverAPI)
{
   __DRIscreenPrivate *psp;
   char *driverName;
   drmHandle hFB;
   drmMagic magic;

   psp = (__DRIscreenPrivate *)malloc(sizeof(__DRIscreenPrivate));
   if (!psp) {
      return NULL;
   }

   psp->display = dpy;
   psp->myNum = scrn;

   psp->fd = drmOpen(NULL,dpy->pciBusID);
   if (psp->fd < 0) {
      fprintf(stderr, "libGL error: failed to open DRM: %s\n", 
	      strerror(-psp->fd));
      free(psp);
      return NULL;
   }

   {
      drmVersionPtr version = drmGetVersion(psp->fd);
      if (version) {
	 psp->drmMajor = version->version_major;
	 psp->drmMinor = version->version_minor;
	 psp->drmPatch = version->version_patchlevel;
	 drmFreeVersion(version);
      }
      else {
	 fprintf(stderr, "libGL error: failed to get drm version: %s\n", 
		 strerror(-psp->fd));
	 free(psp);
	 return NULL;
      }
   }

   /*
    * Fake various version numbers.
    */
   psp->ddxMajor = 4;
   psp->ddxMinor = 0;
   psp->ddxPatch = 1;
   psp->driMajor = 4;
   psp->driMinor = 1;
   psp->driPatch = 0;

   /* install driver's callback functions */
   memcpy(&psp->DriverAPI, driverAPI, sizeof(struct __DriverAPIRec));

   /*
    * Get device-specific info.  pDevPriv will point to a struct
    * (such as DRIRADEONRec in xfree86/driver/ati/radeon_dri.h)
    * that has information about the screen size, depth, pitch,
    * ancilliary buffers, DRM mmap handles, etc.
    */
   psp->pFB = dpy->FrameBuffer;
   psp->fbOrigin = 0;  
   psp->fbSize = dpy->FrameBufferSize; 
   psp->fbStride = dpy->VarInfo.xres_virtual * dpy->cpp; 
   psp->devPrivSize = dpy->driverClientMsgSize;
   psp->pDevPriv = dpy->driverClientMsg;
   psp->fbWidth = dpy->VarInfo.xres;
   psp->fbHeight = dpy->VarInfo.yres;
   psp->fbBPP = dpy->VarInfo.bits_per_pixel;
   psp->pSAREA = dpy->pSAREA;

   /* Initialize the screen specific GLX driver */
   if (psp->DriverAPI.InitDriver) {
      if (!(*psp->DriverAPI.InitDriver)(psp)) {
	 fprintf(stderr, "libGL error: InitDriver failed\n");
	 free(psp->pDevPriv);
	 (void)drmClose(psp->fd);
	 free(psp);
	 return NULL;
      }
   }

   psc->destroyScreen  = driDestroyScreen;
   psc->createContext  = driCreateContext;
   psc->createDrawable = driCreateDrawable;
   psc->getDrawable    = driGetDrawable;

   return psp;
}



/**
 * Version for drivers without a drm module.
 */
__DRIscreenPrivate *
__driUtilCreateScreenNoDRM(Display *dpy, int scrn, __DRIscreen *psc,
			   int numConfigs, __GLXvisualConfig *config,
			   const struct __DriverAPIRec *driverAPI)
{
    __DRIscreenPrivate *psp;
    char *driverName;

    psp = (__DRIscreenPrivate *)calloc(1, sizeof(__DRIscreenPrivate));
    if (!psp) 
	return NULL;

    psp->ddxMajor = 4;
    psp->ddxMinor = 0;
    psp->ddxPatch = 1;
    psp->driMajor = 4;
    psp->driMinor = 1;
    psp->driPatch = 0;
    psp->display = dpy;
    psp->myNum = scrn;
    psp->fd = 0;
    psp->fbOrigin = 0; 
    psp->fbSize = dpy->FrameBufferSize; 
    psp->fbStride = dpy->VarInfo.xres_virtual;
    psp->fbWidth = dpy->VarInfo.xres;
    psp->fbHeight = dpy->VarInfo.yres;
    psp->fbBPP = dpy->VarInfo.bits_per_pixel;
    psp->pFB = dpy->FrameBuffer;
    psp->devPrivSize = 0;
    psp->pDevPriv = 0;

    /* install driver's callback functions */
    memcpy(&psp->DriverAPI, driverAPI, sizeof(struct __DriverAPIRec));

    /* Initialize the screen specific GLX driver */
    if (psp->DriverAPI.InitDriver) {
	if (!(*psp->DriverAPI.InitDriver)(psp)) {
	    fprintf(stderr, "libGL error: InitDriver failed\n");
	    free(psp->pDevPriv);
	    free(psp);
	    return NULL;
	}
    }

    psc->destroyScreen  = driDestroyScreen;
    psc->createContext  = driCreateContext;
    psc->createDrawable = driCreateDrawable;
    psc->getDrawable    = driGetDrawable;

    return psp;
}


