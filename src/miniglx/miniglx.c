/* $Id: miniglx.c,v 1.1.4.2 2002/11/27 17:02:39 brianp Exp $ */

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


/*
 * *PROTOTYPE* mini-GLX interface, layered on fbdev.
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

#include "glheader.h"
#include "GL/miniglx.h"
#include "context.h"
#include "extensions.h"
#include "imports.h"
#include "texformat.h"
#include "texstore.h"
#include "array_cache/acache.h"
#include "swrast/swrast.h"
#include "swrast_setup/swrast_setup.h"
#include "tnl/tnl.h"
#include "tnl/t_context.h"
#include "tnl/t_pipeline.h"


#define PF_B8G8R8     1
#define PF_B8G8R8A8   2
#define PF_B5G6R5     3
#define PF_B5G5R5     4
#define PF_CI8        5


/*
 * This corresponds to X's Visual type.  We're changing it; using it to
 * store all the OpenGL visual attributes.
 */
struct __VisualRec {
   GLvisual glvisual;        /* OpenGL attribs */
   XVisualInfo *visInfo;     /* pointer back to corresponding XVisualInfo */
   Display *dpy;
   GLuint pixelFormat;       /* one of PF_* values */
};

/*
 * Derived from Mesa's GLframebuffer class.
 */
struct MiniGLXWindowRec {
   GLframebuffer glframebuffer;    /* base class */
   Visual *visual;
   int x, y;                       /* pos (always 0,0) */
   unsigned int w, h;              /* size */
   void *frontStart;               /* start of front color buffer */
   void *backStart;                /* start of back color buffer */
   size_t size;                    /* color buffer size, in bytes */
   GLuint bytesPerPixel;
   GLuint rowStride;               /* in bytes */
   GLubyte *frontBottom;           /* pointer to last row */
   GLubyte *backBottom;            /* pointer to last row */
   GLubyte *curBottom;             /* = frontBottom or backBottom */
};

/*
 * Derived from Mesa's GLcontext class.
 */
struct MiniGLXContextRec {
   GLcontext glcontext;            /* base class */
   Visual visual;
   Window drawBuffer;
   Window readBuffer;
   Window curBuffer;
};


/*
 * Per-display info (replaces Xlib's Display type)
 */
struct MiniGLXDisplayRec {
   struct fb_fix_screeninfo FixedInfo;
   struct fb_var_screeninfo OrigVarInfo, VarInfo;
   int DesiredDepth;
   int OriginalVT;
   int ConsoleFD;
   int FrameBufferFD;
   caddr_t FrameBuffer;  /* start of mmap'd framebuffer */
   int FrameBufferSize;  /* in bytes */
   caddr_t MMIOAddress;  /* start of mmap'd MMIO region */
   int MMIOSize;         /* in bytes */
   int NumWindows;
   Window TheWindow;     /* only allow one window for now */
};



/**********************************************************************/
/* Internal device driver functions                                   */
/**********************************************************************/


#define MINIGLX_CONTEXT(CTX)  ((GLXContext) (CTX))
#define MINIGLX_BUFFER(BUF)  ((GLXDrawable) (BUF))


static const GLubyte *
get_string(GLcontext *ctx, GLenum pname)
{
   (void) ctx;
   switch (pname) {
      case GL_RENDERER:
         return (const GLubyte *) "Mesa glfbdev";
      default:
         return NULL;
   }
}


static void
update_state( GLcontext *ctx, GLuint new_state )
{
   /* not much to do here - pass it on */
   _swrast_InvalidateState( ctx, new_state );
   _swsetup_InvalidateState( ctx, new_state );
   _ac_InvalidateState( ctx, new_state );
   _tnl_InvalidateState( ctx, new_state );
}


static void
get_buffer_size( GLframebuffer *buffer, GLuint *width, GLuint *height )
{
   Window win = (Window) buffer;  /* yes, this works */
   *width = win->w;
   *height = win->h;
}


/* specifies the buffer for swrast span rendering/reading */
static void
set_buffer( GLcontext *ctx, GLframebuffer *buffer, GLuint bufferBit )
{
   GLXContext fbdevctx = MINIGLX_CONTEXT(ctx);
   GLXDrawable fbdevbuf = MINIGLX_BUFFER(buffer);
   fbdevctx->curBuffer = fbdevbuf;
   switch (bufferBit) {
   case FRONT_LEFT_BIT:
      fbdevbuf->curBottom = fbdevbuf->frontBottom;
      break;
   case BACK_LEFT_BIT:
      fbdevbuf->curBottom = fbdevbuf->backBottom;
      break;
   default:
      _mesa_problem(ctx, "bad bufferBit in set_buffer()");
   }
}


static void
init_core_functions( GLcontext *ctx )
{
   ctx->Driver.GetString = get_string;
   ctx->Driver.UpdateState = update_state;
   ctx->Driver.ResizeBuffers = _swrast_alloc_buffers;
   ctx->Driver.GetBufferSize = get_buffer_size;

   ctx->Driver.Accum = _swrast_Accum;
   ctx->Driver.Bitmap = _swrast_Bitmap;
   ctx->Driver.Clear = _swrast_Clear;  /* would be good to optimize */
   ctx->Driver.CopyPixels = _swrast_CopyPixels;
   ctx->Driver.DrawPixels = _swrast_DrawPixels;
   ctx->Driver.ReadPixels = _swrast_ReadPixels;
   ctx->Driver.DrawBuffer = _swrast_DrawBuffer;

   ctx->Driver.ChooseTextureFormat = _mesa_choose_tex_format;
   ctx->Driver.TexImage1D = _mesa_store_teximage1d;
   ctx->Driver.TexImage2D = _mesa_store_teximage2d;
   ctx->Driver.TexImage3D = _mesa_store_teximage3d;
   ctx->Driver.TexSubImage1D = _mesa_store_texsubimage1d;
   ctx->Driver.TexSubImage2D = _mesa_store_texsubimage2d;
   ctx->Driver.TexSubImage3D = _mesa_store_texsubimage3d;
   ctx->Driver.TestProxyTexImage = _mesa_test_proxy_teximage;

   ctx->Driver.CompressedTexImage1D = _mesa_store_compressed_teximage1d;
   ctx->Driver.CompressedTexImage2D = _mesa_store_compressed_teximage2d;
   ctx->Driver.CompressedTexImage3D = _mesa_store_compressed_teximage3d;
   ctx->Driver.CompressedTexSubImage1D = _mesa_store_compressed_texsubimage1d;
   ctx->Driver.CompressedTexSubImage2D = _mesa_store_compressed_texsubimage2d;
   ctx->Driver.CompressedTexSubImage3D = _mesa_store_compressed_texsubimage3d;

   ctx->Driver.CopyTexImage1D = _swrast_copy_teximage1d;
   ctx->Driver.CopyTexImage2D = _swrast_copy_teximage2d;
   ctx->Driver.CopyTexSubImage1D = _swrast_copy_texsubimage1d;
   ctx->Driver.CopyTexSubImage2D = _swrast_copy_texsubimage2d;
   ctx->Driver.CopyTexSubImage3D = _swrast_copy_texsubimage3d;
   ctx->Driver.CopyColorTable = _swrast_CopyColorTable;
   ctx->Driver.CopyColorSubTable = _swrast_CopyColorSubTable;
   ctx->Driver.CopyConvolutionFilter1D = _swrast_CopyConvolutionFilter1D;
   ctx->Driver.CopyConvolutionFilter2D = _swrast_CopyConvolutionFilter2D;
}


/*
 * Generate code for span functions.
 */

/* 24-bit BGR */
#define NAME(PREFIX) PREFIX##_B8G8R8
#define SPAN_VARS \
   const GLXContext fbdevctx = MINIGLX_CONTEXT(ctx); \
   const GLXDrawable fbdevbuf = fbdevctx->curBuffer;
#define INIT_PIXEL_PTR(P, X, Y) \
   GLubyte *P = fbdevbuf->curBottom - (Y) * fbdevbuf->rowStride + (X) * 3
#define INC_PIXEL_PTR(P) P += 3
#define STORE_RGB_PIXEL(P, R, G, B) \
   P[0] = B;  P[1] = G;  P[2] = R
#define STORE_RGBA_PIXEL(P, R, G, B, A) \
   P[0] = B;  P[1] = G;  P[2] = R
#define FETCH_RGBA_PIXEL(R, G, B, A, P) \
   R = P[2];  G = P[1];  B = P[0];  A = CHAN_MAX

#include "swrast/s_spantemp.h"


/* 32-bit BGRA */
#define NAME(PREFIX) PREFIX##_B8G8R8A8
#define SPAN_VARS \
   const GLXContext fbdevctx = MINIGLX_CONTEXT(ctx); \
   const GLXDrawable fbdevbuf = fbdevctx->curBuffer;
#define INIT_PIXEL_PTR(P, X, Y) \
   GLubyte *P = fbdevbuf->curBottom - (Y) * fbdevbuf->rowStride + (X) * 4
#define INC_PIXEL_PTR(P) P += 4
#define STORE_RGB_PIXEL(P, R, G, B) \
   P[0] = B;  P[1] = G;  P[2] = R;  P[3] = 255
#define STORE_RGBA_PIXEL(P, R, G, B, A) \
   P[0] = B;  P[1] = G;  P[2] = R;  P[3] = A
#define FETCH_RGBA_PIXEL(R, G, B, A, P) \
   R = P[2];  G = P[1];  B = P[0];  A = P[3]

#include "swrast/s_spantemp.h"


/* 16-bit BGR (XXX implement dithering someday) */
#define NAME(PREFIX) PREFIX##_B5G6R5
#define SPAN_VARS \
   const GLXContext fbdevctx = MINIGLX_CONTEXT(ctx); \
   const GLXDrawable fbdevbuf = fbdevctx->curBuffer;
#define INIT_PIXEL_PTR(P, X, Y) \
   GLushort *P = (GLushort *) (fbdevbuf->curBottom - (Y) * fbdevbuf->rowStride + (X) * 2)
#define INC_PIXEL_PTR(P) P += 1
#define STORE_RGB_PIXEL(P, R, G, B) \
   *P = ( (((R) & 0xf8) << 8) | (((G) & 0xfc) << 3) | ((B) >> 3) )
#define STORE_RGBA_PIXEL(P, R, G, B, A) \
   *P = ( (((R) & 0xf8) << 8) | (((G) & 0xfc) << 3) | ((B) >> 3) )
#define FETCH_RGBA_PIXEL(R, G, B, A, P) \
   R = ( (((*P) >> 8) & 0xf8) | (((*P) >> 11) & 0x7) ); \
   G = ( (((*P) >> 3) & 0xfc) | (((*P) >>  5) & 0x3) ); \
   B = ( (((*P) << 3) & 0xf8) | (((*P)      ) & 0x7) ); \
   A = CHAN_MAX

#include "swrast/s_spantemp.h"


/* 15-bit BGR (XXX implement dithering someday) */
#define NAME(PREFIX) PREFIX##_B5G5R5
#define SPAN_VARS \
   const GLXContext fbdevctx = MINIGLX_CONTEXT(ctx); \
   const GLXDrawable fbdevbuf = fbdevctx->curBuffer;
#define INIT_PIXEL_PTR(P, X, Y) \
   GLushort *P = (GLushort *) (fbdevbuf->curBottom - (Y) * fbdevbuf->rowStride + (X) * 2)
#define INC_PIXEL_PTR(P) P += 1
#define STORE_RGB_PIXEL(P, R, G, B) \
   *P = ( (((R) & 0xf8) << 7) | (((G) & 0xf8) << 2) | ((B) >> 3) )
#define STORE_RGBA_PIXEL(P, R, G, B, A) \
   *P = ( (((R) & 0xf8) << 7) | (((G) & 0xf8) << 2) | ((B) >> 3) )
#define FETCH_RGBA_PIXEL(R, G, B, A, P) \
   R = ( (((*P) >> 7) & 0xf8) | (((*P) >> 10) & 0x7) ); \
   G = ( (((*P) >> 2) & 0xf8) | (((*P) >>  5) & 0x7) ); \
   B = ( (((*P) << 3) & 0xf8) | (((*P)      ) & 0x7) ); \
   A = CHAN_MAX

#include "swrast/s_spantemp.h"


/* 8-bit color index */
#define NAME(PREFIX) PREFIX##_CI8
#define SPAN_VARS \
   const GLXContext fbdevctx = MINIGLX_CONTEXT(ctx); \
   const GLXDrawable fbdevbuf = fbdevctx->curBuffer;
#define INIT_PIXEL_PTR(P, X, Y) \
   GLubyte *P = fbdevbuf->curBottom - (Y) * fbdevbuf->rowStride + (X)
#define INC_PIXEL_PTR(P) P += 1
#define STORE_CI_PIXEL(P, CI) \
   P[0] = CI
#define FETCH_CI_PIXEL(CI, P) \
   CI = P[0]

#include "swrast/s_spantemp.h"


/**********************************************************************/
/* FBdev fucntions                                                    */
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
   dpy->FrameBufferFD = open("/dev/fb0", O_RDWR);
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
   const int width = win->glframebuffer.Width;
   const int height = win->glframebuffer.Height;

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
      dpy->VarInfo.pixclock = 7408;
      dpy->VarInfo.left_margin = 248;
      dpy->VarInfo.right_margin = 16;
      dpy->VarInfo.upper_margin = 38;
      dpy->VarInfo.lower_margin = 1;
      dpy->VarInfo.hsync_len = 144;
      dpy->VarInfo.vsync_len = 3;
   }
   else {
      /* XXX need timings for other screen sizes */
      printf("XXXX only 1280 x 1024 windows are supported at this time!\n");
      assert(0);
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



/*
 * Restore framebuffer to state it was in before we started.
 * Called from XDestroyWindow().
 */
static GLboolean
RestoreFBDev( Display *dpy, Window win )
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
/* Public API functions (Xlib and GLX)                                */
/**********************************************************************/

Display *
WRAP(XOpenDisplay)( const char *display_name )
{
   Display *dpy;

   dpy = (Display *) _mesa_calloc(sizeof(Display));
   if (!dpy)
      return NULL;

   if (!OpenFBDev(dpy)) {
      _mesa_free(dpy);
      return NULL;
   }

   return dpy;
}


void
WRAP(XCloseDisplay)( Display *dpy )
{
   CleanupFBDev(dpy);
   _mesa_free(dpy);
}



Window
WRAP(XCreateWindow)( Display *dpy, Window parent, int x, int y,
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

   win = MALLOC_STRUCT(MiniGLXWindowRec);
   if (!win)
      return NULL;

   /* init Mesa framebuffer data */
   _mesa_initialize_framebuffer(&win->glframebuffer, &visual->glvisual,
                                visual->glvisual.haveDepthBuffer,   /* sw? */
                                visual->glvisual.haveStencilBuffer, /* sw? */
                                visual->glvisual.haveAccumBuffer,   /* sw? */
                                GL_FALSE /* sw alpha? */
                                );
   win->glframebuffer.Width = width;
   win->glframebuffer.Height = height;

   /* init other per-window fields */
   win->x = 0;
   win->y = 0;
   win->w = width;
   win->h = height;
   win->visual = visual;  /* ptr assignment */

   /* do fbdev setup */
   if (!SetupFBDev(dpy, win)) {
      _mesa_free(win);
      return NULL;
   }


   win->bytesPerPixel = dpy->VarInfo.bits_per_pixel / 8;
   win->rowStride = width * win->bytesPerPixel;
   win->size = win->rowStride * height * win->bytesPerPixel; /* XXX stride? */
   win->frontStart = dpy->FrameBuffer;
   win->frontBottom = (GLubyte *) win->frontStart
                    + (dpy->VarInfo.yres_virtual - 1) * win->rowStride;

   if (visual->glvisual.doubleBufferMode) {
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

   dpy->NumWindows++;
   dpy->TheWindow = win;

   return win;
}


int
WRAP(DefaultScreen)( Display *dpy )
{
   (void) dpy;
   return 0;
}


Window
WRAP(RootWindow)( Display *display, int scrNum )
{
   return 0;
}


void
WRAP(XDestroyWindow)( Display *dpy, Window win )
{
   assert(dpy);
   if (win) {
      /* check if destroying the current buffer */
      Window curDraw = WRAP(glXGetCurrentDrawable)();
      Window curRead = WRAP(glXGetCurrentReadDrawable)();
      if (win == curDraw || win == curRead) {
         WRAP(glXMakeCurrent)( dpy, NULL, NULL);
      }
      /* free the software depth, stencil, accum buffers */
      RestoreFBDev(dpy, win);
      _mesa_free_framebuffer_data(&win->glframebuffer);
      _mesa_free(win);
      dpy->NumWindows--;
      assert(dpy->NumWindows == 0);
      dpy->TheWindow = NULL;
   }
}


void
WRAP(XMapWindow)( Display *display, Window w )
{
   /* no-op */
   (void) display;
   (void) w;
}


Colormap
WRAP(XCreateColormap)( Display *display, Window w, Visual *visual, int alloc )
{
   return (Colormap) _mesa_malloc(1); /* dummy */
}


void
WRAP(XFreeColormap)( Display *display, Colormap cmap )
{
   _mesa_free(cmap);
}


XVisualInfo*
WRAP(glXChooseVisual)( Display *display, int screen, int *attribs )
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

   ASSERT(display);

   vis = (Visual *) _mesa_calloc(sizeof(Visual));
   if (!vis)
      return NULL;

   vis->dpy = display;

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
      case GLX_DEPTH_SIZE:
         depthBits = attrib[1];
         attrib++;
         break;
      case GLX_STENCIL_SIZE:
         stencilBits = attrib[1];
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
      default:
         /* unexpected token */
         _mesa_free(vis);
         return NULL;
      }
   }

   if (!_mesa_initialize_visual(&vis->glvisual, rgbFlag, dbFlag, stereoFlag,
                                redBits, greenBits, blueBits, alphaBits,
                                indexBits, depthBits, stencilBits,
                                accumRedBits, accumGreenBits,
                                accumBlueBits, accumAlphaBits,
                                numSamples)) {
      /* something was invalid */
      _mesa_free(vis);
      return NULL;
   }

   visInfo = (XVisualInfo *) _mesa_malloc(sizeof(XVisualInfo));
   if (!visInfo) {
      _mesa_free(vis);
      return NULL;
   }
   visInfo->visual = vis;
   vis->visInfo = visInfo;

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


GLXContext
WRAP(glXCreateContext)( Display *dpy, XVisualInfo *vis,
                  GLXContext shareList, Bool direct )
{
   GLXContext ctx;
   GLcontext *glctx;

   ASSERT(vis);

   ctx = CALLOC_STRUCT(MiniGLXContextRec);
   if (!ctx)
      return NULL;

   if (!_mesa_initialize_context(&ctx->glcontext, &vis->visual->glvisual,
                                 shareList ? &shareList->glcontext : NULL,
                                 (void *) ctx, GL_FALSE)) {
      _mesa_free(ctx);
      return NULL;
   }

#if 0
   ctx->visual = visual;
#endif

   /* Create module contexts */
   glctx = (GLcontext *) &ctx->glcontext;
   init_core_functions( glctx );
   _swrast_CreateContext( glctx );
   _ac_CreateContext( glctx );
   _tnl_CreateContext( glctx );
   _swsetup_CreateContext( glctx );
   _swsetup_Wakeup( glctx );

   /* swrast init */
   {
      struct swrast_device_driver *swdd;
      swdd = _swrast_GetDeviceDriverReference( glctx );
      swdd->SetBuffer = set_buffer;
      if (vis->visual->pixelFormat == PF_B8G8R8) {
         swdd->WriteRGBASpan = write_rgba_span_B8G8R8;
         swdd->WriteRGBSpan = write_rgb_span_B8G8R8;
         swdd->WriteMonoRGBASpan = write_monorgba_span_B8G8R8;
         swdd->WriteRGBAPixels = write_rgba_pixels_B8G8R8;
         swdd->WriteMonoRGBAPixels = write_monorgba_pixels_B8G8R8;
         swdd->ReadRGBASpan = read_rgba_span_B8G8R8;
         swdd->ReadRGBAPixels = read_rgba_pixels_B8G8R8;
      }
      else if (vis->visual->pixelFormat == PF_B8G8R8A8) {
         swdd->WriteRGBASpan = write_rgba_span_B8G8R8A8;
         swdd->WriteRGBSpan = write_rgb_span_B8G8R8A8;
         swdd->WriteMonoRGBASpan = write_monorgba_span_B8G8R8A8;
         swdd->WriteRGBAPixels = write_rgba_pixels_B8G8R8A8;
         swdd->WriteMonoRGBAPixels = write_monorgba_pixels_B8G8R8A8;
         swdd->ReadRGBASpan = read_rgba_span_B8G8R8A8;
         swdd->ReadRGBAPixels = read_rgba_pixels_B8G8R8A8;
      }
      else if (vis->visual->pixelFormat == PF_B5G6R5) {
         swdd->WriteRGBASpan = write_rgba_span_B5G6R5;
         swdd->WriteRGBSpan = write_rgb_span_B5G6R5;
         swdd->WriteMonoRGBASpan = write_monorgba_span_B5G6R5;
         swdd->WriteRGBAPixels = write_rgba_pixels_B5G6R5;
         swdd->WriteMonoRGBAPixels = write_monorgba_pixels_B5G6R5;
         swdd->ReadRGBASpan = read_rgba_span_B5G6R5;
         swdd->ReadRGBAPixels = read_rgba_pixels_B5G6R5;
      }
      else if (vis->visual->pixelFormat == PF_B5G5R5) {
         swdd->WriteRGBASpan = write_rgba_span_B5G5R5;
         swdd->WriteRGBSpan = write_rgb_span_B5G5R5;
         swdd->WriteMonoRGBASpan = write_monorgba_span_B5G5R5;
         swdd->WriteRGBAPixels = write_rgba_pixels_B5G5R5;
         swdd->WriteMonoRGBAPixels = write_monorgba_pixels_B5G5R5;
         swdd->ReadRGBASpan = read_rgba_span_B5G5R5;
         swdd->ReadRGBAPixels = read_rgba_pixels_B5G5R5;
      }
      else if (vis->visual->pixelFormat == PF_CI8) {
         swdd->WriteCI32Span = write_index32_span_CI8;
         swdd->WriteCI8Span = write_index8_span_CI8;
         swdd->WriteMonoCISpan = write_monoindex_span_CI8;
         swdd->WriteCI32Pixels = write_index_pixels_CI8;
         swdd->WriteMonoCIPixels = write_monoindex_pixels_CI8;
         swdd->ReadCI32Span = read_index_span_CI8;
         swdd->ReadCI32Pixels = read_index_pixels_CI8;
      }
      else {
         _mesa_printf("bad pixelformat: %d\n", vis->visual->pixelFormat);
      }
   }

   /* use default TCL pipeline */
   {
      TNLcontext *tnl = TNL_CONTEXT(glctx);
      tnl->Driver.RunPipeline = _tnl_run_pipeline;
   }

   _mesa_enable_sw_extensions(glctx);

   return ctx;
}


void
WRAP(glXDestroyContext)( Display *dpy, GLXContext ctx )
{
   GLXContext glxctx = WRAP(glXGetCurrentContext)();

   if (glxctx) {
      if (glxctx == ctx) {
         /* destroying current context */
         _mesa_make_current2(NULL, NULL, NULL);
         _mesa_notifyDestroy(&ctx->glcontext);
      }
      _mesa_free_context_data(&ctx->glcontext);
      _mesa_free(ctx);
   }
}


Bool
WRAP(glXMakeCurrent)( Display *dpy, GLXDrawable drawable, GLXContext ctx)
{
   if (dpy && drawable && ctx) {
      _mesa_make_current2( &ctx->glcontext,
                           &drawable->glframebuffer,
                           &drawable->glframebuffer );
      ctx->drawBuffer = drawable;
      ctx->readBuffer = drawable;
      ctx->curBuffer = drawable;
   }
   else {
      /* unbind */
      _mesa_make_current2( NULL, NULL, NULL );
   }
   return True;
}


void
WRAP(glXSwapBuffers)( Display *dpy, GLXDrawable drawable )
{
   GLXContext glxctx = WRAP(glXGetCurrentContext)();

   if (!dpy || !drawable)
      return;

   /* check if swapping currently bound buffer */
   if (glxctx->drawBuffer == drawable) {
      /* flush pending rendering */
      _mesa_notifySwapBuffers(&glxctx->glcontext);
   }

   ASSERT(drawable->frontStart);
   ASSERT(drawable->backStart);
   _mesa_memcpy(drawable->frontStart, drawable->backStart, drawable->size);
}


GLXContext
WRAP(glXGetCurrentContext)( void )
{
   GET_CURRENT_CONTEXT(ctx);
   return (GLXContext) ctx;
}


GLXDrawable
WRAP(glXGetCurrentDrawable)( void )
{
   GLXContext glxctx = WRAP(glXGetCurrentContext)();
   if (glxctx)
      return glxctx->drawBuffer;
   else
      return NULL;
}


GLXDrawable
WRAP(glXGetCurrentReadDrawable)( void )
{
   GLXContext glxctx = WRAP(glXGetCurrentContext)();
   if (glxctx)
      return glxctx->readBuffer;
   else
      return NULL;
}


const void *
WRAP(glXGetProcAddress)( const GLubyte *procName )
{
   struct name_address {
      const char *name;
      const void *func;
   };
   static const struct name_address functions[] = {
#if 0
      { "glFBDevGetString", (void *) glFBDevGetString },
      { "glFBDevGetProcAddress", (void *) glFBDevGetProcAddress },
      { "glFBDevCreateVisual", (void *) glFBDevCreateVisual },
      { "glFBDevDestroyVisual", (void *) glFBDevDestroyVisual },
      { "glFBDevGetVisualAttrib", (void *) glFBDevGetVisualAttrib },
      { "glFBDevCreateBuffer", (void *) glFBDevCreateBuffer },
      { "glFBDevDestroyBuffer", (void *) glFBDevDestroyBuffer },
      { "glFBDevGetBufferAttrib", (void *) glFBDevGetBufferAttrib },
      { "glFBDevGetCurrentDrawBuffer", (void *) glFBDevGetCurrentDrawBuffer },
      { "glFBDevGetCurrentReadBuffer", (void *) glFBDevGetCurrentReadBuffer },
      { "glFBDevSwapBuffers", (void *) glFBDevSwapBuffers },
      { "glFBDevCreateContext", (void *) glFBDevCreateContext },
      { "glFBDevDestroyContext", (void *) glFBDevDestroyContext },
      { "glFBDevGetContextAttrib", (void *) glFBDevGetContextAttrib },
      { "glFBDevGetCurrentContext", (void *) glFBDevGetCurrentContext },
      { "glFBDevMakeCurrent", (void *) glFBDevMakeCurrent },
#endif
      { NULL, NULL }
   };
   const struct name_address *entry;
   for (entry = functions; entry->name; entry++) {
      if (_mesa_strcmp(entry->name, (const char *) procName) == 0) {
         return entry->func;
      }
   }
   return _glapi_get_proc_address((const char *) procName);
}
