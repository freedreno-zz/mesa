/**************************************************************************
 * 
 * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.
 * All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 **************************************************************************/


#include "glheader.h"
#include "context.h"
#include "matrix.h"
#include "simple_list.h"
#include "extensions.h"
#include "framebuffer.h"
#include "imports.h"

#include "swrast/swrast.h"
#include "swrast_setup/swrast_setup.h"
#include "tnl/tnl.h"
#include "array_cache/acache.h"

#include "tnl/t_pipeline.h"
#include "tnl/t_vertex.h"

#include "drivers/common/driverfuncs.h"

#include "intel_screen.h"

#include "i830_dri.h"

#include "intel_buffers.h"
#include "intel_tex.h"
#include "intel_span.h"
#include "intel_tris.h"
#include "intel_ioctl.h"
#include "intel_batchbuffer.h"
#include "intel_blit.h"
#include "intel_pixel.h"
#include "intel_regions.h"
#include "intel_buffer_objects.h"
#include "intel_fbo.h"

#include "intel_bufmgr.h"

#include "utils.h"
#ifndef INTEL_DEBUG
int INTEL_DEBUG = (0);
#endif

#define need_GL_ARB_multisample
#define need_GL_ARB_point_parameters
#define need_GL_ARB_texture_compression
#define need_GL_ARB_vertex_buffer_object
#define need_GL_ARB_vertex_program
#define need_GL_ARB_window_pos
#define need_GL_EXT_blend_color
#define need_GL_EXT_blend_equation_separate
#define need_GL_EXT_blend_func_separate
#define need_GL_EXT_blend_minmax
#define need_GL_EXT_cull_vertex
#define need_GL_EXT_fog_coord
#define need_GL_EXT_framebuffer_object
#define need_GL_EXT_multi_draw_arrays
#define need_GL_EXT_secondary_color
#define need_GL_NV_vertex_program
#include "extension_helper.h"


#define DRIVER_DATE                     "20060212"

static const GLubyte *intelGetString( GLcontext *ctx, GLenum name )
{
   const char * chipset;
   static char buffer[128];

   switch (name) {
   case GL_VENDOR:
      return (GLubyte *)"Tungsten Graphics, Inc";
      break;
      
   case GL_RENDERER:
      switch (intel_context(ctx)->intelScreen->deviceID) {
      case PCI_CHIP_845_G:
	 chipset = "Intel(R) 845G"; break;
      case PCI_CHIP_I830_M:
	 chipset = "Intel(R) 830M"; break;
      case PCI_CHIP_I855_GM:
	 chipset = "Intel(R) 852GM/855GM"; break;
      case PCI_CHIP_I865_G:
	 chipset = "Intel(R) 865G"; break;
      case PCI_CHIP_I915_G:
	 chipset = "Intel(R) 915G"; break;
      case PCI_CHIP_I915_GM:
	 chipset = "Intel(R) 915GM"; break;
      case PCI_CHIP_I945_G:
	 chipset = "Intel(R) 945G"; break;
      default:
	 chipset = "Unknown Intel Chipset"; break;
      }

      (void) driGetRendererString( buffer, chipset, DRIVER_DATE, 0 );
      return (GLubyte *) buffer;

   default:
      return NULL;
   }
}


/**
 * Extension strings exported by the intel driver.
 *
 * \note
 * It appears that ARB_texture_env_crossbar has "disappeared" compared to the
 * old i830-specific driver.
 */
const struct dri_extension card_extensions[] =
{
    { "GL_ARB_multisample",                GL_ARB_multisample_functions },
    { "GL_ARB_multitexture",               NULL },
    { "GL_ARB_point_parameters",           GL_ARB_point_parameters_functions },
    { "GL_ARB_texture_border_clamp",       NULL },
    { "GL_ARB_texture_compression",        GL_ARB_texture_compression_functions },
    { "GL_ARB_texture_cube_map",           NULL },
    { "GL_ARB_texture_env_add",            NULL },
    { "GL_ARB_texture_env_combine",        NULL },
    { "GL_ARB_texture_env_dot3",           NULL },
    { "GL_ARB_texture_mirrored_repeat",    NULL },
    { "GL_ARB_texture_rectangle",          NULL },
    { "GL_ARB_vertex_buffer_object",       GL_ARB_vertex_buffer_object_functions },
    { "GL_ARB_pixel_buffer_object",        NULL },
    { "GL_ARB_vertex_program",             GL_ARB_vertex_program_functions },
    { "GL_ARB_window_pos",                 GL_ARB_window_pos_functions },
    { "GL_EXT_blend_color",                GL_EXT_blend_color_functions },
    { "GL_EXT_blend_equation_separate",    GL_EXT_blend_equation_separate_functions },
    { "GL_EXT_blend_func_separate",        GL_EXT_blend_func_separate_functions },
    { "GL_EXT_blend_minmax",               GL_EXT_blend_minmax_functions },
    { "GL_EXT_blend_subtract",             NULL },
    { "GL_EXT_cull_vertex",                GL_EXT_cull_vertex_functions },
    { "GL_EXT_fog_coord",                  GL_EXT_fog_coord_functions },
    { "GL_EXT_framebuffer_object",         GL_EXT_framebuffer_object_functions },
    { "GL_EXT_multi_draw_arrays",          GL_EXT_multi_draw_arrays_functions },
#if 1 /* XXX FBO temporary? */
    { "GL_EXT_packed_depth_stencil",       NULL },
#endif
    { "GL_EXT_secondary_color",            GL_EXT_secondary_color_functions },
    { "GL_EXT_stencil_wrap",               NULL },
    { "GL_EXT_texture_edge_clamp",         NULL },
    { "GL_EXT_texture_env_combine",        NULL },
    { "GL_EXT_texture_env_dot3",           NULL },
    { "GL_EXT_texture_filter_anisotropic", NULL },
    { "GL_EXT_texture_lod_bias",           NULL },
    { "GL_3DFX_texture_compression_FXT1",  NULL },
    { "GL_APPLE_client_storage",           NULL },
    { "GL_MESA_pack_invert",               NULL },
    { "GL_MESA_ycbcr_texture",             NULL },
    { "GL_NV_blend_square",                NULL },
    { "GL_NV_vertex_program",              GL_NV_vertex_program_functions },
    { "GL_NV_vertex_program1_1",           NULL },
/*     { "GL_SGIS_generate_mipmap",           NULL }, */
    { NULL,                                NULL }
};

extern const struct tnl_pipeline_stage _intel_render_stage;

static const struct tnl_pipeline_stage *intel_pipeline[] = {
   &_tnl_vertex_transform_stage,
   &_tnl_vertex_cull_stage,
   &_tnl_normal_transform_stage,
   &_tnl_lighting_stage,
   &_tnl_fog_coordinate_stage,
   &_tnl_texgen_stage,
   &_tnl_texture_transform_stage,
   &_tnl_point_attenuation_stage,
   &_tnl_arb_vertex_program_stage,
   &_tnl_vertex_program_stage,
#if 1
   &_intel_render_stage,     /* ADD: unclipped rastersetup-to-dma */
#endif
   &_tnl_render_stage,
   0,
};


static const struct dri_debug_control debug_control[] =
{
    { "fall",  DEBUG_FALLBACKS },
    { "tex",   DEBUG_TEXTURE },
    { "ioctl", DEBUG_IOCTL },
    { "prim",  DEBUG_PRIMS },
    { "vert",  DEBUG_VERTS },
    { "state", DEBUG_STATE },
    { "verb",  DEBUG_VERBOSE },
    { "dri",   DEBUG_DRI },
    { "dma",   DEBUG_DMA },
    { "san",   DEBUG_SANITY },
    { "sync",  DEBUG_SYNC },
    { "sleep", DEBUG_SLEEP },
    { "pix",   DEBUG_PIXEL },
    { "buf",   DEBUG_BUFMGR },
    { NULL,    0 }
};


static void intelInvalidateState( GLcontext *ctx, GLuint new_state )
{
   _swrast_InvalidateState( ctx, new_state );
   _swsetup_InvalidateState( ctx, new_state );
   _ac_InvalidateState( ctx, new_state );
   _tnl_InvalidateState( ctx, new_state );
   _tnl_invalidate_vertex_state( ctx, new_state );
   intel_context(ctx)->NewGLState |= new_state;
}


void intelFlush( GLcontext *ctx )
{
   struct intel_context *intel = intel_context( ctx );

   if (intel->Fallback)
      _swrast_flush( ctx );

   INTEL_FIREVERTICES( intel );

   if (intel->batch->map != intel->batch->ptr)
      intel_batchbuffer_flush( intel->batch );

   /* XXX: Need to do an MI_FLUSH here.  Actually, the bufmgr_fake.c
    * code will have done one already.
    */
}

void intelFinish( GLcontext *ctx ) 
{
   struct intel_context *intel = intel_context( ctx );
   intelFlush( ctx );
   bmFinishFence( intel->bm, intel->batch->last_fence );
}


void intelInitDriverFunctions( struct dd_function_table *functions )
{
   _mesa_init_driver_functions( functions );

   functions->Flush = intelFlush;
   functions->Finish = intelFinish;
   functions->GetString = intelGetString;
   functions->UpdateState = intelInvalidateState;
   functions->CopyColorTable = _swrast_CopyColorTable;
   functions->CopyColorSubTable = _swrast_CopyColorSubTable;
   functions->CopyConvolutionFilter1D = _swrast_CopyConvolutionFilter1D;
   functions->CopyConvolutionFilter2D = _swrast_CopyConvolutionFilter2D;

   intelInitTextureFuncs( functions );
   intelInitPixelFuncs( functions );
   intelInitStateFuncs( functions );
   intelInitBufferFuncs( functions );
}



GLboolean intelInitContext( struct intel_context *intel,
			    const __GLcontextModes *mesaVis,
			    __DRIcontextPrivate *driContextPriv,
			    void *sharedContextPrivate,
			    struct dd_function_table *functions )
{
   GLcontext *ctx = &intel->ctx;
   GLcontext *shareCtx = (GLcontext *) sharedContextPrivate;
   __DRIscreenPrivate *sPriv = driContextPriv->driScreenPriv;
   intelScreenPrivate *intelScreen = (intelScreenPrivate *)sPriv->private;
   drmI830Sarea *saPriv = (drmI830Sarea *)
      (((GLubyte *)sPriv->pSAREA)+intelScreen->sarea_priv_offset);

   if (!_mesa_initialize_context(&intel->ctx,
				 mesaVis, shareCtx, 
				 functions,
				 (void*) intel))
      return GL_FALSE;

   driContextPriv->driverPrivate = intel;
   intel->intelScreen = intelScreen;
   intel->driScreen = sPriv;
   intel->sarea = saPriv;


   ctx->Const.MaxTextureMaxAnisotropy = 2.0;

   ctx->Const.MinLineWidth = 1.0;
   ctx->Const.MinLineWidthAA = 1.0;
   ctx->Const.MaxLineWidth = 3.0;
   ctx->Const.MaxLineWidthAA = 3.0;
   ctx->Const.LineWidthGranularity = 1.0;

   ctx->Const.MinPointSize = 1.0;
   ctx->Const.MinPointSizeAA = 1.0;
   ctx->Const.MaxPointSize = 255.0;
   ctx->Const.MaxPointSizeAA = 3.0;
   ctx->Const.PointSizeGranularity = 1.0;

   ctx->Const.MaxColorAttachments = 4; /* XXX FBO: review this */

   /* Initialize the software rasterizer and helper modules. */
   _swrast_CreateContext( ctx );
   _ac_CreateContext( ctx );
   _tnl_CreateContext( ctx );
   _swsetup_CreateContext( ctx );

   /* Install the customized pipeline: */
   _tnl_destroy_pipeline( ctx );
   _tnl_install_pipeline( ctx, intel_pipeline );

   /* Configure swrast to match hardware characteristics: */
   _swrast_allow_pixel_fog( ctx, GL_FALSE );
   _swrast_allow_vertex_fog( ctx, GL_TRUE );

   /* Dri stuff */
   intel->hHWContext = driContextPriv->hHWContext;
   intel->driFd = sPriv->fd;
   intel->driHwLock = (drmLock *) &sPriv->pSAREA->lock;

   intel->hw_stipple = 1;

   /* XXX FBO: this doesn't seem to be used anywhere */
   switch(mesaVis->depthBits) {
   case 0:			/* what to do in this case? */
   case 16:
      intel->polygon_offset_scale = 1.0/0xffff;
      break;
   case 24:
      intel->polygon_offset_scale = 2.0/0xffffff; /* req'd to pass glean */
      break;
   default:
      assert(0); 
      break;
   }

   /* Initialize swrast, tnl driver tables: */
   intelInitSpanFuncs( ctx );
   intelInitTriFuncs( ctx );


   intel->RenderIndex = ~0;

   intel->do_irqs = (intel->intelScreen->irq_active &&
		     !getenv("INTEL_NO_IRQS"));

   _math_matrix_ctr (&intel->ViewportMatrix);

   /* Disable imaging extension until convolution is working in
    * teximage paths:
    */
   driInitExtensions( ctx, card_extensions, 
/* 		      GL_TRUE, */
		      GL_FALSE);


   /* Buffer manager: 
    */
   intel->bm = bm_intel_Attach( intel );
#if 0
   bmInitPool(intel->bm,
              intel->intelScreen->tex.offset, /* low offset */
              intel->intelScreen->tex.map, /* low virtual */
              intel->intelScreen->tex.size,
	      DRM_MM_TT);
#endif

   /* XXX FBO: these have to go away!
    * FBO regions should be setup when creating the drawable. */

   /* These are still static, but create regions for them.  
    */
   intel->front_region = 
      intel_region_create_static(intel,
				 DRM_MM_TT,
				 intelScreen->front.offset,
				 intelScreen->front.map,
				 intelScreen->cpp,
				 intelScreen->front.pitch,
				 intelScreen->height);


   intel->back_region = 
      intel_region_create_static(intel,
				 DRM_MM_TT,
				 intelScreen->back.offset,
				 intelScreen->back.map,
				 intelScreen->cpp,
				 intelScreen->back.pitch,
				 intelScreen->height);

   /* Still assuming front.cpp == depth.cpp
    */
   intel->depth_region = 
      intel_region_create_static(intel,
				 DRM_MM_TT,
				 intelScreen->depth.offset,
				 intelScreen->depth.map,
				 intelScreen->cpp,
				 intelScreen->depth.pitch,
				 intelScreen->height);
   
   intel->batch = intel_batchbuffer_alloc( intel );
   intel_bufferobj_init( intel );
   intel_fbo_init( intel );

   if (intel->ctx.Mesa_DXTn) {
     _mesa_enable_extension( ctx, "GL_EXT_texture_compression_s3tc" );
     _mesa_enable_extension( ctx, "GL_S3_s3tc" );
   }
   else if (driQueryOptionb (&intelScreen->optionCache, "force_s3tc_enable")) {
     _mesa_enable_extension( ctx, "GL_EXT_texture_compression_s3tc" );
   }

   intel->prim.primitive = ~0;


#if DO_DEBUG
   INTEL_DEBUG  = driParseDebugString( getenv( "INTEL_DEBUG" ),
				       debug_control );
#endif

   if (getenv("INTEL_NO_RAST")) {
      fprintf(stderr, "disabling 3D rasterization\n");
      FALLBACK(intel, INTEL_FALLBACK_USER, 1); 
   }

   return GL_TRUE;
}

void intelDestroyContext(__DRIcontextPrivate *driContextPriv)
{
   struct intel_context *intel = (struct intel_context *) driContextPriv->driverPrivate;

   assert(intel); /* should never be null */
   if (intel) {
      GLboolean   release_texture_heaps;


      intel->vtbl.destroy( intel );

      release_texture_heaps = (intel->ctx.Shared->RefCount == 1);
      _swsetup_DestroyContext (&intel->ctx);
      _tnl_DestroyContext (&intel->ctx);
      _ac_DestroyContext (&intel->ctx);

      _swrast_DestroyContext (&intel->ctx);
      intel->Fallback = 0;	/* don't call _swrast_Flush later */

      intel_batchbuffer_free(intel->batch);
      

      if ( release_texture_heaps ) {
         /* This share group is about to go away, free our private
          * texture object data.
          */
	 fprintf(stderr, "do something to free texture heaps\n");
      }

      /* free the Mesa context */
      _mesa_free_context_data(&intel->ctx);
   }
}

GLboolean intelUnbindContext(__DRIcontextPrivate *driContextPriv)
{
   return GL_TRUE;
}

GLboolean intelMakeCurrent(__DRIcontextPrivate *driContextPriv,
			  __DRIdrawablePrivate *driDrawPriv,
			  __DRIdrawablePrivate *driReadPriv)
{

   if (driContextPriv) {
      struct intel_context *intel = (struct intel_context *) driContextPriv->driverPrivate;
      GLframebuffer *drawFb = (GLframebuffer *) driDrawPriv->driverPrivate;
      GLframebuffer *readFb = (GLframebuffer *) driReadPriv->driverPrivate;

      if ( intel->driDrawable != driDrawPriv ) {
	 /* Shouldn't the readbuffer be stored also? */
	 intel->driDrawable = driDrawPriv;
	 intelWindowMoved( intel );
      }

      /* XXX FBO temporary fix-ups! */
      /* if the renderbuffers don't have regions, init them from the context */
      {
         struct intel_renderbuffer *irbFront
            = intel_get_renderbuffer(drawFb, BUFFER_FRONT_LEFT);
         struct intel_renderbuffer *irbBack
            = intel_get_renderbuffer(drawFb, BUFFER_BACK_LEFT);
         struct intel_renderbuffer *irbDepth
            = intel_get_renderbuffer(drawFb, BUFFER_DEPTH);
         struct intel_renderbuffer *irbStencil
            = intel_get_renderbuffer(drawFb, BUFFER_STENCIL);

         if (irbFront && !irbFront->region) {
            intel_region_reference(&irbFront->region, intel->front_region);
         }
         if (irbBack && !irbBack->region) {
            intel_region_reference(&irbBack->region, intel->back_region);
         }
         if (irbDepth && !irbDepth->region) {
            intel_region_reference(&irbDepth->region, intel->depth_region);
         }
         if (irbStencil && !irbStencil->region) {
            intel_region_reference(&irbStencil->region, intel->depth_region);
         }
      }

      _mesa_make_current(&intel->ctx, drawFb, readFb);

      intel_draw_buffer(&intel->ctx, drawFb);
   }
   else {
      _mesa_make_current(NULL, NULL, NULL);
   }

   return GL_TRUE;
}

void intelGetLock( struct intel_context *intel, GLuint flags )
{
   __DRIdrawablePrivate *dPriv = intel->driDrawable;
   __DRIscreenPrivate *sPriv = intel->driScreen;
   drmI830Sarea * sarea = intel->sarea;
   int me = intel->hHWContext;

   drmGetLock(intel->driFd, intel->hHWContext, flags);

   /* If the window moved, may need to set a new cliprect now.
    *
    * NOTE: This releases and regains the hw lock, so all state
    * checking must be done *after* this call:
    */
   if (dPriv)
      DRI_VALIDATE_DRAWABLE_INFO(sPriv, dPriv);

   /* Lost context?
    */
   if (sarea->ctxOwner != me) {
      intel->perf_boxes |= I830_BOX_LOST_CONTEXT;
      sarea->ctxOwner = me;
   }

   /* Drawable changed?
    */
   if (dPriv && intel->lastStamp != dPriv->lastStamp) {
      intelWindowMoved( intel );
      intel->lastStamp = dPriv->lastStamp;
   }
}


