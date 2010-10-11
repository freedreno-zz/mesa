LOCAL_PATH := $(call my-dir)

gles_SRC_FILES := \
	egl-gdi/egl-static.c

gles_CFLAGS := \
	-DFEATURE_ES1=1 \
	-DFEATURE_ES2=1 \
	-DGALLIUM_SOFTPIPE \
	-fvisibility=hidden \
	-Wno-sign-compare

gles_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary \
	external/mesa/src/gallium/drivers \
	external/mesa/src/gallium/winsys \
	external/mesa/src/gallium/state_trackers/vega \
	external/mesa/src/gallium/state_trackers/egl \
	external/mesa/src/egl/main \
	external/mesa/src/mesa

gles_STATIC_LIBRARIES := \
	libmesa_st_egl \
	libmesa_winsys_sw \
	libmesa_pipe_softpipe \
	libmesa_st_mesa \
	libmesa_glsl \
	libmesa_st_mesa \
	libmesa_talloc \
	libmesa_gallium

gles_WHOLE_STATIC_LIBRARIES := \
	libmesa_egl \
	libmesa_glapi
	
gles_SHARED_LIBRARIES := \
	libdl \
	libhardware \
	liblog \
	libcutils

gralloc_SRC_FILES :=

gralloc_CFLAGS := \
	-fvisibility=hidden \
	-Wno-sign-compare

gralloc_C_INCLUDES := \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary \
	external/mesa/src/gallium/drivers \
	external/mesa/src/gallium/winsys

gralloc_STATIC_LIBRARIES := \
	libmesa_gallium

gralloc_WHOLE_STATIC_LIBRARIES := \
	libmesa_st_gralloc
	
gralloc_SHARED_LIBRARIES := \
	libdl \
	liblog \
	libcutils \
	libdrm \
	libEGL

ifeq ($(strip $(MESA_BUILD_SWRAST)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(gles_SRC_FILES)

LOCAL_CFLAGS := \
	$(gles_CFLAGS)

LOCAL_C_INCLUDES := \
	$(gles_C_INCLUDES)

LOCAL_STATIC_LIBRARIES := \
	$(gles_STATIC_LIBRARIES)

LOCAL_WHOLE_STATIC_LIBRARIES := \
	$(gles_WHOLE_STATIC_LIBRARIES)
	
LOCAL_SHARED_LIBRARIES := \
	$(gles_SHARED_LIBRARIES)

LOCAL_MODULE := libGLES_swrast
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/egl

include $(BUILD_SHARED_LIBRARY)
endif # MESA_BUILD_SWRAST

ifeq ($(strip $(MESA_BUILD_I915G)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(gles_SRC_FILES) \
	egl/pipe_i915.c

LOCAL_CFLAGS := \
	$(gles_CFLAGS) \
	-DFEATURE_DRM=1

LOCAL_C_INCLUDES := \
	$(gles_C_INCLUDES)

LOCAL_STATIC_LIBRARIES := \
	libmesa_winsys_i915 \
	libmesa_pipe_i915 \
	$(gles_STATIC_LIBRARIES)

LOCAL_WHOLE_STATIC_LIBRARIES := \
	$(gles_WHOLE_STATIC_LIBRARIES)
	
LOCAL_SHARED_LIBRARIES := \
	$(gles_SHARED_LIBRARIES) \
	libdrm \
	libdrm_intel

LOCAL_MODULE := libGLES_i915g
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/egl

include $(BUILD_SHARED_LIBRARY)
endif # MESA_BUILD_I915G

ifeq ($(strip $(MESA_BUILD_VMWGFX)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	egl/pipe_vmwgfx.c \
	$(gralloc_SRC_FILES)

LOCAL_CFLAGS := \
	$(gralloc_CFLAGS)

LOCAL_C_INCLUDES := \
	$(gralloc_C_INCLUDES)

LOCAL_STATIC_LIBRARIES := \
	libmesa_pipe_svga \
	libmesa_winsys_svga \
	$(gralloc_STATIC_LIBRARIES)

LOCAL_WHOLE_STATIC_LIBRARIES := \
	$(gralloc_WHOLE_STATIC_LIBRARIES)
	
LOCAL_SHARED_LIBRARIES := \
	$(gralloc_SHARED_LIBRARIES)

LOCAL_MODULE := gralloc.vmwgfx
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

include $(BUILD_SHARED_LIBRARY)
endif # MESA_BUILD_VMWGFX
