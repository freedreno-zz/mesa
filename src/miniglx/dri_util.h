/**
 * \file dri_util.h
 * 
 * Copyright 1998-1999 Precision Insight, Inc., Cedar Park, Texas.
 * All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * \author Kevin E. Martin <kevin@precisioninsight.com>
 * \author Brian Paul <brian@precisioninsight.com>
 *
 * This module acts as glue between GLX and the actual hardware driver.
 * A DRI driver doesn't really \e have to use any of this - it's optional.
 * But, some useful stuff is done here that otherwise would have to be
 * duplicated in most drivers.
 * 
 * Basically, these utility functions take care of some of the dirty details
 * of screen initialization, context creation, context binding, DRM setup,
 * etc.
 *
 * These functions are compiled into each DRI driver so libGL.so knows
 * nothing about them.
 *
 * Look for more comments in the dri_util.c file.
 */

/* $XFree86$ */


#ifndef _DRI_UTIL_H_
#define _DRI_UTIL_H_

#define CAPI  /* XXX this should be globally defined somewhere */

#include "GL/miniglx.h"           /* for GLXDrawable */
#include "sarea.h"               /* for XF86DRISAREAPtr */
#include "GL/internal/glcore.h"  /* for __GLcontextModes */
#include "miniglxP.h"		/* XID, etc */



typedef struct __DRIdisplayPrivateRec  __DRIdisplayPrivate;
typedef struct __DRIscreenPrivateRec   __DRIscreenPrivate;
typedef struct __DRIcontextPrivateRec  __DRIcontextPrivate;
typedef struct __DRIdrawablePrivateRec __DRIdrawablePrivate;


#define DRI_VALIDATE_DRAWABLE_INFO_ONCE(pDrawPriv)              \
    do {                                                        \
	if (*(pDrawPriv->pStamp) != pDrawPriv->lastStamp) {     \
	    __driUtilUpdateDrawableInfo(pDrawPriv);             \
	}                                                       \
    } while (0)


#define DRI_VALIDATE_DRAWABLE_INFO(psp, pdp)                            \
do {                                                                    \
    while (*(pdp->pStamp) != pdp->lastStamp) {                          \
	DRM_UNLOCK(psp->fd, &psp->pSAREA->lock,                         \
		   pdp->driContextPriv->hHWContext);                    \
                                                                        \
	DRM_SPINLOCK(&psp->pSAREA->drawable_lock, psp->drawLockID);     \
	DRI_VALIDATE_DRAWABLE_INFO_ONCE(pdp);                           \
	DRM_SPINUNLOCK(&psp->pSAREA->drawable_lock, psp->drawLockID);   \
                                                                        \
	DRM_LIGHT_LOCK(psp->fd, &psp->pSAREA->lock,                     \
		       pdp->driContextPriv->hHWContext);                \
    }                                                                   \
} while (0)


/**
 * Each DRI driver must have one of these structs with all the pointers set to
 * appropriate functions within the driver.
 * 
 * When glXCreateContext() is called, for example, it'll call a helper function
 * dri_util.c which in turn will jump through the \a CreateContext pointer in
 * this structure.
 */
struct __DriverAPIRec {
    GLboolean (*InitDriver)(__DRIscreenPrivate *driScrnPriv);
    void (*DestroyScreen)(__DRIscreenPrivate *driScrnPriv);
    GLboolean (*CreateContext)(const __GLcontextModes *glVis,
                               __DRIcontextPrivate *driContextPriv,
                               void *sharedContextPrivate);
    void (*DestroyContext)(__DRIcontextPrivate *driContextPriv);
    GLboolean (*CreateBuffer)(__DRIscreenPrivate *driScrnPriv,
                              __DRIdrawablePrivate *driDrawPriv,
                              const __GLcontextModes *glVis,
                              GLboolean pixmapBuffer);
    void (*DestroyBuffer)(__DRIdrawablePrivate *driDrawPriv);
    void (*SwapBuffers)(__DRIdrawablePrivate *driDrawPriv);
    GLboolean (*MakeCurrent)(__DRIcontextPrivate *driContextPriv,
                             __DRIdrawablePrivate *driDrawPriv,
                             __DRIdrawablePrivate *driReadPriv);
    GLboolean (*UnbindContext)(__DRIcontextPrivate *driContextPriv);
    GLboolean (*OpenFullScreen)(__DRIcontextPrivate *driContextPriv);
    GLboolean (*CloseFullScreen)(__DRIcontextPrivate *driContextPriv);
};


struct __DRIdrawablePrivateRec {
    /**
     * Kernel drawable handle (not currently used).
     */
    drmDrawable hHWDrawable;

    /**
     * Driver's private drawable information.  This structure is opaque.
     */
    void *driverPrivate;

    /**
     * X's drawable ID associated with this private drawable.
     */
    GLXDrawable draw;

    /**
     * Reference count for number of context's currently bound to this
     * drawable.  Once the refcount reaches 0, the drawable can be
     * destroyed.  This behavior will change with GLX 1.3.
     */
    int refcount;

    /**
     * Index of this drawable's information in the SAREA.
     */
    unsigned int index;

    /**
     * Pointer to the "drawable has changed ID" stamp in the SAREA.
     */
    unsigned int *pStamp;

    /**
     * Last value of the stamp.  If this differs from the value stored
     * at *pStamp, then the drawable information has been modified by
     * the X server, and the drawable information (below) should be
     * retrieved from the X server.
     */
    unsigned int lastStamp;

    /**
     * \name Drawable information used in software fallbacks.
     */
    /*@{*/
    int x;
    int y;
    int w;
    int h;
    int numClipRects;
    XF86DRIClipRectPtr pClipRects;
    /*@}*/

    /**
     * Information about the back and depthbuffer where different
     * from above.
     */
    /*@{*/
    int backX;
    int backY;
    int backClipRectType;
    int numBackClipRects;
    XF86DRIClipRectPtr pBackClipRects;
    /*@}*/

    /**
     * Pointer to context to which this drawable is currently bound.
     */
    __DRIcontextPrivate *driContextPriv;

    /**
     * Pointer to screen on which this drawable was created.
     */
    __DRIscreenPrivate *driScreenPriv;

    /**
     * Basically just need these for when the locking code needs to call
     * __driUtilUpdateDrawableInfo() which calls XF86DRIGetDrawableInfo().
     */
    Display *display;
    int screen;

    /**
     * Called via glXSwapBuffers().
     */
    void (*swapBuffers)( __DRIdrawablePrivate *dPriv );
};

struct __DRIcontextPrivateRec {
    /**
     * Kernel context handle used to access the device lock.
     */
    XID contextID;

    /**
     * Kernel context handle used to access the device lock.
     */
    drmContext hHWContext;

    /**
     * Device driver's private context data.  This structure is opaque.
     */
    void *driverPrivate;

    /**
     * This context's display pointer.
     */
    Display *display;

    /**
     * Pointer to drawable currently bound to this context.
     */
    __DRIdrawablePrivate *driDrawablePriv;

    /**
     * Pointer to screen on which this context was created.
     */
    __DRIscreenPrivate *driScreenPriv;
};

struct __DRIscreenPrivateRec {
    /**
     * Display for this screen
     */
    Display *display;

    /**
     * Current screen's number
     */
    int myNum;

    /**
     * Callback functions into the hardware-specific DRI driver code.
     */
    struct __DriverAPIRec DriverAPI;

    /**
     * \name DDX / 2D driver version information.
     */
    /*@{*/
    int ddxMajor;
    int ddxMinor;
    int ddxPatch;
    /*@}*/

    /**
     * \name DRI X extension version information.
     */
    /*@{*/
    int driMajor;
    int driMinor;
    int driPatch;
    /*@}*/

    /**
     * \name DRM (kernel module) version information.
     */
    /*@{*/
    int drmMajor;
    int drmMinor;
    int drmPatch;
    /*@}*/

    /**
     * ID used when the client sets the drawable lock.  The X server
     * uses this value to detect if the client has died while holding
     * the drawable lock.
     */
    int drawLockID;

    /**
     * File descriptor returned when the kernel device driver is opened.
     * It is used to:
     *   - authenticate client to kernel
     *   - map the frame buffer, SAREA, etc.
     *   - close the kernel device driver
     */
    int fd;

    /**
     * SAREA pointer used to access:
     *   - the device lock
     *   - the device-independent per-drawable and per-context(?) information
     */
    XF86DRISAREAPtr pSAREA;

    /**
     * \name Direct frame buffer access information used for software
     * fallbacks.
     */
    /*@{*/
    unsigned char *pFB;
    int fbSize;
    int fbOrigin;
    int fbStride;
    int fbWidth;
    int fbHeight;
    int fbBPP;
    /*@}*/

    /**
     * \name Device-dependent private information (stored in the SAREA).
     *
     * This data is accessed by the client driver only.
     */
    /*@{*/
    void *pDevPriv;
    int devPrivSize;
    /*@}*/

    /**
     * Dummy context to which drawables are bound when not bound to any
     * other context. A dummy hHWContext is created for this context,
     * and is used by the GL core when a HW lock is required but the
     * drawable is not currently bound (e.g., potentially during a
     * SwapBuffers request).  The dummy context is created when the
     * first "real" context is created on this screen.
     */
    __DRIcontextPrivate dummyContextPriv;

    /**
     * Hash table to hold the drawable information for this screen.
     */
    void *drawHash;

    /**
     * Device-dependent private information (not stored in the SAREA).
     * This pointer is never touched by the DRI layer.
     */
    void *private;

    /**
     * If we're in full screen mode (via DRIOpenFullScreen()), this points to
     * the drawable that was bound.  Otherwise, this is NULL.
     */
    __DRIdrawablePrivate *fullscreen;

    /**
     * \name Number of visuals (configs) for this screen, and a pointer to them.
     */
    /*@{*/
    int numConfigs;
    __GLXvisualConfig *configs;
    /*@}*/
};



extern void
__driUtilMessage(const char *f, ...);


extern void
__driUtilUpdateDrawableInfo(__DRIdrawablePrivate *pdp);


extern __DRIscreenPrivate *
__driUtilCreateScreen(Display *dpy, int scrn, __DRIscreen *psc,
                      int numConfigs, __GLXvisualConfig *config,
                      const struct __DriverAPIRec *driverAPI);

__DRIscreenPrivate *
__driUtilCreateScreenNoDRM(Display *dpy, int scrn, __DRIscreen *psc,
			   int numConfigs, __GLXvisualConfig *config,
			   const struct __DriverAPIRec *driverAPI);

/** This must be implemented in each driver */
extern void *
__driCreateScreen(Display *dpy, int scrn, __DRIscreen *psc,
                  int numConfigs, __GLXvisualConfig *config);


/** This is optionally implemented in each driver */
extern void
__driRegisterExtensions( void );


extern void
__driUtilInitScreen( Display *dpy, int scrn, __DRIscreen *psc );

#endif /* _DRI_UTIL_H_ */
