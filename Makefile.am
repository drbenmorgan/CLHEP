## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP

SUBDIRS = Vector Evaluator GenericFunctions Geometry Matrix Random RandomObjects Units Utilities HepPDT HepMC StdHep

## kludge to build libCLHEP

CLHEPLIB = libCLHEP-@VERSION@.a
CLHEPLIBSHARE = libCLHEP-@VERSION@.so
TEMPCLHEP = $(top_builddir)/.libs
AR_FLAGS="cru"

all-local: $(TEMPCLHEP) $(TEMPCLHEP)/$(CLHEPLIB) $(TEMPCLHEP)/$(CLHEPLIBSHARE)

$(TEMPCLHEP):
	rm -rf $(TEMPCLHEP)
	mkdir $(TEMPCLHEP)

$(TEMPCLHEP)/$(CLHEPLIB):
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test -d "$$subdir"/src/.libs; then (cd $(TEMPCLHEP); $(AR) x ../$$subdir/src/.libs/libCLHEP-$$subdir-@VERSION@.a; cd .. ); fi; \
	done
	cd $(TEMPCLHEP); $(AR) $(AR_FLAGS) $(CLHEPLIB) *.o; rm *.o

$(TEMPCLHEP)/$(CLHEPLIBSHARE):
	liblist=`$(srcdir)/getObjectList $(SUBDIRS)`; \
	$(CC) -shared $$liblist -lgcc -Wl,-soname -o $(TEMPCLHEP)/$(CLHEPLIBSHARE).0.0.0; \
	cd $(TEMPCLHEP); ln -s $(CLHEPLIBSHARE).0.0.0 $(CLHEPLIBSHARE)

docs:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test -d "$$subdir"/doc; then (cd $$subdir; $(MAKE) $(AM_MAKEFLAGS) docs; cd .. ); fi; \
	done

install-docs:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test -d "$$subdir"/doc; then (cd $$subdir; $(MAKE) $(AM_MAKEFLAGS) install-docs; cd .. ); fi; \
	done


install: install-recursive $(prefix)/lib/$(CLHEPLIB) $(prefix)/lib/$(CLHEPLIBSHARE)

$(prefix)/lib/$(CLHEPLIB): $(TEMPCLHEP)/$(CLHEPLIB)
	$(mkinstalldirs) $(prefix)/lib
	cp $(TEMPCLHEP)/$(CLHEPLIB) $(prefix)/lib/$(CLHEPLIB)

$(prefix)/lib/$(CLHEPLIBSHARE): $(TEMPCLHEP)/$(CLHEPLIBSHARE)
	$(mkinstalldirs) $(prefix)/lib
	cp $(TEMPCLHEP)/$(CLHEPLIBSHARE).0.0.0 $(prefix)/lib/$(CLHEPLIBSHARE).0.0.0
	ln -s $(prefix)/lib/$(CLHEPLIBSHARE).0.0.0 $(prefix)/lib/$(CLHEPLIBSHARE).0
	ln -s $(prefix)/lib/$(CLHEPLIBSHARE).0.0.0 $(prefix)/lib/$(CLHEPLIBSHARE)



