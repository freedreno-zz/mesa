# $Id: Makefile,v 1.1.2.2 2002/12/04 16:00:05 keithw Exp $

# Mesa 3-D graphics library
# Version:  5.0
# Copyright (C) 1995-2002  Brian Paul



MESA = ../../..
MESABUILDDIR = $(MESA)/src
INCLUDES = -I$(MESABUILDDIR) -I$(MESA)/include -I. -I../common -I$(MESABUILDDIR)/miniglx
CFLAGS = $(INCLUDES) -g -MD -DGLX_DIRECT_RENDERING

# The .a files for each mesa module required by this driver:
#
COREMESA = 	$(MESABUILDDIR)/swrast_setup/swrast_setup.a \
		$(MESABUILDDIR)/tnl/tnl.a \
		$(MESABUILDDIR)/math/math.a \
		$(MESABUILDDIR)/array_cache/array_cache.a \
		$(MESABUILDDIR)/swrast/swrast.a \
		$(MESABUILDDIR)/mesa.a 

DRIVER_SOURCES = radeon_compat.c \
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

default: radeon_dri.so

radeon_dri.so:  $(COREMESA) $(OBJECTS) Makefile
	rm -f $@ && gcc -o $@ -shared $(OBJECTS) $(COREMESA) -L$(MESA)/src/miniglx -lGL -lc -lm

clean:
	-rm -f *.o *~ *.d .\#* *.so

tags:
	etags `find . -name \*.[ch]` `find ../include`

##### DEPENDENCIES #####

include $(C_SOURCES:.c=.d)

.SUFFIXES: .c .d

.c.d:
	$(CC) -M $(INCLUDES) $< > $@
