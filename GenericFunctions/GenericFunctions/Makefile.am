## Process this file with automake to produce Makefile.in
 
if USE_GMAKE
  MAKE = gmake
endif

includedir = $(prefix)/include/CLHEP
tempincludedir = $(TEMPDIR)/CLHEP/@PACKAGE@
COPY_P = @COPY_P@

pkginclude_HEADERS = \
	AbsFunctional.hh         \
	AbsFunction.hh         \
	Abs.hh         \
	AbsParameter.hh         \
	ACos.hh         \
	AnalyticConvolution.hh         \
	Argument.hh         \
	ArgumentList.hh         \
	ArrayFunction.hh	\
	ASin.hh         \
	AssociatedLaguerre.hh         \
	AssociatedLegendre.hh         \
	ATan.hh         \
	Bessel.hh         \
	Bessel.icc	\
	BivariateGaussian.hh         \
	ConstMinusFunction.hh         \
	ConstMinusParameter.hh         \
	ConstOverFunction.hh         \
	ConstOverParameter.hh         \
	ConstPlusFunction.hh         \
	ConstPlusParameter.hh         \
	ConstTimesFunction.hh         \
	ConstTimesParameter.hh         \
	Cos.hh         \
	CumulativeChiSquare.hh         \
	CutBase.hh         \
	CutBase.icc	\
	DefiniteIntegral.hh         \
	DoubleParamToArgAdaptor.hh         \
	DoubleParamToArgAdaptor.icc	\
	EllipticIntegral.hh         \
	EllipticIntegral.icc	\
	Erf.hh         \
	Exp.hh         \
	Exponential.hh         \
	FixedConstant.hh         \
	FloatingConstant.hh         \
	FunctionComposition.hh         \
	FunctionConvolution.hh         \
	FunctionDifference.hh         \
	FunctionDirectProduct.hh         \
	FunctionNegation.hh         \
	FunctionNoop.hh         \
	FunctionNumDeriv.hh         \
	FunctionPlusParameter.hh         \
	FunctionProduct.hh         \
	FunctionQuotient.hh         \
	FunctionSum.hh         \
	FunctionTimesParameter.hh         \
	Gaussian.hh         \
	GenericFunctions.hh         \
	IncompleteGamma.hh         \
	Landau.hh         \
	LikelihoodFunctional.hh         \
	Ln.hh         \
	LogGamma.hh         \
	LogisticFunction.hh         \
	Mod.hh         \
	ParameterDifference.hh         \
	Parameter.hh         \
	ParameterNegation.hh         \
	ParameterProduct.hh         \
	ParameterQuotient.hh         \
	ParameterSum.hh         \
	ParamToArgAdaptor.hh         \
	ParamToArgAdaptor.icc	\
	PeriodicRectangular.hh         \
	Power.hh         \
	Psi2Hydrogen.hh         \
	PtRelFcn.hh        \
	PuncturedSmearedExp.hh \
	RCBase.hh        \
	Rectangular.hh         \
	ReverseExponential.hh         \
	RKIntegrator.hh         \
	Sigma.hh         \
	Sin.hh         \
	SphericalBessel.hh         \
	SphericalBessel.icc	\
	SphericalNeumann.hh         \
	SphericalNeumann.icc	\
	Sqrt.hh         \
	Square.hh         \
	Tan.hh         \
	TrivariateGaussian.hh         \
	Variable.hh         \
	X.hh	\
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
