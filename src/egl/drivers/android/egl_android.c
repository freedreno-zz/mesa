/*
 * Copyright (C) 2009 Chia-I Wu <olvaffe@gmail.com>
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#define LOG_TAG "DROID-EGL"
#include <utils/Log.h>

#include "glapi/glapi.h"

#include "eglconfig.h"
#include "eglcontext.h"
#include "egldisplay.h"
#include "egldriver.h"
#include "eglglobals.h"
#include "egllog.h"
#include "eglsurface.h"
#include "eglimage.h"

#include "droid.h"

#ifndef DROID_DEVICE_PATH
#define DROID_DEVICE_PATH "/dev/dri/card0"
#endif

struct droid_egl_driver
{
   _EGLDriver base;

   /* EGL_DEFAULT_DISPLAY */
   struct droid_egl_display *default_display;
   void (*flush_current)(void);
   void (*finish_current)(void);
};

struct droid_egl_display
{
   EGLint refcnt;

   EGLint apis;
   EGLint major;
   EGLint minor;

   struct droid_backend *backend;
   struct droid_screen *screen;
};

struct droid_egl_context {
   _EGLContext base;
   struct droid_context *context;
};

struct droid_egl_surface {
   _EGLSurface base;
   struct droid_drawable *drawable;
   struct droid_surface *surface;
};

struct droid_egl_image {
   _EGLImage base;
   struct droid_drawable *drawable;
   struct droid_surface *surface;
};

struct droid_egl_config {
   _EGLConfig base;
   const __DRIconfig *config;
};

static INLINE struct droid_egl_driver *
lookup_driver(_EGLDriver *drv)
{
   return (struct droid_egl_driver *) drv;
}

static INLINE struct droid_egl_display *
lookup_display(_EGLDisplay *dpy)
{
   return (struct droid_egl_display *) dpy->DriverData;
}

static INLINE struct droid_egl_context *
lookup_context(_EGLContext *context)
{
   return (struct droid_egl_context *) context;
}

static INLINE struct droid_egl_surface *
lookup_surface(_EGLSurface *surface)
{
   return (struct droid_egl_surface *) surface;
}

static INLINE struct droid_egl_image *
lookup_image(_EGLImage *image)
{
   return (struct droid_egl_image *) image;
}

static INLINE struct droid_egl_config *
lookup_config(_EGLConfig *conf)
{
   return (struct droid_egl_config *) conf;
}

static void
droid_create_configs(_EGLDisplay *dpy, struct droid_egl_display *droid_dpy,
                     const __DRIconfig **configs, EGLint num_configs)
{
   EGLint i;
   EGLint id = 1;

   for (i = 0; i < num_configs; i++) {
      struct droid_egl_config *droid_conf = calloc(1, sizeof(*droid_conf));
      EGLint val;

      if (!droid_conf)
         break;

      _eglInitConfig(&droid_conf->base, id);
      droid_conf->config = configs[i];
      if (!droid_screen_convert_config(droid_dpy->screen, droid_conf->config,
                                       &droid_conf->base)) {
         free(droid_conf);
         continue;
      }

      val = GET_CONFIG_ATTRIB(&droid_conf->base, EGL_CONFIG_CAVEAT);
      /* we do not want slow configs */
      if (val == EGL_SLOW_CONFIG) {
         free(droid_conf);
      } else {
         _eglAddConfig(dpy, &droid_conf->base);
         id++;
      }
   }
}


static EGLBoolean
droid_initialize_display(struct droid_egl_display *droid_dpy)
{
   const char *path = DROID_DEVICE_PATH;

   droid_dpy->backend = droid_backend_create_intel(path);
   if (!droid_dpy->backend)
      return EGL_FALSE;

   droid_dpy->screen = droid_screen_create(droid_dpy->backend);
   if (!droid_dpy->screen) {
      free(droid_dpy->backend);
      droid_dpy->backend = NULL;
      return EGL_FALSE;
   }

   droid_dpy->apis = EGL_OPENGL_ES_BIT;
   droid_dpy->major = 1;
   droid_dpy->major = 4;

   return EGL_TRUE;
}

static EGLBoolean
droid_eglInitialize(_EGLDriver *drv, _EGLDisplay *dpy,
                    EGLint *major, EGLint *minor)
{
   struct droid_egl_driver *droid_drv = lookup_driver(drv);
   struct droid_egl_display *droid_dpy;

   if (dpy->NativeDisplay != EGL_DEFAULT_DISPLAY)
      return _eglError(EGL_NOT_INITIALIZED, "eglInitialize");

   /* the default display */
   droid_dpy = droid_drv->default_display;
   if (!droid_dpy) {
      droid_dpy = calloc(1, sizeof(*droid_dpy));
      if (!droid_dpy)
         return _eglError(EGL_BAD_ALLOC, "eglInitialize");
      if (!droid_initialize_display(droid_dpy))
         return _eglError(EGL_NOT_INITIALIZED, "eglInitialize");

      droid_create_configs(dpy, droid_dpy, droid_dpy->screen->dri_configs,
                           droid_dpy->screen->num_dri_configs);

#if EGL_KHR_image_base
      if (droid_dpy->backend->create_image_surface) {
         dpy->Extensions.KHR_image = EGL_TRUE;
         dpy->Extensions.KHR_image_base = EGL_TRUE;
         dpy->Extensions.KHR_image_pixmap = EGL_TRUE;
      }
#endif

      droid_drv->default_display = droid_dpy;
   }

   dpy->DriverData = (void *) droid_dpy;
   droid_dpy->refcnt++;

   *major = droid_dpy->major;
   *minor = droid_dpy->minor;

   return EGL_TRUE;
}

static EGLBoolean
droid_eglTerminate(_EGLDriver *drv, _EGLDisplay *dpy)
{
   struct droid_egl_driver *droid_drv = lookup_driver(drv);
   struct droid_egl_display *droid_dpy = lookup_display(dpy);

   dpy->DriverData = NULL;
   droid_dpy->refcnt--;
   if (!droid_dpy->refcnt) {
      _eglReleaseDisplayResources(drv, dpy);
      _eglCleanupDisplay(dpy);

      free(droid_dpy);
      droid_drv->default_display = NULL;
   }

   return EGL_TRUE;
}

static _EGLProc
droid_eglGetProcAddress(const char *procname)
{
   return (_EGLProc) _glapi_get_proc_address(procname);
}

static _EGLContext *
droid_eglCreateContext(_EGLDriver *drv, _EGLDisplay *dpy, _EGLConfig *conf,
                       _EGLContext *share_list, const EGLint *attrib_list)
{
   struct droid_egl_display *droid_dpy = lookup_display(dpy);
   struct droid_egl_config *droid_conf = lookup_config(conf);
   struct droid_egl_context *shared = lookup_context(share_list);
   struct droid_egl_context *ctx;

   ctx = calloc(1, sizeof(*ctx));
   if (!ctx) {
      _eglError(EGL_BAD_ALLOC, "eglCreateContext");
      return NULL;
   }

   if (!_eglInitContext(drv, &ctx->base, &droid_conf->base, attrib_list)) {
      free(ctx);
      return NULL;
   }

   ctx->context =
      droid_screen_create_context(droid_dpy->screen, droid_conf->config,
                                  (shared) ? shared->context : NULL);
   if (!ctx->context) {
      free(ctx);
      return NULL;
   }

   return &ctx->base;
}

static EGLBoolean
droid_eglDestroyContext(_EGLDriver *drv, _EGLDisplay *dpy, _EGLContext *ctx)
{
   struct droid_egl_display *droid_dpy = lookup_display(dpy);
   struct droid_egl_context *droid_ctx = lookup_context(ctx);

   if (!_eglIsContextBound(ctx))
      droid_screen_destroy_context(droid_dpy->screen, droid_ctx->context);

   return EGL_TRUE;
}

static EGLBoolean
droid_eglMakeCurrent(_EGLDriver *drv, _EGLDisplay *dpy, _EGLSurface *d,
                     _EGLSurface *r, _EGLContext *ctx)
{
   struct droid_egl_driver *droid_drv = lookup_driver(drv);
   struct droid_egl_display *droid_dpy = lookup_display(dpy);
   struct droid_egl_surface *draw = lookup_surface(d);
   struct droid_egl_surface *read = lookup_surface(r);
   struct droid_egl_context *droid_ctx = lookup_context(ctx);
   _EGLContext *old;
   struct droid_egl_context *droid_old;

   old = _eglGetCurrentContext();
   /* an unlinked context will be invalid after context switch */
   if (!_eglIsContextLinked(old))
      old = NULL;

   droid_old = lookup_context(old);

   if (!_eglMakeCurrent(drv, dpy, d, r, ctx))
      return EGL_FALSE;

   if (droid_old && droid_old != droid_ctx && droid_drv->flush_current)
      droid_drv->flush_current();

   _glapi_check_multithread();

   /* bind new context or unbind old one */
   if (droid_ctx)
      droid_screen_bind_context(droid_dpy->screen,
                                draw->drawable, read->drawable,
                                droid_ctx->context);
   else if (droid_old)
      droid_screen_bind_context(droid_dpy->screen,
                                NULL, NULL,
                                droid_old->context);

   return EGL_TRUE;
}

static _EGLSurface *
droid_eglCreateWindowSurface(_EGLDriver *drv, _EGLDisplay *dpy, _EGLConfig *conf,
                             NativeWindowType window, const EGLint *attrib_list)
{
   struct droid_egl_display *droid_dpy = lookup_display(dpy);
   struct droid_egl_config *droid_conf = lookup_config(conf);
   struct droid_egl_surface *surf;

   surf = calloc(1, sizeof(*surf));
   if (!surf) {
      _eglError(EGL_BAD_ALLOC, "eglCreateWindowSurface");
      return NULL;
   }

   if (!_eglInitSurface(drv, &surf->base, EGL_WINDOW_BIT, &droid_conf->base, attrib_list)) {
      free(surf);
      return NULL;
   }

   surf->surface =
      droid_dpy->backend->create_window_surface(droid_dpy->backend,
                                                &surf->base, window);
   if (!surf->surface) {
      free(surf);
      return NULL;
   }

   surf->drawable = droid_screen_create_drawable(droid_dpy->screen,
                                                 droid_conf->config,
                                                 surf->surface);
   if (!surf->drawable) {
      droid_dpy->backend->destroy_surface(droid_dpy->backend, surf->surface);
      free(surf);
      return NULL;
   }

   return &surf->base;
}

static EGLBoolean
droid_eglDestroySurface(_EGLDriver *drv, _EGLDisplay *dpy, _EGLSurface *surf)
{
   struct droid_egl_display *droid_dpy = lookup_display(dpy);
   struct droid_egl_surface *droid_surf = lookup_surface(surf);

   if (_eglIsSurfaceBound(&droid_surf->base))
      return EGL_TRUE;

   droid_screen_destroy_drawable(droid_dpy->screen, droid_surf->drawable);
   droid_dpy->backend->destroy_surface(droid_dpy->backend, droid_surf->surface);
   free(droid_surf);

   return EGL_TRUE;
}

static EGLBoolean
droid_eglSwapBuffers(_EGLDriver *drv, _EGLDisplay *dpy, _EGLSurface *surf)
{
   struct droid_egl_driver *droid_drv = lookup_driver(drv);
   struct droid_egl_display *droid_dpy = lookup_display(dpy);
   struct droid_egl_surface *droid_surf = lookup_surface(surf);
   _EGLContext *ctx = _eglGetCurrentContext();
   struct droid_egl_context *droid_ctx = lookup_context(ctx);

   if (droid_ctx) {
      if (droid_drv->flush_current)
         droid_drv->flush_current();

      droid_screen_swap_buffers(droid_dpy->screen,
                                droid_ctx->context,
                                droid_surf->drawable);
   }

   return EGL_TRUE;
}

#if EGL_KHR_image_base

static _EGLImage *
droid_eglCreateImageKHR(_EGLDriver *drv, _EGLDisplay *dpy, _EGLContext *ctx,
                       EGLenum target, EGLClientBuffer buffer, const EGLint *attr_list)
{
   struct droid_egl_display *droid_dpy = lookup_display(dpy);
   struct droid_egl_image *droid_img;
   const __DRIconfig *dri_conf;
   int depth;

   if (target != EGL_NATIVE_PIXMAP_KHR || ctx) {
      _eglError(EGL_BAD_PARAMETER, "eglCreateImageKHR");
      return NULL;
   }

   droid_img = calloc(1, sizeof(*droid_img));
   if (!droid_img) {
      _eglError(EGL_BAD_ALLOC, "eglCreateImageKHR");
      return NULL;
   }

   if (!_eglInitImage(drv, &droid_img->base, attr_list)) {
      free(droid_img);
      return NULL;
   }

   droid_img->surface = 
      droid_dpy->backend->create_image_surface(droid_dpy->backend,
                                               (NativePixmapType) buffer,
                                               &depth);
   if (!droid_img->surface) {
      free(droid_img);
      return NULL;
   }

   dri_conf = droid_dpy->screen->image_configs[depth];
   if (!dri_conf) {
      droid_dpy->backend->destroy_surface(droid_dpy->backend,
                                          droid_img->surface);
      free(droid_img);
      return NULL;
   }

   droid_img->drawable =
      droid_screen_create_drawable(droid_dpy->screen, dri_conf,
                                   droid_img->surface);

   if (!droid_img->drawable) {
      droid_dpy->backend->destroy_surface(droid_dpy->backend,
                                          droid_img->surface);
      free(droid_img);
      return NULL;
   }

   droid_img->base.ClientData =
      droid_screen_get_drawable_data(droid_dpy->screen, droid_img->drawable);

   return &droid_img->base;
}


static EGLBoolean
droid_eglDestroyImageKHR(_EGLDriver *drv, _EGLDisplay *dpy, _EGLImage *img)
{
   struct droid_egl_display *droid_dpy = lookup_display(dpy);
   struct droid_egl_image *droid_img = lookup_image(img);

   droid_screen_destroy_drawable(droid_dpy->screen, droid_img->drawable);
   droid_dpy->backend->destroy_surface(droid_dpy->backend, droid_img->surface);
   free(droid_img);

   return EGL_TRUE;
}

#endif /* EGL_KHR_image_base */

static EGLBoolean
droid_eglWaitClient(_EGLDriver *drv, _EGLDisplay *dpy)
{
   struct droid_egl_driver *droid_drv = lookup_driver(drv);
   _EGLContext *ctx = _eglGetCurrentContext();

   if (!ctx || !droid_drv->finish_current)
      return EGL_TRUE;

   if (!_eglIsSurfaceLinked(ctx->DrawSurface))
      return _eglError(EGL_BAD_CURRENT_SURFACE, "eglWaitClient");

   droid_drv->finish_current();

   return EGL_TRUE;
}

static EGLBoolean
droid_eglWaitNative(_EGLDriver *drv, _EGLDisplay *dpy, EGLint engine)
{
   struct droid_egl_display *droid_dpy = lookup_display(dpy);
   _EGLContext *ctx = _eglGetCurrentContext();
   struct droid_egl_surface *droid_surf;

   if (engine != EGL_CORE_NATIVE_ENGINE)
      return _eglError(EGL_BAD_PARAMETER, "eglWaitNative");

   if (!ctx) 
      return EGL_TRUE;

   if (!_eglIsSurfaceLinked(ctx->DrawSurface))
      return _eglError(EGL_BAD_CURRENT_SURFACE, "eglWaitNative");

   droid_surf = lookup_surface(ctx->DrawSurface);
   droid_dpy->backend->swap_native_buffers(droid_dpy->backend,
                                           droid_surf->surface);

   return EGL_TRUE;
}

static void
droid_Unload(_EGLDriver *drv)
{
   struct droid_egl_driver *droid_drv = lookup_driver(drv);
   free(droid_drv);
}

static void
droid_Log(EGLint level, const char *msg)
{
   switch (level) {
   case _EGL_DEBUG:
      LOGD(msg);
      break;
   case _EGL_INFO:
      LOGI(msg);
      break;
   case _EGL_WARNING:
      LOGW(msg);
      break;
   case _EGL_FATAL:
      LOGE(msg);
      break;
   }
}

_EGLDriver *
_eglMain(const char *args)
{
   struct droid_egl_driver *droid_drv = calloc(1, sizeof(*droid_drv));
   if (!droid_drv)
      return NULL;

   _eglInitDriverFallbacks(&droid_drv->base);
   droid_drv->base.API.Initialize = droid_eglInitialize;
   droid_drv->base.API.Terminate = droid_eglTerminate;

   droid_drv->base.API.GetProcAddress = droid_eglGetProcAddress;

   droid_drv->base.API.CreateContext = droid_eglCreateContext;
   droid_drv->base.API.DestroyContext = droid_eglDestroyContext;
   droid_drv->base.API.MakeCurrent = droid_eglMakeCurrent;
   droid_drv->base.API.CreateWindowSurface = droid_eglCreateWindowSurface;
   droid_drv->base.API.DestroySurface = droid_eglDestroySurface;
   droid_drv->base.API.SwapBuffers = droid_eglSwapBuffers;
#if EGL_KHR_image_base
   droid_drv->base.API.CreateImageKHR = droid_eglCreateImageKHR;
   droid_drv->base.API.DestroyImageKHR = droid_eglDestroyImageKHR;
#endif /* EGL_KHR_image_base */
   droid_drv->base.API.WaitClient = droid_eglWaitClient;
   droid_drv->base.API.WaitNative = droid_eglWaitNative;

   droid_drv->base.Name = "Android/i915";
   droid_drv->base.Unload = droid_Unload;

   /* we need a way to flush commands */
   droid_drv->flush_current =
      (void (*)(void)) droid_eglGetProcAddress("glFlush");
   droid_drv->finish_current =
      (void (*)(void)) droid_eglGetProcAddress("glFinish");

   _eglSetLogProc(droid_Log);

   return &droid_drv->base;
}
