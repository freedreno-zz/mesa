LOCAL_PATH := $(call my-dir)

# from Makefile
C_SOURCES = \
	sp_fs_exec.c \
	sp_fs_sse.c \
	sp_clear.c \
	sp_fence.c \
	sp_flush.c \
	sp_query.c \
	sp_context.c \
	sp_draw_arrays.c \
	sp_prim_vbuf.c \
	sp_quad_pipe.c \
	sp_quad_stipple.c \
	sp_quad_depth_test.c \
	sp_quad_fs.c \
	sp_quad_blend.c \
	sp_screen.c \
        sp_setup.c \
	sp_state_blend.c \
	sp_state_clip.c \
	sp_state_derived.c \
	sp_state_sampler.c \
	sp_state_shader.c \
	sp_state_so.c \
	sp_state_rasterizer.c \
	sp_state_surface.c \
	sp_state_vertex.c \
	sp_texture.c \
	sp_tex_sample.c \
	sp_tex_tile_cache.c \
	sp_tile_cache.c \
	sp_surface.c

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(C_SOURCES)

LOCAL_CFLAGS := \
	-fvisibility=hidden \
	-Wno-sign-compare

LOCAL_C_INCLUDES := \
	external/mesa/include \
	external/mesa/src/gallium/include \
	external/mesa/src/gallium/auxiliary

LOCAL_MODULE := libmesa_pipe_softpipe

include $(BUILD_STATIC_LIBRARY)
