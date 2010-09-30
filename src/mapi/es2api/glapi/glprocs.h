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
    "glTexGenf\0"
    "glTexGenfv\0"
    "glTexGeni\0"
    "glTexGeniv\0"
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
    "glGetTexGenfv\0"
    "glGetTexGeniv\0"
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
    "glBlendEquation\0"
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
    "glTexImage3DOES\0"
    "glTexSubImage3DOES\0"
    "glCopyTexSubImage3DOES\0"
    "glActiveTexture\0"
    "glClientActiveTextureARB\0"
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
    "glMultiTexCoord4fARB\0"
    "glMultiTexCoord4fvARB\0"
    "glMultiTexCoord4iARB\0"
    "glMultiTexCoord4ivARB\0"
    "glMultiTexCoord4sARB\0"
    "glMultiTexCoord4svARB\0"
    "glGetBufferPointervOES\0"
    "glMapBufferOES\0"
    "glUnmapBufferOES\0"
    "glCompressedTexImage3DOES\0"
    "glCompressedTexSubImage3DOES\0"
    "glFramebufferTexture3DOES\0"
    "glGetProgramBinaryOES\0"
    "glProgramBinaryOES\0"
    "glMultiDrawArraysEXT\0"
    "glMultiDrawElementsEXT\0"
    "glBindVertexArrayAPPLE\0"
    "glDeleteVertexArraysAPPLE\0"
    "glGenVertexArraysAPPLE\0"
    "glIsVertexArrayAPPLE\0"
    "glEGLImageTargetRenderbufferStorageOES\0"
    "glEGLImageTargetTexture2DOES\0"
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
    "glAttachShader\0"
    "glBindAttribLocation\0"
    "glBlendEquationSeparate\0"
    "glCompileShader\0"
    "glCreateProgram\0"
    "glCreateShader\0"
    "glDeleteProgram\0"
    "glDeleteShader\0"
    "glDetachShader\0"
    "glDisableVertexAttribArray\0"
    "glEnableVertexAttribArray\0"
    "glGetActiveAttrib\0"
    "glGetActiveUniform\0"
    "glGetAttachedShaders\0"
    "glGetAttribLocation\0"
    "glGetProgramInfoLog\0"
    "glGetProgramiv\0"
    "glGetShaderInfoLog\0"
    "glGetShaderSource\0"
    "glGetShaderiv\0"
    "glGetUniformLocation\0"
    "glGetUniformfv\0"
    "glGetUniformiv\0"
    "glGetVertexAttribPointerv\0"
    "glGetVertexAttribfv\0"
    "glGetVertexAttribiv\0"
    "glIsProgram\0"
    "glIsShader\0"
    "glLinkProgram\0"
    "glShaderSource\0"
    "glStencilFuncSeparate\0"
    "glStencilMaskSeparate\0"
    "glStencilOpSeparate\0"
    "glUniform1f\0"
    "glUniform1fv\0"
    "glUniform1i\0"
    "glUniform1iv\0"
    "glUniform2f\0"
    "glUniform2fv\0"
    "glUniform2i\0"
    "glUniform2iv\0"
    "glUniform3f\0"
    "glUniform3fv\0"
    "glUniform3i\0"
    "glUniform3iv\0"
    "glUniform4f\0"
    "glUniform4fv\0"
    "glUniform4i\0"
    "glUniform4iv\0"
    "glUniformMatrix2fv\0"
    "glUniformMatrix3fv\0"
    "glUniformMatrix4fv\0"
    "glUseProgram\0"
    "glValidateProgram\0"
    "glVertexAttrib1f\0"
    "glVertexAttrib1fv\0"
    "glVertexAttrib2f\0"
    "glVertexAttrib2fv\0"
    "glVertexAttrib3f\0"
    "glVertexAttrib3fv\0"
    "glVertexAttrib4f\0"
    "glVertexAttrib4fv\0"
    "glVertexAttribPointer\0"
    "glBlendFuncSeparate\0"
    "glBindFramebuffer\0"
    "glBindRenderbuffer\0"
    "glCheckFramebufferStatus\0"
    "glClearDepthf\0"
    "glDeleteFramebuffers\0"
    "glDeleteRenderbuffers\0"
    "glDepthRangef\0"
    "glFramebufferRenderbuffer\0"
    "glFramebufferTexture2D\0"
    "glGenFramebuffers\0"
    "glGenRenderbuffers\0"
    "glGenerateMipmap\0"
    "glGetFramebufferAttachmentParameteriv\0"
    "glGetRenderbufferParameteriv\0"
    "glGetShaderPrecisionFormat\0"
    "glIsFramebuffer\0"
    "glIsRenderbuffer\0"
    "glReleaseShaderCompiler\0"
    "glRenderbufferStorage\0"
    "glShaderBinary\0"
    "glTexImage3D\0"
    "glTexSubImage3D\0"
    "glCopyTexSubImage3D\0"
    "glActiveTextureARB\0"
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
#define gl_dispatch_stub_29 mgl_dispatch_stub_29
#define gl_dispatch_stub_30 mgl_dispatch_stub_30
#define gl_dispatch_stub_31 mgl_dispatch_stub_31
#define gl_dispatch_stub_32 mgl_dispatch_stub_32
#define gl_dispatch_stub_33 mgl_dispatch_stub_33
#define gl_dispatch_stub_34 mgl_dispatch_stub_34
#define gl_dispatch_stub_35 mgl_dispatch_stub_35
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
#define gl_dispatch_stub_56 mgl_dispatch_stub_56
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
#define gl_dispatch_stub_153 mgl_dispatch_stub_153
#define gl_dispatch_stub_154 mgl_dispatch_stub_154
#define gl_dispatch_stub_155 mgl_dispatch_stub_155
#define gl_dispatch_stub_156 mgl_dispatch_stub_156
#define gl_dispatch_stub_159 mgl_dispatch_stub_159
#define gl_dispatch_stub_160 mgl_dispatch_stub_160
#define gl_dispatch_stub_161 mgl_dispatch_stub_161
#define gl_dispatch_stub_162 mgl_dispatch_stub_162
#define gl_dispatch_stub_163 mgl_dispatch_stub_163
#define gl_dispatch_stub_164 mgl_dispatch_stub_164
#define gl_dispatch_stub_165 mgl_dispatch_stub_165
#define gl_dispatch_stub_166 mgl_dispatch_stub_166
#define gl_dispatch_stub_167 mgl_dispatch_stub_167
#define gl_dispatch_stub_169 mgl_dispatch_stub_169
#define gl_dispatch_stub_170 mgl_dispatch_stub_170
#define gl_dispatch_stub_171 mgl_dispatch_stub_171
#define gl_dispatch_stub_172 mgl_dispatch_stub_172
#define gl_dispatch_stub_173 mgl_dispatch_stub_173
#define gl_dispatch_stub_174 mgl_dispatch_stub_174
#define gl_dispatch_stub_175 mgl_dispatch_stub_175
#define gl_dispatch_stub_177 mgl_dispatch_stub_177
#define gl_dispatch_stub_182 mgl_dispatch_stub_182
#define gl_dispatch_stub_184 mgl_dispatch_stub_184
#define gl_dispatch_stub_185 mgl_dispatch_stub_185
#define gl_dispatch_stub_186 mgl_dispatch_stub_186
#define gl_dispatch_stub_187 mgl_dispatch_stub_187
#define gl_dispatch_stub_188 mgl_dispatch_stub_188
#define gl_dispatch_stub_189 mgl_dispatch_stub_189
#define gl_dispatch_stub_190 mgl_dispatch_stub_190
#define gl_dispatch_stub_191 mgl_dispatch_stub_191
#define gl_dispatch_stub_192 mgl_dispatch_stub_192
#define gl_dispatch_stub_193 mgl_dispatch_stub_193
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
#define gl_dispatch_stub_240 mgl_dispatch_stub_240
#define gl_dispatch_stub_242 mgl_dispatch_stub_242
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
#define gl_dispatch_stub_264 mgl_dispatch_stub_264
#define gl_dispatch_stub_265 mgl_dispatch_stub_265
#define gl_dispatch_stub_266 mgl_dispatch_stub_266
#define gl_dispatch_stub_267 mgl_dispatch_stub_267
#define gl_dispatch_stub_268 mgl_dispatch_stub_268
#define gl_dispatch_stub_269 mgl_dispatch_stub_269
#define gl_dispatch_stub_270 mgl_dispatch_stub_270
#define gl_dispatch_stub_271 mgl_dispatch_stub_271
#define gl_dispatch_stub_272 mgl_dispatch_stub_272
#define gl_dispatch_stub_273 mgl_dispatch_stub_273
#define gl_dispatch_stub_274 mgl_dispatch_stub_274
#define gl_dispatch_stub_276 mgl_dispatch_stub_276
#define gl_dispatch_stub_277 mgl_dispatch_stub_277
#define gl_dispatch_stub_278 mgl_dispatch_stub_278
#define gl_dispatch_stub_279 mgl_dispatch_stub_279
#define gl_dispatch_stub_280 mgl_dispatch_stub_280
#define gl_dispatch_stub_281 mgl_dispatch_stub_281
#define gl_dispatch_stub_284 mgl_dispatch_stub_284
#define gl_dispatch_stub_285 mgl_dispatch_stub_285
#define gl_dispatch_stub_287 mgl_dispatch_stub_287
#define gl_dispatch_stub_288 mgl_dispatch_stub_288
#define gl_dispatch_stub_289 mgl_dispatch_stub_289
#define gl_dispatch_stub_290 mgl_dispatch_stub_290
#define gl_dispatch_stub_291 mgl_dispatch_stub_291
#define gl_dispatch_stub_292 mgl_dispatch_stub_292
#define gl_dispatch_stub_293 mgl_dispatch_stub_293
#define gl_dispatch_stub_294 mgl_dispatch_stub_294
#define gl_dispatch_stub_295 mgl_dispatch_stub_295
#define gl_dispatch_stub_296 mgl_dispatch_stub_296
#define gl_dispatch_stub_297 mgl_dispatch_stub_297
#define gl_dispatch_stub_298 mgl_dispatch_stub_298
#define gl_dispatch_stub_299 mgl_dispatch_stub_299
#define gl_dispatch_stub_300 mgl_dispatch_stub_300
#define gl_dispatch_stub_301 mgl_dispatch_stub_301
#define gl_dispatch_stub_302 mgl_dispatch_stub_302
#define gl_dispatch_stub_303 mgl_dispatch_stub_303
#define gl_dispatch_stub_304 mgl_dispatch_stub_304
#define gl_dispatch_stub_306 mgl_dispatch_stub_306
#define gl_dispatch_stub_308 mgl_dispatch_stub_308
#define gl_dispatch_stub_309 mgl_dispatch_stub_309
#define gl_dispatch_stub_312 mgl_dispatch_stub_312
#define gl_dispatch_stub_313 mgl_dispatch_stub_313
#define gl_dispatch_stub_314 mgl_dispatch_stub_314
#define gl_dispatch_stub_315 mgl_dispatch_stub_315
#define gl_dispatch_stub_316 mgl_dispatch_stub_316
#define gl_dispatch_stub_317 mgl_dispatch_stub_317
#define gl_dispatch_stub_318 mgl_dispatch_stub_318
#define gl_dispatch_stub_320 mgl_dispatch_stub_320
#define gl_dispatch_stub_321 mgl_dispatch_stub_321
#define gl_dispatch_stub_322 mgl_dispatch_stub_322
#define gl_dispatch_stub_323 mgl_dispatch_stub_323
#define gl_dispatch_stub_325 mgl_dispatch_stub_325
#define gl_dispatch_stub_329 mgl_dispatch_stub_329
#define gl_dispatch_stub_331 mgl_dispatch_stub_331
#define gl_dispatch_stub_332 mgl_dispatch_stub_332
#define gl_dispatch_stub_334 mgl_dispatch_stub_334
#define gl_dispatch_stub_335 mgl_dispatch_stub_335
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
#define gl_dispatch_stub_375 mgl_dispatch_stub_375
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
#define gl_dispatch_stub_402 mgl_dispatch_stub_402
#define gl_dispatch_stub_403 mgl_dispatch_stub_403
#define gl_dispatch_stub_404 mgl_dispatch_stub_404
#define gl_dispatch_stub_405 mgl_dispatch_stub_405
#define gl_dispatch_stub_406 mgl_dispatch_stub_406
#define gl_dispatch_stub_407 mgl_dispatch_stub_407
#define gl_dispatch_stub_418 mgl_dispatch_stub_418
#define gl_dispatch_stub_419 mgl_dispatch_stub_419
#define gl_dispatch_stub_420 mgl_dispatch_stub_420
#define gl_dispatch_stub_421 mgl_dispatch_stub_421
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
void GLAPIENTRY gl_dispatch_stub_29(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void GLAPIENTRY gl_dispatch_stub_30(const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_31(GLint red, GLint green, GLint blue, GLint alpha);
void GLAPIENTRY gl_dispatch_stub_32(const GLint * v);
void GLAPIENTRY gl_dispatch_stub_33(GLshort red, GLshort green, GLshort blue, GLshort alpha);
void GLAPIENTRY gl_dispatch_stub_34(const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_35(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
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
void GLAPIENTRY gl_dispatch_stub_56(GLfloat nx, GLfloat ny, GLfloat nz);
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
void GLAPIENTRY gl_dispatch_stub_153(GLenum pname, GLfloat param);
void GLAPIENTRY gl_dispatch_stub_154(GLenum pname, const GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_155(GLenum pname, GLint param);
void GLAPIENTRY gl_dispatch_stub_156(GLenum pname, const GLint * params);
void GLAPIENTRY gl_dispatch_stub_159(GLenum light, GLenum pname, GLfloat param);
void GLAPIENTRY gl_dispatch_stub_160(GLenum light, GLenum pname, const GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_161(GLenum light, GLenum pname, GLint param);
void GLAPIENTRY gl_dispatch_stub_162(GLenum light, GLenum pname, const GLint * params);
void GLAPIENTRY gl_dispatch_stub_163(GLenum pname, GLfloat param);
void GLAPIENTRY gl_dispatch_stub_164(GLenum pname, const GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_165(GLenum pname, GLint param);
void GLAPIENTRY gl_dispatch_stub_166(GLenum pname, const GLint * params);
void GLAPIENTRY gl_dispatch_stub_167(GLint factor, GLushort pattern);
void GLAPIENTRY gl_dispatch_stub_169(GLenum face, GLenum pname, GLfloat param);
void GLAPIENTRY gl_dispatch_stub_170(GLenum face, GLenum pname, const GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_171(GLenum face, GLenum pname, GLint param);
void GLAPIENTRY gl_dispatch_stub_172(GLenum face, GLenum pname, const GLint * params);
void GLAPIENTRY gl_dispatch_stub_173(GLfloat size);
void GLAPIENTRY gl_dispatch_stub_174(GLenum face, GLenum mode);
void GLAPIENTRY gl_dispatch_stub_175(const GLubyte * mask);
void GLAPIENTRY gl_dispatch_stub_177(GLenum mode);
void GLAPIENTRY gl_dispatch_stub_182(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels);
void GLAPIENTRY gl_dispatch_stub_184(GLenum target, GLenum pname, GLfloat param);
void GLAPIENTRY gl_dispatch_stub_185(GLenum target, GLenum pname, const GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_186(GLenum target, GLenum pname, GLint param);
void GLAPIENTRY gl_dispatch_stub_187(GLenum target, GLenum pname, const GLint * params);
void GLAPIENTRY gl_dispatch_stub_188(GLenum coord, GLenum pname, GLdouble param);
void GLAPIENTRY gl_dispatch_stub_189(GLenum coord, GLenum pname, const GLdouble * params);
void GLAPIENTRY gl_dispatch_stub_190(GLenum coord, GLenum pname, GLfloat param);
void GLAPIENTRY gl_dispatch_stub_191(GLenum coord, GLenum pname, const GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_192(GLenum coord, GLenum pname, GLint param);
void GLAPIENTRY gl_dispatch_stub_193(GLenum coord, GLenum pname, const GLint * params);
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
void GLAPIENTRY gl_dispatch_stub_240(GLenum func, GLclampf ref);
void GLAPIENTRY gl_dispatch_stub_242(GLenum opcode);
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
void GLAPIENTRY gl_dispatch_stub_264(GLenum light, GLenum pname, GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_265(GLenum light, GLenum pname, GLint * params);
void GLAPIENTRY gl_dispatch_stub_266(GLenum target, GLenum query, GLdouble * v);
void GLAPIENTRY gl_dispatch_stub_267(GLenum target, GLenum query, GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_268(GLenum target, GLenum query, GLint * v);
void GLAPIENTRY gl_dispatch_stub_269(GLenum face, GLenum pname, GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_270(GLenum face, GLenum pname, GLint * params);
void GLAPIENTRY gl_dispatch_stub_271(GLenum map, GLfloat * values);
void GLAPIENTRY gl_dispatch_stub_272(GLenum map, GLuint * values);
void GLAPIENTRY gl_dispatch_stub_273(GLenum map, GLushort * values);
void GLAPIENTRY gl_dispatch_stub_274(GLubyte * mask);
void GLAPIENTRY gl_dispatch_stub_276(GLenum target, GLenum pname, GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_277(GLenum target, GLenum pname, GLint * params);
void GLAPIENTRY gl_dispatch_stub_278(GLenum coord, GLenum pname, GLdouble * params);
void GLAPIENTRY gl_dispatch_stub_279(GLenum coord, GLenum pname, GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_280(GLenum coord, GLenum pname, GLint * params);
void GLAPIENTRY gl_dispatch_stub_281(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels);
void GLAPIENTRY gl_dispatch_stub_284(GLenum target, GLint level, GLenum pname, GLfloat * params);
void GLAPIENTRY gl_dispatch_stub_285(GLenum target, GLint level, GLenum pname, GLint * params);
GLboolean GLAPIENTRY gl_dispatch_stub_287(GLuint list);
void GLAPIENTRY gl_dispatch_stub_288(GLclampd zNear, GLclampd zFar);
void GLAPIENTRY gl_dispatch_stub_289(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
void GLAPIENTRY gl_dispatch_stub_290(void);
void GLAPIENTRY gl_dispatch_stub_291(const GLfloat * m);
void GLAPIENTRY gl_dispatch_stub_292(const GLdouble * m);
void GLAPIENTRY gl_dispatch_stub_293(GLenum mode);
void GLAPIENTRY gl_dispatch_stub_294(const GLfloat * m);
void GLAPIENTRY gl_dispatch_stub_295(const GLdouble * m);
void GLAPIENTRY gl_dispatch_stub_296(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
void GLAPIENTRY gl_dispatch_stub_297(void);
void GLAPIENTRY gl_dispatch_stub_298(void);
void GLAPIENTRY gl_dispatch_stub_299(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
void GLAPIENTRY gl_dispatch_stub_300(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void GLAPIENTRY gl_dispatch_stub_301(GLdouble x, GLdouble y, GLdouble z);
void GLAPIENTRY gl_dispatch_stub_302(GLfloat x, GLfloat y, GLfloat z);
void GLAPIENTRY gl_dispatch_stub_303(GLdouble x, GLdouble y, GLdouble z);
void GLAPIENTRY gl_dispatch_stub_304(GLfloat x, GLfloat y, GLfloat z);
void GLAPIENTRY gl_dispatch_stub_306(GLint i);
void GLAPIENTRY gl_dispatch_stub_308(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
void GLAPIENTRY gl_dispatch_stub_309(GLenum array);
void GLAPIENTRY gl_dispatch_stub_312(GLsizei stride, const GLvoid * pointer);
void GLAPIENTRY gl_dispatch_stub_313(GLenum array);
void GLAPIENTRY gl_dispatch_stub_314(GLenum type, GLsizei stride, const GLvoid * pointer);
void GLAPIENTRY gl_dispatch_stub_315(GLubyte c);
void GLAPIENTRY gl_dispatch_stub_316(const GLubyte * c);
void GLAPIENTRY gl_dispatch_stub_317(GLenum format, GLsizei stride, const GLvoid * pointer);
void GLAPIENTRY gl_dispatch_stub_318(GLenum type, GLsizei stride, const GLvoid * pointer);
void GLAPIENTRY gl_dispatch_stub_320(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
void GLAPIENTRY gl_dispatch_stub_321(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
GLboolean GLAPIENTRY gl_dispatch_stub_322(GLsizei n, const GLuint * textures, GLboolean * residences);
void GLAPIENTRY gl_dispatch_stub_323(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
void GLAPIENTRY gl_dispatch_stub_325(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
void GLAPIENTRY gl_dispatch_stub_329(GLenum pname, GLvoid ** params);
void GLAPIENTRY gl_dispatch_stub_331(GLsizei n, const GLuint * textures, const GLclampf * priorities);
void GLAPIENTRY gl_dispatch_stub_332(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels);
void GLAPIENTRY gl_dispatch_stub_334(void);
void GLAPIENTRY gl_dispatch_stub_335(GLbitfield mask);
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
void GLAPIENTRY gl_dispatch_stub_375(GLenum texture);
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
void GLAPIENTRY gl_dispatch_stub_402(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
void GLAPIENTRY gl_dispatch_stub_403(GLenum target, const GLfloat * v);
void GLAPIENTRY gl_dispatch_stub_404(GLenum target, GLint s, GLint t, GLint r, GLint q);
void GLAPIENTRY gl_dispatch_stub_405(GLenum target, const GLint * v);
void GLAPIENTRY gl_dispatch_stub_406(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
void GLAPIENTRY gl_dispatch_stub_407(GLenum target, const GLshort * v);
void GLAPIENTRY gl_dispatch_stub_418(GLuint array);
void GLAPIENTRY gl_dispatch_stub_419(GLsizei n, const GLuint * arrays);
void GLAPIENTRY gl_dispatch_stub_420(GLsizei n, GLuint * arrays);
GLboolean GLAPIENTRY gl_dispatch_stub_421(GLuint array);

/* OpenGL ES specific prototypes */

/* category GL_OES_EGL_image */
GLAPI void GLAPIENTRY glEGLImageTargetRenderbufferStorageOES(GLenum target, GLvoid * writeOffset);
GLAPI void GLAPIENTRY glEGLImageTargetTexture2DOES(GLenum target, GLvoid * writeOffset);
/* category GL_OES_get_program_binary */
GLAPI void GLAPIENTRY glGetProgramBinaryOES(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, GLvoid * binary);
GLAPI void GLAPIENTRY glProgramBinaryOES(GLuint program, GLenum binaryFormat, const GLvoid * binary, GLint length);
/* category GL_OES_mapbuffer */
GLAPI void GLAPIENTRY glGetBufferPointervOES(GLenum target, GLenum pname, GLvoid ** params);
GLAPI GLvoid * GLAPIENTRY glMapBufferOES(GLenum target, GLenum access);
GLAPI GLboolean GLAPIENTRY glUnmapBufferOES(GLenum target);
/* category GL_OES_texture_3D */
GLAPI void GLAPIENTRY glTexImage3DOES(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels);
GLAPI void GLAPIENTRY glTexSubImage3DOES(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels);
GLAPI void GLAPIENTRY glCopyTexSubImage3DOES(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI void GLAPIENTRY glCompressedTexImage3DOES(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data);
GLAPI void GLAPIENTRY glCompressedTexSubImage3DOES(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data);
GLAPI void GLAPIENTRY glFramebufferTexture3DOES(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
/* category es2.0 */
GLAPI void GLAPIENTRY glBindFramebuffer(GLenum target, GLuint framebuffer);
GLAPI void GLAPIENTRY glBindRenderbuffer(GLenum target, GLuint renderbuffer);
GLAPI GLenum GLAPIENTRY glCheckFramebufferStatus(GLenum target);
GLAPI void GLAPIENTRY glClearDepthf(GLclampf depth);
GLAPI void GLAPIENTRY glDeleteFramebuffers(GLsizei n, const GLuint * framebuffers);
GLAPI void GLAPIENTRY glDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers);
GLAPI void GLAPIENTRY glDepthRangef(GLclampf zNear, GLclampf zFar);
GLAPI void GLAPIENTRY glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GLAPI void GLAPIENTRY glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GLAPI void GLAPIENTRY glGenFramebuffers(GLsizei n, GLuint * framebuffers);
GLAPI void GLAPIENTRY glGenRenderbuffers(GLsizei n, GLuint * renderbuffers);
GLAPI void GLAPIENTRY glGenerateMipmap(GLenum target);
GLAPI void GLAPIENTRY glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params);
GLAPI void GLAPIENTRY glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params);
GLAPI void GLAPIENTRY glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
GLAPI GLboolean GLAPIENTRY glIsFramebuffer(GLuint framebuffer);
GLAPI GLboolean GLAPIENTRY glIsRenderbuffer(GLuint renderbuffer);
GLAPI void GLAPIENTRY glReleaseShaderCompiler(void);
GLAPI void GLAPIENTRY glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GLAPI void GLAPIENTRY glShaderBinary(GLsizei n, const GLuint * shaders, GLenum binaryformat, const GLvoid * binary, GLsizei length);

#endif /* defined(NEED_FUNCTION_POINTER) || defined(GLX_INDIRECT_RENDERING) */

static const glprocs_table_t static_functions[] = {
    NAME_FUNC_OFFSET(    0, gl_dispatch_stub_0, gl_dispatch_stub_0, NULL, 0),
    NAME_FUNC_OFFSET(   10, gl_dispatch_stub_1, gl_dispatch_stub_1, NULL, 1),
    NAME_FUNC_OFFSET(   20, gl_dispatch_stub_2, gl_dispatch_stub_2, NULL, 2),
    NAME_FUNC_OFFSET(   31, gl_dispatch_stub_3, gl_dispatch_stub_3, NULL, 3),
    NAME_FUNC_OFFSET(   43, gl_dispatch_stub_4, gl_dispatch_stub_4, NULL, 4),
    NAME_FUNC_OFFSET(   57, gl_dispatch_stub_5, gl_dispatch_stub_5, NULL, 5),
    NAME_FUNC_OFFSET(   68, gl_dispatch_stub_6, gl_dispatch_stub_6, NULL, 6),
    NAME_FUNC_OFFSET(   79, gl_dispatch_stub_7, gl_dispatch_stub_7, NULL, 7),
    NAME_FUNC_OFFSET(   87, gl_dispatch_stub_8, gl_dispatch_stub_8, NULL, 8),
    NAME_FUNC_OFFSET(   96, gl_dispatch_stub_9, gl_dispatch_stub_9, NULL, 9),
    NAME_FUNC_OFFSET(  106, gl_dispatch_stub_10, gl_dispatch_stub_10, NULL, 10),
    NAME_FUNC_OFFSET(  117, gl_dispatch_stub_11, gl_dispatch_stub_11, NULL, 11),
    NAME_FUNC_OFFSET(  127, gl_dispatch_stub_12, gl_dispatch_stub_12, NULL, 12),
    NAME_FUNC_OFFSET(  138, gl_dispatch_stub_13, gl_dispatch_stub_13, NULL, 13),
    NAME_FUNC_OFFSET(  148, gl_dispatch_stub_14, gl_dispatch_stub_14, NULL, 14),
    NAME_FUNC_OFFSET(  159, gl_dispatch_stub_15, gl_dispatch_stub_15, NULL, 15),
    NAME_FUNC_OFFSET(  169, gl_dispatch_stub_16, gl_dispatch_stub_16, NULL, 16),
    NAME_FUNC_OFFSET(  180, gl_dispatch_stub_17, gl_dispatch_stub_17, NULL, 17),
    NAME_FUNC_OFFSET(  190, gl_dispatch_stub_18, gl_dispatch_stub_18, NULL, 18),
    NAME_FUNC_OFFSET(  201, gl_dispatch_stub_19, gl_dispatch_stub_19, NULL, 19),
    NAME_FUNC_OFFSET(  212, gl_dispatch_stub_20, gl_dispatch_stub_20, NULL, 20),
    NAME_FUNC_OFFSET(  224, gl_dispatch_stub_21, gl_dispatch_stub_21, NULL, 21),
    NAME_FUNC_OFFSET(  235, gl_dispatch_stub_22, gl_dispatch_stub_22, NULL, 22),
    NAME_FUNC_OFFSET(  247, gl_dispatch_stub_23, gl_dispatch_stub_23, NULL, 23),
    NAME_FUNC_OFFSET(  258, gl_dispatch_stub_24, gl_dispatch_stub_24, NULL, 24),
    NAME_FUNC_OFFSET(  270, gl_dispatch_stub_25, gl_dispatch_stub_25, NULL, 25),
    NAME_FUNC_OFFSET(  280, gl_dispatch_stub_26, gl_dispatch_stub_26, NULL, 26),
    NAME_FUNC_OFFSET(  291, gl_dispatch_stub_27, gl_dispatch_stub_27, NULL, 27),
    NAME_FUNC_OFFSET(  301, gl_dispatch_stub_28, gl_dispatch_stub_28, NULL, 28),
    NAME_FUNC_OFFSET(  312, gl_dispatch_stub_29, gl_dispatch_stub_29, NULL, 29),
    NAME_FUNC_OFFSET(  322, gl_dispatch_stub_30, gl_dispatch_stub_30, NULL, 30),
    NAME_FUNC_OFFSET(  333, gl_dispatch_stub_31, gl_dispatch_stub_31, NULL, 31),
    NAME_FUNC_OFFSET(  343, gl_dispatch_stub_32, gl_dispatch_stub_32, NULL, 32),
    NAME_FUNC_OFFSET(  354, gl_dispatch_stub_33, gl_dispatch_stub_33, NULL, 33),
    NAME_FUNC_OFFSET(  364, gl_dispatch_stub_34, gl_dispatch_stub_34, NULL, 34),
    NAME_FUNC_OFFSET(  375, gl_dispatch_stub_35, gl_dispatch_stub_35, NULL, 35),
    NAME_FUNC_OFFSET(  386, gl_dispatch_stub_36, gl_dispatch_stub_36, NULL, 36),
    NAME_FUNC_OFFSET(  398, gl_dispatch_stub_37, gl_dispatch_stub_37, NULL, 37),
    NAME_FUNC_OFFSET(  409, gl_dispatch_stub_38, gl_dispatch_stub_38, NULL, 38),
    NAME_FUNC_OFFSET(  421, gl_dispatch_stub_39, gl_dispatch_stub_39, NULL, 39),
    NAME_FUNC_OFFSET(  432, gl_dispatch_stub_40, gl_dispatch_stub_40, NULL, 40),
    NAME_FUNC_OFFSET(  444, gl_dispatch_stub_41, gl_dispatch_stub_41, NULL, 41),
    NAME_FUNC_OFFSET(  455, gl_dispatch_stub_42, gl_dispatch_stub_42, NULL, 42),
    NAME_FUNC_OFFSET(  467, gl_dispatch_stub_43, gl_dispatch_stub_43, NULL, 43),
    NAME_FUNC_OFFSET(  473, gl_dispatch_stub_44, gl_dispatch_stub_44, NULL, 44),
    NAME_FUNC_OFFSET(  482, gl_dispatch_stub_45, gl_dispatch_stub_45, NULL, 45),
    NAME_FUNC_OFFSET(  492, gl_dispatch_stub_46, gl_dispatch_stub_46, NULL, 46),
    NAME_FUNC_OFFSET(  501, gl_dispatch_stub_47, gl_dispatch_stub_47, NULL, 47),
    NAME_FUNC_OFFSET(  511, gl_dispatch_stub_48, gl_dispatch_stub_48, NULL, 48),
    NAME_FUNC_OFFSET(  520, gl_dispatch_stub_49, gl_dispatch_stub_49, NULL, 49),
    NAME_FUNC_OFFSET(  530, gl_dispatch_stub_50, gl_dispatch_stub_50, NULL, 50),
    NAME_FUNC_OFFSET(  539, gl_dispatch_stub_51, gl_dispatch_stub_51, NULL, 51),
    NAME_FUNC_OFFSET(  549, gl_dispatch_stub_52, gl_dispatch_stub_52, NULL, 52),
    NAME_FUNC_OFFSET(  560, gl_dispatch_stub_53, gl_dispatch_stub_53, NULL, 53),
    NAME_FUNC_OFFSET(  572, gl_dispatch_stub_54, gl_dispatch_stub_54, NULL, 54),
    NAME_FUNC_OFFSET(  583, gl_dispatch_stub_55, gl_dispatch_stub_55, NULL, 55),
    NAME_FUNC_OFFSET(  595, gl_dispatch_stub_56, gl_dispatch_stub_56, NULL, 56),
    NAME_FUNC_OFFSET(  606, gl_dispatch_stub_57, gl_dispatch_stub_57, NULL, 57),
    NAME_FUNC_OFFSET(  618, gl_dispatch_stub_58, gl_dispatch_stub_58, NULL, 58),
    NAME_FUNC_OFFSET(  629, gl_dispatch_stub_59, gl_dispatch_stub_59, NULL, 59),
    NAME_FUNC_OFFSET(  641, gl_dispatch_stub_60, gl_dispatch_stub_60, NULL, 60),
    NAME_FUNC_OFFSET(  652, gl_dispatch_stub_61, gl_dispatch_stub_61, NULL, 61),
    NAME_FUNC_OFFSET(  664, gl_dispatch_stub_62, gl_dispatch_stub_62, NULL, 62),
    NAME_FUNC_OFFSET(  678, gl_dispatch_stub_63, gl_dispatch_stub_63, NULL, 63),
    NAME_FUNC_OFFSET(  693, gl_dispatch_stub_64, gl_dispatch_stub_64, NULL, 64),
    NAME_FUNC_OFFSET(  707, gl_dispatch_stub_65, gl_dispatch_stub_65, NULL, 65),
    NAME_FUNC_OFFSET(  722, gl_dispatch_stub_66, gl_dispatch_stub_66, NULL, 66),
    NAME_FUNC_OFFSET(  736, gl_dispatch_stub_67, gl_dispatch_stub_67, NULL, 67),
    NAME_FUNC_OFFSET(  751, gl_dispatch_stub_68, gl_dispatch_stub_68, NULL, 68),
    NAME_FUNC_OFFSET(  765, gl_dispatch_stub_69, gl_dispatch_stub_69, NULL, 69),
    NAME_FUNC_OFFSET(  780, gl_dispatch_stub_70, gl_dispatch_stub_70, NULL, 70),
    NAME_FUNC_OFFSET(  794, gl_dispatch_stub_71, gl_dispatch_stub_71, NULL, 71),
    NAME_FUNC_OFFSET(  809, gl_dispatch_stub_72, gl_dispatch_stub_72, NULL, 72),
    NAME_FUNC_OFFSET(  823, gl_dispatch_stub_73, gl_dispatch_stub_73, NULL, 73),
    NAME_FUNC_OFFSET(  838, gl_dispatch_stub_74, gl_dispatch_stub_74, NULL, 74),
    NAME_FUNC_OFFSET(  852, gl_dispatch_stub_75, gl_dispatch_stub_75, NULL, 75),
    NAME_FUNC_OFFSET(  867, gl_dispatch_stub_76, gl_dispatch_stub_76, NULL, 76),
    NAME_FUNC_OFFSET(  881, gl_dispatch_stub_77, gl_dispatch_stub_77, NULL, 77),
    NAME_FUNC_OFFSET(  896, gl_dispatch_stub_78, gl_dispatch_stub_78, NULL, 78),
    NAME_FUNC_OFFSET(  910, gl_dispatch_stub_79, gl_dispatch_stub_79, NULL, 79),
    NAME_FUNC_OFFSET(  925, gl_dispatch_stub_80, gl_dispatch_stub_80, NULL, 80),
    NAME_FUNC_OFFSET(  939, gl_dispatch_stub_81, gl_dispatch_stub_81, NULL, 81),
    NAME_FUNC_OFFSET(  954, gl_dispatch_stub_82, gl_dispatch_stub_82, NULL, 82),
    NAME_FUNC_OFFSET(  968, gl_dispatch_stub_83, gl_dispatch_stub_83, NULL, 83),
    NAME_FUNC_OFFSET(  983, gl_dispatch_stub_84, gl_dispatch_stub_84, NULL, 84),
    NAME_FUNC_OFFSET(  997, gl_dispatch_stub_85, gl_dispatch_stub_85, NULL, 85),
    NAME_FUNC_OFFSET( 1012, gl_dispatch_stub_86, gl_dispatch_stub_86, NULL, 86),
    NAME_FUNC_OFFSET( 1020, gl_dispatch_stub_87, gl_dispatch_stub_87, NULL, 87),
    NAME_FUNC_OFFSET( 1029, gl_dispatch_stub_88, gl_dispatch_stub_88, NULL, 88),
    NAME_FUNC_OFFSET( 1037, gl_dispatch_stub_89, gl_dispatch_stub_89, NULL, 89),
    NAME_FUNC_OFFSET( 1046, gl_dispatch_stub_90, gl_dispatch_stub_90, NULL, 90),
    NAME_FUNC_OFFSET( 1054, gl_dispatch_stub_91, gl_dispatch_stub_91, NULL, 91),
    NAME_FUNC_OFFSET( 1063, gl_dispatch_stub_92, gl_dispatch_stub_92, NULL, 92),
    NAME_FUNC_OFFSET( 1071, gl_dispatch_stub_93, gl_dispatch_stub_93, NULL, 93),
    NAME_FUNC_OFFSET( 1080, gl_dispatch_stub_94, gl_dispatch_stub_94, NULL, 94),
    NAME_FUNC_OFFSET( 1093, gl_dispatch_stub_95, gl_dispatch_stub_95, NULL, 95),
    NAME_FUNC_OFFSET( 1107, gl_dispatch_stub_96, gl_dispatch_stub_96, NULL, 96),
    NAME_FUNC_OFFSET( 1120, gl_dispatch_stub_97, gl_dispatch_stub_97, NULL, 97),
    NAME_FUNC_OFFSET( 1134, gl_dispatch_stub_98, gl_dispatch_stub_98, NULL, 98),
    NAME_FUNC_OFFSET( 1147, gl_dispatch_stub_99, gl_dispatch_stub_99, NULL, 99),
    NAME_FUNC_OFFSET( 1161, gl_dispatch_stub_100, gl_dispatch_stub_100, NULL, 100),
    NAME_FUNC_OFFSET( 1174, gl_dispatch_stub_101, gl_dispatch_stub_101, NULL, 101),
    NAME_FUNC_OFFSET( 1188, gl_dispatch_stub_102, gl_dispatch_stub_102, NULL, 102),
    NAME_FUNC_OFFSET( 1201, gl_dispatch_stub_103, gl_dispatch_stub_103, NULL, 103),
    NAME_FUNC_OFFSET( 1215, gl_dispatch_stub_104, gl_dispatch_stub_104, NULL, 104),
    NAME_FUNC_OFFSET( 1228, gl_dispatch_stub_105, gl_dispatch_stub_105, NULL, 105),
    NAME_FUNC_OFFSET( 1242, gl_dispatch_stub_106, gl_dispatch_stub_106, NULL, 106),
    NAME_FUNC_OFFSET( 1255, gl_dispatch_stub_107, gl_dispatch_stub_107, NULL, 107),
    NAME_FUNC_OFFSET( 1269, gl_dispatch_stub_108, gl_dispatch_stub_108, NULL, 108),
    NAME_FUNC_OFFSET( 1282, gl_dispatch_stub_109, gl_dispatch_stub_109, NULL, 109),
    NAME_FUNC_OFFSET( 1296, gl_dispatch_stub_110, gl_dispatch_stub_110, NULL, 110),
    NAME_FUNC_OFFSET( 1309, gl_dispatch_stub_111, gl_dispatch_stub_111, NULL, 111),
    NAME_FUNC_OFFSET( 1323, gl_dispatch_stub_112, gl_dispatch_stub_112, NULL, 112),
    NAME_FUNC_OFFSET( 1336, gl_dispatch_stub_113, gl_dispatch_stub_113, NULL, 113),
    NAME_FUNC_OFFSET( 1350, gl_dispatch_stub_114, gl_dispatch_stub_114, NULL, 114),
    NAME_FUNC_OFFSET( 1363, gl_dispatch_stub_115, gl_dispatch_stub_115, NULL, 115),
    NAME_FUNC_OFFSET( 1377, gl_dispatch_stub_116, gl_dispatch_stub_116, NULL, 116),
    NAME_FUNC_OFFSET( 1390, gl_dispatch_stub_117, gl_dispatch_stub_117, NULL, 117),
    NAME_FUNC_OFFSET( 1404, gl_dispatch_stub_118, gl_dispatch_stub_118, NULL, 118),
    NAME_FUNC_OFFSET( 1417, gl_dispatch_stub_119, gl_dispatch_stub_119, NULL, 119),
    NAME_FUNC_OFFSET( 1431, gl_dispatch_stub_120, gl_dispatch_stub_120, NULL, 120),
    NAME_FUNC_OFFSET( 1444, gl_dispatch_stub_121, gl_dispatch_stub_121, NULL, 121),
    NAME_FUNC_OFFSET( 1458, gl_dispatch_stub_122, gl_dispatch_stub_122, NULL, 122),
    NAME_FUNC_OFFSET( 1471, gl_dispatch_stub_123, gl_dispatch_stub_123, NULL, 123),
    NAME_FUNC_OFFSET( 1485, gl_dispatch_stub_124, gl_dispatch_stub_124, NULL, 124),
    NAME_FUNC_OFFSET( 1498, gl_dispatch_stub_125, gl_dispatch_stub_125, NULL, 125),
    NAME_FUNC_OFFSET( 1512, gl_dispatch_stub_126, gl_dispatch_stub_126, NULL, 126),
    NAME_FUNC_OFFSET( 1523, gl_dispatch_stub_127, gl_dispatch_stub_127, NULL, 127),
    NAME_FUNC_OFFSET( 1535, gl_dispatch_stub_128, gl_dispatch_stub_128, NULL, 128),
    NAME_FUNC_OFFSET( 1546, gl_dispatch_stub_129, gl_dispatch_stub_129, NULL, 129),
    NAME_FUNC_OFFSET( 1558, gl_dispatch_stub_130, gl_dispatch_stub_130, NULL, 130),
    NAME_FUNC_OFFSET( 1569, gl_dispatch_stub_131, gl_dispatch_stub_131, NULL, 131),
    NAME_FUNC_OFFSET( 1581, gl_dispatch_stub_132, gl_dispatch_stub_132, NULL, 132),
    NAME_FUNC_OFFSET( 1592, gl_dispatch_stub_133, gl_dispatch_stub_133, NULL, 133),
    NAME_FUNC_OFFSET( 1604, gl_dispatch_stub_134, gl_dispatch_stub_134, NULL, 134),
    NAME_FUNC_OFFSET( 1615, gl_dispatch_stub_135, gl_dispatch_stub_135, NULL, 135),
    NAME_FUNC_OFFSET( 1627, gl_dispatch_stub_136, gl_dispatch_stub_136, NULL, 136),
    NAME_FUNC_OFFSET( 1638, gl_dispatch_stub_137, gl_dispatch_stub_137, NULL, 137),
    NAME_FUNC_OFFSET( 1650, gl_dispatch_stub_138, gl_dispatch_stub_138, NULL, 138),
    NAME_FUNC_OFFSET( 1661, gl_dispatch_stub_139, gl_dispatch_stub_139, NULL, 139),
    NAME_FUNC_OFFSET( 1673, gl_dispatch_stub_140, gl_dispatch_stub_140, NULL, 140),
    NAME_FUNC_OFFSET( 1684, gl_dispatch_stub_141, gl_dispatch_stub_141, NULL, 141),
    NAME_FUNC_OFFSET( 1696, gl_dispatch_stub_142, gl_dispatch_stub_142, NULL, 142),
    NAME_FUNC_OFFSET( 1707, gl_dispatch_stub_143, gl_dispatch_stub_143, NULL, 143),
    NAME_FUNC_OFFSET( 1719, gl_dispatch_stub_144, gl_dispatch_stub_144, NULL, 144),
    NAME_FUNC_OFFSET( 1730, gl_dispatch_stub_145, gl_dispatch_stub_145, NULL, 145),
    NAME_FUNC_OFFSET( 1742, gl_dispatch_stub_146, gl_dispatch_stub_146, NULL, 146),
    NAME_FUNC_OFFSET( 1753, gl_dispatch_stub_147, gl_dispatch_stub_147, NULL, 147),
    NAME_FUNC_OFFSET( 1765, gl_dispatch_stub_148, gl_dispatch_stub_148, NULL, 148),
    NAME_FUNC_OFFSET( 1776, gl_dispatch_stub_149, gl_dispatch_stub_149, NULL, 149),
    NAME_FUNC_OFFSET( 1788, gl_dispatch_stub_150, gl_dispatch_stub_150, NULL, 150),
    NAME_FUNC_OFFSET( 1800, gl_dispatch_stub_151, gl_dispatch_stub_151, NULL, 151),
    NAME_FUNC_OFFSET( 1816, glCullFace, glCullFace, NULL, 152),
    NAME_FUNC_OFFSET( 1827, gl_dispatch_stub_153, gl_dispatch_stub_153, NULL, 153),
    NAME_FUNC_OFFSET( 1834, gl_dispatch_stub_154, gl_dispatch_stub_154, NULL, 154),
    NAME_FUNC_OFFSET( 1842, gl_dispatch_stub_155, gl_dispatch_stub_155, NULL, 155),
    NAME_FUNC_OFFSET( 1849, gl_dispatch_stub_156, gl_dispatch_stub_156, NULL, 156),
    NAME_FUNC_OFFSET( 1857, glFrontFace, glFrontFace, NULL, 157),
    NAME_FUNC_OFFSET( 1869, glHint, glHint, NULL, 158),
    NAME_FUNC_OFFSET( 1876, gl_dispatch_stub_159, gl_dispatch_stub_159, NULL, 159),
    NAME_FUNC_OFFSET( 1885, gl_dispatch_stub_160, gl_dispatch_stub_160, NULL, 160),
    NAME_FUNC_OFFSET( 1895, gl_dispatch_stub_161, gl_dispatch_stub_161, NULL, 161),
    NAME_FUNC_OFFSET( 1904, gl_dispatch_stub_162, gl_dispatch_stub_162, NULL, 162),
    NAME_FUNC_OFFSET( 1914, gl_dispatch_stub_163, gl_dispatch_stub_163, NULL, 163),
    NAME_FUNC_OFFSET( 1928, gl_dispatch_stub_164, gl_dispatch_stub_164, NULL, 164),
    NAME_FUNC_OFFSET( 1943, gl_dispatch_stub_165, gl_dispatch_stub_165, NULL, 165),
    NAME_FUNC_OFFSET( 1957, gl_dispatch_stub_166, gl_dispatch_stub_166, NULL, 166),
    NAME_FUNC_OFFSET( 1972, gl_dispatch_stub_167, gl_dispatch_stub_167, NULL, 167),
    NAME_FUNC_OFFSET( 1986, glLineWidth, glLineWidth, NULL, 168),
    NAME_FUNC_OFFSET( 1998, gl_dispatch_stub_169, gl_dispatch_stub_169, NULL, 169),
    NAME_FUNC_OFFSET( 2010, gl_dispatch_stub_170, gl_dispatch_stub_170, NULL, 170),
    NAME_FUNC_OFFSET( 2023, gl_dispatch_stub_171, gl_dispatch_stub_171, NULL, 171),
    NAME_FUNC_OFFSET( 2035, gl_dispatch_stub_172, gl_dispatch_stub_172, NULL, 172),
    NAME_FUNC_OFFSET( 2048, gl_dispatch_stub_173, gl_dispatch_stub_173, NULL, 173),
    NAME_FUNC_OFFSET( 2060, gl_dispatch_stub_174, gl_dispatch_stub_174, NULL, 174),
    NAME_FUNC_OFFSET( 2074, gl_dispatch_stub_175, gl_dispatch_stub_175, NULL, 175),
    NAME_FUNC_OFFSET( 2091, glScissor, glScissor, NULL, 176),
    NAME_FUNC_OFFSET( 2101, gl_dispatch_stub_177, gl_dispatch_stub_177, NULL, 177),
    NAME_FUNC_OFFSET( 2114, glTexParameterf, glTexParameterf, NULL, 178),
    NAME_FUNC_OFFSET( 2130, glTexParameterfv, glTexParameterfv, NULL, 179),
    NAME_FUNC_OFFSET( 2147, glTexParameteri, glTexParameteri, NULL, 180),
    NAME_FUNC_OFFSET( 2163, glTexParameteriv, glTexParameteriv, NULL, 181),
    NAME_FUNC_OFFSET( 2180, gl_dispatch_stub_182, gl_dispatch_stub_182, NULL, 182),
    NAME_FUNC_OFFSET( 2193, glTexImage2D, glTexImage2D, NULL, 183),
    NAME_FUNC_OFFSET( 2206, gl_dispatch_stub_184, gl_dispatch_stub_184, NULL, 184),
    NAME_FUNC_OFFSET( 2216, gl_dispatch_stub_185, gl_dispatch_stub_185, NULL, 185),
    NAME_FUNC_OFFSET( 2227, gl_dispatch_stub_186, gl_dispatch_stub_186, NULL, 186),
    NAME_FUNC_OFFSET( 2237, gl_dispatch_stub_187, gl_dispatch_stub_187, NULL, 187),
    NAME_FUNC_OFFSET( 2248, gl_dispatch_stub_188, gl_dispatch_stub_188, NULL, 188),
    NAME_FUNC_OFFSET( 2258, gl_dispatch_stub_189, gl_dispatch_stub_189, NULL, 189),
    NAME_FUNC_OFFSET( 2269, gl_dispatch_stub_190, gl_dispatch_stub_190, NULL, 190),
    NAME_FUNC_OFFSET( 2279, gl_dispatch_stub_191, gl_dispatch_stub_191, NULL, 191),
    NAME_FUNC_OFFSET( 2290, gl_dispatch_stub_192, gl_dispatch_stub_192, NULL, 192),
    NAME_FUNC_OFFSET( 2300, gl_dispatch_stub_193, gl_dispatch_stub_193, NULL, 193),
    NAME_FUNC_OFFSET( 2311, gl_dispatch_stub_194, gl_dispatch_stub_194, NULL, 194),
    NAME_FUNC_OFFSET( 2328, gl_dispatch_stub_195, gl_dispatch_stub_195, NULL, 195),
    NAME_FUNC_OFFSET( 2343, gl_dispatch_stub_196, gl_dispatch_stub_196, NULL, 196),
    NAME_FUNC_OFFSET( 2356, gl_dispatch_stub_197, gl_dispatch_stub_197, NULL, 197),
    NAME_FUNC_OFFSET( 2368, gl_dispatch_stub_198, gl_dispatch_stub_198, NULL, 198),
    NAME_FUNC_OFFSET( 2379, gl_dispatch_stub_199, gl_dispatch_stub_199, NULL, 199),
    NAME_FUNC_OFFSET( 2393, gl_dispatch_stub_200, gl_dispatch_stub_200, NULL, 200),
    NAME_FUNC_OFFSET( 2403, gl_dispatch_stub_201, gl_dispatch_stub_201, NULL, 201),
    NAME_FUNC_OFFSET( 2414, gl_dispatch_stub_202, gl_dispatch_stub_202, NULL, 202),
    NAME_FUNC_OFFSET( 2427, glClear, glClear, NULL, 203),
    NAME_FUNC_OFFSET( 2435, gl_dispatch_stub_204, gl_dispatch_stub_204, NULL, 204),
    NAME_FUNC_OFFSET( 2448, gl_dispatch_stub_205, gl_dispatch_stub_205, NULL, 205),
    NAME_FUNC_OFFSET( 2461, glClearColor, glClearColor, NULL, 206),
    NAME_FUNC_OFFSET( 2474, glClearStencil, glClearStencil, NULL, 207),
    NAME_FUNC_OFFSET( 2489, gl_dispatch_stub_208, gl_dispatch_stub_208, NULL, 208),
    NAME_FUNC_OFFSET( 2502, glStencilMask, glStencilMask, NULL, 209),
    NAME_FUNC_OFFSET( 2516, glColorMask, glColorMask, NULL, 210),
    NAME_FUNC_OFFSET( 2528, glDepthMask, glDepthMask, NULL, 211),
    NAME_FUNC_OFFSET( 2540, gl_dispatch_stub_212, gl_dispatch_stub_212, NULL, 212),
    NAME_FUNC_OFFSET( 2552, gl_dispatch_stub_213, gl_dispatch_stub_213, NULL, 213),
    NAME_FUNC_OFFSET( 2560, glDisable, glDisable, NULL, 214),
    NAME_FUNC_OFFSET( 2570, glEnable, glEnable, NULL, 215),
    NAME_FUNC_OFFSET( 2579, glFinish, glFinish, NULL, 216),
    NAME_FUNC_OFFSET( 2588, glFlush, glFlush, NULL, 217),
    NAME_FUNC_OFFSET( 2596, gl_dispatch_stub_218, gl_dispatch_stub_218, NULL, 218),
    NAME_FUNC_OFFSET( 2608, gl_dispatch_stub_219, gl_dispatch_stub_219, NULL, 219),
    NAME_FUNC_OFFSET( 2621, gl_dispatch_stub_220, gl_dispatch_stub_220, NULL, 220),
    NAME_FUNC_OFFSET( 2629, gl_dispatch_stub_221, gl_dispatch_stub_221, NULL, 221),
    NAME_FUNC_OFFSET( 2637, gl_dispatch_stub_222, gl_dispatch_stub_222, NULL, 222),
    NAME_FUNC_OFFSET( 2645, gl_dispatch_stub_223, gl_dispatch_stub_223, NULL, 223),
    NAME_FUNC_OFFSET( 2653, gl_dispatch_stub_224, gl_dispatch_stub_224, NULL, 224),
    NAME_FUNC_OFFSET( 2665, gl_dispatch_stub_225, gl_dispatch_stub_225, NULL, 225),
    NAME_FUNC_OFFSET( 2677, gl_dispatch_stub_226, gl_dispatch_stub_226, NULL, 226),
    NAME_FUNC_OFFSET( 2689, gl_dispatch_stub_227, gl_dispatch_stub_227, NULL, 227),
    NAME_FUNC_OFFSET( 2701, gl_dispatch_stub_228, gl_dispatch_stub_228, NULL, 228),
    NAME_FUNC_OFFSET( 2715, gl_dispatch_stub_229, gl_dispatch_stub_229, NULL, 229),
    NAME_FUNC_OFFSET( 2730, gl_dispatch_stub_230, gl_dispatch_stub_230, NULL, 230),
    NAME_FUNC_OFFSET( 2744, gl_dispatch_stub_231, gl_dispatch_stub_231, NULL, 231),
    NAME_FUNC_OFFSET( 2759, gl_dispatch_stub_232, gl_dispatch_stub_232, NULL, 232),
    NAME_FUNC_OFFSET( 2773, gl_dispatch_stub_233, gl_dispatch_stub_233, NULL, 233),
    NAME_FUNC_OFFSET( 2788, gl_dispatch_stub_234, gl_dispatch_stub_234, NULL, 234),
    NAME_FUNC_OFFSET( 2802, gl_dispatch_stub_235, gl_dispatch_stub_235, NULL, 235),
    NAME_FUNC_OFFSET( 2817, gl_dispatch_stub_236, gl_dispatch_stub_236, NULL, 236),
    NAME_FUNC_OFFSET( 2829, gl_dispatch_stub_237, gl_dispatch_stub_237, NULL, 237),
    NAME_FUNC_OFFSET( 2842, gl_dispatch_stub_238, gl_dispatch_stub_238, NULL, 238),
    NAME_FUNC_OFFSET( 2854, gl_dispatch_stub_239, gl_dispatch_stub_239, NULL, 239),
    NAME_FUNC_OFFSET( 2867, gl_dispatch_stub_240, gl_dispatch_stub_240, NULL, 240),
    NAME_FUNC_OFFSET( 2879, glBlendFunc, glBlendFunc, NULL, 241),
    NAME_FUNC_OFFSET( 2891, gl_dispatch_stub_242, gl_dispatch_stub_242, NULL, 242),
    NAME_FUNC_OFFSET( 2901, glStencilFunc, glStencilFunc, NULL, 243),
    NAME_FUNC_OFFSET( 2915, glStencilOp, glStencilOp, NULL, 244),
    NAME_FUNC_OFFSET( 2927, glDepthFunc, glDepthFunc, NULL, 245),
    NAME_FUNC_OFFSET( 2939, gl_dispatch_stub_246, gl_dispatch_stub_246, NULL, 246),
    NAME_FUNC_OFFSET( 2951, gl_dispatch_stub_247, gl_dispatch_stub_247, NULL, 247),
    NAME_FUNC_OFFSET( 2968, gl_dispatch_stub_248, gl_dispatch_stub_248, NULL, 248),
    NAME_FUNC_OFFSET( 2985, gl_dispatch_stub_249, gl_dispatch_stub_249, NULL, 249),
    NAME_FUNC_OFFSET( 2999, glPixelStorei, glPixelStorei, NULL, 250),
    NAME_FUNC_OFFSET( 3013, gl_dispatch_stub_251, gl_dispatch_stub_251, NULL, 251),
    NAME_FUNC_OFFSET( 3026, gl_dispatch_stub_252, gl_dispatch_stub_252, NULL, 252),
    NAME_FUNC_OFFSET( 3040, gl_dispatch_stub_253, gl_dispatch_stub_253, NULL, 253),
    NAME_FUNC_OFFSET( 3054, gl_dispatch_stub_254, gl_dispatch_stub_254, NULL, 254),
    NAME_FUNC_OFFSET( 3067, gl_dispatch_stub_255, gl_dispatch_stub_255, NULL, 255),
    NAME_FUNC_OFFSET( 3080, glReadPixels, glReadPixels, NULL, 256),
    NAME_FUNC_OFFSET( 3093, gl_dispatch_stub_257, gl_dispatch_stub_257, NULL, 257),
    NAME_FUNC_OFFSET( 3106, glGetBooleanv, glGetBooleanv, NULL, 258),
    NAME_FUNC_OFFSET( 3120, gl_dispatch_stub_259, gl_dispatch_stub_259, NULL, 259),
    NAME_FUNC_OFFSET( 3135, gl_dispatch_stub_260, gl_dispatch_stub_260, NULL, 260),
    NAME_FUNC_OFFSET( 3148, glGetError, glGetError, NULL, 261),
    NAME_FUNC_OFFSET( 3159, glGetFloatv, glGetFloatv, NULL, 262),
    NAME_FUNC_OFFSET( 3171, glGetIntegerv, glGetIntegerv, NULL, 263),
    NAME_FUNC_OFFSET( 3185, gl_dispatch_stub_264, gl_dispatch_stub_264, NULL, 264),
    NAME_FUNC_OFFSET( 3198, gl_dispatch_stub_265, gl_dispatch_stub_265, NULL, 265),
    NAME_FUNC_OFFSET( 3211, gl_dispatch_stub_266, gl_dispatch_stub_266, NULL, 266),
    NAME_FUNC_OFFSET( 3222, gl_dispatch_stub_267, gl_dispatch_stub_267, NULL, 267),
    NAME_FUNC_OFFSET( 3233, gl_dispatch_stub_268, gl_dispatch_stub_268, NULL, 268),
    NAME_FUNC_OFFSET( 3244, gl_dispatch_stub_269, gl_dispatch_stub_269, NULL, 269),
    NAME_FUNC_OFFSET( 3260, gl_dispatch_stub_270, gl_dispatch_stub_270, NULL, 270),
    NAME_FUNC_OFFSET( 3276, gl_dispatch_stub_271, gl_dispatch_stub_271, NULL, 271),
    NAME_FUNC_OFFSET( 3292, gl_dispatch_stub_272, gl_dispatch_stub_272, NULL, 272),
    NAME_FUNC_OFFSET( 3309, gl_dispatch_stub_273, gl_dispatch_stub_273, NULL, 273),
    NAME_FUNC_OFFSET( 3326, gl_dispatch_stub_274, gl_dispatch_stub_274, NULL, 274),
    NAME_FUNC_OFFSET( 3346, glGetString, glGetString, NULL, 275),
    NAME_FUNC_OFFSET( 3358, gl_dispatch_stub_276, gl_dispatch_stub_276, NULL, 276),
    NAME_FUNC_OFFSET( 3372, gl_dispatch_stub_277, gl_dispatch_stub_277, NULL, 277),
    NAME_FUNC_OFFSET( 3386, gl_dispatch_stub_278, gl_dispatch_stub_278, NULL, 278),
    NAME_FUNC_OFFSET( 3400, gl_dispatch_stub_279, gl_dispatch_stub_279, NULL, 279),
    NAME_FUNC_OFFSET( 3414, gl_dispatch_stub_280, gl_dispatch_stub_280, NULL, 280),
    NAME_FUNC_OFFSET( 3428, gl_dispatch_stub_281, gl_dispatch_stub_281, NULL, 281),
    NAME_FUNC_OFFSET( 3442, glGetTexParameterfv, glGetTexParameterfv, NULL, 282),
    NAME_FUNC_OFFSET( 3462, glGetTexParameteriv, glGetTexParameteriv, NULL, 283),
    NAME_FUNC_OFFSET( 3482, gl_dispatch_stub_284, gl_dispatch_stub_284, NULL, 284),
    NAME_FUNC_OFFSET( 3507, gl_dispatch_stub_285, gl_dispatch_stub_285, NULL, 285),
    NAME_FUNC_OFFSET( 3532, glIsEnabled, glIsEnabled, NULL, 286),
    NAME_FUNC_OFFSET( 3544, gl_dispatch_stub_287, gl_dispatch_stub_287, NULL, 287),
    NAME_FUNC_OFFSET( 3553, gl_dispatch_stub_288, gl_dispatch_stub_288, NULL, 288),
    NAME_FUNC_OFFSET( 3566, gl_dispatch_stub_289, gl_dispatch_stub_289, NULL, 289),
    NAME_FUNC_OFFSET( 3576, gl_dispatch_stub_290, gl_dispatch_stub_290, NULL, 290),
    NAME_FUNC_OFFSET( 3591, gl_dispatch_stub_291, gl_dispatch_stub_291, NULL, 291),
    NAME_FUNC_OFFSET( 3605, gl_dispatch_stub_292, gl_dispatch_stub_292, NULL, 292),
    NAME_FUNC_OFFSET( 3619, gl_dispatch_stub_293, gl_dispatch_stub_293, NULL, 293),
    NAME_FUNC_OFFSET( 3632, gl_dispatch_stub_294, gl_dispatch_stub_294, NULL, 294),
    NAME_FUNC_OFFSET( 3646, gl_dispatch_stub_295, gl_dispatch_stub_295, NULL, 295),
    NAME_FUNC_OFFSET( 3660, gl_dispatch_stub_296, gl_dispatch_stub_296, NULL, 296),
    NAME_FUNC_OFFSET( 3668, gl_dispatch_stub_297, gl_dispatch_stub_297, NULL, 297),
    NAME_FUNC_OFFSET( 3680, gl_dispatch_stub_298, gl_dispatch_stub_298, NULL, 298),
    NAME_FUNC_OFFSET( 3693, gl_dispatch_stub_299, gl_dispatch_stub_299, NULL, 299),
    NAME_FUNC_OFFSET( 3703, gl_dispatch_stub_300, gl_dispatch_stub_300, NULL, 300),
    NAME_FUNC_OFFSET( 3713, gl_dispatch_stub_301, gl_dispatch_stub_301, NULL, 301),
    NAME_FUNC_OFFSET( 3722, gl_dispatch_stub_302, gl_dispatch_stub_302, NULL, 302),
    NAME_FUNC_OFFSET( 3731, gl_dispatch_stub_303, gl_dispatch_stub_303, NULL, 303),
    NAME_FUNC_OFFSET( 3744, gl_dispatch_stub_304, gl_dispatch_stub_304, NULL, 304),
    NAME_FUNC_OFFSET( 3757, glViewport, glViewport, NULL, 305),
    NAME_FUNC_OFFSET( 3768, gl_dispatch_stub_306, gl_dispatch_stub_306, NULL, 306),
    NAME_FUNC_OFFSET( 3783, glBindTexture, glBindTexture, NULL, 307),
    NAME_FUNC_OFFSET( 3797, gl_dispatch_stub_308, gl_dispatch_stub_308, NULL, 308),
    NAME_FUNC_OFFSET( 3812, gl_dispatch_stub_309, gl_dispatch_stub_309, NULL, 309),
    NAME_FUNC_OFFSET( 3833, glDrawArrays, glDrawArrays, NULL, 310),
    NAME_FUNC_OFFSET( 3846, glDrawElements, glDrawElements, NULL, 311),
    NAME_FUNC_OFFSET( 3861, gl_dispatch_stub_312, gl_dispatch_stub_312, NULL, 312),
    NAME_FUNC_OFFSET( 3879, gl_dispatch_stub_313, gl_dispatch_stub_313, NULL, 313),
    NAME_FUNC_OFFSET( 3899, gl_dispatch_stub_314, gl_dispatch_stub_314, NULL, 314),
    NAME_FUNC_OFFSET( 3914, gl_dispatch_stub_315, gl_dispatch_stub_315, NULL, 315),
    NAME_FUNC_OFFSET( 3924, gl_dispatch_stub_316, gl_dispatch_stub_316, NULL, 316),
    NAME_FUNC_OFFSET( 3935, gl_dispatch_stub_317, gl_dispatch_stub_317, NULL, 317),
    NAME_FUNC_OFFSET( 3955, gl_dispatch_stub_318, gl_dispatch_stub_318, NULL, 318),
    NAME_FUNC_OFFSET( 3971, glPolygonOffset, glPolygonOffset, NULL, 319),
    NAME_FUNC_OFFSET( 3987, gl_dispatch_stub_320, gl_dispatch_stub_320, NULL, 320),
    NAME_FUNC_OFFSET( 4005, gl_dispatch_stub_321, gl_dispatch_stub_321, NULL, 321),
    NAME_FUNC_OFFSET( 4021, gl_dispatch_stub_322, gl_dispatch_stub_322, NULL, 322),
    NAME_FUNC_OFFSET( 4043, gl_dispatch_stub_323, gl_dispatch_stub_323, NULL, 323),
    NAME_FUNC_OFFSET( 4060, glCopyTexImage2D, glCopyTexImage2D, NULL, 324),
    NAME_FUNC_OFFSET( 4077, gl_dispatch_stub_325, gl_dispatch_stub_325, NULL, 325),
    NAME_FUNC_OFFSET( 4097, glCopyTexSubImage2D, glCopyTexSubImage2D, NULL, 326),
    NAME_FUNC_OFFSET( 4117, glDeleteTextures, glDeleteTextures, NULL, 327),
    NAME_FUNC_OFFSET( 4134, glGenTextures, glGenTextures, NULL, 328),
    NAME_FUNC_OFFSET( 4148, gl_dispatch_stub_329, gl_dispatch_stub_329, NULL, 329),
    NAME_FUNC_OFFSET( 4162, glIsTexture, glIsTexture, NULL, 330),
    NAME_FUNC_OFFSET( 4174, gl_dispatch_stub_331, gl_dispatch_stub_331, NULL, 331),
    NAME_FUNC_OFFSET( 4195, gl_dispatch_stub_332, gl_dispatch_stub_332, NULL, 332),
    NAME_FUNC_OFFSET( 4211, glTexSubImage2D, glTexSubImage2D, NULL, 333),
    NAME_FUNC_OFFSET( 4227, gl_dispatch_stub_334, gl_dispatch_stub_334, NULL, 334),
    NAME_FUNC_OFFSET( 4245, gl_dispatch_stub_335, gl_dispatch_stub_335, NULL, 335),
    NAME_FUNC_OFFSET( 4264, glBlendColor, glBlendColor, NULL, 336),
    NAME_FUNC_OFFSET( 4277, glBlendEquation, glBlendEquation, NULL, 337),
    NAME_FUNC_OFFSET( 4293, gl_dispatch_stub_338, gl_dispatch_stub_338, NULL, 338),
    NAME_FUNC_OFFSET( 4313, gl_dispatch_stub_339, gl_dispatch_stub_339, NULL, 339),
    NAME_FUNC_OFFSET( 4326, gl_dispatch_stub_340, gl_dispatch_stub_340, NULL, 340),
    NAME_FUNC_OFFSET( 4350, gl_dispatch_stub_341, gl_dispatch_stub_341, NULL, 341),
    NAME_FUNC_OFFSET( 4374, gl_dispatch_stub_342, gl_dispatch_stub_342, NULL, 342),
    NAME_FUNC_OFFSET( 4391, gl_dispatch_stub_343, gl_dispatch_stub_343, NULL, 343),
    NAME_FUNC_OFFSET( 4407, gl_dispatch_stub_344, gl_dispatch_stub_344, NULL, 344),
    NAME_FUNC_OFFSET( 4434, gl_dispatch_stub_345, gl_dispatch_stub_345, NULL, 345),
    NAME_FUNC_OFFSET( 4461, gl_dispatch_stub_346, gl_dispatch_stub_346, NULL, 346),
    NAME_FUNC_OFFSET( 4477, gl_dispatch_stub_347, gl_dispatch_stub_347, NULL, 347),
    NAME_FUNC_OFFSET( 4497, gl_dispatch_stub_348, gl_dispatch_stub_348, NULL, 348),
    NAME_FUNC_OFFSET( 4519, gl_dispatch_stub_349, gl_dispatch_stub_349, NULL, 349),
    NAME_FUNC_OFFSET( 4541, gl_dispatch_stub_350, gl_dispatch_stub_350, NULL, 350),
    NAME_FUNC_OFFSET( 4565, gl_dispatch_stub_351, gl_dispatch_stub_351, NULL, 351),
    NAME_FUNC_OFFSET( 4590, gl_dispatch_stub_352, gl_dispatch_stub_352, NULL, 352),
    NAME_FUNC_OFFSET( 4614, gl_dispatch_stub_353, gl_dispatch_stub_353, NULL, 353),
    NAME_FUNC_OFFSET( 4639, gl_dispatch_stub_354, gl_dispatch_stub_354, NULL, 354),
    NAME_FUNC_OFFSET( 4665, gl_dispatch_stub_355, gl_dispatch_stub_355, NULL, 355),
    NAME_FUNC_OFFSET( 4691, gl_dispatch_stub_356, gl_dispatch_stub_356, NULL, 356),
    NAME_FUNC_OFFSET( 4714, gl_dispatch_stub_357, gl_dispatch_stub_357, NULL, 357),
    NAME_FUNC_OFFSET( 4742, gl_dispatch_stub_358, gl_dispatch_stub_358, NULL, 358),
    NAME_FUNC_OFFSET( 4770, gl_dispatch_stub_359, gl_dispatch_stub_359, NULL, 359),
    NAME_FUNC_OFFSET( 4791, gl_dispatch_stub_360, gl_dispatch_stub_360, NULL, 360),
    NAME_FUNC_OFFSET( 4811, gl_dispatch_stub_361, gl_dispatch_stub_361, NULL, 361),
    NAME_FUNC_OFFSET( 4826, gl_dispatch_stub_362, gl_dispatch_stub_362, NULL, 362),
    NAME_FUNC_OFFSET( 4852, gl_dispatch_stub_363, gl_dispatch_stub_363, NULL, 363),
    NAME_FUNC_OFFSET( 4878, gl_dispatch_stub_364, gl_dispatch_stub_364, NULL, 364),
    NAME_FUNC_OFFSET( 4890, gl_dispatch_stub_365, gl_dispatch_stub_365, NULL, 365),
    NAME_FUNC_OFFSET( 4913, gl_dispatch_stub_366, gl_dispatch_stub_366, NULL, 366),
    NAME_FUNC_OFFSET( 4936, gl_dispatch_stub_367, gl_dispatch_stub_367, NULL, 367),
    NAME_FUNC_OFFSET( 4948, gl_dispatch_stub_368, gl_dispatch_stub_368, NULL, 368),
    NAME_FUNC_OFFSET( 4957, gl_dispatch_stub_369, gl_dispatch_stub_369, NULL, 369),
    NAME_FUNC_OFFSET( 4974, gl_dispatch_stub_370, gl_dispatch_stub_370, NULL, 370),
    NAME_FUNC_OFFSET( 4988, glTexImage3DOES, glTexImage3DOES, NULL, 371),
    NAME_FUNC_OFFSET( 5004, glTexSubImage3DOES, glTexSubImage3DOES, NULL, 372),
    NAME_FUNC_OFFSET( 5023, glCopyTexSubImage3DOES, glCopyTexSubImage3DOES, NULL, 373),
    NAME_FUNC_OFFSET( 5046, glActiveTexture, glActiveTexture, NULL, 374),
    NAME_FUNC_OFFSET( 5062, gl_dispatch_stub_375, gl_dispatch_stub_375, NULL, 375),
    NAME_FUNC_OFFSET( 5087, gl_dispatch_stub_376, gl_dispatch_stub_376, NULL, 376),
    NAME_FUNC_OFFSET( 5108, gl_dispatch_stub_377, gl_dispatch_stub_377, NULL, 377),
    NAME_FUNC_OFFSET( 5130, gl_dispatch_stub_378, gl_dispatch_stub_378, NULL, 378),
    NAME_FUNC_OFFSET( 5151, gl_dispatch_stub_379, gl_dispatch_stub_379, NULL, 379),
    NAME_FUNC_OFFSET( 5173, gl_dispatch_stub_380, gl_dispatch_stub_380, NULL, 380),
    NAME_FUNC_OFFSET( 5194, gl_dispatch_stub_381, gl_dispatch_stub_381, NULL, 381),
    NAME_FUNC_OFFSET( 5216, gl_dispatch_stub_382, gl_dispatch_stub_382, NULL, 382),
    NAME_FUNC_OFFSET( 5237, gl_dispatch_stub_383, gl_dispatch_stub_383, NULL, 383),
    NAME_FUNC_OFFSET( 5259, gl_dispatch_stub_384, gl_dispatch_stub_384, NULL, 384),
    NAME_FUNC_OFFSET( 5280, gl_dispatch_stub_385, gl_dispatch_stub_385, NULL, 385),
    NAME_FUNC_OFFSET( 5302, gl_dispatch_stub_386, gl_dispatch_stub_386, NULL, 386),
    NAME_FUNC_OFFSET( 5323, gl_dispatch_stub_387, gl_dispatch_stub_387, NULL, 387),
    NAME_FUNC_OFFSET( 5345, gl_dispatch_stub_388, gl_dispatch_stub_388, NULL, 388),
    NAME_FUNC_OFFSET( 5366, gl_dispatch_stub_389, gl_dispatch_stub_389, NULL, 389),
    NAME_FUNC_OFFSET( 5388, gl_dispatch_stub_390, gl_dispatch_stub_390, NULL, 390),
    NAME_FUNC_OFFSET( 5409, gl_dispatch_stub_391, gl_dispatch_stub_391, NULL, 391),
    NAME_FUNC_OFFSET( 5431, gl_dispatch_stub_392, gl_dispatch_stub_392, NULL, 392),
    NAME_FUNC_OFFSET( 5452, gl_dispatch_stub_393, gl_dispatch_stub_393, NULL, 393),
    NAME_FUNC_OFFSET( 5474, gl_dispatch_stub_394, gl_dispatch_stub_394, NULL, 394),
    NAME_FUNC_OFFSET( 5495, gl_dispatch_stub_395, gl_dispatch_stub_395, NULL, 395),
    NAME_FUNC_OFFSET( 5517, gl_dispatch_stub_396, gl_dispatch_stub_396, NULL, 396),
    NAME_FUNC_OFFSET( 5538, gl_dispatch_stub_397, gl_dispatch_stub_397, NULL, 397),
    NAME_FUNC_OFFSET( 5560, gl_dispatch_stub_398, gl_dispatch_stub_398, NULL, 398),
    NAME_FUNC_OFFSET( 5581, gl_dispatch_stub_399, gl_dispatch_stub_399, NULL, 399),
    NAME_FUNC_OFFSET( 5603, gl_dispatch_stub_400, gl_dispatch_stub_400, NULL, 400),
    NAME_FUNC_OFFSET( 5624, gl_dispatch_stub_401, gl_dispatch_stub_401, NULL, 401),
    NAME_FUNC_OFFSET( 5646, gl_dispatch_stub_402, gl_dispatch_stub_402, NULL, 402),
    NAME_FUNC_OFFSET( 5667, gl_dispatch_stub_403, gl_dispatch_stub_403, NULL, 403),
    NAME_FUNC_OFFSET( 5689, gl_dispatch_stub_404, gl_dispatch_stub_404, NULL, 404),
    NAME_FUNC_OFFSET( 5710, gl_dispatch_stub_405, gl_dispatch_stub_405, NULL, 405),
    NAME_FUNC_OFFSET( 5732, gl_dispatch_stub_406, gl_dispatch_stub_406, NULL, 406),
    NAME_FUNC_OFFSET( 5753, gl_dispatch_stub_407, gl_dispatch_stub_407, NULL, 407),
    NAME_FUNC_OFFSET( 5775, glGetBufferPointervOES, glGetBufferPointervOES, NULL, 408),
    NAME_FUNC_OFFSET( 5798, glMapBufferOES, glMapBufferOES, NULL, 409),
    NAME_FUNC_OFFSET( 5813, glUnmapBufferOES, glUnmapBufferOES, NULL, 410),
    NAME_FUNC_OFFSET( 5830, glCompressedTexImage3DOES, glCompressedTexImage3DOES, NULL, 411),
    NAME_FUNC_OFFSET( 5856, glCompressedTexSubImage3DOES, glCompressedTexSubImage3DOES, NULL, 412),
    NAME_FUNC_OFFSET( 5885, glFramebufferTexture3DOES, glFramebufferTexture3DOES, NULL, 413),
    NAME_FUNC_OFFSET( 5911, glGetProgramBinaryOES, glGetProgramBinaryOES, NULL, 414),
    NAME_FUNC_OFFSET( 5933, glProgramBinaryOES, glProgramBinaryOES, NULL, 415),
    NAME_FUNC_OFFSET( 5952, glMultiDrawArraysEXT, glMultiDrawArraysEXT, NULL, 416),
    NAME_FUNC_OFFSET( 5973, glMultiDrawElementsEXT, glMultiDrawElementsEXT, NULL, 417),
    NAME_FUNC_OFFSET( 5996, gl_dispatch_stub_418, gl_dispatch_stub_418, NULL, 418),
    NAME_FUNC_OFFSET( 6019, gl_dispatch_stub_419, gl_dispatch_stub_419, NULL, 419),
    NAME_FUNC_OFFSET( 6045, gl_dispatch_stub_420, gl_dispatch_stub_420, NULL, 420),
    NAME_FUNC_OFFSET( 6068, gl_dispatch_stub_421, gl_dispatch_stub_421, NULL, 421),
    NAME_FUNC_OFFSET( 6089, glEGLImageTargetRenderbufferStorageOES, glEGLImageTargetRenderbufferStorageOES, NULL, 422),
    NAME_FUNC_OFFSET( 6128, glEGLImageTargetTexture2DOES, glEGLImageTargetTexture2DOES, NULL, 423),
    NAME_FUNC_OFFSET( 6157, glCompressedTexImage2D, glCompressedTexImage2D, NULL, 424),
    NAME_FUNC_OFFSET( 6180, glCompressedTexSubImage2D, glCompressedTexSubImage2D, NULL, 425),
    NAME_FUNC_OFFSET( 6206, glSampleCoverage, glSampleCoverage, NULL, 426),
    NAME_FUNC_OFFSET( 6223, glBindBuffer, glBindBuffer, NULL, 427),
    NAME_FUNC_OFFSET( 6236, glBufferData, glBufferData, NULL, 428),
    NAME_FUNC_OFFSET( 6249, glBufferSubData, glBufferSubData, NULL, 429),
    NAME_FUNC_OFFSET( 6265, glDeleteBuffers, glDeleteBuffers, NULL, 430),
    NAME_FUNC_OFFSET( 6281, glGenBuffers, glGenBuffers, NULL, 431),
    NAME_FUNC_OFFSET( 6294, glGetBufferParameteriv, glGetBufferParameteriv, NULL, 432),
    NAME_FUNC_OFFSET( 6317, glIsBuffer, glIsBuffer, NULL, 433),
    NAME_FUNC_OFFSET( 6328, glAttachShader, glAttachShader, NULL, 434),
    NAME_FUNC_OFFSET( 6343, glBindAttribLocation, glBindAttribLocation, NULL, 435),
    NAME_FUNC_OFFSET( 6364, glBlendEquationSeparate, glBlendEquationSeparate, NULL, 436),
    NAME_FUNC_OFFSET( 6388, glCompileShader, glCompileShader, NULL, 437),
    NAME_FUNC_OFFSET( 6404, glCreateProgram, glCreateProgram, NULL, 438),
    NAME_FUNC_OFFSET( 6420, glCreateShader, glCreateShader, NULL, 439),
    NAME_FUNC_OFFSET( 6435, glDeleteProgram, glDeleteProgram, NULL, 440),
    NAME_FUNC_OFFSET( 6451, glDeleteShader, glDeleteShader, NULL, 441),
    NAME_FUNC_OFFSET( 6466, glDetachShader, glDetachShader, NULL, 442),
    NAME_FUNC_OFFSET( 6481, glDisableVertexAttribArray, glDisableVertexAttribArray, NULL, 443),
    NAME_FUNC_OFFSET( 6508, glEnableVertexAttribArray, glEnableVertexAttribArray, NULL, 444),
    NAME_FUNC_OFFSET( 6534, glGetActiveAttrib, glGetActiveAttrib, NULL, 445),
    NAME_FUNC_OFFSET( 6552, glGetActiveUniform, glGetActiveUniform, NULL, 446),
    NAME_FUNC_OFFSET( 6571, glGetAttachedShaders, glGetAttachedShaders, NULL, 447),
    NAME_FUNC_OFFSET( 6592, glGetAttribLocation, glGetAttribLocation, NULL, 448),
    NAME_FUNC_OFFSET( 6612, glGetProgramInfoLog, glGetProgramInfoLog, NULL, 449),
    NAME_FUNC_OFFSET( 6632, glGetProgramiv, glGetProgramiv, NULL, 450),
    NAME_FUNC_OFFSET( 6647, glGetShaderInfoLog, glGetShaderInfoLog, NULL, 451),
    NAME_FUNC_OFFSET( 6666, glGetShaderSource, glGetShaderSource, NULL, 452),
    NAME_FUNC_OFFSET( 6684, glGetShaderiv, glGetShaderiv, NULL, 453),
    NAME_FUNC_OFFSET( 6698, glGetUniformLocation, glGetUniformLocation, NULL, 454),
    NAME_FUNC_OFFSET( 6719, glGetUniformfv, glGetUniformfv, NULL, 455),
    NAME_FUNC_OFFSET( 6734, glGetUniformiv, glGetUniformiv, NULL, 456),
    NAME_FUNC_OFFSET( 6749, glGetVertexAttribPointerv, glGetVertexAttribPointerv, NULL, 457),
    NAME_FUNC_OFFSET( 6775, glGetVertexAttribfv, glGetVertexAttribfv, NULL, 458),
    NAME_FUNC_OFFSET( 6795, glGetVertexAttribiv, glGetVertexAttribiv, NULL, 459),
    NAME_FUNC_OFFSET( 6815, glIsProgram, glIsProgram, NULL, 460),
    NAME_FUNC_OFFSET( 6827, glIsShader, glIsShader, NULL, 461),
    NAME_FUNC_OFFSET( 6838, glLinkProgram, glLinkProgram, NULL, 462),
    NAME_FUNC_OFFSET( 6852, glShaderSource, glShaderSource, NULL, 463),
    NAME_FUNC_OFFSET( 6867, glStencilFuncSeparate, glStencilFuncSeparate, NULL, 464),
    NAME_FUNC_OFFSET( 6889, glStencilMaskSeparate, glStencilMaskSeparate, NULL, 465),
    NAME_FUNC_OFFSET( 6911, glStencilOpSeparate, glStencilOpSeparate, NULL, 466),
    NAME_FUNC_OFFSET( 6931, glUniform1f, glUniform1f, NULL, 467),
    NAME_FUNC_OFFSET( 6943, glUniform1fv, glUniform1fv, NULL, 468),
    NAME_FUNC_OFFSET( 6956, glUniform1i, glUniform1i, NULL, 469),
    NAME_FUNC_OFFSET( 6968, glUniform1iv, glUniform1iv, NULL, 470),
    NAME_FUNC_OFFSET( 6981, glUniform2f, glUniform2f, NULL, 471),
    NAME_FUNC_OFFSET( 6993, glUniform2fv, glUniform2fv, NULL, 472),
    NAME_FUNC_OFFSET( 7006, glUniform2i, glUniform2i, NULL, 473),
    NAME_FUNC_OFFSET( 7018, glUniform2iv, glUniform2iv, NULL, 474),
    NAME_FUNC_OFFSET( 7031, glUniform3f, glUniform3f, NULL, 475),
    NAME_FUNC_OFFSET( 7043, glUniform3fv, glUniform3fv, NULL, 476),
    NAME_FUNC_OFFSET( 7056, glUniform3i, glUniform3i, NULL, 477),
    NAME_FUNC_OFFSET( 7068, glUniform3iv, glUniform3iv, NULL, 478),
    NAME_FUNC_OFFSET( 7081, glUniform4f, glUniform4f, NULL, 479),
    NAME_FUNC_OFFSET( 7093, glUniform4fv, glUniform4fv, NULL, 480),
    NAME_FUNC_OFFSET( 7106, glUniform4i, glUniform4i, NULL, 481),
    NAME_FUNC_OFFSET( 7118, glUniform4iv, glUniform4iv, NULL, 482),
    NAME_FUNC_OFFSET( 7131, glUniformMatrix2fv, glUniformMatrix2fv, NULL, 483),
    NAME_FUNC_OFFSET( 7150, glUniformMatrix3fv, glUniformMatrix3fv, NULL, 484),
    NAME_FUNC_OFFSET( 7169, glUniformMatrix4fv, glUniformMatrix4fv, NULL, 485),
    NAME_FUNC_OFFSET( 7188, glUseProgram, glUseProgram, NULL, 486),
    NAME_FUNC_OFFSET( 7201, glValidateProgram, glValidateProgram, NULL, 487),
    NAME_FUNC_OFFSET( 7219, glVertexAttrib1f, glVertexAttrib1f, NULL, 488),
    NAME_FUNC_OFFSET( 7236, glVertexAttrib1fv, glVertexAttrib1fv, NULL, 489),
    NAME_FUNC_OFFSET( 7254, glVertexAttrib2f, glVertexAttrib2f, NULL, 490),
    NAME_FUNC_OFFSET( 7271, glVertexAttrib2fv, glVertexAttrib2fv, NULL, 491),
    NAME_FUNC_OFFSET( 7289, glVertexAttrib3f, glVertexAttrib3f, NULL, 492),
    NAME_FUNC_OFFSET( 7306, glVertexAttrib3fv, glVertexAttrib3fv, NULL, 493),
    NAME_FUNC_OFFSET( 7324, glVertexAttrib4f, glVertexAttrib4f, NULL, 494),
    NAME_FUNC_OFFSET( 7341, glVertexAttrib4fv, glVertexAttrib4fv, NULL, 495),
    NAME_FUNC_OFFSET( 7359, glVertexAttribPointer, glVertexAttribPointer, NULL, 496),
    NAME_FUNC_OFFSET( 7381, glBlendFuncSeparate, glBlendFuncSeparate, NULL, 497),
    NAME_FUNC_OFFSET( 7401, glBindFramebuffer, glBindFramebuffer, NULL, 498),
    NAME_FUNC_OFFSET( 7419, glBindRenderbuffer, glBindRenderbuffer, NULL, 499),
    NAME_FUNC_OFFSET( 7438, glCheckFramebufferStatus, glCheckFramebufferStatus, NULL, 500),
    NAME_FUNC_OFFSET( 7463, glClearDepthf, glClearDepthf, NULL, 501),
    NAME_FUNC_OFFSET( 7477, glDeleteFramebuffers, glDeleteFramebuffers, NULL, 502),
    NAME_FUNC_OFFSET( 7498, glDeleteRenderbuffers, glDeleteRenderbuffers, NULL, 503),
    NAME_FUNC_OFFSET( 7520, glDepthRangef, glDepthRangef, NULL, 504),
    NAME_FUNC_OFFSET( 7534, glFramebufferRenderbuffer, glFramebufferRenderbuffer, NULL, 505),
    NAME_FUNC_OFFSET( 7560, glFramebufferTexture2D, glFramebufferTexture2D, NULL, 506),
    NAME_FUNC_OFFSET( 7583, glGenFramebuffers, glGenFramebuffers, NULL, 507),
    NAME_FUNC_OFFSET( 7601, glGenRenderbuffers, glGenRenderbuffers, NULL, 508),
    NAME_FUNC_OFFSET( 7620, glGenerateMipmap, glGenerateMipmap, NULL, 509),
    NAME_FUNC_OFFSET( 7637, glGetFramebufferAttachmentParameteriv, glGetFramebufferAttachmentParameteriv, NULL, 510),
    NAME_FUNC_OFFSET( 7675, glGetRenderbufferParameteriv, glGetRenderbufferParameteriv, NULL, 511),
    NAME_FUNC_OFFSET( 7704, glGetShaderPrecisionFormat, glGetShaderPrecisionFormat, NULL, 512),
    NAME_FUNC_OFFSET( 7731, glIsFramebuffer, glIsFramebuffer, NULL, 513),
    NAME_FUNC_OFFSET( 7747, glIsRenderbuffer, glIsRenderbuffer, NULL, 514),
    NAME_FUNC_OFFSET( 7764, glReleaseShaderCompiler, glReleaseShaderCompiler, NULL, 515),
    NAME_FUNC_OFFSET( 7788, glRenderbufferStorage, glRenderbufferStorage, NULL, 516),
    NAME_FUNC_OFFSET( 7810, glShaderBinary, glShaderBinary, NULL, 517),
    NAME_FUNC_OFFSET( 7825, glTexImage3DOES, glTexImage3DOES, NULL, 371),
    NAME_FUNC_OFFSET( 7838, glTexSubImage3DOES, glTexSubImage3DOES, NULL, 372),
    NAME_FUNC_OFFSET( 7854, glCopyTexSubImage3DOES, glCopyTexSubImage3DOES, NULL, 373),
    NAME_FUNC_OFFSET( 7874, glActiveTexture, glActiveTexture, NULL, 374),
    NAME_FUNC_OFFSET(-1, NULL, NULL, NULL, 0)
};

#undef NAME_FUNC_OFFSET
