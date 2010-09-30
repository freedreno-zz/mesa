/* DO NOT EDIT - This file generated automatically by remap_helper.py (from Mesa) script */

/*
 * Copyright (C) 2009 Chia-I Wu <olv@0xlab.org>
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
 * Chia-I Wu,
 * AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "main/dispatch.h"
#include "main/remap.h"

/* this is internal to remap.c */
#ifdef need_MESA_remap_table

static const char _mesa_function_pool[] =
   /* _mesa_function_pool[0]: MapGrid1d (offset 224) */
   "idd\0"
   "glMapGrid1d\0"
   "\0"
   /* _mesa_function_pool[17]: MapGrid1f (offset 225) */
   "iff\0"
   "glMapGrid1f\0"
   "\0"
   /* _mesa_function_pool[34]: RasterPos4i (offset 82) */
   "iiii\0"
   "glRasterPos4i\0"
   "\0"
   /* _mesa_function_pool[54]: RasterPos4d (offset 78) */
   "dddd\0"
   "glRasterPos4d\0"
   "\0"
   /* _mesa_function_pool[74]: NewList (dynamic) */
   "ii\0"
   "glNewList\0"
   "\0"
   /* _mesa_function_pool[88]: RasterPos4f (offset 80) */
   "ffff\0"
   "glRasterPos4f\0"
   "\0"
   /* _mesa_function_pool[108]: LoadIdentity (offset 290) */
   "\0"
   "glLoadIdentity\0"
   "\0"
   /* _mesa_function_pool[125]: ConvolutionFilter1D (offset 348) */
   "iiiiip\0"
   "glConvolutionFilter1D\0"
   "\0"
   /* _mesa_function_pool[155]: RasterPos3dv (offset 71) */
   "p\0"
   "glRasterPos3dv\0"
   "\0"
   /* _mesa_function_pool[173]: GetProgramiv (will be remapped) */
   "iip\0"
   "glGetProgramiv\0"
   "\0"
   /* _mesa_function_pool[193]: TexCoord1iv (offset 99) */
   "p\0"
   "glTexCoord1iv\0"
   "\0"
   /* _mesa_function_pool[210]: TexCoord4sv (offset 125) */
   "p\0"
   "glTexCoord4sv\0"
   "\0"
   /* _mesa_function_pool[227]: RasterPos4s (offset 84) */
   "iiii\0"
   "glRasterPos4s\0"
   "\0"
   /* _mesa_function_pool[247]: TexCoord1f (offset 96) */
   "f\0"
   "glTexCoord1f\0"
   "\0"
   /* _mesa_function_pool[263]: TexCoord1d (offset 94) */
   "d\0"
   "glTexCoord1d\0"
   "\0"
   /* _mesa_function_pool[279]: TexCoord1i (offset 98) */
   "i\0"
   "glTexCoord1i\0"
   "\0"
   /* _mesa_function_pool[295]: Histogram (offset 367) */
   "iiii\0"
   "glHistogram\0"
   "\0"
   /* _mesa_function_pool[313]: TexCoord1s (offset 100) */
   "i\0"
   "glTexCoord1s\0"
   "\0"
   /* _mesa_function_pool[329]: GetMapfv (offset 267) */
   "iip\0"
   "glGetMapfv\0"
   "\0"
   /* _mesa_function_pool[345]: GetProgramInfoLog (will be remapped) */
   "iipp\0"
   "glGetProgramInfoLog\0"
   "\0"
   /* _mesa_function_pool[371]: Uniform2fv (will be remapped) */
   "iip\0"
   "glUniform2fv\0"
   "\0"
   /* _mesa_function_pool[389]: PolygonStipple (offset 175) */
   "p\0"
   "glPolygonStipple\0"
   "\0"
   /* _mesa_function_pool[409]: TexImage3DOES (offset 371) */
   "iiiiiiiiip\0"
   "glTexImage3DOES\0"
   "glTexImage3D\0"
   "\0"
   /* _mesa_function_pool[450]: VertexAttrib4fv (will be remapped) */
   "ip\0"
   "glVertexAttrib4fv\0"
   "\0"
   /* _mesa_function_pool[472]: GetPixelMapfv (offset 271) */
   "ip\0"
   "glGetPixelMapfv\0"
   "\0"
   /* _mesa_function_pool[492]: Color3uiv (offset 22) */
   "p\0"
   "glColor3uiv\0"
   "\0"
   /* _mesa_function_pool[507]: IsEnabled (offset 286) */
   "i\0"
   "glIsEnabled\0"
   "\0"
   /* _mesa_function_pool[522]: EvalCoord2fv (offset 235) */
   "p\0"
   "glEvalCoord2fv\0"
   "\0"
   /* _mesa_function_pool[540]: AttachShader (will be remapped) */
   "ii\0"
   "glAttachShader\0"
   "\0"
   /* _mesa_function_pool[559]: GetMapiv (offset 268) */
   "iip\0"
   "glGetMapiv\0"
   "\0"
   /* _mesa_function_pool[575]: Indexubv (offset 316) */
   "p\0"
   "glIndexubv\0"
   "\0"
   /* _mesa_function_pool[589]: EdgeFlagPointer (offset 312) */
   "ip\0"
   "glEdgeFlagPointer\0"
   "\0"
   /* _mesa_function_pool[611]: Color3ubv (offset 20) */
   "p\0"
   "glColor3ubv\0"
   "\0"
   /* _mesa_function_pool[626]: Vertex3dv (offset 135) */
   "p\0"
   "glVertex3dv\0"
   "\0"
   /* _mesa_function_pool[641]: LightModeliv (offset 166) */
   "ip\0"
   "glLightModeliv\0"
   "\0"
   /* _mesa_function_pool[660]: GetVertexAttribfv (will be remapped) */
   "iip\0"
   "glGetVertexAttribfv\0"
   "\0"
   /* _mesa_function_pool[685]: Normal3bv (offset 53) */
   "p\0"
   "glNormal3bv\0"
   "\0"
   /* _mesa_function_pool[700]: TexGeniv (offset 193) */
   "iip\0"
   "glTexGeniv\0"
   "\0"
   /* _mesa_function_pool[716]: Vertex3iv (offset 139) */
   "p\0"
   "glVertex3iv\0"
   "\0"
   /* _mesa_function_pool[731]: RenderbufferStorage (will be remapped) */
   "iiii\0"
   "glRenderbufferStorage\0"
   "\0"
   /* _mesa_function_pool[759]: CopyConvolutionFilter1D (offset 354) */
   "iiiii\0"
   "glCopyConvolutionFilter1D\0"
   "\0"
   /* _mesa_function_pool[792]: ClearColor (offset 206) */
   "ffff\0"
   "glClearColor\0"
   "\0"
   /* _mesa_function_pool[811]: Uniform3i (will be remapped) */
   "iiii\0"
   "glUniform3i\0"
   "\0"
   /* _mesa_function_pool[829]: BlendColor (offset 336) */
   "ffff\0"
   "glBlendColor\0"
   "\0"
   /* _mesa_function_pool[848]: DeleteVertexArraysAPPLE (will be remapped) */
   "ip\0"
   "glDeleteVertexArraysAPPLE\0"
   "\0"
   /* _mesa_function_pool[878]: Scalef (offset 302) */
   "fff\0"
   "glScalef\0"
   "\0"
   /* _mesa_function_pool[892]: Uniform3f (will be remapped) */
   "ifff\0"
   "glUniform3f\0"
   "\0"
   /* _mesa_function_pool[910]: Normal3iv (offset 59) */
   "p\0"
   "glNormal3iv\0"
   "\0"
   /* _mesa_function_pool[925]: Indexdv (offset 45) */
   "p\0"
   "glIndexdv\0"
   "\0"
   /* _mesa_function_pool[938]: Viewport (offset 305) */
   "iiii\0"
   "glViewport\0"
   "\0"
   /* _mesa_function_pool[955]: UniformMatrix3fv (will be remapped) */
   "iiip\0"
   "glUniformMatrix3fv\0"
   "\0"
   /* _mesa_function_pool[980]: DepthRange (offset 288) */
   "dd\0"
   "glDepthRange\0"
   "\0"
   /* _mesa_function_pool[997]: LoadMatrixf (offset 291) */
   "p\0"
   "glLoadMatrixf\0"
   "\0"
   /* _mesa_function_pool[1014]: VertexAttrib3f (will be remapped) */
   "ifff\0"
   "glVertexAttrib3f\0"
   "\0"
   /* _mesa_function_pool[1037]: CompressedTexSubImage2D (will be remapped) */
   "iiiiiiiip\0"
   "glCompressedTexSubImage2D\0"
   "\0"
   /* _mesa_function_pool[1074]: TexCoord2sv (offset 109) */
   "p\0"
   "glTexCoord2sv\0"
   "\0"
   /* _mesa_function_pool[1091]: TexCoord2dv (offset 103) */
   "p\0"
   "glTexCoord2dv\0"
   "\0"
   /* _mesa_function_pool[1108]: StencilMaskSeparate (will be remapped) */
   "ii\0"
   "glStencilMaskSeparate\0"
   "\0"
   /* _mesa_function_pool[1134]: Color3sv (offset 18) */
   "p\0"
   "glColor3sv\0"
   "\0"
   /* _mesa_function_pool[1148]: EvalCoord1f (offset 230) */
   "f\0"
   "glEvalCoord1f\0"
   "\0"
   /* _mesa_function_pool[1165]: GetConvolutionParameteriv (offset 358) */
   "iip\0"
   "glGetConvolutionParameteriv\0"
   "\0"
   /* _mesa_function_pool[1198]: AlphaFunc (offset 240) */
   "if\0"
   "glAlphaFunc\0"
   "\0"
   /* _mesa_function_pool[1214]: MultiTexCoord1fvARB (offset 379) */
   "ip\0"
   "glMultiTexCoord1fvARB\0"
   "\0"
   /* _mesa_function_pool[1240]: TexCoord3iv (offset 115) */
   "p\0"
   "glTexCoord3iv\0"
   "\0"
   /* _mesa_function_pool[1257]: Color3fv (offset 14) */
   "p\0"
   "glColor3fv\0"
   "\0"
   /* _mesa_function_pool[1271]: CompressedTexImage3DOES (will be remapped) */
   "iiiiiiiip\0"
   "glCompressedTexImage3DOES\0"
   "\0"
   /* _mesa_function_pool[1308]: Translatef (offset 304) */
   "fff\0"
   "glTranslatef\0"
   "\0"
   /* _mesa_function_pool[1326]: PointSize (offset 173) */
   "f\0"
   "glPointSize\0"
   "\0"
   /* _mesa_function_pool[1341]: PopName (offset 200) */
   "\0"
   "glPopName\0"
   "\0"
   /* _mesa_function_pool[1353]: Vertex4sv (offset 149) */
   "p\0"
   "glVertex4sv\0"
   "\0"
   /* _mesa_function_pool[1368]: GetTexEnvfv (offset 276) */
   "iip\0"
   "glGetTexEnvfv\0"
   "\0"
   /* _mesa_function_pool[1387]: BindAttribLocation (will be remapped) */
   "iip\0"
   "glBindAttribLocation\0"
   "\0"
   /* _mesa_function_pool[1413]: GetProgramBinaryOES (will be remapped) */
   "iippp\0"
   "glGetProgramBinaryOES\0"
   "\0"
   /* _mesa_function_pool[1442]: LineStipple (offset 167) */
   "ii\0"
   "glLineStipple\0"
   "\0"
   /* _mesa_function_pool[1460]: TexEnvi (offset 186) */
   "iii\0"
   "glTexEnvi\0"
   "\0"
   /* _mesa_function_pool[1475]: GetClipPlane (offset 259) */
   "ip\0"
   "glGetClipPlane\0"
   "\0"
   /* _mesa_function_pool[1494]: Scaled (offset 301) */
   "ddd\0"
   "glScaled\0"
   "\0"
   /* _mesa_function_pool[1508]: CallLists (offset 3) */
   "iip\0"
   "glCallLists\0"
   "\0"
   /* _mesa_function_pool[1525]: GetUniformfv (will be remapped) */
   "iip\0"
   "glGetUniformfv\0"
   "\0"
   /* _mesa_function_pool[1545]: Vertex2dv (offset 127) */
   "p\0"
   "glVertex2dv\0"
   "\0"
   /* _mesa_function_pool[1560]: EdgeFlag (offset 41) */
   "i\0"
   "glEdgeFlag\0"
   "\0"
   /* _mesa_function_pool[1574]: TexCoord2iv (offset 107) */
   "p\0"
   "glTexCoord2iv\0"
   "\0"
   /* _mesa_function_pool[1591]: Rotated (offset 299) */
   "dddd\0"
   "glRotated\0"
   "\0"
   /* _mesa_function_pool[1607]: ReadPixels (offset 256) */
   "iiiiiip\0"
   "glReadPixels\0"
   "\0"
   /* _mesa_function_pool[1629]: EdgeFlagv (offset 42) */
   "p\0"
   "glEdgeFlagv\0"
   "\0"
   /* _mesa_function_pool[1644]: Indexd (offset 44) */
   "d\0"
   "glIndexd\0"
   "\0"
   /* _mesa_function_pool[1656]: TexParameterf (offset 178) */
   "iif\0"
   "glTexParameterf\0"
   "\0"
   /* _mesa_function_pool[1677]: TexParameteri (offset 180) */
   "iii\0"
   "glTexParameteri\0"
   "\0"
   /* _mesa_function_pool[1698]: MultiTexCoord3dARB (offset 392) */
   "iddd\0"
   "glMultiTexCoord3dARB\0"
   "\0"
   /* _mesa_function_pool[1725]: GetUniformiv (will be remapped) */
   "iip\0"
   "glGetUniformiv\0"
   "\0"
   /* _mesa_function_pool[1745]: DrawPixels (offset 257) */
   "iiiip\0"
   "glDrawPixels\0"
   "\0"
   /* _mesa_function_pool[1765]: MultiTexCoord2svARB (offset 391) */
   "ip\0"
   "glMultiTexCoord2svARB\0"
   "\0"
   /* _mesa_function_pool[1791]: MultiTexCoord2iARB (offset 388) */
   "iii\0"
   "glMultiTexCoord2iARB\0"
   "\0"
   /* _mesa_function_pool[1817]: MultiTexCoord3svARB (offset 399) */
   "ip\0"
   "glMultiTexCoord3svARB\0"
   "\0"
   /* _mesa_function_pool[1843]: CreateProgram (will be remapped) */
   "\0"
   "glCreateProgram\0"
   "\0"
   /* _mesa_function_pool[1861]: DepthRangef (will be remapped) */
   "ff\0"
   "glDepthRangef\0"
   "\0"
   /* _mesa_function_pool[1879]: Uniform3fv (will be remapped) */
   "iip\0"
   "glUniform3fv\0"
   "\0"
   /* _mesa_function_pool[1897]: MapGrid2f (offset 227) */
   "iffiff\0"
   "glMapGrid2f\0"
   "\0"
   /* _mesa_function_pool[1917]: ValidateProgram (will be remapped) */
   "i\0"
   "glValidateProgram\0"
   "\0"
   /* _mesa_function_pool[1938]: Scissor (offset 176) */
   "iiii\0"
   "glScissor\0"
   "\0"
   /* _mesa_function_pool[1954]: Fogf (offset 153) */
   "if\0"
   "glFogf\0"
   "\0"
   /* _mesa_function_pool[1965]: TexSubImage1D (offset 332) */
   "iiiiiip\0"
   "glTexSubImage1D\0"
   "\0"
   /* _mesa_function_pool[1990]: Color4usv (offset 40) */
   "p\0"
   "glColor4usv\0"
   "\0"
   /* _mesa_function_pool[2005]: Fogi (offset 155) */
   "ii\0"
   "glFogi\0"
   "\0"
   /* _mesa_function_pool[2016]: MultiTexCoord3sARB (offset 398) */
   "iiii\0"
   "glMultiTexCoord3sARB\0"
   "\0"
   /* _mesa_function_pool[2043]: RasterPos3iv (offset 75) */
   "p\0"
   "glRasterPos3iv\0"
   "\0"
   /* _mesa_function_pool[2061]: GetActiveAttrib (will be remapped) */
   "iiipppp\0"
   "glGetActiveAttrib\0"
   "\0"
   /* _mesa_function_pool[2088]: TexCoord2i (offset 106) */
   "ii\0"
   "glTexCoord2i\0"
   "\0"
   /* _mesa_function_pool[2105]: DepthFunc (offset 245) */
   "i\0"
   "glDepthFunc\0"
   "\0"
   /* _mesa_function_pool[2120]: Color4ui (offset 37) */
   "iiii\0"
   "glColor4ui\0"
   "\0"
   /* _mesa_function_pool[2137]: RasterPos3s (offset 76) */
   "iii\0"
   "glRasterPos3s\0"
   "\0"
   /* _mesa_function_pool[2156]: Color3usv (offset 24) */
   "p\0"
   "glColor3usv\0"
   "\0"
   /* _mesa_function_pool[2171]: TexCoord2f (offset 104) */
   "ff\0"
   "glTexCoord2f\0"
   "\0"
   /* _mesa_function_pool[2188]: TexCoord2d (offset 102) */
   "dd\0"
   "glTexCoord2d\0"
   "\0"
   /* _mesa_function_pool[2205]: RasterPos3d (offset 70) */
   "ddd\0"
   "glRasterPos3d\0"
   "\0"
   /* _mesa_function_pool[2224]: RasterPos3f (offset 72) */
   "fff\0"
   "glRasterPos3f\0"
   "\0"
   /* _mesa_function_pool[2243]: AreTexturesResident (offset 322) */
   "ipp\0"
   "glAreTexturesResident\0"
   "\0"
   /* _mesa_function_pool[2270]: TexCoord2s (offset 108) */
   "ii\0"
   "glTexCoord2s\0"
   "\0"
   /* _mesa_function_pool[2287]: StencilOpSeparate (will be remapped) */
   "iiii\0"
   "glStencilOpSeparate\0"
   "\0"
   /* _mesa_function_pool[2313]: RasterPos3i (offset 74) */
   "iii\0"
   "glRasterPos3i\0"
   "\0"
   /* _mesa_function_pool[2332]: Color4us (offset 39) */
   "iiii\0"
   "glColor4us\0"
   "\0"
   /* _mesa_function_pool[2349]: GetTexParameteriv (offset 283) */
   "iip\0"
   "glGetTexParameteriv\0"
   "\0"
   /* _mesa_function_pool[2374]: MapBufferOES (will be remapped) */
   "ii\0"
   "glMapBufferOES\0"
   "\0"
   /* _mesa_function_pool[2393]: MultiTexCoord2fARB (offset 386) */
   "iff\0"
   "glMultiTexCoord2fARB\0"
   "\0"
   /* _mesa_function_pool[2419]: ColorTable (offset 339) */
   "iiiiip\0"
   "glColorTable\0"
   "\0"
   /* _mesa_function_pool[2440]: IndexPointer (offset 314) */
   "iip\0"
   "glIndexPointer\0"
   "\0"
   /* _mesa_function_pool[2460]: Accum (offset 213) */
   "if\0"
   "glAccum\0"
   "\0"
   /* _mesa_function_pool[2472]: GetTexImage (offset 281) */
   "iiiip\0"
   "glGetTexImage\0"
   "\0"
   /* _mesa_function_pool[2493]: LoadName (offset 198) */
   "i\0"
   "glLoadName\0"
   "\0"
   /* _mesa_function_pool[2507]: Finish (offset 216) */
   "\0"
   "glFinish\0"
   "\0"
   /* _mesa_function_pool[2518]: ClearStencil (offset 207) */
   "i\0"
   "glClearStencil\0"
   "\0"
   /* _mesa_function_pool[2536]: ConvolutionParameteriv (offset 353) */
   "iip\0"
   "glConvolutionParameteriv\0"
   "\0"
   /* _mesa_function_pool[2566]: GenBuffers (will be remapped) */
   "ip\0"
   "glGenBuffers\0"
   "\0"
   /* _mesa_function_pool[2583]: InterleavedArrays (offset 317) */
   "iip\0"
   "glInterleavedArrays\0"
   "\0"
   /* _mesa_function_pool[2608]: RasterPos2fv (offset 65) */
   "p\0"
   "glRasterPos2fv\0"
   "\0"
   /* _mesa_function_pool[2626]: TexCoord1fv (offset 97) */
   "p\0"
   "glTexCoord1fv\0"
   "\0"
   /* _mesa_function_pool[2643]: MultiTexCoord1sARB (offset 382) */
   "ii\0"
   "glMultiTexCoord1sARB\0"
   "\0"
   /* _mesa_function_pool[2668]: EnableVertexAttribArray (will be remapped) */
   "i\0"
   "glEnableVertexAttribArray\0"
   "\0"
   /* _mesa_function_pool[2697]: Color4i (offset 31) */
   "iiii\0"
   "glColor4i\0"
   "\0"
   /* _mesa_function_pool[2713]: Color4f (offset 29) */
   "ffff\0"
   "glColor4f\0"
   "\0"
   /* _mesa_function_pool[2729]: RasterPos4fv (offset 81) */
   "p\0"
   "glRasterPos4fv\0"
   "\0"
   /* _mesa_function_pool[2747]: Color4d (offset 27) */
   "dddd\0"
   "glColor4d\0"
   "\0"
   /* _mesa_function_pool[2763]: ClearIndex (offset 205) */
   "f\0"
   "glClearIndex\0"
   "\0"
   /* _mesa_function_pool[2779]: Color4b (offset 25) */
   "iiii\0"
   "glColor4b\0"
   "\0"
   /* _mesa_function_pool[2795]: LoadMatrixd (offset 292) */
   "p\0"
   "glLoadMatrixd\0"
   "\0"
   /* _mesa_function_pool[2812]: PushMatrix (offset 298) */
   "\0"
   "glPushMatrix\0"
   "\0"
   /* _mesa_function_pool[2827]: ConvolutionParameterfv (offset 351) */
   "iip\0"
   "glConvolutionParameterfv\0"
   "\0"
   /* _mesa_function_pool[2857]: GetTexGendv (offset 278) */
   "iip\0"
   "glGetTexGendv\0"
   "\0"
   /* _mesa_function_pool[2876]: EndList (offset 1) */
   "\0"
   "glEndList\0"
   "\0"
   /* _mesa_function_pool[2888]: EvalCoord1fv (offset 231) */
   "p\0"
   "glEvalCoord1fv\0"
   "\0"
   /* _mesa_function_pool[2906]: DrawRangeElements (offset 338) */
   "iiiiip\0"
   "glDrawRangeElements\0"
   "\0"
   /* _mesa_function_pool[2934]: EvalMesh2 (offset 238) */
   "iiiii\0"
   "glEvalMesh2\0"
   "\0"
   /* _mesa_function_pool[2953]: Vertex4fv (offset 145) */
   "p\0"
   "glVertex4fv\0"
   "\0"
   /* _mesa_function_pool[2968]: BindFramebuffer (will be remapped) */
   "ii\0"
   "glBindFramebuffer\0"
   "\0"
   /* _mesa_function_pool[2990]: GenLists (offset 5) */
   "i\0"
   "glGenLists\0"
   "\0"
   /* _mesa_function_pool[3004]: ReleaseShaderCompiler (will be remapped) */
   "\0"
   "glReleaseShaderCompiler\0"
   "\0"
   /* _mesa_function_pool[3030]: GetMinmax (offset 364) */
   "iiiip\0"
   "glGetMinmax\0"
   "\0"
   /* _mesa_function_pool[3049]: BlendFuncSeparate (will be remapped) */
   "iiii\0"
   "glBlendFuncSeparate\0"
   "\0"
   /* _mesa_function_pool[3075]: StencilFuncSeparate (will be remapped) */
   "iiii\0"
   "glStencilFuncSeparate\0"
   "\0"
   /* _mesa_function_pool[3103]: ShaderSource (will be remapped) */
   "iipp\0"
   "glShaderSource\0"
   "\0"
   /* _mesa_function_pool[3124]: Normal3fv (offset 57) */
   "p\0"
   "glNormal3fv\0"
   "\0"
   /* _mesa_function_pool[3139]: Color3us (offset 23) */
   "iii\0"
   "glColor3us\0"
   "\0"
   /* _mesa_function_pool[3155]: End (offset 43) */
   "\0"
   "glEnd\0"
   "\0"
   /* _mesa_function_pool[3163]: MultiTexCoord3fvARB (offset 395) */
   "ip\0"
   "glMultiTexCoord3fvARB\0"
   "\0"
   /* _mesa_function_pool[3189]: Color3ub (offset 19) */
   "iii\0"
   "glColor3ub\0"
   "\0"
   /* _mesa_function_pool[3205]: BufferData (will be remapped) */
   "iipi\0"
   "glBufferData\0"
   "\0"
   /* _mesa_function_pool[3224]: Color3ui (offset 21) */
   "iii\0"
   "glColor3ui\0"
   "\0"
   /* _mesa_function_pool[3240]: TexSubImage2D (offset 333) */
   "iiiiiiiip\0"
   "glTexSubImage2D\0"
   "\0"
   /* _mesa_function_pool[3267]: Enable (offset 215) */
   "i\0"
   "glEnable\0"
   "\0"
   /* _mesa_function_pool[3279]: GetVertexAttribiv (will be remapped) */
   "iip\0"
   "glGetVertexAttribiv\0"
   "\0"
   /* _mesa_function_pool[3304]: ShaderBinary (will be remapped) */
   "ipipi\0"
   "glShaderBinary\0"
   "\0"
   /* _mesa_function_pool[3326]: MultiTexCoord4sARB (offset 406) */
   "iiiii\0"
   "glMultiTexCoord4sARB\0"
   "\0"
   /* _mesa_function_pool[3354]: MapGrid2d (offset 226) */
   "iddidd\0"
   "glMapGrid2d\0"
   "\0"
   /* _mesa_function_pool[3374]: BlendEquation (offset 337) */
   "i\0"
   "glBlendEquation\0"
   "\0"
   /* _mesa_function_pool[3393]: GetError (offset 261) */
   "\0"
   "glGetError\0"
   "\0"
   /* _mesa_function_pool[3406]: TexCoord3dv (offset 111) */
   "p\0"
   "glTexCoord3dv\0"
   "\0"
   /* _mesa_function_pool[3423]: PassThrough (offset 199) */
   "f\0"
   "glPassThrough\0"
   "\0"
   /* _mesa_function_pool[3440]: Normal3s (offset 60) */
   "iii\0"
   "glNormal3s\0"
   "\0"
   /* _mesa_function_pool[3456]: PushName (offset 201) */
   "i\0"
   "glPushName\0"
   "\0"
   /* _mesa_function_pool[3470]: MultiTexCoord2dvARB (offset 385) */
   "ip\0"
   "glMultiTexCoord2dvARB\0"
   "\0"
   /* _mesa_function_pool[3496]: Normal3i (offset 58) */
   "iii\0"
   "glNormal3i\0"
   "\0"
   /* _mesa_function_pool[3512]: DeleteRenderbuffers (will be remapped) */
   "ip\0"
   "glDeleteRenderbuffers\0"
   "\0"
   /* _mesa_function_pool[3538]: Normal3b (offset 52) */
   "iii\0"
   "glNormal3b\0"
   "\0"
   /* _mesa_function_pool[3554]: Normal3d (offset 54) */
   "ddd\0"
   "glNormal3d\0"
   "\0"
   /* _mesa_function_pool[3570]: CopyTexSubImage3DOES (offset 373) */
   "iiiiiiiii\0"
   "glCopyTexSubImage3DOES\0"
   "glCopyTexSubImage3D\0"
   "\0"
   /* _mesa_function_pool[3624]: Normal3f (offset 56) */
   "fff\0"
   "glNormal3f\0"
   "\0"
   /* _mesa_function_pool[3640]: MultiTexCoord1svARB (offset 383) */
   "ip\0"
   "glMultiTexCoord1svARB\0"
   "\0"
   /* _mesa_function_pool[3666]: Indexi (offset 48) */
   "i\0"
   "glIndexi\0"
   "\0"
   /* _mesa_function_pool[3678]: EGLImageTargetTexture2DOES (will be remapped) */
   "ip\0"
   "glEGLImageTargetTexture2DOES\0"
   "\0"
   /* _mesa_function_pool[3711]: IsRenderbuffer (will be remapped) */
   "i\0"
   "glIsRenderbuffer\0"
   "\0"
   /* _mesa_function_pool[3731]: DepthMask (offset 211) */
   "i\0"
   "glDepthMask\0"
   "\0"
   /* _mesa_function_pool[3746]: IsShader (will be remapped) */
   "i\0"
   "glIsShader\0"
   "\0"
   /* _mesa_function_pool[3760]: Indexf (offset 46) */
   "f\0"
   "glIndexf\0"
   "\0"
   /* _mesa_function_pool[3772]: Color4iv (offset 32) */
   "p\0"
   "glColor4iv\0"
   "\0"
   /* _mesa_function_pool[3786]: GetMaterialiv (offset 270) */
   "iip\0"
   "glGetMaterialiv\0"
   "\0"
   /* _mesa_function_pool[3807]: StencilOp (offset 244) */
   "iii\0"
   "glStencilOp\0"
   "\0"
   /* _mesa_function_pool[3824]: GetShaderInfoLog (will be remapped) */
   "iipp\0"
   "glGetShaderInfoLog\0"
   "\0"
   /* _mesa_function_pool[3849]: TexEnvfv (offset 185) */
   "iip\0"
   "glTexEnvfv\0"
   "\0"
   /* _mesa_function_pool[3865]: MultiTexCoord4iARB (offset 404) */
   "iiiii\0"
   "glMultiTexCoord4iARB\0"
   "\0"
   /* _mesa_function_pool[3893]: Indexs (offset 50) */
   "i\0"
   "glIndexs\0"
   "\0"
   /* _mesa_function_pool[3905]: EGLImageTargetRenderbufferStorageOES (will be remapped) */
   "ip\0"
   "glEGLImageTargetRenderbufferStorageOES\0"
   "\0"
   /* _mesa_function_pool[3948]: Vertex2i (offset 130) */
   "ii\0"
   "glVertex2i\0"
   "\0"
   /* _mesa_function_pool[3963]: Vertex2d (offset 126) */
   "dd\0"
   "glVertex2d\0"
   "\0"
   /* _mesa_function_pool[3978]: Vertex2f (offset 128) */
   "ff\0"
   "glVertex2f\0"
   "\0"
   /* _mesa_function_pool[3993]: Color4bv (offset 26) */
   "p\0"
   "glColor4bv\0"
   "\0"
   /* _mesa_function_pool[4007]: VertexPointer (offset 321) */
   "iiip\0"
   "glVertexPointer\0"
   "\0"
   /* _mesa_function_pool[4029]: DeleteLists (offset 4) */
   "ii\0"
   "glDeleteLists\0"
   "\0"
   /* _mesa_function_pool[4047]: LogicOp (offset 242) */
   "i\0"
   "glLogicOp\0"
   "\0"
   /* _mesa_function_pool[4060]: Vertex2s (offset 132) */
   "ii\0"
   "glVertex2s\0"
   "\0"
   /* _mesa_function_pool[4075]: TexCoord4fv (offset 121) */
   "p\0"
   "glTexCoord4fv\0"
   "\0"
   /* _mesa_function_pool[4092]: ActiveTexture (offset 374) */
   "i\0"
   "glActiveTexture\0"
   "glActiveTextureARB\0"
   "\0"
   /* _mesa_function_pool[4130]: MultiTexCoord3iARB (offset 396) */
   "iiii\0"
   "glMultiTexCoord3iARB\0"
   "\0"
   /* _mesa_function_pool[4157]: IsProgram (will be remapped) */
   "i\0"
   "glIsProgram\0"
   "\0"
   /* _mesa_function_pool[4172]: GenTextures (offset 328) */
   "ip\0"
   "glGenTextures\0"
   "\0"
   /* _mesa_function_pool[4190]: RasterPos2sv (offset 69) */
   "p\0"
   "glRasterPos2sv\0"
   "\0"
   /* _mesa_function_pool[4208]: Color4ubv (offset 36) */
   "p\0"
   "glColor4ubv\0"
   "\0"
   /* _mesa_function_pool[4223]: DrawBuffer (offset 202) */
   "i\0"
   "glDrawBuffer\0"
   "\0"
   /* _mesa_function_pool[4239]: TexCoord2fv (offset 105) */
   "p\0"
   "glTexCoord2fv\0"
   "\0"
   /* _mesa_function_pool[4256]: GetPointerv (offset 329) */
   "ip\0"
   "glGetPointerv\0"
   "\0"
   /* _mesa_function_pool[4274]: TexCoord1sv (offset 101) */
   "p\0"
   "glTexCoord1sv\0"
   "\0"
   /* _mesa_function_pool[4291]: PixelMapfv (offset 251) */
   "iip\0"
   "glPixelMapfv\0"
   "\0"
   /* _mesa_function_pool[4309]: PixelMapusv (offset 253) */
   "iip\0"
   "glPixelMapusv\0"
   "\0"
   /* _mesa_function_pool[4328]: MultiTexCoord1dARB (offset 376) */
   "id\0"
   "glMultiTexCoord1dARB\0"
   "\0"
   /* _mesa_function_pool[4353]: BlendFunc (offset 241) */
   "ii\0"
   "glBlendFunc\0"
   "\0"
   /* _mesa_function_pool[4369]: Uniform4i (will be remapped) */
   "iiiii\0"
   "glUniform4i\0"
   "\0"
   /* _mesa_function_pool[4388]: ProgramBinaryOES (will be remapped) */
   "iipi\0"
   "glProgramBinaryOES\0"
   "\0"
   /* _mesa_function_pool[4413]: CompressedTexImage2D (will be remapped) */
   "iiiiiiip\0"
   "glCompressedTexImage2D\0"
   "\0"
   /* _mesa_function_pool[4446]: MultiTexCoord3dvARB (offset 393) */
   "ip\0"
   "glMultiTexCoord3dvARB\0"
   "\0"
   /* _mesa_function_pool[4472]: GetShaderPrecisionFormat (will be remapped) */
   "iipp\0"
   "glGetShaderPrecisionFormat\0"
   "\0"
   /* _mesa_function_pool[4505]: Flush (offset 217) */
   "\0"
   "glFlush\0"
   "\0"
   /* _mesa_function_pool[4515]: Color4uiv (offset 38) */
   "p\0"
   "glColor4uiv\0"
   "\0"
   /* _mesa_function_pool[4530]: RasterPos3sv (offset 77) */
   "p\0"
   "glRasterPos3sv\0"
   "\0"
   /* _mesa_function_pool[4548]: PushAttrib (offset 219) */
   "i\0"
   "glPushAttrib\0"
   "\0"
   /* _mesa_function_pool[4564]: RasterPos2i (offset 66) */
   "ii\0"
   "glRasterPos2i\0"
   "\0"
   /* _mesa_function_pool[4582]: Uniform3iv (will be remapped) */
   "iip\0"
   "glUniform3iv\0"
   "\0"
   /* _mesa_function_pool[4600]: TexParameteriv (offset 181) */
   "iip\0"
   "glTexParameteriv\0"
   "\0"
   /* _mesa_function_pool[4622]: GetAttribLocation (will be remapped) */
   "ip\0"
   "glGetAttribLocation\0"
   "\0"
   /* _mesa_function_pool[4646]: RasterPos2f (offset 64) */
   "ff\0"
   "glRasterPos2f\0"
   "\0"
   /* _mesa_function_pool[4664]: RasterPos2d (offset 62) */
   "dd\0"
   "glRasterPos2d\0"
   "\0"
   /* _mesa_function_pool[4682]: RasterPos3fv (offset 73) */
   "p\0"
   "glRasterPos3fv\0"
   "\0"
   /* _mesa_function_pool[4700]: Color4ub (offset 35) */
   "iiii\0"
   "glColor4ub\0"
   "\0"
   /* _mesa_function_pool[4717]: RasterPos2s (offset 68) */
   "ii\0"
   "glRasterPos2s\0"
   "\0"
   /* _mesa_function_pool[4735]: GetColorTable (offset 343) */
   "iiip\0"
   "glGetColorTable\0"
   "\0"
   /* _mesa_function_pool[4757]: Indexiv (offset 49) */
   "p\0"
   "glIndexiv\0"
   "\0"
   /* _mesa_function_pool[4770]: TexCoord3i (offset 114) */
   "iii\0"
   "glTexCoord3i\0"
   "\0"
   /* _mesa_function_pool[4788]: CopyColorTable (offset 342) */
   "iiiii\0"
   "glCopyColorTable\0"
   "\0"
   /* _mesa_function_pool[4812]: GetHistogramParameterfv (offset 362) */
   "iip\0"
   "glGetHistogramParameterfv\0"
   "\0"
   /* _mesa_function_pool[4843]: Frustum (offset 289) */
   "dddddd\0"
   "glFrustum\0"
   "\0"
   /* _mesa_function_pool[4861]: GetString (offset 275) */
   "i\0"
   "glGetString\0"
   "\0"
   /* _mesa_function_pool[4876]: TexEnvf (offset 184) */
   "iif\0"
   "glTexEnvf\0"
   "\0"
   /* _mesa_function_pool[4891]: TexCoord3d (offset 110) */
   "ddd\0"
   "glTexCoord3d\0"
   "\0"
   /* _mesa_function_pool[4909]: VertexAttrib3fv (will be remapped) */
   "ip\0"
   "glVertexAttrib3fv\0"
   "\0"
   /* _mesa_function_pool[4931]: TexCoord3f (offset 112) */
   "fff\0"
   "glTexCoord3f\0"
   "\0"
   /* _mesa_function_pool[4949]: MultiTexCoord3ivARB (offset 397) */
   "ip\0"
   "glMultiTexCoord3ivARB\0"
   "\0"
   /* _mesa_function_pool[4975]: MultiTexCoord2sARB (offset 390) */
   "iii\0"
   "glMultiTexCoord2sARB\0"
   "\0"
   /* _mesa_function_pool[5001]: DeleteTextures (offset 327) */
   "ip\0"
   "glDeleteTextures\0"
   "\0"
   /* _mesa_function_pool[5022]: TexCoord3s (offset 116) */
   "iii\0"
   "glTexCoord3s\0"
   "\0"
   /* _mesa_function_pool[5040]: GetTexLevelParameteriv (offset 285) */
   "iiip\0"
   "glGetTexLevelParameteriv\0"
   "\0"
   /* _mesa_function_pool[5071]: ClearAccum (offset 204) */
   "ffff\0"
   "glClearAccum\0"
   "\0"
   /* _mesa_function_pool[5090]: TexCoord4iv (offset 123) */
   "p\0"
   "glTexCoord4iv\0"
   "\0"
   /* _mesa_function_pool[5107]: PolygonOffset (offset 319) */
   "ff\0"
   "glPolygonOffset\0"
   "\0"
   /* _mesa_function_pool[5127]: GetBufferParameteriv (will be remapped) */
   "iip\0"
   "glGetBufferParameteriv\0"
   "\0"
   /* _mesa_function_pool[5155]: Indexfv (offset 47) */
   "p\0"
   "glIndexfv\0"
   "\0"
   /* _mesa_function_pool[5168]: ColorTableParameteriv (offset 341) */
   "iip\0"
   "glColorTableParameteriv\0"
   "\0"
   /* _mesa_function_pool[5197]: CopyTexImage2D (offset 324) */
   "iiiiiiii\0"
   "glCopyTexImage2D\0"
   "\0"
   /* _mesa_function_pool[5224]: GenVertexArraysAPPLE (will be remapped) */
   "ip\0"
   "glGenVertexArraysAPPLE\0"
   "\0"
   /* _mesa_function_pool[5251]: Lightfv (offset 160) */
   "iip\0"
   "glLightfv\0"
   "\0"
   /* _mesa_function_pool[5266]: GetFramebufferAttachmentParameteriv (will be remapped) */
   "iiip\0"
   "glGetFramebufferAttachmentParameteriv\0"
   "\0"
   /* _mesa_function_pool[5310]: ClearDepth (offset 208) */
   "d\0"
   "glClearDepth\0"
   "\0"
   /* _mesa_function_pool[5326]: GetVertexAttribPointerv (will be remapped) */
   "iip\0"
   "glGetVertexAttribPointerv\0"
   "\0"
   /* _mesa_function_pool[5357]: ColorSubTable (offset 346) */
   "iiiiip\0"
   "glColorSubTable\0"
   "\0"
   /* _mesa_function_pool[5381]: Color4fv (offset 30) */
   "p\0"
   "glColor4fv\0"
   "\0"
   /* _mesa_function_pool[5395]: MultiTexCoord4ivARB (offset 405) */
   "ip\0"
   "glMultiTexCoord4ivARB\0"
   "\0"
   /* _mesa_function_pool[5421]: ColorPointer (offset 308) */
   "iiip\0"
   "glColorPointer\0"
   "\0"
   /* _mesa_function_pool[5442]: GetShaderiv (will be remapped) */
   "iip\0"
   "glGetShaderiv\0"
   "\0"
   /* _mesa_function_pool[5461]: Lightiv (offset 162) */
   "iip\0"
   "glLightiv\0"
   "\0"
   /* _mesa_function_pool[5476]: Color3bv (offset 10) */
   "p\0"
   "glColor3bv\0"
   "\0"
   /* _mesa_function_pool[5490]: GetBufferPointervOES (will be remapped) */
   "iip\0"
   "glGetBufferPointervOES\0"
   "\0"
   /* _mesa_function_pool[5518]: Rectdv (offset 87) */
   "pp\0"
   "glRectdv\0"
   "\0"
   /* _mesa_function_pool[5531]: GetAttachedShaders (will be remapped) */
   "iipp\0"
   "glGetAttachedShaders\0"
   "\0"
   /* _mesa_function_pool[5558]: Materialiv (offset 172) */
   "iip\0"
   "glMaterialiv\0"
   "\0"
   /* _mesa_function_pool[5576]: PushClientAttrib (offset 335) */
   "i\0"
   "glPushClientAttrib\0"
   "\0"
   /* _mesa_function_pool[5598]: PolygonMode (offset 174) */
   "ii\0"
   "glPolygonMode\0"
   "\0"
   /* _mesa_function_pool[5616]: LinkProgram (will be remapped) */
   "i\0"
   "glLinkProgram\0"
   "\0"
   /* _mesa_function_pool[5633]: Uniform1f (will be remapped) */
   "if\0"
   "glUniform1f\0"
   "\0"
   /* _mesa_function_pool[5649]: DisableClientState (offset 309) */
   "i\0"
   "glDisableClientState\0"
   "\0"
   /* _mesa_function_pool[5673]: TexGeni (offset 192) */
   "iii\0"
   "glTexGeni\0"
   "\0"
   /* _mesa_function_pool[5688]: TexGenf (offset 190) */
   "iif\0"
   "glTexGenf\0"
   "\0"
   /* _mesa_function_pool[5703]: TexGend (offset 188) */
   "iid\0"
   "glTexGend\0"
   "\0"
   /* _mesa_function_pool[5718]: Uniform1i (will be remapped) */
   "ii\0"
   "glUniform1i\0"
   "\0"
   /* _mesa_function_pool[5734]: GetPolygonStipple (offset 274) */
   "p\0"
   "glGetPolygonStipple\0"
   "\0"
   /* _mesa_function_pool[5757]: VertexAttrib4f (will be remapped) */
   "iffff\0"
   "glVertexAttrib4f\0"
   "\0"
   /* _mesa_function_pool[5781]: ConvolutionFilter2D (offset 349) */
   "iiiiiip\0"
   "glConvolutionFilter2D\0"
   "\0"
   /* _mesa_function_pool[5812]: ClientActiveTextureARB (offset 375) */
   "i\0"
   "glClientActiveTextureARB\0"
   "\0"
   /* _mesa_function_pool[5840]: UseProgram (will be remapped) */
   "i\0"
   "glUseProgram\0"
   "\0"
   /* _mesa_function_pool[5856]: Color4sv (offset 34) */
   "p\0"
   "glColor4sv\0"
   "\0"
   /* _mesa_function_pool[5870]: Uniform4f (will be remapped) */
   "iffff\0"
   "glUniform4f\0"
   "\0"
   /* _mesa_function_pool[5889]: ResetHistogram (offset 369) */
   "i\0"
   "glResetHistogram\0"
   "\0"
   /* _mesa_function_pool[5909]: PixelZoom (offset 246) */
   "ff\0"
   "glPixelZoom\0"
   "\0"
   /* _mesa_function_pool[5925]: ColorTableParameterfv (offset 340) */
   "iip\0"
   "glColorTableParameterfv\0"
   "\0"
   /* _mesa_function_pool[5954]: PixelMapuiv (offset 252) */
   "iip\0"
   "glPixelMapuiv\0"
   "\0"
   /* _mesa_function_pool[5973]: Color3dv (offset 12) */
   "p\0"
   "glColor3dv\0"
   "\0"
   /* _mesa_function_pool[5987]: IsTexture (offset 330) */
   "i\0"
   "glIsTexture\0"
   "\0"
   /* _mesa_function_pool[6002]: Fogfv (offset 154) */
   "ip\0"
   "glFogfv\0"
   "\0"
   /* _mesa_function_pool[6014]: GetMapdv (offset 266) */
   "iip\0"
   "glGetMapdv\0"
   "\0"
   /* _mesa_function_pool[6030]: GetUniformLocation (will be remapped) */
   "ip\0"
   "glGetUniformLocation\0"
   "\0"
   /* _mesa_function_pool[6055]: PixelStoref (offset 249) */
   "if\0"
   "glPixelStoref\0"
   "\0"
   /* _mesa_function_pool[6073]: PrioritizeTextures (offset 331) */
   "ipp\0"
   "glPrioritizeTextures\0"
   "\0"
   /* _mesa_function_pool[6099]: PixelStorei (offset 250) */
   "ii\0"
   "glPixelStorei\0"
   "\0"
   /* _mesa_function_pool[6117]: IsBuffer (will be remapped) */
   "i\0"
   "glIsBuffer\0"
   "\0"
   /* _mesa_function_pool[6131]: EvalCoord2dv (offset 233) */
   "p\0"
   "glEvalCoord2dv\0"
   "\0"
   /* _mesa_function_pool[6149]: ColorMaterial (offset 151) */
   "ii\0"
   "glColorMaterial\0"
   "\0"
   /* _mesa_function_pool[6169]: Minmax (offset 368) */
   "iii\0"
   "glMinmax\0"
   "\0"
   /* _mesa_function_pool[6183]: GetSeparableFilter (offset 359) */
   "iiippp\0"
   "glGetSeparableFilter\0"
   "\0"
   /* _mesa_function_pool[6212]: FeedbackBuffer (offset 194) */
   "iip\0"
   "glFeedbackBuffer\0"
   "\0"
   /* _mesa_function_pool[6234]: RasterPos2iv (offset 67) */
   "p\0"
   "glRasterPos2iv\0"
   "\0"
   /* _mesa_function_pool[6252]: TexImage1D (offset 182) */
   "iiiiiiip\0"
   "glTexImage1D\0"
   "\0"
   /* _mesa_function_pool[6275]: MultiDrawElementsEXT (will be remapped) */
   "ipipi\0"
   "glMultiDrawElementsEXT\0"
   "\0"
   /* _mesa_function_pool[6305]: Color3s (offset 17) */
   "iii\0"
   "glColor3s\0"
   "\0"
   /* _mesa_function_pool[6320]: CheckFramebufferStatus (will be remapped) */
   "i\0"
   "glCheckFramebufferStatus\0"
   "\0"
   /* _mesa_function_pool[6348]: TexCoordPointer (offset 320) */
   "iiip\0"
   "glTexCoordPointer\0"
   "\0"
   /* _mesa_function_pool[6372]: Color3i (offset 15) */
   "iii\0"
   "glColor3i\0"
   "\0"
   /* _mesa_function_pool[6387]: FrontFace (offset 157) */
   "i\0"
   "glFrontFace\0"
   "\0"
   /* _mesa_function_pool[6402]: EvalCoord2d (offset 232) */
   "dd\0"
   "glEvalCoord2d\0"
   "\0"
   /* _mesa_function_pool[6420]: EvalCoord2f (offset 234) */
   "ff\0"
   "glEvalCoord2f\0"
   "\0"
   /* _mesa_function_pool[6438]: Color3b (offset 9) */
   "iii\0"
   "glColor3b\0"
   "\0"
   /* _mesa_function_pool[6453]: MultiTexCoord2dARB (offset 384) */
   "idd\0"
   "glMultiTexCoord2dARB\0"
   "\0"
   /* _mesa_function_pool[6479]: Color3f (offset 13) */
   "fff\0"
   "glColor3f\0"
   "\0"
   /* _mesa_function_pool[6494]: Color3d (offset 11) */
   "ddd\0"
   "glColor3d\0"
   "\0"
   /* _mesa_function_pool[6509]: Normal3dv (offset 55) */
   "p\0"
   "glNormal3dv\0"
   "\0"
   /* _mesa_function_pool[6524]: Lightf (offset 159) */
   "iif\0"
   "glLightf\0"
   "\0"
   /* _mesa_function_pool[6538]: MatrixMode (offset 293) */
   "i\0"
   "glMatrixMode\0"
   "\0"
   /* _mesa_function_pool[6554]: Uniform1iv (will be remapped) */
   "iip\0"
   "glUniform1iv\0"
   "\0"
   /* _mesa_function_pool[6572]: Lighti (offset 161) */
   "iii\0"
   "glLighti\0"
   "\0"
   /* _mesa_function_pool[6586]: GenFramebuffers (will be remapped) */
   "ip\0"
   "glGenFramebuffers\0"
   "\0"
   /* _mesa_function_pool[6608]: Color4s (offset 33) */
   "iiii\0"
   "glColor4s\0"
   "\0"
   /* _mesa_function_pool[6624]: IsFramebuffer (will be remapped) */
   "i\0"
   "glIsFramebuffer\0"
   "\0"
   /* _mesa_function_pool[6643]: BlendEquationSeparate (will be remapped) */
   "ii\0"
   "glBlendEquationSeparate\0"
   "\0"
   /* _mesa_function_pool[6671]: GetDoublev (offset 260) */
   "ip\0"
   "glGetDoublev\0"
   "\0"
   /* _mesa_function_pool[6688]: MultMatrixd (offset 295) */
   "p\0"
   "glMultMatrixd\0"
   "\0"
   /* _mesa_function_pool[6705]: MultMatrixf (offset 294) */
   "p\0"
   "glMultMatrixf\0"
   "\0"
   /* _mesa_function_pool[6722]: VertexAttrib1f (will be remapped) */
   "if\0"
   "glVertexAttrib1f\0"
   "\0"
   /* _mesa_function_pool[6743]: MultiTexCoord4fvARB (offset 403) */
   "ip\0"
   "glMultiTexCoord4fvARB\0"
   "\0"
   /* _mesa_function_pool[6769]: RasterPos4sv (offset 85) */
   "p\0"
   "glRasterPos4sv\0"
   "\0"
   /* _mesa_function_pool[6787]: DrawArrays (offset 310) */
   "iii\0"
   "glDrawArrays\0"
   "\0"
   /* _mesa_function_pool[6805]: TexEnviv (offset 187) */
   "iip\0"
   "glTexEnviv\0"
   "\0"
   /* _mesa_function_pool[6821]: CreateShader (will be remapped) */
   "i\0"
   "glCreateShader\0"
   "\0"
   /* _mesa_function_pool[6839]: GetColorTableParameterfv (offset 344) */
   "iip\0"
   "glGetColorTableParameterfv\0"
   "\0"
   /* _mesa_function_pool[6871]: FramebufferTexture2D (will be remapped) */
   "iiiii\0"
   "glFramebufferTexture2D\0"
   "\0"
   /* _mesa_function_pool[6901]: Bitmap (offset 8) */
   "iiffffp\0"
   "glBitmap\0"
   "\0"
   /* _mesa_function_pool[6919]: MultiTexCoord3fARB (offset 394) */
   "ifff\0"
   "glMultiTexCoord3fARB\0"
   "\0"
   /* _mesa_function_pool[6946]: GetTexLevelParameterfv (offset 284) */
   "iiip\0"
   "glGetTexLevelParameterfv\0"
   "\0"
   /* _mesa_function_pool[6977]: Vertex2sv (offset 133) */
   "p\0"
   "glVertex2sv\0"
   "\0"
   /* _mesa_function_pool[6992]: GetIntegerv (offset 263) */
   "ip\0"
   "glGetIntegerv\0"
   "\0"
   /* _mesa_function_pool[7010]: GetShaderSource (will be remapped) */
   "iipp\0"
   "glGetShaderSource\0"
   "\0"
   /* _mesa_function_pool[7034]: GetActiveUniform (will be remapped) */
   "iiipppp\0"
   "glGetActiveUniform\0"
   "\0"
   /* _mesa_function_pool[7062]: DeleteBuffers (will be remapped) */
   "ip\0"
   "glDeleteBuffers\0"
   "\0"
   /* _mesa_function_pool[7082]: GetTexEnviv (offset 277) */
   "iip\0"
   "glGetTexEnviv\0"
   "\0"
   /* _mesa_function_pool[7101]: PopClientAttrib (offset 334) */
   "\0"
   "glPopClientAttrib\0"
   "\0"
   /* _mesa_function_pool[7121]: SeparableFilter2D (offset 360) */
   "iiiiiipp\0"
   "glSeparableFilter2D\0"
   "\0"
   /* _mesa_function_pool[7151]: VertexAttrib2fv (will be remapped) */
   "ip\0"
   "glVertexAttrib2fv\0"
   "\0"
   /* _mesa_function_pool[7173]: Map1d (offset 220) */
   "iddiip\0"
   "glMap1d\0"
   "\0"
   /* _mesa_function_pool[7189]: Map1f (offset 221) */
   "iffiip\0"
   "glMap1f\0"
   "\0"
   /* _mesa_function_pool[7205]: ArrayElement (offset 306) */
   "i\0"
   "glArrayElement\0"
   "\0"
   /* _mesa_function_pool[7223]: TexImage2D (offset 183) */
   "iiiiiiiip\0"
   "glTexImage2D\0"
   "\0"
   /* _mesa_function_pool[7247]: GetMinmaxParameteriv (offset 366) */
   "iip\0"
   "glGetMinmaxParameteriv\0"
   "\0"
   /* _mesa_function_pool[7275]: PixelTransferf (offset 247) */
   "if\0"
   "glPixelTransferf\0"
   "\0"
   /* _mesa_function_pool[7296]: CopyTexImage1D (offset 323) */
   "iiiiiii\0"
   "glCopyTexImage1D\0"
   "\0"
   /* _mesa_function_pool[7322]: RasterPos2dv (offset 63) */
   "p\0"
   "glRasterPos2dv\0"
   "\0"
   /* _mesa_function_pool[7340]: Fogiv (offset 156) */
   "ip\0"
   "glFogiv\0"
   "\0"
   /* _mesa_function_pool[7352]: TexCoord1dv (offset 95) */
   "p\0"
   "glTexCoord1dv\0"
   "\0"
   /* _mesa_function_pool[7369]: PixelTransferi (offset 248) */
   "ii\0"
   "glPixelTransferi\0"
   "\0"
   /* _mesa_function_pool[7390]: Rotatef (offset 300) */
   "ffff\0"
   "glRotatef\0"
   "\0"
   /* _mesa_function_pool[7406]: Vertex3i (offset 138) */
   "iii\0"
   "glVertex3i\0"
   "\0"
   /* _mesa_function_pool[7422]: Vertex3f (offset 136) */
   "fff\0"
   "glVertex3f\0"
   "\0"
   /* _mesa_function_pool[7438]: Clear (offset 203) */
   "i\0"
   "glClear\0"
   "\0"
   /* _mesa_function_pool[7449]: Vertex3d (offset 134) */
   "ddd\0"
   "glVertex3d\0"
   "\0"
   /* _mesa_function_pool[7465]: ReadBuffer (offset 254) */
   "i\0"
   "glReadBuffer\0"
   "\0"
   /* _mesa_function_pool[7481]: ConvolutionParameteri (offset 352) */
   "iii\0"
   "glConvolutionParameteri\0"
   "\0"
   /* _mesa_function_pool[7510]: Ortho (offset 296) */
   "dddddd\0"
   "glOrtho\0"
   "\0"
   /* _mesa_function_pool[7526]: ListBase (offset 6) */
   "i\0"
   "glListBase\0"
   "\0"
   /* _mesa_function_pool[7540]: Vertex3s (offset 140) */
   "iii\0"
   "glVertex3s\0"
   "\0"
   /* _mesa_function_pool[7556]: ConvolutionParameterf (offset 350) */
   "iif\0"
   "glConvolutionParameterf\0"
   "\0"
   /* _mesa_function_pool[7585]: GetColorTableParameteriv (offset 345) */
   "iip\0"
   "glGetColorTableParameteriv\0"
   "\0"
   /* _mesa_function_pool[7617]: ShadeModel (offset 177) */
   "i\0"
   "glShadeModel\0"
   "\0"
   /* _mesa_function_pool[7633]: GenerateMipmap (will be remapped) */
   "i\0"
   "glGenerateMipmap\0"
   "\0"
   /* _mesa_function_pool[7653]: Rectiv (offset 91) */
   "pp\0"
   "glRectiv\0"
   "\0"
   /* _mesa_function_pool[7666]: TexCoord3fv (offset 113) */
   "p\0"
   "glTexCoord3fv\0"
   "\0"
   /* _mesa_function_pool[7683]: Vertex2fv (offset 129) */
   "p\0"
   "glVertex2fv\0"
   "\0"
   /* _mesa_function_pool[7698]: MultiDrawArraysEXT (will be remapped) */
   "ippi\0"
   "glMultiDrawArraysEXT\0"
   "\0"
   /* _mesa_function_pool[7725]: MultiTexCoord4dARB (offset 400) */
   "idddd\0"
   "glMultiTexCoord4dARB\0"
   "\0"
   /* _mesa_function_pool[7753]: Vertex3sv (offset 141) */
   "p\0"
   "glVertex3sv\0"
   "\0"
   /* _mesa_function_pool[7768]: EvalMesh1 (offset 236) */
   "iii\0"
   "glEvalMesh1\0"
   "\0"
   /* _mesa_function_pool[7785]: DeleteShader (will be remapped) */
   "i\0"
   "glDeleteShader\0"
   "\0"
   /* _mesa_function_pool[7803]: VertexAttrib2f (will be remapped) */
   "iff\0"
   "glVertexAttrib2f\0"
   "\0"
   /* _mesa_function_pool[7825]: Uniform2f (will be remapped) */
   "iff\0"
   "glUniform2f\0"
   "\0"
   /* _mesa_function_pool[7842]: MultiTexCoord1dvARB (offset 377) */
   "ip\0"
   "glMultiTexCoord1dvARB\0"
   "\0"
   /* _mesa_function_pool[7868]: CompileShader (will be remapped) */
   "i\0"
   "glCompileShader\0"
   "\0"
   /* _mesa_function_pool[7887]: Vertex2iv (offset 131) */
   "p\0"
   "glVertex2iv\0"
   "\0"
   /* _mesa_function_pool[7902]: LineWidth (offset 168) */
   "f\0"
   "glLineWidth\0"
   "\0"
   /* _mesa_function_pool[7917]: MultiTexCoord2ivARB (offset 389) */
   "ip\0"
   "glMultiTexCoord2ivARB\0"
   "\0"
   /* _mesa_function_pool[7943]: Uniform2i (will be remapped) */
   "iii\0"
   "glUniform2i\0"
   "\0"
   /* _mesa_function_pool[7960]: TexGendv (offset 189) */
   "iip\0"
   "glTexGendv\0"
   "\0"
   /* _mesa_function_pool[7976]: Uniform1fv (will be remapped) */
   "iip\0"
   "glUniform1fv\0"
   "\0"
   /* _mesa_function_pool[7994]: ResetMinmax (offset 370) */
   "i\0"
   "glResetMinmax\0"
   "\0"
   /* _mesa_function_pool[8011]: EnableClientState (offset 313) */
   "i\0"
   "glEnableClientState\0"
   "\0"
   /* _mesa_function_pool[8034]: GetConvolutionParameterfv (offset 357) */
   "iip\0"
   "glGetConvolutionParameterfv\0"
   "\0"
   /* _mesa_function_pool[8067]: GetPixelMapusv (offset 273) */
   "ip\0"
   "glGetPixelMapusv\0"
   "\0"
   /* _mesa_function_pool[8088]: GetMaterialfv (offset 269) */
   "iip\0"
   "glGetMaterialfv\0"
   "\0"
   /* _mesa_function_pool[8109]: CallList (offset 2) */
   "i\0"
   "glCallList\0"
   "\0"
   /* _mesa_function_pool[8123]: Materialfv (offset 170) */
   "iip\0"
   "glMaterialfv\0"
   "\0"
   /* _mesa_function_pool[8141]: DeleteProgram (will be remapped) */
   "i\0"
   "glDeleteProgram\0"
   "\0"
   /* _mesa_function_pool[8160]: CompressedTexSubImage3DOES (will be remapped) */
   "iiiiiiiiiip\0"
   "glCompressedTexSubImage3DOES\0"
   "\0"
   /* _mesa_function_pool[8202]: MultiTexCoord1ivARB (offset 381) */
   "ip\0"
   "glMultiTexCoord1ivARB\0"
   "\0"
   /* _mesa_function_pool[8228]: DetachShader (will be remapped) */
   "ii\0"
   "glDetachShader\0"
   "\0"
   /* _mesa_function_pool[8247]: ClearDepthf (will be remapped) */
   "f\0"
   "glClearDepthf\0"
   "\0"
   /* _mesa_function_pool[8264]: CopyTexSubImage2D (offset 326) */
   "iiiiiiii\0"
   "glCopyTexSubImage2D\0"
   "\0"
   /* _mesa_function_pool[8294]: SampleCoverage (will be remapped) */
   "fi\0"
   "glSampleCoverage\0"
   "\0"
   /* _mesa_function_pool[8315]: Color3iv (offset 16) */
   "p\0"
   "glColor3iv\0"
   "\0"
   /* _mesa_function_pool[8329]: DrawElements (offset 311) */
   "iiip\0"
   "glDrawElements\0"
   "\0"
   /* _mesa_function_pool[8350]: BindVertexArrayAPPLE (will be remapped) */
   "i\0"
   "glBindVertexArrayAPPLE\0"
   "\0"
   /* _mesa_function_pool[8376]: GetHistogramParameteriv (offset 363) */
   "iip\0"
   "glGetHistogramParameteriv\0"
   "\0"
   /* _mesa_function_pool[8407]: MultiTexCoord1iARB (offset 380) */
   "ii\0"
   "glMultiTexCoord1iARB\0"
   "\0"
   /* _mesa_function_pool[8432]: GetConvolutionFilter (offset 356) */
   "iiip\0"
   "glGetConvolutionFilter\0"
   "\0"
   /* _mesa_function_pool[8461]: TexSubImage3DOES (offset 372) */
   "iiiiiiiiiip\0"
   "glTexSubImage3DOES\0"
   "glTexSubImage3D\0"
   "\0"
   /* _mesa_function_pool[8509]: Uniform2iv (will be remapped) */
   "iip\0"
   "glUniform2iv\0"
   "\0"
   /* _mesa_function_pool[8527]: BindRenderbuffer (will be remapped) */
   "ii\0"
   "glBindRenderbuffer\0"
   "\0"
   /* _mesa_function_pool[8550]: EvalPoint2 (offset 239) */
   "ii\0"
   "glEvalPoint2\0"
   "\0"
   /* _mesa_function_pool[8567]: EvalPoint1 (offset 237) */
   "i\0"
   "glEvalPoint1\0"
   "\0"
   /* _mesa_function_pool[8583]: PopMatrix (offset 297) */
   "\0"
   "glPopMatrix\0"
   "\0"
   /* _mesa_function_pool[8597]: DeleteFramebuffers (will be remapped) */
   "ip\0"
   "glDeleteFramebuffers\0"
   "\0"
   /* _mesa_function_pool[8622]: GetTexGeniv (offset 280) */
   "iip\0"
   "glGetTexGeniv\0"
   "\0"
   /* _mesa_function_pool[8641]: MultiTexCoord4dvARB (offset 401) */
   "ip\0"
   "glMultiTexCoord4dvARB\0"
   "\0"
   /* _mesa_function_pool[8667]: FramebufferRenderbuffer (will be remapped) */
   "iiii\0"
   "glFramebufferRenderbuffer\0"
   "\0"
   /* _mesa_function_pool[8699]: Map2d (offset 222) */
   "iddiiddiip\0"
   "glMap2d\0"
   "\0"
   /* _mesa_function_pool[8719]: Map2f (offset 223) */
   "iffiiffiip\0"
   "glMap2f\0"
   "\0"
   /* _mesa_function_pool[8739]: Vertex4s (offset 148) */
   "iiii\0"
   "glVertex4s\0"
   "\0"
   /* _mesa_function_pool[8756]: Vertex4f (offset 144) */
   "ffff\0"
   "glVertex4f\0"
   "\0"
   /* _mesa_function_pool[8773]: EvalCoord1d (offset 228) */
   "d\0"
   "glEvalCoord1d\0"
   "\0"
   /* _mesa_function_pool[8790]: Vertex4d (offset 142) */
   "dddd\0"
   "glVertex4d\0"
   "\0"
   /* _mesa_function_pool[8807]: RasterPos4dv (offset 79) */
   "p\0"
   "glRasterPos4dv\0"
   "\0"
   /* _mesa_function_pool[8825]: GetTexGenfv (offset 279) */
   "iip\0"
   "glGetTexGenfv\0"
   "\0"
   /* _mesa_function_pool[8844]: Vertex4i (offset 146) */
   "iiii\0"
   "glVertex4i\0"
   "\0"
   /* _mesa_function_pool[8861]: GetHistogram (offset 361) */
   "iiiip\0"
   "glGetHistogram\0"
   "\0"
   /* _mesa_function_pool[8883]: Materialf (offset 169) */
   "iif\0"
   "glMaterialf\0"
   "\0"
   /* _mesa_function_pool[8900]: Materiali (offset 171) */
   "iii\0"
   "glMateriali\0"
   "\0"
   /* _mesa_function_pool[8917]: Indexsv (offset 51) */
   "p\0"
   "glIndexsv\0"
   "\0"
   /* _mesa_function_pool[8930]: MultiTexCoord4svARB (offset 407) */
   "ip\0"
   "glMultiTexCoord4svARB\0"
   "\0"
   /* _mesa_function_pool[8956]: LightModelfv (offset 164) */
   "ip\0"
   "glLightModelfv\0"
   "\0"
   /* _mesa_function_pool[8975]: Vertex4dv (offset 143) */
   "p\0"
   "glVertex4dv\0"
   "\0"
   /* _mesa_function_pool[8990]: EvalCoord1dv (offset 229) */
   "p\0"
   "glEvalCoord1dv\0"
   "\0"
   /* _mesa_function_pool[9008]: Translated (offset 303) */
   "ddd\0"
   "glTranslated\0"
   "\0"
   /* _mesa_function_pool[9026]: Uniform4fv (will be remapped) */
   "iip\0"
   "glUniform4fv\0"
   "\0"
   /* _mesa_function_pool[9044]: StencilMask (offset 209) */
   "i\0"
   "glStencilMask\0"
   "\0"
   /* _mesa_function_pool[9061]: GetLightiv (offset 265) */
   "iip\0"
   "glGetLightiv\0"
   "\0"
   /* _mesa_function_pool[9079]: IsList (offset 287) */
   "i\0"
   "glIsList\0"
   "\0"
   /* _mesa_function_pool[9091]: RenderMode (offset 196) */
   "i\0"
   "glRenderMode\0"
   "\0"
   /* _mesa_function_pool[9107]: MultiTexCoord1fARB (offset 378) */
   "if\0"
   "glMultiTexCoord1fARB\0"
   "\0"
   /* _mesa_function_pool[9132]: BindBuffer (will be remapped) */
   "ii\0"
   "glBindBuffer\0"
   "\0"
   /* _mesa_function_pool[9149]: CopyTexSubImage1D (offset 325) */
   "iiiiii\0"
   "glCopyTexSubImage1D\0"
   "\0"
   /* _mesa_function_pool[9177]: CullFace (offset 152) */
   "i\0"
   "glCullFace\0"
   "\0"
   /* _mesa_function_pool[9191]: BindTexture (offset 307) */
   "ii\0"
   "glBindTexture\0"
   "\0"
   /* _mesa_function_pool[9209]: MultiTexCoord4fARB (offset 402) */
   "iffff\0"
   "glMultiTexCoord4fARB\0"
   "\0"
   /* _mesa_function_pool[9237]: StencilFunc (offset 243) */
   "iii\0"
   "glStencilFunc\0"
   "\0"
   /* _mesa_function_pool[9256]: CopyPixels (offset 255) */
   "iiiii\0"
   "glCopyPixels\0"
   "\0"
   /* _mesa_function_pool[9276]: Rectsv (offset 93) */
   "pp\0"
   "glRectsv\0"
   "\0"
   /* _mesa_function_pool[9289]: GetPixelMapuiv (offset 272) */
   "ip\0"
   "glGetPixelMapuiv\0"
   "\0"
   /* _mesa_function_pool[9310]: CopyConvolutionFilter2D (offset 355) */
   "iiiiii\0"
   "glCopyConvolutionFilter2D\0"
   "\0"
   /* _mesa_function_pool[9344]: NormalPointer (offset 318) */
   "iip\0"
   "glNormalPointer\0"
   "\0"
   /* _mesa_function_pool[9365]: TexParameterfv (offset 179) */
   "iip\0"
   "glTexParameterfv\0"
   "\0"
   /* _mesa_function_pool[9387]: ClipPlane (offset 150) */
   "ip\0"
   "glClipPlane\0"
   "\0"
   /* _mesa_function_pool[9403]: Recti (offset 90) */
   "iiii\0"
   "glRecti\0"
   "\0"
   /* _mesa_function_pool[9417]: VertexAttribPointer (will be remapped) */
   "iiiiip\0"
   "glVertexAttribPointer\0"
   "\0"
   /* _mesa_function_pool[9447]: VertexAttrib1fv (will be remapped) */
   "ip\0"
   "glVertexAttrib1fv\0"
   "\0"
   /* _mesa_function_pool[9469]: Rectf (offset 88) */
   "ffff\0"
   "glRectf\0"
   "\0"
   /* _mesa_function_pool[9483]: Rectd (offset 86) */
   "dddd\0"
   "glRectd\0"
   "\0"
   /* _mesa_function_pool[9497]: Rects (offset 92) */
   "iiii\0"
   "glRects\0"
   "\0"
   /* _mesa_function_pool[9511]: IndexMask (offset 212) */
   "i\0"
   "glIndexMask\0"
   "\0"
   /* _mesa_function_pool[9526]: GetFloatv (offset 262) */
   "ip\0"
   "glGetFloatv\0"
   "\0"
   /* _mesa_function_pool[9542]: FramebufferTexture3DOES (will be remapped) */
   "iiiiii\0"
   "glFramebufferTexture3DOES\0"
   "\0"
   /* _mesa_function_pool[9576]: TexCoord4s (offset 124) */
   "iiii\0"
   "glTexCoord4s\0"
   "\0"
   /* _mesa_function_pool[9595]: TexCoord3sv (offset 117) */
   "p\0"
   "glTexCoord3sv\0"
   "\0"
   /* _mesa_function_pool[9612]: PopAttrib (offset 218) */
   "\0"
   "glPopAttrib\0"
   "\0"
   /* _mesa_function_pool[9626]: TexCoord4i (offset 122) */
   "iiii\0"
   "glTexCoord4i\0"
   "\0"
   /* _mesa_function_pool[9645]: InitNames (offset 197) */
   "\0"
   "glInitNames\0"
   "\0"
   /* _mesa_function_pool[9659]: Normal3sv (offset 61) */
   "p\0"
   "glNormal3sv\0"
   "\0"
   /* _mesa_function_pool[9674]: UnmapBufferOES (will be remapped) */
   "i\0"
   "glUnmapBufferOES\0"
   "\0"
   /* _mesa_function_pool[9694]: TexCoord4d (offset 118) */
   "dddd\0"
   "glTexCoord4d\0"
   "\0"
   /* _mesa_function_pool[9713]: TexCoord4f (offset 120) */
   "ffff\0"
   "glTexCoord4f\0"
   "\0"
   /* _mesa_function_pool[9732]: GetBooleanv (offset 258) */
   "ip\0"
   "glGetBooleanv\0"
   "\0"
   /* _mesa_function_pool[9750]: Hint (offset 158) */
   "ii\0"
   "glHint\0"
   "\0"
   /* _mesa_function_pool[9761]: Color4dv (offset 28) */
   "p\0"
   "glColor4dv\0"
   "\0"
   /* _mesa_function_pool[9775]: DisableVertexAttribArray (will be remapped) */
   "i\0"
   "glDisableVertexAttribArray\0"
   "\0"
   /* _mesa_function_pool[9805]: CopyColorSubTable (offset 347) */
   "iiiii\0"
   "glCopyColorSubTable\0"
   "\0"
   /* _mesa_function_pool[9832]: IsVertexArrayAPPLE (will be remapped) */
   "i\0"
   "glIsVertexArrayAPPLE\0"
   "\0"
   /* _mesa_function_pool[9856]: Vertex4iv (offset 147) */
   "p\0"
   "glVertex4iv\0"
   "\0"
   /* _mesa_function_pool[9871]: BufferSubData (will be remapped) */
   "iiip\0"
   "glBufferSubData\0"
   "\0"
   /* _mesa_function_pool[9893]: TexCoord4dv (offset 119) */
   "p\0"
   "glTexCoord4dv\0"
   "\0"
   /* _mesa_function_pool[9910]: Begin (offset 7) */
   "i\0"
   "glBegin\0"
   "\0"
   /* _mesa_function_pool[9921]: LightModeli (offset 165) */
   "ii\0"
   "glLightModeli\0"
   "\0"
   /* _mesa_function_pool[9939]: Rectfv (offset 89) */
   "pp\0"
   "glRectfv\0"
   "\0"
   /* _mesa_function_pool[9952]: UniformMatrix2fv (will be remapped) */
   "iiip\0"
   "glUniformMatrix2fv\0"
   "\0"
   /* _mesa_function_pool[9977]: LightModelf (offset 163) */
   "if\0"
   "glLightModelf\0"
   "\0"
   /* _mesa_function_pool[9995]: GetTexParameterfv (offset 282) */
   "iip\0"
   "glGetTexParameterfv\0"
   "\0"
   /* _mesa_function_pool[10020]: GetLightfv (offset 264) */
   "iip\0"
   "glGetLightfv\0"
   "\0"
   /* _mesa_function_pool[10038]: Disable (offset 214) */
   "i\0"
   "glDisable\0"
   "\0"
   /* _mesa_function_pool[10051]: MultiTexCoord2fvARB (offset 387) */
   "ip\0"
   "glMultiTexCoord2fvARB\0"
   "\0"
   /* _mesa_function_pool[10077]: SelectBuffer (offset 195) */
   "ip\0"
   "glSelectBuffer\0"
   "\0"
   /* _mesa_function_pool[10096]: ColorMask (offset 210) */
   "iiii\0"
   "glColorMask\0"
   "\0"
   /* _mesa_function_pool[10114]: RasterPos4iv (offset 83) */
   "p\0"
   "glRasterPos4iv\0"
   "\0"
   /* _mesa_function_pool[10132]: TexGenfv (offset 191) */
   "iip\0"
   "glTexGenfv\0"
   "\0"
   /* _mesa_function_pool[10148]: GetRenderbufferParameteriv (will be remapped) */
   "iip\0"
   "glGetRenderbufferParameteriv\0"
   "\0"
   /* _mesa_function_pool[10182]: Indexub (offset 315) */
   "i\0"
   "glIndexub\0"
   "\0"
   /* _mesa_function_pool[10195]: GenRenderbuffers (will be remapped) */
   "ip\0"
   "glGenRenderbuffers\0"
   "\0"
   /* _mesa_function_pool[10218]: UniformMatrix4fv (will be remapped) */
   "iiip\0"
   "glUniformMatrix4fv\0"
   "\0"
   /* _mesa_function_pool[10243]: GetMinmaxParameterfv (offset 365) */
   "iip\0"
   "glGetMinmaxParameterfv\0"
   "\0"
   /* _mesa_function_pool[10271]: Vertex3fv (offset 137) */
   "p\0"
   "glVertex3fv\0"
   "\0"
   /* _mesa_function_pool[10286]: Uniform4iv (will be remapped) */
   "iip\0"
   "glUniform4iv\0"
   "\0"
   ;

/* these functions need to be remapped */
static const struct gl_function_pool_remap MESA_remap_table_functions[] = {
   {  5490, GetBufferPointervOES_remap_index },
   {  2374, MapBufferOES_remap_index },
   {  9674, UnmapBufferOES_remap_index },
   {  1271, CompressedTexImage3DOES_remap_index },
   {  8160, CompressedTexSubImage3DOES_remap_index },
   {  9542, FramebufferTexture3DOES_remap_index },
   {  1413, GetProgramBinaryOES_remap_index },
   {  4388, ProgramBinaryOES_remap_index },
   {  7698, MultiDrawArraysEXT_remap_index },
   {  6275, MultiDrawElementsEXT_remap_index },
   {  8350, BindVertexArrayAPPLE_remap_index },
   {   848, DeleteVertexArraysAPPLE_remap_index },
   {  5224, GenVertexArraysAPPLE_remap_index },
   {  9832, IsVertexArrayAPPLE_remap_index },
   {  3905, EGLImageTargetRenderbufferStorageOES_remap_index },
   {  3678, EGLImageTargetTexture2DOES_remap_index },
   {  4413, CompressedTexImage2D_remap_index },
   {  1037, CompressedTexSubImage2D_remap_index },
   {  8294, SampleCoverage_remap_index },
   {  9132, BindBuffer_remap_index },
   {  3205, BufferData_remap_index },
   {  9871, BufferSubData_remap_index },
   {  7062, DeleteBuffers_remap_index },
   {  2566, GenBuffers_remap_index },
   {  5127, GetBufferParameteriv_remap_index },
   {  6117, IsBuffer_remap_index },
   {   540, AttachShader_remap_index },
   {  1387, BindAttribLocation_remap_index },
   {  6643, BlendEquationSeparate_remap_index },
   {  7868, CompileShader_remap_index },
   {  1843, CreateProgram_remap_index },
   {  6821, CreateShader_remap_index },
   {  8141, DeleteProgram_remap_index },
   {  7785, DeleteShader_remap_index },
   {  8228, DetachShader_remap_index },
   {  9775, DisableVertexAttribArray_remap_index },
   {  2668, EnableVertexAttribArray_remap_index },
   {  2061, GetActiveAttrib_remap_index },
   {  7034, GetActiveUniform_remap_index },
   {  5531, GetAttachedShaders_remap_index },
   {  4622, GetAttribLocation_remap_index },
   {   345, GetProgramInfoLog_remap_index },
   {   173, GetProgramiv_remap_index },
   {  3824, GetShaderInfoLog_remap_index },
   {  7010, GetShaderSource_remap_index },
   {  5442, GetShaderiv_remap_index },
   {  6030, GetUniformLocation_remap_index },
   {  1525, GetUniformfv_remap_index },
   {  1725, GetUniformiv_remap_index },
   {  5326, GetVertexAttribPointerv_remap_index },
   {   660, GetVertexAttribfv_remap_index },
   {  3279, GetVertexAttribiv_remap_index },
   {  4157, IsProgram_remap_index },
   {  3746, IsShader_remap_index },
   {  5616, LinkProgram_remap_index },
   {  3103, ShaderSource_remap_index },
   {  3075, StencilFuncSeparate_remap_index },
   {  1108, StencilMaskSeparate_remap_index },
   {  2287, StencilOpSeparate_remap_index },
   {  5633, Uniform1f_remap_index },
   {  7976, Uniform1fv_remap_index },
   {  5718, Uniform1i_remap_index },
   {  6554, Uniform1iv_remap_index },
   {  7825, Uniform2f_remap_index },
   {   371, Uniform2fv_remap_index },
   {  7943, Uniform2i_remap_index },
   {  8509, Uniform2iv_remap_index },
   {   892, Uniform3f_remap_index },
   {  1879, Uniform3fv_remap_index },
   {   811, Uniform3i_remap_index },
   {  4582, Uniform3iv_remap_index },
   {  5870, Uniform4f_remap_index },
   {  9026, Uniform4fv_remap_index },
   {  4369, Uniform4i_remap_index },
   { 10286, Uniform4iv_remap_index },
   {  9952, UniformMatrix2fv_remap_index },
   {   955, UniformMatrix3fv_remap_index },
   { 10218, UniformMatrix4fv_remap_index },
   {  5840, UseProgram_remap_index },
   {  1917, ValidateProgram_remap_index },
   {  6722, VertexAttrib1f_remap_index },
   {  9447, VertexAttrib1fv_remap_index },
   {  7803, VertexAttrib2f_remap_index },
   {  7151, VertexAttrib2fv_remap_index },
   {  1014, VertexAttrib3f_remap_index },
   {  4909, VertexAttrib3fv_remap_index },
   {  5757, VertexAttrib4f_remap_index },
   {   450, VertexAttrib4fv_remap_index },
   {  9417, VertexAttribPointer_remap_index },
   {  3049, BlendFuncSeparate_remap_index },
   {  2968, BindFramebuffer_remap_index },
   {  8527, BindRenderbuffer_remap_index },
   {  6320, CheckFramebufferStatus_remap_index },
   {  8247, ClearDepthf_remap_index },
   {  8597, DeleteFramebuffers_remap_index },
   {  3512, DeleteRenderbuffers_remap_index },
   {  1861, DepthRangef_remap_index },
   {  8667, FramebufferRenderbuffer_remap_index },
   {  6871, FramebufferTexture2D_remap_index },
   {  6586, GenFramebuffers_remap_index },
   { 10195, GenRenderbuffers_remap_index },
   {  7633, GenerateMipmap_remap_index },
   {  5266, GetFramebufferAttachmentParameteriv_remap_index },
   { 10148, GetRenderbufferParameteriv_remap_index },
   {  4472, GetShaderPrecisionFormat_remap_index },
   {  6624, IsFramebuffer_remap_index },
   {  3711, IsRenderbuffer_remap_index },
   {  3004, ReleaseShaderCompiler_remap_index },
   {   731, RenderbufferStorage_remap_index },
   {  3304, ShaderBinary_remap_index },
   {    -1, -1 }
};

/* these functions are in the ABI, but have alternative names */
static const struct gl_function_remap MESA_alt_functions[] = {
   {    -1, -1 }
};

#endif /* need_MESA_remap_table */

#if defined(need_GL_APPLE_vertex_array_object)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_APPLE_vertex_array_object_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_EXT_multi_draw_arrays)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_EXT_multi_draw_arrays_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_EGL_image)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_EGL_image_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_get_program_binary)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_get_program_binary_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_mapbuffer)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_mapbuffer_functions[] = {
   {    -1, -1 }
};
#endif

