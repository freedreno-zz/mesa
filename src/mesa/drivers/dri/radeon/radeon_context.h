/**
 * \file radeon_context.h
 * \brief Radeon OpenGL context definition.
 * 
 * \author Kevin E. Martin <martin@valinux.com>
 * \author Gareth Hughes <gareth@valinux.com>
 * \author Keith Whitwell <keith@tungstengraphics.com>
 */

/*
 * Copyright 2000, 2001 ATI Technologies Inc., Ontario, Canada, and
 *                      VA Linux Systems Inc., Fremont, California.
 * 
 * All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * ATI, VA LINUX SYSTEMS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

/* $XFree86: xc/lib/GL/mesa/src/drv/radeon/radeon_context.h,v 1.4 2002/09/10 00:39:39 dawes Exp $ */

#ifndef __RADEON_CONTEXT_H__
#define __RADEON_CONTEXT_H__

struct radeon_context;
typedef struct radeon_context radeonContextRec;
typedef struct radeon_context *radeonContextPtr;

#include "mtypes.h"
#include "macros.h"
#include "radeon_lock.h"
#include "radeon_screen.h"
#include "mm.h"

#if _HAVE_SWTNL
#include "radeon_swtcl.h"
#endif

/**
 * \brief Color buffer state.
 */
struct radeon_colorbuffer_state {
   GLuint clear;	/**< \brief Clear value */	
   GLint drawOffset;	/**< \brief Drawing offset */
   GLint drawPitch;	/**< \brief Drawing pitch */
};

/**
 * \brief Depth buffer state.
 */
struct radeon_depthbuffer_state {
   GLuint clear;	/**< \brief Clear value */
   GLfloat scale;	/**< \brief Depth scale */
};

/**
 * \brief Pixel state.
 */
struct radeon_pixel_state {
   GLint readOffset;	/**< \brief Reading offset */
   GLint readPitch;	/**< \brief Reading pitch */
};

/**
 * \brief Scissor state.
 */
struct radeon_scissor_state {
   XF86DRIClipRectRec rect;
   GLboolean enabled;			/**< \brief Whether scissoring enable */

   GLuint numClipRects;			/**< \brief Number of active cliprects */
   GLuint numAllocedClipRects;		/**< \brief Number of available cliprects */
   XF86DRIClipRectPtr pClipRects;	/**< \brief Cliprects */
};

/**
 * \brief Stencil buffer state.
 */
struct radeon_stencilbuffer_state {
   GLboolean hwBuffer;			/**< \brief Hardware buffer available? */
   GLuint clear;			/**< \brief rb3d_stencilrefmask value */
};

/**
 * \brief Stipple state.
 */
struct radeon_stipple_state {
   GLuint mask[32];	/**< \brief Mask */
};



#define TEX_0   0x1
#define TEX_1   0x2
#define TEX_ALL 0x3


typedef struct radeon_tex_obj radeonTexObj;	/**< \brief Alias for radeon_tex_obj. */
typedef struct radeon_tex_obj *radeonTexObjPtr;	/**< \brief Alias for radeon_tex_obj. */


/**
 * \brief Texture object in locally shared texture space.
 */
struct radeon_tex_obj {
   radeonTexObjPtr next, prev;

   /** \brief Mesa texture object */
   struct gl_texture_object *tObj;	

   /** \brief Memory block containing texture */
   PMemBlock memBlock;			
   
   /** \brief Offset to start of locally shared texture block */
   GLuint bufAddr;
   
   /**
    * \brief Flags for whether or not images need to be uploaded to local or AGP
    * texture space
    */
   GLuint dirty_images;			

   /**
    * \brief Flags (one per texture unit) for whether or not this texture
    * object has dirty hardware state (\c pp_*) that needs to be brought into
    * the texunit.
    */
   GLuint dirty_state;

   /** \brief Texture heap currently stored in */
   GLint heap;				

   /** \brief Texture images */
   drmRadeonTexImage image[RADEON_MAX_TEXTURE_LEVELS];

   /** \brief Total size of the texture including all mipmap levels */
   GLint totalSize;

   /**
    * \name Hardware register values.
    */
   /*@{*/
   GLuint pp_txfilter;
   GLuint pp_txformat;
   GLuint pp_txoffset;
   GLuint pp_border_color;
   /*@}*/

   /**
    * \name Images to upload
    * 
    * texObj->Image[firstLevel] through texObj->Image[lastLevel] are the
    * images to upload.
    */
   /*@{*/
   GLint firstLevel;     
   GLint lastLevel;
   /*@}*/
};

/**
 * \brief Texture environment state.
 */
struct radeon_texture_env_state {
   radeonTexObjPtr texobj; /**< \brief texture object */
   GLenum format;          /**< \brief format */
   GLenum envMode;         /**< \brief environment mode */
};

/**
 * \brief Texture state
 */
struct radeon_texture_state {
   struct radeon_texture_env_state unit[RADEON_MAX_TEXTURE_UNITS]; /**< \brief for each unit */
};


/**
 * \brief Radeon state atom double-linked list.
 */
struct radeon_state_atom {
   struct radeon_state_atom *next, *prev;
   const char *name;		         /**< \brief for debugging purposes */
   int cmd_size;		         /**< \brief size in bytes */
   GLuint is_tcl;                        /**< \brief whether is associated with TCL */
   int *cmd;			         /**< \brief one or more cmd's */
   int *lastcmd;			 /**< \brief one or more cmd's */
   GLboolean (*check)( GLcontext * );    /**< \brief callback to determin whether this state is active */
};
   


/* Trying to keep these relatively short as the variables are becoming
 * extravagently long.  Drop the RADEON_ off the front of everything -
 * I think we know we're in the radeon driver by now, and keep the
 * prefix to 3 letters unless absolutely impossible.  
 */

#define CTX_CMD_0             0
#define CTX_PP_MISC           1
#define CTX_PP_FOG_COLOR      2
#define CTX_RE_SOLID_COLOR    3
#define CTX_RB3D_BLENDCNTL    4
#define CTX_RB3D_DEPTHOFFSET  5
#define CTX_RB3D_DEPTHPITCH   6
#define CTX_RB3D_ZSTENCILCNTL 7
#define CTX_CMD_1             8
#define CTX_PP_CNTL           9
#define CTX_RB3D_CNTL         10
#define CTX_RB3D_COLOROFFSET  11
#define CTX_CMD_2             12
#define CTX_RB3D_COLORPITCH   13
#define CTX_STATE_SIZE        14

#define SET_CMD_0               0
#define SET_SE_CNTL             1
#define SET_SE_COORDFMT         2
#define SET_CMD_1               3
#define SET_SE_CNTL_STATUS      4
#define SET_STATE_SIZE          5

#define LIN_CMD_0               0
#define LIN_RE_LINE_PATTERN     1
#define LIN_RE_LINE_STATE       2
#define LIN_CMD_1               3
#define LIN_SE_LINE_WIDTH       4
#define LIN_STATE_SIZE          5

#define MSK_CMD_0               0
#define MSK_RB3D_STENCILREFMASK 1
#define MSK_RB3D_ROPCNTL        2
#define MSK_RB3D_PLANEMASK      3
#define MSK_STATE_SIZE          4

#define VPT_CMD_0                    0
#define VPT_SE_VPORT_XSCALE          1
#define VPT_SE_VPORT_XOFFSET         2
#define VPT_SE_VPORT_YSCALE          3
#define VPT_SE_VPORT_YOFFSET         4
#define VPT_SE_VPORT_ZSCALE          5
#define VPT_SE_VPORT_ZOFFSET         6
#define VPT_STATE_SIZE               7

#define MSC_CMD_0               0
#define MSC_RE_MISC             1
#define MSC_STATE_SIZE          2

#define TEX_CMD_0                   0
#define TEX_PP_TXFILTER             1
#define TEX_PP_TXFORMAT             2
#define TEX_PP_TXOFFSET             3
#define TEX_PP_TXCBLEND             4
#define TEX_PP_TXABLEND             5
#define TEX_PP_TFACTOR              6
#define TEX_CMD_1                   7
#define TEX_PP_BORDER_COLOR         8
#define TEX_STATE_SIZE              9

#define ZBS_CMD_0                   0
#define ZBS_SE_ZBIAS_FACTOR         1
#define ZBS_SE_ZBIAS_CONSTANT       2
#define ZBS_STATE_SIZE              3

#define TCL_CMD_0                 0
#define TCL_OUTPUT_VTXFMT         1
#define TCL_OUTPUT_VTXSEL         2
#define TCL_MATRIX_SELECT_0       3
#define TCL_MATRIX_SELECT_1       4
#define TCL_UCP_VERT_BLEND_CTL    5
#define TCL_TEXTURE_PROC_CTL      6
#define TCL_LIGHT_MODEL_CTL       7
#define TCL_PER_LIGHT_CTL_0       8
#define TCL_PER_LIGHT_CTL_1       9
#define TCL_PER_LIGHT_CTL_2       10
#define TCL_PER_LIGHT_CTL_3       11
#define TCL_STATE_SIZE            12

#define MTL_CMD_0            0	
#define MTL_EMMISSIVE_RED    1	
#define MTL_EMMISSIVE_GREEN  2	
#define MTL_EMMISSIVE_BLUE   3	
#define MTL_EMMISSIVE_ALPHA  4	
#define MTL_AMBIENT_RED      5
#define MTL_AMBIENT_GREEN    6
#define MTL_AMBIENT_BLUE     7
#define MTL_AMBIENT_ALPHA    8
#define MTL_DIFFUSE_RED      9
#define MTL_DIFFUSE_GREEN    10
#define MTL_DIFFUSE_BLUE     11
#define MTL_DIFFUSE_ALPHA    12
#define MTL_SPECULAR_RED     13
#define MTL_SPECULAR_GREEN   14
#define MTL_SPECULAR_BLUE    15
#define MTL_SPECULAR_ALPHA   16
#define MTL_SHININESS        17
#define MTL_STATE_SIZE       18

#define VTX_CMD_0              0
#define VTX_SE_COORD_FMT       1
#define VTX_STATE_SIZE         2

#define MAT_CMD_0              0
#define MAT_ELT_0              1
#define MAT_STATE_SIZE         17

#define GRD_CMD_0                  0
#define GRD_VERT_GUARD_CLIP_ADJ    1
#define GRD_VERT_GUARD_DISCARD_ADJ 2
#define GRD_HORZ_GUARD_CLIP_ADJ    3
#define GRD_HORZ_GUARD_DISCARD_ADJ 4
#define GRD_STATE_SIZE             5

/* position changes frequently when lighting in modelpos - separate
 * out to new state item?  
 */
#define LIT_CMD_0                  0
#define LIT_AMBIENT_RED            1
#define LIT_AMBIENT_GREEN          2
#define LIT_AMBIENT_BLUE           3
#define LIT_AMBIENT_ALPHA          4
#define LIT_DIFFUSE_RED            5
#define LIT_DIFFUSE_GREEN          6
#define LIT_DIFFUSE_BLUE           7
#define LIT_DIFFUSE_ALPHA          8
#define LIT_SPECULAR_RED           9
#define LIT_SPECULAR_GREEN         10
#define LIT_SPECULAR_BLUE          11
#define LIT_SPECULAR_ALPHA         12
#define LIT_POSITION_X             13
#define LIT_POSITION_Y             14
#define LIT_POSITION_Z             15
#define LIT_POSITION_W             16
#define LIT_DIRECTION_X            17
#define LIT_DIRECTION_Y            18
#define LIT_DIRECTION_Z            19
#define LIT_DIRECTION_W            20
#define LIT_ATTEN_CONST            21
#define LIT_ATTEN_LINEAR           22
#define LIT_ATTEN_QUADRATIC        23
#define LIT_ATTEN_XXX              24
#define LIT_CMD_1                  25
#define LIT_SPOT_DCD               26
#define LIT_SPOT_EXPONENT          27
#define LIT_SPOT_CUTOFF            28
#define LIT_SPECULAR_THRESH        29
#define LIT_RANGE_CUTOFF           30 /* ? */
#define LIT_RANGE_ATTEN            31 /* ? */
#define LIT_STATE_SIZE             32

/* Fog
 */
#define FOG_CMD_0      0
#define FOG_R          1
#define FOG_C          2
#define FOG_D          3
#define FOG_PAD        4
#define FOG_STATE_SIZE 5

/* UCP
 */
#define UCP_CMD_0      0
#define UCP_X          1
#define UCP_Y          2
#define UCP_Z          3
#define UCP_W          4
#define UCP_STATE_SIZE 5

/* GLT - Global ambient
 */
#define GLT_CMD_0      0
#define GLT_RED        1
#define GLT_GREEN      2
#define GLT_BLUE       3
#define GLT_ALPHA      4
#define GLT_STATE_SIZE 5

/* EYE
 */
#define EYE_CMD_0          0
#define EYE_X              1
#define EYE_Y              2
#define EYE_Z              3
#define EYE_RESCALE_FACTOR 4
#define EYE_STATE_SIZE     5

#define SHN_CMD_0          0
#define SHN_SHININESS      1
#define SHN_STATE_SIZE     2


/**
 * \brief Hardware state management.
 */
struct radeon_hw_state {
   /**
    * \name State
    * 
    * All state should be on one of these lists
    */
   /*@{*/
   struct radeon_state_atom dirty; /**< \brief dirty list head placeholder */
   struct radeon_state_atom clean; /**< \brief clean list head placeholder */
   /*@}*/

   /**
    * \name Hardware state
    * 
    * Stored as cmdbuf commands:  
    * - Need to doublebuffer for
    *   - reviving state after loss of context
    *   - eliding no-op statechange loops? (except line stipple count)
    */
   /*@{*/
   struct radeon_state_atom ctx;
   struct radeon_state_atom set;
   struct radeon_state_atom lin;
   struct radeon_state_atom msk;
   struct radeon_state_atom vpt;
   struct radeon_state_atom tcl;	/**< \ brief TCL */
   struct radeon_state_atom msc;
   struct radeon_state_atom tex[2];
   struct radeon_state_atom zbs;
   struct radeon_state_atom mtl; 
   struct radeon_state_atom mat[5];	/**< \brief matrix transformations */
   struct radeon_state_atom lit[8];	/**< \brief includes vec, scl commands */
   struct radeon_state_atom ucp[6];
   struct radeon_state_atom eye;	/**< \brief eye pos */
   struct radeon_state_atom grd;	/**< \brief guard band clipping */
   struct radeon_state_atom fog;	/**< \brief fog */
   struct radeon_state_atom glt; 
   /*@}*/
};

/**
 * \brief Derived state for internal purposes:
 */
struct radeon_state {
   struct radeon_colorbuffer_state color;	/**< \brief Color buffer */
   struct radeon_depthbuffer_state depth;	/**< \brief Depth buffer */
   struct radeon_pixel_state pixel;		/**< \brief Pixel */
   struct radeon_scissor_state scissor;		/**< \brief Scissor */
   struct radeon_stencilbuffer_state stencil;	/**< \brief Stencil buffer */
   struct radeon_stipple_state stipple;		/**< \brief Stipple */
   struct radeon_texture_state texture;		/**< \brief Textures */
};

/**
 * \brief Texture information
 */
struct radeon_texture {
   radeonTexObj objects[RADEON_NR_TEX_HEAPS];	/**< \brief texture objects */
   radeonTexObj swapped;			/**< \brief swapped texture  */

   memHeap_t *heap[RADEON_NR_TEX_HEAPS];	/**< \brief texture heaps */
   GLint age[RADEON_NR_TEX_HEAPS];		/**< \brief aging */

   GLint numHeaps;				/**< \brief number of active heaps */
};

/**
 * \brief Reference counting on DMA buffers.
 */
struct radeon_dma_buffer {
   int refcount;	/**< \brief number of retained regions in radeon_dma_buffer::buf */
   drmBufPtr buf;	/**< \brief DMA buffer */
};

/**
 * \brief Get the start of a DMA region.
 *
 * \param rvb pointer to a radeon_dma_region structure.
 *
 * \return pointer to the region start.
 */
#define GET_START(rvb) (rmesa->radeonScreen->agp_buffer_offset +	\
			(rvb)->address - rmesa->dma.buf0_address +	\
			(rvb)->start)

/**
 * \brief A retained DMA region.
 *
 * e.g. vertices for indexed vertices.
 */
struct radeon_dma_region {
   struct radeon_dma_buffer *buf;	/**< \brief DMA buffer */
   char *address;			/**< \brief buf->address */
   int start;				/**< \brief start offset from start of radeon_dma_region::buf */
   int end;				/**< \brief end offset from start of radeon_dma_region::buf */
   int ptr;				/**< \brief offsets from start of radeon_dma_region::buf */
   int aos_start;			/**< \brief array of structures start */
   int aos_stride;			/**< \brief array of structures stride */
   int aos_size;			/**< \brief array of structures size */
};


/**
 * \brief DMA information
 */
struct radeon_dma {
   /**
    * \brief Active DMA region.  
    *
    * Allocations for vertices and retained regions come from here.  Also used
    * for emitting random vertices, these may be flushed by calling
    * radeon_dma::flush.
    */
   struct radeon_dma_region current;
   
   /**
    * \brief Callback to flush the vertices in radeon_dma::current.
    */
   void (*flush)( radeonContextPtr );

   char *buf0_address;		/**< \brief start of buf[0], for index calculations */
   GLuint nr_released_bufs;	/**< \brief flush after so many buffers released */
};

/**
 * \brief Mirror some DRI context.
 */
struct radeon_dri_mirror {
   __DRIcontextPrivate	*context;	/**< \brief DRI context */
   __DRIscreenPrivate	*screen;	/**< \brief DRI screen */
   __DRIdrawablePrivate	*drawable;	/**< \brief DRI drawable bound to this context */

   drmContext hwContext;		
   drmLock *hwLock;			/**< \brief hardware lock */
   int fd;				/**< \brief DRM device file descriptor */
   int drmMinor;			/**< \brief DRM device minor number */
};

/**
 * \brief Command buffer size
 */
#define RADEON_CMD_BUF_SZ  (8*1024) 

/**
 * \brief Command buffering.
 */
struct radeon_store {
   GLuint statenr;                  /**< \brief state number */
   GLuint primnr;                   /**< \brief primitive number */
   char cmd_buf[RADEON_CMD_BUF_SZ]; /**< \brief command buffer */
   int cmd_used;                    /**< \brief used commands */
   int elts_start;
};


/**
 * \brief TCL information.
 */
struct radeon_tcl_info {
   GLuint vertex_format;
   GLint last_offset;
   GLuint hw_primitive;
   GLuint tcl_flag;			/**< \brief Whether TCL is inabled */

   struct radeon_dma_region *aos_components[8];
   GLuint nr_aos_components;

   GLuint *Elts;

   struct radeon_dma_region indexed_verts;
   struct radeon_dma_region obj;
   struct radeon_dma_region rgba;
   struct radeon_dma_region spec;
   struct radeon_dma_region fog;
   struct radeon_dma_region tex[RADEON_MAX_TEXTURE_UNITS];
   struct radeon_dma_region norm;
};



/**
 * \brief Retained buffer.
 */
struct radeon_ioctl {
   GLuint vertex_offset; /**< \brief offset of the vertex buffer */
   GLuint vertex_size;   /**< \brief size of the vertex buffer */
};



/**
 * \brief Radeon GL context.
 */
struct radeon_context {
   /**
    * \brief Mesa context.
    */
   GLcontext *glCtx;			

   /**
    * \name Driver and hardware state management
    */
   /*@{*/
   struct radeon_hw_state hw; /**< \brief Hardware state */
   struct radeon_state state; /**< \brief Internal state */
   /*@}*/

   /**
    * \brief Texture object bookkeeping
    */
   struct radeon_texture texture;


   /**
    * \name Rasterization and vertex state
    */
   /*@{*/
   GLuint TclFallback;
   GLuint Fallback;
   GLuint NewGLState;
   /*@}*/
   
   /**
    * \name Temporaries for translating away float colors
    */
   /*@{*/
   struct gl_client_array UbyteColor;
   struct gl_client_array UbyteSecondaryColor;
   /*@}*/

   /**
    * \name Vertex buffers
    */
   /*@{*/
   struct radeon_ioctl ioctl; /**< \brief Retained vertex buffer */
   struct radeon_dma dma;     /**< \brief DMA information */
   struct radeon_store store; /**< \brief Command buffer */
   /*@}*/

   /**
    * \brief Page flipping
    */
   GLuint doPageFlip;

   /**
    * \name Busy waiting
    */
   /*@{*/
   GLuint do_usleeps;
   GLuint do_irqs;		/**< \brief Do IRQs */
   GLuint irqsEmitted;		/**< \brief IRQ transition counter.
				  * \sa radeonWaitForFrameCompletion(). */
   drmRadeonIrqWait iw;
   /*@}*/

   /**
    * \name Drawable, cliprect and scissor information
    */
   /*@{*/
   GLuint numClipRects;			/**< \brief Number of cliprects */
   XF86DRIClipRectPtr pClipRects;	/**< \brief cliprects for the draw buffer */
   unsigned int lastStamp;
   GLboolean lost_context;		/**< \brief re-emit all state */
   radeonScreenPtr radeonScreen;	/**< \brief Screen private DRI data */
   RADEONSAREAPrivPtr sarea;		/**< \brief Private SAREA data */
   /*@}*/

   /**
    * \name TCL stuff
    */
   /*@{*/
   GLmatrix TexGenMatrix[RADEON_MAX_TEXTURE_UNITS];
   GLboolean recheck_texgen[RADEON_MAX_TEXTURE_UNITS];
   GLboolean TexGenNeedNormals[RADEON_MAX_TEXTURE_UNITS];
   GLuint TexMatEnabled;
   GLuint TexGenEnabled;
   GLmatrix tmpmat;
   GLuint last_ReallyEnabled;
   /*@}*/

   /**
    * \brief VBI
    */
   GLuint vbl_seq;

   /* radeon_tcl.c
    */
   struct radeon_tcl_info tcl;

   /* radeon_swtcl.c
    */
#if _HAVE_SWTNL
   struct radeon_swtcl_info swtcl;
#endif

   /* radeon_vtxfmt.c
    */
/*    struct radeon_vbinfo vb; */

   /**
    * \brief Mirrors of some DRI state
    */
   struct radeon_dri_mirror dri;
};


/**
 * \brief Get the pointer to the Radeon context from the GL context.
 */
#define RADEON_CONTEXT(ctx)		((radeonContextPtr)(ctx->DriverCtx))


/** 
 * \brief Pack color.
 *
 * \param cpp desired characters (bytes) per pixel. Shouble be either 2 or 4.
 * \param r red color component.
 * \param r green color component.
 * \param b blue color component.
 * \param a alpha color component.
 *
 * \return the packed color, or zero if \p cpp is not supported.
 */
static __inline GLuint radeonPackColor( GLuint cpp,
					GLubyte r, GLubyte g,
					GLubyte b, GLubyte a )
{
   switch ( cpp ) {
   case 2:
      return PACK_COLOR_565( r, g, b );
   case 4:
      return PACK_COLOR_8888( a, r, g, b );
   default:
      return 0;
   }
}


/******************************************************************
 * Debugging:
 */
#define DO_DEBUG		1

#if DO_DEBUG
extern int RADEON_DEBUG;
#else
#define RADEON_DEBUG		0
#endif

#define DEBUG_TEXTURE	0x001
#define DEBUG_STATE	0x002
#define DEBUG_IOCTL	0x004
#define DEBUG_PRIMS	0x008
#define DEBUG_VERTS	0x010
#define DEBUG_FALLBACKS	0x020
#define DEBUG_VFMT	0x040
#define DEBUG_CODEGEN	0x080
#define DEBUG_VERBOSE	0x100
#define DEBUG_DRI       0x200
#define DEBUG_DMA       0x400
#define DEBUG_SANITY    0x800

#endif /* __RADEON_CONTEXT_H__ */
