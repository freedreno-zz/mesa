/* $Id: miniglx.c,v 1.1.4.18 2002/12/20 01:28:15 jrfonseca Exp $ */

/*
 * Mesa 3-D graphics library
 * Version:  4.1
 *
 * Copyright (C) 1999-2002  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


/**
 * \file miniglx.c
 * \brief Mini GLX interface, layered on fbdev.
 * \author Brian Paul
 * \note *PROTOTYPE*
 */

/**
 * \mainpage Mini GLX
 *
 * \section intro Introduction
 *
 * The Mini GLX interface facilitates OpenGL rendering on embedded devices. The
 * interface is a subset of the GLX interface, plus a minimal set of Xlib-like
 * functions.
 *
 * Programs written to the Mini GLX specification should run unchanged on
 * systems with the X Window System and the GLX extension. The intention is to
 * allow flexibility for prototyping and testing.
 *
 * \section references References
 *
 * - Mini GLX Specification, Tungsten Graphics, Inc.
 * - OpenGL Graphics with the X Window System, Silicon Graphics, Inc.,
 *   ftp://ftp.sgi.com/opengl/doc/opengl1.2/glx1.3.ps
 * - XFree86 Man pages, The XFree86 Project, Inc.,
 *   http://www.xfree86.org/current/manindex3.html
 *  
 */

/*
 * Notes on the XVisualInfo, Visual, and __GLXvisualConfig data types:
 *
 * 1. X is kind of silly in that it has two (or three) datatypes which
 *    describe visuals.  In a perfect world there would just be one.
 * 
 * 2. We need the __GLXvisualConfig type to augment XVisualInfo and Visual
 *    because we need to describe the GLX-specific attributes of visuals.
 *
 * 3. In this interface there is a one-to-one-to-one correspondence between
 *    the three types and they're all interconnected.
 *
 * 4. The XVisualInfo type has a pointer to a Visual.  The Visual structure
 *    (aka MiniGLXVisualRec) has a pointer to the __GLXvisualConfig.  The
 *    Visual structure also has a pointer pointing back to the XVisualInfo.
 *
 * 5. The XVisualInfo structure is the only one who's contents are public.
 *
 * 6. The glXChooseVisual and XGetVisualInfo are the only functions that
 *    return XVisualInfo structures.  They can be freed with XFree(), though
 *    there is a small memory leak.
 */


#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <linux/kd.h>
#include <linux/vt.h>

#include "miniglxP.h"

#include "glapi.h"

#define MALLOC(N) malloc(N)
#define CALLOC(N) calloc(1, N)
#define CALLOC_STRUCT(T) ((struct T *) calloc(1, sizeof(struct T)))
#define FREE(P)   free(P)
#define STRCMP(A, B)  strcmp(A, B)



#define PF_B8G8R8     1
#define PF_B8G8R8A8   2
#define PF_B5G6R5     3
#define PF_B5G5R5     4
#define PF_CI8        5



static GLXContext CurrentContext = NULL;


/**********************************************************************/
/* FBdev functions                                                    */
/**********************************************************************/


/*
 * Do first part of setting up fbdev.  This is called during XOpenDisplay().
 */
static GLboolean
OpenFBDev( Display *dpy )
{
   char ttystr[1000];
   int fd, vtnumber, ttyfd;

   assert(dpy);

   if (geteuid()) {
      fprintf(stderr, "error: you need to be root\n");
      return GL_FALSE;
   }

   /* open /dev/tty0 and get the vt number */
   if ((fd = open("/dev/tty0", O_WRONLY, 0)) < 0) {
      fprintf(stderr, "error opening /dev/tty0\n");
      return GL_FALSE;
   }
   if (ioctl(fd, VT_OPENQRY, &vtnumber) < 0 || vtnumber < 0) {
      fprintf(stderr, "error: couldn't get a free vt\n");
      return GL_FALSE;
   }
   close(fd);

   /* open the console tty */
   sprintf(ttystr, "/dev/tty%d", vtnumber);  /* /dev/tty1-64 */
   dpy->ConsoleFD = open(ttystr, O_RDWR | O_NDELAY, 0);
   if (dpy->ConsoleFD < 0) {
      fprintf(stderr, "error couldn't open console fd\n");
      return GL_FALSE;
   }

   /* save current vt number */
   {
      struct vt_stat vts;
      if (ioctl(dpy->ConsoleFD, VT_GETSTATE, &vts) == 0)
         dpy->OriginalVT = vts.v_active;
   }

   /* disconnect from controlling tty */
   ttyfd = open("/dev/tty", O_RDWR);
   if (ttyfd >= 0) {
      ioctl(ttyfd, TIOCNOTTY, 0);
      close(ttyfd);
   }

   /* some magic to restore the vt when we exit */
   {
      struct vt_mode vt;
      if (ioctl(dpy->ConsoleFD, VT_ACTIVATE, vtnumber) != 0)
         printf("ioctl VT_ACTIVATE: %s\n", strerror(errno));
      if (ioctl(dpy->ConsoleFD, VT_WAITACTIVE, vtnumber) != 0)
         printf("ioctl VT_WAITACTIVE: %s\n", strerror(errno));

      if (ioctl(dpy->ConsoleFD, VT_GETMODE, &vt) < 0) {
         fprintf(stderr, "error: ioctl VT_GETMODE: %s\n", strerror(errno));
         return GL_FALSE;
      }

      vt.mode = VT_PROCESS;
      vt.relsig = SIGUSR1;
      vt.acqsig = SIGUSR1;
      if (ioctl(dpy->ConsoleFD, VT_SETMODE, &vt) < 0) {
         fprintf(stderr, "error: ioctl(VT_SETMODE) failed: %s\n",
                 strerror(errno));
         return GL_FALSE;
      }
   }

   /* go into graphics mode */
   if (ioctl(dpy->ConsoleFD, KDSETMODE, KD_GRAPHICS) < 0) {
      fprintf(stderr, "error: ioctl(KDSETMODE, KD_GRAPHICS) failed: %s\n",
              strerror(errno));
      return GL_FALSE;
   }

   /* open the framebuffer device */
   dpy->FrameBufferFD = open(dpy->fbdevDevice, O_RDWR);
   if (dpy->FrameBufferFD < 0) {
      fprintf(stderr, "Error opening /dev/fb0: %s\n", strerror(errno));
      return GL_FALSE;
   }

  /* get the original variable screen info */
   if (ioctl(dpy->FrameBufferFD, FBIOGET_VSCREENINFO, &dpy->OrigVarInfo)) {
      fprintf(stderr, "error: ioctl(FBIOGET_VSCREENINFO) failed: %s\n",
              strerror(errno));
      return GL_FALSE;
   }

   /* make copy */
   dpy->VarInfo = dpy->OrigVarInfo;  /* structure copy */

   return GL_TRUE;
}



/*
 * Setup up our desired fbdev framebuffer mode.  This is called during
 * XCreateWindow.
 */
static GLboolean
SetupFBDev( Display *dpy, Window win )
{
   const int width = win->w;
   const int height = win->h;

   assert(dpy);

   /* set the depth, resolution, etc */
   dpy->VarInfo = dpy->OrigVarInfo;
   dpy->VarInfo.bits_per_pixel = win->visual->visInfo->bits_per_rgb;
   dpy->VarInfo.xres_virtual = width;
   dpy->VarInfo.yres_virtual = height;
   dpy->VarInfo.xres = width;
   dpy->VarInfo.yres = height;
   dpy->VarInfo.xoffset = 0;
   dpy->VarInfo.yoffset = 0;
   dpy->VarInfo.nonstd = 0;
   dpy->VarInfo.vmode &= ~FB_VMODE_YWRAP; /* turn off scrolling */

   if (dpy->VarInfo.bits_per_pixel == 32) {
      assert(win->visual->pixelFormat == PF_B8G8R8A8);
      dpy->VarInfo.red.offset = 16;
      dpy->VarInfo.green.offset = 8;
      dpy->VarInfo.blue.offset = 0;
      dpy->VarInfo.transp.offset = 24;
      dpy->VarInfo.red.length = 8;
      dpy->VarInfo.green.length = 8;
      dpy->VarInfo.blue.length = 8;
      dpy->VarInfo.transp.length = 8;
   }
   else if (dpy->VarInfo.bits_per_pixel == 16) {
      assert(win->visual->pixelFormat == PF_B5G5R5);
      dpy->VarInfo.red.offset = 11;
      dpy->VarInfo.green.offset = 5;
      dpy->VarInfo.blue.offset = 0;
      dpy->VarInfo.red.length = 5;
      dpy->VarInfo.green.length = 6;
      dpy->VarInfo.blue.length = 5;
      dpy->VarInfo.transp.offset = 0;
      dpy->VarInfo.transp.length = 0;
   }
   else if (dpy->VarInfo.bits_per_pixel == 8) {
      assert(win->visual->pixelFormat == PF_CI8);
   }
   else {
      assert(0);
   }

   if (width == 1280 && height == 1024) {
      /* timing values taken from /etc/fb.modes (1280x1024 @ 75Hz) */
      dpy->VarInfo.pixclock = 7408;
      dpy->VarInfo.left_margin = 248;
      dpy->VarInfo.right_margin = 16;
      dpy->VarInfo.upper_margin = 38;
      dpy->VarInfo.lower_margin = 1;
      dpy->VarInfo.hsync_len = 144;
      dpy->VarInfo.vsync_len = 3;
   }
   else if (width == 1024 && height == 768) {
      /* timing values taken from /etc/fb.modes (1024x768 @ 75Hz) */
      dpy->VarInfo.pixclock = 12699;
      dpy->VarInfo.left_margin = 176;
      dpy->VarInfo.right_margin = 16;
      dpy->VarInfo.upper_margin = 28;
      dpy->VarInfo.lower_margin = 1;
      dpy->VarInfo.hsync_len = 96;
      dpy->VarInfo.vsync_len = 3;
   }
   else if (width == 800 && height == 600) {
      /* timing values taken from /etc/fb.modes (800x600 @ 75Hz) */
      dpy->VarInfo.pixclock = 20203;
      dpy->VarInfo.left_margin = 160;
      dpy->VarInfo.right_margin = 16;
      dpy->VarInfo.upper_margin = 21;
      dpy->VarInfo.lower_margin = 1;
      dpy->VarInfo.hsync_len = 80;
      dpy->VarInfo.vsync_len = 3;
   }
   else {
      /* XXX need timings for other screen sizes */
      fprintf(stderr, "XXXX screen size %d x %d not supported at this time!\n",
             width, height);
      abort();
   }

   /* set variable screen info */
   if (ioctl(dpy->FrameBufferFD, FBIOPUT_VSCREENINFO, &dpy->VarInfo)) {
      fprintf(stderr, "Unable to set screen to depth %d\n", dpy->DesiredDepth);
      return GL_FALSE;
   }

   /* Get the fixed screen info */
   if (ioctl(dpy->FrameBufferFD, FBIOGET_FSCREENINFO, &dpy->FixedInfo)) {
      fprintf(stderr, "error: ioctl(FBIOGET_FSCREENINFO) failed: %s\n",
              strerror(errno));
      return GL_FALSE;
   }

   if (dpy->FixedInfo.visual != FB_VISUAL_TRUECOLOR &&
       dpy->FixedInfo.visual != FB_VISUAL_DIRECTCOLOR) {
      fprintf(stderr, "non-TRUECOLOR visuals not supported by this demo.\n");
      return GL_FALSE;
   }

   if (dpy->FixedInfo.visual == FB_VISUAL_DIRECTCOLOR) {
      struct fb_cmap cmap;
      unsigned short red[256], green[256], blue[256];
      int i;

      /* we're assuming 256 entries here */
      cmap.start = 0;
      cmap.len = 256;
      cmap.red   = red;
      cmap.green = green;
      cmap.blue  = blue;
      cmap.transp = NULL;
      for (i = 0; i < cmap.len; i++) {
         red[i] = green[i] = blue[i] = (i << 8) | i;
      }
      if (ioctl(dpy->FrameBufferFD, FBIOPUTCMAP, (void *) &cmap) < 0) {
         fprintf(stderr, "ioctl(FBIOPUTCMAP) failed [%d]\n", i);
      }
   }

   /* mmap the framebuffer into our address space */
   dpy->FrameBufferSize = dpy->FixedInfo.smem_len;
   dpy->FrameBuffer = (caddr_t) mmap(0, /* start */
                                     dpy->FrameBufferSize, /* bytes */
                                     PROT_READ | PROT_WRITE, /* prot */
                                     MAP_SHARED, /* flags */
                                     dpy->FrameBufferFD, /* fd */
                                     0 /* offset */);
   if (dpy->FrameBuffer == (caddr_t) - 1) {
      fprintf(stderr, "error: unable to mmap framebuffer: %s\n",
              strerror(errno));
      return GL_FALSE;
   }

   dpy->cpp = dpy->VarInfo.bits_per_pixel / 8;

   if (0)
   {
      int x, y;
      char *scrn = (char *)dpy->FrameBuffer;

      fprintf(stderr, "scrn: %p bottom %p\n",
	      scrn, scrn+800*599*4);

      for (y = 100 ; y < 200 ; y++)
	 for (x = 100 ; x < 200 ; x++) {
	    scrn[(x+y*800)*4+0] = 255;
	    scrn[(x+y*800)*4+1] = 0;
	    scrn[(x+y*800)*4+2] = 255;
	    scrn[(x+y*800)*4+3] = 255;
	 }
   }
	    

   /* mmap the MMIO region into our address space */
   dpy->MMIOSize = dpy->FixedInfo.mmio_len;
   dpy->MMIOAddress = (caddr_t) mmap(0, /* start */
                                     dpy->MMIOSize, /* bytes */
                                     PROT_READ | PROT_WRITE, /* prot */
                                     MAP_SHARED, /* flags */
                                     dpy->FrameBufferFD, /* fd */
                                     dpy->FixedInfo.smem_len /* offset */);
   if (dpy->MMIOAddress == (caddr_t) - 1) {
      fprintf(stderr, "error: unable to mmap mmio region: %s\n",
              strerror(errno));
      return GL_FALSE;
   }

   /* TODO:  Tell kernel not to use accelerated functions -- see fbdevhw.c */

   return GL_TRUE;
}



/*
 * Restore framebuffer to state it was in before we started.
 * Called from XDestroyWindow().
 */
static GLboolean
RestoreFBDev( Display *dpy )
{
   /* restore original variable screen info */
   if (ioctl(dpy->FrameBufferFD, FBIOPUT_VSCREENINFO, &dpy->OrigVarInfo)) {
      fprintf(stderr, "ioctl(FBIOPUT_VSCREENINFO failed): %s\n",
              strerror(errno));
      return GL_FALSE;
   }
   dpy->VarInfo = dpy->OrigVarInfo;
   return GL_TRUE;
}



/*
 * Close FBDev.  Called from XCloseDisplay().
 */
static void
CleanupFBDev( Display *dpy )
{
   struct vt_mode VT;

   munmap(dpy->FrameBuffer, dpy->FrameBufferSize);
   munmap(dpy->MMIOAddress, dpy->MMIOSize);
   close(dpy->FrameBufferFD);

   /* restore text mode */
   ioctl(dpy->ConsoleFD, KDSETMODE, KD_TEXT);

   /* set vt */
   if (ioctl(dpy->ConsoleFD, VT_GETMODE, &VT) != -1) {
      VT.mode = VT_AUTO;
      ioctl(dpy->ConsoleFD, VT_SETMODE, &VT);
   }

   /* restore original vt */
   if (dpy->OriginalVT >= 0) {
      ioctl(dpy->ConsoleFD, VT_ACTIVATE, dpy->OriginalVT);
      dpy->OriginalVT = -1;
   }

   close(dpy->ConsoleFD);
}


/**********************************************************************/
/* Misc functions needed for DRI drivers                              */
/**********************************************************************/

__DRIscreen *
__glXFindDRIScreen(Display *dpy, int scrn)
{
   (void) scrn;
   return &(dpy->driScreen);
}

Bool
__glXWindowExists(Display *dpy, GLXDrawable draw)
{
   if (dpy->TheWindow == draw)
      return True;
   else
      return False;
}

unsigned long
_glthread_GetID(void)
{
   return 0;
}


/*
 * XXX This code might be moved into the driver.
 * The idea is to establish the set of visuals available for the display.
 * The DRI drivers (or dri_util) requires the __GLXvisualConfig data type.
 */
static void
InitializeScreenConfigs(int *numConfigs, __GLXvisualConfig **configs)
{
   int i;

   *numConfigs = 1;
   *configs = (__GLXvisualConfig *)
      CALLOC(*numConfigs * sizeof(__GLXvisualConfig));
   for (i = 0; i < *numConfigs; i++) {
      (*configs)[i].vid = 100 + i;
      (*configs)[i].class = TrueColor;
      (*configs)[i].rgba = True;
      (*configs)[i].redSize = 8;
      (*configs)[i].greenSize = 8;
      (*configs)[i].blueSize = 8;
      (*configs)[i].alphaSize = 8;
      (*configs)[i].redMask = 0xff0000;
      (*configs)[i].greenMask = 0xff00;
      (*configs)[i].blueMask = 0xff;
      (*configs)[i].alphaMask = 0xff000000;
      (*configs)[i].doubleBuffer = True;
      (*configs)[i].stereo = True;
      (*configs)[i].bufferSize = 32;
      (*configs)[i].depthSize = 24;
      (*configs)[i].stencilSize = 8;
      (*configs)[i].auxBuffers = 0;
      (*configs)[i].level = 0;
      /* leave remaining fields zero */
   }
}


/**********************************************************************/
/* Public API functions (Xlib and GLX)                                */
/**********************************************************************/


/* Replace with a config file read at runtime, eventually...
 */
int __read_config_file( Display *dpy )
{
   dpy->fbdevDevice = "/dev/fb0";
   dpy->clientDriverName = "radeon_dri.so";
   dpy->drmModuleName = "radeon";
   dpy->pciBus = 1;
   dpy->pciDevice = 0;
   dpy->pciFunc = 0;
   dpy->chipset = 0x5144;	/* radeon qd */
   dpy->pciBusID = malloc(64);
   sprintf((char *)dpy->pciBusID, "PCI:%d:%d:%d", 
	   dpy->pciBus, dpy->pciDevice, dpy->pciFunc);
}


/**
 * \brief Initialize the graphics system.
 * 
 * \param display_name currently ignored. It is recommended to pass it as NULL.
 * \return a pointer to a #Display if the function is able to initialize
 * the graphics system, NULL otherwise.
 * 
 * \note XXX: This function not stable.
 */
Display *
XOpenDisplay( const char *display_name )
{
   Display *dpy;

   dpy = (Display *) CALLOC(sizeof(Display));
   if (!dpy)
      return NULL;


   if (!__read_config_file( dpy )) {
      fprintf(stderr, "Couldn't get configuration details\n");
      FREE(dpy);
      return NULL;
   }


   if (!OpenFBDev(dpy)) {
      fprintf(stderr, "OpenFBDev failed\n");
      FREE(dpy);
      return NULL;
   }

   InitializeScreenConfigs(&dpy->numConfigs, &dpy->configs);

   /*
    * Begin DRI setup.
    * We're kind of combining the per-display and per-screen information
    * which was kept separate in XFree86/DRI's libGL.
    */
   dpy->dlHandle = dlopen(dpy->clientDriverName, RTLD_NOW | RTLD_GLOBAL);
   if (!dpy->dlHandle) {
      fprintf(stderr, "Unable to open %s: %s\n", dpy->clientDriverName,
	      dlerror());
      CleanupFBDev(dpy);
      FREE(dpy);
      return NULL;
   }

   dpy->driverInitFBDev = (InitFBDevFunc) dlsym(dpy->dlHandle, 
						"__driInitFBDev");
   if (!dpy->driverInitFBDev) {
      fprintf(stderr, "Couldn't find __driInitFBDev in %s\n",
              dpy->clientDriverName);
      dlclose(dpy->dlHandle);
      FREE(dpy);
      return NULL;
   }

   dpy->createScreen = (CreateScreenFunc) dlsym(dpy->dlHandle,
                                                "__driCreateScreen");
   if (!dpy->createScreen) {
      fprintf(stderr, "Couldn't find __driCreateScreen in %s\n",
              dpy->clientDriverName);
      dlclose(dpy->dlHandle);
      FREE(dpy);
      return NULL;
   }

   return dpy;
}


/**
 * \brief Release display resources.
 * 
 * When the application is about to exit, the resources associated with the
 * graphics system can be released by calling this function.
 * 
 * \param dpy display handle. It becomes invalid at this point.
 */
void
XCloseDisplay( Display *dpy )
{
   (*dpy->driScreen.destroyScreen)(dpy, 0, dpy->driScreen.private);
   dlclose(dpy->dlHandle);
   CleanupFBDev(dpy);
   FREE(dpy);
}


/**
 * \brief Window creation.
 *
 * \param dpy a #Display pointer, as returned by XOpenDisplay().
 * \param parent the parent window for the new window. For Mini GLX this should
 * be \code RootWindow(dpy, 0) \endcode .
 * \param x the window abscissa. For Mini GLX, it should be zero.
 * \param y the window ordinate. For Mini GLX, it should be zero.
 * \param width the window width. For Mini GLX, this specifies the desired
 * screen width such as 1024 or 1280. 
 * \param height the window height. For Mini GLX, this specifies the desired
 * screen height such as 768 or 1024.
 * \param border_width This parameter should be zero.
 * \param depth the window pixel depth. For Mini GLX this should be the depth
 * found in the #XVisualInfo object returned by glxChooseVisual() 
 * \param class the window class. For Mini GLX this value should be
 * #InputOutput.
 * \param visual the visual type. It should be the visual field of the
 * #XVisualInfo object returned by glxChooseVisual().
 * \param valuemask which fields of the XSetWindowAttributes() are to be used.
 * For Mini GLX this is typically the bitmask \code CWBackPixel | CWBorderPixel
 * | CWColormap \endcode
 * \param attributes initial window attributes. Of the fields in the
 * XSetWindowAttributes() structure, the \p background_pixel, \p border_pixel and
 * \p colormap fields should be set.
 *
 * \return a window handle if it succeeds or zero if it fails.
 * 
 * \note For Mini GLX, windows are full-screen; they cover the entire frame
 * buffer.  Also, Mini GLX imposes a limit of one window. A second window
 * cannot be created until the first one is destroyed.
 */
Window
XCreateWindow( Display *dpy, Window parent, int x, int y,
               unsigned int width, unsigned int height,
               unsigned int border_width, int depth, unsigned int class,
               Visual *visual, unsigned long valuemask,
               XSetWindowAttributes *attributes )
{
   Window win;

   /* ignored */
   (void) x;
   (void) y;
   (void) border_width;
   (void) depth;
   (void) class;
   (void) valuemask;
   (void) attributes;

   if (dpy->NumWindows > 0)
      return NULL;  /* only allow one window */

   assert(dpy->TheWindow == NULL);

   win = MALLOC(sizeof(struct MiniGLXWindowRec));
   if (!win)
      return NULL;


   /* init other per-window fields */
   win->x = 0;
   win->y = 0;
   win->w = width;
   win->h = height;
   win->visual = visual;  /* ptr assignment */

   /* do fbdev setup
    * TODO:  Let the driver influence the choice of window pitch.
    */
   if (!SetupFBDev(dpy, win)) {
      FREE(win);
      return NULL;
   }


   win->bytesPerPixel = dpy->VarInfo.bits_per_pixel / 8;
   win->rowStride = width * win->bytesPerPixel;
   win->size = win->rowStride * height * win->bytesPerPixel; /* XXX stride? */
   win->frontStart = dpy->FrameBuffer;
   win->frontBottom = (GLubyte *) win->frontStart
                    + (height - 1) * win->rowStride;

   if (visual->glxConfig->doubleBuffer) {
      win->backStart = (GLubyte *) win->frontStart + win->size;
      win->backBottom = (GLubyte *) win->backStart
                      + (height - 1) * win->rowStride;
      win->curBottom = win->backBottom;
   }
   else {
      /* single buffered */
      win->backStart = NULL;
      win->backBottom = NULL;
      win->curBottom = win->frontBottom;
   }


   /* Perform the initialization normally done in the X server */
   if (!dpy->driverInitFBDev( dpy )) {
      RestoreFBDev(dpy);
      FREE(win);
      return NULL;
   }

   /* Perform the client-side initialization.  Have to do this here as
    * it depends on the display resolution chosen, which in this
    * window system depends on the size of the "window" created.
    *
    * Clearly there is a limit of one on the number of windows in
    * existence at any time.
    *
    * Need to shut down drm and free dri data in XDestroyWindow, too.
    */
   dpy->driScreen.private = (*dpy->createScreen)(dpy, 0, &(dpy->driScreen),
                                                 dpy->numConfigs,
                                                 dpy->configs);
   if (!dpy->driScreen.private) {
      RestoreFBDev(dpy);
      FREE(win);
      return NULL;
   }



   win->driDrawable.private = dpy->driScreen.createDrawable(dpy, 0, win,
                             visual->visInfo->visualid, &(win->driDrawable));
   if (!win->driDrawable.private) {
      RestoreFBDev(dpy);
      FREE(win);
      return NULL;
   }

   dpy->NumWindows++;
   dpy->TheWindow = win;

   return win;
}


/**
 * \brief Destroy Window.
 *
 * \param dpy display handle.
 * \param win window handle.
 */
void
XDestroyWindow( Display *dpy, Window win )
{
   assert(dpy);
   if (win) {
      /* check if destroying the current buffer */
      Window curDraw = glXGetCurrentDrawable();
      if (win == curDraw) {
         glXMakeCurrent( dpy, NULL, NULL);
      }
      (*win->driDrawable.destroyDrawable)(dpy, win->driDrawable.private);
      /* put framebuffer back to initial state */
      RestoreFBDev(dpy);
      FREE(win);
      /* unlink window from display */
      dpy->NumWindows--;
      assert(dpy->NumWindows == 0);
      dpy->TheWindow = NULL;
   }
}


/**
 * \brief Map Window.
 *
 * \param dpy display handle.
 * \param w window handle.
 * 
 * \note This function does nothing in Mini GLX but is required for Xlib/GLX
 * compatibility.
 */
void
XMapWindow( Display *dpy, Window w )
{
   /* Only provided to ease porting.  no-op */
   (void) dpy;
   (void) w;
}


Colormap
XCreateColormap( Display *dpy, Window w, Visual *visual, int alloc )
{
   /* We only provide this function to ease porting.  Practically a no-op. */
   (void) dpy;
   (void) w;
   (void) visual;
   (void) alloc;
   return (Colormap) MALLOC(1);
}


void
XFreeColormap( Display *dpy, Colormap cmap )
{
   (void) dpy;
   (void) cmap;
   FREE(cmap);
}

void
XFree( void *pointer )
{
   FREE(pointer);
}


/**
 * \brief Query available visuals.
 *
 * \param dpy the display handle, as returned by XOpenDisplay().
 * \param visMask a bitmask indicating which fields of the \p vinfoTemplate are to
 * be matched.  The value must be #VisualScreenMask.
 * \param visTemplate a template whose fields indicate which visual attributes
 * must be matched by the results.  The \p screen field of this structure must
 * be zero.
 * \param numVisuals Returns the number of visuals returned.
 *
 * \return the address of an array of all available visuals.
 * 
 * An example of using XGetVisualInfo to get all available visuals follows:
 * 
 * \code
 * XVisualInfo visTemplate, *results;
 * int numVisuals;
 * Display *dpy = XOpenDisplay(NULL);
 * visTemplate.screen = 0;
 * results = XGetVisualInfo(dpy, VisualScreenMask, &visTemplate, &numVisuals);
 * \endcode
 * 
 */

/*
 * Return list of all XVisualInfos we have (one per __GLXvisualConfig).
 */
XVisualInfo *
XGetVisualInfo( Display *dpy, long visMask, XVisualInfo *visTemplate, int *numVisuals )
{
   XVisualInfo *results;
   Visual *visResults;
   int i, n;

   ASSERT(visMask == VisualScreenMask);
   ASSERT(visTemplate.screen == 0);

   n = dpy->numConfigs;
   results = (XVisualInfo *) CALLOC(n * sizeof(XVisualInfo));
   if (!results) {
      *numVisuals = 0;
      return NULL;
   }

   visResults = (Visual *) CALLOC(n * sizeof(Visual));
   if (!results) {
      FREE(results);
      *numVisuals = 0;
      return NULL;
   }

   for (i = 0; i < n; i++) {
      visResults[i].glxConfig = dpy->configs + i;
      visResults[i].visInfo = results + i;
      visResults[i].dpy = dpy;
      visResults[i].pixelFormat = 0;
      results[i].visual = visResults + i;
      results[i].visualid = dpy->configs[i].vid;
      results[i].class = TrueColor;
      results[i].depth = dpy->configs[i].redSize +
                         dpy->configs[i].greenSize +
                         dpy->configs[i].blueSize +
                         dpy->configs[i].alphaSize;
      results[i].bits_per_rgb = 32;
   }
   *numVisuals = n;
   return results;
}


/*
 * Return a pointer to an XVisualInfo which best matches the GLX parameters
 * specified by the attribs list.
 */
XVisualInfo*
glXChooseVisual( Display *dpy, int screen, int *attribs )
{
   Visual *vis;
   XVisualInfo *visInfo;
   const int *attrib;
   GLboolean rgbFlag = GL_FALSE, dbFlag = GL_FALSE, stereoFlag = GL_FALSE;
   GLint redBits = 0, greenBits = 0, blueBits = 0, alphaBits = 0;
   GLint indexBits = 0, depthBits = 0, stencilBits = 0;
   GLint accumRedBits = 0, accumGreenBits = 0;
   GLint accumBlueBits = 0, accumAlphaBits = 0;
   GLint numSamples = 0;
   int i;

   /*
    * XXX in the future, <screen> might be interpreted as a VT
    */
   ASSERT(dpy);
   ASSERT(screen == 0);

   vis = (Visual *) CALLOC(sizeof(Visual));
   if (!vis)
      return NULL;

   visInfo = (XVisualInfo *) MALLOC(sizeof(XVisualInfo));
   if (!visInfo) {
      FREE(vis);
      return NULL;
   }

   visInfo->visual = vis;
   vis->visInfo = visInfo;
   vis->dpy = dpy;

   /* parse the attribute list */
   for (attrib = attribs; attrib && *attrib != None; attrib++) {
      switch (attrib[0]) {
      case GLX_DOUBLEBUFFER:
         dbFlag = GL_TRUE;
         break;
      case GLX_RGBA:
         rgbFlag = GL_TRUE;
         break;
      case GLX_RED_SIZE:
         redBits = attrib[1];
         attrib++;
         break;
      case GLX_GREEN_SIZE:
         redBits = attrib[1];
         attrib++;
         break;
      case GLX_BLUE_SIZE:
         redBits = attrib[1];
         attrib++;
         break;
      case GLX_ALPHA_SIZE:
         redBits = attrib[1];
         attrib++;
         break;
      case GLX_STENCIL_SIZE:
         stencilBits = attrib[1];
         attrib++;
         break;
#if 0
      case GLX_DEPTH_SIZE:
         depthBits = attrib[1];
         attrib++;
         break;
      case GLX_ACCUM_RED_SIZE:
         accumRedBits = attrib[1];
         attrib++;
         break;
      case GLX_ACCUM_GREEN_SIZE:
         accumGreenBits = attrib[1];
         attrib++;
         break;
      case GLX_ACCUM_BLUE_SIZE:
         accumBlueBits = attrib[1];
         attrib++;
         break;
      case GLX_ACCUM_ALPHA_SIZE:
         accumAlphaBits = attrib[1];
         attrib++;
         break;
      case GLX_LEVEL:
         /* ignored for now */
         break;
#endif
      default:
         /* unexpected token */
         fprintf(stderr, "unexpected token in glXChooseVisual attrib list\n");
         FREE(vis);
         FREE(visInfo);
         return NULL;
      }
   }

   /* search screen configs for suitable visual */
   (void) numSamples;
   (void) indexBits;
   (void) redBits;
   (void) greenBits;
   (void) blueBits;
   (void) alphaBits;
   (void) stereoFlag;
   for (i = 0; i < dpy->numConfigs; i++) {
      const __GLXvisualConfig *config = dpy->configs + i;
      if (config->rgba == rgbFlag &&
          config->redSize >= redBits &&
          config->greenSize >= greenBits &&
          config->blueSize >= blueBits &&
          config->alphaSize >= alphaBits &&
          /*config->depthSize >= depthBits &&*/
          config->stencilSize >= stencilBits) {
         /* found it */
         visInfo->visualid = config->vid;
         vis->glxConfig = config;
         break;
      }          
   }

   /* compute depth and bpp */
   if (rgbFlag) {
      /* XXX maybe support depth 16 someday */
      visInfo->class = TrueColor;
      visInfo->depth = 32;
      visInfo->bits_per_rgb = 32;
      vis->pixelFormat = PF_B8G8R8A8;
   }
   else {
      /* color index mode */
      visInfo->class = PseudoColor;
      visInfo->depth = 8;
      visInfo->bits_per_rgb = 8;  /* bits/pixel */
      vis->pixelFormat = PF_CI8;
   }

   return visInfo;
}


int
glXGetConfig( Display *dpy, XVisualInfo *vis, int attrib, int *value )
{
   const __GLXvisualConfig *config = vis->visual->glxConfig;
   if (!config) {
      *value = 0;
      return GLX_BAD_VISUAL;
   }

   switch (attrib) {
   case GLX_USE_GL:
      *value = True;
      return 0;
   case GLX_RGBA:
      *value = config->rgba;
      return 0;
   case GLX_DOUBLEBUFFER:
      *value = config->doubleBuffer;
      return 0;
   case GLX_RED_SIZE:
      *value = config->redSize;
      return 0;
   case GLX_GREEN_SIZE:
      *value = config->greenSize;
      return 0;
   case GLX_BLUE_SIZE:
      *value = config->blueSize;
      return 0;
   case GLX_ALPHA_SIZE:
      *value = config->alphaSize;
      return 0;
   case GLX_DEPTH_SIZE:
      *value = config->depthSize;
      return 0;
   case GLX_STENCIL_SIZE:
      *value = config->stencilSize;
      return 0;
   default:
      *value = 0;
      return GLX_BAD_ATTRIBUTE;
   }
   return 0;
}


GLXContext
glXCreateContext( Display *dpy, XVisualInfo *vis,
                        GLXContext shareList, Bool direct )
{
   GLXContext ctx;
   void *sharePriv;

   ASSERT(vis);

   ctx = CALLOC_STRUCT(MiniGLXContextRec);
   if (!ctx)
      return NULL;

   ctx->vid = vis->visualid;

   if (shareList)
      sharePriv = shareList->driContext.private;
   else
      sharePriv = NULL;
   ctx->driContext.private = (*dpy->driScreen.createContext)(dpy, vis,
                                          sharePriv, &(ctx->driContext));
   if (!ctx->driContext.private) {
      FREE(ctx);
      return NULL;
   }


   return ctx;
}


void
glXDestroyContext( Display *dpy, GLXContext ctx )
{
   GLXContext glxctx = glXGetCurrentContext();

   if (glxctx) {
      if (glxctx == ctx) {
         /* destroying current context */
         (*ctx->driContext.bindContext)(dpy, 0, 0, 0);
      }
      (*ctx->driContext.destroyContext)(dpy, 0, ctx->driContext.private);
      FREE(ctx);
   }
}


Bool
glXMakeCurrent( Display *dpy, GLXDrawable drawable, GLXContext ctx)
{
   if (dpy && drawable && ctx) {
      GLXContext oldContext = glXGetCurrentContext();
      GLXDrawable oldDrawable = glXGetCurrentDrawable();
      /* unbind old */
      if (oldContext) {
         (*oldContext->driContext.unbindContext)(dpy, 0, oldDrawable,
                                                 oldContext, 0);
      }
      /* bind new */
      CurrentContext = ctx;
      (*ctx->driContext.bindContext)(dpy, 0, drawable, ctx);
      ctx->drawBuffer = drawable;
      ctx->curBuffer = drawable;
   }
   else if (ctx && dpy) {
      /* unbind */
      (*ctx->driContext.bindContext)(dpy, 0, 0, 0);
   }

   return True;
}


void
glXSwapBuffers( Display *dpy, GLXDrawable drawable )
{
   if (!dpy || !drawable)
      return;

   (*drawable->driDrawable.swapBuffers)(dpy, drawable->driDrawable.private);
}


GLXContext
glXGetCurrentContext( void )
{
   return CurrentContext;
}


GLXDrawable
glXGetCurrentDrawable( void )
{
   GLXContext glxctx = glXGetCurrentContext();
   if (glxctx)
      return glxctx->drawBuffer;
   else
      return NULL;
}


const void *
glXGetProcAddress( const GLubyte *procName )
{
   struct name_address {
      const char *name;
      const void *func;
   };
   static const struct name_address functions[] = {
      { "glXChooseVisual", (void *) glXChooseVisual },
      { "glXCreateContext", (void *) glXCreateContext },
      { "glXDestroyContext", (void *) glXDestroyContext },
      { "glXMakeCurrent", (void *) glXMakeCurrent },
      { "glXSwapBuffers", (void *) glXSwapBuffers },
      { "glXGetCurrentContext", (void *) glXGetCurrentContext },
      { "glXGetCurrentDrawable", (void *) glXGetCurrentDrawable },
      { "glXGetProcAddress", (void *) glXGetProcAddress },
      { "XOpenDisplay", (void *) XOpenDisplay },
      { "XCloseDisplay", (void *) XCloseDisplay },
      { "XCreateWindow", (void *) XCreateWindow },
      { "XDestroyWindow", (void *) XDestroyWindow },
      { "XMapWindow", (void *) XMapWindow },
      { "XCreateColormap", (void *) XCreateColormap },
      { "XFreeColormap", (void *) XFreeColormap },
      { "XFree", (void *) XFree },
      { "XGetVisualinfo", (void *) XGetVisualInfo },
      { NULL, NULL }
   };
   const struct name_address *entry;
   for (entry = functions; entry->name; entry++) {
      if (STRCMP(entry->name, (const char *) procName) == 0) {
         return entry->func;
      }
   }
   return _glapi_get_proc_address((const char *) procName);
}


Bool
glXQueryVersion( Display *dpy, int *major, int *minor )
{
   (void) dpy;
   *major = 1;
   *minor = 0;
}

