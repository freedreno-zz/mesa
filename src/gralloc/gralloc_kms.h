#ifndef _DRM_KMS_H_
#define _DRM_KMS_H_

#include "gralloc_mod.h"
#include "gralloc_gem.h"

int
drm_kms_init(struct drm_module_t *drm);

int
drm_kms_add_fb(struct drm_module_t *drm, struct drm_bo_t *bo);

void
drm_kms_rm_fb(struct drm_module_t *drm, struct drm_bo_t *bo);

int
drm_kms_post(struct drm_module_t *drm, struct drm_bo_t *bo);

#endif /* _DRM_KMS_H_ */
