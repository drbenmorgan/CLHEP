## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

INCLUDES = -I$(top_builddir)

libCLHEP_StdHep_@VERSION@_a_SOURCES = \
	appendCollision.cc	\
	writeRunInfo.cc	\
	collision.cc	\
	combineEvents.cc	\
	findBlockType.cc	\
	findNextStdEvent.cc	\
	numParticles.cc	\
	numVertices.cc	\
	parseStdEventLine.cc	\
	particle.cc	\
	print.cc	\
	printVersion.cc	\
	readBlockType.cc	\
	readRunInfo.cc	\
	readStdComment.cc	\
	readStdEvent.cc	\
	readStdEventInfo.cc	\
	readStdRun.cc	\
	StdEvent.cc	\
	StdEventPAncestors.cc	\
	StdEventPChildren.cc	\
	StdEventPDescendants.cc	\
	StdEventPParents.cc	\
	StdEventVAncestors.cc	\
	StdEventVChildren.cc	\
	StdEventVDescendants.cc	\
	StdEventVertex.cc	\
	StdEventVParents.cc	\
	RandomState.cc \
	StdRunInfo.cc	\
	tree.cc	\
	writeEventKey.cc	\
	writeStdComment.cc	\
	WriteStdHep.cc

libCLHEP_StdHep_@VERSION@_so_OBJECTS = $(patsubst %.cc,$(shareddir)/%.$(OBJEXT),$(libCLHEP_StdHep_@VERSION@_a_SOURCES))

# these if/else blocks will be parsed by automake and translated
if BUILD_SHARED
  shareddir = shared
  lib_shared = libCLHEP-StdHep-@VERSION@.$(SHEXT)
  SHFLAGS = @MY_SHFLAGS@
  SHLINK = @MY_SHLINK@
  SHNAME = @MY_SHNAME@
endif
if BUILD_STATIC
  lib_LIBRARIES = libCLHEP-StdHep-@VERSION@.a
endif

CLEANFILES =  $(lib_shared)

all-local: $(shareddir) $(lib_shared)

$(shareddir):
	test -d $(shareddir) || mkdir $(shareddir)

$(lib_shared): $(libCLHEP_StdHep_@VERSION@_so_OBJECTS)
	$(CXXLINK) $(SHLINK) $(SHNAME)$@ $(libCLHEP_StdHep_@VERSION@_so_OBJECTS) -o $@

$(shareddir)/%.$(OBJEXT): %.cc
	$(CXXCOMPILE) $(SHFLAGS) -c -o $@ $<

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
