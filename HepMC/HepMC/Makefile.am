## Process this file with automake to produce Makefile.in

includedir = $(prefix)/include/CLHEP
tempincludedir = $(TEMPDIR)/CLHEP/@PACKAGE@
COPY_P = @COPY_P@

SUBDIRS = include 

pkginclude_HEADERS = \
	CBhepevt.h	\
	CBhepevt.icc	\
	CBherwig.h	\
	CBherwig.icc	\
	CBInterface.h	\
	ConvertHEPEVT.h	\
	ConvertHerwig.h	\
	DummyDecayModel.h	\
	Flow.h		\
	GenEventConvert.h	\
	GenEventConvert.icc	\
	GenEvent.h	\
	GenEventtoHEPEVT.icc	\
	GenParticle.h	\
	GenVertex.h	\
	HEPEVTtoGenEvent.icc	\
	HepMCConfig.h	\
	ParticleDataTableConfig.h	\
	Polarization.h	\
	ReadHepMC.h	\
	WeightContainer.h	\
	WriteHepMC.h	\
	defs.h

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = defs.h

# copy headers into $(tempincludedir)
install-tmpHEADERS:
	@echo " install headers in $(TEMPDIR)/CLHEP "
	@list='$(pkginclude_HEADERS)'; \
	if test $(TEMPDIR); then \
	  for p in $$list; do \
	    if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	    f="`echo $$p | sed -e 's|^.*/||'`"; \
	    echo " $(COPY_P) $$d$$p $(tempincludedir)/$$f"; \
	    $(COPY_P) $$d$$p $(tempincludedir)/$$f; \
	  done; \
	fi; test -z "$$fail"
