include $(top_srcdir)/src/gallium/Automake.inc

noinst_LTLIBRARIES = libfd2xx.la

AM_CFLAGS = \
	-Wno-packed-bitfield-compat \
	-I$(top_srcdir)/src/gallium/drivers \
	-I$(top_srcdir)/src/gallium/drivers/freedreno \
	$(GALLIUM_CFLAGS) \
	$(FREEDRENO_CFLAGS) \
	$(PIC_FLAGS) \
	$(VISIBILITY_CFLAGS)

libfd2xx_la_SOURCES = \
	fd2_blend.c \
	fd2_clear.c \
	fd2_context.c \
	fd2_draw.c \
	fd2_emit.c \
	fd2_gmem.c \
	fd2_rasterizer.c \
	fd2_screen.c \
	fd2_texture.c \
	fd2_zsa.c \
	disasm-a2xx.c \
	ir-a2xx.c
