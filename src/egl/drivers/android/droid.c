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

#define LOG_TAG "MESA-EGL"

#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <cutils/log.h>

#include "droid.h"

static const __DRIuseInvalidateExtension use_invalidate = {
   { __DRI_USE_INVALIDATE, 1 }
};

static __DRIimage *
droid_lookup_egl_image(__DRIscreen *screen, void *image, void *data)
{
   _EGLDisplay *disp = data;
   struct droid_egl_image *dimg;
   _EGLImage *img;

   (void) screen;

   img = _eglLookupImage(image, disp);
   if (img == NULL) {
      _eglError(EGL_BAD_PARAMETER, "droid_lookup_egl_image");
      return NULL;
   }

   dimg = droid_egl_image(image);

   return dimg->dri_image;
}

static const __DRIimageLookupExtension image_lookup_extension = {
   { __DRI_IMAGE_LOOKUP, 1 },
   droid_lookup_egl_image
};

static int
get_format_bpp(int native)
{
   int bpp;

   /* see libpixelflinger/format.cpp */
   switch (native) {
   case GGL_PIXEL_FORMAT_RGBA_8888:
   case GGL_PIXEL_FORMAT_RGBX_8888:
   case GGL_PIXEL_FORMAT_BGRA_8888:
      bpp = 4;
      break;
   case GGL_PIXEL_FORMAT_RGB_888:
      bpp = 3;
      break;
   case GGL_PIXEL_FORMAT_RGB_565:
   case GGL_PIXEL_FORMAT_RGBA_5551:
   case GGL_PIXEL_FORMAT_RGBA_4444:
   case GGL_PIXEL_FORMAT_LA_88:
      bpp = 2;
      break;
   case GGL_PIXEL_FORMAT_RGB_332:
   case GGL_PIXEL_FORMAT_A_8:
   case GGL_PIXEL_FORMAT_L_8:
      bpp = 1;
      break;
   default:
      bpp = 0;
      break;
   }

   return bpp;
}

#include <gralloc_gem.h>
int
get_native_buffer_name(struct android_native_buffer_t *buf)
{
   struct drm_bo_t *bo;

   bo = drm_gem_get(buf->handle);

   return (bo) ? bo->name : 0;
}

EGLBoolean
droid_dequeue_buffer(struct droid_egl_surface *dsurf)
{
   __DRIbuffer *buf = &dsurf->dri_buffer;

   if (dsurf->window->dequeueBuffer(dsurf->window, &dsurf->buffer))
      return EGL_FALSE;

   dsurf->buffer->common.incRef(&dsurf->buffer->common);
   dsurf->window->lockBuffer(dsurf->window, dsurf->buffer);

   buf->attachment = __DRI_BUFFER_FAKE_FRONT_LEFT;
   buf->name = get_native_buffer_name(dsurf->buffer);
   buf->cpp = get_format_bpp(dsurf->buffer->format);
   buf->pitch = dsurf->buffer->stride * buf->cpp;
   buf->flags = 0;

   return EGL_TRUE;
}

EGLBoolean
droid_enqueue_buffer(struct droid_egl_surface *dsurf)
{
   dsurf->window->queueBuffer(dsurf->window, dsurf->buffer);

   dsurf->buffer->common.decRef(&dsurf->buffer->common);
   dsurf->buffer = NULL;

   return EGL_TRUE;
}

static void
droid_flush_front_buffer(__DRIdrawable * driDrawable, void *loaderPrivate)
{
}

static __DRIbuffer *
droid_get_buffers_with_format(__DRIdrawable * driDrawable,
			     int *width, int *height,
			     unsigned int *attachments, int count,
			     int *out_count, void *loaderPrivate)
{
   struct droid_egl_surface *dsurf = loaderPrivate;
   struct droid_egl_display *ddpy =
      droid_egl_display(dsurf->base.Resource.Display);

   if (!dsurf->buffer) {
      if (!droid_dequeue_buffer(dsurf))
         return NULL;
   }

   dsurf->base.Width = dsurf->buffer->width;
   dsurf->base.Height = dsurf->buffer->height;

   if (width)
      *width = dsurf->buffer->width;
   if (height)
      *height = dsurf->buffer->height;

   *out_count = 1;

   return &dsurf->dri_buffer;
}

static const EGLint droid_to_egl_attribute_map[] = {
   0,
   EGL_BUFFER_SIZE,		/* __DRI_ATTRIB_BUFFER_SIZE */
   EGL_LEVEL,			/* __DRI_ATTRIB_LEVEL */
   EGL_RED_SIZE,		/* __DRI_ATTRIB_RED_SIZE */
   EGL_GREEN_SIZE,		/* __DRI_ATTRIB_GREEN_SIZE */
   EGL_BLUE_SIZE,		/* __DRI_ATTRIB_BLUE_SIZE */
   EGL_LUMINANCE_SIZE,		/* __DRI_ATTRIB_LUMINANCE_SIZE */
   EGL_ALPHA_SIZE,		/* __DRI_ATTRIB_ALPHA_SIZE */
   0,				/* __DRI_ATTRIB_ALPHA_MASK_SIZE */
   EGL_DEPTH_SIZE,		/* __DRI_ATTRIB_DEPTH_SIZE */
   EGL_STENCIL_SIZE,		/* __DRI_ATTRIB_STENCIL_SIZE */
   0,				/* __DRI_ATTRIB_ACCUM_RED_SIZE */
   0,				/* __DRI_ATTRIB_ACCUM_GREEN_SIZE */
   0,				/* __DRI_ATTRIB_ACCUM_BLUE_SIZE */
   0,				/* __DRI_ATTRIB_ACCUM_ALPHA_SIZE */
   EGL_SAMPLE_BUFFERS,		/* __DRI_ATTRIB_SAMPLE_BUFFERS */
   EGL_SAMPLES,			/* __DRI_ATTRIB_SAMPLES */
   0,				/* __DRI_ATTRIB_RENDER_TYPE, */
   0,				/* __DRI_ATTRIB_CONFIG_CAVEAT */
   0,				/* __DRI_ATTRIB_CONFORMANT */
   0,				/* __DRI_ATTRIB_DOUBLE_BUFFER */
   0,				/* __DRI_ATTRIB_STEREO */
   0,				/* __DRI_ATTRIB_AUX_BUFFERS */
   0,				/* __DRI_ATTRIB_TRANSPARENT_TYPE */
   0,				/* __DRI_ATTRIB_TRANSPARENT_INDEX_VALUE */
   0,				/* __DRI_ATTRIB_TRANSPARENT_RED_VALUE */
   0,				/* __DRI_ATTRIB_TRANSPARENT_GREEN_VALUE */
   0,				/* __DRI_ATTRIB_TRANSPARENT_BLUE_VALUE */
   0,				/* __DRI_ATTRIB_TRANSPARENT_ALPHA_VALUE */
   0,				/* __DRI_ATTRIB_FLOAT_MODE */
   0,				/* __DRI_ATTRIB_RED_MASK */
   0,				/* __DRI_ATTRIB_GREEN_MASK */
   0,				/* __DRI_ATTRIB_BLUE_MASK */
   0,				/* __DRI_ATTRIB_ALPHA_MASK */
   EGL_MAX_PBUFFER_WIDTH,	/* __DRI_ATTRIB_MAX_PBUFFER_WIDTH */
   EGL_MAX_PBUFFER_HEIGHT,	/* __DRI_ATTRIB_MAX_PBUFFER_HEIGHT */
   EGL_MAX_PBUFFER_PIXELS,	/* __DRI_ATTRIB_MAX_PBUFFER_PIXELS */
   0,				/* __DRI_ATTRIB_OPTIMAL_PBUFFER_WIDTH */
   0,				/* __DRI_ATTRIB_OPTIMAL_PBUFFER_HEIGHT */
   0,				/* __DRI_ATTRIB_VISUAL_SELECT_GROUP */
   0,				/* __DRI_ATTRIB_SWAP_METHOD */
   EGL_MAX_SWAP_INTERVAL,	/* __DRI_ATTRIB_MAX_SWAP_INTERVAL */
   EGL_MIN_SWAP_INTERVAL,	/* __DRI_ATTRIB_MIN_SWAP_INTERVAL */
   0,				/* __DRI_ATTRIB_BIND_TO_TEXTURE_RGB */
   0,				/* __DRI_ATTRIB_BIND_TO_TEXTURE_RGBA */
   0,				/* __DRI_ATTRIB_BIND_TO_MIPMAP_TEXTURE */
   0,				/* __DRI_ATTRIB_BIND_TO_TEXTURE_TARGETS */
   EGL_Y_INVERTED_NOK,		/* __DRI_ATTRIB_YINVERTED */
   0,                           /* __DRI_ATTRIB_FRAMEBUFFER_SRGB_CAPABLE */
};

static struct droid_egl_config *
droid_add_config(_EGLDisplay *dpy, const __DRIconfig *dri_config, int id,
		int depth, EGLint surface_type, int rgba_masks[4])
{
   struct droid_egl_config *conf;
   struct droid_egl_display *ddpy;
   _EGLConfig base;
   unsigned int attrib, value, double_buffer;
   EGLint key;
   int dri_masks[4] = { 0, 0, 0, 0 };
   int i;

   ddpy = dpy->DriverData;
   _eglInitConfig(&base, dpy, id);
   
   i = 0;
   double_buffer = 0;

   while (ddpy->core->indexConfigAttrib(dri_config, i++, &attrib, &value)) {
      switch (attrib) {
      case __DRI_ATTRIB_RENDER_TYPE:
	 if (value & __DRI_ATTRIB_RGBA_BIT)
	    value = EGL_RGB_BUFFER;
	 else if (value & __DRI_ATTRIB_LUMINANCE_BIT)
	    value = EGL_LUMINANCE_BUFFER;
	 else
	    assert(0);
	 _eglSetConfigKey(&base, EGL_COLOR_BUFFER_TYPE, value);
	 break;	 

      case __DRI_ATTRIB_CONFIG_CAVEAT:
         if (value & __DRI_ATTRIB_NON_CONFORMANT_CONFIG)
            value = EGL_NON_CONFORMANT_CONFIG;
         else if (value & __DRI_ATTRIB_SLOW_BIT)
            value = EGL_SLOW_CONFIG;
	 else
	    value = EGL_NONE;
	 _eglSetConfigKey(&base, EGL_CONFIG_CAVEAT, value);
         break;

      case __DRI_ATTRIB_DOUBLE_BUFFER:
	 double_buffer = value;
	 break;

      case __DRI_ATTRIB_RED_MASK:
         dri_masks[0] = value;
         break;

      case __DRI_ATTRIB_GREEN_MASK:
         dri_masks[1] = value;
         break;

      case __DRI_ATTRIB_BLUE_MASK:
         dri_masks[2] = value;
         break;

      case __DRI_ATTRIB_ALPHA_MASK:
         dri_masks[3] = value;
         break;

      default:
	 key = droid_to_egl_attribute_map[attrib];
	 if (key != 0)
	    _eglSetConfigKey(&base, key, value);
	 break;
      }
   }

   /* In EGL, double buffer or not isn't a config attribute.  Pixmaps
    * surfaces are always single buffered, pbuffer surfaces are always
    * back buffers and windows can be either, selected by passing an
    * attribute at window surface construction time.  To support this
    * we ignore all double buffer configs and manipulate the buffer we
    * return in the getBuffer callback to get the behaviour we want. */

   if (double_buffer)
      return NULL;

   if (depth > 0 && depth != _eglGetConfigKey(&base, EGL_BUFFER_SIZE))
      return NULL;

   if (memcmp(dri_masks, rgba_masks, sizeof(rgba_masks)))
      return NULL;

   _eglSetConfigKey(&base, EGL_NATIVE_RENDERABLE, EGL_TRUE);

   _eglSetConfigKey(&base, EGL_SURFACE_TYPE, surface_type);

   _eglSetConfigKey(&base, EGL_RENDERABLE_TYPE, dpy->ClientAPIs);
   _eglSetConfigKey(&base, EGL_CONFORMANT, dpy->ClientAPIs);

   if (!_eglValidateConfig(&base, EGL_FALSE)) {
      _eglLog(_EGL_DEBUG, "DRI2: failed to validate config %d", id);
      return NULL;
   }

   conf = calloc(1, sizeof(*conf));
   if (conf != NULL) {
      memcpy(&conf->base, &base, sizeof(base));
      conf->dri_config = dri_config;
      _eglLinkConfig(&conf->base);
   }

   return conf;
}

static EGLBoolean
droid_add_configs_for_visuals(_EGLDriver *drv, _EGLDisplay *dpy)
{
   struct droid_egl_display *ddpy = droid_egl_display(dpy);
   const struct {
      int format;
      int size;
      int rgba_masks[4];
   } visuals[] = {
      { GGL_PIXEL_FORMAT_RGBA_8888, 32, { 0xff, 0xff00, 0xff0000, 0xff000000 } },
      { GGL_PIXEL_FORMAT_RGBX_8888, 32, { 0xff, 0xff00, 0xff0000, 0x0 } },
      { GGL_PIXEL_FORMAT_RGB_888,   24, { 0xff, 0xff00, 0xff0000, 0x0 } },
      { GGL_PIXEL_FORMAT_RGB_565,   16, { 0xf800, 0x7e0, 0x1f, 0x0 } },
      { GGL_PIXEL_FORMAT_BGRA_8888, 32, { 0xff0000, 0xff00, 0xff, 0xff000000 } },
      { GGL_PIXEL_FORMAT_A_8,        8, { 0xf800, 0x7e0, 0x1f, 0x0 } },
      { 0, 0, { 0, 0, 0, 0 } }
   };
   int count, i, j;

   count = 0;
   for (i = 0; visuals[i].format; i++) {
      int format_count = 0;

      for (j = 0; ddpy->dri_configs[j]; j++) {
         struct droid_egl_config *dconf;

         dconf = droid_add_config(dpy, ddpy->dri_configs[j], count + 1,
               visuals[i].size, EGL_WINDOW_BIT, visuals[i].rgba_masks);
         if (dconf) {
            _eglSetConfigKey(&dconf->base,
                  EGL_NATIVE_VISUAL_TYPE, visuals[i].format);
            count++;
            format_count++;
         }
      }

      if (!format_count) {
         _eglLog(_EGL_DEBUG, "No DRI config supports native format 0x%x",
               visuals[i].format);
      }
   }

   return (count != 0);
}

struct droid_extension_match {
   const char *name;
   int version;
   int offset;
};

static struct droid_extension_match droid_driver_extensions[] = {
   { __DRI_CORE, 1, offsetof(struct droid_egl_display, core) },
   { __DRI_DRI2, 1, offsetof(struct droid_egl_display, dri2) },
   { NULL, 0, 0 }
};

static struct droid_extension_match droid_core_extensions[] = {
   { __DRI2_FLUSH, 1, offsetof(struct droid_egl_display, flush) },
   { __DRI_IMAGE, 1, offsetof(struct droid_egl_display, image) },
   { NULL, 0, 0 }
};

extern const __DRIextension *__driDriverExtensions[];

static EGLBoolean
droid_bind_extensions(struct droid_egl_display *ddpy,
		     struct droid_extension_match *matches,
		     const __DRIextension **extensions)
{
   int i, j, ret = EGL_TRUE;
   void *field;

   for (i = 0; extensions[i]; i++) {
      _eglLog(_EGL_DEBUG, "DRI2: found extension `%s'", extensions[i]->name);
      for (j = 0; matches[j].name; j++) {
	 if (strcmp(extensions[i]->name, matches[j].name) == 0 &&
	     extensions[i]->version >= matches[j].version) {
	    field = ((char *) ddpy + matches[j].offset);
	    *(const __DRIextension **) field = extensions[i];
	    _eglLog(_EGL_INFO, "DRI2: found extension %s version %d",
		    extensions[i]->name, extensions[i]->version);
	 }
      }
   }
   
   for (j = 0; matches[j].name; j++) {
      field = ((char *) ddpy + matches[j].offset);
      if (*(const __DRIextension **) field == NULL) {
	 _eglLog(_EGL_FATAL, "DRI2: did not find extension %s version %d",
		 matches[j].name, matches[j].version);
	 ret = EGL_FALSE;
      }
   }

   return ret;
}

static EGLBoolean
droid_create_screen(_EGLDisplay *dpy)
{
   struct droid_egl_display *ddpy = droid_egl_display(dpy);
   const __DRIextension **extensions;
   unsigned int api_mask;

   ddpy->dri_screen =
      ddpy->dri2->createNewScreen(0, ddpy->fd, ddpy->extensions,
				      &ddpy->dri_configs, dpy);
   if (ddpy->dri_screen == NULL) {
      _eglLog(_EGL_WARNING, "failed to create dri screen");
      return EGL_FALSE;
   }

   extensions = ddpy->core->getExtensions(ddpy->dri_screen);
   if (!droid_bind_extensions(ddpy, droid_core_extensions, extensions)) {
      ddpy->core->destroyScreen(ddpy->dri_screen);
      return EGL_FALSE;
   }

   if (ddpy->dri2->base.version >= 2)
      api_mask = ddpy->dri2->getAPIMask(ddpy->dri_screen);
   else
      api_mask = 1 << __DRI_API_OPENGL;

   dpy->ClientAPIs = 0;
   if (api_mask & (1 <<__DRI_API_OPENGL))
      dpy->ClientAPIs |= EGL_OPENGL_BIT;
   if (api_mask & (1 <<__DRI_API_GLES))
      dpy->ClientAPIs |= EGL_OPENGL_ES_BIT;
   if (api_mask & (1 << __DRI_API_GLES2))
      dpy->ClientAPIs |= EGL_OPENGL_ES2_BIT;

   if (ddpy->dri2->base.version >= 2) {
      dpy->Extensions.KHR_surfaceless_gles1 = EGL_TRUE;
      dpy->Extensions.KHR_surfaceless_gles2 = EGL_TRUE;
      dpy->Extensions.KHR_surfaceless_opengl = EGL_TRUE;
   }

   return EGL_TRUE;
}

static EGLBoolean
droid_load_driver(_EGLDisplay *dpy, const char *driver_name)
{
   struct droid_egl_display *ddpy = droid_egl_display(dpy);
   const __DRIextension **extensions;
   char path[PATH_MAX], *base = NULL;
   void *handle;

   if (geteuid() == getuid()) {
      /* don't allow setuid apps to use LIBGL_DRIVERS_PATH */
      base = getenv("LIBGL_DRIVERS_PATH");
   }
   if (!base)
      base = DEFAULT_DRIVER_DIR;
   snprintf(path, sizeof(path), "%s/%s_dri.so", base, driver_name);

   handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
   if (!handle) {
      _eglLog(_EGL_WARNING, "DRI2: failed to load %s: %s", path, dlerror());
      return EGL_FALSE;
   }

   _eglLog(_EGL_DEBUG, "DRI2: dlopen(%s)", path);
   extensions = dlsym(handle, __DRI_DRIVER_EXTENSIONS);
   if (!extensions) {
      _eglLog(_EGL_WARNING, "DRI2: driver exports no extensions");
      dlclose(handle);
      return EGL_FALSE;
   }

   if (!droid_bind_extensions(ddpy, droid_driver_extensions, extensions)) {
      dlclose(handle);
      return EGL_FALSE;
   }

   ddpy->dri_handle = handle;

   return EGL_TRUE;
}

#include <xf86drm.h>
/* for i915 */
#include <i915_drm.h>
#include "dri/intel/intel_chipset.h"
/* for radeon */
#include <radeon_drm.h>
#include "radeon/drm/radeon_drm_public.h"
static const char *
droid_get_driver_name(int fd)
{
   drmVersionPtr version;
   char *name = NULL;

   version = drmGetVersion(fd);
   if (!version) {
      _eglLog(_EGL_WARNING, "invalid drm fd");
      return NULL;
   }
   if (!version->name) {
      _eglLog(_EGL_WARNING, "unable to determine the driver name");
      drmFreeVersion(version);
      return NULL;
   }

   if (strcmp(version->name, "i915") == 0) {
      struct drm_i915_getparam gp;
      int id, ret;

      memset(&gp, 0, sizeof(gp));
      gp.param = I915_PARAM_CHIPSET_ID;
      gp.value = &id;
      ret = drmCommandWriteRead(fd, DRM_I915_GETPARAM, &gp, sizeof(gp));
      if (ret) {
         _eglLog(_EGL_WARNING, "failed to get param for i915");
      }
      else {
         name = (IS_965(id)) ? "i965" : "i915";
      }
   }
   else if (strcmp(version->name, "radeon") == 0) {
      struct drm_radeon_info info;
      int id, ret;

      memset(&info, 0, sizeof(info));
      info.request = RADEON_INFO_DEVICE_ID;
      info.value = (long) &id;
      ret = drmCommandWriteRead(fd, DRM_RADEON_INFO, &info, sizeof(info));
      if (ret) {
         _eglLog(_EGL_WARNING, "failed to get info for radeon");
      }
      else {
         name = (is_r3xx(id)) ? "r300" : "r600";
      }
   }

   drmFreeVersion(version);

   return name;
}

static int
droid_open_device(void)
{
   const hw_module_t *mod;
   int fd = -1, err;

   err = hw_get_module(GRALLOC_HARDWARE_MODULE_ID, &mod);
   if (!err) {
      const gralloc_module_t *gr = (gralloc_module_t *) mod;

      err = -EINVAL;
      if (gr->perform)
         err = gr->perform(gr, GRALLOC_MODULE_PERFORM_GET_DRM_FD, &fd);
   }
   if (err || fd < 0) {
      _eglLog(_EGL_WARNING, "fail to get drm fd");
      fd = -1;
   }

   return fd;
}

static EGLBoolean
droid_initialize_android(_EGLDriver *drv, _EGLDisplay *dpy)
{
   struct droid_egl_display *ddpy;
   const char *driver_name;
   int fd;

   fd = droid_open_device();
   if (fd < 0)
      return EGL_FALSE;
   driver_name = droid_get_driver_name(fd);
   if (!driver_name)
      return EGL_FALSE;

   ddpy = calloc(1, sizeof(*ddpy));
   if (!ddpy)
      return _eglError(EGL_BAD_ALLOC, "eglInitialize");

   ddpy->fd = fd;
   dpy->DriverData = (void *) ddpy;

   if (!droid_load_driver(dpy, driver_name))
      return EGL_FALSE;

   ddpy->loader_extension.base.name = __DRI_DRI2_LOADER;
   ddpy->loader_extension.base.version = 3;
   ddpy->loader_extension.getBuffers = NULL;
   ddpy->loader_extension.flushFrontBuffer = droid_flush_front_buffer;
   ddpy->loader_extension.getBuffersWithFormat =
      droid_get_buffers_with_format;

   ddpy->extensions[0] = &ddpy->loader_extension.base;
   ddpy->extensions[1] = &image_lookup_extension.base;
   ddpy->extensions[2] = &use_invalidate.base;
   ddpy->extensions[3] = NULL;

   if (!droid_create_screen(dpy)) {
      free(ddpy);
      return EGL_FALSE;
   }

   if (!droid_add_configs_for_visuals(drv, dpy)) {
      ddpy->core->destroyScreen(ddpy->dri_screen);
      free(ddpy);
   }

   dpy->Extensions.ANDROID_image_native_buffer = EGL_TRUE;
   dpy->Extensions.KHR_image_base = EGL_TRUE;

   /* we're supporting EGL 1.4 */
   dpy->VersionMajor = 1;
   dpy->VersionMinor = 4;

   return EGL_TRUE;
}

static EGLBoolean
droid_terminate(_EGLDriver *drv, _EGLDisplay *dpy)
{
   struct droid_egl_display *ddpy = droid_egl_display(dpy);

   _eglReleaseDisplayResources(drv, dpy);
   _eglCleanupDisplay(dpy);

   ddpy->core->destroyScreen(ddpy->dri_screen);
   dlclose(ddpy->dri_handle);
   free(ddpy);

   dpy->DriverData = NULL;

   return EGL_TRUE;
}

static EGLBoolean
droid_initialize(_EGLDriver *drv, _EGLDisplay *dpy)
{
   /* not until swrast_dri is supported */
   if (dpy->Options.UseFallback)
      return EGL_FALSE;

   switch (dpy->Platform) {
   case _EGL_PLATFORM_ANDROID:
      if (dpy->Options.TestOnly)
         return EGL_TRUE;
      return droid_initialize_android(drv, dpy);
   default:
      return EGL_FALSE;
   }
}

static _EGLProc
droid_get_proc_address(_EGLDriver *drv, const char *procname)
{
   struct droid_egl_driver *ddrv = droid_egl_driver(drv);

   return ddrv->get_proc_address(procname);
}

static void
droid_log(EGLint level, const char *msg)
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
      LOG_FATAL(msg);
      break;
   default:
      break;
   }
}

static void
droid_unload(_EGLDriver *drv)
{
   struct droid_egl_driver *ddrv = droid_egl_driver(drv);

   free(ddrv);
}

#include "glapi/glapi.h" /* for _glapi_get_proc_address */
static EGLBoolean
droid_load(_EGLDriver *drv)
{
   struct droid_egl_driver *ddrv = droid_egl_driver(drv);

   ddrv->get_proc_address = (_EGLProc (*)(const char *)) _glapi_get_proc_address;

   ddrv->glFlush = (void (*)(void))
      ddrv->get_proc_address("glFlush");
   ddrv->glFinish = (void (*)(void))
      ddrv->get_proc_address("glFinish");

   return EGL_TRUE;
}

_EGLDriver *
droid_create_driver(void)
{
   struct droid_egl_driver *ddrv;

   ddrv = calloc(1, sizeof(*ddrv));
   if (!ddrv)
      return NULL;

   if (!droid_load(&ddrv->base))
      return NULL;

   _eglSetLogProc(droid_log);

   ddrv->base.Name = "Droid";
   ddrv->base.Unload = droid_unload;

   _eglInitDriverFallbacks(&ddrv->base);
   ddrv->base.API.Initialize = droid_initialize;
   ddrv->base.API.Terminate = droid_terminate;
   ddrv->base.API.GetProcAddress = droid_get_proc_address;

   return &ddrv->base;
}
