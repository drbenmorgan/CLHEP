## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP

SUBDIRS = Vector Evaluator GenericFunctions Geometry Matrix Random RandomObjects Units Utilities HepPDT HepMC StdHep

bin_SCRIPTS = clheplib

CLEANFILES = clheplib library-list

docs:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test -d "$$subdir"/doc; then (cd $$subdir; $(MAKE) $(AM_MAKEFLAGS) docs; cd .. ); fi; \
	done

install-docs:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test -d "$$subdir"/doc; then (cd $$subdir; $(MAKE) $(AM_MAKEFLAGS) install-docs; cd .. ); fi; \
	done

clheplib: build-clheplib
	build-clheplib $(SUBDIRS)



