LOCAL_PATH := $(call my-dir)

# from main/Makefile
SOURCES = \
	eglapi.c \
	eglarray.c \
	eglconfig.c \
	eglcontext.c \
	eglcurrent.c \
	egldisplay.c \
	egldriver.c \
	eglfallbacks.c \
	eglglobals.c \
	eglimage.c \
	egllog.c \
	eglmisc.c \
	eglmode.c \
	eglscreen.c \
	eglstring.c \
	eglsurface.c \
	eglsync.c

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(addprefix main/, $(SOURCES))

LOCAL_CFLAGS := \
	-DPTHREADS \
	-D_EGL_NATIVE_PLATFORM=_EGL_PLATFORM_ANDROID \
	-D_EGL_DRIVER_SEARCH_DIR=\"/system/lib/egl\" \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/include

LOCAL_MODULE := libmesa_egl

include $(BUILD_STATIC_LIBRARY)

ifeq ($(strip $(MESA_BUILD_CLASSIC)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	drivers/android/egl_android.c \
	drivers/android/droid.c \
	drivers/android/droid_core.c \
	drivers/android/droid_image.c


LOCAL_CFLAGS := \
	-DPTHREADS \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/mapi \
	external/mesa/src/egl/main \
	external/mesa/src/gralloc \
	external/drm \
	external/drm/include/drm

LOCAL_MODULE := libmesa_classic_egl

include $(BUILD_STATIC_LIBRARY)
endif # MESA_BUILD_CLASSIC
