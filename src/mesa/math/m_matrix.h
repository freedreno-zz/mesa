/**
 * \file m_matrix.h
 * \brief Matrix operations.
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

/* $Id: m_matrix.h,v 1.4.8.3 2003/03/22 16:49:59 jrfonseca Exp $ */


#ifndef _M_MATRIX_H
#define _M_MATRIX_H



/**
 * \name Symbolic names to some of the entries in the matrix
 *
 * To help out with the rework of the viewport_map as a matrix transform.
 */
/*@{*/
#define MAT_SX 0
#define MAT_SY 5
#define MAT_SZ 10
#define MAT_TX 12
#define MAT_TY 13
#define MAT_TZ 14
/*@}*/

/**
 * \brief Different kinds of 4x4 transformation matrices.
 */
enum GLmatrixtype {
	MATRIX_GENERAL = 0,	/**< \brief general 4x4 matrix */
	MATRIX_IDENTITY = 1,	/**< \brief identity matrix */
	MATRIX_3D_NO_ROT = 2,	/**< \brief ortho projection and others... */
	MATRIX_PERSPECTIVE = 3,	/**< \brief perspective projection matrix */
	MATRIX_2D = 4,		/**< \brief 2-D transformation */
	MATRIX_2D_NO_ROT = 5,	/**< \brief 2-D scale & translate only */
	MATRIX_3D = 6,		/**< \brief 3-D transformation */
} ;


/**
 * \name Matrix flags
 */
/*@{*/

#define MAT_FLAG_IDENTITY       0	/**< \brief is an identity matrix flag.
					 *   (Not actualy used - the identity
					 *   matrix is identified by the abcense
					 /   of all other flags.) */
#define MAT_FLAG_GENERAL        0x1	/**< \brief is a general matrix flag */
#define MAT_FLAG_ROTATION       0x2	/**< \brief is a rotation matrix flag */
#define MAT_FLAG_TRANSLATION    0x4	/**< \brief is a translation matrix flag */
#define MAT_FLAG_UNIFORM_SCALE  0x8	/**< \brief is an uniform scaling matrix flag */
#define MAT_FLAG_GENERAL_SCALE  0x10	/**< \brief is a general scaling matrix flag */
#define MAT_FLAG_GENERAL_3D     0x20	/**< \brief general 3D matrix flag */
#define MAT_FLAG_PERSPECTIVE    0x40	/**< \brief is a perspective projection matrix flag */
#define MAT_FLAG_SINGULAR       0x80	/**< \brief is a singular matrix flag */
#define MAT_DIRTY_TYPE          0x100	/**< \brief matrix type is dirty */
#define MAT_DIRTY_FLAGS         0x200	/**< \brief matrix flags are dirty */
#define MAT_DIRTY_INVERSE       0x400	/**< \brief matrix inverse is dirty */

/** \brief angle preserving matrix flags mask */
#define MAT_FLAGS_ANGLE_PRESERVING (MAT_FLAG_ROTATION | \
				    MAT_FLAG_TRANSLATION | \
				    MAT_FLAG_UNIFORM_SCALE)

/** \brief length preserving matrix flags mask */
#define MAT_FLAGS_LENGTH_PRESERVING (MAT_FLAG_ROTATION | \
				     MAT_FLAG_TRANSLATION)

/** \brief 3D (non-perspective) matrix flags mask */
#define MAT_FLAGS_3D (MAT_FLAG_ROTATION | \
		      MAT_FLAG_TRANSLATION | \
		      MAT_FLAG_UNIFORM_SCALE | \
		      MAT_FLAG_GENERAL_SCALE | \
		      MAT_FLAG_GENERAL_3D)

/** \brief geometry related matrix flags mask */
#define MAT_FLAGS_GEOMETRY (MAT_FLAG_GENERAL | \
			    MAT_FLAG_ROTATION | \
			    MAT_FLAG_TRANSLATION | \
			    MAT_FLAG_UNIFORM_SCALE | \
			    MAT_FLAG_GENERAL_SCALE | \
			    MAT_FLAG_GENERAL_3D | \
			    MAT_FLAG_PERSPECTIVE | \
	                    MAT_FLAG_SINGULAR)

/** \brief dirty matrix flags mask */
#define MAT_DIRTY          (MAT_DIRTY_TYPE | \
			    MAT_DIRTY_FLAGS | \
			    MAT_DIRTY_INVERSE)

/*@}*/


/** 
 * \brief Test geometry related matrix flags.
 * 
 * \param mat a pointer to a GLmatrix structure.
 * \param a flags mask.
 *
 * \returns non-zero if all geometry related matrix flags are contained within
 * the mask, or zero otherwise.
 */ 
#define TEST_MAT_FLAGS(mat, a)  \
    ((MAT_FLAGS_GEOMETRY & (~(a)) & ((mat)->flags) ) == 0)


/**
 * \brief Matrix.
 */
typedef struct {
   GLfloat *m;		/**< \brief matrix, 16-byte aligned */
   GLfloat *inv;	/**< \brief optional inverse, 16-byte aligned */
   GLuint flags;	/**< \brief property flags */
   GLuint type;		/**< \brief one of the GLmatrixtype values */
} GLmatrix;




extern void
_math_matrix_ctr( GLmatrix *m );

extern void
_math_matrix_dtr( GLmatrix *m );

extern void
_math_matrix_alloc_inv( GLmatrix *m );

extern void
_math_matrix_mul_matrix( GLmatrix *dest, const GLmatrix *a, const GLmatrix *b );

extern void
_math_matrix_mul_floats( GLmatrix *dest, const GLfloat *b );

extern void
_math_matrix_loadf( GLmatrix *mat, const GLfloat *m );

extern void
_math_matrix_translate( GLmatrix *mat, GLfloat x, GLfloat y, GLfloat z );

extern void
_math_matrix_rotate( GLmatrix *m, GLfloat angle,
		     GLfloat x, GLfloat y, GLfloat z );

extern void
_math_matrix_scale( GLmatrix *mat, GLfloat x, GLfloat y, GLfloat z );

extern void
_math_matrix_ortho( GLmatrix *mat,
		    GLfloat left, GLfloat right,
		    GLfloat bottom, GLfloat top,
		    GLfloat nearval, GLfloat farval );

extern void
_math_matrix_frustum( GLmatrix *mat,
		      GLfloat left, GLfloat right,
		      GLfloat bottom, GLfloat top,
		      GLfloat nearval, GLfloat farval );

extern void
_math_matrix_set_identity( GLmatrix *dest );

extern void
_math_matrix_copy( GLmatrix *to, const GLmatrix *from );

extern void
_math_matrix_analyse( GLmatrix *mat );

extern void
_math_matrix_print( const GLmatrix *m );



/**
 * \name Related functions that don't actually operate on GLmatrix structs
 */
/*@{*/

extern void
_math_transposef( GLfloat to[16], const GLfloat from[16] );

extern void
_math_transposed( GLdouble to[16], const GLdouble from[16] );

extern void
_math_transposefd( GLfloat to[16], const GLdouble from[16] );


/*
 * Transform a point (column vector) by a matrix:   Q = M * P
 */
#define TRANSFORM_POINT( Q, M, P )					\
   Q[0] = M[0] * P[0] + M[4] * P[1] + M[8] *  P[2] + M[12] * P[3];	\
   Q[1] = M[1] * P[0] + M[5] * P[1] + M[9] *  P[2] + M[13] * P[3];	\
   Q[2] = M[2] * P[0] + M[6] * P[1] + M[10] * P[2] + M[14] * P[3];	\
   Q[3] = M[3] * P[0] + M[7] * P[1] + M[11] * P[2] + M[15] * P[3];


#define TRANSFORM_POINT3( Q, M, P )				\
   Q[0] = M[0] * P[0] + M[4] * P[1] + M[8] *  P[2] + M[12];	\
   Q[1] = M[1] * P[0] + M[5] * P[1] + M[9] *  P[2] + M[13];	\
   Q[2] = M[2] * P[0] + M[6] * P[1] + M[10] * P[2] + M[14];	\
   Q[3] = M[3] * P[0] + M[7] * P[1] + M[11] * P[2] + M[15];


/*
 * Transform a normal (row vector) by a matrix:  [NX NY NZ] = N * MAT
 */
#define TRANSFORM_NORMAL( TO, N, MAT )				\
do {								\
   TO[0] = N[0] * MAT[0] + N[1] * MAT[1] + N[2] * MAT[2];	\
   TO[1] = N[0] * MAT[4] + N[1] * MAT[5] + N[2] * MAT[6];	\
   TO[2] = N[0] * MAT[8] + N[1] * MAT[9] + N[2] * MAT[10];	\
} while (0)


/*@}*/


#endif
