#define LOG_TAG "GRALLOC-PIPE"

#include <cutils/log.h>
#include <errno.h>

#include "pipe/p_screen.h"
#include "pipe/p_context.h"
#include "state_tracker/drm_driver.h"
#include "util/u_inlines.h"
#include "util/u_memory.h"

#include "gralloc_mod.h"
#include "gralloc_gem.h"

struct drm_pipe_manager {
   pthread_mutex_t mutex;
   struct pipe_screen *screen;
   struct pipe_context *context;
};

struct drm_pipe_buffer {
   struct winsys_handle winsys;
   uint32_t fb_handle;
   struct pipe_resource *resource;
   struct pipe_transfer *transfer;
};

static void
drm_gem_pipe_init_features(struct drm_module_t *drm)
{
   drm->mode_dirty_fb = 0;
   drm->mode_page_flip = 0;

   if (strcmp(driver_descriptor.driver_name, "vmwgfx") == 0)
      drm->mode_dirty_fb = 1;

   drm->swap_interval = 0;
}

static int
drm_gem_pipe_init(struct drm_module_t *drm)
{
   struct drm_pipe_manager *pm;

   pm = CALLOC(1, sizeof(*pm));
   if (!pm)
      return -ENOMEM;

   pthread_mutex_init(&pm->mutex, NULL);

   pm->screen = driver_descriptor.create_screen(drm->fd);
   if (!pm->screen) {
      LOGE("failed to create pipe screen");
      FREE(pm);
      return -EINVAL;
   }

   drm->gem = (void *) pm;

   drm_gem_pipe_init_features(drm);

   return 0;
}

static enum pipe_format
get_pipe_format(int format)
{
   enum pipe_format fmt;

   switch (format) {
   case HAL_PIXEL_FORMAT_RGBA_8888:
      fmt = PIPE_FORMAT_R8G8B8A8_UNORM;
      break;
   case HAL_PIXEL_FORMAT_RGBX_8888:
      fmt = PIPE_FORMAT_R8G8B8X8_UNORM;
      break;
   case HAL_PIXEL_FORMAT_RGB_888:
      fmt = PIPE_FORMAT_R8G8B8_UNORM;
      break;
   case HAL_PIXEL_FORMAT_RGB_565:
      fmt = PIPE_FORMAT_B5G6R5_UNORM;
      break;
   case HAL_PIXEL_FORMAT_BGRA_8888:
      fmt = PIPE_FORMAT_B8G8R8A8_UNORM;
      break;
   case HAL_PIXEL_FORMAT_RGBA_5551:
   case HAL_PIXEL_FORMAT_RGBA_4444:
   default:
      fmt = PIPE_FORMAT_NONE;
      break;
   }

   return fmt;
}

static unsigned
get_pipe_bind(int usage)
{
   unsigned bind = PIPE_BIND_SHARED;

   if (usage & GRALLOC_USAGE_SW_READ_MASK)
      bind |= PIPE_BIND_TRANSFER_READ;
   if (usage & GRALLOC_USAGE_SW_WRITE_MASK)
      bind |= PIPE_BIND_TRANSFER_WRITE;

   if (usage & GRALLOC_USAGE_HW_TEXTURE)
      bind |= PIPE_BIND_SAMPLER_VIEW;
   if (usage & GRALLOC_USAGE_HW_RENDER)
      bind |= PIPE_BIND_RENDER_TARGET;
   if (usage & GRALLOC_USAGE_HW_FB) {
      bind |= PIPE_BIND_RENDER_TARGET;
      bind |= PIPE_BIND_SCANOUT;
   }

   return bind;
}

static struct drm_pipe_buffer *
get_pipe_buffer(struct drm_pipe_manager *pm, int width, int height,
                int format, int usage, struct winsys_handle *winsys)
{
   struct drm_pipe_buffer *buf;
   struct pipe_resource templ;

   memset(&templ, 0, sizeof(templ));
   templ.format = get_pipe_format(format);
   templ.bind = get_pipe_bind(usage);
   templ.target = PIPE_TEXTURE_2D;

   if (templ.format == PIPE_FORMAT_NONE ||
       !pm->screen->is_format_supported(pm->screen, templ.format,
                                        templ.target, 0, templ.bind)) {
      LOGE("unsupported format 0x%x", format);
      return NULL;
   }

   buf = CALLOC(1, sizeof(*buf));
   if (!buf)
      return NULL;

   templ.width0 = width;
   templ.height0 = height;
   templ.depth0 = 1;

   if (winsys) {
      buf->resource = pm->screen->resource_from_handle(pm->screen,
            &templ, winsys);
      if (!buf->resource)
         goto fail;

      buf->winsys = *winsys;
   }
   else {
      buf->resource = pm->screen->resource_create(pm->screen, &templ);
      if (!buf->resource)
         goto fail;

      buf->winsys.type = DRM_API_HANDLE_TYPE_SHARED;
      if (!pm->screen->resource_get_handle(pm->screen, buf->resource, &buf->winsys))
         goto fail;
   }

   /* need the gem handle for fb */
   if (usage & GRALLOC_USAGE_HW_FB) {
      struct winsys_handle tmp;

      memset(&tmp, 0, sizeof(tmp));
      tmp.type = DRM_API_HANDLE_TYPE_KMS;
      if (!pm->screen->resource_get_handle(pm->screen, buf->resource, &tmp))
         goto fail;

      buf->fb_handle = tmp.handle;
   }

   return buf;

fail:
   LOGE("failed to allocate pipe buffer");
   if (buf->resource)
      pipe_resource_reference(&buf->resource, NULL);
   FREE(buf);

   return NULL;
}

static struct drm_bo_t *
drm_gem_pipe_alloc(struct drm_module_t *drm, int width, int height,
                   int format, int usage, int *stride)
{
   struct drm_pipe_manager *pm = (struct drm_pipe_manager *) drm->gem;
   struct drm_pipe_buffer *buf;
   struct drm_bo_t *bo;
   struct pipe_resource templ;

   bo = drm_gem_create_bo(width, height, format, usage);
   if (!bo)
      return NULL;

   pthread_mutex_lock(&pm->mutex);
   buf = get_pipe_buffer(pm, width, height, format, usage, NULL);
   pthread_mutex_unlock(&pm->mutex);

   if (buf) {
      bo->name = (int) buf->winsys.handle;
      bo->stride = (int) buf->winsys.stride;

      bo->fb_handle = buf->fb_handle;
      bo->data = (int) buf;

      *stride = bo->stride;
   }
   else {
      free(bo);
      bo = NULL;
   }

   return bo;
}

static void
drm_gem_pipe_free(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   struct drm_pipe_manager *pm = (struct drm_pipe_manager *) drm->gem;
   struct drm_pipe_buffer *buf = (struct drm_pipe_buffer *) bo->data;

   pthread_mutex_lock(&pm->mutex);

   if (buf->transfer)
      pipe_transfer_destroy(pm->context, buf->transfer);
   pipe_resource_reference(&buf->resource, NULL);

   pthread_mutex_unlock(&pm->mutex);

   FREE(buf);
   free(bo);
}

static int
drm_gem_pipe_map(struct drm_module_t *drm, struct drm_bo_t *bo,
                 int x, int y, int w, int h, int enable_write, void **addr)
{
   struct drm_pipe_manager *pm = (struct drm_pipe_manager *) drm->gem;
   struct drm_pipe_buffer *buf = (struct drm_pipe_buffer *) bo->data;
   enum pipe_transfer_usage usage = 0;
   int ret = 0;

   pthread_mutex_lock(&pm->mutex);

   /* need a context to get transfer */
   if (!pm->context) {
      pm->context = pm->screen->context_create(pm->screen, NULL);
      if (!pm->context) {
         LOGE("failed to create pipe context");
         ret = -ENOMEM;
      }
   }

   /* the bo was allocated by another process */
   if (!buf && !ret) {
      struct winsys_handle winsys;

      memset(&winsys, 0, sizeof(winsys));
      winsys.type = DRM_API_HANDLE_TYPE_SHARED;
      winsys.handle = bo->name;
      winsys.stride = bo->stride;

      buf = get_pipe_buffer(pm, bo->width, bo->height,
            bo->format, bo->usage, &winsys);
      if (!buf) {
         LOGE("failed to create pipe buffer from name %u", bo->name);
         ret = -ENOMEM;
      }

      bo->data = (int) buf;
   }

   if (buf) {
      usage = PIPE_TRANSFER_READ;
      if (enable_write)
         usage |= PIPE_TRANSFER_WRITE;

      assert(!buf->transfer);

      /*
       * ignore x, y, w and h so that returned addr points at the start of the
       * buffer
       */
      buf->transfer = pipe_get_transfer(pm->context, buf->resource,
            0, 0, usage, 0, 0, bo->width, bo->height);
      if (buf->transfer)
         *addr = pipe_transfer_map(pm->context, buf->transfer);
      else
         ret = -ENOMEM;
   }

   pthread_mutex_unlock(&pm->mutex);

   return ret;
}

static void
drm_gem_pipe_unmap(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   struct drm_pipe_manager *pm = (struct drm_pipe_manager *) drm->gem;
   struct drm_pipe_buffer *buf = (struct drm_pipe_buffer *) bo->data;

   pthread_mutex_lock(&pm->mutex);

   assert(buf && buf->transfer);

   pipe_transfer_unmap(pm->context, buf->transfer);
   pipe_transfer_destroy(pm->context, buf->transfer);
   buf->transfer = NULL;

   pm->context->flush(pm->context, NULL);

   pthread_mutex_unlock(&pm->mutex);
}

const struct drm_gem_drv drm_gem_drv_pipe = {
   .init = drm_gem_pipe_init,
   .alloc = drm_gem_pipe_alloc,
   .free = drm_gem_pipe_free,
   .map = drm_gem_pipe_map,
   .unmap = drm_gem_pipe_unmap,
};
