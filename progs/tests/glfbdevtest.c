/* $Id: glfbdevtest.c,v 1.1.4.3 2002/11/22 16:13:49 brianp Exp $ */

/*
 * Test the GLFBDev interface.
 */


#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <GL/glut.h>
#include "GL/glfbdev.h"

#define DEFAULT_DEPTH 8

static struct fb_fix_screeninfo FixedInfo;
static struct fb_var_screeninfo VarInfo;
static int DesiredDepth = 0;
static int OriginalVT = -1;
static int ConsoleFD = -1;
static int FrameBufferFD = -1;
static caddr_t FrameBuffer = (caddr_t) -1;
static int FrameBufferSize = 0;


static void
signal_handler(int signumber)
{
   signal(signumber, SIG_IGN); /* prevent recursion! */
   fprintf(stderr, "error: got signal %d (exiting)\n", signumber);
   exit(1);
}


static void
initialize_fbdev( void )
{
   char ttystr[1000];
   int fd, vtnumber, ttyfd;

   if (geteuid()) {
      fprintf(stderr, "error: you need to be root\n");
      exit(1);
   }

#if 1
   /* open the framebuffer device */
   FrameBufferFD = open("/dev/fb0", O_RDWR);
   if (FrameBufferFD < 0) {
      fprintf(stderr, "Error opening /dev/fb0: %s\n", strerror(errno));
      exit(1);
   }
#endif

   /* open /dev/tty0 and get the vt number */
   if ((fd = open("/dev/tty0", O_WRONLY, 0)) < 0) {
      fprintf(stderr, "error opening /dev/tty0\n");
      exit(1);
   }
   if (ioctl(fd, VT_OPENQRY, &vtnumber) < 0 || vtnumber < 0) {
      fprintf(stderr, "error: couldn't get a free vt\n");
      exit(1);
   }
   close(fd);

   /* open the console tty */
   sprintf(ttystr, "/dev/tty%d", vtnumber);  /* /dev/tty1-64 */
   ConsoleFD = open(ttystr, O_RDWR | O_NDELAY, 0);
   if (ConsoleFD < 0) {
      fprintf(stderr, "error couldn't open console fd\n");
      exit(1);
   }

   /* save current vt number */
   {
      struct vt_stat vts;
      if (ioctl(ConsoleFD, VT_GETSTATE, &vts) == 0)
         OriginalVT = vts.v_active;
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
      if (ioctl(ConsoleFD, VT_ACTIVATE, vtnumber) != 0)
         printf("ioctl VT_ACTIVATE: %s\n", strerror(errno));
      if (ioctl(ConsoleFD, VT_WAITACTIVE, vtnumber) != 0)
         printf("ioctl VT_WAITACTIVE: %s\n", strerror(errno));

      if (ioctl(ConsoleFD, VT_GETMODE, &vt) < 0) {
         fprintf(stderr, "error: ioctl VT_GETMODE: %s\n", strerror(errno));
         exit(1);
      }

      vt.mode = VT_PROCESS;
      vt.relsig = SIGUSR1;
      vt.acqsig = SIGUSR1;
      if (ioctl(ConsoleFD, VT_SETMODE, &vt) < 0) {
         fprintf(stderr, "error: ioctl(VT_SETMODE) failed: %s\n",
                 strerror(errno));
         exit(1);
      }
   }

   /* go into graphics mode */
   if (ioctl(ConsoleFD, KDSETMODE, KD_GRAPHICS) < 0) {
      fprintf(stderr, "error: ioctl(KDSETMODE, KD_GRAPHICS) failed: %s\n",
              strerror(errno));
      exit(1);
   }


#if 0
   /* open the framebuffer device */
   FrameBufferFD = open("/dev/fb0", O_RDWR);
   if (FrameBufferFD < 0) {
      fprintf(stderr, "Error opening /dev/fb0: %s\n", strerror(errno));
      exit(1);
   }
#endif

  /* get the variable screen info */
   if (ioctl(FrameBufferFD, FBIOGET_VSCREENINFO, &VarInfo)) {
      fprintf(stderr, "error: ioctl(FBIOGET_VSCREENINFO) failed: %s\n",
              strerror(errno));
      exit(1);
   }

   /* set the depth, resolution, etc */
   /*   DesiredDepth = 32;*/
   if (DesiredDepth)
      VarInfo.bits_per_pixel = DesiredDepth;
   VarInfo.xres_virtual = VarInfo.xres = 1280;
   VarInfo.yres_virtual = VarInfo.yres = 1024;
#if 1
   if (VarInfo.bits_per_pixel == 16) {
      VarInfo.red.offset = 11;
      VarInfo.green.offset = 5;
      VarInfo.blue.offset = 0;
      VarInfo.red.length = 5;
      VarInfo.green.length = 6;
      VarInfo.blue.length = 5;
      VarInfo.transp.offset = 0;
      VarInfo.transp.length = 0;
   }
   else if (VarInfo.bits_per_pixel == 32) {
      VarInfo.red.offset = 16;
      VarInfo.green.offset = 8;
      VarInfo.blue.offset = 0;
      VarInfo.transp.offset = 0;
      VarInfo.red.length = 8;
      VarInfo.green.length = 8;
      VarInfo.blue.length = 8;
      VarInfo.transp.length = 0;
   }
#endif
   printf("xres=%d yres=%d\n", VarInfo.xres, VarInfo.yres);
   printf("bits_per_pixel=%d\n", VarInfo.bits_per_pixel);
   VarInfo.xoffset = 0;
   VarInfo.yoffset = 0;
   VarInfo.nonstd = 0;
   VarInfo.vmode &= ~FB_VMODE_YWRAP; /* turn off scrolling */

   /* set variable screen info */
   if (ioctl(FrameBufferFD, FBIOPUT_VSCREENINFO, &VarInfo)) {
      fprintf(stderr, "ioctl(FBIOPUT_VSCREENINFO failed): %s\n",
              strerror(errno));
      exit(1);
   }

   /* Get the fixed screen info */
   if (ioctl(FrameBufferFD, FBIOGET_FSCREENINFO, &FixedInfo)) {
      fprintf(stderr, "error: ioctl(FBIOGET_FSCREENINFO) failed: %s\n",
              strerror(errno));
      exit(1);
   }

   if (FixedInfo.visual != FB_VISUAL_TRUECOLOR &&
       FixedInfo.visual != FB_VISUAL_DIRECTCOLOR) {
      fprintf(stderr, "non-TRUE/DIRECT-COLOR visuals (0x%x) not supported by this demo.\n", FixedInfo.visual);
      exit(1);
   }

   /* initialize colormap */
   if (FixedInfo.visual == FB_VISUAL_DIRECTCOLOR) {
      struct fb_cmap cmap;
      unsigned short red[256], green[256], blue[256];
      int i;

      /* we're assuming 256 entries here */
      printf("initializing directcolor colormap\n");
      cmap.start = 0;
      cmap.len = 256;
      cmap.red   = red;
      cmap.green = green;
      cmap.blue  = blue;
      cmap.transp = NULL;
      for (i = 0; i < cmap.len; i++) {
         red[i] = green[i] = blue[i] = (i << 8) | i;
      }
      if (ioctl(FrameBufferFD, FBIOPUTCMAP, (void *) &cmap) < 0) {
         fprintf(stderr, "ioctl(FBIOPUTCMAP) failed [%d]\n", i);
      }
   }

   /* mmap the framebuffer into our address space */
   FrameBufferSize = FixedInfo.smem_len;
   FrameBuffer = (caddr_t) mmap(0, /* start */
                                FrameBufferSize, /* bytes */
                                PROT_READ | PROT_WRITE, /* prot */
                                MAP_SHARED, /* flags */
                                FrameBufferFD, /* fd */
                                0 /* offset */);
   if (FrameBuffer == (caddr_t) - 1) {
      fprintf(stderr, "error: unable to mmap framebuffer: %s\n",
              strerror(errno));
      exit(1);
   }
}


static void
shutdown_fbdev( void )
{
   struct vt_mode VT;

   munmap(FrameBuffer, FrameBufferSize);
   close(FrameBufferFD);

   /* restore text mode */
   ioctl(ConsoleFD, KDSETMODE, KD_TEXT);

   /* set vt */
   if (ioctl(ConsoleFD, VT_GETMODE, &VT) != -1) {
      VT.mode = VT_AUTO;
      ioctl(ConsoleFD, VT_SETMODE, &VT);
   }

   /* restore original vt */
   if (OriginalVT >= 0) {
      ioctl(ConsoleFD, VT_ACTIVATE, OriginalVT);
      OriginalVT = -1;
   }

   close(ConsoleFD);
}


static void
gltest( void )
{
   static const int attribs[] = {
      GLFBDEV_DOUBLE_BUFFER,
      GLFBDEV_DEPTH_SIZE, 16,
      GLFBDEV_NONE
   };
   GLFBDevContextPtr ctx;
   GLFBDevBufferPtr buf;
   GLFBDevVisualPtr vis;
   int bytes, r, g, b, a;
   float ang;

   printf("GLFBDEV_VENDOR = %s\n", glFBDevGetString(GLFBDEV_VENDOR));
   printf("GLFBDEV_VERSION = %s\n", glFBDevGetString(GLFBDEV_VERSION));

   /* framebuffer size */
   bytes = VarInfo.xres_virtual * VarInfo.yres_virtual * VarInfo.bits_per_pixel / 8;

   vis = glFBDevCreateVisual( &FixedInfo, &VarInfo, attribs );
   assert(vis);

   buf = glFBDevCreateBuffer( &FixedInfo, &VarInfo, vis, FrameBuffer, NULL, bytes );
   assert(buf);

   ctx = glFBDevCreateContext( vis, NULL );
   assert(buf);

   b = glFBDevMakeCurrent( ctx, buf, buf );
   assert(b);

   /*printf("GL_EXTENSIONS: %s\n", glGetString(GL_EXTENSIONS));*/
   glGetIntegerv(GL_RED_BITS, &r);
   glGetIntegerv(GL_GREEN_BITS, &g);
   glGetIntegerv(GL_BLUE_BITS, &b);
   glGetIntegerv(GL_ALPHA_BITS, &a);
   printf("RED_BITS=%d GREEN_BITS=%d BLUE_BITS=%d ALPHA_BITS=%d\n",
          r, g, b, a);

   glClearColor(0.5, 0.5, 1.0, 0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1, 1, -1, 1, 2, 30);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0, 0, -15);
   glViewport(0, 0, VarInfo.xres_virtual, VarInfo.yres_virtual);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

   for (ang = 0; ang <= 180; ang += 15) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glPushMatrix();
      glRotatef(ang, 1, 0, 0);
      glutSolidTorus(1, 3, 40, 20);
      glPopMatrix();
      glFBDevSwapBuffers(buf);
   }

   /* clean up */
   b = glFBDevMakeCurrent( NULL, NULL, NULL);
   assert(b);

   glFBDevDestroyContext(ctx);
   glFBDevDestroyBuffer(buf);
   glFBDevDestroyVisual(vis);
}


int
main( int argc, char *argv[] )
{
   signal(SIGUSR1, signal_handler);  /* exit if someone tries a vt switch */
   signal(SIGSEGV, signal_handler);  /* catch segfaults */

   initialize_fbdev();
   gltest();
   shutdown_fbdev();

   return 0;
}
