/* $XFree86: xc/lib/GL/dri/XF86dri.c,v 1.12 2001/08/27 17:40:57 dawes Exp $ */
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
 *     Keith Whitwell <keith@tungstengraphics.com>
 */

/* Stubs to load a dri driver under fbdev.  Built by combining pieces
 * of dri.c (server side) and XF86dri.c (client side).
 *
 * Interfaces with code lifted from the 2d ddx driver to perform
 * various initialization services which would ordinarily be done by
 * the X server.
 */


#if 1
#include <stdio.h>
#define TRACE(msg)  fprintf(stderr,"XF86DRI%s\n", msg);
#else
#define TRACE(msg)
#endif


Bool XF86DRIQueryVersion(dpy, majorVersion, minorVersion, patchVersion)
    Display* dpy;
    int* majorVersion; 
    int* minorVersion;
    int* patchVersion;
{
    *majorVersion = XF86DRI_MAJOR_VERSION;
    *minorVersion = XF86DRI_MINOR_VERSION;
    *patchVersion = XF86DRI_PATCH_VERSION;
    TRACE("QueryVersion");
    return True;
}

Bool XF86DRIQueryDirectRenderingCapable(dpy, screen, isCapable)
    Display* dpy;
    int screen;
    Bool* isCapable;
{
    TRACE("QueryDirectRenderingCapable... return True");
    *isCapable = True;
    return True;
}

Bool XF86DRIOpenConnection(dpy, screen, hSAREA, busIdString)
    Display* dpy;
    int screen;
    drmHandlePtr hSAREA;
    char **busIdString;
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    *hSAREA           = pDRIPriv->hSAREA;
    *busIdString      = strdup(pDRIPriv->pDriverInfo->busIdString);

    TRACE("OpenConnection... return True");
    return True;
}

Bool XF86DRIAuthConnection(dpy, screen, magic)
    Display* dpy;
    int screen;
    drmMagic magic;
{
    DRIScreenPrivPtr pDRIPriv = DRI_SCREEN_PRIV(pScreen);

    if (drmAuthMagic(pDRIPriv->drmFD, magic)) return FALSE;
    return TRUE;
}

Bool XF86DRICloseConnection(dpy, screen)
    Display* dpy;
    int screen;
{
    return True;
}

Bool XF86DRIGetClientDriverName(dpy, screen, ddxDriverMajorVersion, 
	ddxDriverMinorVersion, ddxDriverPatchVersion, clientDriverName)
    Display* dpy;
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
    Display* dpy;
    int screen;
    Visual* visual;
    XID* context;
    drmContextPtr hHWContext;
{
    XExtDisplayInfo *info = find_display (dpy);
    xXF86DRICreateContextReply rep;
    xXF86DRICreateContextReq *req;

    TRACE("CreateContext...");
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
        TRACE("CreateContext... return False");
	return False;
    }
    *hHWContext = rep.hHWContext;
    UnlockDisplay(dpy);
    SyncHandle();
    TRACE("CreateContext... return True");
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
    Display* dpy;
    int screen;
    XID context;
{
    DRIContextPrivPtr pDRIContextPriv = (DRIContextPrivPtr)pResource;
    DRIScreenPrivPtr pDRIPriv;
    void *contextStore;

    pDRIPriv = DRI_SCREEN_PRIV(pDRIContextPriv->pScreen);

    TRACE("DestroyContext");
    return DRIDestroyContextPriv(pDRIContextPriv);
}

Bool XF86DRICreateDrawable(dpy, screen, drawable, hHWDrawable)
    Display* dpy;
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
    Display* dpy;
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
    Display* dpy;
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
    Display* dpy;
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
    Display* dpy;
    int screen;
    Drawable drawable;
{
    return False;
}

Bool XF86DRICloseFullScreen(dpy, screen, drawable)
    Display* dpy;
    int screen;
    Drawable drawable;
{
    return True;
}

