## Process this file with automake to produce Makefile.in

INCLUDES = -I$(top_builddir)

libCLHEP_HepPDT_@VERSION@_a_SOURCES = \
	Constituent.cc		\
	DMFactory.cc		\
	DefTable.cc		\
	PDGtoQQTable.cc		\
	ParticleName.cc		\
	QQChannel.cc		\
	QQDecay.cc		\
	QQDecayTable.cc		\
	ResonanceStructure.cc	\
	SimpleDecayModel.cc	\
	TempParticleData.cc	\
	listPythiaTranslation.cc	\
	listPDGTranslation.cc	\
	addEvtGenParticles.cc	\
	addPDGParticles.cc	\
	addPythiaParticles.cc	\
	addQQParticles.cc	\
	buildTable.cc		\
	calculateWidthFromLifetime.cc	\
	digit.cc		\
	extraBits.cc		\
	fundamentalID.cc	\
	getPDGpid.cc		\
	getPythiaid.cc		\
	hasMethods.cc		\
	ion.cc			\
	isBaryon.cc		\
	isDiQuark.cc		\
	isHadron.cc		\
	isLepton.cc		\
	isMeson.cc		\
	isNucleus.cc		\
	isValid.cc		\
	jSpin.cc		\
	lSpin.cc		\
	lifetime.cc		\
	quarks.cc		\
	readQQchannel.cc	\
	readQQstream.cc		\
	sSpin.cc		\
	spindtoi.cc		\
	spinitod.cc		\
	stringtodouble.cc	\
	threeCharge.cc		\
	translateEvtGentoPDT.cc	\
	translateGeanttoPDT.cc	\
	translateHerwig.cc	\
	translateIsajet.cc	\
	translatePythia.cc	\
	translatePDGtabletoPDT.cc	\
	translatePDTtoEvtGen.cc	\
	translatePDTtoGeant.cc	\
	translatePDTtoPDGtable.cc	\
	translatePDTtoQQ.cc	\
	translateQQtoPDT.cc	\
	version.cc		\
	write.cc		\
	writeTranslations.cc

libCLHEP_HepPDT_@VERSION@_so_OBJECTS = $(patsubst %.cc,$(shareddir)/%.$(OBJEXT),$(libCLHEP_HepPDT_@VERSION@_a_SOURCES))

# these if/else blocks will be parsed by automake and translated
if BUILD_SHARED
  shareddir = shared
  lib_shared = libCLHEP-HepPDT-@VERSION@.$(SHEXT)
  SHFLAGS = @MY_SHFLAGS@
  SHLINK = @MY_SHLINK@
  SHNAME = @MY_SHNAME@
endif
if BUILD_STATIC
  lib_LIBRARIES = libCLHEP-HepPDT-@VERSION@.a
endif

CLEANFILES =  $(lib_shared)

all-local: $(shareddir) $(lib_shared)

$(shareddir):
	test -d $(shareddir) || mkdir $(shareddir)

$(lib_shared): $(libCLHEP_HepPDT_@VERSION@_so_OBJECTS)
	$(CXXLINK) $(SHLINK) $(SHNAME)$@ $(libCLHEP_HepPDT_@VERSION@_so_OBJECTS) -o $@

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
