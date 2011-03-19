ifeq ($(strip $(MESA_BUILD_R600G)),true)

LOCAL_PATH := $(call my-dir)

# from Makefile
C_SOURCES = \
	r600_asm.c \
	r600_blit.c \
	r600_buffer.c \
	r600_helper.c \
	r600_pipe.c \
	r600_query.c \
	r600_resource.c \
	r600_shader.c \
	r600_state.c \
	r600_texture.c \
	r700_asm.c \
	evergreen_state.c \
	eg_asm.c \
	r600_translate.c \
	r600_state_common.c

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(C_SOURCES)

LOCAL_CFLAGS := \
	-std=c99 \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary \
	external/drm \
	external/drm/include/drm

LOCAL_MODULE := libmesa_pipe_r600

include $(BUILD_STATIC_LIBRARY)

endif # MESA_BUILD_R600G
