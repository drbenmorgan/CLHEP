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
	Airy.hh         \
	Airy.icc        \
	AnalyticConvolution.hh         \
	Argument.hh         \
	ArgumentList.hh         \
	ArrayFunction.hh	\
	ASin.hh         \
	AssociatedLaguerre.hh         \
	AssociatedLegendre.hh         \
	AssociatedLegendre.icc         \
	ATan.hh         \
	Bessel.hh         \
	Bessel.icc	\
	BetaDistribution.hh \
	BivariateGaussian.hh         \
	ClassicalSolver.hh \
	ClebschGordanCoefficientSet.hh \
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
	EfficiencyFunctional.hh \
	EllipticIntegral.hh         \
	EllipticIntegral.icc	\
	Erf.hh         \
	Exp.hh         \
	Exponential.hh         \
	FixedConstant.hh         \
	FloatingConstant.hh         \
	FourierFit.hh \
	FourierFit.icc \
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
	Gamma.hh         \
	GammaDistribution.hh         \
	GenericFunctions.hh         \
	IncompleteGamma.hh         \
	InterpolatingPolynomial.hh         \
	Landau.hh         \
	LegendreCoefficientSet.hh \
	LegendreCoefficientSet.icc \
	LegendreExpansion.hh \
	LegendreExpansion.icc \
	LegendreFit.hh \
	LegendreFit.icc \
	KroneckerDelta.hh \
	Legendre.hh         \
	Legendre.icc         \
	LikelihoodFunctional.hh         \
	Ln.hh         \
	LogGamma.hh         \
	LogisticFunction.hh         \
	Mod.hh         \
	NonrelativisticBW.hh          \
	ParameterComposition.hh         \
	ParameterDifference.hh         \
	Parameter.hh         \
	ParameterNegation.hh         \
	ParameterProduct.hh         \
	ParameterQuotient.hh         \
	ParameterSum.hh         \
	ParamToArgAdaptor.hh         \
	ParamToArgAdaptor.icc	\
	PeriodicRectangular.hh         \
	PhaseSpace.hh       \
	Power.hh         \
	Psi2Hydrogen.hh         \
	Psi2Hydrogen.icc         \
	PtRelFcn.hh        \
	PuncturedSmearedExp.hh \
	RCBase.hh        \
	Rectangular.hh         \
	RelativisticBW.hh          \
	ReverseExponential.hh         \
	RKIntegrator.hh         \
	RungeKuttaClassicalSolver.hh \
	Sigma.hh         \
	Sin.hh         \
	SphericalBessel.hh         \
	SphericalBessel.icc	\
	SphericalNeumann.hh         \
	SphericalNeumann.icc	\
	SphericalHarmonicFit.hh \
	SphericalHarmonicFit.icc \
	SphericalHarmonicExpansion.hh \
	SphericalHarmonicExpansion.icc \
	SphericalHarmonicCoefficientSet.hh \
	SphericalHarmonicCoefficientSet.icc \
	Sqrt.hh         \
	Square.hh         \
	SymToArgAdaptor.hh \
	SymToArgAdaptor.icc \
	Tan.hh         \
	Theta.hh         \
	TrivariateGaussian.hh         \
	Variable.hh         \
	VoigtProfile.hh          \
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
