/**
 * \file accum.h
 * \brief Accumulation buffer operations.
 * 
 * \if subset
 * \brief (No-op.)
 *
 * \endif
 */

/*
 * Mesa 3-D graphics library
 * Version:  3.5
 *
 * Copyright (C) 1999-2001  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* $Id: accum.h,v 1.6.8.2 2003/03/23 03:51:34 jrfonseca Exp $ */


#ifndef ACCUM_H
#define ACCUM_H


#include "mtypes.h"

#if _HAVE_FULL_GL

extern void
_mesa_Accum( GLenum op, GLfloat value );


extern void
_mesa_ClearAccum( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );

extern void 
_mesa_init_accum( GLcontext *ctx );

#else

/** \brief No-op */
#define _mesa_init_accum( c ) ((void)0)

#endif

#endif
