/*
 * Mesa 3-D graphics library
 * Version:  5.0
 *
 * Copyright (C) 1999-2003  Brian Paul   All Rights Reserved.
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

/* $Id: miniglx.c,v 1.1.4.39 2003/01/19 12:18:08 jrfonseca Exp $ */


/**
 * \file miniglx.c
 * \brief Mini GLX interface functions.
 * \author Brian Paul
 *
 * The Mini GLX interface is a subset of the GLX interface, plus a
 * minimal set of Xlib functions.
 */


/**
 * \mainpage Mini GLX
 *
 * \section miniglxIntro Introduction
 *
 * The Mini GLX interface facilitates OpenGL rendering on embedded devices. The
 * interface is a subset of the GLX interface, plus a minimal set of Xlib-like
 * functions.
 *
 * Programs written to the Mini GLX specification should run unchanged on
 * systems with the X Window System and the GLX extension. The intention is to
 * allow flexibility for prototyping and testing.
 *
 *
 * \section miniglxDoxygen About Doxygen
 *
 * For a list of all files, select <b>File List</b>.  Choose a file from
 * the list for a list of all functions in the file.
 *
 * For a list of all functions, types, constants, etc.
 * select <b>File Members</b>.
 *
 *
 * \section miniglxReferences References
 *
 * - <A HREF="file:../../docs/MiniGLX.html">Mini GLX Specification</A>,
 *   Tungsten Graphics, Inc.
 * - OpenGL Graphics with the X Window System, Silicon Graphics, Inc.,
 *   ftp://ftp.sgi.com/opengl/doc/opengl1.2/glx1.3.ps
 * - Xlib - C Language X Interface, X Consortium Standard, X Version 11,
 *   Release 6.4, ftp://ftp.x.org/pub/R6.4/xc/doc/hardcopy/X11/xlib.PS.gz
 * - XFree86 Man pages, The XFree86 Project, Inc.,
 *   http://www.xfree86.org/current/manindex3.html
 *   
 */

/**
 * \page datatypes Notes on the XVisualInfo, Visual, and __GLXvisualConfig data types
 * 
 * -# X (unfortunately) has two (or three) datatypes which
 *    describe visuals.  Ideally, there would just be one.
 * -# We need the #__GLXvisualConfig type to augment #XVisualInfo and #Visual
 *    because we need to describe the GLX-specific attributes of visuals.
 * -# In this interface there is a one-to-one-to-one correspondence between
 *    the three types and they're all interconnected.
 * -# The #XVisualInfo type has a pointer to a #Visual.  The #Visual structure
 *    (aka MiniGLXVisualRec) has a pointer to the #__GLXvisualConfig.  The
 *    #Visual structure also has a pointer pointing back to the #XVisualInfo.
 * -# The #XVisualInfo structure is the only one who's contents are public.
 * -# The glXChooseVisual() and XGetVisualInfo() are the only functions that
 *    return #XVisualInfo structures.  They can be freed with XFree(), though
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

extern void
__driUtilInitScreen( Display *dpy, int scrn, __DRIscreen *psc );


/**
 * \brief Current GLX context.
 *
 * \sa glXGetCurrentContext().
 */
static GLXContext CurrentContext = NULL;


static void SwitchDisplay(int i_signal)
{
}

/**********************************************************************/
/** \name Framebuffer device functions                                */
/**********************************************************************/
/*@{*/

/**
 * \brief Do the first part of setting up the framebuffer device.
 *
 * \param dpy the display handle.
 *
 * \return GL_TRUE on success, or GL_FALSE on failure.
 * 
 * \sa This is called during XOpenDisplay().
 *
 * \internal
 * Gets the VT number, opens the respective console TTY device. Saves its state
 * to restore when exiting and goes into graphics mode.
 *
 * Opens the framebuffer device and make a copy of the original variable screen
 * information and gets the fixed screen information.  Maps the framebuffer and
 * MMIO region into the process address space.
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

   /* open /dev/tty0 and get the VT number */
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
      struct sigaction sig_tty;

      if (ioctl(dpy->ConsoleFD, VT_ACTIVATE, vtnumber) != 0)
         printf("ioctl VT_ACTIVATE: %s\n", strerror(errno));
      if (ioctl(dpy->ConsoleFD, VT_WAITACTIVE, vtnumber) != 0)
         printf("ioctl VT_WAITACTIVE: %s\n", strerror(errno));

      if (ioctl(dpy->ConsoleFD, VT_GETMODE, &vt) < 0) {
         fprintf(stderr, "error: ioctl VT_GETMODE: %s\n", strerror(errno));
         return GL_FALSE;
      }



      /* Set-up tty signal handler to catch the signal we request below */
      memset( &sig_tty, 0, sizeof( sig_tty ) );
      sig_tty.sa_handler = SwitchDisplay;
      sigemptyset( &sig_tty.sa_mask );
      if( sigaction( SIGUSR1, &sig_tty, &dpy->OrigSigUsr1 ) )
      {
	 fprintf(stderr, "error: can't set up signal handler (%s)",
		 strerror(errno) );
	 return GL_FALSE;
      }


      vt.mode = VT_PROCESS;
      vt.waitv = 0;
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

   /* Turn off hw accels (otherwise mmap of mmio region will be
    * refused)
    */
   dpy->VarInfo.accel_flags = 0; 
   if (ioctl(dpy->FrameBufferFD, FBIOPUT_VSCREENINFO, &dpy->VarInfo)) {
      fprintf(stderr, "error: ioctl(FBIOPUT_VSCREENINFO) failed: %s\n",
	      strerror(errno));
      return GL_FALSE;
   }



   /* Get the fixed screen info */
   if (ioctl(dpy->FrameBufferFD, FBIOGET_FSCREENINFO, &dpy->FixedInfo)) {
      fprintf(stderr, "error: ioctl(FBIOGET_FSCREENINFO) failed: %s\n",
              strerror(errno));
      return GL_FALSE;
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

   return GL_TRUE;
}


/**
 * \brief Setup up the desired framebuffer device mode.  
 *
 * \param dpy the display handle.
 * \param win the window handle, from which the screen size is taken.
 * 
 * \return GL_TRUE on success, or GL_FALSE on failure.
 * 
 * \sa This is called during XCreateWindow().
 *
 * \internal
 * Bumps the size of the window the the next supported mode. Sets the variable
 * screen information according to the desired mode and asks the driver to
 * validate the mode. Certifies that a TrueColor visual is used from the
 * updated fixed screen information.
 *
 * Attempts to draws a bitmap with a gradient.
 *
 * \todo Timings are hardcoded in the code for a set of supported modes.
 */
static GLboolean
SetupFBDev( Display *dpy, Window win )
{
   int width = win->w;
   int height = win->h;

   assert(dpy);

   /* Bump size up to next supported mode.
    */
   if (width <= 800 && height <= 600) {
      width = 800; height = 600; 
   }  
   else if (width <= 1024 && height <= 768) { 
      width = 1024; height = 768; 
   } 
   else if (width <= 1280 && height <= 1024) { 
      width = 1280; height = 1024; 
   } 

   if (width > dpy->virtualWidth ||
       height > dpy->virtualHeight ||
       win->visual->visInfo->bits_per_rgb != dpy->bpp) {
      fprintf(stderr, 
	      "width/height/bpp (%d/%d/%d) exceed display limits (%d/%d/%d)\n",
	      width, height, win->visual->visInfo->bits_per_rgb,
	      dpy->virtualWidth, dpy->virtualHeight, dpy->bpp);
      return GL_FALSE;
   }
   
   /* set the depth, resolution, etc */
   dpy->VarInfo = dpy->OrigVarInfo;
   dpy->VarInfo.bits_per_pixel = dpy->bpp;
   dpy->VarInfo.xres_virtual = dpy->virtualWidth;
   dpy->VarInfo.yres_virtual = dpy->virtualHeight;
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
      assert(win->visual->pixelFormat == PF_B5G6R5);
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

   if (!dpy->driver->validateMode( dpy )) {
      fprintf(stderr, "Driver validateMode() failed\n");
      return 0;
   }

   if (dpy->VarInfo.xres == 1280 && 
       dpy->VarInfo.yres == 1024) {
      /* timing values taken from /etc/fb.modes (1280x1024 @ 75Hz) */
      dpy->VarInfo.pixclock = 7408;
      dpy->VarInfo.left_margin = 248;
      dpy->VarInfo.right_margin = 16;
      dpy->VarInfo.upper_margin = 38;
      dpy->VarInfo.lower_margin = 1;
      dpy->VarInfo.hsync_len = 144;
      dpy->VarInfo.vsync_len = 3;
   }
   else if (dpy->VarInfo.xres == 1024 && 
	    dpy->VarInfo.yres == 768) {
      /* timing values taken from /etc/fb.modes (1024x768 @ 75Hz) */
      dpy->VarInfo.pixclock = 12699;
      dpy->VarInfo.left_margin = 176;
      dpy->VarInfo.right_margin = 16;
      dpy->VarInfo.upper_margin = 28;
      dpy->VarInfo.lower_margin = 1;
      dpy->VarInfo.hsync_len = 96;
      dpy->VarInfo.vsync_len = 3;
   }
   else if (dpy->VarInfo.xres == 800 &&
	    dpy->VarInfo.yres == 600) {
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
	      dpy->VarInfo.xres, dpy->VarInfo.yres);
      return GL_FALSE;
   }

   fprintf(stderr, "[miniglx] Setting mode: visible %dx%d virtual %dx%dx%d\n",
	   dpy->VarInfo.xres, dpy->VarInfo.yres,
	   dpy->VarInfo.xres_virtual, dpy->VarInfo.yres_virtual,
	   dpy->VarInfo.bits_per_pixel);

   /* set variable screen info */
   if (ioctl(dpy->FrameBufferFD, FBIOPUT_VSCREENINFO, &dpy->VarInfo)) {
      fprintf(stderr, "error: ioctl(FBIOPUT_VSCREENINFO) failed: %s\n",
	      strerror(errno));
      return GL_FALSE;
   }

   /* get the variable screen info, in case it has been modified */
   if (ioctl(dpy->FrameBufferFD, FBIOGET_VSCREENINFO, &dpy->VarInfo)) {
      fprintf(stderr, "error: ioctl(FBIOGET_VSCREENINFO) failed: %s\n",
              strerror(errno));
      return GL_FALSE;
   }


   fprintf(stderr, "[miniglx] Readback mode: visible %dx%d virtual %dx%dx%d\n",
	   dpy->VarInfo.xres, dpy->VarInfo.yres,
	   dpy->VarInfo.xres_virtual, dpy->VarInfo.yres_virtual,
	   dpy->VarInfo.bits_per_pixel);

   /* Get the fixed screen info */
   if (ioctl(dpy->FrameBufferFD, FBIOGET_FSCREENINFO, &dpy->FixedInfo)) {
      fprintf(stderr, "error: ioctl(FBIOGET_FSCREENINFO) failed: %s\n",
              strerror(errno));
      return GL_FALSE;
   }

   if (dpy->FixedInfo.visual != FB_VISUAL_TRUECOLOR &&
       dpy->FixedInfo.visual != FB_VISUAL_DIRECTCOLOR) {
      fprintf(stderr, "non-TRUECOLOR visuals not supported.\n");
      return GL_FALSE;
   }

   if (dpy->FixedInfo.visual == FB_VISUAL_DIRECTCOLOR) {
      struct fb_cmap cmap;
      unsigned short red[256], green[256], blue[256];
      int rcols = 1 << dpy->VarInfo.red.length;
      int gcols = 1 << dpy->VarInfo.green.length;
      int bcols = 1 << dpy->VarInfo.blue.length;
      int i;

      cmap.start = 0;      
      cmap.len = gcols;
      cmap.red   = red;
      cmap.green = green;
      cmap.blue  = blue;
      cmap.transp = NULL;

      for (i = 0; i < rcols ; i++) 
         red[i] = (65536/(rcols-1)) * i;

      for (i = 0; i < gcols ; i++) 
         green[i] = (65536/(gcols-1)) * i;

      for (i = 0; i < bcols ; i++) 
         blue[i] = (65536/(bcols-1)) * i;
      
      if (ioctl(dpy->FrameBufferFD, FBIOPUTCMAP, (void *) &cmap) < 0) {
         fprintf(stderr, "ioctl(FBIOPUTCMAP) failed [%d]\n", i);
	 exit(1);
      }
   }

   /* May need to restore regs fbdev has clobbered:
    */
   if (!dpy->driver->postValidateMode( dpy )) {
      fprintf(stderr, "Driver postValidateMode() failed\n");
      return 0;
   }

   return GL_TRUE;
}


/**
 * \brief Restore the framebuffer device to state it was in before we started
 *
 * Undoes the work done by SetupFBDev().
 * 
 * \param dpy the display handle.
 *
 * \return GL_TRUE on success, or GL_FALSE on failure.
 * 
 * \sa Called from XDestroyWindow().
 *
 * \internal
 * Restores the original variable screen info.
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


/**
 * \brief Close the framebuffer device.  
 *
 * \param dpy the display handle.
 * 
 * \sa Called from XCloseDisplay().
 *
 * \internal
 * Unmaps the framebuffer and MMIO region.  Restores the text mode and the
 * original virtual terminal. Closes the console and framebuffer devices.
 */
static void
CloseFBDev( Display *dpy )
{
   struct vt_mode VT;

   munmap(dpy->FrameBuffer, dpy->FrameBufferSize);
   munmap(dpy->MMIOAddress, dpy->MMIOSize);

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

   close(dpy->FrameBufferFD);
   close(dpy->ConsoleFD);
}

/*@}*/


/**********************************************************************/
/** \name Misc functions needed for DRI drivers                       */
/**********************************************************************/
/*@{*/

/**
 * \brief Find the DRI screen dependent methods associated with the display.
 *
 * \param dpy a display handle, as returned by XOpenDisplay().
 * \param scrn the screen number. Not referenced.
 * 
 * \returns a pointer to a __DRIscreenRec structure.
 * 
 * \internal
 * Returns the MiniGLXDisplayRec::driScreen attribute.
 */
__DRIscreen *
__glXFindDRIScreen(Display *dpy, int scrn)
{
   (void) scrn;
   return &(dpy->driScreen);
}

/**
 * \brief Validate a drawable.
 *
 * \param dpy a display handle, as returned by XOpenDisplay().
 * \param draw drawable to validate.
 * 
 * \internal
 * Since Mini GLX only supports one window, compares the specified drawable with
 * the MiniGLXDisplayRec::TheWindow attribute.
 */
Bool
__glXWindowExists(Display *dpy, GLXDrawable draw)
{
   if (dpy->TheWindow == draw)
      return True;
   else
      return False;
}

/**
 * \brief Get current thread ID.
 *
 * \return thread ID.
 *
 * \internal
 * Always returns 0. 
 */
unsigned long
_glthread_GetID(void)
{
   return 0;
}

/*@}*/


/**
 * \brief Scan linux /prog/bus/pci/devices file to determine hardware
 * chipset based on supplied busid.
 * 
 * \return non-zeros on success, zero otherwise.
 * 
 * \internal 
 */
static int get_chipset_from_busid( Display *dpy )
{
   char buf[0x200];
   FILE *file;
   const char *fname = "/proc/bus/pci/devices";
   int retval = 0;

   if (!(file = fopen(fname,"r"))) {
      fprintf(stderr, "couldn't open %s: %s\n", fname, strerror(errno));
      return 0;
   }

   while (fgets(buf, sizeof(buf)-1, file)) {
      int nr, bus, dev, fn, vendor, device;
      nr = sscanf(buf, "%02x%01x%01x\t%04x%04x", &bus, &dev, &fn, 
		  &vendor, &device);

      if (nr != 5)
	 break;

      if (bus == dpy->pciBus && dev == dpy->pciDevice && fn == dpy->pciFunc) {
	 retval = device;
	 break;
      }
   }

   fclose(file);

   if (retval)
      fprintf(stderr, "[miniglx] probed chipset 0x%x\n", retval);
   else
      fprintf(stderr, "[miniglx] failed to probe chipset\n");

   return retval;
}


/**
 * \brief Read settings from a configuration file.
 * 
 * The configuration file is usually "/etc/minigilx.conf", but can be overriden
 * with the MINIGLX_CONF environment variable. 
 *
 * The format consists in \code option = value \endcode lines. The option names 
 * corresponds to the fields in MiniGLXDisplayRec.
 * 
 * \param dpy the display handle as.
 *
 * \return non-zero on success, zero otherwise.
 * 
 * \internal 
 * Sets some defaults. Opens and parses the the Mini GLX configuration file and
 * fills in the MiniGLXDisplayRec field that corresponds for each option.
 */
static int __read_config_file( Display *dpy )
{
   FILE *file;
   const char *fname;

   /* Fallback/defaults
    */
   dpy->fbdevDevice = "/dev/fb0";
   dpy->clientDriverName = "fb_dri.so";
   dpy->drmModuleName = 0;
   dpy->pciBus = 0;
   dpy->pciDevice = 0;
   dpy->pciFunc = 0;
   dpy->chipset = 0;   
   dpy->pciBusID = 0;
   dpy->virtualWidth = 1280;
   dpy->virtualHeight = 1024;
   dpy->bpp = 32;
   dpy->cpp = 4;

   fname = getenv("MINIGLX_CONF");
   if (!fname) fname = "/etc/miniglx.conf";

   file = fopen(fname, "r");
   if (!file) {
      fprintf(stderr, "couldn't open config file %s\n", fname);
      return 0;
   }


   while (!feof(file)) {
      char buf[81], *opt = buf, *val, *tmp1, *tmp2;
      fgets(buf, sizeof(buf), file); 

      /* Parse 'opt = val' -- must be easier ways to do this.
       */
      while (isspace(*opt)) opt++;
      val = opt;
      if (*val == '#') continue; /* comment */
      while (!isspace(*val) && *val != '=' && *val) val++;
      tmp1 = val;
      while (isspace(*val)) val++;
      if (*val != '=') continue;
      *tmp1 = 0; 
      val++;
      while (isspace(*val)) val++;
      tmp2 = val;
      while (!isspace(*tmp2) && *tmp2 != '\n' && *tmp2) tmp2++;
      *tmp2 = 0;


      if (strcmp(opt, "fbdevDevice") == 0) 
	 dpy->fbdevDevice = strdup(val);
      else if (strcmp(opt, "clientDriverName") == 0)
	 dpy->clientDriverName = strdup(val);
      else if (strcmp(opt, "drmModuleName") == 0)
	 dpy->drmModuleName = strdup(val);
      else if (strcmp(opt, "pciBusID") == 0) {
	 if (sscanf(val, "PCI:%d:%d:%d",
		    &dpy->pciBus, &dpy->pciDevice, &dpy->pciFunc) != 3) {
	    fprintf(stderr, "malformed bus id: %s\n", val);
	    continue;
	 }
   	 dpy->pciBusID = strdup(val);
      }
      else if (strcmp(opt, "chipset") == 0) {
	 if (sscanf(val, "0x%x", &dpy->chipset) != 1)
	    fprintf(stderr, "malformed chipset: %s\n", opt);
      }
      else if (strcmp(opt, "virtualWidth") == 0) {
	 if (sscanf(val, "%d", &dpy->virtualWidth) != 1)
	    fprintf(stderr, "malformed virtualWidth: %s\n", opt);
      }
      else if (strcmp(opt, "virtualHeight") == 0) {
	 if (sscanf(val, "%d", &dpy->virtualHeight) != 1)
	    fprintf(stderr, "malformed virutalHeight: %s\n", opt);
      }
      else if (strcmp(opt, "bpp") == 0) {
	 if (sscanf(val, "%d", &dpy->bpp) != 1)
	    fprintf(stderr, "malformed bpp: %s\n", opt);
	 dpy->cpp = dpy->bpp / 8;
      }
   }

   fclose(file);

   if (dpy->chipset == 0 && dpy->pciBusID != 0) 
      dpy->chipset = get_chipset_from_busid( dpy );

   return 1;
}


/**********************************************************************/
/** \name Public API functions (Xlib and GLX)                         */
/**********************************************************************/
/*@{*/


/**
 * \brief Initialize the graphics system.
 * 
 * \param display_name currently ignored. It is recommended to pass it as NULL.
 * \return a pointer to a #Display if the function is able to initialize
 * the graphics system, NULL otherwise.
 * 
 * \internal
 * Allocates a MiniGLXDisplayRec structure and fills in with information from a
 * configuration file. 
 *
 * Opens and initializes the fbdev device.
 *
 * Loads the DRI driver and pulls in MiniGLX-specific hooks into a
 * MiniGLXDriverRec structure, and the standard DRI \e __driCreateScreen hook.
 * Asks the driver for a list of supported visuals.  Performs the client-side
 * initialization - has to be done this here as it depends on the chosen
 * display resolution, which in this window system depends on the size of the
 * \e window created. Also setups the callbacks in the screen private
 * information.
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

   /* Open the fbdev device
    */
   if (!OpenFBDev(dpy)) {
      fprintf(stderr, "OpenFBDev failed\n");
      FREE(dpy);
      return NULL;
   }


   /*
    * Begin DRI setup.
    * We're kind of combining the per-display and per-screen information
    * which was kept separate in XFree86/DRI's libGL.
    */
   dpy->dlHandle = dlopen(dpy->clientDriverName, RTLD_NOW | RTLD_GLOBAL);
   if (!dpy->dlHandle) {
      fprintf(stderr, "Unable to open %s: %s\n", dpy->clientDriverName,
	      dlerror());
      CloseFBDev(dpy);
      FREE(dpy);
      return NULL;
   }

   /* Pull in MiniGLX-specific hooks:
    */
   dpy->driver = (struct MiniGLXDriverRec *) dlsym(dpy->dlHandle,
						   "__driMiniGLXDriver");
   if (!dpy->driver) {
      fprintf(stderr, "Couldn't find __driMiniGLXDriver in %s\n",
              dpy->clientDriverName);
      dlclose(dpy->dlHandle);
      FREE(dpy);
      return NULL;
   }

   /* Pull in standard DRI client-side driver hooks:
    */
   dpy->createScreen = (CreateScreenFunc) dlsym(dpy->dlHandle,
                                                "__driCreateScreen");
   if (!dpy->createScreen) {
      fprintf(stderr, "Couldn't find __driCreateScreen in %s\n",
              dpy->clientDriverName);
      dlclose(dpy->dlHandle);
      FREE(dpy);
      return NULL;
   }

   /* Ask the driver for a list of supported configs:
    */
   dpy->driver->initScreenConfigs( dpy, &dpy->numConfigs, &dpy->configs );


   /* Perform the initialization normally done in the X server */
   if (!dpy->driver->initFBDev( dpy )) {
      fprintf(stderr, "%s: __driInitFBDev failed\n", __FUNCTION__);
      dlclose(dpy->dlHandle);
      FREE(dpy);
      return NULL;
   }

   /* Perform the client-side initialization.  Have to do this here as
    * it depends on the display resolution chosen, which in this
    * window system depends on the size of the "window" created.
    *
    * Clearly there is a limit of one on the number of windows in
    * existence at any time.
    *
    * Need to shut down DRM and free DRI data in XDestroyWindow(), too.
    */
   dpy->driScreen.private = (*dpy->createScreen)(dpy, 0, 
						 &(dpy->driScreen),
						 dpy->numConfigs,
						 dpy->configs);
   if (!dpy->driScreen.private) {
      fprintf(stderr, "%s: __driCreateScreen failed\n", __FUNCTION__);
      dlclose(dpy->dlHandle);
      FREE(dpy);
      return NULL;
   }



   /* Setup some callbacks in the screen private.
    */
   __driUtilInitScreen( dpy, 0, &(dpy->driScreen) );

   return dpy;
}


/**
 * \brief Release display resources.
 * 
 * When the application is about to exit, the resources associated with the
 * graphics system can be released by calling this function.
 * 
 * \param display display handle. It becomes invalid at this point.
 * 
 * \internal 
 * This function frees the \p display structure, after calling the
 * __DRIscreenRec::destroyScreen method pointed by
 * MiniGLXDisplayRec::driScreen attribute of \p display, closing the dynamic
 * library handle MiniGLXDisplayRec::dlHandle and calling CloseFBDev() to
 * close the fbdev.
 *
 * Also destroy the window and halt the framebuffer device.
 */
void
XCloseDisplay( Display *display )
{
   GLXContext *ctx;

   glXMakeCurrent( display, NULL, NULL);

   if (display->NumWindows) 
      XDestroyWindow( display, display->TheWindow );

   /* As this is done in CreateWindow, need to undo it here:
    */
   if (display->driScreen.private) 
      (*display->driScreen.destroyScreen)(display, 0, 
					  display->driScreen.private);

   /* As this is done in CreateWindow, need to undo it here:
    */
   (*display->driver->haltFBDev)( display );


   dlclose(display->dlHandle);
   CloseFBDev(display);
   FREE(display);
}


/**
 * \brief Window creation.
 *
 * \param display a display handle, as returned by XOpenDisplay().
 * \param parent the parent window for the new window. For Mini GLX this should
 * be 
 * \code RootWindow(display, 0) \endcode
 * \param x the window abscissa. For Mini GLX, it should be zero.
 * \param y the window ordinate. For Mini GLX, it should be zero.
 * \param width the window width. For Mini GLX, this specifies the desired
 * screen width such as 1024 or 1280. 
 * \param height the window height. For Mini GLX, this specifies the desired
 * screen height such as 768 or 1024.
 * \param border_width the border sith. For Mini GLX, it should be zero.
 * \param depth the window pixel depth. For Mini GLX, this should be the depth
 * found in the #XVisualInfo object returned by glXChooseVisual() 
 * \param class the window class. For Mini GLX this value should be
 * #InputOutput.
 * \param visual the visual type. It should be the visual field of the
 * #XVisualInfo object returned by glXChooseVisual().
 * \param valuemask which fields of the XSetWindowAttributes() are to be used.
 * For Mini GLX this is typically the bitmask 
 * \code CWBackPixel | CWBorderPixel | CWColormap \endcode
 * \param attributes initial window attributes. The
 * XSetWindowAttributes::background_pixel, XSetWindowAttributes::border_pixel
 * and XSetWindowAttributes::colormap fields should be set.
 *
 * \return a window handle if it succeeds or zero if it fails.
 * 
 * \note For Mini GLX, windows are full-screen; they cover the entire frame
 * buffer.  Also, Mini GLX imposes a limit of one window. A second window
 * cannot be created until the first one is destroyed.
 *
 * \internal 
 * This function creates and initializes a ::MiniGLXWindowRec structure after
 * ensuring that there is no other window created, and calls SetupFBDev() to
 * setup the framebuffer device mode and get its geometry. It performs the
 * client-side initialization calling MiniGLXDisplayRec::createScreen and
 * __DRIscreenRec::createDrawable methods.
 * 
 */
Window
XCreateWindow( Display *display, Window parent, int x, int y,
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

   if (display->NumWindows > 0)
      return NULL;  /* only allow one window */

   assert(display->TheWindow == NULL);

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
    */
   if (!SetupFBDev(display, win)) {
      FREE(win);
      return NULL;
   }


   win->bytesPerPixel = display->bpp / 8;
   win->rowStride = display->VarInfo.xres_virtual * win->bytesPerPixel;
   win->size = win->rowStride * height; 
   win->frontStart = display->FrameBuffer;
   win->frontBottom = (GLubyte *) win->frontStart + (height-1) * win->rowStride;

   /* This is incorrect: the hardware driver could put the backbuffer
    * just about anywhere.  These fields, including the above are
    * hardware dependent & don't really belong here.
    */
   if (visual->glxConfig->doubleBuffer) {
      win->backStart = (GLubyte *) win->frontStart +
	 win->rowStride * display->VarInfo.yres_virtual;
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



   win->driDrawable.private = display->driScreen.createDrawable(display, 0, win,
								visual->visInfo->visualid, &(win->driDrawable));
   if (!win->driDrawable.private) {
      fprintf(stderr, "%s: dri.createDrawable failed\n", __FUNCTION__);
      RestoreFBDev(display);
      FREE(win);
      return NULL;
   }


   display->NumWindows++;
   display->TheWindow = win;

   return win; 
}


/**
 * \brief Destroy window.
 *
 * \param display display handle.
 * \param w window handle.
 *
 * \internal
 * This function frees window \p w after calling
 * __DRIdrawableRec::destroyDrawable to destroy the
 * private data and restoring the framebuffer via RestoreFBDev().
 * 
 * In case of destroying the current buffer first unbinds the GLX context
 * by calling glXMakeCurrent() with no drawable.
 */
void
XDestroyWindow( Display *display, Window w )
{
   assert(display);
   if (w) {
      /* check if destroying the current buffer */
      Window curDraw = glXGetCurrentDrawable();
      if (w == curDraw) {
         glXMakeCurrent( display, NULL, NULL);
      }

      /* Destroy the drawable.
       */
      if (w->driDrawable.private)
	 (*w->driDrawable.destroyDrawable)(display, w->driDrawable.private);

      /* put framebuffer back to initial state */
      RestoreFBDev(display);

      FREE(w);
      /* unlink window from display */
      display->NumWindows--;
      assert(display->NumWindows == 0);
      display->TheWindow = NULL;
   }
}


/**
 * \brief Map Window.
 *
 * \param display the display handle as returned by XOpenDisplay().
 * \param w the window handle.
 * 
 * This function does nothing in Mini GLX but is required for Xlib/GLX
 * compatibility.
 * 
 * \internal
 * This function is only provided to ease porting.  no-op
 */
void
XMapWindow( Display *display, Window w )
{
   (void) display;
   (void) w;
}


/**
 * \brief Create color map structure.
 *
 * \param dpy the display handle as returned by XOpenDisplay().
 * \param w the window on whose screen you want to create a colormap. This
 * parameter is ignored by Mini GLX but should be the value returned by the
 * \code RootWindow(display, 0) \endcode macro.
 * \param visual a visual type supported on the screen. This parameter is
 * ignored by Mini GLX but should be the XVisualInfo::visual returned by
 * glXChooseVisual().
 * \param alloc the colormap entries to be allocated. This parameter is ignored
 * by Mini GLX but should be set to #AllocNone.
 *
 * \return the color map.
 * 
 * \internal
 * This function is only provided to ease porting.  Practically a no-op -
 * returns a pointer to a dinamically allocated chunk of memory (one byte).
 */
Colormap
XCreateColormap( Display *dpy, Window w, Visual *visual, int alloc )
{
   (void) dpy;
   (void) w;
   (void) visual;
   (void) alloc;
   return (Colormap) MALLOC(1);
}


/**
 * \brief Destroy colormap structure.
 *
 * \param display The display handle as returned by XOpenDisplay().
 * \param colormap the colormap to destroy.
 *
 * \internal
 * This function is only provided to ease porting.  Practically a no-op. 
 * Frees the chunk of memory pointed by \p colormap with #FREE.
 */
void
XFreeColormap( Display *display, Colormap colormap )
{
   (void) display;
   (void) colormap;
   FREE(colormap);
}


/**
 * \brief Free client data.
 *
 * \param data the data that is to be freed.
 *
 * \internal
 * This function frees the memory pointed by \p data with #FREE.
 */
void
XFree( void *data )
{
   FREE(data);
}


/**
 * \brief Query available visuals.
 *
 * \param dpy the display handle, as returned by XOpenDisplay().
 * \param vinfo_mask a bitmask indicating which fields of the \p vinfo_template
 * are to be matched.  The value must be \c VisualScreenMask.
 * \param vinfo_template a template whose fields indicate which visual
 * attributes must be matched by the results.  The XVisualInfo::screen field of
 * this structure must be zero.
 * \param nitens_return Returns the number of visuals returned.
 *
 * \return the address of an array of all available visuals.
 * 
 * An example of using XGetVisualInfo() to get all available visuals follows:
 * 
 * \code
 * XVisualInfo vinfo_template, *results;
 * int nitens_return;
 * Display *dpy = XOpenDisplay(NULL);
 * vinfo_template.screen = 0;
 * results = XGetVisualInfo(dpy, VisualScreenMask, &vinfo_template, &nitens_return);
 * \endcode
 * 
 * \internal
 * Returns the list of all ::XVisualInfos available, one per
 * ::__GLXvisualConfig stored in MiniGLXDisplayRec::configs.
 */
XVisualInfo *
XGetVisualInfo( Display *dpy, long vinfo_mask, XVisualInfo *vinfo_template, int *nitens_return )
{
   XVisualInfo *results;
   Visual *visResults;
   int i, n;

   ASSERT(vinfo_mask == VisualScreenMask);
   ASSERT(vinfo_template.screen == 0);

   n = dpy->numConfigs;
   results = (XVisualInfo *) CALLOC(n * sizeof(XVisualInfo));
   if (!results) {
      *nitens_return = 0;
      return NULL;
   }

   visResults = (Visual *) CALLOC(n * sizeof(Visual));
   if (!results) {
      FREE(results);
      *nitens_return = 0;
      return NULL;
   }

   for (i = 0; i < n; i++) {
      visResults[i].glxConfig = dpy->configs + i;
      visResults[i].visInfo = results + i;
      visResults[i].dpy = dpy;

      if (dpy->bpp == 32)
	 visResults[i].pixelFormat = PF_B8G8R8A8; /* XXX: FIX ME */
      else
	 visResults[i].pixelFormat = PF_B5G6R5; /* XXX: FIX ME */

      results[i].visual = visResults + i;
      results[i].visualid = dpy->configs[i].vid;
      results[i].class = TrueColor;
      results[i].depth = dpy->configs[i].redSize +
                         dpy->configs[i].greenSize +
                         dpy->configs[i].blueSize +
                         dpy->configs[i].alphaSize;
      results[i].bits_per_rgb = dpy->bpp;
   }
   *nitens_return = n;
   return results;
}


/**
 * \brief Return a visual that matches specified attributes.
 *
 * \param dpy the display handle, as returned by XOpenDisplay().
 * \param screen the screen number. It is currently ignored by Mini GLX and
 * should be zero.
 * \param attribList a list of GLX attributes which describe the desired pixel
 * format. It is terminated by the token \c None. 
 *
 * The attributes are as follows:
 * \arg GLX_USE_GL:
 * This attribute should always be present in order to maintain compatibility
 * with GLX.
 * \arg GLX_RGBA:
 * If present, only RGBA pixel formats will be considered. Otherwise, only
 * color index formats are considered.
 * \arg GLX_DOUBLEBUFFER:
 * if present, only double-buffered pixel formats will be chosen.
 * \arg GLX_RED_SIZE \e n:
 * Must be followed by a non-negative integer indicating the minimum number of
 * bits per red pixel component that is acceptable.
 * \arg GLX_GREEN_SIZE \e n:
 * Must be followed by a non-negative integer indicating the minimum number of
 * bits per green pixel component that is acceptable.
 * \arg GLX_BLUE_SIZE \e n:
 * Must be followed by a non-negative integer indicating the minimum number of
 * bits per blue pixel component that is acceptable.
 * \arg GLX_ALPHA_SIZE \e n:
 * Must be followed by a non-negative integer indicating the minimum number of
 * bits per alpha pixel component that is acceptable.
 * \arg GLX_STENCIL_SIZE \e n:
 * Must be followed by a non-negative integer indicating the minimum number of
 * bits per stencil value that is acceptable.
 * \arg GLX_DEPTH_SIZE \e n:
 * Must be followed by a non-negative integer indicating the minimum number of
 * bits per depth component that is acceptable.
 * \arg None:
 * This token is used to terminate the attribute list.
 *
 * \return a pointer to an #XVisualInfo object which most closely matches the
 * requirements of the attribute list. If there is no visual which matches the
 * request, \c NULL will be returned.
 *
 * \note Visuals with accumulation buffers are not available.
 *
 * \internal
 * This function searches the list of available visual configurations in
 * MiniGLXDisplayRec::configs for a configuration which best matches the GLX
 * attribute list parameter.  A new ::XVisualInfo object is created which
 * describes the visual configuration.  The match criteria is described in the
 * specification.
 */
XVisualInfo*
glXChooseVisual( Display *dpy, int screen, int *attribList )
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
   for (attrib = attribList; attrib && *attrib != None; attrib++) {
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
      case GLX_DEPTH_SIZE:
         depthBits = attrib[1];
         attrib++;
         break;
#if 0
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
          config->depthSize >= depthBits &&
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
      visInfo->depth = dpy->bpp;
      visInfo->bits_per_rgb = dpy->bpp;
      if (dpy->bpp == 32)
	 vis->pixelFormat = PF_B8G8R8A8;
      else
	 vis->pixelFormat = PF_B5G6R5;
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


/**
 * \brief Return information about GLX visuals.
 *
 * \param dpy the display handle, as returned by XOpenDisplay().
 * \param vis the visual to be queried, as returned by glXChooseVisual().
 * \param attrib the visual attribute to be returned.
 * \param value pointer to an integer in which the result of the query will be
 * stored.
 * 
 * \return zero if no error occurs, \c GLX_INVALID_ATTRIBUTE if the attribute
 * parameter is invalid, or \c GLX_BAD_VISUAL if the \p vis parameter is
 * invalid.
 *
 * \internal
 * Returns the appropriate attribute of ::__GLXvisualConfig pointed by
 * MiniGLXVisualRec::glxConfig of XVisualInfo::visual.
 *
 * \sa datatypes.
 */
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


/**
 * \brief Create a new GLX rendering context.
 *
 * \param dpy the display handle, as returned by XOpenDisplay().
 * \param vis the visual that defines the frame buffer resources available to
 * the rendering context, as returned by glXChooseVisual().
 * \param shareList If non-zero, texture objects and display lists are shared
 * with the named rendering context. If zero, texture objects and display lists
 * will (initially) be private to this context. They may be shared when a
 * subsequent context is created.
 * \param direct whether direct or indirect rendering is desired. For Mini GLX
 * this value is ignored but it should be set to \c True.
 *
 * \return a ::GLXContext handle if it succeeds or zero if it fails due to
 * invalid parameter or insufficient resources.
 *
 * \internal
 * This function creates and initializes a ::MiniGLXContextRec structure and
 * calls the __DRIscreenRec::createContext method to initalize the client
 * private data.
 */ 
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


/**
 * \brief Destroy a GLX context.
 *
 * \param dpy the display handle, as returned by XOpenDisplay().
 * \param ctx the GLX context to be destroyed.
 * 
 * \internal
 * This function frees the \p ctx parameter after unbinding the current context
 * by calling the __DRIcontextRec::bindContext method with zeros and calling
 * the __DRIcontextRec::destroyContext method.
 */
void
glXDestroyContext( Display *dpy, GLXContext ctx )
{
   GLXContext glxctx = glXGetCurrentContext();

   if (ctx) {
      if (glxctx == ctx) {
         /* destroying current context */
         (*ctx->driContext.bindContext)(dpy, 0, 0, 0);
	 CurrentContext = 0;
      }
      (*ctx->driContext.destroyContext)(dpy, 0, ctx->driContext.private);
      FREE(ctx);
   }
}


/**
 * \brief Bind a GLX context to a window or a GLX.
 *
 * \param dpy the display handle, as returned by XOpenDisplay().
 * \param drawable the window or drawable to bind to the rendering context.
 * This should be the value returned by XCreateWindow().
 * \param ctx the GLX context to be destroyed.
 *
 * \return \c True if it succeeds, \c False otherwise to indicate an invalid
 * display, window or context parameter.
 *
 * The current rendering context may be unbound by calling glXMakeCurrent()
 * with the window and context parameters set to zero.
 * 
 * An application may create any number of rendering contexts and bind them as
 * needed. Note that binding a rendering context is generally not a
 * light-weight operation.  Most simple OpenGL applications create only one
 * rendering context.
 *
 * \internal
 * This function first unbinds any old context via
 * __DRIcontextRec::unbindContext and binds the new one via
 * __DRIcontextRec::bindContext.
 *
 * If \p drawable is zero it unbinds the GLX context by calling
 * __DRIcontextRec::bindContext with zeros.
 */
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
   else if (dpy) {
      CurrentContext = 0;	/* kw:  this seems to be intended??? */
   }

   return True;
}


/**
 * \brief Exchange front and back buffers.
 * 
 * \param dpy the display handle, as returned by XOpenDisplay().
 * \param drawable the drawable whose buffers are to be swapped.
 * 
 * Any pending rendering commands will be completed before the buffer swap
 * takes place.
 * 
 * Calling glXSwapBuffers() on a window which is single-buffered has no effect.
 *
 * \internal
 * This function just calls the __DRIdrawableRec::swapBuffers method to do the
 * work.
 */
void
glXSwapBuffers( Display *dpy, GLXDrawable drawable )
{
   if (!dpy || !drawable)
      return;

   (*drawable->driDrawable.swapBuffers)(dpy, drawable->driDrawable.private);
}


/**
 * \brief Return the current context
 *
 * \return the current context, as specified by glXMakeCurrent(), or zero if no
 * context is currently bound.
 *
 * \sa glXCreateContext(), glXMakeCurrent()
 *
 * \internal
 * Returns the value of the ::CurrentContext global variable.
 */
GLXContext
glXGetCurrentContext( void )
{
   return CurrentContext;
}


/**
 * \brief Return the current drawable.
 *
 * \return the current drawable, as specified by glXMakeCurrent(), or zero if
 * no drawable is currently bound.
 *
 * \internal
 * This function gets the current context via glXGetCurrentContext() and
 * returns the MiniGLXContextRec::drawbuffer attribute.
 */
GLXDrawable
glXGetCurrentDrawable( void )
{
   GLXContext glxctx = glXGetCurrentContext();
   if (glxctx)
      return glxctx->drawBuffer;
   else
      return NULL;
}


/**
 * \brief Query function address.
 *
 * The glXGetProcAddress() function will return the address of any available
 * OpenGL or Mini GLX function.
 * 
 * \param procName name of the function to be returned.
 *
 * \return If \p procName is a valid function name, a pointer to that function
 * will be returned.  Otherwise, \c NULL will be returned.
 *
 * The purpose of glXGetProcAddress() is to facilitate using future extensions
 * to OpenGL or Mini GLX. If a future version of the library adds new extension
 * functions they'll be accessible via glXGetProcAddress(). The alternative is
 * to hard-code calls to the new functions in the application but doing so will
 * prevent linking the application with older versions of the library.
 * 
 * \internal
 * Returns the function address by looking up its name in a static (name, func)
 * pair structure list.
 */
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


/**
 * \brief Query the Mini GLX version.
 *
 * \param dpy the display handle. It is currently ignored, but should be the
 * value returned by XOpenDisplay().
 * \param major receives the major version number of Mini GLX.
 * \param minor receives the minor version number of Mini GLX.
 *
 * \return \c True if the function succeeds, \c False if the function fails due
 * to invalid parameters.
 *
 * \sa #MINI_GLX_VERSION_1_0.
 * 
 * \internal
 * Returns the hardcoded Mini GLX version.
 */
Bool
glXQueryVersion( Display *dpy, int *major, int *minor )
{
   (void) dpy;
   *major = 1;
   *minor = 0;
}

/*@}*/
