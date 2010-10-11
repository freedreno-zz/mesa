# Android.mk for gralloc

LOCAL_PATH := $(call my-dir)

common_SRC_FILES := \
	gralloc_gem.c \
	gralloc_kms.c \
	gralloc_mod.c

common_C_INCLUDES := \
	external/drm \
	external/drm/include/drm

common_SHARED_LIBRARIES := \
	libdrm \
	liblog \
	libcutils

ifeq ($(strip $(MESA_BUILD_INTEL)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(common_SRC_FILES) \
	gralloc_gem_i915.c

LOCAL_C_INCLUDES := \
	$(common_C_INCLUDES) \
	external/drm/intel

LOCAL_SHARED_LIBRARIES := \
	$(common_SHARED_LIBRARIES) \
	libdrm_intel \
	libEGL

LOCAL_MODULE := gralloc.mesa
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

include $(BUILD_SHARED_LIBRARY)
endif # MESA_BUILD_INTEL

ifeq ($(strip $(MESA_BUILD_GALLIUM)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(common_SRC_FILES) \
	gralloc_gem_pipe.c

LOCAL_C_INCLUDES := \
	$(common_C_INCLUDES) \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary

LOCAL_MODULE := libmesa_st_gralloc

include $(BUILD_STATIC_LIBRARY)
endif # MESA_BUILD_GALLIUM
