/**
 * \file mtypes.h
 * \brief Main Mesa data structures.
 *
 * Please try to mark derived values with a leading underscore ('_').
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

/* $Id: mtypes.h,v 1.97.4.7 2003/03/22 08:43:26 keithw Exp $ */


#ifndef TYPES_H
#define TYPES_H


#include "glheader.h"
#include "config.h"		/* Hardwired parameters */
#include "glapitable.h"
#include "glthread.h"

#include "math/m_matrix.h"	/* GLmatrix */

#if defined(MESA_TRACE)
#include "Trace/tr_context.h"
#endif


/**
 * \brief Color channel data type.
 */
#if CHAN_BITS == 8
   typedef GLubyte GLchan;
#define CHAN_MAX 255
#define CHAN_MAXF 255.0F
#define CHAN_TYPE GL_UNSIGNED_BYTE
#elif CHAN_BITS == 16
   typedef GLushort GLchan;
#define CHAN_MAX 65535
#define CHAN_MAXF 65535.0F
#define CHAN_TYPE GL_UNSIGNED_SHORT
#elif CHAN_BITS == 32
   typedef GLfloat GLchan;
#define CHAN_MAX 1.0
#define CHAN_MAXF 1.0F
#define CHAN_TYPE GL_FLOAT
#else
#error "illegal number of color channel bits"
#endif


/**
 * \brief Accumulation buffer data type.
 */
#if ACCUM_BITS==8
   typedef GLbyte GLaccum;
#elif ACCUM_BITS==16
   typedef GLshort GLaccum;
#elif ACCUM_BITS==32
   typedef GLfloat GLaccum;
#else
#  error "illegal number of accumulation bits"
#endif


/**
 * \brief Stencil buffer data type.
 */
#if STENCIL_BITS==8
   typedef GLubyte GLstencil;
#  define STENCIL_MAX 0xff
#elif STENCIL_BITS==16
   typedef GLushort GLstencil;
#  define STENCIL_MAX 0xffff
#else
#  error "illegal number of stencil bits"
#endif


/**
 * \brief Depth buffer data type.
 *
 * \note Must be 32-bits!
 */
typedef GLuint GLdepth;  


/**
 * \brief Fixed point data type.
 */
typedef int GLfixed;



/**
 * \name Some forward type declarations
 */
/*@{*/
struct _mesa_HashTable;
struct gl_texture_image;
struct gl_texture_object;
typedef struct __GLcontextRec GLcontext;
typedef struct __GLcontextModesRec GLvisual;
typedef struct gl_frame_buffer GLframebuffer;
/*@}*/



/**
 * These define the aliases between numbered vertex attributes and
 * conventional OpenGL vertex attributes.  We use these values in
 * quite a few places.  
 *
 * New in Mesa 4.1.
 */
enum {
	VERT_ATTRIB_POS = 0,
	VERT_ATTRIB_WEIGHT = 1,
	VERT_ATTRIB_NORMAL = 2,
	VERT_ATTRIB_COLOR0 = 3,
	VERT_ATTRIB_COLOR1 = 4,
	VERT_ATTRIB_FOG = 5,
	VERT_ATTRIB_SIX = 6,
	VERT_ATTRIB_SEVEN = 7,
	VERT_ATTRIB_TEX0 = 8,
	VERT_ATTRIB_TEX1 = 9,
	VERT_ATTRIB_TEX2 = 10,
	VERT_ATTRIB_TEX3 = 11,
	VERT_ATTRIB_TEX4 = 12,
	VERT_ATTRIB_TEX5 = 13,
	VERT_ATTRIB_TEX6 = 14,
	VERT_ATTRIB_TEX7 = 15,
	VERT_ATTRIB_MAX = 16,
} ;

/* These are used in bitfields in many places */
#define VERT_BIT_POS     (1 << VERT_ATTRIB_POS)
#define VERT_BIT_WEIGHT  (1 << VERT_ATTRIB_WEIGHT)
#define VERT_BIT_NORMAL  (1 << VERT_ATTRIB_NORMAL)
#define VERT_BIT_COLOR0  (1 << VERT_ATTRIB_COLOR0)
#define VERT_BIT_COLOR1  (1 << VERT_ATTRIB_COLOR1)
#define VERT_BIT_FOG     (1 << VERT_ATTRIB_FOG)
#define VERT_BIT_SIX     (1 << VERT_ATTRIB_SIX)
#define VERT_BIT_SEVEN   (1 << VERT_ATTRIB_SEVEN)
#define VERT_BIT_TEX0    (1 << VERT_ATTRIB_TEX0)
#define VERT_BIT_TEX1    (1 << VERT_ATTRIB_TEX1)
#define VERT_BIT_TEX2    (1 << VERT_ATTRIB_TEX2)
#define VERT_BIT_TEX3    (1 << VERT_ATTRIB_TEX3)
#define VERT_BIT_TEX4    (1 << VERT_ATTRIB_TEX4)
#define VERT_BIT_TEX5    (1 << VERT_ATTRIB_TEX5)
#define VERT_BIT_TEX6    (1 << VERT_ATTRIB_TEX6)
#define VERT_BIT_TEX7    (1 << VERT_ATTRIB_TEX7)

#define VERT_BIT_TEX(u)  (1 << (VERT_ATTRIB_TEX0 + (u)))



/**
 * Maximum number of temporary vertices required for clipping.  
 *
 * Used in array_cache and tnl modules.
 */
#define MAX_CLIPPED_VERTICES ((2 * (6 + MAX_CLIP_PLANES))+1)


/**
 * \brief Data structure for color tables
 */
struct gl_color_table {
   GLenum Format;         /**< \brief GL_ALPHA, GL_RGB, GL_RGB, etc */
   GLenum IntFormat;
   GLuint Size;           /**< \brief number of entries (rows) in table */
   GLvoid *Table;         /**< \brief either GLfloat * or GLchan * */
   GLboolean FloatTable;  /**< \brief are entries stored as floats? */
   GLubyte RedSize;
   GLubyte GreenSize;
   GLubyte BlueSize;
   GLubyte AlphaSize;
   GLubyte LuminanceSize;
   GLubyte IntensitySize;
};


/*
 * Bit flags used for updating material values.
 */
#define FRONT_AMBIENT_BIT     0x1
#define BACK_AMBIENT_BIT      0x2
#define FRONT_DIFFUSE_BIT     0x4
#define BACK_DIFFUSE_BIT      0x8
#define FRONT_SPECULAR_BIT   0x10
#define BACK_SPECULAR_BIT    0x20
#define FRONT_EMISSION_BIT   0x40
#define BACK_EMISSION_BIT    0x80
#define FRONT_SHININESS_BIT 0x100
#define BACK_SHININESS_BIT  0x200
#define FRONT_INDEXES_BIT   0x400
#define BACK_INDEXES_BIT    0x800

#define FRONT_MATERIAL_BITS	(FRONT_EMISSION_BIT | FRONT_AMBIENT_BIT | \
				 FRONT_DIFFUSE_BIT | FRONT_SPECULAR_BIT | \
				 FRONT_SHININESS_BIT | FRONT_INDEXES_BIT)

#define BACK_MATERIAL_BITS	(BACK_EMISSION_BIT | BACK_AMBIENT_BIT | \
				 BACK_DIFFUSE_BIT | BACK_SPECULAR_BIT | \
				 BACK_SHININESS_BIT | BACK_INDEXES_BIT)

#define ALL_MATERIAL_BITS	(FRONT_MATERIAL_BITS | BACK_MATERIAL_BITS)




#define EXP_TABLE_SIZE 512	/**< \brief Specular exponent lookup table sizes */
#define SHINE_TABLE_SIZE 256	/**< \brief Material shininess lookup table sizes */

/**
 * \brief Material shininess lookup table.
 */
struct gl_shine_tab {
   struct gl_shine_tab *next, *prev;
   GLfloat tab[SHINE_TABLE_SIZE+1];
   GLfloat shininess;
   GLuint refcount;
};


/**
 * \brief Light.
 */
struct gl_light {
   struct gl_light *next;	/**< \brief double linked list with sentinel */
   struct gl_light *prev;

   GLfloat Ambient[4];		/**< \brief ambient color */
   GLfloat Diffuse[4];		/**< \brief diffuse color */
   GLfloat Specular[4];		/**< \brief specular color */
   GLfloat EyePosition[4];	/**< \brief position in eye coordinates */
   GLfloat EyeDirection[4];	/**< \brief spotlight dir in eye coordinates */
   GLfloat SpotExponent;
   GLfloat SpotCutoff;		/**< \brief in degress */
   GLfloat _CosCutoff;		/**< \brief = MAX(0, cos(SpotCutoff)) */
   GLfloat ConstantAttenuation;
   GLfloat LinearAttenuation;
   GLfloat QuadraticAttenuation;
   GLboolean Enabled;		/**< \brief On/off flag */

   /** 
    * \name Derived fields
    */
   /*@{*/
   GLuint _Flags;		/**< \brief State */

   GLfloat _Position[4];	/**< \brief position in eye/obj coordinates */
   GLfloat _VP_inf_norm[3];	/**< \brief Norm direction to infinite light */
   GLfloat _h_inf_norm[3];	/**< \brief Norm( _VP_inf_norm + <0,0,1> ) */
   GLfloat _NormDirection[4];	/**< \brief normalized spotlight direction */
   GLfloat _VP_inf_spot_attenuation;

   GLfloat _SpotExpTable[EXP_TABLE_SIZE][2];  /**< \brief to replace a pow() call */
   GLfloat _MatAmbient[2][3];	/**< \brief material ambient * light ambient */
   GLfloat _MatDiffuse[2][3];	/**< \brief material diffuse * light diffuse */
   GLfloat _MatSpecular[2][3];	/**< \brief material spec * light specular */
   GLfloat _dli;		/**< \brief CI diffuse light intensity */
   GLfloat _sli;		/**< \brief CI specular light intensity */
   /*@}*/
};


/**
 * \brief Light model.
 */
struct gl_lightmodel {
   GLfloat Ambient[4];		/**< \brief ambient color */
   GLboolean LocalViewer;	/**< \brief Local (or infinite) view point? */
   GLboolean TwoSide;		/**< \brief Two (or one) sided lighting? */
   GLenum ColorControl;		/**< \brief either GL_SINGLE_COLOR
				 *    or GL_SEPARATE_SPECULAR_COLOR */
};


/**
 * \brief Material.
 */
struct gl_material
{
   GLfloat Ambient[4];
   GLfloat Diffuse[4];
   GLfloat Specular[4];
   GLfloat Emission[4];
   GLfloat Shininess;
   GLfloat AmbientIndex;	/**< \brief for color index lighting */
   GLfloat DiffuseIndex;	/**< \brief for color index lighting */
   GLfloat SpecularIndex;	/**< \brief for color index lighting */
};


/**
 * \brief Accumulation buffer attributes.
 */
struct gl_accum_attrib {
   GLfloat ClearColor[4];	/**< \brief Accumulation buffer clear color */
};


/*
 * Used in _DrawDestMask and _ReadSrcMask below to identify color buffers.
 */
#define FRONT_LEFT_BIT  0x1
#define FRONT_RIGHT_BIT 0x2
#define BACK_LEFT_BIT   0x4
#define BACK_RIGHT_BIT  0x8
#define AUX0_BIT        0x10
#define AUX1_BIT        0x20
#define AUX2_BIT        0x40
#define AUX3_BIT        0x80


/**
 * \brief Color buffers attributes.
 */
struct gl_colorbuffer_attrib {
   GLuint ClearIndex;			/**< \brief Index to use for glClear */
   GLclampf ClearColor[4];		/**< \brief Color to use for glClear */

   GLuint IndexMask;			/**< \brief Color index write mask */
   GLubyte ColorMask[4];		/**< \brief Each flag is 0xff or 0x0 */

   GLenum DrawBuffer;		/**< \brief Which buffer to draw into */
   GLubyte _DrawDestMask;	/**< \brief bitwise-OR of FRONT/BACK_LEFT/RIGHT_BITs */

   /** 
    * \name alpha testing
    */
   /*@{*/
   GLboolean AlphaEnabled;		/**< \brief Alpha test enabled flag */
   GLenum AlphaFunc;			/**< \brief Alpha test function */
   GLclampf AlphaRef;
   /*@}*/

   /** 
    * \name blending
    */
   /*@{*/
   GLboolean BlendEnabled;		/**< \brief Blending enabled flag */
   GLenum BlendSrcRGB;			/**< \brief Blending source operator */
   GLenum BlendDstRGB;			/**< \brief Blending destination operator */
   GLenum BlendSrcA;			/**< \brief GL_INGR_blend_func_separate */
   GLenum BlendDstA;			/**< \brief GL_INGR_blend_func_separate */
   GLenum BlendEquation;
   GLfloat BlendColor[4];
   /*@}*/

   /** 
    * \name logic op
    */
   /*@{*/
   GLenum LogicOp;			/**< \brief Logic operator */
   GLboolean IndexLogicOpEnabled;	/**< \brief Color index logic op enabled flag */
   GLboolean ColorLogicOpEnabled;	/**< \brief RGBA logic op enabled flag */
   /*@}*/

   GLboolean DitherFlag;		/**< \brief Dither enable flag */
};


/**
 * \brief Current attributes.
 */
struct gl_current_attrib {
   /**
    * \name Values valid only when FLUSH_VERTICES has been called.
    */
   /*@{*/
   GLfloat Attrib[VERT_ATTRIB_MAX][4];		/**< \brief Current vertex attributes
						  *  indexed by VERT_ATTRIB_* */
   GLuint Index;				/**< \brief Current color index */
   GLboolean EdgeFlag;				/**< \brief Current edge flag */
   /*@}*/

   /**
    * \name Values are always valid.  
    * 
    * \note BTW, note how similar this set of attributes is to the SWvertex datatype
    * in the software rasterizer...
    */
   /*@{*/
   GLfloat RasterPos[4];			/**< \brief Current raster position */
   GLfloat RasterDistance;			/**< \brief Current raster distance */
   GLfloat RasterColor[4];			/**< \brief Current raster color */
   GLfloat RasterSecondaryColor[4];             /**< \brief Current raster secondary color */
   GLuint RasterIndex;				/**< \brief Current raster index */
   GLfloat RasterTexCoords[MAX_TEXTURE_UNITS][4];/**< \brief Current raster texcoords */
   GLboolean RasterPosValid;			/**< \brief Raster pos valid flag */
   /*@}*/
};


/**
 * \brief Depth buffer attributes.
 */
struct gl_depthbuffer_attrib {
   GLenum Func;			/**< \brief Function for depth buffer compare */
   GLfloat Clear;		/**< \brief Value to clear depth buffer to */
   GLboolean Test;		/**< \brief Depth buffering enabled flag */
   GLboolean Mask;		/**< \brief Depth buffer writable? */
   GLboolean OcclusionTest;	/**< \brief GL_HP_occlusion_test */
};


/**
 * \brief glEnable()/glDisable() attributes.
 */
struct gl_enable_attrib {
   GLboolean AlphaTest;
   GLboolean AutoNormal;
   GLboolean Blend;
   GLuint ClipPlanes;
   GLboolean ColorMaterial;
   GLboolean Convolution1D;
   GLboolean Convolution2D;
   GLboolean Separable2D;
   GLboolean CullFace;
   GLboolean DepthTest;
   GLboolean Dither;
   GLboolean Fog;
   GLboolean Histogram;
   GLboolean Light[MAX_LIGHTS];
   GLboolean Lighting;
   GLboolean LineSmooth;
   GLboolean LineStipple;
   GLboolean IndexLogicOp;
   GLboolean ColorLogicOp;
   GLboolean Map1Color4;
   GLboolean Map1Index;
   GLboolean Map1Normal;
   GLboolean Map1TextureCoord1;
   GLboolean Map1TextureCoord2;
   GLboolean Map1TextureCoord3;
   GLboolean Map1TextureCoord4;
   GLboolean Map1Vertex3;
   GLboolean Map1Vertex4;
   GLboolean Map1Attrib[16];  /* GL_NV_vertex_program */
   GLboolean Map2Color4;
   GLboolean Map2Index;
   GLboolean Map2Normal;
   GLboolean Map2TextureCoord1;
   GLboolean Map2TextureCoord2;
   GLboolean Map2TextureCoord3;
   GLboolean Map2TextureCoord4;
   GLboolean Map2Vertex3;
   GLboolean Map2Vertex4;
   GLboolean Map2Attrib[16];  /* GL_NV_vertex_program */
   GLboolean MinMax;
   GLboolean Normalize;
   GLboolean PixelTexture;
   GLboolean PointSmooth;
   GLboolean PolygonOffsetPoint;
   GLboolean PolygonOffsetLine;
   GLboolean PolygonOffsetFill;
   GLboolean PolygonSmooth;
   GLboolean PolygonStipple;
   GLboolean RescaleNormals;
   GLboolean Scissor;
   GLboolean Stencil;
   GLboolean MultisampleEnabled;      /* GL_ARB_multisample */
   GLboolean SampleAlphaToCoverage;   /* GL_ARB_multisample */
   GLboolean SampleAlphaToOne;        /* GL_ARB_multisample */
   GLboolean SampleCoverage;          /* GL_ARB_multisample */
   GLboolean SampleCoverageInvert;    /* GL_ARB_multisample */
   GLboolean RasterPositionUnclipped; /* GL_IBM_rasterpos_clip */
   GLuint Texture[MAX_TEXTURE_UNITS];
   GLuint TexGen[MAX_TEXTURE_UNITS];
   GLboolean VertexProgram;           /* GL_NV_vertex_program */
   GLboolean VertexProgramPointSize;  /* GL_NV_vertex_program */
   GLboolean VertexProgramTwoSide;    /* GL_NV_vertex_program */
   GLboolean PointSprite;             /* GL_NV_point_sprite */
};


/**
 * \brief Eval attributes.
 */
struct gl_eval_attrib {
   /**
    * \name Enable bits 
    */
   /*@{*/
   GLboolean Map1Color4;
   GLboolean Map1Index;
   GLboolean Map1Normal;
   GLboolean Map1TextureCoord1;
   GLboolean Map1TextureCoord2;
   GLboolean Map1TextureCoord3;
   GLboolean Map1TextureCoord4;
   GLboolean Map1Vertex3;
   GLboolean Map1Vertex4;
   GLboolean Map1Attrib[16];  /* GL_NV_vertex_program */
   GLboolean Map2Color4;
   GLboolean Map2Index;
   GLboolean Map2Normal;
   GLboolean Map2TextureCoord1;
   GLboolean Map2TextureCoord2;
   GLboolean Map2TextureCoord3;
   GLboolean Map2TextureCoord4;
   GLboolean Map2Vertex3;
   GLboolean Map2Vertex4;
   GLboolean Map2Attrib[16];  /* GL_NV_vertex_program */
   GLboolean AutoNormal;
   /*@}*/
   
   /**
    * \name Map Grid endpoints and divisions and calculated du values
    */
   /*@{*/
   GLint MapGrid1un;
   GLfloat MapGrid1u1, MapGrid1u2, MapGrid1du;
   GLint MapGrid2un, MapGrid2vn;
   GLfloat MapGrid2u1, MapGrid2u2, MapGrid2du;
   GLfloat MapGrid2v1, MapGrid2v2, MapGrid2dv;
   /*@}*/
};


/**
 * \brief Fog attributes.
 */
struct gl_fog_attrib {
   GLboolean Enabled;		/**< \brief Fog enabled flag */
   GLfloat Color[4];		/**< \brief Fog color */
   GLfloat Density;		/**< \brief Density >= 0.0 */
   GLfloat Start;		/**< \brief Start distance in eye coords */
   GLfloat End;			/**< \brief End distance in eye coords */
   GLfloat Index;		/**< \brief Fog index */
   GLenum Mode;			/**< \brief Fog mode */
   GLboolean ColorSumEnabled;
   GLenum FogCoordinateSource;  /**< \brief GL_EXT_fog_coord */
};


/** 
 * \brief Hint attributes.
 * 
 * Values are always one of GL_FASTEST, GL_NICEST, or GL_DONT_CARE.
 */
struct gl_hint_attrib {
   GLenum PerspectiveCorrection;
   GLenum PointSmooth;
   GLenum LineSmooth;
   GLenum PolygonSmooth;
   GLenum Fog;
   GLenum ClipVolumeClipping;   /**< \brief GL_EXT_clip_volume_hint */
   GLenum TextureCompression;   /**< \brief GL_ARB_texture_compression */
   GLenum GenerateMipmap;       /**< \brief GL_SGIS_generate_mipmap */
};


/**
 * \brief Histogram attributes.
 */
struct gl_histogram_attrib {
   GLuint Width;				/**< \brief number of table entries */
   GLint Format;				/**< \brief GL_ALPHA, GL_RGB, etc */
   GLuint Count[HISTOGRAM_TABLE_SIZE][4];	/**< \brief the histogram */
   GLboolean Sink;				/**< \brief terminate image transfer? */
   GLubyte RedSize;				/**< \brief Bits per counter */
   GLubyte GreenSize;
   GLubyte BlueSize;
   GLubyte AlphaSize;
   GLubyte LuminanceSize;
};


struct gl_minmax_attrib {
   GLenum Format;
   GLboolean Sink;
   GLfloat Min[4], Max[4];   /**< \brief RGBA */
};


struct gl_convolution_attrib {
   GLenum Format;
   GLenum InternalFormat;
   GLuint Width;
   GLuint Height;
   GLfloat Filter[MAX_CONVOLUTION_WIDTH * MAX_CONVOLUTION_HEIGHT * 4];
};


#define LIGHT_SPOT         0x1
#define LIGHT_LOCAL_VIEWER 0x2
#define LIGHT_POSITIONAL   0x4
#define LIGHT_NEED_VERTICES (LIGHT_POSITIONAL|LIGHT_LOCAL_VIEWER)

struct gl_light_attrib {
   struct gl_light Light[MAX_LIGHTS];	/**< \brief Array of lights */
   struct gl_lightmodel Model;		/**< \brief Lighting model */

   /**
    * Must flush FLUSH_VERTICES before referencing:
    */
   /*@{*/
   struct gl_material Material[2];	/**< \brief Material 0=front, 1=back */
   /*@}*/

   GLboolean Enabled;			/**< \brief Lighting enabled flag */
   GLenum ShadeModel;			/**< \brief GL_FLAT or GL_SMOOTH */
   GLenum ColorMaterialFace;		/**< \brief GL_FRONT, BACK or FRONT_AND_BACK */
   GLenum ColorMaterialMode;		/**< \brief GL_AMBIENT, GL_DIFFUSE, etc */
   GLuint ColorMaterialBitmask;		/**< \brief bitmask formed from Face and Mode */
   GLboolean ColorMaterialEnabled;

   struct gl_light EnabledList;         /**< \brief List sentinel */

   /** 
    * Derived for optimizations: 
    */
   /*@{*/
   GLboolean _NeedVertices;		/**< \brief Use fast shader? */
   GLuint  _Flags;		        /**< \brief LIGHT_* flags, see above */
   GLfloat _BaseColor[2][3];
   /*@}*/
};


/**
 * \brief Line attributes.
 */
struct gl_line_attrib {
   GLboolean SmoothFlag;	/**< \brief GL_LINE_SMOOTH enabled? */
   GLboolean StippleFlag;	/**< \brief GL_LINE_STIPPLE enabled? */
   GLushort StipplePattern;	/**< \brief Stipple pattern */
   GLint StippleFactor;		/**< \brief Stipple repeat factor */
   GLfloat Width;		/**< \brief Line width */
   GLfloat _Width;		/**< \brief Clamped Line width */
};


struct gl_list_attrib {
   GLuint ListBase;
};


struct gl_list_opcode {
   GLuint size;
   void (*execute)( GLcontext *ctx, void *data );
   void (*destroy)( GLcontext *ctx, void *data );
   void (*print)( GLcontext *ctx, void *data );
};

#define GL_MAX_EXT_OPCODES 16

struct gl_list_extensions {
   struct gl_list_opcode opcode[GL_MAX_EXT_OPCODES];
   GLuint nr_opcodes;
};


struct gl_multisample_attrib {
   GLboolean Enabled;
   GLboolean SampleAlphaToCoverage;
   GLboolean SampleAlphaToOne;
   GLboolean SampleCoverage;
   GLfloat SampleCoverageValue;
   GLboolean SampleCoverageInvert;
};


/**
 * \brief Pixel attributes.
 */
struct gl_pixel_attrib {
   GLenum ReadBuffer;		/**< \brief src buffer for glRead/CopyPixels */
   GLubyte _ReadSrcMask;	/**< \brief Not really a mask, but like _DrawDestMask
				  * May be: FRONT_LEFT_BIT, BACK_LEFT_BIT,
				  * FRONT_RIGHT_BIT or BACK_RIGHT_BIT. */
   GLfloat RedBias, RedScale;
   GLfloat GreenBias, GreenScale;
   GLfloat BlueBias, BlueScale;
   GLfloat AlphaBias, AlphaScale;
   GLfloat DepthBias, DepthScale;
   GLint IndexShift, IndexOffset;
   GLboolean MapColorFlag;
   GLboolean MapStencilFlag;
   GLfloat ZoomX, ZoomY;
   /* XXX move these out of gl_pixel_attrib */
   GLint MapStoSsize;		/**< \brief Size of each pixel map */
   GLint MapItoIsize;
   GLint MapItoRsize;
   GLint MapItoGsize;
   GLint MapItoBsize;
   GLint MapItoAsize;
   GLint MapRtoRsize;
   GLint MapGtoGsize;
   GLint MapBtoBsize;
   GLint MapAtoAsize;
   GLint MapStoS[MAX_PIXEL_MAP_TABLE];	/**< \brief Pixel map tables */
   GLint MapItoI[MAX_PIXEL_MAP_TABLE];
   GLfloat MapItoR[MAX_PIXEL_MAP_TABLE];
   GLfloat MapItoG[MAX_PIXEL_MAP_TABLE];
   GLfloat MapItoB[MAX_PIXEL_MAP_TABLE];
   GLfloat MapItoA[MAX_PIXEL_MAP_TABLE];
   GLubyte MapItoR8[MAX_PIXEL_MAP_TABLE];  /**< \brief converted to 8-bit color */
   GLubyte MapItoG8[MAX_PIXEL_MAP_TABLE];
   GLubyte MapItoB8[MAX_PIXEL_MAP_TABLE];
   GLubyte MapItoA8[MAX_PIXEL_MAP_TABLE];
   GLfloat MapRtoR[MAX_PIXEL_MAP_TABLE];
   GLfloat MapGtoG[MAX_PIXEL_MAP_TABLE];
   GLfloat MapBtoB[MAX_PIXEL_MAP_TABLE];
   GLfloat MapAtoA[MAX_PIXEL_MAP_TABLE];
   /** GL_EXT_histogram */
   GLboolean HistogramEnabled;
   GLboolean MinMaxEnabled;
   /** GL_SGIS_pixel_texture */
   GLboolean PixelTextureEnabled;
   GLenum FragmentRgbSource;
   GLenum FragmentAlphaSource;
   /** GL_SGI_color_matrix */
   GLfloat PostColorMatrixScale[4];  /**< \brief RGBA */
   GLfloat PostColorMatrixBias[4];   /**< \brief RGBA */
   /** GL_SGI_color_table */
   GLfloat ColorTableScale[4];
   GLfloat ColorTableBias[4];
   GLboolean ColorTableEnabled;
   GLfloat PCCTscale[4];
   GLfloat PCCTbias[4];
   GLboolean PostConvolutionColorTableEnabled;
   GLfloat PCMCTscale[4];
   GLfloat PCMCTbias[4];
   GLboolean PostColorMatrixColorTableEnabled;
   /** Convolution */
   GLboolean Convolution1DEnabled;
   GLboolean Convolution2DEnabled;
   GLboolean Separable2DEnabled;
   GLfloat ConvolutionBorderColor[3][4];
   GLenum ConvolutionBorderMode[3];
   GLfloat ConvolutionFilterScale[3][4];
   GLfloat ConvolutionFilterBias[3][4];
   GLfloat PostConvolutionScale[4];  /**< \brief RGBA */
   GLfloat PostConvolutionBias[4];   /**< \brief RGBA */
};


/**
 * \brief Point attributes.
 */
struct gl_point_attrib {
   GLboolean SmoothFlag;	/**< \brief True if GL_POINT_SMOOTH is enabled */
   GLfloat Size;		/**< \brief User-specified point size */
   GLfloat _Size;		/**< \brief Size clamped to Const.Min/MaxPointSize */
   GLfloat Params[3];		/**< \brief GL_EXT_point_parameters */
   GLfloat MinSize, MaxSize;	/**< \brief GL_EXT_point_parameters */
   GLfloat Threshold;		/**< \brief GL_EXT_point_parameters */
   GLboolean _Attenuated;	/**< \brief True if Params != [1, 0, 0] */
   GLboolean PointSprite;	/**< \brief GL_NV_point_sprite */
   GLboolean CoordReplace[MAX_TEXTURE_UNITS]; /**< \brief GL_NV_point_sprite */
   GLenum SpriteRMode;		/**< \brief GL_NV_point_sprite */
};


/**
 * \brief Polygon attributes.
 */
struct gl_polygon_attrib {
   GLenum FrontFace;		/**< \brief Either GL_CW or GL_CCW */
   GLenum FrontMode;		/**< \brief Either GL_POINT, GL_LINE or GL_FILL */
   GLenum BackMode;		/**< \brief Either GL_POINT, GL_LINE or GL_FILL */
   GLboolean _FrontBit;		/**< \brief 0=GL_CCW, 1=GL_CW */
   GLboolean CullFlag;		/**< \brief Culling on/off flag */
   GLboolean SmoothFlag;	/**< \brief True if GL_POLYGON_SMOOTH is enabled */
   GLboolean StippleFlag;	/**< \brief True if GL_POLYGON_STIPPLE is enabled */
   GLenum CullFaceMode;		/**< \brief Culling mode GL_FRONT or GL_BACK */
   GLfloat OffsetFactor;	/**< \brief Polygon offset factor, from user */
   GLfloat OffsetUnits;		/**< \brief Polygon offset units, from user */
   GLboolean OffsetPoint;	/**< \brief Offset in GL_POINT mode */
   GLboolean OffsetLine;	/**< \brief Offset in GL_LINE mode */
   GLboolean OffsetFill;	/**< \brief Offset in GL_FILL mode */
};


/**
 * \brief Scissor attributes.
 */
struct gl_scissor_attrib {
   GLboolean Enabled;		/**< \brief Scissor test enabled? */
   GLint X, Y;			/**< \brief Lower left corner of box */
   GLsizei Width, Height;	/**< \brief Size of box */
};


/**
 * \brief Stencil attributes.
 */
struct gl_stencil_attrib {
   GLboolean Enabled;		/**< \brief Enabled flag */
   GLboolean TestTwoSide;	/**< \brief GL_EXT_stencil_two_side */
   GLubyte ActiveFace;		/**< \brief GL_EXT_stencil_two_side (0 or 1) */
   GLenum Function[2];		/**< \brief Stencil function */
   GLenum FailFunc[2];		/**< \brief Fail function */
   GLenum ZPassFunc[2];		/**< \brief Depth buffer pass function */
   GLenum ZFailFunc[2];		/**< \brief Depth buffer fail function */
   GLstencil Ref[2];		/**< \brief Reference value */
   GLstencil ValueMask[2];	/**< \brief Value mask */
   GLstencil WriteMask[2];	/**< \brief Write mask */
   GLstencil Clear;		/**< \brief Clear value */
};


/* TexGenEnabled flags */
#define S_BIT 1
#define T_BIT 2
#define R_BIT 4
#define Q_BIT 8

/* Texture.Unit[]._ReallyEnabled flags: */
#define TEXTURE_1D_BIT   0x01
#define TEXTURE_2D_BIT   0x02
#define TEXTURE_3D_BIT   0x04
#define TEXTURE_CUBE_BIT 0x08
#define TEXTURE_RECT_BIT 0x10

#define NUM_TEXTURE_TARGETS 5   /**< \brief 1D, 2D, 3D, CUBE and RECT */


/* Bitmap versions of the GL_ constants. */
#define TEXGEN_SPHERE_MAP        0x1
#define TEXGEN_OBJ_LINEAR        0x2
#define TEXGEN_EYE_LINEAR        0x4
#define TEXGEN_REFLECTION_MAP_NV 0x8
#define TEXGEN_NORMAL_MAP_NV     0x10

#define TEXGEN_NEED_NORMALS      (TEXGEN_SPHERE_MAP        | \
				  TEXGEN_REFLECTION_MAP_NV | \
				  TEXGEN_NORMAL_MAP_NV)
#define TEXGEN_NEED_EYE_COORD    (TEXGEN_SPHERE_MAP        | \
				  TEXGEN_REFLECTION_MAP_NV | \
				  TEXGEN_NORMAL_MAP_NV     | \
				  TEXGEN_EYE_LINEAR)



/* A selection of state flags to make driver and module's lives easier. */
#define ENABLE_TEXGEN0        0x1
#define ENABLE_TEXGEN1        0x2
#define ENABLE_TEXGEN2        0x4
#define ENABLE_TEXGEN3        0x8
#define ENABLE_TEXGEN4        0x10
#define ENABLE_TEXGEN5        0x20
#define ENABLE_TEXGEN6        0x40
#define ENABLE_TEXGEN7        0x80

#define ENABLE_TEXMAT0        0x1	/* Ie. not the identity matrix */
#define ENABLE_TEXMAT1        0x2
#define ENABLE_TEXMAT2        0x4
#define ENABLE_TEXMAT3        0x8
#define ENABLE_TEXMAT4        0x10
#define ENABLE_TEXMAT5        0x20
#define ENABLE_TEXMAT6        0x40
#define ENABLE_TEXMAT7        0x80

#define ENABLE_TEXGEN(i) (ENABLE_TEXGEN0 << (i))
#define ENABLE_TEXMAT(i) (ENABLE_TEXMAT0 << (i))

/**
 * \brief Texel fetch function prototype.
 * 
 * \param texImage texture image.
 * \param col texel column.
 * \param row texel row.
 * \param img texel level.
 * \param texelOut output texel. If \p texImage is color-index, \p texelOut
 * returns <c>GLchan[1]</c>.  If \p texImage is depth, \p texelOut returns
 * <c>GLfloat[1]</c>.  Otherwise, \p texelOut returns <c>GLchan[4]</c>.
 */
typedef void (*FetchTexelFunc)( const struct gl_texture_image *texImage,
                                GLint col, GLint row, GLint img,
                                GLvoid *texelOut );

/**
 * \brief Texture format record 
 */
struct gl_texture_format {
   GLint MesaFormat;		/**< \brief One of the MESA_FORMAT_* values */

   GLenum BaseFormat;		/**< \brief Either GL_ALPHA, GL_INTENSITY, GL_LUMINANCE,
                                 *   GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA,
                                 *   GL_COLOR_INDEX or GL_DEPTH_COMPONENT.
                                 */
   GLubyte RedBits;		/**< \brief Bits per texel component */
   GLubyte GreenBits;		/**< \brief These are just rough approximations for */
   GLubyte BlueBits;		/**< \brief compressed texture formats. */
   GLubyte AlphaBits;
   GLubyte LuminanceBits;
   GLubyte IntensityBits;
   GLubyte IndexBits;
   GLubyte DepthBits;

   GLint TexelBytes;		/**< \brief Bytes per texel (0 for compressed formats */

   /**
    * \name Texel fetch function pointers
    */
   /*@{*/
   FetchTexelFunc FetchTexel1D;
   FetchTexelFunc FetchTexel2D;
   FetchTexelFunc FetchTexel3D;
   /*@}*/
};


/**
 * \brief Texture image record 
 */
struct gl_texture_image {
   GLenum Format;		/**< \brief GL_ALPHA, GL_LUMINANCE, GL_LUMINANCE_ALPHA,
				 *    GL_INTENSITY, GL_RGB, GL_RGBA,
                                 *    GL_COLOR_INDEX or GL_DEPTH_COMPONENT only.
                                 *    Used for choosing TexEnv arithmetic.
				 */
   GLint IntFormat;		/**< \brief Internal format as given by the user */
   GLuint Border;		/**< \brief 0 or 1 */
   GLuint Width;		/**< \brief = 2^WidthLog2 + 2*Border */
   GLuint Height;		/**< \brief = 2^HeightLog2 + 2*Border */
   GLuint Depth;		/**< \brief = 2^DepthLog2 + 2*Border */
   GLuint RowStride;		/**< \brief == Width unless IsClientData and padded */
   GLuint Width2;		/**< \brief = Width - 2*Border */
   GLuint Height2;		/**< \brief = Height - 2*Border */
   GLuint Depth2;		/**< \brief = Depth - 2*Border */
   GLuint WidthLog2;		/**< \brief = log2(Width2) */
   GLuint HeightLog2;		/**< \brief = log2(Height2) */
   GLuint DepthLog2;		/**< \brief = log2(Depth2) */
   GLuint MaxLog2;		/**< \brief = MAX(WidthLog2, HeightLog2) */
   GLfloat WidthScale;		/**< \brief used for mipmap lod computation */
   GLfloat HeightScale;		/**< \brief used for mipmap lod computation */
   GLfloat DepthScale;		/**< \brief used for mipmap lod computation */
   GLvoid *Data;		/**< \brief Image data, accessed via FetchTexel() */
   GLboolean IsClientData;	/**< \brief Data owned by client? */


   const struct gl_texture_format *TexFormat;

   FetchTexelFunc FetchTexel;	/**< \brief Texel fetch function pointer */

   GLboolean IsCompressed;	/**< \brief GL_ARB_texture_compression */
   GLuint CompressedSize;	/**< \brief GL_ARB_texture_compression */

   /**
    * \name For device driver:
    */
   /*@{*/
   void *DriverData;		/**< \brief Arbitrary device driver data */
   /*@}*/
};


/**
 * \brief Texture object record
 */
struct gl_texture_object {
   _glthread_Mutex Mutex;	/**< \brief for thread safety */
   GLint RefCount;		/**< \brief reference count */
   GLuint Name;			/**< \brief an unsigned integer */
   GLenum Target;               /**< \brief GL_TEXTURE_1D, GL_TEXTURE_2D, etc. */
   GLfloat Priority;		/**< \brief in [0,1] */
   GLfloat BorderColor[4];	/**< \brief unclamped */
   GLchan _BorderChan[4];	/**< \brief clamped, as GLchan */
   /** \name Wrap modes
    * Are GL_CLAMP, REPEAT, GL_CLAMP_TO_EDGE, and GL_CLAMP_TO_BORDER_ARB. */
   /*@{*/
   GLenum WrapS;
   GLenum WrapT;
   GLenum WrapR;
   /*@}*/
   GLenum MinFilter;		/**< \brief minification filter */
   GLenum MagFilter;		/**< \brief magnification filter */
   GLfloat MinLod;		/**< \brief min lambda, OpenGL 1.2 */
   GLfloat MaxLod;		/**< \brief max lambda, OpenGL 1.2 */
   GLint BaseLevel;		/**< \brief min mipmap level, OpenGL 1.2 */
   GLint MaxLevel;		/**< \brief max mipmap level, OpenGL 1.2 */
   GLfloat MaxAnisotropy;	/**< \brief GL_EXT_texture_filter_anisotropic */
   GLboolean CompareFlag;	/**< \brief GL_SGIX_shadow */
   GLenum CompareOperator;	/**< \brief GL_SGIX_shadow */
   GLfloat ShadowAmbient;
   GLenum CompareMode;		/**< \brief GL_ARB_shadow */
   GLenum CompareFunc;		/**< \brief GL_ARB_shadow */
   GLenum DepthMode;		/**< \brief GL_ARB_depth_texture */
   GLint _MaxLevel;		/**< \brief actual max mipmap level (q in the spec) */
   GLfloat _MaxLambda;		/**< \brief = _MaxLevel - BaseLevel (q - b in spec) */
   GLboolean GenerateMipmap;    /**< \brief GL_SGIS_generate_mipmap */

   struct gl_texture_image *Image[MAX_TEXTURE_LEVELS];

   /**
    * \name Texture cube faces 
    * 
    * Image[] is alias for *PosX[MAX_TEXTURE_LEVELS];
    */
   /*@{*/
   struct gl_texture_image *NegX[MAX_TEXTURE_LEVELS];
   struct gl_texture_image *PosY[MAX_TEXTURE_LEVELS];
   struct gl_texture_image *NegY[MAX_TEXTURE_LEVELS];
   struct gl_texture_image *PosZ[MAX_TEXTURE_LEVELS];
   struct gl_texture_image *NegZ[MAX_TEXTURE_LEVELS];
   /*@}*/

   /** \brief GL_EXT_paletted_texture */
   struct gl_color_table Palette;

   GLboolean Complete;			/**< \brief Is texture object complete? */
   struct gl_texture_object *Next;	/**< \brief Next in linked list */

   /**
    * \name For device driver
    */
   /*@{*/
   void *DriverData;	/**< \brief Arbitrary device driver data */
   /*@}*/
};


/* Texture unit record */
struct gl_texture_unit {
   GLuint Enabled;              /**< \brief bitmask of TEXTURE_*_BIT flags */
   GLuint _ReallyEnabled;       /**< \brief 0 or exactly one of TEXTURE_*_BIT flags */

   GLenum EnvMode;              /**< \brief GL_MODULATE, GL_DECAL, GL_BLEND, etc. */
   GLfloat EnvColor[4];
   GLuint TexGenEnabled;	/**< \brief Bitwise-OR of [STRQ]_BIT values */
   /** \name Tex coord generation mode
    * Either GL_OBJECT_LINEAR, GL_EYE_LINEAR or GL_SPHERE_MAP. */
   /*@{*/
   GLenum GenModeS;		
   GLenum GenModeT;
   GLenum GenModeR;
   GLenum GenModeQ;
   /*@}*/
   GLuint _GenBitS;
   GLuint _GenBitT;
   GLuint _GenBitR;
   GLuint _GenBitQ;
   GLuint _GenFlags;		/**< \brief bitwise or of GenBit[STRQ] */
   GLfloat ObjectPlaneS[4];
   GLfloat ObjectPlaneT[4];
   GLfloat ObjectPlaneR[4];
   GLfloat ObjectPlaneQ[4];
   GLfloat EyePlaneS[4];
   GLfloat EyePlaneT[4];
   GLfloat EyePlaneR[4];
   GLfloat EyePlaneQ[4];
   GLfloat LodBias;		/**< \brief for biasing mipmap levels */

   /** 
    * \name GL_EXT_texture_env_combine 
    */
   /*@{*/
   GLenum CombineModeRGB;       /**< \brief GL_REPLACE, GL_DECAL, GL_ADD, etc. */
   GLenum CombineModeA;         /**< \brief GL_REPLACE, GL_DECAL, GL_ADD, etc. */
   GLenum CombineSourceRGB[3];  /**< \brief GL_PRIMARY_COLOR, GL_TEXTURE, etc. */
   GLenum CombineSourceA[3];    /**< \brief GL_PRIMARY_COLOR, GL_TEXTURE, etc. */
   GLenum CombineOperandRGB[3]; /**< \brief SRC_COLOR, ONE_MINUS_SRC_COLOR, etc */
   GLenum CombineOperandA[3];   /**< \brief SRC_ALPHA, ONE_MINUS_SRC_ALPHA, etc */
   GLuint CombineScaleShiftRGB; /**< \brief 0, 1 or 2 */
   GLuint CombineScaleShiftA;   /**< \brief 0, 1 or 2 */
   /*@}*/

   struct gl_texture_object *Current1D;
   struct gl_texture_object *Current2D;
   struct gl_texture_object *Current3D;
   struct gl_texture_object *CurrentCubeMap; /**< \brief GL_ARB_texture_cube_map */
   struct gl_texture_object *CurrentRect;    /**< \brief GL_NV_texture_rectangle */

   struct gl_texture_object *_Current; /**< \brief Points to really enabled tex obj */

   struct gl_texture_object Saved1D;  /**< \brief only used by glPush/PopAttrib */
   struct gl_texture_object Saved2D;
   struct gl_texture_object Saved3D;
   struct gl_texture_object SavedCubeMap;
   struct gl_texture_object SavedRect;
};


/**
 * \brief Texture attributes
 */
struct gl_texture_attrib {
   /**
    * name multitexture 
    */
   /**@{*/
   GLuint CurrentUnit;	          /**< \brief Active texture unit */

   GLuint _EnabledUnits;        /**< \brief one bit set for each really-enabled unit */
   GLuint _GenFlags;  /**< \brief for texgen */
   GLuint _NeedEyeCoords;
   GLuint _TexGenEnabled;
   GLuint _TexMatEnabled;
   /**@}*/

   struct gl_texture_unit Unit[MAX_TEXTURE_UNITS];

   struct gl_texture_object *Proxy1D;
   struct gl_texture_object *Proxy2D;
   struct gl_texture_object *Proxy3D;
   struct gl_texture_object *ProxyCubeMap;
   struct gl_texture_object *ProxyRect;

   /** \brief GL_EXT_shared_texture_palette */
   GLboolean SharedPalette;
   struct gl_color_table Palette;
};


/**
 * \brief Transformation attributes.
 */
struct gl_transform_attrib {
   GLenum MatrixMode;				/**< \brief Matrix mode */
   GLfloat EyeUserPlane[MAX_CLIP_PLANES][4];
   GLfloat _ClipUserPlane[MAX_CLIP_PLANES][4];	/**< \brief derived */
   GLuint ClipPlanesEnabled;                    /**< \brief on/off bitmask */
   GLboolean Normalize;				/**< \brief Normalize all normals? */
   GLboolean RescaleNormals;			/**< \brief GL_EXT_rescale_normal */
   GLboolean RasterPositionUnclipped;           /**< \brief GL_IBM_rasterpos_clip */
};


/**
 * \brief Viewport attributes.
 */
struct gl_viewport_attrib {
   GLint X, Y;			/**< \brief position */
   GLsizei Width, Height;	/**< \brief size */
   GLfloat Near, Far;		/**< \brief Depth buffer range */
   GLmatrix _WindowMap;		/**< \brief Mapping transformation as a matrix. */
};


/**
 * \brief Node for the attribute stack
 */
struct gl_attrib_node {
   GLbitfield kind;
   void *data;
   struct gl_attrib_node *next;
};


/**
 * \brief Client pixel packing/unpacking attributes
 */
struct gl_pixelstore_attrib {
   GLint Alignment;
   GLint RowLength;
   GLint SkipPixels;
   GLint SkipRows;
   GLint ImageHeight;     /**< \brief for GL_EXT_texture3D */
   GLint SkipImages;      /**< \brief for GL_EXT_texture3D */
   GLboolean SwapBytes;
   GLboolean LsbFirst;
   GLboolean ClientStorage; /**< \brief GL_APPLE_client_storage */
   GLboolean Invert;        /**< \brief GL_MESA_pack_invert */
};


#define CA_CLIENT_DATA     0x1	/**< \brief Data not alloced by mesa */


/**
 * \brief Client vertex array attributes
 */
struct gl_client_array {
   GLint Size;
   GLenum Type;
   GLsizei Stride;		/**< \brief user-specified stride */
   GLsizei StrideB;		/**< \brief actual stride in bytes */
   void *Ptr;
   GLuint Flags;
   GLuint Enabled;		/**< \brief one of the _NEW_ARRAY_ bits */
};


/**
 * \brief Array attributes.
 */
struct gl_array_attrib {
   struct gl_client_array Vertex;	     /**< \brief client data descriptors */
   struct gl_client_array Normal;
   struct gl_client_array Color;
   struct gl_client_array SecondaryColor;
   struct gl_client_array FogCoord;
   struct gl_client_array Index;
   struct gl_client_array TexCoord[MAX_TEXTURE_UNITS];
   struct gl_client_array EdgeFlag;

   struct gl_client_array VertexAttrib[16];  /**< \brief GL_NV_vertex_program */

   GLint TexCoordInterleaveFactor;
   GLint ActiveTexture;		/**< \brief Client Active Texture */
   GLuint LockFirst;
   GLuint LockCount;

   GLuint _Enabled;		/**< \brief _NEW_ARRAY_* - bit set if array enabled */
   GLuint NewState;		/**< \brief _NEW_ARRAY_* */
};


struct gl_feedback {
   GLenum Type;
   GLuint _Mask;		/* FB_* bits */
   GLfloat *Buffer;
   GLuint BufferSize;
   GLuint Count;
};


/**
 * \brief Selection attributes.
 */
struct gl_selection {
   GLuint *Buffer;	/**< \brief selection buffer */
   GLuint BufferSize;	/**< \brief size of the selection buffer */
   GLuint BufferCount;	/**< \brief number of values in the selection buffer */
   GLuint Hits;		/**< \brief number of records in the selection buffer */
   GLuint NameStackDepth; /**< \brief name stack depth */
   GLuint NameStack[MAX_NAME_STACK_DEPTH]; /**< \brief name stack */
   GLboolean HitFlag;	/**< \brief hit flag */
   GLfloat HitMinZ;	/**< \brief minimum hit depth */
   GLfloat HitMaxZ;	/**< \brief maximum hit depth */
};


/**
 * \brief 1-D Evaluator control points
 */
struct gl_1d_map {
   GLuint Order;	/**< \brief Number of control points */
   GLfloat u1, u2, du;	/**< \brief u1, u2, 1.0/(u2-u1) */
   GLfloat *Points;	/**< \brief Points to contiguous control points */
};


/**
 * \brief 2-D Evaluator control points
 */
struct gl_2d_map {
   GLuint Uorder;		/**< \brief Number of control points in U dimension */
   GLuint Vorder;		/**< \brief Number of control points in V dimension */
   GLfloat u1, u2, du;
   GLfloat v1, v2, dv;
   GLfloat *Points;		/**< \brief Points to contiguous control points */
};


/**
 * \brief All evalutator control points
 */
struct gl_evaluators {
   /** 
    * \name 1-D maps
    */
   /*@{*/
   struct gl_1d_map Map1Vertex3;
   struct gl_1d_map Map1Vertex4;
   struct gl_1d_map Map1Index;
   struct gl_1d_map Map1Color4;
   struct gl_1d_map Map1Normal;
   struct gl_1d_map Map1Texture1;
   struct gl_1d_map Map1Texture2;
   struct gl_1d_map Map1Texture3;
   struct gl_1d_map Map1Texture4;
   struct gl_1d_map Map1Attrib[16];  /**< \brief GL_NV_vertex_program */
   /*@}*/

   /** 
    * \name 2-D maps 
    */
   /*@{*/
   struct gl_2d_map Map2Vertex3;
   struct gl_2d_map Map2Vertex4;
   struct gl_2d_map Map2Index;
   struct gl_2d_map Map2Color4;
   struct gl_2d_map Map2Normal;
   struct gl_2d_map Map2Texture1;
   struct gl_2d_map Map2Texture2;
   struct gl_2d_map Map2Texture3;
   struct gl_2d_map Map2Texture4;
   struct gl_2d_map Map2Attrib[16];  /**< \brief GL_NV_vertex_program */
   /*@}*/
};


/**
 * \name Vertex program tokens and datatypes
 */
/*@{*/

#define VP_MAX_INSTRUCTIONS 128

#define VP_NUM_INPUT_REGS VERT_ATTRIB_MAX
#define VP_NUM_OUTPUT_REGS 15
#define VP_NUM_TEMP_REGS 12
#define VP_NUM_PROG_REGS 96

#define VP_NUM_TOTAL_REGISTERS (VP_NUM_INPUT_REGS + VP_NUM_OUTPUT_REGS + VP_NUM_TEMP_REGS + VP_NUM_PROG_REGS)

/* Location of register sets within the whole register file */
#define VP_INPUT_REG_START  0
#define VP_INPUT_REG_END    (VP_INPUT_REG_START + VP_NUM_INPUT_REGS - 1)
#define VP_OUTPUT_REG_START (VP_INPUT_REG_END + 1)
#define VP_OUTPUT_REG_END   (VP_OUTPUT_REG_START + VP_NUM_OUTPUT_REGS - 1)
#define VP_TEMP_REG_START   (VP_OUTPUT_REG_END + 1)
#define VP_TEMP_REG_END     (VP_TEMP_REG_START + VP_NUM_TEMP_REGS - 1)
#define VP_PROG_REG_START   (VP_TEMP_REG_END + 1)
#define VP_PROG_REG_END     (VP_PROG_REG_START + VP_NUM_PROG_REGS - 1)


/** 
 * \brief Machine state (i.e. the register file) 
 */
struct vp_machine
{
   GLfloat Registers[VP_NUM_TOTAL_REGISTERS][4];
   GLint AddressReg;  /* might someday be a 4-vector */
};


/**
 * \brief Vertex program opcodes 
 */
enum vp_opcode
{
   MOV,
   LIT,
   RCP,
   RSQ,
   EXP,
   LOG,
   MUL,
   ADD,
   DP3,
   DP4,
   DST,
   MIN,
   MAX,
   SLT,
   SGE,
   MAD,
   ARL,
   DPH,
   RCC,
   SUB,
   ABS,
   END
};


/**
 * \brief Instruction source register
 */
struct vp_src_register
{
   GLint Register;    /* or the offset from the address register */
   GLuint Swizzle[4];
   GLboolean Negate;
   GLboolean RelAddr;
};


/**
 * \brief Instruction destination register 
 */
struct vp_dst_register
{
   GLint Register;
   GLboolean WriteMask[4];
};


/** 
 * \brief Vertex program instruction 
 */
struct vp_instruction
{
   enum vp_opcode Opcode;
   struct vp_src_register SrcReg[3];
   struct vp_dst_register DstReg;
};


/**
 * \brief The actual vertex program, stored in the hash table 
 */
struct vp_program
{
   GLubyte *String;                      /**< \brief Original user code */
   struct vp_instruction *Instructions;  /**< \brief Compiled instructions */
   GLenum Target;      /**< \brief GL_VERTEX_PROGRAM_NV or GL_VERTEX_STATE_PROGRAM_NV */
   GLint RefCount;            /**< \brief Since programs can be shared among contexts */
   GLboolean IsPositionInvariant;  /**< \brief GL_NV_vertex_program1_1 */
   GLboolean Resident;
   GLuint InputsRead;     /**< \brief Bitmask of which input regs are read */
   GLuint OutputsWritten; /**< \brief Bitmask of which output regs are written to */
};


/**
 * \brief State vars for GL_NV_vertex_program
 */
struct vertex_program_state
{
   GLboolean Enabled;                    /**< \brief GL_VERTEX_PROGRAM_NV */
   GLboolean PointSizeEnabled;           /**< \brief GL_VERTEX_PROGRAM_POINT_SIZE_NV */
   GLboolean TwoSideEnabled;             /**< \brief GL_VERTEX_PROGRAM_TWO_SIDE_NV */
   GLuint CurrentID;                     /**< \brief currently bound program's ID */
   GLint ErrorPos;                       /**< \brief GL_PROGRAM_ERROR_POSITION_NV */
   struct vp_program *Current;           /**< \brief ptr to currently bound program */
   struct vp_machine Machine;            /**< \brief machine state */

   GLenum TrackMatrix[VP_NUM_PROG_REGS / 4];
   GLenum TrackMatrixTransform[VP_NUM_PROG_REGS / 4];
};

/*@}*/


/**
 * \brief State which can be shared by multiple contexts:
 */
struct gl_shared_state {
   _glthread_Mutex Mutex;		   /**< \brief for thread safety */
   GLint RefCount;			   /**< \brief Reference count */
   struct _mesa_HashTable *DisplayList;	   /**< \brief Display lists hash table */
   struct _mesa_HashTable *TexObjects;	   /**< \brief Texture objects hash table */
   struct gl_texture_object *TexObjectList;/**< \brief Linked list of texture objects */

   /**
    * \name Default texture objects (shared by all multi-texture units)
    */
   /*@{*/
   struct gl_texture_object *Default1D;
   struct gl_texture_object *Default2D;
   struct gl_texture_object *Default3D;
   struct gl_texture_object *DefaultCubeMap;
   struct gl_texture_object *DefaultRect;
   /*@}*/

   /** \brief GL_NV_vertex_program */
   struct _mesa_HashTable *VertexPrograms;

   void *DriverData;  /**< \brief Device driver shared state */
};


/**
 * \brief Frame buffer.
 *
 * A "frame buffer" is a color buffer and its optional ancillary buffers:
 * depth, accum, stencil, and software-simulated alpha buffers.
 * In C++ terms, think of this as a base class from which device drivers
 * will make derived classes.
 */
struct gl_frame_buffer {
   GLvisual Visual;		/**< \brief The corresponding visual */

   GLuint Width, Height;	/**< \brief size of frame buffer in pixels */

   GLboolean UseSoftwareDepthBuffer;
   GLboolean UseSoftwareAccumBuffer;
   GLboolean UseSoftwareStencilBuffer;
   GLboolean UseSoftwareAlphaBuffers;

   /** \name Software depth (aka Z) buffer */
   /*@{*/
   GLvoid *DepthBuffer;		/**< \brief array [Width*Height] of GLushort or GLuint*/
   /*@}*/

   /** \name Software stencil buffer */
   /*@{*/
   GLstencil *Stencil;		/**< \brief array [Width*Height] of GLstencil values */
   /*@}*/

   /** \name Software accumulation buffer */
   /*@{*/
   GLaccum *Accum;		/**< \brief array [4*Width*Height] of GLaccum values */
   /*@}*/

   /** \name Software alpha planes */
   /*@{*/
   GLvoid *FrontLeftAlpha;	/**< \brief array [Width*Height] of GLubyte */
   GLvoid *BackLeftAlpha;	/**< \brief array [Width*Height] of GLubyte */
   GLvoid *FrontRightAlpha;	/**< \brief array [Width*Height] of GLubyte */
   GLvoid *BackRightAlpha;	/**< \brief array [Width*Height] of GLubyte */
   /*@}*/

   /** 
    * \name Drawing bounds
    *
    * Intersection of window size and scissor box 
    */
   /*@{*/
   GLint _Xmin;  /**< \brief inclusive */
   GLint _Ymin;  /**< \brief inclusive */
   GLint _Xmax;  /**< \brief exclusive */
   GLint _Ymax;  /**< \brief exclusive */
   /*@}*/
};


/**
 * \brief Constants which may be overriden by device driver during context creation
 * but are never changed after that.
 */
struct gl_constants {
   GLint MaxTextureLevels;		/**< \brief Maximum number of allowed mipmap levels. */ 
   GLint Max3DTextureLevels;		/**< \brief Maximum number of allowed mipmap levels for 3D texture targets. */
   GLint MaxCubeTextureLevels;          /**< \brief Maximum number of allowed mipmap levels for GL_ARB_texture_cube_map */
   GLint MaxTextureRectSize;            /* GL_NV_texture_rectangle */
   GLuint MaxTextureUnits;
   GLfloat MaxTextureMaxAnisotropy;	/* GL_EXT_texture_filter_anisotropic */
   GLfloat MaxTextureLodBias;           /* GL_EXT_texture_lod_bias */
   GLuint MaxArrayLockSize;
   GLint SubPixelBits;
   GLfloat MinPointSize, MaxPointSize;		/* aliased */
   GLfloat MinPointSizeAA, MaxPointSizeAA;	/* antialiased */
   GLfloat PointSizeGranularity;
   GLfloat MinLineWidth, MaxLineWidth;		/* aliased */
   GLfloat MinLineWidthAA, MaxLineWidthAA;	/* antialiased */
   GLfloat LineWidthGranularity;
   GLuint NumAuxBuffers;
   GLuint MaxColorTableSize;
   GLuint MaxConvolutionWidth;
   GLuint MaxConvolutionHeight;
   GLuint MaxClipPlanes;
   GLuint MaxLights;
};


/**
 * \brief List of extensions.
 */
struct extension;
struct gl_extensions {
   char *ext_string;
   struct extension *ext_list;
   /**
    * \name Flags to quickly test if certain extensions are available.
    * 
    * Not every extension needs to have such a flag, but it's encouraged.
    */
   /*@{*/
   GLboolean ARB_depth_texture;
   GLboolean ARB_imaging;
   GLboolean ARB_multisample;
   GLboolean ARB_multitexture;
   GLboolean ARB_shadow;
   GLboolean ARB_texture_border_clamp;
   GLboolean ARB_texture_compression;
   GLboolean ARB_texture_cube_map;
   GLboolean ARB_texture_env_combine;
   GLboolean ARB_texture_env_crossbar;
   GLboolean ARB_texture_env_dot3;
   GLboolean ARB_texture_mirrored_repeat;
   GLboolean ARB_window_pos;
   GLboolean ATI_texture_mirror_once;
   GLboolean EXT_blend_color;
   GLboolean EXT_blend_func_separate;
   GLboolean EXT_blend_logic_op;
   GLboolean EXT_blend_minmax;
   GLboolean EXT_blend_subtract;
   GLboolean EXT_clip_volume_hint;
   GLboolean EXT_convolution;
   GLboolean EXT_compiled_vertex_array;
   GLboolean EXT_fog_coord;
   GLboolean EXT_histogram;
   GLboolean EXT_multi_draw_arrays;
   GLboolean EXT_packed_pixels;
   GLboolean EXT_paletted_texture;
   GLboolean EXT_point_parameters;
   GLboolean EXT_polygon_offset;
   GLboolean EXT_rescale_normal;
   GLboolean EXT_shadow_funcs;
   GLboolean EXT_secondary_color;
   GLboolean EXT_shared_texture_palette;
   GLboolean EXT_stencil_wrap;
   GLboolean EXT_stencil_two_side;
   GLboolean EXT_texture3D;
   GLboolean EXT_texture_compression_s3tc;
   GLboolean EXT_texture_env_add;
   GLboolean EXT_texture_env_combine;
   GLboolean EXT_texture_env_dot3;
   GLboolean EXT_texture_filter_anisotropic;
   GLboolean EXT_texture_object;
   GLboolean EXT_texture_lod_bias;
   GLboolean EXT_vertex_array_set;
   GLboolean HP_occlusion_test;
   GLboolean IBM_rasterpos_clip;
   GLboolean INGR_blend_func_separate;
   GLboolean MESA_pack_invert;
   GLboolean MESA_window_pos;
   GLboolean MESA_resize_buffers;
   GLboolean MESA_ycbcr_texture;
   GLboolean NV_blend_square;
   GLboolean NV_point_sprite;
   GLboolean NV_texture_rectangle;
   GLboolean NV_texgen_reflection;
   GLboolean NV_vertex_program;
   GLboolean NV_vertex_program1_1;
   GLboolean SGI_color_matrix;
   GLboolean SGI_color_table;
   GLboolean SGIS_generate_mipmap;
   GLboolean SGIS_pixel_texture;
   GLboolean SGIS_texture_edge_clamp;
   GLboolean SGIX_depth_texture;
   GLboolean SGIX_pixel_texture;
   GLboolean SGIX_shadow;
   GLboolean SGIX_shadow_ambient; /* or GL_ARB_shadow_ambient */
   GLboolean TDFX_texture_compression_FXT1;
   GLboolean APPLE_client_storage;
   /*@}*/
};


/**
 * \brief A stack of matrices (projection, modelview, color, texture, etc).
 */
struct matrix_stack
{
   GLmatrix *Top;      /**< \brief points into Stack */
   GLmatrix *Stack;    /**< \brief array [MaxDepth] of GLmatrix */
   GLuint Depth;       /**< \brief 0 <= Depth < MaxDepth */
   GLuint MaxDepth;    /**< \brief size of Stack[] array */
   GLuint DirtyFlag;   /**< \brief _NEW_MODELVIEW or _NEW_PROJECTION, for example */
};


/*
 * Bits for image transfer operations (ctx->ImageTransferState).
 */
#define IMAGE_SCALE_BIAS_BIT                      0x1
#define IMAGE_SHIFT_OFFSET_BIT                    0x2
#define IMAGE_MAP_COLOR_BIT                       0x4
#define IMAGE_COLOR_TABLE_BIT                     0x8
#define IMAGE_CONVOLUTION_BIT                     0x10
#define IMAGE_POST_CONVOLUTION_SCALE_BIAS         0x20
#define IMAGE_POST_CONVOLUTION_COLOR_TABLE_BIT    0x40
#define IMAGE_COLOR_MATRIX_BIT                    0x80
#define IMAGE_POST_COLOR_MATRIX_COLOR_TABLE_BIT   0x100
#define IMAGE_HISTOGRAM_BIT                       0x200
#define IMAGE_MIN_MAX_BIT                         0x400

/** transfer ops up to convolution: */
#define IMAGE_PRE_CONVOLUTION_BITS (IMAGE_SCALE_BIAS_BIT |     \
                                    IMAGE_SHIFT_OFFSET_BIT |   \
                                    IMAGE_MAP_COLOR_BIT |      \
                                    IMAGE_COLOR_TABLE_BIT)

/** transfer ops after convolution: */
#define IMAGE_POST_CONVOLUTION_BITS (IMAGE_POST_CONVOLUTION_SCALE_BIAS |      \
                                     IMAGE_POST_CONVOLUTION_COLOR_TABLE_BIT | \
                                     IMAGE_COLOR_MATRIX_BIT |                 \
                                     IMAGE_POST_COLOR_MATRIX_COLOR_TABLE_BIT |\
                                     IMAGE_HISTOGRAM_BIT |                    \
                                     IMAGE_MIN_MAX_BIT)


/*
 * Bits to indicate what state has changed.  6 unused flags.
 */
#define _NEW_MODELVIEW		0x1        /**< \brief ctx->ModelView */
#define _NEW_PROJECTION		0x2        /**< \brief ctx->Projection */
#define _NEW_TEXTURE_MATRIX	0x4        /**< \brief ctx->TextureMatrix */
#define _NEW_COLOR_MATRIX	0x8        /**< \brief ctx->ColorMatrix */
#define _NEW_ACCUM		0x10       /**< \brief ctx->Accum */
#define _NEW_COLOR		0x20       /**< \brief ctx->Color */
#define _NEW_DEPTH		0x40       /**< \brief ctx->Depth */
#define _NEW_EVAL		0x80       /**< \brief ctx->Eval, ctx->EvalMap */
#define _NEW_FOG		0x100      /**< \brief ctx->Fog */
#define _NEW_HINT		0x200      /**< \brief ctx->Hint */
#define _NEW_LIGHT		0x400      /**< \brief ctx->Light */
#define _NEW_LINE		0x800      /**< \brief ctx->Line */
#define _NEW_PIXEL		0x1000     /**< \brief ctx->Pixel */
#define _NEW_POINT		0x2000     /**< \brief ctx->Point */
#define _NEW_POLYGON		0x4000     /**< \brief ctx->Polygon */
#define _NEW_POLYGONSTIPPLE	0x8000     /**< \brief ctx->PolygonStipple */
#define _NEW_SCISSOR		0x10000    /**< \brief ctx->Scissor */
#define _NEW_STENCIL		0x20000    /**< \brief ctx->Stencil */
#define _NEW_TEXTURE		0x40000    /**< \brief ctx->Texture */
#define _NEW_TRANSFORM		0x80000    /**< \brief ctx->Transform */
#define _NEW_VIEWPORT		0x100000   /**< \brief ctx->Viewport */
#define _NEW_PACKUNPACK		0x200000   /**< \brief ctx->Pack, ctx->Unpack */
#define _NEW_ARRAY	        0x400000   /**< \brief ctx->Array */
#define _NEW_RENDERMODE		0x800000   /**< \brief RenderMode, Feedback, Select */
#define _NEW_BUFFERS            0x1000000  /**< \brief ctx->Visual, ctx->DrawBuffer, */
#define _NEW_MULTISAMPLE        0x2000000  /**< \brief ctx->Multisample */
#define _NEW_TRACK_MATRIX       0x4000000  /**< \brief ctx->VertexProgram */
#define _NEW_PROGRAM            0x8000000  /**< \brief ctx->VertexProgram */
#define _NEW_ALL ~0



/* Bits to track array state changes (also used to summarize array enabled)
 */
#define _NEW_ARRAY_VERTEX           VERT_BIT_POS
#define _NEW_ARRAY_WEIGHT           VERT_BIT_WEIGHT
#define _NEW_ARRAY_NORMAL           VERT_BIT_NORMAL
#define _NEW_ARRAY_COLOR0           VERT_BIT_COLOR0
#define _NEW_ARRAY_COLOR1           VERT_BIT_COLOR1
#define _NEW_ARRAY_FOGCOORD         VERT_BIT_FOG
#define _NEW_ARRAY_INDEX            VERT_BIT_SIX
#define _NEW_ARRAY_EDGEFLAG         VERT_BIT_SEVEN
#define _NEW_ARRAY_TEXCOORD_0       VERT_BIT_TEX0
#define _NEW_ARRAY_TEXCOORD_1       VERT_BIT_TEX1
#define _NEW_ARRAY_TEXCOORD_2       VERT_BIT_TEX2
#define _NEW_ARRAY_TEXCOORD_3       VERT_BIT_TEX3
#define _NEW_ARRAY_TEXCOORD_4       VERT_BIT_TEX4
#define _NEW_ARRAY_TEXCOORD_5       VERT_BIT_TEX5
#define _NEW_ARRAY_TEXCOORD_6       VERT_BIT_TEX6
#define _NEW_ARRAY_TEXCOORD_7       VERT_BIT_TEX7
#define _NEW_ARRAY_ATTRIB_0         0x10000  /* start at bit 16 */
#define _NEW_ARRAY_ALL              0xffffffff


#define _NEW_ARRAY_TEXCOORD(i) (_NEW_ARRAY_TEXCOORD_0 << (i))
#define _NEW_ARRAY_ATTRIB(i) (_NEW_ARRAY_ATTRIB_0 << (i))


/* A bunch of flags that we think might be useful to drivers.
 * Set in the ctx->_TriangleCaps bitfield.
 */
#define DD_FLATSHADE                0x1
#define DD_SEPARATE_SPECULAR        0x2
#define DD_TRI_CULL_FRONT_BACK      0x4 /* special case on some hw */
#define DD_TRI_LIGHT_TWOSIDE        0x8
#define DD_TRI_UNFILLED             0x10
#define DD_TRI_SMOOTH               0x20
#define DD_TRI_STIPPLE              0x40
#define DD_TRI_OFFSET               0x80
#define DD_LINE_SMOOTH              0x100
#define DD_LINE_STIPPLE             0x200
#define DD_LINE_WIDTH               0x400
#define DD_POINT_SMOOTH             0x800
#define DD_POINT_SIZE               0x1000
#define DD_POINT_ATTEN              0x2000


/* Define the state changes under which each of these bits might change
 */
#define _DD_NEW_FLATSHADE                _NEW_LIGHT
#define _DD_NEW_SEPARATE_SPECULAR        (_NEW_LIGHT | _NEW_FOG)
#define _DD_NEW_TRI_CULL_FRONT_BACK      _NEW_POLYGON
#define _DD_NEW_TRI_LIGHT_TWOSIDE        _NEW_LIGHT
#define _DD_NEW_TRI_UNFILLED             _NEW_POLYGON
#define _DD_NEW_TRI_SMOOTH               _NEW_POLYGON
#define _DD_NEW_TRI_STIPPLE              _NEW_POLYGON
#define _DD_NEW_TRI_OFFSET               _NEW_POLYGON
#define _DD_NEW_LINE_SMOOTH              _NEW_LINE
#define _DD_NEW_LINE_STIPPLE             _NEW_LINE
#define _DD_NEW_LINE_WIDTH               _NEW_LINE
#define _DD_NEW_POINT_SMOOTH             _NEW_POINT
#define _DD_NEW_POINT_SIZE               _NEW_POINT
#define _DD_NEW_POINT_ATTEN              _NEW_POINT

#define _MESA_NEW_NEED_EYE_COORDS         (_NEW_LIGHT |		\
                                           _NEW_TEXTURE |	\
                                           _NEW_POINT |		\
                                           _NEW_MODELVIEW)

#define _MESA_NEW_NEED_NORMALS            (_NEW_LIGHT |		\
                                           _NEW_TEXTURE)

#define _IMAGE_NEW_TRANSFER_STATE         (_NEW_PIXEL | _NEW_COLOR_MATRIX)


/* Bits for ctx->_NeedEyeCoords */
#define NEED_EYE_TEXGEN          0x1
#define NEED_EYE_LIGHT           0x2
#define NEED_EYE_LIGHT_MODELVIEW 0x4
#define NEED_EYE_POINT_ATTEN     0x8
#define NEED_EYE_DRIVER          0x10


/*
 * Forward declaration of display list datatypes:
 */
union node;
typedef union node Node;


/* This has to be included here. */
#include "dd.h"


#define NUM_VERTEX_FORMAT_ENTRIES (sizeof(GLvertexformat) / sizeof(void *))

/**
 * \brief Core Mesa's support for tnl modules:
 */
struct gl_tnl_module {
   /**
    * \brief Vertex format to be lazily swapped into current dispatch.
    */
   GLvertexformat *Current;

   /**
    * \name Record of functions swapped out.  
    * On restore, only need to swap these functions back in.
    */
   /*@{*/
   void *Swapped[NUM_VERTEX_FORMAT_ENTRIES][2];
   GLuint SwapCount;
   /*@}*/
};


/**
 * \brief Mesa context
 *
 * This is the central context data structure for Mesa.  Almost all
 * OpenGL state is contained in this structure.
 * Think of this as a base class from which device drivers will derive
 * sub classes.
 */
struct __GLcontextRec {
   /**
    * \name OS related interfaces. 
    *
    * These \b must be the first members of this structure, because they are
    * exposed to the outside world (i.e. GLX extension).
    */
   /*@{*/
   __GLimports imports;
   __GLexports exports;
   /*@}*/

   /** \brief State possibly shared with other contexts in the address space */
   struct gl_shared_state *Shared;

   /** \name API function pointer tables */
   /*@{*/
   struct _glapi_table *Save;	/**< \brief Display list save funcs */
   struct _glapi_table *Exec;	/**< \brief Execute funcs */
   struct _glapi_table *CurrentDispatch;  /**< == Save or Exec !! */
   /*@}*/

   GLboolean ExecPrefersFloat;	/**< \brief What preference for color conversion? */
   GLboolean SavePrefersFloat;

   GLvisual Visual;
   GLframebuffer *DrawBuffer;	/**< \brief buffer for writing */
   GLframebuffer *ReadBuffer;	/**< \brief buffer for reading */

   /**
    * \brief Device driver function pointer table
    */
   struct dd_function_table Driver;

   void *DriverCtx;	/**< \brief Points to device driver context/state */
   void *DriverMgrCtx;	/**< \brief Points to device driver manager (optional)*/

   /** \brief Core/Driver constants */
   struct gl_constants Const;

   /** \name The various 4x4 matrix stacks */
   /*@{*/
   struct matrix_stack ModelviewMatrixStack;
   struct matrix_stack ProjectionMatrixStack;
   struct matrix_stack ColorMatrixStack;
   struct matrix_stack TextureMatrixStack[MAX_TEXTURE_UNITS];
   struct matrix_stack ProgramMatrixStack[MAX_PROGRAM_MATRICES];
   struct matrix_stack *CurrentStack; /**< \brief Points to one of the above stacks */
   /*@}*/

   /** \brief Combined modelview and projection matrix */
   GLmatrix _ModelProjectMatrix;

   /** \name Display lists */
   /*@{*/
   GLuint CallDepth;		/**< \brief Current recursion calling depth */
   GLboolean ExecuteFlag;	/**< \brief Execute GL commands? */
   GLboolean CompileFlag;	/**< \brief Compile GL commands into display list? */
   Node *CurrentListPtr;	/**< \brief Head of list being compiled */
   GLuint CurrentListNum;	/**< \brief Number of the list being compiled */
   Node *CurrentBlock;		/**< \brief Pointer to current block of nodes */
   GLuint CurrentPos;		/**< \brief Index into current block of nodes */
   /*@}*/

   /** \brief Extensions */
   struct gl_extensions Extensions;

   /** \name Renderer attribute stack */
   /*@{*/
   GLuint AttribStackDepth;
   struct gl_attrib_node *AttribStack[MAX_ATTRIB_STACK_DEPTH];
   /*@}*/

   /** \name Renderer attribute groups
    * 
    * We define a struct for each attribute group to make pushing and popping
    * attributes easy.  Also it's a good organization.
    */
   /*@{*/
   struct gl_accum_attrib	Accum;		/**< \brief Accumulation buffer attributes */
   struct gl_colorbuffer_attrib	Color;		/**< \brief Color buffers attributes */
   struct gl_current_attrib	Current;	/**< \brief Current attributes */
   struct gl_depthbuffer_attrib	Depth;		/**< \brief Depth buffer attributes */
   struct gl_eval_attrib	Eval;		/**< \brief Eval attributes */
   struct gl_fog_attrib		Fog;		/**< \brief Fog attributes */
   struct gl_hint_attrib	Hint;		/**< \brief Hint attributes */
   struct gl_light_attrib	Light;		/**< \brief Light attributes */
   struct gl_line_attrib	Line;		/**< \brief Line attributes */
   struct gl_list_attrib	List;		/**< \brief List attributes */
   struct gl_multisample_attrib Multisample;
   struct gl_pixel_attrib	Pixel;		/**< \brief Pixel attributes */
   struct gl_point_attrib	Point;		/**< \brief Point attributes */
   struct gl_polygon_attrib	Polygon;	/**< \brief Polygon attributes */
   GLuint PolygonStipple[32];			/**< \brief Polygon stipple */
   struct gl_scissor_attrib	Scissor;	/**< \brief Scissor attributes */
   struct gl_stencil_attrib	Stencil;	/**< \brief Stencil buffer attributes */
   struct gl_texture_attrib	Texture;	/**< \brief Texture attributes */
   struct gl_transform_attrib	Transform;	/**< \brief Transformation attributes */
   struct gl_viewport_attrib	Viewport;	/**< \brief Viewport attributes */
   /*@}*/

   /** \name Other attribute groups */
   /*@{*/
   struct gl_histogram_attrib	Histogram;
   struct gl_minmax_attrib	MinMax;
   struct gl_convolution_attrib Convolution1D;
   struct gl_convolution_attrib Convolution2D;
   struct gl_convolution_attrib Separable2D;
   /*@}*/

   /** \name Client attribute stack */
   /*@{*/
   GLuint ClientAttribStackDepth;
   struct gl_attrib_node *ClientAttribStack[MAX_CLIENT_ATTRIB_STACK_DEPTH];
   /*@}*/

   /** \name Client attribute groups */
   /*@{*/
   struct gl_array_attrib	Array;	/**< \brief Vertex arrays */
   struct gl_pixelstore_attrib	Pack;	/**< \brief Pixel packing */
   struct gl_pixelstore_attrib	Unpack;	/**< \brief Pixel unpacking */

   struct gl_evaluators EvalMap;   /**< \brief All evaluators */
   struct gl_feedback   Feedback;  /**< \brief Feedback */
   struct gl_selection  Select;    /**< \brief Selection */

   struct gl_color_table ColorTable;       /**< \brief Pre-convolution */
   struct gl_color_table ProxyColorTable;  /**< \brief Pre-convolution */
   struct gl_color_table PostConvolutionColorTable;
   struct gl_color_table ProxyPostConvolutionColorTable;
   struct gl_color_table PostColorMatrixColorTable;
   struct gl_color_table ProxyPostColorMatrixColorTable;

   struct vertex_program_state VertexProgram;  /**< \brief GL_NV_vertex_program */

   GLenum ErrorValue;        /**< \brief Last error code */
   GLenum RenderMode;        /**< \brief either GL_RENDER, GL_SELECT, GL_FEEDBACK */
   GLuint NewState;          /**< \brief bitwise-or of _NEW_* flags */
   /*@}*/

   /** \name Derived */
   /*@{*/
   GLuint _TriangleCaps;      /**< \brief bitwise-or of DD_* flags */
   GLuint _ImageTransferState;/**< \brief bitwise-or of IMAGE_*_BIT flags */
   GLfloat _EyeZDir[3];
   GLfloat _ModelViewInvScale;
   GLuint _NeedEyeCoords;
   GLuint _ForceEyeCoords; 
   GLboolean _RotateMode;

   struct gl_shine_tab *_ShineTable[2]; /**< \brief Active shine tables */
   struct gl_shine_tab *_ShineTabList;  /**< \brief Mru list of inactive shine tables */
   /**@}*/

   struct gl_list_extensions listext; /**< \brief driver dlist extensions */


   GLboolean OcclusionResult;       /**< \brief*< for GL_HP_occlusion_test */
   GLboolean OcclusionResultSaved;  /**< \brief*< for GL_HP_occlusion_test */
   GLuint _Facing; /**< \brief This is a hack for 2-sided stencil test.
		    *
		    * We don't have a better way to communicate this value from
		    * swrast_setup to swrast. */


   /** \name Z buffer stuff */
   /*@{*/
   GLuint DepthMax;	/**< \brief Max depth buffer value */
   GLfloat DepthMaxF;	/**< \brief Float max depth buffer value */
   GLfloat MRD;		/**< \brief minimum resolvable difference in Z values */
   /*@}*/

   /** \brief Should 3Dfx Glide driver catch signals? */
   GLboolean CatchSignals;

   /** \name For debugging/development only */
   /*@{*/
   GLboolean NoRaster;
   GLboolean FirstTimeCurrent;
   /*@}*/

   /** \brief Dither disable via MESA_NO_DITHER env var */
   GLboolean NoDither;

   GLboolean Rendering;

#if defined(MESA_TRACE)
   struct _glapi_table *TraceDispatch;
   trace_context_t     *TraceCtx;
#else
   void *TraceDispatch;
   void *TraceCtx;
#endif

   /** \brief Core tnl module support */
   struct gl_tnl_module TnlModule;

   /**
    * \name Hooks for module contexts.  
    *
    * These will eventually live in the driver or elsewhere.
    */
   /*@{*/
   void *swrast_context;
   void *swsetup_context;
   void *swtnl_context;
   void *swtnl_im;
   void *acache_context;
   void *aelt_context;
   /*@}*/
};


/** \brief The string names for GL_POINT, GL_LINE_LOOP, etc */
extern const char *_mesa_prim_name[GL_POLYGON+4];

/* #ifndef MESA_DEBUG */
/* #define MESA_DEBUG */
/* #endif */

#ifdef MESA_DEBUG
extern int MESA_VERBOSE;
extern int MESA_DEBUG_FLAGS;
#else
# define MESA_VERBOSE 0
# define MESA_DEBUG_FLAGS 0
# ifndef NDEBUG
#  define NDEBUG
# endif
#endif


enum _verbose {
   VERBOSE_VARRAY		= 0x0001,
   VERBOSE_TEXTURE		= 0x0002,
   VERBOSE_IMMEDIATE		= 0x0004,
   VERBOSE_PIPELINE		= 0x0008,
   VERBOSE_DRIVER		= 0x0010,
   VERBOSE_STATE		= 0x0020,
   VERBOSE_API			= 0x0040,
   VERBOSE_DISPLAY_LIST		= 0x0100,
   VERBOSE_LIGHTING		= 0x0200,
   VERBOSE_PRIMS		= 0x0400,
   VERBOSE_VERTS		= 0x0800
};


enum _debug {
   DEBUG_ALWAYS_FLUSH		= 0x1
};



#define Elements(x) sizeof(x)/sizeof(*(x))


/* Eventually let the driver specify what statechanges require a flush:
 */
#define FLUSH_VERTICES(ctx, newstate)				\
do {								\
   if (MESA_VERBOSE & VERBOSE_STATE)				\
      _mesa_debug(ctx, "FLUSH_VERTICES in %s\n", __FUNCTION__);	\
   if (ctx->Driver.NeedFlush & FLUSH_STORED_VERTICES)		\
      ctx->Driver.FlushVertices(ctx, FLUSH_STORED_VERTICES);	\
   ctx->NewState |= newstate;					\
} while (0)

#define FLUSH_CURRENT(ctx, newstate)				\
do {								\
   if (MESA_VERBOSE & VERBOSE_STATE)				\
      _mesa_debug(ctx, "FLUSH_CURRENT in %s\n", __FUNCTION__);	\
   if (ctx->Driver.NeedFlush & FLUSH_UPDATE_CURRENT)		\
      ctx->Driver.FlushVertices(ctx, FLUSH_UPDATE_CURRENT);	\
   ctx->NewState |= newstate;					\
} while (0)

#define ASSERT_OUTSIDE_BEGIN_END_WITH_RETVAL(ctx, retval)		\
do {									\
   if (ctx->Driver.CurrentExecPrimitive != PRIM_OUTSIDE_BEGIN_END) {	\
      _mesa_error( ctx, GL_INVALID_OPERATION, "begin/end" );		\
      return retval;							\
   }									\
} while (0)

#define ASSERT_OUTSIDE_BEGIN_END(ctx)					\
do {									\
   if (ctx->Driver.CurrentExecPrimitive != PRIM_OUTSIDE_BEGIN_END) {	\
      _mesa_error( ctx, GL_INVALID_OPERATION, "begin/end" );		\
      return;								\
   }									\
} while (0)

#define ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx)				\
do {									\
   ASSERT_OUTSIDE_BEGIN_END(ctx);					\
   FLUSH_VERTICES(ctx, 0);						\
} while (0)

#define ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH_WITH_RETVAL(ctx, retval)	\
do {									\
   ASSERT_OUTSIDE_BEGIN_END_WITH_RETVAL(ctx, retval);			\
   FLUSH_VERTICES(ctx, 0);						\
} while (0)




#endif /* TYPES_H */
