# Mesa 3-D graphics library
# Version:  4.0
# 
# Copyright (C) 1999  Brian Paul   All Rights Reserved.
# 
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
# AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# DOS/DJGPP glut makefile v1.1 for Mesa 4.0
#
#  Copyright (C) 2002 - Borca Daniel
#  Email : dborca@yahoo.com
#  Web   : http://www.geocities.com/dborca



.PHONY: all clean

TOP = ../..
MARK = $(TOP)/src-glut
LIBDIR = $(TOP)/lib
GLUT_LIB = libglut.so

CC = gcc
INCLUDES = -I$(TOP)/include -I$(MARK)
CFLAGS = -c -g $(INCLUDES) -MD 

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

OBJS = $(addsuffix .o,$(basename $(SOURCES)))

LIBS=-L$(TOP)/lib -lGL -lGLU -lm

.c.o:
	$(CC) -o $@ -c $(CFLAGS) $<
.S.o:
	$(CC) -o $@ -c $(CFLAGS) $<

default: libglut.so.3.7 install 


libglut.so.3.7: $(OBJS) Makefile
	gcc -shared -Wl,-soname,libglut.so -Wl,-Bsymbolic $(OBJS) $(LIBS) -o $@ 

install:
	rm -f $(TOP)/lib/libglut.so*
	install -D libglut.so.3.7 $(TOP)/lib/libglut.so.3.7
	ln -s libglut.so.3.7 $(TOP)/lib/libglut.so.3
	ln -s libglut.so.3 $(TOP)/lib/libglut.so


clean:
	rm -f *~ .*~ *.o libglut.so*  *.d


-include $(SOURCES:.c=.d)

.SUFFIXES: .c .d

.c.d:
	$(CC) -M $(INCLUDES) $< > $@
