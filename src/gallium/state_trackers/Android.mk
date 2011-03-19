LOCAL_PATH := $(call my-dir)

common_SOURCES := \
	egl/common/egl_g3d.c \
	egl/common/egl_g3d_api.c \
	egl/common/egl_g3d_image.c \
	egl/common/egl_g3d_st.c \
	egl/common/egl_g3d_sync.c \
	egl/common/native_helper.c

android_SOURCES := \
	egl/android/native_android.cpp

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(common_SOURCES) \
	$(android_SOURCES)

LOCAL_CFLAGS := \
	-DHAVE_ANDROID_BACKEND \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary \
	external/mesa/src/egl/main \
	external/mesa/src/gallium/state_trackers/egl \
	external/mesa/src/gallium/winsys \
	external/mesa/src/gallium/winsys/sw \
	external/mesa/src/gralloc \
	external/drm \
	external/drm/include/drm

LOCAL_MODULE := libmesa_st_egl

include $(BUILD_STATIC_LIBRARY)
