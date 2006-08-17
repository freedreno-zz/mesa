
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>



GLenum doubleBuffer;

/* Demonstrate an equivalent to paletted texturing using fragment
 * programs and dependent texturing.  This requires at least one
 * texture unit to be reserved for the palette lookup.
 */

static void Init( void )
{
   static const char *modulate2D =
      "!!ARBfp1.0\n"
      "TEMP index; \n"
      "TEX index, fragment.texcoord[0], texture[0], 2D; \n"
      "TEX result.color, index, texture[1], 1D; \n"
      "END"
      ;
   GLuint modulateProg;
   GLuint Texture;

   if (!glutExtensionSupported("GL_ARB_fragment_program")) {
      printf("Error: GL_ARB_fragment_program not supported!\n");
      exit(1);
   }
   printf("GL_RENDERER = %s\n", (char *) glGetString(GL_RENDERER));

   /* Setup the fragment program */
   glGenProgramsARB(1, &modulateProg);
   glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, modulateProg);
   glProgramStringARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
		      strlen(modulate2D), (const GLubyte *)modulate2D);

   printf("glGetError = 0x%x\n", (int) glGetError());
   printf("glError(GL_PROGRAM_ERROR_STRING_ARB) = %s\n",
          (char *) glGetString(GL_PROGRAM_ERROR_STRING_ARB));
   assert(glIsProgramARB(modulateProg));

   glEnable(GL_FRAGMENT_PROGRAM_ARB);


   {
#define HEIGHT 8
#define WIDTH 32

#define B 0
#define G 1
#define R 2
#define A 3

     static char texture[HEIGHT * WIDTH + 1] =
	"                                "
	"    MMM    EEEE   SSS    AAA    "
	"   M M M  E      S   S  A   A   "
	"   M M M  EEEE    SS    A   A   "
	"   M M M  E         SS  AAAAA   "
	"   M   M  E      S   S  A   A   "
	"   M   M   EEEE   SSS   A   A   ";
      
      GLubyte table[256][4];

      
      
      /* load the color table for each texel-index */
      memset(table, 0xff, 256*4);
      table[' '][B] = 255;
      table[' '][G] = 255;
      table[' '][R] = 255;
      table[' '][A] = 64;
      table['M'][B] = 0;
      table['M'][G] = 0;
      table['M'][R] = 255;
      table['M'][A] = 255;
      table['E'][B] = 0;
      table['E'][G] = 255;
      table['E'][R] = 0;
      table['E'][A] = 255;
      table['S'][B] = 255;
      table['S'][G] = 0;
      table['S'][R] = 0;
      table['S'][A] = 255;
      table['A'][B] = 0;
      table['A'][G] = 255;
      table['A'][R] = 255;
      table['A'][A] = 255;

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


      /* Load indexed texture as a 2D I8 texture */
      glActiveTextureARB(GL_TEXTURE0_ARB);
      glGenTextures(1, &Texture);
      glBindTexture(GL_TEXTURE_2D, Texture);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTexImage2D(GL_TEXTURE_2D,       /* target */
		   0,                   /* level */
		   GL_INTENSITY, /* internal format */
		   WIDTH, HEIGHT,       /* width, height */
		   0,                   /* border */
		   GL_LUMINANCE,      /* texture format */
		   GL_UNSIGNED_BYTE,    /* texture type */
		   texture);            /* the texture */


   printf("glGetError = 0x%x\n", (int) glGetError());
   printf("glError(GL_PROGRAM_ERROR_STRING_ARB) = %s\n",
          (char *) glGetString(GL_PROGRAM_ERROR_STRING_ARB));

      glEnable(GL_TEXTURE_2D);

      /* Load "pallete" as a 1D BGRA8888 texture */
      glActiveTextureARB(GL_TEXTURE1_ARB);
      glGenTextures(1, &Texture);
      glBindTexture(GL_TEXTURE_1D, Texture);

      glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTexImage1D(GL_TEXTURE_1D,       /* target */
		   0,                   /* level */
		   GL_RGBA,	/* internal format */
		   256,		/* width */
		   0,                   /* border */
		   GL_BGRA,      /* texture format */
		   GL_UNSIGNED_BYTE,    /* texture type */
		   table);            /* the texture */

      glEnable(GL_TEXTURE_1D);

/*       glEnable(GL_BLEND); */
/*       glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); */
#undef HEIGHT
#undef WIDTH
   }


   glClearColor(.3, .3, .3, 0);
}

static void Reshape(int width, int height)
{

    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -0.5, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

static void Key(unsigned char key, int x, int y)
{

    switch (key) {
      case 27:
	exit(1);
      default:
	return;
    }

    glutPostRedisplay();
}

static void Draw(void)
{
   glClear(GL_COLOR_BUFFER_BIT); 

   glBegin(GL_QUADS);
   glTexCoord2f(1,1); 
   glVertex3f( 0.9, -0.9, -30.0);
   glTexCoord2f(1,0); 
   glVertex3f( 0.9,  0.9, -30.0);
   glTexCoord2f(0,0); 
   glVertex3f(-0.9,  0.9, -30.0);
   glTexCoord2f(0,1); 
   glVertex3f(-0.9,  -0.9, -30.0);
   glEnd();

   glFlush();

   if (doubleBuffer) {
      glutSwapBuffers();
   }


}

static GLenum Args(int argc, char **argv)
{
    GLint i;

    doubleBuffer = GL_FALSE;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-sb") == 0) {
	    doubleBuffer = GL_FALSE;
	} else if (strcmp(argv[i], "-db") == 0) {
	    doubleBuffer = GL_TRUE;
	} else {
	    fprintf(stderr, "%s (Bad option).\n", argv[i]);
	    return GL_FALSE;
	}
    }
    return GL_TRUE;
}

int main(int argc, char **argv)
{
    GLenum type;

    glutInit(&argc, argv);

    if (Args(argc, argv) == GL_FALSE) {
	exit(1);
    }

    glutInitWindowPosition(0, 0); glutInitWindowSize( 250, 250);

    type = GLUT_RGB;
    type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
    glutInitDisplayMode(type);

    if (glutCreateWindow("First Tri") == GL_FALSE) {
	exit(1);
    }

    Init();

    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Key);
    glutDisplayFunc(Draw);
    glutMainLoop();
	return 0;
}
