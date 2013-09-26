## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

includedir = $(prefix)/include/CLHEP
tempincludedir = $(TEMPDIR)/CLHEP/@PACKAGE@
COPY_P = @COPY_P@

pkginclude_HEADERS = \
	DoubConv.hh	\
	DRand48Engine.h	\
	DualRand.h	\
	EngineFactory.h \
	engineIDulong.h \
	Hurd160Engine.h	\
	Hurd288Engine.h	\
	JamesRandom.h	\
	MTwistEngine.h	\
	NonRandomEngine.h	\
	RandBinomial.h	\
	RandBinomial.icc	\
	RandBit.h	\
	RandBit.icc	\
	RandBreitWigner.h	\
	RandBreitWigner.icc	\
	RandChiSquare.h	\
	RandChiSquare.icc	\
	RandEngine.h	\
	RandExponential.h	\
	RandExponential.icc	\
	RandExpZiggurat.h	\
	RandFlat.h	\
	RandFlat.icc	\
	RandGamma.h	\
	RandGamma.icc	\
	RandGauss.h	\
	RandGauss.icc	\
	RandGaussQ.h	\
	RandGaussQ.icc	\
	RandGaussT.h	\
	RandGaussT.icc	\
	RandGaussZiggurat.h	\
	RandGeneral.h	\
	RandGeneral.icc	\
	RandLandau.h	\
	RandLandau.icc	\
	RandomEngine.h	\
	RandomEngine.icc	\
	Random.h	\
	Random.icc	\
	Randomize.h	\
	RandomFunc.h	\
	RandPoisson.h	\
	RandPoisson.icc	\
	RandPoissonQ.h	\
	RandPoissonQ.icc	\
	RandPoissonT.h	\
	RandPoissonT.icc	\
	RandSkewNormal.h	\
	RandSkewNormal.icc	\
	RandStudentT.h	\
	RandStudentT.icc	\
	RanecuEngine.h	\
	Ranlux64Engine.h	\
	RanluxEngine.h	\
	RanshiEngine.h	\
	SeedTable.h	\
	Stat.h	\
	StaticRandomStates.h	\
	TripleRand.h	\
	defs.h

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = defs.h

# copy headers into $(tempincludedir)
install-tmpHEADERS:
	@echo " install headers in $(tempincludedir) "
	@list='$(pkginclude_HEADERS)'; \
	if test $(tempincludedir); then \
	  for p in $$list; do \
	    if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	    f="`echo $$p | sed -e 's|^.*/||'`"; \
	    ./copy-header.pl $$d$$p $(tempincludedir)/$$f; \
	  done; \
	fi; test -z "$$fail"
