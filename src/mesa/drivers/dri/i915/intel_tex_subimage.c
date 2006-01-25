

#include "mtypes.h"
#include "texobj.h"
#include "texstore.h"
#include "enums.h"

#include "intel_context.h"
#include "intel_tex.h"
#include "intel_mipmap_tree.h"


static void intelTexSubimage (GLcontext *ctx,
			      GLint dims,
			      GLenum target, GLint level,
			      GLint xoffset, GLint yoffset,
			      GLint width, GLint height,
			      GLenum format, GLenum type, const void *pixels,
			      const struct gl_pixelstore_attrib *packing,
			      struct gl_texture_object *texObj,
			      struct gl_texture_image *texImage)
{
   struct intel_context *intel = intel_context(ctx);
   struct intel_texture_image *intelImage = intel_texture_image(texImage);
   GLuint dstImageStride = 0;
   GLuint dstRowStride;

   _mesa_printf("%s target %s level %d offset %d,%d %dx%d\n", __FUNCTION__,
		_mesa_lookup_enum_by_nr(target),
		level,
		xoffset, yoffset,
		width, height);

   pixels = _mesa_validate_pbo_teximage(ctx, dims, width, height, 1, format, type,
                                        pixels, packing, "glTexSubImage2D");
   if (!pixels)
      return;

   LOCK_HARDWARE(intel);

   /* Map buffer if necessary.  Need to lock to prevent other contexts
    * from uploading the buffer under us.
    */
   if (intelImage->mt) 
      texImage->Data = intel_miptree_image_map(intel, 
					       intelImage->mt, 
					       intelImage->face, 
					       intelImage->level, 
					       &dstRowStride );
      

   if (!texImage->TexFormat->StoreImage(ctx, dims, texImage->_BaseFormat,
					texImage->TexFormat,
					texImage->Data,
					xoffset, yoffset, 0,
					dstRowStride, dstImageStride,
					width, height, 1,
					format, type, pixels, packing)) {
      _mesa_error(ctx, GL_OUT_OF_MEMORY, "glTexSubImage2D");
   }

#if 0
   /* GL_SGIS_generate_mipmap */
   if (level == texObj->BaseLevel && texObj->GenerateMipmap) {
      _mesa_generate_mipmap(ctx, target,
                            &ctx->Texture.Unit[ctx->Texture.CurrentUnit],
                            texObj);
   }
#endif

   _mesa_unmap_teximage_pbo(ctx, packing);

   if (intelImage->mt) {
      intel_miptree_image_unmap(intel, intelImage->mt);
      texImage->Data = NULL;
   }

   UNLOCK_HARDWARE(intel);
}






void intelTexSubImage2D(GLcontext *ctx,
			GLenum target,
			GLint level,
			GLint xoffset, GLint yoffset,
			GLsizei width, GLsizei height,
			GLenum format, GLenum type,
			const GLvoid *pixels,
			const struct gl_pixelstore_attrib *packing,
			struct gl_texture_object *texObj,
			struct gl_texture_image *texImage)
{

   intelTexSubimage(ctx, 2,
		    target, level, xoffset, yoffset, width,
		    height, format, type, pixels, packing, texObj,
		    texImage);

}


void intelTexSubImage1D(GLcontext *ctx,
			GLenum target,
			GLint level,
			GLint xoffset,
			GLsizei width,
			GLenum format, GLenum type,
			const GLvoid *pixels,
			const struct gl_pixelstore_attrib *packing,
			struct gl_texture_object *texObj,
			struct gl_texture_image *texImage)
{
   intelTexSubimage(ctx, 1,
		    target, level, xoffset, 0, width,
		    1, format, type, pixels, packing, texObj,
		    texImage);

}
