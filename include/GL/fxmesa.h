/* $Id: fxmesa.h,v 1.1.1.1.2.1 1999/11/24 18:38:52 brianp Exp $ */

/*
 * Mesa 3-D graphics library
 * Version:  3.1
 *
 * Copyright (C) 1999  Brian Paul   All Rights Reserved.
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


/*
 * FXMesa - 3Dfx Glide driver for Mesa.  Contributed by David Bucciarelli
 *
 * NOTE: This version requires Glide 2.3 or later.
 */


#ifndef FXMESA_H
#define FXMESA_H


#include <glide.h>


#ifdef __cplusplus
extern "C" {
#endif


#define FXMESA_MAJOR_VERSION 3
#define FXMESA_MINOR_VERSION 1


/*
 * Values for attribList parameter to fxMesaCreateContext():
 */
#define FXMESA_NONE		0	/* to terminate attribList */
#define FXMESA_DOUBLEBUFFER	10
#define FXMESA_ALPHA_SIZE	11      /* followed by an integer */
#define FXMESA_DEPTH_SIZE	12      /* followed by an integer */
#define FXMESA_STENCIL_SIZE	13      /* followed by an integer */
#define FXMESA_ACCUM_SIZE	14      /* followed by an integer */



typedef struct tfxMesaContext *fxMesaContext;


#if defined (__BEOS__)
#pragma export on
#endif


GLAPI fxMesaContext GLAPIENTRY fxMesaCreateContext(GLuint win, GrScreenResolution_t,
						  GrScreenRefresh_t,
						  const GLint attribList[]);

GLAPI fxMesaContext GLAPIENTRY fxMesaCreateBestContext(GLuint win,
						      GLint width, GLint height,
						      const GLint attribList[]);
GLAPI void GLAPIENTRY fxMesaDestroyContext(fxMesaContext ctx);

GLAPI GLboolean GLAPIENTRY fxMesaSelectCurrentBoard(int n);

GLAPI void GLAPIENTRY fxMesaMakeCurrent(fxMesaContext ctx);

GLAPI fxMesaContext GLAPIENTRY fxMesaGetCurrentContext(void);

GLAPI void GLAPIENTRY fxMesaSwapBuffers(void);

GLAPI void GLAPIENTRY fxMesaSetNearFar(GLfloat nearVal, GLfloat farVal);

GLAPI void GLAPIENTRY fxMesaUpdateScreenSize(fxMesaContext ctx);

GLAPI int GLAPIENTRY fxQueryHardware(void);

GLAPI void GLAPIENTRY fxCloseHardware(void);


#if defined (__BEOS__)
#pragma export off
#endif


#ifdef __cplusplus
}
#endif


#endif
