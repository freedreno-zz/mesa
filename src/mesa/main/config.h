/**
 * \file config.h
 * \brief Tunable configuration parameters.
 */

/*
 * Mesa 3-D graphics library
 * Version:  4.1
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

/* $Id: config.h,v 1.42.4.5 2003/03/23 03:51:34 jrfonseca Exp $ */


#ifndef CONFIG_H
#define CONFIG_H

#ifdef HAVE_CONFIG_H
#include "conf.h"
#endif


/**
 * \name OpenGL implementation limits
 */
/*@{*/

/** \brief Maximum modelview matrix stack depth */
#define MAX_MODELVIEW_STACK_DEPTH 32

/** \brief Maximum projection matrix stack depth */
#define MAX_PROJECTION_STACK_DEPTH 32

/** \brief Maximum texture matrix stack depth */
#define MAX_TEXTURE_STACK_DEPTH 10

/** \brief Maximum color matrix stack depth */
#define MAX_COLOR_STACK_DEPTH 4

/** \brief Vertex program matrices */
#define MAX_PROGRAM_MATRICES 8
/** \brief Vertex program stack depth */
#define MAX_PROGRAM_STACK_DEPTH 4

/** \brief Maximum attribute stack depth */
#define MAX_ATTRIB_STACK_DEPTH 16

/** \brief Maximum client attribute stack depth */
#define MAX_CLIENT_ATTRIB_STACK_DEPTH 16

/** \brief Maximum recursion depth of display list calls */
#define MAX_LIST_NESTING 64

/** \brief Maximum number of lights */
#define MAX_LIGHTS 8

/** \brief Maximum user-defined clipping planes */
#define MAX_CLIP_PLANES 6

/** \brief Maximum pixel map lookup table size */
#define MAX_PIXEL_MAP_TABLE 256

/** \brief Number of auxillary color buffers */
#define NUM_AUX_BUFFERS 0

/** \brief Maximum order (degree) of curves */
#ifdef AMIGA
#   define MAX_EVAL_ORDER 12
#else
#   define MAX_EVAL_ORDER 30
#endif

/** \brief Maximum Name stack depth */
#define MAX_NAME_STACK_DEPTH 64

/** \brief Minimum point size */
#define MIN_POINT_SIZE 1.0
/** \brief Maximum point size */
#define MAX_POINT_SIZE 20.0
/** \brief Point size granularity */
#define POINT_SIZE_GRANULARITY 0.1

/** \brief Minimum line width */
#define MIN_LINE_WIDTH 1.0
/** \brief Maximum line width */
#define MAX_LINE_WIDTH 10.0
/** \brief Line width granularity */
#define LINE_WIDTH_GRANULARITY 0.1

/** \brief Max texture palette / color table size */
#define MAX_COLOR_TABLE_SIZE 256

/** \brief Number of 1D/2D texture mipmap levels */
#define MAX_TEXTURE_LEVELS 12

/** \brief Number of 3D texture mipmap levels */
#define MAX_3D_TEXTURE_LEVELS 8

/** \brief Number of cube texture mipmap levels - GL_ARB_texture_cube_map */
#define MAX_CUBE_TEXTURE_LEVELS 12

/** \brief Maximum rectangular texture size - GL_NV_texture_rectangle */
#define MAX_TEXTURE_RECT_SIZE 2048

/** \brief Number of texture units - GL_ARB_multitexture */
#define MAX_TEXTURE_UNITS 8

/** \brief Maximum viewport/image width */
#define MAX_WIDTH 2048
/** \brief Maximum viewport/image height */
#define MAX_HEIGHT 2048

/** \brief Maxmimum size for CVA.  May be overridden by the drivers.  */
#define MAX_ARRAY_LOCK_SIZE 3000

/** \brief Subpixel precision for antialiasing, window coordinate snapping */
#define SUB_PIXEL_BITS 4

/** \brief Size of histogram tables */
#define HISTOGRAM_TABLE_SIZE 256

/** \brief Max convolution filter width */
#define MAX_CONVOLUTION_WIDTH 9
/** \brief Max convolution filter height */
#define MAX_CONVOLUTION_HEIGHT 9

/** \brief GL_ARB_texture_compression */
#define MAX_COMPRESSED_TEXTURE_FORMATS 25

/** \brief GL_EXT_texture_filter_anisotropic */
#define MAX_TEXTURE_MAX_ANISOTROPY 16.0

/** \brief GL_EXT_texture_lod_bias */
#define MAX_TEXTURE_LOD_BIAS 4.0

/*@}*/


/**
 * \name Mesa-specific parameters
 */
/*@{*/


/**
 * \brief Bits per accumulation buffer color component:  8, 16 or 32
 */
#define ACCUM_BITS 16

/**
 * \brief Bits per depth buffer value.  
 *
 * Any reasonable value up to 31 will work.  32 doesn't work because of integer
 * overflow problems in the rasterizer code.
 */
#ifndef DEFAULT_SOFTWARE_DEPTH_BITS
#define DEFAULT_SOFTWARE_DEPTH_BITS 16
#endif
/** \brief Depth buffer data type */
#if DEFAULT_SOFTWARE_DEPTH_BITS <= 16
#define DEFAULT_SOFTWARE_DEPTH_TYPE GLushort
#else
#define DEFAULT_SOFTWARE_DEPTH_TYPE GLuint
#endif


/**
 * \brief Bits per stencil value: 8
 */
#define STENCIL_BITS 8


/**
 * \brief Bits per color channel:  8, 16 or 32
 */
#ifndef CHAN_BITS
#define CHAN_BITS 8
#endif


/*
 * Color channel component order
 * 
 * \note Changes will almost certainly cause problems at this time.
 */
#define RCOMP 0
#define GCOMP 1
#define BCOMP 2
#define ACOMP 3


/*
 * Enable/disable features (blocks of code) by setting FEATURE_xyz to 0 or 1.
 */
#if _HAVE_FULL_GL
#define FEATURE_NV_vertex_program 1
#define FEATURE_userclip 1
#define FEATURE_texgen 1
#define FEATURE_windowpos 1
#endif

/*@}*/

#endif /* CONFIG_H */
