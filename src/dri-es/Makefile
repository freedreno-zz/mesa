# $Id: Makefile,v 1.1.2.1 2003/02/05 04:37:12 keithw Exp $

# Mesa 3-D graphics library
# Version:  5.0
# Copyright (C) 1995-2002  Brian Paul



MESA = ../..
MESABUILDDIR = ..


INCLUDES = -I/usr/X11R6/include -I/usr/X11R6/include/X11/extensions -I$(MESA)/include -I. -I..
DEFINES = 

CFLAGS = $(INCLUDES) $(DEFINES) -g -MD -Wall -Wpointer-arith \
	 -Wstrict-prototypes -Wmissing-prototypes \
	 -Wmissing-declarations -Wnested-externs

# The .a files for each mesa module required by this driver:
#
DRI_SOURCES = dri_glx.c \
	      dri_util.c \
	      xf86drm.c \
	      xf86drmHash.c \
	      xf86drmRandom.c \
	      xf86drmSL.c


C_SOURCES = $(DRI_SOURCES) 

ASM_SOURCES = 

OBJECTS = $(C_SOURCES:.c=.o) \
	  $(ASM_SOURCES:.S=.o) 



##### RULES #####

.S.o:
	$(CC) -c $(CFLAGS) $< -o $@

.c.o: 
	$(CC) -c $(CFLAGS) $< -o $@

##### TARGETS #####

default: dri.a

dri.a: $(OBJECTS) Makefile
	rm -f $@ && ar rcv $@ $(OBJECTS) && ranlib $@

clean:
	-rm -f *.o *~ *.d .\#* *.so

tags:
	etags `find . -name \*.[ch]` `find ../include`

##### DEPENDENCIES #####

-include $(C_SOURCES:.c=.d)

.SUFFIXES: .c .d

.c.d:
	$(CC) -M $(INCLUDES) $(DEFINES) $< > $@
