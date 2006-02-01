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

#include "i915_context.h"
#include "imports.h"
#include "intel_tex.h"
#include "intel_tris.h"
#include "tnl/t_context.h"
#include "tnl/t_pipeline.h"
#include "tnl/t_vertex.h"

#include "swrast/swrast.h"
#include "swrast_setup/swrast_setup.h"
#include "tnl/tnl.h"
#include "array_cache/acache.h"

#include "utils.h"
#include "i915_reg.h"

#include "bufmgr.h"
#include "intel_regions.h"

/***************************************
 * Mesa's Driver Functions
 ***************************************/

static const struct dri_extension i915_extensions[] =
{
    { "GL_ARB_depth_texture",              NULL },
    { "GL_ARB_fragment_program",           NULL },
    { "GL_ARB_shadow",                     NULL },
    { "GL_EXT_shadow_funcs",               NULL },
    /* ARB extn won't work if not enabled */
    { "GL_SGIX_depth_texture",             NULL },
    { NULL,                                NULL }
};

/* Override intel default.
 */
static void i915InvalidateState( GLcontext *ctx, GLuint new_state )
{
   _swrast_InvalidateState( ctx, new_state );
   _swsetup_InvalidateState( ctx, new_state );
   _ac_InvalidateState( ctx, new_state );
   _tnl_InvalidateState( ctx, new_state );
   _tnl_invalidate_vertex_state( ctx, new_state );
   INTEL_CONTEXT(ctx)->NewGLState |= new_state;

   /* Todo: gather state values under which tracked parameters become
    * invalidated, add callbacks for things like
    * ProgramLocalParameters, etc.
    */
   {
      struct i915_fragment_program *p = 
	 (struct i915_fragment_program *)ctx->FragmentProgram._Current;
      if (p && p->nr_params)
	 p->params_uptodate = 0;
   }

   if (new_state & (_NEW_FOG|_NEW_HINT|_NEW_PROGRAM))
      i915_update_fog(ctx);
}


static void i915InitDriverFunctions( struct dd_function_table *functions )
{
   intelInitDriverFunctions( functions );
   i915InitStateFunctions( functions );
   i915InitTextureFuncs( functions );
   i915InitFragProgFuncs( functions );
   functions->UpdateState = i915InvalidateState;
}



GLboolean i915CreateContext( const __GLcontextModes *mesaVis,
			    __DRIcontextPrivate *driContextPriv,
			    void *sharedContextPrivate)
{
   struct dd_function_table functions;
   i915ContextPtr i915 = (i915ContextPtr) CALLOC_STRUCT(i915_context);
   intelContextPtr intel = &i915->intel;
   intelScreenPrivate *intelScreen;
   GLcontext *ctx = &intel->ctx;

   if (!i915) return GL_FALSE;

   _mesa_printf( "\ntexmem branch (i915)\n\n");
   
   i915InitVtbl( i915 );

   i915InitDriverFunctions( &functions );

   if (!intelInitContext( intel, mesaVis, driContextPriv,
			  sharedContextPrivate, &functions )) {
      FREE(i915);
      return GL_FALSE;
   }

   ctx->Const.MaxTextureUnits = I915_TEX_UNITS;
   ctx->Const.MaxTextureImageUnits = I915_TEX_UNITS;
   ctx->Const.MaxTextureCoordUnits = I915_TEX_UNITS;

   intel->bm = bm_fake_intel_Attach( intel );

   bmInitPool(intel->bm,
              intel->intelScreen->tex.offset, /* low offset */
              intel->intelScreen->tex.map, /* low virtual */
              intel->intelScreen->tex.size,
	      BM_MEM_AGP);

   intelScreen = intel->intelScreen;

   /* These are still static, but create regions for them.  
    */
   intel->front_region = 
      intel_region_create_static(intel,
				 BM_MEM_AGP,
				 intelScreen->front.offset,
				 intelScreen->front.map,
				 intelScreen->cpp,
				 intelScreen->front.pitch,
				 intelScreen->height);


   intel->back_region = 
      intel_region_create_static(intel,
				 BM_MEM_AGP,
				 intelScreen->back.offset,
				 intelScreen->back.map,
				 intelScreen->cpp,
				 intelScreen->back.pitch,
				 intelScreen->height);

   /* Still assuming front.cpp == depth.cpp
    */
   intel->depth_region = 
      intel_region_create_static(intel,
				 BM_MEM_AGP,
				 intelScreen->depth.offset,
				 intelScreen->depth.map,
				 intelScreen->cpp,
				 intelScreen->depth.pitch,
				 intelScreen->height);

   intelInitBatchBuffer(intel);

   /* Advertise the full hardware capabilities.  The new memory
    * manager should cope much better with overload situations:
    */
   ctx->Const.MaxTextureLevels = 11;
   ctx->Const.Max3DTextureLevels = 8;
   ctx->Const.MaxCubeTextureLevels = 11;
   ctx->Const.MaxTextureRectSize = (1<<11);
   ctx->Const.MaxTextureUnits = I915_TEX_UNITS;

   /* GL_ARB_fragment_program limits - don't think Mesa actually
    * validates programs against these, and in any case one ARB
    * instruction can translate to more than one HW instruction, so
    * we'll still have to check and fallback each time.
    */   
   ctx->Const.FragmentProgram.MaxNativeTemps = I915_MAX_TEMPORARY;
   ctx->Const.FragmentProgram.MaxNativeAttribs = 11; /* 8 tex, 2 color, fog */
   ctx->Const.FragmentProgram.MaxNativeParameters = I915_MAX_CONSTANT;
   ctx->Const.FragmentProgram.MaxNativeAluInstructions = I915_MAX_ALU_INSN;
   ctx->Const.FragmentProgram.MaxNativeTexInstructions = I915_MAX_TEX_INSN;
   ctx->Const.FragmentProgram.MaxNativeInstructions = (I915_MAX_ALU_INSN + 
						       I915_MAX_TEX_INSN);
   ctx->Const.FragmentProgram.MaxNativeTexIndirections = I915_MAX_TEX_INDIRECT;
   ctx->Const.FragmentProgram.MaxNativeAddressRegs = 0; /* I don't think we have one */


   driInitExtensions( ctx, i915_extensions, GL_FALSE );


   _tnl_init_vertices( ctx, ctx->Const.MaxArrayLockSize + 12, 
		       36 * sizeof(GLfloat) );

   intel->verts = TNL_CONTEXT(ctx)->clipspace.vertex_buf;

   i915InitState( i915 );

   return GL_TRUE;
}

