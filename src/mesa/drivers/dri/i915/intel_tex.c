#include "texobj.h"
#include "intel_context.h"
#include "intel_mipmap_tree.h"
#include "intel_tex.h"


static GLboolean intelIsTextureResident(GLcontext *ctx,
                                      struct gl_texture_object *texObj)
{
#if 0
   struct intel_context *intel = intel_context(ctx);
   struct intel_texture_object *intelObj = intel_texture_object(texObj);
   
   return 
      intelObj->mt && 
      intelObj->mt->region && 
      intel_is_region_resident(intel, intelObj->mt->region);
#endif
   return 1;
}



static struct gl_texture_image *intelNewTextureImage( GLcontext *ctx )
{
   (void) ctx;
   return (struct gl_texture_image *)CALLOC_STRUCT(intel_texture_image);
}


static struct gl_texture_object *intelNewTextureObject( GLcontext *ctx, 
							GLuint name, 
							GLenum target )
{
   struct intel_texture_object *obj = CALLOC_STRUCT(intel_texture_object);

   _mesa_initialize_texture_object(&obj->base, name, target);

   return &obj->base;
}


static void intelFreeTextureImageData( GLcontext *ctx, 
				     struct gl_texture_image *texImage )
{
   struct intel_context *intel = intel_context(ctx);
   struct intel_texture_image *intelImage = intel_texture_image(texImage);

   if (intelImage->mt) {
      intel_miptree_release(intel, intelImage->mt);
      intelImage->mt = NULL;
   }
   
   if (texImage->Data) {
      free(texImage->Data);
      texImage->Data = NULL;
   }
}


void intelInitTextureFuncs(struct dd_function_table * functions)
{
   functions->ChooseTextureFormat = intelChooseTextureFormat;
   functions->TexImage1D = intelTexImage1D;
   functions->TexImage2D = intelTexImage2D;
   functions->TexSubImage1D = intelTexSubImage1D;
   functions->TexSubImage2D = intelTexSubImage2D;
   functions->CopyTexImage1D = intelCopyTexImage1D;
   functions->CopyTexImage2D = intelCopyTexImage2D;
   functions->CopyTexSubImage1D = intelCopyTexSubImage1D;
   functions->CopyTexSubImage2D = intelCopyTexSubImage2D;
   functions->NewTextureObject = intelNewTextureObject;
   functions->NewTextureImage = intelNewTextureImage;
   functions->DeleteTexture = _mesa_delete_texture_object;
   functions->FreeTexImageData = intelFreeTextureImageData;
   functions->UpdateTexturePalette = 0;
   functions->IsTextureResident = intelIsTextureResident;

   /* The system memcpy (at least on ubuntu 5.10) has problems copying
    * to agp (writecombined) memory from a source which isn't 64-byte
    * aligned - there is a 4x performance falloff.
    *
    * The x86 __memcpy is immune to this but is slightly slower
    * (10%-ish) than the system memcpy.
    *
    * The sse_memcpy seems to have a slight cliff at 64/32 bytes, but
    * isn't much faster than x86_memcpy for agp copies.
    * 
    * TODO: switch dynamically.
    */
   functions->TextureMemCpy = __memcpy;	
}
