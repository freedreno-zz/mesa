
#ifndef SVGA_MESA_16_H
#define SVGA_MESA_16_H

extern void __set_color16( GLcontext *ctx, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha );
extern void __clear_color16( GLcontext *ctx, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha );
extern GLbitfield __clear16( GLcontext *ctx, GLbitfield mask, GLboolean all, GLint x, GLint y, GLint width, GLint height );
extern void __write_rgba_span16( const GLcontext *ctx, GLuint n, GLint x, GLint y, const GLubyte rgba[][4], const GLubyte mask[] );
extern void __write_mono_rgba_span16( const GLcontext *ctx, GLuint n, GLint x, GLint y, const GLubyte mask[]);
extern void __read_rgba_span16( const GLcontext *ctx, GLuint n, GLint x, GLint y, GLubyte rgba[][4] );
extern void __write_rgba_pixels16( const GLcontext *ctx, GLuint n, const GLint x[], const GLint y[], const GLubyte rgba[][4], const GLubyte mask[] );
extern void __write_mono_rgba_pixels16( const GLcontext *ctx, GLuint n, const GLint x[], const GLint y[], const GLubyte mask[] );
extern void __read_rgba_pixels16( const GLcontext *ctx, GLuint n, const GLint x[], const GLint y[], GLubyte rgba[][4], const GLubyte mask[] );

#endif /* SVGA_MESA_16_H */

