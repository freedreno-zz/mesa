#ifndef _GRALLOC_DRM_H
#define _GRALLOC_DRM_H

#include <hardware/gralloc.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <pthread.h>

struct drm_module_t {
   gralloc_module_t base;

   pthread_mutex_t mutex;

   /* initialized by drm_gem_init */
   int fd;

   /* initialized by drm_kms_init */
   drmModeResPtr resources;
   uint32_t crtc_id;
   uint32_t connector_id;
   drmModeModeInfo mode;
   int xdpi, ydpi;
   int format;
#ifdef DRM_MODE_FEATURE_DIRTYFB
   drmModeClip clip;
#endif

   /* initialized by drm_gem_drv_init */
   void *drv;
   void *gem;
   int mode_dirty_fb;
   int mode_page_flip;
   int mode_page_flip_blocking; /* page flip should block */
   int swap_interval;
   int vblank_secondary;

   int first_post;
};

static inline int
drm_mod_get_bpp(int format)
{
   int bpp;

   switch (format) {
   case HAL_PIXEL_FORMAT_RGBA_8888:
   case HAL_PIXEL_FORMAT_RGBX_8888:
   case HAL_PIXEL_FORMAT_BGRA_8888:
      bpp = 4;
      break;
   case HAL_PIXEL_FORMAT_RGB_888:
      bpp = 3;
      break;
   case HAL_PIXEL_FORMAT_RGB_565:
   case HAL_PIXEL_FORMAT_RGBA_5551:
   case HAL_PIXEL_FORMAT_RGBA_4444:
      bpp = 2;
      break;
   default:
      bpp = 0;
      break;
   }

   return bpp;
}

#endif /* _GRALLOC_DRM_H */
