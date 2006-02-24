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


#include "imports.h"
#include "mtypes.h"
#include "bufferobj.h"

#include "intel_context.h"
#include "intel_buffer_objects.h"
#include "bufmgr.h"


struct intel_buffer_object {
   struct gl_buffer_object Base;
   GLuint buffer;
};

static inline struct intel_buffer_object *
intel_buffer_object( struct gl_buffer_object *obj )
{
   return (struct intel_buffer_object *)obj;
}

/* There is some duplication between mesa's bufferobjects and our
 * bufmgr buffers.  Both have an integer handle and a hashtable to
 * lookup an opaque structure.  It would be nice if the handles and
 * internal structure where somehow shared.
 */
static struct gl_buffer_object *intel_bufferobj_alloc( GLcontext *ctx, 
						       GLuint name, 
						       GLenum target )
{
   struct intel_context *intel = intel_context(ctx);
   struct intel_buffer_object *obj = MALLOC_STRUCT(intel_buffer_object);

   _mesa_initialize_buffer_object(&obj->Base, name, target);

   /* XXX:  We generate our own handle, which is different to 'name' above.
    */
   bmGenBuffers(intel->bm, &obj->buffer, 1);

   return &obj->Base;
}

static void intel_bufferobj_free( GLcontext *ctx, 
				  struct gl_buffer_object *obj )
{ 
   /* Are the obj->Name tests necessary?  Unfortunately yes, mesa
    * allocates a couple of gl_buffer_object structs statically, and
    * the Name == 0 test is the only way to identify them and avoid
    * casting them erroneously to our structs.
    */
   if (obj->Name) {
      struct intel_context *intel = intel_context(ctx);
      struct intel_buffer_object *intel_obj = intel_buffer_object(obj);

      if (intel_obj->buffer) 
	 bmDeleteBuffers( intel->bm, 1, &intel_obj->buffer );
  
      _mesa_free(obj);
   }
}



/* Allocate space for and store data in a buffer object.  Any data that was
 * previously stored in the buffer object is lost.  If data is NULL,
 * memory will be allocated, but no copy will occur.
 */
static void intel_bufferobj_data( GLcontext *ctx, 
				  GLenum target, 
				  GLsizeiptrARB size,
				  const GLvoid *data, 
				  GLenum usage,
				  struct gl_buffer_object *obj )
{
   if (obj->Name) {
      struct intel_context *intel = intel_context(ctx);
      struct intel_buffer_object *intel_obj = intel_buffer_object(obj);

      /* XXX: do something useful with 'usage' (eg. populate flags
       * argument below)
       */
      bmBufferData(intel->bm, obj->buffer, size, data, 0);
   }
}


/* Replace data in a subrange of buffer object.  If the data range
 * specified by size + offset extends beyond the end of the buffer or
 * if data is NULL, no copy is performed.
 */
static void intel_bufferobj_subdata( GLcontext *ctx, 
				     GLenum target, 
				     GLintptrARB offset,
				     GLsizeiptrARB size, 
				     const GLvoid * data,
				     struct gl_buffer_object * obj )
{
   if (obj->Name) {
      struct intel_context *intel = intel_context(ctx);
      struct intel_buffer_object *intel_obj = intel_buffer_object(obj);

      bmBufferSubData(intel->bm, obj->buffer, size, data);
   }
}




static void *intel_bufferobj_map( GLcontext *ctx, 
				  GLenum target, 
				  GLenum access,
				  struct gl_buffer_object *obj )
{
   if (obj->Name) {
      struct intel_context *intel = intel_context(ctx);
      struct intel_buffer_object *intel_obj = intel_buffer_object(obj);

      /* XXX: Translate access to flags arg below:
       */
      return bmMapBuffer(intel->bm, intel_obj->buffer, 0);
   }
      
   return NULL;
}


static GLboolean intel_bufferobj_unmap( GLcontext *ctx,
					GLenum target,
					struct gl_buffer_object *obj )
{
   if (obj->Name) {
      struct intel_context *intel = intel_context(ctx);
      struct intel_buffer_object *intel_obj = intel_buffer_object(obj);

      return bmUnmapBuffer(intel->bm, intel_obj->buffer);
   }
   
   return GL_TRUE;
}

GLuint intel_bufferobj_buffer( struct gl_buffer_object *obj )
{
   if (obj->Name) {
      struct intel_buffer_object *intel_obj = intel_buffer_object(obj);
      return intel_obj->buffer;
   }
   else {
      assert(0);
      return 0;
   }
      
}  

void intel_bufferobj_init( struct intel_context *intel )
{
   GLcontext *ctx = &intel->ctx;

   ctx->Driver.NewBufferObject = intel_new_buffer_object;
   ctx->Driver.DeleteBuffer = intel_delete_buffer_object;
   ctx->Driver.BufferData = intel_buffer_data;
   ctx->Driver.BufferSubData = intel_buffer_subdata;
   ctx->Driver.MapBuffer = intel_buffer_map;
   ctx->Driver.UnmapBuffer = intel_buffer_unmap;
}
