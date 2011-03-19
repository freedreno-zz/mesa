#define LOG_TAG "GRALLOC-GEM"

#include <cutils/log.h>
#include <cutils/atomic.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "gralloc_mod.h"
#include "gralloc_gem.h"

#define unlikely(x) __builtin_expect(!!(x), 0)

#define DRM_PATH "/dev/dri/card0"

static int32_t drm_gem_pid = 0;

static int
drm_gem_get_pid(void)
{
   if (unlikely(!drm_gem_pid))
      android_atomic_write((int32_t) getpid(), &drm_gem_pid);
   return drm_gem_pid;
}

static int
drm_gem_init_locked(struct drm_module_t *drm)
{
   int ret;

   if (drm->fd >= 0)
      return 0;

   drm->fd = open(DRM_PATH, O_RDWR);
   if (drm->fd < 0) {
      LOGE("failed to open %s", DRM_PATH);
      return -EINVAL;
   }

   return 0;
}

int
drm_gem_init(struct drm_module_t *drm)
{
   int ret;

   pthread_mutex_lock(&drm->mutex);
   ret = drm_gem_init_locked(drm);
   pthread_mutex_unlock(&drm->mutex);

   return ret;
}

int
drm_gem_get_magic(struct drm_module_t *drm, int32_t *magic)
{
   int ret;

   ret = drm_gem_init(drm);
   if (ret)
      return ret;

   return drmGetMagic(drm->fd, (drm_magic_t *) magic);
}

int
drm_gem_auth_magic(struct drm_module_t *drm, int32_t magic)
{
   int ret;

   ret = drm_gem_init(drm);
   if (ret)
      return ret;

   return drmAuthMagic(drm->fd, (drm_magic_t) magic);
}

struct drm_bo_t *
drm_gem_create_bo(int width, int height, int format, int usage)
{
   struct drm_bo_t *bo;

   bo = calloc(1, sizeof(*bo));
   if (!bo)
      return NULL;

   bo->base.version = sizeof(bo->base);
   bo->base.numInts = DRM_HANDLE_NUM_INTS;
   bo->base.numFds = DRM_HANDLE_NUM_FDS;

   bo->magic = DRM_HANDLE_MAGIC;

   bo->width = width;
   bo->height = height;
   bo->format = format;
   bo->usage = usage;

   bo->pid = drm_gem_get_pid();

   return bo;
}

struct drm_bo_t *
drm_gem_validate(buffer_handle_t handle)
{
   struct drm_bo_t *bo = drm_gem_get(handle);

   if (bo && unlikely(bo->pid != drm_gem_pid)) {
      bo->pid = drm_gem_get_pid();
      bo->fb_handle = 0;
      bo->fb_id = 0;
      bo->data = 0;
   }

   return bo;
}

static const struct drm_gem_drv *
get_drv_from_fd(int fd)
{
   const struct drm_gem_drv *drv = NULL;
   drmVersionPtr version;

   version = drmGetVersion(fd);
   if (!version) {
      LOGE("invalid DRM fd");
      return NULL;
   }

   if (version->name) {
#ifdef ENABLE_INTEL
      if (!drv && !strcmp(version->name, "intel"))
         drv = &drm_gem_drv_intel;
#endif
#ifdef ENABLE_RADEON
      if (!drv && !strcmp(version->name, "radeon"))
         drv = &drm_gem_drv_radeon;
#endif
#ifdef ENABLE_VMWGFX
      if (!drv && !strcmp(version->name, "vmwgfx"))
         drv = &drm_gem_drv_pipe;
#endif
   }

   if (!drv)
      LOGE("unknown driver: %s", (version->name) ? version->name : "NULL");

   drmFreeVersion(version);

   return drv;
}

static int
drm_gem_drv_init_locked(struct drm_module_t *drm)
{
   const struct drm_gem_drv *drv;
   int ret;

   if (drm->gem)
      return 0;

   drv = get_drv_from_fd(drm->fd);
   if (!drv)
      return -EINVAL;

   ret = drv->init(drm);
   if (!ret)
      drm->drv = (void *) drv;

   return ret;
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
