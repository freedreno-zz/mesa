/* $XFree86: xc/lib/GL/glx/glxext.c,v 1.14 2002/02/22 21:32:53 dawes Exp $ */

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
**
*/

/*                                                            <
 * Direct rendering support added by Precision Insight, Inc.  <
 *                                                            <
 * Authors:                                                   <
 *   Kevin E. Martin <kevin@precisioninsight.com>             <
 *   Brian Paul                                               <
 *                                                            <
 */     

#include <assert.h>
#include <dlfcn.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "glxclient.h"
/*#include "xf86dri.h"*/

#include "glapi.h"


static const char __glXGLXClientVendorName[] = "SGI";
static const char __glXGLXClientVersion[] = "1.2";
static const char __glXGLXClientExtensions[] = 
   "GLX_EXT_visual_info "
   "GLX_EXT_visual_rating "
   "GLX_EXT_import_context ";


/*
 * Current context management and locking
 */
static __GLXcontext *__glXcurrentContext = NULL;
#define __glXGetCurrentContext()	__glXcurrentContext
#define __glXSetCurrentContext(gc)	__glXcurrentContext = gc


static __GLXdisplayPrivate *displayPrivates = NULL;


/* forward decl */
static Bool driInitDisplay(Display *dpy, __GLXdisplayPrivate *pdisp);

static __DRIdriver *driGetDriver(Display *dpy, int scrNum);



/**********************************************************************/
/* NEW: this replaces a bunch of GLX calls to the server.
/**********************************************************************/

static __GLXvisualConfig
*XF86DRI_GetScreenConfigs( int *count )
{
   __GLXvisualConfig *configs;
   int i;

   *count = 2;
   configs = malloc(*count * sizeof(__GLXvisualConfig));
   if (!configs) {
      *count = 0;
      return NULL;
   }

   memset(configs, 0, *count * sizeof(__GLXvisualConfig));
   for (i = 0; i < *count; i++) {
      configs[i].vid = 0x23 + i;         /* XXX a hack! */
      configs[i].class = TrueColor;
      configs[i].rgba = 1;
      configs[i].redSize = 8;
      configs[i].greenSize = 8;
      configs[i].blueSize = 8;
      configs[i].alphaSize = 8;
      configs[i].doubleBuffer = 1;
      configs[i].bufferSize = 24;
      configs[i].depthSize = 24;
      configs[i].stencilSize = i * 8;
   }
   return configs;
}


/*
 * Dummy version
 */
static Bool
XF86DRI_GetClientDriverName(Display* dpy, int screen,
                           int* ddxDriverMajorVersion,
                           int* ddxDriverMinorVersion,
                           int* ddxDriverPatchVersion,
                           char** clientDriverName)
{
   (void) dpy;
   (void) screen;
   *ddxDriverMajorVersion = 4;
   *ddxDriverMinorVersion = 0;
   *ddxDriverPatchVersion = 1;
   *clientDriverName = "r200";
   return True;
}



/*
** Allocate the memory for the per screen configs for each screen.
** If that works then fetch the per screen configs data.
*/
static Bool AllocAndFetchScreenConfigs(Display *dpy, __GLXdisplayPrivate *priv)
{
    __GLXscreenConfigs *psc;
    GLint i, screens;

    /*
    ** First allocate memory for the array of per screen configs.
    */
    screens = ScreenCount(dpy);
    psc = (__GLXscreenConfigs*) malloc(screens * sizeof(__GLXscreenConfigs));
    if (!psc) {
	return GL_FALSE;
    }
    memset(psc, 0, screens * sizeof(__GLXscreenConfigs));
    priv->screenConfigs = psc;
    
    /* XXX prototype solution: */
    psc->configs = XF86DRI_GetScreenConfigs( &psc->numConfigs );

    /* Initialize the direct rendering per screen data and functions */
    if (priv->createScreen && priv->createScreen[0]) {
       /* register glx extensions */
       __DRIdriver *driver = driGetDriver(dpy, 0);
       if (driver && driver->registerExtensionsFunc)
          (*driver->registerExtensionsFunc)();
       /* screen initialization (bootstrap the driver) */
       psc->driScreen.private =
          (*(priv->createScreen[0]))(dpy, 0, &psc->driScreen,
                                     psc->numConfigs,
                                     psc->configs);
    }

    return GL_TRUE;
}


/*
** Initialize the client side extension code.
*/
__GLXdisplayPrivate *__glXInitialize(Display* dpy)
{
    __GLXdisplayPrivate *dpyPriv;
    int major, minor;

    /* See if a display private already exists.  If so, return it */
    {
       __GLXdisplayPrivate *d;
       for (d = displayPrivates; d; d = d->next) {
          if (d->dpy == dpy)
             return d;
       }
    }

    /* See if the versions are compatible */
    major = 1;
    minor = 2;

    /*
    ** Allocate memory for all the pieces needed for this buffer.
    */
    dpyPriv = (__GLXdisplayPrivate *) malloc(sizeof(__GLXdisplayPrivate));
    if (!dpyPriv) {
	return 0;
    }
    memset(dpyPriv, 0, sizeof(__GLXdisplayPrivate));

    /*
    ** Init the display private and then read in the screen config
    ** structures from the server.
    */
    dpyPriv->majorVersion = major;
    dpyPriv->minorVersion = minor;
    dpyPriv->dpy = dpy;

    dpyPriv->serverGLXvendor = 0x0; 
    dpyPriv->serverGLXversion = 0x0;

#ifdef GLX_DIRECT_RENDERING
    /*
    ** Initialize the direct rendering per display data and functions.
    ** Note: This _must_ be done before calling any other DRI routines
    ** (e.g., those called in AllocAndFetchScreenConfigs).
    */
    if (!driInitDisplay(dpy, dpyPriv))
       return 0;
#endif

    if (!AllocAndFetchScreenConfigs(dpy, dpyPriv)) {
	free((char*) dpyPriv);
	return 0;
    }

    /* add to head */
    dpyPriv->next = displayPrivates;
    displayPrivates = dpyPriv;

    return dpyPriv;
}


GLXContext glXGetCurrentContext(void)
{
    GLXContext cx = __glXGetCurrentContext();
    return cx;
}


/* Return the DRI per screen structure */
__DRIscreen *__glXFindDRIScreen(Display *dpy, int scrn)
{
    __GLXdisplayPrivate *d;
    for (d = displayPrivates; d; d = d->next) {
       if (d->dpy == dpy) {
          __DRIscreen *pDRIScreen = &d->screenConfigs[scrn].driScreen;
          return pDRIScreen;
       }
    }
    return NULL;
}


/*
** Make a particular context current.
*/
Bool glXMakeCurrent(Display *dpy, GLXDrawable draw, GLXContext gc)
{
    GLXContext oldGC = __glXGetCurrentContext();

    /* Unbind the old direct rendering context */
    if (oldGC && oldGC != gc) {
	if (oldGC->driContext.private) {
	    int will_rebind = (gc && draw == oldGC->currentDrawable);
	    if (!(*oldGC->driContext.unbindContext)(oldGC->currentDpy,
						    oldGC->screen,
						    oldGC->currentDrawable,
						    oldGC,
						    will_rebind)) {
		/* The make current failed.  Just return GL_FALSE. */
		return False;
	    }
	}
    }

    /* Bind the direct rendering context to the drawable */
    if (gc && gc->driContext.private &&
        !(*gc->driContext.bindContext)(dpy, gc->screen, draw, gc)) {
       return False;
    }

    /* Update our notion of what is current */
    if (gc == oldGC) {
	/*
	** Even though the contexts are the same the drawable might have
	** changed.  Note that gc cannot be the dummy, and that oldGC
	** cannot be NULL, therefore if they are the same, gc is not
	** NULL and not the dummy.
	*/
        if (gc)
            gc->currentDrawable = draw;
    }
    else {
	if (oldGC) {
	    oldGC->currentDpy = 0;
	    oldGC->currentDrawable = None;
	}
	if (gc) {
	    __glXSetCurrentContext(gc);
	    gc->currentDpy = dpy;
	    gc->currentDrawable = draw;
	}
        else {
	    __glXSetCurrentContext(NULL);
            _glapi_set_dispatch(NULL);  /* no-op functions */
	}
    }
    return True;
}



/*
** Create a new context.
*/
GLXContext glXCreateContext(Display *dpy, XVisualInfo *vis,
			    GLXContext shareList, Bool allowDirect)
{
    GLXContext gc;
    __GLXdisplayPrivate *priv;

    if (!dpy || !vis)
       return NULL;

    /* Allocate our context record */
    gc = (GLXContext) malloc(sizeof(struct __GLXcontextRec));
    if (!gc) {
	/* Out of memory */
	return NULL;
    }
    memset(gc, 0, sizeof(struct __GLXcontextRec));

    /*
    ** Create the direct rendering context, if requested and
    ** available.
    */
    priv = __glXInitialize(dpy);
    if (allowDirect) {
       __GLXscreenConfigs *psc = &priv->screenConfigs[vis->screen];
       if (psc && psc->driScreen.private) {
          void *shared = (shareList ?
                          shareList->driContext.private : NULL);
          gc->driContext.private =
             (*psc->driScreen.createContext)(dpy, vis, shared,
                                             &gc->driContext);
          if (!gc->driContext.private) {
             free(gc);
             return 0;
          }
          gc->screen = vis->screen;
          gc->vid = vis->visualid;
       }
    }

    return gc;
}


void __glXFreeContext(__GLXcontext *gc)
{
    free((char *) gc);
}


/*
** Destroy the named context
*/
void glXDestroyContext(Display *dpy, GLXContext gc)
{
   if (gc->driContext.private) {
      (*gc->driContext.destroyContext)(dpy, gc->screen,
                                       gc->driContext.private);
      gc->driContext.private = NULL;
   }
    __glXFreeContext(gc);
    printf(">>> %s %d\n", __FUNCTION__, __LINE__);
}


/*
** Return the major and minor version #s for the GLX extension
*/
Bool glXQueryVersion(Display *dpy, int *major, int *minor)
{
    *major = 1;
    *minor = 2;
    return True;
}

/*
** Query the existance of the GLX extension
*/
Bool glXQueryExtension(Display *dpy, int *errorBase, int *eventBase)
{
   *errorBase = 0;
   *eventBase = 0;
   return True;
}



void glXSwapBuffers(Display *dpy, GLXDrawable drawable)
{
    GLXContext gc = __glXGetCurrentContext();
    __GLXdisplayPrivate *priv;
    __DRIdrawable *pdraw;

    if (!gc)
       return;

    priv = __glXInitialize(dpy);
    {
	__GLXscreenConfigs *psc = &priv->screenConfigs[gc->screen];
	if (psc && psc->driScreen.private) {
	    /*
	    ** getDrawable returning NULL implies that the drawable is
	    ** not bound to a direct rendering context.
	    */
	    pdraw = (*psc->driScreen.getDrawable)(dpy, drawable,
						  psc->driScreen.private);
	    if (pdraw) {
		(*pdraw->swapBuffers)(dpy, pdraw->private);
	    }
	}
    }
}


/*
** Return the visual that best matches the template.  Return None if no
** visual matches the template.
*/
XVisualInfo *glXChooseVisual(Display *dpy, int screen, int *attribList)
{
    XVisualInfo visualTemplate;
    XVisualInfo *visualList;
    int i, count;

    /*
    ** Declare and initialize template variables
    */
    int bufferSize = 0;
    int level = 0;
    int rgba = 0;
    int doublebuffer = 0;
    int stereo = 0;
    int auxBuffers = 0;
    int redSize = 0;
    int greenSize = 0;
    int blueSize = 0;
    int alphaSize = 0;
    int depthSize = 0;
    int stencilSize = 0;
    int accumRedSize = 0;
    int accumGreenSize = 0;
    int accumBlueSize = 0;
    int accumAlphaSize = 0;
    /* for visual_info extension */
    int visualType = 0;		
    int visualTypeValue = 0;

    /* Initialize the extension, if needed */
    __GLXdisplayPrivate *priv;
    priv = __glXInitialize(dpy);
    if (!priv) {
	/* No extension */
	return NULL;
    }

    /*
    ** Build a template from the defaults and the attribute list
    ** Free visual list and return if an unexpected token is encountered
    */
    while (*attribList != None) {
	switch (*attribList++) {
	  case GLX_USE_GL:
	    break;
	  case GLX_BUFFER_SIZE:
	    bufferSize = *attribList++;
	    break;
	  case GLX_LEVEL:
	    level = *attribList++;
	    break;
	  case GLX_RGBA:
	    rgba = 1;
	    break;
	  case GLX_DOUBLEBUFFER:
	    doublebuffer = 1;
	    break;
	  case GLX_STEREO:
	    stereo = 1;
	    break;
	  case GLX_AUX_BUFFERS:
	    auxBuffers = *attribList++;
	    break;
	  case GLX_RED_SIZE:
	    redSize = *attribList++;
	    break;
	  case GLX_GREEN_SIZE:
	    greenSize = *attribList++;
	    break;
	  case GLX_BLUE_SIZE:
	    blueSize = *attribList++;
	    break;
	  case GLX_ALPHA_SIZE:
	    alphaSize = *attribList++;
	    break;
	  case GLX_DEPTH_SIZE:
	    depthSize = *attribList++;
	    break;
	  case GLX_STENCIL_SIZE:
	    stencilSize = *attribList++;
	    break;
	  case GLX_ACCUM_RED_SIZE:
	    accumRedSize = *attribList++;
	    break;
	  case GLX_ACCUM_GREEN_SIZE:
	    accumGreenSize = *attribList++;
	    break;
	  case GLX_ACCUM_BLUE_SIZE:
	    accumBlueSize = *attribList++;
	    break;
	  case GLX_ACCUM_ALPHA_SIZE:
	    accumAlphaSize = *attribList++;
	    break;
	  case GLX_X_VISUAL_TYPE_EXT:
	    visualType = 1;
	    visualTypeValue = *attribList++;
	    break;
	  default:
	    return NULL;
	}
    }

    /* search list of __GLXscreenConfigs to match requested visual */
    for (i = 0; i < priv->screenConfigs[screen].numConfigs; i++) {
       const __GLXvisualConfig *config = priv->screenConfigs[screen].configs + i;
       if (doublebuffer && !config->doubleBuffer) {
          /* no match */
          continue;
       }
       if (rgba && !config->rgba)
          continue;
       if (config->redSize < redSize ||
           config->blueSize < blueSize ||
           config->greenSize < greenSize ||
           config->alphaSize < alphaSize)
          continue;
       if (config->depthSize < depthSize)
          continue;
       if (config->stencilSize < stencilSize)
          continue;
       /* found a good match! */
       visualTemplate.screen = screen;
       visualTemplate.visualid = config->vid;
       visualList = XGetVisualInfo(dpy,VisualScreenMask|VisualIDMask,&visualTemplate,&count);
       return visualList;
    }

    /* didn't find a match */
    return NULL;
}


const char *glXQueryExtensionsString( Display *dpy, int screen )
{
    (void) dpy;
    (void) screen;
    return "GLX_ARB_get_proc_address";
}


const char *glXGetClientString( Display *dpy, int name )
{
    switch(name) {
	case GLX_VENDOR:
	    return (__glXGLXClientVendorName);
	case GLX_VERSION:
	    return (__glXGLXClientVersion);
	case GLX_EXTENSIONS:
	    return (__glXGLXClientExtensions);
	default:
	    return NULL;
    }
}


const char *glXQueryServerString( Display *dpy, int screen, int name )
{
    (void) dpy;
    (void) screen;
    switch (name) {
    case GLX_VENDOR:
       return "Tungsten Graphics, Inc.";
    case GLX_VERSION:
       return "1.2";
    case GLX_EXTENSIONS:
       return "GLX_ARB_get_proc_address";
    default:
       return NULL;
    }
}



Bool glXIsDirect( Display *dpy, GLXContext ctx )
{
   return True;
}

void glXWaitX( void )
{
   return;
}



/* strdup() is actually not a standard ANSI C or POSIX routine.
 * Irix will not define it if ANSI mode is in effect.
 */
char *
__glXstrdup(const char *str)
{
   char *copy;
   copy = (char *) malloc(strlen(str) + 1);
   if (!copy)
      return NULL;
   strcpy(copy, str);
   return copy;
}

/*
** glXGetProcAddress support
*/

struct name_address_pair {
   const char *Name;
   GLvoid *Address;
   struct name_address_pair *Next;
};

static struct name_address_pair GLX_functions[] = {
   /*** GLX_VERSION_1_0 ***/
   { "glXChooseVisual", (GLvoid *) glXChooseVisual, NULL },
   { "glXCreateContext", (GLvoid *) glXCreateContext, NULL },
   { "glXDestroyContext", (GLvoid *) glXDestroyContext, NULL },
   { "glXMakeCurrent", (GLvoid *) glXMakeCurrent, NULL },
   { "glXQueryExtension", (GLvoid *) glXQueryExtension, NULL },
   { "glXQueryVersion", (GLvoid *) glXQueryVersion, NULL },
   { "glXSwapBuffers", (GLvoid *) glXSwapBuffers, NULL },

   /*** GLX_VERSION_1_1 ***/
   { "glXGetClientString", (GLvoid *) glXGetClientString, NULL },
   { "glXQueryExtensionsString", (GLvoid *) glXQueryExtensionsString, NULL },
   { "glXQueryServerString", (GLvoid *) glXQueryServerString, NULL },

   /*** GLX_ARB_get_proc_address ***/
   { "glXGetProcAddressARB", (GLvoid *) glXGetProcAddressARB, NULL },

   /*** GLX 1.4 ***/
   { "glXGetProcAddress", (GLvoid *) glXGetProcAddress, NULL },

   { NULL, NULL, NULL }   /* end of list */
};


static const GLvoid *
get_glx_proc_address(const char *funcName)
{
   GLuint i;

   /* try static functions */
   for (i = 0; GLX_functions[i].Name; i++) {
      if (strcmp(GLX_functions[i].Name, funcName) == 0)
         return GLX_functions[i].Address;
   }
   return NULL;
}


void (*glXGetProcAddressARB(const GLubyte *procName))( void )
{
   typedef void (*gl_function)( void );
   gl_function f;

   f = (gl_function) get_glx_proc_address((const char *) procName);
   if (f) {
      return f;
   }
#if defined(GLX_DIRECT_RENDERING)
   else if (procName[0] == 'g' && procName[1] == 'l' && procName[2] == 'X') {
      /* The user might be asking for a glX function that might be
       * dynamically added by a driver.  Call __glXRegisterExtensions()
       * to try to make that happen.
       */
      __glXRegisterExtensions();
      f = (gl_function) get_glx_proc_address((const char *) procName);
      return f; /* may be NULL */
   }
#endif
   /* try regular "gl*" functions */
   f = (gl_function) _glapi_get_proc_address((const char *) procName);
   return f;
}

/* GLX 1.4 */
void (*glXGetProcAddress(const GLubyte *procName))( void )
{
   return glXGetProcAddressARB(procName);
}


#ifdef BUILT_IN_DRI_DRIVER

extern void *__driCreateScreen(Display *dpy, int scrn, __DRIscreen *psc,
                               int numConfigs, __GLXvisualConfig *config);


#else /* BUILT_IN_DRI_DRIVER */

#ifndef DEFAULT_DRIVER_DIR
/* this is normally defined in the Imakefile */
#define DEFAULT_DRIVER_DIR "/usr/X11R6/lib/modules/dri"
#endif

static __DRIdriver *Drivers = NULL;


/*
 * printf wrappers
 */

static void InfoMessageF(const char *f, ...)
{
    va_list args;
    const char *env;

    if ((env = getenv("LIBGL_DEBUG")) && strstr(env, "verbose")) {
	fprintf(stderr, "libGL: ");
	va_start(args, f);
	vfprintf(stderr, f, args);
	va_end(args);
    }
}

static void ErrorMessageF(const char *f, ...)
{
    va_list args;

    if (getenv("LIBGL_DEBUG")) {
	fprintf(stderr, "libGL error: ");
	va_start(args, f);
	vfprintf(stderr, f, args);
	va_end(args);
    }
    exit(1);
}


/*
 * We'll save a pointer to this function when we couldn't find a
 * direct rendering driver for a given screen.
 */
static void *DummyCreateScreen(Display *dpy, int scrn, __DRIscreen *psc,
                               int numConfigs, __GLXvisualConfig *config)
{
    (void) dpy;
    (void) scrn;
    (void) psc;
    (void) numConfigs;
    (void) config;
    return NULL;
}



/*
 * Extract the ith directory path out of a colon-separated list of
 * paths.
 * Input:
 *   index - index of path to extract (starting at zero)
 *   paths - the colon-separated list of paths
 *   dirLen - max length of result to store in <dir>
 * Output:
 *   dir - the extracted directory path, dir[0] will be zero when
 *         extraction fails.
 */
static void ExtractDir(int index, const char *paths, int dirLen, char *dir)
{
   int i, len;
   const char *start, *end;

   /* find ith colon */
   start = paths;
   i = 0;
   while (i < index) {
      if (*start == ':') {
         i++;
         start++;
      }
      else if (*start == 0) {
         /* end of string and couldn't find ith colon */
         dir[0] = 0;
         return;
      }
      else {
         start++;
      }
   }

   while (*start == ':')
      start++;

   /* find next colon, or end of string */
   end = start + 1;
   while (*end != ':' && *end != 0) {
      end++;
   }

   /* copy string between <start> and <end> into result string */
   len = end - start;
   if (len > dirLen - 1)
      len = dirLen - 1;
   strncpy(dir, start, len);
   dir[len] = 0;
}


/*
 * Try to dlopen() the named driver.  This function adds the
 * "_dri.so" suffix to the driver name and searches the
 * directories specified by the LIBGL_DRIVERS_PATH env var
 * in order to find the driver.
 * Input:
 *   driverName - a name like "tdfx", "i810", "mga", etc.
 * Return:
 *   handle from dlopen, or NULL if driver file not found.
 */
static __DRIdriver *OpenDriver(const char *driverName)
{
   char *libPaths = NULL;
   int i;
   __DRIdriver *driver;

   /* First, search Drivers list to see if we've already opened this driver */
   for (driver = Drivers; driver; driver = driver->next) {
      if (strcmp(driver->name, driverName) == 0) {
         /* found it */
         return driver;
      }
   }

   if (geteuid() == getuid()) {
      /* don't allow setuid apps to use LIBGL_DRIVERS_PATH */
      libPaths = getenv("LIBGL_DRIVERS_PATH");
      if (!libPaths)
         libPaths = getenv("LIBGL_DRIVERS_DIR"); /* deprecated */
   }
   if (!libPaths)
      libPaths = DEFAULT_DRIVER_DIR;

   for (i = 0; ; i++) {
      char libDir[1000], realDriverName[200];
      void *handle;
      ExtractDir(i, libPaths, 1000, libDir);
      if (!libDir[0])
         break; /* ran out of paths to search */
      snprintf(realDriverName, 200, "%s/%s_dri.so", libDir, driverName);
      InfoMessageF("OpenDriver: trying %s\n", realDriverName);
      handle = dlopen(realDriverName, RTLD_NOW | RTLD_GLOBAL);
      if (handle) {
         /* allocate __DRIdriver struct */
         driver = (__DRIdriver *) malloc(sizeof(__DRIdriver));
         if (!driver)
            return NULL; /* out of memory! */
         /* init the struct */
         driver->name = __glXstrdup(driverName);
         if (!driver->name) {
            free(driver);
            return NULL; /* out of memory! */
         }
         driver->createScreenFunc = (CreateScreenFunc)
            dlsym(handle, "__driCreateScreen");
         if (!driver->createScreenFunc) {
            /* If the driver doesn't have this symbol then something's
             * really, really wrong.
             */
            ErrorMessageF("__driCreateScreen() not defined in %s_dri.so!\n",
                          driverName);
            free(driver);
            dlclose(handle);
            continue;
         }
         driver->registerExtensionsFunc = (RegisterExtensionsFunc)
            dlsym(handle, "__driRegisterExtensions");
         driver->handle = handle;
         /* put at head of linked list */
         driver->next = Drivers;
         Drivers = driver;
         return driver;
      }
      else {
	 ErrorMessageF("dlopen %s failed (%s)\n", realDriverName, dlerror());
      }
   }

   ErrorMessageF("unable to find driver: %s_dri.so\n", driverName);
   exit(1);
   return NULL;
}


/*
 * Given a display pointer and screen number, determine the name of
 * the DRI driver for the screen. (I.e. "r128", "tdfx", etc).
 * Return True for success, False for failure.
 */
static Bool GetDriverName(Display *dpy, int scrNum, char **driverName)
{
   int driverMajor, driverMinor, driverPatch;
   Bool b;

   b = XF86DRI_GetClientDriverName(dpy, scrNum, &driverMajor, &driverMinor,
                                  &driverPatch, driverName);

   InfoMessageF("XF86DRIGetClientDriverName: %d.%d.%d %s (screen %d)\n",
	     driverMajor, driverMinor, driverPatch, *driverName, scrNum);

   return True;
}


/*
 * Given a display pointer and screen number, return a __DRIdriver handle.
 * Return NULL if anything goes wrong.
 */
static __DRIdriver *driGetDriver(Display *dpy, int scrNum)
{
   char *driverName;

   if (GetDriverName(dpy, scrNum, &driverName)) {
      return OpenDriver(driverName);
   }
   return NULL;
}


#endif /* BUILT_IN_DRI_DRIVER */


/* This function isn't currently used.
 */
static void driDestroyDisplay(Display *dpy, __GLXdisplayPrivate *ddpyp)
{
    if (ddpyp) {
        const int numScreens = ScreenCount(dpy);
        int i;
        for (i = 0; i < numScreens; i++) {
            if (ddpyp->libraryHandles[i])
                dlclose(ddpyp->libraryHandles[i]);
        }
        free(ddpyp->libraryHandles);
    }
}


/*
 * This is called from __glXInitialize() when we are given a new
 * display pointer.
 */
static Bool driInitDisplay(Display *dpy, __GLXdisplayPrivate *pdisp)
{
    const int numScreens = ScreenCount(dpy);
#if 0
    int eventBase, errorBase;
#endif
    int scrn;

    /* Initialize these fields to NULL in case we fail.
     * If we don't do this we may later get segfaults trying to free random
     * addresses when the display is closed.
     */
    pdisp->destroyDisplay = NULL;
    pdisp->createScreen = NULL;

#if 0
    if (!XF86DRIQueryExtension(dpy, &eventBase, &errorBase)) {
	return False;
    }
#endif

    pdisp->destroyDisplay = driDestroyDisplay;

    /* allocate array of pointers to createScreen funcs */
    pdisp->createScreen = (CreateScreenFunc *) malloc(numScreens * sizeof(void *));
    if (!pdisp->createScreen) {
       return False;
    }

    /* allocate array of library handles */
    pdisp->libraryHandles = (void **) malloc(numScreens * sizeof(void*));
    if (!pdisp->libraryHandles) {
       free(pdisp->createScreen);
       return False;
    }

#ifdef BUILT_IN_DRI_DRIVER
    /* we'll statically bind to the built-in __driCreateScreen function */
    for (scrn = 0; scrn < numScreens; scrn++) {
       pdisp->createScreen[scrn] = __driCreateScreen;
       pdisp->libraryHandles[scrn] = NULL;
    }

#else
    /* dynamically discover DRI drivers for all screens, saving each
     * driver's "__driCreateScreen" function pointer.  That's the bootstrap
     * entrypoint for all DRI drivers.
     */
    __glXRegisterExtensions();
    for (scrn = 0; scrn < numScreens; scrn++) {
        __DRIdriver *driver = driGetDriver(dpy, scrn);
        if (driver) {
           pdisp->createScreen[scrn] = driver->createScreenFunc;
           pdisp->libraryHandles[scrn] = driver->handle;
        }
        else {
           pdisp->createScreen[scrn] = DummyCreateScreen;
           pdisp->libraryHandles[scrn] = NULL;
        }
    }
#endif

    return True;
}



/*
** Here we'll query the DRI driver for each screen and let each
** driver register its GL extension functions.  We only have to
** do this once.
**
** In older versions of libGL (prior to October 2002) we _always_
** called this function during libGL start-up.  Now, we only call
** it from glXGetProcAddress() as a last resort.
**
** Two key things changed along the way:
** 1. _glapi_get_proc_address() now generates new dispatch stub functions
**    anytime it gets an unknown "gl*" function name.  I.e. we always return
**    a valid function address and later patch it up to use the correct
**    dispatch offset.
** 2. The GL API dispatch table is a fixed size (with plenty of extra slots).
**    This means we don't have to register all new functions before we create
**    the first dispatch table.
*/
void
__glXRegisterExtensions(void)
{
#ifndef BUILT_IN_DRI_DRIVER
   static GLboolean alreadyCalled = GL_FALSE;
   int displayNum, maxDisplays;

   if (alreadyCalled)
      return;
   alreadyCalled = GL_TRUE;

   if (getenv("LIBGL_MULTIHEAD")) {
      /* we'd like to always take this path but doing so causes a second
       * or more of delay while the XOpenDisplay() function times out.
       */
      maxDisplays = 10;  /* infinity, really */
   }
   else {
      /* just open the :0 display */
      maxDisplays = 1;
   }

   for (displayNum = 0; displayNum < maxDisplays; displayNum++) {
      char displayName[200];
      Display *dpy;
      snprintf(displayName, 199, ":%d.0", displayNum);
      dpy = XOpenDisplay(displayName);
      if (dpy) {
         const int numScreens = ScreenCount(dpy);
         int screenNum;
         for (screenNum = 0; screenNum < numScreens; screenNum++) {
            __DRIdriver *driver = driGetDriver(dpy, screenNum);
            if (driver && driver->registerExtensionsFunc) {
               (*driver->registerExtensionsFunc)();
            }
         }
         XCloseDisplay(dpy);
      }
      else {
         break;
      }
   }
#endif
}

