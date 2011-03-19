/*
 * Based on xf86-video-ati, which is
 *
 * Copyright © 2009 Red Hat, Inc.
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Dave Airlie <airlied@redhat.com>
 */

#define LOG_TAG "GRALLOC-RADEON"

#include <cutils/log.h>
#include <stdlib.h>
#include <errno.h>
#include <drm.h>
#include <radeon_drm.h>
#include <radeon_bo_gem.h>
#include <radeon_bo.h>

#include "gralloc_mod.h"
#include "gralloc_gem.h"

#define RADEON_GPU_PAGE_SIZE 4096

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define ALIGN(val, align) (((val) + (align) - 1) & ~((align) - 1))

struct radeon_info {
   struct drm_module_t *drm;
   struct radeon_bo_manager *bufmgr;

   uint32_t tile_config;
   int num_channels;
   int num_banks;
   int group_bytes;
   /* r6xx+ tile config */
   int have_tiling_info;
   int allow_color_tiling;
};

static int
eg_init_tile_config(struct radeon_info *info)
{
   struct drm_radeon_info ginfo;
   uint32_t val;
   int ret;

   memset(&ginfo, 0, sizeof(ginfo));
   ginfo.request = RADEON_INFO_TILING_CONFIG;
   ginfo.value = (long) &val;
   ret = drmCommandWriteRead(info->drm->fd, DRM_RADEON_INFO, &ginfo, sizeof(ginfo));
   if (ret)
      return ret;

   info->tile_config = val;

   switch (info->tile_config & 0xf) {
   case 0:
      info->num_channels = 1;
      break;
   case 1:
      info->num_channels = 2;
      break;
   case 2:
      info->num_channels = 4;
      break;
   case 3:
      info->num_channels = 8;
      break;
   default:
      return -EINVAL;
      break;
   }

   info->num_banks = (info->tile_config & 0xf0) >> 4;

   switch ((info->tile_config & 0xf00) >> 8) {
   case 0:
      info->group_bytes = 256;
      break;
   case 1:
      info->group_bytes = 512;
      break;
   default:
      return -EINVAL;
      break;
   }

   info->have_tiling_info = 1;
   info->allow_color_tiling = 0;

   return 0;
}

/* returns pitch alignment in pixels */
static int
eg_get_pitch_align(struct radeon_info *info, int bpe, uint32_t tiling)
{
   int pitch_align = 1;

   if (tiling & RADEON_TILING_MACRO) {
      /* general surface requirements */
      pitch_align = MAX(info->num_banks,
            (((info->group_bytes / 8) / bpe) * info->num_banks)) * 8;
      /* further restrictions for scanout */
      pitch_align = MAX(info->num_banks * 8, pitch_align);
   } else if (tiling & RADEON_TILING_MICRO) {
      /* general surface requirements */
      pitch_align = MAX(8, (info->group_bytes / (8 * bpe)));
      /* further restrictions for scanout */
      pitch_align = MAX(info->group_bytes / bpe, pitch_align);
   } else {
      if (info->have_tiling_info)
         /* linear aligned requirements */
         pitch_align = MAX(64, info->group_bytes / bpe);
      else
         /* default to 512 elements if we don't know the real
          * group size otherwise the kernel may reject the CS
          * if the group sizes don't match as the pitch won't
          * be aligned properly.
          */
         pitch_align = 512;
   }

   return pitch_align;
}

/* returns height alignment in pixels */
static int
eg_get_height_align(struct radeon_info *info, uint32_t tiling)
{
   int height_align = 1;

   if (tiling & RADEON_TILING_MACRO)
      height_align =  info->num_channels * 8;
   else if (tiling & RADEON_TILING_MICRO)
      height_align = 8;
   else
      height_align = 8;

   return height_align;
}

/* returns base alignment in bytes */
static int
eg_get_base_align(struct radeon_info *info, int bpe, uint32_t tiling)
{
   int pixel_align = eg_get_pitch_align(info, bpe, tiling);
   int height_align = eg_get_height_align(info, tiling);
   int base_align = RADEON_GPU_PAGE_SIZE;

   if (tiling & RADEON_TILING_MACRO) {
      base_align = MAX(info->num_banks * info->num_channels * 8 * 8 * bpe,
            pixel_align * bpe * height_align);
   }
   else {
      if (info->have_tiling_info)
         base_align = info->group_bytes;
      else
         /* default to 512 if we don't know the real
          * group size otherwise the kernel may reject the CS
          * if the group sizes don't match as the base won't
          * be aligned properly.
          */
         base_align = 512;
   }

   return base_align;
}

static void
drm_gem_radeon_init_features(struct drm_module_t *drm)
{
   drm->mode_dirty_fb = 0;
   /* XXX there are synchronization issues */
   drm->mode_page_flip = 0;
   drm->swap_interval = 1;
   drm->vblank_secondary = 0;
}

static int
drm_gem_radeon_init(struct drm_module_t *drm)
{
   struct radeon_info *info;
   int ret;

   info = calloc(1, sizeof(*info));
   if (!info)
      return -ENOMEM;

   info->drm = drm;
   info->bufmgr = radeon_bo_manager_gem_ctor(info->drm->fd);
   if (!info->bufmgr) {
      LOGE("failed to create buffer manager");
      free(info);
      return -ENOMEM;
   }


   drm->gem = (void *) info;

   ret = eg_init_tile_config(info);
   if (ret) {
      radeon_bo_manager_gem_dtor(info->bufmgr);
      free(info);
      return ret;
   }

   drm_gem_radeon_init_features(drm);

   return 0;
}

static uint32_t
drm_gem_get_tiling(struct drm_bo_t *bo)
{
   return 0;
}

static struct drm_bo_t *
drm_gem_radeon_alloc(struct drm_module_t *drm, int width, int height,
                    int format, int usage, int *stride)
{
   struct radeon_info *info = (struct radeon_info *) drm->gem;
   struct drm_bo_t *bo;
   struct radeon_bo *rbo;
   int aligned_width, aligned_height, cpp;
   int pitch, size, base_align;
   uint32_t tiling;

   bo = drm_gem_create_bo(width, height, format, usage);
   if (!bo)
      return NULL;

   cpp = drm_mod_get_bpp(format);
   if (!cpp) {
      LOGE("unrecognized format 0x%x", format);
      free(bo);
      return NULL;
   }

   tiling = drm_gem_get_tiling(bo);

   if (usage & (GRALLOC_USAGE_HW_FB | GRALLOC_USAGE_HW_TEXTURE)) {
      aligned_width = ALIGN(width, eg_get_pitch_align(info, cpp, tiling));
      aligned_height = ALIGN(height, eg_get_height_align(info, tiling));
   }
   else {
      aligned_width = width;
      aligned_height = height;
   }

   pitch = aligned_width * cpp;
   size = ALIGN(aligned_height * pitch, RADEON_GPU_PAGE_SIZE);
   base_align = eg_get_base_align(info, cpp, tiling);

   rbo = radeon_bo_open(info->bufmgr, 0, size,
         base_align, RADEON_GEM_DOMAIN_VRAM, 0);
   if (!rbo) {
      LOGE("failed to allocate rbo %dx%dx%d", width, height, cpp);
      free(bo);
      return NULL;
   }

   if (tiling)
      radeon_bo_set_tiling(rbo, tiling, pitch);

   if (bo->usage & GRALLOC_USAGE_HW_FB) {
      bo->stride = pitch;
      bo->fb_handle = rbo->handle;
   }

   if (radeon_gem_get_kernel_name(rbo, (uint32_t *) &bo->name)) {
      LOGE("failed to flink rbo");
      radeon_bo_unref(rbo);
      free(bo);
      return NULL;
   }

   bo->data = (int) rbo;

   *stride = pitch;

   return bo;
}

static void
drm_gem_radeon_free(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   radeon_bo_unref((struct radeon_bo *) bo->data);
   free(bo);
}

static int
drm_gem_radeon_map(struct drm_module_t *drm, struct drm_bo_t *bo,
                  int x, int y, int w, int h, int enable_write, void **addr)
{
   struct radeon_bo *rbo = (struct radeon_bo *) bo->data;
   int err;

   if (!rbo) {
      struct radeon_info *info = (struct radeon_info *) drm->gem;

      rbo = radeon_bo_open(info->bufmgr, bo->name, 0, 0, RADEON_GEM_DOMAIN_VRAM, 0);
      if (!rbo) {
         LOGE("failed to create rbo from name %u", bo->name);
         return -EINVAL;
      }

      bo->data = (int) rbo;
   }

   err = radeon_bo_map(rbo, enable_write);
   if (!err)
      *addr = rbo->ptr;

   return err;
}

static void
drm_gem_radeon_unmap(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   struct radeon_bo *rbo = (struct radeon_bo *) bo->data;

   radeon_bo_unmap(rbo);
}

const struct drm_gem_drv drm_gem_drv_radeon = {
   .init = drm_gem_radeon_init,
   .alloc = drm_gem_radeon_alloc,
   .free = drm_gem_radeon_free,
   .map = drm_gem_radeon_map,
   .unmap = drm_gem_radeon_unmap,
};
