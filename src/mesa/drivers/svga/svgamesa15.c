
#include "svgapix.h"

GLshort * shortBuffer;

int __svga_drawpixel15(int x, int y, unsigned long c)
{
    unsigned long offset;
    
    shortBuffer=(void *)SVGABuffer.BackBuffer;
    y = SVGAInfo->height-y-1;
    offset = y * SVGAInfo->width + x;
    shortBuffer[offset]=c;
    return 0;
}

unsigned long __svga_getpixel15(int x, int y)
{
    unsigned long offset;

    shortBuffer=(void *)SVGABuffer.BackBuffer;
    y = SVGAInfo->height-y-1;
    offset = y * SVGAInfo->width + x;
    return shortBuffer[offset];
}

void __set_color15( GLcontext *ctx,
                    GLubyte red, GLubyte green,
                    GLubyte blue, GLubyte alpha )
{
   SVGAMesa->hicolor=(red>>3)<<10 | (green>>3)<<5 | (blue>>3); 
/*   SVGAMesa->hicolor=(red)<<10 | (green)<<5 | (blue); */
}   

void __clear_color15( GLcontext *ctx,
                      GLubyte red, GLubyte green,
                      GLubyte blue, GLubyte alpha )
{
   SVGAMesa->clear_hicolor=(red>>3)<<10 | (green>>3)<<5 | (blue>>3);  
/*   SVGAMesa->clear_hicolor=(red)<<10 | (green)<<5 | (blue);*/
}   

GLbitfield __clear15( GLcontext *ctx, GLbitfield mask, GLboolean all,
                      GLint x, GLint y, GLint width, GLint height )
{
   int i,j;
   
   if (mask & GL_COLOR_BUFFER_BIT) {
    shortBuffer=(void *)SVGABuffer.BackBuffer;
    if (all) {
     for (i=0;i<SVGABuffer.BufferSize / 2;i++) shortBuffer[i]=SVGAMesa->clear_hicolor;
    } else {
    for (i=x;i<width;i++)    
     for (j=y;j<height;j++)    
      __svga_drawpixel15(i,j,SVGAMesa->clear_hicolor);
    }	
   }    
   return mask & (~GL_COLOR_BUFFER_BIT);
}

void __write_rgba_span15( const GLcontext *ctx, GLuint n, GLint x, GLint y,
                          const GLubyte rgba[][4], const GLubyte mask[] )
{
   int i;
   if (mask) {
      /* draw some pixels */
      for (i=0; i<n; i++, x++) {
         if (mask[i]) {
         __svga_drawpixel15( x, y, (rgba[i][RCOMP]>>3)<<10 | \
			           (rgba[i][GCOMP]>>3)<<5 |  \
			           (rgba[i][BCOMP]>>3));
         }
      }
   }
   else {
      /* draw all pixels */
      for (i=0; i<n; i++, x++) {
         __svga_drawpixel15( x, y, (rgba[i][RCOMP]>>3)<<10 | \
			           (rgba[i][GCOMP]>>3)<<5  | \
			           (rgba[i][BCOMP]>>3));
      }
   }
}

void __write_mono_rgba_span15( const GLcontext *ctx,
                               GLuint n, GLint x, GLint y,
                               const GLubyte mask[])
{
   int i;
   for (i=0; i<n; i++, x++) {
      if (mask[i]) {
         __svga_drawpixel15( x, y, SVGAMesa->hicolor);
      }
   }
}

void __read_rgba_span15( const GLcontext *ctx, GLuint n, GLint x, GLint y,
                         GLubyte rgba[][4] )
{
   int i,pix;
   for (i=0; i<n; i++, x++) {
    pix = __svga_getpixel15( x, y);
    rgba[i][RCOMP] = ((pix>>10)<<3) & 0xff;
    rgba[i][GCOMP] = ((pix>> 5)<<3) & 0xff;
    rgba[i][BCOMP] = ((pix    )<<3) & 0xff;
   }
}

void __write_rgba_pixels15( const GLcontext *ctx,
                            GLuint n, const GLint x[], const GLint y[],
                            const GLubyte rgba[][4], const GLubyte mask[] )
{
   int i;
   for (i=0; i<n; i++) {
      if (mask[i]) {
         __svga_drawpixel15( x[i], y[i], (rgba[i][RCOMP]>>3)<<10 | \
			                 (rgba[i][GCOMP]>>3)<<5  | \
			                 (rgba[i][BCOMP]>>3));
      }
   }
}


void __write_mono_rgba_pixels15( const GLcontext *ctx,
                                 GLuint n,
                                 const GLint x[], const GLint y[],
                                 const GLubyte mask[] )
{
   int i;
   /* use current rgb color */
   for (i=0; i<n; i++) {
      if (mask[i]) {
         __svga_drawpixel15( x[i], y[i], SVGAMesa->hicolor );
      }
   }
}

void __read_rgba_pixels15( const GLcontext *ctx,
                           GLuint n, const GLint x[], const GLint y[],
                           GLubyte rgba[][4], const GLubyte mask[] )
{
   int i,pix;
   for (i=0; i<n; i++,x++) {
    pix = __svga_getpixel15( x[i], y[i] );
    rgba[i][RCOMP] = ((pix>>10)<<3) & 0xff;
    rgba[i][GCOMP] = ((pix>> 5)<<3) & 0xff;
    rgba[i][BCOMP] = ((pix    )<<3) & 0xff;
   }
}
