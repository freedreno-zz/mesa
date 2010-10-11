ifeq ($(strip $(MESA_BUILD_I915G)),true)

LOCAL_PATH := $(call my-dir)

# from Makefile
C_SOURCES = \
	i915_blit.c \
	i915_clear.c \
	i915_flush.c \
	i915_context.c \
	i915_debug.c \
	i915_debug_fp.c \
	i915_state.c \
	i915_state_immediate.c \
	i915_state_dynamic.c \
	i915_state_derived.c \
	i915_state_emit.c \
	i915_state_fpc.c \
	i915_state_sampler.c \
	i915_state_static.c \
	i915_screen.c \
	i915_prim_emit.c \
	i915_prim_vbuf.c \
	i915_resource.c \
	i915_resource_texture.c \
	i915_resource_buffer.c \
	i915_fpc_emit.c \
	i915_fpc_translate.c \
	i915_surface.c 

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(C_SOURCES)

LOCAL_CFLAGS := \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary

LOCAL_MODULE := libmesa_pipe_i915

include $(BUILD_STATIC_LIBRARY)

endif # MESA_BUILD_I915G
