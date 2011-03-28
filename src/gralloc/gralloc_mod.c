#define LOG_TAG "GRALLOC-MOD"

#include <cutils/log.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>

#include "gralloc_mod.h"
#include "gralloc_gem.h"
#include "gralloc_kms.h"

static int
drm_mod_perform(const struct gralloc_module_t *mod, int op, ...)
{
   struct drm_module_t *drm = (struct drm_module_t *) mod;
   va_list args;
   int ret;

   va_start(args, op);
   switch (op) {
   case GRALLOC_MODULE_PERFORM_GET_DRM_FD:
      {
         int *fd = va_arg(args, int *);

         ret = drm_gem_init(drm);
         if (!ret)
            *fd = drm->fd;
      }
      break;
   case GRALLOC_MODULE_PERFORM_GET_DRM_MAGIC:
      {
         int32_t *magic = va_arg(args, int32_t *);

         ret = drm_gem_init(drm);
         if (!ret)
            ret = drm_gem_get_magic(drm, magic);
      }
      break;
   case GRALLOC_MODULE_PERFORM_AUTH_DRM_MAGIC:
      {
         int32_t magic = va_arg(args, int32_t);

         ret = drm_gem_init(drm);
         if (!ret)
            ret = drm_gem_auth_magic(drm, magic);
      }
      break;
   default:
      ret = -EINVAL;
      break;
   }
   va_end(args);

   return ret;
}

static int
drm_mod_register_buffer(const gralloc_module_t *mod, buffer_handle_t handle)
{
   return (drm_gem_get(handle)) ? 0 : -EINVAL;
}

static int
drm_mod_unregister_buffer(const gralloc_module_t *mod, buffer_handle_t handle)
{
   return (drm_gem_get(handle)) ? 0 : -EINVAL;
}

static int
drm_mod_lock(const gralloc_module_t *mod, buffer_handle_t handle,
             int usage, int x, int y, int w, int h, void **ptr)
{
   struct drm_module_t *drm = (struct drm_module_t *) mod;
   struct drm_bo_t *bo;
   int ret;

   ret = drm_gem_init(drm);
   if (!ret)
      ret = drm_gem_drv_init(drm);
   if (ret)
      return ret;

   bo = drm_gem_validate(handle);
   if (!bo)
      return -EINVAL;

   return drm_gem_drv_map(drm, bo, x, y, w, h, 1, ptr);
}

static int
drm_mod_unlock(const gralloc_module_t *mod, buffer_handle_t handle)
{
   struct drm_module_t *drm = (struct drm_module_t *) mod;
   struct drm_bo_t *bo;

   bo = drm_gem_validate(handle);
   if (!bo)
      return -EINVAL;

   drm_gem_drv_unmap(drm, bo);

   return 0;
}

static int
drm_mod_close_gpu0(struct hw_device_t *dev)
{
   struct alloc_device_t *alloc = (struct alloc_device_t *) dev;

   free(alloc);

   return 0;
}

static int
drm_mod_free_gpu0(alloc_device_t *dev, buffer_handle_t handle)
{
   struct drm_module_t *drm = (struct drm_module_t *) dev->common.module;
   struct drm_bo_t *bo;

   bo = drm_gem_validate(handle);
   if (!bo)
      return -EINVAL;

   if (bo->usage & GRALLOC_USAGE_HW_FB)
      drm_kms_rm_fb(drm, bo);

   drm_gem_drv_free(drm, bo);

   return 0;
}

static int
drm_mod_alloc_gpu0(alloc_device_t *dev, int w, int h, int format, int usage,
                   buffer_handle_t *handle, int *stride)
{
   struct drm_module_t *drm = (struct drm_module_t *) dev->common.module;
   struct drm_bo_t *bo;
   int size, bpp, ret;

   ret = drm_gem_drv_init(drm);
   if (ret)
      return ret;

   bpp = drm_mod_get_bpp(format);
   if (!bpp)
      return -EINVAL;

   bo = drm_gem_drv_alloc(drm, w, h, format, usage, stride);
   if (!bo)
      return -EINVAL;
   if (bo->usage & GRALLOC_USAGE_HW_FB) {
      ret = drm_kms_add_fb(drm, bo);
      if (ret) {
         LOGE("failed to add fb");
         drm_gem_drv_free(drm, bo);
         return ret;
      }
   }

   *stride /= bpp;
   *handle = &bo->base;

   return 0;
}

static int
drm_mod_open_gpu0(struct drm_module_t *drm, hw_device_t **dev)
{
   struct alloc_device_t *alloc;
   int ret;

   ret = drm_gem_init(drm);
   if (ret)
      return ret;

   alloc = calloc(1, sizeof(*alloc));
   if (!alloc)
      return -EINVAL;

   alloc->common.tag = HARDWARE_DEVICE_TAG;
   alloc->common.version = 0;
   alloc->common.module = (hw_module_t *) drm;
   alloc->common.close = drm_mod_close_gpu0;

   alloc->alloc = drm_mod_alloc_gpu0;
   alloc->free = drm_mod_free_gpu0;

   *dev = &alloc->common;

   return 0;
}

static int
drm_mod_close_fb0(struct hw_device_t *dev)
{
   struct framebuffer_device_t *fb = (struct framebuffer_device_t *) dev;

   free(fb);

   return 0;
}

static int
drm_mod_set_swap_interval_fb0(struct framebuffer_device_t *fb, int interval)
{
   if (interval < fb->minSwapInterval || interval > fb->maxSwapInterval)
      return -EINVAL;
   return 0;
}

static int
drm_mod_post_fb0(struct framebuffer_device_t *fb, buffer_handle_t handle)
{
   struct drm_module_t *drm = (struct drm_module_t *) fb->common.module;
   struct drm_bo_t *bo;

   bo = drm_gem_validate(handle);
   if (!bo)
      return -EINVAL;

   return drm_kms_post(drm, bo);
}

#include <GLES/gl.h>
static int
drm_mod_composition_complete_fb0(struct framebuffer_device_t *fb)
{
   struct drm_module_t *drm = (struct drm_module_t *) fb->common.module;

   if (drm->mode_page_flip)
      glFlush();
   else
      glFinish();

   return 0;
}

static int
drm_mod_open_fb0(struct drm_module_t *drm, struct hw_device_t **dev)
{
   struct framebuffer_device_t *fb;
   int ret;

   fb = calloc(1, sizeof(*fb));
   if (!fb)
      return -ENOMEM;

   ret = drm_gem_init(drm);
   if (!ret)
      ret = drm_kms_init(drm);
   if (ret) {
      free(fb);
      return ret;
   }

   fb->common.tag = HARDWARE_DEVICE_TAG;
   fb->common.version = 0;
   fb->common.module = (hw_module_t *) drm;
   fb->common.close = drm_mod_close_fb0;

   fb->setSwapInterval = drm_mod_set_swap_interval_fb0;
   fb->post = drm_mod_post_fb0;
   fb->compositionComplete = drm_mod_composition_complete_fb0;

   *((uint32_t *) &fb->flags) = 0x0;
   *((uint32_t *) &fb->width) = drm->mode.hdisplay;
   *((uint32_t *) &fb->height) = drm->mode.vdisplay;
   *((int *)      &fb->stride) = drm->mode.hdisplay;
   *((float *)    &fb->fps) = drm->mode.vrefresh;

   *((int *)      &fb->format) = drm->format;
   *((float *)    &fb->xdpi) = drm->xdpi;
   *((float *)    &fb->ydpi) = drm->ydpi;
   *((int *)      &fb->minSwapInterval) = drm->swap_interval;
   *((int *)      &fb->maxSwapInterval) = drm->swap_interval;

   *dev = &fb->common;

   LOGI("mode.hdisplay %d\n"
        "mode.vdisplay %d\n"
        "mode.vrefresh %d\n"
        "format 0x%x\n"
        "xdpi %d\n"
        "ydpi %d\n",
        drm->mode.hdisplay,
        drm->mode.vdisplay,
        drm->mode.vrefresh,
        drm->format,
        drm->xdpi, drm->ydpi);

   return 0;
}

static int
drm_mod_open(const struct hw_module_t *mod, const char *name, struct hw_device_t **dev)
{
   struct drm_module_t *drm = (struct drm_module_t *) mod;
   int ret;

    if (strcmp(name, GRALLOC_HARDWARE_GPU0) == 0)
       ret = drm_mod_open_gpu0(drm, dev);
    else if (strcmp(name, GRALLOC_HARDWARE_FB0) == 0)
       ret = drm_mod_open_fb0(drm, dev);
    else
       ret = -EINVAL;

    return ret;
}

static struct hw_module_methods_t drm_mod_methods = {
   .open = drm_mod_open
};

struct drm_module_t HAL_MODULE_INFO_SYM = {
   .base = {
      .common = {
         .tag = HARDWARE_MODULE_TAG,
         .version_major = 1,
         .version_minor = 0,
         .id = GRALLOC_HARDWARE_MODULE_ID,
         .name = "DRM Memory Allocator",
         .author = "Chia-I Wu",
         .methods = &drm_mod_methods
      },
      .registerBuffer = drm_mod_register_buffer,
      .unregisterBuffer = drm_mod_unregister_buffer,
      .lock = drm_mod_lock,
      .unlock = drm_mod_unlock,
      .perform = drm_mod_perform
   },
   .mutex = PTHREAD_MUTEX_INITIALIZER,
   .fd = -1
};
