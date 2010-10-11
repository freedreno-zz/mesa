# Android.mk for glapi

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

include $(LOCAL_PATH)/mapi/sources.mak
LOCAL_SRC_FILES := $(addprefix mapi/, $(MAPI_GLAPI_SOURCES))

LOCAL_CFLAGS := \
	-DPTHREADS \
	-DMAPI_MODE_GLAPI \
	-DMAPI_ABI_HEADER=\"shared-glapi/glapi_mapi_tmp.h\" \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/mapi

LOCAL_MODULE := libglapi

include $(BUILD_SHARED_LIBRARY)
