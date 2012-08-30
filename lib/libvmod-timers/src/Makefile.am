INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)

vmoddir = $(pkglibdir)/vmods
vmod_LTLIBRARIES = libvmod_timers.la

libvmod_timers_la_LDFLAGS = -module -export-dynamic -avoid-version

libvmod_timers_la_SOURCES = \
	vcc_if.c \
	vcc_if.h \
	vmod_timers.c

vcc_if.c vcc_if.h: $(top_srcdir)/lib/libvmod_std/vmod.py $(top_srcdir)/lib/libvmod-timers/src/vmod_timers.vcc
	@PYTHON@ $(top_srcdir)/lib/libvmod_std/vmod.py $(top_srcdir)/src/vmod_timers.vcc

VMOD_TESTS = tests/*.vtc
.PHONY: $(VMOD_TESTS)

tests/*.vtc:
	$(top_srcdir)/bin/varnishtest/varnishtest -Dvarnishd=$(top_srcdir)/bin/varnishd/varnishd -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_timers.vcc \
	$(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c $(builddir)/vcc_if.h
