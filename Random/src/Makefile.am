## Process this file with automake to produce Makefile.in

INCLUDES = -I$(top_builddir) -I$(top_srcdir)

libCLHEP_Random_@VERSION@_a_SOURCES = \
	DoubConv.cc	\
	DRand48Engine.cc	\
	DualRand.cc	\
	EngineFactory.cc	\
	engineIDulong.cc	\
	erfQ.cc	\
	flatToGaussian.cc	\
	gammln.cc	\
	Hurd160Engine.cc	\
	Hurd288Engine.cc	\
	JamesRandom.cc	\
	MTwistEngine.cc	\
	NonRandomEngine.cc	\
	RandBinomial.cc	\
	RandBit.cc	\
	RandBreitWigner.cc	\
	RandChiSquare.cc	\
	RandEngine.cc	\
	RandExponential.cc	\
	RandFlat.cc	\
	RandGamma.cc	\
	RandGauss.cc	\
	RandGaussQ.cc	\
	RandGaussT.cc	\
	RandGeneral.cc	\
	RandLandau.cc	\
	Random.cc	\
	RandomEngine.cc	\
	RandPoisson.cc	\
	RandPoissonQ.cc	\
	RandPoissonT.cc	\
	RandStudentT.cc	\
	RanecuEngine.cc	\
	Ranlux64Engine.cc	\
	RanluxEngine.cc	\
	RanshiEngine.cc	\
	StaticRandomStates.cc \
	TripleRand.cc

libCLHEP_Random_@VERSION@_so_OBJECTS = $(patsubst %.cc,$(shareddir)/%.$(OBJEXT),$(libCLHEP_Random_@VERSION@_a_SOURCES))

# these if/else blocks will be parsed by automake and translated
if BUILD_SHARED
  shareddir = shared
  lib_shared = libCLHEP-Random-@VERSION@.$(SHEXT)
  SHFLAGS = @MY_SHFLAGS@
  SHLINK = @MY_SHLINK@
  SHNAME = @MY_SHNAME@
endif
if BUILD_STATIC
  lib_LIBRARIES = libCLHEP-Random-@VERSION@.a
endif

CLEANFILES =  $(lib_shared)

all-local: $(shareddir) $(lib_shared)

$(shareddir):
	test -d $(shareddir) || mkdir $(shareddir)

$(lib_shared): $(libCLHEP_Random_@VERSION@_so_OBJECTS)
	$(CXXLINK) $(SHLINK) $(SHNAME)$@ $(libCLHEP_Random_@VERSION@_so_OBJECTS) -o $@

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
