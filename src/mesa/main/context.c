/**
 * \file context.c
 * \brief Mesa context/visual/framebuffer management functions.
 * \author Brian Paul
 */

/*
 * Mesa 3-D graphics library
 * Version:  4.1
 *
 * Copyright (C) 1999-2002  Brian Paul   All Rights Reserved.
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

/* $Id: context.c,v 1.188.2.1.2.16 2003/03/23 23:22:47 jrfonseca Exp $ */

/**
 * \mainpage Mesa Core Module
 *
 * \section CoreIntroduction Introduction
 *
 * The Mesa core module consists of all the top-level files in the src
 * directory.  The core module basically takes care of API dispatch,
 * and OpenGL state management.
 *
 * For example, calls to glPolygonMode() are routed to _mesa_PolygonMode()
 * which updates the state related to polygonmode.  Furthermore, dirty
 * state flags related to polygon mode are set and if the device driver
 * implements a special routine for PolygonMode, it will be called.
 *
 *
 * \section AboutDoxygen About Doxygen
 *
 * If you're viewing this information as Doxygen-generated HTML you'll
 * see the documentation index at the top of this page.
 *
 * The first line lists the Mesa source code modules.
 * The second line lists the indexes available for viewing the documentation
 * for each module.
 *
 * Selecting the <b>Main page</b> link will display a summary of the module
 * (this page).
 *
 * Selecting <b>Compound List</b> will list all C structures.
 *
 * Selecting the <b>File List</b> link will list all the source files in
 * the module.
 * Selecting a filename will show a list of all functions defined in that file.
 *
 * Selecting the <b>Compound Members</b> link will display a list of all
 * documented structure members.
 *
 * Selecting the <b>File Members</b> link will display a list
 * of all functions, structures, global variables and macros in the module.
 *
 */


#include "glheader.h"
#include "imports.h"
#include "accum.h"
#include "attrib.h"
#include "blend.h"
#include "buffers.h"
//#include "clip.h"
#include "colortab.h"
#include "context.h"
#include "debug.h"
#include "depth.h"
#include "dlist.h"
#include "eval.h"
#include "enums.h"
#include "extensions.h"
#include "feedback.h"
#include "fog.h"
#include "get.h"
#include "glthread.h"
#include "histogram.h"
#include "hint.h"
#include "hash.h"
#include "light.h"
#include "lines.h"
#include "macros.h"
#include "matrix.h"
#include "mmath.h"
#include "pixel.h"
#include "points.h"
#include "polygon.h"
#include "rastpos.h"
#include "simple_list.h"
#include "state.h"
#include "stencil.h"
#include "teximage.h"
#include "texobj.h"
#include "texstate.h"
#include "mtypes.h"
#include "varray.h"
#if FEATURE_NV_vertex_program
#include "vpstate.h"
#endif
#include "vtxfmt.h"
#if _HAVE_FULL_GL
#include "math/m_translate.h"
#include "math/m_matrix.h"
#include "math/m_xform.h"
#include "math/mathmod.h"
#endif

#if defined(MESA_TRACE)
#include "Trace/tr_context.h"
#include "Trace/tr_wrapper.h"
#endif

#ifdef USE_SPARC_ASM
#include "SPARC/sparc.h"
#endif

#ifndef MESA_VERBOSE
int MESA_VERBOSE = 0;
#endif

#ifndef MESA_DEBUG_FLAGS
int MESA_DEBUG_FLAGS = 0;
#endif


static void
free_shared_state( GLcontext *ctx, struct gl_shared_state *ss );


/**********************************************************************/
/** \name OpenGL SI-style interface (new in Mesa 3.5)
 *
 * \if subset
 * \note Most of these functions are never called in the Mesa subset.
 * \endif
 */
/*@{*/

/**
 * \brief Destroy context callback.
 * 
 * \param gc context.
 * \return GL_TRUE on success, or GL_FALSE on failure.
 * 
 * \ifnot subset
 * Called by window system/device driver (via __GLexports::destroyCurrent) when
 * the rendering context is to be destroyed.
 * \endif
 *
 * Frees the context data and the context structure.
 */
GLboolean
_mesa_destroyContext(__GLcontext *gc)
{
   if (gc) {
      _mesa_free_context_data(gc);
      _mesa_free(gc);
   }
   return GL_TRUE;
}

/**
 * \brief Unbind context callback.
 * 
 * \param gc context.
 * \return GL_TRUE on success, or GL_FALSE on failure.
 *
 * \ifnot subset
 * Called by window system/device driver (via __GLexports::loseCurrent)
 * when the rendering context is made non-current.
 * \endif
 *
 * No-op
 */
GLboolean
_mesa_loseCurrent(__GLcontext *gc)
{
   /* XXX unbind context from thread */
   return GL_TRUE;
}

/**
 * \brief Bind context callback.
 * 
 * \param gc context.
 * \return GL_TRUE on success, or GL_FALSE on failure.
 *
 * \ifnot subset
 * Called by window system/device driver (via __GLexports::makeCurrent)
 * when the rendering context is made current.
 * \endif
 *
 * No-op
 */
GLboolean
_mesa_makeCurrent(__GLcontext *gc)
{
   /* XXX bind context to thread */
   return GL_TRUE;
}

/**
 * \brief Share context callback.
 * 
 * \param gc context.
 * \return GL_TRUE on success, or GL_FALSE on failure.
 *
 * \ifnot subset
 * Called by window system/device driver (via __GLexports::shareContext)
 * \endif
 *
 * Update the shared context reference count, gl_shared_state::RefCount.
 */
GLboolean
_mesa_shareContext(__GLcontext *gc, __GLcontext *gcShare)
{
   if (gc && gcShare && gc->Shared && gcShare->Shared) {
      gc->Shared->RefCount--;
      if (gc->Shared->RefCount == 0) {
         free_shared_state(gc, gc->Shared);
      }
      gc->Shared = gcShare->Shared;
      gc->Shared->RefCount++;
      return GL_TRUE;
   }
   else {
      return GL_FALSE;
   }
}


#if _HAVE_FULL_GL
/**
 * \brief Copy context callback.
 */
GLboolean
_mesa_copyContext(__GLcontext *dst, const __GLcontext *src, GLuint mask)
{
   if (dst && src) {
      _mesa_copy_context( src, dst, mask );
      return GL_TRUE;
   }
   else {
      return GL_FALSE;
   }
}
#endif

/** \brief No-op */
GLboolean
_mesa_forceCurrent(__GLcontext *gc)
{
   return GL_TRUE;
}

/**
 * \brief Windows/buffer resizing notification callback.
 *
 * \param gc GL context.
 * \return GL_TRUE on success, or GL_FALSE on failure.
 */
GLboolean
_mesa_notifyResize(__GLcontext *gc)
{
   GLint x, y;
   GLuint width, height;
   __GLdrawablePrivate *d = gc->imports.getDrawablePrivate(gc);
   if (!d || !d->getDrawableSize)
      return GL_FALSE;
   d->getDrawableSize( d, &x, &y, &width, &height );
   /* update viewport, resize software buffers, etc. */
   return GL_TRUE;
}

/**
 * \brief Window/buffer destruction notification callback.
 *
 * \param gc GL context.
 * 
 * Called when the context's window/buffer is going to be destroyed. 
 *
 * No-op
 */
void
_mesa_notifyDestroy(__GLcontext *gc)
{
   /* Unbind from it. */
}

/**
 * \brief Swap buffers notification callback.
 * 
 * \param gc GL context.
 *
 * Called by window system just before swapping buffers.
 * We have to finish any pending rendering.
 */
void
_mesa_notifySwapBuffers(__GLcontext *gc)
{
   FLUSH_VERTICES( gc, 0 );
}

/** \brief No-op */
struct __GLdispatchStateRec *
_mesa_dispatchExec(__GLcontext *gc)
{
   return NULL;
}

/** \brief No-op */
void
_mesa_beginDispatchOverride(__GLcontext *gc)
{
}

/** \brief No-op */
void
_mesa_endDispatchOverride(__GLcontext *gc)
{
}

/**
 * \ifnot subset
 * \brief Setup the exports.  
 *
 * The window system will call these functions when it needs Mesa to do
 * something.
 * 
 * \note Device drivers should override these functions!  For example,
 * the Xlib driver should plug in the XMesa*-style functions into this
 * structure.  The XMesa-style functions should then call the _mesa_*
 * version of these functions.  This is an approximation to OO design
 * (inheritance and virtual functions).
 * \endif
 *
 * \if subset
 * \brief No-op.
 * 
 * \endif
 */
static void
_mesa_init_default_exports(__GLexports *exports)
{
#if _HAVE_FULL_GL
    exports->destroyContext = _mesa_destroyContext;
    exports->loseCurrent = _mesa_loseCurrent;
    exports->makeCurrent = _mesa_makeCurrent;
    exports->shareContext = _mesa_shareContext;
    exports->copyContext = _mesa_copyContext;
    exports->forceCurrent = _mesa_forceCurrent;
    exports->notifyResize = _mesa_notifyResize;
    exports->notifyDestroy = _mesa_notifyDestroy;
    exports->notifySwapBuffers = _mesa_notifySwapBuffers;
    exports->dispatchExec = _mesa_dispatchExec;
    exports->beginDispatchOverride = _mesa_beginDispatchOverride;
    exports->endDispatchOverride = _mesa_endDispatchOverride;
#endif
}

/**
 * \brief Exported OpenGL SI interface.
 */
__GLcontext *
__glCoreCreateContext(__GLimports *imports, __GLcontextModes *modes)
{
    GLcontext *ctx;

    ctx = (GLcontext *) (*imports->calloc)(NULL, 1, sizeof(GLcontext));
    if (ctx == NULL) {
	return NULL;
    }

    _mesa_initialize_context(ctx, modes, NULL, imports, GL_FALSE);
    ctx->imports = *imports;

    return ctx;
}

/**
 * \brief Exported OpenGL SI interface.
 */
void
__glCoreNopDispatch(void)
{
#if 0
   /* SI */
   __gl_dispatch = __glNopDispatchState;
#else
   /* Mesa */
   _glapi_set_dispatch(NULL);
#endif
}

/*@}*/


/**********************************************************************/
/** \name GL Visual allocation/destruction                            */
/**********************************************************************/
/*@{*/

/**
 * \brief Allocate a new GLvisual object.
 * 
 * \param rgbFlag GL_TRUE for RGB(A) mode, GL_FALSE for Color Index mode.
 * \param dbFlag double buffering
 * \param stereoFlag stereo buffer
 * \param depthBits requested bits per depth buffer value. Any value in [0, 32]
 * is acceptable but the actual depth type will be GLushort or GLuint as
 * needed.
 * \param stencilBits requested minimum bits per stencil buffer value
 * \param accumBits requested minimum bits per accum buffer component
 * \param indexBits number of bits per pixel if \p rgbFlag is GL_FALSE
 * \param red number of bits per color component in frame buffer for RGB(A)
 * mode.  We always use 8 in core Mesa though.
 * \param green same as above.
 * \param blue same as above.
 * \param alphaBits same as above.
 * 
 * \return pointer to new GLvisual or NULL if requested parameters can't be
 * met.
 *
 * Allocates a GLvisual structure and initializes it via
 * _mesa_initialize_visual().
 */
GLvisual *
_mesa_create_visual( GLboolean rgbFlag,
                     GLboolean dbFlag,
                     GLboolean stereoFlag,
                     GLint redBits,
                     GLint greenBits,
                     GLint blueBits,
                     GLint alphaBits,
                     GLint indexBits,
                     GLint depthBits,
                     GLint stencilBits,
                     GLint accumRedBits,
                     GLint accumGreenBits,
                     GLint accumBlueBits,
                     GLint accumAlphaBits,
                     GLint numSamples )
{
   GLvisual *vis = (GLvisual *) CALLOC( sizeof(GLvisual) );
   if (vis) {
      if (!_mesa_initialize_visual(vis, rgbFlag, dbFlag, stereoFlag,
                                   redBits, greenBits, blueBits, alphaBits,
                                   indexBits, depthBits, stencilBits,
                                   accumRedBits, accumGreenBits,
                                   accumBlueBits, accumAlphaBits,
                                   numSamples)) {
         FREE(vis);
         return NULL;
      }
   }
   return vis;
}

/**
 * \brief Initialize the fields of the given GLvisual.
 * 
 * \return GL_TRUE on success, or GL_FALSE on failure.
 *
 * \sa _mesa_create_visual() above for the parameter description.
 *
 * Makes some sanity checks and fills in the fields of the
 * GLvisual structure with the given parameters.
 */
GLboolean
_mesa_initialize_visual( GLvisual *vis,
                         GLboolean rgbFlag,
                         GLboolean dbFlag,
                         GLboolean stereoFlag,
                         GLint redBits,
                         GLint greenBits,
                         GLint blueBits,
                         GLint alphaBits,
                         GLint indexBits,
                         GLint depthBits,
                         GLint stencilBits,
                         GLint accumRedBits,
                         GLint accumGreenBits,
                         GLint accumBlueBits,
                         GLint accumAlphaBits,
                         GLint numSamples )
{
   (void) numSamples;

   assert(vis);

   /* This is to catch bad values from device drivers not updated for
    * Mesa 3.3.  Some device drivers just passed 1.  That's a REALLY
    * bad value now (a 1-bit depth buffer!?!).
    */
   assert(depthBits == 0 || depthBits > 1);

   if (depthBits < 0 || depthBits > 32) {
      return GL_FALSE;
   }
   if (stencilBits < 0 || stencilBits > (GLint) (8 * sizeof(GLstencil))) {
      return GL_FALSE;
   }
   if (accumRedBits < 0 || accumRedBits > (GLint) (8 * sizeof(GLaccum))) {
      return GL_FALSE;
   }
   if (accumGreenBits < 0 || accumGreenBits > (GLint) (8 * sizeof(GLaccum))) {
      return GL_FALSE;
   }
   if (accumBlueBits < 0 || accumBlueBits > (GLint) (8 * sizeof(GLaccum))) {
      return GL_FALSE;
   }
   if (accumAlphaBits < 0 || accumAlphaBits > (GLint) (8 * sizeof(GLaccum))) {
      return GL_FALSE;
   }

   vis->rgbMode          = rgbFlag;
   vis->doubleBufferMode = dbFlag;
   vis->stereoMode       = stereoFlag;

   vis->redBits          = redBits;
   vis->greenBits        = greenBits;
   vis->blueBits         = blueBits;
   vis->alphaBits        = alphaBits;

   vis->indexBits      = indexBits;
   vis->depthBits      = depthBits;
   vis->accumRedBits   = (accumRedBits > 0) ? (8 * sizeof(GLaccum)) : 0;
   vis->accumGreenBits = (accumGreenBits > 0) ? (8 * sizeof(GLaccum)) : 0;
   vis->accumBlueBits  = (accumBlueBits > 0) ? (8 * sizeof(GLaccum)) : 0;
   vis->accumAlphaBits = (accumAlphaBits > 0) ? (8 * sizeof(GLaccum)) : 0;
   vis->stencilBits    = (stencilBits > 0) ? (8 * sizeof(GLstencil)) : 0;

   vis->haveAccumBuffer   = accumRedBits > 0;
   vis->haveDepthBuffer   = depthBits > 0;
   vis->haveStencilBuffer = stencilBits > 0;

   vis->numAuxBuffers = 0;
   vis->level = 0;
   vis->pixmapMode = 0;

   return GL_TRUE;
}

/**
 * \brief Destroy a visual.
 *
 * \param vis visual.
 * 
 * Frees the visual structure.
 */
void
_mesa_destroy_visual( GLvisual *vis )
{
   FREE(vis);
}

/*@}*/


/**********************************************************************/
/** \name GL Framebuffer allocation/destruction                       */
/**********************************************************************/
/*@{*/

/**
 * \brief Create a new framebuffer.  
 *
 * A GLframebuffer is a structure which encapsulates the depth, stencil and
 * accum buffers and related parameters.
 * 
 * \param visual a GLvisual pointer (we copy the struct contents)
 * \param softwareDepth create/use a software depth buffer?
 * \param softwareStencil create/use a software stencil buffer?
 * \param softwareAccum create/use a software accum buffer?
 * \param softwareAlpha create/use a software alpha buffer?
 *
 * \return pointer to new GLframebuffer struct or NULL if error.
 *
 * Allocate a GLframebuffer structure and initializes it via
 * _mesa_initialize_framebuffer().
 */
GLframebuffer *
_mesa_create_framebuffer( const GLvisual *visual,
                          GLboolean softwareDepth,
                          GLboolean softwareStencil,
                          GLboolean softwareAccum,
                          GLboolean softwareAlpha )
{
   GLframebuffer *buffer = CALLOC_STRUCT(gl_frame_buffer);
   assert(visual);
   if (buffer) {
      _mesa_initialize_framebuffer(buffer, visual,
                                   softwareDepth, softwareStencil,
                                   softwareAccum, softwareAlpha );
   }
   return buffer;
}

/**
 * \brief Initialize a GLframebuffer object.
 * 
 * \sa _mesa_create_framebuffer() above for the parameter description.
 *
 * Makes some sanity checks and fills in the fields of the
 * GLframebuffer structure with the given parameters.
 */
void
_mesa_initialize_framebuffer( GLframebuffer *buffer,
                              const GLvisual *visual,
                              GLboolean softwareDepth,
                              GLboolean softwareStencil,
                              GLboolean softwareAccum,
                              GLboolean softwareAlpha )
{
   assert(buffer);
   assert(visual);

   _mesa_bzero(buffer, sizeof(GLframebuffer));

   /* sanity checks */
   if (softwareDepth ) {
      assert(visual->depthBits > 0);
   }
   if (softwareStencil) {
      assert(visual->stencilBits > 0);
   }
   if (softwareAccum) {
      assert(visual->rgbMode);
      assert(visual->accumRedBits > 0);
      assert(visual->accumGreenBits > 0);
      assert(visual->accumBlueBits > 0);
   }
   if (softwareAlpha) {
      assert(visual->rgbMode);
      assert(visual->alphaBits > 0);
   }

   buffer->Visual = *visual;
   buffer->UseSoftwareDepthBuffer = softwareDepth;
   buffer->UseSoftwareStencilBuffer = softwareStencil;
   buffer->UseSoftwareAccumBuffer = softwareAccum;
   buffer->UseSoftwareAlphaBuffers = softwareAlpha;
}

/**
 * \brief Free a framebuffer struct and its buffers.
 *
 * Calls _mesa_free_framebuffer_data() and frees the structure.
 */
void
_mesa_destroy_framebuffer( GLframebuffer *buffer )
{
   if (buffer) {
      _mesa_free_framebuffer_data(buffer);
      FREE(buffer);
   }
}

/**
 * \brief Free the data hanging off of \p buffer, but not \p buffer itself.
 *
 * \param buffer framebuffer.
 *
 * Frees all the buffers associated with the structure.
 */
void
_mesa_free_framebuffer_data( GLframebuffer *buffer )
{
   if (!buffer)
      return;

   if (buffer->DepthBuffer) {
      MESA_PBUFFER_FREE( buffer->DepthBuffer );
      buffer->DepthBuffer = NULL;
   }
   if (buffer->Accum) {
      MESA_PBUFFER_FREE( buffer->Accum );
      buffer->Accum = NULL;
   }
   if (buffer->Stencil) {
      MESA_PBUFFER_FREE( buffer->Stencil );
      buffer->Stencil = NULL;
   }
   if (buffer->FrontLeftAlpha) {
      MESA_PBUFFER_FREE( buffer->FrontLeftAlpha );
      buffer->FrontLeftAlpha = NULL;
   }
   if (buffer->BackLeftAlpha) {
      MESA_PBUFFER_FREE( buffer->BackLeftAlpha );
      buffer->BackLeftAlpha = NULL;
   }
   if (buffer->FrontRightAlpha) {
      MESA_PBUFFER_FREE( buffer->FrontRightAlpha );
      buffer->FrontRightAlpha = NULL;
   }
   if (buffer->BackRightAlpha) {
      MESA_PBUFFER_FREE( buffer->BackRightAlpha );
      buffer->BackRightAlpha = NULL;
   }
}

/*@}*/


/**********************************************************************/
/** \name Context allocation, initialization, destroying
 *
 * The purpose of the most initalization functions here is to provide the
 * default state values according to the OpenGL specification.
 */
/**********************************************************************/
/*@{*/

/**
 * \brief One-time initalization mutex lock.
 *
 * \sa Used by one_time_init().
 */
_glthread_DECLARE_STATIC_MUTEX(OneTimeLock);

/**
 * \brief Calls all the various one-time-init functions in Mesa.
 *
 * While holding a global mutex lock, calls several initialization functions,
 * and sets the glapi callbacks if the \c MESA_DEBUG environment variable is
 * defined.
 *
 * \sa _mesa_init_lists(), _math_init() and _mesa_init_math().
 */
static void
one_time_init( GLcontext *ctx )
{
   static GLboolean alreadyCalled = GL_FALSE;
   _glthread_LOCK_MUTEX(OneTimeLock);
   if (!alreadyCalled) {
      /* do some implementation tests */
      assert( sizeof(GLbyte) == 1 );
      assert( sizeof(GLshort) >= 2 );
      assert( sizeof(GLint) >= 4 );
      assert( sizeof(GLubyte) == 1 );
      assert( sizeof(GLushort) >= 2 );
      assert( sizeof(GLuint) >= 4 );

      _mesa_init_lists();

#if _HAVE_FULL_GL
      _math_init();
      _mesa_init_math();
#endif

#ifdef USE_SPARC_ASM
      _mesa_init_sparc_glapi_relocs();
#endif
      if (_mesa_getenv("MESA_DEBUG")) {
         _glapi_noop_enable_warnings(GL_TRUE);
#ifndef GLX_DIRECT_RENDERING
         /* libGL from before 2002/06/28 don't have this function.  Someday,
          * when newer libGL libs are common, remove the #ifdef test.  This
          * only serves to print warnings when calling undefined GL functions.
          */
         _glapi_set_warning_func( (_glapi_warning_func) _mesa_warning );
#endif
      }
      else {
         _glapi_noop_enable_warnings(GL_FALSE);
      }

#if defined(DEBUG) && defined(__DATE__) && defined(__TIME__)
      _mesa_debug(ctx, "Mesa DEBUG build %s %s\n", __DATE__, __TIME__);
#endif

      alreadyCalled = GL_TRUE;
   }
   _glthread_UNLOCK_MUTEX(OneTimeLock);
}

/**
 * \brief Allocate and initialize a shared context state structure.
 *
 * \return pointer to a gl_shared_state structure on success, or NULL on
 * failure.
 *
 * Initializes the display list, texture objects and vertex programs hash
 * tables, allocates the texture objects. If it runs out of memory, frees
 * everything already allocated before returing NULL.
 */
static struct gl_shared_state *
alloc_shared_state( void )
{
   struct gl_shared_state *ss;
   GLboolean outOfMemory;

   ss = CALLOC_STRUCT(gl_shared_state);
   if (!ss)
      return NULL;

   _glthread_INIT_MUTEX(ss->Mutex);

   ss->DisplayList = _mesa_NewHashTable();
   ss->TexObjects = _mesa_NewHashTable();
#if FEATURE_NV_vertex_program
   ss->VertexPrograms = _mesa_NewHashTable();
#endif

   /* Default Texture objects */
   outOfMemory = GL_FALSE;

   ss->Default1D = _mesa_alloc_texture_object(ss, 0, GL_TEXTURE_1D);
   if (!ss->Default1D) {
      outOfMemory = GL_TRUE;
   }

   ss->Default2D = _mesa_alloc_texture_object(ss, 0, GL_TEXTURE_2D);
   if (!ss->Default2D) {
      outOfMemory = GL_TRUE;
   }

   ss->Default3D = _mesa_alloc_texture_object(ss, 0, GL_TEXTURE_3D);
   if (!ss->Default3D) {
      outOfMemory = GL_TRUE;
   }

   ss->DefaultCubeMap = _mesa_alloc_texture_object(ss, 0,
                                                   GL_TEXTURE_CUBE_MAP_ARB);
   if (!ss->DefaultCubeMap) {
      outOfMemory = GL_TRUE;
   }

   ss->DefaultRect = _mesa_alloc_texture_object(ss, 0,
                                                GL_TEXTURE_RECTANGLE_NV);
   if (!ss->DefaultRect) {
      outOfMemory = GL_TRUE;
   }

   if (!ss->DisplayList || !ss->TexObjects
#if FEATURE_NV_vertex_program
       || !ss->VertexPrograms
#endif
       || outOfMemory) {
      /* Ran out of memory at some point.  Free everything and return NULL */
      if (ss->DisplayList)
         _mesa_DeleteHashTable(ss->DisplayList);
      if (ss->TexObjects)
         _mesa_DeleteHashTable(ss->TexObjects);
      if (ss->VertexPrograms)
         _mesa_DeleteHashTable(ss->VertexPrograms);
      if (ss->Default1D)
         _mesa_free_texture_object(ss, ss->Default1D);
      if (ss->Default2D)
         _mesa_free_texture_object(ss, ss->Default2D);
      if (ss->Default3D)
         _mesa_free_texture_object(ss, ss->Default3D);
      if (ss->DefaultCubeMap)
         _mesa_free_texture_object(ss, ss->DefaultCubeMap);
      if (ss->DefaultRect)
         _mesa_free_texture_object(ss, ss->DefaultRect);
      FREE(ss);
      return NULL;
   }
   else {
      return ss;
   }
}

/**
 * \brief Deallocate a shared state context and all children structures.
 *
 * \param ctx GL context.
 * \param ss shared state pointer.
 * 
 * Frees the display lists, the texture objects (calling the driver texture
 * deletion callback to free its private data) and the vertex programs, as well
 * as their hash tables.
 *
 * \sa alloc_shared_state().
 */
static void
free_shared_state( GLcontext *ctx, struct gl_shared_state *ss )
{
   /* Free display lists */
   while (1) {
      GLuint list = _mesa_HashFirstEntry(ss->DisplayList);
      if (list) {
         _mesa_destroy_list(ctx, list);
      }
      else {
         break;
      }
   }
   _mesa_DeleteHashTable(ss->DisplayList);

   /* Free texture objects */
   while (ss->TexObjectList) {
      if (ctx->Driver.DeleteTexture)
         (*ctx->Driver.DeleteTexture)( ctx, ss->TexObjectList );
      /* this function removes from linked list too! */
      _mesa_free_texture_object(ss, ss->TexObjectList);
   }
   _mesa_DeleteHashTable(ss->TexObjects);

#if FEATURE_NV_vertex_program
   /* Free vertex programs */
   while (1) {
      GLuint prog = _mesa_HashFirstEntry(ss->VertexPrograms);
      if (prog) {
         _mesa_delete_program(ctx, prog);
      }
      else {
         break;
      }
   }
   _mesa_DeleteHashTable(ss->VertexPrograms);
#endif

   FREE(ss);
}


static void _mesa_init_current( GLcontext *ctx )
{
   int i;

   /* Current group */
   ASSIGN_4V( ctx->Current.Attrib[VERT_ATTRIB_WEIGHT], 0.0, 0.0, 0.0, 0.0 );
   ASSIGN_4V( ctx->Current.Attrib[VERT_ATTRIB_NORMAL], 0.0, 0.0, 1.0, 0.0 );
   ASSIGN_4V( ctx->Current.Attrib[VERT_ATTRIB_COLOR0], 1.0, 1.0, 1.0, 1.0 );
   ASSIGN_4V( ctx->Current.Attrib[VERT_ATTRIB_COLOR1], 0.0, 0.0, 0.0, 0.0 );
   ASSIGN_4V( ctx->Current.Attrib[VERT_ATTRIB_FOG], 0.0, 0.0, 0.0, 0.0 );
   for (i = 0; i < MAX_TEXTURE_UNITS; i++)
      ASSIGN_4V( ctx->Current.Attrib[VERT_ATTRIB_TEX0 + i], 0.0, 0.0, 0.0, 1.0);
   ctx->Current.Index = 1;
   ctx->Current.EdgeFlag = GL_TRUE;
}


/**
 * \brief Initialize the attribute groups in a GL context.
 *
 * \param ctx GL context.
 *
 * Initializes all the attributes, calling the respective <tt>init*</tt>
 * functions for the more complex data structures.
 */
static GLboolean
init_attrib_groups( GLcontext *ctx )
{
   assert(ctx);

   /* Extensions */
   _mesa_extensions_ctr( ctx );

   _mesa_init_accum( ctx );
   _mesa_init_attrib( ctx );
   _mesa_init_buffers( ctx );
   _mesa_init_color( ctx );
   _mesa_init_colortable( ctx );
   _mesa_init_current( ctx );
   _mesa_init_depth( ctx );
   _mesa_init_debug( ctx );
   _mesa_init_display_list( ctx );
   _mesa_init_eval( ctx );
   _mesa_init_feedback( ctx );
   _mesa_init_fog( ctx );
   _mesa_init_histogram( ctx );
   _mesa_init_hint( ctx );
   _mesa_init_line( ctx );
   _mesa_init_lighting( ctx );
   _mesa_init_matrix( ctx );
   _mesa_init_pixel( ctx );
   _mesa_init_point( ctx );
   _mesa_init_polygon( ctx );
   _mesa_init_rastpos( ctx );
   _mesa_init_stencil( ctx );
   _mesa_init_transform( ctx );
   _mesa_init_varray( ctx );
   _mesa_init_viewport( ctx );
#if FEATURE_NV_vertex_program
   _mesa_init_vertex_program( ctx );
#endif

   if (!_mesa_init_texture( ctx ))
      return GL_FALSE;

   /* Miscellaneous */
   ctx->NewState = _NEW_ALL;
   ctx->ErrorValue = (GLenum) GL_NO_ERROR;
   ctx->CatchSignals = GL_TRUE;
   ctx->OcclusionResult = GL_FALSE;
   ctx->OcclusionResultSaved = GL_FALSE;
   ctx->_Facing = 0;

   /* Constants, may be overriden by device drivers */
   ctx->Const.SubPixelBits = SUB_PIXEL_BITS;

   return GL_TRUE;
}



/**
 * \brief Initialize a GLcontext struct. 
 *
 * This includes allocating all the other structs and arrays which hang off of
 * the context by pointers.
 * 
 * \param ctx GL context.
 * 
 * \sa _mesa_create_context() for the remaining parameter description.
 *
 * Performs the imports and exports callback tables initialzation, and
 * miscellaenuos one-time initializations. If no shared context is supplied one
 * is allocated, and increase its reference count.  Setups the GL API dispatch
 * tables.  Initialize the TNL module. Sets the maximum Z buffer depth.
 * Finally queries the \c MESA_DEBUG and \c MESA_VERBOSE environment variables
 * for debug flags.
 */
GLboolean
_mesa_initialize_context( GLcontext *ctx,
                          const GLvisual *visual,
                          GLcontext *share_list,
                          void *driver_ctx,
                          GLboolean direct )
{
   GLuint dispatchSize;

   ASSERT(driver_ctx);

   /* If the driver wants core Mesa to use special imports, it'll have to
    * override these defaults.
    */
   _mesa_init_default_imports( &(ctx->imports), driver_ctx );

   /* initialize the exports (Mesa functions called by the window system) */
   _mesa_init_default_exports( &(ctx->exports) );

   /* misc one-time initializations */
   one_time_init(ctx);

   ctx->DriverCtx = driver_ctx;
   ctx->Visual = *visual;
   ctx->DrawBuffer = NULL;
   ctx->ReadBuffer = NULL;

   if (share_list) {
      /* share state with another context */
      ctx->Shared = share_list->Shared;
   }
   else {
      /* allocate new, unshared state */
      ctx->Shared = alloc_shared_state();
      if (!ctx->Shared) {
	 fprintf(stderr, "%s: failed to alloc shared state\n", __FUNCTION__);
         return GL_FALSE;
      }
   }
   _glthread_LOCK_MUTEX(ctx->Shared->Mutex);
   ctx->Shared->RefCount++;
   _glthread_UNLOCK_MUTEX(ctx->Shared->Mutex);

   if (!init_attrib_groups( ctx )) {
      free_shared_state(ctx, ctx->Shared);
      fprintf(stderr, "%s: failed to init attrib groups\n", __FUNCTION__);
      return GL_FALSE;
   }

   /* Find the larger of Mesa's dispatch table and libGL's dispatch table.
    * In practice, this'll be the same for stand-alone Mesa.  But for DRI
    * Mesa we do this to accomodate different versions of libGL and various
    * DRI drivers.
    */
   dispatchSize = MAX2(_glapi_get_dispatch_table_size(),
                       sizeof(struct _glapi_table) / sizeof(void *));

   /* setup API dispatch tables */
   ctx->Exec = (struct _glapi_table *) CALLOC(dispatchSize * sizeof(void*));
   ctx->Save = (struct _glapi_table *) CALLOC(dispatchSize * sizeof(void*));
   if (!ctx->Exec || !ctx->Save) {
      free_shared_state(ctx, ctx->Shared);
      if (ctx->Exec)
         FREE( ctx->Exec );
   }
   _mesa_init_exec_table(ctx->Exec, dispatchSize);
   ctx->CurrentDispatch = ctx->Exec;

#if _HAVE_FULL_GL
   _mesa_init_dlist_table(ctx->Save, dispatchSize);

   ctx->ExecPrefersFloat = GL_FALSE;
   ctx->SavePrefersFloat = GL_FALSE;

   /* Neutral tnl module stuff */
   _mesa_init_exec_vtxfmt( ctx ); 
   ctx->TnlModule.Current = NULL;
   ctx->TnlModule.SwapCount = 0;

#endif

   fprintf(stderr, "%s: succeded\n", __FUNCTION__);
   return GL_TRUE;
}

/**
 * \brief Allocate and initialize a GLcontext structure.
 *
 * \param visual a GLvisual pointer (we copy the struct contents)
 * \param sharelist another context to share display lists with or NULL
 * \param driver_ctx pointer to device driver's context state struct
 * \param direct direct rendering?
 * 
 * \return pointer to a new __GLcontextRec or NULL if error.
 */
GLcontext *
_mesa_create_context( const GLvisual *visual,
                      GLcontext *share_list,
                      void *driver_ctx,
                      GLboolean direct )

{
   GLcontext *ctx;

   ASSERT(visual);
   ASSERT(driver_ctx);

   ctx = (GLcontext *) _mesa_calloc(sizeof(GLcontext));
   if (!ctx)
      return NULL;

   if (_mesa_initialize_context(ctx, visual, share_list, driver_ctx, direct)) {
      return ctx;
   }
   else {
      _mesa_free(ctx);
      return NULL;
   }
}

/**
 * \brief Free the data associated with the given context.
 * 
 * But doesn't free the GLcontext struct itself.
 *
 * \sa _mesa_initialize_context() and init_attrib_groups().
 */
void
_mesa_free_context_data( GLcontext *ctx )
{
   /* if we're destroying the current context, unbind it first */
   if (ctx == _mesa_get_current_context()) {
      _mesa_make_current(NULL, NULL);
   }


   _mesa_free_lighting_data( ctx );
   _mesa_free_eval_data( ctx );
   _mesa_free_texture_data( ctx );
   _mesa_free_matrix_data( ctx );
   _mesa_free_viewport_data( ctx );
   _mesa_free_colortable_data( ctx );
#if FEATURE_NV_vertex_program
   _mesa_free_vertex_program_data( ctx );
#endif

   /* Shared context state (display lists, textures, etc) */
   _glthread_LOCK_MUTEX(ctx->Shared->Mutex);
   ctx->Shared->RefCount--;
   assert(ctx->Shared->RefCount >= 0);
   _glthread_UNLOCK_MUTEX(ctx->Shared->Mutex);
   if (ctx->Shared->RefCount == 0) {
      /* free shared state */
      free_shared_state( ctx, ctx->Shared );
   }

   _mesa_extensions_dtr(ctx);

   FREE(ctx->Exec);
   FREE(ctx->Save);
}

/**
 * \brief Destroy a GLcontext structure.
 *
 * \param ctx GL context.
 * 
 * Calls _mesa_free_context_data() and free the structure.
 */
void
_mesa_destroy_context( GLcontext *ctx )
{
   if (ctx) {
      _mesa_free_context_data(ctx);
      FREE( (void *) ctx );
   }
}

#if _HAVE_FULL_GL
/**
 * \brief Copy attribute groups from one context to another.
 * 
 * \param src source context
 * \param dst destination context
 * \param mask bitwise OR of GL_*_BIT flags
 *
 * According to the bits specified in \p mask, copies the corresponding
 * attributes from \p src into \dst.  For many of the attributes a simple \c
 * memcpy is not enough due to the existence of internal pointers in their data
 * structures.
 */
void
_mesa_copy_context( const GLcontext *src, GLcontext *dst, GLuint mask )
{
   if (mask & GL_ACCUM_BUFFER_BIT) {
      /* OK to memcpy */
      dst->Accum = src->Accum;
   }
   if (mask & GL_COLOR_BUFFER_BIT) {
      /* OK to memcpy */
      dst->Color = src->Color;
   }
   if (mask & GL_CURRENT_BIT) {
      /* OK to memcpy */
      dst->Current = src->Current;
   }
   if (mask & GL_DEPTH_BUFFER_BIT) {
      /* OK to memcpy */
      dst->Depth = src->Depth;
   }
   if (mask & GL_ENABLE_BIT) {
      /* no op */
   }
   if (mask & GL_EVAL_BIT) {
      /* OK to memcpy */
      dst->Eval = src->Eval;
   }
   if (mask & GL_FOG_BIT) {
      /* OK to memcpy */
      dst->Fog = src->Fog;
   }
   if (mask & GL_HINT_BIT) {
      /* OK to memcpy */
      dst->Hint = src->Hint;
   }
   if (mask & GL_LIGHTING_BIT) {
      GLuint i;
      /* begin with memcpy */
      MEMCPY( &dst->Light, &src->Light, sizeof(struct gl_light) );
      /* fixup linked lists to prevent pointer insanity */
      make_empty_list( &(dst->Light.EnabledList) );
      for (i = 0; i < MAX_LIGHTS; i++) {
         if (dst->Light.Light[i].Enabled) {
            insert_at_tail(&(dst->Light.EnabledList), &(dst->Light.Light[i]));
         }
      }
   }
   if (mask & GL_LINE_BIT) {
      /* OK to memcpy */
      dst->Line = src->Line;
   }
   if (mask & GL_LIST_BIT) {
      /* OK to memcpy */
      dst->List = src->List;
   }
   if (mask & GL_PIXEL_MODE_BIT) {
      /* OK to memcpy */
      dst->Pixel = src->Pixel;
   }
   if (mask & GL_POINT_BIT) {
      /* OK to memcpy */
      dst->Point = src->Point;
   }
   if (mask & GL_POLYGON_BIT) {
      /* OK to memcpy */
      dst->Polygon = src->Polygon;
   }
   if (mask & GL_POLYGON_STIPPLE_BIT) {
      /* Use loop instead of MEMCPY due to problem with Portland Group's
       * C compiler.  Reported by John Stone.
       */
      GLuint i;
      for (i = 0; i < 32; i++) {
         dst->PolygonStipple[i] = src->PolygonStipple[i];
      }
   }
   if (mask & GL_SCISSOR_BIT) {
      /* OK to memcpy */
      dst->Scissor = src->Scissor;
   }
   if (mask & GL_STENCIL_BUFFER_BIT) {
      /* OK to memcpy */
      dst->Stencil = src->Stencil;
   }
   if (mask & GL_TEXTURE_BIT) {
      /* Cannot memcpy because of pointers */
      _mesa_copy_texture_state(src, dst);
   }
   if (mask & GL_TRANSFORM_BIT) {
      /* OK to memcpy */
      dst->Transform = src->Transform;
   }
   if (mask & GL_VIEWPORT_BIT) {
      /* Cannot use memcpy, because of pointers in GLmatrix _WindowMap */
      dst->Viewport.X = src->Viewport.X;
      dst->Viewport.Y = src->Viewport.Y;
      dst->Viewport.Width = src->Viewport.Width;
      dst->Viewport.Height = src->Viewport.Height;
      dst->Viewport.Near = src->Viewport.Near;
      dst->Viewport.Far = src->Viewport.Far;
      _math_matrix_copy(&dst->Viewport._WindowMap, &src->Viewport._WindowMap);
   }

   /* XXX FIXME:  Call callbacks?
    */
   dst->NewState = _NEW_ALL;
}
#endif


/**
 * \brief Set the current context, binding the given frame buffer to the context.
 *
 * \param newCtx new GL context.
 * \param buffer framebuffer.
 * 
 * Calls _mesa_make_current2() with \p buffer as read and write framebuffer.
 */
void
_mesa_make_current( GLcontext *newCtx, GLframebuffer *buffer )
{
   _mesa_make_current2( newCtx, buffer, buffer );
}

/**
 * \brief Bind the given context to the given draw-buffer and read-buffer and
 * make it the current context for this thread.
 *
 * \param newCtx new GL context. If NULL then there will be no current GL
 * context.
 * \param drawBuffer draw framebuffer.
 * \param readBuffer read framebuffer.
 * 
 * Check that the context's and framebuffer's visuals are compatible, returning
 * imediatly otherwise. Sets the glapi current context via
 * _glapi_set_context(). If \p newCtx is not NULL, associates \p drawBuffer and
 * \p readBuffer with it and calls dd_function_table::ResizeBuffers if the buffers size has changed. 
 * Calls dd_function_table::MakeCurrent callback if defined.
 *
 * When a context is bound by the first time and the \c MESA_INFO environment
 * variable is set it calls print_info() as an aid for remote user
 * troubleshooting.
 */
void
_mesa_make_current2( GLcontext *newCtx, GLframebuffer *drawBuffer,
                     GLframebuffer *readBuffer )
{
   if (MESA_VERBOSE)
      _mesa_debug(newCtx, "_mesa_make_current2()\n");

   /* Check that the context's and framebuffer's visuals are compatible.
    * We could do a lot more checking here but this'll catch obvious
    * problems.
    */
   if (newCtx && drawBuffer && readBuffer) {
      if (newCtx->Visual.rgbMode != drawBuffer->Visual.rgbMode ||
          newCtx->Visual.redBits != drawBuffer->Visual.redBits ||
          newCtx->Visual.depthBits != drawBuffer->Visual.depthBits ||
          newCtx->Visual.stencilBits != drawBuffer->Visual.stencilBits ||
          newCtx->Visual.accumRedBits != drawBuffer->Visual.accumRedBits) {
         return; /* incompatible */
      }
   }

   /* We call this function periodically (just here for now) in
    * order to detect when multithreading has begun.
    */
   _glapi_check_multithread();

   _glapi_set_context((void *) newCtx);
   ASSERT(_mesa_get_current_context() == newCtx);


   if (!newCtx) {
      _glapi_set_dispatch(NULL);  /* none current */
   }
   else {
      _glapi_set_dispatch(newCtx->CurrentDispatch);

      if (drawBuffer && readBuffer) {
	 /* TODO: check if newCtx and buffer's visual match??? */
	 newCtx->DrawBuffer = drawBuffer;
	 newCtx->ReadBuffer = readBuffer;
	 newCtx->NewState |= _NEW_BUFFERS;

         if (drawBuffer->Width == 0 && drawBuffer->Height == 0) {
            /* get initial window size */
            GLuint bufWidth, bufHeight;

            /* ask device driver for size of output buffer */
            (*newCtx->Driver.GetBufferSize)( drawBuffer, &bufWidth, &bufHeight );

            if (drawBuffer->Width != bufWidth || 
		drawBuffer->Height != bufHeight) {

	       drawBuffer->Width = bufWidth;
	       drawBuffer->Height = bufHeight;

 	       newCtx->Driver.ResizeBuffers( drawBuffer );
	    }
         }

         if (readBuffer != drawBuffer &&
             readBuffer->Width == 0 && readBuffer->Height == 0) {
            /* get initial window size */
            GLuint bufWidth, bufHeight;

            /* ask device driver for size of output buffer */
            (*newCtx->Driver.GetBufferSize)( readBuffer, &bufWidth, &bufHeight );

            if (readBuffer->Width != bufWidth ||
		readBuffer->Height != bufHeight) {

	       readBuffer->Width = bufWidth;
	       readBuffer->Height = bufHeight;

	       newCtx->Driver.ResizeBuffers( readBuffer );
	    }
         }
      }

      /* Alert the driver - usually passed on to the sw t&l module,
       * but also used to detect threaded cases in the radeon codegen
       * hw t&l module.
       */
      if (newCtx->Driver.MakeCurrent)
	 newCtx->Driver.MakeCurrent( newCtx, drawBuffer, readBuffer );

      /* We can use this to help debug user's problems.  Tell them to set
       * the MESA_INFO env variable before running their app.  Then the
       * first time each context is made current we'll print some useful
       * information.
       */
      if (newCtx->FirstTimeCurrent) {
	 if (_mesa_getenv("MESA_INFO")) {
	    _mesa_print_info();
	 }
	 newCtx->FirstTimeCurrent = GL_FALSE;
      }
   }
}

/**
 * \brief Get current context for the calling thread.
 * 
 * \return pointer to the current GL context.
 * 
 * Calls _glapi_get_context(). This isn't the fastest way to get the current
 * context.  If you need speed, see the #GET_CURRENT_CONTEXT macro in context.h.
 */
GLcontext *
_mesa_get_current_context( void )
{
   return (GLcontext *) _glapi_get_context();
}

/**
 * \brief Get context's current API dispatch table.
 *
 * It'll either be the immediate-mode execute dispatcher or the display list
 * compile dispatcher.
 * 
 * \param ctx GL context.
 *
 * \return pointer to dispatch_table.
 *
 * Simply returns __GLcontextRec::CurrentDispatch.
 */
struct _glapi_table *
_mesa_get_dispatch(GLcontext *ctx)
{
   return ctx->CurrentDispatch;
}

/*@}*/


/**********************************************************************/
/** \name Miscellaneous functions                                     */
/**********************************************************************/
/*@{*/

/**
 * \brief Record an error.
 *
 * \param ctx GL context.
 * \param error error code.
 * 
 * Records the given error code and call the driver's dd_function_table::Error
 * function if defined.
 *
 * \sa
 * This is called via _mesa_error().
 */
void
_mesa_record_error( GLcontext *ctx, GLenum error )
{
   if (!ctx)
      return;

   if (ctx->ErrorValue == GL_NO_ERROR) {
      ctx->ErrorValue = error;
   }

   /* Call device driver's error handler, if any.  This is used on the Mac. */
   if (ctx->Driver.Error) {
      (*ctx->Driver.Error)( ctx );
   }
}

/**
 * \brief Execute glFinish().
 *
 * Calls the #ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH macro and the
 * dd_function_table::Finish driver callback, if not NULL.
 */
void
_mesa_Finish( void )
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);
   if (ctx->Driver.Finish) {
      (*ctx->Driver.Finish)( ctx );
   }
}

/**
 * \brief Execute glFlush().
 *
 * Calls the #ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH macro and the
 * dd_function_table::Flush driver callback, if not NULL.
 */
void
_mesa_Flush( void )
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);
   if (ctx->Driver.Flush) {
      (*ctx->Driver.Flush)( ctx );
   }
}


/*@}*/
