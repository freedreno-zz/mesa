/**
 * \file macros.h
 * \brief A collection of useful macros.
 */

/*
 * Mesa 3-D graphics library
 * Version:  4.0.3
 *
 * Copyright (C) 1999-2002  Brian Paul   All Rights Reserved.
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

/* $Id: macros.h,v 1.30.4.1 2003/03/20 12:56:58 jrfonseca Exp $ */


#ifndef MACROS_H
#define MACROS_H


#include "glheader.h"
/* Do not reference mtypes.h from this file.
 */


/* Limits: */
#define MAX_GLUSHORT	0xffff
#define MAX_GLUINT	0xffffffff


/** \brief Pi */
#ifndef M_PI
#define M_PI (3.1415926)
#endif


/** \brief Degrees to radians conversion */
#define DEG2RAD (M_PI/180.0)


/** \brief Null pointer */
#ifndef NULL
#define NULL 0
#endif


/** \brief Stepping a GLfloat pointer by a byte stride */
#define STRIDE_F(p, i)  (p = (GLfloat *)((GLubyte *)p + i))
/** \brief Stepping a GLuint pointer by a byte stride */
#define STRIDE_UI(p, i)  (p = (GLuint *)((GLubyte *)p + i))
/** \brief Stepping a GLubyte[4] pointer by a byte stride */
#define STRIDE_4UB(p, i)  (p = (GLubyte (*)[4])((GLubyte *)p + i))
/** \brief Stepping a GLchan[4] pointer by a byte stride */
#define STRIDE_4CHAN(p, i)  (p = (GLchan (*)[4])((GLubyte *)p + i))
/** \brief Stepping a GLchan pointer by a byte stride */
#define STRIDE_CHAN(p, i)  (p = (GLchan *)((GLubyte *)p + i))
/** \brief Stepping a \p t pointer by a byte stride */
#define STRIDE_T(p, t, i)  (p = (t)((GLubyte *)p + i))


/**********************************************************************/
/** \name 4-element vector operations */
/*@{*/

/** \brief Zero */
#define ZERO_4V( DST )	(DST)[0] = (DST)[1] = (DST)[2] = (DST)[3] = 0

/** \brief Test for equality */
#define TEST_EQ_4V(a,b)  ((a)[0] == (b)[0] && 	\
			  (a)[1] == (b)[1] &&	\
			  (a)[2] == (b)[2] &&	\
			  (a)[3] == (b)[3])

/** \brief Test for equality (unsined bytes) */
#if defined(__i386__)
#define TEST_EQ_4UBV(DST, SRC) *((GLuint*)(DST)) == *((GLuint*)(SRC))
#else
#define TEST_EQ_4UBV(DST, SRC) TEST_EQ_4V(DST, SRC)
#endif

/** \brief Copy a 4-element vector */
#define COPY_4V( DST, SRC )			\
do {						\
   (DST)[0] = (SRC)[0];				\
   (DST)[1] = (SRC)[1];				\
   (DST)[2] = (SRC)[2];				\
   (DST)[3] = (SRC)[3];				\
} while (0)

/** \brief Copy a 4-element vector with cast */
#define COPY_4V_CAST( DST, SRC, CAST )		\
do {						\
   (DST)[0] = (CAST)(SRC)[0];			\
   (DST)[1] = (CAST)(SRC)[1];			\
   (DST)[2] = (CAST)(SRC)[2];			\
   (DST)[3] = (CAST)(SRC)[3];			\
} while (0)

/** \brief Copy a 4-element unsigned byte vector */
#if defined(__i386__)
#define COPY_4UBV(DST, SRC)			\
do {						\
   *((GLuint*)(DST)) = *((GLuint*)(SRC));	\
} while (0)
#else
/* The GLuint cast might fail if DST or SRC are not dword-aligned (RISC) */
#define COPY_4UBV(DST, SRC)			\
do {						\
   (DST)[0] = (SRC)[0];				\
   (DST)[1] = (SRC)[1];				\
   (DST)[2] = (SRC)[2];				\
   (DST)[3] = (SRC)[3];				\
} while (0)
#endif

/** \brief Copy a 4-element float vector */
#define COPY_4FV( DST, SRC )			\
do {						\
   const GLfloat *_tmp = (SRC);			\
   (DST)[0] = _tmp[0];				\
   (DST)[1] = _tmp[1];				\
   (DST)[2] = _tmp[2];				\
   (DST)[3] = _tmp[3];				\
} while (0)


/** \brief Copy \p SZ elements into a 4-element vector */
#define COPY_SZ_4V(DST, SZ, SRC) 		\
do {						\
   switch (SZ) {				\
   case 4: (DST)[3] = (SRC)[3];			\
   case 3: (DST)[2] = (SRC)[2];			\
   case 2: (DST)[1] = (SRC)[1];			\
   case 1: (DST)[0] = (SRC)[0];			\
   }  						\
} while(0)

/** \brief Copy \p SZ elements into a homegenous (4-element) vector, giving
 * default values to the remaining */
#define COPY_CLEAN_4V(DST, SZ, SRC) 		\
do {						\
      ASSIGN_4V( DST, 0, 0, 0, 1 );		\
      COPY_SZ_4V( DST, SZ, SRC );		\
} while (0)

/** \brief Subtraction */
#define SUB_4V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] = (SRCA)[0] - (SRCB)[0];		\
      (DST)[1] = (SRCA)[1] - (SRCB)[1];		\
      (DST)[2] = (SRCA)[2] - (SRCB)[2];		\
      (DST)[3] = (SRCA)[3] - (SRCB)[3];		\
} while (0)

/** \brief Addition */
#define ADD_4V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] = (SRCA)[0] + (SRCB)[0];		\
      (DST)[1] = (SRCA)[1] + (SRCB)[1];		\
      (DST)[2] = (SRCA)[2] + (SRCB)[2];		\
      (DST)[3] = (SRCA)[3] + (SRCB)[3];		\
} while (0)

/** \brief Element-wise multiplication */
#define SCALE_4V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] = (SRCA)[0] * (SRCB)[0];		\
      (DST)[1] = (SRCA)[1] * (SRCB)[1];		\
      (DST)[2] = (SRCA)[2] * (SRCB)[2];		\
      (DST)[3] = (SRCA)[3] * (SRCB)[3];		\
} while (0)

/** \brief In-place addition */
#define ACC_4V( DST, SRC )			\
do {						\
      (DST)[0] += (SRC)[0];			\
      (DST)[1] += (SRC)[1];			\
      (DST)[2] += (SRC)[2];			\
      (DST)[3] += (SRC)[3];			\
} while (0)

/** \brief Element-wise multiplication and addition */
#define ACC_SCALE_4V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] += (SRCA)[0] * (SRCB)[0];	\
      (DST)[1] += (SRCA)[1] * (SRCB)[1];	\
      (DST)[2] += (SRCA)[2] * (SRCB)[2];	\
      (DST)[3] += (SRCA)[3] * (SRCB)[3];	\
} while (0)

/** \brief In-place scalar multiplication and addition */
#define ACC_SCALE_SCALAR_4V( DST, S, SRCB )	\
do {						\
      (DST)[0] += S * (SRCB)[0];		\
      (DST)[1] += S * (SRCB)[1];		\
      (DST)[2] += S * (SRCB)[2];		\
      (DST)[3] += S * (SRCB)[3];		\
} while (0)

/** \brief Scalar multiplication */
#define SCALE_SCALAR_4V( DST, S, SRCB )		\
do {						\
      (DST)[0] = S * (SRCB)[0];			\
      (DST)[1] = S * (SRCB)[1];			\
      (DST)[2] = S * (SRCB)[2];			\
      (DST)[3] = S * (SRCB)[3];			\
} while (0)

/** \brief In-place scalar multiplication */
#define SELF_SCALE_SCALAR_4V( DST, S )		\
do {						\
      (DST)[0] *= S;				\
      (DST)[1] *= S;				\
      (DST)[2] *= S;				\
      (DST)[3] *= S;				\
} while (0)

/** \brief Assignment */
#define ASSIGN_4V( V, V0, V1, V2, V3 ) 		\
do { 						\
    V[0] = V0;					\
    V[1] = V1;					\
    V[2] = V2;					\
    V[3] = V3; 					\
} while(0)

/*@}*/


/**********************************************************************/
/** \name 3-element vector operations*/
/*@{*/

/** \brief Zero */
#define ZERO_3V( DST )	(DST)[0] = (DST)[1] = (DST)[2] = 0

/** \brief Test for equality */
#define TEST_EQ_3V(a,b)  ((a)[0] == (b)[0] && 	\
			  (a)[1] == (b)[1] &&	\
			  (a)[2] == (b)[2])

/** \brief Copy a 3-element vector */
#define COPY_3V( DST, SRC )			\
do {						\
   (DST)[0] = (SRC)[0];				\
   (DST)[1] = (SRC)[1];				\
   (DST)[2] = (SRC)[2];				\
} while (0)

/** \brief Copy a 3-element vector with cast */
#define COPY_3V_CAST( DST, SRC, CAST )		\
do {						\
   (DST)[0] = (CAST)(SRC)[0];			\
   (DST)[1] = (CAST)(SRC)[1];			\
   (DST)[2] = (CAST)(SRC)[2];			\
} while (0)

/** \brief Copy a 3-element float vector */
#define COPY_3FV( DST, SRC )			\
do {						\
   const GLfloat *_tmp = (SRC);			\
   (DST)[0] = _tmp[0];				\
   (DST)[1] = _tmp[1];				\
   (DST)[2] = _tmp[2];				\
} while (0)

/** \brief Subtraction */
#define SUB_3V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] = (SRCA)[0] - (SRCB)[0];		\
      (DST)[1] = (SRCA)[1] - (SRCB)[1];		\
      (DST)[2] = (SRCA)[2] - (SRCB)[2];		\
} while (0)

/** \brief Addition */
#define ADD_3V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] = (SRCA)[0] + (SRCB)[0];		\
      (DST)[1] = (SRCA)[1] + (SRCB)[1];		\
      (DST)[2] = (SRCA)[2] + (SRCB)[2];		\
} while (0)

/** \brief In-place scalar multiplication */
#define SCALE_3V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] = (SRCA)[0] * (SRCB)[0];		\
      (DST)[1] = (SRCA)[1] * (SRCB)[1];		\
      (DST)[2] = (SRCA)[2] * (SRCB)[2];		\
} while (0)

/** \brief In-place element-wise multiplication */
#define SELF_SCALE_3V( DST, SRC )		\
do {						\
      (DST)[0] *= (SRC)[0];			\
      (DST)[1] *= (SRC)[1];			\
      (DST)[2] *= (SRC)[2];			\
} while (0)

/** \brief In-place addition */
#define ACC_3V( DST, SRC )			\
do {						\
      (DST)[0] += (SRC)[0];			\
      (DST)[1] += (SRC)[1];			\
      (DST)[2] += (SRC)[2];			\
} while (0)

/** \brief Element-wise multiplication and addition */
#define ACC_SCALE_3V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] += (SRCA)[0] * (SRCB)[0];	\
      (DST)[1] += (SRCA)[1] * (SRCB)[1];	\
      (DST)[2] += (SRCA)[2] * (SRCB)[2];	\
} while (0)

/** \brief Scalar multiplication */
#define SCALE_SCALAR_3V( DST, S, SRCB ) 	\
do {						\
      (DST)[0] = S * (SRCB)[0];			\
      (DST)[1] = S * (SRCB)[1];			\
      (DST)[2] = S * (SRCB)[2];			\
} while (0)

/** \brief In-place scalar multiplication and addition */
#define ACC_SCALE_SCALAR_3V( DST, S, SRCB )	\
do {						\
      (DST)[0] += S * (SRCB)[0];		\
      (DST)[1] += S * (SRCB)[1];		\
      (DST)[2] += S * (SRCB)[2];		\
} while (0)

/** \brief In-place scalar multiplication */
#define SELF_SCALE_SCALAR_3V( DST, S )		\
do {						\
      (DST)[0] *= S;				\
      (DST)[1] *= S;				\
      (DST)[2] *= S;				\
} while (0)

/** \brief In-place scalar addition */
#define ACC_SCALAR_3V( DST, S ) 		\
do {						\
      (DST)[0] += S;				\
      (DST)[1] += S;				\
      (DST)[2] += S;				\
} while (0)

/** \brief Assignment */
#define ASSIGN_3V( V, V0, V1, V2 )	\
do { 				 	\
    V[0] = V0; 				\
    V[1] = V1; 				\
    V[2] = V2; 				\
} while(0)

/*@}*/


/**********************************************************************/
/** \name 2-element vector operations*/
/*@{*/

/** \brief Zero */
#define ZERO_2V( DST )	(DST)[0] = (DST)[1] = 0

/** \brief Copy a 2-element vector */
#define COPY_2V( DST, SRC )			\
do {						\
   (DST)[0] = (SRC)[0];				\
   (DST)[1] = (SRC)[1];				\
} while (0)

/** \brief Copy a 2-element vector with cast */
#define COPY_2V_CAST( DST, SRC, CAST )		\
do {						\
   (DST)[0] = (CAST)(SRC)[0];			\
   (DST)[1] = (CAST)(SRC)[1];			\
} while (0)

/** \brief Copy a 2-element float vector */
#define COPY_2FV( DST, SRC )			\
do {						\
   const GLfloat *_tmp = (SRC);			\
   (DST)[0] = _tmp[0];				\
   (DST)[1] = _tmp[1];				\
} while (0)

/** \brief Subtraction */
#define SUB_2V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] = (SRCA)[0] - (SRCB)[0];		\
      (DST)[1] = (SRCA)[1] - (SRCB)[1];		\
} while (0)

/** \brief Addition */
#define ADD_2V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] = (SRCA)[0] + (SRCB)[0];		\
      (DST)[1] = (SRCA)[1] + (SRCB)[1];		\
} while (0)

/** \brief In-place scalar multiplication */
#define SCALE_2V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] = (SRCA)[0] * (SRCB)[0];		\
      (DST)[1] = (SRCA)[1] * (SRCB)[1];		\
} while (0)

/** \brief In-place addition */
#define ACC_2V( DST, SRC )			\
do {						\
      (DST)[0] += (SRC)[0];			\
      (DST)[1] += (SRC)[1];			\
} while (0)

/** \brief Element-wise multiplication and addition */
#define ACC_SCALE_2V( DST, SRCA, SRCB )		\
do {						\
      (DST)[0] += (SRCA)[0] * (SRCB)[0];	\
      (DST)[1] += (SRCA)[1] * (SRCB)[1];	\
} while (0)

/** \brief Scalar multiplication */
#define SCALE_SCALAR_2V( DST, S, SRCB ) 	\
do {						\
      (DST)[0] = S * (SRCB)[0];			\
      (DST)[1] = S * (SRCB)[1];			\
} while (0)

/** \brief In-place scalar multiplication and addition */
#define ACC_SCALE_SCALAR_2V( DST, S, SRCB )	\
do {						\
      (DST)[0] += S * (SRCB)[0];		\
      (DST)[1] += S * (SRCB)[1];		\
} while (0)

/** \brief In-place scalar multiplication */
#define SELF_SCALE_SCALAR_2V( DST, S )		\
do {						\
      (DST)[0] *= S;				\
      (DST)[1] *= S;				\
} while (0)

/** \brief In-place scalar addition */
#define ACC_SCALAR_2V( DST, S ) 		\
do {						\
      (DST)[0] += S;				\
      (DST)[1] += S;				\
} while (0)

/** \brief Assignment */
#define ASSIGN_2V( V, V0, V1 )	\
do { 				\
    V[0] = V0; 			\
    V[1] = V1; 			\
} while(0)

/*@}*/


/** \brief Absolute value for integers */
#define ABSI(X)  ((X) < 0 ? -(X) : (X))
/** \brief Absolute value for single-precision floats */
#define ABSF(X)  ((X) < 0.0F ? -(X) : (X))
/** \brief Absolute value for double-precision floats */
#define ABSD(X)  ((X) < 0.0 ? -(X) : (X))


/** \brief Round a floating-point value to the nearest integer */
#define ROUNDF(X)  ( (X)<0.0F ? ((GLint) ((X)-0.5F)) : ((GLint) ((X)+0.5F)) )


/** \brief Compute ceiling of integer quotient of \p A divided by \p B */
#define CEILING( A, B )  ( (A) % (B) == 0 ? (A)/(B) : (A)/(B)+1 )


/** \brief Clamp X to [MIN,MAX]: */
#define CLAMP( X, MIN, MAX )  ( (X)<(MIN) ? (MIN) : ((X)>(MAX) ? (MAX) : (X)) )

/** \brief Assign X to CLAMP(X, MIN, MAX) */
#define CLAMP_SELF(x, mn, mx)  \
   ( (x)<(mn) ? ((x) = (mn)) : ((x)>(mx) ? ((x)=(mx)) : (x)) )



/** \brief Minimum of two values: */
#define MIN2( A, B )   ( (A)<(B) ? (A) : (B) )

/** \brief Maximum of two values: */
#define MAX2( A, B )   ( (A)>(B) ? (A) : (B) )

/** \brief Dot product of two 2-element vectors */
#define DOT2( a, b )  ( (a)[0]*(b)[0] + (a)[1]*(b)[1] )

/** \brief Dot product of two 3-element vectors */
#define DOT3( a, b )  ( (a)[0]*(b)[0] + (a)[1]*(b)[1] + (a)[2]*(b)[2] )

/** \brief Dot product of two 4-element vectors */
#define DOT4( a, b )  ( (a)[0]*(b)[0] + (a)[1]*(b)[1] + \
			(a)[2]*(b)[2] + (a)[3]*(b)[3] )

/** \brief Dot product of two 4-element vectors */
#define DOT4V(v,a,b,c,d) (v[0]*(a) + v[1]*(b) + v[2]*(c) + v[3]*(d))


/** \brief Cross product of two 3-element vectors */
#define CROSS3(n, u, v) 			\
do {						\
   (n)[0] = (u)[1]*(v)[2] - (u)[2]*(v)[1]; 	\
   (n)[1] = (u)[2]*(v)[0] - (u)[0]*(v)[2]; 	\
   (n)[2] = (u)[0]*(v)[1] - (u)[1]*(v)[0];	\
} while (0)



/**
 * \name Generic color packing macros
 *
 * \todo We may move these into texutil.h at some point.
 */
/*@{*/

#define PACK_COLOR_8888( a, b, c, d )					\
   (((a) << 24) | ((b) << 16) | ((c) << 8) | (d))

#define PACK_COLOR_888( a, b, c )					\
   (((a) << 16) | ((b) << 8) | (c))

#define PACK_COLOR_565( a, b, c )					\
   ((((a) & 0xf8) << 8) | (((b) & 0xfc) << 3) | (((c) & 0xf8) >> 3))

#define PACK_COLOR_1555( a, b, c, d )					\
   ((((b) & 0xf8) << 7) | (((c) & 0xf8) << 2) | (((d) & 0xf8) >> 3) |	\
    ((a) ? 0x8000 : 0))

#define PACK_COLOR_4444( a, b, c, d )					\
   ((((a) & 0xf0) << 8) | (((b) & 0xf0) << 4) | ((c) & 0xf0) | ((d) >> 4))

#define PACK_COLOR_88( a, b )						\
   (((a) << 8) | (b))

#define PACK_COLOR_332( a, b, c )					\
   (((a) & 0xe0) | (((b) & 0xe0) >> 3) | (((c) & 0xc0) >> 6))


#ifdef MESA_BIG_ENDIAN

#define PACK_COLOR_8888_LE( a, b, c, d )	PACK_COLOR_8888( d, c, b, a )

#define PACK_COLOR_565_LE( a, b, c )					\
   (((a) & 0xf8) | (((b) & 0xe0) >> 5) | (((b) & 0x1c) << 11) |		\
   (((c) & 0xf8) << 5))

#define PACK_COLOR_1555_LE( a, b, c, d )				\
   ((((b) & 0xf8) >> 1) | (((c) & 0xc0) >> 6) | (((c) & 0x38) << 10) |	\
    (((d) & 0xf8) << 5) | ((a) ? 0x80 : 0))

#define PACK_COLOR_4444_LE( a, b, c, d )	PACK_COLOR_4444( c, d, a, b )

#define PACK_COLOR_88_LE( a, b )		PACK_COLOR_88( b, a )

#else	/* little endian */

#define PACK_COLOR_8888_LE( a, b, c, d )	PACK_COLOR_8888( a, b, c, d )

#define PACK_COLOR_565_LE( a, b, c )		PACK_COLOR_565( a, b, c )

#define PACK_COLOR_1555_LE( a, b, c, d )	PACK_COLOR_1555( a, b, c, d )

#define PACK_COLOR_4444_LE( a, b, c, d )	PACK_COLOR_4444( a, b, c, d )

#define PACK_COLOR_88_LE( a, b )		PACK_COLOR_88( a, b )

#endif	/* endianness */

/*@}*/


#endif
