/* $XFree86: xc/programs/Xserver/GL/dri/dri.c,v 1.35 2002/09/18 18:14:50 martin Exp $ */
/**************************************************************************

Copyright 1998-1999 Precision Insight, Inc., Cedar Park, Texas.
Copyright 2000 VA Linux Systems, Inc.
All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sub license, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice (including the
next paragraph) shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

/*
 * Authors:
 *   Jens Owen <jens@tungstengraphics.com>
 *   Rickard E. (Rik) Faith <faith@valinux.com>
 *
 */

#include "dri.h"
#include "sarea.h"
#include "dristruct.h"
/* #include "xf86.h" */
#include "xf86drm.h"
/* #include "glxserver.h" */


static int DRIScreenPrivIndex = -1;
static int DRIWindowPrivIndex = -1;
static unsigned long DRIGeneration = 0;
static unsigned int DRIDrawableValidationStamp = 0;
static int lockRefCount=0;

				/* Support cleanup for fullscreen mode,
                                   independent of the DRICreateDrawable
                                   resource management. */
static Bool    _DRICloseFullScreen(pointer pResource, XID id);
static RESTYPE DRIFullScreenResType;

static RESTYPE DRIDrawablePrivResType;
static RESTYPE DRIContextPrivResType;



/* Statics used in place of per-screen data:
 */
DRIScreenPrivPtr  __pDRIPriv;



				/* Wrapper just like xf86DrvMsg, but
				   without the verbosity level checking.
				   This will make it easy to turn off some
				   messages later, based on verbosity
				   level. */

static void
DRIDrvMsg(int scrnIndex, MessageType type, const char *format, ...)
{
    va_list     ap;

    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
}

Bool
DRIScreenInit(DRIInfoPtr pDRIInfo, int *pDRMFD)
{
    DRIScreenPrivPtr    pDRIPriv;
    drmContextPtr       reserved;
    int                 reserved_count;
    int                 i, fd, drmWasAvailable;
    Bool                xineramaInCore = FALSE;
    int                 err = 0;

    if (DRIGeneration != serverGeneration) {
	if ((DRIScreenPrivIndex = AllocateScreenPrivateIndex()) < 0)
	    return FALSE;
	DRIGeneration = serverGeneration;
    }

    drmWasAvailable = drmAvailable();

    /* Note that drmOpen will try to load the kernel module, if needed. */
    fd = drmOpen(pDRIInfo->drmDriverName, NULL );
    if (fd < 0) {
        /* failed to open DRM */
        DRIDrvMsg(0, X_INFO,
                  "[drm] drmOpen failed\n");
        return FALSE;
    }

    if (!drmWasAvailable) {
       /* drmOpen loaded the kernel module, print a message to say so */
       DRIDrvMsg(0, X_INFO,
                 "[drm] loaded kernel module for \"%s\" driver\n",
                 pDRIInfo->drmDriverName);
    }

    pDRIPriv = (DRIScreenPrivPtr) xcalloc(1, sizeof(DRIScreenPrivRec));
    if (!pDRIPriv) {
        return FALSE;
    }

    pDRIPriv->drmFD = fd;
    pDRIPriv->directRenderingSupport = TRUE;
    pDRIPriv->pDriverInfo = pDRIInfo;
    pDRIPriv->nrWindows = 0;
    pDRIPriv->fullscreen = NULL;

    pDRIPriv->grabbedDRILock = FALSE;
    pDRIPriv->drmSIGIOHandlerInstalled = FALSE;

    if ((err = drmSetBusid(pDRIPriv->drmFD, pDRIPriv->pDriverInfo->busIdString)) < 0) {
	pDRIPriv->directRenderingSupport = FALSE;
	drmClose(pDRIPriv->drmFD);
        DRIDrvMsg(0, X_INFO,
                  "[drm] drmSetBusid failed (%d, %s), %s\n",
                  pDRIPriv->drmFD, pDRIPriv->pDriverInfo->busIdString, strerror(-err));
	return FALSE;
    }

    *pDRMFD = pDRIPriv->drmFD;
    DRIDrvMsg(0, X_INFO,
	      "[drm] created \"%s\" driver at busid \"%s\"\n",
	      pDRIPriv->pDriverInfo->drmDriverName,
	      pDRIPriv->pDriverInfo->busIdString);

    if (drmAddMap( pDRIPriv->drmFD,
		   0,
		   pDRIPriv->pDriverInfo->SAREASize,
		   DRM_SHM,
		   DRM_CONTAINS_LOCK,
		   &pDRIPriv->hSAREA) < 0)
    {
	pDRIPriv->directRenderingSupport = FALSE;
	drmClose(pDRIPriv->drmFD);
        DRIDrvMsg(0, X_INFO,
                  "[drm] drmAddMap failed\n");
	return FALSE;
    }
    DRIDrvMsg(0, X_INFO,
	      "[drm] added %d byte SAREA at 0x%08lx\n",
	      pDRIPriv->pDriverInfo->SAREASize, pDRIPriv->hSAREA);

    if (drmMap( pDRIPriv->drmFD,
		pDRIPriv->hSAREA,
		pDRIPriv->pDriverInfo->SAREASize,
		(drmAddressPtr)(&pDRIPriv->pSAREA)) < 0)
    {
	pDRIPriv->directRenderingSupport = FALSE;
	drmClose(pDRIPriv->drmFD);
        DRIDrvMsg(0, X_INFO,
                  "[drm] drmMap failed\n");
	return FALSE;
    }
    memset(pDRIPriv->pSAREA, 0, pDRIPriv->pDriverInfo->SAREASize);
    DRIDrvMsg(0, X_INFO, "[drm] mapped SAREA 0x%08lx to %p\n",
	      pDRIPriv->hSAREA, pDRIPriv->pSAREA);

    if (drmAddMap( pDRIPriv->drmFD,
		   (drmHandle)pDRIPriv->pDriverInfo->frameBufferPhysicalAddress,
		   pDRIPriv->pDriverInfo->frameBufferSize,
		   DRM_FRAME_BUFFER,
		   0,
		   &pDRIPriv->hFrameBuffer) < 0)
    {
	pDRIPriv->directRenderingSupport = FALSE;
	drmUnmap(pDRIPriv->pSAREA, pDRIPriv->pDriverInfo->SAREASize);
	drmClose(pDRIPriv->drmFD);
        DRIDrvMsg(0, X_INFO,
                  "[drm] drmAddMap failed\n");
	return FALSE;
    }
    DRIDrvMsg(0, X_INFO, "[drm] framebuffer handle = 0x%08lx\n",
	      pDRIPriv->hFrameBuffer);

				/* Add tags for reserved contexts */
    if ((reserved = drmGetReservedContextList(pDRIPriv->drmFD,
					      &reserved_count))) {
	int  i;
	void *tag;

	for (i = 0; i < reserved_count; i++) {
	    tag = DRICreateContextPrivFromHandle(pScreen,
						 reserved[i],
						 DRI_CONTEXT_RESERVED);
	    drmAddContextTag(pDRIPriv->drmFD, reserved[i], tag);
	}
	drmFreeReservedContextList(reserved);
	DRIDrvMsg(0, X_INFO,
		  "[drm] added %d reserved context%s for kernel\n",
		  reserved_count, reserved_count > 1 ? "s" : "");
    }

    /* validate max drawable table entry set by driver */
    if ((pDRIPriv->pDriverInfo->maxDrawableTableEntry <= 0) ||
        (pDRIPriv->pDriverInfo->maxDrawableTableEntry > SAREA_MAX_DRAWABLES)) {
	    DRIDrvMsg(0, X_ERROR,
		      "Invalid max drawable table size set by driver: %d\n",
		      pDRIPriv->pDriverInfo->maxDrawableTableEntry);
    }

    /* Initialize drawable tables (screen private and SAREA) */
    for( i=0; i < pDRIPriv->pDriverInfo->maxDrawableTableEntry; i++) {
	pDRIPriv->DRIDrawables[i] = NULL;
	pDRIPriv->pSAREA->drawableTable[i].stamp = 0;
	pDRIPriv->pSAREA->drawableTable[i].flags = 0;
    }

    return TRUE;
}

Bool
DRIFinishScreenInit( void )
{
    DRIScreenPrivPtr  pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    DRIInfoPtr        pDRIInfo = pDRIPriv->pDriverInfo;
    DRIContextFlags   flags    = 0;
    DRIContextPrivPtr pDRIContextPriv;

				/* Set up flags for DRICreateContextPriv */
    switch (pDRIInfo->driverSwapMethod) {
    case DRI_KERNEL_SWAP:    flags = DRI_CONTEXT_2DONLY;    break;
    case DRI_HIDE_X_CONTEXT: flags = DRI_CONTEXT_PRESERVED; break;
    }

    if (!(pDRIContextPriv = DRICreateContextPriv(pScreen,
						 &pDRIPriv->myContext,
						 flags))) {
	DRIDrvMsg(0, X_ERROR,
		  "failed to create server context\n");
	return FALSE;
    }
    pDRIPriv->myContextPriv = pDRIContextPriv;

    DRIDrvMsg(0, X_INFO,
	      "X context handle = 0x%08lx\n", pDRIPriv->myContext);

    /* Now that we have created the X server's context, we can grab the
     * hardware lock for the X server.
     */
    DRILock(pScreen, 0);
    pDRIPriv->grabbedDRILock = TRUE;

    /* pointers so that we can prevent memory leaks later */
    pDRIPriv->hiddenContextStore    = NULL;
    pDRIPriv->partial3DContextStore = NULL;



    DRIDrvMsg(0, X_INFO, "[DRI] installation complete\n");

    return TRUE;
}

void
DRICloseScreen( void )
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    DRIInfoPtr       pDRIInfo;
    drmContextPtr    reserved;
    int              reserved_count;

    if (pDRIPriv && pDRIPriv->directRenderingSupport) {

        pDRIInfo = pDRIPriv->pDriverInfo;


	if (pDRIPriv->drmSIGIOHandlerInstalled) {
	    if (!drmRemoveSIGIOHandler(pDRIPriv->drmFD)) {
		DRIDrvMsg(0, X_ERROR,
			  "[drm] failed to remove DRM signal handler\n");
	    }
	}

	if (!DRIDestroyContextPriv(pDRIPriv->myContextPriv)) {
	    DRIDrvMsg(0, X_ERROR,
		      "failed to destroy server context\n");
	}

				/* Remove tags for reserved contexts */
	if ((reserved = drmGetReservedContextList(pDRIPriv->drmFD,
						  &reserved_count))) {
	    int  i;

	    for (i = 0; i < reserved_count; i++) {
		DRIDestroyContextPriv(drmGetContextTag(pDRIPriv->drmFD,
						       reserved[i]));
	    }
	    drmFreeReservedContextList(reserved);
	    DRIDrvMsg(0, X_INFO,
		      "[drm] removed %d reserved context%s for kernel\n",
		      reserved_count, reserved_count > 1 ? "s" : "");
	}

	/* Make sure signals get unblocked etc. */
	drmUnlock(pDRIPriv->drmFD, pDRIPriv->myContext);
	lockRefCount=0;
	DRIDrvMsg(0, X_INFO,
		  "[drm] unmapping %d bytes of SAREA 0x%08lx at %p\n",
		  pDRIInfo->SAREASize,
		  pDRIPriv->hSAREA,
		  pDRIPriv->pSAREA);
	if (drmUnmap(pDRIPriv->pSAREA, pDRIInfo->SAREASize)) {
	    DRIDrvMsg(0, X_ERROR,
		      "[drm] unable to unmap %d bytes"
		      " of SAREA 0x%08lx at %p\n",
		      pDRIInfo->SAREASize,
		      pDRIPriv->hSAREA,
		      pDRIPriv->pSAREA);
	}

	drmClose(pDRIPriv->drmFD);

	xfree(pDRIPriv);
	pScreen->devPrivates[DRIScreenPrivIndex].ptr = NULL;
    }
}


Bool
DRIOpenConnection(drmHandlePtr hSAREA, char **busIdString)
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    *hSAREA           = pDRIPriv->hSAREA;
    *busIdString      = pDRIPriv->pDriverInfo->busIdString;

    return TRUE;
}

Bool
DRIAuthConnection(drmMagic magic)
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    if (drmAuthMagic(pDRIPriv->drmFD, magic)) return FALSE;
    return TRUE;
}

Bool
DRICloseConnection( void )
{
    return TRUE;
}

Bool
DRIGetClientDriverName(ScreenPtr pScreen,
                       int *ddxDriverMajorVersion,
                       int *ddxDriverMinorVersion,
                       int *ddxDriverPatchVersion,
                       char **clientDriverName)
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    *ddxDriverMajorVersion = pDRIPriv->pDriverInfo->ddxDriverMajorVersion;
    *ddxDriverMinorVersion = pDRIPriv->pDriverInfo->ddxDriverMinorVersion;
    *ddxDriverPatchVersion = pDRIPriv->pDriverInfo->ddxDriverPatchVersion;
    *clientDriverName      = pDRIPriv->pDriverInfo->clientDriverName;

    return TRUE;
}

/* DRICreateContextPriv and DRICreateContextPrivFromHandle are helper
   functions that layer on drmCreateContext and drmAddContextTag.

   DRICreateContextPriv always creates a kernel drmContext and then calls
   DRICreateContextPrivFromHandle to create a DRIContextPriv structure for
   DRI tracking.  For the SIGIO handler, the drmContext is associated with
   DRIContextPrivPtr.  Any special flags are stored in the DRIContextPriv
   area and are passed to the kernel (if necessary).

   DRICreateContextPriv returns a pointer to newly allocated
   DRIContextPriv, and returns the kernel drmContext in pHWContext. */

DRIContextPrivPtr
DRICreateContextPriv(ScreenPtr pScreen,
		     drmContextPtr pHWContext,
		     DRIContextFlags flags)
{
    DRIScreenPrivPtr  pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    if (drmCreateContext(pDRIPriv->drmFD, pHWContext)) {
	return NULL;
    }

    return DRICreateContextPrivFromHandle(pScreen, *pHWContext, flags);
}

DRIContextPrivPtr
DRICreateContextPrivFromHandle(ScreenPtr pScreen,
			       drmContext hHWContext,
			       DRIContextFlags flags)
{
    DRIScreenPrivPtr  pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    DRIContextPrivPtr pDRIContextPriv;
    int 	      contextPrivSize;

    contextPrivSize = sizeof(DRIContextPrivRec) +
			    pDRIPriv->pDriverInfo->contextSize;
    if (!(pDRIContextPriv = xcalloc(1, contextPrivSize))) {
	return NULL;
    }
    pDRIContextPriv->pContextStore = (void *)(pDRIContextPriv + 1);

    drmAddContextTag(pDRIPriv->drmFD, hHWContext, pDRIContextPriv);

    pDRIContextPriv->hwContext = hHWContext;
    pDRIContextPriv->pScreen   = pScreen;
    pDRIContextPriv->flags     = flags;
    pDRIContextPriv->valid3D   = FALSE;

    if (flags & DRI_CONTEXT_2DONLY) {
	if (drmSetContextFlags(pDRIPriv->drmFD,
			       hHWContext,
			       DRM_CONTEXT_2DONLY)) {
	    DRIDrvMsg(0, X_ERROR,
		      "[drm] failed to set 2D context flag\n");
	    DRIDestroyContextPriv(pDRIContextPriv);
	    return NULL;
	}
    }
    if (flags & DRI_CONTEXT_PRESERVED) {
	if (drmSetContextFlags(pDRIPriv->drmFD,
			       hHWContext,
			       DRM_CONTEXT_PRESERVED)) {
	    DRIDrvMsg(0, X_ERROR,
		      "[drm] failed to set preserved flag\n");
	    DRIDestroyContextPriv(pDRIContextPriv);
	    return NULL;
	}
    }
    return pDRIContextPriv;
}

Bool
DRIDestroyContextPriv(DRIContextPrivPtr pDRIContextPriv)
{
    DRIScreenPrivPtr pDRIPriv;

    if (!pDRIContextPriv) return TRUE;

    pDRIPriv = DRI_SCREEN_PRIV(pDRIContextPriv->pScreen);

    if (!(pDRIContextPriv->flags & DRI_CONTEXT_RESERVED)) {
				/* Don't delete reserved contexts from
                                   kernel area -- the kernel manages its
                                   reserved contexts itself. */
	if (drmDestroyContext(pDRIPriv->drmFD, pDRIContextPriv->hwContext))
	    return FALSE;
    }

				/* Remove the tag last to prevent a race
                                   condition where the context has pending
                                   buffers.  The context can't be re-used
                                   while in this thread, but buffers can be
                                   dispatched asynchronously. */
    drmDelContextTag(pDRIPriv->drmFD, pDRIContextPriv->hwContext);
    xfree(pDRIContextPriv);
    return TRUE;
}


Bool
DRICreateContext(VisualPtr visual,
                 XID context, drmContextPtr pHWContext)
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    __GLXscreenInfo *pGLXScreen = &__glXActiveScreens[0];
    __GLXvisualConfig *pGLXVis = pGLXScreen->pGlxVisual;
    void **pVisualConfigPriv = pGLXScreen->pVisualPriv;
    DRIContextPrivPtr pDRIContextPriv;
    void *contextStore;
    int visNum;

    /* Find the GLX visual associated with the one requested */
    for (visNum = 0;
	 visNum < pGLXScreen->numVisuals;
	 visNum++, pGLXVis++, pVisualConfigPriv++)
	if (pGLXVis->vid == visual->vid)
	    break;
    if (visNum == pGLXScreen->numVisuals) {
	/* No matching GLX visual found */
	return FALSE;
    }

    if (!(pDRIContextPriv = DRICreateContextPriv(pScreen, pHWContext, 0))) {
	return FALSE;
    }

    contextStore = DRIGetContextStore(pDRIContextPriv);
    if (pDRIPriv->pDriverInfo->CreateContext) {
	if (!((*pDRIPriv->pDriverInfo->CreateContext)(pScreen, visual,
		*pHWContext, *pVisualConfigPriv,
		(DRIContextType)(long)contextStore))) {
	    DRIDestroyContextPriv(pDRIContextPriv);
	    return FALSE;
	}
    }

    /* track this in case the client dies before cleanup */
    AddResource(context, DRIContextPrivResType, (pointer)pDRIContextPriv);

    return TRUE;
}

Bool
DRIDestroyContext(XID context)
{
    FreeResourceByType(context, DRIContextPrivResType, FALSE);

    return TRUE;
}

/* DRIContextPrivDelete is called by the resource manager. */
Bool
DRIContextPrivDelete(pointer pResource, XID id)
{
    DRIContextPrivPtr pDRIContextPriv = (DRIContextPrivPtr)pResource;
    DRIScreenPrivPtr pDRIPriv;
    void *contextStore;

    pDRIPriv = DRI_SCREEN_PRIV(pDRIContextPriv->pScreen);
    if (pDRIPriv->pDriverInfo->DestroyContext) {
      contextStore = DRIGetContextStore(pDRIContextPriv);
      pDRIPriv->pDriverInfo->DestroyContext(pDRIContextPriv->pScreen,
					    pDRIContextPriv->hwContext,
					    (DRIContextType)(long)contextStore);
    }
    return DRIDestroyContextPriv(pDRIContextPriv);
}




Bool
DRICreateDrawable(Drawable id,
                  DrawablePtr pDrawable, drmDrawablePtr hHWDrawable)
{
    DRIScreenPrivPtr	pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    DRIDrawablePrivPtr	pDRIDrawablePriv;
    WindowPtr		pWin;

    if (pDrawable->type == DRAWABLE_WINDOW) {
	pWin = (WindowPtr)pDrawable;
	if ((pDRIDrawablePriv = DRI_DRAWABLE_PRIV_FROM_WINDOW(pWin))) {
	    pDRIDrawablePriv->refCount++;
	}
	else {
	    /* allocate a DRI Window Private record */
	    if (!(pDRIDrawablePriv = xalloc(sizeof(DRIDrawablePrivRec)))) {
		return FALSE;
	    }

	    /* Only create a drmDrawable once */
	    if (drmCreateDrawable(pDRIPriv->drmFD, hHWDrawable)) {
		xfree(pDRIDrawablePriv);
		return FALSE;
	    }

	    /* add it to the list of DRI drawables for this screen */
	    pDRIDrawablePriv->hwDrawable = *hHWDrawable;
	    pDRIDrawablePriv->pScreen = pScreen;
	    pDRIDrawablePriv->refCount = 1;
	    pDRIDrawablePriv->drawableIndex = -1;

	    /* save private off of preallocated index */
	    pWin->devPrivates[DRIWindowPrivIndex].ptr =
						(pointer)pDRIDrawablePriv;

	    switch (++pDRIPriv->nrWindows) {
	    case 1:
	       DRITransitionTo3d( pScreen );
	       break;
	    case 2:
	       DRITransitionToSharedBuffers( pScreen );
	       break;
	    default:
	       break;
	    }

	    /* track this in case this window is destroyed */
	    AddResource(id, DRIDrawablePrivResType, (pointer)pWin);
	}
    }
    else { /* pixmap (or for GLX 1.3, a PBuffer) */
	/* NOT_DONE */
	return FALSE;
    }

    return TRUE;
}

Bool
DRIDestroyDrawable(Drawable id, DrawablePtr pDrawable)
{
    DRIDrawablePrivPtr	pDRIDrawablePriv;
    WindowPtr		pWin;


    if (pDrawable->type == DRAWABLE_WINDOW) {
	pWin = (WindowPtr)pDrawable;
	pDRIDrawablePriv = DRI_DRAWABLE_PRIV_FROM_WINDOW(pWin);
	pDRIDrawablePriv->refCount--;
	if (pDRIDrawablePriv->refCount <= 0) {
	    /* This calls back DRIDrawablePrivDelete which frees private area */
	    FreeResourceByType(id, DRIDrawablePrivResType, FALSE);
	}
    }
    else { /* pixmap (or for GLX 1.3, a PBuffer) */
	/* NOT_DONE */
	return FALSE;
    }

    return TRUE;
}

Bool
DRIDrawablePrivDelete(pointer pResource, XID id)
{
    DrawablePtr		pDrawable = (DrawablePtr)pResource;
    DRIScreenPrivPtr	pDRIPriv = DRI_SCREEN_PRIV(pDrawable->pScreen);
    DRIDrawablePrivPtr	pDRIDrawablePriv;
    WindowPtr		pWin;

    if (pDrawable->type == DRAWABLE_WINDOW) {
	pWin = (WindowPtr)pDrawable;
	pDRIDrawablePriv = DRI_DRAWABLE_PRIV_FROM_WINDOW(pWin);

	if (pDRIDrawablePriv->drawableIndex != -1) {
	    /* bump stamp to force outstanding 3D requests to resync */
	    pDRIPriv->pSAREA->drawableTable[pDRIDrawablePriv->drawableIndex].stamp
		= DRIDrawableValidationStamp++;

	    /* release drawable table entry */
	    pDRIPriv->DRIDrawables[pDRIDrawablePriv->drawableIndex] = NULL;
	}

	if (drmDestroyDrawable(pDRIPriv->drmFD,
			       pDRIDrawablePriv->hwDrawable)) {
	    return FALSE;
	}
	xfree(pDRIDrawablePriv);
	pWin->devPrivates[DRIWindowPrivIndex].ptr = NULL;
    }
    else { /* pixmap (or for GLX 1.3, a PBuffer) */
	/* NOT_DONE */
	return FALSE;
    }

    return TRUE;
}

Bool
DRIGetDrawableInfo(ScreenPtr pScreen,
                   DrawablePtr pDrawable,
                   unsigned int* index,
                   unsigned int* stamp,
                   int* X,
                   int* Y,
                   int* W,
                   int* H,
                   int* numClipRects,
                   XF86DRIClipRectPtr* pClipRects,
                   int* backX,
                   int* backY,
                   int* numBackClipRects,
                   XF86DRIClipRectPtr* pBackClipRects)
{
    DRIScreenPrivPtr    pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    DRIDrawablePrivPtr	pDRIDrawablePriv, pOldDrawPriv;
    WindowPtr		pWin, pOldWin;
    int			i;

    printf("maxDrawableTableEntry = %d\n", pDRIPriv->pDriverInfo->maxDrawableTableEntry);

    if (pDrawable->type == DRAWABLE_WINDOW) {
	pWin = (WindowPtr)pDrawable;
	if ((pDRIDrawablePriv = DRI_DRAWABLE_PRIV_FROM_WINDOW(pWin))) {

	    /* Manage drawable table */
	    if (pDRIDrawablePriv->drawableIndex == -1) { /* load SAREA table */

		/* Search table for empty entry */
		i = 0;
		while (i < pDRIPriv->pDriverInfo->maxDrawableTableEntry) {
		    if (!(pDRIPriv->DRIDrawables[i])) {
			pDRIPriv->DRIDrawables[i] = pDrawable;
			pDRIDrawablePriv->drawableIndex = i;
			pDRIPriv->pSAREA->drawableTable[i].stamp =
					    DRIDrawableValidationStamp++;
			break;
		    }
		    i++;
		}

		/* Search table for oldest entry */
		if (i == pDRIPriv->pDriverInfo->maxDrawableTableEntry) {
                    unsigned int oldestStamp = ~0;
                    int oldestIndex = 0;
		    i = pDRIPriv->pDriverInfo->maxDrawableTableEntry;
		    while (i--) {
			if (pDRIPriv->pSAREA->drawableTable[i].stamp <
								oldestStamp) {
			    oldestIndex = i;
			    oldestStamp =
				pDRIPriv->pSAREA->drawableTable[i].stamp;
			}
		    }
		    pDRIDrawablePriv->drawableIndex = oldestIndex;

		    /* release oldest drawable table entry */
		    pOldWin = (WindowPtr)pDRIPriv->DRIDrawables[oldestIndex];
		    pOldDrawPriv = DRI_DRAWABLE_PRIV_FROM_WINDOW(pOldWin);
		    pOldDrawPriv->drawableIndex = -1;

		    /* claim drawable table entry */
		    pDRIPriv->DRIDrawables[oldestIndex] = pDrawable;

		    /* validate SAREA entry */
		    pDRIPriv->pSAREA->drawableTable[oldestIndex].stamp =
					DRIDrawableValidationStamp++;

		    /* check for stamp wrap around */
		    if (oldestStamp > DRIDrawableValidationStamp) {

			/* walk SAREA table and invalidate all drawables */
			for( i=0;
                             i < pDRIPriv->pDriverInfo->maxDrawableTableEntry;
                             i++) {
				pDRIPriv->pSAREA->drawableTable[i].stamp =
					DRIDrawableValidationStamp++;
			}
		    }
		}

		/* If the driver wants to be notified when the index is
		 * set for a drawable, let it know now.
		 */
		if (pDRIPriv->pDriverInfo->SetDrawableIndex)
			pDRIPriv->pDriverInfo->SetDrawableIndex(pWin,
				pDRIDrawablePriv->drawableIndex);

		/* reinit drawable ID if window is visible */
		if ((pWin->viewable) &&
		    (pDRIPriv->pDriverInfo->bufferRequests != DRI_NO_WINDOWS))
		{
		    (*pDRIPriv->pDriverInfo->InitBuffers)(pWin,
			    &pWin->clipList, pDRIDrawablePriv->drawableIndex);
		}
	    }

	    *index = pDRIDrawablePriv->drawableIndex;
	    *stamp = pDRIPriv->pSAREA->drawableTable[*index].stamp;
	    *X = (int)(pWin->drawable.x);
	    *Y = (int)(pWin->drawable.y);
#if 0
	    *W = (int)(pWin->winSize.extents.x2 - pWin->winSize.extents.x1);
	    *H = (int)(pWin->winSize.extents.y2 - pWin->winSize.extents.y1);
#endif
	    *W = (int)(pWin->drawable.width);
	    *H = (int)(pWin->drawable.height);
	    *numClipRects = REGION_NUM_RECTS(&pWin->clipList);
	    *pClipRects = (XF86DRIClipRectPtr)REGION_RECTS(&pWin->clipList);

	    if (!*numClipRects && pDRIPriv->fullscreen) {
				/* use fake full-screen clip rect */
		pDRIPriv->fullscreen_rect.x1 = *X;
		pDRIPriv->fullscreen_rect.y1 = *Y;
		pDRIPriv->fullscreen_rect.x2 = *X + *W;
		pDRIPriv->fullscreen_rect.y2 = *Y + *H;

		*numClipRects = 1;
		*pClipRects   = &pDRIPriv->fullscreen_rect;
	    }

	    *backX = *X;
	    *backY = *Y;

	    if (pDRIPriv->nrWindows == 1 && *numClipRects) {
	       /* Use a single cliprect. */

	       int x0 = *X;
	       int y0 = *Y;
	       int x1 = x0 + *W;
	       int y1 = y0 + *H;

	       if (x0 < 0) x0 = 0;
	       if (y0 < 0) y0 = 0;
	       if (x1 > pScreen->width-1) x1 = pScreen->width-1;
	       if (y1 > pScreen->height-1) y1 = pScreen->height-1;

	       pDRIPriv->private_buffer_rect.x1 = x0;
	       pDRIPriv->private_buffer_rect.y1 = y0;
	       pDRIPriv->private_buffer_rect.x2 = x1;
	       pDRIPriv->private_buffer_rect.y2 = y1;

	       *numBackClipRects = 1;
	       *pBackClipRects = &(pDRIPriv->private_buffer_rect);
	    } else {
	       /* Use the frontbuffer cliprects for back buffers.  */
	       *numBackClipRects = 0;
	       *pBackClipRects = 0;
	    }
	}
	else {
	    /* Not a DRIDrawable */
	    return FALSE;
	}
    }
    else { /* pixmap (or for GLX 1.3, a PBuffer) */
	/* NOT_DONE */
	return FALSE;
    }

    return TRUE;
}

Bool
DRIGetDeviceInfo(ScreenPtr pScreen,
                 drmHandlePtr hFrameBuffer,
                 int* fbOrigin,
                 int* fbSize,
                 int* fbStride,
                 int* devPrivateSize,
                 void** pDevPrivate)
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    *hFrameBuffer = pDRIPriv->hFrameBuffer;
    *fbOrigin = 0;
    *fbSize = pDRIPriv->pDriverInfo->frameBufferSize;
    *fbStride = pDRIPriv->pDriverInfo->frameBufferStride;
    *devPrivateSize = pDRIPriv->pDriverInfo->devPrivateSize;
    *pDevPrivate = pDRIPriv->pDriverInfo->devPrivate;

    return TRUE;
}

DRIInfoPtr
DRICreateInfoRec(void)
{
    DRIInfoPtr inforec = (DRIInfoPtr)xcalloc(1, sizeof(DRIInfoRec));
    if (!inforec) return NULL;

    /* Initialize defaults */
    inforec->busIdString = NULL;

    /* Wrapped function defaults */
    inforec->wrap.WakeupHandler         = DRIDoWakeupHandler;
    inforec->wrap.BlockHandler          = DRIDoBlockHandler;
    inforec->wrap.WindowExposures       = DRIWindowExposures;
    inforec->wrap.CopyWindow            = DRICopyWindow;
    inforec->wrap.ValidateTree          = DRIValidateTree;
    inforec->wrap.PostValidateTree      = DRIPostValidateTree;
    inforec->wrap.ClipNotify            = DRIClipNotify;
    inforec->wrap.AdjustFrame           = DRIAdjustFrame;

    inforec->TransitionTo2d = 0;
    inforec->TransitionTo3d = 0;
    inforec->SetDrawableIndex = 0;

    return inforec;
}

void
DRIDestroyInfoRec(DRIInfoPtr DRIInfo)
{
    if (DRIInfo->busIdString) xfree(DRIInfo->busIdString);
    xfree((char*)DRIInfo);
}



void* 
DRIGetContextStore(DRIContextPrivPtr context)
{
    return((void *)context->pContextStore);
}


void
DRILock(int flags)
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    if(!pDRIPriv) return;

    if (!lockRefCount)
        DRM_LOCK(pDRIPriv->drmFD, pDRIPriv->pSAREA, pDRIPriv->myContext, flags);
    lockRefCount++;
}

void
DRIUnlock( void )
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    if(!pDRIPriv) return;

    if (lockRefCount > 0) {
        lockRefCount--;
    }
    else {
        ErrorF("DRIUnlock called when not locked\n");
        return;
    }
    if (!lockRefCount)
        DRM_UNLOCK(pDRIPriv->drmFD, pDRIPriv->pSAREA, pDRIPriv->myContext);
}

void *
DRIGetSAREAPrivate( void )
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    if (!pDRIPriv) return 0;

    return (void *)(((char*)pDRIPriv->pSAREA)+sizeof(XF86DRISAREARec));
}


void
DRIQueryVersion(int *majorVersion,
                int *minorVersion,
                int *patchVersion)
{
    *majorVersion = XF86DRI_MAJOR_VERSION;
    *minorVersion = XF86DRI_MINOR_VERSION;
    *patchVersion = XF86DRI_PATCH_VERSION;
}

/**************************************************************************
**************************************************************************/

static void TRACE(const char *format, ...)
{
   if (1) {
      va_list     ap;
      va_start(ap, format);
      vfprintf( stderr, format, ap );
      va_end(ap);
   }
}


Bool XF86DRIQueryVersion(dpy, majorVersion, minorVersion, patchVersion)
    void* dpy;
    int* majorVersion; 
    int* minorVersion;
    int* patchVersion;
{
    *majorVersion = XF86DRI_MAJOR_VERSION;
    *minorVersion = XF86DRI_MINOR_VERSION;
    *patchVersion = XF86DRI_PATCH_VERSION;
    TRACE("QueryVersion\n");
    return True;
}

Bool XF86DRIQueryDirectRenderingCapable(dpy, screen, isCapable)
    void* dpy;
    int screen;
    Bool* isCapable;
{
    TRACE("QueryDirectRenderingCapable... return True\n");
    *isCapable = True;
    return True;
}

Bool XF86DRIOpenConnection(dpy, screen, hSAREA, busIdString)
    void* dpy;
    int screen;
    drmHandlePtr hSAREA;
    char **busIdString;
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    *hSAREA           = pDRIPriv->hSAREA;
    *busIdString      = strdup(pDRIPriv->pDriverInfo->busIdString);

    TRACE("OpenConnection... return True\n");
    return True;
}

Bool XF86DRIAuthConnection(dpy, screen, magic)
    void* dpy;
    int screen;
    drmMagic magic;
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    if (drmAuthMagic(pDRIPriv->drmFD, magic)) return FALSE;
    return TRUE;
}

Bool XF86DRICloseConnection(dpy, screen)
    void* dpy;
    int screen;
{
    return True;
}

Bool XF86DRIGetClientDriverName(dpy, screen, ddxDriverMajorVersion, 
	ddxDriverMinorVersion, ddxDriverPatchVersion, clientDriverName)
    void* dpy;
    int screen;
    int* ddxDriverMajorVersion;
    int* ddxDriverMinorVersion;
    int* ddxDriverPatchVersion;
    char** clientDriverName;
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    *ddxDriverMajorVersion = pDRIPriv->pDriverInfo->ddxDriverMajorVersion;
    *ddxDriverMinorVersion = pDRIPriv->pDriverInfo->ddxDriverMinorVersion;
    *ddxDriverPatchVersion = pDRIPriv->pDriverInfo->ddxDriverPatchVersion;
    *clientDriverName      = strdup(pDRIPriv->pDriverInfo->clientDriverName);

    return TRUE;
}
DRIContextPrivPtr
DRICreateContextPriv(ScreenPtr pScreen,
		     drmContextPtr pHWContext,
		     DRIContextFlags flags)
{
    DRIScreenPrivPtr  pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    if (drmCreateContext(pDRIPriv->drmFD, pHWContext)) {
	return NULL;
    }

    return DRICreateContextPrivFromHandle(pScreen, *pHWContext, flags);
}

DRIContextPrivPtr
DRICreateContextPrivFromHandle(ScreenPtr pScreen,
			       drmContext hHWContext,
			       DRIContextFlags flags)
{
    DRIScreenPrivPtr  pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    DRIContextPrivPtr pDRIContextPriv;
    int 	      contextPrivSize;

    contextPrivSize = sizeof(DRIContextPrivRec) +
			    pDRIPriv->pDriverInfo->contextSize;
    if (!(pDRIContextPriv = xcalloc(1, contextPrivSize))) {
	return NULL;
    }
    pDRIContextPriv->pContextStore = (void *)(pDRIContextPriv + 1);

    drmAddContextTag(pDRIPriv->drmFD, hHWContext, pDRIContextPriv);

    pDRIContextPriv->hwContext = hHWContext;
    pDRIContextPriv->pScreen   = pScreen;
    pDRIContextPriv->flags     = flags;
    pDRIContextPriv->valid3D   = FALSE;

    if (flags & DRI_CONTEXT_2DONLY) {
	if (drmSetContextFlags(pDRIPriv->drmFD,
			       hHWContext,
			       DRM_CONTEXT_2DONLY)) {
	    DRIDrvMsg(0, X_ERROR,
		      "[drm] failed to set 2D context flag\n");
	    DRIDestroyContextPriv(pDRIContextPriv);
	    return NULL;
	}
    }
    if (flags & DRI_CONTEXT_PRESERVED) {
	if (drmSetContextFlags(pDRIPriv->drmFD,
			       hHWContext,
			       DRM_CONTEXT_PRESERVED)) {
	    DRIDrvMsg(0, X_ERROR,
		      "[drm] failed to set preserved flag\n");
	    DRIDestroyContextPriv(pDRIContextPriv);
	    return NULL;
	}
    }
    return pDRIContextPriv;
}

Bool
DRICreateContext(ScreenPtr pScreen, VisualPtr visual,
                 XID context, drmContextPtr pHWContext)
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    __GLXscreenInfo *pGLXScreen = &__glXActiveScreens[0];
    __GLXvisualConfig *pGLXVis = pGLXScreen->pGlxVisual;
    void **pVisualConfigPriv = pGLXScreen->pVisualPriv;
    DRIContextPrivPtr pDRIContextPriv;
    void *contextStore;
    int visNum;

    /* Find the GLX visual associated with the one requested */
    for (visNum = 0;
	 visNum < pGLXScreen->numVisuals;
	 visNum++, pGLXVis++, pVisualConfigPriv++)
	if (pGLXVis->vid == visual->vid)
	    break;
    if (visNum == pGLXScreen->numVisuals) {
	/* No matching GLX visual found */
	return FALSE;
    }

    if (!(pDRIContextPriv = DRICreateContextPriv(pScreen, pHWContext, 0))) {
	return FALSE;
    }

    contextStore = DRIGetContextStore(pDRIContextPriv);
    if (pDRIPriv->pDriverInfo->CreateContext) {
	if (!((*pDRIPriv->pDriverInfo->CreateContext)(pScreen, visual,
		*pHWContext, *pVisualConfigPriv,
		(DRIContextType)(long)contextStore))) {
	    DRIDestroyContextPriv(pDRIContextPriv);
	    return FALSE;
	}
    }

    /* track this in case the client dies before cleanup */
    AddResource(context, DRIContextPrivResType, (pointer)pDRIContextPriv);

    return TRUE;
}




Bool XF86DRICreateContext(dpy, screen, visual, context, hHWContext)
    void* dpy;
    int screen;
    Visual* visual;
    XID* context;
    drmContextPtr hHWContext;
{
    XExtDisplayInfo *info = find_display (dpy);
    xXF86DRICreateContextReply rep;
    xXF86DRICreateContextReq *req;

    TRACE("CreateContext...\n");
    XF86DRICheckExtension (dpy, info, False);

    LockDisplay(dpy);
    GetReq(XF86DRICreateContext, req);
    req->reqType = info->codes->major_opcode;
    req->driReqType = X_XF86DRICreateContext;
    req->visual = visual->visualid;
    req->screen = screen;
    *context = XAllocID(dpy);
    req->context = *context;
    if (!_XReply(dpy, (xReply *)&rep, 0, xFalse)) {
	UnlockDisplay(dpy);
	SyncHandle();
        TRACE("CreateContext... return False\n");
	return False;
    }
    *hHWContext = rep.hHWContext;
    UnlockDisplay(dpy);
    SyncHandle();
    TRACE("CreateContext... return True\n");
    return True;
}

Bool
DRIDestroyContextPriv(DRIContextPrivPtr pDRIContextPriv)
{
    DRIScreenPrivPtr pDRIPriv;

    if (!pDRIContextPriv) return TRUE;

    pDRIPriv = DRI_SCREEN_PRIV(pDRIContextPriv->pScreen);

    if (!(pDRIContextPriv->flags & DRI_CONTEXT_RESERVED)) {
				/* Don't delete reserved contexts from
                                   kernel area -- the kernel manages its
                                   reserved contexts itself. */
	if (drmDestroyContext(pDRIPriv->drmFD, pDRIContextPriv->hwContext))
	    return FALSE;
    }

				/* Remove the tag last to prevent a race
                                   condition where the context has pending
                                   buffers.  The context can't be re-used
                                   while in this thread, but buffers can be
                                   dispatched asynchronously. */
    drmDelContextTag(pDRIPriv->drmFD, pDRIContextPriv->hwContext);
    xfree(pDRIContextPriv);
    return TRUE;
}


Bool XF86DRIDestroyContext(dpy, screen, context)
    void* dpy;
    int screen;
    XID context;
{
    DRIContextPrivPtr pDRIContextPriv = (DRIContextPrivPtr)pResource;
    DRIScreenPrivPtr pDRIPriv;
    void *contextStore;

    pDRIPriv = DRI_SCREEN_PRIV(pDRIContextPriv->pScreen);

    TRACE("DestroyContext\n");
    return DRIDestroyContextPriv(pDRIContextPriv);
}

Bool XF86DRICreateDrawable(dpy, screen, drawable, hHWDrawable)
    void* dpy;
    int screen;
    Drawable drawable;
    drmDrawablePtr hHWDrawable;
{
    DRIScreenPrivPtr	pDRIPriv = DRI_SCREEN_PRIV(pScreen);
    DRIDrawablePrivPtr	pDRIDrawablePriv;
    WindowPtr		pWin;

    if (pDrawable->type == DRAWABLE_WINDOW) {
	pWin = (WindowPtr)pDrawable;
	if ((pDRIDrawablePriv = DRI_DRAWABLE_PRIV_FROM_WINDOW(pWin))) {
	    pDRIDrawablePriv->refCount++;
	}
	else {
	    /* allocate a DRI Window Private record */
	    if (!(pDRIDrawablePriv = xalloc(sizeof(DRIDrawablePrivRec)))) {
		return FALSE;
	    }

	    /* Only create a drmDrawable once */
	    if (drmCreateDrawable(pDRIPriv->drmFD, hHWDrawable)) {
		xfree(pDRIDrawablePriv);
		return FALSE;
	    }

	    /* add it to the list of DRI drawables for this screen */
	    pDRIDrawablePriv->hwDrawable = *hHWDrawable;
	    pDRIDrawablePriv->pScreen = pScreen;
	    pDRIDrawablePriv->refCount = 1;
	    pDRIDrawablePriv->drawableIndex = -1;


	    /* track this in case this window is destroyed */
	    AddResource(id, DRIDrawablePrivResType, (pointer)pWin);
	}
    }
    else { /* pixmap (or for GLX 1.3, a PBuffer) */
	/* NOT_DONE */
	return FALSE;
    }

    return TRUE;
}

Bool
DRIDrawablePrivDelete(pointer pResource, XID id)
{
    DrawablePtr		pDrawable = (DrawablePtr)pResource;
    DRIScreenPrivPtr	pDRIPriv = DRI_SCREEN_PRIV(pDrawable->pScreen);
    DRIDrawablePrivPtr	pDRIDrawablePriv;
    WindowPtr		pWin;

    if (pDrawable->type == DRAWABLE_WINDOW) {
	pWin = (WindowPtr)pDrawable;
	pDRIDrawablePriv = DRI_DRAWABLE_PRIV_FROM_WINDOW(pWin);

	if (pDRIDrawablePriv->drawableIndex != -1) {
	    /* bump stamp to force outstanding 3D requests to resync */
	    pDRIPriv->pSAREA->drawableTable[pDRIDrawablePriv->drawableIndex].stamp
		= DRIDrawableValidationStamp++;

	    /* release drawable table entry */
	    pDRIPriv->DRIDrawables[pDRIDrawablePriv->drawableIndex] = NULL;
	}

	if (drmDestroyDrawable(pDRIPriv->drmFD,
			       pDRIDrawablePriv->hwDrawable)) {
	    return FALSE;
	}
	xfree(pDRIDrawablePriv);
    }
    else { /* pixmap (or for GLX 1.3, a PBuffer) */
	/* NOT_DONE */
	return FALSE;
    }

    return TRUE;
}


Bool XF86DRIDestroyDrawable(dpy, screen, drawable)
    void* dpy;
    int screen;
    Drawable drawable;
{
    DRIDrawablePrivPtr	pDRIDrawablePriv;
    WindowPtr		pWin;


    if (pDrawable->type == DRAWABLE_WINDOW) {
	pWin = (WindowPtr)pDrawable;
	pDRIDrawablePriv = DRI_DRAWABLE_PRIV_FROM_WINDOW(pWin);
	pDRIDrawablePriv->refCount--;
	if (pDRIDrawablePriv->refCount <= 0) {
	    /* This calls back DRIDrawablePrivDelete which frees private area */
	    FreeResourceByType(id, DRIDrawablePrivResType, FALSE);
	}
    }
    else { /* pixmap (or for GLX 1.3, a PBuffer) */
	/* NOT_DONE */
	return FALSE;
    }

    return TRUE;
}

Bool XF86DRIGetDrawableInfo(dpy, screen, drawable, 
			    index, stamp, X, Y, W, H, 
			    numClipRects, pClipRects,
			    backX, backY, 
			    numBackClipRects, pBackClipRects
			    )
    void* dpy;
    int screen;
    Drawable drawable;
    unsigned int* index;
    unsigned int* stamp;
    int* X;
    int* Y;
    int* W;
    int* H;
    int* numClipRects;
    XF86DRIClipRectPtr* pClipRects;
    int* backX;
    int* backY;
    int* numBackClipRects;
    XF86DRIClipRectPtr*	pBackClipRects;    
{
   DRIScreenPrivPtr    pDRIPriv = DRI_SCREEN_PRIV(pScreen);
   DRIDrawablePrivPtr	pDRIDrawablePriv, pOldDrawPriv;
   int			i;

   *index = 0;
   *stamp = 0;
   *X = 0;
   *Y = 0;
   *W = pScreen->w;
   *H = pScreen->h;
   *numClipRects = 1;
   *pClipRects = &pScreen->clipList;

   return TRUE;
}

Bool XF86DRIGetDeviceInfo(dpy, screen, hFrameBuffer, 
	fbOrigin, fbSize, fbStride, devPrivateSize, pDevPrivate)
    void* dpy;
    int screen;
    drmHandlePtr hFrameBuffer;
    int* fbOrigin;
    int* fbSize;
    int* fbStride;
    int* devPrivateSize;
    void** pDevPrivate;
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    *hFrameBuffer = pDRIPriv->hFrameBuffer;
    *fbOrigin = 0;
    *fbSize = pDRIPriv->pDriverInfo->frameBufferSize;
    *fbStride = pDRIPriv->pDriverInfo->frameBufferStride;
    *devPrivateSize = 0;
    *pDevPrivate = 0;

    return TRUE;
}

Bool XF86DRIOpenFullScreen(dpy, screen, drawable)
    void* dpy;
    int screen;
    Drawable drawable;
{
    return False;
}

Bool XF86DRICloseFullScreen(dpy, screen, drawable)
    void* dpy;
    int screen;
    Drawable drawable;
{
    return True;
}

