
TOP = ../../../../..
include $(TOP)/configs/current

LIBNAME = i915_dri.so

DRIVER_SOURCES = \
	bufmgr_fake.c \
	intel_regions.c \
	intel_mipmap_tree.c \
	i915_tex_layout.c \
	intel_tex_image.c \
	intel_tex_subimage.c \
	intel_tex_copy.c \
	intel_tex_validate.c \
	intel_tex_format.c \
	intel_tex.c \
	intel_blit.c \
	i915_tex.c \
	i915_texstate.c \
	i915_context.c \
	i915_debug.c \
	i915_fragprog.c \
	i915_metaops.c \
	i915_program.c \
	i915_state.c \
	i915_texprog.c \
	i915_vtbl.c \
	intel_batchbuffer.c \
	intel_context.c \
	intel_ioctl.c \
	intel_pixel.c \
	intel_screen.c \
	intel_span.c \
	intel_state.c \
	intel_tris.c 


DISABLED = \
	intel_render.c \
	i830_context.c \
	i830_metaops.c \
	i830_state.c \
	i830_texblend.c \
	i830_tex.c \
	i830_texstate.c \
	i830_vtbl.c 

C_SOURCES = \
	$(COMMON_SOURCES) \
	$(MINIGLX_SOURCES) \
	$(DRIVER_SOURCES)

ASM_SOURCES = 



include ../Makefile.template

symlinks:
