## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif


includedir = $(prefix)/include/CLHEP

SUBDIRS = Utilities 

docs:
	cd doc; $(MAKE) $(AM_MAKEFLAGS)

install-docs:
	cd doc; $(MAKE) $(AM_MAKEFLAGS) install-docs
