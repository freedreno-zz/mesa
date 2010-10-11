LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	talloc.c

LOCAL_CFLAGS := \
	-fvisibility=hidden

LOCAL_MODULE := libmesa_talloc

include $(BUILD_STATIC_LIBRARY)
