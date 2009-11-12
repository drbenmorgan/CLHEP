## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

INCLUDES = -I$(top_builddir)

libCLHEP_Exceptions_@VERSION@_a_SOURCES = \
	ZMerrno.cc		\
	ZMexClassInfo.cc	\
	ZMexHandler.cc		\
	ZMexLogger.cc		\
	ZMexSeverity.cc		\
	ZMexception.cc		\
	ZMthrow.cc

libCLHEP_Exceptions_@VERSION@_so_OBJECTS = $(patsubst %.cc,$(shareddir)/%.$(OBJEXT),$(libCLHEP_Exceptions_@VERSION@_a_SOURCES))

# these if/else blocks will be parsed by automake and translated
if BUILD_SHARED
  shareddir = shared
if BUILD_VISUAL
  lib_shared = CLHEP-Exceptions-@VERSION@.$(SHEXT)
  LDADD = -L${top_builddir}/../Cast/src -lCLHEP-Cast-@VERSION@ \
	  -L${top_builddir}/../RefCount/src -lCLHEP-RefCount-@VERSION@
else
  lib_shared = libCLHEP-Exceptions-@VERSION@.$(SHEXT)
  LDADD = -L${top_builddir}/../Cast/src -lCLHEP-Cast-@VERSION@ \
	  -L${top_builddir}/../RefCount/src -lCLHEP-RefCount-@VERSION@
endif
  SHFLAGS = @MY_SHFLAGS@
  SHLINK = @MY_SHLINK@ @MY_SHEXTRA@
  SHNAME = @MY_SHNAME@
endif
if BUILD_STATIC
  lib_LIBRARIES = libCLHEP-Exceptions-@VERSION@.a
endif

CLEANFILES =  $(lib_shared)

all-local: $(shareddir) $(lib_shared)

$(shareddir):
	test -d $(shareddir) || mkdir $(shareddir)

if BUILD_VISUAL
$(lib_shared): $(libCLHEP_Exceptions_@VERSION@_so_OBJECTS)
	$(SHLINK) $(SHNAME)$@ $(libCLHEP_Exceptions_@VERSION@_so_OBJECTS) $(LDADD)

$(shareddir)/%.$(OBJEXT): %.cc
	$(CXXCOMPILE) $(SHFLAGS) /c /Fo$@ $<
else
$(lib_shared): $(libCLHEP_Exceptions_@VERSION@_so_OBJECTS)
	$(CXXLINK) $(SHLINK) $(SHNAME)$@ $(libCLHEP_Exceptions_@VERSION@_so_OBJECTS) $(LDADD) -o $@

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
