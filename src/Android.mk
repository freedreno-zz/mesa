LOCAL_PATH := $(call my-dir)

# build classic static libraries
MESA_BUILD_CLASSIC := false

# build gallium static libraries
MESA_BUILD_GALLIUM := false

# build gralloc.i915
MESA_BUILD_I915 := false

# build libGLES_i915c
MESA_BUILD_I915C := false

# build libGLES_swrast
MESA_BUILD_SWRAST := false

# build gralloc.vmwgfx
MESA_BUILD_VMWGFX := false

# build libGLES_i915g
MESA_BUILD_I915G := false

# for testing purpose
#BOARD_USES_I915C := true
#BOARD_USES_I915G := true
#BOARD_USES_VMWGFX := true

MESA_GRALLOC_NAME := 
MESA_GLES_NAME :=

ifeq ($(strip $(BOARD_USES_I915C)),true)
MESA_BUILD_CLASSIC := true
MESA_BUILD_I915 := true
MESA_BUILD_I915C := true

MESA_GRALLOC_NAME := i915
MESA_GLES_NAME := i915c
endif

ifeq ($(strip $(BOARD_USES_I915G)),true)
MESA_BUILD_GALLIUM := true
MESA_BUILD_I915 := true
MESA_BUILD_I915G := true

MESA_GRALLOC_NAME := i915
MESA_GLES_NAME := i915g
endif

ifeq ($(strip $(BOARD_USES_VMWGFX)),true)
MESA_BUILD_GALLIUM := true
MESA_BUILD_SWRAST := true
MESA_BUILD_VMWGFX := true

MESA_GRALLOC_NAME := vmwgfx
MESA_GLES_NAME := swrast
endif

ifneq ($(strip $(MESA_GRALLOC_NAME) $(MESA_GLES_NAME)),)

# build the real modules
include $(call all-subdir-makefiles)

include $(CLEAR_VARS)

symlink := $(TARGET_OUT_SHARED_LIBRARIES)/hw/gralloc.$(TARGET_PRODUCT)$(TARGET_SHLIB_SUFFIX)
symlink_to := gralloc.$(MESA_GRALLOC_NAME)$(TARGET_SHLIB_SUFFIX)
$(symlink): PRIVATE_TO := $(symlink_to)
$(symlink): $(TARGET_OUT_SHARED_LIBRARIES)/hw/$(symlink_to)
	@echo "Symlink: $@ -> $(PRIVATE_TO)"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -sf $(PRIVATE_TO) $@
ALL_PREBUILT += $(symlink)

symlink := $(TARGET_OUT_SHARED_LIBRARIES)/egl/libGLES_mesa$(TARGET_SHLIB_SUFFIX)
symlink_to := libGLES_$(MESA_GLES_NAME)$(TARGET_SHLIB_SUFFIX)
$(symlink): PRIVATE_TO := $(symlink_to)
$(symlink): $(TARGET_OUT_SHARED_LIBRARIES)/egl/$(symlink_to)
	@echo "Symlink: $@ -> $(PRIVATE_TO)"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -sf $(PRIVATE_TO) $@
ALL_PREBUILT += $(symlink)

endif # MESA_GRALLOC_NAME || MESA_GLES_NAME
