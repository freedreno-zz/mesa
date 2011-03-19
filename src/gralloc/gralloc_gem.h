#ifndef _GRALLOC_GEM_H_
#define _GRALLOC_GEM_H_

#include <cutils/native_handle.h>
#include "gralloc_mod.h"

struct drm_bo_t {
   native_handle_t base;

#define DRM_HANDLE_MAGIC 0x12345678
#define DRM_HANDLE_NUM_INTS 11
#define DRM_HANDLE_NUM_FDS 0
   int magic;

   int width;
   int height;
   int format;
   int usage;

   int name;
   int stride;

   /* these fields are undefined until validated */
   int pid;
   int fb_handle;
   int fb_id;
   int data; /* pointer as int? 32-bit only! */
};

int
drm_gem_init(struct drm_module_t *drm);

int
drm_gem_get_magic(struct drm_module_t *drm, int32_t *magic);

int
drm_gem_auth_magic(struct drm_module_t *drm, int32_t magic);

static inline struct drm_bo_t *
drm_gem_get(buffer_handle_t handle)
{
   struct drm_bo_t *bo = (struct drm_bo_t *) handle;

   if (bo->base.version != sizeof(bo->base) ||
       bo->base.numInts != DRM_HANDLE_NUM_INTS ||
       bo->base.numFds != DRM_HANDLE_NUM_FDS ||
       bo->magic != DRM_HANDLE_MAGIC)
      bo = NULL;

   return bo;
}

struct drm_bo_t *
drm_gem_validate(buffer_handle_t handle);

struct drm_bo_t *
drm_gem_create_bo(int width, int height, int format, int usage);

int
drm_gem_drv_init(struct drm_module_t *drm);


struct drm_gem_drv {
   int (*init)(struct drm_module_t *drm);

   struct drm_bo_t *(*alloc)(struct drm_module_t *drm, int width, int height,
                             int format, int usage, int *stride);

   void (*free)(struct drm_module_t *drm, struct drm_bo_t *bo);

   int (*map)(struct drm_module_t *drm, struct drm_bo_t *bo,
              int x, int y, int w, int h, int enable_write, void **addr);

   void (*unmap)(struct drm_module_t *drm, struct drm_bo_t *bo);
};

extern const struct drm_gem_drv drm_gem_drv_intel;
extern const struct drm_gem_drv drm_gem_drv_pipe;

static inline struct drm_bo_t *
drm_gem_drv_alloc(struct drm_module_t *drm, int width, int height,
                  int format, int usage, int *stride)
{
   const struct drm_gem_drv *drv = (const struct drm_gem_drv *) drm->drv;
   return drv->alloc(drm, width, height, format, usage, stride);
}

static inline void
drm_gem_drv_free(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   const struct drm_gem_drv *drv = (const struct drm_gem_drv *) drm->drv;
   drv->free(drm, bo);
}

static inline int
drm_gem_drv_map(struct drm_module_t *drm, struct drm_bo_t *bo,
                int x, int y, int w, int h, int enable_write, void **addr)
{
   const struct drm_gem_drv *drv = (const struct drm_gem_drv *) drm->drv;
   return drv->map(drm, bo, x, y, w, h, enable_write, addr);
}

static inline void
drm_gem_drv_unmap(struct drm_module_t *drm, struct drm_bo_t *bo)
{
   const struct drm_gem_drv *drv = (const struct drm_gem_drv *) drm->drv;
   drv->unmap(drm, bo);
}

#endif /* _GRALLOC_GEM_H_ */
