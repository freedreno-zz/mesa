ifeq ($(strip $(MESA_BUILD_I915G)),true)

LOCAL_PATH := $(call my-dir)

# from drm/Makefile
C_SOURCES = \
	i915_drm_batchbuffer.c \
	i915_drm_buffer.c \
	i915_drm_fence.c \
	i915_drm_winsys.c

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(addprefix drm/, $(C_SOURCES))

LOCAL_CFLAGS := \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary \
	external/mesa/src/gallium/drivers \
	external/drm \
	external/drm/include/drm \
	external/drm/intel

LOCAL_MODULE := libmesa_winsys_i915

include $(BUILD_STATIC_LIBRARY)

endif # MESA_BUILD_I915G
