## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

INCLUDES = -I$(top_builddir)

libCLHEP_GenericFunctions_@VERSION@_a_SOURCES = \
	Abs.cc       \
	AbsFunctional.cc       \
	AbsFunction.cc       \
	AbsParameter.cc       \
	ACos.cc       \
	AnalyticConvolution.cc       \
	ArrayFunction.cc       \
	ASin.cc       \
	AssociatedLaguerre.cc       \
	AssociatedLegendre.cc       \
	ATan.cc       \
	BivariateGaussian.cc       \
	ConstMinusFunction.cc       \
	ConstMinusParameter.cc       \
	ConstOverFunction.cc       \
	ConstOverParameter.cc       \
	ConstPlusFunction.cc       \
	ConstPlusParameter.cc       \
	ConstTimesFunction.cc       \
	ConstTimesParameter.cc       \
	Cos.cc       \
	CumulativeChiSquare.cc       \
	DefiniteIntegral.cc       \
	Erf.cc       \
	Exp.cc       \
	Exponential.cc       \
	FixedConstant.cc       \
	FloatingConstant.cc       \
	FunctionComposition.cc       \
	FunctionConvolution.cc       \
	FunctionDifference.cc       \
	FunctionDirectProduct.cc       \
	FunctionNegation.cc       \
	FunctionNoop.cc       \
	FunctionNumDeriv.cc       \
	FunctionPlusParameter.cc       \
	FunctionProduct.cc       \
	FunctionQuotient.cc       \
	FunctionSum.cc       \
	FunctionTimesParameter.cc       \
	Gaussian.cc       \
	IncompleteGamma.cc       \
	Landau.cc       \
	LikelihoodFunctional.cc       \
	Ln.cc       \
	LogGamma.cc       \
	LogisticFunction.cc       \
	Mod.cc       \
	Parameter.cc       \
	ParameterDifference.cc       \
	ParameterNegation.cc       \
	ParameterProduct.cc       \
	ParameterQuotient.cc       \
	ParameterSum.cc       \
	PeriodicRectangular.cc       \
	Power.cc       \
	Psi2Hydrogen.cc       \
	PtRelFcn.cc       \
	PuncturedSmearedExp.cc \
	RCBase.cc       \
	Rectangular.cc       \
	ReverseExponential.cc       \
	RKIntegrator.cc       \
	Sigma.cc	\
	Sin.cc       \
	Sqrt.cc       \
	Square.cc       \
	Tan.cc       \
	TrivariateGaussian.cc       \
	Variable.cc       \
	X.cc

libCLHEP_GenericFunctions_@VERSION@_so_OBJECTS = $(patsubst %.cc,$(shareddir)/%.$(OBJEXT),$(libCLHEP_GenericFunctions_@VERSION@_a_SOURCES))

# these if/else blocks will be parsed by automake and translated
if BUILD_SHARED
  shareddir = shared
if BUILD_VISUAL
  lib_shared = CLHEP-GenericFunctions-@VERSION@.$(SHEXT)
else
  lib_shared = libCLHEP-GenericFunctions-@VERSION@.$(SHEXT)
endif
  SHFLAGS = @MY_SHFLAGS@
  SHLINK = @MY_SHLINK@ @MY_SHEXTRA@
  SHNAME = @MY_SHNAME@
endif
if BUILD_STATIC
  lib_LIBRARIES = libCLHEP-GenericFunctions-@VERSION@.a
endif

CLEANFILES =  $(lib_shared)

all-local: $(shareddir) $(lib_shared)

$(shareddir):
	test -d $(shareddir) || mkdir $(shareddir)

if BUILD_VISUAL
$(lib_shared): $(libCLHEP_GenericFunctions_@VERSION@_so_OBJECTS)
	$(SHLINK) $(SHNAME)$@ $(libCLHEP_GenericFunctions_@VERSION@_so_OBJECTS)

$(shareddir)/%.$(OBJEXT): %.cc
	$(CXXCOMPILE) $(SHFLAGS) /c /Fo$@ $<
else
$(lib_shared): $(libCLHEP_GenericFunctions_@VERSION@_so_OBJECTS)
	$(CXXLINK) $(SHLINK) $(SHNAME)$@ $(libCLHEP_GenericFunctions_@VERSION@_so_OBJECTS) -o $@

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
