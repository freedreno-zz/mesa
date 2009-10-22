/*
 * Copyright (C) 2009 Chia-I Wu <olvaffe@gmail.com>
 *
 * This is based on the work of eagle, by
 * Copyright © 2008, 2009 Kristian Høgsberg
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

#define LOG_TAG "DROID-LOADER"
#include <utils/Log.h>

#include <string.h>
#include <errno.h>
#include <dlfcn.h>
#include <assert.h>

#include "droid.h"
#include "EGL/internal/eglimage_dri.h"

#ifndef DROID_DRIVER_PATH
#define DROID_DRIVER_PATH "/system/lib"
#endif

struct droid_loader {
   struct droid_backend *backend;

   char *filename;
   void *handle;

   __DRIcoreExtension *core;
   __DRIdri2Extension *dri2;
};

struct droid_context {
   __DRIcontext *dri_context;
};

struct droid_drawable {
   struct droid_loader *loader;
   struct droid_surface *surface;

   __DRIdrawable *dri_drawable;
   const __DRIconfig *dri_config;
   __DRIEGLImage *dri_image;
};

static __DRIbuffer *
loader_ext_get_buffers_with_format(__DRIdrawable *driDrawable,
                                   int *width, int *height,
                                   unsigned int *attachments, int count,
                                   int *out_count, void *loaderPrivate)
{
   struct droid_drawable *drawable = (struct droid_drawable *) loaderPrivate;
   struct droid_loader *loader = drawable->loader;
   __DRIbuffer *buffers;

   buffers = loader->backend->get_surface_buffers(loader->backend,
                                                  drawable->surface,
                                                  width, height,
                                                  attachments, count,
                                                  out_count, 1);

   return buffers;
}

static const __DRIdri2LoaderExtension loader_ext_dri2_loader = {
   { __DRI_DRI2_LOADER, __DRI_DRI2_LOADER_VERSION },
   NULL,
   NULL,
   loader_ext_get_buffers_with_format,
};

static int
loader_ext_get_ust(int64_t *ust)
{
   struct timeval tv;

   if (ust == NULL)
      return -EFAULT;

   if (gettimeofday(&tv, NULL) == 0) {
      ust[0] = (tv.tv_sec * 1000000) + tv.tv_usec;
      return 0;
   } else {
      return -errno;
   }
}

static const __DRIsystemTimeExtension loader_ext_system_time = {
   { __DRI_SYSTEM_TIME, __DRI_SYSTEM_TIME_VERSION },
   loader_ext_get_ust,
   NULL,
};

static const __DRIextension *loader_extensions[] = {
   &loader_ext_dri2_loader.base,
   &loader_ext_system_time.base,
   NULL
};

static struct droid_loader *
loader_create(struct droid_backend *backend)
{
   struct droid_loader *loader;

   loader = calloc(1, sizeof(*loader));
   if (!loader)
      return NULL;

   loader->backend = backend;

   return loader;
}

static void
loader_destroy(struct droid_loader *loader)
{
   if (loader->filename)
      free(loader->filename);
   if (loader->handle)
      dlclose(loader->handle);
   free(loader);
}

static int
loader_load(struct droid_loader *loader, const char *filename)
{
   const __DRIextension **extensions;
   const char *path = NULL;
   int i;

   LOGD("Loading DRI driver %s", filename);

   loader->handle = dlopen(filename, RTLD_NOW | RTLD_LOCAL);
   if (loader->handle == NULL) {
      LOGE("dlopen: %s", dlerror());
      return 0;
   }

   extensions = dlsym(loader->handle, __DRI_DRIVER_EXTENSIONS);
   if (extensions == NULL) {
      LOGE("dlsym: %s", dlerror());
      dlclose(loader->handle);
      loader->handle = NULL;
      return 0;
   }

   for (i = 0; extensions[i]; i++) {
      if (strcmp(extensions[i]->name, __DRI_CORE) == 0 &&
          extensions[i]->version >= __DRI_CORE_VERSION) {
         loader->core = (__DRIcoreExtension *) extensions[i];
      }

      if (strcmp(extensions[i]->name, __DRI_DRI2) == 0 &&
          extensions[i]->version >= __DRI_DRI2_VERSION) {
         loader->dri2 = (__DRIdri2Extension *) extensions[i];
      }
   }

   if (loader->core == NULL || loader->dri2 == NULL) {
      LOGE("missing required DRI extensions");
      dlclose(loader->handle);
      loader->handle = NULL;
      return 0;
   }

   return 1;
}

static int
loader_init(struct droid_loader *loader)
{
   char filename[1024];
   const char *path;

   path = DROID_DRIVER_PATH;
   snprintf(filename, sizeof(filename), "%s/%s_dri.so",
            path, loader->backend->driver_name);

   if (!loader_load(loader, filename))
      return 0;

   loader->filename = strdup(filename);

   return 1;
}

void
droid_backend_destroy(struct droid_backend *backend)
{
   backend->destroy(backend);
}

static void
screen_find_image_configs(struct droid_screen *screen)
{
   struct droid_loader *loader = screen->loader;
   int depth, i;

   for (depth = 0; depth < DROID_MAX_IMAGE_DEPTH + 1; depth++) {
      for (i = 0; i < screen->num_dri_configs; i++) {
         const __DRIconfig *conf = screen->dri_configs[i];
         _EGLConfig egl_conf;
         EGLint rgba, val;

         droid_screen_convert_config(screen, conf, &egl_conf);

         val = GET_CONFIG_ATTRIB(&egl_conf, EGL_CONFIG_CAVEAT);
         if (val == EGL_SLOW_CONFIG)
            continue;

         rgba  = GET_CONFIG_ATTRIB(&egl_conf, EGL_RED_SIZE);
         rgba += GET_CONFIG_ATTRIB(&egl_conf, EGL_GREEN_SIZE);
         rgba += GET_CONFIG_ATTRIB(&egl_conf, EGL_BLUE_SIZE);
         rgba += GET_CONFIG_ATTRIB(&egl_conf, EGL_ALPHA_SIZE);
         if (depth != rgba)
            continue;

         if (depth == 32) {
            val = GET_CONFIG_ATTRIB(&egl_conf, EGL_BIND_TO_TEXTURE_RGBA);
            if (val) {
               screen->image_configs[depth] = conf;
               break;
            }
         }

         val = GET_CONFIG_ATTRIB(&egl_conf, EGL_BIND_TO_TEXTURE_RGB);
         if (val) {
            screen->image_configs[depth] = conf;
            break;
         }
      }
   }
}

struct droid_screen *
droid_screen_create(struct droid_backend *backend)
{
   struct droid_screen *screen = NULL;
   struct droid_loader *loader;
   const __DRIextension **extensions;
   int fd, screen_number;
   int i;

   loader = loader_create(backend);
   if (!loader || !loader_init(loader)) {
      LOGE("failed to initialize loader");
      goto fail;
   }

   screen = calloc(1, sizeof(*screen));
   if (!screen) {
      LOGE("failed to allocate new screen");
      goto fail;
   }

   if (!loader->backend->initialize(loader->backend, &fd, &screen_number)) {
      LOGE("failed to initialize backend");
      goto fail;
   }

   screen->loader = loader;
   screen->dri_screen =
      loader->dri2->createNewScreen(screen_number, fd,
                                    loader_extensions,
                                    &screen->dri_configs, NULL);
   if (!screen->dri_screen) {
      LOGE("failed to create DRI screen");
      goto fail;
   }

   extensions = loader->core->getExtensions(screen->dri_screen);

   for (i = 0; extensions && extensions[i]; i++) {
      if (strcmp(extensions[i]->name, __DRI_TEX_BUFFER) == 0 &&
          extensions[i]->version >= __DRI_TEX_BUFFER_VERSION)
         screen->tex_buffer = (__DRItexBufferExtension *) extensions[i];

      if (strcmp(extensions[i]->name, __DRI_COPY_BUFFER) == 0 &&
          extensions[i]->version >= __DRI_COPY_BUFFER_VERSION)
         screen->copy_buffer = (__DRIcopyBufferExtension *) extensions[i];
   }

   if (!screen->tex_buffer) {
      LOGE("DRI driver has no TexBuffer extension");
      goto fail;
   }

   if (!screen->tex_buffer) {
      LOGE("DRI driver has no CopyBuffer extension");
      goto fail;
   }

   for (i = 0; screen->dri_configs[i]; i++)
      ;
   screen->num_dri_configs = i;

   screen_find_image_configs(screen);

   return screen;

fail:
   if (screen)
      droid_screen_destroy(screen);
   if (loader)
      loader_destroy(loader);

   return NULL;
}

void
droid_screen_destroy(struct droid_screen *screen)
{
   struct droid_loader *loader = screen->loader;
   if (screen->dri_screen)
      loader->core->destroyScreen(screen->dri_screen);
   free(screen);
}

static const struct {
   EGLenum egl_attrib;
   unsigned int dri_attrib;
} droid_attrib_map[] = {
   { EGL_BUFFER_SIZE,              __DRI_ATTRIB_BUFFER_SIZE },
   { EGL_RED_SIZE,                 __DRI_ATTRIB_RED_SIZE },
   { EGL_GREEN_SIZE,               __DRI_ATTRIB_GREEN_SIZE },
   { EGL_BLUE_SIZE,                __DRI_ATTRIB_BLUE_SIZE },
   { EGL_ALPHA_SIZE,               __DRI_ATTRIB_ALPHA_SIZE },
   { EGL_BIND_TO_TEXTURE_RGB,      __DRI_ATTRIB_BIND_TO_TEXTURE_RGB },
   { EGL_BIND_TO_TEXTURE_RGBA,     __DRI_ATTRIB_BIND_TO_TEXTURE_RGBA },
   { EGL_CONFIG_CAVEAT,            __DRI_ATTRIB_CONFIG_CAVEAT },
   { EGL_DEPTH_SIZE,               __DRI_ATTRIB_DEPTH_SIZE },
   { EGL_LEVEL,                    __DRI_ATTRIB_LEVEL },
   { EGL_MAX_PBUFFER_WIDTH,        __DRI_ATTRIB_MAX_PBUFFER_WIDTH },
   { EGL_MAX_PBUFFER_HEIGHT,       __DRI_ATTRIB_MAX_PBUFFER_HEIGHT },
   { EGL_MAX_PBUFFER_PIXELS,       __DRI_ATTRIB_MAX_PBUFFER_PIXELS },
   { EGL_SAMPLE_BUFFERS,           __DRI_ATTRIB_SAMPLE_BUFFERS },
   { EGL_SAMPLES,                  __DRI_ATTRIB_SAMPLES },
   { EGL_STENCIL_SIZE,             __DRI_ATTRIB_STENCIL_SIZE },
};

void
droid_screen_convert_config(struct droid_screen *screen,
                            const __DRIconfig *conf, _EGLConfig *egl_conf)
{
   struct droid_loader *loader = screen->loader;
   const int num_attrs =
      sizeof(droid_attrib_map) / sizeof(droid_attrib_map[0]);
   int i;

   for (i = 0; i < num_attrs; i++) {
      unsigned int dri_attrib = droid_attrib_map[i].dri_attrib;
      unsigned int dri_value;
      EGLenum egl_attrib = droid_attrib_map[i].egl_attrib;
      EGLint egl_value;

      if (!loader->core->getConfigAttrib(conf, dri_attrib, &dri_value)) {
         LOGE("failed to get attribute %02d for %p", dri_attrib, conf);
         continue;
      }

      switch (egl_attrib) {
      case EGL_CONFIG_CAVEAT:
         if (dri_value & __DRI_ATTRIB_SLOW_BIT)
            egl_value = EGL_SLOW_CONFIG;
         else if  (dri_value & __DRI_ATTRIB_NON_CONFORMANT_CONFIG)
            egl_value = EGL_NON_CONFORMANT_CONFIG;
         else
            egl_value = EGL_NONE;
         break;
      default:
         egl_value = (EGLint) dri_value;
         break;
      }
      SET_CONFIG_ATTRIB(egl_conf, egl_attrib, egl_value);
   }
}

struct droid_context *
droid_screen_create_context(struct droid_screen *screen,
                            const __DRIconfig *conf,
                            struct droid_context *shared)
{
   struct droid_loader *loader = screen->loader;
   struct droid_context *ctx;

   ctx = calloc(1, sizeof(*ctx));
   if (!ctx) {
      LOGE("failed to allocate context");
      return NULL;
   }

   ctx->dri_context =
      loader->dri2->createNewContext(screen->dri_screen, conf,
                                     (shared) ? shared->dri_context : NULL,
                                     NULL);
   if (!ctx->dri_context) {
      LOGE("failed to create DRI context");
      free(ctx);
      return NULL;
   }

   return ctx;
}

void
droid_screen_destroy_context(struct droid_screen *screen,
                             struct droid_context *ctx)
{
   struct droid_loader *loader = screen->loader;
   loader->core->destroyContext(ctx->dri_context);
   free(ctx);
}

struct droid_drawable *
droid_screen_create_drawable(struct droid_screen *screen,
                             const __DRIconfig *conf,
                             struct droid_surface *surf)
{
   struct droid_loader *loader = screen->loader;
   struct droid_drawable *drawable;

   drawable = calloc(1, sizeof(*drawable));
   if (!drawable) {
      LOGE("failed to allocate drawable");
      return NULL;
   }

   /* needed in GetBuffers */
   drawable->loader = loader;
   drawable->surface = surf;
   drawable->dri_config = conf;

   drawable->dri_drawable =
      loader->dri2->createNewDrawable(screen->dri_screen,
                                      conf, (void *) drawable);
   if (!drawable->dri_drawable) {
      LOGE("failed to create DRI drawable");
      free(drawable);
      return NULL;
   }

   return drawable;
}

void *
droid_screen_get_drawable_data(struct droid_screen *screen,
                               struct droid_drawable *drawable)
{
   struct droid_loader *loader = screen->loader;
   __DRIEGLImage *img = drawable->dri_image;

   if (!img) {
      unsigned int val;

      img = calloc(1, sizeof(__DRIEGLImage));
      if (!img)
         return NULL;

      img->magic = __DRI_EGL_IMAGE_MAGIC;
      img->drawable = drawable->dri_drawable;
      img->level = 0;
      if (drawable->dri_config == screen->image_configs[32] &&
          loader->core->getConfigAttrib(drawable->dri_config,
                                        __DRI_ATTRIB_BIND_TO_TEXTURE_RGBA,
                                        &val))
         img->texture_format_rgba = val;

      drawable->dri_image = img;
   }

   return (void *) img;
}

void
droid_screen_destroy_drawable(struct droid_screen *screen,
                              struct droid_drawable *drawable)
{
   struct droid_loader *loader = screen->loader;
   if (drawable->dri_image)
      free(drawable->dri_image);
   loader->core->destroyDrawable(drawable->dri_drawable);
   free(drawable);
}

int
droid_screen_bind_context(struct droid_screen *screen,
                          struct droid_drawable *draw,
                          struct droid_drawable *read,
                          struct droid_context *ctx)
{
   struct droid_loader *loader = screen->loader;
   int ret = 0;

   if (ctx) {
      if (draw && read)
         ret = loader->core->bindContext(ctx->dri_context,
                                         draw->dri_drawable,
                                         read->dri_drawable);
      else if (!draw && !read)
         ret = loader->core->unbindContext(ctx->dri_context);
   }

   if (!ret)
      LOGE("failed to bind context %p", ctx);

   return ret;
}

int
droid_screen_swap_buffers(struct droid_screen *screen,
                          struct droid_context *ctx,
                          struct droid_drawable *drawable)
{
   struct droid_loader *loader = screen->loader;
   __DRIbuffer *native;
   int width, height;
   int err = 0;

   native = loader->backend->get_native_buffer(loader->backend,
                                               drawable->surface,
                                               &width, &height);

   /* copy from front buffer to native buffer */
   if (native)
      err = screen->copy_buffer->copyBuffer(ctx->dri_context, native, 0, 0,
                                            drawable->dri_drawable,
                                            __DRI_BUFFER_FRONT_LEFT, 0, 0,
                                            width, height);

   if (!err)
      loader->backend->swap_native_buffers(loader->backend, drawable->surface);

   return (!err);
}
