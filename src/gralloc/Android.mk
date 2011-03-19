# Android.mk for gralloc

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	gralloc_gem.c \
	gralloc_kms.c \
	gralloc_mod.c

LOCAL_C_INCLUDES := \
	external/drm \
	external/drm/include/drm

LOCAL_SHARED_LIBRARIES := \
	libdrm \
	liblog \
	libcutils \
	libEGL

ifeq ($(strip $(MESA_BUILD_INTEL)),true)
LOCAL_SRC_FILES += gralloc_gem_intel.c
LOCAL_C_INCLUDES += external/drm/intel
LOCAL_CFLAGS += -DENABLE_INTEL
LOCAL_SHARED_LIBRARIES += libdrm_intel
endif # MESA_BUILD_INTEL

ifeq ($(strip $(MESA_BUILD_RADEON)),true)
LOCAL_SRC_FILES += gralloc_gem_radeon.c
LOCAL_C_INCLUDES += external/drm/radeon
LOCAL_CFLAGS += -DENABLE_RADEON
LOCAL_SHARED_LIBRARIES += libdrm_radeon
endif # MESA_BUILD_INTEL

# this is broken
ifeq ($(strip $(MESA_BUILD_VMWGFX)),true)
LOCAL_SRC_FILES += gralloc_gem_pipe.c
LOCAL_C_INCLUDES += \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary
LOCAL_CFLAGS += -DENABLE_VMWGFX
endif # MESA_BUILD_VMWGFX

LOCAL_MODULE := gralloc.mesa
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

include $(BUILD_SHARED_LIBRARY)
