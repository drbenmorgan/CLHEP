## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

includedir = $(prefix)/include/CLHEP
tempincludedir = $(TEMPDIR)/CLHEP/@PACKAGE@
COPY_P = @COPY_P@

pkginclude_HEADERS = \
	AxisAngle.h		\
	AxisAngle.icc		\
	Boost.h			\
	Boost.icc		\
	BoostX.h		\
	BoostX.icc		\
	BoostY.h		\
	BoostY.icc		\
	BoostZ.h		\
	BoostZ.icc		\
	EulerAngles.h		\
	EulerAngles.icc		\
	LorentzRotation.h	\
	LorentzRotation.icc	\
	LorentzVector.h		\
	LorentzVector.icc	\
	Rotation.h		\
	Rotation.icc		\
	RotationInterfaces.h	\
	RotationInterfaces.icc	\
	RotationX.h		\
	RotationX.icc		\
	RotationY.h		\
	RotationY.icc		\
	RotationZ.h		\
	RotationZ.icc		\
	Sqr.h			\
	ThreeVector.h		\
	ThreeVector.icc		\
	TwoVector.h		\
	TwoVector.icc		\
	ZMxpv.h			\
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
