# Copyright © 2016 Red Hat.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.

include Makefile.sources
include $(top_srcdir)/src/gallium/Automake.inc

AM_CPPFLAGS = \
	$(GALLIUM_DRIVER_CFLAGS) \
	$(LIBDRM_CFLAGS)

noinst_LTLIBRARIES = libresequencer.la

PYTHON_GEN = $(AM_V_GEN)$(PYTHON2) $(PYTHON_FLAGS)

# NOTE: dependency on rsq_state.h seems to be required to ensure it
# is regenerated before other files that #include it are built :-/
rsq_state.c: rsq_state.py rsq_state.h
	$(MKDIR_GEN)
	$(PYTHON_GEN) $(srcdir)/rsq_state.py -c > $@ || ($(RM) $@; false)

rsq_state.h: rsq_state.py
	$(MKDIR_GEN)
	$(PYTHON_GEN) $(srcdir)/rsq_state.py -h > $@ || ($(RM) $@; false)

libresequencer_la_SOURCES = $(C_SOURCES) $(C_GENERATED_SOURCES)
