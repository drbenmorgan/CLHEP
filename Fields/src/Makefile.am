## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

INCLUDES = -I$(top_builddir) -I$(top_srcdir)

libCLHEP_Fields_@VERSION@_a_SOURCES = XF.cc

libCLHEP_Fields_@VERSION@_so_OBJECTS = $(patsubst %.cc,$(shareddir)/%.$(OBJEXT),$(libCLHEP_Fields_@VERSION@_a_SOURCES))

# these if/else blocks will be parsed by automake and translated
if BUILD_SHARED
  shareddir = shared
if BUILD_VISUAL
  lib_shared = CLHEP-Fields-@VERSION@.$(SHEXT)
else
  lib_shared = libCLHEP-Fields-@VERSION@.$(SHEXT)
  LDADD = -L${top_builddir}/../Geometry/src -lCLHEP-Geometry-@VERSION@ \
	  -L${top_builddir}/../GenericFunctions/src -lCLHEP-GenericFunctions-@VERSION@ \
	  -L${top_builddir}/../Vector/src -lCLHEP-Vector-@VERSION@
endif
  SHFLAGS = @MY_SHFLAGS@
  SHLINK = @MY_SHLINK@ @MY_SHEXTRA@
  SHNAME = @MY_SHNAME@
endif
if BUILD_STATIC
  lib_LIBRARIES = libCLHEP-Fields-@VERSION@.a
endif

CLEANFILES =  $(lib_shared)

all-local: $(shareddir) $(lib_shared)

$(shareddir):
	test -d $(shareddir) || mkdir $(shareddir)

if BUILD_VISUAL
$(lib_shared): $(libCLHEP_Fields_@VERSION@_so_OBJECTS)
	$(SHLINK) $(SHNAME)$@ $(libCLHEP_Fields_@VERSION@_so_OBJECTS) $(LDADD)

$(shareddir)/%.$(OBJEXT): %.cc
	$(CXXCOMPILE) $(SHFLAGS) /c /Fo$@ $<
else
$(lib_shared): $(libCLHEP_Fields_@VERSION@_so_OBJECTS)
	$(CXXLINK) $(SHLINK) $(SHNAME)$@ $(libCLHEP_Fields_@VERSION@_so_OBJECTS) $(LDADD)

$(shareddir)/%.$(OBJEXT): %.cc
	$(CXXCOMPILE) $(SHFLAGS) -c -o $@ $<
endif

install-exec-local: $(lib_shared)
	@$(NORMAL_INSTALL)
	test -z "$(libdir)" || $(mkdir_p) "$(DESTDIR)$(libdir)"
	@list='$(lib_shared)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(INSTALL) '$$p' '$(DESTDIR)$(libdir)/$$p'"; \
	    $(INSTALL) "$$p" "$(DESTDIR)$(libdir)/$$f"; \
	  else :; fi; \
	done

clean-local:
	-test -d $(shareddir) && rm -f $(shareddir)/*.$(OBJEXT)

distclean-local:
	-test -d $(shareddir) && rm -rf ./$(shareddir)
