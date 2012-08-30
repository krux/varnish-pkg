INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)

vmoddir = $(pkglibdir)/vmods
vmod_LTLIBRARIES = libvmod_statsd.la

libvmod_statsd_la_LDFLAGS = -module -export-dynamic -avoid-version

libvmod_statsd_la_SOURCES = \
	vcc_if.c \
	vcc_if.h \
	vmod_statsd.c

vcc_if.c vcc_if.h: $(top_srcdir)/lib/libvmod_std/vmod.py $(top_srcdir)/lib/libvmod-statsd/src/vmod_statsd.vcc
	@PYTHON@ $(top_srcdir)/lib/libvmod_std/vmod.py $(top_srcdir)/src/vmod_statsd.vcc

VMOD_TESTS = tests/*.vtc
.PHONY: $(VMOD_TESTS)

tests/*.vtc:
	$(top_srcdir)/bin/varnishtest/varnishtest -Dvarnishd=$(top_srcdir)/bin/varnishd/varnishd -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_statsd.vcc \
	$(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c $(builddir)/vcc_if.h
