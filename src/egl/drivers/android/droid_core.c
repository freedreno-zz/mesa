/*
 * Copyright © 2010 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Kristian Høgsberg <krh@bitplanet.net>
 */

#include "droid.h"

static _EGLContext *
droid_create_context(_EGLDriver *drv, _EGLDisplay *disp, _EGLConfig *conf,
		    _EGLContext *share_list, const EGLint *attrib_list)
{
   struct droid_egl_context *dctx;
   struct droid_egl_display *ddpy = droid_egl_display(disp);
   struct droid_egl_context *dctx_shared = droid_egl_context(share_list);
   struct droid_egl_config *dconf = droid_egl_config(conf);
   const __DRIconfig *dri_config;
   int api;

   (void) drv;

   dctx = calloc(1, sizeof *dctx);
   if (!dctx) {
      _eglError(EGL_BAD_ALLOC, "eglCreateContext");
      return NULL;
   }

   if (!_eglInitContext(&dctx->base, disp, conf, attrib_list))
      goto cleanup;

   switch (dctx->base.ClientAPI) {
   case EGL_OPENGL_ES_API:
      switch (dctx->base.ClientVersion) {
      case 1:
         api = __DRI_API_GLES;
         break;
      case 2:
         api = __DRI_API_GLES2;
         break;
      default:
	 _eglError(EGL_BAD_PARAMETER, "eglCreateContext");
	 return NULL;
      }
      break;
   case EGL_OPENGL_API:
      api = __DRI_API_OPENGL;
      break;
   default:
      _eglError(EGL_BAD_PARAMETER, "eglCreateContext");
      return NULL;
   }

   if (conf != NULL)
      dri_config = dconf->dri_config;
   else
      dri_config = NULL;

   if (ddpy->dri2->base.version >= 2) {
      dctx->dri_context =
	 ddpy->dri2->createNewContextForAPI(ddpy->dri_screen,
						api,
						dri_config,
						dctx_shared ? 
						dctx_shared->dri_context : NULL,
						dctx);
   } else if (api == __DRI_API_OPENGL) {
      dctx->dri_context =
	 ddpy->dri2->createNewContext(ddpy->dri_screen,
					  dconf->dri_config,
					  dctx_shared ? 
					  dctx_shared->dri_context : NULL,
					  dctx);
   } else {
      /* fail */
   }

   if (!dctx->dri_context)
      goto cleanup;

   return &dctx->base;

 cleanup:
   free(dctx);
   return NULL;
}

static _EGLSurface *
droid_create_surface(_EGLDriver *drv, _EGLDisplay *disp, EGLint type,
		    _EGLConfig *conf, EGLNativeWindowType window,
		    const EGLint *attrib_list)
{
   struct droid_egl_display *ddpy = droid_egl_display(disp);
   struct droid_egl_config *dconf = droid_egl_config(conf);
   struct droid_egl_surface *dsurf;
   int format, vis_type;

   (void) drv;

   if (!window || window->common.magic != ANDROID_NATIVE_WINDOW_MAGIC) {
      _eglError(EGL_BAD_NATIVE_WINDOW, "droid_create_surface");
      return NULL;
   }
   if (window->query(window, NATIVE_WINDOW_FORMAT, &format)) {
      _eglError(EGL_BAD_NATIVE_WINDOW, "droid_create_surface");
      return NULL;
   }

   vis_type = _eglGetConfigKey(&dconf->base, EGL_NATIVE_VISUAL_TYPE);
   if (format != vis_type) {
      _eglLog(_EGL_WARNING, "Native format mismatch: 0x%x != 0x%x",
            format, vis_type);
   }

   dsurf = calloc(1, sizeof *dsurf);
   if (!dsurf) {
      _eglError(EGL_BAD_ALLOC, "droid_create_surface");
      return NULL;
   }

   if (!_eglInitSurface(&dsurf->base, disp, type, conf, attrib_list))
      goto cleanup_surf;

   dsurf->dri_drawable =
      (*ddpy->dri2->createNewDrawable) (ddpy->dri_screen,
					    dconf->dri_config, dsurf);
   if (dsurf->dri_drawable == NULL) {
      _eglError(EGL_BAD_ALLOC, "dri2->createNewDrawable");
      goto cleanup_pixmap;
   }

   window->common.incRef(&window->common);
   window->query(window, NATIVE_WINDOW_WIDTH, &dsurf->base.Width);
   window->query(window, NATIVE_WINDOW_HEIGHT, &dsurf->base.Height);

   dsurf->window = window;

   return &dsurf->base;

 cleanup_dri_drawable:
   ddpy->core->destroyDrawable(dsurf->dri_drawable);
 cleanup_pixmap:
 cleanup_surf:
   free(dsurf);

   return NULL;
}

static _EGLSurface *
droid_create_window_surface(_EGLDriver *drv, _EGLDisplay *disp,
			   _EGLConfig *conf, EGLNativeWindowType window,
			   const EGLint *attrib_list)
{
   return droid_create_surface(drv, disp, EGL_WINDOW_BIT, conf,
			      window, attrib_list);
}

static _EGLSurface *
droid_create_pixmap_surface(_EGLDriver *drv, _EGLDisplay *disp,
			   _EGLConfig *conf, EGLNativePixmapType pixmap,
			   const EGLint *attrib_list)
{
   return NULL;
}

static _EGLSurface *
droid_create_pbuffer_surface(_EGLDriver *drv, _EGLDisplay *disp,
			    _EGLConfig *conf, const EGLint *attrib_list)
{
   return NULL;
}

static EGLBoolean
droid_destroy_surface(_EGLDriver *drv, _EGLDisplay *disp, _EGLSurface *surf)
{
   struct droid_egl_display *ddpy = droid_egl_display(disp);
   struct droid_egl_surface *dsurf = droid_egl_surface(surf);

   (void) drv;

   if (!_eglPutSurface(surf))
      return EGL_TRUE;

   (*ddpy->core->destroyDrawable)(dsurf->dri_drawable);

   droid_enqueue_buffer(dsurf);
   dsurf->window->common.decRef(&dsurf->window->common);

   free(surf);

   return EGL_TRUE;
}

static EGLBoolean
droid_make_current(_EGLDriver *drv, _EGLDisplay *disp, _EGLSurface *dsurf,
		  _EGLSurface *rsurf, _EGLContext *ctx)
{
   struct droid_egl_driver *ddrv = droid_egl_driver(drv);
   struct droid_egl_display *ddpy = droid_egl_display(disp);
   struct droid_egl_surface *droid_dsurf = droid_egl_surface(dsurf);
   struct droid_egl_surface *droid_rsurf = droid_egl_surface(rsurf);
   struct droid_egl_context *dctx = droid_egl_context(ctx);
   _EGLContext *old_ctx;
   _EGLSurface *old_dsurf, *old_rsurf;
   __DRIdrawable *ddraw, *rdraw;
   __DRIcontext *cctx;

   /* make new bindings */
   if (!_eglBindContext(ctx, dsurf, rsurf, &old_ctx, &old_dsurf, &old_rsurf))
      return EGL_FALSE;

   /* flush before context switch */
   if (old_ctx && ddrv->glFlush)
      ddrv->glFlush();

   ddraw = (droid_dsurf) ? droid_dsurf->dri_drawable : NULL;
   rdraw = (droid_rsurf) ? droid_rsurf->dri_drawable : NULL;
   cctx = (dctx) ? dctx->dri_context : NULL;

   if ((cctx == NULL && ddraw == NULL && rdraw == NULL) ||
       ddpy->core->bindContext(cctx, ddraw, rdraw)) {
      droid_destroy_surface(drv, disp, old_dsurf);
      droid_destroy_surface(drv, disp, old_rsurf);
      if (old_ctx) {
         /* unbind the old context only when there is no new context bound */
         if (!ctx) {
            __DRIcontext *old_cctx = droid_egl_context(old_ctx)->dri_context;
            ddpy->core->unbindContext(old_cctx);
         }
         /* no destroy? */
         _eglPutContext(old_ctx);
      }

      return EGL_TRUE;
   } else {
      /* undo the previous _eglBindContext */
      _eglBindContext(old_ctx, old_dsurf, old_rsurf, &ctx, &dsurf, &rsurf);
      assert(&dctx->base == ctx &&
             &droid_dsurf->base == dsurf &&
             &droid_rsurf->base == rsurf);

      _eglPutSurface(dsurf);
      _eglPutSurface(rsurf);
      _eglPutContext(ctx);

      _eglPutSurface(old_dsurf);
      _eglPutSurface(old_rsurf);
      _eglPutContext(old_ctx);

      return EGL_FALSE;
   }
}

static EGLBoolean
droid_swap_buffers(_EGLDriver *drv, _EGLDisplay *disp, _EGLSurface *draw)
{
   struct droid_egl_driver *ddrv = droid_egl_driver(drv);
   struct droid_egl_display *ddpy = droid_egl_display(disp);
   struct droid_egl_surface *dsurf = droid_egl_surface(draw);
   _EGLContext *ctx;

   if (ddrv->glFlush) {
      ctx = _eglGetCurrentContext();
      if (ctx && ctx->DrawSurface == &dsurf->base)
         ddrv->glFlush();
   }

   (*ddpy->flush->flush)(dsurf->dri_drawable);

   if (dsurf->buffer)
      droid_enqueue_buffer(dsurf);

   (*ddpy->flush->invalidate)(dsurf->dri_drawable);

   return EGL_TRUE;
}

static EGLBoolean
droid_wait_client(_EGLDriver *drv, _EGLDisplay *disp, _EGLContext *ctx)
{
   struct droid_egl_driver *ddrv = droid_egl_driver(drv);
   struct droid_egl_display *ddpy = droid_egl_display(disp);
   struct droid_egl_surface *dsurf = droid_egl_surface(ctx->DrawSurface);

   if (ddrv->glFinish)
      ddrv->glFinish();

   if (dsurf)
      (*ddpy->flush->flush)(dsurf->dri_drawable);

   return EGL_TRUE;
}

void
droid_init_core_functions(_EGLDriver *drv)
{
   struct droid_egl_driver *ddrv = droid_egl_driver(drv);

   ddrv->base.API.CreateContext = droid_create_context;
   ddrv->base.API.CreateWindowSurface = droid_create_window_surface;
   ddrv->base.API.CreatePixmapSurface = droid_create_pixmap_surface;
   ddrv->base.API.CreatePbufferSurface = droid_create_pbuffer_surface;
   ddrv->base.API.DestroySurface = droid_destroy_surface;
   ddrv->base.API.MakeCurrent = droid_make_current;
   ddrv->base.API.SwapBuffers = droid_swap_buffers;
   ddrv->base.API.WaitClient = droid_wait_client;
}
