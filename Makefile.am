## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP

SUBDIRS = Vector Evaluator GenericFunctions Geometry Matrix Random RandomObjects Units Utilities HepPDT HepMC StdHep

## kludge to build libCLHEP

CLHEPLIB = libCLHEP-@VERSION@.a
TEMPCLHEP = $(top_builddir)/.libs
AR_FLAGS="cru"

all-local: $(CLHEPLIB)

$(CLHEPLIB):
	rm -rf $(TEMPCLHEP)
	mkdir $(TEMPCLHEP)
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test -d "$$subdir"/src/.libs; then (cd $(TEMPCLHEP); $(AR) x ../$$subdir/src/.libs/lib$$subdir-toy1.9.0.0.a; cd .. ); fi; \
	done
	cd $(TEMPCLHEP); $(AR) $(AR_FLAGS) $(CLHEPLIB) *.o

install: install-recursive $(prefix)/lib/$(CLHEPLIB)

$(prefix)/lib/$(CLHEPLIB): $(TEMPCLHEP)/$(CLHEPLIB)
	$(mkinstalldirs) $(prefix)/lib
	cp $(TEMPCLHEP)/$(CLHEPLIB) $(prefix)/lib/$(CLHEPLIB)
