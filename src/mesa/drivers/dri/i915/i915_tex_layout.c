/**************************************************************************
 * 
 * Copyright 2006 Tungsten Graphics, Inc., Cedar Park, Texas.
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

/* Code to layout images in a mipmap tree for i915 and i945
 * respectively.
 */

#include "intel_mipmap_tree.h"
#include "macros.h"

static GLint initial_offsets[6][2] = { {0,0},
				       {0,2},
				       {1,0},
				       {1,2},
				       {1,1},
				       {1,3} };


static GLint step_offsets[6][2] = { {0,2},
				    {0,2},
				    {-1,2},
				    {-1,2},
				    {-1,1},
				    {-1,1} };

static GLuint minify( GLuint d )
{
   return MAX2(1, d>>1);
}

GLboolean i915_miptree_layout( struct intel_mipmap_tree *mt )
{
   GLint i;

   switch (mt->target) {
   case GL_TEXTURE_CUBE_MAP: {
      const GLuint dim = mt->width0;
      GLuint face;

      /* double pitch for cube layouts */
      mt->pitch = ((dim * mt->cpp * 2 + 3) & ~3) / mt->cpp;
      mt->total_height = dim * 4;
      
      for ( face = 0 ; face < 6 ; face++) {
	 GLuint x = initial_offsets[face][0] * dim;
	 GLuint y = initial_offsets[face][1] * dim;
	 GLuint d = dim;
	 
	 for (i = mt->first_level; i <= mt->last_level; i++) {
	    mt->offset[face][i].x = x; 
	    mt->offset[face][i].y = y; 
	    mt->offset[face][i].width = d;
	    mt->offset[face][i].height = d;
	    mt->offset[face][i].depth = 1;
	 
	    d >>= 1;
	    assert(d > 0);

	    x += step_offsets[face][0] * d;
	    y += step_offsets[face][1] * d;
	 }
      }
      break;
   }
   case GL_TEXTURE_3D: {
      GLuint width  = mt->width0;
      GLuint height = mt->height0;
      GLuint depth  = mt->depth0;

      /* Calculate the size of a single slice.  Hardware demands a
       * minimum of 8 mipmaps, some of which might ultimately not be
       * used:
       */
      mt->pitch = ((mt->width0 * mt->cpp + 3) & ~3) / mt->cpp;
      mt->total_height = 0;

      /* XXX: fixme! hardware expects/requires 9 levels at minimum.
       */
      for ( i = mt->first_level ; i <= mt->last_level ; i++ ) {
	 mt->offset[0][i].x = 0;
	 mt->offset[0][i].y = mt->total_height;
	 mt->offset[0][i].width = width;
	 mt->offset[0][i].height = height;
	 mt->offset[0][i].depth = depth;

	 mt->total_height += MAX2(2, height);

	 width  = minify(width);
	 height = minify(height);
	 depth  = minify(depth);
      }


      /* Multiply slice size by texture depth for total size.  It's
       * remarkable how wasteful of memory the i915 texture layouts
       * are.  They are largely fixed in the i945.
       */
      mt->depth_pitch = mt->total_height * mt->pitch;
      mt->total_height *= mt->depth0;
      break;
   }

   default: {
      GLuint width  = mt->width0;
      GLuint height = mt->height0;

      mt->pitch = ((mt->width0 * mt->cpp + 3) & ~3) / mt->cpp;
      mt->total_height = 0;

      for ( i = mt->first_level ; i <= mt->last_level ; i++ ) {
	 mt->offset[0][i].x = 0;
	 mt->offset[0][i].y = mt->total_height;
	 mt->offset[0][i].height = height;
	 mt->offset[0][i].width = width;
	 mt->offset[0][i].depth = 1;

	 
	 if (mt->compressed)
	    mt->total_height += MAX2(1, height/4);
	 else
	    mt->total_height += MAX2(2, height);

	 width  = minify(width);
	 height = minify(height);
      }
      break;
   }
   }

   return GL_TRUE;
}


GLboolean i945_miptree_layout( struct intel_mipmap_tree *mt )
{
   GLint i;

   switch (mt->target) {
   case GL_TEXTURE_CUBE_MAP: {
      const GLuint dim = mt->width0;
      GLuint face;

      /* Depending on the size of the largest images, pitch can be
       * determined either by the old-style packing of cubemap faces,
       * or the final row of 4x4, 2x2 and 1x1 faces below this. 
       */
      if (dim > 32) 
	 mt->pitch = ((dim * mt->cpp * 2 + 3) & ~3) / mt->cpp;
      else 
	 mt->pitch = 14 * 8; 

      mt->total_height = dim * 4 + 4;

      
      for ( face = 0 ; face < 6 ; face++) {
	 GLuint x = initial_offsets[face][0] * dim;
	 GLuint y = initial_offsets[face][1] * dim;
	 GLuint d = dim;
	 
	 if (dim == 4 && face >= 4) {
	    y = mt->total_height - 4;
	    x = (face - 4) * 8;
	 }
	 else if (dim < 4) {
	    y = mt->total_height - 4;
	    x = face * 8;
	 }

	 for ( i = mt->first_level ; i <= mt->last_level ; i++ ) {
	    mt->offset[face][i].x = x; 
	    mt->offset[face][i].y = y; 
	    mt->offset[face][i].width = d;
	    mt->offset[face][i].height = d;
	    mt->offset[face][i].depth = 1;

	    d >>= 1;
	    assert(d > 0);
	    
	    switch (d) {
	    case 4:
	       switch (face) {
	       case FACE_POS_X:
	       case FACE_NEG_X:
		  x += step_offsets[face][0] * d;
		  y += step_offsets[face][1] * d;
		  break;
	       case FACE_POS_Y:
	       case FACE_NEG_Y:
		  y += 12;
		  x -= 8;
		  break;
	       case FACE_POS_Z:
	       case FACE_NEG_Z:
		  y = mt->total_height - 4;
		  x = (face - 4) * 8;
		  break;
	       }

	    case 2:
	       y = mt->total_height - 4;
	       x = 16 + face * 8;
	       break;

	    case 1:
	       x += 48;
	       break;
	       
	    default:
	       x += step_offsets[face][0] * d;
	       y += step_offsets[face][1] * d;
	       break;
	    }
	 }
      }
      break;
   }
   case GL_TEXTURE_3D: {
      GLuint width  = mt->width0;
      GLuint height = mt->height0;
      GLuint depth = mt->depth0;
      GLuint depth_pack_pitch;
      GLuint depth_packing = 0;

      mt->pitch = ((mt->width0 * mt->cpp + 3) & ~3) / mt->cpp;
      mt->total_height = 0;

      depth_pack_pitch = mt->pitch * mt->cpp;

      for ( i = mt->first_level ; i <= mt->last_level ; i++ ) {

	 mt->offset[0][i].x = 0;
	 mt->offset[0][i].y = mt->total_height;
	 mt->offset[0][i].width = width;
	 mt->offset[0][i].height = height;
	 mt->offset[0][i].depth = depth;

	 mt->total_height += MAX2(2, height) * MAX2((depth >> depth_packing), 1);

	 /* When alignment dominates, can't increase depth packing?
	  * Or does pitch grow???  What are the alignment constraints,
	  * anyway?
	  */
	 if (depth_pack_pitch > 4) {
	    depth_packing++;
	    depth_pack_pitch <<= 2; /* KW: is this right?? */
	 }

	 width  = minify(width);
	 height = minify(height);
	 depth  = minify(depth);

	 /* XXX: Not sure how 3d textures work on i945 - where did
	  * t->depth_pitch get set in the old code.  Did it ever work?
	  * Fix up later.
	  */
      }
      break;
   }

   default: {
      GLuint x = 0;
      GLuint y = 0;
      GLuint width = mt->width0;
      GLuint height = mt->height0;

      mt->pitch = ((mt->width0 * mt->cpp + 3) & ~3) / mt->cpp;
      mt->total_height = 0;

      for ( i = mt->first_level ; i <= mt->last_level ; i++ ) {
	 mt->offset[0][i].x = x;
	 mt->offset[0][i].y = y;
	 mt->offset[0][i].height = height;
	 mt->offset[0][i].width = width;
	 mt->offset[0][i].depth = 1;

	 
	 /* LPT change: step right after second mipmap.
	  */
	 if (i == 1) 
	    x += mt->pitch / 2;
	 else {
	    GLuint img_height;
	 
	    if (mt->compressed)
	       img_height = MAX2(1, height/4);
	    else
	       img_height = MAX2(2, height);

	    y += img_height;
	 }

	 /* Because the images are packed better, the final offset
	  * might not be the maximal one:
	  */
	 mt->total_height = MAX2(mt->total_height, y);

	 width  = minify(width);
	 height = minify(height);
      }
      break;
   }
   }
   return GL_TRUE;
}

