## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP

SUBDIRS = Units Vector Evaluator GenericFunctions Geometry \
          Random Matrix RandomObjects Fields HepPDT HepMC StdHep \
          RefCount Cast Exceptions

bin_SCRIPTS = clheplib

CLEANFILES = clheplib library-list $(LTCLHEPLIB)

LDFLAGS = @LDFLAGS@
LIBS = @LIBS@
CXXFLAGS = @CXXFLAGS@
LTCLHEPLIB = libCLHEP-@VERSION@.la
CXXLD = $(CXX)
CXXLINK = $(LIBTOOL) --mode=link $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@

all-local: $(LTCLHEPLIB)

$(LTCLHEPLIB): 
	liblist=`$(srcdir)/getObjectList $(SUBDIRS)`; \
	$(CXXLINK) -rpath $(libdir) $$liblist $(LIBS)

docs:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test -d "$$subdir"/doc; then (cd $$subdir; $(MAKE) $(AM_MAKEFLAGS) docs; cd .. ); fi; \
	done

install-docs:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test -d "$$subdir"/doc; then (cd $$subdir; $(MAKE) $(AM_MAKEFLAGS) install-docs; cd .. ); fi; \
	done

clheplib: build-clheplib
	./build-clheplib $(SUBDIRS)

install-exec-local: install-LTCLHEPLIB

install-LTCLHEPLIB: $(LTCLHEPLIB)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libdir)
	@list='$(LTCLHEPLIB)'; for p in $$list; do \
	  if test -f $$p; then \
	    f="`echo $$p | sed -e 's|^.*/||'`"; \
	    echo " $(LIBTOOL) --mode=install $(libLTLIBRARIES_INSTALL) $(INSTALL_STRIP_FLAG) $$p $(DESTDIR)$(libdir)/$$f"; \
	    $(LIBTOOL) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) $$p $(DESTDIR)$(libdir)/$$f; \
	  else :; fi; \
	done

clean-local:
	rm -f *-dep-list
	rm -f *-library-list
