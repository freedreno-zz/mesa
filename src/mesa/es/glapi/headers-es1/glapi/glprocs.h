/* DO NOT EDIT - This file generated automatically by gl_procs.py (from Mesa) script */

/*
 * Copyright (C) 1999-2001  Brian Paul   All Rights Reserved.
 * (C) Copyright IBM Corporation 2004, 2006
 * All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL, IBM,
 * AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


/* This file is only included by glapi.c and is used for
 * the GetProcAddress() function
 */

typedef struct {
    GLint Name_offset;
#if defined(NEED_FUNCTION_POINTER) || defined(GLX_INDIRECT_RENDERING)
    _glapi_proc Address;
#endif
    GLuint Offset;
} glprocs_table_t;

#if   !defined(NEED_FUNCTION_POINTER) && !defined(GLX_INDIRECT_RENDERING)
#  define NAME_FUNC_OFFSET(n,f1,f2,f3,o) { n , o }
#elif  defined(NEED_FUNCTION_POINTER) && !defined(GLX_INDIRECT_RENDERING)
#  define NAME_FUNC_OFFSET(n,f1,f2,f3,o) { n , (_glapi_proc) f1 , o }
#elif  defined(NEED_FUNCTION_POINTER) &&  defined(GLX_INDIRECT_RENDERING)
#  define NAME_FUNC_OFFSET(n,f1,f2,f3,o) { n , (_glapi_proc) f2 , o }
#elif !defined(NEED_FUNCTION_POINTER) &&  defined(GLX_INDIRECT_RENDERING)
#  define NAME_FUNC_OFFSET(n,f1,f2,f3,o) { n , (_glapi_proc) f3 , o }
#endif



/* OpenGL ES specific prototypes */
/* category GL_OES_texture_cube_map */
GLAPI void GLAPIENTRY glTexGenfOES(GLenum coord, GLenum pname, GLfloat param);
/* category GL_OES_texture_cube_map */
GLAPI void GLAPIENTRY glTexGenfvOES(GLenum coord, GLenum pname, const GLfloat * params);
/* category GL_OES_texture_cube_map */
GLAPI void GLAPIENTRY glTexGeniOES(GLenum coord, GLenum pname, GLint param);
/* category GL_OES_texture_cube_map */
GLAPI void GLAPIENTRY glTexGenivOES(GLenum coord, GLenum pname, const GLint * params);
/* category GL_OES_texture_cube_map */
GLAPI void GLAPIENTRY glGetTexGenfvOES(GLenum coord, GLenum pname, GLfloat * params);
/* category GL_OES_texture_cube_map */
GLAPI void GLAPIENTRY glGetTexGenivOES(GLenum coord, GLenum pname, GLint * params);
/* category GL_OES_blend_subtract */
GLAPI void GLAPIENTRY glBlendEquationOES(GLenum mode);
/* category GL_OES_blend_equation_separate */
GLAPI void GLAPIENTRY glBlendEquationSeparateOES(GLenum modeRGB, GLenum modeA);
/* category GL_OES_blend_func_separate */
GLAPI void GLAPIENTRY glBlendFuncSeparateOES(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
/* category GL_OES_draw_texture */
GLAPI void GLAPIENTRY glDrawTexfOES(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
/* category GL_OES_draw_texture */
GLAPI void GLAPIENTRY glDrawTexfvOES(const GLfloat * coords);
/* category GL_OES_draw_texture */
GLAPI void GLAPIENTRY glDrawTexiOES(GLint x, GLint y, GLint z, GLint width, GLint height);
/* category GL_OES_draw_texture */
GLAPI void GLAPIENTRY glDrawTexivOES(const GLint * coords);
/* category GL_OES_draw_texture */
GLAPI void GLAPIENTRY glDrawTexsOES(GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);
/* category GL_OES_draw_texture */
GLAPI void GLAPIENTRY glDrawTexsvOES(const GLshort * coords);
/* category GL_OES_draw_texture */
GLAPI void GLAPIENTRY glDrawTexxOES(GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);
/* category GL_OES_draw_texture */
GLAPI void GLAPIENTRY glDrawTexxvOES(const GLfixed * coords);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glBindFramebufferOES(GLenum target, GLuint framebuffer);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glBindRenderbufferOES(GLenum target, GLuint renderbuffer);
/* category GL_OES_framebuffer_object */
GLAPI GLenum GLAPIENTRY glCheckFramebufferStatusOES(GLenum target);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glDeleteFramebuffersOES(GLsizei n, const GLuint * framebuffers);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glDeleteRenderbuffersOES(GLsizei n, const GLuint * renderbuffers);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glFramebufferRenderbufferOES(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glFramebufferTexture2DOES(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glGenFramebuffersOES(GLsizei n, GLuint * framebuffers);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glGenRenderbuffersOES(GLsizei n, GLuint * renderbuffers);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glGenerateMipmapOES(GLenum target);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glGetFramebufferAttachmentParameterivOES(GLenum target, GLenum attachment, GLenum pname, GLint * params);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glGetRenderbufferParameterivOES(GLenum target, GLenum pname, GLint * params);
/* category GL_OES_framebuffer_object */
GLAPI GLboolean GLAPIENTRY glIsFramebufferOES(GLuint framebuffer);
/* category GL_OES_framebuffer_object */
GLAPI GLboolean GLAPIENTRY glIsRenderbufferOES(GLuint renderbuffer);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glRenderbufferStorageOES(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
/* category GL_OES_point_size_array */
GLAPI void GLAPIENTRY glPointSizePointerOES(GLenum type, GLsizei stride, const GLvoid * pointer);
/* category GL_OES_query_matrix */
GLAPI GLbitfield GLAPIENTRY glQueryMatrixxOES(GLfixed * mantissa, GLint * exponent);
/* category GL_OES_texture_cube_map */
GLAPI void GLAPIENTRY glGetTexGenxvOES(GLenum coord, GLenum pname, GLfixed * params);
/* category GL_OES_texture_cube_map */
GLAPI void GLAPIENTRY glTexGenxOES(GLenum coord, GLenum pname, GLint param);
/* category GL_OES_texture_cube_map */
GLAPI void GLAPIENTRY glTexGenxvOES(GLenum coord, GLenum pname, const GLfixed * params);
/* category GL_OES_EGL_image */
GLAPI void GLAPIENTRY glEGLImageTargetRenderbufferStorageOES(GLenum target, GLeglImageOES image);
/* category GL_OES_EGL_image */
GLAPI void GLAPIENTRY glEGLImageTargetTexture2DOES(GLenum target, GLeglImageOES image);
/* category GL_OES_mapbuffer */
GLAPI void GLAPIENTRY glGetBufferPointervOES(GLenum target, GLenum pname, GLvoid ** params);
/* category GL_OES_mapbuffer */
GLAPI GLvoid * GLAPIENTRY glMapBufferOES(GLenum target, GLenum access);
/* category GL_OES_mapbuffer */
GLAPI GLboolean GLAPIENTRY glUnmapBufferOES(GLenum target);
/* category es1.0 */
GLAPI void GLAPIENTRY glAlphaFuncx(GLenum func, GLclampx ref);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glAlphaFuncxOES(GLenum func, GLclampx ref);
/* category es1.0 */
GLAPI void GLAPIENTRY glClearColorx(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glClearColorxOES(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);
/* category es1.0 */
GLAPI void GLAPIENTRY glClearDepthf(GLclampf depth);
/* category GL_OES_single_precision */
GLAPI void GLAPIENTRY glClearDepthfOES(GLclampf depth);
/* category es1.0 */
GLAPI void GLAPIENTRY glClearDepthx(GLclampx depth);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glClearDepthxOES(GLclampx depth);
/* category es1.0 */
GLAPI void GLAPIENTRY glColor4x(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glColor4xOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
/* category es1.0 */
GLAPI void GLAPIENTRY glDepthRangef(GLclampf zNear, GLclampf zFar);
/* category GL_OES_single_precision */
GLAPI void GLAPIENTRY glDepthRangefOES(GLclampf zNear, GLclampf zFar);
/* category es1.0 */
GLAPI void GLAPIENTRY glDepthRangex(GLclampx zNear, GLclampx zFar);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glDepthRangexOES(GLclampx zNear, GLclampx zFar);
/* category es1.0 */
GLAPI void GLAPIENTRY glFogx(GLenum pname, GLfixed param);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glFogxOES(GLenum pname, GLfixed param);
/* category es1.0 */
GLAPI void GLAPIENTRY glFogxv(GLenum pname, const GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glFogxvOES(GLenum pname, const GLfixed * params);
/* category es1.0 */
GLAPI void GLAPIENTRY glFrustumf(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
/* category GL_OES_single_precision */
GLAPI void GLAPIENTRY glFrustumfOES(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
/* category es1.0 */
GLAPI void GLAPIENTRY glFrustumx(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glFrustumxOES(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
/* category es1.0 */
GLAPI void GLAPIENTRY glLightModelx(GLenum pname, GLfixed param);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glLightModelxOES(GLenum pname, GLfixed param);
/* category es1.0 */
GLAPI void GLAPIENTRY glLightModelxv(GLenum pname, const GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glLightModelxvOES(GLenum pname, const GLfixed * params);
/* category es1.0 */
GLAPI void GLAPIENTRY glLightx(GLenum light, GLenum pname, GLfixed param);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glLightxOES(GLenum light, GLenum pname, GLfixed param);
/* category es1.0 */
GLAPI void GLAPIENTRY glLightxv(GLenum light, GLenum pname, const GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glLightxvOES(GLenum light, GLenum pname, const GLfixed * params);
/* category es1.0 */
GLAPI void GLAPIENTRY glLineWidthx(GLfixed width);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glLineWidthxOES(GLfixed width);
/* category es1.0 */
GLAPI void GLAPIENTRY glLoadMatrixx(const GLfixed * m);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glLoadMatrixxOES(const GLfixed * m);
/* category es1.0 */
GLAPI void GLAPIENTRY glMaterialx(GLenum face, GLenum pname, GLfixed param);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glMaterialxOES(GLenum face, GLenum pname, GLfixed param);
/* category es1.0 */
GLAPI void GLAPIENTRY glMaterialxv(GLenum face, GLenum pname, const GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glMaterialxvOES(GLenum face, GLenum pname, const GLfixed * params);
/* category es1.0 */
GLAPI void GLAPIENTRY glMultMatrixx(const GLfixed * m);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glMultMatrixxOES(const GLfixed * m);
/* category es1.0 */
GLAPI void GLAPIENTRY glMultiTexCoord4x(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glMultiTexCoord4xOES(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
/* category es1.0 */
GLAPI void GLAPIENTRY glNormal3x(GLfixed nx, GLfixed ny, GLfixed nz);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glNormal3xOES(GLfixed nx, GLfixed ny, GLfixed nz);
/* category es1.0 */
GLAPI void GLAPIENTRY glOrthof(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
/* category GL_OES_single_precision */
GLAPI void GLAPIENTRY glOrthofOES(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
/* category es1.0 */
GLAPI void GLAPIENTRY glOrthox(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glOrthoxOES(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
/* category es1.0 */
GLAPI void GLAPIENTRY glPointSizex(GLfixed size);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glPointSizexOES(GLfixed size);
/* category es1.0 */
GLAPI void GLAPIENTRY glPolygonOffsetx(GLfixed factor, GLfixed units);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glPolygonOffsetxOES(GLfixed factor, GLfixed units);
/* category es1.0 */
GLAPI void GLAPIENTRY glRotatex(GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glRotatexOES(GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
/* category es1.0 */
GLAPI void GLAPIENTRY glSampleCoveragex(GLclampx value, GLboolean invert);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glSampleCoveragexOES(GLclampx value, GLboolean invert);
/* category es1.0 */
GLAPI void GLAPIENTRY glScalex(GLfixed x, GLfixed y, GLfixed z);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glScalexOES(GLfixed x, GLfixed y, GLfixed z);
/* category es1.0 */
GLAPI void GLAPIENTRY glTexEnvx(GLenum target, GLenum pname, GLfixed param);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glTexEnvxOES(GLenum target, GLenum pname, GLfixed param);
/* category es1.0 */
GLAPI void GLAPIENTRY glTexEnvxv(GLenum target, GLenum pname, const GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glTexEnvxvOES(GLenum target, GLenum pname, const GLfixed * params);
/* category es1.0 */
GLAPI void GLAPIENTRY glTexParameterx(GLenum target, GLenum pname, GLfixed param);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glTexParameterxOES(GLenum target, GLenum pname, GLfixed param);
/* category es1.0 */
GLAPI void GLAPIENTRY glTranslatex(GLfixed x, GLfixed y, GLfixed z);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glTranslatexOES(GLfixed x, GLfixed y, GLfixed z);
/* category es1.1 */
GLAPI void GLAPIENTRY glClipPlanef(GLenum plane, const GLfloat * equation);
/* category GL_OES_single_precision */
GLAPI void GLAPIENTRY glClipPlanefOES(GLenum plane, const GLfloat * equation);
/* category es1.1 */
GLAPI void GLAPIENTRY glClipPlanex(GLenum plane, const GLfixed * equation);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glClipPlanexOES(GLenum plane, const GLfixed * equation);
/* category es1.1 */
GLAPI void GLAPIENTRY glGetClipPlanef(GLenum plane, GLfloat * equation);
/* category GL_OES_single_precision */
GLAPI void GLAPIENTRY glGetClipPlanefOES(GLenum plane, GLfloat * equation);
/* category es1.1 */
GLAPI void GLAPIENTRY glGetClipPlanex(GLenum plane, GLfixed * equation);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glGetClipPlanexOES(GLenum plane, GLfixed * equation);
/* category es1.1 */
GLAPI void GLAPIENTRY glGetFixedv(GLenum pname, GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glGetFixedvOES(GLenum pname, GLfixed * params);
/* category es1.1 */
GLAPI void GLAPIENTRY glGetLightxv(GLenum light, GLenum pname, GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glGetLightxvOES(GLenum light, GLenum pname, GLfixed * params);
/* category es1.1 */
GLAPI void GLAPIENTRY glGetMaterialxv(GLenum face, GLenum pname, GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glGetMaterialxvOES(GLenum face, GLenum pname, GLfixed * params);
/* category es1.1 */
GLAPI void GLAPIENTRY glGetTexEnvxv(GLenum target, GLenum pname, GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glGetTexEnvxvOES(GLenum target, GLenum pname, GLfixed * params);
/* category es1.1 */
GLAPI void GLAPIENTRY glGetTexParameterxv(GLenum target, GLenum pname, GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glGetTexParameterxvOES(GLenum target, GLenum pname, GLfixed * params);
/* category es1.1 */
GLAPI void GLAPIENTRY glPointParameterx(GLenum pname, GLfixed param);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glPointParameterxOES(GLenum pname, GLfixed param);
/* category es1.1 */
GLAPI void GLAPIENTRY glPointParameterxv(GLenum pname, const GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glPointParameterxvOES(GLenum pname, const GLfixed * params);
/* category es1.1 */
GLAPI void GLAPIENTRY glTexParameterxv(GLenum target, GLenum pname, const GLfixed * params);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glTexParameterxvOES(GLenum target, GLenum pname, const GLfixed * params);

static const char gl_string_table[] =
    "glNewList\0"
    "glEndList\0"
    "glCallList\0"
    "glCallLists\0"
    "glDeleteLists\0"
    "glGenLists\0"
    "glListBase\0"
    "glBegin\0"
    "glBitmap\0"
    "glColor3b\0"
    "glColor3bv\0"
    "glColor3d\0"
    "glColor3dv\0"
    "glColor3f\0"
    "glColor3fv\0"
    "glColor3i\0"
    "glColor3iv\0"
    "glColor3s\0"
    "glColor3sv\0"
    "glColor3ub\0"
    "glColor3ubv\0"
    "glColor3ui\0"
    "glColor3uiv\0"
    "glColor3us\0"
    "glColor3usv\0"
    "glColor4b\0"
    "glColor4bv\0"
    "glColor4d\0"
    "glColor4dv\0"
    "glColor4f\0"
    "glColor4fv\0"
    "glColor4i\0"
    "glColor4iv\0"
    "glColor4s\0"
    "glColor4sv\0"
    "glColor4ub\0"
    "glColor4ubv\0"
    "glColor4ui\0"
    "glColor4uiv\0"
    "glColor4us\0"
    "glColor4usv\0"
    "glEdgeFlag\0"
    "glEdgeFlagv\0"
    "glEnd\0"
    "glIndexd\0"
    "glIndexdv\0"
    "glIndexf\0"
    "glIndexfv\0"
    "glIndexi\0"
    "glIndexiv\0"
    "glIndexs\0"
    "glIndexsv\0"
    "glNormal3b\0"
    "glNormal3bv\0"
    "glNormal3d\0"
    "glNormal3dv\0"
    "glNormal3f\0"
    "glNormal3fv\0"
    "glNormal3i\0"
    "glNormal3iv\0"
    "glNormal3s\0"
    "glNormal3sv\0"
    "glRasterPos2d\0"
    "glRasterPos2dv\0"
    "glRasterPos2f\0"
    "glRasterPos2fv\0"
    "glRasterPos2i\0"
    "glRasterPos2iv\0"
    "glRasterPos2s\0"
    "glRasterPos2sv\0"
    "glRasterPos3d\0"
    "glRasterPos3dv\0"
    "glRasterPos3f\0"
    "glRasterPos3fv\0"
    "glRasterPos3i\0"
    "glRasterPos3iv\0"
    "glRasterPos3s\0"
    "glRasterPos3sv\0"
    "glRasterPos4d\0"
    "glRasterPos4dv\0"
    "glRasterPos4f\0"
    "glRasterPos4fv\0"
    "glRasterPos4i\0"
    "glRasterPos4iv\0"
    "glRasterPos4s\0"
    "glRasterPos4sv\0"
    "glRectd\0"
    "glRectdv\0"
    "glRectf\0"
    "glRectfv\0"
    "glRecti\0"
    "glRectiv\0"
    "glRects\0"
    "glRectsv\0"
    "glTexCoord1d\0"
    "glTexCoord1dv\0"
    "glTexCoord1f\0"
    "glTexCoord1fv\0"
    "glTexCoord1i\0"
    "glTexCoord1iv\0"
    "glTexCoord1s\0"
    "glTexCoord1sv\0"
    "glTexCoord2d\0"
    "glTexCoord2dv\0"
    "glTexCoord2f\0"
    "glTexCoord2fv\0"
    "glTexCoord2i\0"
    "glTexCoord2iv\0"
    "glTexCoord2s\0"
    "glTexCoord2sv\0"
    "glTexCoord3d\0"
    "glTexCoord3dv\0"
    "glTexCoord3f\0"
    "glTexCoord3fv\0"
    "glTexCoord3i\0"
    "glTexCoord3iv\0"
    "glTexCoord3s\0"
    "glTexCoord3sv\0"
    "glTexCoord4d\0"
    "glTexCoord4dv\0"
    "glTexCoord4f\0"
    "glTexCoord4fv\0"
    "glTexCoord4i\0"
    "glTexCoord4iv\0"
    "glTexCoord4s\0"
    "glTexCoord4sv\0"
    "glVertex2d\0"
    "glVertex2dv\0"
    "glVertex2f\0"
    "glVertex2fv\0"
    "glVertex2i\0"
    "glVertex2iv\0"
    "glVertex2s\0"
    "glVertex2sv\0"
    "glVertex3d\0"
    "glVertex3dv\0"
    "glVertex3f\0"
    "glVertex3fv\0"
    "glVertex3i\0"
    "glVertex3iv\0"
    "glVertex3s\0"
    "glVertex3sv\0"
    "glVertex4d\0"
    "glVertex4dv\0"
    "glVertex4f\0"
    "glVertex4fv\0"
    "glVertex4i\0"
    "glVertex4iv\0"
    "glVertex4s\0"
    "glVertex4sv\0"
    "glClipPlane\0"
    "glColorMaterial\0"
    "glCullFace\0"
    "glFogf\0"
    "glFogfv\0"
    "glFogi\0"
    "glFogiv\0"
    "glFrontFace\0"
    "glHint\0"
    "glLightf\0"
    "glLightfv\0"
    "glLighti\0"
    "glLightiv\0"
    "glLightModelf\0"
    "glLightModelfv\0"
    "glLightModeli\0"
    "glLightModeliv\0"
    "glLineStipple\0"
    "glLineWidth\0"
    "glMaterialf\0"
    "glMaterialfv\0"
    "glMateriali\0"
    "glMaterialiv\0"
    "glPointSize\0"
    "glPolygonMode\0"
    "glPolygonStipple\0"
    "glScissor\0"
    "glShadeModel\0"
    "glTexParameterf\0"
    "glTexParameterfv\0"
    "glTexParameteri\0"
    "glTexParameteriv\0"
    "glTexImage1D\0"
    "glTexImage2D\0"
    "glTexEnvf\0"
    "glTexEnvfv\0"
    "glTexEnvi\0"
    "glTexEnviv\0"
    "glTexGend\0"
    "glTexGendv\0"
    "glTexGenfOES\0"
    "glTexGenfvOES\0"
    "glTexGeniOES\0"
    "glTexGenivOES\0"
    "glFeedbackBuffer\0"
    "glSelectBuffer\0"
    "glRenderMode\0"
    "glInitNames\0"
    "glLoadName\0"
    "glPassThrough\0"
    "glPopName\0"
    "glPushName\0"
    "glDrawBuffer\0"
    "glClear\0"
    "glClearAccum\0"
    "glClearIndex\0"
    "glClearColor\0"
    "glClearStencil\0"
    "glClearDepth\0"
    "glStencilMask\0"
    "glColorMask\0"
    "glDepthMask\0"
    "glIndexMask\0"
    "glAccum\0"
    "glDisable\0"
    "glEnable\0"
    "glFinish\0"
    "glFlush\0"
    "glPopAttrib\0"
    "glPushAttrib\0"
    "glMap1d\0"
    "glMap1f\0"
    "glMap2d\0"
    "glMap2f\0"
    "glMapGrid1d\0"
    "glMapGrid1f\0"
    "glMapGrid2d\0"
    "glMapGrid2f\0"
    "glEvalCoord1d\0"
    "glEvalCoord1dv\0"
    "glEvalCoord1f\0"
    "glEvalCoord1fv\0"
    "glEvalCoord2d\0"
    "glEvalCoord2dv\0"
    "glEvalCoord2f\0"
    "glEvalCoord2fv\0"
    "glEvalMesh1\0"
    "glEvalPoint1\0"
    "glEvalMesh2\0"
    "glEvalPoint2\0"
    "glAlphaFunc\0"
    "glBlendFunc\0"
    "glLogicOp\0"
    "glStencilFunc\0"
    "glStencilOp\0"
    "glDepthFunc\0"
    "glPixelZoom\0"
    "glPixelTransferf\0"
    "glPixelTransferi\0"
    "glPixelStoref\0"
    "glPixelStorei\0"
    "glPixelMapfv\0"
    "glPixelMapuiv\0"
    "glPixelMapusv\0"
    "glReadBuffer\0"
    "glCopyPixels\0"
    "glReadPixels\0"
    "glDrawPixels\0"
    "glGetBooleanv\0"
    "glGetClipPlane\0"
    "glGetDoublev\0"
    "glGetError\0"
    "glGetFloatv\0"
    "glGetIntegerv\0"
    "glGetLightfv\0"
    "glGetLightiv\0"
    "glGetMapdv\0"
    "glGetMapfv\0"
    "glGetMapiv\0"
    "glGetMaterialfv\0"
    "glGetMaterialiv\0"
    "glGetPixelMapfv\0"
    "glGetPixelMapuiv\0"
    "glGetPixelMapusv\0"
    "glGetPolygonStipple\0"
    "glGetString\0"
    "glGetTexEnvfv\0"
    "glGetTexEnviv\0"
    "glGetTexGendv\0"
    "glGetTexGenfvOES\0"
    "glGetTexGenivOES\0"
    "glGetTexImage\0"
    "glGetTexParameterfv\0"
    "glGetTexParameteriv\0"
    "glGetTexLevelParameterfv\0"
    "glGetTexLevelParameteriv\0"
    "glIsEnabled\0"
    "glIsList\0"
    "glDepthRange\0"
    "glFrustum\0"
    "glLoadIdentity\0"
    "glLoadMatrixf\0"
    "glLoadMatrixd\0"
    "glMatrixMode\0"
    "glMultMatrixf\0"
    "glMultMatrixd\0"
    "glOrtho\0"
    "glPopMatrix\0"
    "glPushMatrix\0"
    "glRotated\0"
    "glRotatef\0"
    "glScaled\0"
    "glScalef\0"
    "glTranslated\0"
    "glTranslatef\0"
    "glViewport\0"
    "glArrayElement\0"
    "glBindTexture\0"
    "glColorPointer\0"
    "glDisableClientState\0"
    "glDrawArrays\0"
    "glDrawElements\0"
    "glEdgeFlagPointer\0"
    "glEnableClientState\0"
    "glIndexPointer\0"
    "glIndexub\0"
    "glIndexubv\0"
    "glInterleavedArrays\0"
    "glNormalPointer\0"
    "glPolygonOffset\0"
    "glTexCoordPointer\0"
    "glVertexPointer\0"
    "glAreTexturesResident\0"
    "glCopyTexImage1D\0"
    "glCopyTexImage2D\0"
    "glCopyTexSubImage1D\0"
    "glCopyTexSubImage2D\0"
    "glDeleteTextures\0"
    "glGenTextures\0"
    "glGetPointerv\0"
    "glIsTexture\0"
    "glPrioritizeTextures\0"
    "glTexSubImage1D\0"
    "glTexSubImage2D\0"
    "glPopClientAttrib\0"
    "glPushClientAttrib\0"
    "glBlendColor\0"
    "glBlendEquationOES\0"
    "glDrawRangeElements\0"
    "glColorTable\0"
    "glColorTableParameterfv\0"
    "glColorTableParameteriv\0"
    "glCopyColorTable\0"
    "glGetColorTable\0"
    "glGetColorTableParameterfv\0"
    "glGetColorTableParameteriv\0"
    "glColorSubTable\0"
    "glCopyColorSubTable\0"
    "glConvolutionFilter1D\0"
    "glConvolutionFilter2D\0"
    "glConvolutionParameterf\0"
    "glConvolutionParameterfv\0"
    "glConvolutionParameteri\0"
    "glConvolutionParameteriv\0"
    "glCopyConvolutionFilter1D\0"
    "glCopyConvolutionFilter2D\0"
    "glGetConvolutionFilter\0"
    "glGetConvolutionParameterfv\0"
    "glGetConvolutionParameteriv\0"
    "glGetSeparableFilter\0"
    "glSeparableFilter2D\0"
    "glGetHistogram\0"
    "glGetHistogramParameterfv\0"
    "glGetHistogramParameteriv\0"
    "glGetMinmax\0"
    "glGetMinmaxParameterfv\0"
    "glGetMinmaxParameteriv\0"
    "glHistogram\0"
    "glMinmax\0"
    "glResetHistogram\0"
    "glResetMinmax\0"
    "glTexImage3D\0"
    "glTexSubImage3D\0"
    "glCopyTexSubImage3D\0"
    "glActiveTexture\0"
    "glClientActiveTexture\0"
    "glMultiTexCoord1dARB\0"
    "glMultiTexCoord1dvARB\0"
    "glMultiTexCoord1fARB\0"
    "glMultiTexCoord1fvARB\0"
    "glMultiTexCoord1iARB\0"
    "glMultiTexCoord1ivARB\0"
    "glMultiTexCoord1sARB\0"
    "glMultiTexCoord1svARB\0"
    "glMultiTexCoord2dARB\0"
    "glMultiTexCoord2dvARB\0"
    "glMultiTexCoord2fARB\0"
    "glMultiTexCoord2fvARB\0"
    "glMultiTexCoord2iARB\0"
    "glMultiTexCoord2ivARB\0"
    "glMultiTexCoord2sARB\0"
    "glMultiTexCoord2svARB\0"
    "glMultiTexCoord3dARB\0"
    "glMultiTexCoord3dvARB\0"
    "glMultiTexCoord3fARB\0"
    "glMultiTexCoord3fvARB\0"
    "glMultiTexCoord3iARB\0"
    "glMultiTexCoord3ivARB\0"
    "glMultiTexCoord3sARB\0"
    "glMultiTexCoord3svARB\0"
    "glMultiTexCoord4dARB\0"
    "glMultiTexCoord4dvARB\0"
    "glMultiTexCoord4f\0"
    "glMultiTexCoord4fvARB\0"
    "glMultiTexCoord4iARB\0"
    "glMultiTexCoord4ivARB\0"
    "glMultiTexCoord4sARB\0"
    "glMultiTexCoord4svARB\0"
    "glBlendEquationSeparateOES\0"
    "glBlendFuncSeparateOES\0"
    "glDrawTexfOES\0"
    "glDrawTexfvOES\0"
    "glDrawTexiOES\0"
    "glDrawTexivOES\0"
    "glDrawTexsOES\0"
    "glDrawTexsvOES\0"
    "glDrawTexxOES\0"
    "glDrawTexxvOES\0"
    "glBindFramebufferOES\0"
    "glBindRenderbufferOES\0"
    "glCheckFramebufferStatusOES\0"
    "glDeleteFramebuffersOES\0"
    "glDeleteRenderbuffersOES\0"
    "glFramebufferRenderbufferOES\0"
    "glFramebufferTexture2DOES\0"
    "glGenFramebuffersOES\0"
    "glGenRenderbuffersOES\0"
    "glGenerateMipmapOES\0"
    "glGetFramebufferAttachmentParameterivOES\0"
    "glGetRenderbufferParameterivOES\0"
    "glIsFramebufferOES\0"
    "glIsRenderbufferOES\0"
    "glRenderbufferStorageOES\0"
    "glPointSizePointerOES\0"
    "glQueryMatrixxOES\0"
    "glGetTexGenxvOES\0"
    "glTexGenxOES\0"
    "glTexGenxvOES\0"
    "glEGLImageTargetRenderbufferStorageOES\0"
    "glEGLImageTargetTexture2DOES\0"
    "glGetBufferPointervOES\0"
    "glMapBufferOES\0"
    "glUnmapBufferOES\0"
    "glBindVertexArrayAPPLE\0"
    "glDeleteVertexArraysAPPLE\0"
    "glGenVertexArraysAPPLE\0"
    "glIsVertexArrayAPPLE\0"
    "glCompressedTexImage2D\0"
    "glCompressedTexSubImage2D\0"
    "glSampleCoverage\0"
    "glBindBuffer\0"
    "glBufferData\0"
    "glBufferSubData\0"
    "glDeleteBuffers\0"
    "glGenBuffers\0"
    "glGetBufferParameteriv\0"
    "glIsBuffer\0"
    "glAlphaFuncx\0"
    "glClearColorx\0"
    "glClearDepthf\0"
    "glClearDepthx\0"
    "glColor4x\0"
    "glDepthRangef\0"
    "glDepthRangex\0"
    "glFogx\0"
    "glFogxv\0"
    "glFrustumf\0"
    "glFrustumx\0"
    "glLightModelx\0"
    "glLightModelxv\0"
    "glLightx\0"
    "glLightxv\0"
    "glLineWidthx\0"
    "glLoadMatrixx\0"
    "glMaterialx\0"
    "glMaterialxv\0"
    "glMultMatrixx\0"
    "glMultiTexCoord4x\0"
    "glNormal3x\0"
    "glOrthof\0"
    "glOrthox\0"
    "glPointSizex\0"
    "glPolygonOffsetx\0"
    "glRotatex\0"
    "glSampleCoveragex\0"
    "glScalex\0"
    "glTexEnvx\0"
    "glTexEnvxv\0"
    "glTexParameterx\0"
    "glTranslatex\0"
    "glClipPlanef\0"
    "glClipPlanex\0"
    "glGetClipPlanef\0"
    "glGetClipPlanex\0"
    "glGetFixedv\0"
    "glGetLightxv\0"
    "glGetMaterialxv\0"
    "glGetTexEnvxv\0"
    "glGetTexParameterxv\0"
    "glPointParameterx\0"
    "glPointParameterxv\0"
    "glTexParameterxv\0"
    "glPointParameterf\0"
    "glPointParameterfv\0"
    "glTexGenf\0"
    "glTexGenfv\0"
    "glTexGeni\0"
    "glTexGeniv\0"
    "glGetTexGenfv\0"
    "glGetTexGeniv\0"
    "glBlendEquation\0"
    "glActiveTextureARB\0"
    "glClientActiveTextureARB\0"
    "glMultiTexCoord4fARB\0"
    "glAlphaFuncxOES\0"
    "glClearColorxOES\0"
    "glClearDepthfOES\0"
    "glClearDepthxOES\0"
    "glColor4xOES\0"
    "glDepthRangefOES\0"
    "glDepthRangexOES\0"
    "glFogxOES\0"
    "glFogxvOES\0"
    "glFrustumfOES\0"
    "glFrustumxOES\0"
    "glLightModelxOES\0"
    "glLightModelxvOES\0"
    "glLightxOES\0"
    "glLightxvOES\0"
    "glLineWidthxOES\0"
    "glLoadMatrixxOES\0"
    "glMaterialxOES\0"
    "glMaterialxvOES\0"
    "glMultMatrixxOES\0"
    "glMultiTexCoord4xOES\0"
    "glNormal3xOES\0"
    "glOrthofOES\0"
    "glOrthoxOES\0"
    "glPointSizexOES\0"
    "glPolygonOffsetxOES\0"
    "glRotatexOES\0"
    "glSampleCoveragexOES\0"
    "glScalexOES\0"
    "glTexEnvxOES\0"
    "glTexEnvxvOES\0"
    "glTexParameterxOES\0"
    "glTranslatexOES\0"
    "glClipPlanefOES\0"
    "glClipPlanexOES\0"
    "glGetClipPlanefOES\0"
    "glGetClipPlanexOES\0"
    "glGetFixedvOES\0"
    "glGetLightxvOES\0"
    "glGetMaterialxvOES\0"
    "glGetTexEnvxvOES\0"
    "glGetTexParameterxvOES\0"
    "glPointParameterxOES\0"
    "glPointParameterxvOES\0"
    "glTexParameterxvOES\0"
    ;


#ifdef USE_MGL_NAMESPACE
#define gl_dispatch_stub_0 mgl_dispatch_stub_0
#define gl_dispatch_stub_1 mgl_dispatch_stub_1
#define gl_dispatch_stub_2 mgl_dispatch_stub_2
#define gl_dispatch_stub_3 mgl_dispatch_stub_3
#define gl_dispatch_stub_4 mgl_dispatch_stub_4
#define gl_dispatch_stub_5 mgl_dispatch_stub_5
#define gl_dispatch_stub_6 mgl_dispatch_stub_6
#define gl_dispatch_stub_7 mgl_dispatch_stub_7
#define gl_dispatch_stub_8 mgl_dispatch_stub_8
#define gl_dispatch_stub_9 mgl_dispatch_stub_9
#define gl_dispatch_stub_10 mgl_dispatch_stub_10
#define gl_dispatch_stub_11 mgl_dispatch_stub_11
#define gl_dispatch_stub_12 mgl_dispatch_stub_12
#define gl_dispatch_stub_13 mgl_dispatch_stub_13
#define gl_dispatch_stub_14 mgl_dispatch_stub_14
#define gl_dispatch_stub_15 mgl_dispatch_stub_15
#define gl_dispatch_stub_16 mgl_dispatch_stub_16
#define gl_dispatch_stub_17 mgl_dispatch_stub_17
#define gl_dispatch_stub_18 mgl_dispatch_stub_18
#define gl_dispatch_stub_19 mgl_dispatch_stub_19
#define gl_dispatch_stub_20 mgl_dispatch_stub_20
#define gl_dispatch_stub_21 mgl_dispatch_stub_21
#define gl_dispatch_stub_22 mgl_dispatch_stub_22
#define gl_dispatch_stub_23 mgl_dispatch_stub_23
#define gl_dispatch_stub_24 mgl_dispatch_stub_24
#define gl_dispatch_stub_25 mgl_dispatch_stub_25
#define gl_dispatch_stub_26 mgl_dispatch_stub_26
#define gl_dispatch_stub_27 mgl_dispatch_stub_27
#define gl_dispatch_stub_28 mgl_dispatch_stub_28
#define gl_dispatch_stub_30 mgl_dispatch_stub_30
#define gl_dispatch_stub_31 mgl_dispatch_stub_31
#define gl_dispatch_stub_32 mgl_dispatch_stub_32
#define gl_dispatch_stub_33 mgl_dispatch_stub_33
#define gl_dispatch_stub_34 mgl_dispatch_stub_34
#define gl_dispatch_stub_36 mgl_dispatch_stub_36
#define gl_dispatch_stub_37 mgl_dispatch_stub_37
#define gl_dispatch_stub_38 mgl_dispatch_stub_38
#define gl_dispatch_stub_39 mgl_dispatch_stub_39
#define gl_dispatch_stub_40 mgl_dispatch_stub_40
#define gl_dispatch_stub_41 mgl_dispatch_stub_41
#define gl_dispatch_stub_42 mgl_dispatch_stub_42
#define gl_dispatch_stub_43 mgl_dispatch_stub_43
#define gl_dispatch_stub_44 mgl_dispatch_stub_44
#define gl_dispatch_stub_45 mgl_dispatch_stub_45
#define gl_dispatch_stub_46 mgl_dispatch_stub_46
#define gl_dispatch_stub_47 mgl_dispatch_stub_47
#define gl_dispatch_stub_48 mgl_dispatch_stub_48
#define gl_dispatch_stub_49 mgl_dispatch_stub_49
#define gl_dispatch_stub_50 mgl_dispatch_stub_50
#define gl_dispatch_stub_51 mgl_dispatch_stub_51
#define gl_dispatch_stub_52 mgl_dispatch_stub_52
#define gl_dispatch_stub_53 mgl_dispatch_stub_53
#define gl_dispatch_stub_54 mgl_dispatch_stub_54
#define gl_dispatch_stub_55 mgl_dispatch_stub_55
#define gl_dispatch_stub_57 mgl_dispatch_stub_57
#define gl_dispatch_stub_58 mgl_dispatch_stub_58
#define gl_dispatch_stub_59 mgl_dispatch_stub_59
#define gl_dispatch_stub_60 mgl_dispatch_stub_60
#define gl_dispatch_stub_61 mgl_dispatch_stub_61
#define gl_dispatch_stub_62 mgl_dispatch_stub_62
#define gl_dispatch_stub_63 mgl_dispatch_stub_63
#define gl_dispatch_stub_64 mgl_dispatch_stub_64
#define gl_dispatch_stub_65 mgl_dispatch_stub_65
#define gl_dispatch_stub_66 mgl_dispatch_stub_66
#define gl_dispatch_stub_67 mgl_dispatch_stub_67
#define gl_dispatch_stub_68 mgl_dispatch_stub_68
#define gl_dispatch_stub_69 mgl_dispatch_stub_69
#define gl_dispatch_stub_70 mgl_dispatch_stub_70
#define gl_dispatch_stub_71 mgl_dispatch_stub_71
#define gl_dispatch_stub_72 mgl_dispatch_stub_72
#define gl_dispatch_stub_73 mgl_dispatch_stub_73
#define gl_dispatch_stub_74 mgl_dispatch_stub_74
#define gl_dispatch_stub_75 mgl_dispatch_stub_75
#define gl_dispatch_stub_76 mgl_dispatch_stub_76
#define gl_dispatch_stub_77 mgl_dispatch_stub_77
#define gl_dispatch_stub_78 mgl_dispatch_stub_78
#define gl_dispatch_stub_79 mgl_dispatch_stub_79
#define gl_dispatch_stub_80 mgl_dispatch_stub_80
#define gl_dispatch_stub_81 mgl_dispatch_stub_81
#define gl_dispatch_stub_82 mgl_dispatch_stub_82
#define gl_dispatch_stub_83 mgl_dispatch_stub_83
#define gl_dispatch_stub_84 mgl_dispatch_stub_84
#define gl_dispatch_stub_85 mgl_dispatch_stub_85
#define gl_dispatch_stub_86 mgl_dispatch_stub_86
#define gl_dispatch_stub_87 mgl_dispatch_stub_87
#define gl_dispatch_stub_88 mgl_dispatch_stub_88
#define gl_dispatch_stub_89 mgl_dispatch_stub_89
#define gl_dispatch_stub_90 mgl_dispatch_stub_90
#define gl_dispatch_stub_91 mgl_dispatch_stub_91
#define gl_dispatch_stub_92 mgl_dispatch_stub_92
#define gl_dispatch_stub_93 mgl_dispatch_stub_93
#define gl_dispatch_stub_94 mgl_dispatch_stub_94
#define gl_dispatch_stub_95 mgl_dispatch_stub_95
#define gl_dispatch_stub_96 mgl_dispatch_stub_96
#define gl_dispatch_stub_97 mgl_dispatch_stub_97
#define gl_dispatch_stub_98 mgl_dispatch_stub_98
#define gl_dispatch_stub_99 mgl_dispatch_stub_99
#define gl_dispatch_stub_100 mgl_dispatch_stub_100
#define gl_dispatch_stub_101 mgl_dispatch_stub_101
#define gl_dispatch_stub_102 mgl_dispatch_stub_102
#define gl_dispatch_stub_103 mgl_dispatch_stub_103
#define gl_dispatch_stub_104 mgl_dispatch_stub_104
#define gl_dispatch_stub_105 mgl_dispatch_stub_105
#define gl_dispatch_stub_106 mgl_dispatch_stub_106
#define gl_dispatch_stub_107 mgl_dispatch_stub_107
#define gl_dispatch_stub_108 mgl_dispatch_stub_108
#define gl_dispatch_stub_109 mgl_dispatch_stub_109
#define gl_dispatch_stub_110 mgl_dispatch_stub_110
#define gl_dispatch_stub_111 mgl_dispatch_stub_111
#define gl_dispatch_stub_112 mgl_dispatch_stub_112
#define gl_dispatch_stub_113 mgl_dispatch_stub_113
#define gl_dispatch_stub_114 mgl_dispatch_stub_114
#define gl_dispatch_stub_115 mgl_dispatch_stub_115
#define gl_dispatch_stub_116 mgl_dispatch_stub_116
#define gl_dispatch_stub_117 mgl_dispatch_stub_117
#define gl_dispatch_stub_118 mgl_dispatch_stub_118
#define gl_dispatch_stub_119 mgl_dispatch_stub_119
#define gl_dispatch_stub_120 mgl_dispatch_stub_120
#define gl_dispatch_stub_121 mgl_dispatch_stub_121
#define gl_dispatch_stub_122 mgl_dispatch_stub_122
#define gl_dispatch_stub_123 mgl_dispatch_stub_123
#define gl_dispatch_stub_124 mgl_dispatch_stub_124
#define gl_dispatch_stub_125 mgl_dispatch_stub_125
#define gl_dispatch_stub_126 mgl_dispatch_stub_126
#define gl_dispatch_stub_127 mgl_dispatch_stub_127
#define gl_dispatch_stub_128 mgl_dispatch_stub_128
#define gl_dispatch_stub_129 mgl_dispatch_stub_129
#define gl_dispatch_stub_130 mgl_dispatch_stub_130
#define gl_dispatch_stub_131 mgl_dispatch_stub_131
#define gl_dispatch_stub_132 mgl_dispatch_stub_132
#define gl_dispatch_stub_133 mgl_dispatch_stub_133
#define gl_dispatch_stub_134 mgl_dispatch_stub_134
#define gl_dispatch_stub_135 mgl_dispatch_stub_135
#define gl_dispatch_stub_136 mgl_dispatch_stub_136
#define gl_dispatch_stub_137 mgl_dispatch_stub_137
#define gl_dispatch_stub_138 mgl_dispatch_stub_138
#define gl_dispatch_stub_139 mgl_dispatch_stub_139
#define gl_dispatch_stub_140 mgl_dispatch_stub_140
#define gl_dispatch_stub_141 mgl_dispatch_stub_141
#define gl_dispatch_stub_142 mgl_dispatch_stub_142
#define gl_dispatch_stub_143 mgl_dispatch_stub_143
#define gl_dispatch_stub_144 mgl_dispatch_stub_144
#define gl_dispatch_stub_145 mgl_dispatch_stub_145
#define gl_dispatch_stub_146 mgl_dispatch_stub_146
#define gl_dispatch_stub_147 mgl_dispatch_stub_147
#define gl_dispatch_stub_148 mgl_dispatch_stub_148
#define gl_dispatch_stub_149 mgl_dispatch_stub_149
#define gl_dispatch_stub_150 mgl_dispatch_stub_150
#define gl_dispatch_stub_151 mgl_dispatch_stub_151
#define gl_dispatch_stub_155 mgl_dispatch_stub_155
#define gl_dispatch_stub_156 mgl_dispatch_stub_156
#define gl_dispatch_stub_161 mgl_dispatch_stub_161
#define gl_dispatch_stub_162 mgl_dispatch_stub_162
#define gl_dispatch_stub_165 mgl_dispatch_stub_165
#define gl_dispatch_stub_166 mgl_dispatch_stub_166
#define gl_dispatch_stub_167 mgl_dispatch_stub_167
#define gl_dispatch_stub_171 mgl_dispatch_stub_171
#define gl_dispatch_stub_172 mgl_dispatch_stub_172
#define gl_dispatch_stub_174 mgl_dispatch_stub_174
#define gl_dispatch_stub_175 mgl_dispatch_stub_175
#define gl_dispatch_stub_182 mgl_dispatch_stub_182
#define gl_dispatch_stub_188 mgl_dispatch_stub_188
#define gl_dispatch_stub_189 mgl_dispatch_stub_189
#define gl_dispatch_stub_194 mgl_dispatch_stub_194
#define gl_dispatch_stub_195 mgl_dispatch_stub_195
#define gl_dispatch_stub_196 mgl_dispatch_stub_196
#define gl_dispatch_stub_197 mgl_dispatch_stub_197
#define gl_dispatch_stub_198 mgl_dispatch_stub_198
#define gl_dispatch_stub_199 mgl_dispatch_stub_199
#define gl_dispatch_stub_200 mgl_dispatch_stub_200
#define gl_dispatch_stub_201 mgl_dispatch_stub_201
#define gl_dispatch_stub_202 mgl_dispatch_stub_202
#define gl_dispatch_stub_204 mgl_dispatch_stub_204
#define gl_dispatch_stub_205 mgl_dispatch_stub_205
#define gl_dispatch_stub_208 mgl_dispatch_stub_208
#define gl_dispatch_stub_212 mgl_dispatch_stub_212
#define gl_dispatch_stub_213 mgl_dispatch_stub_213
#define gl_dispatch_stub_218 mgl_dispatch_stub_218
#define gl_dispatch_stub_219 mgl_dispatch_stub_219
#define gl_dispatch_stub_220 mgl_dispatch_stub_220
#define gl_dispatch_stub_221 mgl_dispatch_stub_221
#define gl_dispatch_stub_222 mgl_dispatch_stub_222
#define gl_dispatch_stub_223 mgl_dispatch_stub_223
#define gl_dispatch_stub_224 mgl_dispatch_stub_224
#define gl_dispatch_stub_225 mgl_dispatch_stub_225
#define gl_dispatch_stub_226 mgl_dispatch_stub_226
#define gl_dispatch_stub_227 mgl_dispatch_stub_227
#define gl_dispatch_stub_228 mgl_dispatch_stub_228
#define gl_dispatch_stub_229 mgl_dispatch_stub_229
#define gl_dispatch_stub_230 mgl_dispatch_stub_230
#define gl_dispatch_stub_231 mgl_dispatch_stub_231
#define gl_dispatch_stub_232 mgl_dispatch_stub_232
#define gl_dispatch_stub_233 mgl_dispatch_stub_233
#define gl_dispatch_stub_234 mgl_dispatch_stub_234
#define gl_dispatch_stub_235 mgl_dispatch_stub_235
#define gl_dispatch_stub_236 mgl_dispatch_stub_236
#define gl_dispatch_stub_237 mgl_dispatch_stub_237
#define gl_dispatch_stub_238 mgl_dispatch_stub_238
#define gl_dispatch_stub_239 mgl_dispatch_stub_239
#define gl_dispatch_stub_246 mgl_dispatch_stub_246
#define gl_dispatch_stub_247 mgl_dispatch_stub_247
#define gl_dispatch_stub_248 mgl_dispatch_stub_248
#define gl_dispatch_stub_249 mgl_dispatch_stub_249
#define gl_dispatch_stub_251 mgl_dispatch_stub_251
#define gl_dispatch_stub_252 mgl_dispatch_stub_252
#define gl_dispatch_stub_253 mgl_dispatch_stub_253
#define gl_dispatch_stub_254 mgl_dispatch_stub_254
#define gl_dispatch_stub_255 mgl_dispatch_stub_255
#define gl_dispatch_stub_257 mgl_dispatch_stub_257
#define gl_dispatch_stub_259 mgl_dispatch_stub_259
#define gl_dispatch_stub_260 mgl_dispatch_stub_260
#define gl_dispatch_stub_265 mgl_dispatch_stub_265
#define gl_dispatch_stub_266 mgl_dispatch_stub_266
#define gl_dispatch_stub_267 mgl_dispatch_stub_267
#define gl_dispatch_stub_268 mgl_dispatch_stub_268
#define gl_dispatch_stub_270 mgl_dispatch_stub_270
#define gl_dispatch_stub_271 mgl_dispatch_stub_271
#define gl_dispatch_stub_272 mgl_dispatch_stub_272
#define gl_dispatch_stub_273 mgl_dispatch_stub_273
#define gl_dispatch_stub_274 mgl_dispatch_stub_274
#define gl_dispatch_stub_278 mgl_dispatch_stub_278
#define gl_dispatch_stub_281 mgl_dispatch_stub_281
#define gl_dispatch_stub_284 mgl_dispatch_stub_284
#define gl_dispatch_stub_285 mgl_dispatch_stub_285
#define gl_dispatch_stub_287 mgl_dispatch_stub_287
#define gl_dispatch_stub_288 mgl_dispatch_stub_288
#define gl_dispatch_stub_289 mgl_dispatch_stub_289
#define gl_dispatch_stub_292 mgl_dispatch_stub_292
#define gl_dispatch_stub_295 mgl_dispatch_stub_295
#define gl_dispatch_stub_296 mgl_dispatch_stub_296
#define gl_dispatch_stub_299 mgl_dispatch_stub_299
#define gl_dispatch_stub_301 mgl_dispatch_stub_301
#define gl_dispatch_stub_303 mgl_dispatch_stub_303
#define gl_dispatch_stub_306 mgl_dispatch_stub_306
#define gl_dispatch_stub_312 mgl_dispatch_stub_312
#define gl_dispatch_stub_314 mgl_dispatch_stub_314
#define gl_dispatch_stub_315 mgl_dispatch_stub_315
#define gl_dispatch_stub_316 mgl_dispatch_stub_316
#define gl_dispatch_stub_317 mgl_dispatch_stub_317
#define gl_dispatch_stub_322 mgl_dispatch_stub_322
#define gl_dispatch_stub_323 mgl_dispatch_stub_323
#define gl_dispatch_stub_325 mgl_dispatch_stub_325
#define gl_dispatch_stub_331 mgl_dispatch_stub_331
#define gl_dispatch_stub_332 mgl_dispatch_stub_332
#define gl_dispatch_stub_334 mgl_dispatch_stub_334
#define gl_dispatch_stub_335 mgl_dispatch_stub_335
#define gl_dispatch_stub_336 mgl_dispatch_stub_336
#define gl_dispatch_stub_338 mgl_dispatch_stub_338
#define gl_dispatch_stub_339 mgl_dispatch_stub_339
#define gl_dispatch_stub_340 mgl_dispatch_stub_340
#define gl_dispatch_stub_341 mgl_dispatch_stub_341
#define gl_dispatch_stub_342 mgl_dispatch_stub_342
#define gl_dispatch_stub_343 mgl_dispatch_stub_343
#define gl_dispatch_stub_344 mgl_dispatch_stub_344
#define gl_dispatch_stub_345 mgl_dispatch_stub_345
#define gl_dispatch_stub_346 mgl_dispatch_stub_346
#define gl_dispatch_stub_347 mgl_dispatch_stub_347
#define gl_dispatch_stub_348 mgl_dispatch_stub_348
#define gl_dispatch_stub_349 mgl_dispatch_stub_349
#define gl_dispatch_stub_350 mgl_dispatch_stub_350
#define gl_dispatch_stub_351 mgl_dispatch_stub_351
#define gl_dispatch_stub_352 mgl_dispatch_stub_352
#define gl_dispatch_stub_353 mgl_dispatch_stub_353
#define gl_dispatch_stub_354 mgl_dispatch_stub_354
#define gl_dispatch_stub_355 mgl_dispatch_stub_355
#define gl_dispatch_stub_356 mgl_dispatch_stub_356
#define gl_dispatch_stub_357 mgl_dispatch_stub_357
#define gl_dispatch_stub_358 mgl_dispatch_stub_358
#define gl_dispatch_stub_359 mgl_dispatch_stub_359
#define gl_dispatch_stub_360 mgl_dispatch_stub_360
#define gl_dispatch_stub_361 mgl_dispatch_stub_361
#define gl_dispatch_stub_362 mgl_dispatch_stub_362
#define gl_dispatch_stub_363 mgl_dispatch_stub_363
#define gl_dispatch_stub_364 mgl_dispatch_stub_364
#define gl_dispatch_stub_365 mgl_dispatch_stub_365
#define gl_dispatch_stub_366 mgl_dispatch_stub_366
#define gl_dispatch_stub_367 mgl_dispatch_stub_367
#define gl_dispatch_stub_368 mgl_dispatch_stub_368
#define gl_dispatch_stub_369 mgl_dispatch_stub_369
#define gl_dispatch_stub_370 mgl_dispatch_stub_370
#define gl_dispatch_stub_371 mgl_dispatch_stub_371
#define gl_dispatch_stub_372 mgl_dispatch_stub_372
#define gl_dispatch_stub_373 mgl_dispatch_stub_373
#define gl_dispatch_stub_376 mgl_dispatch_stub_376
#define gl_dispatch_stub_377 mgl_dispatch_stub_377
#define gl_dispatch_stub_378 mgl_dispatch_stub_378
#define gl_dispatch_stub_379 mgl_dispatch_stub_379
#define gl_dispatch_stub_380 mgl_dispatch_stub_380
#define gl_dispatch_stub_381 mgl_dispatch_stub_381
#define gl_dispatch_stub_382 mgl_dispatch_stub_382
#define gl_dispatch_stub_383 mgl_dispatch_stub_383
#define gl_dispatch_stub_384 mgl_dispatch_stub_384
#define gl_dispatch_stub_385 mgl_dispatch_stub_385
#define gl_dispatch_stub_386 mgl_dispatch_stub_386
#define gl_dispatch_stub_387 mgl_dispatch_stub_387
#define gl_dispatch_stub_388 mgl_dispatch_stub_388
#define gl_dispatch_stub_389 mgl_dispatch_stub_389
#define gl_dispatch_stub_390 mgl_dispatch_stub_390
#define gl_dispatch_stub_391 mgl_dispatch_stub_391
#define gl_dispatch_stub_392 mgl_dispatch_stub_392
#define gl_dispatch_stub_393 mgl_dispatch_stub_393
#define gl_dispatch_stub_394 mgl_dispatch_stub_394
#define gl_dispatch_stub_395 mgl_dispatch_stub_395
#define gl_dispatch_stub_396 mgl_dispatch_stub_396
#define gl_dispatch_stub_397 mgl_dispatch_stub_397
#define gl_dispatch_stub_398 mgl_dispatch_stub_398
#define gl_dispatch_stub_399 mgl_dispatch_stub_399
#define gl_dispatch_stub_400 mgl_dispatch_stub_400
#define gl_dispatch_stub_401 mgl_dispatch_stub_401
#define gl_dispatch_stub_403 mgl_dispatch_stub_403
#define gl_dispatch_stub_404 mgl_dispatch_stub_404
#define gl_dispatch_stub_405 mgl_dispatch_stub_405
#define gl_dispatch_stub_406 mgl_dispatch_stub_406
#define gl_dispatch_stub_407 mgl_dispatch_stub_407
#define gl_dispatch_stub_443 mgl_dispatch_stub_443
#define gl_dispatch_stub_444 mgl_dispatch_stub_444
#define gl_dispatch_stub_445 mgl_dispatch_stub_445
#define gl_dispatch_stub_446 mgl_dispatch_stub_446
#endif /* USE_MGL_NAMESPACE */


#if defined(NEED_FUNCTION_POINTER) || defined(GLX_INDIRECT_RENDERING)
void GLAPIENTRY gl_dispatch_stub_0(GLuint list, GLenum mode);
void GLAPIENTRY gl_dispatch_stub_1(void);
void GLAPIENTRY gl_dispatch_stub_2(GLuint list);
void GLAPIENTRY gl_dispatch_stub_3(GLsizei n, GLenum type, const GLvoid * lists);
void GLAPIENTRY gl_dispatch_stub_4(GLuint list, GLsizei range);
GLuint GLAPIENTRY gl_dispatch_stub_5(GLsizei range);
void GLAPIENTRY gl_dispatch_stub_6(GLuint base);
void GLAPIENTRY gl_dispatch_stub_7(GLenum mode);
void GLAPIENTRY gl_dispatch_stub_8(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap);
void GLAPIENTRY gl_dispatch_stub_9(GLbyte red, GLbyte green, GLbyte blue);
void GLAPIENTRY gl_dispatch_stub_10(const GLbyte * v);
void GLAPIENTRY gl_dispatch_stub_11(GLdouble red, GLdouble green, GLdouble blue);
void GLAPIENTRY gl_dispatch_stub_12(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_13(GLfloat red, GLfloat green, GLfloat blue);
void GLAPIENTRY gl_dispatch_stub_14(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_15(GLint red, GLint green, GLint blue);
void GLAPIENTRY gl_dispatch_stub_16(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_17(GLshort red, GLshort green, GLshort blue);
void GLAPIENTRY gl_dispatch_stub_18(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_19(GLubyte red, GLubyte green, GLubyte blue);
void GLAPIENTRY gl_dispatch_stub_20(const GLubyte * v);
void GLAPIENTRY gl_dispatch_stub_21(GLuint red, GLuint green, GLuint blue);
void GLAPIENTRY gl_dispatch_stub_22(const GLuint * v);
void GLAPIENTRY gl_dispatch_stub_23(GLushort red, GLushort green, GLushort blue);
void GLAPIENTRY gl_dispatch_stub_24(const GLushort * v);
void GLAPIENTRY gl_dispatch_stub_25(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
void GLAPIENTRY gl_dispatch_stub_26(const GLbyte * v);
void GLAPIENTRY gl_dispatch_stub_27(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
void GLAPIENTRY gl_dispatch_stub_28(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_30(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_31(GLint red, GLint green, GLint blue, GLint alpha);
void GLAPIENTRY gl_dispatch_stub_32(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_33(GLshort red, GLshort green, GLshort blue, GLshort alpha);
void GLAPIENTRY gl_dispatch_stub_34(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_36(const GLubyte * v);
void GLAPIENTRY gl_dispatch_stub_37(GLuint red, GLuint green, GLuint blue, GLuint alpha);
void GLAPIENTRY gl_dispatch_stub_38(const GLuint * v);
void GLAPIENTRY gl_dispatch_stub_39(GLushort red, GLushort green, GLushort blue, GLushort alpha);
void GLAPIENTRY gl_dispatch_stub_40(const GLushort * v);
void GLAPIENTRY gl_dispatch_stub_41(GLboolean flag);
void GLAPIENTRY gl_dispatch_stub_42(const GLboolean * flag);
void GLAPIENTRY gl_dispatch_stub_43(void);
void GLAPIENTRY gl_dispatch_stub_44(GLdouble c);
void GLAPIENTRY gl_dispatch_stub_45(const GLdouble * c);
void GLAPIENTRY gl_dispatch_stub_46(GLfloat c);
void GLAPIENTRY gl_dispatch_stub_47(const GLfloat * c);
void GLAPIENTRY gl_dispatch_stub_48(GLint c);
void GLAPIENTRY gl_dispatch_stub_49(const GLint * c);
void GLAPIENTRY gl_dispatch_stub_50(GLshort c);
void GLAPIENTRY gl_dispatch_stub_51(const GLshort * c);
void GLAPIENTRY gl_dispatch_stub_52(GLbyte nx, GLbyte ny, GLbyte nz);
void GLAPIENTRY gl_dispatch_stub_53(const GLbyte * v);
void GLAPIENTRY gl_dispatch_stub_54(GLdouble nx, GLdouble ny, GLdouble nz);
void GLAPIENTRY gl_dispatch_stub_55(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_57(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_58(GLint nx, GLint ny, GLint nz);
void GLAPIENTRY gl_dispatch_stub_59(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_60(GLshort nx, GLshort ny, GLshort nz);
void GLAPIENTRY gl_dispatch_stub_61(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_62(GLdouble x, GLdouble y);
void GLAPIENTRY gl_dispatch_stub_63(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_64(GLfloat x, GLfloat y);
void GLAPIENTRY gl_dispatch_stub_65(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_66(GLint x, GLint y);
void GLAPIENTRY gl_dispatch_stub_67(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_68(GLshort x, GLshort y);
void GLAPIENTRY gl_dispatch_stub_69(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_70(GLdouble x, GLdouble y, GLdouble z);
void GLAPIENTRY gl_dispatch_stub_71(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_72(GLfloat x, GLfloat y, GLfloat z);
void GLAPIENTRY gl_dispatch_stub_73(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_74(GLint x, GLint y, GLint z);
void GLAPIENTRY gl_dispatch_stub_75(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_76(GLshort x, GLshort y, GLshort z);
void GLAPIENTRY gl_dispatch_stub_77(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_78(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
void GLAPIENTRY gl_dispatch_stub_79(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_80(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void GLAPIENTRY gl_dispatch_stub_81(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_82(GLint x, GLint y, GLint z, GLint w);
void GLAPIENTRY gl_dispatch_stub_83(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_84(GLshort x, GLshort y, GLshort z, GLshort w);
void GLAPIENTRY gl_dispatch_stub_85(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_86(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
void GLAPIENTRY gl_dispatch_stub_87(const GLdouble * v1, const GLdouble * v2);
void GLAPIENTRY gl_dispatch_stub_88(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
void GLAPIENTRY gl_dispatch_stub_89(const GLfloat * v1, const GLfloat * v2);
void GLAPIENTRY gl_dispatch_stub_90(GLint x1, GLint y1, GLint x2, GLint y2);
void GLAPIENTRY gl_dispatch_stub_91(const GLint * v1, const GLint * v2);
void GLAPIENTRY gl_dispatch_stub_92(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
void GLAPIENTRY gl_dispatch_stub_93(const GLshort * v1, const GLshort * v2);
void GLAPIENTRY gl_dispatch_stub_94(GLdouble s);
void GLAPIENTRY gl_dispatch_stub_95(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_96(GLfloat s);
void GLAPIENTRY gl_dispatch_stub_97(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_98(GLint s);
void GLAPIENTRY gl_dispatch_stub_99(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_100(GLshort s);
void GLAPIENTRY gl_dispatch_stub_101(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_102(GLdouble s, GLdouble t);
void GLAPIENTRY gl_dispatch_stub_103(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_104(GLfloat s, GLfloat t);
void GLAPIENTRY gl_dispatch_stub_105(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_106(GLint s, GLint t);
void GLAPIENTRY gl_dispatch_stub_107(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_108(GLshort s, GLshort t);
void GLAPIENTRY gl_dispatch_stub_109(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_110(GLdouble s, GLdouble t, GLdouble r);
void GLAPIENTRY gl_dispatch_stub_111(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_112(GLfloat s, GLfloat t, GLfloat r);
void GLAPIENTRY gl_dispatch_stub_113(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_114(GLint s, GLint t, GLint r);
void GLAPIENTRY gl_dispatch_stub_115(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_116(GLshort s, GLshort t, GLshort r);
void GLAPIENTRY gl_dispatch_stub_117(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_118(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
void GLAPIENTRY gl_dispatch_stub_119(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_120(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
void GLAPIENTRY gl_dispatch_stub_121(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_122(GLint s, GLint t, GLint r, GLint q);
void GLAPIENTRY gl_dispatch_stub_123(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_124(GLshort s, GLshort t, GLshort r, GLshort q);
void GLAPIENTRY gl_dispatch_stub_125(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_126(GLdouble x, GLdouble y);
void GLAPIENTRY gl_dispatch_stub_127(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_128(GLfloat x, GLfloat y);
void GLAPIENTRY gl_dispatch_stub_129(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_130(GLint x, GLint y);
void GLAPIENTRY gl_dispatch_stub_131(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_132(GLshort x, GLshort y);
void GLAPIENTRY gl_dispatch_stub_133(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_134(GLdouble x, GLdouble y, GLdouble z);
void GLAPIENTRY gl_dispatch_stub_135(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_136(GLfloat x, GLfloat y, GLfloat z);
void GLAPIENTRY gl_dispatch_stub_137(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_138(GLint x, GLint y, GLint z);
void GLAPIENTRY gl_dispatch_stub_139(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_140(GLshort x, GLshort y, GLshort z);
void GLAPIENTRY gl_dispatch_stub_141(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_142(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
void GLAPIENTRY gl_dispatch_stub_143(const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_144(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void GLAPIENTRY gl_dispatch_stub_145(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_146(GLint x, GLint y, GLint z, GLint w);
void GLAPIENTRY gl_dispatch_stub_147(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_148(GLshort x, GLshort y, GLshort z, GLshort w);
void GLAPIENTRY gl_dispatch_stub_149(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_150(GLenum plane, const GLdouble * equation);
void GLAPIENTRY gl_dispatch_stub_151(GLenum face, GLenum mode);
void GLAPIENTRY gl_dispatch_stub_155(GLenum pname, GLint param);
void GLAPIENTRY gl_dispatch_stub_156(GLenum pname, const GLint * params);
void GLAPIENTRY gl_dispatch_stub_161(GLenum light, GLenum pname, GLint param);
void GLAPIENTRY gl_dispatch_stub_162(GLenum light, GLenum pname, const GLint * params);
void GLAPIENTRY gl_dispatch_stub_165(GLenum pname, GLint param);
void GLAPIENTRY gl_dispatch_stub_166(GLenum pname, const GLint * params);
void GLAPIENTRY gl_dispatch_stub_167(GLint factor, GLushort pattern);
void GLAPIENTRY gl_dispatch_stub_171(GLenum face, GLenum pname, GLint param);
void GLAPIENTRY gl_dispatch_stub_172(GLenum face, GLenum pname, const GLint * params);
void GLAPIENTRY gl_dispatch_stub_174(GLenum face, GLenum mode);
void GLAPIENTRY gl_dispatch_stub_175(const GLubyte * mask);
void GLAPIENTRY gl_dispatch_stub_182(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels);
void GLAPIENTRY gl_dispatch_stub_188(GLenum coord, GLenum pname, GLdouble param);
void GLAPIENTRY gl_dispatch_stub_189(GLenum coord, GLenum pname, const GLdouble * params);
void GLAPIENTRY gl_dispatch_stub_194(GLsizei size, GLenum type, GLfloat * buffer);
void GLAPIENTRY gl_dispatch_stub_195(GLsizei size, GLuint * buffer);
GLint GLAPIENTRY gl_dispatch_stub_196(GLenum mode);
void GLAPIENTRY gl_dispatch_stub_197(void);
void GLAPIENTRY gl_dispatch_stub_198(GLuint name);
void GLAPIENTRY gl_dispatch_stub_199(GLfloat token);
void GLAPIENTRY gl_dispatch_stub_200(void);
void GLAPIENTRY gl_dispatch_stub_201(GLuint name);
void GLAPIENTRY gl_dispatch_stub_202(GLenum mode);
void GLAPIENTRY gl_dispatch_stub_204(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void GLAPIENTRY gl_dispatch_stub_205(GLfloat c);
void GLAPIENTRY gl_dispatch_stub_208(GLclampd depth);
void GLAPIENTRY gl_dispatch_stub_212(GLuint mask);
void GLAPIENTRY gl_dispatch_stub_213(GLenum op, GLfloat value);
void GLAPIENTRY gl_dispatch_stub_218(void);
void GLAPIENTRY gl_dispatch_stub_219(GLbitfield mask);
void GLAPIENTRY gl_dispatch_stub_220(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points);
void GLAPIENTRY gl_dispatch_stub_221(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points);
void GLAPIENTRY gl_dispatch_stub_222(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points);
void GLAPIENTRY gl_dispatch_stub_223(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points);
void GLAPIENTRY gl_dispatch_stub_224(GLint un, GLdouble u1, GLdouble u2);
void GLAPIENTRY gl_dispatch_stub_225(GLint un, GLfloat u1, GLfloat u2);
void GLAPIENTRY gl_dispatch_stub_226(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
void GLAPIENTRY gl_dispatch_stub_227(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
void GLAPIENTRY gl_dispatch_stub_228(GLdouble u);
void GLAPIENTRY gl_dispatch_stub_229(const GLdouble * u);
void GLAPIENTRY gl_dispatch_stub_230(GLfloat u);
void GLAPIENTRY gl_dispatch_stub_231(const GLfloat * u);
void GLAPIENTRY gl_dispatch_stub_232(GLdouble u, GLdouble v);
void GLAPIENTRY gl_dispatch_stub_233(const GLdouble * u);
void GLAPIENTRY gl_dispatch_stub_234(GLfloat u, GLfloat v);
void GLAPIENTRY gl_dispatch_stub_235(const GLfloat * u);
void GLAPIENTRY gl_dispatch_stub_236(GLenum mode, GLint i1, GLint i2);
void GLAPIENTRY gl_dispatch_stub_237(GLint i);
void GLAPIENTRY gl_dispatch_stub_238(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
void GLAPIENTRY gl_dispatch_stub_239(GLint i, GLint j);
void GLAPIENTRY gl_dispatch_stub_246(GLfloat xfactor, GLfloat yfactor);
void GLAPIENTRY gl_dispatch_stub_247(GLenum pname, GLfloat param);
void GLAPIENTRY gl_dispatch_stub_248(GLenum pname, GLint param);
void GLAPIENTRY gl_dispatch_stub_249(GLenum pname, GLfloat param);
void GLAPIENTRY gl_dispatch_stub_251(GLenum map, GLsizei mapsize, const GLfloat * values);
void GLAPIENTRY gl_dispatch_stub_252(GLenum map, GLsizei mapsize, const GLuint * values);
void GLAPIENTRY gl_dispatch_stub_253(GLenum map, GLsizei mapsize, const GLushort * values);
void GLAPIENTRY gl_dispatch_stub_254(GLenum mode);
void GLAPIENTRY gl_dispatch_stub_255(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
void GLAPIENTRY gl_dispatch_stub_257(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels);
void GLAPIENTRY gl_dispatch_stub_259(GLenum plane, GLdouble * equation);
void GLAPIENTRY gl_dispatch_stub_260(GLenum pname, GLdouble * params);
void GLAPIENTRY gl_dispatch_stub_265(GLenum light, GLenum pname, GLint * params);
void GLAPIENTRY gl_dispatch_stub_266(GLenum target, GLenum query, GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_267(GLenum target, GLenum query, GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_268(GLenum target, GLenum query, GLint * v);
void GLAPIENTRY gl_dispatch_stub_270(GLenum face, GLenum pname, GLint * params);
void GLAPIENTRY gl_dispatch_stub_271(GLenum map, GLfloat * values);
void GLAPIENTRY gl_dispatch_stub_272(GLenum map, GLuint * values);
void GLAPIENTRY gl_dispatch_stub_273(GLenum map, GLushort * values);
void GLAPIENTRY gl_dispatch_stub_274(GLubyte * mask);
void GLAPIENTRY gl_dispatch_stub_278(GLenum coord, GLenum pname, GLdouble * params);
void GLAPIENTRY gl_dispatch_stub_281(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels);
void GLAPIENTRY gl_dispatch_stub_284(GLenum target, GLint level, GLenum pname, GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_285(GLenum target, GLint level, GLenum pname, GLint * params);
GLboolean GLAPIENTRY gl_dispatch_stub_287(GLuint list);
void GLAPIENTRY gl_dispatch_stub_288(GLclampd zNear, GLclampd zFar);
void GLAPIENTRY gl_dispatch_stub_289(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
void GLAPIENTRY gl_dispatch_stub_292(const GLdouble * m);
void GLAPIENTRY gl_dispatch_stub_295(const GLdouble * m);
void GLAPIENTRY gl_dispatch_stub_296(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
void GLAPIENTRY gl_dispatch_stub_299(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
void GLAPIENTRY gl_dispatch_stub_301(GLdouble x, GLdouble y, GLdouble z);
void GLAPIENTRY gl_dispatch_stub_303(GLdouble x, GLdouble y, GLdouble z);
void GLAPIENTRY gl_dispatch_stub_306(GLint i);
void GLAPIENTRY gl_dispatch_stub_312(GLsizei stride, const GLvoid * pointer);
void GLAPIENTRY gl_dispatch_stub_314(GLenum type, GLsizei stride, const GLvoid * pointer);
void GLAPIENTRY gl_dispatch_stub_315(GLubyte c);
void GLAPIENTRY gl_dispatch_stub_316(const GLubyte * c);
void GLAPIENTRY gl_dispatch_stub_317(GLenum format, GLsizei stride, const GLvoid * pointer);
GLboolean GLAPIENTRY gl_dispatch_stub_322(GLsizei n, const GLuint * textures, GLboolean * residences);
void GLAPIENTRY gl_dispatch_stub_323(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
void GLAPIENTRY gl_dispatch_stub_325(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
void GLAPIENTRY gl_dispatch_stub_331(GLsizei n, const GLuint * textures, const GLclampf * priorities);
void GLAPIENTRY gl_dispatch_stub_332(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels);
void GLAPIENTRY gl_dispatch_stub_334(void);
void GLAPIENTRY gl_dispatch_stub_335(GLbitfield mask);
void GLAPIENTRY gl_dispatch_stub_336(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
void GLAPIENTRY gl_dispatch_stub_338(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices);
void GLAPIENTRY gl_dispatch_stub_339(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * table);
void GLAPIENTRY gl_dispatch_stub_340(GLenum target, GLenum pname, const GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_341(GLenum target, GLenum pname, const GLint * params);
void GLAPIENTRY gl_dispatch_stub_342(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
void GLAPIENTRY gl_dispatch_stub_343(GLenum target, GLenum format, GLenum type, GLvoid * table);
void GLAPIENTRY gl_dispatch_stub_344(GLenum target, GLenum pname, GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_345(GLenum target, GLenum pname, GLint * params);
void GLAPIENTRY gl_dispatch_stub_346(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid * data);
void GLAPIENTRY gl_dispatch_stub_347(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
void GLAPIENTRY gl_dispatch_stub_348(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * image);
void GLAPIENTRY gl_dispatch_stub_349(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * image);
void GLAPIENTRY gl_dispatch_stub_350(GLenum target, GLenum pname, GLfloat params);
void GLAPIENTRY gl_dispatch_stub_351(GLenum target, GLenum pname, const GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_352(GLenum target, GLenum pname, GLint params);
void GLAPIENTRY gl_dispatch_stub_353(GLenum target, GLenum pname, const GLint * params);
void GLAPIENTRY gl_dispatch_stub_354(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
void GLAPIENTRY gl_dispatch_stub_355(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
void GLAPIENTRY gl_dispatch_stub_356(GLenum target, GLenum format, GLenum type, GLvoid * image);
void GLAPIENTRY gl_dispatch_stub_357(GLenum target, GLenum pname, GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_358(GLenum target, GLenum pname, GLint * params);
void GLAPIENTRY gl_dispatch_stub_359(GLenum target, GLenum format, GLenum type, GLvoid * row, GLvoid * column, GLvoid * span);
void GLAPIENTRY gl_dispatch_stub_360(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * row, const GLvoid * column);
void GLAPIENTRY gl_dispatch_stub_361(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values);
void GLAPIENTRY gl_dispatch_stub_362(GLenum target, GLenum pname, GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_363(GLenum target, GLenum pname, GLint * params);
void GLAPIENTRY gl_dispatch_stub_364(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values);
void GLAPIENTRY gl_dispatch_stub_365(GLenum target, GLenum pname, GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_366(GLenum target, GLenum pname, GLint * params);
void GLAPIENTRY gl_dispatch_stub_367(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
void GLAPIENTRY gl_dispatch_stub_368(GLenum target, GLenum internalformat, GLboolean sink);
void GLAPIENTRY gl_dispatch_stub_369(GLenum target);
void GLAPIENTRY gl_dispatch_stub_370(GLenum target);
void GLAPIENTRY gl_dispatch_stub_371(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels);
void GLAPIENTRY gl_dispatch_stub_372(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels);
void GLAPIENTRY gl_dispatch_stub_373(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
void GLAPIENTRY gl_dispatch_stub_376(GLenum target, GLdouble s);
void GLAPIENTRY gl_dispatch_stub_377(GLenum target, const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_378(GLenum target, GLfloat s);
void GLAPIENTRY gl_dispatch_stub_379(GLenum target, const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_380(GLenum target, GLint s);
void GLAPIENTRY gl_dispatch_stub_381(GLenum target, const GLint * v);
void GLAPIENTRY gl_dispatch_stub_382(GLenum target, GLshort s);
void GLAPIENTRY gl_dispatch_stub_383(GLenum target, const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_384(GLenum target, GLdouble s, GLdouble t);
void GLAPIENTRY gl_dispatch_stub_385(GLenum target, const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_386(GLenum target, GLfloat s, GLfloat t);
void GLAPIENTRY gl_dispatch_stub_387(GLenum target, const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_388(GLenum target, GLint s, GLint t);
void GLAPIENTRY gl_dispatch_stub_389(GLenum target, const GLint * v);
void GLAPIENTRY gl_dispatch_stub_390(GLenum target, GLshort s, GLshort t);
void GLAPIENTRY gl_dispatch_stub_391(GLenum target, const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_392(GLenum target, GLdouble s, GLdouble t, GLdouble r);
void GLAPIENTRY gl_dispatch_stub_393(GLenum target, const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_394(GLenum target, GLfloat s, GLfloat t, GLfloat r);
void GLAPIENTRY gl_dispatch_stub_395(GLenum target, const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_396(GLenum target, GLint s, GLint t, GLint r);
void GLAPIENTRY gl_dispatch_stub_397(GLenum target, const GLint * v);
void GLAPIENTRY gl_dispatch_stub_398(GLenum target, GLshort s, GLshort t, GLshort r);
void GLAPIENTRY gl_dispatch_stub_399(GLenum target, const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_400(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
void GLAPIENTRY gl_dispatch_stub_401(GLenum target, const GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_403(GLenum target, const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_404(GLenum target, GLint s, GLint t, GLint r, GLint q);
void GLAPIENTRY gl_dispatch_stub_405(GLenum target, const GLint * v);
void GLAPIENTRY gl_dispatch_stub_406(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
void GLAPIENTRY gl_dispatch_stub_407(GLenum target, const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_443(GLuint array);
void GLAPIENTRY gl_dispatch_stub_444(GLsizei n, const GLuint * arrays);
void GLAPIENTRY gl_dispatch_stub_445(GLsizei n, GLuint * arrays);
GLboolean GLAPIENTRY gl_dispatch_stub_446(GLuint array);
#endif /* defined(NEED_FUNCTION_POINTER) || defined(GLX_INDIRECT_RENDERING) */

static const glprocs_table_t static_functions[] = {
    NAME_FUNC_OFFSET(    0, gl_dispatch_stub_0, gl_dispatch_stub_0, NULL, _gloffset_NewList),
    NAME_FUNC_OFFSET(   10, gl_dispatch_stub_1, gl_dispatch_stub_1, NULL, _gloffset_EndList),
    NAME_FUNC_OFFSET(   20, gl_dispatch_stub_2, gl_dispatch_stub_2, NULL, _gloffset_CallList),
    NAME_FUNC_OFFSET(   31, gl_dispatch_stub_3, gl_dispatch_stub_3, NULL, _gloffset_CallLists),
    NAME_FUNC_OFFSET(   43, gl_dispatch_stub_4, gl_dispatch_stub_4, NULL, _gloffset_DeleteLists),
    NAME_FUNC_OFFSET(   57, gl_dispatch_stub_5, gl_dispatch_stub_5, NULL, _gloffset_GenLists),
    NAME_FUNC_OFFSET(   68, gl_dispatch_stub_6, gl_dispatch_stub_6, NULL, _gloffset_ListBase),
    NAME_FUNC_OFFSET(   79, gl_dispatch_stub_7, gl_dispatch_stub_7, NULL, _gloffset_Begin),
    NAME_FUNC_OFFSET(   87, gl_dispatch_stub_8, gl_dispatch_stub_8, NULL, _gloffset_Bitmap),
    NAME_FUNC_OFFSET(   96, gl_dispatch_stub_9, gl_dispatch_stub_9, NULL, _gloffset_Color3b),
    NAME_FUNC_OFFSET(  106, gl_dispatch_stub_10, gl_dispatch_stub_10, NULL, _gloffset_Color3bv),
    NAME_FUNC_OFFSET(  117, gl_dispatch_stub_11, gl_dispatch_stub_11, NULL, _gloffset_Color3d),
    NAME_FUNC_OFFSET(  127, gl_dispatch_stub_12, gl_dispatch_stub_12, NULL, _gloffset_Color3dv),
    NAME_FUNC_OFFSET(  138, gl_dispatch_stub_13, gl_dispatch_stub_13, NULL, _gloffset_Color3f),
    NAME_FUNC_OFFSET(  148, gl_dispatch_stub_14, gl_dispatch_stub_14, NULL, _gloffset_Color3fv),
    NAME_FUNC_OFFSET(  159, gl_dispatch_stub_15, gl_dispatch_stub_15, NULL, _gloffset_Color3i),
    NAME_FUNC_OFFSET(  169, gl_dispatch_stub_16, gl_dispatch_stub_16, NULL, _gloffset_Color3iv),
    NAME_FUNC_OFFSET(  180, gl_dispatch_stub_17, gl_dispatch_stub_17, NULL, _gloffset_Color3s),
    NAME_FUNC_OFFSET(  190, gl_dispatch_stub_18, gl_dispatch_stub_18, NULL, _gloffset_Color3sv),
    NAME_FUNC_OFFSET(  201, gl_dispatch_stub_19, gl_dispatch_stub_19, NULL, _gloffset_Color3ub),
    NAME_FUNC_OFFSET(  212, gl_dispatch_stub_20, gl_dispatch_stub_20, NULL, _gloffset_Color3ubv),
    NAME_FUNC_OFFSET(  224, gl_dispatch_stub_21, gl_dispatch_stub_21, NULL, _gloffset_Color3ui),
    NAME_FUNC_OFFSET(  235, gl_dispatch_stub_22, gl_dispatch_stub_22, NULL, _gloffset_Color3uiv),
    NAME_FUNC_OFFSET(  247, gl_dispatch_stub_23, gl_dispatch_stub_23, NULL, _gloffset_Color3us),
    NAME_FUNC_OFFSET(  258, gl_dispatch_stub_24, gl_dispatch_stub_24, NULL, _gloffset_Color3usv),
    NAME_FUNC_OFFSET(  270, gl_dispatch_stub_25, gl_dispatch_stub_25, NULL, _gloffset_Color4b),
    NAME_FUNC_OFFSET(  280, gl_dispatch_stub_26, gl_dispatch_stub_26, NULL, _gloffset_Color4bv),
    NAME_FUNC_OFFSET(  291, gl_dispatch_stub_27, gl_dispatch_stub_27, NULL, _gloffset_Color4d),
    NAME_FUNC_OFFSET(  301, gl_dispatch_stub_28, gl_dispatch_stub_28, NULL, _gloffset_Color4dv),
    NAME_FUNC_OFFSET(  312, glColor4f, glColor4f, NULL, _gloffset_Color4f),
    NAME_FUNC_OFFSET(  322, gl_dispatch_stub_30, gl_dispatch_stub_30, NULL, _gloffset_Color4fv),
    NAME_FUNC_OFFSET(  333, gl_dispatch_stub_31, gl_dispatch_stub_31, NULL, _gloffset_Color4i),
    NAME_FUNC_OFFSET(  343, gl_dispatch_stub_32, gl_dispatch_stub_32, NULL, _gloffset_Color4iv),
    NAME_FUNC_OFFSET(  354, gl_dispatch_stub_33, gl_dispatch_stub_33, NULL, _gloffset_Color4s),
    NAME_FUNC_OFFSET(  364, gl_dispatch_stub_34, gl_dispatch_stub_34, NULL, _gloffset_Color4sv),
    NAME_FUNC_OFFSET(  375, glColor4ub, glColor4ub, NULL, _gloffset_Color4ub),
    NAME_FUNC_OFFSET(  386, gl_dispatch_stub_36, gl_dispatch_stub_36, NULL, _gloffset_Color4ubv),
    NAME_FUNC_OFFSET(  398, gl_dispatch_stub_37, gl_dispatch_stub_37, NULL, _gloffset_Color4ui),
    NAME_FUNC_OFFSET(  409, gl_dispatch_stub_38, gl_dispatch_stub_38, NULL, _gloffset_Color4uiv),
    NAME_FUNC_OFFSET(  421, gl_dispatch_stub_39, gl_dispatch_stub_39, NULL, _gloffset_Color4us),
    NAME_FUNC_OFFSET(  432, gl_dispatch_stub_40, gl_dispatch_stub_40, NULL, _gloffset_Color4usv),
    NAME_FUNC_OFFSET(  444, gl_dispatch_stub_41, gl_dispatch_stub_41, NULL, _gloffset_EdgeFlag),
    NAME_FUNC_OFFSET(  455, gl_dispatch_stub_42, gl_dispatch_stub_42, NULL, _gloffset_EdgeFlagv),
    NAME_FUNC_OFFSET(  467, gl_dispatch_stub_43, gl_dispatch_stub_43, NULL, _gloffset_End),
    NAME_FUNC_OFFSET(  473, gl_dispatch_stub_44, gl_dispatch_stub_44, NULL, _gloffset_Indexd),
    NAME_FUNC_OFFSET(  482, gl_dispatch_stub_45, gl_dispatch_stub_45, NULL, _gloffset_Indexdv),
    NAME_FUNC_OFFSET(  492, gl_dispatch_stub_46, gl_dispatch_stub_46, NULL, _gloffset_Indexf),
    NAME_FUNC_OFFSET(  501, gl_dispatch_stub_47, gl_dispatch_stub_47, NULL, _gloffset_Indexfv),
    NAME_FUNC_OFFSET(  511, gl_dispatch_stub_48, gl_dispatch_stub_48, NULL, _gloffset_Indexi),
    NAME_FUNC_OFFSET(  520, gl_dispatch_stub_49, gl_dispatch_stub_49, NULL, _gloffset_Indexiv),
    NAME_FUNC_OFFSET(  530, gl_dispatch_stub_50, gl_dispatch_stub_50, NULL, _gloffset_Indexs),
    NAME_FUNC_OFFSET(  539, gl_dispatch_stub_51, gl_dispatch_stub_51, NULL, _gloffset_Indexsv),
    NAME_FUNC_OFFSET(  549, gl_dispatch_stub_52, gl_dispatch_stub_52, NULL, _gloffset_Normal3b),
    NAME_FUNC_OFFSET(  560, gl_dispatch_stub_53, gl_dispatch_stub_53, NULL, _gloffset_Normal3bv),
    NAME_FUNC_OFFSET(  572, gl_dispatch_stub_54, gl_dispatch_stub_54, NULL, _gloffset_Normal3d),
    NAME_FUNC_OFFSET(  583, gl_dispatch_stub_55, gl_dispatch_stub_55, NULL, _gloffset_Normal3dv),
    NAME_FUNC_OFFSET(  595, glNormal3f, glNormal3f, NULL, _gloffset_Normal3f),
    NAME_FUNC_OFFSET(  606, gl_dispatch_stub_57, gl_dispatch_stub_57, NULL, _gloffset_Normal3fv),
    NAME_FUNC_OFFSET(  618, gl_dispatch_stub_58, gl_dispatch_stub_58, NULL, _gloffset_Normal3i),
    NAME_FUNC_OFFSET(  629, gl_dispatch_stub_59, gl_dispatch_stub_59, NULL, _gloffset_Normal3iv),
    NAME_FUNC_OFFSET(  641, gl_dispatch_stub_60, gl_dispatch_stub_60, NULL, _gloffset_Normal3s),
    NAME_FUNC_OFFSET(  652, gl_dispatch_stub_61, gl_dispatch_stub_61, NULL, _gloffset_Normal3sv),
    NAME_FUNC_OFFSET(  664, gl_dispatch_stub_62, gl_dispatch_stub_62, NULL, _gloffset_RasterPos2d),
    NAME_FUNC_OFFSET(  678, gl_dispatch_stub_63, gl_dispatch_stub_63, NULL, _gloffset_RasterPos2dv),
    NAME_FUNC_OFFSET(  693, gl_dispatch_stub_64, gl_dispatch_stub_64, NULL, _gloffset_RasterPos2f),
    NAME_FUNC_OFFSET(  707, gl_dispatch_stub_65, gl_dispatch_stub_65, NULL, _gloffset_RasterPos2fv),
    NAME_FUNC_OFFSET(  722, gl_dispatch_stub_66, gl_dispatch_stub_66, NULL, _gloffset_RasterPos2i),
    NAME_FUNC_OFFSET(  736, gl_dispatch_stub_67, gl_dispatch_stub_67, NULL, _gloffset_RasterPos2iv),
    NAME_FUNC_OFFSET(  751, gl_dispatch_stub_68, gl_dispatch_stub_68, NULL, _gloffset_RasterPos2s),
    NAME_FUNC_OFFSET(  765, gl_dispatch_stub_69, gl_dispatch_stub_69, NULL, _gloffset_RasterPos2sv),
    NAME_FUNC_OFFSET(  780, gl_dispatch_stub_70, gl_dispatch_stub_70, NULL, _gloffset_RasterPos3d),
    NAME_FUNC_OFFSET(  794, gl_dispatch_stub_71, gl_dispatch_stub_71, NULL, _gloffset_RasterPos3dv),
    NAME_FUNC_OFFSET(  809, gl_dispatch_stub_72, gl_dispatch_stub_72, NULL, _gloffset_RasterPos3f),
    NAME_FUNC_OFFSET(  823, gl_dispatch_stub_73, gl_dispatch_stub_73, NULL, _gloffset_RasterPos3fv),
    NAME_FUNC_OFFSET(  838, gl_dispatch_stub_74, gl_dispatch_stub_74, NULL, _gloffset_RasterPos3i),
    NAME_FUNC_OFFSET(  852, gl_dispatch_stub_75, gl_dispatch_stub_75, NULL, _gloffset_RasterPos3iv),
    NAME_FUNC_OFFSET(  867, gl_dispatch_stub_76, gl_dispatch_stub_76, NULL, _gloffset_RasterPos3s),
    NAME_FUNC_OFFSET(  881, gl_dispatch_stub_77, gl_dispatch_stub_77, NULL, _gloffset_RasterPos3sv),
    NAME_FUNC_OFFSET(  896, gl_dispatch_stub_78, gl_dispatch_stub_78, NULL, _gloffset_RasterPos4d),
    NAME_FUNC_OFFSET(  910, gl_dispatch_stub_79, gl_dispatch_stub_79, NULL, _gloffset_RasterPos4dv),
    NAME_FUNC_OFFSET(  925, gl_dispatch_stub_80, gl_dispatch_stub_80, NULL, _gloffset_RasterPos4f),
    NAME_FUNC_OFFSET(  939, gl_dispatch_stub_81, gl_dispatch_stub_81, NULL, _gloffset_RasterPos4fv),
    NAME_FUNC_OFFSET(  954, gl_dispatch_stub_82, gl_dispatch_stub_82, NULL, _gloffset_RasterPos4i),
    NAME_FUNC_OFFSET(  968, gl_dispatch_stub_83, gl_dispatch_stub_83, NULL, _gloffset_RasterPos4iv),
    NAME_FUNC_OFFSET(  983, gl_dispatch_stub_84, gl_dispatch_stub_84, NULL, _gloffset_RasterPos4s),
    NAME_FUNC_OFFSET(  997, gl_dispatch_stub_85, gl_dispatch_stub_85, NULL, _gloffset_RasterPos4sv),
    NAME_FUNC_OFFSET( 1012, gl_dispatch_stub_86, gl_dispatch_stub_86, NULL, _gloffset_Rectd),
    NAME_FUNC_OFFSET( 1020, gl_dispatch_stub_87, gl_dispatch_stub_87, NULL, _gloffset_Rectdv),
    NAME_FUNC_OFFSET( 1029, gl_dispatch_stub_88, gl_dispatch_stub_88, NULL, _gloffset_Rectf),
    NAME_FUNC_OFFSET( 1037, gl_dispatch_stub_89, gl_dispatch_stub_89, NULL, _gloffset_Rectfv),
    NAME_FUNC_OFFSET( 1046, gl_dispatch_stub_90, gl_dispatch_stub_90, NULL, _gloffset_Recti),
    NAME_FUNC_OFFSET( 1054, gl_dispatch_stub_91, gl_dispatch_stub_91, NULL, _gloffset_Rectiv),
    NAME_FUNC_OFFSET( 1063, gl_dispatch_stub_92, gl_dispatch_stub_92, NULL, _gloffset_Rects),
    NAME_FUNC_OFFSET( 1071, gl_dispatch_stub_93, gl_dispatch_stub_93, NULL, _gloffset_Rectsv),
    NAME_FUNC_OFFSET( 1080, gl_dispatch_stub_94, gl_dispatch_stub_94, NULL, _gloffset_TexCoord1d),
    NAME_FUNC_OFFSET( 1093, gl_dispatch_stub_95, gl_dispatch_stub_95, NULL, _gloffset_TexCoord1dv),
    NAME_FUNC_OFFSET( 1107, gl_dispatch_stub_96, gl_dispatch_stub_96, NULL, _gloffset_TexCoord1f),
    NAME_FUNC_OFFSET( 1120, gl_dispatch_stub_97, gl_dispatch_stub_97, NULL, _gloffset_TexCoord1fv),
    NAME_FUNC_OFFSET( 1134, gl_dispatch_stub_98, gl_dispatch_stub_98, NULL, _gloffset_TexCoord1i),
    NAME_FUNC_OFFSET( 1147, gl_dispatch_stub_99, gl_dispatch_stub_99, NULL, _gloffset_TexCoord1iv),
    NAME_FUNC_OFFSET( 1161, gl_dispatch_stub_100, gl_dispatch_stub_100, NULL, _gloffset_TexCoord1s),
    NAME_FUNC_OFFSET( 1174, gl_dispatch_stub_101, gl_dispatch_stub_101, NULL, _gloffset_TexCoord1sv),
    NAME_FUNC_OFFSET( 1188, gl_dispatch_stub_102, gl_dispatch_stub_102, NULL, _gloffset_TexCoord2d),
    NAME_FUNC_OFFSET( 1201, gl_dispatch_stub_103, gl_dispatch_stub_103, NULL, _gloffset_TexCoord2dv),
    NAME_FUNC_OFFSET( 1215, gl_dispatch_stub_104, gl_dispatch_stub_104, NULL, _gloffset_TexCoord2f),
    NAME_FUNC_OFFSET( 1228, gl_dispatch_stub_105, gl_dispatch_stub_105, NULL, _gloffset_TexCoord2fv),
    NAME_FUNC_OFFSET( 1242, gl_dispatch_stub_106, gl_dispatch_stub_106, NULL, _gloffset_TexCoord2i),
    NAME_FUNC_OFFSET( 1255, gl_dispatch_stub_107, gl_dispatch_stub_107, NULL, _gloffset_TexCoord2iv),
    NAME_FUNC_OFFSET( 1269, gl_dispatch_stub_108, gl_dispatch_stub_108, NULL, _gloffset_TexCoord2s),
    NAME_FUNC_OFFSET( 1282, gl_dispatch_stub_109, gl_dispatch_stub_109, NULL, _gloffset_TexCoord2sv),
    NAME_FUNC_OFFSET( 1296, gl_dispatch_stub_110, gl_dispatch_stub_110, NULL, _gloffset_TexCoord3d),
    NAME_FUNC_OFFSET( 1309, gl_dispatch_stub_111, gl_dispatch_stub_111, NULL, _gloffset_TexCoord3dv),
    NAME_FUNC_OFFSET( 1323, gl_dispatch_stub_112, gl_dispatch_stub_112, NULL, _gloffset_TexCoord3f),
    NAME_FUNC_OFFSET( 1336, gl_dispatch_stub_113, gl_dispatch_stub_113, NULL, _gloffset_TexCoord3fv),
    NAME_FUNC_OFFSET( 1350, gl_dispatch_stub_114, gl_dispatch_stub_114, NULL, _gloffset_TexCoord3i),
    NAME_FUNC_OFFSET( 1363, gl_dispatch_stub_115, gl_dispatch_stub_115, NULL, _gloffset_TexCoord3iv),
    NAME_FUNC_OFFSET( 1377, gl_dispatch_stub_116, gl_dispatch_stub_116, NULL, _gloffset_TexCoord3s),
    NAME_FUNC_OFFSET( 1390, gl_dispatch_stub_117, gl_dispatch_stub_117, NULL, _gloffset_TexCoord3sv),
    NAME_FUNC_OFFSET( 1404, gl_dispatch_stub_118, gl_dispatch_stub_118, NULL, _gloffset_TexCoord4d),
    NAME_FUNC_OFFSET( 1417, gl_dispatch_stub_119, gl_dispatch_stub_119, NULL, _gloffset_TexCoord4dv),
    NAME_FUNC_OFFSET( 1431, gl_dispatch_stub_120, gl_dispatch_stub_120, NULL, _gloffset_TexCoord4f),
    NAME_FUNC_OFFSET( 1444, gl_dispatch_stub_121, gl_dispatch_stub_121, NULL, _gloffset_TexCoord4fv),
    NAME_FUNC_OFFSET( 1458, gl_dispatch_stub_122, gl_dispatch_stub_122, NULL, _gloffset_TexCoord4i),
    NAME_FUNC_OFFSET( 1471, gl_dispatch_stub_123, gl_dispatch_stub_123, NULL, _gloffset_TexCoord4iv),
    NAME_FUNC_OFFSET( 1485, gl_dispatch_stub_124, gl_dispatch_stub_124, NULL, _gloffset_TexCoord4s),
    NAME_FUNC_OFFSET( 1498, gl_dispatch_stub_125, gl_dispatch_stub_125, NULL, _gloffset_TexCoord4sv),
    NAME_FUNC_OFFSET( 1512, gl_dispatch_stub_126, gl_dispatch_stub_126, NULL, _gloffset_Vertex2d),
    NAME_FUNC_OFFSET( 1523, gl_dispatch_stub_127, gl_dispatch_stub_127, NULL, _gloffset_Vertex2dv),
    NAME_FUNC_OFFSET( 1535, gl_dispatch_stub_128, gl_dispatch_stub_128, NULL, _gloffset_Vertex2f),
    NAME_FUNC_OFFSET( 1546, gl_dispatch_stub_129, gl_dispatch_stub_129, NULL, _gloffset_Vertex2fv),
    NAME_FUNC_OFFSET( 1558, gl_dispatch_stub_130, gl_dispatch_stub_130, NULL, _gloffset_Vertex2i),
    NAME_FUNC_OFFSET( 1569, gl_dispatch_stub_131, gl_dispatch_stub_131, NULL, _gloffset_Vertex2iv),
    NAME_FUNC_OFFSET( 1581, gl_dispatch_stub_132, gl_dispatch_stub_132, NULL, _gloffset_Vertex2s),
    NAME_FUNC_OFFSET( 1592, gl_dispatch_stub_133, gl_dispatch_stub_133, NULL, _gloffset_Vertex2sv),
    NAME_FUNC_OFFSET( 1604, gl_dispatch_stub_134, gl_dispatch_stub_134, NULL, _gloffset_Vertex3d),
    NAME_FUNC_OFFSET( 1615, gl_dispatch_stub_135, gl_dispatch_stub_135, NULL, _gloffset_Vertex3dv),
    NAME_FUNC_OFFSET( 1627, gl_dispatch_stub_136, gl_dispatch_stub_136, NULL, _gloffset_Vertex3f),
    NAME_FUNC_OFFSET( 1638, gl_dispatch_stub_137, gl_dispatch_stub_137, NULL, _gloffset_Vertex3fv),
    NAME_FUNC_OFFSET( 1650, gl_dispatch_stub_138, gl_dispatch_stub_138, NULL, _gloffset_Vertex3i),
    NAME_FUNC_OFFSET( 1661, gl_dispatch_stub_139, gl_dispatch_stub_139, NULL, _gloffset_Vertex3iv),
    NAME_FUNC_OFFSET( 1673, gl_dispatch_stub_140, gl_dispatch_stub_140, NULL, _gloffset_Vertex3s),
    NAME_FUNC_OFFSET( 1684, gl_dispatch_stub_141, gl_dispatch_stub_141, NULL, _gloffset_Vertex3sv),
    NAME_FUNC_OFFSET( 1696, gl_dispatch_stub_142, gl_dispatch_stub_142, NULL, _gloffset_Vertex4d),
    NAME_FUNC_OFFSET( 1707, gl_dispatch_stub_143, gl_dispatch_stub_143, NULL, _gloffset_Vertex4dv),
    NAME_FUNC_OFFSET( 1719, gl_dispatch_stub_144, gl_dispatch_stub_144, NULL, _gloffset_Vertex4f),
    NAME_FUNC_OFFSET( 1730, gl_dispatch_stub_145, gl_dispatch_stub_145, NULL, _gloffset_Vertex4fv),
    NAME_FUNC_OFFSET( 1742, gl_dispatch_stub_146, gl_dispatch_stub_146, NULL, _gloffset_Vertex4i),
    NAME_FUNC_OFFSET( 1753, gl_dispatch_stub_147, gl_dispatch_stub_147, NULL, _gloffset_Vertex4iv),
    NAME_FUNC_OFFSET( 1765, gl_dispatch_stub_148, gl_dispatch_stub_148, NULL, _gloffset_Vertex4s),
    NAME_FUNC_OFFSET( 1776, gl_dispatch_stub_149, gl_dispatch_stub_149, NULL, _gloffset_Vertex4sv),
    NAME_FUNC_OFFSET( 1788, gl_dispatch_stub_150, gl_dispatch_stub_150, NULL, _gloffset_ClipPlane),
    NAME_FUNC_OFFSET( 1800, gl_dispatch_stub_151, gl_dispatch_stub_151, NULL, _gloffset_ColorMaterial),
    NAME_FUNC_OFFSET( 1816, glCullFace, glCullFace, NULL, _gloffset_CullFace),
    NAME_FUNC_OFFSET( 1827, glFogf, glFogf, NULL, _gloffset_Fogf),
    NAME_FUNC_OFFSET( 1834, glFogfv, glFogfv, NULL, _gloffset_Fogfv),
    NAME_FUNC_OFFSET( 1842, gl_dispatch_stub_155, gl_dispatch_stub_155, NULL, _gloffset_Fogi),
    NAME_FUNC_OFFSET( 1849, gl_dispatch_stub_156, gl_dispatch_stub_156, NULL, _gloffset_Fogiv),
    NAME_FUNC_OFFSET( 1857, glFrontFace, glFrontFace, NULL, _gloffset_FrontFace),
    NAME_FUNC_OFFSET( 1869, glHint, glHint, NULL, _gloffset_Hint),
    NAME_FUNC_OFFSET( 1876, glLightf, glLightf, NULL, _gloffset_Lightf),
    NAME_FUNC_OFFSET( 1885, glLightfv, glLightfv, NULL, _gloffset_Lightfv),
    NAME_FUNC_OFFSET( 1895, gl_dispatch_stub_161, gl_dispatch_stub_161, NULL, _gloffset_Lighti),
    NAME_FUNC_OFFSET( 1904, gl_dispatch_stub_162, gl_dispatch_stub_162, NULL, _gloffset_Lightiv),
    NAME_FUNC_OFFSET( 1914, glLightModelf, glLightModelf, NULL, _gloffset_LightModelf),
    NAME_FUNC_OFFSET( 1928, glLightModelfv, glLightModelfv, NULL, _gloffset_LightModelfv),
    NAME_FUNC_OFFSET( 1943, gl_dispatch_stub_165, gl_dispatch_stub_165, NULL, _gloffset_LightModeli),
    NAME_FUNC_OFFSET( 1957, gl_dispatch_stub_166, gl_dispatch_stub_166, NULL, _gloffset_LightModeliv),
    NAME_FUNC_OFFSET( 1972, gl_dispatch_stub_167, gl_dispatch_stub_167, NULL, _gloffset_LineStipple),
    NAME_FUNC_OFFSET( 1986, glLineWidth, glLineWidth, NULL, _gloffset_LineWidth),
    NAME_FUNC_OFFSET( 1998, glMaterialf, glMaterialf, NULL, _gloffset_Materialf),
    NAME_FUNC_OFFSET( 2010, glMaterialfv, glMaterialfv, NULL, _gloffset_Materialfv),
    NAME_FUNC_OFFSET( 2023, gl_dispatch_stub_171, gl_dispatch_stub_171, NULL, _gloffset_Materiali),
    NAME_FUNC_OFFSET( 2035, gl_dispatch_stub_172, gl_dispatch_stub_172, NULL, _gloffset_Materialiv),
    NAME_FUNC_OFFSET( 2048, glPointSize, glPointSize, NULL, _gloffset_PointSize),
    NAME_FUNC_OFFSET( 2060, gl_dispatch_stub_174, gl_dispatch_stub_174, NULL, _gloffset_PolygonMode),
    NAME_FUNC_OFFSET( 2074, gl_dispatch_stub_175, gl_dispatch_stub_175, NULL, _gloffset_PolygonStipple),
    NAME_FUNC_OFFSET( 2091, glScissor, glScissor, NULL, _gloffset_Scissor),
    NAME_FUNC_OFFSET( 2101, glShadeModel, glShadeModel, NULL, _gloffset_ShadeModel),
    NAME_FUNC_OFFSET( 2114, glTexParameterf, glTexParameterf, NULL, _gloffset_TexParameterf),
    NAME_FUNC_OFFSET( 2130, glTexParameterfv, glTexParameterfv, NULL, _gloffset_TexParameterfv),
    NAME_FUNC_OFFSET( 2147, glTexParameteri, glTexParameteri, NULL, _gloffset_TexParameteri),
    NAME_FUNC_OFFSET( 2163, glTexParameteriv, glTexParameteriv, NULL, _gloffset_TexParameteriv),
    NAME_FUNC_OFFSET( 2180, gl_dispatch_stub_182, gl_dispatch_stub_182, NULL, _gloffset_TexImage1D),
    NAME_FUNC_OFFSET( 2193, glTexImage2D, glTexImage2D, NULL, _gloffset_TexImage2D),
    NAME_FUNC_OFFSET( 2206, glTexEnvf, glTexEnvf, NULL, _gloffset_TexEnvf),
    NAME_FUNC_OFFSET( 2216, glTexEnvfv, glTexEnvfv, NULL, _gloffset_TexEnvfv),
    NAME_FUNC_OFFSET( 2227, glTexEnvi, glTexEnvi, NULL, _gloffset_TexEnvi),
    NAME_FUNC_OFFSET( 2237, glTexEnviv, glTexEnviv, NULL, _gloffset_TexEnviv),
    NAME_FUNC_OFFSET( 2248, gl_dispatch_stub_188, gl_dispatch_stub_188, NULL, _gloffset_TexGend),
    NAME_FUNC_OFFSET( 2258, gl_dispatch_stub_189, gl_dispatch_stub_189, NULL, _gloffset_TexGendv),
    NAME_FUNC_OFFSET( 2269, glTexGenfOES, glTexGenfOES, NULL, _gloffset_TexGenfOES),
    NAME_FUNC_OFFSET( 2282, glTexGenfvOES, glTexGenfvOES, NULL, _gloffset_TexGenfvOES),
    NAME_FUNC_OFFSET( 2296, glTexGeniOES, glTexGeniOES, NULL, _gloffset_TexGeniOES),
    NAME_FUNC_OFFSET( 2309, glTexGenivOES, glTexGenivOES, NULL, _gloffset_TexGenivOES),
    NAME_FUNC_OFFSET( 2323, gl_dispatch_stub_194, gl_dispatch_stub_194, NULL, _gloffset_FeedbackBuffer),
    NAME_FUNC_OFFSET( 2340, gl_dispatch_stub_195, gl_dispatch_stub_195, NULL, _gloffset_SelectBuffer),
    NAME_FUNC_OFFSET( 2355, gl_dispatch_stub_196, gl_dispatch_stub_196, NULL, _gloffset_RenderMode),
    NAME_FUNC_OFFSET( 2368, gl_dispatch_stub_197, gl_dispatch_stub_197, NULL, _gloffset_InitNames),
    NAME_FUNC_OFFSET( 2380, gl_dispatch_stub_198, gl_dispatch_stub_198, NULL, _gloffset_LoadName),
    NAME_FUNC_OFFSET( 2391, gl_dispatch_stub_199, gl_dispatch_stub_199, NULL, _gloffset_PassThrough),
    NAME_FUNC_OFFSET( 2405, gl_dispatch_stub_200, gl_dispatch_stub_200, NULL, _gloffset_PopName),
    NAME_FUNC_OFFSET( 2415, gl_dispatch_stub_201, gl_dispatch_stub_201, NULL, _gloffset_PushName),
    NAME_FUNC_OFFSET( 2426, gl_dispatch_stub_202, gl_dispatch_stub_202, NULL, _gloffset_DrawBuffer),
    NAME_FUNC_OFFSET( 2439, glClear, glClear, NULL, _gloffset_Clear),
    NAME_FUNC_OFFSET( 2447, gl_dispatch_stub_204, gl_dispatch_stub_204, NULL, _gloffset_ClearAccum),
    NAME_FUNC_OFFSET( 2460, gl_dispatch_stub_205, gl_dispatch_stub_205, NULL, _gloffset_ClearIndex),
    NAME_FUNC_OFFSET( 2473, glClearColor, glClearColor, NULL, _gloffset_ClearColor),
    NAME_FUNC_OFFSET( 2486, glClearStencil, glClearStencil, NULL, _gloffset_ClearStencil),
    NAME_FUNC_OFFSET( 2501, gl_dispatch_stub_208, gl_dispatch_stub_208, NULL, _gloffset_ClearDepth),
    NAME_FUNC_OFFSET( 2514, glStencilMask, glStencilMask, NULL, _gloffset_StencilMask),
    NAME_FUNC_OFFSET( 2528, glColorMask, glColorMask, NULL, _gloffset_ColorMask),
    NAME_FUNC_OFFSET( 2540, glDepthMask, glDepthMask, NULL, _gloffset_DepthMask),
    NAME_FUNC_OFFSET( 2552, gl_dispatch_stub_212, gl_dispatch_stub_212, NULL, _gloffset_IndexMask),
    NAME_FUNC_OFFSET( 2564, gl_dispatch_stub_213, gl_dispatch_stub_213, NULL, _gloffset_Accum),
    NAME_FUNC_OFFSET( 2572, glDisable, glDisable, NULL, _gloffset_Disable),
    NAME_FUNC_OFFSET( 2582, glEnable, glEnable, NULL, _gloffset_Enable),
    NAME_FUNC_OFFSET( 2591, glFinish, glFinish, NULL, _gloffset_Finish),
    NAME_FUNC_OFFSET( 2600, glFlush, glFlush, NULL, _gloffset_Flush),
    NAME_FUNC_OFFSET( 2608, gl_dispatch_stub_218, gl_dispatch_stub_218, NULL, _gloffset_PopAttrib),
    NAME_FUNC_OFFSET( 2620, gl_dispatch_stub_219, gl_dispatch_stub_219, NULL, _gloffset_PushAttrib),
    NAME_FUNC_OFFSET( 2633, gl_dispatch_stub_220, gl_dispatch_stub_220, NULL, _gloffset_Map1d),
    NAME_FUNC_OFFSET( 2641, gl_dispatch_stub_221, gl_dispatch_stub_221, NULL, _gloffset_Map1f),
    NAME_FUNC_OFFSET( 2649, gl_dispatch_stub_222, gl_dispatch_stub_222, NULL, _gloffset_Map2d),
    NAME_FUNC_OFFSET( 2657, gl_dispatch_stub_223, gl_dispatch_stub_223, NULL, _gloffset_Map2f),
    NAME_FUNC_OFFSET( 2665, gl_dispatch_stub_224, gl_dispatch_stub_224, NULL, _gloffset_MapGrid1d),
    NAME_FUNC_OFFSET( 2677, gl_dispatch_stub_225, gl_dispatch_stub_225, NULL, _gloffset_MapGrid1f),
    NAME_FUNC_OFFSET( 2689, gl_dispatch_stub_226, gl_dispatch_stub_226, NULL, _gloffset_MapGrid2d),
    NAME_FUNC_OFFSET( 2701, gl_dispatch_stub_227, gl_dispatch_stub_227, NULL, _gloffset_MapGrid2f),
    NAME_FUNC_OFFSET( 2713, gl_dispatch_stub_228, gl_dispatch_stub_228, NULL, _gloffset_EvalCoord1d),
    NAME_FUNC_OFFSET( 2727, gl_dispatch_stub_229, gl_dispatch_stub_229, NULL, _gloffset_EvalCoord1dv),
    NAME_FUNC_OFFSET( 2742, gl_dispatch_stub_230, gl_dispatch_stub_230, NULL, _gloffset_EvalCoord1f),
    NAME_FUNC_OFFSET( 2756, gl_dispatch_stub_231, gl_dispatch_stub_231, NULL, _gloffset_EvalCoord1fv),
    NAME_FUNC_OFFSET( 2771, gl_dispatch_stub_232, gl_dispatch_stub_232, NULL, _gloffset_EvalCoord2d),
    NAME_FUNC_OFFSET( 2785, gl_dispatch_stub_233, gl_dispatch_stub_233, NULL, _gloffset_EvalCoord2dv),
    NAME_FUNC_OFFSET( 2800, gl_dispatch_stub_234, gl_dispatch_stub_234, NULL, _gloffset_EvalCoord2f),
    NAME_FUNC_OFFSET( 2814, gl_dispatch_stub_235, gl_dispatch_stub_235, NULL, _gloffset_EvalCoord2fv),
    NAME_FUNC_OFFSET( 2829, gl_dispatch_stub_236, gl_dispatch_stub_236, NULL, _gloffset_EvalMesh1),
    NAME_FUNC_OFFSET( 2841, gl_dispatch_stub_237, gl_dispatch_stub_237, NULL, _gloffset_EvalPoint1),
    NAME_FUNC_OFFSET( 2854, gl_dispatch_stub_238, gl_dispatch_stub_238, NULL, _gloffset_EvalMesh2),
    NAME_FUNC_OFFSET( 2866, gl_dispatch_stub_239, gl_dispatch_stub_239, NULL, _gloffset_EvalPoint2),
    NAME_FUNC_OFFSET( 2879, glAlphaFunc, glAlphaFunc, NULL, _gloffset_AlphaFunc),
    NAME_FUNC_OFFSET( 2891, glBlendFunc, glBlendFunc, NULL, _gloffset_BlendFunc),
    NAME_FUNC_OFFSET( 2903, glLogicOp, glLogicOp, NULL, _gloffset_LogicOp),
    NAME_FUNC_OFFSET( 2913, glStencilFunc, glStencilFunc, NULL, _gloffset_StencilFunc),
    NAME_FUNC_OFFSET( 2927, glStencilOp, glStencilOp, NULL, _gloffset_StencilOp),
    NAME_FUNC_OFFSET( 2939, glDepthFunc, glDepthFunc, NULL, _gloffset_DepthFunc),
    NAME_FUNC_OFFSET( 2951, gl_dispatch_stub_246, gl_dispatch_stub_246, NULL, _gloffset_PixelZoom),
    NAME_FUNC_OFFSET( 2963, gl_dispatch_stub_247, gl_dispatch_stub_247, NULL, _gloffset_PixelTransferf),
    NAME_FUNC_OFFSET( 2980, gl_dispatch_stub_248, gl_dispatch_stub_248, NULL, _gloffset_PixelTransferi),
    NAME_FUNC_OFFSET( 2997, gl_dispatch_stub_249, gl_dispatch_stub_249, NULL, _gloffset_PixelStoref),
    NAME_FUNC_OFFSET( 3011, glPixelStorei, glPixelStorei, NULL, _gloffset_PixelStorei),
    NAME_FUNC_OFFSET( 3025, gl_dispatch_stub_251, gl_dispatch_stub_251, NULL, _gloffset_PixelMapfv),
    NAME_FUNC_OFFSET( 3038, gl_dispatch_stub_252, gl_dispatch_stub_252, NULL, _gloffset_PixelMapuiv),
    NAME_FUNC_OFFSET( 3052, gl_dispatch_stub_253, gl_dispatch_stub_253, NULL, _gloffset_PixelMapusv),
    NAME_FUNC_OFFSET( 3066, gl_dispatch_stub_254, gl_dispatch_stub_254, NULL, _gloffset_ReadBuffer),
    NAME_FUNC_OFFSET( 3079, gl_dispatch_stub_255, gl_dispatch_stub_255, NULL, _gloffset_CopyPixels),
    NAME_FUNC_OFFSET( 3092, glReadPixels, glReadPixels, NULL, _gloffset_ReadPixels),
    NAME_FUNC_OFFSET( 3105, gl_dispatch_stub_257, gl_dispatch_stub_257, NULL, _gloffset_DrawPixels),
    NAME_FUNC_OFFSET( 3118, glGetBooleanv, glGetBooleanv, NULL, _gloffset_GetBooleanv),
    NAME_FUNC_OFFSET( 3132, gl_dispatch_stub_259, gl_dispatch_stub_259, NULL, _gloffset_GetClipPlane),
    NAME_FUNC_OFFSET( 3147, gl_dispatch_stub_260, gl_dispatch_stub_260, NULL, _gloffset_GetDoublev),
    NAME_FUNC_OFFSET( 3160, glGetError, glGetError, NULL, _gloffset_GetError),
    NAME_FUNC_OFFSET( 3171, glGetFloatv, glGetFloatv, NULL, _gloffset_GetFloatv),
    NAME_FUNC_OFFSET( 3183, glGetIntegerv, glGetIntegerv, NULL, _gloffset_GetIntegerv),
    NAME_FUNC_OFFSET( 3197, glGetLightfv, glGetLightfv, NULL, _gloffset_GetLightfv),
    NAME_FUNC_OFFSET( 3210, gl_dispatch_stub_265, gl_dispatch_stub_265, NULL, _gloffset_GetLightiv),
    NAME_FUNC_OFFSET( 3223, gl_dispatch_stub_266, gl_dispatch_stub_266, NULL, _gloffset_GetMapdv),
    NAME_FUNC_OFFSET( 3234, gl_dispatch_stub_267, gl_dispatch_stub_267, NULL, _gloffset_GetMapfv),
    NAME_FUNC_OFFSET( 3245, gl_dispatch_stub_268, gl_dispatch_stub_268, NULL, _gloffset_GetMapiv),
    NAME_FUNC_OFFSET( 3256, glGetMaterialfv, glGetMaterialfv, NULL, _gloffset_GetMaterialfv),
    NAME_FUNC_OFFSET( 3272, gl_dispatch_stub_270, gl_dispatch_stub_270, NULL, _gloffset_GetMaterialiv),
    NAME_FUNC_OFFSET( 3288, gl_dispatch_stub_271, gl_dispatch_stub_271, NULL, _gloffset_GetPixelMapfv),
    NAME_FUNC_OFFSET( 3304, gl_dispatch_stub_272, gl_dispatch_stub_272, NULL, _gloffset_GetPixelMapuiv),
    NAME_FUNC_OFFSET( 3321, gl_dispatch_stub_273, gl_dispatch_stub_273, NULL, _gloffset_GetPixelMapusv),
    NAME_FUNC_OFFSET( 3338, gl_dispatch_stub_274, gl_dispatch_stub_274, NULL, _gloffset_GetPolygonStipple),
    NAME_FUNC_OFFSET( 3358, glGetString, glGetString, NULL, _gloffset_GetString),
    NAME_FUNC_OFFSET( 3370, glGetTexEnvfv, glGetTexEnvfv, NULL, _gloffset_GetTexEnvfv),
    NAME_FUNC_OFFSET( 3384, glGetTexEnviv, glGetTexEnviv, NULL, _gloffset_GetTexEnviv),
    NAME_FUNC_OFFSET( 3398, gl_dispatch_stub_278, gl_dispatch_stub_278, NULL, _gloffset_GetTexGendv),
    NAME_FUNC_OFFSET( 3412, glGetTexGenfvOES, glGetTexGenfvOES, NULL, _gloffset_GetTexGenfvOES),
    NAME_FUNC_OFFSET( 3429, glGetTexGenivOES, glGetTexGenivOES, NULL, _gloffset_GetTexGenivOES),
    NAME_FUNC_OFFSET( 3446, gl_dispatch_stub_281, gl_dispatch_stub_281, NULL, _gloffset_GetTexImage),
    NAME_FUNC_OFFSET( 3460, glGetTexParameterfv, glGetTexParameterfv, NULL, _gloffset_GetTexParameterfv),
    NAME_FUNC_OFFSET( 3480, glGetTexParameteriv, glGetTexParameteriv, NULL, _gloffset_GetTexParameteriv),
    NAME_FUNC_OFFSET( 3500, gl_dispatch_stub_284, gl_dispatch_stub_284, NULL, _gloffset_GetTexLevelParameterfv),
    NAME_FUNC_OFFSET( 3525, gl_dispatch_stub_285, gl_dispatch_stub_285, NULL, _gloffset_GetTexLevelParameteriv),
    NAME_FUNC_OFFSET( 3550, glIsEnabled, glIsEnabled, NULL, _gloffset_IsEnabled),
    NAME_FUNC_OFFSET( 3562, gl_dispatch_stub_287, gl_dispatch_stub_287, NULL, _gloffset_IsList),
    NAME_FUNC_OFFSET( 3571, gl_dispatch_stub_288, gl_dispatch_stub_288, NULL, _gloffset_DepthRange),
    NAME_FUNC_OFFSET( 3584, gl_dispatch_stub_289, gl_dispatch_stub_289, NULL, _gloffset_Frustum),
    NAME_FUNC_OFFSET( 3594, glLoadIdentity, glLoadIdentity, NULL, _gloffset_LoadIdentity),
    NAME_FUNC_OFFSET( 3609, glLoadMatrixf, glLoadMatrixf, NULL, _gloffset_LoadMatrixf),
    NAME_FUNC_OFFSET( 3623, gl_dispatch_stub_292, gl_dispatch_stub_292, NULL, _gloffset_LoadMatrixd),
    NAME_FUNC_OFFSET( 3637, glMatrixMode, glMatrixMode, NULL, _gloffset_MatrixMode),
    NAME_FUNC_OFFSET( 3650, glMultMatrixf, glMultMatrixf, NULL, _gloffset_MultMatrixf),
    NAME_FUNC_OFFSET( 3664, gl_dispatch_stub_295, gl_dispatch_stub_295, NULL, _gloffset_MultMatrixd),
    NAME_FUNC_OFFSET( 3678, gl_dispatch_stub_296, gl_dispatch_stub_296, NULL, _gloffset_Ortho),
    NAME_FUNC_OFFSET( 3686, glPopMatrix, glPopMatrix, NULL, _gloffset_PopMatrix),
    NAME_FUNC_OFFSET( 3698, glPushMatrix, glPushMatrix, NULL, _gloffset_PushMatrix),
    NAME_FUNC_OFFSET( 3711, gl_dispatch_stub_299, gl_dispatch_stub_299, NULL, _gloffset_Rotated),
    NAME_FUNC_OFFSET( 3721, glRotatef, glRotatef, NULL, _gloffset_Rotatef),
    NAME_FUNC_OFFSET( 3731, gl_dispatch_stub_301, gl_dispatch_stub_301, NULL, _gloffset_Scaled),
    NAME_FUNC_OFFSET( 3740, glScalef, glScalef, NULL, _gloffset_Scalef),
    NAME_FUNC_OFFSET( 3749, gl_dispatch_stub_303, gl_dispatch_stub_303, NULL, _gloffset_Translated),
    NAME_FUNC_OFFSET( 3762, glTranslatef, glTranslatef, NULL, _gloffset_Translatef),
    NAME_FUNC_OFFSET( 3775, glViewport, glViewport, NULL, _gloffset_Viewport),
    NAME_FUNC_OFFSET( 3786, gl_dispatch_stub_306, gl_dispatch_stub_306, NULL, _gloffset_ArrayElement),
    NAME_FUNC_OFFSET( 3801, glBindTexture, glBindTexture, NULL, _gloffset_BindTexture),
    NAME_FUNC_OFFSET( 3815, glColorPointer, glColorPointer, NULL, _gloffset_ColorPointer),
    NAME_FUNC_OFFSET( 3830, glDisableClientState, glDisableClientState, NULL, _gloffset_DisableClientState),
    NAME_FUNC_OFFSET( 3851, glDrawArrays, glDrawArrays, NULL, _gloffset_DrawArrays),
    NAME_FUNC_OFFSET( 3864, glDrawElements, glDrawElements, NULL, _gloffset_DrawElements),
    NAME_FUNC_OFFSET( 3879, gl_dispatch_stub_312, gl_dispatch_stub_312, NULL, _gloffset_EdgeFlagPointer),
    NAME_FUNC_OFFSET( 3897, glEnableClientState, glEnableClientState, NULL, _gloffset_EnableClientState),
    NAME_FUNC_OFFSET( 3917, gl_dispatch_stub_314, gl_dispatch_stub_314, NULL, _gloffset_IndexPointer),
    NAME_FUNC_OFFSET( 3932, gl_dispatch_stub_315, gl_dispatch_stub_315, NULL, _gloffset_Indexub),
    NAME_FUNC_OFFSET( 3942, gl_dispatch_stub_316, gl_dispatch_stub_316, NULL, _gloffset_Indexubv),
    NAME_FUNC_OFFSET( 3953, gl_dispatch_stub_317, gl_dispatch_stub_317, NULL, _gloffset_InterleavedArrays),
    NAME_FUNC_OFFSET( 3973, glNormalPointer, glNormalPointer, NULL, _gloffset_NormalPointer),
    NAME_FUNC_OFFSET( 3989, glPolygonOffset, glPolygonOffset, NULL, _gloffset_PolygonOffset),
    NAME_FUNC_OFFSET( 4005, glTexCoordPointer, glTexCoordPointer, NULL, _gloffset_TexCoordPointer),
    NAME_FUNC_OFFSET( 4023, glVertexPointer, glVertexPointer, NULL, _gloffset_VertexPointer),
    NAME_FUNC_OFFSET( 4039, gl_dispatch_stub_322, gl_dispatch_stub_322, NULL, _gloffset_AreTexturesResident),
    NAME_FUNC_OFFSET( 4061, gl_dispatch_stub_323, gl_dispatch_stub_323, NULL, _gloffset_CopyTexImage1D),
    NAME_FUNC_OFFSET( 4078, glCopyTexImage2D, glCopyTexImage2D, NULL, _gloffset_CopyTexImage2D),
    NAME_FUNC_OFFSET( 4095, gl_dispatch_stub_325, gl_dispatch_stub_325, NULL, _gloffset_CopyTexSubImage1D),
    NAME_FUNC_OFFSET( 4115, glCopyTexSubImage2D, glCopyTexSubImage2D, NULL, _gloffset_CopyTexSubImage2D),
    NAME_FUNC_OFFSET( 4135, glDeleteTextures, glDeleteTextures, NULL, _gloffset_DeleteTextures),
    NAME_FUNC_OFFSET( 4152, glGenTextures, glGenTextures, NULL, _gloffset_GenTextures),
    NAME_FUNC_OFFSET( 4166, glGetPointerv, glGetPointerv, NULL, _gloffset_GetPointerv),
    NAME_FUNC_OFFSET( 4180, glIsTexture, glIsTexture, NULL, _gloffset_IsTexture),
    NAME_FUNC_OFFSET( 4192, gl_dispatch_stub_331, gl_dispatch_stub_331, NULL, _gloffset_PrioritizeTextures),
    NAME_FUNC_OFFSET( 4213, gl_dispatch_stub_332, gl_dispatch_stub_332, NULL, _gloffset_TexSubImage1D),
    NAME_FUNC_OFFSET( 4229, glTexSubImage2D, glTexSubImage2D, NULL, _gloffset_TexSubImage2D),
    NAME_FUNC_OFFSET( 4245, gl_dispatch_stub_334, gl_dispatch_stub_334, NULL, _gloffset_PopClientAttrib),
    NAME_FUNC_OFFSET( 4263, gl_dispatch_stub_335, gl_dispatch_stub_335, NULL, _gloffset_PushClientAttrib),
    NAME_FUNC_OFFSET( 4282, gl_dispatch_stub_336, gl_dispatch_stub_336, NULL, _gloffset_BlendColor),
    NAME_FUNC_OFFSET( 4295, glBlendEquationOES, glBlendEquationOES, NULL, _gloffset_BlendEquationOES),
    NAME_FUNC_OFFSET( 4314, gl_dispatch_stub_338, gl_dispatch_stub_338, NULL, _gloffset_DrawRangeElements),
    NAME_FUNC_OFFSET( 4334, gl_dispatch_stub_339, gl_dispatch_stub_339, NULL, _gloffset_ColorTable),
    NAME_FUNC_OFFSET( 4347, gl_dispatch_stub_340, gl_dispatch_stub_340, NULL, _gloffset_ColorTableParameterfv),
    NAME_FUNC_OFFSET( 4371, gl_dispatch_stub_341, gl_dispatch_stub_341, NULL, _gloffset_ColorTableParameteriv),
    NAME_FUNC_OFFSET( 4395, gl_dispatch_stub_342, gl_dispatch_stub_342, NULL, _gloffset_CopyColorTable),
    NAME_FUNC_OFFSET( 4412, gl_dispatch_stub_343, gl_dispatch_stub_343, NULL, _gloffset_GetColorTable),
    NAME_FUNC_OFFSET( 4428, gl_dispatch_stub_344, gl_dispatch_stub_344, NULL, _gloffset_GetColorTableParameterfv),
    NAME_FUNC_OFFSET( 4455, gl_dispatch_stub_345, gl_dispatch_stub_345, NULL, _gloffset_GetColorTableParameteriv),
    NAME_FUNC_OFFSET( 4482, gl_dispatch_stub_346, gl_dispatch_stub_346, NULL, _gloffset_ColorSubTable),
    NAME_FUNC_OFFSET( 4498, gl_dispatch_stub_347, gl_dispatch_stub_347, NULL, _gloffset_CopyColorSubTable),
    NAME_FUNC_OFFSET( 4518, gl_dispatch_stub_348, gl_dispatch_stub_348, NULL, _gloffset_ConvolutionFilter1D),
    NAME_FUNC_OFFSET( 4540, gl_dispatch_stub_349, gl_dispatch_stub_349, NULL, _gloffset_ConvolutionFilter2D),
    NAME_FUNC_OFFSET( 4562, gl_dispatch_stub_350, gl_dispatch_stub_350, NULL, _gloffset_ConvolutionParameterf),
    NAME_FUNC_OFFSET( 4586, gl_dispatch_stub_351, gl_dispatch_stub_351, NULL, _gloffset_ConvolutionParameterfv),
    NAME_FUNC_OFFSET( 4611, gl_dispatch_stub_352, gl_dispatch_stub_352, NULL, _gloffset_ConvolutionParameteri),
    NAME_FUNC_OFFSET( 4635, gl_dispatch_stub_353, gl_dispatch_stub_353, NULL, _gloffset_ConvolutionParameteriv),
    NAME_FUNC_OFFSET( 4660, gl_dispatch_stub_354, gl_dispatch_stub_354, NULL, _gloffset_CopyConvolutionFilter1D),
    NAME_FUNC_OFFSET( 4686, gl_dispatch_stub_355, gl_dispatch_stub_355, NULL, _gloffset_CopyConvolutionFilter2D),
    NAME_FUNC_OFFSET( 4712, gl_dispatch_stub_356, gl_dispatch_stub_356, NULL, _gloffset_GetConvolutionFilter),
    NAME_FUNC_OFFSET( 4735, gl_dispatch_stub_357, gl_dispatch_stub_357, NULL, _gloffset_GetConvolutionParameterfv),
    NAME_FUNC_OFFSET( 4763, gl_dispatch_stub_358, gl_dispatch_stub_358, NULL, _gloffset_GetConvolutionParameteriv),
    NAME_FUNC_OFFSET( 4791, gl_dispatch_stub_359, gl_dispatch_stub_359, NULL, _gloffset_GetSeparableFilter),
    NAME_FUNC_OFFSET( 4812, gl_dispatch_stub_360, gl_dispatch_stub_360, NULL, _gloffset_SeparableFilter2D),
    NAME_FUNC_OFFSET( 4832, gl_dispatch_stub_361, gl_dispatch_stub_361, NULL, _gloffset_GetHistogram),
    NAME_FUNC_OFFSET( 4847, gl_dispatch_stub_362, gl_dispatch_stub_362, NULL, _gloffset_GetHistogramParameterfv),
    NAME_FUNC_OFFSET( 4873, gl_dispatch_stub_363, gl_dispatch_stub_363, NULL, _gloffset_GetHistogramParameteriv),
    NAME_FUNC_OFFSET( 4899, gl_dispatch_stub_364, gl_dispatch_stub_364, NULL, _gloffset_GetMinmax),
    NAME_FUNC_OFFSET( 4911, gl_dispatch_stub_365, gl_dispatch_stub_365, NULL, _gloffset_GetMinmaxParameterfv),
    NAME_FUNC_OFFSET( 4934, gl_dispatch_stub_366, gl_dispatch_stub_366, NULL, _gloffset_GetMinmaxParameteriv),
    NAME_FUNC_OFFSET( 4957, gl_dispatch_stub_367, gl_dispatch_stub_367, NULL, _gloffset_Histogram),
    NAME_FUNC_OFFSET( 4969, gl_dispatch_stub_368, gl_dispatch_stub_368, NULL, _gloffset_Minmax),
    NAME_FUNC_OFFSET( 4978, gl_dispatch_stub_369, gl_dispatch_stub_369, NULL, _gloffset_ResetHistogram),
    NAME_FUNC_OFFSET( 4995, gl_dispatch_stub_370, gl_dispatch_stub_370, NULL, _gloffset_ResetMinmax),
    NAME_FUNC_OFFSET( 5009, gl_dispatch_stub_371, gl_dispatch_stub_371, NULL, _gloffset_TexImage3D),
    NAME_FUNC_OFFSET( 5022, gl_dispatch_stub_372, gl_dispatch_stub_372, NULL, _gloffset_TexSubImage3D),
    NAME_FUNC_OFFSET( 5038, gl_dispatch_stub_373, gl_dispatch_stub_373, NULL, _gloffset_CopyTexSubImage3D),
    NAME_FUNC_OFFSET( 5058, glActiveTexture, glActiveTexture, NULL, _gloffset_ActiveTexture),
    NAME_FUNC_OFFSET( 5074, glClientActiveTexture, glClientActiveTexture, NULL, _gloffset_ClientActiveTexture),
    NAME_FUNC_OFFSET( 5096, gl_dispatch_stub_376, gl_dispatch_stub_376, NULL, _gloffset_MultiTexCoord1dARB),
    NAME_FUNC_OFFSET( 5117, gl_dispatch_stub_377, gl_dispatch_stub_377, NULL, _gloffset_MultiTexCoord1dvARB),
    NAME_FUNC_OFFSET( 5139, gl_dispatch_stub_378, gl_dispatch_stub_378, NULL, _gloffset_MultiTexCoord1fARB),
    NAME_FUNC_OFFSET( 5160, gl_dispatch_stub_379, gl_dispatch_stub_379, NULL, _gloffset_MultiTexCoord1fvARB),
    NAME_FUNC_OFFSET( 5182, gl_dispatch_stub_380, gl_dispatch_stub_380, NULL, _gloffset_MultiTexCoord1iARB),
    NAME_FUNC_OFFSET( 5203, gl_dispatch_stub_381, gl_dispatch_stub_381, NULL, _gloffset_MultiTexCoord1ivARB),
    NAME_FUNC_OFFSET( 5225, gl_dispatch_stub_382, gl_dispatch_stub_382, NULL, _gloffset_MultiTexCoord1sARB),
    NAME_FUNC_OFFSET( 5246, gl_dispatch_stub_383, gl_dispatch_stub_383, NULL, _gloffset_MultiTexCoord1svARB),
    NAME_FUNC_OFFSET( 5268, gl_dispatch_stub_384, gl_dispatch_stub_384, NULL, _gloffset_MultiTexCoord2dARB),
    NAME_FUNC_OFFSET( 5289, gl_dispatch_stub_385, gl_dispatch_stub_385, NULL, _gloffset_MultiTexCoord2dvARB),
    NAME_FUNC_OFFSET( 5311, gl_dispatch_stub_386, gl_dispatch_stub_386, NULL, _gloffset_MultiTexCoord2fARB),
    NAME_FUNC_OFFSET( 5332, gl_dispatch_stub_387, gl_dispatch_stub_387, NULL, _gloffset_MultiTexCoord2fvARB),
    NAME_FUNC_OFFSET( 5354, gl_dispatch_stub_388, gl_dispatch_stub_388, NULL, _gloffset_MultiTexCoord2iARB),
    NAME_FUNC_OFFSET( 5375, gl_dispatch_stub_389, gl_dispatch_stub_389, NULL, _gloffset_MultiTexCoord2ivARB),
    NAME_FUNC_OFFSET( 5397, gl_dispatch_stub_390, gl_dispatch_stub_390, NULL, _gloffset_MultiTexCoord2sARB),
    NAME_FUNC_OFFSET( 5418, gl_dispatch_stub_391, gl_dispatch_stub_391, NULL, _gloffset_MultiTexCoord2svARB),
    NAME_FUNC_OFFSET( 5440, gl_dispatch_stub_392, gl_dispatch_stub_392, NULL, _gloffset_MultiTexCoord3dARB),
    NAME_FUNC_OFFSET( 5461, gl_dispatch_stub_393, gl_dispatch_stub_393, NULL, _gloffset_MultiTexCoord3dvARB),
    NAME_FUNC_OFFSET( 5483, gl_dispatch_stub_394, gl_dispatch_stub_394, NULL, _gloffset_MultiTexCoord3fARB),
    NAME_FUNC_OFFSET( 5504, gl_dispatch_stub_395, gl_dispatch_stub_395, NULL, _gloffset_MultiTexCoord3fvARB),
    NAME_FUNC_OFFSET( 5526, gl_dispatch_stub_396, gl_dispatch_stub_396, NULL, _gloffset_MultiTexCoord3iARB),
    NAME_FUNC_OFFSET( 5547, gl_dispatch_stub_397, gl_dispatch_stub_397, NULL, _gloffset_MultiTexCoord3ivARB),
    NAME_FUNC_OFFSET( 5569, gl_dispatch_stub_398, gl_dispatch_stub_398, NULL, _gloffset_MultiTexCoord3sARB),
    NAME_FUNC_OFFSET( 5590, gl_dispatch_stub_399, gl_dispatch_stub_399, NULL, _gloffset_MultiTexCoord3svARB),
    NAME_FUNC_OFFSET( 5612, gl_dispatch_stub_400, gl_dispatch_stub_400, NULL, _gloffset_MultiTexCoord4dARB),
    NAME_FUNC_OFFSET( 5633, gl_dispatch_stub_401, gl_dispatch_stub_401, NULL, _gloffset_MultiTexCoord4dvARB),
    NAME_FUNC_OFFSET( 5655, glMultiTexCoord4f, glMultiTexCoord4f, NULL, _gloffset_MultiTexCoord4f),
    NAME_FUNC_OFFSET( 5673, gl_dispatch_stub_403, gl_dispatch_stub_403, NULL, _gloffset_MultiTexCoord4fvARB),
    NAME_FUNC_OFFSET( 5695, gl_dispatch_stub_404, gl_dispatch_stub_404, NULL, _gloffset_MultiTexCoord4iARB),
    NAME_FUNC_OFFSET( 5716, gl_dispatch_stub_405, gl_dispatch_stub_405, NULL, _gloffset_MultiTexCoord4ivARB),
    NAME_FUNC_OFFSET( 5738, gl_dispatch_stub_406, gl_dispatch_stub_406, NULL, _gloffset_MultiTexCoord4sARB),
    NAME_FUNC_OFFSET( 5759, gl_dispatch_stub_407, gl_dispatch_stub_407, NULL, _gloffset_MultiTexCoord4svARB),
    NAME_FUNC_OFFSET( 5781, glBlendEquationSeparateOES, glBlendEquationSeparateOES, NULL, _gloffset_BlendEquationSeparateOES),
    NAME_FUNC_OFFSET( 5808, glBlendFuncSeparateOES, glBlendFuncSeparateOES, NULL, _gloffset_BlendFuncSeparateOES),
    NAME_FUNC_OFFSET( 5831, glDrawTexfOES, glDrawTexfOES, NULL, _gloffset_DrawTexfOES),
    NAME_FUNC_OFFSET( 5845, glDrawTexfvOES, glDrawTexfvOES, NULL, _gloffset_DrawTexfvOES),
    NAME_FUNC_OFFSET( 5860, glDrawTexiOES, glDrawTexiOES, NULL, _gloffset_DrawTexiOES),
    NAME_FUNC_OFFSET( 5874, glDrawTexivOES, glDrawTexivOES, NULL, _gloffset_DrawTexivOES),
    NAME_FUNC_OFFSET( 5889, glDrawTexsOES, glDrawTexsOES, NULL, _gloffset_DrawTexsOES),
    NAME_FUNC_OFFSET( 5903, glDrawTexsvOES, glDrawTexsvOES, NULL, _gloffset_DrawTexsvOES),
    NAME_FUNC_OFFSET( 5918, glDrawTexxOES, glDrawTexxOES, NULL, _gloffset_DrawTexxOES),
    NAME_FUNC_OFFSET( 5932, glDrawTexxvOES, glDrawTexxvOES, NULL, _gloffset_DrawTexxvOES),
    NAME_FUNC_OFFSET( 5947, glBindFramebufferOES, glBindFramebufferOES, NULL, _gloffset_BindFramebufferOES),
    NAME_FUNC_OFFSET( 5968, glBindRenderbufferOES, glBindRenderbufferOES, NULL, _gloffset_BindRenderbufferOES),
    NAME_FUNC_OFFSET( 5990, glCheckFramebufferStatusOES, glCheckFramebufferStatusOES, NULL, _gloffset_CheckFramebufferStatusOES),
    NAME_FUNC_OFFSET( 6018, glDeleteFramebuffersOES, glDeleteFramebuffersOES, NULL, _gloffset_DeleteFramebuffersOES),
    NAME_FUNC_OFFSET( 6042, glDeleteRenderbuffersOES, glDeleteRenderbuffersOES, NULL, _gloffset_DeleteRenderbuffersOES),
    NAME_FUNC_OFFSET( 6067, glFramebufferRenderbufferOES, glFramebufferRenderbufferOES, NULL, _gloffset_FramebufferRenderbufferOES),
    NAME_FUNC_OFFSET( 6096, glFramebufferTexture2DOES, glFramebufferTexture2DOES, NULL, _gloffset_FramebufferTexture2DOES),
    NAME_FUNC_OFFSET( 6122, glGenFramebuffersOES, glGenFramebuffersOES, NULL, _gloffset_GenFramebuffersOES),
    NAME_FUNC_OFFSET( 6143, glGenRenderbuffersOES, glGenRenderbuffersOES, NULL, _gloffset_GenRenderbuffersOES),
    NAME_FUNC_OFFSET( 6165, glGenerateMipmapOES, glGenerateMipmapOES, NULL, _gloffset_GenerateMipmapOES),
    NAME_FUNC_OFFSET( 6185, glGetFramebufferAttachmentParameterivOES, glGetFramebufferAttachmentParameterivOES, NULL, _gloffset_GetFramebufferAttachmentParameterivOES),
    NAME_FUNC_OFFSET( 6226, glGetRenderbufferParameterivOES, glGetRenderbufferParameterivOES, NULL, _gloffset_GetRenderbufferParameterivOES),
    NAME_FUNC_OFFSET( 6258, glIsFramebufferOES, glIsFramebufferOES, NULL, _gloffset_IsFramebufferOES),
    NAME_FUNC_OFFSET( 6277, glIsRenderbufferOES, glIsRenderbufferOES, NULL, _gloffset_IsRenderbufferOES),
    NAME_FUNC_OFFSET( 6297, glRenderbufferStorageOES, glRenderbufferStorageOES, NULL, _gloffset_RenderbufferStorageOES),
    NAME_FUNC_OFFSET( 6322, glPointSizePointerOES, glPointSizePointerOES, NULL, _gloffset_PointSizePointerOES),
    NAME_FUNC_OFFSET( 6344, glQueryMatrixxOES, glQueryMatrixxOES, NULL, _gloffset_QueryMatrixxOES),
    NAME_FUNC_OFFSET( 6362, glGetTexGenxvOES, glGetTexGenxvOES, NULL, _gloffset_GetTexGenxvOES),
    NAME_FUNC_OFFSET( 6379, glTexGenxOES, glTexGenxOES, NULL, _gloffset_TexGenxOES),
    NAME_FUNC_OFFSET( 6392, glTexGenxvOES, glTexGenxvOES, NULL, _gloffset_TexGenxvOES),
    NAME_FUNC_OFFSET( 6406, glEGLImageTargetRenderbufferStorageOES, glEGLImageTargetRenderbufferStorageOES, NULL, _gloffset_EGLImageTargetRenderbufferStorageOES),
    NAME_FUNC_OFFSET( 6445, glEGLImageTargetTexture2DOES, glEGLImageTargetTexture2DOES, NULL, _gloffset_EGLImageTargetTexture2DOES),
    NAME_FUNC_OFFSET( 6474, glGetBufferPointervOES, glGetBufferPointervOES, NULL, _gloffset_GetBufferPointervOES),
    NAME_FUNC_OFFSET( 6497, glMapBufferOES, glMapBufferOES, NULL, _gloffset_MapBufferOES),
    NAME_FUNC_OFFSET( 6512, glUnmapBufferOES, glUnmapBufferOES, NULL, _gloffset_UnmapBufferOES),
    NAME_FUNC_OFFSET( 6529, gl_dispatch_stub_443, gl_dispatch_stub_443, NULL, _gloffset_BindVertexArrayAPPLE),
    NAME_FUNC_OFFSET( 6552, gl_dispatch_stub_444, gl_dispatch_stub_444, NULL, _gloffset_DeleteVertexArraysAPPLE),
    NAME_FUNC_OFFSET( 6578, gl_dispatch_stub_445, gl_dispatch_stub_445, NULL, _gloffset_GenVertexArraysAPPLE),
    NAME_FUNC_OFFSET( 6601, gl_dispatch_stub_446, gl_dispatch_stub_446, NULL, _gloffset_IsVertexArrayAPPLE),
    NAME_FUNC_OFFSET( 6622, glCompressedTexImage2D, glCompressedTexImage2D, NULL, _gloffset_CompressedTexImage2D),
    NAME_FUNC_OFFSET( 6645, glCompressedTexSubImage2D, glCompressedTexSubImage2D, NULL, _gloffset_CompressedTexSubImage2D),
    NAME_FUNC_OFFSET( 6671, glSampleCoverage, glSampleCoverage, NULL, _gloffset_SampleCoverage),
    NAME_FUNC_OFFSET( 6688, glBindBuffer, glBindBuffer, NULL, _gloffset_BindBuffer),
    NAME_FUNC_OFFSET( 6701, glBufferData, glBufferData, NULL, _gloffset_BufferData),
    NAME_FUNC_OFFSET( 6714, glBufferSubData, glBufferSubData, NULL, _gloffset_BufferSubData),
    NAME_FUNC_OFFSET( 6730, glDeleteBuffers, glDeleteBuffers, NULL, _gloffset_DeleteBuffers),
    NAME_FUNC_OFFSET( 6746, glGenBuffers, glGenBuffers, NULL, _gloffset_GenBuffers),
    NAME_FUNC_OFFSET( 6759, glGetBufferParameteriv, glGetBufferParameteriv, NULL, _gloffset_GetBufferParameteriv),
    NAME_FUNC_OFFSET( 6782, glIsBuffer, glIsBuffer, NULL, _gloffset_IsBuffer),
    NAME_FUNC_OFFSET( 6793, glAlphaFuncx, glAlphaFuncx, NULL, _gloffset_AlphaFuncx),
    NAME_FUNC_OFFSET( 6806, glClearColorx, glClearColorx, NULL, _gloffset_ClearColorx),
    NAME_FUNC_OFFSET( 6820, glClearDepthf, glClearDepthf, NULL, _gloffset_ClearDepthf),
    NAME_FUNC_OFFSET( 6834, glClearDepthx, glClearDepthx, NULL, _gloffset_ClearDepthx),
    NAME_FUNC_OFFSET( 6848, glColor4x, glColor4x, NULL, _gloffset_Color4x),
    NAME_FUNC_OFFSET( 6858, glDepthRangef, glDepthRangef, NULL, _gloffset_DepthRangef),
    NAME_FUNC_OFFSET( 6872, glDepthRangex, glDepthRangex, NULL, _gloffset_DepthRangex),
    NAME_FUNC_OFFSET( 6886, glFogx, glFogx, NULL, _gloffset_Fogx),
    NAME_FUNC_OFFSET( 6893, glFogxv, glFogxv, NULL, _gloffset_Fogxv),
    NAME_FUNC_OFFSET( 6901, glFrustumf, glFrustumf, NULL, _gloffset_Frustumf),
    NAME_FUNC_OFFSET( 6912, glFrustumx, glFrustumx, NULL, _gloffset_Frustumx),
    NAME_FUNC_OFFSET( 6923, glLightModelx, glLightModelx, NULL, _gloffset_LightModelx),
    NAME_FUNC_OFFSET( 6937, glLightModelxv, glLightModelxv, NULL, _gloffset_LightModelxv),
    NAME_FUNC_OFFSET( 6952, glLightx, glLightx, NULL, _gloffset_Lightx),
    NAME_FUNC_OFFSET( 6961, glLightxv, glLightxv, NULL, _gloffset_Lightxv),
    NAME_FUNC_OFFSET( 6971, glLineWidthx, glLineWidthx, NULL, _gloffset_LineWidthx),
    NAME_FUNC_OFFSET( 6984, glLoadMatrixx, glLoadMatrixx, NULL, _gloffset_LoadMatrixx),
    NAME_FUNC_OFFSET( 6998, glMaterialx, glMaterialx, NULL, _gloffset_Materialx),
    NAME_FUNC_OFFSET( 7010, glMaterialxv, glMaterialxv, NULL, _gloffset_Materialxv),
    NAME_FUNC_OFFSET( 7023, glMultMatrixx, glMultMatrixx, NULL, _gloffset_MultMatrixx),
    NAME_FUNC_OFFSET( 7037, glMultiTexCoord4x, glMultiTexCoord4x, NULL, _gloffset_MultiTexCoord4x),
    NAME_FUNC_OFFSET( 7055, glNormal3x, glNormal3x, NULL, _gloffset_Normal3x),
    NAME_FUNC_OFFSET( 7066, glOrthof, glOrthof, NULL, _gloffset_Orthof),
    NAME_FUNC_OFFSET( 7075, glOrthox, glOrthox, NULL, _gloffset_Orthox),
    NAME_FUNC_OFFSET( 7084, glPointSizex, glPointSizex, NULL, _gloffset_PointSizex),
    NAME_FUNC_OFFSET( 7097, glPolygonOffsetx, glPolygonOffsetx, NULL, _gloffset_PolygonOffsetx),
    NAME_FUNC_OFFSET( 7114, glRotatex, glRotatex, NULL, _gloffset_Rotatex),
    NAME_FUNC_OFFSET( 7124, glSampleCoveragex, glSampleCoveragex, NULL, _gloffset_SampleCoveragex),
    NAME_FUNC_OFFSET( 7142, glScalex, glScalex, NULL, _gloffset_Scalex),
    NAME_FUNC_OFFSET( 7151, glTexEnvx, glTexEnvx, NULL, _gloffset_TexEnvx),
    NAME_FUNC_OFFSET( 7161, glTexEnvxv, glTexEnvxv, NULL, _gloffset_TexEnvxv),
    NAME_FUNC_OFFSET( 7172, glTexParameterx, glTexParameterx, NULL, _gloffset_TexParameterx),
    NAME_FUNC_OFFSET( 7188, glTranslatex, glTranslatex, NULL, _gloffset_Translatex),
    NAME_FUNC_OFFSET( 7201, glClipPlanef, glClipPlanef, NULL, _gloffset_ClipPlanef),
    NAME_FUNC_OFFSET( 7214, glClipPlanex, glClipPlanex, NULL, _gloffset_ClipPlanex),
    NAME_FUNC_OFFSET( 7227, glGetClipPlanef, glGetClipPlanef, NULL, _gloffset_GetClipPlanef),
    NAME_FUNC_OFFSET( 7243, glGetClipPlanex, glGetClipPlanex, NULL, _gloffset_GetClipPlanex),
    NAME_FUNC_OFFSET( 7259, glGetFixedv, glGetFixedv, NULL, _gloffset_GetFixedv),
    NAME_FUNC_OFFSET( 7271, glGetLightxv, glGetLightxv, NULL, _gloffset_GetLightxv),
    NAME_FUNC_OFFSET( 7284, glGetMaterialxv, glGetMaterialxv, NULL, _gloffset_GetMaterialxv),
    NAME_FUNC_OFFSET( 7300, glGetTexEnvxv, glGetTexEnvxv, NULL, _gloffset_GetTexEnvxv),
    NAME_FUNC_OFFSET( 7314, glGetTexParameterxv, glGetTexParameterxv, NULL, _gloffset_GetTexParameterxv),
    NAME_FUNC_OFFSET( 7334, glPointParameterx, glPointParameterx, NULL, _gloffset_PointParameterx),
    NAME_FUNC_OFFSET( 7352, glPointParameterxv, glPointParameterxv, NULL, _gloffset_PointParameterxv),
    NAME_FUNC_OFFSET( 7371, glTexParameterxv, glTexParameterxv, NULL, _gloffset_TexParameterxv),
    NAME_FUNC_OFFSET( 7388, glPointParameterf, glPointParameterf, NULL, _gloffset_PointParameterf),
    NAME_FUNC_OFFSET( 7406, glPointParameterfv, glPointParameterfv, NULL, _gloffset_PointParameterfv),
    NAME_FUNC_OFFSET( 7425, glTexGenfOES, glTexGenfOES, NULL, _gloffset_TexGenfOES),
    NAME_FUNC_OFFSET( 7435, glTexGenfvOES, glTexGenfvOES, NULL, _gloffset_TexGenfvOES),
    NAME_FUNC_OFFSET( 7446, glTexGeniOES, glTexGeniOES, NULL, _gloffset_TexGeniOES),
    NAME_FUNC_OFFSET( 7456, glTexGenivOES, glTexGenivOES, NULL, _gloffset_TexGenivOES),
    NAME_FUNC_OFFSET( 7467, glGetTexGenfvOES, glGetTexGenfvOES, NULL, _gloffset_GetTexGenfvOES),
    NAME_FUNC_OFFSET( 7481, glGetTexGenivOES, glGetTexGenivOES, NULL, _gloffset_GetTexGenivOES),
    NAME_FUNC_OFFSET( 7495, glBlendEquationOES, glBlendEquationOES, NULL, _gloffset_BlendEquationOES),
    NAME_FUNC_OFFSET( 7511, glActiveTexture, glActiveTexture, NULL, _gloffset_ActiveTexture),
    NAME_FUNC_OFFSET( 7530, glClientActiveTexture, glClientActiveTexture, NULL, _gloffset_ClientActiveTexture),
    NAME_FUNC_OFFSET( 7555, glMultiTexCoord4f, glMultiTexCoord4f, NULL, _gloffset_MultiTexCoord4f),
    NAME_FUNC_OFFSET( 7576, glAlphaFuncx, glAlphaFuncx, NULL, _gloffset_AlphaFuncx),
    NAME_FUNC_OFFSET( 7592, glClearColorx, glClearColorx, NULL, _gloffset_ClearColorx),
    NAME_FUNC_OFFSET( 7609, glClearDepthf, glClearDepthf, NULL, _gloffset_ClearDepthf),
    NAME_FUNC_OFFSET( 7626, glClearDepthx, glClearDepthx, NULL, _gloffset_ClearDepthx),
    NAME_FUNC_OFFSET( 7643, glColor4x, glColor4x, NULL, _gloffset_Color4x),
    NAME_FUNC_OFFSET( 7656, glDepthRangef, glDepthRangef, NULL, _gloffset_DepthRangef),
    NAME_FUNC_OFFSET( 7673, glDepthRangex, glDepthRangex, NULL, _gloffset_DepthRangex),
    NAME_FUNC_OFFSET( 7690, glFogx, glFogx, NULL, _gloffset_Fogx),
    NAME_FUNC_OFFSET( 7700, glFogxv, glFogxv, NULL, _gloffset_Fogxv),
    NAME_FUNC_OFFSET( 7711, glFrustumf, glFrustumf, NULL, _gloffset_Frustumf),
    NAME_FUNC_OFFSET( 7725, glFrustumx, glFrustumx, NULL, _gloffset_Frustumx),
    NAME_FUNC_OFFSET( 7739, glLightModelx, glLightModelx, NULL, _gloffset_LightModelx),
    NAME_FUNC_OFFSET( 7756, glLightModelxv, glLightModelxv, NULL, _gloffset_LightModelxv),
    NAME_FUNC_OFFSET( 7774, glLightx, glLightx, NULL, _gloffset_Lightx),
    NAME_FUNC_OFFSET( 7786, glLightxv, glLightxv, NULL, _gloffset_Lightxv),
    NAME_FUNC_OFFSET( 7799, glLineWidthx, glLineWidthx, NULL, _gloffset_LineWidthx),
    NAME_FUNC_OFFSET( 7815, glLoadMatrixx, glLoadMatrixx, NULL, _gloffset_LoadMatrixx),
    NAME_FUNC_OFFSET( 7832, glMaterialx, glMaterialx, NULL, _gloffset_Materialx),
    NAME_FUNC_OFFSET( 7847, glMaterialxv, glMaterialxv, NULL, _gloffset_Materialxv),
    NAME_FUNC_OFFSET( 7863, glMultMatrixx, glMultMatrixx, NULL, _gloffset_MultMatrixx),
    NAME_FUNC_OFFSET( 7880, glMultiTexCoord4x, glMultiTexCoord4x, NULL, _gloffset_MultiTexCoord4x),
    NAME_FUNC_OFFSET( 7901, glNormal3x, glNormal3x, NULL, _gloffset_Normal3x),
    NAME_FUNC_OFFSET( 7915, glOrthof, glOrthof, NULL, _gloffset_Orthof),
    NAME_FUNC_OFFSET( 7927, glOrthox, glOrthox, NULL, _gloffset_Orthox),
    NAME_FUNC_OFFSET( 7939, glPointSizex, glPointSizex, NULL, _gloffset_PointSizex),
    NAME_FUNC_OFFSET( 7955, glPolygonOffsetx, glPolygonOffsetx, NULL, _gloffset_PolygonOffsetx),
    NAME_FUNC_OFFSET( 7975, glRotatex, glRotatex, NULL, _gloffset_Rotatex),
    NAME_FUNC_OFFSET( 7988, glSampleCoveragex, glSampleCoveragex, NULL, _gloffset_SampleCoveragex),
    NAME_FUNC_OFFSET( 8009, glScalex, glScalex, NULL, _gloffset_Scalex),
    NAME_FUNC_OFFSET( 8021, glTexEnvx, glTexEnvx, NULL, _gloffset_TexEnvx),
    NAME_FUNC_OFFSET( 8034, glTexEnvxv, glTexEnvxv, NULL, _gloffset_TexEnvxv),
    NAME_FUNC_OFFSET( 8048, glTexParameterx, glTexParameterx, NULL, _gloffset_TexParameterx),
    NAME_FUNC_OFFSET( 8067, glTranslatex, glTranslatex, NULL, _gloffset_Translatex),
    NAME_FUNC_OFFSET( 8083, glClipPlanef, glClipPlanef, NULL, _gloffset_ClipPlanef),
    NAME_FUNC_OFFSET( 8099, glClipPlanex, glClipPlanex, NULL, _gloffset_ClipPlanex),
    NAME_FUNC_OFFSET( 8115, glGetClipPlanef, glGetClipPlanef, NULL, _gloffset_GetClipPlanef),
    NAME_FUNC_OFFSET( 8134, glGetClipPlanex, glGetClipPlanex, NULL, _gloffset_GetClipPlanex),
    NAME_FUNC_OFFSET( 8153, glGetFixedv, glGetFixedv, NULL, _gloffset_GetFixedv),
    NAME_FUNC_OFFSET( 8168, glGetLightxv, glGetLightxv, NULL, _gloffset_GetLightxv),
    NAME_FUNC_OFFSET( 8184, glGetMaterialxv, glGetMaterialxv, NULL, _gloffset_GetMaterialxv),
    NAME_FUNC_OFFSET( 8203, glGetTexEnvxv, glGetTexEnvxv, NULL, _gloffset_GetTexEnvxv),
    NAME_FUNC_OFFSET( 8220, glGetTexParameterxv, glGetTexParameterxv, NULL, _gloffset_GetTexParameterxv),
    NAME_FUNC_OFFSET( 8243, glPointParameterx, glPointParameterx, NULL, _gloffset_PointParameterx),
    NAME_FUNC_OFFSET( 8264, glPointParameterxv, glPointParameterxv, NULL, _gloffset_PointParameterxv),
    NAME_FUNC_OFFSET( 8286, glTexParameterxv, glTexParameterxv, NULL, _gloffset_TexParameterxv),
    NAME_FUNC_OFFSET(-1, NULL, NULL, NULL, 0)
};

#undef NAME_FUNC_OFFSET
