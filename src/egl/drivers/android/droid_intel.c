/*
 * Copyright (C) 2009 Chia-I Wu <olvaffe@gmail.com>
 *
 * This is based on the work of eagle, by
 * Copyright © 2008, 2009 Kristian Høgsberg
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#define LOG_TAG "DROID-INTEL"
#include <utils/Log.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <i915_drm.h>
#include <GL/gl.h> /* dri_interface.h uses some GL integer types... */
#include <GL/internal/dri_interface.h>
#include <EGL/egl.h>

#include "droid.h"
#include "droid_ui.h"

#define INTEL_IS_I965(x) ((x) & INTEL_GEN_4)
#define INTEL_IS_I915(x) ((x) & INTEL_GEN_3)
#define INTEL_IS_I9xx(x) ((x) & (INTEL_GEN_3 | INTEL_GEN_4))
#define INTEL_IS_I8xx(x) ((x) & (INTEL_GEN_1 | INTEL_GEN_2))

#define INTEL_HAS_128_BYTE_Y_TILING(x) \
   (((x) & (INTEL_GEN_3 | INTEL_GEN_4 | INTEL_GEN_MINOR_MASK)) > INTEL_GEN_3)

enum {
   INTEL_SURFACE_TYPE_WINDOW,
   INTEL_SURFACE_TYPE_IMAGE,
};

/* Look at xf86-video-intel/src/common.h for the full horror of device
 * identification.
 */
enum {
	INTEL_GEN_1  = 0x10,
	INTEL_GEN_2  = 0x20,
	INTEL_GEN_3  = 0x40,
	INTEL_GEN_31 = 0x41,
	INTEL_GEN_4  = 0x80,

	INTEL_GEN_MAJOR_MASK = 0xf0,
	INTEL_GEN_MINOR_MASK = 0x0f,
};

struct droid_backend_intel {
   struct droid_backend base;
   int fd;
   int screen_number;

   uint32_t generation;
   int pitch_align;
   int enable_tiling;
};

struct droid_surface_intel {
   int type;
   union {
      NativeWindowType win;
      NativePixmapType pix;
   } native;
   __DRIbuffer native_buffer;
   unsigned int native_width, native_height;
   int native_changed;

   unsigned int attachments[20];
   __DRIbuffer buffers[10];
   uint32_t handles[10];
   int num_buffers;
   int depth_idx;

   _EGLSurface *surf;
};

static INLINE struct droid_backend_intel *
lookup_backend(struct droid_backend *backend)
{
   return (struct droid_backend_intel *) backend;
}

static INLINE struct droid_surface_intel *
lookup_surface(struct droid_surface *surface)
{
   return (struct droid_surface_intel *) surface;
}

static __DRIbuffer *
intel_get_native_buffer(struct droid_backend *backend,
                        struct droid_surface *surf,
                        int *width, int *height)
{
   struct droid_surface_intel *isurf = lookup_surface(surf);

   /* non-window surface is single-buffered */
   if (isurf->type != INTEL_SURFACE_TYPE_WINDOW)
      return NULL;

   if (!isurf->native_buffer.name)
      return NULL;

   if (width)
      *width = isurf->native_width;
   if (height)
      *height = isurf->native_height;

   return &isurf->native_buffer;
}

static INLINE uint32_t
align_to(uint32_t value, uint32_t align)
{
   return (value + align - 1) & ~(align - 1);
}

static INLINE int
fence_pitch(struct droid_backend *backend, int pitch, int tiling)
{
   struct droid_backend_intel *intel = lookup_backend(backend);
   int pitch_align, tile_width;

   switch (tiling) {
   case I915_TILING_NONE:
   default:
      pitch_align = intel->pitch_align;
      tile_width = 1; /* not used */
      break;
   case I915_TILING_X:
      pitch_align = 512;
      tile_width = 512;
      break;
   case I915_TILING_Y:
      pitch_align = 512;
      tile_width =
         (INTEL_HAS_128_BYTE_Y_TILING(intel->generation)) ? 128 : 512;
      break;
   }

   pitch = align_to(pitch, pitch_align);
   if (tiling == I915_TILING_NONE)
      return pitch;

   /* 965+ just needs multiples of tile width */
   if (INTEL_IS_I965(intel->generation)) {
      pitch = align_to(pitch,  tile_width);
   }
   else {
      /* Pre-965 needs power of two tile widths */
      while (tile_width < pitch)
         tile_width <<= 1;
      pitch = tile_width;
   }

   return pitch;
}

static INLINE uint32_t
fence_size(struct droid_backend *backend, int height, int pitch, int tiling)
{
   struct droid_backend_intel *intel = lookup_backend(backend);
   int height_align;
   uint32_t size;

   switch (tiling) {
   case I915_TILING_NONE:
   default:
      /* Round the height up so that the GPU's access to a 2x2 aligned
       * subspan doesn't address an invalid page offset beyond the
       * end of the GTT.
       */
      height_align = 2;
      break;
   case I915_TILING_X:
      height_align = 8;
      break;
   case I915_TILING_Y:
      height_align = 32;
      break;
   }

   height = align_to(height, height_align);
   size = pitch * height;
   if (tiling == I915_TILING_NONE)
      return size;

   /* The 965 can have fences at any page boundary. */
   if (INTEL_IS_I965(intel->generation)) {
      size = align_to(size, 4096);
   }
   else {
      uint32_t fence;

      /* Align the size to a power of two greater than the smallest fence. */
      if (INTEL_IS_I9xx(intel->generation))
         fence = 1 << 20; /* 1 MiB */
      else
         fence = 1 << 19; /* 512 KiB */

      while (fence < size)
         fence <<= 1;

      size = fence;
   }

   return size;
}

static int
create_buffer(struct droid_backend *backend, __DRIbuffer *buffer,
              int width, int height, int cpp, int tiling)
{
   struct droid_backend_intel *intel = lookup_backend(backend);
   struct drm_i915_gem_create create;
   struct drm_gem_flink flink;

   buffer->pitch = fence_pitch(backend, width * cpp, tiling);
   create.size = fence_size(backend, height, buffer->pitch, tiling);
   if (ioctl(intel->fd, DRM_IOCTL_I915_GEM_CREATE, &create)) {
      LOGE("failed to create buffer");
      return 0;
   }

   if (tiling != I915_TILING_NONE) {
      struct drm_i915_gem_set_tiling set_tiling;

      memset(&set_tiling, 0, sizeof(set_tiling));
      set_tiling.handle = create.handle;
      set_tiling.tiling_mode = tiling;
      set_tiling.stride = buffer->pitch;

      if (ioctl(intel->fd, DRM_IOCTL_I915_GEM_SET_TILING, &set_tiling))
         LOGW("failed to enable tiling");
   }

   flink.handle = create.handle;
   if (ioctl(intel->fd, DRM_IOCTL_GEM_FLINK, &flink) < 0) {
      LOGE("failed to flink buffer");
      return 0;
   }

   buffer->name = flink.name;
   buffer->cpp = cpp;
   buffer->flags = 0;

   return create.handle;
}

static void
delete_buffers(struct droid_backend *backend, struct droid_surface *surf)
{
   struct droid_backend_intel *intel = lookup_backend(backend);
   struct droid_surface_intel *isurf = lookup_surface(surf);
   int i;

   for (i = 0; i < isurf->num_buffers; i++) {
      if (isurf->handles[i]) {
         struct drm_gem_close close;

         close.handle = isurf->handles[i];
         if (ioctl(intel->fd, DRM_IOCTL_GEM_CLOSE, &close) < 0)
            LOGE("failed to close bo %d", close.handle);
         isurf->handles[i] = 0;
      }
   }

   isurf->num_buffers = 0;
}

static __DRIbuffer *
intel_get_surface_buffers(struct droid_backend *backend,
                          struct droid_surface *surf,
                          int *width, int *height,
                          unsigned int *attachments, int count,
                          int *out_count, int has_format)
{
   struct droid_backend_intel *intel = lookup_backend(backend);
   struct droid_surface_intel *isurf = lookup_surface(surf);
   unsigned int att_size;
   __DRIbuffer buffers[10];
   uint32_t handles[10];
   int num = 0;

   if (count > 10) {
      LOGW("too many buffers requested");
      count = 10;
   }

   att_size = sizeof(attachments[0]) * count * ((has_format) ? 2 : 1);

   if (isurf->native_changed) {
      delete_buffers(backend, surf);
      isurf->native_changed = 0;
   }

   /* same buffers requested */
   if (isurf->num_buffers == count &&
       memcmp(isurf->attachments, attachments, att_size) == 0) {
      num = isurf->num_buffers;
      goto end;
   }
   memcpy(isurf->attachments, attachments, att_size);

   while (count-- > 0) {
      unsigned int att = *attachments++;
      unsigned int format = (has_format) ? *attachments++ : 0;
      unsigned int cpp = (format) ? format / 8 : isurf->native_buffer.cpp;
      __DRIbuffer *buf = NULL;
      int reuse;

      /* re-use buffer */
      for (reuse = 0; reuse < isurf->num_buffers; reuse++) {
         if (isurf->buffers[reuse].attachment == att) {
            if (isurf->buffers[reuse].cpp == cpp &&
                isurf->handles[reuse])
               buf = &isurf->buffers[reuse];
            break;
         }
      }

      if (0)
         LOGD("%s buffer %d: att %d cpp %d",
               (buf) ? "reuse" : "create", num, att, cpp);

      if (buf) {
         buffers[num] = isurf->buffers[reuse];
         handles[num] = isurf->handles[reuse];
         isurf->handles[reuse] = 0;
      }
      else {
         int tiling =
            (intel->enable_tiling) ? I915_TILING_X : I915_TILING_NONE;

         buffers[num].attachment = att;

         if (isurf->type == INTEL_SURFACE_TYPE_IMAGE &&
             att == __DRI_BUFFER_FRONT_LEFT) {
            /* return native buffer */
            buffers[num] = isurf->native_buffer;
            buffers[num].attachment = att;
            handles[num] = 0;
         } else {
            buffers[num].attachment = att;
            handles[num] = create_buffer(backend, &buffers[num],
                                         isurf->native_width,
                                         isurf->native_height,
                                         cpp,
                                         tiling);
         }
      }
      num++;
   }

   /* delete old buffers that are not re-used */
   delete_buffers(backend, surf);

   memcpy(isurf->buffers, buffers, sizeof(buffers[0]) * num);
   memcpy(isurf->handles, handles, sizeof(handles[0]) * num);
   isurf->num_buffers = num;

end:
   *out_count = num;
   *width = isurf->native_width;
   *height = isurf->native_height;

   return isurf->buffers;
}

static void
update_native_buffer(struct droid_surface *surf)
{
   struct droid_surface_intel *isurf = lookup_surface(surf);
   unsigned int name, cpp, pitch, width, height;

   switch (isurf->type) {
   case INTEL_SURFACE_TYPE_WINDOW:
      /* oem[0] always point to the buffer that a client is drawing to */
      name = isurf->native.win->oem[0];
      cpp = ui_bytes_per_pixel(isurf->native.win->format);
      pitch = isurf->native.win->stride * cpp;
      width = isurf->native.win->width;
      height = isurf->native.win->height;
      break;
   case INTEL_SURFACE_TYPE_IMAGE:
      name = isurf->native.pix->reserved;
      cpp = ui_bytes_per_pixel(isurf->native.pix->format);
      pitch = isurf->native.pix->stride * cpp;
      width = isurf->native.pix->width;
      height = isurf->native.pix->height;
      break;
   default:
      name = cpp = pitch = width = height = 0;
      break;
   }

   isurf->native_buffer.attachment = __DRI_BUFFER_FRONT_LEFT;
   isurf->native_buffer.name = name;
   isurf->native_buffer.cpp = cpp;
   isurf->native_buffer.pitch = pitch;
   isurf->native_buffer.flags = 0;

   isurf->native_width = width;
   isurf->native_height = height;

   isurf->native_changed = 1;
}

static struct droid_surface *
intel_create_window_surface(struct droid_backend *backend,
                            _EGLSurface *surf,
                            NativeWindowType win)
{
   struct droid_surface_intel *isurf;

   if (!win) {
      LOGE("invalid native window");
      _eglError(EGL_BAD_NATIVE_WINDOW, "eglCreateWindowSurface");
      return NULL;
   }

   /* TODO lift this limitation */
   if (!win->oem[0]) {
      LOGE("TODO support for non-gem based window");
      _eglError(EGL_BAD_NATIVE_WINDOW, "eglCreateWindowSurface");
      return NULL;
   }

   isurf = calloc(1, sizeof(*isurf));
   if (!isurf) {
      _eglError(EGL_BAD_ALLOC, "eglCreateWindowSurface");
      return NULL;
   }

   isurf->type = INTEL_SURFACE_TYPE_WINDOW;
   isurf->native.win = win;

   surf->Width = win->width;
   surf->Height = win->height;
   /* always back buffer */
   surf->RenderBuffer = EGL_BACK_BUFFER;

   isurf->surf = surf;

   update_native_buffer((struct droid_surface *) isurf);

   return (struct droid_surface *) isurf;
}

static struct droid_surface *
intel_create_image_surface(struct droid_backend *backend,
                           NativePixmapType pix, int *depth)
{
   struct droid_surface_intel *isurf;
   int cpp;

   if (!pix) {
      LOGE("invalid native pixmap");
      _eglError(EGL_BAD_NATIVE_PIXMAP, "eglCreateImage");
      return NULL;
   }

   /* TODO lift this limitation */
   if (!pix->reserved) {
      LOGE("TODO support for non-gem based pixmap");
      _eglError(EGL_BAD_NATIVE_PIXMAP, "eglCreateImage");
      return NULL;
   }

   cpp = ui_bytes_per_pixel(pix->format);
   if (cpp * 8 > DROID_MAX_IMAGE_DEPTH) {
      LOGE("pixmap of depth %d is not supported", cpp * 8);
      _eglError(EGL_BAD_NATIVE_PIXMAP, "eglCreateImage");
      return NULL;
   }

   isurf = calloc(1, sizeof(*isurf));
   if (!isurf) {
      _eglError(EGL_BAD_ALLOC, "eglCreateWindowSurface");
      return NULL;
   }

   isurf->type = INTEL_SURFACE_TYPE_IMAGE;
   isurf->native.pix = pix;

   update_native_buffer((struct droid_surface *) isurf);

   if (depth)
      *depth = cpp * 8;

   return (struct droid_surface *) isurf;
}

static void
intel_destroy_surface(struct droid_backend *backend, struct droid_surface *surf)
{
   struct droid_surface_intel *isurf = lookup_surface(surf);
   delete_buffers(backend, surf);
   free(isurf);
}

static void
intel_swap_native_buffers(struct droid_backend *backend,
                          struct droid_surface *surf)
{
   struct droid_surface_intel *isurf = lookup_surface(surf);

   if (isurf->type == INTEL_SURFACE_TYPE_WINDOW) {
      uint32_t flags;

      flags = isurf->native.win->swapBuffers(isurf->native.win);
      if (flags & EGL_NATIVES_FLAG_SIZE_CHANGED) {
         update_native_buffer(surf);
      } else {
         /* oem[0] is changed after buffer swap */
         isurf->native_buffer.name = isurf->native.win->oem[0];
      }
   }
}

static int
intel_initialize(struct droid_backend *backend, int *fd, int *screen_number)
{
   struct droid_backend_intel *intel = lookup_backend(backend);
   drm_auth_t auth;
   int err;

   err = ioctl(intel->fd, DRM_IOCTL_GET_MAGIC, &auth);
   if (!err)
      err = ui_auth_gpu(auth.magic);

   if (err) {
      LOGE("failed to authenticate");
      return 0;
   }

   if (fd)
      *fd = intel->fd;
   if (screen_number)
      *screen_number = intel->screen_number;

   return 1;
}

#include <assert.h>
static int
intel_process_config(struct droid_backend *backend, _EGLConfig *conf)
{
   int r, g, b, a;
   int surface_type;
   int format;

   r = GET_CONFIG_ATTRIB(conf, EGL_RED_SIZE);
   g = GET_CONFIG_ATTRIB(conf, EGL_GREEN_SIZE);
   b = GET_CONFIG_ATTRIB(conf, EGL_BLUE_SIZE);
   a = GET_CONFIG_ATTRIB(conf, EGL_ALPHA_SIZE);
   format = ui_get_rgb_format(r, g, b, a);

   if (format) {
      SET_CONFIG_ATTRIB(conf, EGL_NATIVE_VISUAL_TYPE, format);
      SET_CONFIG_ATTRIB(conf, EGL_SURFACE_TYPE,
                        EGL_WINDOW_BIT |
                        EGL_PIXMAP_BIT |
                        EGL_PBUFFER_BIT);
   }
   else {
      SET_CONFIG_ATTRIB(conf, EGL_SURFACE_TYPE, EGL_PBUFFER_BIT);
   }

   return 1;
}

static void
intel_destroy(struct droid_backend *backend)
{
   struct droid_backend_intel *intel = lookup_backend(backend);
   close(intel->fd);
   free(intel);
}

struct droid_backend *
droid_backend_create_intel(const char *dev)
{
   struct droid_backend_intel *intel;

   intel = calloc(1, sizeof(*intel));
   if (!intel)
      return NULL;

   intel->fd = open(dev, O_RDWR);
   if (intel->fd < 0) {
      LOGE("failed to open %s", dev);
      free(intel);
      return NULL;
   }

   intel->screen_number = 0;

   /* XXX query using I915_GETPARAM + PARAM_CHIPSET_ID */
   intel->generation = INTEL_GEN_3;

   intel->pitch_align = 64;
   intel->enable_tiling = 1;

   intel->base.driver_name = "i915";
   intel->base.initialize = intel_initialize;
   intel->base.process_config = intel_process_config;
   intel->base.destroy = intel_destroy;

   intel->base.get_native_buffer = intel_get_native_buffer;
   intel->base.get_surface_buffers = intel_get_surface_buffers;

   intel->base.create_window_surface = intel_create_window_surface;
   intel->base.create_image_surface = intel_create_image_surface;
   intel->base.destroy_surface = intel_destroy_surface;
   intel->base.swap_native_buffers = intel_swap_native_buffers;

   return &intel->base;
}
