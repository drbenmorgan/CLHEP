## Process this file with automake to produce Makefile.in

INCLUDES = -I$(top_builddir)

libCLHEP_HepMC_@VERSION@_a_SOURCES = \
	DummyDecayModel.cc	\
	WriteHepMC.cc	\
	Flow.cc	\
	GenEvent.cc	\
	genMass.cc	\
	GenParticle.cc	\
	GenVertex.cc	\
	getParticleID.cc	\
	particleCollision.cc	\
	particleCreationVertex.cc	\
	particleDecayVertex.cc	\
	particleHas.cc	\
	particleListAncestors.cc	\
	particleListChildren.cc	\
	particleListDescendants.cc	\
	particleListParents.cc	\
	particleMomentum.cc	\
	particleMotherDaughter.cc	\
	particleNum.cc	\
	particlePointers.cc	\
	Polarization.cc	\
	ReadHepMCBlockType.cc	\
	ReadHepMC.cc	\
	ReadHepMCComment.cc	\
	ReadHepMCDetail.cc	\
	ReadHepMCFindBlock.cc	\
	ReadNextHepMC.cc	\
	vertexHas.cc	\
	vertexListAncestors.cc	\
	vertexListChildren.cc	\
	vertexListDescendants.cc	\
	vertexListParents.cc	\
	vertexNum.cc	\
	vertexPointers.cc	\
	writeComment.cc	\
	WriteHepMCDetail.cc	\
	DoubleConversion.cc

libCLHEP_HepMC_@VERSION@_so_OBJECTS = $(patsubst %.cc,$(shareddir)/%.$(OBJEXT),$(libCLHEP_HepMC_@VERSION@_a_SOURCES))

# these if/else blocks will be parsed by automake and translated
if BUILD_SHARED
  shareddir = shared
  lib_shared = libCLHEP-HepMC-@VERSION@.$(SHEXT)
  SHFLAGS = @MY_SHFLAGS@
  SHLINK = @MY_SHLINK@
  SHNAME = @MY_SHNAME@
endif
if BUILD_STATIC
  lib_LIBRARIES = libCLHEP-HepMC-@VERSION@.a
endif

CLEANFILES =  $(lib_shared)

all-local: $(shareddir) $(lib_shared)

$(shareddir):
	test -d $(shareddir) || mkdir $(shareddir)

$(lib_shared): $(libCLHEP_HepMC_@VERSION@_so_OBJECTS)
	$(CXXLINK) $(SHLINK) $(SHNAME)$@ $(libCLHEP_HepMC_@VERSION@_so_OBJECTS) -o $@

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
