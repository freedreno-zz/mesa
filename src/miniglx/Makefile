# Build a subset DRI-based libGL.so library.
# Indirect rendering not supported, etc.

MESA=../..

SOURCES = dispatch.c \
	  dri_util.c \
	  glapi.c \
	  miniglx.c \
	  xf86drm.c 

OBJS = $(SOURCES:.c=.o)


INCLUDES = -I. -I.. -I$(MESA)/include
CFLAGS = -c -g $(INCLUDES) -MD 

LIBS = -ldl 



default: libGL.so.1.2 install drmtest


libGL.so.1.2: $(OBJS) Makefile
	gcc -shared -Wl,-soname,libGL.so -Wl,-Bsymbolic $(OBJS) $(LIBS) -o $@ 

install:
	rm -f $(MESA)/lib/libGL.so*
	install -D libGL.so.1.2 $(MESA)/lib/libGL.so.1.2
	ln -s libGL.so.1.2 $(MESA)/lib/libGL.so.1
	ln -s libGL.so.1 $(MESA)/lib/libGL.so

#miniglx.a: $(OBJECTS) Makefile
#	rm -f $@ && ar rcv $@ $(OBJECTS) && ranlib $@


drmtest: xf86drm.o drmtest.o
	rm -f drmtest && $(CC) -o drmtest xf86drm.o drmtest.o

glapi.c: ../glapi.c
	ln -s ../glapi.c .

clean:
	rm -f *~ .*~ *.o libGL.so* glapi.c *.d

tags:
	etags *.[ch]

-include $(SOURCES:.c=.d)

.SUFFIXES: .c .d

.c.d:
	$(CC) -M $(INCLUDES) $< > $@
