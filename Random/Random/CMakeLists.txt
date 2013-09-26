
set( pkginclude_HEADERS DoubConv.hh
			DRand48Engine.h
			DualRand.h
			EngineFactory.h
			engineIDulong.h
			Hurd160Engine.h
			Hurd288Engine.h
			JamesRandom.h
			MTwistEngine.h
			NonRandomEngine.h
			RandBinomial.h
			RandBinomial.icc
			RandBit.h
			RandBit.icc
			RandBreitWigner.h
			RandBreitWigner.icc
			RandChiSquare.h
			RandChiSquare.icc
			RandEngine.h
			RandExponential.h
			RandExponential.icc
			RandExpZiggurat.h
			RandFlat.h
			RandFlat.icc
			RandGamma.h
			RandGamma.icc
			RandGauss.h
			RandGauss.icc
			RandGaussQ.h
			RandGaussQ.icc
			RandGaussT.h
			RandGaussT.icc
			RandGaussZiggurat.h
			RandGeneral.h
			RandGeneral.icc
			RandLandau.h
			RandLandau.icc
			RandomEngine.h
			RandomEngine.icc
			Random.h
			Random.icc
			Randomize.h
			RandomFunc.h
			RandPoisson.h
			RandPoisson.icc
			RandPoissonQ.h
			RandPoissonQ.icc
			RandPoissonT.h
			RandPoissonT.icc
			RandSkewNormal.h
			RandSkewNormal.icc
			RandStudentT.h
			RandStudentT.icc
			RanecuEngine.h
			Ranlux64Engine.h
			RanluxEngine.h
			RanshiEngine.h
			SeedTable.h
			Stat.h
			StaticRandomStates.h
			TripleRand.h )

# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS}  
         DESTINATION include/CLHEP/Random )

