# $Id: Makefile,v 1.1.2.24 2003/02/23 19:37:52 keithw Exp $

# Mesa 3-D graphics library
# Version:  5.0
# Copyright (C) 1995-2002  Brian Paul



MESA = ../../..
MESABUILDDIR = ../..

SHARED_INCLUDES = -I$(MESABUILDDIR) -I$(MESA)/include -I. -I../common -Iserver
MINIGLX_INCLUDES = -I$(MESABUILDDIR)/miniglx 
DRI_INCLUDES = -I$(MESABUILDDIR)/dri

DEFINES = \
	-D_HAVE_SWRAST=0 \
	-D_HAVE_SWTNL=0 \
	-D_HAVE_SANITY=0 \
	-D_HAVE_CODEGEN=0 \
	-D_HAVE_LIGHTING=0 \
	-D_HAVE_TEXGEN=0 \
	-D_HAVE_USERCLIP=0 \
	-D_HAVE_FULL_GL=0

CFLAGS = $(INCLUDES) $(DEFINES) -O1 -MD -Wall -Wpointer-arith \
	 -Wstrict-prototypes -Wmissing-prototypes \
	 -Wmissing-declarations -Wnested-externs

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

DRI =           $(MESABUILDDIR)/dri/dri.a

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

C_SOURCES = $(DRIVER_SOURCES) \
	    $(SUBSET_DRIVER_SOURCES) \
	    $(MINIGLX_SOURCES) 

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

radeon_dri.so:  $(SUBSET_MESA) $(OBJECTS) Makefile
	rm -f $@ && gcc -o $@ -shared $(OBJECTS) $(SUBSET_MESA) -L$(MESA)/src/miniglx -lGL -lc -lm

#radeon_dri.so:  $(SUBSET_MESA) $(DRI) $(OBJECTS) Makefile
#	rm -f $@ && gcc -o $@ -shared $(OBJECTS) $(SUBSET_MESA) $(DRI) -lc -lm


loc:
	wc -l $(DRIVER_SOURCES) $(SUBSET_DRIVER_SOURCES)
	wc -l $(DRIVER_SOURCES) $(FULL_DRIVER_SOURCES) radeon_maos_verts.c radeon_maos_vbtmp.h

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
