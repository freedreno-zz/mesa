
MESA = ../..

MARK = $(MESA)/src-glut
default: libglut.so.3.7 install 
include $(MESA)/Makefile.include

INCLUDES = -I$(MESA)/include -I$(MARK)

CORE_SOURCES = \
	bitmap.c \
	callback.c \
	color.c \
	globals.c \
	init.c \
	menu.c \
	models.c \
	overlay.c \
	state.c \
	teapot.c \
	window.c


MARK_SOURCES = \
	$(MARK)/glut_8x13.c \
	$(MARK)/glut_9x15.c \
	$(MARK)/glut_hel10.c \
	$(MARK)/glut_hel12.c \
	$(MARK)/glut_hel18.c \
	$(MARK)/glut_tr10.c \
	$(MARK)/glut_tr24.c

SOURCES = $(CORE_SOURCES)  $(MARK_SOURCES)

OBJS =  $(SOURCES:.c=.o)

LIBS = -L$(MESA)/lib -lGL -lGLU -lm

libglut.so.3.7: $(OBJS) Makefile
	gcc -shared -Wl,-soname,libglut.so -Wl,-Bsymbolic $(OBJS) $(LIBS) -o $@ 

install:
	rm -f $(MESA)/lib/libglut.so*
	install -D libglut.so.3.7 $(MESA)/lib/libglut.so.3.7
	ln -s libglut.so.3.7 $(MESA)/lib/libglut.so.3
	ln -s libglut.so.3 $(MESA)/lib/libglut.so


-include $(SOURCES:.c=.d)

