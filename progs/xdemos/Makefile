
# Simple makefile for compiling test programs on Linux
# These programs aren't intended to be included with the normal
# distro.  They're not too interesting but they're good for testing.


CC = gcc
CFLAGS = -g -I../include
LIBS = -L../lib -lGL -lm

PROGS = glxgears


##### RULES #####

.SUFFIXES:
.SUFFIXES: .c

.c:
	$(CC) $(CFLAGS) $< $(LIBS) -o $@




##### TARGETS #####

default: $(PROGS)

clean:
	rm -f $(PROGS)
	rm -f *.o




