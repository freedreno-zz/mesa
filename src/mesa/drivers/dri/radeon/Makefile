# $Id: Makefile,v 1.1.2.11 2003/01/18 12:25:56 keithw Exp $

# Mesa 3-D graphics library
# Version:  5.0
# Copyright (C) 1995-2002  Brian Paul



MESA = ../../..
MESABUILDDIR = ../..

INCLUDES = -I$(MESABUILDDIR) -I$(MESA)/include -I. -I../common \
	   -I$(MESABUILDDIR)/miniglx -Iserver

DEFINES = -D_HAVE_SWRAST=1 -D_HAVE_SWTNL=1 -D_HAVE_SANITY=1
CFLAGS = $(INCLUDES) $(DEFINES) -g -MD -DGLX_DIRECT_RENDERING

# The .a files for each mesa module required by this driver:
#
COREMESA = 	$(MESABUILDDIR)/swrast_setup/swrast_setup.a \
		$(MESABUILDDIR)/tnl/tnl.a \
		$(MESABUILDDIR)/math/math.a \
		$(MESABUILDDIR)/array_cache/array_cache.a \
		$(MESABUILDDIR)/swrast/swrast.a \
		$(MESABUILDDIR)/mesa.a \
		$(MESABUILDDIR)/math/math.a #kludge

DRIVER_SOURCES = server/radeon_dri.c \
	  	 radeon_compat.c \
		 radeon_context.c \
		 radeon_ioctl.c \
		 radeon_lock.c \
		 radeon_maos.c \
		 radeon_sanity.c \
		 radeon_screen.c \
		 radeon_span.c \
		 radeon_state.c \
		 radeon_state_init.c \
		 radeon_swtcl.c \
		 radeon_tcl.c \
		 radeon_tex.c \
		 radeon_texmem.c \
		 radeon_texstate.c \
		 radeon_vtxfmt.c \
		 radeon_vtxfmt_c.c \
		 radeon_vtxfmt_sse.c \
		 radeon_vtxfmt_x86.c \
		 ../common/mm.c 


C_SOURCES = $(DRIVER_SOURCES) \
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

radeon_dri.so:  $(COREMESA) $(OBJECTS) Makefile
	rm -f $@ && gcc -o $@ -shared $(OBJECTS) $(COREMESA) -L$(MESA)/src/miniglx -lGL -lc -lm

install:
	rm -f $(MESA)/lib/radeon_dri.so && \
	install -C radeon_dri.so $(MESA)/lib/radeon_dri.so

clean:
	-rm -f *.o *~ *.d .\#* *.so

tags:
	etags `find . -name \*.[ch]` `find ../include`

##### DEPENDENCIES #####

-include $(C_SOURCES:.c=.d)

.SUFFIXES: .c .d

.c.d:
	$(CC) -M $(INCLUDES) $(DEFINES) $< > $@
