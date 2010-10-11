LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/glapi/sources.mak
include $(LOCAL_PATH)/mapi/sources.mak
glapi_SOURCES := \
	$(addprefix glapi/, $(GLAPI_SOURCES)) \
	$(addprefix mapi/, $(MAPI_GLAPI_SOURCES))

glapi_CFLAGS := \
	-DPTHREADS \
	-DMAPI_GLAPI_CURRENT \
	-fvisibility=hidden \
	-Wno-sign-compare

glapi_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/mapi

include $(CLEAR_VARS)

LOCAL_MODULE := libmesa_glapi

LOCAL_SRC_FILES := $(glapi_SOURCES)
LOCAL_CFLAGS := $(glapi_CFLAGS)

## generate glapi headers
#intermediates := $(call local-intermediates-dir)
#glapi_OUT := $(intermediates)/es1api
#glapi_XML := $(LOCAL_PATH)/glapi/gen-es/es1_API.xml
#include $(LOCAL_PATH)/generate_glapi.mk
#
## depend on the generated headers
#$(intermediates)/%.o: $(LOCAL_GENERATED_SOURCES)
glapi_OUT := external/mesa/src/mapi/es1api

LOCAL_C_INCLUDES := $(glapi_OUT) $(glapi_C_INCLUDES)

include $(BUILD_STATIC_LIBRARY)
