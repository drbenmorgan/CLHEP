## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP

# put . first so that CLHEP directory is built before anything else
SUBDIRS = . Random src test

all-local: $(top_builddir)/CLHEP

$(top_builddir)/CLHEP:
	$(top_srcdir)/makeCLHEPdir  $(top_srcdir)/..

doc:
	cd doc; $(MAKE) $(AM_MAKEFLAGS) doc || exit 1
