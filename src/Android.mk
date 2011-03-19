# Either one of, or both of, MESA_BUILD_CLASSIC and MESA_BUILD_GALLIUM must be
# set.  When MESA_BUILD_GALLIUM is not set, EGL consists of
# 
#   libmesa_classic_egl
#   libmesa_egl
#
# and the rules for it can be found in egl/drivers/android/Android.mk.
#
# When MESA_BUILD_GALLIUM is set, EGL consists of
#
#   libmesa_st_egl
#   libmesa_egl
#   libmesa_st_mesa
#   libmesa_pipe_<DRIVER>
#   libmesa_winsys_<DRIVER>
#   libmesa_gallium
#   <plus libmesa_classic_egl if MESA_BUILD_CLASSIC is also set>
#
# and the rules for it can be found in gallium/targets/Android.mk
#
# When MESA_BUILD_CLASSIC is set, DRI drivers are created.  A DRI driver
# consists of
#
#   libmesa_classic_mesa
#   libmesa_glsl
#   <driver-specific objects>
#
# and the rules for it can be found in mesa/drivers/Android.mk.
#
# As for gralloc,  the goal is to provide a single module that is able to
# detect and support the hardware.  This is not the case yet though.

LOCAL_PATH := $(call my-dir)

# DRI drivers
MESA_BUILD_CLASSIC := false
MESA_BUILD_I915C := false
MESA_BUILD_I965C := false

# Gallium drivers
MESA_BUILD_GALLIUM := false
MESA_BUILD_I915G := false
MESA_BUILD_R600G := false
MESA_BUILD_SWRAST := false

# gralloc modules
MESA_BUILD_INTEL := false
MESA_BUILD_RADEON := false
MESA_BUILD_VMWGFX := false

MESA_DO_BUILD := false

ifeq ($(strip $(BOARD_USES_I915C)),true)
MESA_BUILD_CLASSIC := true
MESA_BUILD_I915C := true
# gralloc
MESA_BUILD_INTEL := true

MESA_DO_BUILD := true
endif

ifeq ($(strip $(BOARD_USES_I915G)),true)
MESA_BUILD_GALLIUM := true
MESA_BUILD_I915G := true
# gralloc
MESA_BUILD_INTEL := true

MESA_DO_BUILD := true
endif

ifeq ($(strip $(BOARD_USES_I965C)),true)
MESA_BUILD_CLASSIC := true
MESA_BUILD_I965C := true
# gralloc
MESA_BUILD_INTEL := true

MESA_DO_BUILD := true
endif

ifeq ($(strip $(BOARD_USES_R600G)),true)
MESA_BUILD_GALLIUM := true
MESA_BUILD_R600G := true
# gralloc
MESA_BUILD_RADEON := true

MESA_DO_BUILD := true
endif

ifeq ($(strip $(BOARD_USES_VMWGFX)),true)
MESA_BUILD_GALLIUM := true
MESA_BUILD_SWRAST := true
# gralloc
MESA_BUILD_VMWGFX := true

MESA_DO_BUILD := true
endif

ifeq ($(strip $(MESA_DO_BUILD)),true)

# build the real modules
include $(call all-subdir-makefiles)

include $(CLEAR_VARS)

symlink := $(TARGET_OUT_SHARED_LIBRARIES)/hw/gralloc.$(TARGET_PRODUCT)$(TARGET_SHLIB_SUFFIX)
symlink_to := gralloc.mesa$(TARGET_SHLIB_SUFFIX)
$(symlink): PRIVATE_TO := $(symlink_to)
$(symlink): $(TARGET_OUT_SHARED_LIBRARIES)/hw/$(symlink_to)
	@echo "Symlink: $@ -> $(PRIVATE_TO)"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -sf $(PRIVATE_TO) $@
ALL_PREBUILT += $(symlink)

endif # MESA_DO_BUILD
