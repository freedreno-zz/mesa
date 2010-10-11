GLAPI := $(LOCAL_PATH)/glapi/gen

GEN := $(glapi_OUT)/glapi/glapidispatch.h
$(GEN): PRIVATE_CUSTOM_TOOL := python $(GLAPI)/gl_table.py -f $(glapi_XML) -c -m remap_table > $(GEN)
$(GEN): $(glapi_XML)
	$(transform-generated-source)

LOCAL_GENERATED_SOURCES += $(GEN)

GEN := $(glapi_OUT)/glapi/glapioffsets.h
$(GEN): PRIVATE_CUSTOM_TOOL := python $(GLAPI)/gl_offsets.py -f $(glapi_XML) -c > $(GEN)
$(GEN): $(glapi_XML)
	$(transform-generated-source)

LOCAL_GENERATED_SOURCES += $(GEN)

GEN := $(glapi_OUT)/glapi/glapitable.h
$(GEN): PRIVATE_CUSTOM_TOOL := python $(GLAPI)/gl_table.py -f $(glapi_XML) -c > $(GEN)
$(GEN): $(glapi_XML)
	$(transform-generated-source)

LOCAL_GENERATED_SOURCES += $(GEN)

GEN := $(glapi_OUT)/glapi/glapitemp.h
$(GEN): PRIVATE_CUSTOM_TOOL := python $(GLAPI)/gl_apitemp.py -f $(glapi_XML) -c > $(GEN)
$(GEN): $(glapi_XML)
	$(transform-generated-source)

LOCAL_GENERATED_SOURCES += $(GEN)

GEN := $(glapi_OUT)/glapi/glprocs.h
$(GEN): PRIVATE_CUSTOM_TOOL := python $(GLAPI)/gl_procs.py -f $(glapi_XML) -c > $(GEN)
$(GEN): $(glapi_XML)
	$(transform-generated-source)

LOCAL_GENERATED_SOURCES += $(GEN)

GEN := $(glapi_OUT)/main/remap_helper.h
$(GEN): PRIVATE_CUSTOM_TOOL := python $(GLAPI)/remap_helper.py -f $(glapi_XML) > $(GEN)
$(GEN): $(glapi_XML)
	$(transform-generated-source)

LOCAL_GENERATED_SOURCES += $(GEN)
