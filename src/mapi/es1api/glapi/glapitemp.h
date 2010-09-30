/* DO NOT EDIT - This file generated automatically by gl_apitemp.py (from Mesa) script */

/*
 * Copyright (C) 1999-2001  Brian Paul   All Rights Reserved.
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


#  if defined(__GNUC__) || (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590)) && defined(__ELF__)
#    define HIDDEN  __attribute__((visibility("hidden")))
#  else
#    define HIDDEN
#  endif

/*
 * This file is a template which generates the OpenGL API entry point
 * functions.  It should be included by a .c file which first defines
 * the following macros:
 *   KEYWORD1 - usually nothing, but might be __declspec(dllexport) on Win32
 *   KEYWORD2 - usually nothing, but might be __stdcall on Win32
 *   NAME(n)  - builds the final function name (usually add "gl" prefix)
 *   DISPATCH(func, args, msg) - code to do dispatch of named function.
 *                               msg is a printf-style debug message.
 *   RETURN_DISPATCH(func, args, msg) - code to do dispatch with a return value
 *
 * Here is an example which generates the usual OpenGL functions:
 *   #define KEYWORD1
 *   #define KEYWORD2
 *   #define NAME(func)  gl##func
 *   #define DISPATCH(func, args, msg)                           \
 *          struct _glapi_table *dispatch = CurrentDispatch;     \
 *          (*dispatch->func) args
 *   #define RETURN DISPATCH(func, args, msg)                    \
 *          struct _glapi_table *dispatch = CurrentDispatch;     \
 *          return (*dispatch->func) args
 *
 */


#if defined( NAME )
#ifndef KEYWORD1
#define KEYWORD1
#endif

#ifndef KEYWORD1_ALT
#define KEYWORD1_ALT HIDDEN
#endif

#ifndef KEYWORD2
#define KEYWORD2
#endif

#ifndef DISPATCH
#error DISPATCH must be defined
#endif

#ifndef RETURN_DISPATCH
#error RETURN_DISPATCH must be defined
#endif


#ifndef _GLAPI_SKIP_NORMAL_ENTRY_POINTS

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_0)(GLuint list, GLenum mode);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_0)(GLuint list, GLenum mode)
{
   DISPATCH(NewList, (list, mode), (F, "glNewList(%d, 0x%x);\n", list, mode));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_1)(void);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_1)(void)
{
   DISPATCH(EndList, (), (F, "glEndList();\n"));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_2)(GLuint list);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_2)(GLuint list)
{
   DISPATCH(CallList, (list), (F, "glCallList(%d);\n", list));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_3)(GLsizei n, GLenum type, const GLvoid * lists);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_3)(GLsizei n, GLenum type, const GLvoid * lists)
{
   DISPATCH(CallLists, (n, type, lists), (F, "glCallLists(%d, 0x%x, %p);\n", n, type, (const void *) lists));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_4)(GLuint list, GLsizei range);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_4)(GLuint list, GLsizei range)
{
   DISPATCH(DeleteLists, (list, range), (F, "glDeleteLists(%d, %d);\n", list, range));
}

KEYWORD1_ALT GLuint KEYWORD2 NAME(_dispatch_stub_5)(GLsizei range);

KEYWORD1_ALT GLuint KEYWORD2 NAME(_dispatch_stub_5)(GLsizei range)
{
   RETURN_DISPATCH(GenLists, (range), (F, "glGenLists(%d);\n", range));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_6)(GLuint base);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_6)(GLuint base)
{
   DISPATCH(ListBase, (base), (F, "glListBase(%d);\n", base));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_7)(GLenum mode);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_7)(GLenum mode)
{
   DISPATCH(Begin, (mode), (F, "glBegin(0x%x);\n", mode));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_8)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_8)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap)
{
   DISPATCH(Bitmap, (width, height, xorig, yorig, xmove, ymove, bitmap), (F, "glBitmap(%d, %d, %f, %f, %f, %f, %p);\n", width, height, xorig, yorig, xmove, ymove, (const void *) bitmap));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_9)(GLbyte red, GLbyte green, GLbyte blue);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_9)(GLbyte red, GLbyte green, GLbyte blue)
{
   DISPATCH(Color3b, (red, green, blue), (F, "glColor3b(%d, %d, %d);\n", red, green, blue));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_10)(const GLbyte * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_10)(const GLbyte * v)
{
   DISPATCH(Color3bv, (v), (F, "glColor3bv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_11)(GLdouble red, GLdouble green, GLdouble blue);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_11)(GLdouble red, GLdouble green, GLdouble blue)
{
   DISPATCH(Color3d, (red, green, blue), (F, "glColor3d(%f, %f, %f);\n", red, green, blue));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_12)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_12)(const GLdouble * v)
{
   DISPATCH(Color3dv, (v), (F, "glColor3dv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_13)(GLfloat red, GLfloat green, GLfloat blue);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_13)(GLfloat red, GLfloat green, GLfloat blue)
{
   DISPATCH(Color3f, (red, green, blue), (F, "glColor3f(%f, %f, %f);\n", red, green, blue));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_14)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_14)(const GLfloat * v)
{
   DISPATCH(Color3fv, (v), (F, "glColor3fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_15)(GLint red, GLint green, GLint blue);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_15)(GLint red, GLint green, GLint blue)
{
   DISPATCH(Color3i, (red, green, blue), (F, "glColor3i(%d, %d, %d);\n", red, green, blue));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_16)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_16)(const GLint * v)
{
   DISPATCH(Color3iv, (v), (F, "glColor3iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_17)(GLshort red, GLshort green, GLshort blue);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_17)(GLshort red, GLshort green, GLshort blue)
{
   DISPATCH(Color3s, (red, green, blue), (F, "glColor3s(%d, %d, %d);\n", red, green, blue));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_18)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_18)(const GLshort * v)
{
   DISPATCH(Color3sv, (v), (F, "glColor3sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_19)(GLubyte red, GLubyte green, GLubyte blue);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_19)(GLubyte red, GLubyte green, GLubyte blue)
{
   DISPATCH(Color3ub, (red, green, blue), (F, "glColor3ub(%d, %d, %d);\n", red, green, blue));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_20)(const GLubyte * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_20)(const GLubyte * v)
{
   DISPATCH(Color3ubv, (v), (F, "glColor3ubv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_21)(GLuint red, GLuint green, GLuint blue);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_21)(GLuint red, GLuint green, GLuint blue)
{
   DISPATCH(Color3ui, (red, green, blue), (F, "glColor3ui(%d, %d, %d);\n", red, green, blue));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_22)(const GLuint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_22)(const GLuint * v)
{
   DISPATCH(Color3uiv, (v), (F, "glColor3uiv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_23)(GLushort red, GLushort green, GLushort blue);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_23)(GLushort red, GLushort green, GLushort blue)
{
   DISPATCH(Color3us, (red, green, blue), (F, "glColor3us(%d, %d, %d);\n", red, green, blue));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_24)(const GLushort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_24)(const GLushort * v)
{
   DISPATCH(Color3usv, (v), (F, "glColor3usv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_25)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_25)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha)
{
   DISPATCH(Color4b, (red, green, blue, alpha), (F, "glColor4b(%d, %d, %d, %d);\n", red, green, blue, alpha));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_26)(const GLbyte * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_26)(const GLbyte * v)
{
   DISPATCH(Color4bv, (v), (F, "glColor4bv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_27)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_27)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha)
{
   DISPATCH(Color4d, (red, green, blue, alpha), (F, "glColor4d(%f, %f, %f, %f);\n", red, green, blue, alpha));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_28)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_28)(const GLdouble * v)
{
   DISPATCH(Color4dv, (v), (F, "glColor4dv(%p);\n", (const void *) v));
}

KEYWORD1 void KEYWORD2 NAME(Color4f)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
   DISPATCH(Color4f, (red, green, blue, alpha), (F, "glColor4f(%f, %f, %f, %f);\n", red, green, blue, alpha));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_30)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_30)(const GLfloat * v)
{
   DISPATCH(Color4fv, (v), (F, "glColor4fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_31)(GLint red, GLint green, GLint blue, GLint alpha);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_31)(GLint red, GLint green, GLint blue, GLint alpha)
{
   DISPATCH(Color4i, (red, green, blue, alpha), (F, "glColor4i(%d, %d, %d, %d);\n", red, green, blue, alpha));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_32)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_32)(const GLint * v)
{
   DISPATCH(Color4iv, (v), (F, "glColor4iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_33)(GLshort red, GLshort green, GLshort blue, GLshort alpha);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_33)(GLshort red, GLshort green, GLshort blue, GLshort alpha)
{
   DISPATCH(Color4s, (red, green, blue, alpha), (F, "glColor4s(%d, %d, %d, %d);\n", red, green, blue, alpha));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_34)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_34)(const GLshort * v)
{
   DISPATCH(Color4sv, (v), (F, "glColor4sv(%p);\n", (const void *) v));
}

KEYWORD1 void KEYWORD2 NAME(Color4ub)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
   DISPATCH(Color4ub, (red, green, blue, alpha), (F, "glColor4ub(%d, %d, %d, %d);\n", red, green, blue, alpha));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_36)(const GLubyte * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_36)(const GLubyte * v)
{
   DISPATCH(Color4ubv, (v), (F, "glColor4ubv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_37)(GLuint red, GLuint green, GLuint blue, GLuint alpha);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_37)(GLuint red, GLuint green, GLuint blue, GLuint alpha)
{
   DISPATCH(Color4ui, (red, green, blue, alpha), (F, "glColor4ui(%d, %d, %d, %d);\n", red, green, blue, alpha));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_38)(const GLuint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_38)(const GLuint * v)
{
   DISPATCH(Color4uiv, (v), (F, "glColor4uiv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_39)(GLushort red, GLushort green, GLushort blue, GLushort alpha);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_39)(GLushort red, GLushort green, GLushort blue, GLushort alpha)
{
   DISPATCH(Color4us, (red, green, blue, alpha), (F, "glColor4us(%d, %d, %d, %d);\n", red, green, blue, alpha));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_40)(const GLushort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_40)(const GLushort * v)
{
   DISPATCH(Color4usv, (v), (F, "glColor4usv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_41)(GLboolean flag);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_41)(GLboolean flag)
{
   DISPATCH(EdgeFlag, (flag), (F, "glEdgeFlag(%d);\n", flag));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_42)(const GLboolean * flag);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_42)(const GLboolean * flag)
{
   DISPATCH(EdgeFlagv, (flag), (F, "glEdgeFlagv(%p);\n", (const void *) flag));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_43)(void);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_43)(void)
{
   DISPATCH(End, (), (F, "glEnd();\n"));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_44)(GLdouble c);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_44)(GLdouble c)
{
   DISPATCH(Indexd, (c), (F, "glIndexd(%f);\n", c));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_45)(const GLdouble * c);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_45)(const GLdouble * c)
{
   DISPATCH(Indexdv, (c), (F, "glIndexdv(%p);\n", (const void *) c));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_46)(GLfloat c);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_46)(GLfloat c)
{
   DISPATCH(Indexf, (c), (F, "glIndexf(%f);\n", c));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_47)(const GLfloat * c);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_47)(const GLfloat * c)
{
   DISPATCH(Indexfv, (c), (F, "glIndexfv(%p);\n", (const void *) c));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_48)(GLint c);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_48)(GLint c)
{
   DISPATCH(Indexi, (c), (F, "glIndexi(%d);\n", c));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_49)(const GLint * c);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_49)(const GLint * c)
{
   DISPATCH(Indexiv, (c), (F, "glIndexiv(%p);\n", (const void *) c));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_50)(GLshort c);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_50)(GLshort c)
{
   DISPATCH(Indexs, (c), (F, "glIndexs(%d);\n", c));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_51)(const GLshort * c);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_51)(const GLshort * c)
{
   DISPATCH(Indexsv, (c), (F, "glIndexsv(%p);\n", (const void *) c));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_52)(GLbyte nx, GLbyte ny, GLbyte nz);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_52)(GLbyte nx, GLbyte ny, GLbyte nz)
{
   DISPATCH(Normal3b, (nx, ny, nz), (F, "glNormal3b(%d, %d, %d);\n", nx, ny, nz));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_53)(const GLbyte * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_53)(const GLbyte * v)
{
   DISPATCH(Normal3bv, (v), (F, "glNormal3bv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_54)(GLdouble nx, GLdouble ny, GLdouble nz);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_54)(GLdouble nx, GLdouble ny, GLdouble nz)
{
   DISPATCH(Normal3d, (nx, ny, nz), (F, "glNormal3d(%f, %f, %f);\n", nx, ny, nz));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_55)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_55)(const GLdouble * v)
{
   DISPATCH(Normal3dv, (v), (F, "glNormal3dv(%p);\n", (const void *) v));
}

KEYWORD1 void KEYWORD2 NAME(Normal3f)(GLfloat nx, GLfloat ny, GLfloat nz)
{
   DISPATCH(Normal3f, (nx, ny, nz), (F, "glNormal3f(%f, %f, %f);\n", nx, ny, nz));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_57)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_57)(const GLfloat * v)
{
   DISPATCH(Normal3fv, (v), (F, "glNormal3fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_58)(GLint nx, GLint ny, GLint nz);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_58)(GLint nx, GLint ny, GLint nz)
{
   DISPATCH(Normal3i, (nx, ny, nz), (F, "glNormal3i(%d, %d, %d);\n", nx, ny, nz));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_59)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_59)(const GLint * v)
{
   DISPATCH(Normal3iv, (v), (F, "glNormal3iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_60)(GLshort nx, GLshort ny, GLshort nz);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_60)(GLshort nx, GLshort ny, GLshort nz)
{
   DISPATCH(Normal3s, (nx, ny, nz), (F, "glNormal3s(%d, %d, %d);\n", nx, ny, nz));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_61)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_61)(const GLshort * v)
{
   DISPATCH(Normal3sv, (v), (F, "glNormal3sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_62)(GLdouble x, GLdouble y);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_62)(GLdouble x, GLdouble y)
{
   DISPATCH(RasterPos2d, (x, y), (F, "glRasterPos2d(%f, %f);\n", x, y));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_63)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_63)(const GLdouble * v)
{
   DISPATCH(RasterPos2dv, (v), (F, "glRasterPos2dv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_64)(GLfloat x, GLfloat y);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_64)(GLfloat x, GLfloat y)
{
   DISPATCH(RasterPos2f, (x, y), (F, "glRasterPos2f(%f, %f);\n", x, y));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_65)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_65)(const GLfloat * v)
{
   DISPATCH(RasterPos2fv, (v), (F, "glRasterPos2fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_66)(GLint x, GLint y);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_66)(GLint x, GLint y)
{
   DISPATCH(RasterPos2i, (x, y), (F, "glRasterPos2i(%d, %d);\n", x, y));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_67)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_67)(const GLint * v)
{
   DISPATCH(RasterPos2iv, (v), (F, "glRasterPos2iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_68)(GLshort x, GLshort y);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_68)(GLshort x, GLshort y)
{
   DISPATCH(RasterPos2s, (x, y), (F, "glRasterPos2s(%d, %d);\n", x, y));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_69)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_69)(const GLshort * v)
{
   DISPATCH(RasterPos2sv, (v), (F, "glRasterPos2sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_70)(GLdouble x, GLdouble y, GLdouble z);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_70)(GLdouble x, GLdouble y, GLdouble z)
{
   DISPATCH(RasterPos3d, (x, y, z), (F, "glRasterPos3d(%f, %f, %f);\n", x, y, z));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_71)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_71)(const GLdouble * v)
{
   DISPATCH(RasterPos3dv, (v), (F, "glRasterPos3dv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_72)(GLfloat x, GLfloat y, GLfloat z);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_72)(GLfloat x, GLfloat y, GLfloat z)
{
   DISPATCH(RasterPos3f, (x, y, z), (F, "glRasterPos3f(%f, %f, %f);\n", x, y, z));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_73)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_73)(const GLfloat * v)
{
   DISPATCH(RasterPos3fv, (v), (F, "glRasterPos3fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_74)(GLint x, GLint y, GLint z);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_74)(GLint x, GLint y, GLint z)
{
   DISPATCH(RasterPos3i, (x, y, z), (F, "glRasterPos3i(%d, %d, %d);\n", x, y, z));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_75)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_75)(const GLint * v)
{
   DISPATCH(RasterPos3iv, (v), (F, "glRasterPos3iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_76)(GLshort x, GLshort y, GLshort z);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_76)(GLshort x, GLshort y, GLshort z)
{
   DISPATCH(RasterPos3s, (x, y, z), (F, "glRasterPos3s(%d, %d, %d);\n", x, y, z));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_77)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_77)(const GLshort * v)
{
   DISPATCH(RasterPos3sv, (v), (F, "glRasterPos3sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_78)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_78)(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
   DISPATCH(RasterPos4d, (x, y, z, w), (F, "glRasterPos4d(%f, %f, %f, %f);\n", x, y, z, w));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_79)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_79)(const GLdouble * v)
{
   DISPATCH(RasterPos4dv, (v), (F, "glRasterPos4dv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_80)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_80)(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
   DISPATCH(RasterPos4f, (x, y, z, w), (F, "glRasterPos4f(%f, %f, %f, %f);\n", x, y, z, w));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_81)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_81)(const GLfloat * v)
{
   DISPATCH(RasterPos4fv, (v), (F, "glRasterPos4fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_82)(GLint x, GLint y, GLint z, GLint w);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_82)(GLint x, GLint y, GLint z, GLint w)
{
   DISPATCH(RasterPos4i, (x, y, z, w), (F, "glRasterPos4i(%d, %d, %d, %d);\n", x, y, z, w));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_83)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_83)(const GLint * v)
{
   DISPATCH(RasterPos4iv, (v), (F, "glRasterPos4iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_84)(GLshort x, GLshort y, GLshort z, GLshort w);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_84)(GLshort x, GLshort y, GLshort z, GLshort w)
{
   DISPATCH(RasterPos4s, (x, y, z, w), (F, "glRasterPos4s(%d, %d, %d, %d);\n", x, y, z, w));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_85)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_85)(const GLshort * v)
{
   DISPATCH(RasterPos4sv, (v), (F, "glRasterPos4sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_86)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_86)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
   DISPATCH(Rectd, (x1, y1, x2, y2), (F, "glRectd(%f, %f, %f, %f);\n", x1, y1, x2, y2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_87)(const GLdouble * v1, const GLdouble * v2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_87)(const GLdouble * v1, const GLdouble * v2)
{
   DISPATCH(Rectdv, (v1, v2), (F, "glRectdv(%p, %p);\n", (const void *) v1, (const void *) v2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_88)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_88)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
   DISPATCH(Rectf, (x1, y1, x2, y2), (F, "glRectf(%f, %f, %f, %f);\n", x1, y1, x2, y2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_89)(const GLfloat * v1, const GLfloat * v2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_89)(const GLfloat * v1, const GLfloat * v2)
{
   DISPATCH(Rectfv, (v1, v2), (F, "glRectfv(%p, %p);\n", (const void *) v1, (const void *) v2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_90)(GLint x1, GLint y1, GLint x2, GLint y2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_90)(GLint x1, GLint y1, GLint x2, GLint y2)
{
   DISPATCH(Recti, (x1, y1, x2, y2), (F, "glRecti(%d, %d, %d, %d);\n", x1, y1, x2, y2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_91)(const GLint * v1, const GLint * v2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_91)(const GLint * v1, const GLint * v2)
{
   DISPATCH(Rectiv, (v1, v2), (F, "glRectiv(%p, %p);\n", (const void *) v1, (const void *) v2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_92)(GLshort x1, GLshort y1, GLshort x2, GLshort y2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_92)(GLshort x1, GLshort y1, GLshort x2, GLshort y2)
{
   DISPATCH(Rects, (x1, y1, x2, y2), (F, "glRects(%d, %d, %d, %d);\n", x1, y1, x2, y2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_93)(const GLshort * v1, const GLshort * v2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_93)(const GLshort * v1, const GLshort * v2)
{
   DISPATCH(Rectsv, (v1, v2), (F, "glRectsv(%p, %p);\n", (const void *) v1, (const void *) v2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_94)(GLdouble s);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_94)(GLdouble s)
{
   DISPATCH(TexCoord1d, (s), (F, "glTexCoord1d(%f);\n", s));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_95)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_95)(const GLdouble * v)
{
   DISPATCH(TexCoord1dv, (v), (F, "glTexCoord1dv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_96)(GLfloat s);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_96)(GLfloat s)
{
   DISPATCH(TexCoord1f, (s), (F, "glTexCoord1f(%f);\n", s));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_97)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_97)(const GLfloat * v)
{
   DISPATCH(TexCoord1fv, (v), (F, "glTexCoord1fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_98)(GLint s);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_98)(GLint s)
{
   DISPATCH(TexCoord1i, (s), (F, "glTexCoord1i(%d);\n", s));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_99)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_99)(const GLint * v)
{
   DISPATCH(TexCoord1iv, (v), (F, "glTexCoord1iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_100)(GLshort s);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_100)(GLshort s)
{
   DISPATCH(TexCoord1s, (s), (F, "glTexCoord1s(%d);\n", s));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_101)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_101)(const GLshort * v)
{
   DISPATCH(TexCoord1sv, (v), (F, "glTexCoord1sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_102)(GLdouble s, GLdouble t);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_102)(GLdouble s, GLdouble t)
{
   DISPATCH(TexCoord2d, (s, t), (F, "glTexCoord2d(%f, %f);\n", s, t));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_103)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_103)(const GLdouble * v)
{
   DISPATCH(TexCoord2dv, (v), (F, "glTexCoord2dv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_104)(GLfloat s, GLfloat t);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_104)(GLfloat s, GLfloat t)
{
   DISPATCH(TexCoord2f, (s, t), (F, "glTexCoord2f(%f, %f);\n", s, t));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_105)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_105)(const GLfloat * v)
{
   DISPATCH(TexCoord2fv, (v), (F, "glTexCoord2fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_106)(GLint s, GLint t);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_106)(GLint s, GLint t)
{
   DISPATCH(TexCoord2i, (s, t), (F, "glTexCoord2i(%d, %d);\n", s, t));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_107)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_107)(const GLint * v)
{
   DISPATCH(TexCoord2iv, (v), (F, "glTexCoord2iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_108)(GLshort s, GLshort t);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_108)(GLshort s, GLshort t)
{
   DISPATCH(TexCoord2s, (s, t), (F, "glTexCoord2s(%d, %d);\n", s, t));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_109)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_109)(const GLshort * v)
{
   DISPATCH(TexCoord2sv, (v), (F, "glTexCoord2sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_110)(GLdouble s, GLdouble t, GLdouble r);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_110)(GLdouble s, GLdouble t, GLdouble r)
{
   DISPATCH(TexCoord3d, (s, t, r), (F, "glTexCoord3d(%f, %f, %f);\n", s, t, r));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_111)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_111)(const GLdouble * v)
{
   DISPATCH(TexCoord3dv, (v), (F, "glTexCoord3dv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_112)(GLfloat s, GLfloat t, GLfloat r);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_112)(GLfloat s, GLfloat t, GLfloat r)
{
   DISPATCH(TexCoord3f, (s, t, r), (F, "glTexCoord3f(%f, %f, %f);\n", s, t, r));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_113)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_113)(const GLfloat * v)
{
   DISPATCH(TexCoord3fv, (v), (F, "glTexCoord3fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_114)(GLint s, GLint t, GLint r);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_114)(GLint s, GLint t, GLint r)
{
   DISPATCH(TexCoord3i, (s, t, r), (F, "glTexCoord3i(%d, %d, %d);\n", s, t, r));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_115)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_115)(const GLint * v)
{
   DISPATCH(TexCoord3iv, (v), (F, "glTexCoord3iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_116)(GLshort s, GLshort t, GLshort r);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_116)(GLshort s, GLshort t, GLshort r)
{
   DISPATCH(TexCoord3s, (s, t, r), (F, "glTexCoord3s(%d, %d, %d);\n", s, t, r));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_117)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_117)(const GLshort * v)
{
   DISPATCH(TexCoord3sv, (v), (F, "glTexCoord3sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_118)(GLdouble s, GLdouble t, GLdouble r, GLdouble q);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_118)(GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
   DISPATCH(TexCoord4d, (s, t, r, q), (F, "glTexCoord4d(%f, %f, %f, %f);\n", s, t, r, q));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_119)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_119)(const GLdouble * v)
{
   DISPATCH(TexCoord4dv, (v), (F, "glTexCoord4dv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_120)(GLfloat s, GLfloat t, GLfloat r, GLfloat q);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_120)(GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
   DISPATCH(TexCoord4f, (s, t, r, q), (F, "glTexCoord4f(%f, %f, %f, %f);\n", s, t, r, q));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_121)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_121)(const GLfloat * v)
{
   DISPATCH(TexCoord4fv, (v), (F, "glTexCoord4fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_122)(GLint s, GLint t, GLint r, GLint q);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_122)(GLint s, GLint t, GLint r, GLint q)
{
   DISPATCH(TexCoord4i, (s, t, r, q), (F, "glTexCoord4i(%d, %d, %d, %d);\n", s, t, r, q));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_123)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_123)(const GLint * v)
{
   DISPATCH(TexCoord4iv, (v), (F, "glTexCoord4iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_124)(GLshort s, GLshort t, GLshort r, GLshort q);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_124)(GLshort s, GLshort t, GLshort r, GLshort q)
{
   DISPATCH(TexCoord4s, (s, t, r, q), (F, "glTexCoord4s(%d, %d, %d, %d);\n", s, t, r, q));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_125)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_125)(const GLshort * v)
{
   DISPATCH(TexCoord4sv, (v), (F, "glTexCoord4sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_126)(GLdouble x, GLdouble y);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_126)(GLdouble x, GLdouble y)
{
   DISPATCH(Vertex2d, (x, y), (F, "glVertex2d(%f, %f);\n", x, y));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_127)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_127)(const GLdouble * v)
{
   DISPATCH(Vertex2dv, (v), (F, "glVertex2dv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_128)(GLfloat x, GLfloat y);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_128)(GLfloat x, GLfloat y)
{
   DISPATCH(Vertex2f, (x, y), (F, "glVertex2f(%f, %f);\n", x, y));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_129)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_129)(const GLfloat * v)
{
   DISPATCH(Vertex2fv, (v), (F, "glVertex2fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_130)(GLint x, GLint y);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_130)(GLint x, GLint y)
{
   DISPATCH(Vertex2i, (x, y), (F, "glVertex2i(%d, %d);\n", x, y));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_131)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_131)(const GLint * v)
{
   DISPATCH(Vertex2iv, (v), (F, "glVertex2iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_132)(GLshort x, GLshort y);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_132)(GLshort x, GLshort y)
{
   DISPATCH(Vertex2s, (x, y), (F, "glVertex2s(%d, %d);\n", x, y));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_133)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_133)(const GLshort * v)
{
   DISPATCH(Vertex2sv, (v), (F, "glVertex2sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_134)(GLdouble x, GLdouble y, GLdouble z);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_134)(GLdouble x, GLdouble y, GLdouble z)
{
   DISPATCH(Vertex3d, (x, y, z), (F, "glVertex3d(%f, %f, %f);\n", x, y, z));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_135)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_135)(const GLdouble * v)
{
   DISPATCH(Vertex3dv, (v), (F, "glVertex3dv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_136)(GLfloat x, GLfloat y, GLfloat z);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_136)(GLfloat x, GLfloat y, GLfloat z)
{
   DISPATCH(Vertex3f, (x, y, z), (F, "glVertex3f(%f, %f, %f);\n", x, y, z));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_137)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_137)(const GLfloat * v)
{
   DISPATCH(Vertex3fv, (v), (F, "glVertex3fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_138)(GLint x, GLint y, GLint z);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_138)(GLint x, GLint y, GLint z)
{
   DISPATCH(Vertex3i, (x, y, z), (F, "glVertex3i(%d, %d, %d);\n", x, y, z));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_139)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_139)(const GLint * v)
{
   DISPATCH(Vertex3iv, (v), (F, "glVertex3iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_140)(GLshort x, GLshort y, GLshort z);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_140)(GLshort x, GLshort y, GLshort z)
{
   DISPATCH(Vertex3s, (x, y, z), (F, "glVertex3s(%d, %d, %d);\n", x, y, z));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_141)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_141)(const GLshort * v)
{
   DISPATCH(Vertex3sv, (v), (F, "glVertex3sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_142)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_142)(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
   DISPATCH(Vertex4d, (x, y, z, w), (F, "glVertex4d(%f, %f, %f, %f);\n", x, y, z, w));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_143)(const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_143)(const GLdouble * v)
{
   DISPATCH(Vertex4dv, (v), (F, "glVertex4dv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_144)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_144)(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
   DISPATCH(Vertex4f, (x, y, z, w), (F, "glVertex4f(%f, %f, %f, %f);\n", x, y, z, w));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_145)(const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_145)(const GLfloat * v)
{
   DISPATCH(Vertex4fv, (v), (F, "glVertex4fv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_146)(GLint x, GLint y, GLint z, GLint w);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_146)(GLint x, GLint y, GLint z, GLint w)
{
   DISPATCH(Vertex4i, (x, y, z, w), (F, "glVertex4i(%d, %d, %d, %d);\n", x, y, z, w));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_147)(const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_147)(const GLint * v)
{
   DISPATCH(Vertex4iv, (v), (F, "glVertex4iv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_148)(GLshort x, GLshort y, GLshort z, GLshort w);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_148)(GLshort x, GLshort y, GLshort z, GLshort w)
{
   DISPATCH(Vertex4s, (x, y, z, w), (F, "glVertex4s(%d, %d, %d, %d);\n", x, y, z, w));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_149)(const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_149)(const GLshort * v)
{
   DISPATCH(Vertex4sv, (v), (F, "glVertex4sv(%p);\n", (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_150)(GLenum plane, const GLdouble * equation);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_150)(GLenum plane, const GLdouble * equation)
{
   DISPATCH(ClipPlane, (plane, equation), (F, "glClipPlane(0x%x, %p);\n", plane, (const void *) equation));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_151)(GLenum face, GLenum mode);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_151)(GLenum face, GLenum mode)
{
   DISPATCH(ColorMaterial, (face, mode), (F, "glColorMaterial(0x%x, 0x%x);\n", face, mode));
}

KEYWORD1 void KEYWORD2 NAME(CullFace)(GLenum mode)
{
   DISPATCH(CullFace, (mode), (F, "glCullFace(0x%x);\n", mode));
}

KEYWORD1 void KEYWORD2 NAME(Fogf)(GLenum pname, GLfloat param)
{
   DISPATCH(Fogf, (pname, param), (F, "glFogf(0x%x, %f);\n", pname, param));
}

KEYWORD1 void KEYWORD2 NAME(Fogfv)(GLenum pname, const GLfloat * params)
{
   DISPATCH(Fogfv, (pname, params), (F, "glFogfv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_155)(GLenum pname, GLint param);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_155)(GLenum pname, GLint param)
{
   DISPATCH(Fogi, (pname, param), (F, "glFogi(0x%x, %d);\n", pname, param));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_156)(GLenum pname, const GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_156)(GLenum pname, const GLint * params)
{
   DISPATCH(Fogiv, (pname, params), (F, "glFogiv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(FrontFace)(GLenum mode)
{
   DISPATCH(FrontFace, (mode), (F, "glFrontFace(0x%x);\n", mode));
}

KEYWORD1 void KEYWORD2 NAME(Hint)(GLenum target, GLenum mode)
{
   DISPATCH(Hint, (target, mode), (F, "glHint(0x%x, 0x%x);\n", target, mode));
}

KEYWORD1 void KEYWORD2 NAME(Lightf)(GLenum light, GLenum pname, GLfloat param)
{
   DISPATCH(Lightf, (light, pname, param), (F, "glLightf(0x%x, 0x%x, %f);\n", light, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(Lightfv)(GLenum light, GLenum pname, const GLfloat * params)
{
   DISPATCH(Lightfv, (light, pname, params), (F, "glLightfv(0x%x, 0x%x, %p);\n", light, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_161)(GLenum light, GLenum pname, GLint param);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_161)(GLenum light, GLenum pname, GLint param)
{
   DISPATCH(Lighti, (light, pname, param), (F, "glLighti(0x%x, 0x%x, %d);\n", light, pname, param));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_162)(GLenum light, GLenum pname, const GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_162)(GLenum light, GLenum pname, const GLint * params)
{
   DISPATCH(Lightiv, (light, pname, params), (F, "glLightiv(0x%x, 0x%x, %p);\n", light, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(LightModelf)(GLenum pname, GLfloat param)
{
   DISPATCH(LightModelf, (pname, param), (F, "glLightModelf(0x%x, %f);\n", pname, param));
}

KEYWORD1 void KEYWORD2 NAME(LightModelfv)(GLenum pname, const GLfloat * params)
{
   DISPATCH(LightModelfv, (pname, params), (F, "glLightModelfv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_165)(GLenum pname, GLint param);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_165)(GLenum pname, GLint param)
{
   DISPATCH(LightModeli, (pname, param), (F, "glLightModeli(0x%x, %d);\n", pname, param));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_166)(GLenum pname, const GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_166)(GLenum pname, const GLint * params)
{
   DISPATCH(LightModeliv, (pname, params), (F, "glLightModeliv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_167)(GLint factor, GLushort pattern);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_167)(GLint factor, GLushort pattern)
{
   DISPATCH(LineStipple, (factor, pattern), (F, "glLineStipple(%d, %d);\n", factor, pattern));
}

KEYWORD1 void KEYWORD2 NAME(LineWidth)(GLfloat width)
{
   DISPATCH(LineWidth, (width), (F, "glLineWidth(%f);\n", width));
}

KEYWORD1 void KEYWORD2 NAME(Materialf)(GLenum face, GLenum pname, GLfloat param)
{
   DISPATCH(Materialf, (face, pname, param), (F, "glMaterialf(0x%x, 0x%x, %f);\n", face, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(Materialfv)(GLenum face, GLenum pname, const GLfloat * params)
{
   DISPATCH(Materialfv, (face, pname, params), (F, "glMaterialfv(0x%x, 0x%x, %p);\n", face, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_171)(GLenum face, GLenum pname, GLint param);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_171)(GLenum face, GLenum pname, GLint param)
{
   DISPATCH(Materiali, (face, pname, param), (F, "glMateriali(0x%x, 0x%x, %d);\n", face, pname, param));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_172)(GLenum face, GLenum pname, const GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_172)(GLenum face, GLenum pname, const GLint * params)
{
   DISPATCH(Materialiv, (face, pname, params), (F, "glMaterialiv(0x%x, 0x%x, %p);\n", face, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(PointSize)(GLfloat size)
{
   DISPATCH(PointSize, (size), (F, "glPointSize(%f);\n", size));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_174)(GLenum face, GLenum mode);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_174)(GLenum face, GLenum mode)
{
   DISPATCH(PolygonMode, (face, mode), (F, "glPolygonMode(0x%x, 0x%x);\n", face, mode));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_175)(const GLubyte * mask);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_175)(const GLubyte * mask)
{
   DISPATCH(PolygonStipple, (mask), (F, "glPolygonStipple(%p);\n", (const void *) mask));
}

KEYWORD1 void KEYWORD2 NAME(Scissor)(GLint x, GLint y, GLsizei width, GLsizei height)
{
   DISPATCH(Scissor, (x, y, width, height), (F, "glScissor(%d, %d, %d, %d);\n", x, y, width, height));
}

KEYWORD1 void KEYWORD2 NAME(ShadeModel)(GLenum mode)
{
   DISPATCH(ShadeModel, (mode), (F, "glShadeModel(0x%x);\n", mode));
}

KEYWORD1 void KEYWORD2 NAME(TexParameterf)(GLenum target, GLenum pname, GLfloat param)
{
   DISPATCH(TexParameterf, (target, pname, param), (F, "glTexParameterf(0x%x, 0x%x, %f);\n", target, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(TexParameterfv)(GLenum target, GLenum pname, const GLfloat * params)
{
   DISPATCH(TexParameterfv, (target, pname, params), (F, "glTexParameterfv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(TexParameteri)(GLenum target, GLenum pname, GLint param)
{
   DISPATCH(TexParameteri, (target, pname, param), (F, "glTexParameteri(0x%x, 0x%x, %d);\n", target, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(TexParameteriv)(GLenum target, GLenum pname, const GLint * params)
{
   DISPATCH(TexParameteriv, (target, pname, params), (F, "glTexParameteriv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_182)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_182)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels)
{
   DISPATCH(TexImage1D, (target, level, internalformat, width, border, format, type, pixels), (F, "glTexImage1D(0x%x, %d, %d, %d, %d, 0x%x, 0x%x, %p);\n", target, level, internalformat, width, border, format, type, (const void *) pixels));
}

KEYWORD1 void KEYWORD2 NAME(TexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels)
{
   DISPATCH(TexImage2D, (target, level, internalformat, width, height, border, format, type, pixels), (F, "glTexImage2D(0x%x, %d, %d, %d, %d, %d, 0x%x, 0x%x, %p);\n", target, level, internalformat, width, height, border, format, type, (const void *) pixels));
}

KEYWORD1 void KEYWORD2 NAME(TexEnvf)(GLenum target, GLenum pname, GLfloat param)
{
   DISPATCH(TexEnvf, (target, pname, param), (F, "glTexEnvf(0x%x, 0x%x, %f);\n", target, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(TexEnvfv)(GLenum target, GLenum pname, const GLfloat * params)
{
   DISPATCH(TexEnvfv, (target, pname, params), (F, "glTexEnvfv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(TexEnvi)(GLenum target, GLenum pname, GLint param)
{
   DISPATCH(TexEnvi, (target, pname, param), (F, "glTexEnvi(0x%x, 0x%x, %d);\n", target, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(TexEnviv)(GLenum target, GLenum pname, const GLint * params)
{
   DISPATCH(TexEnviv, (target, pname, params), (F, "glTexEnviv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_188)(GLenum coord, GLenum pname, GLdouble param);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_188)(GLenum coord, GLenum pname, GLdouble param)
{
   DISPATCH(TexGend, (coord, pname, param), (F, "glTexGend(0x%x, 0x%x, %f);\n", coord, pname, param));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_189)(GLenum coord, GLenum pname, const GLdouble * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_189)(GLenum coord, GLenum pname, const GLdouble * params)
{
   DISPATCH(TexGendv, (coord, pname, params), (F, "glTexGendv(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(TexGenfOES)(GLenum coord, GLenum pname, GLfloat param);

KEYWORD1 void KEYWORD2 NAME(TexGenfOES)(GLenum coord, GLenum pname, GLfloat param)
{
   DISPATCH(TexGenfOES, (coord, pname, param), (F, "glTexGenfOES(0x%x, 0x%x, %f);\n", coord, pname, param));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_190)(GLenum coord, GLenum pname, GLfloat param);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_190)(GLenum coord, GLenum pname, GLfloat param)
{
   DISPATCH(TexGenfOES, (coord, pname, param), (F, "glTexGenf(0x%x, 0x%x, %f);\n", coord, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(TexGenfvOES)(GLenum coord, GLenum pname, const GLfloat * params);

KEYWORD1 void KEYWORD2 NAME(TexGenfvOES)(GLenum coord, GLenum pname, const GLfloat * params)
{
   DISPATCH(TexGenfvOES, (coord, pname, params), (F, "glTexGenfvOES(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_191)(GLenum coord, GLenum pname, const GLfloat * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_191)(GLenum coord, GLenum pname, const GLfloat * params)
{
   DISPATCH(TexGenfvOES, (coord, pname, params), (F, "glTexGenfv(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(TexGeniOES)(GLenum coord, GLenum pname, GLint param);

KEYWORD1 void KEYWORD2 NAME(TexGeniOES)(GLenum coord, GLenum pname, GLint param)
{
   DISPATCH(TexGeniOES, (coord, pname, param), (F, "glTexGeniOES(0x%x, 0x%x, %d);\n", coord, pname, param));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_192)(GLenum coord, GLenum pname, GLint param);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_192)(GLenum coord, GLenum pname, GLint param)
{
   DISPATCH(TexGeniOES, (coord, pname, param), (F, "glTexGeni(0x%x, 0x%x, %d);\n", coord, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(TexGenivOES)(GLenum coord, GLenum pname, const GLint * params);

KEYWORD1 void KEYWORD2 NAME(TexGenivOES)(GLenum coord, GLenum pname, const GLint * params)
{
   DISPATCH(TexGenivOES, (coord, pname, params), (F, "glTexGenivOES(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_193)(GLenum coord, GLenum pname, const GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_193)(GLenum coord, GLenum pname, const GLint * params)
{
   DISPATCH(TexGenivOES, (coord, pname, params), (F, "glTexGeniv(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_194)(GLsizei size, GLenum type, GLfloat * buffer);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_194)(GLsizei size, GLenum type, GLfloat * buffer)
{
   DISPATCH(FeedbackBuffer, (size, type, buffer), (F, "glFeedbackBuffer(%d, 0x%x, %p);\n", size, type, (const void *) buffer));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_195)(GLsizei size, GLuint * buffer);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_195)(GLsizei size, GLuint * buffer)
{
   DISPATCH(SelectBuffer, (size, buffer), (F, "glSelectBuffer(%d, %p);\n", size, (const void *) buffer));
}

KEYWORD1_ALT GLint KEYWORD2 NAME(_dispatch_stub_196)(GLenum mode);

KEYWORD1_ALT GLint KEYWORD2 NAME(_dispatch_stub_196)(GLenum mode)
{
   RETURN_DISPATCH(RenderMode, (mode), (F, "glRenderMode(0x%x);\n", mode));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_197)(void);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_197)(void)
{
   DISPATCH(InitNames, (), (F, "glInitNames();\n"));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_198)(GLuint name);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_198)(GLuint name)
{
   DISPATCH(LoadName, (name), (F, "glLoadName(%d);\n", name));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_199)(GLfloat token);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_199)(GLfloat token)
{
   DISPATCH(PassThrough, (token), (F, "glPassThrough(%f);\n", token));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_200)(void);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_200)(void)
{
   DISPATCH(PopName, (), (F, "glPopName();\n"));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_201)(GLuint name);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_201)(GLuint name)
{
   DISPATCH(PushName, (name), (F, "glPushName(%d);\n", name));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_202)(GLenum mode);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_202)(GLenum mode)
{
   DISPATCH(DrawBuffer, (mode), (F, "glDrawBuffer(0x%x);\n", mode));
}

KEYWORD1 void KEYWORD2 NAME(Clear)(GLbitfield mask)
{
   DISPATCH(Clear, (mask), (F, "glClear(%d);\n", mask));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_204)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_204)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
   DISPATCH(ClearAccum, (red, green, blue, alpha), (F, "glClearAccum(%f, %f, %f, %f);\n", red, green, blue, alpha));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_205)(GLfloat c);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_205)(GLfloat c)
{
   DISPATCH(ClearIndex, (c), (F, "glClearIndex(%f);\n", c));
}

KEYWORD1 void KEYWORD2 NAME(ClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
   DISPATCH(ClearColor, (red, green, blue, alpha), (F, "glClearColor(%f, %f, %f, %f);\n", red, green, blue, alpha));
}

KEYWORD1 void KEYWORD2 NAME(ClearStencil)(GLint s)
{
   DISPATCH(ClearStencil, (s), (F, "glClearStencil(%d);\n", s));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_208)(GLclampd depth);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_208)(GLclampd depth)
{
   DISPATCH(ClearDepth, (depth), (F, "glClearDepth(%f);\n", depth));
}

KEYWORD1 void KEYWORD2 NAME(StencilMask)(GLuint mask)
{
   DISPATCH(StencilMask, (mask), (F, "glStencilMask(%d);\n", mask));
}

KEYWORD1 void KEYWORD2 NAME(ColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
   DISPATCH(ColorMask, (red, green, blue, alpha), (F, "glColorMask(%d, %d, %d, %d);\n", red, green, blue, alpha));
}

KEYWORD1 void KEYWORD2 NAME(DepthMask)(GLboolean flag)
{
   DISPATCH(DepthMask, (flag), (F, "glDepthMask(%d);\n", flag));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_212)(GLuint mask);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_212)(GLuint mask)
{
   DISPATCH(IndexMask, (mask), (F, "glIndexMask(%d);\n", mask));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_213)(GLenum op, GLfloat value);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_213)(GLenum op, GLfloat value)
{
   DISPATCH(Accum, (op, value), (F, "glAccum(0x%x, %f);\n", op, value));
}

KEYWORD1 void KEYWORD2 NAME(Disable)(GLenum cap)
{
   DISPATCH(Disable, (cap), (F, "glDisable(0x%x);\n", cap));
}

KEYWORD1 void KEYWORD2 NAME(Enable)(GLenum cap)
{
   DISPATCH(Enable, (cap), (F, "glEnable(0x%x);\n", cap));
}

KEYWORD1 void KEYWORD2 NAME(Finish)(void)
{
   DISPATCH(Finish, (), (F, "glFinish();\n"));
}

KEYWORD1 void KEYWORD2 NAME(Flush)(void)
{
   DISPATCH(Flush, (), (F, "glFlush();\n"));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_218)(void);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_218)(void)
{
   DISPATCH(PopAttrib, (), (F, "glPopAttrib();\n"));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_219)(GLbitfield mask);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_219)(GLbitfield mask)
{
   DISPATCH(PushAttrib, (mask), (F, "glPushAttrib(%d);\n", mask));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_220)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_220)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points)
{
   DISPATCH(Map1d, (target, u1, u2, stride, order, points), (F, "glMap1d(0x%x, %f, %f, %d, %d, %p);\n", target, u1, u2, stride, order, (const void *) points));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_221)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_221)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points)
{
   DISPATCH(Map1f, (target, u1, u2, stride, order, points), (F, "glMap1f(0x%x, %f, %f, %d, %d, %p);\n", target, u1, u2, stride, order, (const void *) points));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_222)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_222)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points)
{
   DISPATCH(Map2d, (target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points), (F, "glMap2d(0x%x, %f, %f, %d, %d, %f, %f, %d, %d, %p);\n", target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, (const void *) points));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_223)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_223)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points)
{
   DISPATCH(Map2f, (target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points), (F, "glMap2f(0x%x, %f, %f, %d, %d, %f, %f, %d, %d, %p);\n", target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, (const void *) points));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_224)(GLint un, GLdouble u1, GLdouble u2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_224)(GLint un, GLdouble u1, GLdouble u2)
{
   DISPATCH(MapGrid1d, (un, u1, u2), (F, "glMapGrid1d(%d, %f, %f);\n", un, u1, u2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_225)(GLint un, GLfloat u1, GLfloat u2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_225)(GLint un, GLfloat u1, GLfloat u2)
{
   DISPATCH(MapGrid1f, (un, u1, u2), (F, "glMapGrid1f(%d, %f, %f);\n", un, u1, u2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_226)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_226)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2)
{
   DISPATCH(MapGrid2d, (un, u1, u2, vn, v1, v2), (F, "glMapGrid2d(%d, %f, %f, %d, %f, %f);\n", un, u1, u2, vn, v1, v2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_227)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_227)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2)
{
   DISPATCH(MapGrid2f, (un, u1, u2, vn, v1, v2), (F, "glMapGrid2f(%d, %f, %f, %d, %f, %f);\n", un, u1, u2, vn, v1, v2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_228)(GLdouble u);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_228)(GLdouble u)
{
   DISPATCH(EvalCoord1d, (u), (F, "glEvalCoord1d(%f);\n", u));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_229)(const GLdouble * u);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_229)(const GLdouble * u)
{
   DISPATCH(EvalCoord1dv, (u), (F, "glEvalCoord1dv(%p);\n", (const void *) u));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_230)(GLfloat u);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_230)(GLfloat u)
{
   DISPATCH(EvalCoord1f, (u), (F, "glEvalCoord1f(%f);\n", u));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_231)(const GLfloat * u);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_231)(const GLfloat * u)
{
   DISPATCH(EvalCoord1fv, (u), (F, "glEvalCoord1fv(%p);\n", (const void *) u));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_232)(GLdouble u, GLdouble v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_232)(GLdouble u, GLdouble v)
{
   DISPATCH(EvalCoord2d, (u, v), (F, "glEvalCoord2d(%f, %f);\n", u, v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_233)(const GLdouble * u);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_233)(const GLdouble * u)
{
   DISPATCH(EvalCoord2dv, (u), (F, "glEvalCoord2dv(%p);\n", (const void *) u));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_234)(GLfloat u, GLfloat v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_234)(GLfloat u, GLfloat v)
{
   DISPATCH(EvalCoord2f, (u, v), (F, "glEvalCoord2f(%f, %f);\n", u, v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_235)(const GLfloat * u);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_235)(const GLfloat * u)
{
   DISPATCH(EvalCoord2fv, (u), (F, "glEvalCoord2fv(%p);\n", (const void *) u));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_236)(GLenum mode, GLint i1, GLint i2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_236)(GLenum mode, GLint i1, GLint i2)
{
   DISPATCH(EvalMesh1, (mode, i1, i2), (F, "glEvalMesh1(0x%x, %d, %d);\n", mode, i1, i2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_237)(GLint i);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_237)(GLint i)
{
   DISPATCH(EvalPoint1, (i), (F, "glEvalPoint1(%d);\n", i));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_238)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_238)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2)
{
   DISPATCH(EvalMesh2, (mode, i1, i2, j1, j2), (F, "glEvalMesh2(0x%x, %d, %d, %d, %d);\n", mode, i1, i2, j1, j2));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_239)(GLint i, GLint j);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_239)(GLint i, GLint j)
{
   DISPATCH(EvalPoint2, (i, j), (F, "glEvalPoint2(%d, %d);\n", i, j));
}

KEYWORD1 void KEYWORD2 NAME(AlphaFunc)(GLenum func, GLclampf ref)
{
   DISPATCH(AlphaFunc, (func, ref), (F, "glAlphaFunc(0x%x, %f);\n", func, ref));
}

KEYWORD1 void KEYWORD2 NAME(BlendFunc)(GLenum sfactor, GLenum dfactor)
{
   DISPATCH(BlendFunc, (sfactor, dfactor), (F, "glBlendFunc(0x%x, 0x%x);\n", sfactor, dfactor));
}

KEYWORD1 void KEYWORD2 NAME(LogicOp)(GLenum opcode)
{
   DISPATCH(LogicOp, (opcode), (F, "glLogicOp(0x%x);\n", opcode));
}

KEYWORD1 void KEYWORD2 NAME(StencilFunc)(GLenum func, GLint ref, GLuint mask)
{
   DISPATCH(StencilFunc, (func, ref, mask), (F, "glStencilFunc(0x%x, %d, %d);\n", func, ref, mask));
}

KEYWORD1 void KEYWORD2 NAME(StencilOp)(GLenum fail, GLenum zfail, GLenum zpass)
{
   DISPATCH(StencilOp, (fail, zfail, zpass), (F, "glStencilOp(0x%x, 0x%x, 0x%x);\n", fail, zfail, zpass));
}

KEYWORD1 void KEYWORD2 NAME(DepthFunc)(GLenum func)
{
   DISPATCH(DepthFunc, (func), (F, "glDepthFunc(0x%x);\n", func));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_246)(GLfloat xfactor, GLfloat yfactor);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_246)(GLfloat xfactor, GLfloat yfactor)
{
   DISPATCH(PixelZoom, (xfactor, yfactor), (F, "glPixelZoom(%f, %f);\n", xfactor, yfactor));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_247)(GLenum pname, GLfloat param);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_247)(GLenum pname, GLfloat param)
{
   DISPATCH(PixelTransferf, (pname, param), (F, "glPixelTransferf(0x%x, %f);\n", pname, param));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_248)(GLenum pname, GLint param);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_248)(GLenum pname, GLint param)
{
   DISPATCH(PixelTransferi, (pname, param), (F, "glPixelTransferi(0x%x, %d);\n", pname, param));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_249)(GLenum pname, GLfloat param);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_249)(GLenum pname, GLfloat param)
{
   DISPATCH(PixelStoref, (pname, param), (F, "glPixelStoref(0x%x, %f);\n", pname, param));
}

KEYWORD1 void KEYWORD2 NAME(PixelStorei)(GLenum pname, GLint param)
{
   DISPATCH(PixelStorei, (pname, param), (F, "glPixelStorei(0x%x, %d);\n", pname, param));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_251)(GLenum map, GLsizei mapsize, const GLfloat * values);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_251)(GLenum map, GLsizei mapsize, const GLfloat * values)
{
   DISPATCH(PixelMapfv, (map, mapsize, values), (F, "glPixelMapfv(0x%x, %d, %p);\n", map, mapsize, (const void *) values));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_252)(GLenum map, GLsizei mapsize, const GLuint * values);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_252)(GLenum map, GLsizei mapsize, const GLuint * values)
{
   DISPATCH(PixelMapuiv, (map, mapsize, values), (F, "glPixelMapuiv(0x%x, %d, %p);\n", map, mapsize, (const void *) values));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_253)(GLenum map, GLsizei mapsize, const GLushort * values);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_253)(GLenum map, GLsizei mapsize, const GLushort * values)
{
   DISPATCH(PixelMapusv, (map, mapsize, values), (F, "glPixelMapusv(0x%x, %d, %p);\n", map, mapsize, (const void *) values));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_254)(GLenum mode);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_254)(GLenum mode)
{
   DISPATCH(ReadBuffer, (mode), (F, "glReadBuffer(0x%x);\n", mode));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_255)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_255)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type)
{
   DISPATCH(CopyPixels, (x, y, width, height, type), (F, "glCopyPixels(%d, %d, %d, %d, 0x%x);\n", x, y, width, height, type));
}

KEYWORD1 void KEYWORD2 NAME(ReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels)
{
   DISPATCH(ReadPixels, (x, y, width, height, format, type, pixels), (F, "glReadPixels(%d, %d, %d, %d, 0x%x, 0x%x, %p);\n", x, y, width, height, format, type, (const void *) pixels));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_257)(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_257)(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels)
{
   DISPATCH(DrawPixels, (width, height, format, type, pixels), (F, "glDrawPixels(%d, %d, 0x%x, 0x%x, %p);\n", width, height, format, type, (const void *) pixels));
}

KEYWORD1 void KEYWORD2 NAME(GetBooleanv)(GLenum pname, GLboolean * params)
{
   DISPATCH(GetBooleanv, (pname, params), (F, "glGetBooleanv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_259)(GLenum plane, GLdouble * equation);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_259)(GLenum plane, GLdouble * equation)
{
   DISPATCH(GetClipPlane, (plane, equation), (F, "glGetClipPlane(0x%x, %p);\n", plane, (const void *) equation));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_260)(GLenum pname, GLdouble * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_260)(GLenum pname, GLdouble * params)
{
   DISPATCH(GetDoublev, (pname, params), (F, "glGetDoublev(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 GLenum KEYWORD2 NAME(GetError)(void)
{
   RETURN_DISPATCH(GetError, (), (F, "glGetError();\n"));
}

KEYWORD1 void KEYWORD2 NAME(GetFloatv)(GLenum pname, GLfloat * params)
{
   DISPATCH(GetFloatv, (pname, params), (F, "glGetFloatv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetIntegerv)(GLenum pname, GLint * params)
{
   DISPATCH(GetIntegerv, (pname, params), (F, "glGetIntegerv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetLightfv)(GLenum light, GLenum pname, GLfloat * params)
{
   DISPATCH(GetLightfv, (light, pname, params), (F, "glGetLightfv(0x%x, 0x%x, %p);\n", light, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_265)(GLenum light, GLenum pname, GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_265)(GLenum light, GLenum pname, GLint * params)
{
   DISPATCH(GetLightiv, (light, pname, params), (F, "glGetLightiv(0x%x, 0x%x, %p);\n", light, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_266)(GLenum target, GLenum query, GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_266)(GLenum target, GLenum query, GLdouble * v)
{
   DISPATCH(GetMapdv, (target, query, v), (F, "glGetMapdv(0x%x, 0x%x, %p);\n", target, query, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_267)(GLenum target, GLenum query, GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_267)(GLenum target, GLenum query, GLfloat * v)
{
   DISPATCH(GetMapfv, (target, query, v), (F, "glGetMapfv(0x%x, 0x%x, %p);\n", target, query, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_268)(GLenum target, GLenum query, GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_268)(GLenum target, GLenum query, GLint * v)
{
   DISPATCH(GetMapiv, (target, query, v), (F, "glGetMapiv(0x%x, 0x%x, %p);\n", target, query, (const void *) v));
}

KEYWORD1 void KEYWORD2 NAME(GetMaterialfv)(GLenum face, GLenum pname, GLfloat * params)
{
   DISPATCH(GetMaterialfv, (face, pname, params), (F, "glGetMaterialfv(0x%x, 0x%x, %p);\n", face, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_270)(GLenum face, GLenum pname, GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_270)(GLenum face, GLenum pname, GLint * params)
{
   DISPATCH(GetMaterialiv, (face, pname, params), (F, "glGetMaterialiv(0x%x, 0x%x, %p);\n", face, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_271)(GLenum map, GLfloat * values);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_271)(GLenum map, GLfloat * values)
{
   DISPATCH(GetPixelMapfv, (map, values), (F, "glGetPixelMapfv(0x%x, %p);\n", map, (const void *) values));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_272)(GLenum map, GLuint * values);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_272)(GLenum map, GLuint * values)
{
   DISPATCH(GetPixelMapuiv, (map, values), (F, "glGetPixelMapuiv(0x%x, %p);\n", map, (const void *) values));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_273)(GLenum map, GLushort * values);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_273)(GLenum map, GLushort * values)
{
   DISPATCH(GetPixelMapusv, (map, values), (F, "glGetPixelMapusv(0x%x, %p);\n", map, (const void *) values));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_274)(GLubyte * mask);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_274)(GLubyte * mask)
{
   DISPATCH(GetPolygonStipple, (mask), (F, "glGetPolygonStipple(%p);\n", (const void *) mask));
}

KEYWORD1 const GLubyte * KEYWORD2 NAME(GetString)(GLenum name)
{
   RETURN_DISPATCH(GetString, (name), (F, "glGetString(0x%x);\n", name));
}

KEYWORD1 void KEYWORD2 NAME(GetTexEnvfv)(GLenum target, GLenum pname, GLfloat * params)
{
   DISPATCH(GetTexEnvfv, (target, pname, params), (F, "glGetTexEnvfv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetTexEnviv)(GLenum target, GLenum pname, GLint * params)
{
   DISPATCH(GetTexEnviv, (target, pname, params), (F, "glGetTexEnviv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_278)(GLenum coord, GLenum pname, GLdouble * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_278)(GLenum coord, GLenum pname, GLdouble * params)
{
   DISPATCH(GetTexGendv, (coord, pname, params), (F, "glGetTexGendv(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetTexGenfvOES)(GLenum coord, GLenum pname, GLfloat * params);

KEYWORD1 void KEYWORD2 NAME(GetTexGenfvOES)(GLenum coord, GLenum pname, GLfloat * params)
{
   DISPATCH(GetTexGenfvOES, (coord, pname, params), (F, "glGetTexGenfvOES(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_279)(GLenum coord, GLenum pname, GLfloat * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_279)(GLenum coord, GLenum pname, GLfloat * params)
{
   DISPATCH(GetTexGenfvOES, (coord, pname, params), (F, "glGetTexGenfv(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetTexGenivOES)(GLenum coord, GLenum pname, GLint * params);

KEYWORD1 void KEYWORD2 NAME(GetTexGenivOES)(GLenum coord, GLenum pname, GLint * params)
{
   DISPATCH(GetTexGenivOES, (coord, pname, params), (F, "glGetTexGenivOES(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_280)(GLenum coord, GLenum pname, GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_280)(GLenum coord, GLenum pname, GLint * params)
{
   DISPATCH(GetTexGenivOES, (coord, pname, params), (F, "glGetTexGeniv(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_281)(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_281)(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels)
{
   DISPATCH(GetTexImage, (target, level, format, type, pixels), (F, "glGetTexImage(0x%x, %d, 0x%x, 0x%x, %p);\n", target, level, format, type, (const void *) pixels));
}

KEYWORD1 void KEYWORD2 NAME(GetTexParameterfv)(GLenum target, GLenum pname, GLfloat * params)
{
   DISPATCH(GetTexParameterfv, (target, pname, params), (F, "glGetTexParameterfv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetTexParameteriv)(GLenum target, GLenum pname, GLint * params)
{
   DISPATCH(GetTexParameteriv, (target, pname, params), (F, "glGetTexParameteriv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_284)(GLenum target, GLint level, GLenum pname, GLfloat * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_284)(GLenum target, GLint level, GLenum pname, GLfloat * params)
{
   DISPATCH(GetTexLevelParameterfv, (target, level, pname, params), (F, "glGetTexLevelParameterfv(0x%x, %d, 0x%x, %p);\n", target, level, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_285)(GLenum target, GLint level, GLenum pname, GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_285)(GLenum target, GLint level, GLenum pname, GLint * params)
{
   DISPATCH(GetTexLevelParameteriv, (target, level, pname, params), (F, "glGetTexLevelParameteriv(0x%x, %d, 0x%x, %p);\n", target, level, pname, (const void *) params));
}

KEYWORD1 GLboolean KEYWORD2 NAME(IsEnabled)(GLenum cap)
{
   RETURN_DISPATCH(IsEnabled, (cap), (F, "glIsEnabled(0x%x);\n", cap));
}

KEYWORD1_ALT GLboolean KEYWORD2 NAME(_dispatch_stub_287)(GLuint list);

KEYWORD1_ALT GLboolean KEYWORD2 NAME(_dispatch_stub_287)(GLuint list)
{
   RETURN_DISPATCH(IsList, (list), (F, "glIsList(%d);\n", list));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_288)(GLclampd zNear, GLclampd zFar);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_288)(GLclampd zNear, GLclampd zFar)
{
   DISPATCH(DepthRange, (zNear, zFar), (F, "glDepthRange(%f, %f);\n", zNear, zFar));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_289)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_289)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
   DISPATCH(Frustum, (left, right, bottom, top, zNear, zFar), (F, "glFrustum(%f, %f, %f, %f, %f, %f);\n", left, right, bottom, top, zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(LoadIdentity)(void)
{
   DISPATCH(LoadIdentity, (), (F, "glLoadIdentity();\n"));
}

KEYWORD1 void KEYWORD2 NAME(LoadMatrixf)(const GLfloat * m)
{
   DISPATCH(LoadMatrixf, (m), (F, "glLoadMatrixf(%p);\n", (const void *) m));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_292)(const GLdouble * m);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_292)(const GLdouble * m)
{
   DISPATCH(LoadMatrixd, (m), (F, "glLoadMatrixd(%p);\n", (const void *) m));
}

KEYWORD1 void KEYWORD2 NAME(MatrixMode)(GLenum mode)
{
   DISPATCH(MatrixMode, (mode), (F, "glMatrixMode(0x%x);\n", mode));
}

KEYWORD1 void KEYWORD2 NAME(MultMatrixf)(const GLfloat * m)
{
   DISPATCH(MultMatrixf, (m), (F, "glMultMatrixf(%p);\n", (const void *) m));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_295)(const GLdouble * m);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_295)(const GLdouble * m)
{
   DISPATCH(MultMatrixd, (m), (F, "glMultMatrixd(%p);\n", (const void *) m));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_296)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_296)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
   DISPATCH(Ortho, (left, right, bottom, top, zNear, zFar), (F, "glOrtho(%f, %f, %f, %f, %f, %f);\n", left, right, bottom, top, zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(PopMatrix)(void)
{
   DISPATCH(PopMatrix, (), (F, "glPopMatrix();\n"));
}

KEYWORD1 void KEYWORD2 NAME(PushMatrix)(void)
{
   DISPATCH(PushMatrix, (), (F, "glPushMatrix();\n"));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_299)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_299)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
   DISPATCH(Rotated, (angle, x, y, z), (F, "glRotated(%f, %f, %f, %f);\n", angle, x, y, z));
}

KEYWORD1 void KEYWORD2 NAME(Rotatef)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
   DISPATCH(Rotatef, (angle, x, y, z), (F, "glRotatef(%f, %f, %f, %f);\n", angle, x, y, z));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_301)(GLdouble x, GLdouble y, GLdouble z);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_301)(GLdouble x, GLdouble y, GLdouble z)
{
   DISPATCH(Scaled, (x, y, z), (F, "glScaled(%f, %f, %f);\n", x, y, z));
}

KEYWORD1 void KEYWORD2 NAME(Scalef)(GLfloat x, GLfloat y, GLfloat z)
{
   DISPATCH(Scalef, (x, y, z), (F, "glScalef(%f, %f, %f);\n", x, y, z));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_303)(GLdouble x, GLdouble y, GLdouble z);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_303)(GLdouble x, GLdouble y, GLdouble z)
{
   DISPATCH(Translated, (x, y, z), (F, "glTranslated(%f, %f, %f);\n", x, y, z));
}

KEYWORD1 void KEYWORD2 NAME(Translatef)(GLfloat x, GLfloat y, GLfloat z)
{
   DISPATCH(Translatef, (x, y, z), (F, "glTranslatef(%f, %f, %f);\n", x, y, z));
}

KEYWORD1 void KEYWORD2 NAME(Viewport)(GLint x, GLint y, GLsizei width, GLsizei height)
{
   DISPATCH(Viewport, (x, y, width, height), (F, "glViewport(%d, %d, %d, %d);\n", x, y, width, height));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_306)(GLint i);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_306)(GLint i)
{
   DISPATCH(ArrayElement, (i), (F, "glArrayElement(%d);\n", i));
}

KEYWORD1 void KEYWORD2 NAME(BindTexture)(GLenum target, GLuint texture)
{
   DISPATCH(BindTexture, (target, texture), (F, "glBindTexture(0x%x, %d);\n", target, texture));
}

KEYWORD1 void KEYWORD2 NAME(ColorPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
{
   DISPATCH(ColorPointer, (size, type, stride, pointer), (F, "glColorPointer(%d, 0x%x, %d, %p);\n", size, type, stride, (const void *) pointer));
}

KEYWORD1 void KEYWORD2 NAME(DisableClientState)(GLenum array)
{
   DISPATCH(DisableClientState, (array), (F, "glDisableClientState(0x%x);\n", array));
}

KEYWORD1 void KEYWORD2 NAME(DrawArrays)(GLenum mode, GLint first, GLsizei count)
{
   DISPATCH(DrawArrays, (mode, first, count), (F, "glDrawArrays(0x%x, %d, %d);\n", mode, first, count));
}

KEYWORD1 void KEYWORD2 NAME(DrawElements)(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices)
{
   DISPATCH(DrawElements, (mode, count, type, indices), (F, "glDrawElements(0x%x, %d, 0x%x, %p);\n", mode, count, type, (const void *) indices));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_312)(GLsizei stride, const GLvoid * pointer);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_312)(GLsizei stride, const GLvoid * pointer)
{
   DISPATCH(EdgeFlagPointer, (stride, pointer), (F, "glEdgeFlagPointer(%d, %p);\n", stride, (const void *) pointer));
}

KEYWORD1 void KEYWORD2 NAME(EnableClientState)(GLenum array)
{
   DISPATCH(EnableClientState, (array), (F, "glEnableClientState(0x%x);\n", array));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_314)(GLenum type, GLsizei stride, const GLvoid * pointer);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_314)(GLenum type, GLsizei stride, const GLvoid * pointer)
{
   DISPATCH(IndexPointer, (type, stride, pointer), (F, "glIndexPointer(0x%x, %d, %p);\n", type, stride, (const void *) pointer));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_315)(GLubyte c);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_315)(GLubyte c)
{
   DISPATCH(Indexub, (c), (F, "glIndexub(%d);\n", c));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_316)(const GLubyte * c);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_316)(const GLubyte * c)
{
   DISPATCH(Indexubv, (c), (F, "glIndexubv(%p);\n", (const void *) c));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_317)(GLenum format, GLsizei stride, const GLvoid * pointer);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_317)(GLenum format, GLsizei stride, const GLvoid * pointer)
{
   DISPATCH(InterleavedArrays, (format, stride, pointer), (F, "glInterleavedArrays(0x%x, %d, %p);\n", format, stride, (const void *) pointer));
}

KEYWORD1 void KEYWORD2 NAME(NormalPointer)(GLenum type, GLsizei stride, const GLvoid * pointer)
{
   DISPATCH(NormalPointer, (type, stride, pointer), (F, "glNormalPointer(0x%x, %d, %p);\n", type, stride, (const void *) pointer));
}

KEYWORD1 void KEYWORD2 NAME(PolygonOffset)(GLfloat factor, GLfloat units)
{
   DISPATCH(PolygonOffset, (factor, units), (F, "glPolygonOffset(%f, %f);\n", factor, units));
}

KEYWORD1 void KEYWORD2 NAME(TexCoordPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
{
   DISPATCH(TexCoordPointer, (size, type, stride, pointer), (F, "glTexCoordPointer(%d, 0x%x, %d, %p);\n", size, type, stride, (const void *) pointer));
}

KEYWORD1 void KEYWORD2 NAME(VertexPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
{
   DISPATCH(VertexPointer, (size, type, stride, pointer), (F, "glVertexPointer(%d, 0x%x, %d, %p);\n", size, type, stride, (const void *) pointer));
}

KEYWORD1_ALT GLboolean KEYWORD2 NAME(_dispatch_stub_322)(GLsizei n, const GLuint * textures, GLboolean * residences);

KEYWORD1_ALT GLboolean KEYWORD2 NAME(_dispatch_stub_322)(GLsizei n, const GLuint * textures, GLboolean * residences)
{
   RETURN_DISPATCH(AreTexturesResident, (n, textures, residences), (F, "glAreTexturesResident(%d, %p, %p);\n", n, (const void *) textures, (const void *) residences));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_323)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_323)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
   DISPATCH(CopyTexImage1D, (target, level, internalformat, x, y, width, border), (F, "glCopyTexImage1D(0x%x, %d, 0x%x, %d, %d, %d, %d);\n", target, level, internalformat, x, y, width, border));
}

KEYWORD1 void KEYWORD2 NAME(CopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
   DISPATCH(CopyTexImage2D, (target, level, internalformat, x, y, width, height, border), (F, "glCopyTexImage2D(0x%x, %d, 0x%x, %d, %d, %d, %d, %d);\n", target, level, internalformat, x, y, width, height, border));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_325)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_325)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
   DISPATCH(CopyTexSubImage1D, (target, level, xoffset, x, y, width), (F, "glCopyTexSubImage1D(0x%x, %d, %d, %d, %d, %d);\n", target, level, xoffset, x, y, width));
}

KEYWORD1 void KEYWORD2 NAME(CopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
   DISPATCH(CopyTexSubImage2D, (target, level, xoffset, yoffset, x, y, width, height), (F, "glCopyTexSubImage2D(0x%x, %d, %d, %d, %d, %d, %d, %d);\n", target, level, xoffset, yoffset, x, y, width, height));
}

KEYWORD1 void KEYWORD2 NAME(DeleteTextures)(GLsizei n, const GLuint * textures)
{
   DISPATCH(DeleteTextures, (n, textures), (F, "glDeleteTextures(%d, %p);\n", n, (const void *) textures));
}

KEYWORD1 void KEYWORD2 NAME(GenTextures)(GLsizei n, GLuint * textures)
{
   DISPATCH(GenTextures, (n, textures), (F, "glGenTextures(%d, %p);\n", n, (const void *) textures));
}

KEYWORD1 void KEYWORD2 NAME(GetPointerv)(GLenum pname, GLvoid ** params)
{
   DISPATCH(GetPointerv, (pname, params), (F, "glGetPointerv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 GLboolean KEYWORD2 NAME(IsTexture)(GLuint texture)
{
   RETURN_DISPATCH(IsTexture, (texture), (F, "glIsTexture(%d);\n", texture));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_331)(GLsizei n, const GLuint * textures, const GLclampf * priorities);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_331)(GLsizei n, const GLuint * textures, const GLclampf * priorities)
{
   DISPATCH(PrioritizeTextures, (n, textures, priorities), (F, "glPrioritizeTextures(%d, %p, %p);\n", n, (const void *) textures, (const void *) priorities));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_332)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_332)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels)
{
   DISPATCH(TexSubImage1D, (target, level, xoffset, width, format, type, pixels), (F, "glTexSubImage1D(0x%x, %d, %d, %d, 0x%x, 0x%x, %p);\n", target, level, xoffset, width, format, type, (const void *) pixels));
}

KEYWORD1 void KEYWORD2 NAME(TexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels)
{
   DISPATCH(TexSubImage2D, (target, level, xoffset, yoffset, width, height, format, type, pixels), (F, "glTexSubImage2D(0x%x, %d, %d, %d, %d, %d, 0x%x, 0x%x, %p);\n", target, level, xoffset, yoffset, width, height, format, type, (const void *) pixels));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_334)(void);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_334)(void)
{
   DISPATCH(PopClientAttrib, (), (F, "glPopClientAttrib();\n"));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_335)(GLbitfield mask);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_335)(GLbitfield mask)
{
   DISPATCH(PushClientAttrib, (mask), (F, "glPushClientAttrib(%d);\n", mask));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_336)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_336)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
   DISPATCH(BlendColor, (red, green, blue, alpha), (F, "glBlendColor(%f, %f, %f, %f);\n", red, green, blue, alpha));
}

KEYWORD1 void KEYWORD2 NAME(BlendEquationOES)(GLenum mode);

KEYWORD1 void KEYWORD2 NAME(BlendEquationOES)(GLenum mode)
{
   DISPATCH(BlendEquationOES, (mode), (F, "glBlendEquationOES(0x%x);\n", mode));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_337)(GLenum mode);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_337)(GLenum mode)
{
   DISPATCH(BlendEquationOES, (mode), (F, "glBlendEquation(0x%x);\n", mode));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_338)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_338)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices)
{
   DISPATCH(DrawRangeElements, (mode, start, end, count, type, indices), (F, "glDrawRangeElements(0x%x, %d, %d, %d, 0x%x, %p);\n", mode, start, end, count, type, (const void *) indices));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_339)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * table);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_339)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * table)
{
   DISPATCH(ColorTable, (target, internalformat, width, format, type, table), (F, "glColorTable(0x%x, 0x%x, %d, 0x%x, 0x%x, %p);\n", target, internalformat, width, format, type, (const void *) table));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_340)(GLenum target, GLenum pname, const GLfloat * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_340)(GLenum target, GLenum pname, const GLfloat * params)
{
   DISPATCH(ColorTableParameterfv, (target, pname, params), (F, "glColorTableParameterfv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_341)(GLenum target, GLenum pname, const GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_341)(GLenum target, GLenum pname, const GLint * params)
{
   DISPATCH(ColorTableParameteriv, (target, pname, params), (F, "glColorTableParameteriv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_342)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_342)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
   DISPATCH(CopyColorTable, (target, internalformat, x, y, width), (F, "glCopyColorTable(0x%x, 0x%x, %d, %d, %d);\n", target, internalformat, x, y, width));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_343)(GLenum target, GLenum format, GLenum type, GLvoid * table);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_343)(GLenum target, GLenum format, GLenum type, GLvoid * table)
{
   DISPATCH(GetColorTable, (target, format, type, table), (F, "glGetColorTable(0x%x, 0x%x, 0x%x, %p);\n", target, format, type, (const void *) table));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_344)(GLenum target, GLenum pname, GLfloat * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_344)(GLenum target, GLenum pname, GLfloat * params)
{
   DISPATCH(GetColorTableParameterfv, (target, pname, params), (F, "glGetColorTableParameterfv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_345)(GLenum target, GLenum pname, GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_345)(GLenum target, GLenum pname, GLint * params)
{
   DISPATCH(GetColorTableParameteriv, (target, pname, params), (F, "glGetColorTableParameteriv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_346)(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid * data);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_346)(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid * data)
{
   DISPATCH(ColorSubTable, (target, start, count, format, type, data), (F, "glColorSubTable(0x%x, %d, %d, 0x%x, 0x%x, %p);\n", target, start, count, format, type, (const void *) data));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_347)(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_347)(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width)
{
   DISPATCH(CopyColorSubTable, (target, start, x, y, width), (F, "glCopyColorSubTable(0x%x, %d, %d, %d, %d);\n", target, start, x, y, width));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_348)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * image);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_348)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * image)
{
   DISPATCH(ConvolutionFilter1D, (target, internalformat, width, format, type, image), (F, "glConvolutionFilter1D(0x%x, 0x%x, %d, 0x%x, 0x%x, %p);\n", target, internalformat, width, format, type, (const void *) image));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_349)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * image);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_349)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * image)
{
   DISPATCH(ConvolutionFilter2D, (target, internalformat, width, height, format, type, image), (F, "glConvolutionFilter2D(0x%x, 0x%x, %d, %d, 0x%x, 0x%x, %p);\n", target, internalformat, width, height, format, type, (const void *) image));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_350)(GLenum target, GLenum pname, GLfloat params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_350)(GLenum target, GLenum pname, GLfloat params)
{
   DISPATCH(ConvolutionParameterf, (target, pname, params), (F, "glConvolutionParameterf(0x%x, 0x%x, %f);\n", target, pname, params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_351)(GLenum target, GLenum pname, const GLfloat * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_351)(GLenum target, GLenum pname, const GLfloat * params)
{
   DISPATCH(ConvolutionParameterfv, (target, pname, params), (F, "glConvolutionParameterfv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_352)(GLenum target, GLenum pname, GLint params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_352)(GLenum target, GLenum pname, GLint params)
{
   DISPATCH(ConvolutionParameteri, (target, pname, params), (F, "glConvolutionParameteri(0x%x, 0x%x, %d);\n", target, pname, params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_353)(GLenum target, GLenum pname, const GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_353)(GLenum target, GLenum pname, const GLint * params)
{
   DISPATCH(ConvolutionParameteriv, (target, pname, params), (F, "glConvolutionParameteriv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_354)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_354)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
   DISPATCH(CopyConvolutionFilter1D, (target, internalformat, x, y, width), (F, "glCopyConvolutionFilter1D(0x%x, 0x%x, %d, %d, %d);\n", target, internalformat, x, y, width));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_355)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_355)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
   DISPATCH(CopyConvolutionFilter2D, (target, internalformat, x, y, width, height), (F, "glCopyConvolutionFilter2D(0x%x, 0x%x, %d, %d, %d, %d);\n", target, internalformat, x, y, width, height));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_356)(GLenum target, GLenum format, GLenum type, GLvoid * image);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_356)(GLenum target, GLenum format, GLenum type, GLvoid * image)
{
   DISPATCH(GetConvolutionFilter, (target, format, type, image), (F, "glGetConvolutionFilter(0x%x, 0x%x, 0x%x, %p);\n", target, format, type, (const void *) image));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_357)(GLenum target, GLenum pname, GLfloat * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_357)(GLenum target, GLenum pname, GLfloat * params)
{
   DISPATCH(GetConvolutionParameterfv, (target, pname, params), (F, "glGetConvolutionParameterfv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_358)(GLenum target, GLenum pname, GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_358)(GLenum target, GLenum pname, GLint * params)
{
   DISPATCH(GetConvolutionParameteriv, (target, pname, params), (F, "glGetConvolutionParameteriv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_359)(GLenum target, GLenum format, GLenum type, GLvoid * row, GLvoid * column, GLvoid * span);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_359)(GLenum target, GLenum format, GLenum type, GLvoid * row, GLvoid * column, GLvoid * span)
{
   DISPATCH(GetSeparableFilter, (target, format, type, row, column, span), (F, "glGetSeparableFilter(0x%x, 0x%x, 0x%x, %p, %p, %p);\n", target, format, type, (const void *) row, (const void *) column, (const void *) span));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_360)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * row, const GLvoid * column);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_360)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * row, const GLvoid * column)
{
   DISPATCH(SeparableFilter2D, (target, internalformat, width, height, format, type, row, column), (F, "glSeparableFilter2D(0x%x, 0x%x, %d, %d, 0x%x, 0x%x, %p, %p);\n", target, internalformat, width, height, format, type, (const void *) row, (const void *) column));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_361)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_361)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values)
{
   DISPATCH(GetHistogram, (target, reset, format, type, values), (F, "glGetHistogram(0x%x, %d, 0x%x, 0x%x, %p);\n", target, reset, format, type, (const void *) values));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_362)(GLenum target, GLenum pname, GLfloat * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_362)(GLenum target, GLenum pname, GLfloat * params)
{
   DISPATCH(GetHistogramParameterfv, (target, pname, params), (F, "glGetHistogramParameterfv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_363)(GLenum target, GLenum pname, GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_363)(GLenum target, GLenum pname, GLint * params)
{
   DISPATCH(GetHistogramParameteriv, (target, pname, params), (F, "glGetHistogramParameteriv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_364)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_364)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values)
{
   DISPATCH(GetMinmax, (target, reset, format, type, values), (F, "glGetMinmax(0x%x, %d, 0x%x, 0x%x, %p);\n", target, reset, format, type, (const void *) values));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_365)(GLenum target, GLenum pname, GLfloat * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_365)(GLenum target, GLenum pname, GLfloat * params)
{
   DISPATCH(GetMinmaxParameterfv, (target, pname, params), (F, "glGetMinmaxParameterfv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_366)(GLenum target, GLenum pname, GLint * params);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_366)(GLenum target, GLenum pname, GLint * params)
{
   DISPATCH(GetMinmaxParameteriv, (target, pname, params), (F, "glGetMinmaxParameteriv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_367)(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_367)(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink)
{
   DISPATCH(Histogram, (target, width, internalformat, sink), (F, "glHistogram(0x%x, %d, 0x%x, %d);\n", target, width, internalformat, sink));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_368)(GLenum target, GLenum internalformat, GLboolean sink);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_368)(GLenum target, GLenum internalformat, GLboolean sink)
{
   DISPATCH(Minmax, (target, internalformat, sink), (F, "glMinmax(0x%x, 0x%x, %d);\n", target, internalformat, sink));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_369)(GLenum target);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_369)(GLenum target)
{
   DISPATCH(ResetHistogram, (target), (F, "glResetHistogram(0x%x);\n", target));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_370)(GLenum target);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_370)(GLenum target)
{
   DISPATCH(ResetMinmax, (target), (F, "glResetMinmax(0x%x);\n", target));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_371)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_371)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels)
{
   DISPATCH(TexImage3D, (target, level, internalformat, width, height, depth, border, format, type, pixels), (F, "glTexImage3D(0x%x, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, %p);\n", target, level, internalformat, width, height, depth, border, format, type, (const void *) pixels));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_372)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_372)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels)
{
   DISPATCH(TexSubImage3D, (target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels), (F, "glTexSubImage3D(0x%x, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, %p);\n", target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, (const void *) pixels));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_373)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_373)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
   DISPATCH(CopyTexSubImage3D, (target, level, xoffset, yoffset, zoffset, x, y, width, height), (F, "glCopyTexSubImage3D(0x%x, %d, %d, %d, %d, %d, %d, %d, %d);\n", target, level, xoffset, yoffset, zoffset, x, y, width, height));
}

KEYWORD1 void KEYWORD2 NAME(ActiveTexture)(GLenum texture)
{
   DISPATCH(ActiveTexture, (texture), (F, "glActiveTexture(0x%x);\n", texture));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_374)(GLenum texture);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_374)(GLenum texture)
{
   DISPATCH(ActiveTexture, (texture), (F, "glActiveTextureARB(0x%x);\n", texture));
}

KEYWORD1 void KEYWORD2 NAME(ClientActiveTexture)(GLenum texture)
{
   DISPATCH(ClientActiveTexture, (texture), (F, "glClientActiveTexture(0x%x);\n", texture));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_375)(GLenum texture);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_375)(GLenum texture)
{
   DISPATCH(ClientActiveTexture, (texture), (F, "glClientActiveTextureARB(0x%x);\n", texture));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_376)(GLenum target, GLdouble s);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_376)(GLenum target, GLdouble s)
{
   DISPATCH(MultiTexCoord1dARB, (target, s), (F, "glMultiTexCoord1dARB(0x%x, %f);\n", target, s));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_377)(GLenum target, const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_377)(GLenum target, const GLdouble * v)
{
   DISPATCH(MultiTexCoord1dvARB, (target, v), (F, "glMultiTexCoord1dvARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_378)(GLenum target, GLfloat s);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_378)(GLenum target, GLfloat s)
{
   DISPATCH(MultiTexCoord1fARB, (target, s), (F, "glMultiTexCoord1fARB(0x%x, %f);\n", target, s));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_379)(GLenum target, const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_379)(GLenum target, const GLfloat * v)
{
   DISPATCH(MultiTexCoord1fvARB, (target, v), (F, "glMultiTexCoord1fvARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_380)(GLenum target, GLint s);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_380)(GLenum target, GLint s)
{
   DISPATCH(MultiTexCoord1iARB, (target, s), (F, "glMultiTexCoord1iARB(0x%x, %d);\n", target, s));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_381)(GLenum target, const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_381)(GLenum target, const GLint * v)
{
   DISPATCH(MultiTexCoord1ivARB, (target, v), (F, "glMultiTexCoord1ivARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_382)(GLenum target, GLshort s);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_382)(GLenum target, GLshort s)
{
   DISPATCH(MultiTexCoord1sARB, (target, s), (F, "glMultiTexCoord1sARB(0x%x, %d);\n", target, s));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_383)(GLenum target, const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_383)(GLenum target, const GLshort * v)
{
   DISPATCH(MultiTexCoord1svARB, (target, v), (F, "glMultiTexCoord1svARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_384)(GLenum target, GLdouble s, GLdouble t);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_384)(GLenum target, GLdouble s, GLdouble t)
{
   DISPATCH(MultiTexCoord2dARB, (target, s, t), (F, "glMultiTexCoord2dARB(0x%x, %f, %f);\n", target, s, t));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_385)(GLenum target, const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_385)(GLenum target, const GLdouble * v)
{
   DISPATCH(MultiTexCoord2dvARB, (target, v), (F, "glMultiTexCoord2dvARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_386)(GLenum target, GLfloat s, GLfloat t);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_386)(GLenum target, GLfloat s, GLfloat t)
{
   DISPATCH(MultiTexCoord2fARB, (target, s, t), (F, "glMultiTexCoord2fARB(0x%x, %f, %f);\n", target, s, t));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_387)(GLenum target, const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_387)(GLenum target, const GLfloat * v)
{
   DISPATCH(MultiTexCoord2fvARB, (target, v), (F, "glMultiTexCoord2fvARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_388)(GLenum target, GLint s, GLint t);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_388)(GLenum target, GLint s, GLint t)
{
   DISPATCH(MultiTexCoord2iARB, (target, s, t), (F, "glMultiTexCoord2iARB(0x%x, %d, %d);\n", target, s, t));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_389)(GLenum target, const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_389)(GLenum target, const GLint * v)
{
   DISPATCH(MultiTexCoord2ivARB, (target, v), (F, "glMultiTexCoord2ivARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_390)(GLenum target, GLshort s, GLshort t);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_390)(GLenum target, GLshort s, GLshort t)
{
   DISPATCH(MultiTexCoord2sARB, (target, s, t), (F, "glMultiTexCoord2sARB(0x%x, %d, %d);\n", target, s, t));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_391)(GLenum target, const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_391)(GLenum target, const GLshort * v)
{
   DISPATCH(MultiTexCoord2svARB, (target, v), (F, "glMultiTexCoord2svARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_392)(GLenum target, GLdouble s, GLdouble t, GLdouble r);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_392)(GLenum target, GLdouble s, GLdouble t, GLdouble r)
{
   DISPATCH(MultiTexCoord3dARB, (target, s, t, r), (F, "glMultiTexCoord3dARB(0x%x, %f, %f, %f);\n", target, s, t, r));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_393)(GLenum target, const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_393)(GLenum target, const GLdouble * v)
{
   DISPATCH(MultiTexCoord3dvARB, (target, v), (F, "glMultiTexCoord3dvARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_394)(GLenum target, GLfloat s, GLfloat t, GLfloat r);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_394)(GLenum target, GLfloat s, GLfloat t, GLfloat r)
{
   DISPATCH(MultiTexCoord3fARB, (target, s, t, r), (F, "glMultiTexCoord3fARB(0x%x, %f, %f, %f);\n", target, s, t, r));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_395)(GLenum target, const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_395)(GLenum target, const GLfloat * v)
{
   DISPATCH(MultiTexCoord3fvARB, (target, v), (F, "glMultiTexCoord3fvARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_396)(GLenum target, GLint s, GLint t, GLint r);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_396)(GLenum target, GLint s, GLint t, GLint r)
{
   DISPATCH(MultiTexCoord3iARB, (target, s, t, r), (F, "glMultiTexCoord3iARB(0x%x, %d, %d, %d);\n", target, s, t, r));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_397)(GLenum target, const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_397)(GLenum target, const GLint * v)
{
   DISPATCH(MultiTexCoord3ivARB, (target, v), (F, "glMultiTexCoord3ivARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_398)(GLenum target, GLshort s, GLshort t, GLshort r);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_398)(GLenum target, GLshort s, GLshort t, GLshort r)
{
   DISPATCH(MultiTexCoord3sARB, (target, s, t, r), (F, "glMultiTexCoord3sARB(0x%x, %d, %d, %d);\n", target, s, t, r));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_399)(GLenum target, const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_399)(GLenum target, const GLshort * v)
{
   DISPATCH(MultiTexCoord3svARB, (target, v), (F, "glMultiTexCoord3svARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_400)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_400)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
   DISPATCH(MultiTexCoord4dARB, (target, s, t, r, q), (F, "glMultiTexCoord4dARB(0x%x, %f, %f, %f, %f);\n", target, s, t, r, q));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_401)(GLenum target, const GLdouble * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_401)(GLenum target, const GLdouble * v)
{
   DISPATCH(MultiTexCoord4dvARB, (target, v), (F, "glMultiTexCoord4dvARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1 void KEYWORD2 NAME(MultiTexCoord4f)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
   DISPATCH(MultiTexCoord4f, (target, s, t, r, q), (F, "glMultiTexCoord4f(0x%x, %f, %f, %f, %f);\n", target, s, t, r, q));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_402)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_402)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
   DISPATCH(MultiTexCoord4f, (target, s, t, r, q), (F, "glMultiTexCoord4fARB(0x%x, %f, %f, %f, %f);\n", target, s, t, r, q));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_403)(GLenum target, const GLfloat * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_403)(GLenum target, const GLfloat * v)
{
   DISPATCH(MultiTexCoord4fvARB, (target, v), (F, "glMultiTexCoord4fvARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_404)(GLenum target, GLint s, GLint t, GLint r, GLint q);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_404)(GLenum target, GLint s, GLint t, GLint r, GLint q)
{
   DISPATCH(MultiTexCoord4iARB, (target, s, t, r, q), (F, "glMultiTexCoord4iARB(0x%x, %d, %d, %d, %d);\n", target, s, t, r, q));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_405)(GLenum target, const GLint * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_405)(GLenum target, const GLint * v)
{
   DISPATCH(MultiTexCoord4ivARB, (target, v), (F, "glMultiTexCoord4ivARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_406)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_406)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)
{
   DISPATCH(MultiTexCoord4sARB, (target, s, t, r, q), (F, "glMultiTexCoord4sARB(0x%x, %d, %d, %d, %d);\n", target, s, t, r, q));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_407)(GLenum target, const GLshort * v);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_407)(GLenum target, const GLshort * v)
{
   DISPATCH(MultiTexCoord4svARB, (target, v), (F, "glMultiTexCoord4svARB(0x%x, %p);\n", target, (const void *) v));
}

KEYWORD1 void KEYWORD2 NAME(BlendEquationSeparateOES)(GLenum modeRGB, GLenum modeA);

KEYWORD1 void KEYWORD2 NAME(BlendEquationSeparateOES)(GLenum modeRGB, GLenum modeA)
{
   DISPATCH(BlendEquationSeparateOES, (modeRGB, modeA), (F, "glBlendEquationSeparateOES(0x%x, 0x%x);\n", modeRGB, modeA));
}

KEYWORD1 void KEYWORD2 NAME(BlendFuncSeparateOES)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);

KEYWORD1 void KEYWORD2 NAME(BlendFuncSeparateOES)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
   DISPATCH(BlendFuncSeparateOES, (sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha), (F, "glBlendFuncSeparateOES(0x%x, 0x%x, 0x%x, 0x%x);\n", sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha));
}

KEYWORD1 void KEYWORD2 NAME(DrawTexfOES)(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);

KEYWORD1 void KEYWORD2 NAME(DrawTexfOES)(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height)
{
   DISPATCH(DrawTexfOES, (x, y, z, width, height), (F, "glDrawTexfOES(%f, %f, %f, %f, %f);\n", x, y, z, width, height));
}

KEYWORD1 void KEYWORD2 NAME(DrawTexfvOES)(const GLfloat * coords);

KEYWORD1 void KEYWORD2 NAME(DrawTexfvOES)(const GLfloat * coords)
{
   DISPATCH(DrawTexfvOES, (coords), (F, "glDrawTexfvOES(%p);\n", (const void *) coords));
}

KEYWORD1 void KEYWORD2 NAME(DrawTexiOES)(GLint x, GLint y, GLint z, GLint width, GLint height);

KEYWORD1 void KEYWORD2 NAME(DrawTexiOES)(GLint x, GLint y, GLint z, GLint width, GLint height)
{
   DISPATCH(DrawTexiOES, (x, y, z, width, height), (F, "glDrawTexiOES(%d, %d, %d, %d, %d);\n", x, y, z, width, height));
}

KEYWORD1 void KEYWORD2 NAME(DrawTexivOES)(const GLint * coords);

KEYWORD1 void KEYWORD2 NAME(DrawTexivOES)(const GLint * coords)
{
   DISPATCH(DrawTexivOES, (coords), (F, "glDrawTexivOES(%p);\n", (const void *) coords));
}

KEYWORD1 void KEYWORD2 NAME(DrawTexsOES)(GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);

KEYWORD1 void KEYWORD2 NAME(DrawTexsOES)(GLshort x, GLshort y, GLshort z, GLshort width, GLshort height)
{
   DISPATCH(DrawTexsOES, (x, y, z, width, height), (F, "glDrawTexsOES(%d, %d, %d, %d, %d);\n", x, y, z, width, height));
}

KEYWORD1 void KEYWORD2 NAME(DrawTexsvOES)(const GLshort * coords);

KEYWORD1 void KEYWORD2 NAME(DrawTexsvOES)(const GLshort * coords)
{
   DISPATCH(DrawTexsvOES, (coords), (F, "glDrawTexsvOES(%p);\n", (const void *) coords));
}

KEYWORD1 void KEYWORD2 NAME(DrawTexxOES)(GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);

KEYWORD1 void KEYWORD2 NAME(DrawTexxOES)(GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height)
{
   DISPATCH(DrawTexxOES, (x, y, z, width, height), (F, "glDrawTexxOES(%d, %d, %d, %d, %d);\n", x, y, z, width, height));
}

KEYWORD1 void KEYWORD2 NAME(DrawTexxvOES)(const GLfixed * coords);

KEYWORD1 void KEYWORD2 NAME(DrawTexxvOES)(const GLfixed * coords)
{
   DISPATCH(DrawTexxvOES, (coords), (F, "glDrawTexxvOES(%p);\n", (const void *) coords));
}

KEYWORD1 void KEYWORD2 NAME(BindFramebufferOES)(GLenum target, GLuint framebuffer);

KEYWORD1 void KEYWORD2 NAME(BindFramebufferOES)(GLenum target, GLuint framebuffer)
{
   DISPATCH(BindFramebufferOES, (target, framebuffer), (F, "glBindFramebufferOES(0x%x, %d);\n", target, framebuffer));
}

KEYWORD1 void KEYWORD2 NAME(BindRenderbufferOES)(GLenum target, GLuint renderbuffer);

KEYWORD1 void KEYWORD2 NAME(BindRenderbufferOES)(GLenum target, GLuint renderbuffer)
{
   DISPATCH(BindRenderbufferOES, (target, renderbuffer), (F, "glBindRenderbufferOES(0x%x, %d);\n", target, renderbuffer));
}

KEYWORD1 GLenum KEYWORD2 NAME(CheckFramebufferStatusOES)(GLenum target);

KEYWORD1 GLenum KEYWORD2 NAME(CheckFramebufferStatusOES)(GLenum target)
{
   RETURN_DISPATCH(CheckFramebufferStatusOES, (target), (F, "glCheckFramebufferStatusOES(0x%x);\n", target));
}

KEYWORD1 void KEYWORD2 NAME(DeleteFramebuffersOES)(GLsizei n, const GLuint * framebuffers);

KEYWORD1 void KEYWORD2 NAME(DeleteFramebuffersOES)(GLsizei n, const GLuint * framebuffers)
{
   DISPATCH(DeleteFramebuffersOES, (n, framebuffers), (F, "glDeleteFramebuffersOES(%d, %p);\n", n, (const void *) framebuffers));
}

KEYWORD1 void KEYWORD2 NAME(DeleteRenderbuffersOES)(GLsizei n, const GLuint * renderbuffers);

KEYWORD1 void KEYWORD2 NAME(DeleteRenderbuffersOES)(GLsizei n, const GLuint * renderbuffers)
{
   DISPATCH(DeleteRenderbuffersOES, (n, renderbuffers), (F, "glDeleteRenderbuffersOES(%d, %p);\n", n, (const void *) renderbuffers));
}

KEYWORD1 void KEYWORD2 NAME(FramebufferRenderbufferOES)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);

KEYWORD1 void KEYWORD2 NAME(FramebufferRenderbufferOES)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
   DISPATCH(FramebufferRenderbufferOES, (target, attachment, renderbuffertarget, renderbuffer), (F, "glFramebufferRenderbufferOES(0x%x, 0x%x, 0x%x, %d);\n", target, attachment, renderbuffertarget, renderbuffer));
}

KEYWORD1 void KEYWORD2 NAME(FramebufferTexture2DOES)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);

KEYWORD1 void KEYWORD2 NAME(FramebufferTexture2DOES)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
   DISPATCH(FramebufferTexture2DOES, (target, attachment, textarget, texture, level), (F, "glFramebufferTexture2DOES(0x%x, 0x%x, 0x%x, %d, %d);\n", target, attachment, textarget, texture, level));
}

KEYWORD1 void KEYWORD2 NAME(GenFramebuffersOES)(GLsizei n, GLuint * framebuffers);

KEYWORD1 void KEYWORD2 NAME(GenFramebuffersOES)(GLsizei n, GLuint * framebuffers)
{
   DISPATCH(GenFramebuffersOES, (n, framebuffers), (F, "glGenFramebuffersOES(%d, %p);\n", n, (const void *) framebuffers));
}

KEYWORD1 void KEYWORD2 NAME(GenRenderbuffersOES)(GLsizei n, GLuint * renderbuffers);

KEYWORD1 void KEYWORD2 NAME(GenRenderbuffersOES)(GLsizei n, GLuint * renderbuffers)
{
   DISPATCH(GenRenderbuffersOES, (n, renderbuffers), (F, "glGenRenderbuffersOES(%d, %p);\n", n, (const void *) renderbuffers));
}

KEYWORD1 void KEYWORD2 NAME(GenerateMipmapOES)(GLenum target);

KEYWORD1 void KEYWORD2 NAME(GenerateMipmapOES)(GLenum target)
{
   DISPATCH(GenerateMipmapOES, (target), (F, "glGenerateMipmapOES(0x%x);\n", target));
}

KEYWORD1 void KEYWORD2 NAME(GetFramebufferAttachmentParameterivOES)(GLenum target, GLenum attachment, GLenum pname, GLint * params);

KEYWORD1 void KEYWORD2 NAME(GetFramebufferAttachmentParameterivOES)(GLenum target, GLenum attachment, GLenum pname, GLint * params)
{
   DISPATCH(GetFramebufferAttachmentParameterivOES, (target, attachment, pname, params), (F, "glGetFramebufferAttachmentParameterivOES(0x%x, 0x%x, 0x%x, %p);\n", target, attachment, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetRenderbufferParameterivOES)(GLenum target, GLenum pname, GLint * params);

KEYWORD1 void KEYWORD2 NAME(GetRenderbufferParameterivOES)(GLenum target, GLenum pname, GLint * params)
{
   DISPATCH(GetRenderbufferParameterivOES, (target, pname, params), (F, "glGetRenderbufferParameterivOES(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 GLboolean KEYWORD2 NAME(IsFramebufferOES)(GLuint framebuffer);

KEYWORD1 GLboolean KEYWORD2 NAME(IsFramebufferOES)(GLuint framebuffer)
{
   RETURN_DISPATCH(IsFramebufferOES, (framebuffer), (F, "glIsFramebufferOES(%d);\n", framebuffer));
}

KEYWORD1 GLboolean KEYWORD2 NAME(IsRenderbufferOES)(GLuint renderbuffer);

KEYWORD1 GLboolean KEYWORD2 NAME(IsRenderbufferOES)(GLuint renderbuffer)
{
   RETURN_DISPATCH(IsRenderbufferOES, (renderbuffer), (F, "glIsRenderbufferOES(%d);\n", renderbuffer));
}

KEYWORD1 void KEYWORD2 NAME(RenderbufferStorageOES)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);

KEYWORD1 void KEYWORD2 NAME(RenderbufferStorageOES)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
   DISPATCH(RenderbufferStorageOES, (target, internalformat, width, height), (F, "glRenderbufferStorageOES(0x%x, 0x%x, %d, %d);\n", target, internalformat, width, height));
}

KEYWORD1 void KEYWORD2 NAME(PointSizePointerOES)(GLenum type, GLsizei stride, const GLvoid * pointer);

KEYWORD1 void KEYWORD2 NAME(PointSizePointerOES)(GLenum type, GLsizei stride, const GLvoid * pointer)
{
   DISPATCH(PointSizePointerOES, (type, stride, pointer), (F, "glPointSizePointerOES(0x%x, %d, %p);\n", type, stride, (const void *) pointer));
}

KEYWORD1 GLbitfield KEYWORD2 NAME(QueryMatrixxOES)(GLfixed * mantissa, GLint * exponent);

KEYWORD1 GLbitfield KEYWORD2 NAME(QueryMatrixxOES)(GLfixed * mantissa, GLint * exponent)
{
   RETURN_DISPATCH(QueryMatrixxOES, (mantissa, exponent), (F, "glQueryMatrixxOES(%p, %p);\n", (const void *) mantissa, (const void *) exponent));
}

KEYWORD1 void KEYWORD2 NAME(GetTexGenxvOES)(GLenum coord, GLenum pname, GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(GetTexGenxvOES)(GLenum coord, GLenum pname, GLfixed * params)
{
   DISPATCH(GetTexGenxvOES, (coord, pname, params), (F, "glGetTexGenxvOES(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(TexGenxOES)(GLenum coord, GLenum pname, GLint param);

KEYWORD1 void KEYWORD2 NAME(TexGenxOES)(GLenum coord, GLenum pname, GLint param)
{
   DISPATCH(TexGenxOES, (coord, pname, param), (F, "glTexGenxOES(0x%x, 0x%x, %d);\n", coord, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(TexGenxvOES)(GLenum coord, GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(TexGenxvOES)(GLenum coord, GLenum pname, const GLfixed * params)
{
   DISPATCH(TexGenxvOES, (coord, pname, params), (F, "glTexGenxvOES(0x%x, 0x%x, %p);\n", coord, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetBufferPointervOES)(GLenum target, GLenum pname, GLvoid ** params);

KEYWORD1 void KEYWORD2 NAME(GetBufferPointervOES)(GLenum target, GLenum pname, GLvoid ** params)
{
   DISPATCH(GetBufferPointervOES, (target, pname, params), (F, "glGetBufferPointervOES(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 GLvoid * KEYWORD2 NAME(MapBufferOES)(GLenum target, GLenum access);

KEYWORD1 GLvoid * KEYWORD2 NAME(MapBufferOES)(GLenum target, GLenum access)
{
   RETURN_DISPATCH(MapBufferOES, (target, access), (F, "glMapBufferOES(0x%x, 0x%x);\n", target, access));
}

KEYWORD1 GLboolean KEYWORD2 NAME(UnmapBufferOES)(GLenum target);

KEYWORD1 GLboolean KEYWORD2 NAME(UnmapBufferOES)(GLenum target)
{
   RETURN_DISPATCH(UnmapBufferOES, (target), (F, "glUnmapBufferOES(0x%x);\n", target));
}

KEYWORD1 void KEYWORD2 NAME(MultiDrawArraysEXT)(GLenum mode, const GLint * first, const GLsizei * count, GLsizei primcount)
{
   DISPATCH(MultiDrawArraysEXT, (mode, first, count, primcount), (F, "glMultiDrawArraysEXT(0x%x, %p, %p, %d);\n", mode, (const void *) first, (const void *) count, primcount));
}

KEYWORD1 void KEYWORD2 NAME(MultiDrawElementsEXT)(GLenum mode, const GLsizei * count, GLenum type, const GLvoid ** indices, GLsizei primcount)
{
   DISPATCH(MultiDrawElementsEXT, (mode, count, type, indices, primcount), (F, "glMultiDrawElementsEXT(0x%x, %p, 0x%x, %p, %d);\n", mode, (const void *) count, type, (const void *) indices, primcount));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_443)(GLuint array);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_443)(GLuint array)
{
   DISPATCH(BindVertexArrayAPPLE, (array), (F, "glBindVertexArrayAPPLE(%d);\n", array));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_444)(GLsizei n, const GLuint * arrays);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_444)(GLsizei n, const GLuint * arrays)
{
   DISPATCH(DeleteVertexArraysAPPLE, (n, arrays), (F, "glDeleteVertexArraysAPPLE(%d, %p);\n", n, (const void *) arrays));
}

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_445)(GLsizei n, GLuint * arrays);

KEYWORD1_ALT void KEYWORD2 NAME(_dispatch_stub_445)(GLsizei n, GLuint * arrays)
{
   DISPATCH(GenVertexArraysAPPLE, (n, arrays), (F, "glGenVertexArraysAPPLE(%d, %p);\n", n, (const void *) arrays));
}

KEYWORD1_ALT GLboolean KEYWORD2 NAME(_dispatch_stub_446)(GLuint array);

KEYWORD1_ALT GLboolean KEYWORD2 NAME(_dispatch_stub_446)(GLuint array)
{
   RETURN_DISPATCH(IsVertexArrayAPPLE, (array), (F, "glIsVertexArrayAPPLE(%d);\n", array));
}

KEYWORD1 void KEYWORD2 NAME(EGLImageTargetRenderbufferStorageOES)(GLenum target, GLvoid * writeOffset);

KEYWORD1 void KEYWORD2 NAME(EGLImageTargetRenderbufferStorageOES)(GLenum target, GLvoid * writeOffset)
{
   DISPATCH(EGLImageTargetRenderbufferStorageOES, (target, writeOffset), (F, "glEGLImageTargetRenderbufferStorageOES(0x%x, %p);\n", target, (const void *) writeOffset));
}

KEYWORD1 void KEYWORD2 NAME(EGLImageTargetTexture2DOES)(GLenum target, GLvoid * writeOffset);

KEYWORD1 void KEYWORD2 NAME(EGLImageTargetTexture2DOES)(GLenum target, GLvoid * writeOffset)
{
   DISPATCH(EGLImageTargetTexture2DOES, (target, writeOffset), (F, "glEGLImageTargetTexture2DOES(0x%x, %p);\n", target, (const void *) writeOffset));
}

KEYWORD1 void KEYWORD2 NAME(CompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data)
{
   DISPATCH(CompressedTexImage2D, (target, level, internalformat, width, height, border, imageSize, data), (F, "glCompressedTexImage2D(0x%x, %d, 0x%x, %d, %d, %d, %d, %p);\n", target, level, internalformat, width, height, border, imageSize, (const void *) data));
}

KEYWORD1 void KEYWORD2 NAME(CompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data)
{
   DISPATCH(CompressedTexSubImage2D, (target, level, xoffset, yoffset, width, height, format, imageSize, data), (F, "glCompressedTexSubImage2D(0x%x, %d, %d, %d, %d, %d, 0x%x, %d, %p);\n", target, level, xoffset, yoffset, width, height, format, imageSize, (const void *) data));
}

KEYWORD1 void KEYWORD2 NAME(SampleCoverage)(GLclampf value, GLboolean invert)
{
   DISPATCH(SampleCoverage, (value, invert), (F, "glSampleCoverage(%f, %d);\n", value, invert));
}

KEYWORD1 void KEYWORD2 NAME(BindBuffer)(GLenum target, GLuint buffer)
{
   DISPATCH(BindBuffer, (target, buffer), (F, "glBindBuffer(0x%x, %d);\n", target, buffer));
}

KEYWORD1 void KEYWORD2 NAME(BufferData)(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage)
{
   DISPATCH(BufferData, (target, size, data, usage), (F, "glBufferData(0x%x, %d, %p, 0x%x);\n", target, size, (const void *) data, usage));
}

KEYWORD1 void KEYWORD2 NAME(BufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data)
{
   DISPATCH(BufferSubData, (target, offset, size, data), (F, "glBufferSubData(0x%x, %d, %d, %p);\n", target, offset, size, (const void *) data));
}

KEYWORD1 void KEYWORD2 NAME(DeleteBuffers)(GLsizei n, const GLuint * buffer)
{
   DISPATCH(DeleteBuffers, (n, buffer), (F, "glDeleteBuffers(%d, %p);\n", n, (const void *) buffer));
}

KEYWORD1 void KEYWORD2 NAME(GenBuffers)(GLsizei n, GLuint * buffer)
{
   DISPATCH(GenBuffers, (n, buffer), (F, "glGenBuffers(%d, %p);\n", n, (const void *) buffer));
}

KEYWORD1 void KEYWORD2 NAME(GetBufferParameteriv)(GLenum target, GLenum pname, GLint * params)
{
   DISPATCH(GetBufferParameteriv, (target, pname, params), (F, "glGetBufferParameteriv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 GLboolean KEYWORD2 NAME(IsBuffer)(GLuint buffer)
{
   RETURN_DISPATCH(IsBuffer, (buffer), (F, "glIsBuffer(%d);\n", buffer));
}

KEYWORD1 void KEYWORD2 NAME(PointParameterf)(GLenum pname, GLfloat param)
{
   DISPATCH(PointParameterf, (pname, param), (F, "glPointParameterf(0x%x, %f);\n", pname, param));
}

KEYWORD1 void KEYWORD2 NAME(PointParameterfv)(GLenum pname, const GLfloat * params)
{
   DISPATCH(PointParameterfv, (pname, params), (F, "glPointParameterfv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(AlphaFuncx)(GLenum func, GLclampx ref);

KEYWORD1 void KEYWORD2 NAME(AlphaFuncx)(GLenum func, GLclampx ref)
{
   DISPATCH(AlphaFuncx, (func, ref), (F, "glAlphaFuncx(0x%x, %d);\n", func, ref));
}

KEYWORD1 void KEYWORD2 NAME(AlphaFuncxOES)(GLenum func, GLclampx ref);

KEYWORD1 void KEYWORD2 NAME(AlphaFuncxOES)(GLenum func, GLclampx ref)
{
   DISPATCH(AlphaFuncx, (func, ref), (F, "glAlphaFuncxOES(0x%x, %d);\n", func, ref));
}

KEYWORD1 void KEYWORD2 NAME(ClearColorx)(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);

KEYWORD1 void KEYWORD2 NAME(ClearColorx)(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha)
{
   DISPATCH(ClearColorx, (red, green, blue, alpha), (F, "glClearColorx(%d, %d, %d, %d);\n", red, green, blue, alpha));
}

KEYWORD1 void KEYWORD2 NAME(ClearColorxOES)(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);

KEYWORD1 void KEYWORD2 NAME(ClearColorxOES)(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha)
{
   DISPATCH(ClearColorx, (red, green, blue, alpha), (F, "glClearColorxOES(%d, %d, %d, %d);\n", red, green, blue, alpha));
}

KEYWORD1 void KEYWORD2 NAME(ClearDepthf)(GLclampf depth);

KEYWORD1 void KEYWORD2 NAME(ClearDepthf)(GLclampf depth)
{
   DISPATCH(ClearDepthf, (depth), (F, "glClearDepthf(%f);\n", depth));
}

KEYWORD1 void KEYWORD2 NAME(ClearDepthfOES)(GLclampf depth);

KEYWORD1 void KEYWORD2 NAME(ClearDepthfOES)(GLclampf depth)
{
   DISPATCH(ClearDepthf, (depth), (F, "glClearDepthfOES(%f);\n", depth));
}

KEYWORD1 void KEYWORD2 NAME(ClearDepthx)(GLclampx depth);

KEYWORD1 void KEYWORD2 NAME(ClearDepthx)(GLclampx depth)
{
   DISPATCH(ClearDepthx, (depth), (F, "glClearDepthx(%d);\n", depth));
}

KEYWORD1 void KEYWORD2 NAME(ClearDepthxOES)(GLclampx depth);

KEYWORD1 void KEYWORD2 NAME(ClearDepthxOES)(GLclampx depth)
{
   DISPATCH(ClearDepthx, (depth), (F, "glClearDepthxOES(%d);\n", depth));
}

KEYWORD1 void KEYWORD2 NAME(Color4x)(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);

KEYWORD1 void KEYWORD2 NAME(Color4x)(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
   DISPATCH(Color4x, (red, green, blue, alpha), (F, "glColor4x(%d, %d, %d, %d);\n", red, green, blue, alpha));
}

KEYWORD1 void KEYWORD2 NAME(Color4xOES)(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);

KEYWORD1 void KEYWORD2 NAME(Color4xOES)(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
   DISPATCH(Color4x, (red, green, blue, alpha), (F, "glColor4xOES(%d, %d, %d, %d);\n", red, green, blue, alpha));
}

KEYWORD1 void KEYWORD2 NAME(DepthRangef)(GLclampf zNear, GLclampf zFar);

KEYWORD1 void KEYWORD2 NAME(DepthRangef)(GLclampf zNear, GLclampf zFar)
{
   DISPATCH(DepthRangef, (zNear, zFar), (F, "glDepthRangef(%f, %f);\n", zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(DepthRangefOES)(GLclampf zNear, GLclampf zFar);

KEYWORD1 void KEYWORD2 NAME(DepthRangefOES)(GLclampf zNear, GLclampf zFar)
{
   DISPATCH(DepthRangef, (zNear, zFar), (F, "glDepthRangefOES(%f, %f);\n", zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(DepthRangex)(GLclampx zNear, GLclampx zFar);

KEYWORD1 void KEYWORD2 NAME(DepthRangex)(GLclampx zNear, GLclampx zFar)
{
   DISPATCH(DepthRangex, (zNear, zFar), (F, "glDepthRangex(%d, %d);\n", zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(DepthRangexOES)(GLclampx zNear, GLclampx zFar);

KEYWORD1 void KEYWORD2 NAME(DepthRangexOES)(GLclampx zNear, GLclampx zFar)
{
   DISPATCH(DepthRangex, (zNear, zFar), (F, "glDepthRangexOES(%d, %d);\n", zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(Fogx)(GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(Fogx)(GLenum pname, GLfixed param)
{
   DISPATCH(Fogx, (pname, param), (F, "glFogx(0x%x, %d);\n", pname, param));
}

KEYWORD1 void KEYWORD2 NAME(FogxOES)(GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(FogxOES)(GLenum pname, GLfixed param)
{
   DISPATCH(Fogx, (pname, param), (F, "glFogxOES(0x%x, %d);\n", pname, param));
}

KEYWORD1 void KEYWORD2 NAME(Fogxv)(GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(Fogxv)(GLenum pname, const GLfixed * params)
{
   DISPATCH(Fogxv, (pname, params), (F, "glFogxv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(FogxvOES)(GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(FogxvOES)(GLenum pname, const GLfixed * params)
{
   DISPATCH(Fogxv, (pname, params), (F, "glFogxvOES(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(Frustumf)(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

KEYWORD1 void KEYWORD2 NAME(Frustumf)(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
   DISPATCH(Frustumf, (left, right, bottom, top, zNear, zFar), (F, "glFrustumf(%f, %f, %f, %f, %f, %f);\n", left, right, bottom, top, zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(FrustumfOES)(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

KEYWORD1 void KEYWORD2 NAME(FrustumfOES)(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
   DISPATCH(Frustumf, (left, right, bottom, top, zNear, zFar), (F, "glFrustumfOES(%f, %f, %f, %f, %f, %f);\n", left, right, bottom, top, zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(Frustumx)(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);

KEYWORD1 void KEYWORD2 NAME(Frustumx)(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
   DISPATCH(Frustumx, (left, right, bottom, top, zNear, zFar), (F, "glFrustumx(%d, %d, %d, %d, %d, %d);\n", left, right, bottom, top, zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(FrustumxOES)(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);

KEYWORD1 void KEYWORD2 NAME(FrustumxOES)(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
   DISPATCH(Frustumx, (left, right, bottom, top, zNear, zFar), (F, "glFrustumxOES(%d, %d, %d, %d, %d, %d);\n", left, right, bottom, top, zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(LightModelx)(GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(LightModelx)(GLenum pname, GLfixed param)
{
   DISPATCH(LightModelx, (pname, param), (F, "glLightModelx(0x%x, %d);\n", pname, param));
}

KEYWORD1 void KEYWORD2 NAME(LightModelxOES)(GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(LightModelxOES)(GLenum pname, GLfixed param)
{
   DISPATCH(LightModelx, (pname, param), (F, "glLightModelxOES(0x%x, %d);\n", pname, param));
}

KEYWORD1 void KEYWORD2 NAME(LightModelxv)(GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(LightModelxv)(GLenum pname, const GLfixed * params)
{
   DISPATCH(LightModelxv, (pname, params), (F, "glLightModelxv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(LightModelxvOES)(GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(LightModelxvOES)(GLenum pname, const GLfixed * params)
{
   DISPATCH(LightModelxv, (pname, params), (F, "glLightModelxvOES(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(Lightx)(GLenum light, GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(Lightx)(GLenum light, GLenum pname, GLfixed param)
{
   DISPATCH(Lightx, (light, pname, param), (F, "glLightx(0x%x, 0x%x, %d);\n", light, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(LightxOES)(GLenum light, GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(LightxOES)(GLenum light, GLenum pname, GLfixed param)
{
   DISPATCH(Lightx, (light, pname, param), (F, "glLightxOES(0x%x, 0x%x, %d);\n", light, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(Lightxv)(GLenum light, GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(Lightxv)(GLenum light, GLenum pname, const GLfixed * params)
{
   DISPATCH(Lightxv, (light, pname, params), (F, "glLightxv(0x%x, 0x%x, %p);\n", light, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(LightxvOES)(GLenum light, GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(LightxvOES)(GLenum light, GLenum pname, const GLfixed * params)
{
   DISPATCH(Lightxv, (light, pname, params), (F, "glLightxvOES(0x%x, 0x%x, %p);\n", light, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(LineWidthx)(GLfixed width);

KEYWORD1 void KEYWORD2 NAME(LineWidthx)(GLfixed width)
{
   DISPATCH(LineWidthx, (width), (F, "glLineWidthx(%d);\n", width));
}

KEYWORD1 void KEYWORD2 NAME(LineWidthxOES)(GLfixed width);

KEYWORD1 void KEYWORD2 NAME(LineWidthxOES)(GLfixed width)
{
   DISPATCH(LineWidthx, (width), (F, "glLineWidthxOES(%d);\n", width));
}

KEYWORD1 void KEYWORD2 NAME(LoadMatrixx)(const GLfixed * m);

KEYWORD1 void KEYWORD2 NAME(LoadMatrixx)(const GLfixed * m)
{
   DISPATCH(LoadMatrixx, (m), (F, "glLoadMatrixx(%p);\n", (const void *) m));
}

KEYWORD1 void KEYWORD2 NAME(LoadMatrixxOES)(const GLfixed * m);

KEYWORD1 void KEYWORD2 NAME(LoadMatrixxOES)(const GLfixed * m)
{
   DISPATCH(LoadMatrixx, (m), (F, "glLoadMatrixxOES(%p);\n", (const void *) m));
}

KEYWORD1 void KEYWORD2 NAME(Materialx)(GLenum face, GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(Materialx)(GLenum face, GLenum pname, GLfixed param)
{
   DISPATCH(Materialx, (face, pname, param), (F, "glMaterialx(0x%x, 0x%x, %d);\n", face, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(MaterialxOES)(GLenum face, GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(MaterialxOES)(GLenum face, GLenum pname, GLfixed param)
{
   DISPATCH(Materialx, (face, pname, param), (F, "glMaterialxOES(0x%x, 0x%x, %d);\n", face, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(Materialxv)(GLenum face, GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(Materialxv)(GLenum face, GLenum pname, const GLfixed * params)
{
   DISPATCH(Materialxv, (face, pname, params), (F, "glMaterialxv(0x%x, 0x%x, %p);\n", face, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(MaterialxvOES)(GLenum face, GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(MaterialxvOES)(GLenum face, GLenum pname, const GLfixed * params)
{
   DISPATCH(Materialxv, (face, pname, params), (F, "glMaterialxvOES(0x%x, 0x%x, %p);\n", face, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(MultMatrixx)(const GLfixed * m);

KEYWORD1 void KEYWORD2 NAME(MultMatrixx)(const GLfixed * m)
{
   DISPATCH(MultMatrixx, (m), (F, "glMultMatrixx(%p);\n", (const void *) m));
}

KEYWORD1 void KEYWORD2 NAME(MultMatrixxOES)(const GLfixed * m);

KEYWORD1 void KEYWORD2 NAME(MultMatrixxOES)(const GLfixed * m)
{
   DISPATCH(MultMatrixx, (m), (F, "glMultMatrixxOES(%p);\n", (const void *) m));
}

KEYWORD1 void KEYWORD2 NAME(MultiTexCoord4x)(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);

KEYWORD1 void KEYWORD2 NAME(MultiTexCoord4x)(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q)
{
   DISPATCH(MultiTexCoord4x, (target, s, t, r, q), (F, "glMultiTexCoord4x(0x%x, %d, %d, %d, %d);\n", target, s, t, r, q));
}

KEYWORD1 void KEYWORD2 NAME(MultiTexCoord4xOES)(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);

KEYWORD1 void KEYWORD2 NAME(MultiTexCoord4xOES)(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q)
{
   DISPATCH(MultiTexCoord4x, (target, s, t, r, q), (F, "glMultiTexCoord4xOES(0x%x, %d, %d, %d, %d);\n", target, s, t, r, q));
}

KEYWORD1 void KEYWORD2 NAME(Normal3x)(GLfixed nx, GLfixed ny, GLfixed nz);

KEYWORD1 void KEYWORD2 NAME(Normal3x)(GLfixed nx, GLfixed ny, GLfixed nz)
{
   DISPATCH(Normal3x, (nx, ny, nz), (F, "glNormal3x(%d, %d, %d);\n", nx, ny, nz));
}

KEYWORD1 void KEYWORD2 NAME(Normal3xOES)(GLfixed nx, GLfixed ny, GLfixed nz);

KEYWORD1 void KEYWORD2 NAME(Normal3xOES)(GLfixed nx, GLfixed ny, GLfixed nz)
{
   DISPATCH(Normal3x, (nx, ny, nz), (F, "glNormal3xOES(%d, %d, %d);\n", nx, ny, nz));
}

KEYWORD1 void KEYWORD2 NAME(Orthof)(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

KEYWORD1 void KEYWORD2 NAME(Orthof)(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
   DISPATCH(Orthof, (left, right, bottom, top, zNear, zFar), (F, "glOrthof(%f, %f, %f, %f, %f, %f);\n", left, right, bottom, top, zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(OrthofOES)(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

KEYWORD1 void KEYWORD2 NAME(OrthofOES)(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
   DISPATCH(Orthof, (left, right, bottom, top, zNear, zFar), (F, "glOrthofOES(%f, %f, %f, %f, %f, %f);\n", left, right, bottom, top, zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(Orthox)(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);

KEYWORD1 void KEYWORD2 NAME(Orthox)(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
   DISPATCH(Orthox, (left, right, bottom, top, zNear, zFar), (F, "glOrthox(%d, %d, %d, %d, %d, %d);\n", left, right, bottom, top, zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(OrthoxOES)(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);

KEYWORD1 void KEYWORD2 NAME(OrthoxOES)(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
   DISPATCH(Orthox, (left, right, bottom, top, zNear, zFar), (F, "glOrthoxOES(%d, %d, %d, %d, %d, %d);\n", left, right, bottom, top, zNear, zFar));
}

KEYWORD1 void KEYWORD2 NAME(PointSizex)(GLfixed size);

KEYWORD1 void KEYWORD2 NAME(PointSizex)(GLfixed size)
{
   DISPATCH(PointSizex, (size), (F, "glPointSizex(%d);\n", size));
}

KEYWORD1 void KEYWORD2 NAME(PointSizexOES)(GLfixed size);

KEYWORD1 void KEYWORD2 NAME(PointSizexOES)(GLfixed size)
{
   DISPATCH(PointSizex, (size), (F, "glPointSizexOES(%d);\n", size));
}

KEYWORD1 void KEYWORD2 NAME(PolygonOffsetx)(GLfixed factor, GLfixed units);

KEYWORD1 void KEYWORD2 NAME(PolygonOffsetx)(GLfixed factor, GLfixed units)
{
   DISPATCH(PolygonOffsetx, (factor, units), (F, "glPolygonOffsetx(%d, %d);\n", factor, units));
}

KEYWORD1 void KEYWORD2 NAME(PolygonOffsetxOES)(GLfixed factor, GLfixed units);

KEYWORD1 void KEYWORD2 NAME(PolygonOffsetxOES)(GLfixed factor, GLfixed units)
{
   DISPATCH(PolygonOffsetx, (factor, units), (F, "glPolygonOffsetxOES(%d, %d);\n", factor, units));
}

KEYWORD1 void KEYWORD2 NAME(Rotatex)(GLfixed angle, GLfixed x, GLfixed y, GLfixed z);

KEYWORD1 void KEYWORD2 NAME(Rotatex)(GLfixed angle, GLfixed x, GLfixed y, GLfixed z)
{
   DISPATCH(Rotatex, (angle, x, y, z), (F, "glRotatex(%d, %d, %d, %d);\n", angle, x, y, z));
}

KEYWORD1 void KEYWORD2 NAME(RotatexOES)(GLfixed angle, GLfixed x, GLfixed y, GLfixed z);

KEYWORD1 void KEYWORD2 NAME(RotatexOES)(GLfixed angle, GLfixed x, GLfixed y, GLfixed z)
{
   DISPATCH(Rotatex, (angle, x, y, z), (F, "glRotatexOES(%d, %d, %d, %d);\n", angle, x, y, z));
}

KEYWORD1 void KEYWORD2 NAME(SampleCoveragex)(GLclampx value, GLboolean invert);

KEYWORD1 void KEYWORD2 NAME(SampleCoveragex)(GLclampx value, GLboolean invert)
{
   DISPATCH(SampleCoveragex, (value, invert), (F, "glSampleCoveragex(%d, %d);\n", value, invert));
}

KEYWORD1 void KEYWORD2 NAME(SampleCoveragexOES)(GLclampx value, GLboolean invert);

KEYWORD1 void KEYWORD2 NAME(SampleCoveragexOES)(GLclampx value, GLboolean invert)
{
   DISPATCH(SampleCoveragex, (value, invert), (F, "glSampleCoveragexOES(%d, %d);\n", value, invert));
}

KEYWORD1 void KEYWORD2 NAME(Scalex)(GLfixed x, GLfixed y, GLfixed z);

KEYWORD1 void KEYWORD2 NAME(Scalex)(GLfixed x, GLfixed y, GLfixed z)
{
   DISPATCH(Scalex, (x, y, z), (F, "glScalex(%d, %d, %d);\n", x, y, z));
}

KEYWORD1 void KEYWORD2 NAME(ScalexOES)(GLfixed x, GLfixed y, GLfixed z);

KEYWORD1 void KEYWORD2 NAME(ScalexOES)(GLfixed x, GLfixed y, GLfixed z)
{
   DISPATCH(Scalex, (x, y, z), (F, "glScalexOES(%d, %d, %d);\n", x, y, z));
}

KEYWORD1 void KEYWORD2 NAME(TexEnvx)(GLenum target, GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(TexEnvx)(GLenum target, GLenum pname, GLfixed param)
{
   DISPATCH(TexEnvx, (target, pname, param), (F, "glTexEnvx(0x%x, 0x%x, %d);\n", target, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(TexEnvxOES)(GLenum target, GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(TexEnvxOES)(GLenum target, GLenum pname, GLfixed param)
{
   DISPATCH(TexEnvx, (target, pname, param), (F, "glTexEnvxOES(0x%x, 0x%x, %d);\n", target, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(TexEnvxv)(GLenum target, GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(TexEnvxv)(GLenum target, GLenum pname, const GLfixed * params)
{
   DISPATCH(TexEnvxv, (target, pname, params), (F, "glTexEnvxv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(TexEnvxvOES)(GLenum target, GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(TexEnvxvOES)(GLenum target, GLenum pname, const GLfixed * params)
{
   DISPATCH(TexEnvxv, (target, pname, params), (F, "glTexEnvxvOES(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(TexParameterx)(GLenum target, GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(TexParameterx)(GLenum target, GLenum pname, GLfixed param)
{
   DISPATCH(TexParameterx, (target, pname, param), (F, "glTexParameterx(0x%x, 0x%x, %d);\n", target, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(TexParameterxOES)(GLenum target, GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(TexParameterxOES)(GLenum target, GLenum pname, GLfixed param)
{
   DISPATCH(TexParameterx, (target, pname, param), (F, "glTexParameterxOES(0x%x, 0x%x, %d);\n", target, pname, param));
}

KEYWORD1 void KEYWORD2 NAME(Translatex)(GLfixed x, GLfixed y, GLfixed z);

KEYWORD1 void KEYWORD2 NAME(Translatex)(GLfixed x, GLfixed y, GLfixed z)
{
   DISPATCH(Translatex, (x, y, z), (F, "glTranslatex(%d, %d, %d);\n", x, y, z));
}

KEYWORD1 void KEYWORD2 NAME(TranslatexOES)(GLfixed x, GLfixed y, GLfixed z);

KEYWORD1 void KEYWORD2 NAME(TranslatexOES)(GLfixed x, GLfixed y, GLfixed z)
{
   DISPATCH(Translatex, (x, y, z), (F, "glTranslatexOES(%d, %d, %d);\n", x, y, z));
}

KEYWORD1 void KEYWORD2 NAME(ClipPlanef)(GLenum plane, const GLfloat * equation);

KEYWORD1 void KEYWORD2 NAME(ClipPlanef)(GLenum plane, const GLfloat * equation)
{
   DISPATCH(ClipPlanef, (plane, equation), (F, "glClipPlanef(0x%x, %p);\n", plane, (const void *) equation));
}

KEYWORD1 void KEYWORD2 NAME(ClipPlanefOES)(GLenum plane, const GLfloat * equation);

KEYWORD1 void KEYWORD2 NAME(ClipPlanefOES)(GLenum plane, const GLfloat * equation)
{
   DISPATCH(ClipPlanef, (plane, equation), (F, "glClipPlanefOES(0x%x, %p);\n", plane, (const void *) equation));
}

KEYWORD1 void KEYWORD2 NAME(ClipPlanex)(GLenum plane, const GLfixed * equation);

KEYWORD1 void KEYWORD2 NAME(ClipPlanex)(GLenum plane, const GLfixed * equation)
{
   DISPATCH(ClipPlanex, (plane, equation), (F, "glClipPlanex(0x%x, %p);\n", plane, (const void *) equation));
}

KEYWORD1 void KEYWORD2 NAME(ClipPlanexOES)(GLenum plane, const GLfixed * equation);

KEYWORD1 void KEYWORD2 NAME(ClipPlanexOES)(GLenum plane, const GLfixed * equation)
{
   DISPATCH(ClipPlanex, (plane, equation), (F, "glClipPlanexOES(0x%x, %p);\n", plane, (const void *) equation));
}

KEYWORD1 void KEYWORD2 NAME(GetClipPlanef)(GLenum plane, GLfloat * equation);

KEYWORD1 void KEYWORD2 NAME(GetClipPlanef)(GLenum plane, GLfloat * equation)
{
   DISPATCH(GetClipPlanef, (plane, equation), (F, "glGetClipPlanef(0x%x, %p);\n", plane, (const void *) equation));
}

KEYWORD1 void KEYWORD2 NAME(GetClipPlanefOES)(GLenum plane, GLfloat * equation);

KEYWORD1 void KEYWORD2 NAME(GetClipPlanefOES)(GLenum plane, GLfloat * equation)
{
   DISPATCH(GetClipPlanef, (plane, equation), (F, "glGetClipPlanefOES(0x%x, %p);\n", plane, (const void *) equation));
}

KEYWORD1 void KEYWORD2 NAME(GetClipPlanex)(GLenum plane, GLfixed * equation);

KEYWORD1 void KEYWORD2 NAME(GetClipPlanex)(GLenum plane, GLfixed * equation)
{
   DISPATCH(GetClipPlanex, (plane, equation), (F, "glGetClipPlanex(0x%x, %p);\n", plane, (const void *) equation));
}

KEYWORD1 void KEYWORD2 NAME(GetClipPlanexOES)(GLenum plane, GLfixed * equation);

KEYWORD1 void KEYWORD2 NAME(GetClipPlanexOES)(GLenum plane, GLfixed * equation)
{
   DISPATCH(GetClipPlanex, (plane, equation), (F, "glGetClipPlanexOES(0x%x, %p);\n", plane, (const void *) equation));
}

KEYWORD1 void KEYWORD2 NAME(GetFixedv)(GLenum pname, GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(GetFixedv)(GLenum pname, GLfixed * params)
{
   DISPATCH(GetFixedv, (pname, params), (F, "glGetFixedv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetFixedvOES)(GLenum pname, GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(GetFixedvOES)(GLenum pname, GLfixed * params)
{
   DISPATCH(GetFixedv, (pname, params), (F, "glGetFixedvOES(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetLightxv)(GLenum light, GLenum pname, GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(GetLightxv)(GLenum light, GLenum pname, GLfixed * params)
{
   DISPATCH(GetLightxv, (light, pname, params), (F, "glGetLightxv(0x%x, 0x%x, %p);\n", light, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetLightxvOES)(GLenum light, GLenum pname, GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(GetLightxvOES)(GLenum light, GLenum pname, GLfixed * params)
{
   DISPATCH(GetLightxv, (light, pname, params), (F, "glGetLightxvOES(0x%x, 0x%x, %p);\n", light, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetMaterialxv)(GLenum face, GLenum pname, GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(GetMaterialxv)(GLenum face, GLenum pname, GLfixed * params)
{
   DISPATCH(GetMaterialxv, (face, pname, params), (F, "glGetMaterialxv(0x%x, 0x%x, %p);\n", face, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetMaterialxvOES)(GLenum face, GLenum pname, GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(GetMaterialxvOES)(GLenum face, GLenum pname, GLfixed * params)
{
   DISPATCH(GetMaterialxv, (face, pname, params), (F, "glGetMaterialxvOES(0x%x, 0x%x, %p);\n", face, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetTexEnvxv)(GLenum target, GLenum pname, GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(GetTexEnvxv)(GLenum target, GLenum pname, GLfixed * params)
{
   DISPATCH(GetTexEnvxv, (target, pname, params), (F, "glGetTexEnvxv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetTexEnvxvOES)(GLenum target, GLenum pname, GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(GetTexEnvxvOES)(GLenum target, GLenum pname, GLfixed * params)
{
   DISPATCH(GetTexEnvxv, (target, pname, params), (F, "glGetTexEnvxvOES(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetTexParameterxv)(GLenum target, GLenum pname, GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(GetTexParameterxv)(GLenum target, GLenum pname, GLfixed * params)
{
   DISPATCH(GetTexParameterxv, (target, pname, params), (F, "glGetTexParameterxv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(GetTexParameterxvOES)(GLenum target, GLenum pname, GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(GetTexParameterxvOES)(GLenum target, GLenum pname, GLfixed * params)
{
   DISPATCH(GetTexParameterxv, (target, pname, params), (F, "glGetTexParameterxvOES(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(PointParameterx)(GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(PointParameterx)(GLenum pname, GLfixed param)
{
   DISPATCH(PointParameterx, (pname, param), (F, "glPointParameterx(0x%x, %d);\n", pname, param));
}

KEYWORD1 void KEYWORD2 NAME(PointParameterxOES)(GLenum pname, GLfixed param);

KEYWORD1 void KEYWORD2 NAME(PointParameterxOES)(GLenum pname, GLfixed param)
{
   DISPATCH(PointParameterx, (pname, param), (F, "glPointParameterxOES(0x%x, %d);\n", pname, param));
}

KEYWORD1 void KEYWORD2 NAME(PointParameterxv)(GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(PointParameterxv)(GLenum pname, const GLfixed * params)
{
   DISPATCH(PointParameterxv, (pname, params), (F, "glPointParameterxv(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(PointParameterxvOES)(GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(PointParameterxvOES)(GLenum pname, const GLfixed * params)
{
   DISPATCH(PointParameterxv, (pname, params), (F, "glPointParameterxvOES(0x%x, %p);\n", pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(TexParameterxv)(GLenum target, GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(TexParameterxv)(GLenum target, GLenum pname, const GLfixed * params)
{
   DISPATCH(TexParameterxv, (target, pname, params), (F, "glTexParameterxv(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}

KEYWORD1 void KEYWORD2 NAME(TexParameterxvOES)(GLenum target, GLenum pname, const GLfixed * params);

KEYWORD1 void KEYWORD2 NAME(TexParameterxvOES)(GLenum target, GLenum pname, const GLfixed * params)
{
   DISPATCH(TexParameterxv, (target, pname, params), (F, "glTexParameterxvOES(0x%x, 0x%x, %p);\n", target, pname, (const void *) params));
}


#endif /* _GLAPI_SKIP_NORMAL_ENTRY_POINTS */

/* these entry points might require different protocols */
#ifndef _GLAPI_SKIP_PROTO_ENTRY_POINTS


#endif /* _GLAPI_SKIP_PROTO_ENTRY_POINTS */


#endif /* defined( NAME ) */

/*
 * This is how a dispatch table can be initialized with all the functions
 * we generated above.
 */
#ifdef DISPATCH_TABLE_NAME

#ifndef TABLE_ENTRY
#error TABLE_ENTRY must be defined
#endif

#ifdef _GLAPI_SKIP_NORMAL_ENTRY_POINTS
#error _GLAPI_SKIP_NORMAL_ENTRY_POINTS must not be defined
#endif

_glapi_proc DISPATCH_TABLE_NAME[] = {
   TABLE_ENTRY(_dispatch_stub_0),
   TABLE_ENTRY(_dispatch_stub_1),
   TABLE_ENTRY(_dispatch_stub_2),
   TABLE_ENTRY(_dispatch_stub_3),
   TABLE_ENTRY(_dispatch_stub_4),
   TABLE_ENTRY(_dispatch_stub_5),
   TABLE_ENTRY(_dispatch_stub_6),
   TABLE_ENTRY(_dispatch_stub_7),
   TABLE_ENTRY(_dispatch_stub_8),
   TABLE_ENTRY(_dispatch_stub_9),
   TABLE_ENTRY(_dispatch_stub_10),
   TABLE_ENTRY(_dispatch_stub_11),
   TABLE_ENTRY(_dispatch_stub_12),
   TABLE_ENTRY(_dispatch_stub_13),
   TABLE_ENTRY(_dispatch_stub_14),
   TABLE_ENTRY(_dispatch_stub_15),
   TABLE_ENTRY(_dispatch_stub_16),
   TABLE_ENTRY(_dispatch_stub_17),
   TABLE_ENTRY(_dispatch_stub_18),
   TABLE_ENTRY(_dispatch_stub_19),
   TABLE_ENTRY(_dispatch_stub_20),
   TABLE_ENTRY(_dispatch_stub_21),
   TABLE_ENTRY(_dispatch_stub_22),
   TABLE_ENTRY(_dispatch_stub_23),
   TABLE_ENTRY(_dispatch_stub_24),
   TABLE_ENTRY(_dispatch_stub_25),
   TABLE_ENTRY(_dispatch_stub_26),
   TABLE_ENTRY(_dispatch_stub_27),
   TABLE_ENTRY(_dispatch_stub_28),
   TABLE_ENTRY(Color4f),
   TABLE_ENTRY(_dispatch_stub_30),
   TABLE_ENTRY(_dispatch_stub_31),
   TABLE_ENTRY(_dispatch_stub_32),
   TABLE_ENTRY(_dispatch_stub_33),
   TABLE_ENTRY(_dispatch_stub_34),
   TABLE_ENTRY(Color4ub),
   TABLE_ENTRY(_dispatch_stub_36),
   TABLE_ENTRY(_dispatch_stub_37),
   TABLE_ENTRY(_dispatch_stub_38),
   TABLE_ENTRY(_dispatch_stub_39),
   TABLE_ENTRY(_dispatch_stub_40),
   TABLE_ENTRY(_dispatch_stub_41),
   TABLE_ENTRY(_dispatch_stub_42),
   TABLE_ENTRY(_dispatch_stub_43),
   TABLE_ENTRY(_dispatch_stub_44),
   TABLE_ENTRY(_dispatch_stub_45),
   TABLE_ENTRY(_dispatch_stub_46),
   TABLE_ENTRY(_dispatch_stub_47),
   TABLE_ENTRY(_dispatch_stub_48),
   TABLE_ENTRY(_dispatch_stub_49),
   TABLE_ENTRY(_dispatch_stub_50),
   TABLE_ENTRY(_dispatch_stub_51),
   TABLE_ENTRY(_dispatch_stub_52),
   TABLE_ENTRY(_dispatch_stub_53),
   TABLE_ENTRY(_dispatch_stub_54),
   TABLE_ENTRY(_dispatch_stub_55),
   TABLE_ENTRY(Normal3f),
   TABLE_ENTRY(_dispatch_stub_57),
   TABLE_ENTRY(_dispatch_stub_58),
   TABLE_ENTRY(_dispatch_stub_59),
   TABLE_ENTRY(_dispatch_stub_60),
   TABLE_ENTRY(_dispatch_stub_61),
   TABLE_ENTRY(_dispatch_stub_62),
   TABLE_ENTRY(_dispatch_stub_63),
   TABLE_ENTRY(_dispatch_stub_64),
   TABLE_ENTRY(_dispatch_stub_65),
   TABLE_ENTRY(_dispatch_stub_66),
   TABLE_ENTRY(_dispatch_stub_67),
   TABLE_ENTRY(_dispatch_stub_68),
   TABLE_ENTRY(_dispatch_stub_69),
   TABLE_ENTRY(_dispatch_stub_70),
   TABLE_ENTRY(_dispatch_stub_71),
   TABLE_ENTRY(_dispatch_stub_72),
   TABLE_ENTRY(_dispatch_stub_73),
   TABLE_ENTRY(_dispatch_stub_74),
   TABLE_ENTRY(_dispatch_stub_75),
   TABLE_ENTRY(_dispatch_stub_76),
   TABLE_ENTRY(_dispatch_stub_77),
   TABLE_ENTRY(_dispatch_stub_78),
   TABLE_ENTRY(_dispatch_stub_79),
   TABLE_ENTRY(_dispatch_stub_80),
   TABLE_ENTRY(_dispatch_stub_81),
   TABLE_ENTRY(_dispatch_stub_82),
   TABLE_ENTRY(_dispatch_stub_83),
   TABLE_ENTRY(_dispatch_stub_84),
   TABLE_ENTRY(_dispatch_stub_85),
   TABLE_ENTRY(_dispatch_stub_86),
   TABLE_ENTRY(_dispatch_stub_87),
   TABLE_ENTRY(_dispatch_stub_88),
   TABLE_ENTRY(_dispatch_stub_89),
   TABLE_ENTRY(_dispatch_stub_90),
   TABLE_ENTRY(_dispatch_stub_91),
   TABLE_ENTRY(_dispatch_stub_92),
   TABLE_ENTRY(_dispatch_stub_93),
   TABLE_ENTRY(_dispatch_stub_94),
   TABLE_ENTRY(_dispatch_stub_95),
   TABLE_ENTRY(_dispatch_stub_96),
   TABLE_ENTRY(_dispatch_stub_97),
   TABLE_ENTRY(_dispatch_stub_98),
   TABLE_ENTRY(_dispatch_stub_99),
   TABLE_ENTRY(_dispatch_stub_100),
   TABLE_ENTRY(_dispatch_stub_101),
   TABLE_ENTRY(_dispatch_stub_102),
   TABLE_ENTRY(_dispatch_stub_103),
   TABLE_ENTRY(_dispatch_stub_104),
   TABLE_ENTRY(_dispatch_stub_105),
   TABLE_ENTRY(_dispatch_stub_106),
   TABLE_ENTRY(_dispatch_stub_107),
   TABLE_ENTRY(_dispatch_stub_108),
   TABLE_ENTRY(_dispatch_stub_109),
   TABLE_ENTRY(_dispatch_stub_110),
   TABLE_ENTRY(_dispatch_stub_111),
   TABLE_ENTRY(_dispatch_stub_112),
   TABLE_ENTRY(_dispatch_stub_113),
   TABLE_ENTRY(_dispatch_stub_114),
   TABLE_ENTRY(_dispatch_stub_115),
   TABLE_ENTRY(_dispatch_stub_116),
   TABLE_ENTRY(_dispatch_stub_117),
   TABLE_ENTRY(_dispatch_stub_118),
   TABLE_ENTRY(_dispatch_stub_119),
   TABLE_ENTRY(_dispatch_stub_120),
   TABLE_ENTRY(_dispatch_stub_121),
   TABLE_ENTRY(_dispatch_stub_122),
   TABLE_ENTRY(_dispatch_stub_123),
   TABLE_ENTRY(_dispatch_stub_124),
   TABLE_ENTRY(_dispatch_stub_125),
   TABLE_ENTRY(_dispatch_stub_126),
   TABLE_ENTRY(_dispatch_stub_127),
   TABLE_ENTRY(_dispatch_stub_128),
   TABLE_ENTRY(_dispatch_stub_129),
   TABLE_ENTRY(_dispatch_stub_130),
   TABLE_ENTRY(_dispatch_stub_131),
   TABLE_ENTRY(_dispatch_stub_132),
   TABLE_ENTRY(_dispatch_stub_133),
   TABLE_ENTRY(_dispatch_stub_134),
   TABLE_ENTRY(_dispatch_stub_135),
   TABLE_ENTRY(_dispatch_stub_136),
   TABLE_ENTRY(_dispatch_stub_137),
   TABLE_ENTRY(_dispatch_stub_138),
   TABLE_ENTRY(_dispatch_stub_139),
   TABLE_ENTRY(_dispatch_stub_140),
   TABLE_ENTRY(_dispatch_stub_141),
   TABLE_ENTRY(_dispatch_stub_142),
   TABLE_ENTRY(_dispatch_stub_143),
   TABLE_ENTRY(_dispatch_stub_144),
   TABLE_ENTRY(_dispatch_stub_145),
   TABLE_ENTRY(_dispatch_stub_146),
   TABLE_ENTRY(_dispatch_stub_147),
   TABLE_ENTRY(_dispatch_stub_148),
   TABLE_ENTRY(_dispatch_stub_149),
   TABLE_ENTRY(_dispatch_stub_150),
   TABLE_ENTRY(_dispatch_stub_151),
   TABLE_ENTRY(CullFace),
   TABLE_ENTRY(Fogf),
   TABLE_ENTRY(Fogfv),
   TABLE_ENTRY(_dispatch_stub_155),
   TABLE_ENTRY(_dispatch_stub_156),
   TABLE_ENTRY(FrontFace),
   TABLE_ENTRY(Hint),
   TABLE_ENTRY(Lightf),
   TABLE_ENTRY(Lightfv),
   TABLE_ENTRY(_dispatch_stub_161),
   TABLE_ENTRY(_dispatch_stub_162),
   TABLE_ENTRY(LightModelf),
   TABLE_ENTRY(LightModelfv),
   TABLE_ENTRY(_dispatch_stub_165),
   TABLE_ENTRY(_dispatch_stub_166),
   TABLE_ENTRY(_dispatch_stub_167),
   TABLE_ENTRY(LineWidth),
   TABLE_ENTRY(Materialf),
   TABLE_ENTRY(Materialfv),
   TABLE_ENTRY(_dispatch_stub_171),
   TABLE_ENTRY(_dispatch_stub_172),
   TABLE_ENTRY(PointSize),
   TABLE_ENTRY(_dispatch_stub_174),
   TABLE_ENTRY(_dispatch_stub_175),
   TABLE_ENTRY(Scissor),
   TABLE_ENTRY(ShadeModel),
   TABLE_ENTRY(TexParameterf),
   TABLE_ENTRY(TexParameterfv),
   TABLE_ENTRY(TexParameteri),
   TABLE_ENTRY(TexParameteriv),
   TABLE_ENTRY(_dispatch_stub_182),
   TABLE_ENTRY(TexImage2D),
   TABLE_ENTRY(TexEnvf),
   TABLE_ENTRY(TexEnvfv),
   TABLE_ENTRY(TexEnvi),
   TABLE_ENTRY(TexEnviv),
   TABLE_ENTRY(_dispatch_stub_188),
   TABLE_ENTRY(_dispatch_stub_189),
   TABLE_ENTRY(TexGenfOES),
   TABLE_ENTRY(TexGenfvOES),
   TABLE_ENTRY(TexGeniOES),
   TABLE_ENTRY(TexGenivOES),
   TABLE_ENTRY(_dispatch_stub_194),
   TABLE_ENTRY(_dispatch_stub_195),
   TABLE_ENTRY(_dispatch_stub_196),
   TABLE_ENTRY(_dispatch_stub_197),
   TABLE_ENTRY(_dispatch_stub_198),
   TABLE_ENTRY(_dispatch_stub_199),
   TABLE_ENTRY(_dispatch_stub_200),
   TABLE_ENTRY(_dispatch_stub_201),
   TABLE_ENTRY(_dispatch_stub_202),
   TABLE_ENTRY(Clear),
   TABLE_ENTRY(_dispatch_stub_204),
   TABLE_ENTRY(_dispatch_stub_205),
   TABLE_ENTRY(ClearColor),
   TABLE_ENTRY(ClearStencil),
   TABLE_ENTRY(_dispatch_stub_208),
   TABLE_ENTRY(StencilMask),
   TABLE_ENTRY(ColorMask),
   TABLE_ENTRY(DepthMask),
   TABLE_ENTRY(_dispatch_stub_212),
   TABLE_ENTRY(_dispatch_stub_213),
   TABLE_ENTRY(Disable),
   TABLE_ENTRY(Enable),
   TABLE_ENTRY(Finish),
   TABLE_ENTRY(Flush),
   TABLE_ENTRY(_dispatch_stub_218),
   TABLE_ENTRY(_dispatch_stub_219),
   TABLE_ENTRY(_dispatch_stub_220),
   TABLE_ENTRY(_dispatch_stub_221),
   TABLE_ENTRY(_dispatch_stub_222),
   TABLE_ENTRY(_dispatch_stub_223),
   TABLE_ENTRY(_dispatch_stub_224),
   TABLE_ENTRY(_dispatch_stub_225),
   TABLE_ENTRY(_dispatch_stub_226),
   TABLE_ENTRY(_dispatch_stub_227),
   TABLE_ENTRY(_dispatch_stub_228),
   TABLE_ENTRY(_dispatch_stub_229),
   TABLE_ENTRY(_dispatch_stub_230),
   TABLE_ENTRY(_dispatch_stub_231),
   TABLE_ENTRY(_dispatch_stub_232),
   TABLE_ENTRY(_dispatch_stub_233),
   TABLE_ENTRY(_dispatch_stub_234),
   TABLE_ENTRY(_dispatch_stub_235),
   TABLE_ENTRY(_dispatch_stub_236),
   TABLE_ENTRY(_dispatch_stub_237),
   TABLE_ENTRY(_dispatch_stub_238),
   TABLE_ENTRY(_dispatch_stub_239),
   TABLE_ENTRY(AlphaFunc),
   TABLE_ENTRY(BlendFunc),
   TABLE_ENTRY(LogicOp),
   TABLE_ENTRY(StencilFunc),
   TABLE_ENTRY(StencilOp),
   TABLE_ENTRY(DepthFunc),
   TABLE_ENTRY(_dispatch_stub_246),
   TABLE_ENTRY(_dispatch_stub_247),
   TABLE_ENTRY(_dispatch_stub_248),
   TABLE_ENTRY(_dispatch_stub_249),
   TABLE_ENTRY(PixelStorei),
   TABLE_ENTRY(_dispatch_stub_251),
   TABLE_ENTRY(_dispatch_stub_252),
   TABLE_ENTRY(_dispatch_stub_253),
   TABLE_ENTRY(_dispatch_stub_254),
   TABLE_ENTRY(_dispatch_stub_255),
   TABLE_ENTRY(ReadPixels),
   TABLE_ENTRY(_dispatch_stub_257),
   TABLE_ENTRY(GetBooleanv),
   TABLE_ENTRY(_dispatch_stub_259),
   TABLE_ENTRY(_dispatch_stub_260),
   TABLE_ENTRY(GetError),
   TABLE_ENTRY(GetFloatv),
   TABLE_ENTRY(GetIntegerv),
   TABLE_ENTRY(GetLightfv),
   TABLE_ENTRY(_dispatch_stub_265),
   TABLE_ENTRY(_dispatch_stub_266),
   TABLE_ENTRY(_dispatch_stub_267),
   TABLE_ENTRY(_dispatch_stub_268),
   TABLE_ENTRY(GetMaterialfv),
   TABLE_ENTRY(_dispatch_stub_270),
   TABLE_ENTRY(_dispatch_stub_271),
   TABLE_ENTRY(_dispatch_stub_272),
   TABLE_ENTRY(_dispatch_stub_273),
   TABLE_ENTRY(_dispatch_stub_274),
   TABLE_ENTRY(GetString),
   TABLE_ENTRY(GetTexEnvfv),
   TABLE_ENTRY(GetTexEnviv),
   TABLE_ENTRY(_dispatch_stub_278),
   TABLE_ENTRY(GetTexGenfvOES),
   TABLE_ENTRY(GetTexGenivOES),
   TABLE_ENTRY(_dispatch_stub_281),
   TABLE_ENTRY(GetTexParameterfv),
   TABLE_ENTRY(GetTexParameteriv),
   TABLE_ENTRY(_dispatch_stub_284),
   TABLE_ENTRY(_dispatch_stub_285),
   TABLE_ENTRY(IsEnabled),
   TABLE_ENTRY(_dispatch_stub_287),
   TABLE_ENTRY(_dispatch_stub_288),
   TABLE_ENTRY(_dispatch_stub_289),
   TABLE_ENTRY(LoadIdentity),
   TABLE_ENTRY(LoadMatrixf),
   TABLE_ENTRY(_dispatch_stub_292),
   TABLE_ENTRY(MatrixMode),
   TABLE_ENTRY(MultMatrixf),
   TABLE_ENTRY(_dispatch_stub_295),
   TABLE_ENTRY(_dispatch_stub_296),
   TABLE_ENTRY(PopMatrix),
   TABLE_ENTRY(PushMatrix),
   TABLE_ENTRY(_dispatch_stub_299),
   TABLE_ENTRY(Rotatef),
   TABLE_ENTRY(_dispatch_stub_301),
   TABLE_ENTRY(Scalef),
   TABLE_ENTRY(_dispatch_stub_303),
   TABLE_ENTRY(Translatef),
   TABLE_ENTRY(Viewport),
   TABLE_ENTRY(_dispatch_stub_306),
   TABLE_ENTRY(BindTexture),
   TABLE_ENTRY(ColorPointer),
   TABLE_ENTRY(DisableClientState),
   TABLE_ENTRY(DrawArrays),
   TABLE_ENTRY(DrawElements),
   TABLE_ENTRY(_dispatch_stub_312),
   TABLE_ENTRY(EnableClientState),
   TABLE_ENTRY(_dispatch_stub_314),
   TABLE_ENTRY(_dispatch_stub_315),
   TABLE_ENTRY(_dispatch_stub_316),
   TABLE_ENTRY(_dispatch_stub_317),
   TABLE_ENTRY(NormalPointer),
   TABLE_ENTRY(PolygonOffset),
   TABLE_ENTRY(TexCoordPointer),
   TABLE_ENTRY(VertexPointer),
   TABLE_ENTRY(_dispatch_stub_322),
   TABLE_ENTRY(_dispatch_stub_323),
   TABLE_ENTRY(CopyTexImage2D),
   TABLE_ENTRY(_dispatch_stub_325),
   TABLE_ENTRY(CopyTexSubImage2D),
   TABLE_ENTRY(DeleteTextures),
   TABLE_ENTRY(GenTextures),
   TABLE_ENTRY(GetPointerv),
   TABLE_ENTRY(IsTexture),
   TABLE_ENTRY(_dispatch_stub_331),
   TABLE_ENTRY(_dispatch_stub_332),
   TABLE_ENTRY(TexSubImage2D),
   TABLE_ENTRY(_dispatch_stub_334),
   TABLE_ENTRY(_dispatch_stub_335),
   TABLE_ENTRY(_dispatch_stub_336),
   TABLE_ENTRY(BlendEquationOES),
   TABLE_ENTRY(_dispatch_stub_338),
   TABLE_ENTRY(_dispatch_stub_339),
   TABLE_ENTRY(_dispatch_stub_340),
   TABLE_ENTRY(_dispatch_stub_341),
   TABLE_ENTRY(_dispatch_stub_342),
   TABLE_ENTRY(_dispatch_stub_343),
   TABLE_ENTRY(_dispatch_stub_344),
   TABLE_ENTRY(_dispatch_stub_345),
   TABLE_ENTRY(_dispatch_stub_346),
   TABLE_ENTRY(_dispatch_stub_347),
   TABLE_ENTRY(_dispatch_stub_348),
   TABLE_ENTRY(_dispatch_stub_349),
   TABLE_ENTRY(_dispatch_stub_350),
   TABLE_ENTRY(_dispatch_stub_351),
   TABLE_ENTRY(_dispatch_stub_352),
   TABLE_ENTRY(_dispatch_stub_353),
   TABLE_ENTRY(_dispatch_stub_354),
   TABLE_ENTRY(_dispatch_stub_355),
   TABLE_ENTRY(_dispatch_stub_356),
   TABLE_ENTRY(_dispatch_stub_357),
   TABLE_ENTRY(_dispatch_stub_358),
   TABLE_ENTRY(_dispatch_stub_359),
   TABLE_ENTRY(_dispatch_stub_360),
   TABLE_ENTRY(_dispatch_stub_361),
   TABLE_ENTRY(_dispatch_stub_362),
   TABLE_ENTRY(_dispatch_stub_363),
   TABLE_ENTRY(_dispatch_stub_364),
   TABLE_ENTRY(_dispatch_stub_365),
   TABLE_ENTRY(_dispatch_stub_366),
   TABLE_ENTRY(_dispatch_stub_367),
   TABLE_ENTRY(_dispatch_stub_368),
   TABLE_ENTRY(_dispatch_stub_369),
   TABLE_ENTRY(_dispatch_stub_370),
   TABLE_ENTRY(_dispatch_stub_371),
   TABLE_ENTRY(_dispatch_stub_372),
   TABLE_ENTRY(_dispatch_stub_373),
   TABLE_ENTRY(ActiveTexture),
   TABLE_ENTRY(ClientActiveTexture),
   TABLE_ENTRY(_dispatch_stub_376),
   TABLE_ENTRY(_dispatch_stub_377),
   TABLE_ENTRY(_dispatch_stub_378),
   TABLE_ENTRY(_dispatch_stub_379),
   TABLE_ENTRY(_dispatch_stub_380),
   TABLE_ENTRY(_dispatch_stub_381),
   TABLE_ENTRY(_dispatch_stub_382),
   TABLE_ENTRY(_dispatch_stub_383),
   TABLE_ENTRY(_dispatch_stub_384),
   TABLE_ENTRY(_dispatch_stub_385),
   TABLE_ENTRY(_dispatch_stub_386),
   TABLE_ENTRY(_dispatch_stub_387),
   TABLE_ENTRY(_dispatch_stub_388),
   TABLE_ENTRY(_dispatch_stub_389),
   TABLE_ENTRY(_dispatch_stub_390),
   TABLE_ENTRY(_dispatch_stub_391),
   TABLE_ENTRY(_dispatch_stub_392),
   TABLE_ENTRY(_dispatch_stub_393),
   TABLE_ENTRY(_dispatch_stub_394),
   TABLE_ENTRY(_dispatch_stub_395),
   TABLE_ENTRY(_dispatch_stub_396),
   TABLE_ENTRY(_dispatch_stub_397),
   TABLE_ENTRY(_dispatch_stub_398),
   TABLE_ENTRY(_dispatch_stub_399),
   TABLE_ENTRY(_dispatch_stub_400),
   TABLE_ENTRY(_dispatch_stub_401),
   TABLE_ENTRY(MultiTexCoord4f),
   TABLE_ENTRY(_dispatch_stub_403),
   TABLE_ENTRY(_dispatch_stub_404),
   TABLE_ENTRY(_dispatch_stub_405),
   TABLE_ENTRY(_dispatch_stub_406),
   TABLE_ENTRY(_dispatch_stub_407),
   TABLE_ENTRY(BlendEquationSeparateOES),
   TABLE_ENTRY(BlendFuncSeparateOES),
   TABLE_ENTRY(DrawTexfOES),
   TABLE_ENTRY(DrawTexfvOES),
   TABLE_ENTRY(DrawTexiOES),
   TABLE_ENTRY(DrawTexivOES),
   TABLE_ENTRY(DrawTexsOES),
   TABLE_ENTRY(DrawTexsvOES),
   TABLE_ENTRY(DrawTexxOES),
   TABLE_ENTRY(DrawTexxvOES),
   TABLE_ENTRY(BindFramebufferOES),
   TABLE_ENTRY(BindRenderbufferOES),
   TABLE_ENTRY(CheckFramebufferStatusOES),
   TABLE_ENTRY(DeleteFramebuffersOES),
   TABLE_ENTRY(DeleteRenderbuffersOES),
   TABLE_ENTRY(FramebufferRenderbufferOES),
   TABLE_ENTRY(FramebufferTexture2DOES),
   TABLE_ENTRY(GenFramebuffersOES),
   TABLE_ENTRY(GenRenderbuffersOES),
   TABLE_ENTRY(GenerateMipmapOES),
   TABLE_ENTRY(GetFramebufferAttachmentParameterivOES),
   TABLE_ENTRY(GetRenderbufferParameterivOES),
   TABLE_ENTRY(IsFramebufferOES),
   TABLE_ENTRY(IsRenderbufferOES),
   TABLE_ENTRY(RenderbufferStorageOES),
   TABLE_ENTRY(PointSizePointerOES),
   TABLE_ENTRY(QueryMatrixxOES),
   TABLE_ENTRY(GetTexGenxvOES),
   TABLE_ENTRY(TexGenxOES),
   TABLE_ENTRY(TexGenxvOES),
   TABLE_ENTRY(GetBufferPointervOES),
   TABLE_ENTRY(MapBufferOES),
   TABLE_ENTRY(UnmapBufferOES),
   TABLE_ENTRY(MultiDrawArraysEXT),
   TABLE_ENTRY(MultiDrawElementsEXT),
   TABLE_ENTRY(_dispatch_stub_443),
   TABLE_ENTRY(_dispatch_stub_444),
   TABLE_ENTRY(_dispatch_stub_445),
   TABLE_ENTRY(_dispatch_stub_446),
   TABLE_ENTRY(EGLImageTargetRenderbufferStorageOES),
   TABLE_ENTRY(EGLImageTargetTexture2DOES),
   TABLE_ENTRY(CompressedTexImage2D),
   TABLE_ENTRY(CompressedTexSubImage2D),
   TABLE_ENTRY(SampleCoverage),
   TABLE_ENTRY(BindBuffer),
   TABLE_ENTRY(BufferData),
   TABLE_ENTRY(BufferSubData),
   TABLE_ENTRY(DeleteBuffers),
   TABLE_ENTRY(GenBuffers),
   TABLE_ENTRY(GetBufferParameteriv),
   TABLE_ENTRY(IsBuffer),
   TABLE_ENTRY(PointParameterf),
   TABLE_ENTRY(PointParameterfv),
   TABLE_ENTRY(AlphaFuncx),
   TABLE_ENTRY(ClearColorx),
   TABLE_ENTRY(ClearDepthf),
   TABLE_ENTRY(ClearDepthx),
   TABLE_ENTRY(Color4x),
   TABLE_ENTRY(DepthRangef),
   TABLE_ENTRY(DepthRangex),
   TABLE_ENTRY(Fogx),
   TABLE_ENTRY(Fogxv),
   TABLE_ENTRY(Frustumf),
   TABLE_ENTRY(Frustumx),
   TABLE_ENTRY(LightModelx),
   TABLE_ENTRY(LightModelxv),
   TABLE_ENTRY(Lightx),
   TABLE_ENTRY(Lightxv),
   TABLE_ENTRY(LineWidthx),
   TABLE_ENTRY(LoadMatrixx),
   TABLE_ENTRY(Materialx),
   TABLE_ENTRY(Materialxv),
   TABLE_ENTRY(MultMatrixx),
   TABLE_ENTRY(MultiTexCoord4x),
   TABLE_ENTRY(Normal3x),
   TABLE_ENTRY(Orthof),
   TABLE_ENTRY(Orthox),
   TABLE_ENTRY(PointSizex),
   TABLE_ENTRY(PolygonOffsetx),
   TABLE_ENTRY(Rotatex),
   TABLE_ENTRY(SampleCoveragex),
   TABLE_ENTRY(Scalex),
   TABLE_ENTRY(TexEnvx),
   TABLE_ENTRY(TexEnvxv),
   TABLE_ENTRY(TexParameterx),
   TABLE_ENTRY(Translatex),
   TABLE_ENTRY(ClipPlanef),
   TABLE_ENTRY(ClipPlanex),
   TABLE_ENTRY(GetClipPlanef),
   TABLE_ENTRY(GetClipPlanex),
   TABLE_ENTRY(GetFixedv),
   TABLE_ENTRY(GetLightxv),
   TABLE_ENTRY(GetMaterialxv),
   TABLE_ENTRY(GetTexEnvxv),
   TABLE_ENTRY(GetTexParameterxv),
   TABLE_ENTRY(PointParameterx),
   TABLE_ENTRY(PointParameterxv),
   TABLE_ENTRY(TexParameterxv),
   /* A whole bunch of no-op functions.  These might be called
    * when someone tries to call a dynamically-registered
    * extension function without a current rendering context.
    */
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
   TABLE_ENTRY(Unused),
};
#endif /* DISPATCH_TABLE_NAME */


/*
 * This is just used to silence compiler warnings.
 * We list the functions which are not otherwise used.
 */
#ifdef UNUSED_TABLE_NAME
_glapi_proc UNUSED_TABLE_NAME[] = {
#ifndef _GLAPI_SKIP_NORMAL_ENTRY_POINTS
   TABLE_ENTRY(_dispatch_stub_190),
   TABLE_ENTRY(_dispatch_stub_191),
   TABLE_ENTRY(_dispatch_stub_192),
   TABLE_ENTRY(_dispatch_stub_193),
   TABLE_ENTRY(_dispatch_stub_279),
   TABLE_ENTRY(_dispatch_stub_280),
   TABLE_ENTRY(_dispatch_stub_337),
   TABLE_ENTRY(_dispatch_stub_374),
   TABLE_ENTRY(_dispatch_stub_375),
   TABLE_ENTRY(_dispatch_stub_402),
   TABLE_ENTRY(AlphaFuncxOES),
   TABLE_ENTRY(ClearColorxOES),
   TABLE_ENTRY(ClearDepthfOES),
   TABLE_ENTRY(ClearDepthxOES),
   TABLE_ENTRY(Color4xOES),
   TABLE_ENTRY(DepthRangefOES),
   TABLE_ENTRY(DepthRangexOES),
   TABLE_ENTRY(FogxOES),
   TABLE_ENTRY(FogxvOES),
   TABLE_ENTRY(FrustumfOES),
   TABLE_ENTRY(FrustumxOES),
   TABLE_ENTRY(LightModelxOES),
   TABLE_ENTRY(LightModelxvOES),
   TABLE_ENTRY(LightxOES),
   TABLE_ENTRY(LightxvOES),
   TABLE_ENTRY(LineWidthxOES),
   TABLE_ENTRY(LoadMatrixxOES),
   TABLE_ENTRY(MaterialxOES),
   TABLE_ENTRY(MaterialxvOES),
   TABLE_ENTRY(MultMatrixxOES),
   TABLE_ENTRY(MultiTexCoord4xOES),
   TABLE_ENTRY(Normal3xOES),
   TABLE_ENTRY(OrthofOES),
   TABLE_ENTRY(OrthoxOES),
   TABLE_ENTRY(PointSizexOES),
   TABLE_ENTRY(PolygonOffsetxOES),
   TABLE_ENTRY(RotatexOES),
   TABLE_ENTRY(SampleCoveragexOES),
   TABLE_ENTRY(ScalexOES),
   TABLE_ENTRY(TexEnvxOES),
   TABLE_ENTRY(TexEnvxvOES),
   TABLE_ENTRY(TexParameterxOES),
   TABLE_ENTRY(TranslatexOES),
   TABLE_ENTRY(ClipPlanefOES),
   TABLE_ENTRY(ClipPlanexOES),
   TABLE_ENTRY(GetClipPlanefOES),
   TABLE_ENTRY(GetClipPlanexOES),
   TABLE_ENTRY(GetFixedvOES),
   TABLE_ENTRY(GetLightxvOES),
   TABLE_ENTRY(GetMaterialxvOES),
   TABLE_ENTRY(GetTexEnvxvOES),
   TABLE_ENTRY(GetTexParameterxvOES),
   TABLE_ENTRY(PointParameterxOES),
   TABLE_ENTRY(PointParameterxvOES),
   TABLE_ENTRY(TexParameterxvOES),
#endif /* _GLAPI_SKIP_NORMAL_ENTRY_POINTS */
#ifndef _GLAPI_SKIP_PROTO_ENTRY_POINTS
#endif /* _GLAPI_SKIP_PROTO_ENTRY_POINTS */
};
#endif /*UNUSED_TABLE_NAME*/


#  undef KEYWORD1
#  undef KEYWORD1_ALT
#  undef KEYWORD2
#  undef NAME
#  undef DISPATCH
#  undef RETURN_DISPATCH
#  undef DISPATCH_TABLE_NAME
#  undef UNUSED_TABLE_NAME
#  undef TABLE_ENTRY
#  undef HIDDEN
