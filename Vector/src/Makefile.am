## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

INCLUDES = -I$(top_builddir)

libCLHEP_Vector_@VERSION@_a_SOURCES = \
	AxisAngle.cc		\
	Boost.cc		\
	BoostX.cc		\
	BoostY.cc		\
	BoostZ.cc		\
	EulerAngles.cc		\
	LorentzRotation.cc	\
	LorentzRotationC.cc	\
	LorentzRotationD.cc	\
	LorentzVector.cc	\
	LorentzVectorB.cc	\
	LorentzVectorC.cc	\
	LorentzVectorK.cc	\
	LorentzVectorL.cc	\
	LorentzVectorR.cc	\
	Rotation.cc		\
	RotationA.cc		\
	RotationC.cc		\
	RotationE.cc		\
	RotationIO.cc		\
	RotationInterfaces.cc	\
	RotationL.cc		\
	RotationP.cc		\
	RotationX.cc		\
	RotationXYZ.cc		\
	RotationY.cc		\
	RotationZ.cc		\
	SpaceVector.cc		\
	SpaceVectorD.cc		\
	SpaceVectorP.cc		\
	SpaceVectorR.cc		\
	ThreeVector.cc		\
	ThreeVectorR.cc		\
	TwoVector.cc		\
	ZMinput.cc		\
	ZMxpv.cc

libCLHEP_Vector_@VERSION@_so_OBJECTS = $(patsubst %.cc,$(shareddir)/%.$(OBJEXT),$(libCLHEP_Vector_@VERSION@_a_SOURCES))

# these if/else blocks will be parsed by automake and translated
if BUILD_SHARED
  shareddir = shared
if BUILD_VISUAL
  lib_shared = CLHEP-Vector-@VERSION@.$(SHEXT)
else
  lib_shared = libCLHEP-Vector-@VERSION@.$(SHEXT)
endif
  SHFLAGS = @MY_SHFLAGS@
  SHLINK = @MY_SHLINK@ @MY_SHEXTRA@
  SHNAME = @MY_SHNAME@
endif
if BUILD_STATIC
  lib_LIBRARIES = libCLHEP-Vector-@VERSION@.a
endif

CLEANFILES =  $(lib_shared)

all-local: $(shareddir) $(lib_shared)

$(shareddir):
	test -d $(shareddir) || mkdir $(shareddir)

if BUILD_VISUAL
$(lib_shared): $(libCLHEP_Vector_@VERSION@_so_OBJECTS)
	$(SHLINK) $(SHNAME)$@ $(libCLHEP_Vector_@VERSION@_so_OBJECTS)

$(shareddir)/%.$(OBJEXT): %.cc
	$(CXXCOMPILE) $(SHFLAGS) /c /Fo$@ $<
else
$(lib_shared): $(libCLHEP_Vector_@VERSION@_so_OBJECTS)
	$(CXXLINK) $(SHLINK) $(SHNAME)$@ $(libCLHEP_Vector_@VERSION@_so_OBJECTS) -o $@

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
