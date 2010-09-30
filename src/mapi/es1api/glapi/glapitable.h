/* DO NOT EDIT - This file generated automatically by gl_table.py (from Mesa) script */

/*
 * Copyright (C) 1999-2003  Brian Paul   All Rights Reserved.
 * (C) Copyright IBM Corporation 2004
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

#if !defined( _GLAPI_TABLE_H_ )
#  define _GLAPI_TABLE_H_

#ifndef GLAPIENTRYP
# ifndef GLAPIENTRY
#  define GLAPIENTRY
# endif

# define GLAPIENTRYP GLAPIENTRY *
#endif


struct _glapi_table
{
   void (GLAPIENTRYP NewList)(GLuint list, GLenum mode); /* 0 */
   void (GLAPIENTRYP EndList)(void); /* 1 */
   void (GLAPIENTRYP CallList)(GLuint list); /* 2 */
   void (GLAPIENTRYP CallLists)(GLsizei n, GLenum type, const GLvoid * lists); /* 3 */
   void (GLAPIENTRYP DeleteLists)(GLuint list, GLsizei range); /* 4 */
   GLuint (GLAPIENTRYP GenLists)(GLsizei range); /* 5 */
   void (GLAPIENTRYP ListBase)(GLuint base); /* 6 */
   void (GLAPIENTRYP Begin)(GLenum mode); /* 7 */
   void (GLAPIENTRYP Bitmap)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap); /* 8 */
   void (GLAPIENTRYP Color3b)(GLbyte red, GLbyte green, GLbyte blue); /* 9 */
   void (GLAPIENTRYP Color3bv)(const GLbyte * v); /* 10 */
   void (GLAPIENTRYP Color3d)(GLdouble red, GLdouble green, GLdouble blue); /* 11 */
   void (GLAPIENTRYP Color3dv)(const GLdouble * v); /* 12 */
   void (GLAPIENTRYP Color3f)(GLfloat red, GLfloat green, GLfloat blue); /* 13 */
   void (GLAPIENTRYP Color3fv)(const GLfloat * v); /* 14 */
   void (GLAPIENTRYP Color3i)(GLint red, GLint green, GLint blue); /* 15 */
   void (GLAPIENTRYP Color3iv)(const GLint * v); /* 16 */
   void (GLAPIENTRYP Color3s)(GLshort red, GLshort green, GLshort blue); /* 17 */
   void (GLAPIENTRYP Color3sv)(const GLshort * v); /* 18 */
   void (GLAPIENTRYP Color3ub)(GLubyte red, GLubyte green, GLubyte blue); /* 19 */
   void (GLAPIENTRYP Color3ubv)(const GLubyte * v); /* 20 */
   void (GLAPIENTRYP Color3ui)(GLuint red, GLuint green, GLuint blue); /* 21 */
   void (GLAPIENTRYP Color3uiv)(const GLuint * v); /* 22 */
   void (GLAPIENTRYP Color3us)(GLushort red, GLushort green, GLushort blue); /* 23 */
   void (GLAPIENTRYP Color3usv)(const GLushort * v); /* 24 */
   void (GLAPIENTRYP Color4b)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha); /* 25 */
   void (GLAPIENTRYP Color4bv)(const GLbyte * v); /* 26 */
   void (GLAPIENTRYP Color4d)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha); /* 27 */
   void (GLAPIENTRYP Color4dv)(const GLdouble * v); /* 28 */
   void (GLAPIENTRYP Color4f)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha); /* 29 */
   void (GLAPIENTRYP Color4fv)(const GLfloat * v); /* 30 */
   void (GLAPIENTRYP Color4i)(GLint red, GLint green, GLint blue, GLint alpha); /* 31 */
   void (GLAPIENTRYP Color4iv)(const GLint * v); /* 32 */
   void (GLAPIENTRYP Color4s)(GLshort red, GLshort green, GLshort blue, GLshort alpha); /* 33 */
   void (GLAPIENTRYP Color4sv)(const GLshort * v); /* 34 */
   void (GLAPIENTRYP Color4ub)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha); /* 35 */
   void (GLAPIENTRYP Color4ubv)(const GLubyte * v); /* 36 */
   void (GLAPIENTRYP Color4ui)(GLuint red, GLuint green, GLuint blue, GLuint alpha); /* 37 */
   void (GLAPIENTRYP Color4uiv)(const GLuint * v); /* 38 */
   void (GLAPIENTRYP Color4us)(GLushort red, GLushort green, GLushort blue, GLushort alpha); /* 39 */
   void (GLAPIENTRYP Color4usv)(const GLushort * v); /* 40 */
   void (GLAPIENTRYP EdgeFlag)(GLboolean flag); /* 41 */
   void (GLAPIENTRYP EdgeFlagv)(const GLboolean * flag); /* 42 */
   void (GLAPIENTRYP End)(void); /* 43 */
   void (GLAPIENTRYP Indexd)(GLdouble c); /* 44 */
   void (GLAPIENTRYP Indexdv)(const GLdouble * c); /* 45 */
   void (GLAPIENTRYP Indexf)(GLfloat c); /* 46 */
   void (GLAPIENTRYP Indexfv)(const GLfloat * c); /* 47 */
   void (GLAPIENTRYP Indexi)(GLint c); /* 48 */
   void (GLAPIENTRYP Indexiv)(const GLint * c); /* 49 */
   void (GLAPIENTRYP Indexs)(GLshort c); /* 50 */
   void (GLAPIENTRYP Indexsv)(const GLshort * c); /* 51 */
   void (GLAPIENTRYP Normal3b)(GLbyte nx, GLbyte ny, GLbyte nz); /* 52 */
   void (GLAPIENTRYP Normal3bv)(const GLbyte * v); /* 53 */
   void (GLAPIENTRYP Normal3d)(GLdouble nx, GLdouble ny, GLdouble nz); /* 54 */
   void (GLAPIENTRYP Normal3dv)(const GLdouble * v); /* 55 */
   void (GLAPIENTRYP Normal3f)(GLfloat nx, GLfloat ny, GLfloat nz); /* 56 */
   void (GLAPIENTRYP Normal3fv)(const GLfloat * v); /* 57 */
   void (GLAPIENTRYP Normal3i)(GLint nx, GLint ny, GLint nz); /* 58 */
   void (GLAPIENTRYP Normal3iv)(const GLint * v); /* 59 */
   void (GLAPIENTRYP Normal3s)(GLshort nx, GLshort ny, GLshort nz); /* 60 */
   void (GLAPIENTRYP Normal3sv)(const GLshort * v); /* 61 */
   void (GLAPIENTRYP RasterPos2d)(GLdouble x, GLdouble y); /* 62 */
   void (GLAPIENTRYP RasterPos2dv)(const GLdouble * v); /* 63 */
   void (GLAPIENTRYP RasterPos2f)(GLfloat x, GLfloat y); /* 64 */
   void (GLAPIENTRYP RasterPos2fv)(const GLfloat * v); /* 65 */
   void (GLAPIENTRYP RasterPos2i)(GLint x, GLint y); /* 66 */
   void (GLAPIENTRYP RasterPos2iv)(const GLint * v); /* 67 */
   void (GLAPIENTRYP RasterPos2s)(GLshort x, GLshort y); /* 68 */
   void (GLAPIENTRYP RasterPos2sv)(const GLshort * v); /* 69 */
   void (GLAPIENTRYP RasterPos3d)(GLdouble x, GLdouble y, GLdouble z); /* 70 */
   void (GLAPIENTRYP RasterPos3dv)(const GLdouble * v); /* 71 */
   void (GLAPIENTRYP RasterPos3f)(GLfloat x, GLfloat y, GLfloat z); /* 72 */
   void (GLAPIENTRYP RasterPos3fv)(const GLfloat * v); /* 73 */
   void (GLAPIENTRYP RasterPos3i)(GLint x, GLint y, GLint z); /* 74 */
   void (GLAPIENTRYP RasterPos3iv)(const GLint * v); /* 75 */
   void (GLAPIENTRYP RasterPos3s)(GLshort x, GLshort y, GLshort z); /* 76 */
   void (GLAPIENTRYP RasterPos3sv)(const GLshort * v); /* 77 */
   void (GLAPIENTRYP RasterPos4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w); /* 78 */
   void (GLAPIENTRYP RasterPos4dv)(const GLdouble * v); /* 79 */
   void (GLAPIENTRYP RasterPos4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w); /* 80 */
   void (GLAPIENTRYP RasterPos4fv)(const GLfloat * v); /* 81 */
   void (GLAPIENTRYP RasterPos4i)(GLint x, GLint y, GLint z, GLint w); /* 82 */
   void (GLAPIENTRYP RasterPos4iv)(const GLint * v); /* 83 */
   void (GLAPIENTRYP RasterPos4s)(GLshort x, GLshort y, GLshort z, GLshort w); /* 84 */
   void (GLAPIENTRYP RasterPos4sv)(const GLshort * v); /* 85 */
   void (GLAPIENTRYP Rectd)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2); /* 86 */
   void (GLAPIENTRYP Rectdv)(const GLdouble * v1, const GLdouble * v2); /* 87 */
   void (GLAPIENTRYP Rectf)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2); /* 88 */
   void (GLAPIENTRYP Rectfv)(const GLfloat * v1, const GLfloat * v2); /* 89 */
   void (GLAPIENTRYP Recti)(GLint x1, GLint y1, GLint x2, GLint y2); /* 90 */
   void (GLAPIENTRYP Rectiv)(const GLint * v1, const GLint * v2); /* 91 */
   void (GLAPIENTRYP Rects)(GLshort x1, GLshort y1, GLshort x2, GLshort y2); /* 92 */
   void (GLAPIENTRYP Rectsv)(const GLshort * v1, const GLshort * v2); /* 93 */
   void (GLAPIENTRYP TexCoord1d)(GLdouble s); /* 94 */
   void (GLAPIENTRYP TexCoord1dv)(const GLdouble * v); /* 95 */
   void (GLAPIENTRYP TexCoord1f)(GLfloat s); /* 96 */
   void (GLAPIENTRYP TexCoord1fv)(const GLfloat * v); /* 97 */
   void (GLAPIENTRYP TexCoord1i)(GLint s); /* 98 */
   void (GLAPIENTRYP TexCoord1iv)(const GLint * v); /* 99 */
   void (GLAPIENTRYP TexCoord1s)(GLshort s); /* 100 */
   void (GLAPIENTRYP TexCoord1sv)(const GLshort * v); /* 101 */
   void (GLAPIENTRYP TexCoord2d)(GLdouble s, GLdouble t); /* 102 */
   void (GLAPIENTRYP TexCoord2dv)(const GLdouble * v); /* 103 */
   void (GLAPIENTRYP TexCoord2f)(GLfloat s, GLfloat t); /* 104 */
   void (GLAPIENTRYP TexCoord2fv)(const GLfloat * v); /* 105 */
   void (GLAPIENTRYP TexCoord2i)(GLint s, GLint t); /* 106 */
   void (GLAPIENTRYP TexCoord2iv)(const GLint * v); /* 107 */
   void (GLAPIENTRYP TexCoord2s)(GLshort s, GLshort t); /* 108 */
   void (GLAPIENTRYP TexCoord2sv)(const GLshort * v); /* 109 */
   void (GLAPIENTRYP TexCoord3d)(GLdouble s, GLdouble t, GLdouble r); /* 110 */
   void (GLAPIENTRYP TexCoord3dv)(const GLdouble * v); /* 111 */
   void (GLAPIENTRYP TexCoord3f)(GLfloat s, GLfloat t, GLfloat r); /* 112 */
   void (GLAPIENTRYP TexCoord3fv)(const GLfloat * v); /* 113 */
   void (GLAPIENTRYP TexCoord3i)(GLint s, GLint t, GLint r); /* 114 */
   void (GLAPIENTRYP TexCoord3iv)(const GLint * v); /* 115 */
   void (GLAPIENTRYP TexCoord3s)(GLshort s, GLshort t, GLshort r); /* 116 */
   void (GLAPIENTRYP TexCoord3sv)(const GLshort * v); /* 117 */
   void (GLAPIENTRYP TexCoord4d)(GLdouble s, GLdouble t, GLdouble r, GLdouble q); /* 118 */
   void (GLAPIENTRYP TexCoord4dv)(const GLdouble * v); /* 119 */
   void (GLAPIENTRYP TexCoord4f)(GLfloat s, GLfloat t, GLfloat r, GLfloat q); /* 120 */
   void (GLAPIENTRYP TexCoord4fv)(const GLfloat * v); /* 121 */
   void (GLAPIENTRYP TexCoord4i)(GLint s, GLint t, GLint r, GLint q); /* 122 */
   void (GLAPIENTRYP TexCoord4iv)(const GLint * v); /* 123 */
   void (GLAPIENTRYP TexCoord4s)(GLshort s, GLshort t, GLshort r, GLshort q); /* 124 */
   void (GLAPIENTRYP TexCoord4sv)(const GLshort * v); /* 125 */
   void (GLAPIENTRYP Vertex2d)(GLdouble x, GLdouble y); /* 126 */
   void (GLAPIENTRYP Vertex2dv)(const GLdouble * v); /* 127 */
   void (GLAPIENTRYP Vertex2f)(GLfloat x, GLfloat y); /* 128 */
   void (GLAPIENTRYP Vertex2fv)(const GLfloat * v); /* 129 */
   void (GLAPIENTRYP Vertex2i)(GLint x, GLint y); /* 130 */
   void (GLAPIENTRYP Vertex2iv)(const GLint * v); /* 131 */
   void (GLAPIENTRYP Vertex2s)(GLshort x, GLshort y); /* 132 */
   void (GLAPIENTRYP Vertex2sv)(const GLshort * v); /* 133 */
   void (GLAPIENTRYP Vertex3d)(GLdouble x, GLdouble y, GLdouble z); /* 134 */
   void (GLAPIENTRYP Vertex3dv)(const GLdouble * v); /* 135 */
   void (GLAPIENTRYP Vertex3f)(GLfloat x, GLfloat y, GLfloat z); /* 136 */
   void (GLAPIENTRYP Vertex3fv)(const GLfloat * v); /* 137 */
   void (GLAPIENTRYP Vertex3i)(GLint x, GLint y, GLint z); /* 138 */
   void (GLAPIENTRYP Vertex3iv)(const GLint * v); /* 139 */
   void (GLAPIENTRYP Vertex3s)(GLshort x, GLshort y, GLshort z); /* 140 */
   void (GLAPIENTRYP Vertex3sv)(const GLshort * v); /* 141 */
   void (GLAPIENTRYP Vertex4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w); /* 142 */
   void (GLAPIENTRYP Vertex4dv)(const GLdouble * v); /* 143 */
   void (GLAPIENTRYP Vertex4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w); /* 144 */
   void (GLAPIENTRYP Vertex4fv)(const GLfloat * v); /* 145 */
   void (GLAPIENTRYP Vertex4i)(GLint x, GLint y, GLint z, GLint w); /* 146 */
   void (GLAPIENTRYP Vertex4iv)(const GLint * v); /* 147 */
   void (GLAPIENTRYP Vertex4s)(GLshort x, GLshort y, GLshort z, GLshort w); /* 148 */
   void (GLAPIENTRYP Vertex4sv)(const GLshort * v); /* 149 */
   void (GLAPIENTRYP ClipPlane)(GLenum plane, const GLdouble * equation); /* 150 */
   void (GLAPIENTRYP ColorMaterial)(GLenum face, GLenum mode); /* 151 */
   void (GLAPIENTRYP CullFace)(GLenum mode); /* 152 */
   void (GLAPIENTRYP Fogf)(GLenum pname, GLfloat param); /* 153 */
   void (GLAPIENTRYP Fogfv)(GLenum pname, const GLfloat * params); /* 154 */
   void (GLAPIENTRYP Fogi)(GLenum pname, GLint param); /* 155 */
   void (GLAPIENTRYP Fogiv)(GLenum pname, const GLint * params); /* 156 */
   void (GLAPIENTRYP FrontFace)(GLenum mode); /* 157 */
   void (GLAPIENTRYP Hint)(GLenum target, GLenum mode); /* 158 */
   void (GLAPIENTRYP Lightf)(GLenum light, GLenum pname, GLfloat param); /* 159 */
   void (GLAPIENTRYP Lightfv)(GLenum light, GLenum pname, const GLfloat * params); /* 160 */
   void (GLAPIENTRYP Lighti)(GLenum light, GLenum pname, GLint param); /* 161 */
   void (GLAPIENTRYP Lightiv)(GLenum light, GLenum pname, const GLint * params); /* 162 */
   void (GLAPIENTRYP LightModelf)(GLenum pname, GLfloat param); /* 163 */
   void (GLAPIENTRYP LightModelfv)(GLenum pname, const GLfloat * params); /* 164 */
   void (GLAPIENTRYP LightModeli)(GLenum pname, GLint param); /* 165 */
   void (GLAPIENTRYP LightModeliv)(GLenum pname, const GLint * params); /* 166 */
   void (GLAPIENTRYP LineStipple)(GLint factor, GLushort pattern); /* 167 */
   void (GLAPIENTRYP LineWidth)(GLfloat width); /* 168 */
   void (GLAPIENTRYP Materialf)(GLenum face, GLenum pname, GLfloat param); /* 169 */
   void (GLAPIENTRYP Materialfv)(GLenum face, GLenum pname, const GLfloat * params); /* 170 */
   void (GLAPIENTRYP Materiali)(GLenum face, GLenum pname, GLint param); /* 171 */
   void (GLAPIENTRYP Materialiv)(GLenum face, GLenum pname, const GLint * params); /* 172 */
   void (GLAPIENTRYP PointSize)(GLfloat size); /* 173 */
   void (GLAPIENTRYP PolygonMode)(GLenum face, GLenum mode); /* 174 */
   void (GLAPIENTRYP PolygonStipple)(const GLubyte * mask); /* 175 */
   void (GLAPIENTRYP Scissor)(GLint x, GLint y, GLsizei width, GLsizei height); /* 176 */
   void (GLAPIENTRYP ShadeModel)(GLenum mode); /* 177 */
   void (GLAPIENTRYP TexParameterf)(GLenum target, GLenum pname, GLfloat param); /* 178 */
   void (GLAPIENTRYP TexParameterfv)(GLenum target, GLenum pname, const GLfloat * params); /* 179 */
   void (GLAPIENTRYP TexParameteri)(GLenum target, GLenum pname, GLint param); /* 180 */
   void (GLAPIENTRYP TexParameteriv)(GLenum target, GLenum pname, const GLint * params); /* 181 */
   void (GLAPIENTRYP TexImage1D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels); /* 182 */
   void (GLAPIENTRYP TexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels); /* 183 */
   void (GLAPIENTRYP TexEnvf)(GLenum target, GLenum pname, GLfloat param); /* 184 */
   void (GLAPIENTRYP TexEnvfv)(GLenum target, GLenum pname, const GLfloat * params); /* 185 */
   void (GLAPIENTRYP TexEnvi)(GLenum target, GLenum pname, GLint param); /* 186 */
   void (GLAPIENTRYP TexEnviv)(GLenum target, GLenum pname, const GLint * params); /* 187 */
   void (GLAPIENTRYP TexGend)(GLenum coord, GLenum pname, GLdouble param); /* 188 */
   void (GLAPIENTRYP TexGendv)(GLenum coord, GLenum pname, const GLdouble * params); /* 189 */
   void (GLAPIENTRYP TexGenfOES)(GLenum coord, GLenum pname, GLfloat param); /* 190 */
   void (GLAPIENTRYP TexGenfvOES)(GLenum coord, GLenum pname, const GLfloat * params); /* 191 */
   void (GLAPIENTRYP TexGeniOES)(GLenum coord, GLenum pname, GLint param); /* 192 */
   void (GLAPIENTRYP TexGenivOES)(GLenum coord, GLenum pname, const GLint * params); /* 193 */
   void (GLAPIENTRYP FeedbackBuffer)(GLsizei size, GLenum type, GLfloat * buffer); /* 194 */
   void (GLAPIENTRYP SelectBuffer)(GLsizei size, GLuint * buffer); /* 195 */
   GLint (GLAPIENTRYP RenderMode)(GLenum mode); /* 196 */
   void (GLAPIENTRYP InitNames)(void); /* 197 */
   void (GLAPIENTRYP LoadName)(GLuint name); /* 198 */
   void (GLAPIENTRYP PassThrough)(GLfloat token); /* 199 */
   void (GLAPIENTRYP PopName)(void); /* 200 */
   void (GLAPIENTRYP PushName)(GLuint name); /* 201 */
   void (GLAPIENTRYP DrawBuffer)(GLenum mode); /* 202 */
   void (GLAPIENTRYP Clear)(GLbitfield mask); /* 203 */
   void (GLAPIENTRYP ClearAccum)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha); /* 204 */
   void (GLAPIENTRYP ClearIndex)(GLfloat c); /* 205 */
   void (GLAPIENTRYP ClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha); /* 206 */
   void (GLAPIENTRYP ClearStencil)(GLint s); /* 207 */
   void (GLAPIENTRYP ClearDepth)(GLclampd depth); /* 208 */
   void (GLAPIENTRYP StencilMask)(GLuint mask); /* 209 */
   void (GLAPIENTRYP ColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha); /* 210 */
   void (GLAPIENTRYP DepthMask)(GLboolean flag); /* 211 */
   void (GLAPIENTRYP IndexMask)(GLuint mask); /* 212 */
   void (GLAPIENTRYP Accum)(GLenum op, GLfloat value); /* 213 */
   void (GLAPIENTRYP Disable)(GLenum cap); /* 214 */
   void (GLAPIENTRYP Enable)(GLenum cap); /* 215 */
   void (GLAPIENTRYP Finish)(void); /* 216 */
   void (GLAPIENTRYP Flush)(void); /* 217 */
   void (GLAPIENTRYP PopAttrib)(void); /* 218 */
   void (GLAPIENTRYP PushAttrib)(GLbitfield mask); /* 219 */
   void (GLAPIENTRYP Map1d)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points); /* 220 */
   void (GLAPIENTRYP Map1f)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points); /* 221 */
   void (GLAPIENTRYP Map2d)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points); /* 222 */
   void (GLAPIENTRYP Map2f)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points); /* 223 */
   void (GLAPIENTRYP MapGrid1d)(GLint un, GLdouble u1, GLdouble u2); /* 224 */
   void (GLAPIENTRYP MapGrid1f)(GLint un, GLfloat u1, GLfloat u2); /* 225 */
   void (GLAPIENTRYP MapGrid2d)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2); /* 226 */
   void (GLAPIENTRYP MapGrid2f)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2); /* 227 */
   void (GLAPIENTRYP EvalCoord1d)(GLdouble u); /* 228 */
   void (GLAPIENTRYP EvalCoord1dv)(const GLdouble * u); /* 229 */
   void (GLAPIENTRYP EvalCoord1f)(GLfloat u); /* 230 */
   void (GLAPIENTRYP EvalCoord1fv)(const GLfloat * u); /* 231 */
   void (GLAPIENTRYP EvalCoord2d)(GLdouble u, GLdouble v); /* 232 */
   void (GLAPIENTRYP EvalCoord2dv)(const GLdouble * u); /* 233 */
   void (GLAPIENTRYP EvalCoord2f)(GLfloat u, GLfloat v); /* 234 */
   void (GLAPIENTRYP EvalCoord2fv)(const GLfloat * u); /* 235 */
   void (GLAPIENTRYP EvalMesh1)(GLenum mode, GLint i1, GLint i2); /* 236 */
   void (GLAPIENTRYP EvalPoint1)(GLint i); /* 237 */
   void (GLAPIENTRYP EvalMesh2)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2); /* 238 */
   void (GLAPIENTRYP EvalPoint2)(GLint i, GLint j); /* 239 */
   void (GLAPIENTRYP AlphaFunc)(GLenum func, GLclampf ref); /* 240 */
   void (GLAPIENTRYP BlendFunc)(GLenum sfactor, GLenum dfactor); /* 241 */
   void (GLAPIENTRYP LogicOp)(GLenum opcode); /* 242 */
   void (GLAPIENTRYP StencilFunc)(GLenum func, GLint ref, GLuint mask); /* 243 */
   void (GLAPIENTRYP StencilOp)(GLenum fail, GLenum zfail, GLenum zpass); /* 244 */
   void (GLAPIENTRYP DepthFunc)(GLenum func); /* 245 */
   void (GLAPIENTRYP PixelZoom)(GLfloat xfactor, GLfloat yfactor); /* 246 */
   void (GLAPIENTRYP PixelTransferf)(GLenum pname, GLfloat param); /* 247 */
   void (GLAPIENTRYP PixelTransferi)(GLenum pname, GLint param); /* 248 */
   void (GLAPIENTRYP PixelStoref)(GLenum pname, GLfloat param); /* 249 */
   void (GLAPIENTRYP PixelStorei)(GLenum pname, GLint param); /* 250 */
   void (GLAPIENTRYP PixelMapfv)(GLenum map, GLsizei mapsize, const GLfloat * values); /* 251 */
   void (GLAPIENTRYP PixelMapuiv)(GLenum map, GLsizei mapsize, const GLuint * values); /* 252 */
   void (GLAPIENTRYP PixelMapusv)(GLenum map, GLsizei mapsize, const GLushort * values); /* 253 */
   void (GLAPIENTRYP ReadBuffer)(GLenum mode); /* 254 */
   void (GLAPIENTRYP CopyPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type); /* 255 */
   void (GLAPIENTRYP ReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels); /* 256 */
   void (GLAPIENTRYP DrawPixels)(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels); /* 257 */
   void (GLAPIENTRYP GetBooleanv)(GLenum pname, GLboolean * params); /* 258 */
   void (GLAPIENTRYP GetClipPlane)(GLenum plane, GLdouble * equation); /* 259 */
   void (GLAPIENTRYP GetDoublev)(GLenum pname, GLdouble * params); /* 260 */
   GLenum (GLAPIENTRYP GetError)(void); /* 261 */
   void (GLAPIENTRYP GetFloatv)(GLenum pname, GLfloat * params); /* 262 */
   void (GLAPIENTRYP GetIntegerv)(GLenum pname, GLint * params); /* 263 */
   void (GLAPIENTRYP GetLightfv)(GLenum light, GLenum pname, GLfloat * params); /* 264 */
   void (GLAPIENTRYP GetLightiv)(GLenum light, GLenum pname, GLint * params); /* 265 */
   void (GLAPIENTRYP GetMapdv)(GLenum target, GLenum query, GLdouble * v); /* 266 */
   void (GLAPIENTRYP GetMapfv)(GLenum target, GLenum query, GLfloat * v); /* 267 */
   void (GLAPIENTRYP GetMapiv)(GLenum target, GLenum query, GLint * v); /* 268 */
   void (GLAPIENTRYP GetMaterialfv)(GLenum face, GLenum pname, GLfloat * params); /* 269 */
   void (GLAPIENTRYP GetMaterialiv)(GLenum face, GLenum pname, GLint * params); /* 270 */
   void (GLAPIENTRYP GetPixelMapfv)(GLenum map, GLfloat * values); /* 271 */
   void (GLAPIENTRYP GetPixelMapuiv)(GLenum map, GLuint * values); /* 272 */
   void (GLAPIENTRYP GetPixelMapusv)(GLenum map, GLushort * values); /* 273 */
   void (GLAPIENTRYP GetPolygonStipple)(GLubyte * mask); /* 274 */
   const GLubyte * (GLAPIENTRYP GetString)(GLenum name); /* 275 */
   void (GLAPIENTRYP GetTexEnvfv)(GLenum target, GLenum pname, GLfloat * params); /* 276 */
   void (GLAPIENTRYP GetTexEnviv)(GLenum target, GLenum pname, GLint * params); /* 277 */
   void (GLAPIENTRYP GetTexGendv)(GLenum coord, GLenum pname, GLdouble * params); /* 278 */
   void (GLAPIENTRYP GetTexGenfvOES)(GLenum coord, GLenum pname, GLfloat * params); /* 279 */
   void (GLAPIENTRYP GetTexGenivOES)(GLenum coord, GLenum pname, GLint * params); /* 280 */
   void (GLAPIENTRYP GetTexImage)(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels); /* 281 */
   void (GLAPIENTRYP GetTexParameterfv)(GLenum target, GLenum pname, GLfloat * params); /* 282 */
   void (GLAPIENTRYP GetTexParameteriv)(GLenum target, GLenum pname, GLint * params); /* 283 */
   void (GLAPIENTRYP GetTexLevelParameterfv)(GLenum target, GLint level, GLenum pname, GLfloat * params); /* 284 */
   void (GLAPIENTRYP GetTexLevelParameteriv)(GLenum target, GLint level, GLenum pname, GLint * params); /* 285 */
   GLboolean (GLAPIENTRYP IsEnabled)(GLenum cap); /* 286 */
   GLboolean (GLAPIENTRYP IsList)(GLuint list); /* 287 */
   void (GLAPIENTRYP DepthRange)(GLclampd zNear, GLclampd zFar); /* 288 */
   void (GLAPIENTRYP Frustum)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar); /* 289 */
   void (GLAPIENTRYP LoadIdentity)(void); /* 290 */
   void (GLAPIENTRYP LoadMatrixf)(const GLfloat * m); /* 291 */
   void (GLAPIENTRYP LoadMatrixd)(const GLdouble * m); /* 292 */
   void (GLAPIENTRYP MatrixMode)(GLenum mode); /* 293 */
   void (GLAPIENTRYP MultMatrixf)(const GLfloat * m); /* 294 */
   void (GLAPIENTRYP MultMatrixd)(const GLdouble * m); /* 295 */
   void (GLAPIENTRYP Ortho)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar); /* 296 */
   void (GLAPIENTRYP PopMatrix)(void); /* 297 */
   void (GLAPIENTRYP PushMatrix)(void); /* 298 */
   void (GLAPIENTRYP Rotated)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z); /* 299 */
   void (GLAPIENTRYP Rotatef)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z); /* 300 */
   void (GLAPIENTRYP Scaled)(GLdouble x, GLdouble y, GLdouble z); /* 301 */
   void (GLAPIENTRYP Scalef)(GLfloat x, GLfloat y, GLfloat z); /* 302 */
   void (GLAPIENTRYP Translated)(GLdouble x, GLdouble y, GLdouble z); /* 303 */
   void (GLAPIENTRYP Translatef)(GLfloat x, GLfloat y, GLfloat z); /* 304 */
   void (GLAPIENTRYP Viewport)(GLint x, GLint y, GLsizei width, GLsizei height); /* 305 */
   void (GLAPIENTRYP ArrayElement)(GLint i); /* 306 */
   void (GLAPIENTRYP BindTexture)(GLenum target, GLuint texture); /* 307 */
   void (GLAPIENTRYP ColorPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer); /* 308 */
   void (GLAPIENTRYP DisableClientState)(GLenum array); /* 309 */
   void (GLAPIENTRYP DrawArrays)(GLenum mode, GLint first, GLsizei count); /* 310 */
   void (GLAPIENTRYP DrawElements)(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices); /* 311 */
   void (GLAPIENTRYP EdgeFlagPointer)(GLsizei stride, const GLvoid * pointer); /* 312 */
   void (GLAPIENTRYP EnableClientState)(GLenum array); /* 313 */
   void (GLAPIENTRYP IndexPointer)(GLenum type, GLsizei stride, const GLvoid * pointer); /* 314 */
   void (GLAPIENTRYP Indexub)(GLubyte c); /* 315 */
   void (GLAPIENTRYP Indexubv)(const GLubyte * c); /* 316 */
   void (GLAPIENTRYP InterleavedArrays)(GLenum format, GLsizei stride, const GLvoid * pointer); /* 317 */
   void (GLAPIENTRYP NormalPointer)(GLenum type, GLsizei stride, const GLvoid * pointer); /* 318 */
   void (GLAPIENTRYP PolygonOffset)(GLfloat factor, GLfloat units); /* 319 */
   void (GLAPIENTRYP TexCoordPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer); /* 320 */
   void (GLAPIENTRYP VertexPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer); /* 321 */
   GLboolean (GLAPIENTRYP AreTexturesResident)(GLsizei n, const GLuint * textures, GLboolean * residences); /* 322 */
   void (GLAPIENTRYP CopyTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border); /* 323 */
   void (GLAPIENTRYP CopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border); /* 324 */
   void (GLAPIENTRYP CopyTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width); /* 325 */
   void (GLAPIENTRYP CopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height); /* 326 */
   void (GLAPIENTRYP DeleteTextures)(GLsizei n, const GLuint * textures); /* 327 */
   void (GLAPIENTRYP GenTextures)(GLsizei n, GLuint * textures); /* 328 */
   void (GLAPIENTRYP GetPointerv)(GLenum pname, GLvoid ** params); /* 329 */
   GLboolean (GLAPIENTRYP IsTexture)(GLuint texture); /* 330 */
   void (GLAPIENTRYP PrioritizeTextures)(GLsizei n, const GLuint * textures, const GLclampf * priorities); /* 331 */
   void (GLAPIENTRYP TexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels); /* 332 */
   void (GLAPIENTRYP TexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels); /* 333 */
   void (GLAPIENTRYP PopClientAttrib)(void); /* 334 */
   void (GLAPIENTRYP PushClientAttrib)(GLbitfield mask); /* 335 */
   void (GLAPIENTRYP BlendColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha); /* 336 */
   void (GLAPIENTRYP BlendEquationOES)(GLenum mode); /* 337 */
   void (GLAPIENTRYP DrawRangeElements)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices); /* 338 */
   void (GLAPIENTRYP ColorTable)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * table); /* 339 */
   void (GLAPIENTRYP ColorTableParameterfv)(GLenum target, GLenum pname, const GLfloat * params); /* 340 */
   void (GLAPIENTRYP ColorTableParameteriv)(GLenum target, GLenum pname, const GLint * params); /* 341 */
   void (GLAPIENTRYP CopyColorTable)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width); /* 342 */
   void (GLAPIENTRYP GetColorTable)(GLenum target, GLenum format, GLenum type, GLvoid * table); /* 343 */
   void (GLAPIENTRYP GetColorTableParameterfv)(GLenum target, GLenum pname, GLfloat * params); /* 344 */
   void (GLAPIENTRYP GetColorTableParameteriv)(GLenum target, GLenum pname, GLint * params); /* 345 */
   void (GLAPIENTRYP ColorSubTable)(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid * data); /* 346 */
   void (GLAPIENTRYP CopyColorSubTable)(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width); /* 347 */
   void (GLAPIENTRYP ConvolutionFilter1D)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * image); /* 348 */
   void (GLAPIENTRYP ConvolutionFilter2D)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * image); /* 349 */
   void (GLAPIENTRYP ConvolutionParameterf)(GLenum target, GLenum pname, GLfloat params); /* 350 */
   void (GLAPIENTRYP ConvolutionParameterfv)(GLenum target, GLenum pname, const GLfloat * params); /* 351 */
   void (GLAPIENTRYP ConvolutionParameteri)(GLenum target, GLenum pname, GLint params); /* 352 */
   void (GLAPIENTRYP ConvolutionParameteriv)(GLenum target, GLenum pname, const GLint * params); /* 353 */
   void (GLAPIENTRYP CopyConvolutionFilter1D)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width); /* 354 */
   void (GLAPIENTRYP CopyConvolutionFilter2D)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height); /* 355 */
   void (GLAPIENTRYP GetConvolutionFilter)(GLenum target, GLenum format, GLenum type, GLvoid * image); /* 356 */
   void (GLAPIENTRYP GetConvolutionParameterfv)(GLenum target, GLenum pname, GLfloat * params); /* 357 */
   void (GLAPIENTRYP GetConvolutionParameteriv)(GLenum target, GLenum pname, GLint * params); /* 358 */
   void (GLAPIENTRYP GetSeparableFilter)(GLenum target, GLenum format, GLenum type, GLvoid * row, GLvoid * column, GLvoid * span); /* 359 */
   void (GLAPIENTRYP SeparableFilter2D)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * row, const GLvoid * column); /* 360 */
   void (GLAPIENTRYP GetHistogram)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values); /* 361 */
   void (GLAPIENTRYP GetHistogramParameterfv)(GLenum target, GLenum pname, GLfloat * params); /* 362 */
   void (GLAPIENTRYP GetHistogramParameteriv)(GLenum target, GLenum pname, GLint * params); /* 363 */
   void (GLAPIENTRYP GetMinmax)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values); /* 364 */
   void (GLAPIENTRYP GetMinmaxParameterfv)(GLenum target, GLenum pname, GLfloat * params); /* 365 */
   void (GLAPIENTRYP GetMinmaxParameteriv)(GLenum target, GLenum pname, GLint * params); /* 366 */
   void (GLAPIENTRYP Histogram)(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink); /* 367 */
   void (GLAPIENTRYP Minmax)(GLenum target, GLenum internalformat, GLboolean sink); /* 368 */
   void (GLAPIENTRYP ResetHistogram)(GLenum target); /* 369 */
   void (GLAPIENTRYP ResetMinmax)(GLenum target); /* 370 */
   void (GLAPIENTRYP TexImage3D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels); /* 371 */
   void (GLAPIENTRYP TexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels); /* 372 */
   void (GLAPIENTRYP CopyTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height); /* 373 */
   void (GLAPIENTRYP ActiveTexture)(GLenum texture); /* 374 */
   void (GLAPIENTRYP ClientActiveTexture)(GLenum texture); /* 375 */
   void (GLAPIENTRYP MultiTexCoord1dARB)(GLenum target, GLdouble s); /* 376 */
   void (GLAPIENTRYP MultiTexCoord1dvARB)(GLenum target, const GLdouble * v); /* 377 */
   void (GLAPIENTRYP MultiTexCoord1fARB)(GLenum target, GLfloat s); /* 378 */
   void (GLAPIENTRYP MultiTexCoord1fvARB)(GLenum target, const GLfloat * v); /* 379 */
   void (GLAPIENTRYP MultiTexCoord1iARB)(GLenum target, GLint s); /* 380 */
   void (GLAPIENTRYP MultiTexCoord1ivARB)(GLenum target, const GLint * v); /* 381 */
   void (GLAPIENTRYP MultiTexCoord1sARB)(GLenum target, GLshort s); /* 382 */
   void (GLAPIENTRYP MultiTexCoord1svARB)(GLenum target, const GLshort * v); /* 383 */
   void (GLAPIENTRYP MultiTexCoord2dARB)(GLenum target, GLdouble s, GLdouble t); /* 384 */
   void (GLAPIENTRYP MultiTexCoord2dvARB)(GLenum target, const GLdouble * v); /* 385 */
   void (GLAPIENTRYP MultiTexCoord2fARB)(GLenum target, GLfloat s, GLfloat t); /* 386 */
   void (GLAPIENTRYP MultiTexCoord2fvARB)(GLenum target, const GLfloat * v); /* 387 */
   void (GLAPIENTRYP MultiTexCoord2iARB)(GLenum target, GLint s, GLint t); /* 388 */
   void (GLAPIENTRYP MultiTexCoord2ivARB)(GLenum target, const GLint * v); /* 389 */
   void (GLAPIENTRYP MultiTexCoord2sARB)(GLenum target, GLshort s, GLshort t); /* 390 */
   void (GLAPIENTRYP MultiTexCoord2svARB)(GLenum target, const GLshort * v); /* 391 */
   void (GLAPIENTRYP MultiTexCoord3dARB)(GLenum target, GLdouble s, GLdouble t, GLdouble r); /* 392 */
   void (GLAPIENTRYP MultiTexCoord3dvARB)(GLenum target, const GLdouble * v); /* 393 */
   void (GLAPIENTRYP MultiTexCoord3fARB)(GLenum target, GLfloat s, GLfloat t, GLfloat r); /* 394 */
   void (GLAPIENTRYP MultiTexCoord3fvARB)(GLenum target, const GLfloat * v); /* 395 */
   void (GLAPIENTRYP MultiTexCoord3iARB)(GLenum target, GLint s, GLint t, GLint r); /* 396 */
   void (GLAPIENTRYP MultiTexCoord3ivARB)(GLenum target, const GLint * v); /* 397 */
   void (GLAPIENTRYP MultiTexCoord3sARB)(GLenum target, GLshort s, GLshort t, GLshort r); /* 398 */
   void (GLAPIENTRYP MultiTexCoord3svARB)(GLenum target, const GLshort * v); /* 399 */
   void (GLAPIENTRYP MultiTexCoord4dARB)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q); /* 400 */
   void (GLAPIENTRYP MultiTexCoord4dvARB)(GLenum target, const GLdouble * v); /* 401 */
   void (GLAPIENTRYP MultiTexCoord4f)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q); /* 402 */
   void (GLAPIENTRYP MultiTexCoord4fvARB)(GLenum target, const GLfloat * v); /* 403 */
   void (GLAPIENTRYP MultiTexCoord4iARB)(GLenum target, GLint s, GLint t, GLint r, GLint q); /* 404 */
   void (GLAPIENTRYP MultiTexCoord4ivARB)(GLenum target, const GLint * v); /* 405 */
   void (GLAPIENTRYP MultiTexCoord4sARB)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q); /* 406 */
   void (GLAPIENTRYP MultiTexCoord4svARB)(GLenum target, const GLshort * v); /* 407 */
   void (GLAPIENTRYP BlendEquationSeparateOES)(GLenum modeRGB, GLenum modeA); /* 408 */
   void (GLAPIENTRYP BlendFuncSeparateOES)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha); /* 409 */
   void (GLAPIENTRYP DrawTexfOES)(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height); /* 410 */
   void (GLAPIENTRYP DrawTexfvOES)(const GLfloat * coords); /* 411 */
   void (GLAPIENTRYP DrawTexiOES)(GLint x, GLint y, GLint z, GLint width, GLint height); /* 412 */
   void (GLAPIENTRYP DrawTexivOES)(const GLint * coords); /* 413 */
   void (GLAPIENTRYP DrawTexsOES)(GLshort x, GLshort y, GLshort z, GLshort width, GLshort height); /* 414 */
   void (GLAPIENTRYP DrawTexsvOES)(const GLshort * coords); /* 415 */
   void (GLAPIENTRYP DrawTexxOES)(GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height); /* 416 */
   void (GLAPIENTRYP DrawTexxvOES)(const GLfixed * coords); /* 417 */
   void (GLAPIENTRYP BindFramebufferOES)(GLenum target, GLuint framebuffer); /* 418 */
   void (GLAPIENTRYP BindRenderbufferOES)(GLenum target, GLuint renderbuffer); /* 419 */
   GLenum (GLAPIENTRYP CheckFramebufferStatusOES)(GLenum target); /* 420 */
   void (GLAPIENTRYP DeleteFramebuffersOES)(GLsizei n, const GLuint * framebuffers); /* 421 */
   void (GLAPIENTRYP DeleteRenderbuffersOES)(GLsizei n, const GLuint * renderbuffers); /* 422 */
   void (GLAPIENTRYP FramebufferRenderbufferOES)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer); /* 423 */
   void (GLAPIENTRYP FramebufferTexture2DOES)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level); /* 424 */
   void (GLAPIENTRYP GenFramebuffersOES)(GLsizei n, GLuint * framebuffers); /* 425 */
   void (GLAPIENTRYP GenRenderbuffersOES)(GLsizei n, GLuint * renderbuffers); /* 426 */
   void (GLAPIENTRYP GenerateMipmapOES)(GLenum target); /* 427 */
   void (GLAPIENTRYP GetFramebufferAttachmentParameterivOES)(GLenum target, GLenum attachment, GLenum pname, GLint * params); /* 428 */
   void (GLAPIENTRYP GetRenderbufferParameterivOES)(GLenum target, GLenum pname, GLint * params); /* 429 */
   GLboolean (GLAPIENTRYP IsFramebufferOES)(GLuint framebuffer); /* 430 */
   GLboolean (GLAPIENTRYP IsRenderbufferOES)(GLuint renderbuffer); /* 431 */
   void (GLAPIENTRYP RenderbufferStorageOES)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height); /* 432 */
   void (GLAPIENTRYP PointSizePointerOES)(GLenum type, GLsizei stride, const GLvoid * pointer); /* 433 */
   GLbitfield (GLAPIENTRYP QueryMatrixxOES)(GLfixed * mantissa, GLint * exponent); /* 434 */
   void (GLAPIENTRYP GetTexGenxvOES)(GLenum coord, GLenum pname, GLfixed * params); /* 435 */
   void (GLAPIENTRYP TexGenxOES)(GLenum coord, GLenum pname, GLint param); /* 436 */
   void (GLAPIENTRYP TexGenxvOES)(GLenum coord, GLenum pname, const GLfixed * params); /* 437 */
   void (GLAPIENTRYP GetBufferPointervOES)(GLenum target, GLenum pname, GLvoid ** params); /* 438 */
   GLvoid * (GLAPIENTRYP MapBufferOES)(GLenum target, GLenum access); /* 439 */
   GLboolean (GLAPIENTRYP UnmapBufferOES)(GLenum target); /* 440 */
   void (GLAPIENTRYP MultiDrawArraysEXT)(GLenum mode, const GLint * first, const GLsizei * count, GLsizei primcount); /* 441 */
   void (GLAPIENTRYP MultiDrawElementsEXT)(GLenum mode, const GLsizei * count, GLenum type, const GLvoid ** indices, GLsizei primcount); /* 442 */
   void (GLAPIENTRYP BindVertexArrayAPPLE)(GLuint array); /* 443 */
   void (GLAPIENTRYP DeleteVertexArraysAPPLE)(GLsizei n, const GLuint * arrays); /* 444 */
   void (GLAPIENTRYP GenVertexArraysAPPLE)(GLsizei n, GLuint * arrays); /* 445 */
   GLboolean (GLAPIENTRYP IsVertexArrayAPPLE)(GLuint array); /* 446 */
   void (GLAPIENTRYP EGLImageTargetRenderbufferStorageOES)(GLenum target, GLvoid * writeOffset); /* 447 */
   void (GLAPIENTRYP EGLImageTargetTexture2DOES)(GLenum target, GLvoid * writeOffset); /* 448 */
   void (GLAPIENTRYP CompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data); /* 449 */
   void (GLAPIENTRYP CompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data); /* 450 */
   void (GLAPIENTRYP SampleCoverage)(GLclampf value, GLboolean invert); /* 451 */
   void (GLAPIENTRYP BindBuffer)(GLenum target, GLuint buffer); /* 452 */
   void (GLAPIENTRYP BufferData)(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage); /* 453 */
   void (GLAPIENTRYP BufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data); /* 454 */
   void (GLAPIENTRYP DeleteBuffers)(GLsizei n, const GLuint * buffer); /* 455 */
   void (GLAPIENTRYP GenBuffers)(GLsizei n, GLuint * buffer); /* 456 */
   void (GLAPIENTRYP GetBufferParameteriv)(GLenum target, GLenum pname, GLint * params); /* 457 */
   GLboolean (GLAPIENTRYP IsBuffer)(GLuint buffer); /* 458 */
   void (GLAPIENTRYP PointParameterf)(GLenum pname, GLfloat param); /* 459 */
   void (GLAPIENTRYP PointParameterfv)(GLenum pname, const GLfloat * params); /* 460 */
   void (GLAPIENTRYP AlphaFuncx)(GLenum func, GLclampx ref); /* 461 */
   void (GLAPIENTRYP ClearColorx)(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha); /* 462 */
   void (GLAPIENTRYP ClearDepthf)(GLclampf depth); /* 463 */
   void (GLAPIENTRYP ClearDepthx)(GLclampx depth); /* 464 */
   void (GLAPIENTRYP Color4x)(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha); /* 465 */
   void (GLAPIENTRYP DepthRangef)(GLclampf zNear, GLclampf zFar); /* 466 */
   void (GLAPIENTRYP DepthRangex)(GLclampx zNear, GLclampx zFar); /* 467 */
   void (GLAPIENTRYP Fogx)(GLenum pname, GLfixed param); /* 468 */
   void (GLAPIENTRYP Fogxv)(GLenum pname, const GLfixed * params); /* 469 */
   void (GLAPIENTRYP Frustumf)(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar); /* 470 */
   void (GLAPIENTRYP Frustumx)(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar); /* 471 */
   void (GLAPIENTRYP LightModelx)(GLenum pname, GLfixed param); /* 472 */
   void (GLAPIENTRYP LightModelxv)(GLenum pname, const GLfixed * params); /* 473 */
   void (GLAPIENTRYP Lightx)(GLenum light, GLenum pname, GLfixed param); /* 474 */
   void (GLAPIENTRYP Lightxv)(GLenum light, GLenum pname, const GLfixed * params); /* 475 */
   void (GLAPIENTRYP LineWidthx)(GLfixed width); /* 476 */
   void (GLAPIENTRYP LoadMatrixx)(const GLfixed * m); /* 477 */
   void (GLAPIENTRYP Materialx)(GLenum face, GLenum pname, GLfixed param); /* 478 */
   void (GLAPIENTRYP Materialxv)(GLenum face, GLenum pname, const GLfixed * params); /* 479 */
   void (GLAPIENTRYP MultMatrixx)(const GLfixed * m); /* 480 */
   void (GLAPIENTRYP MultiTexCoord4x)(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q); /* 481 */
   void (GLAPIENTRYP Normal3x)(GLfixed nx, GLfixed ny, GLfixed nz); /* 482 */
   void (GLAPIENTRYP Orthof)(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar); /* 483 */
   void (GLAPIENTRYP Orthox)(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar); /* 484 */
   void (GLAPIENTRYP PointSizex)(GLfixed size); /* 485 */
   void (GLAPIENTRYP PolygonOffsetx)(GLfixed factor, GLfixed units); /* 486 */
   void (GLAPIENTRYP Rotatex)(GLfixed angle, GLfixed x, GLfixed y, GLfixed z); /* 487 */
   void (GLAPIENTRYP SampleCoveragex)(GLclampx value, GLboolean invert); /* 488 */
   void (GLAPIENTRYP Scalex)(GLfixed x, GLfixed y, GLfixed z); /* 489 */
   void (GLAPIENTRYP TexEnvx)(GLenum target, GLenum pname, GLfixed param); /* 490 */
   void (GLAPIENTRYP TexEnvxv)(GLenum target, GLenum pname, const GLfixed * params); /* 491 */
   void (GLAPIENTRYP TexParameterx)(GLenum target, GLenum pname, GLfixed param); /* 492 */
   void (GLAPIENTRYP Translatex)(GLfixed x, GLfixed y, GLfixed z); /* 493 */
   void (GLAPIENTRYP ClipPlanef)(GLenum plane, const GLfloat * equation); /* 494 */
   void (GLAPIENTRYP ClipPlanex)(GLenum plane, const GLfixed * equation); /* 495 */
   void (GLAPIENTRYP GetClipPlanef)(GLenum plane, GLfloat * equation); /* 496 */
   void (GLAPIENTRYP GetClipPlanex)(GLenum plane, GLfixed * equation); /* 497 */
   void (GLAPIENTRYP GetFixedv)(GLenum pname, GLfixed * params); /* 498 */
   void (GLAPIENTRYP GetLightxv)(GLenum light, GLenum pname, GLfixed * params); /* 499 */
   void (GLAPIENTRYP GetMaterialxv)(GLenum face, GLenum pname, GLfixed * params); /* 500 */
   void (GLAPIENTRYP GetTexEnvxv)(GLenum target, GLenum pname, GLfixed * params); /* 501 */
   void (GLAPIENTRYP GetTexParameterxv)(GLenum target, GLenum pname, GLfixed * params); /* 502 */
   void (GLAPIENTRYP PointParameterx)(GLenum pname, GLfixed param); /* 503 */
   void (GLAPIENTRYP PointParameterxv)(GLenum pname, const GLfixed * params); /* 504 */
   void (GLAPIENTRYP TexParameterxv)(GLenum target, GLenum pname, const GLfixed * params); /* 505 */
};

#endif /* !defined( _GLAPI_TABLE_H_ ) */
