LOCAL_PATH := $(call my-dir)

# from dri/Makefile.template
COMMON_SOURCES = \
	 dri/common/utils.c \
	 dri/common/vblank.c \
	 dri/common/dri_util.c \
	 dri/common/xmlconfig.c \
	 dri/common/texmem.c \
	 dri/common/drirenderbuffer.c \
	 dri/common/dri_metaops.c \
	 common/driverfuncs.c

# from dri/i915/Makefile
i915_DRIVER_SOURCES = \
	i830_context.c \
	i830_state.c \
	i830_texblend.c \
	i830_texstate.c \
	i830_vtbl.c \
	intel_render.c \
	intel_regions.c \
	intel_buffer_objects.c \
	intel_batchbuffer.c \
	intel_clear.c \
	intel_extensions.c \
	intel_extensions_es2.c \
	intel_mipmap_tree.c \
	intel_tex_layout.c \
	intel_tex_image.c \
	intel_tex_subimage.c \
	intel_tex_copy.c \
	intel_tex_validate.c \
	intel_tex_format.c \
	intel_tex.c \
	intel_pixel.c \
	intel_pixel_bitmap.c \
	intel_pixel_copy.c \
	intel_pixel_draw.c \
	intel_pixel_read.c \
	intel_buffers.c \
	intel_blit.c \
	i915_tex_layout.c \
	i915_texstate.c \
	i915_context.c \
	i915_debug.c \
	i915_debug_fp.c \
	i915_fragprog.c \
	i915_program.c \
	i915_state.c \
	i915_vtbl.c \
	intel_context.c \
	intel_decode.c \
	intel_screen.c \
	intel_span.c \
	intel_state.c \
	intel_syncobj.c \
	intel_tris.c \
	intel_fbo.c
i915_DRIVER_SOURCES := $(addprefix dri/i915/, $(i915_DRIVER_SOURCES))

common_CFLAGS := \
	-DPTHREADS \
	-DFEATURE_GL=1 \
	-DFEATURE_ES1=1 \
	-fvisibility=hidden \
	-Wno-sign-compare

common_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/mapi \
	external/mesa/src/glsl \
	external/mesa/src/talloc \
	external/mesa/src/mesa \
	external/mesa/src/mesa/drivers/dri/common \
	external/drm/ \
	external/drm/include/drm \
	external/expat/lib

common_STATIC_LIBRARIES := \
	libmesa_classic_mesa \
	libmesa_glsl \
	libmesa_classic_mesa \
	libmesa_talloc \
	libmesa_classic_egl

common_WHOLE_STATIC_LIBRARIES := \
	libmesa_egl \
	libmesa_glapi

common_SHARED_LIBRARIES := \
	libdl \
	libdrm \
	libexpat \
	libhardware \
	liblog \
	libcutils

ifeq ($(strip $(MESA_BUILD_I915C)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(COMMON_SOURCES) \
	$(i915_DRIVER_SOURCES)

LOCAL_CFLAGS := \
	$(common_CFLAGS) \
	-DI915

LOCAL_C_INCLUDES := \
	$(common_C_INCLUDES) \
	external/mesa/src/mesa/drivers/dri/intel \
	external/drm/intel

LOCAL_STATIC_LIBRARIES := \
	$(common_STATIC_LIBRARIES)

LOCAL_WHOLE_STATIC_LIBRARIES := \
	$(common_WHOLE_STATIC_LIBRARIES)

LOCAL_SHARED_LIBRARIES := \
	$(common_SHARED_LIBRARIES) \
	libdrm_intel

LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/egl
LOCAL_MODULE := libGLES_i915c

include $(BUILD_SHARED_LIBRARY)
endif # MESA_BUILD_I915C
