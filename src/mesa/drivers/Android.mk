# Android.mk for DRI drivers

LOCAL_PATH := $(call my-dir)

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

# from dri/i965/Makefile
i965_DRIVER_SOURCES = \
	intel_batchbuffer.c \
	intel_blit.c \
	intel_buffer_objects.c \
	intel_buffers.c \
	intel_clear.c \
	intel_context.c \
	intel_decode.c \
	intel_extensions.c \
	intel_extensions_es2.c \
	intel_fbo.c \
	intel_mipmap_tree.c \
	intel_regions.c \
	intel_screen.c \
	intel_span.c \
	intel_pixel.c \
	intel_pixel_bitmap.c \
	intel_pixel_copy.c \
	intel_pixel_draw.c \
	intel_pixel_read.c \
	intel_state.c \
	intel_syncobj.c \
	intel_tex.c \
	intel_tex_copy.c \
	intel_tex_format.c \
	intel_tex_image.c \
	intel_tex_layout.c \
	intel_tex_subimage.c \
	intel_tex_validate.c \
	brw_cc.c \
	brw_clip.c \
	brw_clip_line.c \
	brw_clip_point.c \
	brw_clip_state.c \
	brw_clip_tri.c \
	brw_clip_unfilled.c \
	brw_clip_util.c \
	brw_context.c \
	brw_curbe.c \
	brw_disasm.c \
	brw_draw.c \
	brw_draw_upload.c \
	brw_eu.c \
	brw_eu_debug.c \
	brw_eu_emit.c \
	brw_eu_util.c \
	brw_fallback.c \
	brw_gs.c \
	brw_gs_emit.c \
	brw_gs_state.c \
	brw_misc_state.c \
	brw_optimize.c \
	brw_program.c \
	brw_queryobj.c \
	brw_sf.c \
	brw_sf_emit.c \
	brw_sf_state.c \
	brw_state.c \
	brw_state_batch.c \
	brw_state_cache.c \
	brw_state_dump.c \
	brw_state_upload.c \
	brw_tex.c \
	brw_tex_layout.c \
	brw_urb.c \
	brw_util.c \
	brw_vs.c \
	brw_vs_constval.c \
	brw_vs_emit.c \
	brw_vs_state.c \
	brw_vs_surface_state.c \
	brw_vtbl.c \
	brw_wm.c \
	brw_wm_debug.c \
	brw_wm_emit.c \
	brw_wm_fp.c \
	brw_wm_iz.c \
	brw_wm_pass0.c \
	brw_wm_pass1.c \
	brw_wm_pass2.c \
	brw_wm_sampler_state.c \
	brw_wm_state.c \
	brw_wm_surface_state.c \
	gen6_cc.c \
	gen6_clip_state.c \
	gen6_depthstencil.c \
	gen6_gs_state.c \
	gen6_sampler_state.c \
	gen6_scissor_state.c \
	gen6_sf_state.c \
	gen6_urb.c \
	gen6_viewport_state.c \
	gen6_vs_state.c \
	gen6_wm_state.c
i965_CXX_SOURCES = \
	brw_cubemap_normalize.cpp \
	brw_fs.cpp \
	brw_fs_channel_expressions.cpp \
	brw_fs_reg_allocate.cpp \
	brw_fs_schedule_instructions.cpp \
	brw_fs_vector_splitting.cpp
i965_DRIVER_SOURCES := \
	$(addprefix dri/i965/, $(i965_DRIVER_SOURCES)) \
	$(addprefix dri/i965/, $(i965_CXX_SOURCES))

# from dri/Makefile.template
common_SOURCES = \
	dri/common/utils.c \
	dri/common/vblank.c \
	dri/common/dri_util.c \
	dri/common/xmlconfig.c \
	dri/common/texmem.c \
	dri/common/drirenderbuffer.c \
	common/driverfuncs.c

common_CFLAGS := \
	-DPTHREADS \
	-DFEATURE_GL=1 \
	-DFEATURE_ES1=1 \
	-DFEATURE_ES2=1 \
	-fvisibility=hidden \
	-Wno-sign-compare

common_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/mapi \
	external/mesa/src/glsl \
	external/mesa/src/mesa \
	external/mesa/src/mesa/drivers/dri/common \
	external/drm/ \
	external/drm/include/drm \
	external/expat/lib

common_STATIC_LIBRARIES := \
	libmesa_classic_mesa \
	libmesa_glsl \
	libmesa_classic_mesa

common_SHARED_LIBRARIES := \
	libglapi \
	libdl \
	libdrm \
	libexpat \
	liblog \
	libcutils

common_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/dri

ifeq ($(strip $(MESA_BUILD_I915C)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(common_SOURCES) \
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

LOCAL_SHARED_LIBRARIES := \
	$(common_SHARED_LIBRARIES) \
	libdrm_intel

LOCAL_MODULE := i915_dri
LOCAL_MODULE_PATH := $(common_MODULE_PATH)

include $(BUILD_SHARED_LIBRARY)
endif # MESA_BUILD_I915C

ifeq ($(strip $(MESA_BUILD_I965C)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(common_SOURCES) \
	$(i965_DRIVER_SOURCES)

LOCAL_CFLAGS := \
	$(common_CFLAGS) \
	-DI965

LOCAL_C_INCLUDES := \
	$(common_C_INCLUDES) \
	external/mesa/src/mesa/drivers/dri/intel \
	external/drm/intel

LOCAL_STATIC_LIBRARIES := \
	$(common_STATIC_LIBRARIES)

LOCAL_SHARED_LIBRARIES := \
	$(common_SHARED_LIBRARIES) \
	libdrm_intel

LOCAL_MODULE := i965_dri
LOCAL_MODULE_PATH := $(common_MODULE_PATH)

include $(BUILD_SHARED_LIBRARY)
endif # MESA_BUILD_I965C
