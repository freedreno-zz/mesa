# $Id: Makefile,v 1.1.2.27 2003/03/05 13:16:20 keithw Exp $

# Mesa 3-D graphics library
# Version:  5.0
# Copyright (C) 1995-2002  Brian Paul



MESA = ../../..
default: radeon_dri.so 
include $(MESA)/Makefile.include


SHARED_INCLUDES= -I$(MESABUILDDIR) -I$(MESA)/include -I. -I../common -Iserver
MINIGLX_INCLUDES = -I$(MESABUILDDIR)/miniglx 
DRI_INCLUDES = -I$(MESABUILDDIR)/dri

ifeq ($(FULL_DRIVER),true)
DEFINES = \
	-D_HAVE_SWRAST=1 \
	-D_HAVE_SWTNL=1 \
	-D_HAVE_SANITY=1 \
	-D_HAVE_CODEGEN=1 \
	-D_HAVE_LIGHTING=1 \
	-D_HAVE_TEXGEN=1 \
	-D_HAVE_USERCLIP=1 \
	-D_HAVE_FULL_GL=1
else
DEFINES = \
	-D_HAVE_SWRAST=0 \
	-D_HAVE_SWTNL=0 \
	-D_HAVE_SANITY=0 \
	-D_HAVE_CODEGEN=0 \
	-D_HAVE_LIGHTING=0 \
	-D_HAVE_TEXGEN=0 \
	-D_HAVE_USERCLIP=0 \
	-D_HAVE_FULL_GL=0
endif

# The .a files for each mesa module required by this driver:
#
FULL_MESA = 	$(MESABUILDDIR)/swrast_setup/swrast_setup.a \
		$(MESABUILDDIR)/tnl/tnl.a \
		$(MESABUILDDIR)/math/math.a \
		$(MESABUILDDIR)/array_cache/array_cache.a \
		$(MESABUILDDIR)/swrast/swrast.a \
		$(MESABUILDDIR)/mesa.a \
		$(MESABUILDDIR)/math/math.a #kludge

SUBSET_MESA = 	$(MESABUILDDIR)/mesa.a \
		$(MESABUILDDIR)/math/math.a



MINIGLX_SOURCES = server/radeon_dri.c 

DRIVER_SOURCES = radeon_context.c \
		 radeon_ioctl.c \
		 radeon_lock.c \
		 radeon_screen.c \
		 radeon_state.c \
		 radeon_state_init.c \
		 ../common/mm.c 

SUBSET_DRIVER_SOURCES = \
		radeon_subset_bitmap.c \
		radeon_subset_readpix.c \
		radeon_subset_select.c \
		radeon_subset_tex.c \
		radeon_subset_vtx.c 

FULL_DRIVER_SOURCES = 	\
		 radeon_tex.c \
		 radeon_texmem.c \
		 radeon_texstate.c \
		 radeon_texcombine.c \
		 radeon_lighting.c \
		 radeon_userclip.c \
		 radeon_texgen.c \
		 radeon_tcl.c \
		 radeon_swtcl.c \
		 radeon_span.c \
		 radeon_maos.c \
		 radeon_sanity.c \
	  	 radeon_compat.c \
		 radeon_vtxfmt.c \
		 radeon_vtxfmt_c.c \
		 radeon_vtxfmt_sse.c \
		 radeon_vtxfmt_x86.c 


INCLUDES = $(MINIGLX_INCLUDES) \
	   $(SHARED_INCLUDES)


ifeq ($(FULL_DRIVER),true)
C_SOURCES = $(DRIVER_SOURCES) \
	    $(FULL_DRIVER_SOURCES) \
	    $(MINIGLX_SOURCES) 
MESA_MODULES = $(FULL_MESA)
else
C_SOURCES = $(DRIVER_SOURCES) \
	    $(SUBSET_DRIVER_SOURCES) \
	    $(MINIGLX_SOURCES) 
MESA_MODULES = $(SUBSET_MESA)
endif


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



##### TARGETS #####


# Build the subset or full driver?
#
radeon_dri.so:  $(OBJECTS) $(MESA_MODULES) $(WINOBJ) Makefile
	rm -f $@ && gcc -o $@ -shared $(OBJECTS) $(MESA_MODULES) $(WINOBJ) $(WINLIB) -lGL -lc -lm
	rm -f $(MESA)/lib/radeon_dri.so && \
	install radeon_dri.so $(MESA)/lib/radeon_dri.so

##### DEPENDENCIES #####

-include $(C_SOURCES:.c=.d)
