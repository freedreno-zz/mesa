#
# Makefile for building the radeonfb module standalone.
#
# Modelled closely on the drm kernel Makefile.linux in the XFree86 source
# tree.
#
# $TG: radeonfb/GNUmakefile,v 1.5 2002/12/18 14:54:08 dawes Exp $
#

.SUFFIXES:

MODS = radeonfb.o

PROGS = 

FBHEADERS = 

FBLINHEADERS = 

FBOBJS = 

WARNINGS = -Wall -Wwrite-strings -Wpointer-arith -Wcast-align \
	   -Wstrict-prototypes -Wnested-externs \
	   -Wpointer-arith
CFLAGS = -O2 $(WARNINGS)

MODCFLAGS = $(CFLAGS) -D__KERNEL__ -DMODULE -fomit-frame-pointer

# First, locate correct tree for this kernel version.  If we find a
# matching tree, we assume that we can rely on that tree's autoconf.h.
# This may not be correct, but it is the best assumption we can make.

VERSION := $(shell uname -r)
# For Red Hat...
RHVERS := $(shell uname -r)custom

A := /lib/modules/$(VERSION)/build/include
B := /usr/src/linux-$(VERSION)/include
C := /usr/src/linux/include
D := /usr/include

all::; @echo $(RHVERS)
V := $(shell gcc -E -nostdinc -I$A picker.c 2>/dev/null \
      | grep -s 'RELEASE = ' | cut -d' ' -f3)
ifeq ($(V),"$(VERSION)")
TREE := $A
else
ifeq ($(V),"$(RHVERS)")
  TREE := $A
else
  V := $(shell gcc -E -nostdinc -I$B picker.c 2>/dev/null \
        | grep -s 'RELEASE = ' | cut -d' ' -f3)
ifeq ($(V),"$(VERSION)")
    TREE := $B
else
ifeq ($(V),"$(RHVERS)")
      TREE := $B
else
      V := $(shell gcc -E -nostdinc -I$C picker.c 2>/dev/null \
          | grep -s 'RELEASE = ' | cut -d' ' -f3)
ifeq ($(V),"$(VERSION)")
        TREE := $C
else
        V := $(shell gcc -E -nostdinc -I$D picker.c 2>/dev/null \
          | grep -s 'RELEASE = ' | cut -d' ' -f3)
ifeq ($(V),"$(VERSION)")
          TREE := $D
else
          TREE := 0
endif
endif
endif
endif
endif
endif

ifeq ($(TREE),0)
all::; @echo Error: Could not locate kernel tree in $A $B $C $D
else
SMP := $(shell gcc -E -nostdinc -I$(TREE) picker.c 2>/dev/null \
        | grep -s 'SMP = ' | cut -d' ' -f3)
MODULES := $(shell gcc -E -nostdinc -I$(TREE) picker.c 2>/dev/null \
        | grep -s 'MODULES = ' | cut -d' ' -f3)
MODVERSIONS := $(shell gcc -E -nostdinc -I$(TREE) picker.c 2>/dev/null \
        | grep -s 'MODVERSIONS = ' | cut -d' ' -f3)
MACHINE := $(shell echo `uname -m`)
endif

all::;@echo === KERNEL HEADERS IN $(TREE)
all::;@echo === SMP=${SMP} MODULES=${MODULES} MODVERSIONS=${MODVERSIONS}
all::;@echo === Compiling for machine $(MACHINE)

ifeq ($(MODULES),0)
all::;@echo
all::;@echo "*** Kernel modules must be configured.  Build aborted."
all::;@echo
else
all:: linux video $(MODS) $(PROGS)
endif

ifeq ($(SMP),1)
MODCFLAGS += -D__SMP__
endif
ifeq ($(MODVERSIONS),1)
MODCFLAGS += -DMODVERSIONS -include $(TREE)/linux/modversions.h
endif

# radeonfb.o: radeonfb_be.o radeonfb_fe.o
# 	$(LD) -r $^ -o $@


%.o: %.c
	$(CC) $(MODCFLAGS) -DEXPORT_SYMTAB -I. -I$(TREE) -c $< -o $@

$(AGPOBJS): $(AGPHEADERS)

linux:
	rm -f linux
	ln -s . linux

video:
	rm -f video
	ln -s . video

clean:
	rm -f *.o
	rm -f linux
	rm -f $(PROGS)

