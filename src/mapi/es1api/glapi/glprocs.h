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
    "glGetBufferPointervOES\0"
    "glMapBufferOES\0"
    "glUnmapBufferOES\0"
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
    "glPointParameterf\0"
    "glPointParameterfv\0"
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

/* OpenGL ES specific prototypes */

/* category GL_OES_EGL_image */
GLAPI void GLAPIENTRY glEGLImageTargetRenderbufferStorageOES(GLenum target, GLvoid * writeOffset);
GLAPI void GLAPIENTRY glEGLImageTargetTexture2DOES(GLenum target, GLvoid * writeOffset);
/* category GL_OES_blend_equation_separate */
GLAPI void GLAPIENTRY glBlendEquationSeparateOES(GLenum modeRGB, GLenum modeA);
/* category GL_OES_blend_func_separate */
GLAPI void GLAPIENTRY glBlendFuncSeparateOES(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
/* category GL_OES_blend_subtract */
GLAPI void GLAPIENTRY glBlendEquationOES(GLenum mode);
/* category GL_OES_draw_texture */
GLAPI void GLAPIENTRY glDrawTexfOES(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
GLAPI void GLAPIENTRY glDrawTexfvOES(const GLfloat * coords);
GLAPI void GLAPIENTRY glDrawTexiOES(GLint x, GLint y, GLint z, GLint width, GLint height);
GLAPI void GLAPIENTRY glDrawTexivOES(const GLint * coords);
GLAPI void GLAPIENTRY glDrawTexsOES(GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);
GLAPI void GLAPIENTRY glDrawTexsvOES(const GLshort * coords);
GLAPI void GLAPIENTRY glDrawTexxOES(GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);
GLAPI void GLAPIENTRY glDrawTexxvOES(const GLfixed * coords);
/* category GL_OES_fixed_point */
GLAPI void GLAPIENTRY glAlphaFuncxOES(GLenum func, GLclampx ref);
GLAPI void GLAPIENTRY glClearColorxOES(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);
GLAPI void GLAPIENTRY glClearDepthxOES(GLclampx depth);
GLAPI void GLAPIENTRY glColor4xOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GLAPI void GLAPIENTRY glDepthRangexOES(GLclampx zNear, GLclampx zFar);
GLAPI void GLAPIENTRY glFogxOES(GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glFogxvOES(GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glFrustumxOES(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
GLAPI void GLAPIENTRY glLightModelxOES(GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glLightModelxvOES(GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glLightxOES(GLenum light, GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glLightxvOES(GLenum light, GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glLineWidthxOES(GLfixed width);
GLAPI void GLAPIENTRY glLoadMatrixxOES(const GLfixed * m);
GLAPI void GLAPIENTRY glMaterialxOES(GLenum face, GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glMaterialxvOES(GLenum face, GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glMultMatrixxOES(const GLfixed * m);
GLAPI void GLAPIENTRY glMultiTexCoord4xOES(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GLAPI void GLAPIENTRY glNormal3xOES(GLfixed nx, GLfixed ny, GLfixed nz);
GLAPI void GLAPIENTRY glOrthoxOES(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
GLAPI void GLAPIENTRY glPointSizexOES(GLfixed size);
GLAPI void GLAPIENTRY glPolygonOffsetxOES(GLfixed factor, GLfixed units);
GLAPI void GLAPIENTRY glRotatexOES(GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GLAPI void GLAPIENTRY glSampleCoveragexOES(GLclampx value, GLboolean invert);
GLAPI void GLAPIENTRY glScalexOES(GLfixed x, GLfixed y, GLfixed z);
GLAPI void GLAPIENTRY glTexEnvxOES(GLenum target, GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glTexEnvxvOES(GLenum target, GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glTexParameterxOES(GLenum target, GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glTranslatexOES(GLfixed x, GLfixed y, GLfixed z);
GLAPI void GLAPIENTRY glClipPlanexOES(GLenum plane, const GLfixed * equation);
GLAPI void GLAPIENTRY glGetClipPlanexOES(GLenum plane, GLfixed * equation);
GLAPI void GLAPIENTRY glGetFixedvOES(GLenum pname, GLfixed * params);
GLAPI void GLAPIENTRY glGetLightxvOES(GLenum light, GLenum pname, GLfixed * params);
GLAPI void GLAPIENTRY glGetMaterialxvOES(GLenum face, GLenum pname, GLfixed * params);
GLAPI void GLAPIENTRY glGetTexEnvxvOES(GLenum target, GLenum pname, GLfixed * params);
GLAPI void GLAPIENTRY glGetTexParameterxvOES(GLenum target, GLenum pname, GLfixed * params);
GLAPI void GLAPIENTRY glPointParameterxOES(GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glPointParameterxvOES(GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glTexParameterxvOES(GLenum target, GLenum pname, const GLfixed * params);
/* category GL_OES_framebuffer_object */
GLAPI void GLAPIENTRY glBindFramebufferOES(GLenum target, GLuint framebuffer);
GLAPI void GLAPIENTRY glBindRenderbufferOES(GLenum target, GLuint renderbuffer);
GLAPI GLenum GLAPIENTRY glCheckFramebufferStatusOES(GLenum target);
GLAPI void GLAPIENTRY glDeleteFramebuffersOES(GLsizei n, const GLuint * framebuffers);
GLAPI void GLAPIENTRY glDeleteRenderbuffersOES(GLsizei n, const GLuint * renderbuffers);
GLAPI void GLAPIENTRY glFramebufferRenderbufferOES(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GLAPI void GLAPIENTRY glFramebufferTexture2DOES(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GLAPI void GLAPIENTRY glGenFramebuffersOES(GLsizei n, GLuint * framebuffers);
GLAPI void GLAPIENTRY glGenRenderbuffersOES(GLsizei n, GLuint * renderbuffers);
GLAPI void GLAPIENTRY glGenerateMipmapOES(GLenum target);
GLAPI void GLAPIENTRY glGetFramebufferAttachmentParameterivOES(GLenum target, GLenum attachment, GLenum pname, GLint * params);
GLAPI void GLAPIENTRY glGetRenderbufferParameterivOES(GLenum target, GLenum pname, GLint * params);
GLAPI GLboolean GLAPIENTRY glIsFramebufferOES(GLuint framebuffer);
GLAPI GLboolean GLAPIENTRY glIsRenderbufferOES(GLuint renderbuffer);
GLAPI void GLAPIENTRY glRenderbufferStorageOES(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
/* category GL_OES_mapbuffer */
GLAPI void GLAPIENTRY glGetBufferPointervOES(GLenum target, GLenum pname, GLvoid ** params);
GLAPI GLvoid * GLAPIENTRY glMapBufferOES(GLenum target, GLenum access);
GLAPI GLboolean GLAPIENTRY glUnmapBufferOES(GLenum target);
/* category GL_OES_point_size_array */
GLAPI void GLAPIENTRY glPointSizePointerOES(GLenum type, GLsizei stride, const GLvoid * pointer);
/* category GL_OES_query_matrix */
GLAPI GLbitfield GLAPIENTRY glQueryMatrixxOES(GLfixed * mantissa, GLint * exponent);
/* category GL_OES_single_precision */
GLAPI void GLAPIENTRY glClearDepthfOES(GLclampf depth);
GLAPI void GLAPIENTRY glDepthRangefOES(GLclampf zNear, GLclampf zFar);
GLAPI void GLAPIENTRY glFrustumfOES(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
GLAPI void GLAPIENTRY glOrthofOES(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
GLAPI void GLAPIENTRY glClipPlanefOES(GLenum plane, const GLfloat * equation);
GLAPI void GLAPIENTRY glGetClipPlanefOES(GLenum plane, GLfloat * equation);
/* category GL_OES_texture_cube_map */
GLAPI void GLAPIENTRY glTexGenfOES(GLenum coord, GLenum pname, GLfloat param);
GLAPI void GLAPIENTRY glTexGenfvOES(GLenum coord, GLenum pname, const GLfloat * params);
GLAPI void GLAPIENTRY glTexGeniOES(GLenum coord, GLenum pname, GLint param);
GLAPI void GLAPIENTRY glTexGenivOES(GLenum coord, GLenum pname, const GLint * params);
GLAPI void GLAPIENTRY glGetTexGenfvOES(GLenum coord, GLenum pname, GLfloat * params);
GLAPI void GLAPIENTRY glGetTexGenivOES(GLenum coord, GLenum pname, GLint * params);
GLAPI void GLAPIENTRY glGetTexGenxvOES(GLenum coord, GLenum pname, GLfixed * params);
GLAPI void GLAPIENTRY glTexGenxOES(GLenum coord, GLenum pname, GLint param);
GLAPI void GLAPIENTRY glTexGenxvOES(GLenum coord, GLenum pname, const GLfixed * params);
/* category es1.0 */
GLAPI void GLAPIENTRY glAlphaFuncx(GLenum func, GLclampx ref);
GLAPI void GLAPIENTRY glClearColorx(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);
GLAPI void GLAPIENTRY glClearDepthf(GLclampf depth);
GLAPI void GLAPIENTRY glClearDepthx(GLclampx depth);
GLAPI void GLAPIENTRY glColor4x(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GLAPI void GLAPIENTRY glDepthRangef(GLclampf zNear, GLclampf zFar);
GLAPI void GLAPIENTRY glDepthRangex(GLclampx zNear, GLclampx zFar);
GLAPI void GLAPIENTRY glFogx(GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glFogxv(GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glFrustumf(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
GLAPI void GLAPIENTRY glFrustumx(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
GLAPI void GLAPIENTRY glLightModelx(GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glLightModelxv(GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glLightx(GLenum light, GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glLightxv(GLenum light, GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glLineWidthx(GLfixed width);
GLAPI void GLAPIENTRY glLoadMatrixx(const GLfixed * m);
GLAPI void GLAPIENTRY glMaterialx(GLenum face, GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glMaterialxv(GLenum face, GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glMultMatrixx(const GLfixed * m);
GLAPI void GLAPIENTRY glMultiTexCoord4x(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GLAPI void GLAPIENTRY glNormal3x(GLfixed nx, GLfixed ny, GLfixed nz);
GLAPI void GLAPIENTRY glOrthof(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
GLAPI void GLAPIENTRY glOrthox(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
GLAPI void GLAPIENTRY glPointSizex(GLfixed size);
GLAPI void GLAPIENTRY glPolygonOffsetx(GLfixed factor, GLfixed units);
GLAPI void GLAPIENTRY glRotatex(GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GLAPI void GLAPIENTRY glSampleCoveragex(GLclampx value, GLboolean invert);
GLAPI void GLAPIENTRY glScalex(GLfixed x, GLfixed y, GLfixed z);
GLAPI void GLAPIENTRY glTexEnvx(GLenum target, GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glTexEnvxv(GLenum target, GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glTexParameterx(GLenum target, GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glTranslatex(GLfixed x, GLfixed y, GLfixed z);
/* category es1.1 */
GLAPI void GLAPIENTRY glClipPlanef(GLenum plane, const GLfloat * equation);
GLAPI void GLAPIENTRY glClipPlanex(GLenum plane, const GLfixed * equation);
GLAPI void GLAPIENTRY glGetClipPlanef(GLenum plane, GLfloat * equation);
GLAPI void GLAPIENTRY glGetClipPlanex(GLenum plane, GLfixed * equation);
GLAPI void GLAPIENTRY glGetFixedv(GLenum pname, GLfixed * params);
GLAPI void GLAPIENTRY glGetLightxv(GLenum light, GLenum pname, GLfixed * params);
GLAPI void GLAPIENTRY glGetMaterialxv(GLenum face, GLenum pname, GLfixed * params);
GLAPI void GLAPIENTRY glGetTexEnvxv(GLenum target, GLenum pname, GLfixed * params);
GLAPI void GLAPIENTRY glGetTexParameterxv(GLenum target, GLenum pname, GLfixed * params);
GLAPI void GLAPIENTRY glPointParameterx(GLenum pname, GLfixed param);
GLAPI void GLAPIENTRY glPointParameterxv(GLenum pname, const GLfixed * params);
GLAPI void GLAPIENTRY glTexParameterxv(GLenum target, GLenum pname, const GLfixed * params);

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
    NAME_FUNC_OFFSET(  312, glColor4f, glColor4f, NULL, 29),
    NAME_FUNC_OFFSET(  322, gl_dispatch_stub_30, gl_dispatch_stub_30, NULL, 30),
    NAME_FUNC_OFFSET(  333, gl_dispatch_stub_31, gl_dispatch_stub_31, NULL, 31),
    NAME_FUNC_OFFSET(  343, gl_dispatch_stub_32, gl_dispatch_stub_32, NULL, 32),
    NAME_FUNC_OFFSET(  354, gl_dispatch_stub_33, gl_dispatch_stub_33, NULL, 33),
    NAME_FUNC_OFFSET(  364, gl_dispatch_stub_34, gl_dispatch_stub_34, NULL, 34),
    NAME_FUNC_OFFSET(  375, glColor4ub, glColor4ub, NULL, 35),
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
    NAME_FUNC_OFFSET(  595, glNormal3f, glNormal3f, NULL, 56),
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
    NAME_FUNC_OFFSET( 1827, glFogf, glFogf, NULL, 153),
    NAME_FUNC_OFFSET( 1834, glFogfv, glFogfv, NULL, 154),
    NAME_FUNC_OFFSET( 1842, gl_dispatch_stub_155, gl_dispatch_stub_155, NULL, 155),
    NAME_FUNC_OFFSET( 1849, gl_dispatch_stub_156, gl_dispatch_stub_156, NULL, 156),
    NAME_FUNC_OFFSET( 1857, glFrontFace, glFrontFace, NULL, 157),
    NAME_FUNC_OFFSET( 1869, glHint, glHint, NULL, 158),
    NAME_FUNC_OFFSET( 1876, glLightf, glLightf, NULL, 159),
    NAME_FUNC_OFFSET( 1885, glLightfv, glLightfv, NULL, 160),
    NAME_FUNC_OFFSET( 1895, gl_dispatch_stub_161, gl_dispatch_stub_161, NULL, 161),
    NAME_FUNC_OFFSET( 1904, gl_dispatch_stub_162, gl_dispatch_stub_162, NULL, 162),
    NAME_FUNC_OFFSET( 1914, glLightModelf, glLightModelf, NULL, 163),
    NAME_FUNC_OFFSET( 1928, glLightModelfv, glLightModelfv, NULL, 164),
    NAME_FUNC_OFFSET( 1943, gl_dispatch_stub_165, gl_dispatch_stub_165, NULL, 165),
    NAME_FUNC_OFFSET( 1957, gl_dispatch_stub_166, gl_dispatch_stub_166, NULL, 166),
    NAME_FUNC_OFFSET( 1972, gl_dispatch_stub_167, gl_dispatch_stub_167, NULL, 167),
    NAME_FUNC_OFFSET( 1986, glLineWidth, glLineWidth, NULL, 168),
    NAME_FUNC_OFFSET( 1998, glMaterialf, glMaterialf, NULL, 169),
    NAME_FUNC_OFFSET( 2010, glMaterialfv, glMaterialfv, NULL, 170),
    NAME_FUNC_OFFSET( 2023, gl_dispatch_stub_171, gl_dispatch_stub_171, NULL, 171),
    NAME_FUNC_OFFSET( 2035, gl_dispatch_stub_172, gl_dispatch_stub_172, NULL, 172),
    NAME_FUNC_OFFSET( 2048, glPointSize, glPointSize, NULL, 173),
    NAME_FUNC_OFFSET( 2060, gl_dispatch_stub_174, gl_dispatch_stub_174, NULL, 174),
    NAME_FUNC_OFFSET( 2074, gl_dispatch_stub_175, gl_dispatch_stub_175, NULL, 175),
    NAME_FUNC_OFFSET( 2091, glScissor, glScissor, NULL, 176),
    NAME_FUNC_OFFSET( 2101, glShadeModel, glShadeModel, NULL, 177),
    NAME_FUNC_OFFSET( 2114, glTexParameterf, glTexParameterf, NULL, 178),
    NAME_FUNC_OFFSET( 2130, glTexParameterfv, glTexParameterfv, NULL, 179),
    NAME_FUNC_OFFSET( 2147, glTexParameteri, glTexParameteri, NULL, 180),
    NAME_FUNC_OFFSET( 2163, glTexParameteriv, glTexParameteriv, NULL, 181),
    NAME_FUNC_OFFSET( 2180, gl_dispatch_stub_182, gl_dispatch_stub_182, NULL, 182),
    NAME_FUNC_OFFSET( 2193, glTexImage2D, glTexImage2D, NULL, 183),
    NAME_FUNC_OFFSET( 2206, glTexEnvf, glTexEnvf, NULL, 184),
    NAME_FUNC_OFFSET( 2216, glTexEnvfv, glTexEnvfv, NULL, 185),
    NAME_FUNC_OFFSET( 2227, glTexEnvi, glTexEnvi, NULL, 186),
    NAME_FUNC_OFFSET( 2237, glTexEnviv, glTexEnviv, NULL, 187),
    NAME_FUNC_OFFSET( 2248, gl_dispatch_stub_188, gl_dispatch_stub_188, NULL, 188),
    NAME_FUNC_OFFSET( 2258, gl_dispatch_stub_189, gl_dispatch_stub_189, NULL, 189),
    NAME_FUNC_OFFSET( 2269, glTexGenfOES, glTexGenfOES, NULL, 190),
    NAME_FUNC_OFFSET( 2282, glTexGenfvOES, glTexGenfvOES, NULL, 191),
    NAME_FUNC_OFFSET( 2296, glTexGeniOES, glTexGeniOES, NULL, 192),
    NAME_FUNC_OFFSET( 2309, glTexGenivOES, glTexGenivOES, NULL, 193),
    NAME_FUNC_OFFSET( 2323, gl_dispatch_stub_194, gl_dispatch_stub_194, NULL, 194),
    NAME_FUNC_OFFSET( 2340, gl_dispatch_stub_195, gl_dispatch_stub_195, NULL, 195),
    NAME_FUNC_OFFSET( 2355, gl_dispatch_stub_196, gl_dispatch_stub_196, NULL, 196),
    NAME_FUNC_OFFSET( 2368, gl_dispatch_stub_197, gl_dispatch_stub_197, NULL, 197),
    NAME_FUNC_OFFSET( 2380, gl_dispatch_stub_198, gl_dispatch_stub_198, NULL, 198),
    NAME_FUNC_OFFSET( 2391, gl_dispatch_stub_199, gl_dispatch_stub_199, NULL, 199),
    NAME_FUNC_OFFSET( 2405, gl_dispatch_stub_200, gl_dispatch_stub_200, NULL, 200),
    NAME_FUNC_OFFSET( 2415, gl_dispatch_stub_201, gl_dispatch_stub_201, NULL, 201),
    NAME_FUNC_OFFSET( 2426, gl_dispatch_stub_202, gl_dispatch_stub_202, NULL, 202),
    NAME_FUNC_OFFSET( 2439, glClear, glClear, NULL, 203),
    NAME_FUNC_OFFSET( 2447, gl_dispatch_stub_204, gl_dispatch_stub_204, NULL, 204),
    NAME_FUNC_OFFSET( 2460, gl_dispatch_stub_205, gl_dispatch_stub_205, NULL, 205),
    NAME_FUNC_OFFSET( 2473, glClearColor, glClearColor, NULL, 206),
    NAME_FUNC_OFFSET( 2486, glClearStencil, glClearStencil, NULL, 207),
    NAME_FUNC_OFFSET( 2501, gl_dispatch_stub_208, gl_dispatch_stub_208, NULL, 208),
    NAME_FUNC_OFFSET( 2514, glStencilMask, glStencilMask, NULL, 209),
    NAME_FUNC_OFFSET( 2528, glColorMask, glColorMask, NULL, 210),
    NAME_FUNC_OFFSET( 2540, glDepthMask, glDepthMask, NULL, 211),
    NAME_FUNC_OFFSET( 2552, gl_dispatch_stub_212, gl_dispatch_stub_212, NULL, 212),
    NAME_FUNC_OFFSET( 2564, gl_dispatch_stub_213, gl_dispatch_stub_213, NULL, 213),
    NAME_FUNC_OFFSET( 2572, glDisable, glDisable, NULL, 214),
    NAME_FUNC_OFFSET( 2582, glEnable, glEnable, NULL, 215),
    NAME_FUNC_OFFSET( 2591, glFinish, glFinish, NULL, 216),
    NAME_FUNC_OFFSET( 2600, glFlush, glFlush, NULL, 217),
    NAME_FUNC_OFFSET( 2608, gl_dispatch_stub_218, gl_dispatch_stub_218, NULL, 218),
    NAME_FUNC_OFFSET( 2620, gl_dispatch_stub_219, gl_dispatch_stub_219, NULL, 219),
    NAME_FUNC_OFFSET( 2633, gl_dispatch_stub_220, gl_dispatch_stub_220, NULL, 220),
    NAME_FUNC_OFFSET( 2641, gl_dispatch_stub_221, gl_dispatch_stub_221, NULL, 221),
    NAME_FUNC_OFFSET( 2649, gl_dispatch_stub_222, gl_dispatch_stub_222, NULL, 222),
    NAME_FUNC_OFFSET( 2657, gl_dispatch_stub_223, gl_dispatch_stub_223, NULL, 223),
    NAME_FUNC_OFFSET( 2665, gl_dispatch_stub_224, gl_dispatch_stub_224, NULL, 224),
    NAME_FUNC_OFFSET( 2677, gl_dispatch_stub_225, gl_dispatch_stub_225, NULL, 225),
    NAME_FUNC_OFFSET( 2689, gl_dispatch_stub_226, gl_dispatch_stub_226, NULL, 226),
    NAME_FUNC_OFFSET( 2701, gl_dispatch_stub_227, gl_dispatch_stub_227, NULL, 227),
    NAME_FUNC_OFFSET( 2713, gl_dispatch_stub_228, gl_dispatch_stub_228, NULL, 228),
    NAME_FUNC_OFFSET( 2727, gl_dispatch_stub_229, gl_dispatch_stub_229, NULL, 229),
    NAME_FUNC_OFFSET( 2742, gl_dispatch_stub_230, gl_dispatch_stub_230, NULL, 230),
    NAME_FUNC_OFFSET( 2756, gl_dispatch_stub_231, gl_dispatch_stub_231, NULL, 231),
    NAME_FUNC_OFFSET( 2771, gl_dispatch_stub_232, gl_dispatch_stub_232, NULL, 232),
    NAME_FUNC_OFFSET( 2785, gl_dispatch_stub_233, gl_dispatch_stub_233, NULL, 233),
    NAME_FUNC_OFFSET( 2800, gl_dispatch_stub_234, gl_dispatch_stub_234, NULL, 234),
    NAME_FUNC_OFFSET( 2814, gl_dispatch_stub_235, gl_dispatch_stub_235, NULL, 235),
    NAME_FUNC_OFFSET( 2829, gl_dispatch_stub_236, gl_dispatch_stub_236, NULL, 236),
    NAME_FUNC_OFFSET( 2841, gl_dispatch_stub_237, gl_dispatch_stub_237, NULL, 237),
    NAME_FUNC_OFFSET( 2854, gl_dispatch_stub_238, gl_dispatch_stub_238, NULL, 238),
    NAME_FUNC_OFFSET( 2866, gl_dispatch_stub_239, gl_dispatch_stub_239, NULL, 239),
    NAME_FUNC_OFFSET( 2879, glAlphaFunc, glAlphaFunc, NULL, 240),
    NAME_FUNC_OFFSET( 2891, glBlendFunc, glBlendFunc, NULL, 241),
    NAME_FUNC_OFFSET( 2903, glLogicOp, glLogicOp, NULL, 242),
    NAME_FUNC_OFFSET( 2913, glStencilFunc, glStencilFunc, NULL, 243),
    NAME_FUNC_OFFSET( 2927, glStencilOp, glStencilOp, NULL, 244),
    NAME_FUNC_OFFSET( 2939, glDepthFunc, glDepthFunc, NULL, 245),
    NAME_FUNC_OFFSET( 2951, gl_dispatch_stub_246, gl_dispatch_stub_246, NULL, 246),
    NAME_FUNC_OFFSET( 2963, gl_dispatch_stub_247, gl_dispatch_stub_247, NULL, 247),
    NAME_FUNC_OFFSET( 2980, gl_dispatch_stub_248, gl_dispatch_stub_248, NULL, 248),
    NAME_FUNC_OFFSET( 2997, gl_dispatch_stub_249, gl_dispatch_stub_249, NULL, 249),
    NAME_FUNC_OFFSET( 3011, glPixelStorei, glPixelStorei, NULL, 250),
    NAME_FUNC_OFFSET( 3025, gl_dispatch_stub_251, gl_dispatch_stub_251, NULL, 251),
    NAME_FUNC_OFFSET( 3038, gl_dispatch_stub_252, gl_dispatch_stub_252, NULL, 252),
    NAME_FUNC_OFFSET( 3052, gl_dispatch_stub_253, gl_dispatch_stub_253, NULL, 253),
    NAME_FUNC_OFFSET( 3066, gl_dispatch_stub_254, gl_dispatch_stub_254, NULL, 254),
    NAME_FUNC_OFFSET( 3079, gl_dispatch_stub_255, gl_dispatch_stub_255, NULL, 255),
    NAME_FUNC_OFFSET( 3092, glReadPixels, glReadPixels, NULL, 256),
    NAME_FUNC_OFFSET( 3105, gl_dispatch_stub_257, gl_dispatch_stub_257, NULL, 257),
    NAME_FUNC_OFFSET( 3118, glGetBooleanv, glGetBooleanv, NULL, 258),
    NAME_FUNC_OFFSET( 3132, gl_dispatch_stub_259, gl_dispatch_stub_259, NULL, 259),
    NAME_FUNC_OFFSET( 3147, gl_dispatch_stub_260, gl_dispatch_stub_260, NULL, 260),
    NAME_FUNC_OFFSET( 3160, glGetError, glGetError, NULL, 261),
    NAME_FUNC_OFFSET( 3171, glGetFloatv, glGetFloatv, NULL, 262),
    NAME_FUNC_OFFSET( 3183, glGetIntegerv, glGetIntegerv, NULL, 263),
    NAME_FUNC_OFFSET( 3197, glGetLightfv, glGetLightfv, NULL, 264),
    NAME_FUNC_OFFSET( 3210, gl_dispatch_stub_265, gl_dispatch_stub_265, NULL, 265),
    NAME_FUNC_OFFSET( 3223, gl_dispatch_stub_266, gl_dispatch_stub_266, NULL, 266),
    NAME_FUNC_OFFSET( 3234, gl_dispatch_stub_267, gl_dispatch_stub_267, NULL, 267),
    NAME_FUNC_OFFSET( 3245, gl_dispatch_stub_268, gl_dispatch_stub_268, NULL, 268),
    NAME_FUNC_OFFSET( 3256, glGetMaterialfv, glGetMaterialfv, NULL, 269),
    NAME_FUNC_OFFSET( 3272, gl_dispatch_stub_270, gl_dispatch_stub_270, NULL, 270),
    NAME_FUNC_OFFSET( 3288, gl_dispatch_stub_271, gl_dispatch_stub_271, NULL, 271),
    NAME_FUNC_OFFSET( 3304, gl_dispatch_stub_272, gl_dispatch_stub_272, NULL, 272),
    NAME_FUNC_OFFSET( 3321, gl_dispatch_stub_273, gl_dispatch_stub_273, NULL, 273),
    NAME_FUNC_OFFSET( 3338, gl_dispatch_stub_274, gl_dispatch_stub_274, NULL, 274),
    NAME_FUNC_OFFSET( 3358, glGetString, glGetString, NULL, 275),
    NAME_FUNC_OFFSET( 3370, glGetTexEnvfv, glGetTexEnvfv, NULL, 276),
    NAME_FUNC_OFFSET( 3384, glGetTexEnviv, glGetTexEnviv, NULL, 277),
    NAME_FUNC_OFFSET( 3398, gl_dispatch_stub_278, gl_dispatch_stub_278, NULL, 278),
    NAME_FUNC_OFFSET( 3412, glGetTexGenfvOES, glGetTexGenfvOES, NULL, 279),
    NAME_FUNC_OFFSET( 3429, glGetTexGenivOES, glGetTexGenivOES, NULL, 280),
    NAME_FUNC_OFFSET( 3446, gl_dispatch_stub_281, gl_dispatch_stub_281, NULL, 281),
    NAME_FUNC_OFFSET( 3460, glGetTexParameterfv, glGetTexParameterfv, NULL, 282),
    NAME_FUNC_OFFSET( 3480, glGetTexParameteriv, glGetTexParameteriv, NULL, 283),
    NAME_FUNC_OFFSET( 3500, gl_dispatch_stub_284, gl_dispatch_stub_284, NULL, 284),
    NAME_FUNC_OFFSET( 3525, gl_dispatch_stub_285, gl_dispatch_stub_285, NULL, 285),
    NAME_FUNC_OFFSET( 3550, glIsEnabled, glIsEnabled, NULL, 286),
    NAME_FUNC_OFFSET( 3562, gl_dispatch_stub_287, gl_dispatch_stub_287, NULL, 287),
    NAME_FUNC_OFFSET( 3571, gl_dispatch_stub_288, gl_dispatch_stub_288, NULL, 288),
    NAME_FUNC_OFFSET( 3584, gl_dispatch_stub_289, gl_dispatch_stub_289, NULL, 289),
    NAME_FUNC_OFFSET( 3594, glLoadIdentity, glLoadIdentity, NULL, 290),
    NAME_FUNC_OFFSET( 3609, glLoadMatrixf, glLoadMatrixf, NULL, 291),
    NAME_FUNC_OFFSET( 3623, gl_dispatch_stub_292, gl_dispatch_stub_292, NULL, 292),
    NAME_FUNC_OFFSET( 3637, glMatrixMode, glMatrixMode, NULL, 293),
    NAME_FUNC_OFFSET( 3650, glMultMatrixf, glMultMatrixf, NULL, 294),
    NAME_FUNC_OFFSET( 3664, gl_dispatch_stub_295, gl_dispatch_stub_295, NULL, 295),
    NAME_FUNC_OFFSET( 3678, gl_dispatch_stub_296, gl_dispatch_stub_296, NULL, 296),
    NAME_FUNC_OFFSET( 3686, glPopMatrix, glPopMatrix, NULL, 297),
    NAME_FUNC_OFFSET( 3698, glPushMatrix, glPushMatrix, NULL, 298),
    NAME_FUNC_OFFSET( 3711, gl_dispatch_stub_299, gl_dispatch_stub_299, NULL, 299),
    NAME_FUNC_OFFSET( 3721, glRotatef, glRotatef, NULL, 300),
    NAME_FUNC_OFFSET( 3731, gl_dispatch_stub_301, gl_dispatch_stub_301, NULL, 301),
    NAME_FUNC_OFFSET( 3740, glScalef, glScalef, NULL, 302),
    NAME_FUNC_OFFSET( 3749, gl_dispatch_stub_303, gl_dispatch_stub_303, NULL, 303),
    NAME_FUNC_OFFSET( 3762, glTranslatef, glTranslatef, NULL, 304),
    NAME_FUNC_OFFSET( 3775, glViewport, glViewport, NULL, 305),
    NAME_FUNC_OFFSET( 3786, gl_dispatch_stub_306, gl_dispatch_stub_306, NULL, 306),
    NAME_FUNC_OFFSET( 3801, glBindTexture, glBindTexture, NULL, 307),
    NAME_FUNC_OFFSET( 3815, glColorPointer, glColorPointer, NULL, 308),
    NAME_FUNC_OFFSET( 3830, glDisableClientState, glDisableClientState, NULL, 309),
    NAME_FUNC_OFFSET( 3851, glDrawArrays, glDrawArrays, NULL, 310),
    NAME_FUNC_OFFSET( 3864, glDrawElements, glDrawElements, NULL, 311),
    NAME_FUNC_OFFSET( 3879, gl_dispatch_stub_312, gl_dispatch_stub_312, NULL, 312),
    NAME_FUNC_OFFSET( 3897, glEnableClientState, glEnableClientState, NULL, 313),
    NAME_FUNC_OFFSET( 3917, gl_dispatch_stub_314, gl_dispatch_stub_314, NULL, 314),
    NAME_FUNC_OFFSET( 3932, gl_dispatch_stub_315, gl_dispatch_stub_315, NULL, 315),
    NAME_FUNC_OFFSET( 3942, gl_dispatch_stub_316, gl_dispatch_stub_316, NULL, 316),
    NAME_FUNC_OFFSET( 3953, gl_dispatch_stub_317, gl_dispatch_stub_317, NULL, 317),
    NAME_FUNC_OFFSET( 3973, glNormalPointer, glNormalPointer, NULL, 318),
    NAME_FUNC_OFFSET( 3989, glPolygonOffset, glPolygonOffset, NULL, 319),
    NAME_FUNC_OFFSET( 4005, glTexCoordPointer, glTexCoordPointer, NULL, 320),
    NAME_FUNC_OFFSET( 4023, glVertexPointer, glVertexPointer, NULL, 321),
    NAME_FUNC_OFFSET( 4039, gl_dispatch_stub_322, gl_dispatch_stub_322, NULL, 322),
    NAME_FUNC_OFFSET( 4061, gl_dispatch_stub_323, gl_dispatch_stub_323, NULL, 323),
    NAME_FUNC_OFFSET( 4078, glCopyTexImage2D, glCopyTexImage2D, NULL, 324),
    NAME_FUNC_OFFSET( 4095, gl_dispatch_stub_325, gl_dispatch_stub_325, NULL, 325),
    NAME_FUNC_OFFSET( 4115, glCopyTexSubImage2D, glCopyTexSubImage2D, NULL, 326),
    NAME_FUNC_OFFSET( 4135, glDeleteTextures, glDeleteTextures, NULL, 327),
    NAME_FUNC_OFFSET( 4152, glGenTextures, glGenTextures, NULL, 328),
    NAME_FUNC_OFFSET( 4166, glGetPointerv, glGetPointerv, NULL, 329),
    NAME_FUNC_OFFSET( 4180, glIsTexture, glIsTexture, NULL, 330),
    NAME_FUNC_OFFSET( 4192, gl_dispatch_stub_331, gl_dispatch_stub_331, NULL, 331),
    NAME_FUNC_OFFSET( 4213, gl_dispatch_stub_332, gl_dispatch_stub_332, NULL, 332),
    NAME_FUNC_OFFSET( 4229, glTexSubImage2D, glTexSubImage2D, NULL, 333),
    NAME_FUNC_OFFSET( 4245, gl_dispatch_stub_334, gl_dispatch_stub_334, NULL, 334),
    NAME_FUNC_OFFSET( 4263, gl_dispatch_stub_335, gl_dispatch_stub_335, NULL, 335),
    NAME_FUNC_OFFSET( 4282, gl_dispatch_stub_336, gl_dispatch_stub_336, NULL, 336),
    NAME_FUNC_OFFSET( 4295, glBlendEquationOES, glBlendEquationOES, NULL, 337),
    NAME_FUNC_OFFSET( 4314, gl_dispatch_stub_338, gl_dispatch_stub_338, NULL, 338),
    NAME_FUNC_OFFSET( 4334, gl_dispatch_stub_339, gl_dispatch_stub_339, NULL, 339),
    NAME_FUNC_OFFSET( 4347, gl_dispatch_stub_340, gl_dispatch_stub_340, NULL, 340),
    NAME_FUNC_OFFSET( 4371, gl_dispatch_stub_341, gl_dispatch_stub_341, NULL, 341),
    NAME_FUNC_OFFSET( 4395, gl_dispatch_stub_342, gl_dispatch_stub_342, NULL, 342),
    NAME_FUNC_OFFSET( 4412, gl_dispatch_stub_343, gl_dispatch_stub_343, NULL, 343),
    NAME_FUNC_OFFSET( 4428, gl_dispatch_stub_344, gl_dispatch_stub_344, NULL, 344),
    NAME_FUNC_OFFSET( 4455, gl_dispatch_stub_345, gl_dispatch_stub_345, NULL, 345),
    NAME_FUNC_OFFSET( 4482, gl_dispatch_stub_346, gl_dispatch_stub_346, NULL, 346),
    NAME_FUNC_OFFSET( 4498, gl_dispatch_stub_347, gl_dispatch_stub_347, NULL, 347),
    NAME_FUNC_OFFSET( 4518, gl_dispatch_stub_348, gl_dispatch_stub_348, NULL, 348),
    NAME_FUNC_OFFSET( 4540, gl_dispatch_stub_349, gl_dispatch_stub_349, NULL, 349),
    NAME_FUNC_OFFSET( 4562, gl_dispatch_stub_350, gl_dispatch_stub_350, NULL, 350),
    NAME_FUNC_OFFSET( 4586, gl_dispatch_stub_351, gl_dispatch_stub_351, NULL, 351),
    NAME_FUNC_OFFSET( 4611, gl_dispatch_stub_352, gl_dispatch_stub_352, NULL, 352),
    NAME_FUNC_OFFSET( 4635, gl_dispatch_stub_353, gl_dispatch_stub_353, NULL, 353),
    NAME_FUNC_OFFSET( 4660, gl_dispatch_stub_354, gl_dispatch_stub_354, NULL, 354),
    NAME_FUNC_OFFSET( 4686, gl_dispatch_stub_355, gl_dispatch_stub_355, NULL, 355),
    NAME_FUNC_OFFSET( 4712, gl_dispatch_stub_356, gl_dispatch_stub_356, NULL, 356),
    NAME_FUNC_OFFSET( 4735, gl_dispatch_stub_357, gl_dispatch_stub_357, NULL, 357),
    NAME_FUNC_OFFSET( 4763, gl_dispatch_stub_358, gl_dispatch_stub_358, NULL, 358),
    NAME_FUNC_OFFSET( 4791, gl_dispatch_stub_359, gl_dispatch_stub_359, NULL, 359),
    NAME_FUNC_OFFSET( 4812, gl_dispatch_stub_360, gl_dispatch_stub_360, NULL, 360),
    NAME_FUNC_OFFSET( 4832, gl_dispatch_stub_361, gl_dispatch_stub_361, NULL, 361),
    NAME_FUNC_OFFSET( 4847, gl_dispatch_stub_362, gl_dispatch_stub_362, NULL, 362),
    NAME_FUNC_OFFSET( 4873, gl_dispatch_stub_363, gl_dispatch_stub_363, NULL, 363),
    NAME_FUNC_OFFSET( 4899, gl_dispatch_stub_364, gl_dispatch_stub_364, NULL, 364),
    NAME_FUNC_OFFSET( 4911, gl_dispatch_stub_365, gl_dispatch_stub_365, NULL, 365),
    NAME_FUNC_OFFSET( 4934, gl_dispatch_stub_366, gl_dispatch_stub_366, NULL, 366),
    NAME_FUNC_OFFSET( 4957, gl_dispatch_stub_367, gl_dispatch_stub_367, NULL, 367),
    NAME_FUNC_OFFSET( 4969, gl_dispatch_stub_368, gl_dispatch_stub_368, NULL, 368),
    NAME_FUNC_OFFSET( 4978, gl_dispatch_stub_369, gl_dispatch_stub_369, NULL, 369),
    NAME_FUNC_OFFSET( 4995, gl_dispatch_stub_370, gl_dispatch_stub_370, NULL, 370),
    NAME_FUNC_OFFSET( 5009, gl_dispatch_stub_371, gl_dispatch_stub_371, NULL, 371),
    NAME_FUNC_OFFSET( 5022, gl_dispatch_stub_372, gl_dispatch_stub_372, NULL, 372),
    NAME_FUNC_OFFSET( 5038, gl_dispatch_stub_373, gl_dispatch_stub_373, NULL, 373),
    NAME_FUNC_OFFSET( 5058, glActiveTexture, glActiveTexture, NULL, 374),
    NAME_FUNC_OFFSET( 5074, glClientActiveTexture, glClientActiveTexture, NULL, 375),
    NAME_FUNC_OFFSET( 5096, gl_dispatch_stub_376, gl_dispatch_stub_376, NULL, 376),
    NAME_FUNC_OFFSET( 5117, gl_dispatch_stub_377, gl_dispatch_stub_377, NULL, 377),
    NAME_FUNC_OFFSET( 5139, gl_dispatch_stub_378, gl_dispatch_stub_378, NULL, 378),
    NAME_FUNC_OFFSET( 5160, gl_dispatch_stub_379, gl_dispatch_stub_379, NULL, 379),
    NAME_FUNC_OFFSET( 5182, gl_dispatch_stub_380, gl_dispatch_stub_380, NULL, 380),
    NAME_FUNC_OFFSET( 5203, gl_dispatch_stub_381, gl_dispatch_stub_381, NULL, 381),
    NAME_FUNC_OFFSET( 5225, gl_dispatch_stub_382, gl_dispatch_stub_382, NULL, 382),
    NAME_FUNC_OFFSET( 5246, gl_dispatch_stub_383, gl_dispatch_stub_383, NULL, 383),
    NAME_FUNC_OFFSET( 5268, gl_dispatch_stub_384, gl_dispatch_stub_384, NULL, 384),
    NAME_FUNC_OFFSET( 5289, gl_dispatch_stub_385, gl_dispatch_stub_385, NULL, 385),
    NAME_FUNC_OFFSET( 5311, gl_dispatch_stub_386, gl_dispatch_stub_386, NULL, 386),
    NAME_FUNC_OFFSET( 5332, gl_dispatch_stub_387, gl_dispatch_stub_387, NULL, 387),
    NAME_FUNC_OFFSET( 5354, gl_dispatch_stub_388, gl_dispatch_stub_388, NULL, 388),
    NAME_FUNC_OFFSET( 5375, gl_dispatch_stub_389, gl_dispatch_stub_389, NULL, 389),
    NAME_FUNC_OFFSET( 5397, gl_dispatch_stub_390, gl_dispatch_stub_390, NULL, 390),
    NAME_FUNC_OFFSET( 5418, gl_dispatch_stub_391, gl_dispatch_stub_391, NULL, 391),
    NAME_FUNC_OFFSET( 5440, gl_dispatch_stub_392, gl_dispatch_stub_392, NULL, 392),
    NAME_FUNC_OFFSET( 5461, gl_dispatch_stub_393, gl_dispatch_stub_393, NULL, 393),
    NAME_FUNC_OFFSET( 5483, gl_dispatch_stub_394, gl_dispatch_stub_394, NULL, 394),
    NAME_FUNC_OFFSET( 5504, gl_dispatch_stub_395, gl_dispatch_stub_395, NULL, 395),
    NAME_FUNC_OFFSET( 5526, gl_dispatch_stub_396, gl_dispatch_stub_396, NULL, 396),
    NAME_FUNC_OFFSET( 5547, gl_dispatch_stub_397, gl_dispatch_stub_397, NULL, 397),
    NAME_FUNC_OFFSET( 5569, gl_dispatch_stub_398, gl_dispatch_stub_398, NULL, 398),
    NAME_FUNC_OFFSET( 5590, gl_dispatch_stub_399, gl_dispatch_stub_399, NULL, 399),
    NAME_FUNC_OFFSET( 5612, gl_dispatch_stub_400, gl_dispatch_stub_400, NULL, 400),
    NAME_FUNC_OFFSET( 5633, gl_dispatch_stub_401, gl_dispatch_stub_401, NULL, 401),
    NAME_FUNC_OFFSET( 5655, glMultiTexCoord4f, glMultiTexCoord4f, NULL, 402),
    NAME_FUNC_OFFSET( 5673, gl_dispatch_stub_403, gl_dispatch_stub_403, NULL, 403),
    NAME_FUNC_OFFSET( 5695, gl_dispatch_stub_404, gl_dispatch_stub_404, NULL, 404),
    NAME_FUNC_OFFSET( 5716, gl_dispatch_stub_405, gl_dispatch_stub_405, NULL, 405),
    NAME_FUNC_OFFSET( 5738, gl_dispatch_stub_406, gl_dispatch_stub_406, NULL, 406),
    NAME_FUNC_OFFSET( 5759, gl_dispatch_stub_407, gl_dispatch_stub_407, NULL, 407),
    NAME_FUNC_OFFSET( 5781, glBlendEquationSeparateOES, glBlendEquationSeparateOES, NULL, 408),
    NAME_FUNC_OFFSET( 5808, glBlendFuncSeparateOES, glBlendFuncSeparateOES, NULL, 409),
    NAME_FUNC_OFFSET( 5831, glDrawTexfOES, glDrawTexfOES, NULL, 410),
    NAME_FUNC_OFFSET( 5845, glDrawTexfvOES, glDrawTexfvOES, NULL, 411),
    NAME_FUNC_OFFSET( 5860, glDrawTexiOES, glDrawTexiOES, NULL, 412),
    NAME_FUNC_OFFSET( 5874, glDrawTexivOES, glDrawTexivOES, NULL, 413),
    NAME_FUNC_OFFSET( 5889, glDrawTexsOES, glDrawTexsOES, NULL, 414),
    NAME_FUNC_OFFSET( 5903, glDrawTexsvOES, glDrawTexsvOES, NULL, 415),
    NAME_FUNC_OFFSET( 5918, glDrawTexxOES, glDrawTexxOES, NULL, 416),
    NAME_FUNC_OFFSET( 5932, glDrawTexxvOES, glDrawTexxvOES, NULL, 417),
    NAME_FUNC_OFFSET( 5947, glBindFramebufferOES, glBindFramebufferOES, NULL, 418),
    NAME_FUNC_OFFSET( 5968, glBindRenderbufferOES, glBindRenderbufferOES, NULL, 419),
    NAME_FUNC_OFFSET( 5990, glCheckFramebufferStatusOES, glCheckFramebufferStatusOES, NULL, 420),
    NAME_FUNC_OFFSET( 6018, glDeleteFramebuffersOES, glDeleteFramebuffersOES, NULL, 421),
    NAME_FUNC_OFFSET( 6042, glDeleteRenderbuffersOES, glDeleteRenderbuffersOES, NULL, 422),
    NAME_FUNC_OFFSET( 6067, glFramebufferRenderbufferOES, glFramebufferRenderbufferOES, NULL, 423),
    NAME_FUNC_OFFSET( 6096, glFramebufferTexture2DOES, glFramebufferTexture2DOES, NULL, 424),
    NAME_FUNC_OFFSET( 6122, glGenFramebuffersOES, glGenFramebuffersOES, NULL, 425),
    NAME_FUNC_OFFSET( 6143, glGenRenderbuffersOES, glGenRenderbuffersOES, NULL, 426),
    NAME_FUNC_OFFSET( 6165, glGenerateMipmapOES, glGenerateMipmapOES, NULL, 427),
    NAME_FUNC_OFFSET( 6185, glGetFramebufferAttachmentParameterivOES, glGetFramebufferAttachmentParameterivOES, NULL, 428),
    NAME_FUNC_OFFSET( 6226, glGetRenderbufferParameterivOES, glGetRenderbufferParameterivOES, NULL, 429),
    NAME_FUNC_OFFSET( 6258, glIsFramebufferOES, glIsFramebufferOES, NULL, 430),
    NAME_FUNC_OFFSET( 6277, glIsRenderbufferOES, glIsRenderbufferOES, NULL, 431),
    NAME_FUNC_OFFSET( 6297, glRenderbufferStorageOES, glRenderbufferStorageOES, NULL, 432),
    NAME_FUNC_OFFSET( 6322, glPointSizePointerOES, glPointSizePointerOES, NULL, 433),
    NAME_FUNC_OFFSET( 6344, glQueryMatrixxOES, glQueryMatrixxOES, NULL, 434),
    NAME_FUNC_OFFSET( 6362, glGetTexGenxvOES, glGetTexGenxvOES, NULL, 435),
    NAME_FUNC_OFFSET( 6379, glTexGenxOES, glTexGenxOES, NULL, 436),
    NAME_FUNC_OFFSET( 6392, glTexGenxvOES, glTexGenxvOES, NULL, 437),
    NAME_FUNC_OFFSET( 6406, glGetBufferPointervOES, glGetBufferPointervOES, NULL, 438),
    NAME_FUNC_OFFSET( 6429, glMapBufferOES, glMapBufferOES, NULL, 439),
    NAME_FUNC_OFFSET( 6444, glUnmapBufferOES, glUnmapBufferOES, NULL, 440),
    NAME_FUNC_OFFSET( 6461, glMultiDrawArraysEXT, glMultiDrawArraysEXT, NULL, 441),
    NAME_FUNC_OFFSET( 6482, glMultiDrawElementsEXT, glMultiDrawElementsEXT, NULL, 442),
    NAME_FUNC_OFFSET( 6505, gl_dispatch_stub_443, gl_dispatch_stub_443, NULL, 443),
    NAME_FUNC_OFFSET( 6528, gl_dispatch_stub_444, gl_dispatch_stub_444, NULL, 444),
    NAME_FUNC_OFFSET( 6554, gl_dispatch_stub_445, gl_dispatch_stub_445, NULL, 445),
    NAME_FUNC_OFFSET( 6577, gl_dispatch_stub_446, gl_dispatch_stub_446, NULL, 446),
    NAME_FUNC_OFFSET( 6598, glEGLImageTargetRenderbufferStorageOES, glEGLImageTargetRenderbufferStorageOES, NULL, 447),
    NAME_FUNC_OFFSET( 6637, glEGLImageTargetTexture2DOES, glEGLImageTargetTexture2DOES, NULL, 448),
    NAME_FUNC_OFFSET( 6666, glCompressedTexImage2D, glCompressedTexImage2D, NULL, 449),
    NAME_FUNC_OFFSET( 6689, glCompressedTexSubImage2D, glCompressedTexSubImage2D, NULL, 450),
    NAME_FUNC_OFFSET( 6715, glSampleCoverage, glSampleCoverage, NULL, 451),
    NAME_FUNC_OFFSET( 6732, glBindBuffer, glBindBuffer, NULL, 452),
    NAME_FUNC_OFFSET( 6745, glBufferData, glBufferData, NULL, 453),
    NAME_FUNC_OFFSET( 6758, glBufferSubData, glBufferSubData, NULL, 454),
    NAME_FUNC_OFFSET( 6774, glDeleteBuffers, glDeleteBuffers, NULL, 455),
    NAME_FUNC_OFFSET( 6790, glGenBuffers, glGenBuffers, NULL, 456),
    NAME_FUNC_OFFSET( 6803, glGetBufferParameteriv, glGetBufferParameteriv, NULL, 457),
    NAME_FUNC_OFFSET( 6826, glIsBuffer, glIsBuffer, NULL, 458),
    NAME_FUNC_OFFSET( 6837, glPointParameterf, glPointParameterf, NULL, 459),
    NAME_FUNC_OFFSET( 6855, glPointParameterfv, glPointParameterfv, NULL, 460),
    NAME_FUNC_OFFSET( 6874, glAlphaFuncx, glAlphaFuncx, NULL, 461),
    NAME_FUNC_OFFSET( 6887, glClearColorx, glClearColorx, NULL, 462),
    NAME_FUNC_OFFSET( 6901, glClearDepthf, glClearDepthf, NULL, 463),
    NAME_FUNC_OFFSET( 6915, glClearDepthx, glClearDepthx, NULL, 464),
    NAME_FUNC_OFFSET( 6929, glColor4x, glColor4x, NULL, 465),
    NAME_FUNC_OFFSET( 6939, glDepthRangef, glDepthRangef, NULL, 466),
    NAME_FUNC_OFFSET( 6953, glDepthRangex, glDepthRangex, NULL, 467),
    NAME_FUNC_OFFSET( 6967, glFogx, glFogx, NULL, 468),
    NAME_FUNC_OFFSET( 6974, glFogxv, glFogxv, NULL, 469),
    NAME_FUNC_OFFSET( 6982, glFrustumf, glFrustumf, NULL, 470),
    NAME_FUNC_OFFSET( 6993, glFrustumx, glFrustumx, NULL, 471),
    NAME_FUNC_OFFSET( 7004, glLightModelx, glLightModelx, NULL, 472),
    NAME_FUNC_OFFSET( 7018, glLightModelxv, glLightModelxv, NULL, 473),
    NAME_FUNC_OFFSET( 7033, glLightx, glLightx, NULL, 474),
    NAME_FUNC_OFFSET( 7042, glLightxv, glLightxv, NULL, 475),
    NAME_FUNC_OFFSET( 7052, glLineWidthx, glLineWidthx, NULL, 476),
    NAME_FUNC_OFFSET( 7065, glLoadMatrixx, glLoadMatrixx, NULL, 477),
    NAME_FUNC_OFFSET( 7079, glMaterialx, glMaterialx, NULL, 478),
    NAME_FUNC_OFFSET( 7091, glMaterialxv, glMaterialxv, NULL, 479),
    NAME_FUNC_OFFSET( 7104, glMultMatrixx, glMultMatrixx, NULL, 480),
    NAME_FUNC_OFFSET( 7118, glMultiTexCoord4x, glMultiTexCoord4x, NULL, 481),
    NAME_FUNC_OFFSET( 7136, glNormal3x, glNormal3x, NULL, 482),
    NAME_FUNC_OFFSET( 7147, glOrthof, glOrthof, NULL, 483),
    NAME_FUNC_OFFSET( 7156, glOrthox, glOrthox, NULL, 484),
    NAME_FUNC_OFFSET( 7165, glPointSizex, glPointSizex, NULL, 485),
    NAME_FUNC_OFFSET( 7178, glPolygonOffsetx, glPolygonOffsetx, NULL, 486),
    NAME_FUNC_OFFSET( 7195, glRotatex, glRotatex, NULL, 487),
    NAME_FUNC_OFFSET( 7205, glSampleCoveragex, glSampleCoveragex, NULL, 488),
    NAME_FUNC_OFFSET( 7223, glScalex, glScalex, NULL, 489),
    NAME_FUNC_OFFSET( 7232, glTexEnvx, glTexEnvx, NULL, 490),
    NAME_FUNC_OFFSET( 7242, glTexEnvxv, glTexEnvxv, NULL, 491),
    NAME_FUNC_OFFSET( 7253, glTexParameterx, glTexParameterx, NULL, 492),
    NAME_FUNC_OFFSET( 7269, glTranslatex, glTranslatex, NULL, 493),
    NAME_FUNC_OFFSET( 7282, glClipPlanef, glClipPlanef, NULL, 494),
    NAME_FUNC_OFFSET( 7295, glClipPlanex, glClipPlanex, NULL, 495),
    NAME_FUNC_OFFSET( 7308, glGetClipPlanef, glGetClipPlanef, NULL, 496),
    NAME_FUNC_OFFSET( 7324, glGetClipPlanex, glGetClipPlanex, NULL, 497),
    NAME_FUNC_OFFSET( 7340, glGetFixedv, glGetFixedv, NULL, 498),
    NAME_FUNC_OFFSET( 7352, glGetLightxv, glGetLightxv, NULL, 499),
    NAME_FUNC_OFFSET( 7365, glGetMaterialxv, glGetMaterialxv, NULL, 500),
    NAME_FUNC_OFFSET( 7381, glGetTexEnvxv, glGetTexEnvxv, NULL, 501),
    NAME_FUNC_OFFSET( 7395, glGetTexParameterxv, glGetTexParameterxv, NULL, 502),
    NAME_FUNC_OFFSET( 7415, glPointParameterx, glPointParameterx, NULL, 503),
    NAME_FUNC_OFFSET( 7433, glPointParameterxv, glPointParameterxv, NULL, 504),
    NAME_FUNC_OFFSET( 7452, glTexParameterxv, glTexParameterxv, NULL, 505),
    NAME_FUNC_OFFSET( 7469, glTexGenfOES, glTexGenfOES, NULL, 190),
    NAME_FUNC_OFFSET( 7479, glTexGenfvOES, glTexGenfvOES, NULL, 191),
    NAME_FUNC_OFFSET( 7490, glTexGeniOES, glTexGeniOES, NULL, 192),
    NAME_FUNC_OFFSET( 7500, glTexGenivOES, glTexGenivOES, NULL, 193),
    NAME_FUNC_OFFSET( 7511, glGetTexGenfvOES, glGetTexGenfvOES, NULL, 279),
    NAME_FUNC_OFFSET( 7525, glGetTexGenivOES, glGetTexGenivOES, NULL, 280),
    NAME_FUNC_OFFSET( 7539, glBlendEquationOES, glBlendEquationOES, NULL, 337),
    NAME_FUNC_OFFSET( 7555, glActiveTexture, glActiveTexture, NULL, 374),
    NAME_FUNC_OFFSET( 7574, glClientActiveTexture, glClientActiveTexture, NULL, 375),
    NAME_FUNC_OFFSET( 7599, glMultiTexCoord4f, glMultiTexCoord4f, NULL, 402),
    NAME_FUNC_OFFSET( 7620, glAlphaFuncx, glAlphaFuncx, NULL, 461),
    NAME_FUNC_OFFSET( 7636, glClearColorx, glClearColorx, NULL, 462),
    NAME_FUNC_OFFSET( 7653, glClearDepthf, glClearDepthf, NULL, 463),
    NAME_FUNC_OFFSET( 7670, glClearDepthx, glClearDepthx, NULL, 464),
    NAME_FUNC_OFFSET( 7687, glColor4x, glColor4x, NULL, 465),
    NAME_FUNC_OFFSET( 7700, glDepthRangef, glDepthRangef, NULL, 466),
    NAME_FUNC_OFFSET( 7717, glDepthRangex, glDepthRangex, NULL, 467),
    NAME_FUNC_OFFSET( 7734, glFogx, glFogx, NULL, 468),
    NAME_FUNC_OFFSET( 7744, glFogxv, glFogxv, NULL, 469),
    NAME_FUNC_OFFSET( 7755, glFrustumf, glFrustumf, NULL, 470),
    NAME_FUNC_OFFSET( 7769, glFrustumx, glFrustumx, NULL, 471),
    NAME_FUNC_OFFSET( 7783, glLightModelx, glLightModelx, NULL, 472),
    NAME_FUNC_OFFSET( 7800, glLightModelxv, glLightModelxv, NULL, 473),
    NAME_FUNC_OFFSET( 7818, glLightx, glLightx, NULL, 474),
    NAME_FUNC_OFFSET( 7830, glLightxv, glLightxv, NULL, 475),
    NAME_FUNC_OFFSET( 7843, glLineWidthx, glLineWidthx, NULL, 476),
    NAME_FUNC_OFFSET( 7859, glLoadMatrixx, glLoadMatrixx, NULL, 477),
    NAME_FUNC_OFFSET( 7876, glMaterialx, glMaterialx, NULL, 478),
    NAME_FUNC_OFFSET( 7891, glMaterialxv, glMaterialxv, NULL, 479),
    NAME_FUNC_OFFSET( 7907, glMultMatrixx, glMultMatrixx, NULL, 480),
    NAME_FUNC_OFFSET( 7924, glMultiTexCoord4x, glMultiTexCoord4x, NULL, 481),
    NAME_FUNC_OFFSET( 7945, glNormal3x, glNormal3x, NULL, 482),
    NAME_FUNC_OFFSET( 7959, glOrthof, glOrthof, NULL, 483),
    NAME_FUNC_OFFSET( 7971, glOrthox, glOrthox, NULL, 484),
    NAME_FUNC_OFFSET( 7983, glPointSizex, glPointSizex, NULL, 485),
    NAME_FUNC_OFFSET( 7999, glPolygonOffsetx, glPolygonOffsetx, NULL, 486),
    NAME_FUNC_OFFSET( 8019, glRotatex, glRotatex, NULL, 487),
    NAME_FUNC_OFFSET( 8032, glSampleCoveragex, glSampleCoveragex, NULL, 488),
    NAME_FUNC_OFFSET( 8053, glScalex, glScalex, NULL, 489),
    NAME_FUNC_OFFSET( 8065, glTexEnvx, glTexEnvx, NULL, 490),
    NAME_FUNC_OFFSET( 8078, glTexEnvxv, glTexEnvxv, NULL, 491),
    NAME_FUNC_OFFSET( 8092, glTexParameterx, glTexParameterx, NULL, 492),
    NAME_FUNC_OFFSET( 8111, glTranslatex, glTranslatex, NULL, 493),
    NAME_FUNC_OFFSET( 8127, glClipPlanef, glClipPlanef, NULL, 494),
    NAME_FUNC_OFFSET( 8143, glClipPlanex, glClipPlanex, NULL, 495),
    NAME_FUNC_OFFSET( 8159, glGetClipPlanef, glGetClipPlanef, NULL, 496),
    NAME_FUNC_OFFSET( 8178, glGetClipPlanex, glGetClipPlanex, NULL, 497),
    NAME_FUNC_OFFSET( 8197, glGetFixedv, glGetFixedv, NULL, 498),
    NAME_FUNC_OFFSET( 8212, glGetLightxv, glGetLightxv, NULL, 499),
    NAME_FUNC_OFFSET( 8228, glGetMaterialxv, glGetMaterialxv, NULL, 500),
    NAME_FUNC_OFFSET( 8247, glGetTexEnvxv, glGetTexEnvxv, NULL, 501),
    NAME_FUNC_OFFSET( 8264, glGetTexParameterxv, glGetTexParameterxv, NULL, 502),
    NAME_FUNC_OFFSET( 8287, glPointParameterx, glPointParameterx, NULL, 503),
    NAME_FUNC_OFFSET( 8308, glPointParameterxv, glPointParameterxv, NULL, 504),
    NAME_FUNC_OFFSET( 8330, glTexParameterxv, glTexParameterxv, NULL, 505),
    NAME_FUNC_OFFSET(-1, NULL, NULL, NULL, 0)
};

#undef NAME_FUNC_OFFSET
