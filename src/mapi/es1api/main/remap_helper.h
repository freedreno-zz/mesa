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
   /* _mesa_function_pool[173]: TexCoord1iv (offset 99) */
   "p\0"
   "glTexCoord1iv\0"
   "\0"
   /* _mesa_function_pool[190]: TexCoord4sv (offset 125) */
   "p\0"
   "glTexCoord4sv\0"
   "\0"
   /* _mesa_function_pool[207]: RasterPos4s (offset 84) */
   "iiii\0"
   "glRasterPos4s\0"
   "\0"
   /* _mesa_function_pool[227]: TexCoord1f (offset 96) */
   "f\0"
   "glTexCoord1f\0"
   "\0"
   /* _mesa_function_pool[243]: PolygonOffsetx (will be remapped) */
   "ii\0"
   "glPolygonOffsetx\0"
   "glPolygonOffsetxOES\0"
   "\0"
   /* _mesa_function_pool[284]: TexCoord1i (offset 98) */
   "i\0"
   "glTexCoord1i\0"
   "\0"
   /* _mesa_function_pool[300]: Histogram (offset 367) */
   "iiii\0"
   "glHistogram\0"
   "\0"
   /* _mesa_function_pool[318]: TexCoord1s (offset 100) */
   "i\0"
   "glTexCoord1s\0"
   "\0"
   /* _mesa_function_pool[334]: GetMapfv (offset 267) */
   "iip\0"
   "glGetMapfv\0"
   "\0"
   /* _mesa_function_pool[350]: EvalCoord1f (offset 230) */
   "f\0"
   "glEvalCoord1f\0"
   "\0"
   /* _mesa_function_pool[367]: ConvolutionFilter2D (offset 349) */
   "iiiiiip\0"
   "glConvolutionFilter2D\0"
   "\0"
   /* _mesa_function_pool[398]: PolygonStipple (offset 175) */
   "p\0"
   "glPolygonStipple\0"
   "\0"
   /* _mesa_function_pool[418]: GetPixelMapfv (offset 271) */
   "ip\0"
   "glGetPixelMapfv\0"
   "\0"
   /* _mesa_function_pool[438]: Color3uiv (offset 22) */
   "p\0"
   "glColor3uiv\0"
   "\0"
   /* _mesa_function_pool[453]: IsEnabled (offset 286) */
   "i\0"
   "glIsEnabled\0"
   "\0"
   /* _mesa_function_pool[468]: EvalCoord2fv (offset 235) */
   "p\0"
   "glEvalCoord2fv\0"
   "\0"
   /* _mesa_function_pool[486]: GenerateMipmapOES (will be remapped) */
   "i\0"
   "glGenerateMipmapOES\0"
   "\0"
   /* _mesa_function_pool[509]: GetMapiv (offset 268) */
   "iip\0"
   "glGetMapiv\0"
   "\0"
   /* _mesa_function_pool[525]: Indexubv (offset 316) */
   "p\0"
   "glIndexubv\0"
   "\0"
   /* _mesa_function_pool[539]: TexImage3D (offset 371) */
   "iiiiiiiiip\0"
   "glTexImage3D\0"
   "\0"
   /* _mesa_function_pool[564]: EdgeFlagPointer (offset 312) */
   "ip\0"
   "glEdgeFlagPointer\0"
   "\0"
   /* _mesa_function_pool[586]: Color3ubv (offset 20) */
   "p\0"
   "glColor3ubv\0"
   "\0"
   /* _mesa_function_pool[601]: Vertex3dv (offset 135) */
   "p\0"
   "glVertex3dv\0"
   "\0"
   /* _mesa_function_pool[616]: Disable (offset 214) */
   "i\0"
   "glDisable\0"
   "\0"
   /* _mesa_function_pool[629]: LightModeliv (offset 166) */
   "ip\0"
   "glLightModeliv\0"
   "\0"
   /* _mesa_function_pool[648]: GetClipPlanex (will be remapped) */
   "ip\0"
   "glGetClipPlanex\0"
   "glGetClipPlanexOES\0"
   "\0"
   /* _mesa_function_pool[687]: Vertex3iv (offset 139) */
   "p\0"
   "glVertex3iv\0"
   "\0"
   /* _mesa_function_pool[702]: GetClipPlanef (will be remapped) */
   "ip\0"
   "glGetClipPlanef\0"
   "glGetClipPlanefOES\0"
   "\0"
   /* _mesa_function_pool[741]: BlendColor (offset 336) */
   "ffff\0"
   "glBlendColor\0"
   "\0"
   /* _mesa_function_pool[760]: MultiTexCoord3fARB (offset 394) */
   "ifff\0"
   "glMultiTexCoord3fARB\0"
   "\0"
   /* _mesa_function_pool[787]: DeleteVertexArraysAPPLE (will be remapped) */
   "ip\0"
   "glDeleteVertexArraysAPPLE\0"
   "\0"
   /* _mesa_function_pool[817]: Scalef (offset 302) */
   "fff\0"
   "glScalef\0"
   "\0"
   /* _mesa_function_pool[831]: Normal3iv (offset 59) */
   "p\0"
   "glNormal3iv\0"
   "\0"
   /* _mesa_function_pool[846]: PointSizex (will be remapped) */
   "i\0"
   "glPointSizex\0"
   "glPointSizexOES\0"
   "\0"
   /* _mesa_function_pool[878]: DrawTexiOES (will be remapped) */
   "iiiii\0"
   "glDrawTexiOES\0"
   "\0"
   /* _mesa_function_pool[899]: PassThrough (offset 199) */
   "f\0"
   "glPassThrough\0"
   "\0"
   /* _mesa_function_pool[916]: Viewport (offset 305) */
   "iiii\0"
   "glViewport\0"
   "\0"
   /* _mesa_function_pool[933]: DepthRange (offset 288) */
   "dd\0"
   "glDepthRange\0"
   "\0"
   /* _mesa_function_pool[950]: ResetHistogram (offset 369) */
   "i\0"
   "glResetHistogram\0"
   "\0"
   /* _mesa_function_pool[970]: CompressedTexSubImage2D (will be remapped) */
   "iiiiiiiip\0"
   "glCompressedTexSubImage2D\0"
   "\0"
   /* _mesa_function_pool[1007]: MultiTexCoord2dvARB (offset 385) */
   "ip\0"
   "glMultiTexCoord2dvARB\0"
   "\0"
   /* _mesa_function_pool[1033]: GetMaterialxv (will be remapped) */
   "iip\0"
   "glGetMaterialxv\0"
   "glGetMaterialxvOES\0"
   "\0"
   /* _mesa_function_pool[1073]: TexCoord2sv (offset 109) */
   "p\0"
   "glTexCoord2sv\0"
   "\0"
   /* _mesa_function_pool[1090]: TexCoord2dv (offset 103) */
   "p\0"
   "glTexCoord2dv\0"
   "\0"
   /* _mesa_function_pool[1107]: TexCoord1d (offset 94) */
   "d\0"
   "glTexCoord1d\0"
   "\0"
   /* _mesa_function_pool[1123]: Color3sv (offset 18) */
   "p\0"
   "glColor3sv\0"
   "\0"
   /* _mesa_function_pool[1137]: GetLightxv (will be remapped) */
   "iip\0"
   "glGetLightxv\0"
   "glGetLightxvOES\0"
   "\0"
   /* _mesa_function_pool[1171]: GetConvolutionParameteriv (offset 358) */
   "iip\0"
   "glGetConvolutionParameteriv\0"
   "\0"
   /* _mesa_function_pool[1204]: AlphaFunc (offset 240) */
   "if\0"
   "glAlphaFunc\0"
   "\0"
   /* _mesa_function_pool[1220]: DrawTexsOES (will be remapped) */
   "iiiii\0"
   "glDrawTexsOES\0"
   "\0"
   /* _mesa_function_pool[1241]: MultiTexCoord1fvARB (offset 379) */
   "ip\0"
   "glMultiTexCoord1fvARB\0"
   "\0"
   /* _mesa_function_pool[1267]: TexCoord3iv (offset 115) */
   "p\0"
   "glTexCoord3iv\0"
   "\0"
   /* _mesa_function_pool[1284]: Color3fv (offset 14) */
   "p\0"
   "glColor3fv\0"
   "\0"
   /* _mesa_function_pool[1298]: Translated (offset 303) */
   "ddd\0"
   "glTranslated\0"
   "\0"
   /* _mesa_function_pool[1316]: PointSize (offset 173) */
   "f\0"
   "glPointSize\0"
   "\0"
   /* _mesa_function_pool[1331]: PopName (offset 200) */
   "\0"
   "glPopName\0"
   "\0"
   /* _mesa_function_pool[1343]: Vertex4sv (offset 149) */
   "p\0"
   "glVertex4sv\0"
   "\0"
   /* _mesa_function_pool[1358]: GetTexEnvfv (offset 276) */
   "iip\0"
   "glGetTexEnvfv\0"
   "\0"
   /* _mesa_function_pool[1377]: ColorTableParameteriv (offset 341) */
   "iip\0"
   "glColorTableParameteriv\0"
   "\0"
   /* _mesa_function_pool[1406]: LineStipple (offset 167) */
   "ii\0"
   "glLineStipple\0"
   "\0"
   /* _mesa_function_pool[1424]: TexEnvi (offset 186) */
   "iii\0"
   "glTexEnvi\0"
   "\0"
   /* _mesa_function_pool[1439]: GetClipPlane (offset 259) */
   "ip\0"
   "glGetClipPlane\0"
   "\0"
   /* _mesa_function_pool[1458]: Scalex (will be remapped) */
   "iii\0"
   "glScalex\0"
   "glScalexOES\0"
   "\0"
   /* _mesa_function_pool[1484]: Scaled (offset 301) */
   "ddd\0"
   "glScaled\0"
   "\0"
   /* _mesa_function_pool[1498]: CallLists (offset 3) */
   "iip\0"
   "glCallLists\0"
   "\0"
   /* _mesa_function_pool[1515]: Vertex2dv (offset 127) */
   "p\0"
   "glVertex2dv\0"
   "\0"
   /* _mesa_function_pool[1530]: EdgeFlag (offset 41) */
   "i\0"
   "glEdgeFlag\0"
   "\0"
   /* _mesa_function_pool[1544]: TexCoord2iv (offset 107) */
   "p\0"
   "glTexCoord2iv\0"
   "\0"
   /* _mesa_function_pool[1561]: BlendEquationSeparateOES (will be remapped) */
   "ii\0"
   "glBlendEquationSeparateOES\0"
   "\0"
   /* _mesa_function_pool[1592]: TexParameterx (will be remapped) */
   "iii\0"
   "glTexParameterx\0"
   "glTexParameterxOES\0"
   "\0"
   /* _mesa_function_pool[1632]: ReadPixels (offset 256) */
   "iiiiiip\0"
   "glReadPixels\0"
   "\0"
   /* _mesa_function_pool[1654]: TexParameteri (offset 180) */
   "iii\0"
   "glTexParameteri\0"
   "\0"
   /* _mesa_function_pool[1675]: Color4iv (offset 32) */
   "p\0"
   "glColor4iv\0"
   "\0"
   /* _mesa_function_pool[1689]: TexParameterf (offset 178) */
   "iif\0"
   "glTexParameterf\0"
   "\0"
   /* _mesa_function_pool[1710]: EdgeFlagv (offset 42) */
   "p\0"
   "glEdgeFlagv\0"
   "\0"
   /* _mesa_function_pool[1725]: MultiTexCoord3dARB (offset 392) */
   "iddd\0"
   "glMultiTexCoord3dARB\0"
   "\0"
   /* _mesa_function_pool[1752]: MultiTexCoord2iARB (offset 388) */
   "iii\0"
   "glMultiTexCoord2iARB\0"
   "\0"
   /* _mesa_function_pool[1778]: DrawPixels (offset 257) */
   "iiiip\0"
   "glDrawPixels\0"
   "\0"
   /* _mesa_function_pool[1798]: DepthRangex (will be remapped) */
   "ii\0"
   "glDepthRangex\0"
   "glDepthRangexOES\0"
   "\0"
   /* _mesa_function_pool[1833]: GenLists (offset 5) */
   "i\0"
   "glGenLists\0"
   "\0"
   /* _mesa_function_pool[1847]: DepthRangef (will be remapped) */
   "ff\0"
   "glDepthRangef\0"
   "glDepthRangefOES\0"
   "\0"
   /* _mesa_function_pool[1882]: MapGrid2d (offset 226) */
   "iddidd\0"
   "glMapGrid2d\0"
   "\0"
   /* _mesa_function_pool[1902]: MapGrid2f (offset 227) */
   "iffiff\0"
   "glMapGrid2f\0"
   "\0"
   /* _mesa_function_pool[1922]: Fogx (will be remapped) */
   "ii\0"
   "glFogx\0"
   "glFogxOES\0"
   "\0"
   /* _mesa_function_pool[1943]: GetTexGenivOES (offset 280) */
   "iip\0"
   "glGetTexGenivOES\0"
   "glGetTexGeniv\0"
   "\0"
   /* _mesa_function_pool[1979]: Scissor (offset 176) */
   "iiii\0"
   "glScissor\0"
   "\0"
   /* _mesa_function_pool[1995]: Fogf (offset 153) */
   "if\0"
   "glFogf\0"
   "\0"
   /* _mesa_function_pool[2006]: TexSubImage1D (offset 332) */
   "iiiiiip\0"
   "glTexSubImage1D\0"
   "\0"
   /* _mesa_function_pool[2031]: Color4usv (offset 40) */
   "p\0"
   "glColor4usv\0"
   "\0"
   /* _mesa_function_pool[2046]: Fogi (offset 155) */
   "ii\0"
   "glFogi\0"
   "\0"
   /* _mesa_function_pool[2057]: MultiTexCoord3sARB (offset 398) */
   "iiii\0"
   "glMultiTexCoord3sARB\0"
   "\0"
   /* _mesa_function_pool[2084]: RasterPos3iv (offset 75) */
   "p\0"
   "glRasterPos3iv\0"
   "\0"
   /* _mesa_function_pool[2102]: FramebufferRenderbufferOES (will be remapped) */
   "iiii\0"
   "glFramebufferRenderbufferOES\0"
   "\0"
   /* _mesa_function_pool[2137]: TexCoord2i (offset 106) */
   "ii\0"
   "glTexCoord2i\0"
   "\0"
   /* _mesa_function_pool[2154]: DepthFunc (offset 245) */
   "i\0"
   "glDepthFunc\0"
   "\0"
   /* _mesa_function_pool[2169]: Color4ui (offset 37) */
   "iiii\0"
   "glColor4ui\0"
   "\0"
   /* _mesa_function_pool[2186]: RasterPos3s (offset 76) */
   "iii\0"
   "glRasterPos3s\0"
   "\0"
   /* _mesa_function_pool[2205]: Color3usv (offset 24) */
   "p\0"
   "glColor3usv\0"
   "\0"
   /* _mesa_function_pool[2220]: TexCoord2f (offset 104) */
   "ff\0"
   "glTexCoord2f\0"
   "\0"
   /* _mesa_function_pool[2237]: TexCoord2d (offset 102) */
   "dd\0"
   "glTexCoord2d\0"
   "\0"
   /* _mesa_function_pool[2254]: RasterPos3d (offset 70) */
   "ddd\0"
   "glRasterPos3d\0"
   "\0"
   /* _mesa_function_pool[2273]: RasterPos3f (offset 72) */
   "fff\0"
   "glRasterPos3f\0"
   "\0"
   /* _mesa_function_pool[2292]: AreTexturesResident (offset 322) */
   "ipp\0"
   "glAreTexturesResident\0"
   "\0"
   /* _mesa_function_pool[2319]: TexCoord2s (offset 108) */
   "ii\0"
   "glTexCoord2s\0"
   "\0"
   /* _mesa_function_pool[2336]: RasterPos3i (offset 74) */
   "iii\0"
   "glRasterPos3i\0"
   "\0"
   /* _mesa_function_pool[2355]: Color4us (offset 39) */
   "iiii\0"
   "glColor4us\0"
   "\0"
   /* _mesa_function_pool[2372]: GetTexParameteriv (offset 283) */
   "iip\0"
   "glGetTexParameteriv\0"
   "\0"
   /* _mesa_function_pool[2397]: MapBufferOES (will be remapped) */
   "ii\0"
   "glMapBufferOES\0"
   "\0"
   /* _mesa_function_pool[2416]: DrawTexfOES (will be remapped) */
   "fffff\0"
   "glDrawTexfOES\0"
   "\0"
   /* _mesa_function_pool[2437]: MultiTexCoord2fARB (offset 386) */
   "iff\0"
   "glMultiTexCoord2fARB\0"
   "\0"
   /* _mesa_function_pool[2463]: ColorTable (offset 339) */
   "iiiiip\0"
   "glColorTable\0"
   "\0"
   /* _mesa_function_pool[2484]: IndexPointer (offset 314) */
   "iip\0"
   "glIndexPointer\0"
   "\0"
   /* _mesa_function_pool[2504]: Accum (offset 213) */
   "if\0"
   "glAccum\0"
   "\0"
   /* _mesa_function_pool[2516]: GetTexImage (offset 281) */
   "iiiip\0"
   "glGetTexImage\0"
   "\0"
   /* _mesa_function_pool[2537]: LoadName (offset 198) */
   "i\0"
   "glLoadName\0"
   "\0"
   /* _mesa_function_pool[2551]: Finish (offset 216) */
   "\0"
   "glFinish\0"
   "\0"
   /* _mesa_function_pool[2562]: ClearStencil (offset 207) */
   "i\0"
   "glClearStencil\0"
   "\0"
   /* _mesa_function_pool[2580]: Color4x (will be remapped) */
   "iiii\0"
   "glColor4x\0"
   "glColor4xOES\0"
   "\0"
   /* _mesa_function_pool[2609]: ConvolutionParameteriv (offset 353) */
   "iip\0"
   "glConvolutionParameteriv\0"
   "\0"
   /* _mesa_function_pool[2639]: GenBuffers (will be remapped) */
   "ip\0"
   "glGenBuffers\0"
   "\0"
   /* _mesa_function_pool[2656]: InterleavedArrays (offset 317) */
   "iip\0"
   "glInterleavedArrays\0"
   "\0"
   /* _mesa_function_pool[2681]: RasterPos2fv (offset 65) */
   "p\0"
   "glRasterPos2fv\0"
   "\0"
   /* _mesa_function_pool[2699]: TexCoord1fv (offset 97) */
   "p\0"
   "glTexCoord1fv\0"
   "\0"
   /* _mesa_function_pool[2716]: Vertex2d (offset 126) */
   "dd\0"
   "glVertex2d\0"
   "\0"
   /* _mesa_function_pool[2731]: PixelTransferf (offset 247) */
   "if\0"
   "glPixelTransferf\0"
   "\0"
   /* _mesa_function_pool[2752]: Color4i (offset 31) */
   "iiii\0"
   "glColor4i\0"
   "\0"
   /* _mesa_function_pool[2768]: Color4f (offset 29) */
   "ffff\0"
   "glColor4f\0"
   "\0"
   /* _mesa_function_pool[2784]: RasterPos4fv (offset 81) */
   "p\0"
   "glRasterPos4fv\0"
   "\0"
   /* _mesa_function_pool[2802]: Color4d (offset 27) */
   "dddd\0"
   "glColor4d\0"
   "\0"
   /* _mesa_function_pool[2818]: ClearIndex (offset 205) */
   "f\0"
   "glClearIndex\0"
   "\0"
   /* _mesa_function_pool[2834]: Color4b (offset 25) */
   "iiii\0"
   "glColor4b\0"
   "\0"
   /* _mesa_function_pool[2850]: LoadMatrixd (offset 292) */
   "p\0"
   "glLoadMatrixd\0"
   "\0"
   /* _mesa_function_pool[2867]: PushMatrix (offset 298) */
   "\0"
   "glPushMatrix\0"
   "\0"
   /* _mesa_function_pool[2882]: ConvolutionParameterfv (offset 351) */
   "iip\0"
   "glConvolutionParameterfv\0"
   "\0"
   /* _mesa_function_pool[2912]: BlendFuncSeparateOES (will be remapped) */
   "iiii\0"
   "glBlendFuncSeparateOES\0"
   "\0"
   /* _mesa_function_pool[2941]: GetTexGendv (offset 278) */
   "iip\0"
   "glGetTexGendv\0"
   "\0"
   /* _mesa_function_pool[2960]: EndList (offset 1) */
   "\0"
   "glEndList\0"
   "\0"
   /* _mesa_function_pool[2972]: Fogiv (offset 156) */
   "ip\0"
   "glFogiv\0"
   "\0"
   /* _mesa_function_pool[2984]: EvalCoord1fv (offset 231) */
   "p\0"
   "glEvalCoord1fv\0"
   "\0"
   /* _mesa_function_pool[3002]: DrawRangeElements (offset 338) */
   "iiiiip\0"
   "glDrawRangeElements\0"
   "\0"
   /* _mesa_function_pool[3030]: EvalMesh2 (offset 238) */
   "iiiii\0"
   "glEvalMesh2\0"
   "\0"
   /* _mesa_function_pool[3049]: GetTexGenxvOES (will be remapped) */
   "iip\0"
   "glGetTexGenxvOES\0"
   "\0"
   /* _mesa_function_pool[3071]: Vertex4fv (offset 145) */
   "p\0"
   "glVertex4fv\0"
   "\0"
   /* _mesa_function_pool[3086]: VertexPointer (offset 321) */
   "iiip\0"
   "glVertexPointer\0"
   "\0"
   /* _mesa_function_pool[3108]: GetMinmax (offset 364) */
   "iiiip\0"
   "glGetMinmax\0"
   "\0"
   /* _mesa_function_pool[3127]: Normal3fv (offset 57) */
   "p\0"
   "glNormal3fv\0"
   "\0"
   /* _mesa_function_pool[3142]: Color3us (offset 23) */
   "iii\0"
   "glColor3us\0"
   "\0"
   /* _mesa_function_pool[3158]: End (offset 43) */
   "\0"
   "glEnd\0"
   "\0"
   /* _mesa_function_pool[3166]: MultiTexCoord3fvARB (offset 395) */
   "ip\0"
   "glMultiTexCoord3fvARB\0"
   "\0"
   /* _mesa_function_pool[3192]: Color3ub (offset 19) */
   "iii\0"
   "glColor3ub\0"
   "\0"
   /* _mesa_function_pool[3208]: BufferData (will be remapped) */
   "iipi\0"
   "glBufferData\0"
   "\0"
   /* _mesa_function_pool[3227]: BlendEquationOES (offset 337) */
   "i\0"
   "glBlendEquationOES\0"
   "glBlendEquation\0"
   "\0"
   /* _mesa_function_pool[3265]: Color3ui (offset 21) */
   "iii\0"
   "glColor3ui\0"
   "\0"
   /* _mesa_function_pool[3281]: TexSubImage2D (offset 333) */
   "iiiiiiiip\0"
   "glTexSubImage2D\0"
   "\0"
   /* _mesa_function_pool[3308]: Enable (offset 215) */
   "i\0"
   "glEnable\0"
   "\0"
   /* _mesa_function_pool[3320]: MultiTexCoord4sARB (offset 406) */
   "iiiii\0"
   "glMultiTexCoord4sARB\0"
   "\0"
   /* _mesa_function_pool[3348]: Normal3x (will be remapped) */
   "iii\0"
   "glNormal3x\0"
   "glNormal3xOES\0"
   "\0"
   /* _mesa_function_pool[3378]: LineWidthx (will be remapped) */
   "i\0"
   "glLineWidthx\0"
   "glLineWidthxOES\0"
   "\0"
   /* _mesa_function_pool[3410]: GetError (offset 261) */
   "\0"
   "glGetError\0"
   "\0"
   /* _mesa_function_pool[3423]: TexCoord3dv (offset 111) */
   "p\0"
   "glTexCoord3dv\0"
   "\0"
   /* _mesa_function_pool[3440]: Indexdv (offset 45) */
   "p\0"
   "glIndexdv\0"
   "\0"
   /* _mesa_function_pool[3453]: Normal3s (offset 60) */
   "iii\0"
   "glNormal3s\0"
   "\0"
   /* _mesa_function_pool[3469]: PushName (offset 201) */
   "i\0"
   "glPushName\0"
   "\0"
   /* _mesa_function_pool[3483]: Materialxv (will be remapped) */
   "iip\0"
   "glMaterialxv\0"
   "glMaterialxvOES\0"
   "\0"
   /* _mesa_function_pool[3517]: Normal3i (offset 58) */
   "iii\0"
   "glNormal3i\0"
   "\0"
   /* _mesa_function_pool[3533]: Normal3b (offset 52) */
   "iii\0"
   "glNormal3b\0"
   "\0"
   /* _mesa_function_pool[3549]: Normal3d (offset 54) */
   "ddd\0"
   "glNormal3d\0"
   "\0"
   /* _mesa_function_pool[3565]: Normal3f (offset 56) */
   "fff\0"
   "glNormal3f\0"
   "\0"
   /* _mesa_function_pool[3581]: MultiTexCoord1svARB (offset 383) */
   "ip\0"
   "glMultiTexCoord1svARB\0"
   "\0"
   /* _mesa_function_pool[3607]: Indexi (offset 48) */
   "i\0"
   "glIndexi\0"
   "\0"
   /* _mesa_function_pool[3619]: EGLImageTargetTexture2DOES (will be remapped) */
   "ip\0"
   "glEGLImageTargetTexture2DOES\0"
   "\0"
   /* _mesa_function_pool[3652]: DepthMask (offset 211) */
   "i\0"
   "glDepthMask\0"
   "\0"
   /* _mesa_function_pool[3667]: Indexf (offset 46) */
   "f\0"
   "glIndexf\0"
   "\0"
   /* _mesa_function_pool[3679]: Indexd (offset 44) */
   "d\0"
   "glIndexd\0"
   "\0"
   /* _mesa_function_pool[3691]: GetMaterialiv (offset 270) */
   "iip\0"
   "glGetMaterialiv\0"
   "\0"
   /* _mesa_function_pool[3712]: StencilOp (offset 244) */
   "iii\0"
   "glStencilOp\0"
   "\0"
   /* _mesa_function_pool[3729]: MultiTexCoord3svARB (offset 399) */
   "ip\0"
   "glMultiTexCoord3svARB\0"
   "\0"
   /* _mesa_function_pool[3755]: TexEnvfv (offset 185) */
   "iip\0"
   "glTexEnvfv\0"
   "\0"
   /* _mesa_function_pool[3771]: MultiTexCoord4iARB (offset 404) */
   "iiiii\0"
   "glMultiTexCoord4iARB\0"
   "\0"
   /* _mesa_function_pool[3799]: Indexs (offset 50) */
   "i\0"
   "glIndexs\0"
   "\0"
   /* _mesa_function_pool[3811]: BindFramebufferOES (will be remapped) */
   "ii\0"
   "glBindFramebufferOES\0"
   "\0"
   /* _mesa_function_pool[3836]: Fogxv (will be remapped) */
   "ip\0"
   "glFogxv\0"
   "glFogxvOES\0"
   "\0"
   /* _mesa_function_pool[3859]: EGLImageTargetRenderbufferStorageOES (will be remapped) */
   "ip\0"
   "glEGLImageTargetRenderbufferStorageOES\0"
   "\0"
   /* _mesa_function_pool[3902]: Vertex2i (offset 130) */
   "ii\0"
   "glVertex2i\0"
   "\0"
   /* _mesa_function_pool[3917]: LoadMatrixf (offset 291) */
   "p\0"
   "glLoadMatrixf\0"
   "\0"
   /* _mesa_function_pool[3934]: Vertex2f (offset 128) */
   "ff\0"
   "glVertex2f\0"
   "\0"
   /* _mesa_function_pool[3949]: Color4bv (offset 26) */
   "p\0"
   "glColor4bv\0"
   "\0"
   /* _mesa_function_pool[3963]: DrawTexfvOES (will be remapped) */
   "p\0"
   "glDrawTexfvOES\0"
   "\0"
   /* _mesa_function_pool[3981]: LoadMatrixx (will be remapped) */
   "p\0"
   "glLoadMatrixx\0"
   "glLoadMatrixxOES\0"
   "\0"
   /* _mesa_function_pool[4015]: DeleteLists (offset 4) */
   "ii\0"
   "glDeleteLists\0"
   "\0"
   /* _mesa_function_pool[4033]: LogicOp (offset 242) */
   "i\0"
   "glLogicOp\0"
   "\0"
   /* _mesa_function_pool[4046]: Vertex2s (offset 132) */
   "ii\0"
   "glVertex2s\0"
   "\0"
   /* _mesa_function_pool[4061]: TexCoord4fv (offset 121) */
   "p\0"
   "glTexCoord4fv\0"
   "\0"
   /* _mesa_function_pool[4078]: ActiveTexture (offset 374) */
   "i\0"
   "glActiveTexture\0"
   "glActiveTextureARB\0"
   "\0"
   /* _mesa_function_pool[4116]: MultiTexCoord3iARB (offset 396) */
   "iiii\0"
   "glMultiTexCoord3iARB\0"
   "\0"
   /* _mesa_function_pool[4143]: GenRenderbuffersOES (will be remapped) */
   "ip\0"
   "glGenRenderbuffersOES\0"
   "\0"
   /* _mesa_function_pool[4169]: DrawTexxOES (will be remapped) */
   "iiiii\0"
   "glDrawTexxOES\0"
   "\0"
   /* _mesa_function_pool[4190]: GenTextures (offset 328) */
   "ip\0"
   "glGenTextures\0"
   "\0"
   /* _mesa_function_pool[4208]: Normal3bv (offset 53) */
   "p\0"
   "glNormal3bv\0"
   "\0"
   /* _mesa_function_pool[4223]: DrawTexxvOES (will be remapped) */
   "p\0"
   "glDrawTexxvOES\0"
   "\0"
   /* _mesa_function_pool[4241]: TexCoord4iv (offset 123) */
   "p\0"
   "glTexCoord4iv\0"
   "\0"
   /* _mesa_function_pool[4258]: Color4ubv (offset 36) */
   "p\0"
   "glColor4ubv\0"
   "\0"
   /* _mesa_function_pool[4273]: DrawBuffer (offset 202) */
   "i\0"
   "glDrawBuffer\0"
   "\0"
   /* _mesa_function_pool[4289]: TexCoord2fv (offset 105) */
   "p\0"
   "glTexCoord2fv\0"
   "\0"
   /* _mesa_function_pool[4306]: TexCoord1sv (offset 101) */
   "p\0"
   "glTexCoord1sv\0"
   "\0"
   /* _mesa_function_pool[4323]: PixelMapfv (offset 251) */
   "iip\0"
   "glPixelMapfv\0"
   "\0"
   /* _mesa_function_pool[4341]: GenFramebuffersOES (will be remapped) */
   "ip\0"
   "glGenFramebuffersOES\0"
   "\0"
   /* _mesa_function_pool[4366]: MultiTexCoord1dARB (offset 376) */
   "id\0"
   "glMultiTexCoord1dARB\0"
   "\0"
   /* _mesa_function_pool[4391]: Orthof (will be remapped) */
   "ffffff\0"
   "glOrthof\0"
   "glOrthofOES\0"
   "\0"
   /* _mesa_function_pool[4420]: CompressedTexImage2D (will be remapped) */
   "iiiiiiip\0"
   "glCompressedTexImage2D\0"
   "\0"
   /* _mesa_function_pool[4453]: MultiTexCoord3dvARB (offset 393) */
   "ip\0"
   "glMultiTexCoord3dvARB\0"
   "\0"
   /* _mesa_function_pool[4479]: Flush (offset 217) */
   "\0"
   "glFlush\0"
   "\0"
   /* _mesa_function_pool[4489]: Color4uiv (offset 38) */
   "p\0"
   "glColor4uiv\0"
   "\0"
   /* _mesa_function_pool[4504]: Orthox (will be remapped) */
   "iiiiii\0"
   "glOrthox\0"
   "glOrthoxOES\0"
   "\0"
   /* _mesa_function_pool[4533]: RasterPos3sv (offset 77) */
   "p\0"
   "glRasterPos3sv\0"
   "\0"
   /* _mesa_function_pool[4551]: PushAttrib (offset 219) */
   "i\0"
   "glPushAttrib\0"
   "\0"
   /* _mesa_function_pool[4567]: RasterPos2i (offset 66) */
   "ii\0"
   "glRasterPos2i\0"
   "\0"
   /* _mesa_function_pool[4585]: TexParameteriv (offset 181) */
   "iip\0"
   "glTexParameteriv\0"
   "\0"
   /* _mesa_function_pool[4607]: RasterPos2f (offset 64) */
   "ff\0"
   "glRasterPos2f\0"
   "\0"
   /* _mesa_function_pool[4625]: RasterPos2d (offset 62) */
   "dd\0"
   "glRasterPos2d\0"
   "\0"
   /* _mesa_function_pool[4643]: RasterPos3fv (offset 73) */
   "p\0"
   "glRasterPos3fv\0"
   "\0"
   /* _mesa_function_pool[4661]: CopyTexSubImage3D (offset 373) */
   "iiiiiiiii\0"
   "glCopyTexSubImage3D\0"
   "\0"
   /* _mesa_function_pool[4692]: Color4ub (offset 35) */
   "iiii\0"
   "glColor4ub\0"
   "\0"
   /* _mesa_function_pool[4709]: RasterPos2s (offset 68) */
   "ii\0"
   "glRasterPos2s\0"
   "\0"
   /* _mesa_function_pool[4727]: GetColorTable (offset 343) */
   "iiip\0"
   "glGetColorTable\0"
   "\0"
   /* _mesa_function_pool[4749]: SelectBuffer (offset 195) */
   "ip\0"
   "glSelectBuffer\0"
   "\0"
   /* _mesa_function_pool[4768]: Indexiv (offset 49) */
   "p\0"
   "glIndexiv\0"
   "\0"
   /* _mesa_function_pool[4781]: TexCoord3i (offset 114) */
   "iii\0"
   "glTexCoord3i\0"
   "\0"
   /* _mesa_function_pool[4799]: CopyColorTable (offset 342) */
   "iiiii\0"
   "glCopyColorTable\0"
   "\0"
   /* _mesa_function_pool[4823]: PointParameterfv (will be remapped) */
   "ip\0"
   "glPointParameterfv\0"
   "\0"
   /* _mesa_function_pool[4846]: GetHistogramParameterfv (offset 362) */
   "iip\0"
   "glGetHistogramParameterfv\0"
   "\0"
   /* _mesa_function_pool[4877]: Frustum (offset 289) */
   "dddddd\0"
   "glFrustum\0"
   "\0"
   /* _mesa_function_pool[4895]: GetString (offset 275) */
   "i\0"
   "glGetString\0"
   "\0"
   /* _mesa_function_pool[4910]: TexEnvf (offset 184) */
   "iif\0"
   "glTexEnvf\0"
   "\0"
   /* _mesa_function_pool[4925]: TexCoord3d (offset 110) */
   "ddd\0"
   "glTexCoord3d\0"
   "\0"
   /* _mesa_function_pool[4943]: TexCoord3f (offset 112) */
   "fff\0"
   "glTexCoord3f\0"
   "\0"
   /* _mesa_function_pool[4961]: MultiTexCoord3ivARB (offset 397) */
   "ip\0"
   "glMultiTexCoord3ivARB\0"
   "\0"
   /* _mesa_function_pool[4987]: MultiTexCoord2sARB (offset 390) */
   "iii\0"
   "glMultiTexCoord2sARB\0"
   "\0"
   /* _mesa_function_pool[5013]: TexEnvx (will be remapped) */
   "iii\0"
   "glTexEnvx\0"
   "glTexEnvxOES\0"
   "\0"
   /* _mesa_function_pool[5041]: TexCoord3s (offset 116) */
   "iii\0"
   "glTexCoord3s\0"
   "\0"
   /* _mesa_function_pool[5059]: GetTexLevelParameteriv (offset 285) */
   "iiip\0"
   "glGetTexLevelParameteriv\0"
   "\0"
   /* _mesa_function_pool[5090]: ClearAccum (offset 204) */
   "ffff\0"
   "glClearAccum\0"
   "\0"
   /* _mesa_function_pool[5109]: RasterPos2sv (offset 69) */
   "p\0"
   "glRasterPos2sv\0"
   "\0"
   /* _mesa_function_pool[5127]: PolygonOffset (offset 319) */
   "ff\0"
   "glPolygonOffset\0"
   "\0"
   /* _mesa_function_pool[5147]: GetBufferParameteriv (will be remapped) */
   "iip\0"
   "glGetBufferParameteriv\0"
   "\0"
   /* _mesa_function_pool[5175]: Rectd (offset 86) */
   "dddd\0"
   "glRectd\0"
   "\0"
   /* _mesa_function_pool[5189]: PointSizePointerOES (will be remapped) */
   "iip\0"
   "glPointSizePointerOES\0"
   "\0"
   /* _mesa_function_pool[5216]: CopyTexImage2D (offset 324) */
   "iiiiiiii\0"
   "glCopyTexImage2D\0"
   "\0"
   /* _mesa_function_pool[5243]: GenVertexArraysAPPLE (will be remapped) */
   "ip\0"
   "glGenVertexArraysAPPLE\0"
   "\0"
   /* _mesa_function_pool[5270]: Lightfv (offset 160) */
   "iip\0"
   "glLightfv\0"
   "\0"
   /* _mesa_function_pool[5285]: Vertex3fv (offset 137) */
   "p\0"
   "glVertex3fv\0"
   "\0"
   /* _mesa_function_pool[5300]: ColorSubTable (offset 346) */
   "iiiiip\0"
   "glColorSubTable\0"
   "\0"
   /* _mesa_function_pool[5324]: Color4fv (offset 30) */
   "p\0"
   "glColor4fv\0"
   "\0"
   /* _mesa_function_pool[5338]: MultiTexCoord4ivARB (offset 405) */
   "ip\0"
   "glMultiTexCoord4ivARB\0"
   "\0"
   /* _mesa_function_pool[5364]: LoadPaletteFromModelViewMatrixOES (dynamic) */
   "\0"
   "glLoadPaletteFromModelViewMatrixOES\0"
   "\0"
   /* _mesa_function_pool[5402]: ColorPointer (offset 308) */
   "iiip\0"
   "glColorPointer\0"
   "\0"
   /* _mesa_function_pool[5423]: Rects (offset 92) */
   "iiii\0"
   "glRects\0"
   "\0"
   /* _mesa_function_pool[5437]: Lightiv (offset 162) */
   "iip\0"
   "glLightiv\0"
   "\0"
   /* _mesa_function_pool[5452]: IsFramebufferOES (will be remapped) */
   "i\0"
   "glIsFramebufferOES\0"
   "\0"
   /* _mesa_function_pool[5474]: Color3bv (offset 10) */
   "p\0"
   "glColor3bv\0"
   "\0"
   /* _mesa_function_pool[5488]: GetBufferPointervOES (will be remapped) */
   "iip\0"
   "glGetBufferPointervOES\0"
   "\0"
   /* _mesa_function_pool[5516]: PixelMapusv (offset 253) */
   "iip\0"
   "glPixelMapusv\0"
   "\0"
   /* _mesa_function_pool[5535]: GetTexGenfvOES (offset 279) */
   "iip\0"
   "glGetTexGenfvOES\0"
   "glGetTexGenfv\0"
   "\0"
   /* _mesa_function_pool[5571]: Rectdv (offset 87) */
   "pp\0"
   "glRectdv\0"
   "\0"
   /* _mesa_function_pool[5584]: GetTexParameterxv (will be remapped) */
   "iip\0"
   "glGetTexParameterxv\0"
   "glGetTexParameterxvOES\0"
   "\0"
   /* _mesa_function_pool[5632]: Materialiv (offset 172) */
   "iip\0"
   "glMaterialiv\0"
   "\0"
   /* _mesa_function_pool[5650]: PushClientAttrib (offset 335) */
   "i\0"
   "glPushClientAttrib\0"
   "\0"
   /* _mesa_function_pool[5672]: TexGenfOES (offset 190) */
   "iif\0"
   "glTexGenfOES\0"
   "glTexGenf\0"
   "\0"
   /* _mesa_function_pool[5700]: MatrixIndexPointerOES (dynamic) */
   "iiip\0"
   "glMatrixIndexPointerOES\0"
   "\0"
   /* _mesa_function_pool[5730]: PolygonMode (offset 174) */
   "ii\0"
   "glPolygonMode\0"
   "\0"
   /* _mesa_function_pool[5748]: BlendFunc (offset 241) */
   "ii\0"
   "glBlendFunc\0"
   "\0"
   /* _mesa_function_pool[5764]: DisableClientState (offset 309) */
   "i\0"
   "glDisableClientState\0"
   "\0"
   /* _mesa_function_pool[5788]: TexGend (offset 188) */
   "iid\0"
   "glTexGend\0"
   "\0"
   /* _mesa_function_pool[5803]: GetPolygonStipple (offset 274) */
   "p\0"
   "glGetPolygonStipple\0"
   "\0"
   /* _mesa_function_pool[5826]: TexGenxOES (will be remapped) */
   "iii\0"
   "glTexGenxOES\0"
   "\0"
   /* _mesa_function_pool[5844]: PointParameterxv (will be remapped) */
   "ip\0"
   "glPointParameterxv\0"
   "glPointParameterxvOES\0"
   "\0"
   /* _mesa_function_pool[5889]: Color4sv (offset 34) */
   "p\0"
   "glColor4sv\0"
   "\0"
   /* _mesa_function_pool[5903]: PixelZoom (offset 246) */
   "ff\0"
   "glPixelZoom\0"
   "\0"
   /* _mesa_function_pool[5919]: ColorTableParameterfv (offset 340) */
   "iip\0"
   "glColorTableParameterfv\0"
   "\0"
   /* _mesa_function_pool[5948]: PixelMapuiv (offset 252) */
   "iip\0"
   "glPixelMapuiv\0"
   "\0"
   /* _mesa_function_pool[5967]: Color3dv (offset 12) */
   "p\0"
   "glColor3dv\0"
   "\0"
   /* _mesa_function_pool[5981]: IsTexture (offset 330) */
   "i\0"
   "glIsTexture\0"
   "\0"
   /* _mesa_function_pool[5996]: DeleteFramebuffersOES (will be remapped) */
   "ip\0"
   "glDeleteFramebuffersOES\0"
   "\0"
   /* _mesa_function_pool[6024]: WeightPointerOES (dynamic) */
   "iiip\0"
   "glWeightPointerOES\0"
   "\0"
   /* _mesa_function_pool[6049]: CurrentPaletteMatrixOES (dynamic) */
   "i\0"
   "glCurrentPaletteMatrixOES\0"
   "\0"
   /* _mesa_function_pool[6078]: TexCoord4i (offset 122) */
   "iiii\0"
   "glTexCoord4i\0"
   "\0"
   /* _mesa_function_pool[6097]: GetMapdv (offset 266) */
   "iip\0"
   "glGetMapdv\0"
   "\0"
   /* _mesa_function_pool[6113]: PixelStoref (offset 249) */
   "if\0"
   "glPixelStoref\0"
   "\0"
   /* _mesa_function_pool[6131]: PrioritizeTextures (offset 331) */
   "ipp\0"
   "glPrioritizeTextures\0"
   "\0"
   /* _mesa_function_pool[6157]: PixelStorei (offset 250) */
   "ii\0"
   "glPixelStorei\0"
   "\0"
   /* _mesa_function_pool[6175]: IsBuffer (will be remapped) */
   "i\0"
   "glIsBuffer\0"
   "\0"
   /* _mesa_function_pool[6189]: EvalCoord2dv (offset 233) */
   "p\0"
   "glEvalCoord2dv\0"
   "\0"
   /* _mesa_function_pool[6207]: GetFixedv (will be remapped) */
   "ip\0"
   "glGetFixedv\0"
   "glGetFixedvOES\0"
   "\0"
   /* _mesa_function_pool[6238]: RenderbufferStorageOES (will be remapped) */
   "iiii\0"
   "glRenderbufferStorageOES\0"
   "\0"
   /* _mesa_function_pool[6269]: ColorMaterial (offset 151) */
   "ii\0"
   "glColorMaterial\0"
   "\0"
   /* _mesa_function_pool[6289]: Minmax (offset 368) */
   "iii\0"
   "glMinmax\0"
   "\0"
   /* _mesa_function_pool[6303]: GetSeparableFilter (offset 359) */
   "iiippp\0"
   "glGetSeparableFilter\0"
   "\0"
   /* _mesa_function_pool[6332]: FeedbackBuffer (offset 194) */
   "iip\0"
   "glFeedbackBuffer\0"
   "\0"
   /* _mesa_function_pool[6354]: RasterPos2iv (offset 67) */
   "p\0"
   "glRasterPos2iv\0"
   "\0"
   /* _mesa_function_pool[6372]: TexImage1D (offset 182) */
   "iiiiiiip\0"
   "glTexImage1D\0"
   "\0"
   /* _mesa_function_pool[6395]: MultiDrawElementsEXT (will be remapped) */
   "ipipi\0"
   "glMultiDrawElementsEXT\0"
   "\0"
   /* _mesa_function_pool[6425]: Color3s (offset 17) */
   "iii\0"
   "glColor3s\0"
   "\0"
   /* _mesa_function_pool[6440]: TexCoordPointer (offset 320) */
   "iiip\0"
   "glTexCoordPointer\0"
   "\0"
   /* _mesa_function_pool[6464]: GetRenderbufferParameterivOES (will be remapped) */
   "iip\0"
   "glGetRenderbufferParameterivOES\0"
   "\0"
   /* _mesa_function_pool[6501]: Color3i (offset 15) */
   "iii\0"
   "glColor3i\0"
   "\0"
   /* _mesa_function_pool[6516]: FrontFace (offset 157) */
   "i\0"
   "glFrontFace\0"
   "\0"
   /* _mesa_function_pool[6531]: EvalCoord2d (offset 232) */
   "dd\0"
   "glEvalCoord2d\0"
   "\0"
   /* _mesa_function_pool[6549]: EvalCoord2f (offset 234) */
   "ff\0"
   "glEvalCoord2f\0"
   "\0"
   /* _mesa_function_pool[6567]: Color3b (offset 9) */
   "iii\0"
   "glColor3b\0"
   "\0"
   /* _mesa_function_pool[6582]: MultiTexCoord2dARB (offset 384) */
   "idd\0"
   "glMultiTexCoord2dARB\0"
   "\0"
   /* _mesa_function_pool[6608]: Color3f (offset 13) */
   "fff\0"
   "glColor3f\0"
   "\0"
   /* _mesa_function_pool[6623]: Color3d (offset 11) */
   "ddd\0"
   "glColor3d\0"
   "\0"
   /* _mesa_function_pool[6638]: Normal3dv (offset 55) */
   "p\0"
   "glNormal3dv\0"
   "\0"
   /* _mesa_function_pool[6653]: Lightf (offset 159) */
   "iif\0"
   "glLightf\0"
   "\0"
   /* _mesa_function_pool[6667]: MatrixMode (offset 293) */
   "i\0"
   "glMatrixMode\0"
   "\0"
   /* _mesa_function_pool[6683]: GetPixelMapusv (offset 273) */
   "ip\0"
   "glGetPixelMapusv\0"
   "\0"
   /* _mesa_function_pool[6704]: Lighti (offset 161) */
   "iii\0"
   "glLighti\0"
   "\0"
   /* _mesa_function_pool[6718]: Color4s (offset 33) */
   "iiii\0"
   "glColor4s\0"
   "\0"
   /* _mesa_function_pool[6734]: ClearDepthx (will be remapped) */
   "i\0"
   "glClearDepthx\0"
   "glClearDepthxOES\0"
   "\0"
   /* _mesa_function_pool[6768]: MultiTexCoord4dvARB (offset 401) */
   "ip\0"
   "glMultiTexCoord4dvARB\0"
   "\0"
   /* _mesa_function_pool[6794]: Lightx (will be remapped) */
   "iii\0"
   "glLightx\0"
   "glLightxOES\0"
   "\0"
   /* _mesa_function_pool[6820]: GetDoublev (offset 260) */
   "ip\0"
   "glGetDoublev\0"
   "\0"
   /* _mesa_function_pool[6837]: MultMatrixd (offset 295) */
   "p\0"
   "glMultMatrixd\0"
   "\0"
   /* _mesa_function_pool[6854]: MultMatrixf (offset 294) */
   "p\0"
   "glMultMatrixf\0"
   "\0"
   /* _mesa_function_pool[6871]: GetFramebufferAttachmentParameterivOES (will be remapped) */
   "iiip\0"
   "glGetFramebufferAttachmentParameterivOES\0"
   "\0"
   /* _mesa_function_pool[6918]: MultiTexCoord4fvARB (offset 403) */
   "ip\0"
   "glMultiTexCoord4fvARB\0"
   "\0"
   /* _mesa_function_pool[6944]: MultMatrixx (will be remapped) */
   "p\0"
   "glMultMatrixx\0"
   "glMultMatrixxOES\0"
   "\0"
   /* _mesa_function_pool[6978]: PointParameterx (will be remapped) */
   "ii\0"
   "glPointParameterx\0"
   "glPointParameterxOES\0"
   "\0"
   /* _mesa_function_pool[7021]: DrawArrays (offset 310) */
   "iii\0"
   "glDrawArrays\0"
   "\0"
   /* _mesa_function_pool[7039]: PointParameterf (will be remapped) */
   "if\0"
   "glPointParameterf\0"
   "\0"
   /* _mesa_function_pool[7061]: TexEnviv (offset 187) */
   "iip\0"
   "glTexEnviv\0"
   "\0"
   /* _mesa_function_pool[7077]: TexSubImage3D (offset 372) */
   "iiiiiiiiiip\0"
   "glTexSubImage3D\0"
   "\0"
   /* _mesa_function_pool[7106]: GetColorTableParameterfv (offset 344) */
   "iip\0"
   "glGetColorTableParameterfv\0"
   "\0"
   /* _mesa_function_pool[7138]: Bitmap (offset 8) */
   "iiffffp\0"
   "glBitmap\0"
   "\0"
   /* _mesa_function_pool[7156]: TexGeniOES (offset 192) */
   "iii\0"
   "glTexGeniOES\0"
   "glTexGeni\0"
   "\0"
   /* _mesa_function_pool[7184]: GetTexLevelParameterfv (offset 284) */
   "iiip\0"
   "glGetTexLevelParameterfv\0"
   "\0"
   /* _mesa_function_pool[7215]: QueryMatrixxOES (will be remapped) */
   "pp\0"
   "glQueryMatrixxOES\0"
   "\0"
   /* _mesa_function_pool[7237]: Vertex2sv (offset 133) */
   "p\0"
   "glVertex2sv\0"
   "\0"
   /* _mesa_function_pool[7252]: GetIntegerv (offset 263) */
   "ip\0"
   "glGetIntegerv\0"
   "\0"
   /* _mesa_function_pool[7270]: Rotated (offset 299) */
   "dddd\0"
   "glRotated\0"
   "\0"
   /* _mesa_function_pool[7286]: DeleteBuffers (will be remapped) */
   "ip\0"
   "glDeleteBuffers\0"
   "\0"
   /* _mesa_function_pool[7306]: AlphaFuncx (will be remapped) */
   "ii\0"
   "glAlphaFuncx\0"
   "glAlphaFuncxOES\0"
   "\0"
   /* _mesa_function_pool[7339]: GetTexEnviv (offset 277) */
   "iip\0"
   "glGetTexEnviv\0"
   "\0"
   /* _mesa_function_pool[7358]: PopClientAttrib (offset 334) */
   "\0"
   "glPopClientAttrib\0"
   "\0"
   /* _mesa_function_pool[7378]: SeparableFilter2D (offset 360) */
   "iiiiiipp\0"
   "glSeparableFilter2D\0"
   "\0"
   /* _mesa_function_pool[7408]: Map1d (offset 220) */
   "iddiip\0"
   "glMap1d\0"
   "\0"
   /* _mesa_function_pool[7424]: Map1f (offset 221) */
   "iffiip\0"
   "glMap1f\0"
   "\0"
   /* _mesa_function_pool[7440]: ArrayElement (offset 306) */
   "i\0"
   "glArrayElement\0"
   "\0"
   /* _mesa_function_pool[7458]: TexImage2D (offset 183) */
   "iiiiiiiip\0"
   "glTexImage2D\0"
   "\0"
   /* _mesa_function_pool[7482]: GetMinmaxParameteriv (offset 366) */
   "iip\0"
   "glGetMinmaxParameteriv\0"
   "\0"
   /* _mesa_function_pool[7510]: DrawTexivOES (will be remapped) */
   "p\0"
   "glDrawTexivOES\0"
   "\0"
   /* _mesa_function_pool[7528]: CopyTexImage1D (offset 323) */
   "iiiiiii\0"
   "glCopyTexImage1D\0"
   "\0"
   /* _mesa_function_pool[7554]: RasterPos2dv (offset 63) */
   "p\0"
   "glRasterPos2dv\0"
   "\0"
   /* _mesa_function_pool[7572]: SampleCoveragex (will be remapped) */
   "ii\0"
   "glSampleCoveragex\0"
   "glSampleCoveragexOES\0"
   "\0"
   /* _mesa_function_pool[7615]: TexCoord1dv (offset 95) */
   "p\0"
   "glTexCoord1dv\0"
   "\0"
   /* _mesa_function_pool[7632]: PixelTransferi (offset 248) */
   "ii\0"
   "glPixelTransferi\0"
   "\0"
   /* _mesa_function_pool[7653]: Rotatef (offset 300) */
   "ffff\0"
   "glRotatef\0"
   "\0"
   /* _mesa_function_pool[7669]: Vertex3i (offset 138) */
   "iii\0"
   "glVertex3i\0"
   "\0"
   /* _mesa_function_pool[7685]: Vertex3f (offset 136) */
   "fff\0"
   "glVertex3f\0"
   "\0"
   /* _mesa_function_pool[7701]: Clear (offset 203) */
   "i\0"
   "glClear\0"
   "\0"
   /* _mesa_function_pool[7712]: Vertex3d (offset 134) */
   "ddd\0"
   "glVertex3d\0"
   "\0"
   /* _mesa_function_pool[7728]: ReadBuffer (offset 254) */
   "i\0"
   "glReadBuffer\0"
   "\0"
   /* _mesa_function_pool[7744]: ConvolutionParameteri (offset 352) */
   "iii\0"
   "glConvolutionParameteri\0"
   "\0"
   /* _mesa_function_pool[7773]: Ortho (offset 296) */
   "dddddd\0"
   "glOrtho\0"
   "\0"
   /* _mesa_function_pool[7789]: ListBase (offset 6) */
   "i\0"
   "glListBase\0"
   "\0"
   /* _mesa_function_pool[7803]: Vertex3s (offset 140) */
   "iii\0"
   "glVertex3s\0"
   "\0"
   /* _mesa_function_pool[7819]: ConvolutionParameterf (offset 350) */
   "iif\0"
   "glConvolutionParameterf\0"
   "\0"
   /* _mesa_function_pool[7848]: GetColorTableParameteriv (offset 345) */
   "iip\0"
   "glGetColorTableParameteriv\0"
   "\0"
   /* _mesa_function_pool[7880]: CallList (offset 2) */
   "i\0"
   "glCallList\0"
   "\0"
   /* _mesa_function_pool[7894]: Rectiv (offset 91) */
   "pp\0"
   "glRectiv\0"
   "\0"
   /* _mesa_function_pool[7907]: TexGenivOES (offset 193) */
   "iip\0"
   "glTexGenivOES\0"
   "glTexGeniv\0"
   "\0"
   /* _mesa_function_pool[7937]: TexParameterxv (will be remapped) */
   "iip\0"
   "glTexParameterxv\0"
   "glTexParameterxvOES\0"
   "\0"
   /* _mesa_function_pool[7979]: Vertex2fv (offset 129) */
   "p\0"
   "glVertex2fv\0"
   "\0"
   /* _mesa_function_pool[7994]: MultiDrawArraysEXT (will be remapped) */
   "ippi\0"
   "glMultiDrawArraysEXT\0"
   "\0"
   /* _mesa_function_pool[8021]: MultiTexCoord4dARB (offset 400) */
   "idddd\0"
   "glMultiTexCoord4dARB\0"
   "\0"
   /* _mesa_function_pool[8049]: Rotatex (will be remapped) */
   "iiii\0"
   "glRotatex\0"
   "glRotatexOES\0"
   "\0"
   /* _mesa_function_pool[8078]: Vertex3sv (offset 141) */
   "p\0"
   "glVertex3sv\0"
   "\0"
   /* _mesa_function_pool[8093]: EvalMesh1 (offset 236) */
   "iii\0"
   "glEvalMesh1\0"
   "\0"
   /* _mesa_function_pool[8110]: BindRenderbufferOES (will be remapped) */
   "ii\0"
   "glBindRenderbufferOES\0"
   "\0"
   /* _mesa_function_pool[8136]: MultiTexCoord1sARB (offset 382) */
   "ii\0"
   "glMultiTexCoord1sARB\0"
   "\0"
   /* _mesa_function_pool[8161]: GetTexParameterfv (offset 282) */
   "iip\0"
   "glGetTexParameterfv\0"
   "\0"
   /* _mesa_function_pool[8186]: MultiTexCoord1dvARB (offset 377) */
   "ip\0"
   "glMultiTexCoord1dvARB\0"
   "\0"
   /* _mesa_function_pool[8212]: Vertex2iv (offset 131) */
   "p\0"
   "glVertex2iv\0"
   "\0"
   /* _mesa_function_pool[8227]: LineWidth (offset 168) */
   "f\0"
   "glLineWidth\0"
   "\0"
   /* _mesa_function_pool[8242]: FramebufferTexture2DOES (will be remapped) */
   "iiiii\0"
   "glFramebufferTexture2DOES\0"
   "\0"
   /* _mesa_function_pool[8275]: Lightxv (will be remapped) */
   "iip\0"
   "glLightxv\0"
   "glLightxvOES\0"
   "\0"
   /* _mesa_function_pool[8303]: TexGendv (offset 189) */
   "iip\0"
   "glTexGendv\0"
   "\0"
   /* _mesa_function_pool[8319]: CheckFramebufferStatusOES (will be remapped) */
   "i\0"
   "glCheckFramebufferStatusOES\0"
   "\0"
   /* _mesa_function_pool[8350]: ResetMinmax (offset 370) */
   "i\0"
   "glResetMinmax\0"
   "\0"
   /* _mesa_function_pool[8367]: EnableClientState (offset 313) */
   "i\0"
   "glEnableClientState\0"
   "\0"
   /* _mesa_function_pool[8390]: GetConvolutionParameterfv (offset 357) */
   "iip\0"
   "glGetConvolutionParameterfv\0"
   "\0"
   /* _mesa_function_pool[8423]: GetMaterialfv (offset 269) */
   "iip\0"
   "glGetMaterialfv\0"
   "\0"
   /* _mesa_function_pool[8444]: DeleteTextures (offset 327) */
   "ip\0"
   "glDeleteTextures\0"
   "\0"
   /* _mesa_function_pool[8465]: ShadeModel (offset 177) */
   "i\0"
   "glShadeModel\0"
   "\0"
   /* _mesa_function_pool[8481]: Materialfv (offset 170) */
   "iip\0"
   "glMaterialfv\0"
   "\0"
   /* _mesa_function_pool[8499]: TexCoord3fv (offset 113) */
   "p\0"
   "glTexCoord3fv\0"
   "\0"
   /* _mesa_function_pool[8516]: CopyConvolutionFilter1D (offset 354) */
   "iiiii\0"
   "glCopyConvolutionFilter1D\0"
   "\0"
   /* _mesa_function_pool[8549]: TexGenfvOES (offset 191) */
   "iip\0"
   "glTexGenfvOES\0"
   "glTexGenfv\0"
   "\0"
   /* _mesa_function_pool[8579]: MultiTexCoord1ivARB (offset 381) */
   "ip\0"
   "glMultiTexCoord1ivARB\0"
   "\0"
   /* _mesa_function_pool[8605]: MultiTexCoord2ivARB (offset 389) */
   "ip\0"
   "glMultiTexCoord2ivARB\0"
   "\0"
   /* _mesa_function_pool[8631]: ClearDepthf (will be remapped) */
   "f\0"
   "glClearDepthf\0"
   "glClearDepthfOES\0"
   "\0"
   /* _mesa_function_pool[8665]: CopyTexSubImage2D (offset 326) */
   "iiiiiiii\0"
   "glCopyTexSubImage2D\0"
   "\0"
   /* _mesa_function_pool[8695]: SampleCoverage (will be remapped) */
   "fi\0"
   "glSampleCoverage\0"
   "\0"
   /* _mesa_function_pool[8716]: Color3iv (offset 16) */
   "p\0"
   "glColor3iv\0"
   "\0"
   /* _mesa_function_pool[8730]: DrawElements (offset 311) */
   "iiip\0"
   "glDrawElements\0"
   "\0"
   /* _mesa_function_pool[8751]: BindVertexArrayAPPLE (will be remapped) */
   "i\0"
   "glBindVertexArrayAPPLE\0"
   "\0"
   /* _mesa_function_pool[8777]: GetHistogramParameteriv (offset 363) */
   "iip\0"
   "glGetHistogramParameteriv\0"
   "\0"
   /* _mesa_function_pool[8808]: MultiTexCoord1iARB (offset 380) */
   "ii\0"
   "glMultiTexCoord1iARB\0"
   "\0"
   /* _mesa_function_pool[8833]: GetConvolutionFilter (offset 356) */
   "iiip\0"
   "glGetConvolutionFilter\0"
   "\0"
   /* _mesa_function_pool[8862]: EvalPoint2 (offset 239) */
   "ii\0"
   "glEvalPoint2\0"
   "\0"
   /* _mesa_function_pool[8879]: EvalPoint1 (offset 237) */
   "i\0"
   "glEvalPoint1\0"
   "\0"
   /* _mesa_function_pool[8895]: TexGenxvOES (will be remapped) */
   "iip\0"
   "glTexGenxvOES\0"
   "\0"
   /* _mesa_function_pool[8914]: Map2d (offset 222) */
   "iddiiddiip\0"
   "glMap2d\0"
   "\0"
   /* _mesa_function_pool[8934]: Map2f (offset 223) */
   "iffiiffiip\0"
   "glMap2f\0"
   "\0"
   /* _mesa_function_pool[8954]: MultiTexCoord4x (will be remapped) */
   "iiiii\0"
   "glMultiTexCoord4x\0"
   "glMultiTexCoord4xOES\0"
   "\0"
   /* _mesa_function_pool[9000]: Vertex4s (offset 148) */
   "iiii\0"
   "glVertex4s\0"
   "\0"
   /* _mesa_function_pool[9017]: Vertex4f (offset 144) */
   "ffff\0"
   "glVertex4f\0"
   "\0"
   /* _mesa_function_pool[9034]: EvalCoord1d (offset 228) */
   "d\0"
   "glEvalCoord1d\0"
   "\0"
   /* _mesa_function_pool[9051]: Vertex4d (offset 142) */
   "dddd\0"
   "glVertex4d\0"
   "\0"
   /* _mesa_function_pool[9068]: RasterPos4dv (offset 79) */
   "p\0"
   "glRasterPos4dv\0"
   "\0"
   /* _mesa_function_pool[9086]: MultiTexCoord4f (offset 402) */
   "iffff\0"
   "glMultiTexCoord4f\0"
   "glMultiTexCoord4fARB\0"
   "\0"
   /* _mesa_function_pool[9132]: Vertex4i (offset 146) */
   "iiii\0"
   "glVertex4i\0"
   "\0"
   /* _mesa_function_pool[9149]: GetHistogram (offset 361) */
   "iiiip\0"
   "glGetHistogram\0"
   "\0"
   /* _mesa_function_pool[9171]: Translatex (will be remapped) */
   "iii\0"
   "glTranslatex\0"
   "glTranslatexOES\0"
   "\0"
   /* _mesa_function_pool[9205]: Materialf (offset 169) */
   "iif\0"
   "glMaterialf\0"
   "\0"
   /* _mesa_function_pool[9222]: Materiali (offset 171) */
   "iii\0"
   "glMateriali\0"
   "\0"
   /* _mesa_function_pool[9239]: Indexsv (offset 51) */
   "p\0"
   "glIndexsv\0"
   "\0"
   /* _mesa_function_pool[9252]: MultiTexCoord4svARB (offset 407) */
   "ip\0"
   "glMultiTexCoord4svARB\0"
   "\0"
   /* _mesa_function_pool[9278]: LightModelfv (offset 164) */
   "ip\0"
   "glLightModelfv\0"
   "\0"
   /* _mesa_function_pool[9297]: Vertex4dv (offset 143) */
   "p\0"
   "glVertex4dv\0"
   "\0"
   /* _mesa_function_pool[9312]: EvalCoord1dv (offset 229) */
   "p\0"
   "glEvalCoord1dv\0"
   "\0"
   /* _mesa_function_pool[9330]: Materialx (will be remapped) */
   "iii\0"
   "glMaterialx\0"
   "glMaterialxOES\0"
   "\0"
   /* _mesa_function_pool[9362]: Translatef (offset 304) */
   "fff\0"
   "glTranslatef\0"
   "\0"
   /* _mesa_function_pool[9380]: StencilMask (offset 209) */
   "i\0"
   "glStencilMask\0"
   "\0"
   /* _mesa_function_pool[9397]: GetLightiv (offset 265) */
   "iip\0"
   "glGetLightiv\0"
   "\0"
   /* _mesa_function_pool[9415]: IsList (offset 287) */
   "i\0"
   "glIsList\0"
   "\0"
   /* _mesa_function_pool[9427]: RenderMode (offset 196) */
   "i\0"
   "glRenderMode\0"
   "\0"
   /* _mesa_function_pool[9443]: MultiTexCoord1fARB (offset 378) */
   "if\0"
   "glMultiTexCoord1fARB\0"
   "\0"
   /* _mesa_function_pool[9468]: BindBuffer (will be remapped) */
   "ii\0"
   "glBindBuffer\0"
   "\0"
   /* _mesa_function_pool[9485]: Frustumf (will be remapped) */
   "ffffff\0"
   "glFrustumf\0"
   "glFrustumfOES\0"
   "\0"
   /* _mesa_function_pool[9518]: LightModelxv (will be remapped) */
   "ip\0"
   "glLightModelxv\0"
   "glLightModelxvOES\0"
   "\0"
   /* _mesa_function_pool[9555]: IsRenderbufferOES (will be remapped) */
   "i\0"
   "glIsRenderbufferOES\0"
   "\0"
   /* _mesa_function_pool[9578]: CopyTexSubImage1D (offset 325) */
   "iiiiii\0"
   "glCopyTexSubImage1D\0"
   "\0"
   /* _mesa_function_pool[9606]: Frustumx (will be remapped) */
   "iiiiii\0"
   "glFrustumx\0"
   "glFrustumxOES\0"
   "\0"
   /* _mesa_function_pool[9639]: CullFace (offset 152) */
   "i\0"
   "glCullFace\0"
   "\0"
   /* _mesa_function_pool[9653]: BindTexture (offset 307) */
   "ii\0"
   "glBindTexture\0"
   "\0"
   /* _mesa_function_pool[9671]: StencilFunc (offset 243) */
   "iii\0"
   "glStencilFunc\0"
   "\0"
   /* _mesa_function_pool[9690]: CopyPixels (offset 255) */
   "iiiii\0"
   "glCopyPixels\0"
   "\0"
   /* _mesa_function_pool[9710]: Rectsv (offset 93) */
   "pp\0"
   "glRectsv\0"
   "\0"
   /* _mesa_function_pool[9723]: PopMatrix (offset 297) */
   "\0"
   "glPopMatrix\0"
   "\0"
   /* _mesa_function_pool[9737]: CopyConvolutionFilter2D (offset 355) */
   "iiiiii\0"
   "glCopyConvolutionFilter2D\0"
   "\0"
   /* _mesa_function_pool[9771]: DeleteRenderbuffersOES (will be remapped) */
   "ip\0"
   "glDeleteRenderbuffersOES\0"
   "\0"
   /* _mesa_function_pool[9800]: NormalPointer (offset 318) */
   "iip\0"
   "glNormalPointer\0"
   "\0"
   /* _mesa_function_pool[9821]: TexParameterfv (offset 179) */
   "iip\0"
   "glTexParameterfv\0"
   "\0"
   /* _mesa_function_pool[9843]: ClipPlane (offset 150) */
   "ip\0"
   "glClipPlane\0"
   "\0"
   /* _mesa_function_pool[9859]: Recti (offset 90) */
   "iiii\0"
   "glRecti\0"
   "\0"
   /* _mesa_function_pool[9873]: GetPixelMapuiv (offset 272) */
   "ip\0"
   "glGetPixelMapuiv\0"
   "\0"
   /* _mesa_function_pool[9894]: Rectf (offset 88) */
   "ffff\0"
   "glRectf\0"
   "\0"
   /* _mesa_function_pool[9908]: Indexfv (offset 47) */
   "p\0"
   "glIndexfv\0"
   "\0"
   /* _mesa_function_pool[9921]: GetPointerv (offset 329) */
   "ip\0"
   "glGetPointerv\0"
   "\0"
   /* _mesa_function_pool[9939]: IndexMask (offset 212) */
   "i\0"
   "glIndexMask\0"
   "\0"
   /* _mesa_function_pool[9954]: GetFloatv (offset 262) */
   "ip\0"
   "glGetFloatv\0"
   "\0"
   /* _mesa_function_pool[9970]: TexCoord4s (offset 124) */
   "iiii\0"
   "glTexCoord4s\0"
   "\0"
   /* _mesa_function_pool[9989]: TexCoord3sv (offset 117) */
   "p\0"
   "glTexCoord3sv\0"
   "\0"
   /* _mesa_function_pool[10006]: TexEnvxv (will be remapped) */
   "iip\0"
   "glTexEnvxv\0"
   "glTexEnvxvOES\0"
   "\0"
   /* _mesa_function_pool[10036]: PopAttrib (offset 218) */
   "\0"
   "glPopAttrib\0"
   "\0"
   /* _mesa_function_pool[10050]: Fogfv (offset 154) */
   "ip\0"
   "glFogfv\0"
   "\0"
   /* _mesa_function_pool[10062]: InitNames (offset 197) */
   "\0"
   "glInitNames\0"
   "\0"
   /* _mesa_function_pool[10076]: Normal3sv (offset 61) */
   "p\0"
   "glNormal3sv\0"
   "\0"
   /* _mesa_function_pool[10091]: UnmapBufferOES (will be remapped) */
   "i\0"
   "glUnmapBufferOES\0"
   "\0"
   /* _mesa_function_pool[10111]: TexCoord4d (offset 118) */
   "dddd\0"
   "glTexCoord4d\0"
   "\0"
   /* _mesa_function_pool[10130]: TexCoord4f (offset 120) */
   "ffff\0"
   "glTexCoord4f\0"
   "\0"
   /* _mesa_function_pool[10149]: GetBooleanv (offset 258) */
   "ip\0"
   "glGetBooleanv\0"
   "\0"
   /* _mesa_function_pool[10167]: Hint (offset 158) */
   "ii\0"
   "glHint\0"
   "\0"
   /* _mesa_function_pool[10178]: Color4dv (offset 28) */
   "p\0"
   "glColor4dv\0"
   "\0"
   /* _mesa_function_pool[10192]: CopyColorSubTable (offset 347) */
   "iiiii\0"
   "glCopyColorSubTable\0"
   "\0"
   /* _mesa_function_pool[10219]: IsVertexArrayAPPLE (will be remapped) */
   "i\0"
   "glIsVertexArrayAPPLE\0"
   "\0"
   /* _mesa_function_pool[10243]: Vertex4iv (offset 147) */
   "p\0"
   "glVertex4iv\0"
   "\0"
   /* _mesa_function_pool[10258]: BufferSubData (will be remapped) */
   "iiip\0"
   "glBufferSubData\0"
   "\0"
   /* _mesa_function_pool[10280]: TexCoord4dv (offset 119) */
   "p\0"
   "glTexCoord4dv\0"
   "\0"
   /* _mesa_function_pool[10297]: GetTexEnvxv (will be remapped) */
   "iip\0"
   "glGetTexEnvxv\0"
   "glGetTexEnvxvOES\0"
   "\0"
   /* _mesa_function_pool[10333]: Begin (offset 7) */
   "i\0"
   "glBegin\0"
   "\0"
   /* _mesa_function_pool[10344]: LightModeli (offset 165) */
   "ii\0"
   "glLightModeli\0"
   "\0"
   /* _mesa_function_pool[10362]: RasterPos4sv (offset 85) */
   "p\0"
   "glRasterPos4sv\0"
   "\0"
   /* _mesa_function_pool[10380]: Rectfv (offset 89) */
   "pp\0"
   "glRectfv\0"
   "\0"
   /* _mesa_function_pool[10393]: ClipPlanex (will be remapped) */
   "ip\0"
   "glClipPlanex\0"
   "glClipPlanexOES\0"
   "\0"
   /* _mesa_function_pool[10426]: LightModelf (offset 163) */
   "if\0"
   "glLightModelf\0"
   "\0"
   /* _mesa_function_pool[10444]: DrawTexsvOES (will be remapped) */
   "p\0"
   "glDrawTexsvOES\0"
   "\0"
   /* _mesa_function_pool[10462]: GetLightfv (offset 264) */
   "iip\0"
   "glGetLightfv\0"
   "\0"
   /* _mesa_function_pool[10480]: LightModelx (will be remapped) */
   "ii\0"
   "glLightModelx\0"
   "glLightModelxOES\0"
   "\0"
   /* _mesa_function_pool[10515]: ClearColorx (will be remapped) */
   "iiii\0"
   "glClearColorx\0"
   "glClearColorxOES\0"
   "\0"
   /* _mesa_function_pool[10552]: ClipPlanef (will be remapped) */
   "ip\0"
   "glClipPlanef\0"
   "glClipPlanefOES\0"
   "\0"
   /* _mesa_function_pool[10585]: MultiTexCoord2fvARB (offset 387) */
   "ip\0"
   "glMultiTexCoord2fvARB\0"
   "\0"
   /* _mesa_function_pool[10611]: ClearColor (offset 206) */
   "ffff\0"
   "glClearColor\0"
   "\0"
   /* _mesa_function_pool[10630]: ColorMask (offset 210) */
   "iiii\0"
   "glColorMask\0"
   "\0"
   /* _mesa_function_pool[10648]: RasterPos4iv (offset 83) */
   "p\0"
   "glRasterPos4iv\0"
   "\0"
   /* _mesa_function_pool[10666]: Indexub (offset 315) */
   "i\0"
   "glIndexub\0"
   "\0"
   /* _mesa_function_pool[10679]: GetMinmaxParameterfv (offset 365) */
   "iip\0"
   "glGetMinmaxParameterfv\0"
   "\0"
   /* _mesa_function_pool[10707]: ClientActiveTexture (offset 375) */
   "i\0"
   "glClientActiveTexture\0"
   "glClientActiveTextureARB\0"
   "\0"
   /* _mesa_function_pool[10757]: ClearDepth (offset 208) */
   "d\0"
   "glClearDepth\0"
   "\0"
   /* _mesa_function_pool[10773]: MultiTexCoord2svARB (offset 391) */
   "ip\0"
   "glMultiTexCoord2svARB\0"
   "\0"
   ;

/* these functions need to be remapped */
static const struct gl_function_pool_remap MESA_remap_table_functions[] = {
   {  1561, BlendEquationSeparateOES_remap_index },
   {  2912, BlendFuncSeparateOES_remap_index },
   {  2416, DrawTexfOES_remap_index },
   {  3963, DrawTexfvOES_remap_index },
   {   878, DrawTexiOES_remap_index },
   {  7510, DrawTexivOES_remap_index },
   {  1220, DrawTexsOES_remap_index },
   { 10444, DrawTexsvOES_remap_index },
   {  4169, DrawTexxOES_remap_index },
   {  4223, DrawTexxvOES_remap_index },
   {  3811, BindFramebufferOES_remap_index },
   {  8110, BindRenderbufferOES_remap_index },
   {  8319, CheckFramebufferStatusOES_remap_index },
   {  5996, DeleteFramebuffersOES_remap_index },
   {  9771, DeleteRenderbuffersOES_remap_index },
   {  2102, FramebufferRenderbufferOES_remap_index },
   {  8242, FramebufferTexture2DOES_remap_index },
   {  4341, GenFramebuffersOES_remap_index },
   {  4143, GenRenderbuffersOES_remap_index },
   {   486, GenerateMipmapOES_remap_index },
   {  6871, GetFramebufferAttachmentParameterivOES_remap_index },
   {  6464, GetRenderbufferParameterivOES_remap_index },
   {  5452, IsFramebufferOES_remap_index },
   {  9555, IsRenderbufferOES_remap_index },
   {  6238, RenderbufferStorageOES_remap_index },
   {  5189, PointSizePointerOES_remap_index },
   {  7215, QueryMatrixxOES_remap_index },
   {  3049, GetTexGenxvOES_remap_index },
   {  5826, TexGenxOES_remap_index },
   {  8895, TexGenxvOES_remap_index },
   {  5488, GetBufferPointervOES_remap_index },
   {  2397, MapBufferOES_remap_index },
   { 10091, UnmapBufferOES_remap_index },
   {  7994, MultiDrawArraysEXT_remap_index },
   {  6395, MultiDrawElementsEXT_remap_index },
   {  8751, BindVertexArrayAPPLE_remap_index },
   {   787, DeleteVertexArraysAPPLE_remap_index },
   {  5243, GenVertexArraysAPPLE_remap_index },
   { 10219, IsVertexArrayAPPLE_remap_index },
   {  3859, EGLImageTargetRenderbufferStorageOES_remap_index },
   {  3619, EGLImageTargetTexture2DOES_remap_index },
   {  4420, CompressedTexImage2D_remap_index },
   {   970, CompressedTexSubImage2D_remap_index },
   {  8695, SampleCoverage_remap_index },
   {  9468, BindBuffer_remap_index },
   {  3208, BufferData_remap_index },
   { 10258, BufferSubData_remap_index },
   {  7286, DeleteBuffers_remap_index },
   {  2639, GenBuffers_remap_index },
   {  5147, GetBufferParameteriv_remap_index },
   {  6175, IsBuffer_remap_index },
   {  7039, PointParameterf_remap_index },
   {  4823, PointParameterfv_remap_index },
   {  7306, AlphaFuncx_remap_index },
   { 10515, ClearColorx_remap_index },
   {  8631, ClearDepthf_remap_index },
   {  6734, ClearDepthx_remap_index },
   {  2580, Color4x_remap_index },
   {  1847, DepthRangef_remap_index },
   {  1798, DepthRangex_remap_index },
   {  1922, Fogx_remap_index },
   {  3836, Fogxv_remap_index },
   {  9485, Frustumf_remap_index },
   {  9606, Frustumx_remap_index },
   { 10480, LightModelx_remap_index },
   {  9518, LightModelxv_remap_index },
   {  6794, Lightx_remap_index },
   {  8275, Lightxv_remap_index },
   {  3378, LineWidthx_remap_index },
   {  3981, LoadMatrixx_remap_index },
   {  9330, Materialx_remap_index },
   {  3483, Materialxv_remap_index },
   {  6944, MultMatrixx_remap_index },
   {  8954, MultiTexCoord4x_remap_index },
   {  3348, Normal3x_remap_index },
   {  4391, Orthof_remap_index },
   {  4504, Orthox_remap_index },
   {   846, PointSizex_remap_index },
   {   243, PolygonOffsetx_remap_index },
   {  8049, Rotatex_remap_index },
   {  7572, SampleCoveragex_remap_index },
   {  1458, Scalex_remap_index },
   {  5013, TexEnvx_remap_index },
   { 10006, TexEnvxv_remap_index },
   {  1592, TexParameterx_remap_index },
   {  9171, Translatex_remap_index },
   { 10552, ClipPlanef_remap_index },
   { 10393, ClipPlanex_remap_index },
   {   702, GetClipPlanef_remap_index },
   {   648, GetClipPlanex_remap_index },
   {  6207, GetFixedv_remap_index },
   {  1137, GetLightxv_remap_index },
   {  1033, GetMaterialxv_remap_index },
   { 10297, GetTexEnvxv_remap_index },
   {  5584, GetTexParameterxv_remap_index },
   {  6978, PointParameterx_remap_index },
   {  5844, PointParameterxv_remap_index },
   {  7937, TexParameterxv_remap_index },
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

#if defined(need_GL_OES_blend_equation_separate)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_blend_equation_separate_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_blend_func_separate)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_blend_func_separate_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_draw_texture)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_draw_texture_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_fixed_point)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_fixed_point_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_framebuffer_object)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_framebuffer_object_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_mapbuffer)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_mapbuffer_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_matrix_palette)
static const struct gl_function_remap GL_OES_matrix_palette_functions[] = {
   {  5364, -1 }, /* LoadPaletteFromModelViewMatrixOES */
   {  5700, -1 }, /* MatrixIndexPointerOES */
   {  6024, -1 }, /* WeightPointerOES */
   {  6049, -1 }, /* CurrentPaletteMatrixOES */
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_point_size_array)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_point_size_array_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_query_matrix)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_query_matrix_functions[] = {
   {    -1, -1 }
};
#endif

#if defined(need_GL_OES_single_precision)
/* functions defined in MESA_remap_table_functions are excluded */
static const struct gl_function_remap GL_OES_single_precision_functions[] = {
   {    -1, -1 }
};
#endif

