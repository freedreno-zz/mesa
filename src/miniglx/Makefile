# Build a subset DRI-based libGL.so library.
# Indirect rendering not supported, etc.


#SOURCES = glxext.c dispatch.c glapi.c
SOURCES = miniglx.c dispatch.c glapi.c XF86dri.c
OBJS = $(SOURCES:.c=.o)

INCLUDES = -I. -I.. -I../../include
CFLAGS = -c -g $(INCLUDES) -MD 

LIBS = -ldl 



default: libGL.so.1.2 libGL.so.1 libGL.so


libGL.so.1.2: $(OBJS) Makefile
	gcc -shared -Wl,-soname,libGL.so -Wl,-Bsymbolic $(OBJS) $(LIBS) -o $@

libGL.so.1:
	ln -s libGL.so.1.2 libGL.so.1

libGL.so:
	ln -s libGL.so.1 libGL.so

glapi.c: ../glapi.c
	ln -s ../glapi.c .

clean:
	rm -f *~ *.o libGL.so* glapi.c *.d

include $(SOURCES:.c=.d)

.SUFFIXES: .c .d

.c.d:
	$(CC) -M $(INCLUDES) $< > $@
