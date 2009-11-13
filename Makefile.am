## Process this file with automake to produce Makefile.in

## Special note:  Run buildDoxy.sh here to generate the html reference documentation.
## Then copy or move the html directory to the appropriate place.

if USE_GMAKE
  MAKE = gmake
endif

includedir = $(prefix)/include/CLHEP

SUBDIRS = Units Vector Evaluator GenericFunctions Geometry \
          Random Matrix RandomObjects Cast RefCount Exceptions

bin_SCRIPTS = clheplib clhep-config

LDFLAGS = @LDFLAGS@
LIBS = @LIBS@
CXXFLAGS = @CXXFLAGS@
CXXLD = $(CXX)
CXXLINK = $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@

# these if/else blocks will be parsed by automake and translated
if BUILD_SHARED
  shareddir = shared
if BUILD_VISUAL
  lib_shared = CLHEP-@VERSION@.$(SHEXT)
else
  lib_shared = libCLHEP-@VERSION@.$(SHEXT)
endif
  SHFLAGS = @MY_SHFLAGS@
  SHLINK = @MY_SHLINK@
  SHNAME = @MY_SHNAME@
endif
if BUILD_STATIC
  CLHEPLIB = libCLHEP-@VERSION@.a
endif
if BUILD_VISUAL
  MAKE_STATIC_CLHEP = $(COPY_P) libCLHEP-@VERSION@.a libCLHEP.a
  MAKE_SHARED_CLHEP = $(COPY_P) CLHEP-@VERSION@.$(SHEXT) CLHEP.$(SHEXT)
else
  MAKE_STATIC_CLHEP = $(LN_S) libCLHEP-@VERSION@.a libCLHEP.a
  MAKE_SHARED_CLHEP = $(LN_S) libCLHEP-@VERSION@.$(SHEXT) libCLHEP.$(SHEXT)
endif

CLEANFILES = clheplib library-list $(CLHEPLIB) $(lib_shared) ClhepVersion.h

all-local: $(CLHEPLIB) $(lib_shared) versionheader

$(CLHEPLIB): 
	-rm -f $@
	liblist=`$(top_builddir)/getObjectList -static $(SUBDIRS)`; \
	$(AR) $(ARFLAGS) $@ $$liblist; $(RANLIB) $@

if BUILD_VISUAL
$(lib_shared): 
	-rm -f $@
	liblist=`$(top_builddir)/getObjectList -shared $(SUBDIRS)`; \
	$(SHLINK) $(SHNAME)$@ $$liblist
else
$(lib_shared): 
	-rm -f $@
	liblist=`$(top_builddir)/getObjectList -shared $(SUBDIRS)`; \
	$(CXXLINK) $(SHLINK) $(SHNAME)$@ $$liblist -o $@
endif

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

versionheader: build-header
	./build-header

install-exec-local: install-CLHEPLIB install-versionheader

install-CLHEPLIB: $(CLHEPLIB) $(lib_shared)
	@$(NORMAL_INSTALL)
	test -z "$(libdir)" || $(mkdir_p) "$(DESTDIR)$(libdir)"
	@list='$(CLHEPLIB)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(INSTALL_DATA) '$$p' '$(DESTDIR)$(libdir)/$$p'"; \
	    $(INSTALL_DATA) "$$p" "$(DESTDIR)$(libdir)/$$p"; \
	  else :; fi; \
	done
	@$(POST_INSTALL)
	@list='$(CLHEPLIB)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(RANLIB) '$(DESTDIR)$(libdir)/$$p'"; \
	    $(RANLIB) "$(DESTDIR)$(libdir)/$$p"; \
	    if test -f $(DESTDIR)$(libdir)/libCLHEP.a; then \
	    (rm -f $(DESTDIR)$(libdir)/libCLHEP.a); fi; \
	    (cd $(DESTDIR)$(libdir) && $(MAKE_STATIC_CLHEP) ); \
	  else :; fi; \
	done
	@$(NORMAL_INSTALL)
	@list='$(lib_shared)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(INSTALL) '$$p' '$(DESTDIR)$(libdir)/$$p'"; \
	    $(INSTALL) "$$p" "$(DESTDIR)$(libdir)/$$f"; \
	  else :; fi; \
	done
	@$(POST_INSTALL)
	@list='$(lib_shared)'; for p in $$list; do \
	  if test -f $$p; then \
	    if test -f $(DESTDIR)$(libdir)/libCLHEP.a; then \
	    (rm -f $(DESTDIR)$(libdir)/libCLHEP.$(SHEXT)); fi; \
	    (cd $(DESTDIR)$(libdir) && $(MAKE_SHARED_CLHEP) ); \
	  else :; fi; \
	done

install-versionheader: versionheader
	@$(NORMAL_INSTALL)
	test -z "$(includedir)" || $(mkdir_p) "$(DESTDIR)$(includedir)"
	if test -f ClhepVersion.h; then \
	  echo " $(INSTALL_DATA) 'ClhepVersion.h' '$(DESTDIR)$(includedir)/ClhepVersion.h'"; \
	  $(INSTALL_DATA) "ClhepVersion.h" "$(DESTDIR)$(includedir)/ClhepVersion.h"; \
	else :; fi
	@$(POST_INSTALL)

clean-local:
	rm -f *-dep-list
	rm -f *-library-list
