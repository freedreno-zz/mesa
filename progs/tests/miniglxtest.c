/* $Id: miniglxtest.c,v 1.1.4.3 2002/11/27 21:04:18 brianp Exp $ */

/*
 * Test the mini GLX interface.
 */


#include <GL/gl.h>
#include <GL/miniglx.h>
#include <stdio.h>
#include <stdlib.h>


static void redraw( Display *dpy, Window w, int rot )
{
   printf("Redraw event\n");

   glClear( GL_COLOR_BUFFER_BIT );

   glColor3f( 1.0, 1.0, 0.0 );
   glPushMatrix();
   glRotatef(rot, 0, 0, 1);
   glScalef(.5, .5, .5);
   glRectf( -1, -1, 1, 1 );
   glPopMatrix();

   WRAP(glXSwapBuffers)( dpy, w );
}


static Window make_rgb_db_window( Display *dpy,
				  unsigned int width, unsigned int height )
{
   int attrib[] = { GLX_RGBA,
		    GLX_RED_SIZE, 1,
		    GLX_GREEN_SIZE, 1,
		    GLX_BLUE_SIZE, 1,
		    GLX_DOUBLEBUFFER,
		    None };
   int scrnum;
   XSetWindowAttributes attr;
   unsigned long mask;
   Window root;
   Window win;
   GLXContext ctx;
   XVisualInfo *visinfo;

   scrnum = WRAP(DefaultScreen)( dpy );
   root = WRAP(RootWindow)( dpy, scrnum );

   visinfo = WRAP(glXChooseVisual)( dpy, scrnum, attrib );
   if (!visinfo) {
      printf("Error: couldn't get an RGB, Double-buffered visual\n");
      exit(1);
   }

   /* window attributes */
   attr.background_pixel = 0;
   attr.border_pixel = 0;
   attr.colormap = WRAP(XCreateColormap)( dpy, root, visinfo->visual, AllocNone);
   attr.event_mask = StructureNotifyMask | ExposureMask;
   mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

   win = WRAP(XCreateWindow)( dpy, root, 0, 0, width, height,
		        0, visinfo->depth, InputOutput,
		        visinfo->visual, mask, &attr );

   ctx = WRAP(glXCreateContext)( dpy, visinfo, NULL, True );
   if (!ctx) {
      printf("Error: glXCreateContext failed\n");
      exit(1);
   }

   WRAP(glXMakeCurrent)( dpy, win, ctx );

   return win;
}


static void event_loop( Display *dpy, Window win )
{
   int i;

   printf("Hang on... drawing 5 frames\n");
   for (i = 0; i < 5; i++) {
      redraw( dpy, win, i*10 );
   }
}


int main( int argc, char *argv[] )
{
   Display *dpy;
   Window win;

   dpy = WRAP(XOpenDisplay)(NULL);

   win = make_rgb_db_window( dpy, 800, 600);

   glShadeModel( GL_FLAT );
   glClearColor( 0.5, 0.5, 0.5, 1.0 );

   WRAP(XMapWindow)( dpy, win );

   event_loop( dpy, win );

   WRAP(XDestroyWindow)( dpy, win );

   WRAP(XCloseDisplay)( dpy );

   return 0;
}
