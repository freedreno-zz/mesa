

MESA = ../..
default: libGLU.so.1.1 install 
include $(MESA)/Makefile.include

LIBDIR = $(MESA)/lib

INCLUDES = -I$(MESA)/include 
CFLAGS = -c -g $(INCLUDES) -MD 

SOURCES = glu.c \
	mipmap.c \
	nurbs.c \
	polytest.c \
	project.c \
	quadric.c \
	tess.c \
	tesselat.c


OBJS = $(addsuffix .o,$(basename $(SOURCES)))

LIBS=-L$(MESA)/lib -lGL -lm





libGLU.so.1.1: $(OBJS) Makefile
	gcc -shared -Wl,-soname,libGLU.so -Wl,-Bsymbolic $(OBJS) $(LIBS) -o $@ 

install:
	rm -f $(MESA)/lib/libGLU.so*
	install -D libGLU.so.1.1 $(MESA)/lib/libGLU.so.1.1
	ln -s libGLU.so.1.1 $(MESA)/lib/libGLU.so.1
	ln -s libGLU.so.1 $(MESA)/lib/libGLU.so


clean: clean_here

clean_here:
	rm -f ../lib/libGLU.so*


-include $(SOURCES:.c=.d)
