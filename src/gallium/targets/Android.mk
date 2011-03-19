# Android.mk for Gallium EGL and gralloc

LOCAL_PATH := $(call my-dir)

# EGL
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	egl-static/egl.c \
	egl-static/egl_pipe.c \
	egl-static/egl_st.c

LOCAL_CFLAGS := \
	-DFEATURE_ES1=1 \
	-DFEATURE_ES2=1 \
	-DGALLIUM_SOFTPIPE \
	-D_EGL_MAIN=_eglBuiltInDriverGALLIUM \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary \
	external/mesa/src/gallium/drivers \
	external/mesa/src/gallium/winsys \
	external/mesa/src/gallium/state_trackers/vega \
	external/mesa/src/gallium/state_trackers/egl \
	external/mesa/src/egl/main \
	external/mesa/src/mesa

LOCAL_STATIC_LIBRARIES := \
	libmesa_st_egl \
	libmesa_winsys_sw \
	libmesa_pipe_softpipe \
	libmesa_st_mesa \
	libmesa_glsl \
	libmesa_st_mesa \
	libmesa_gallium

LOCAL_WHOLE_STATIC_LIBRARIES := \
	libmesa_egl
	
LOCAL_SHARED_LIBRARIES := \
	libglapi \
	libdl \
	libhardware \
	liblog \
	libcutils

ifeq ($(strip $(MESA_BUILD_CLASSIC)),true)
LOCAL_STATIC_LIBRARIES :=  \
	libmesa_classic_egl \
	$(LOCAL_STATIC_LIBRARIES)
LOCAL_SHARED_LIBRARIES += libdrm
endif # MESA_BUILD_CLASSIC

ifeq ($(strip $(MESA_BUILD_I915G)),true)
LOCAL_CFLAGS += -D_EGL_PIPE_I915
LOCAL_STATIC_LIBRARIES := \
	libmesa_winsys_i915 \
	libmesa_pipe_i915 \
	$(LOCAL_STATIC_LIBRARIES)
LOCAL_SHARED_LIBRARIES += \
	libdrm \
	libdrm_intel
endif # MESA_BUILD_I915G

ifeq ($(strip $(MESA_BUILD_R600G)),true)
LOCAL_CFLAGS += -D_EGL_PIPE_R600
LOCAL_STATIC_LIBRARIES := \
	libmesa_pipe_r600 \
	libmesa_winsys_r600 \
	$(LOCAL_STATIC_LIBRARIES)
LOCAL_SHARED_LIBRARIES += \
	libdrm \
	libdrm_radeon
endif # MESA_BUILD_R600G

LOCAL_MODULE := libGLES_mesa
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/egl

include $(BUILD_SHARED_LIBRARY)

# gralloc (broken!)
ifeq ($(strip $(MESA_BUILD_VMWGFX)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := egl/egl_pipe.c

LOCAL_CFLAGS := \
	-D_EGL_PIPE_VMWGFX=1 \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary \
	external/mesa/src/gallium/drivers \
	external/mesa/src/gallium/winsys

LOCAL_STATIC_LIBRARIES := \
	libmesa_pipe_svga \
	libmesa_winsys_svga \
	libmesa_gallium

LOCAL_WHOLE_STATIC_LIBRARIES := \
	libmesa_st_gralloc
	
LOCAL_SHARED_LIBRARIES := \
	libdl \
	liblog \
	libcutils \
	libdrm \
	libEGL

LOCAL_MODULE := gralloc.mesa
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

include $(BUILD_SHARED_LIBRARY)
endif # MESA_BUILD_VMWGFX
