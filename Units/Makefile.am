## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP

# put . first so that CLHEP directory is built before anything else
SUBDIRS = Units . test
# list all subdirectories - for distribution and cleaning
DIST_SUBDIRS = Units . test doc

docs:
	cd doc; $(MAKE) $(AM_MAKEFLAGS)

install-docs:
	cd doc; $(MAKE) $(AM_MAKEFLAGS) install-docs
