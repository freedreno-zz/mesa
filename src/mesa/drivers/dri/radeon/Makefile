# $Id: Makefile,v 1.1.2.21 2003/02/03 21:33:02 keithw Exp $

# Mesa 3-D graphics library
# Version:  5.0
# Copyright (C) 1995-2002  Brian Paul



MESA = ../../..
MESABUILDDIR = ../..

INCLUDES = -I$(MESABUILDDIR) -I$(MESA)/include -I. -I../common \
	   -I$(MESABUILDDIR)/miniglx -Iserver

DEFINES = \
	-D_HAVE_SWRAST=0 \
	-D_HAVE_SWTNL=0 \
	-D_HAVE_SANITY=0 \
	-D_HAVE_CODEGEN=0 \
	-D_HAVE_LIGHTING=0 \
	-D_HAVE_TEXGEN=0 \
	-D_HAVE_USERCLIP=0

CFLAGS = $(INCLUDES) $(DEFINES) -g -MD 

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

DRIVER_SOURCES = server/radeon_dri.c \
		 radeon_context.c \
		 radeon_ioctl.c \
		 radeon_lock.c \
		 radeon_screen.c \
		 radeon_state.c \
		 radeon_state_init.c \
		 radeon_tex.c \
		 radeon_texmem.c \
		 radeon_texstate.c \
		 ../common/mm.c 

SUBSET_DRIVER_SOURCES = \
		radeon_subset_bitmap.c \
		radeon_subset_readpix.c \
		radeon_subset_feedback.c \
		radeon_subset_vtx.c 

FULL_DRIVER_SOURCES = 	\
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



C_SOURCES = $(DRIVER_SOURCES) \
	    $(SUBSET_DRIVER_SOURCES) \
	    $(DRI_SOURCES) 

ASM_SOURCES = 

OBJECTS = $(C_SOURCES:.c=.o) \
	  $(ASM_SOURCES:.S=.o) 



##### RULES #####

.S.o:
	$(CC) -c $(CFLAGS) $< -o $@

.c.o: 
	$(CC) -c $(CFLAGS) $< -o $@

##### TARGETS #####

default: radeon_dri.so install

radeon_dri.so:  $(FULL_MESA) $(OBJECTS) Makefile
	rm -f $@ && gcc -o $@ -shared $(OBJECTS) $(FULL_MESA) -L$(MESA)/src/miniglx -lGL -lc -lm

loc:
	wc -l $(DRIVER_SOURCES)
	wc -l $(SUBSET_DRIVER_SOURCES)
	wc -l $(FULL_DRIVER_SOURCES)

install:
	rm -f $(MESA)/lib/radeon_dri.so && \
	install radeon_dri.so $(MESA)/lib/radeon_dri.so

clean:
	-rm -f *.o *~ *.d .\#* *.so

tags:
	etags `find . -name \*.[ch]` `find ../include`

##### DEPENDENCIES #####

-include $(C_SOURCES:.c=.d)

.SUFFIXES: .c .d

.c.d:
	$(CC) -M $(INCLUDES) $(DEFINES) $< > $@
