#define LOG_TAG "GRALLOC-KMS"

#include <cutils/log.h>
#include <errno.h>
#include <unistd.h>
#include "gralloc_kms.h"

int
drm_kms_add_fb(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   uint8_t bpp;

   bpp = drm_mod_get_bpp(bo->format) * 8;

   return drmModeAddFB(drm->fd, bo->width, bo->height, bpp, bpp,
         bo->stride, bo->fb_handle, (uint32_t *) &bo->fb_id);
}

void
drm_kms_rm_fb(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   drmModeRmFB(drm->fd, bo->fb_id);
   bo->fb_id = 0;
}

static void
drm_kms_wait_vblank(struct drm_module_t *drm, int num)
{
   drmVBlank vbl;
   int ret;

   memset(&vbl, 0, sizeof(vbl));
   vbl.request.type = DRM_VBLANK_RELATIVE;
   if (drm->vblank_secondary)
      vbl.request.type |= DRM_VBLANK_SECONDARY;
   vbl.request.sequence = num;

   ret = drmWaitVBlank(drm->fd, &vbl);
   if (ret)
      LOGW("failed to wait vblank");
}

static int
drm_kms_set_crtc(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   int ret;

   if (drm->swap_interval)
      drm_kms_wait_vblank(drm, drm->swap_interval);

   ret = drmModeSetCrtc(drm->fd, drm->crtc_id, bo->fb_id,
         0, 0, &drm->connector_id, 1, &drm->mode);
   if (ret) {
      LOGE("failed to set crtc");
      return ret;
   }

#ifdef DRM_MODE_FEATURE_DIRTYFB
   if (drm->mode_dirty_fb)
      ret = drmModeDirtyFB(drm->fd, bo->fb_id, &drm->clip, 1);
#endif

   return ret;
}

static int
drm_kms_page_flip(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   int waits = 3, ret;

   if (drm->swap_interval > 1)
      drm_kms_wait_vblank(drm, drm->swap_interval - 1);

   while (waits) {
      ret = drmModePageFlip(drm->fd, drm->crtc_id, bo->fb_id, 0x0, NULL);
      if (ret && errno == EBUSY) {
         if (drm->swap_interval)
            drm_kms_wait_vblank(drm, 1);
         else
            usleep(5000);
         waits--;
      }
      else {
         break;
      }
   }

   if (ret) {
      LOGE("failed to perform page flip");
   }
   else if (drm->mode_page_flip_blocking) {
      /*
       * TODO page flip with DRM_MODE_PAGE_FLIP_EVENT instead of waiting for
       * next vblank
       */
      drm_kms_wait_vblank(drm, 1);
   }

   return ret;
}

int
drm_kms_post(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   int ret;

   if (!bo->fb_id) {
      LOGE("unable to post bo %p without fb", bo);
      return -EINVAL;
   }

   /* TODO spawn a thread to avoid waiting */

   if (drm->first_post) {
      pthread_mutex_lock(&drm->mutex);
      if (drm->first_post) {
         ret = drm_kms_set_crtc(drm, bo);
         if (!ret)
            drm->first_post = 0;
         pthread_mutex_unlock(&drm->mutex);

         return ret;
      }
      pthread_mutex_unlock(&drm->mutex);
   }

   if (drm->mode_page_flip && drm->swap_interval)
      ret = drm_kms_page_flip(drm, bo);
   else
      ret = drm_kms_set_crtc(drm, bo);

   return ret;
}

static int
drm_kms_init_with_connector_locked(struct drm_module_t *drm,
                                   drmModeConnectorPtr connector)
{
   drmModeEncoderPtr encoder;
   drmModeModeInfoPtr mode;
   int i;

   if (!connector->count_modes)
      return -EINVAL;

   encoder = drmModeGetEncoder(drm->fd, connector->encoders[0]);
   if (!encoder)
      return -EINVAL;

   for (i = 0; i < drm->resources->count_crtcs; i++) {
      if (encoder->possible_crtcs & (1 << i))
         break;
   }
   drmModeFreeEncoder(encoder);
   if (i == drm->resources->count_crtcs)
      return -EINVAL;

   drm->crtc_id = drm->resources->crtcs[i];
   drm->connector_id = connector->connector_id;

   /* find the first preferred mode */
   mode = NULL;
   for (i = 0; i < connector->count_modes; i++) {
      drmModeModeInfoPtr m = &connector->modes[i];
      if (m->type & DRM_MODE_TYPE_PREFERRED) {
         mode = m;
         break;
      }
   }
   /* no preference; use the first */
   if (!mode)
      mode = &connector->modes[0];

   drm->mode = *mode;

   if (connector->mmWidth && connector->mmHeight) {
      drm->xdpi = (drm->mode.hdisplay * 25.4 / connector->mmWidth);
      drm->ydpi = (drm->mode.vdisplay * 25.4 / connector->mmHeight);
   }
   else {
      drm->xdpi = 75;
      drm->ydpi = 75;
   }

   /* select between 32/16 bits */
#if 1
   drm->format = HAL_PIXEL_FORMAT_BGRA_8888;
#else
   drm->format = HAL_PIXEL_FORMAT_RGB_565;
#endif

#ifdef DRM_MODE_FEATURE_DIRTYFB
   drm->clip.x1 = 0;
   drm->clip.y1 = 0;
   drm->clip.x2 = drm->mode.hdisplay;
   drm->clip.y2 = drm->mode.vdisplay;
#endif

   drm->first_post = 1;

   return 0;
}

static int
drm_kms_init_locked(struct drm_module_t *drm)
{
   int i, ret;

   if (drm->resources)
      return 0;

   drm->resources = drmModeGetResources(drm->fd);
   if (!drm->resources) {
      LOGE("failed to get modeset resources");
      return -EINVAL;
   }

   for (i = 0; i < drm->resources->count_connectors; i++) {
      drmModeConnectorPtr connector;

      connector = drmModeGetConnector(drm->fd, drm->resources->connectors[i]);
      if (connector) {
         if (connector->connection == DRM_MODE_CONNECTED) {
            if (!drm_kms_init_with_connector_locked(drm, connector))
               break;
         }

         drmModeFreeConnector(connector);
      }
   }
   if (i == drm->resources->count_connectors) {
      drmModeFreeResources(drm->resources);
      drm->resources = NULL;

      return -EINVAL;
   }

   return 0;
}

int
drm_kms_init(struct drm_module_t *drm)
{
   int ret;

   pthread_mutex_lock(&drm->mutex);
   ret = drm_kms_init_locked(drm);
   pthread_mutex_unlock(&drm->mutex);

   return ret;
}
