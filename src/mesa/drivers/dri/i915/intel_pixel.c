#include "swrast/swrast.h"
#include "intel_context.h"
#include "intel_pixel.h"



#if 0
struct intel_client_region *intel_pack_region( struct intel_context *intel,
					       const struct gl_pixelstore_attrib *pack,
					       GLenum format,
					       GLenum type,
					       GLvoid *pixels )
{
}


struct intel_client_region *intel_unpack_region( struct intel_context *intel,
						 const struct gl_pixelstore_attrib *pack,
						 GLenum format,
						 GLenum type,
						 GLvoid *pixels )
{
   GLint pitch = unpack->RowLength ? unpack->RowLength : width;
   /* XXX: Need to adjust pixels pointer for unpack->skip pixels/rows
    * offsets.
    */

}

void release_client_region( struct intel_context *intel,
			    struct intel_region *region )
{
}
#endif



GLboolean intel_check_color_per_fragment_ops( const GLcontext *ctx )
{
   return !(ctx->Color.AlphaEnabled || 
	    ctx->Depth.Test ||
	    ctx->Fog.Enabled ||
	    ctx->Scissor.Enabled ||
	    ctx->Stencil.Enabled ||
	    !ctx->Color.ColorMask[0] ||
	    !ctx->Color.ColorMask[1] ||
	    !ctx->Color.ColorMask[2] ||
	    !ctx->Color.ColorMask[3] ||
	    ctx->Color.ColorLogicOpEnabled ||
	    ctx->Texture._EnabledUnits);
}

#if 0
/* The intel_region struct doesn't really do enough to capture the
 * format of the pixels in the region.  For now this code assumes that
 * the region is a display surface and hence is either ARGB8888 or
 * RGB565.
 */
GLboolean intel_check_blit_format( struct intel_region *region,
				   struct intel_client_region *client_region )
{
   if (region->cpp == 4 
       client_region->cpp == 4 && 
       client_region->type == GL_UNSIGNED_INT_8_8_8_8_REV &&        
       client_region->format == GL_BGRA ) {
      return GL_TRUE;
   }
   
   if (region->cpp == 2 && 
       client_region->cpp == 2 &&
       client_region->type == GL_UNSIGNED_INT_5_6_5_REV && 
       client_region->format == GL_BGR ) {
      return GL_TRUE;
   }
   
   fprintf(stderr, "%s: request doesn't match pixel format\n", __FUNCTION__);
   return GL_FALSE;
}
#endif


GLboolean intel_clip_to_framebuffer( GLcontext *ctx,
				     const GLframebuffer *buffer,
				     GLint *x, GLint *y,
				     GLsizei *width, GLsizei *height )
{
   /* left clipping */
   if (*x < buffer->_Xmin) {
      *width -= (buffer->_Xmin - *x);
      *x = buffer->_Xmin;
   }

   /* right clipping */
   if (*x + *width > buffer->_Xmax)
      *width -= (*x + *width - buffer->_Xmax - 1);

   if (*width <= 0)
      return GL_FALSE;

   /* bottom clipping */
   if (*y < buffer->_Ymin) {
      *height -= (buffer->_Ymin - *y);
      *y = buffer->_Ymin;
   }

   /* top clipping */
   if (*y + *height > buffer->_Ymax)
      *height -= (*y + *height - buffer->_Ymax - 1);

   if (*height <= 0)
      return GL_FALSE;

   return GL_TRUE;
}




void intelInitPixelFuncs( struct dd_function_table *functions )
{
   /* Pixel path fallbacks.
    */
   functions->Accum = _swrast_Accum;
   functions->Bitmap = _swrast_Bitmap;

   if (getenv("INTEL_NO_BLITS") == 0) {
      functions->CopyPixels = intelCopyPixels;
      functions->ReadPixels = intelReadPixels;  
      functions->DrawPixels = intelDrawPixels; 
   }
   else {
      functions->CopyPixels = _swrast_CopyPixels;
      functions->ReadPixels = _swrast_ReadPixels;
      functions->DrawPixels = _swrast_DrawPixels;
   }
}

