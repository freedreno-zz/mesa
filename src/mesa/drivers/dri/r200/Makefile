# $Id: Makefile,v 1.1.2.2 2003/04/15 09:47:37 keithw Exp $

# Mesa 3-D graphics library
# Version:  5.0
# Copyright (C) 1995-2002  Brian Paul



MESA = ../../..
default: r200_dri.so 
include $(MESA)/Makefile.include


SHARED_INCLUDES= -I$(MESABUILDDIR) -I$(MESA)/include -I. -I../common -Iserver
MINIGLX_INCLUDES = -I$(MESABUILDDIR)/miniglx 
DRI_INCLUDES = -I$(MESABUILDDIR)/dri

DEFINES = \
	-DGLX_DIRECT_RENDERING \
-Dlinux -D__i386__ -D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE -D_XOPEN_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE  -D_GNU_SOURCE   -DFUNCPROTO=15 -DNARROWPROTO -DXTHREADS  -D_REENTRANT -DXUSE_MTSAFE_API    -DMALLOC_0_RETURNS_NULL -DGLXEXT -DXF86DRI -DGLX_DIRECT_RENDERING -DGLX_USE_DLOPEN -DGLX_USE_MESA  -DX_BYTE_ORDER=X_LITTLE_ENDIAN \
	-D_HAVE_SWRAST=1 \
	-D_HAVE_SWTNL=1 \
	-D_HAVE_SANITY=1 \
	-D_HAVE_CODEGEN=1 \
	-D_HAVE_LIGHTING=1 \
	-D_HAVE_TEXGEN=1 \
	-D_HAVE_USERCLIP=1 \
	-D_HAVE_FULL_GL=1


# The .a files for each mesa module required by this driver:
#
FULL_MESA = 	$(MESABUILDDIR)/swrast_setup/swrast_setup.a \
		$(MESABUILDDIR)/tnl/tnl.a \
		$(MESABUILDDIR)/math/math.a \
		$(MESABUILDDIR)/array_cache/array_cache.a \
		$(MESABUILDDIR)/swrast/swrast.a \
		$(MESABUILDDIR)/mesa.a \
		$(MESABUILDDIR)/math/math.a #kludge


MINIGLX_SOURCES = server/radeon_dri.c 

DRIVER_SOURCES = r200_context.c \
		 r200_ioctl.c \
		 r200_lock.c \
		 r200_screen.c \
		 r200_state.c \
		 r200_state_init.c \
		 ../common/mm.c \
		 r200_cmdbuf.c \
		 r200_pixel.c \
		 r200_tex.c \
		 r200_texmem.c \
		 r200_texstate.c \
		 r200_tcl.c \
		 r200_swtcl.c \
		 r200_span.c \
		 r200_maos.c \
		 r200_sanity.c \
		 r200_vtxfmt.c \
		 r200_vtxfmt_c.c \
		 r200_vtxfmt_sse.c \
		 r200_vtxfmt_x86.c 


INCLUDES = $(MINIGLX_INCLUDES) \
	   $(SHARED_INCLUDES)


C_SOURCES = $(DRIVER_SOURCES) \
	    $(MINIGLX_SOURCES) 
MESA_MODULES = $(FULL_MESA)


ifeq ($(WINDOW_SYSTEM),dri)
WINOBJ=$(MESABUILDDIR)/dri/dri.a
WINLIB=
else
WINOBJ=
WINLIB=-L$(MESA)/src/miniglx
endif

ASM_SOURCES = 
OBJECTS = $(C_SOURCES:.c=.o) \
	  $(ASM_SOURCES:.S=.o) 

SYMLINKS = server/Makefile \
	server/radeon_common.h \
	server/radeon_dri.c \
	server/radeon_dri.h \
	server/radeon.h \
	server/radeon_macros.h \
	server/radeon_reg.h \
	server/radeon_sarea.h \


$(SYMLINKS):
	rm -f $@ && ln -s ../../radeon/$@ $@


##### TARGETS #####

clean: clean_here

clean_here:
	rm -f $(SYMLINKS)

# Build the subset or full driver?
#
r200_dri.so:  $(SYMLINKS) $(OBJECTS) $(MESA_MODULES) $(WINOBJ) Makefile
	rm -f $@ && gcc -o $@ -shared $(OBJECTS) $(MESA_MODULES) $(WINOBJ) $(WINLIB) -lGL -lc -lm -Wl,-rpath,../../../lib
	rm -f $(MESA)/lib/r200_dri.so && \
	install r200_dri.so $(MESA)/lib/r200_dri.so

##### DEPENDENCIES #####

-include $(C_SOURCES:.c=.d)
