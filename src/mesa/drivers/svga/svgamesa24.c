
#include "svgapix.h"

_RGB * rgbBuffer;

inline int RGB2BGR24(int c)
{
	asm("rorw  $8, %0\n"	 
	    "rorl $16, %0\n"	 
	    "rorw  $8, %0\n"	 
	    "shrl  $8, %0\n"	 
      : "=q"(c):"0"(c));
    return c;
}


int __svga_drawpixel24(int x, int y, GLubyte r, GLubyte g, GLubyte b)
{
    unsigned long offset;

    rgbBuffer=(void *)SVGABuffer.BackBuffer;
    y = SVGAInfo->height-y-1;
    offset = y * SVGAInfo->width + x;

    rgbBuffer[offset].r=r;
    rgbBuffer[offset].g=g;
    rgbBuffer[offset].b=b;

    return 0;
}

unsigned long __svga_getpixel24(int x, int y)
{
    unsigned long offset;

    rgbBuffer=(void *)SVGABuffer.BackBuffer;
    y = SVGAInfo->height-y-1;
    offset = y * SVGAInfo->width + x;
    return rgbBuffer[offset].r<<16 | rgbBuffer[offset].g<<8 | rgbBuffer[offset].b;
}

void __set_color24( GLcontext *ctx,
                    GLubyte red, GLubyte green,
                    GLubyte blue, GLubyte alpha )
{
   SVGAMesa->red = red;
   SVGAMesa->green = green;
   SVGAMesa->blue = blue;
/*   SVGAMesa->truecolor = red<<16 | green<<8 | blue; */
}

void __clear_color24( GLcontext *ctx,
                      GLubyte red, GLubyte green,
                      GLubyte blue, GLubyte alpha )
{
   SVGAMesa->clear_red = red;
   SVGAMesa->clear_green = green;
   SVGAMesa->clear_blue = blue;
/*   SVGAMesa->clear_truecolor = red<<16 | green<<8 | blue; */
}

GLbitfield __clear24( GLcontext *ctx, GLbitfield mask, GLboolean all,
                      GLint x, GLint y, GLint width, GLint height )
{
   int i,j;
   
   if (mask & GL_COLOR_BUFFER_BIT) {
    if (all) {
     rgbBuffer=(void *)SVGABuffer.BackBuffer;
     for (i=0;i<SVGABuffer.BufferSize / 3;i++)
      {
       rgbBuffer[i].r=SVGAMesa->clear_red;
       rgbBuffer[i].g=SVGAMesa->clear_green;
       rgbBuffer[i].b=SVGAMesa->clear_blue;
      } 
    } else {
    for (i=x;i<width;i++)    
     for (j=y;j<height;j++)    
      __svga_drawpixel24( i, j, SVGAMesa->clear_red,
                                SVGAMesa->clear_green,
				SVGAMesa->clear_blue);
    }	
   }
   return mask & (~GL_COLOR_BUFFER_BIT);
}

void __write_rgba_span24( const GLcontext *ctx, GLuint n, GLint x, GLint y,
                          const GLubyte rgba[][4], const GLubyte mask[] )
{
   int i;
   if (mask) {
      /* draw some pixels */
      for (i=0; i<n; i++, x++) {
         if (mask[i]) {
         __svga_drawpixel24( x, y, rgba[i][RCOMP],
	                           rgba[i][GCOMP],
				   rgba[i][BCOMP]);
         }
      }
   }
   else {
      /* draw all pixels */
      for (i=0; i<n; i++, x++) {
         __svga_drawpixel24( x, y, rgba[i][RCOMP],
	                           rgba[i][GCOMP],
				   rgba[i][BCOMP]);
      }
   }
}

void __write_mono_rgba_span24( const GLcontext *ctx,
                               GLuint n, GLint x, GLint y,
                               const GLubyte mask[])
{
   int i;
   for (i=0; i<n; i++, x++) {
      if (mask[i]) {
         __svga_drawpixel24( x, y, SVGAMesa->red,
                                   SVGAMesa->green,
				   SVGAMesa->blue);
      }
   }
}

void __read_rgba_span24( const GLcontext *ctx, GLuint n, GLint x, GLint y,
                         GLubyte rgba[][4] )
{
   int i;
   for (i=0; i<n; i++, x++) {
    *((GLint*)rgba[i]) = RGB2BGR24(__svga_getpixel24( x, y));
   }
}

void __write_rgba_pixels24( const GLcontext *ctx,
                            GLuint n, const GLint x[], const GLint y[],
                            const GLubyte rgba[][4], const GLubyte mask[] )
{
   int i;
   for (i=0; i<n; i++) {
      if (mask[i]) {
         __svga_drawpixel24( x[i], y[i], rgba[i][RCOMP],
	                                 rgba[i][GCOMP],
				         rgba[i][BCOMP]);
      }
   }
}

void __write_mono_rgba_pixels24( const GLcontext *ctx,
                                 GLuint n,
                                 const GLint x[], const GLint y[],
                                 const GLubyte mask[] )
{
   int i;
   /* use current rgb color */
   for (i=0; i<n; i++) {
      if (mask[i]) {
         __svga_drawpixel24( x[i], y[i], SVGAMesa->red,
                                         SVGAMesa->green,
				         SVGAMesa->blue);
      }
   }
}

void __read_rgba_pixels24( const GLcontext *ctx,
                           GLuint n, const GLint x[], const GLint y[],
                           GLubyte rgba[][4], const GLubyte mask[] )
{
   int i;
   for (i=0; i<n; i++,x++) {
    *((GLint*)rgba[i]) = RGB2BGR24(__svga_getpixel24( x[i], y[i]));    
   }
}
