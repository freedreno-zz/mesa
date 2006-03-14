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
#include "macros.h"
#include "mtypes.h"
#include "colormac.h"

#include "intel_screen.h"
#include "intel_span.h"
#include "intel_regions.h"
#include "intel_ioctl.h"
#include "intel_tex.h"

#include "swrast/swrast.h"

#undef DBG
#define DBG 0

#define LOCAL_VARS						\
   struct intel_context *intel = intel_context(ctx);		\
   driRenderbuffer *drb = (driRenderbuffer *) rb;		\
   const __DRIdrawablePrivate *dPriv = drb->dPriv;		\
   const GLuint bottom = dPriv->h - 1;				\
   GLubyte *buf = (GLubyte *) drb->flippedData			\
      + (dPriv->y * drb->flippedPitch + dPriv->x) * drb->cpp;	\
   GLuint p;							\
   assert(dPriv->x == intel->drawX); \
   assert(dPriv->y == intel->drawY); \
   (void) p;

#define Y_FLIP(_y) (bottom - _y)

#define HW_LOCK()

#define HW_UNLOCK()

/* 16 bit, RGB565 color spanline and pixel functions
 */
#define SPANTMP_PIXEL_FMT GL_RGB
#define SPANTMP_PIXEL_TYPE GL_UNSIGNED_SHORT_5_6_5

#define TAG(x)    intel##x##_RGB565
#define TAG2(x,y) intel##x##_RGB565##y
#define GET_PTR(X,Y) (buf + ((Y) * drb->flippedPitch + (X)) * 2)
#include "spantmp2.h"

/* 32 bit, ARGB8888 color spanline and pixel functions
 */
#define SPANTMP_PIXEL_FMT GL_BGRA
#define SPANTMP_PIXEL_TYPE GL_UNSIGNED_INT_8_8_8_8_REV

#define TAG(x)    intel##x##_ARGB8888
#define TAG2(x,y) intel##x##_ARGB8888##y
#define GET_PTR(X,Y) (buf + ((Y) * drb->flippedPitch + (X)) * 4)
#include "spantmp2.h"


#define LOCAL_DEPTH_VARS					\
   struct intel_context *intel = intel_context(ctx);		\
   __DRIdrawablePrivate *dPriv = intel->driDrawable;		\
   driRenderbuffer *drb = (driRenderbuffer *) rb;		\
   const GLuint pitch = drb->pitch * drb->cpp;			\
   const GLuint bottom = dPriv->h - 1;				\
   char *buf = (char *) drb->Base.Data +			\
			dPriv->x * drb->cpp +			\
			dPriv->y * pitch

#define LOCAL_STENCIL_VARS LOCAL_DEPTH_VARS 

/* 16 bit depthbuffer functions.
 */
#define WRITE_DEPTH( _x, _y, d ) \
   *(GLushort *)(buf + (_x)*2 + (_y)*pitch)  = d;

#define READ_DEPTH( d, _x, _y )	\
   d = *(GLushort *)(buf + (_x)*2 + (_y)*pitch);	 


#define TAG(x) intel##x##_z16
#include "depthtmp.h"


/* 24/8 bit interleaved depth/stencil functions
 */
#define WRITE_DEPTH( _x, _y, d ) {			\
   GLuint tmp = *(GLuint *)(buf + (_x)*4 + (_y)*pitch);	\
   tmp &= 0xff000000;					\
   tmp |= (d) & 0xffffff;				\
   *(GLuint *)(buf + (_x)*4 + (_y)*pitch) = tmp;		\
}

#define READ_DEPTH( d, _x, _y )		\
   d = *(GLuint *)(buf + (_x)*4 + (_y)*pitch) & 0xffffff;


#define TAG(x) intel##x##_z24_s8
#include "depthtmp.h"

#define WRITE_STENCIL( _x, _y, d ) {			\
   GLuint tmp = *(GLuint *)(buf + (_x)*4 + (_y)*pitch);	\
   tmp &= 0xffffff;					\
   tmp |= ((d)<<24);					\
   *(GLuint *)(buf + (_x)*4 + (_y)*pitch) = tmp;		\
}

#define READ_STENCIL( d, _x, _y )			\
   d = *(GLuint *)(buf + (_x)*4 + (_y)*pitch) >> 24;

#define TAG(x) intel##x##_z24_s8
#include "stenciltmp.h"


/**
 * Prepare for softare rendering.  Map current read/draw framebuffers'
 * renderbuffes and all currently bound texture objects.
 *
 * Old note: Moved locking out to get reasonable span performance.
 */
void intelSpanRenderStart( GLcontext *ctx )
{
   struct intel_context *intel = intel_context(ctx);
   GLuint i;

   intelFlush(&intel->ctx);
   LOCK_HARDWARE(intel);

   /* Just map the framebuffer and all textures.  Bufmgr code will
    * take care of waiting on the necessary fences:
    */
   intel_region_map(intel, intel->front_region);
   intel_region_map(intel, intel->back_region);
   intel_region_map(intel, intel->depth_region);

   for (i = 0; i < ctx->Const.MaxTextureCoordUnits; i++) {
      if (ctx->Texture.Unit[i]._ReallyEnabled) {
	 struct gl_texture_object *texObj = ctx->Texture.Unit[i]._Current;
	 intel_tex_map_images(intel, intel_texture_object(texObj));
      }
   }
}

/**
 * Called when done softare rendering.  Unmap the buffers we mapped in
 * the above function.
 */
void intelSpanRenderFinish( GLcontext *ctx )
{
   struct intel_context *intel = intel_context( ctx );
   GLuint i;

   _swrast_flush( ctx );

   /* Now unmap the framebuffer:
    */
   intel_region_unmap(intel, intel->front_region);
   intel_region_unmap(intel, intel->back_region);
   intel_region_unmap(intel, intel->depth_region);

   for (i = 0; i < ctx->Const.MaxTextureCoordUnits; i++) {
      if (ctx->Texture.Unit[i]._ReallyEnabled) {
	 struct gl_texture_object *texObj = ctx->Texture.Unit[i]._Current;
	 intel_tex_unmap_images(intel, intel_texture_object(texObj));
      }
   }

   UNLOCK_HARDWARE( intel );
}

void intelInitSpanFuncs( GLcontext *ctx )
{
   struct swrast_device_driver *swdd = _swrast_GetDeviceDriverReference(ctx);
   swdd->SpanRenderStart = intelSpanRenderStart;
   swdd->SpanRenderFinish = intelSpanRenderFinish; 
}


void
intel_set_span_functions(struct gl_renderbuffer *rb)
{
   if (rb->InternalFormat == GL_RGB5) {
      /* 565 RGB */
      intelInitPointers_RGB565(rb);
   }
   else if (rb->InternalFormat == GL_RGBA8) {
      /* 8888 RGBA */
      intelInitPointers_ARGB8888(rb);
   }
   else if (rb->InternalFormat == GL_DEPTH_COMPONENT16) {
      intelInitDepthPointers_z16(rb);
   }
   else if (rb->InternalFormat == GL_DEPTH_COMPONENT24) {
      intelInitDepthPointers_z24_s8(rb);
   }
   else if (rb->InternalFormat == GL_STENCIL_INDEX8_EXT) {
      intelInitStencilPointers_z24_s8(rb);
   }
   else {
      _mesa_problem(NULL, "Unexpected InternalFormat in intelSetSpanFunctions");
   }
}
