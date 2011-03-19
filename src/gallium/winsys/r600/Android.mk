ifeq ($(strip $(MESA_BUILD_R600G)),true)

LOCAL_PATH := $(call my-dir)

# from drm/Makefile
C_SOURCES = \
	bof.c \
	evergreen_hw_context.c \
	radeon_bo.c \
	radeon_pciid.c \
	r600_bo.c \
	r600_drm.c \
	r600_hw_context.c \
	r600_bomgr.c

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(addprefix drm/, $(C_SOURCES))

LOCAL_CFLAGS := \
	-std=c99 \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary \
	external/mesa/src/gallium/drivers/r600 \
	external/drm \
	external/drm/include/drm

LOCAL_MODULE := libmesa_winsys_r600

include $(BUILD_STATIC_LIBRARY)

endif # MESA_BUILD_R600G
