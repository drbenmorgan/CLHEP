## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP

SUBDIRS = config Units Vector Evaluator GenericFunctions Geometry \
          Random Matrix RandomObjects HepPDT HepMC StdHep \
          RefCount Cast Exceptions

bin_SCRIPTS = clheplib clhep-config

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
	if test -f $(DESTDIR)$(libdir)/libCLHEP-@VERSION@.a; then \
	   if ! test -f $(DESTDIR)$(libdir)/libCLHEP.a; then \
	     (cd $(DESTDIR)$(libdir) && $(LN_S) libCLHEP-@VERSION@.a libCLHEP.a ); \
	   fi; fi
	if test -f $(DESTDIR)$(libdir)/libCLHEP-@VERSION@.so; then \
	   if ! test -f $(DESTDIR)$(libdir)/libCLHEP.so; then \
	     (cd $(DESTDIR)$(libdir) && $(LN_S) libCLHEP-@VERSION@.so libCLHEP.so ); \
	   fi; fi
	if test -f $(DESTDIR)$(libdir)/libCLHEP-@VERSION@.dylib; then \
	   if ! test -f $(DESTDIR)$(libdir)/libCLHEP.dylib; then \
	     (cd $(DESTDIR)$(libdir) && $(LN_S) libCLHEP-@VERSION@.dylib libCLHEP.dylib ); \
	   fi; fi

clean-local:
	rm -f *-dep-list
	rm -f *-library-list
