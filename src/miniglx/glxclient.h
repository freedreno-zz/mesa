/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.1 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
** 
** http://oss.sgi.com/projects/FreeB
** 
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
** 
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
** 
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
*/
/* $XFree86: xc/lib/GL/glx/glxclient.h,v 1.14 2002/02/22 21:32:53 dawes Exp $ */

/*
 * Direct rendering support added by Precision Insight, Inc.
 *
 * Authors:
 *   Kevin E. Martin <kevin@precisioninsight.com>
 *
 */

#ifndef _GLX_client_h_
#define _GLX_client_h_

#include <stdlib.h>

#define GLX_GLXEXT_PROTOTYPES
#include <GL/glx.h>
#include "GL/glxint.h"
#include "glapitable.h"


#undef XTHREADS

#define GLX_DIRECT_RENDERING 1

#define GLX_MAJOR_VERSION	1	/* current version numbers */
#define GLX_MINOR_VERSION	2


typedef struct __GLXcontextRec __GLXcontext;
typedef struct __GLXdisplayPrivateRec __GLXdisplayPrivate;

typedef struct __DRIscreenRec   __DRIscreen;
typedef struct __DRIcontextRec  __DRIcontext;
typedef struct __DRIdrawableRec __DRIdrawable;
typedef struct __DRIdriverRec   __DRIdriver;


/*
** Screen dependent methods.  This structure is initialized during the
** (*createScreen)() call.
*/
struct __DRIscreenRec {
    /*
    ** Method to destroy the private DRI screen data.
    */
    void (*destroyScreen)(Display *dpy, int scrn, void *screenPrivate);

    /*
    ** Method to create the private DRI context data and initialize the
    ** context dependent methods.
    */
    void *(*createContext)(Display *dpy, XVisualInfo *vis, void *sharedPrivate,
			   __DRIcontext *pctx);

    /*
    ** Method to create the private DRI drawable data and initialize the
    ** drawable dependent methods.
    */
    void *(*createDrawable)(Display *dpy, int scrn, GLXDrawable draw,
			    VisualID vid, __DRIdrawable *pdraw);

    /*
    ** Method to return a pointer to the DRI drawable data.
    */
    __DRIdrawable *(*getDrawable)(Display *dpy, GLXDrawable draw,
				  void *drawablePrivate);

    /*
    ** XXX in the future, implement this:
    void *(*createPBuffer)(Display *dpy, int scrn, GLXPbuffer pbuffer,
			   GLXFBConfig config, __DRIdrawable *pdraw);
    **/

    /*
    ** Opaque pointer to private per screen direct rendering data.  NULL
    ** if direct rendering is not supported on this screen.  Never
    ** dereferenced in libGL.
    */
    void *private;
};

/*
** Context dependent methods.  This structure is initialized during the
** (*createContext)() call.
*/
struct __DRIcontextRec {
    /*
    ** Method to destroy the private DRI context data.
    */
    void (*destroyContext)(Display *dpy, int scrn, void *contextPrivate);

    /*
    ** Method to bind a DRI drawable to a DRI graphics context.
    ** XXX in the future, also pass a 'read' GLXDrawable for
    ** glXMakeCurrentReadSGI() and GLX 1.3's glXMakeContextCurrent().
    */
    Bool (*bindContext)(Display *dpy, int scrn, GLXDrawable draw,
			GLXContext gc);

    /*
    ** Method to unbind a DRI drawable to a DRI graphics context.
    */
    Bool (*unbindContext)(Display *dpy, int scrn, GLXDrawable draw,
			  GLXContext gc, int will_rebind);

    /*
    ** Opaque pointer to private per context direct rendering data.
    ** NULL if direct rendering is not supported on the display or
    ** screen used to create this context.  Never dereferenced in libGL.
    */
    void *private;
};

/*
** Drawable dependent methods.  This structure is initialized during the
** (*createDrawable)() call.  createDrawable() is not called by libGL at
** this time.  It's currently used via the dri_util.c utility code instead.
*/
struct __DRIdrawableRec {
    /*
    ** Method to destroy the private DRI drawable data.
    */
    void (*destroyDrawable)(Display *dpy, void *drawablePrivate);

    /*
    ** Method to swap the front and back buffers.
    */
    void (*swapBuffers)(Display *dpy, void *drawablePrivate);

    /*
    ** Opaque pointer to private per drawable direct rendering data.
    ** NULL if direct rendering is not supported on the display or
    ** screen used to create this drawable.  Never dereferenced in libGL.
    */
    void *private;
};


typedef void *(*CreateScreenFunc)(Display *dpy, int scrn, __DRIscreen *psc,
                                  int numConfigs, __GLXvisualConfig *config);

typedef void *(*RegisterExtensionsFunc)(void);


/*
** We keep a linked list of these structures, one per DRI device driver.
*/
struct __DRIdriverRec {
   const char *name;
   void *handle;
   CreateScreenFunc createScreenFunc;
   RegisterExtensionsFunc registerExtensionsFunc;
   struct __DRIdriverRec *next;
};


/*
** GLX state that needs to be kept on the client.  One of these records
** exist for each context that has been made current by this client.
*/
struct __GLXcontextRec {
    /*
    ** Visual id.
    */
    VisualID vid;

    /*
    ** screen number.
    */
    GLint screen;

    /*
    ** dpy of current display for this context. Will be NULL if not
    ** current to any display, or if this is the "dummy context".
    */
    Display *currentDpy;

    /*
    ** The current drawable for this context.  Will be None if this
    ** context is not current to any drawable.
    */
    GLXDrawable currentDrawable;

#ifdef GLX_DIRECT_RENDERING
    /*
    ** Per context direct rendering interface functions and data.
    */
    __DRIcontext driContext;
#endif
};


/*
** One of these records exists per screen of the display.  It contains
** a pointer to the config data for that screen (if the screen supports GL).
*/
typedef struct __GLXscreenConfigsRec {
    __GLXvisualConfig *configs;
    int numConfigs;

    /*
    ** Per screen direct rendering interface functions and data.
    */
    __DRIscreen driScreen;
} __GLXscreenConfigs;


/*
** Per display private data.  One of these records exists for each display
** that is using the OpenGL (GLX) extension.
*/
struct __GLXdisplayPrivateRec {
    /*
    ** Back pointer to the display
    */
    Display *dpy;

    /* for linked list */
    struct __GLXdisplayPrivateRec *next;


    /*
    ** The majorOpcode is common to all connections to the same server.
    ** It is also copied into the context structure.
    */
    int majorOpcode;

    /*
    ** Major and minor version returned by the server during initialization.
    */
    int majorVersion, minorVersion;

    /* Storage for the servers GLX vendor and versions strings.  These
    ** are the same for all screens on this display. These fields will
    ** be filled in on demand.
    */
    char *serverGLXvendor;
    char *serverGLXversion;

    /*
    ** Configurations of visuals for all screens on this display.
    ** Also, per screen data which now includes the server GLX_EXTENSION
    ** string.
    */
    __GLXscreenConfigs *screenConfigs;

    /*----------------------------------------------------------------------
    ** Direct rendering stuff (formerly in __DRIdisplay)
    */

    /*
    ** Method to destroy the private DRI display data.
    */
    void (*destroyDisplay)(Display *dpy, __GLXdisplayPrivate *displayPrivate);

    /*
    ** Methods to create the private DRI screen data and initialize the
    ** screen dependent methods.
    ** This is an array [indexed by screen number] of function pointers.
    */
    void *(**createScreen)(Display *dpy, int scrn, __DRIscreen *psc,
			  int numConfigs, __GLXvisualConfig *config);

    /*
    ** Array of library handles [indexed by screen number]
    */
    void **libraryHandles;
};



extern __DRIscreen *__glXFindDRIScreen(Display *dpy, int scrn);

extern void __glXFreeContext(__GLXcontext*);

extern __GLXdisplayPrivate *__glXInitialize(Display*);

extern void __glXRegisterExtensions(void);
extern void *__glXRegisterGLXFunction(const char *funcName, void *funcAddr);
extern void __glXRegisterGLXExtensionString(const char *extName);


/************************************************************************/

/*
** Declarations that should be in Xlib
*/
#ifdef __GL_USE_OUR_PROTOTYPES
extern void _XFlush(Display*);
extern Status _XReply(Display*, xReply*, int, Bool);
extern void _XRead(Display*, void*, long);
extern void _XSend(Display*, const void*, long);
#endif


extern char *__glXstrdup(const char *str);

#endif /* !__GLX_client_h__ */
