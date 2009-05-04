LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/sources

common_CFLAGS :=							\
	-DUSE_EXTERNAL_DXTN_LIB=1 -DHAVE_ALIAS -DIN_DRI_DRIVER		\
	-DGLX_DIRECT_RENDERING -DGLX_INDIRECT_RENDERING

common_CFLAGS += -DPTHREADS
# FIXME should we?
#common_CFLAGS += -DGLX_USE_TLS

ifeq ($(TARGET_ARCH),x86)
	MESA_ASM_SOURCES := $(X86_SOURCES)
	common_CFLAGS += -DUSE_X86_ASM -DUSE_MMX_ASM -DUSE_3DNOW_ASM	\
			 -DUSE_SSE_ASM
endif

common_C_INCLUDES :=			\
	$(LOCAL_PATH)/../../include	\
	$(LOCAL_PATH)			\
	$(LOCAL_PATH)/main


include $(CLEAR_VARS)

LOCAL_SRC_FILES := x86/gen_matypes.c
LOCAL_C_INCLUDES += $(common_C_INCLUDES)
LOCAL_CFLAGS +=	$(common_CFLAGS)
LOCAL_MODULE := gen_matypes

# build gen_matypes
ifeq ($(TARGET_ARCH),x86)
  include $(BUILD_HOST_EXECUTABLE)
endif


include $(CLEAR_VARS)

LOCAL_SRC_FILES :=			\
	$(MESA_SOURCES)			\
	$(MESA_ASM_SOURCES)

LOCAL_C_INCLUDES += $(common_C_INCLUDES)

LOCAL_CFLAGS +=				\
	$(common_CFLAGS)		\
	-Wno-sign-compare

LOCAL_MODULE := libmesa
LOCAL_MODULE_CLASS := STATIC_LIBRARIES

# generate matypes.h
ifeq ($(TARGET_ARCH),x86)
intermediates := $(local-intermediates-dir)
GEN := $(intermediates)/matypes.h
$(GEN): PRIVATE_CUSTOM_TOOL = $(HOST_OUT_EXECUTABLES)/gen_matypes > $@
$(GEN): $(HOST_OUT_EXECUTABLES)/gen_matypes
	$(transform-generated-source)

LOCAL_GENERATED_SOURCES += $(GEN)
LOCAL_C_INCLUDES += $(intermediates)
endif

include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)

i915_SOURCES = \
	i830_context.c \
	i830_metaops.c \
	i830_state.c \
	i830_texblend.c \
	i830_tex.c \
	i830_texstate.c \
	i830_vtbl.c \
	intel_render.c \
	intel_regions.c \
	intel_buffer_objects.c \
	intel_batchbuffer.c \
	intel_mipmap_tree.c \
	i915_tex_layout.c \
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
	i915_tex.c \
	i915_texstate.c \
	i915_context.c \
	i915_debug.c \
	i915_debug_fp.c \
	i915_fragprog.c \
	i915_metaops.c \
	i915_program.c \
	i915_state.c \
	i915_vtbl.c \
	intel_context.c \
	intel_decode.c \
	intel_screen.c \
	intel_span.c \
	intel_state.c \
	intel_tris.c \
	intel_fbo.c \
	intel_depthstencil.c
i915_SOURCES := $(addprefix drivers/dri/i915/, $(i915_SOURCES))

common_SOURCES = \
        utils.c \
        texmem.c \
        vblank.c \
        dri_util.c \
        xmlconfig.c \
        drirenderbuffer.c 
common_SOURCES := $(addprefix drivers/dri/common/, $(common_SOURCES))

LOCAL_SRC_FILES :=				\
	$(i915_SOURCES)				\
	$(common_SOURCES)

LOCAL_C_INCLUDES +=				\
	$(LOCAL_PATH)/drivers/dri/i915		\
	$(LOCAL_PATH)/drivers/dri/common	\
	$(LOCAL_PATH)/drivers/dri/intel		\
	$(LOCAL_PATH)/drivers/dri/intel/server	\
	$(common_C_INCLUDES)			\
	external/drm/libdrm			\
	external/drm/libdrm/intel		\
	external/drm/shared-core

LOCAL_CFLAGS +=					\
	$(common_CFLAGS)			\
	-DI915					\
	-DDRM_VBLANK_FLIP=DRM_VBLANK_FLIP	\
	-Wno-sign-compare

LOCAL_SHARED_LIBRARIES := libexpat libdrm libdrm_intel
LOCAL_STATIC_LIBRARIES := libmesa

LOCAL_MODULE := i915_dri
LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

include $(BUILD_SHARED_LIBRARY)
