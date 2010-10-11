LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/sources.mak

common_CFLAGS := \
	-DPTHREADS \
	-DFEATURE_ES1=1 \
	-DFEATURE_ES2=1 \
	-fvisibility=hidden \
	-Wno-sign-compare

common_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/mapi \
	external/mesa/src/glsl \
	external/mesa/src/talloc

ifeq ($(strip $(MESA_BUILD_GALLIUM)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(filter-out $(MAIN_ES_SOURCES), $(MESA_GALLIUM_SOURCES)) \
	$(MESA_GALLIUM_CXX_SOURCES)

LOCAL_CFLAGS := \
	$(common_CFLAGS)

LOCAL_C_INCLUDES := \
	$(common_C_INCLUDES) \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary

LOCAL_MODULE := libmesa_st_mesa
LOCAL_MODULE_CLASS := STATIC_LIBRARIES

#GEN_SCRIPT := python $(LOCAL_PATH)/main/es_generator.py
#intermediates := $(call local-intermediates-dir)
#
#GEN := $(intermediates)/main/api_exec_es1.c
#$(GEN): PRIVATE_CUSTOM_TOOL = $(GEN_SCRIPT) -S $< -V GLES1.1 > $@
#$(GEN): $(LOCAL_PATH)/main/APIspec.xml
#	$(transform-generated-source)
#
#LOCAL_GENERATED_SOURCES += $(GEN)
#
#GEN := $(intermediates)/main/api_exec_es2.c
#$(GEN): PRIVATE_CUSTOM_TOOL = $(GEN_SCRIPT) -S $< -V GLES2.0 > $@
#$(GEN): $(LOCAL_PATH)/main/APIspec.xml
#	$(transform-generated-source)
#
#LOCAL_GENERATED_SOURCES += $(GEN)
#
#LOCAL_C_INCLUDES += \
#	$(call intermediates-dir-for,SHARED_LIBRARIES,libGLESv1_CM_mesa) \
#	$(call intermediates-dir-for,SHARED_LIBRARIES,libGLESv2_mesa)
LOCAL_SRC_FILES += $(MAIN_ES_SOURCES)

include $(BUILD_STATIC_LIBRARY)
endif # MESA_BUILD_GALLIUM

ifeq ($(strip $(MESA_BUILD_CLASSIC)),true)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(MESA_SOURCES) \
	$(MESA_CXX_SOURCES)

LOCAL_CFLAGS := \
	$(common_CFLAGS) \
	-DFEATURE_GL=1

LOCAL_C_INCLUDES := \
	$(common_C_INCLUDES)

LOCAL_MODULE := libmesa_classic_mesa

include $(BUILD_STATIC_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))
endif # MESA_BUILD_CLASSIC
