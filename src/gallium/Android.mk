ifeq ($(strip $(MESA_BUILD_GALLIUM)),true)
include $(call all-subdir-makefiles)
endif
