# $Id: Makefile,v 1.1.2.2 2003/03/04 17:29:55 keithw Exp $

# Mesa 3-D graphics library
# Version:  5.0
# Copyright (C) 1995-2002  Brian Paul



MESA = ../..
default: dri.a
include $(MESA)/Makefile.include

INCLUDES = -I/usr/X11R6/include -I/usr/X11R6/include/X11/extensions -I$(MESA)/include -I. -I..
DEFINES = 

C_SOURCES = dri_glx.c \
	    dri_util.c \
	    xf86drm.c \
	    xf86drmHash.c \
	    xf86drmRandom.c \
	    xf86drmSL.c

ASM_SOURCES = 

OBJECTS = $(C_SOURCES:.c=.o) \
	  $(ASM_SOURCES:.S=.o) 



##### TARGETS #####

dri.a: $(OBJECTS) Makefile
	rm -f $@ && ar rcv $@ $(OBJECTS) && ranlib $@

##### DEPENDENCIES #####

-include $(C_SOURCES:.c=.d)
