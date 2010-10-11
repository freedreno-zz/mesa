LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	android/android_sw_winsys.cpp

LOCAL_CFLAGS := \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary

LOCAL_MODULE := libmesa_winsys_sw

include $(BUILD_STATIC_LIBRARY)
