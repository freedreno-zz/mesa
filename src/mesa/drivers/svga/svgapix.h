#ifndef SVGAPIX_H
#define SVGAPIX_H

#include "GL/gl.h"
#include "svgamesa.h"
#include "context.h"
#include "vga.h"

struct svgamesa_context {
   GLcontext *gl_ctx;		/* the core Mesa context */
   GLvisual *gl_vis;		/* describes the color buffer */
   GLframebuffer *gl_buffer;	/* the ancillary buffers */
   GLuint index;		/* current color index */
   GLuint clear_index;		/* current clear index */
   GLint red, green, blue;	/* current rgb color */
   GLuint truecolor;		/* current rgb color */
   GLint clear_red, 
         clear_green, 
	 clear_blue;		/* current clear rgb color */
   GLuint clear_truecolor;	/* current clear rgb color */
   GLushort hicolor;		/* current hicolor */
   GLushort clear_hicolor;	/* current clear hicolor */
   GLint width, height;		/* size of color buffer */
   GLint depth;			/* bits per pixel (8,16,24 or 32) */
};

typedef struct { GLubyte b,g,r; } _RGB;

struct svga_buffer {   
   GLint     Depth;
   GLint     BufferSize;
   GLubyte   * FrontBuffer;
   GLubyte   * BackBuffer;
   GLubyte   * VideoRam;
};

extern struct svga_buffer SVGABuffer;
extern vga_modeinfo * SVGAInfo;
extern SVGAMesaContext SVGAMesa;    /* the current context */

#endif /* SVGAPIX_H */