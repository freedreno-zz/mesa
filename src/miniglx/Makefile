# Build a subset DRI-based libGL.so library.
# Indirect rendering not supported, etc.


OBJS = glxext.o dispatch.o glapi.o

CFLAGS = -c -g -I. -I.. -I../../include

LIBS = -ldl -L/usr/X11R6/lib -lX11



default: libGL.so.1.2 libGL.so.1 libGL.so


libGL.so.1.2: $(OBJS)
	gcc -shared -Wl,-soname,libGL.so -Wl,-Bsymbolic $(OBJS) $(LIBS) -o $@

libGL.so.1:
	ln -s libGL.so.1.2 libGL.so.1

libGL.so:
	ln -s libGL.so.1 libGL.so

glxext.o: glxext.c glxclient.h
	$(CC) $(CFLAGS) glxext.c

dispatch.o: dispatch.c
	$(CC) $(CFLAGS) dispatch.c

glapi.o: glapi.c
	$(CC) $(CFLAGS) glapi.c

glapi.c: ../glapi.c
	ln -s ../glapi.c .


clean:
	rm -f *~ *.o libGL.so* glapi.c
