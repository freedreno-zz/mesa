LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/sources.mak

common_CFLAGS := \
	-DPTHREADS \
	-DFEATURE_ES1=1 \
	-DFEATURE_ES2=1 \
	-fvisibility=hidden \
	-Wno-sign-compare

ifeq ($(strip $(MESA_BUILD_CLASSIC)),true)
common_CFLAGS += -DFEATURE_GL=1
endif

common_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/mapi \
	external/mesa/src/glsl

ifeq ($(strip $(MESA_BUILD_GALLIUM)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(MESA_GALLIUM_SOURCES) \
	$(MESA_GALLIUM_CXX_SOURCES)

LOCAL_CFLAGS := $(common_CFLAGS)

LOCAL_C_INCLUDES := \
	$(common_C_INCLUDES) \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary

LOCAL_MODULE := libmesa_st_mesa

include $(BUILD_STATIC_LIBRARY)
endif # MESA_BUILD_GALLIUM

ifeq ($(strip $(MESA_BUILD_CLASSIC)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(MESA_SOURCES) \
	$(MESA_CXX_SOURCES)

LOCAL_CFLAGS := $(common_CFLAGS)
LOCAL_C_INCLUDES := $(common_C_INCLUDES)

LOCAL_MODULE := libmesa_classic_mesa

include $(BUILD_STATIC_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))
endif # MESA_BUILD_CLASSIC
