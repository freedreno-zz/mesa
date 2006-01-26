#include "mtypes.h"
#include "macros.h"

#include "intel_context.h"
#include "intel_mipmap_tree.h"
#include "intel_tex.h"
#include "bufmgr.h"

/**
 * Compute which mipmap levels that really need to be sent to the hardware.
 * This depends on the base image size, GL_TEXTURE_MIN_LOD,
 * GL_TEXTURE_MAX_LOD, GL_TEXTURE_BASE_LEVEL, and GL_TEXTURE_MAX_LEVEL.
 */
static void intel_calculate_first_last_level( struct intel_texture_object *intelObj )
{
   struct gl_texture_object *tObj = &intelObj->base;
   const struct gl_texture_image * const baseImage =
       tObj->Image[0][tObj->BaseLevel];

   /* These must be signed values.  MinLod and MaxLod can be negative numbers,
    * and having firstLevel and lastLevel as signed prevents the need for
    * extra sign checks.
    */
   int   firstLevel;
   int   lastLevel;

   /* Yes, this looks overly complicated, but it's all needed.
    */
   switch (tObj->Target) {
   case GL_TEXTURE_1D:
   case GL_TEXTURE_2D:
   case GL_TEXTURE_3D:
   case GL_TEXTURE_CUBE_MAP:
      if (tObj->MinFilter == GL_NEAREST || tObj->MinFilter == GL_LINEAR) {
         /* GL_NEAREST and GL_LINEAR only care about GL_TEXTURE_BASE_LEVEL.
          */
         firstLevel = lastLevel = tObj->BaseLevel;
      }
      else {
	 firstLevel = tObj->BaseLevel + (GLint)(tObj->MinLod + 0.5);
	 firstLevel = MAX2(firstLevel, tObj->BaseLevel);
	 lastLevel = tObj->BaseLevel + (GLint)(tObj->MaxLod + 0.5);
	 lastLevel = MAX2(lastLevel, tObj->BaseLevel);
	 lastLevel = MIN2(lastLevel, tObj->BaseLevel + baseImage->MaxLog2);
	 lastLevel = MIN2(lastLevel, tObj->MaxLevel);
	 lastLevel = MAX2(firstLevel, lastLevel); /* need at least one level */
      }
      break;
   case GL_TEXTURE_RECTANGLE_NV:
   case GL_TEXTURE_4D_SGIS:
      firstLevel = lastLevel = 0;
      break;
   default:
      return;
   }

   /* save these values */
   intelObj->firstLevel = firstLevel;
   intelObj->lastLevel = lastLevel;
}

static void copy_image_data_to_tree( struct intel_context *intel,
				     struct intel_mipmap_tree *mt,
				     struct intel_texture_image *intelImage )
{
   if (intelImage->mt) {
      /* Copy potentially with the blitter:
       */
      intel_miptree_image_copy(intel,
			       mt,
			       intelImage->face,
			       intelImage->level,
			       intelImage->mt);

      intel_miptree_release(intel, intelImage->mt);
   }
   else {
      assert(intelImage->base.Data != NULL);

      /* More straightforward upload.  
       */
      intel_miptree_image_data(intel,
			       mt,
			       intelImage->face,
			       intelImage->level,
			       intelImage->base.Data,
			       intelImage->base.RowStride);

      free(intelImage->base.Data);
      intelImage->base.Data = NULL;
   }

   intelImage->mt = intel_miptree_reference(mt);
}


/*  
 */
static GLuint intel_finalize_mipmap_tree( struct intel_context *intel, GLuint unit )
{
   struct gl_texture_object *tObj = intel->ctx.Texture.Unit[unit]._Current;
   struct intel_texture_object *intelObj = intel_texture_object(tObj);

   GLuint face, i;
   GLuint nr_faces = 0;
   struct intel_texture_image *firstImage;

   /* We know/require this is true by now: 
    */
   assert(intelObj->base.Complete);

   /* What levels must the tree include at a minimum?
    */
   intel_calculate_first_last_level( intelObj );
   firstImage = intel_texture_image(intelObj->base.Image[0][intelObj->firstLevel]);

   /* Fallback case:
    */
   if (firstImage->base.Border) {
      if (intelObj->mt) {
	 intel_miptree_release(intel, intelObj->mt);
	 intelObj->mt = NULL;
      }
      return 0;
   }


   /* If both firstImage and intelObj have a tree which can contain
    * all active images, favour firstImage.
    */
   if (firstImage->mt &&
       firstImage->mt != intelObj->mt &&
       firstImage->mt->first_level <= intelObj->firstLevel &&
       firstImage->mt->last_level >= intelObj->lastLevel) {

      if (intelObj->mt) 
	 intel_miptree_release(intel, intelObj->mt);

      intelObj->mt = intel_miptree_reference(firstImage->mt);
   }

   /* Check tree can hold all active levels.  Check tree matches
    * target, imageFormat, etc.
    * 
    * XXX: For some layouts (eg i945?), the test might have to be
    * first_level == firstLevel, as the tree isn't valid except at the
    * original start level.  Hope to get around this by
    * programming minLod, maxLod, baseLevel into the hardware and
    * leaving the tree alone.
    */
   if (intelObj->mt &&
       ((intelObj->mt->first_level > intelObj->firstLevel) ||
	(intelObj->mt->last_level < intelObj->lastLevel) ||
	(intelObj->mt->internal_format != firstImage->base.InternalFormat))) {
      intel_miptree_release(intel, intelObj->mt);
      intelObj->mt = NULL;
   }
      

   /* May need to create a new tree:
    */
   if (!intelObj->mt) {
      intelObj->mt = intel_miptree_create(intel,
					  intelObj->base.Target,
					  firstImage->base.InternalFormat,
					  intelObj->firstLevel,
					  intelObj->lastLevel,
					  firstImage->base.Width,
					  firstImage->base.Height,
					  firstImage->base.Depth,
					  firstImage->base.TexFormat->TexelBytes,
					  firstImage->base.IsCompressed);
   }

   /* Pull in any images not in the object's tree:
    */
   nr_faces = (intelObj->base.Target == GL_TEXTURE_CUBE_MAP) ? 6 : 1;
   for (face = 0; face < nr_faces; face++) {
      for (i = intelObj->firstLevel; i < intelObj->lastLevel; i++) {
	 struct intel_texture_image *intelImage = 
	    intel_texture_image(intelObj->base.Image[face][i]);
	 
	 /* Need to import images in main memory or held in other trees.
	  */
	 if (intelObj->mt != intelImage->mt) {
	    copy_image_data_to_tree(intel,
				    intelObj->mt,
				    intelImage);
	 }
      }
   }

   return GL_TRUE;
}

void intel_add_texoffset_fixup( struct intel_context *intel,
				GLuint unit,
				GLuint *ptr )
{
   struct gl_texture_object *tObj = intel->ctx.Texture.Unit[unit]._Current;
   struct intel_texture_object *intelObj = intel_texture_object(tObj);

#if 0
   struct intel_reloc *f = &intel->fixup[intel->nr_fixups++];
   assert(intel->nr_fixups <= INTEL_MAX_FIXUP);
   f->dest = ptr;
   f->value = &intelObj->textureOffset;
   f->delta = (intel->intelScreen->tex.offset + 
	       intel_miptree_image_offset(intelObj->mt, 0, intelObj->firstLevel));
#else
   *ptr = (intelObj->textureOffset + 	   
	   intel_miptree_image_offset(intelObj->mt, 0, intelObj->firstLevel));
#endif
}

/* Fix up the command buffer:
 */
void intel_apply_fixups( struct intel_context *intel )
{
   GLuint i;

   for (i = 0; i < intel->nr_fixups; i++) {
      struct intel_reloc *f = &intel->fixup[i];
      *f->dest = *f->value + f->delta;
   }

   intel->nr_fixups = 0;
}



/* One upshot of the new manager is that it should be possible to tell
 * ahead of time whether a certain set of buffers will cause a
 * fallback.  
 *
 * Unless we do this we either have to a) hold the DRI lock
 * while emitting all vertices and fire after each vertex buffer, or
 * b) build a fallback path that operates on i915 command streams
 * rather than the state in the GLcontext.
 */
GLboolean intel_prevalidate_buffers( struct intel_context *intel )
{
   return GL_TRUE;		/* never fallback */
}


GLboolean intel_validate_buffers( struct intel_context *intel )
{
   GLcontext *ctx = &intel->ctx;
   GLboolean ok = GL_TRUE;
   GLuint i;

   _mesa_printf("%s\n", __FUNCTION__);

   assert(intel->locked);
   assert (!intel->buffer_list);

   intel->buffer_list = bmNewBufferList();
      
   /* Add the color and depth buffers:
    */
      

   /* Add each enabled texture:
    */
   for (i = 0 ; i < ctx->Const.MaxTextureUnits && ok ; i++) {
      if (ctx->Texture.Unit[i]._ReallyEnabled) {
	 struct gl_texture_object *tObj = intel->ctx.Texture.Unit[i]._Current;
	 struct intel_texture_object *intelObj = intel_texture_object(tObj);

	 ok = intel_finalize_mipmap_tree( intel, i );
	 if (ok) {
	    bmAddBuffer(intel->buffer_list,
			intelObj->mt->region->buffer,
			BM_READ,
			NULL,
			&intelObj->textureOffset);
	 }
      }
   }

   ok = bmValidateBufferList(intel->bm, intel->buffer_list, BM_MEM_AGP);
   assert(ok);
   return ok;
}

void intel_fence_buffers( struct intel_context *intel )
{
   assert(intel->locked);
   assert(intel->buffer_list);
   bmFenceBufferList(intel->bm, intel->buffer_list);
   bmFreeBufferList(intel->buffer_list);
   intel->buffer_list = NULL;
}

