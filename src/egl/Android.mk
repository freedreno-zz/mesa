# Android.mk for EGL

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

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

LOCAL_SRC_FILES := \
	$(addprefix main/, $(SOURCES))

LOCAL_CFLAGS := \
	-DPTHREADS \
	-D_EGL_NATIVE_PLATFORM=_EGL_PLATFORM_ANDROID \
	-D_EGL_DRIVER_SEARCH_DIR=\"/system/lib/egl\" \
	-D_EGL_OS_UNIX=1 \
	-fvisibility=hidden \
	-Wno-sign-compare

ifeq ($(strip $(MESA_BUILD_CLASSIC)),true)
LOCAL_CFLAGS += -D_EGL_BUILT_IN_DRIVER_ANDROID
endif
ifeq ($(strip $(MESA_BUILD_GALLIUM)),true)
LOCAL_CFLAGS += -D_EGL_BUILT_IN_DRIVER_GALLIUM
endif

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
	-D_EGL_MAIN=_eglBuiltInDriverANDROID \
	-DDEFAULT_DRIVER_DIR=\"/system/lib/dri\" \
	-DPTHREADS \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/mapi \
	external/mesa/src/egl/main \
	external/mesa/src/gralloc \
	external/drm \
	external/drm/include/drm \
	external/mesa/src/mesa/drivers \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/winsys

LOCAL_MODULE := libmesa_classic_egl

include $(BUILD_STATIC_LIBRARY)

# build libGLES if gallium is not enabled
ifneq ($(strip $(MESA_BUILD_GALLIUM)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES :=
LOCAL_CFLAGS :=
LOCAL_C_INCLUDES :=

LOCAL_STATIC_LIBRARIES :=
  
LOCAL_WHOLE_STATIC_LIBRARIES := \
	libmesa_classic_egl \
	libmesa_egl

LOCAL_SHARED_LIBRARIES := \
	libglapi \
	libdrm \
	libdl \
	libhardware \
	liblog \
	libcutils

LOCAL_MODULE := libGLES_mesa
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/egl

include $(BUILD_SHARED_LIBRARY)
endif # MESA_BUILD_GALLIUM

endif # MESA_BUILD_CLASSIC
