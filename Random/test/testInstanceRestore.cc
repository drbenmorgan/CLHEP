// ----------------------------------------------------------------------
#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "CLHEP/Random/defs.h"
#include <iostream>
#include <iomanip>
#include <vector>

#define CLEAN_OUTPUT
#ifdef CLEAN_OUTPUT
  std::ofstream output("testInstanceRestore.cout");  
#else
  std::ostream & output = std::cout;
#endif

// Normally on  for routine validation:


#ifdef TURNOFF
#endif

#define TEST_ENGINE_NAMES
#define TEST_INSTANCE_METHODS

#define VERBOSER
#define VERBOSER2

using namespace CLHEP;

// Absolutely Safe Equals Without Registers Screwing Us Up
bool equals01(const std::vector<double> &ab) {
  return ab[1]==ab[0];
}  
bool equals(double a, double b) {
  std::vector<double> ab(2);
  ab[0]=a;  ab[1]=b;
  return (equals01(ab));
}

std::vector<double> aSequence(int n) {
  std::vector<double> v;
  DualRand e(13542);
  RandFlat f(e);
  for (int i=0; i<n; i++) {
    v.push_back(f()); 
  }
  return v;
}

// ----------- Tests for instance methods -----------

template <class E>
int checkEngineName(const std::string & name) {
  int stat = 0;
  output << E::engineName() << "\n";
  if (E::engineName() != name) {
    std::cout << "???? engineName mismatch for " << name << " <--> " 
    					<< E::engineName() << "\n";
    #ifdef CLEAN_OUTPUT
    output << "???? engineName mismatch for " << name << " <--> " 
    					<< E::engineName() << "\n";
    #endif
    stat |= 256;
  }
  E e(123);
  if (e.name() != name) {
    std::cout << "???? name mismatch for " << name << " <--> " 
    					<< e.name() << "\n";
    #ifdef CLEAN_OUTPUT
    output << "???? name mismatch for " << name << " <--> " 
    					<< e.name() << "\n";
    #endif
    stat |= 256;
  }
  return stat;
}

template <class E, class D>
int checkEngine() {
  int stat = 0;
  E e(1234);
  D d(e);
  if (d.engine().name() != e.name()) {
    std::cout << "???? Improper d.engine() \n";
    #ifdef CLEAN_OUTPUT
    output << "???? Improper d.engine() \n";
    #endif
    stat |= 512;
  }
  return stat;
}

template <class E>
int checkEngineInstanceSave(E & e) {
  int stat = 0;
  output << "checkEngineInstanceSave for " << e.name() << "\n";
  int pr=output.precision(20);
  double r=0; 
  for (int i=0; i<100; i++) r += e.flat();
  {std::ofstream os ("engine.save"); os << e;}
  for (int i=0; i<100; i++) r += e.flat();
  double keyValue1 = e.flat();
  double keyValue2 = e.flat();
#ifdef VERBOSER
  output << keyValue1 << " " << keyValue2 << "\n";
#endif
  E e2;
  {std::ifstream is ("engine.save"); is >> e2;}
  for (int i=0; i<100; i++) r += e2.flat();
  double k1 = e2.flat();
  double k2 = e2.flat();
#ifdef VERBOSER
  output << k1 << " " << k2 << "\n";
#endif
  if ( !(equals(k1,keyValue1)) || !(equals(k2,keyValue2)) ) {
    std::cout << "???? checkInstanceSave failed for " << e.name() << "\n";
    #ifdef CLEAN_OUTPUT
    output << "???? checkInstanceSave failed for " << e.name() << "\n";
    #endif
    stat |= 1024;
  }
  output.precision(pr);
  return stat;
}

template <class E, class D>
int checkSaveDistribution(D & d, int nth) {
  dynamic_cast<E &>(d.engine());
  int stat = 0;
  output << "checkSaveDistribution with " << d.engine().name() 
  	    << ", " << d.name() << "\n";
  double r=0; 
  r = d();
  double keyValue1, keyValue2, keyValue3, keyValue4;
  for (int i=0; i<nth; i++) r += d();
  {std::ofstream os ("distribution.save1"); os << d.engine() << d;}
  keyValue1 = d();
  keyValue2 = d();
  r += d();
  // A second capture will test non-cached if first tested cached case:
  {std::ofstream os ("distribution.save2"); os << d.engine() << d;}
  keyValue3 = d();
  keyValue4 = d();
  int pr = output.precision(20);
#ifdef VERBOSER
  output << "keyValue1 = " << keyValue1 <<
             "  keyValue2 = " << keyValue2 << "\n";
  output << "keyValue3 = " << keyValue3 <<
             "  keyValue3 = " << keyValue4 << "\n";
#endif
  output.precision(pr);
  E e;
  D d2(e);   
  { std::ifstream is ("distribution.save1"); is >> e >> d2;}
  double k1 = d2();
  double k2 = d2();
  { std::ifstream is ("distribution.save2"); is >> e >> d2;}
  double k3 = d2();
  double k4 = d2();
#ifdef VERBOSER
  pr = output.precision(20);
  output << "k1 =        " << k1 <<
             "  k2 =        " << k2 << "\n";
  output << "k3 =        " << k3 <<
             "  k4 =        " << k4 << "\n";
  output.precision(pr);
#endif
  if ( !equals(k1,keyValue1) || !equals(k2,keyValue2) ||
       !equals(k3,keyValue3) || !equals(k4,keyValue4) ) {
    std::cout << "???? Incorrect restored value for distribution " 
    			<< d.name() << "\n"; 
    #ifdef CLEAN_OUTPUT
    output << "???? Incorrect restored value for distribution " 
    			<< d.name() << "\n"; 
    #endif
    stat |= 2048;
  }
//  if (stat) exit(-1);
  return stat;
}

template <class E>
int checkRandGeneralDistribution(RandGeneral & d, int nth) {
  dynamic_cast<E &>(d.engine());
  int stat = 0;
  output << "checkSaveDistribution with " << d.engine().name() 
  	    << ", " << d.name() << "\n";
  double r=0; 
  r = d();
  double keyValue1, keyValue2, keyValue3, keyValue4;
  for (int i=0; i<nth; i++) r += d();
  {std::ofstream os ("distribution.save1"); os << d.engine() << d;}
  keyValue1 = d();
  keyValue2 = d();
  r += d();
  // A second capture will test non-cached if first tested cached case:
  {std::ofstream os ("distribution.save2"); os << d.engine() << d;}
  keyValue3 = d();
  keyValue4 = d();
  int pr = output.precision(20);
#ifdef VERBOSER
  output << "keyValue1 = " << keyValue1 <<
             "  keyValue2 = " << keyValue2 << "\n";
  output << "keyValue3 = " << keyValue3 <<
             "  keyValue3 = " << keyValue4 << "\n";
#endif
  output.precision(pr);
  E e;
  double temp = 1; 
  RandGeneral d2(e, &temp, 1);   
  { std::ifstream is ("distribution.save1"); is >> e >> d2;}
  double k1 = d2();
  double k2 = d2();
  { std::ifstream is ("distribution.save2"); is >> e >> d2;}
  double k3 = d2();
  double k4 = d2();
#ifdef VERBOSER
  pr = output.precision(20);
  output << "k1 =        " << k1 <<
             "  k2 =        " << k2 << "\n";
  output << "k3 =        " << k3 <<
             "  k4 =        " << k4 << "\n";
  output.precision(pr);
#endif
  if ( !equals(k1,keyValue1) || !equals(k2,keyValue2) ||
       !equals(k3,keyValue3) || !equals(k4,keyValue4) ) {
    std::cout << "???? Incorrect restored value for distribution " 
    			<< d.name() << "\n"; 
    #ifdef CLEAN_OUTPUT
    output << "???? Incorrect restored value for distribution " 
    			<< d.name() << "\n"; 
    #endif
    stat |= 2048;
  }
//  if (stat) exit(-1);
  return stat;
}

template <class E>
int checkDistributions() {
  int stat = 0;
  {RandGauss d(new E(12561),100.0,3.0);
   stat |= checkSaveDistribution<E,RandGauss> (d,33); 			}
  {RandGauss d(new E(12572),100.0,3.0);
   stat |= checkSaveDistribution<E,RandGauss> (d,34); 			}
  {RandGaussQ d(new E(12563),10.0,4.0);
   stat |= checkSaveDistribution<E,RandGaussQ> (d,33); 			}
  {RandGaussT d(new E(12564),5.0,2.0);
   stat |= checkSaveDistribution<E,RandGaussT> (d,33); 			}
  {RandBinomial d(new E(12565),4,0.6);
   stat |= checkSaveDistribution<E,RandBinomial> (d,33); 		}
  {RandFlat d(new E(12576),12.5,35.0);
   stat |= checkSaveDistribution<E,RandFlat> (d,33); 			}
  {RandBit d(new E(12567));
   stat |= checkSaveDistribution<E,RandBit> (d,31); 			}
  {RandBit d(new E(12578));
   stat |= checkSaveDistribution<E,RandBit> (d,32); 			}
  {RandBit d(new E(12589));
   stat |= checkSaveDistribution<E,RandBit> (d,33); 			}
  {RandBreitWigner d(new E(125611),50.0,15.0);
   stat |= checkSaveDistribution<E,RandBreitWigner> (d,33); 		}
  {RandChiSquare d(new E(125612),5.0);
   stat |= checkSaveDistribution<E,RandChiSquare> (d,33); 		}
  {RandExponential d(new E(125713),8.00);
   stat |= checkSaveDistribution<E,RandExponential> (d,33); 		}
  {RandGamma d(new E(125713),6.0,2.0);
   stat |= checkSaveDistribution<E,RandGamma> (d,33); 			}
  {RandLandau d(new E(125714));
   stat |= checkSaveDistribution<E,RandLandau> (d,33); 			}
  {RandStudentT d(new E(125715),5);
   stat |= checkSaveDistribution<E,RandStudentT> (d,33); 		}

  // Multiple tests of Poisson distributions for small desired, since 
  // the answer in each test is a small int, and coincidental agreement
  // is very possible.
  
  {RandPoisson d(new E(125616),2.5);
   stat |= checkSaveDistribution<E,RandPoisson> (d,33); 		}
  {RandPoisson d(new E(125617),105.0);
   stat |= checkSaveDistribution<E,RandPoisson> (d,34); 		}
  {RandPoisson d(new E(125618),2.5);
   stat |= checkSaveDistribution<E,RandPoisson> (d,35); 		}
  {RandPoisson d(new E(325618),2.5);
   stat |= checkSaveDistribution<E,RandPoisson> (d,36); 		}
  {RandPoisson d(new E(425618),2.5);
   stat |= checkSaveDistribution<E,RandPoisson> (d,37); 		}
  {RandPoisson d(new E(525618),2.5);
   stat |= checkSaveDistribution<E,RandPoisson> (d,38); 		}
  {RandPoisson d(new E(125619),110.0);
   stat |= checkSaveDistribution<E,RandPoisson> (d,39); 		}
  {RandPoissonQ d(new E(124616),2.5);
   stat |= checkSaveDistribution<E,RandPoissonQ> (d,33); 		}
  {RandPoissonQ d(new E(126616),2.5);
   stat |= checkSaveDistribution<E,RandPoissonQ> (d,32); 		}
  {RandPoissonQ d(new E(127616),2.5);
   stat |= checkSaveDistribution<E,RandPoissonQ> (d,31); 		}
  {RandPoissonQ d(new E(129616),2.5);
   stat |= checkSaveDistribution<E,RandPoissonQ> (d,30); 		}
  {RandPoissonQ d(new E(125616),110.0);
   stat |= checkSaveDistribution<E,RandPoissonQ> (d,33); 		}
  {RandPoissonQ d(new E(125616),2.5);
   stat |= checkSaveDistribution<E,RandPoissonQ> (d,34); 		}
  {RandPoissonQ d(new E(125616),110.0);
   stat |= checkSaveDistribution<E,RandPoissonQ> (d,34); 		}
  {RandPoissonT d(new E(125616),2.5);
   stat |= checkSaveDistribution<E,RandPoissonT> (d,33); 		}
  {RandPoissonT d(new E(125616),110.0);
   stat |= checkSaveDistribution<E,RandPoissonT> (d,33); 		}
  {RandPoissonT d(new E(125616),2.5);
   stat |= checkSaveDistribution<E,RandPoissonT> (d,34); 		}
  {RandPoissonT d(new E(125616),110.0);
   stat |= checkSaveDistribution<E,RandPoissonT> (d,34); 		}
  {RandPoissonT d(new E(125916),2.5);
   stat |= checkSaveDistribution<E,RandPoissonT> (d,10); 		}
  {RandPoissonT d(new E(125816),2.5);
   stat |= checkSaveDistribution<E,RandPoissonT> (d,11); 		}
  {RandPoissonT d(new E(125716),2.5);
   stat |= checkSaveDistribution<E,RandPoissonT> (d,12); 		}

  {std::vector<double> pdf;
   int nbins = 20;
   for (int i = 0; i < nbins; ++i) 
   		pdf.push_back( 5*i + (10.5-i) * (10.5-i) );
   RandGeneral d(new E(125917), &pdf[0], 20);  
   stat |= checkRandGeneralDistribution<E> (d,33);  		}
   
  return stat;
}

// ---------------------------------------------
// ---------------------------------------------
// ---------------------------------------------


int main() {
  int stat = 0;

#ifdef TEST_ENGINE_NAMES
  output << "\n=============================================\n";
  output << "              Part II \n";
  output << "Check all engine names were entered correctly \n";
  output << "=============================================\n\n";

  stat |= checkEngineName<DRand48Engine >("DRand48Engine");
  stat |= checkEngineName<DualRand      >("DualRand");
  stat |= checkEngineName<Hurd160Engine >("Hurd160Engine");
  stat |= checkEngineName<Hurd288Engine >("Hurd288Engine");
  stat |= checkEngineName<HepJamesRandom>("HepJamesRandom");
  stat |= checkEngineName<MTwistEngine  >("MTwistEngine");
  stat |= checkEngineName<RandEngine    >("RandEngine");
  stat |= checkEngineName<RanecuEngine  >("RanecuEngine");
  stat |= checkEngineName<Ranlux64Engine>("Ranlux64Engine");
  stat |= checkEngineName<RanluxEngine  >("RanluxEngine");
  stat |= checkEngineName<RanshiEngine  >("RanshiEngine");
  stat |= checkEngineName<TripleRand    >("TripleRand");
#endif

#ifdef TEST_INSTANCE_METHODS
  output << "===========================================\n\n";
  output << "              Part III\n";
  output << "Check instance methods for specific engines \n";
  output << "     specific engines and distributions\n";
  output << "===========================================\n\n";

  {DualRand e(234);	    stat |= checkEngineInstanceSave(e);}
  {Hurd160Engine e(234);    stat |= checkEngineInstanceSave(e);}
  {Hurd288Engine e(234);    stat |= checkEngineInstanceSave(e);}
  {HepJamesRandom e(234);   stat |= checkEngineInstanceSave(e);}
  {MTwistEngine e(234);     stat |= checkEngineInstanceSave(e);}
  {RandEngine e(234);	    stat |= checkEngineInstanceSave(e);}
  {RanecuEngine e(234);     stat |= checkEngineInstanceSave(e);}
  {Ranlux64Engine e(234);   stat |= checkEngineInstanceSave(e);}
  {RanluxEngine e(234);     stat |= checkEngineInstanceSave(e);}
  {RanshiEngine e(234);     stat |= checkEngineInstanceSave(e);}
  {TripleRand e(234);	    stat |= checkEngineInstanceSave(e);}

  {std::vector<double> nonRand = aSequence(500);
   NonRandomEngine e; 
   e.setRandomSequence(&nonRand[0], nonRand.size());
   stat |= checkEngineInstanceSave(e);}

  stat |= checkDistributions<DualRand>();
  stat |= checkDistributions<Hurd160Engine>();
  stat |= checkDistributions<Hurd288Engine>();
  stat |= checkDistributions<HepJamesRandom>();
  stat |= checkDistributions<MTwistEngine>();
  stat |= checkDistributions<Ranlux64Engine>();
  stat |= checkDistributions<RanluxEngine>();
  stat |= checkDistributions<RanshiEngine>();
  stat |= checkDistributions<TripleRand>();

  RandGaussQ::shoot();  // Just to verify that the static engine is OK
#endif

  output << "\n=============================================\n\n";

  if (stat != 0) {
     std::cout << "One or more problems detected: stat = " << stat << "\n";
     output << "One or more problems detected: stat = " << stat << "\n";
  }  else {
     output << "testInstanceRestore passed with no problems detected.\n";    
  }

  if (stat == 0) return 0;
  if (stat > 0) return -(stat|1);
  return stat|1;

}	

