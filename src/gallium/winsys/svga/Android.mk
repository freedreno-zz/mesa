ifeq ($(strip $(MESA_BUILD_VMWGFX)),true)

LOCAL_PATH := $(call my-dir)

# from drm/Makefile
C_SOURCES = \
        vmw_buffer.c \
        vmw_context.c  \
        vmw_fence.c  \
        vmw_screen.c  \
        vmw_screen_dri.c  \
        vmw_screen_ioctl.c  \
        vmw_screen_pools.c  \
        vmw_screen_svga.c  \
        vmw_surface.c

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(addprefix drm/, $(C_SOURCES))

LOCAL_CFLAGS := \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary \
	external/mesa/src/gallium/drivers/svga \
	external/mesa/src/gallium/drivers/svga/include \
	external/drm \
	external/drm/include/drm

LOCAL_MODULE := libmesa_winsys_svga

include $(BUILD_STATIC_LIBRARY)

endif # MESA_BUILD_VMWGFX
