# Build a subset DRI-based libGL.so library.
# Indirect rendering not supported, etc.

MESA=../..
default: libGL.so.1.2 install drmtest
include $(MESA)/Makefile.include

SOURCES = dispatch.c \
	  dri_util.c \
	  glapi.c \
	  miniglx.c \
	  miniglx_events.c \
	  xf86drm.c 

OBJS = $(SOURCES:.c=.o)

INCLUDES = -I. -I.. -I$(MESA)/include
LIBS = -ldl 


libGL.so.1.2: $(OBJS) Makefile
	gcc -shared -Wl,-soname,libGL.so -Wl,-Bsymbolic $(OBJS) $(LIBS) -o $@ 

install:
	rm -f $(MESA)/lib/libGL.so* 
	rm -f $(MESA)/lib/miniglx.conf
	install -D libGL.so.1.2 $(MESA)/lib/libGL.so.1.2
	ln -s libGL.so.1.2 $(MESA)/lib/libGL.so.1
	ln -s libGL.so.1 $(MESA)/lib/libGL.so
	install example.miniglx.conf $(MESA)/lib/miniglx.conf


drmtest: xf86drm.o drmtest.o
	rm -f drmtest && $(CC) -o drmtest xf86drm.o drmtest.o

glapi.c: ../glapi.c
	ln -s ../glapi.c .

clean: clean_here

clean_here:
	rm -f drmtest glapi.c $(MESA)/lib/libGL.so*

-include $(SOURCES:.c=.d)
