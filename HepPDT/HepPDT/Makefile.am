## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP
tempincludedir = $(TEMPDIR)/CLHEP/@PACKAGE@
COPY_P = @COPY_P@

pkginclude_HEADERS = \
	CommonParticleData.hh	 \
	MapVector.hh		 \
	QQStructs.hh		\
	CommonParticleData.icc	 \
	Measurement.hh		 \
	ResonanceStructure.hh	\
	Constituent.hh		 \
	Measurement.icc	 \
	SimpleDecayModel.hh	\
	convertTemporaryMap.icc  \
	NullDecayModel.hh	 \
	SimpleParticle.hh	\
	NullDecayModelT.hh	 \
	SpinState.hh	\
	DecayChannel.hh		 \
	ParticleData.hh	 \
	SpinState.icc	\
	DecayChannelT.hh	 \
	ParticleDataTable.hh	 \
	stringtodouble.hh	\
	DecayChannelT.icc	 \
	ParticleDataTableT.hh	 \
	TableBuilderHerwigT.icc	\
	DecayData.hh		 \
	ParticleDataTableT.icc  \
	TableBuilder.hh		\
	DecayDataT.hh		 \
	ParticleDataT.hh	 \
	TableBuilderIsajetT.icc	\
	DecayDataT.icc		 \
	ParticleDataT.icc	 \
	TableBuilderPythiaT.icc	\
	DecayModelBase.hh	 \
	ParticleID.hh		 \
	TableBuilderTEvtGen.icc	\
	DecayModel.hh		 \
	ParticleID.icc		 \
	TableBuilderT.hh	\
	DefaultConfig.hh	 \
	PDGtoQQTable.hh	 \
	TableBuilderT.icc	\
	DefTable.hh		 \
	pretend.hh		 \
	TableBuilderTQQ.icc	\
	DMFactory.hh		 \
	QQChannel.hh		 \
	TempParticleData.hh	\
	DMFactory.icc		 \
	QQDecay.hh		 \
	Version.hh	\
	QQDecayTable.hh	\
	StringStream.h	\
	ParticleName.hh	\
	ParticleIDTranslations.hh	\
	ParticleTranslation.hh	\
	ParticleTranslation.icc	\
	TranslationList.hh	\
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
