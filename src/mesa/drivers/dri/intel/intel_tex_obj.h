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

#ifndef _INTEL_TEX_OBJ_H
#define _INTEL_TEX_OBJ_H

#include "swrast/s_context.h"
#include "intel_regions.h"


struct intel_texture_object
{
   struct gl_texture_object base;

   /* This is a mirror of base._MaxLevel, updated at validate time,
    * except that we don't bother with the non-base levels for
    * non-mipmapped textures.
    */
   unsigned int _MaxLevel;

   /* Offset for firstLevel image:
    */
   GLuint textureOffset;

   /* On validation any active images held in main memory or in other
    * regions will be copied to this region and the old storage freed.
    */
   struct intel_mipmap_tree *mt;

   /**
    * Set when mipmap trees in the texture images of this texture object
    * might not all be the mipmap tree above.
    */
   bool needs_validate;
};


/**
 * intel_texture_image is a subclass of swrast_texture_image because we
 * sometimes fall back to using the swrast module for software rendering.
 */
struct intel_texture_image
{
   struct swrast_texture_image base;

   /* If intelImage->mt != NULL, image data is stored here.
    * Else if intelImage->base.Buffer != NULL, image is stored there.
    * Else there is no image data.
    */
   struct intel_mipmap_tree *mt;

   /* If ext_format != NULL, the image represents an external buffer. Depending
    * on the format the details for the individual components of planar formats
    * (such as NV12) are set in ext_strides and ext_offsets.
    */
   const struct intel_image_format *ext_format;
   uint32_t ext_strides[3];
   uint32_t ext_offsets[3];
};

/** Use specifically the format of the first image as this is set directly based
 *  on the format of "__DRIimage" representing the external surface:
 *  (see intel_image_target_texture_2d() and intel_set_texture_image_region()).
 */
static INLINE unsigned
resolve_hw_surf_num(const struct gl_texture_unit *units, const GLbitfield *used,
                    unsigned unit)
{
   const struct intel_texture_image *intel_img;
   const struct gl_texture_object *tex_obj;

   /** Only external textures may require more than one surface */
   if (!(used[unit] & (1 << TEXTURE_EXTERNAL_INDEX)))
      return 1;

   tex_obj = units[unit].CurrentTex[TEXTURE_EXTERNAL_INDEX];
   assert(tex_obj->Target == GL_TEXTURE_EXTERNAL_OES);

   intel_img = (const struct intel_texture_image *)
      tex_obj->Image[0][tex_obj->BaseLevel];

   /** Assume one surface as no images are bound yet */
   if (!intel_img)
      return 1;

   return intel_img->ext_format ? intel_img->ext_format->nplanes : 1;
}

static INLINE struct intel_texture_object *
intel_texture_object(struct gl_texture_object *obj)
{
   return (struct intel_texture_object *) obj;
}

static INLINE struct intel_texture_image *
intel_texture_image(struct gl_texture_image *img)
{
   return (struct intel_texture_image *) img;
}

#endif /* _INTEL_TEX_OBJ_H */
