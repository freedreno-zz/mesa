/* $XFree86: xc/programs/Xserver/GL/dri/dri.h,v 1.18 2001/03/21 16:21:40 dawes Exp $ */
/**************************************************************************

Copyright 1998-1999 Precision Insight, Inc., Cedar Park, Texas.
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
 *
 */

/* Prototypes for DRI functions */

#ifndef _DRI_H_

#include "scrnintstr.h"
#include "xf86dri.h"

typedef int DRISyncType;

#define DRI_NO_SYNC 0
#define DRI_2D_SYNC 1
#define DRI_3D_SYNC 2

typedef int DRIContextType;

typedef struct _DRIContextPrivRec DRIContextPrivRec, *DRIContextPrivPtr;

typedef enum _DRIContextFlags
{
    DRI_CONTEXT_2DONLY    = 0x01,
    DRI_CONTEXT_PRESERVED = 0x02,
    DRI_CONTEXT_RESERVED  = 0x04 /* DRI Only -- no kernel equivalent */
} DRIContextFlags;

#define DRI_NO_CONTEXT 0
#define DRI_2D_CONTEXT 1
#define DRI_3D_CONTEXT 2

typedef int DRISwapMethod;

#define DRI_HIDE_X_CONTEXT 0
#define DRI_SERVER_SWAP    1
#define DRI_KERNEL_SWAP    2

typedef int DRIWindowRequests;

#define DRI_NO_WINDOWS       0
#define DRI_3D_WINDOWS_ONLY  1
#define DRI_ALL_WINDOWS      2



/*
 * These functions can be wrapped by the DRI.  Each of these have
 * generic default funcs (initialized in DRICreateInfoRec) and can be
 * overridden by the driver in its [driver]DRIScreenInit function.
 */



typedef struct {
    /* driver call back functions
     *
     * New fields should be added at the end for backwards compatability.
     * Don't forget to bump the version minor number in 
     *   xc/lib/GL/dri/xf86dristr.h
     */
    Bool	(*CreateContext)(ScreenPtr pScreen,
				 VisualPtr visual,
				 drmContext hHWContext,
				 void* pVisualConfigPriv,
				 DRIContextType context);
    void        (*DestroyContext)(ScreenPtr pScreen,
				  drmContext hHWContext,
                                  DRIContextType context);
    void	(*SwapContext)(ScreenPtr pScreen,
			       DRISyncType syncType,
			       DRIContextType readContextType,
			       void* readContextStore,
			       DRIContextType writeContextType,
			       void* writeContextStore);
    void	(*SetDrawableIndex)(WindowPtr pWin, CARD32 indx);
    /* device info */
    char*		drmDriverName;
    char*		clientDriverName;
    char*		busIdString;
    int			ddxDriverMajorVersion;
    int			ddxDriverMinorVersion;
    int			ddxDriverPatchVersion;
    CARD32		frameBufferPhysicalAddress;
    long		frameBufferSize;
    long		frameBufferStride;
    long		SAREASize;
    int			maxDrawableTableEntry;
    int			ddxDrawableTableEntry;
    long		contextSize;
    DRISwapMethod	driverSwapMethod;
    DRIWindowRequests	bufferRequests;
    int			devPrivateSize;
    void*		devPrivate;

} DRIInfoRec, *DRIInfoPtr;


extern Bool DRIScreenInit(ScreenPtr pScreen,
                          DRIInfoPtr pDRIInfo,
                          int *pDRMFD);

extern void DRICloseScreen(ScreenPtr pScreen);

extern Bool DRIExtensionInit(void);

extern void DRIReset(void);

extern Bool DRIQueryDirectRenderingCapable(ScreenPtr pScreen,
                                           Bool *isCapable);

extern Bool DRIOpenConnection(ScreenPtr pScreen,
                              drmHandlePtr hSAREA,
                              char **busIdString);

extern Bool DRIAuthConnection(ScreenPtr pScreen, drmMagic magic);

extern Bool DRICloseConnection(ScreenPtr pScreen);

extern Bool DRIGetClientDriverName(ScreenPtr pScreen,
                                   int* ddxDriverMajorVersion,
                                   int* ddxDriverMinorVersion,
                                   int* ddxDriverPatchVersion,
                                   char** clientDriverName);

extern Bool DRICreateContext(ScreenPtr pScreen,
                             VisualPtr visual,
                             XID context,
                             drmContextPtr pHWContext);

extern Bool DRIDestroyContext(ScreenPtr pScreen, XID context);

extern Bool DRIContextPrivDelete(pointer pResource, XID id);

extern Bool DRICreateDrawable(ScreenPtr pScreen,
                              Drawable id,
                              DrawablePtr pDrawable,
                              drmDrawablePtr hHWDrawable);

extern Bool DRIDestroyDrawable(ScreenPtr pScreen, 
                               Drawable id,
                               DrawablePtr pDrawable);

extern Bool DRIDrawablePrivDelete(pointer pResource,
                                  XID id);

extern Bool DRIGetDrawableInfo(ScreenPtr pScreen,
                               DrawablePtr pDrawable,
                               unsigned int* indx,
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
                               XF86DRIClipRectPtr* pBackClipRects);

extern Bool DRIGetDeviceInfo(ScreenPtr pScreen,
                             drmHandlePtr hFrameBuffer,
                             int* fbOrigin,
                             int* fbSize,
                             int* fbStride,
                             int* devPrivateSize,
                             void** pDevPrivate);

extern DRIInfoPtr DRICreateInfoRec(void);

extern void DRIDestroyInfoRec(DRIInfoPtr DRIInfo);

extern Bool DRIFinishScreenInit(ScreenPtr pScreen);

extern void *DRIGetContextStore(DRIContextPrivPtr context);

extern CARD32 DRIGetDrawableIndex(WindowPtr pWin);

extern void DRIPrintDrawableLock(ScreenPtr pScreen, char *msg);

extern void DRILock(ScreenPtr pScreen, int flags);

extern void DRIUnlock(ScreenPtr pScreen);

extern DRIWrappedFuncsRec *DRIGetWrappedFuncs(ScreenPtr pScreen);

extern void *DRIGetSAREAPrivate(ScreenPtr pScreen);

extern unsigned int DRIGetDrawableStamp(ScreenPtr pScreen,
                                        CARD32 drawable_index);

extern DRIContextPrivPtr DRICreateContextPriv(ScreenPtr pScreen,
                                              drmContextPtr pHWContext,
                                              DRIContextFlags flags);

extern DRIContextPrivPtr DRICreateContextPrivFromHandle(ScreenPtr pScreen,
                                                        drmContext hHWContext,
                                                        DRIContextFlags flags);

extern Bool DRIDestroyContextPriv(DRIContextPrivPtr pDRIContextPriv);

extern drmContext DRIGetContext(ScreenPtr pScreen);

extern void DRIQueryVersion(int *majorVersion,
                            int *minorVersion,
                            int *patchVersion);

#define _DRI_H_

#endif
