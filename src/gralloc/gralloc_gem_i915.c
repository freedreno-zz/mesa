#define LOG_TAG "GRALLOC-I915"

#include <cutils/log.h>
#include <stdlib.h>
#include <errno.h>
#include <drm.h>
#include <intel_bufmgr.h>
#include <i915_drm.h>

#include "gralloc_mod.h"
#include "gralloc_gem.h"

static void
drm_gem_drv_init_features_locked(struct drm_module_t *drm)
{
   struct drm_i915_getparam gp;

   drm_intel_bufmgr *bufmgr = (drm_intel_bufmgr *) drm->gem;

   drm->mode_dirty_fb = 0;

   memset(&gp, 0, sizeof(gp));
   gp.param = I915_PARAM_HAS_PAGEFLIPPING;
   gp.value = &drm->mode_page_flip;
   if (!drmCommandWriteRead(drm->fd, DRM_I915_GETPARAM, &gp, sizeof(gp)))
      drm->mode_page_flip = *gp.value;
   else
      drm->mode_page_flip = 0;

   if (drm->resources) {
      int pipe;

      pipe = drm_intel_get_pipe_from_crtc_id(bufmgr, drm->crtc_id);
      drm->swap_interval = (pipe >= 0) ? 1 : 0;
      drm->vblank_secondary = (pipe > 0);
   }
   else {
      drm->swap_interval = 0;
   }

   /* XXX there is a bug in the kernel module */
   drm->mode_page_flip = 0;

}

static int
drm_gem_drv_init_locked(struct drm_module_t *drm)
{
   if (drm->gem)
      return 0;

   drm->gem = (void *) drm_intel_bufmgr_gem_init(drm->fd, 16 * 1024);
   if (!drm->gem) {
      LOGE("failed to create buffer manager");
      return -ENOMEM;
   }

   drm_gem_drv_init_features_locked(drm);

   return 0;
}

int
drm_gem_drv_init(struct drm_module_t *drm)
{
   int ret;

   pthread_mutex_lock(&drm->mutex);
   ret = drm_gem_drv_init_locked(drm);
   pthread_mutex_unlock(&drm->mutex);

   return ret;
}

static uint32_t
drm_gem_get_tiling(struct drm_bo_t *bo)
{
   uint32_t tiling = I915_TILING_NONE;

   if (bo->usage & GRALLOC_USAGE_SW_READ_OFTEN)
      return tiling;

   if (bo->usage & GRALLOC_USAGE_HW_FB ||
       bo->usage & GRALLOC_USAGE_HW_TEXTURE) {
      if (bo->width >= 64)
         tiling = I915_TILING_X;
   }

   return tiling;
}

struct drm_bo_t *
drm_gem_drv_alloc(struct drm_module_t *drm, int width, int height,
                  int format, int usage, int *stride)
{
   drm_intel_bufmgr *bufmgr = (drm_intel_bufmgr *) drm->gem;
   struct drm_bo_t *bo;
   drm_intel_bo *ibo;
   int aligned_width, aligned_height, cpp;
   unsigned long pitch, flags;
   uint32_t tiling;
   const char *name;

   bo = drm_gem_create_bo(width, height, format, usage);
   if (!bo)
      return NULL;

   cpp = drm_mod_get_bpp(format);
   if (!cpp) {
      LOGE("unrecognized format 0x%x", format);
      free(bo);
      return NULL;
   }

   if (usage & GRALLOC_USAGE_HW_FB) {
      name = "gralloc-fb";
      aligned_width = (width + 63) & ~63;
   }
   if (usage & GRALLOC_USAGE_HW_TEXTURE) {
      name = "gralloc-texture";
      aligned_width = (width + 3) & ~3;
      aligned_height = (height + 1) & ~1;
   }
   else {
      name = "gralloc-buf";
      aligned_width = width;
      aligned_height = height;
   }

   tiling = drm_gem_get_tiling(bo);

   flags = 0x0;
   if (bo->usage & (GRALLOC_USAGE_HW_RENDER | GRALLOC_USAGE_HW_FB))
      flags |= BO_ALLOC_FOR_RENDER;

   ibo = drm_intel_bo_alloc_tiled(bufmgr, name,
         aligned_width, aligned_height, cpp, &tiling, &pitch, flags);
   if (!ibo) {
      LOGE("failed to allocate ibo %dx%dx%d", width, height, cpp);
      free(bo);
      return NULL;
   }

   if (bo->usage & GRALLOC_USAGE_HW_FB) {
      drm_intel_bo_disable_reuse(ibo);
      bo->stride = pitch;
      bo->fb_handle = ibo->handle;
   }

   if (drm_intel_bo_flink(ibo, (uint32_t *) &bo->name)) {
      LOGE("failed to flink ibo");
      drm_intel_bo_unreference(ibo);
      free(bo);
      return NULL;
   }

   bo->data = (int) ibo;

   *stride = pitch;

   return bo;
}

void
drm_gem_drv_free(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   drm_intel_bo_unreference((drm_intel_bo *) bo->data);
   free(bo);
}

int
drm_gem_drv_map(struct drm_module_t *drm, struct drm_bo_t *bo,
                int x, int y, int w, int h, int enable_write, void **addr)
{
   drm_intel_bo *ibo = (drm_intel_bo *) bo->data;
   int err;

   if (!ibo) {
      drm_intel_bufmgr *bufmgr = (drm_intel_bufmgr *) drm->gem;

      ibo = drm_intel_bo_gem_create_from_name(bufmgr, "gralloc-r", bo->name);
      if (!ibo) {
         LOGE("failed to create ibo from name %u", bo->name);
         return -EINVAL;
      }

      bo->data = (int) ibo;
   }

   if ((bo->usage & GRALLOC_USAGE_HW_FB) ||
       drm_gem_get_tiling(bo) != I915_TILING_NONE)
      err = drm_intel_gem_bo_map_gtt(ibo);
   else
      err = drm_intel_bo_map(ibo, enable_write);
   if (!err)
      *addr = ibo->virtual;

   return err;
}

void
drm_gem_drv_unmap(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   drm_intel_bo *ibo = (drm_intel_bo *) bo->data;

   if ((bo->usage & GRALLOC_USAGE_HW_FB) ||
       drm_gem_get_tiling(bo) != I915_TILING_NONE)
      drm_intel_gem_bo_unmap_gtt(ibo);
   else
      drm_intel_bo_unmap(ibo);
}
