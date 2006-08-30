
/*
 * GL_ARB_multitexture demo
 *
 * Command line options:
 *    -info      print GL implementation information
 *
 *
 * Brian Paul  November 1998  This program is in the public domain.
 * Modified on 12 Feb 2002 for > 2 texture units.
 */

#define GL_GLEXT_PROTOTYPES

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

#include "readtex.h"

enum {
   WHOLERECT,
   RENDER,
   SWAPBUF,

   UPLOAD_CONVENTIONAL,
   UPLOAD_PBO_NAIVE,
   UPLOAD_PBO_PINGPONG,
   UPLOAD_PBO_WITH_RESET,
   UPLOAD_NOOP,

   QUIT
};

static GLint upload_style = UPLOAD_CONVENTIONAL;
static GLboolean whole_rect = 1;
static GLboolean do_render = 1;
static GLboolean do_swapbuffers = 1;


static GLuint col = 0x0;
static GLfloat Xrot = 20.0, Yrot = 30.0;

static GLuint Width = 1024;
static GLuint Height = 512;

#define NR_PBO 2
static GLuint texObj, DrawPBO[NR_PBO];


static void Idle( void )
{
   col++;
   
   glutPostRedisplay();
}

static int min( int a, int b ) { return a < b ? a : b; }

static void DrawObject()
{
   GLint size = Width * Height * 4;
   static char *static_image = NULL;
   static int current = 0;

   switch (upload_style) {
   case UPLOAD_PBO_NAIVE:
      /* Continually upload from the one pbo without any attempt to
       * decouple from hardware trying to access the same data:
       */
      glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT, DrawPBO[0]);

      {
	 char *image = glMapBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT, GL_WRITE_ONLY_ARB);
	 memset(image, col&0xff, size);
	 glUnmapBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT);
      }
   
      glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, Width, Height, 0,
		   GL_BGRA, GL_UNSIGNED_BYTE, NULL);
      glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT, 0);
      break;

   case UPLOAD_PBO_PINGPONG:
      /* Cycle through the available upload buffers to avoid waiting
       * on buffers currently enqueued on the hardware.  Avoids
       * waiting on buffer contents that may still be referenced by
       * hardware.
       */
      current = (current + 1) % NR_PBO;

      glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT, DrawPBO[current]);

      {
	 char *image = glMapBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT, GL_WRITE_ONLY_ARB);
	 memset(image, col&0xff, size);
	 glUnmapBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT);
      }
   
      glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, Width, Height, 0,
		   GL_BGRA, GL_UNSIGNED_BYTE, NULL);
      glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT, 0);
      break;


   case UPLOAD_PBO_WITH_RESET:
      /* Alternate approach, uses BufferDataARB(NULL) to explicitly
       * release the old image contents from the pbo prior to upload.
       * Similar effect to double buffering pbos as above, but a
       * little more subtle as the implications of the NULL data are
       * not entirely clear.  I don't know if all drivers will take
       * full advantage of the optimization or not.
       */
      glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT, DrawPBO[0]);

      /* XXX: This is extremely important - semantically makes the buffer
       * contents undefined, but in practice means that the driver can
       * release the old copy of the texture and allocate a new one
       * without waiting for outstanding rendering to complete.
       */
      glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_EXT, size, NULL, GL_STREAM_DRAW_ARB);

      {
	 char *image = glMapBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT, GL_WRITE_ONLY_ARB);
	 memset(image, col&0xff, size);
	 glUnmapBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT);
      }
   
      glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, Width, Height, 0,
		   GL_BGRA, GL_UNSIGNED_BYTE, NULL);
      glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT, 0);
      break;


   case UPLOAD_CONVENTIONAL: 
      if (static_image == NULL) 
	 static_image = malloc(size);

      memset(static_image, col&0xff, size);

      /* BGRA should be the fast path for regular uploads as well.
       */
      glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, Width, Height, 0,
		   GL_BGRA, GL_UNSIGNED_BYTE, static_image);
      break;

   case UPLOAD_NOOP:
      break;
   }

   if (do_render)
   {
      int x,y,w,h;

      if (whole_rect) {
	 x = y = 0;
	 w = Width;
	 h = Height;
      }
      else {
	 x = y = 0;
	 w = min(10, Width);
	 h = min(10, Height);
      }

      glBegin(GL_QUADS);

      glTexCoord2f( x, y);
      glVertex2f( x, y );

      glTexCoord2f( x, y + h);
      glVertex2f( x, y + h);

      glTexCoord2f( x + w, y + h);
      glVertex2f( x + w, y + h );

      glTexCoord2f( x + w, y);
      glVertex2f( x + w, y );

      glEnd();
   }
}



static void Display( void )
{
   static GLint T0 = 0;
   static GLint Frames = 0;
   GLint t;

   glClear( GL_COLOR_BUFFER_BIT );

   glPushMatrix();
      DrawObject();
   glPopMatrix();

   if (do_swapbuffers) 
      glutSwapBuffers();
   else
      glFlush();

   Frames++;

   t = glutGet(GLUT_ELAPSED_TIME);
   if (t - T0 >= 1000) {
      GLfloat seconds = (t - T0) / 1000.0;

      GLfloat fps = Frames / seconds;
      printf("%d frames in %6.3f seconds = %6.3f FPS\n", Frames, seconds, fps);

      T0 = t;
      Frames = 0;
   }
}


static void Reshape( int width, int height )
{
   glViewport( 0, 0, width, height );
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
/*    glFrustum( -1.0, 1.0, -1.0, 1.0, 10.0, 100.0 ); */
   gluOrtho2D( 0, width, height, 0 );
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();
/*    glTranslatef(0.375, 0.375, 0); */
}


static void ModeMenu(int entry)
{
   switch (entry) {
   case WHOLERECT:
      whole_rect = !whole_rect;
      break;
   case RENDER:
      do_render = !do_render;
      break;
   case SWAPBUF:
      do_swapbuffers = !do_swapbuffers;
      break;

   case UPLOAD_CONVENTIONAL:
   case UPLOAD_PBO_NAIVE:
   case UPLOAD_PBO_PINGPONG:
   case UPLOAD_PBO_WITH_RESET:
   case UPLOAD_NOOP:
      upload_style = entry;
      break;

   case QUIT:
      exit(0);
      break;
   }

   glutPostRedisplay();
}


static void Key( unsigned char key, int x, int y )
{
   (void) x;
   (void) y;
   switch (key) {
      case 27:
         exit(0);
         break;
   }
   glutPostRedisplay();
}


static void SpecialKey( int key, int x, int y )
{
   float step = 3.0;
   (void) x;
   (void) y;

   switch (key) {
      case GLUT_KEY_UP:
         Xrot += step;
         break;
      case GLUT_KEY_DOWN:
         Xrot -= step;
         break;
      case GLUT_KEY_LEFT:
         Yrot += step;
         break;
      case GLUT_KEY_RIGHT:
         Yrot -= step;
         break;
   }
   glutPostRedisplay();
}


static void Init( int argc, char *argv[] )
{
   const char *exten = (const char *) glGetString(GL_EXTENSIONS);
   GLint size;


   if (!strstr(exten, "GL_ARB_multitexture")) {
      printf("Sorry, GL_ARB_multitexture not supported by this renderer.\n");
      exit(1);
   }

   glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);
   printf("%d x %d max texture size\n", size, size);

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   /* allocate two texture objects */
   glGenTextures(1, &texObj);

   /* setup the texture objects */
   glActiveTextureARB(GL_TEXTURE0_ARB);
   glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texObj);

   glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   glGenBuffersARB(NR_PBO, DrawPBO);

   {
      int i;
      for (i = 0; i < NR_PBO; i++) {
	 glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT, DrawPBO[i]);
	 glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_EXT, Width * Height * 4, NULL, GL_STREAM_DRAW_ARB);
      }
      glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_EXT, 0);
   }
   
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

   glEnable(GL_TEXTURE_RECTANGLE_ARB);

   glShadeModel(GL_SMOOTH);
   glClearColor(0.3, 0.3, 0.4, 1.0);

   if (argc > 1 && strcmp(argv[1], "-info")==0) {
      printf("GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
      printf("GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
      printf("GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
      printf("GL_EXTENSIONS = %s\n", (char *) glGetString(GL_EXTENSIONS));
   }
}


int main( int argc, char *argv[] )
{
   GLint i;

   glutInit( &argc, argv );

   for (i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-w") == 0) {
         Width = atoi(argv[i+1]);
         if (Width <= 0) {
            printf("Error, bad width\n");
            exit(1);
         }
         i++;
      }
      else if (strcmp(argv[i], "-h") == 0) {
         Height = atoi(argv[i+1]);
         if (Height <= 0) {
            printf("Error, bad height\n");
            exit(1);
         }
         i++;
      }
   }

   glutInitWindowSize( Width, Height );
   glutInitWindowPosition( 0, 0 );
   glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
   glutCreateWindow(argv[0] );

   Init( argc, argv );

   glutReshapeFunc( Reshape );
   glutKeyboardFunc( Key );
   glutSpecialFunc( SpecialKey );
   glutDisplayFunc( Display );
   glutIdleFunc( Idle );

   glutCreateMenu(ModeMenu);
   glutAddMenuEntry("Wholerect", WHOLERECT);
   glutAddMenuEntry("Render", RENDER);
   glutAddMenuEntry("Swapbuf", SWAPBUF);

   glutAddMenuEntry("Upload style CONVENTIONAL", UPLOAD_CONVENTIONAL);
   glutAddMenuEntry("Upload style PBO_NAIVE", UPLOAD_PBO_NAIVE);
   glutAddMenuEntry("Upload style PBO_PINGPONG", UPLOAD_PBO_PINGPONG);
   glutAddMenuEntry("Upload style PBO_WITH_RESET", UPLOAD_PBO_WITH_RESET);
   glutAddMenuEntry("Upload style NOOP", UPLOAD_NOOP);

   glutAddMenuEntry("Quit", QUIT);
   glutAttachMenu(GLUT_RIGHT_BUTTON);

   glutMainLoop();
   return 0;
}
