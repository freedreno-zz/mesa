
/*
 * Mesa 3-D graphics library
 * Version:  5.1
 *
 * Copyright (C) 1999-2003  Brian Paul   All Rights Reserved.
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



#include "glheader.h"
#include "colormac.h"
#include "light.h"
#include "macros.h"
#include "imports.h"
#include "simple_list.h"
#include "mtypes.h"

#include "math/m_translate.h"

#include "t_context.h"
#include "t_pipeline.h"

#define LIGHT_TWOSIDE       0x1
#define LIGHT_MATERIAL      0x2
#define MAX_LIGHT_FUNC      0x4

typedef void (*light_func)( GLcontext *ctx,
			    struct vertex_buffer *VB,
			    struct tnl_pipeline_stage *stage,
			    GLvector4f *input );

struct light_stage_data {
   GLvector4f LitColor[2];
   GLvector4f LitSecondary[2];
   GLvector4f LitIndex[2];
   light_func *light_func_tab;
};


#define LIGHT_STAGE_DATA(stage) ((struct light_stage_data *)(stage->privatePtr))




static void update_materials( GLcontext *ctx, GLuint j )
{
/*
   _mesa_copy_materials( &ctx->Light.Material, src, bitmask );
   _mesa_update_material( ctx, bitmask );
*/
}

/* Tables for all the shading functions.
 */
static light_func _tnl_light_tab[MAX_LIGHT_FUNC];
static light_func _tnl_light_fast_tab[MAX_LIGHT_FUNC];
static light_func _tnl_light_fast_single_tab[MAX_LIGHT_FUNC];
static light_func _tnl_light_spec_tab[MAX_LIGHT_FUNC];
static light_func _tnl_light_ci_tab[MAX_LIGHT_FUNC];

#define TAG(x)           x
#define IDX              (0)
#include "t_vb_lighttmp.h"

#define TAG(x)           x##_twoside
#define IDX              (LIGHT_TWOSIDE)
#include "t_vb_lighttmp.h"

#define TAG(x)           x##_material
#define IDX              (LIGHT_MATERIAL)
#include "t_vb_lighttmp.h"

#define TAG(x)           x##_twoside_material
#define IDX              (LIGHT_TWOSIDE|LIGHT_MATERIAL)
#include "t_vb_lighttmp.h"


static void init_lighting( void )
{
   static int done;

   if (!done) {
      init_light_tab();
      init_light_tab_twoside();
      init_light_tab_material();
      init_light_tab_twoside_material();
      done = 1;
   }
}


static GLboolean run_lighting( GLcontext *ctx, struct tnl_pipeline_stage *stage )
{
   struct light_stage_data *store = LIGHT_STAGE_DATA(stage);
   TNLcontext *tnl = TNL_CONTEXT(ctx);
   struct vertex_buffer *VB = &tnl->vb;
   GLvector4f *input = ctx->_NeedEyeCoords ? VB->EyePtr : VB->ObjPtr;

/*     _tnl_print_vert_flags( __FUNCTION__, stage->changed_inputs ); */

   /* Make sure we can talk about position x,y and z:
    *
    * FIXME!
    */
#if 0
   if (stage->changed_inputs & _TNL_BIT_POS) {
      if (input->size <= 2 && input == VB->ObjPtr) {
	 input = _mesa_vector4f_clean_elem(VB->ObjPtr, some_storage,
					   VB->Count, 2);
      }
   }
#endif

   
   /* The individual functions know about replaying side-effects
    * vs. full re-execution. 
    */
   store->light_func_tab[0]( ctx, VB, stage, input );

   return GL_TRUE;
}


/* Called in place of do_lighting when the light table may have changed.
 */
static GLboolean run_validate_lighting( GLcontext *ctx,
					struct tnl_pipeline_stage *stage )
{
   GLuint ind = 0;
   light_func *tab;

   if (ctx->Visual.rgbMode) {
      if (ctx->Light._NeedVertices) {
	 if (ctx->Light.Model.ColorControl == GL_SEPARATE_SPECULAR_COLOR)
	    tab = _tnl_light_spec_tab;
	 else
	    tab = _tnl_light_tab;
      }
      else {
	 if (ctx->Light.EnabledList.next == ctx->Light.EnabledList.prev)
	    tab = _tnl_light_fast_single_tab;
	 else
	    tab = _tnl_light_fast_tab;
      }
   }
   else
      tab = _tnl_light_ci_tab;

   /* Need to check color stride != 0.
    * Also need to check for materials in the VB:
    */
   if (ctx->Light.ColorMaterialEnabled)
      ind |= LIGHT_MATERIAL;

   if (ctx->Light.Model.TwoSide)
      ind |= LIGHT_TWOSIDE;

   LIGHT_STAGE_DATA(stage)->light_func_tab = &tab[ind];

   /* This and the above should only be done on _NEW_LIGHT:
    */
   TNL_CONTEXT(ctx)->Driver.NotifyMaterialChange( ctx );

   /* Now run the stage...
    */
   stage->run = run_lighting;
   return stage->run( ctx, stage );
}



/* Called the first time stage->run is called.  In effect, don't
 * allocate data until the first time the stage is run.
 */
static GLboolean run_init_lighting( GLcontext *ctx,
				    struct tnl_pipeline_stage *stage )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx);
   struct light_stage_data *store;
   GLuint size = tnl->vb.Size;

   stage->privatePtr = MALLOC(sizeof(*store));
   store = LIGHT_STAGE_DATA(stage);
   if (!store)
      return GL_FALSE;

   /* Do onetime init.
    */
   init_lighting();

   _mesa_vector4f_alloc( &store->LitColor[0], 0, size, 32 );
   _mesa_vector4f_alloc( &store->LitColor[1], 0, size, 32 );
   _mesa_vector4f_alloc( &store->LitSecondary[0], 0, size, 32 );
   _mesa_vector4f_alloc( &store->LitSecondary[1], 0, size, 32 );
   _mesa_vector4f_alloc( &store->LitIndex[0], 0, size, 32 );
   _mesa_vector4f_alloc( &store->LitIndex[1], 0, size, 32 );

   /* Now validate the stage derived data...
    */
   stage->run = run_validate_lighting;
   return stage->run( ctx, stage );
}



/*
 * Check if lighting is enabled.  If so, configure the pipeline stage's
 * type, inputs, and outputs.
 */
static void check_lighting( GLcontext *ctx, struct tnl_pipeline_stage *stage )
{
   stage->active = ctx->Light.Enabled && !ctx->VertexProgram.Enabled;
   if (stage->active) {
      if (stage->privatePtr)
	 stage->run = run_validate_lighting;
      stage->inputs = _TNL_BIT_NORMAL|_TNL_BITS_MAT_ANY;
      if (ctx->Light._NeedVertices)
	 stage->inputs |= _TNL_BIT_POS; 
      if (ctx->Light.ColorMaterialEnabled)
	 stage->inputs |= _TNL_BIT_COLOR0;

      stage->outputs = _TNL_BIT_COLOR0;
      if (ctx->Light.Model.ColorControl == GL_SEPARATE_SPECULAR_COLOR)
	 stage->outputs |= _TNL_BIT_COLOR1;
   }
}


static void dtr( struct tnl_pipeline_stage *stage )
{
   struct light_stage_data *store = LIGHT_STAGE_DATA(stage);

   if (store) {
      _mesa_vector4f_free( &store->LitColor[0] );
      _mesa_vector4f_free( &store->LitColor[1] );
      _mesa_vector4f_free( &store->LitSecondary[0] );
      _mesa_vector4f_free( &store->LitSecondary[1] );
      _mesa_vector4f_free( &store->LitIndex[0] );
      _mesa_vector4f_free( &store->LitIndex[1] );
      FREE( store );
      stage->privatePtr = 0;
   }
}

const struct tnl_pipeline_stage _tnl_lighting_stage =
{
   "lighting",			/* name */
   _NEW_LIGHT,			/* recheck */
   _NEW_LIGHT|_NEW_MODELVIEW,	/* recalc -- modelview dependency
				 * otherwise not captured by inputs
				 * (which may be _TNL_BIT_POS) */
   GL_FALSE,			/* active? */
   0,				/* inputs */
   0,				/* outputs */
   0,				/* changed_inputs */
   NULL,			/* private_data */
   dtr,				/* destroy */
   check_lighting,		/* check */
   run_init_lighting		/* run -- initially set to ctr */
};
