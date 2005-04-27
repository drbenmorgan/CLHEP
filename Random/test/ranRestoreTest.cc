// -*- C++ -*-
// $Id: ranRestoreTest.cc,v 1.4 2005/04/27 20:12:50 garren Exp $
// ----------------------------------------------------------------------
#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "CLHEP/Random/defs.h"
#include <iostream>
#include <iomanip>
#include <vector>

#define CLEAN_OUTPUT
#ifdef CLEAN_OUTPUT
  std::ofstream output("ranRestoreTest.cout");  
#else
  std::ostream & output = std::cout;
#endif

// Normally on  for routine validation:

#define TEST_ORIGINAL_SAVE

#ifdef TURNOFF
#endif

#define TEST_ENGINE_NAMES
#define TEST_INSTANCE_METHODS
#define TEST_SHARED_ENGINES
#define TEST_STATIC_SAVE
#define TEST_SAVE_STATIC_STATES
#define TEST_ANONYMOUS_ENGINE_RESTORE
#define TEST_ANONYMOUS_RESTORE_STATICS
#define TEST_VECTOR_ENGINE_RESTORE

// Normally off for routine validation:

#ifdef TURNOFF
#define TEST_MISSING_FILES
#define CREATE_OLD_SAVES
#define VERIFY_OLD_SAVES
#endif

//#define VERBOSER
//#define VERBOSER2

using namespace CLHEP;

double remembered_r2;
double remembered_r1005;
double remembered_r1006;
double remembered_r1007;

// Absolutely Safe Equals Without Registers Screwing Us Up
bool equals01(const std::vector<double> &ab) {
  return ab[1]==ab[0];
}  
bool equals(double a, double b) {
  std::vector<double> ab(2);
  ab[0]=a;  ab[1]=b;
  return (equals01(ab));
}

// ------------------- The following should all FAIL ------------

int saveStepX() {
  double r = RandGauss::shoot();
  output << "r(1) = " << r << std::endl;
  HepRandom::saveEngineStatus();
  r = RandGauss::shoot();
  output << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandGauss::shoot();
  output << "r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  remembered_r1005 = r;
  output << "r1005= " << r << std::endl;
  r = RandGauss::shoot();
  return 0;
}

int restoreStepX() {
  HepRandom::restoreEngineStatus();
  double r = RandGauss::shoot();
  output << "restored r(2) = " << r << std::endl;
  if ( ! equals(r,remembered_r2) ) {
    output << "THIS DOES NOT MATCH REMEMBERED VALUE BUT THAT IS EXPECTED\n";
  }
  r = RandGauss::shoot();
  output << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  output << "restored r1005= " << r << std::endl;
  if ( !equals(r,remembered_r1005) ) {
    output << "THIS DOES NOT MATCH REMEMBERED VALUE BUT THAT IS EXPECTED\n";
  }
  return 0;
}

int BsaveStepX() {
  int r = RandFlat::shootBit();
  output << "r(1) = " << r << std::endl;
  HepRandom::saveEngineStatus();
  r = RandFlat::shootBit();
  output << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandFlat::shootBit();
  output << "r(3) = " << r << std::endl;
  double d;
  for (int i=0; i < 1001; i++) {
    d = RandFlat::shoot();
    if (d > 1) output << 
    "This line inserted so clever compilers don't warn about not using d\n";
  }    
  r = RandFlat::shootBit();
  remembered_r1005 = r;
  output << "r1005= " << r << std::endl;
  r = RandFlat::shootBit();
  return 0;
}

int BrestoreStepX() {
  HepRandom::restoreEngineStatus();
  int r = RandFlat::shootBit();
  output << "restored r(2) = " << r << std::endl;
  if ( r != remembered_r2 ) {
    output << "THIS DOES NOT MATCH REMEMBERED VALUE BUT THAT IS EXPECTED\n";
  }
  r = RandFlat::shootBit();
  output << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandFlat::shootBit();
  }    
  r = RandFlat::shootBit();
  output << "restored r1005= " << r << std::endl;
  if ( r != remembered_r1005 ) {
    output << "THIS DOES NOT MATCH REMEMBERED VALUE BUT THAT IS EXPECTED\n";
  }
  return 0;
}

// ------------------- The following should all WORK ------------

int saveStep() {
  int stat=0;
  double r = RandGauss::shoot();
  output << "r(1) = " << r << std::endl;
  RandGauss::saveEngineStatus();
  r = RandGauss::shoot();
  output << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandGauss::shoot();
  output << "r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  remembered_r1005 = r;
  output << "r1005= " << r << std::endl;
  r = RandGauss::shoot();
  return stat;
}

int restoreStep() {
  int stat=0;
  RandGauss::restoreEngineStatus();
  double r = RandGauss::shoot();
  output << "restored r(2) = " << r << std::endl;
  if ( !equals(r,remembered_r2) ) {
    std::cout << "restored r(2) = " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    stat += 1;
  }
  r = RandGauss::shoot();
  output << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandGauss::shoot();
  }    
  r = RandGauss::shoot();
  output << "restored r1005= " << r << std::endl;
  if ( !equals(r,remembered_r1005) ) {
    std::cout << "restored r1005= " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
    stat += 2;
  }
  return stat;
}

int BsaveStep() {
  int stat=0;
  int r = RandFlat::shootBit();
  output << "r(1) = " << r << std::endl;
  RandFlat::saveEngineStatus();
  r = RandFlat::shootBit();
  output << "r(2) = " << r << std::endl;
  remembered_r2 = r;
  r = RandFlat::shootBit();
  output << "r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandFlat::shootBit();
  }    
  r = RandFlat::shootBit();
  remembered_r1005 = r;
  output << "r1005 = " << r << std::endl;
  r = RandFlat::shootBit();
  remembered_r1006 = r;
  output << "r1006 = " << r << std::endl;
  r = RandFlat::shootBit();
  remembered_r1007 = r;
  output << "r1007 = " << r << std::endl;
  r = RandFlat::shootBit();
  return stat;
}

int BrestoreStep() {
  int stat=0;
  RandFlat::restoreEngineStatus();
  int r = RandFlat::shootBit();
  output << "restored r(2) = " << r << std::endl;
  if ( r != remembered_r2 ) {
    stat += 4;
    std::cout << "restored r(2) = " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  r = RandFlat::shootBit();
  output << "restored r(3) = " << r << std::endl;
  for (int i=0; i < 1001; i++) {
    r = RandFlat::shootBit();
  }    
  r = RandFlat::shootBit();
  output << "restored r1005= " << r << std::endl;
  if ( r != remembered_r1005 ) {
    stat += 8;
    std::cout << "restored r1005= " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  r = RandFlat::shootBit();
  output << "restored r1006= " << r << std::endl;
  if ( r != remembered_r1006 ) {
    stat += 16;
    std::cout << "restored r1006= " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  r = RandFlat::shootBit();
  output << "restored r1007= " << r << std::endl;
  if ( r != remembered_r1007 ) {
    stat += 32;
    std::cout << "restored r1007= " << r << std::endl;
    std::cout << "????? THIS DOES NOT MATCH REMEMBERED VALUE!\n";
  }
  return stat;
}

// --- The following should work, by failing in an expected way -------

template <class E, class D>
int fileNotThere() {
  int stat = 0;
  HepRandomEngine * old = D::getTheEngine();
  E e(123);
  output << "File-not-found test restoring "<<D::distributionName()<<":\n";
  D::setTheEngine(&e);
  D::restoreEngineStatus("noSuchFile");
  D::setTheEngine(old);  // If we don't do this, then the static engine shared
  			 // by every shoot() method reamins e -- which is about
			 // to go out of scope and be destructed!
  return stat;
}

template <class E>
int fileNotThereEngine() {
  int stat = 0;
  stat |= fileNotThere <E, RandBinomial>();
  stat |= fileNotThere <E, RandBit>();
  stat |= fileNotThere <E, RandBreitWigner>();
  stat |= fileNotThere <E, RandChiSquare>();
  stat |= fileNotThere <E, RandExponential>();
  stat |= fileNotThere <E, RandFlat>();
  stat |= fileNotThere <E, RandGamma>();
  stat |= fileNotThere <E, RandGauss>();
  stat |= fileNotThere <E, RandGaussQ>();
  stat |= fileNotThere <E, RandGaussT>();
  stat |= fileNotThere <E, RandLandau>();
  stat |= fileNotThere <E, RandPoisson>();
  stat |= fileNotThere <E, RandPoissonQ>();
  stat |= fileNotThere <E, RandPoissonT>();
  stat |= fileNotThere <E, RandStudentT>();
  return stat;
}

int missingFile() {
  int stat = 0;
  stat |= fileNotThereEngine<DRand48Engine>();
  stat |= fileNotThereEngine<DualRand>();
  stat |= fileNotThereEngine<Hurd160Engine>();
  stat |= fileNotThereEngine<Hurd288Engine>();
  stat |= fileNotThereEngine<HepJamesRandom>();
  stat |= fileNotThereEngine<MTwistEngine>();
  stat |= fileNotThereEngine<RandEngine>();
  stat |= fileNotThereEngine<RanecuEngine>();
  stat |= fileNotThereEngine<Ranlux64Engine>();
  stat |= fileNotThereEngine<RanluxEngine>();
  stat |= fileNotThereEngine<RanshiEngine>();
  stat |= fileNotThereEngine<TripleRand>();
  return stat;
}
  
// -- The following was used to capture old-form engine states (sans name) --

template <class E, class D>
int saveEngine(const char* filename) {
  int stat = 0;
  HepRandomEngine * old = D::getTheEngine();
  E e(123);
  D::setTheEngine(&e);
  double r=0; 
  for (int i=0; i<3; i++) r += D::shoot();
  D::saveEngineStatus(filename);
  if (r == -99999999.1) stat = 999; // This prevents clever compilers from
  				    // deducing that r is never needed
  D::setTheEngine(old);  // If we don't do this, then the static engine shared
  			 // by every shoot() method reamins e -- which is about
			 // to go out of scope and be destructed!
  return stat;
}

// -- The following checks on static engine restores, from old and new forms --

template <class E, class D>
int checkSaveEngine(const char* filename) {
  int stat = 0;
  HepRandomEngine * old = D::getTheEngine();

  // Generate save with current format (default file name is fine)
  E e(123);
  D::setTheEngine(&e);
  double r=0; 
  for (int i=0; i<3; i++) r += D::shoot();
  D::saveEngineStatus();

  // Figure out what the key variate value should be
  double keyValue = D::shoot();

  // Restore state based on old file, and check for proper value
  D::restoreEngineStatus(filename);
  if (!equals(D::shoot(), keyValue)) {
    std::cout << "???? Value mismatch from file " << filename << "\n";
    stat |= 64;
  }

  // Restore state based on that save, and check for proper value
  D::restoreEngineStatus();
  if (!equals(D::shoot(),keyValue)) {
    std::cout << "???? Value mismatch from new-format file \n";
    stat |= 128;
  }

  D::setTheEngine(old);  
  return stat;
}


// ----------- Tests for instance methods -----------

template <class E>
int checkEngineName(const std::string & name) {
  int stat = 0;
  output << E::engineName() << "\n";
  if (E::engineName() != name) {
    std::cout << "???? engineName mismatch for " << name << " <--> " 
    					<< E::engineName() << "\n";
    stat |= 256;
  }
  E e(123);
  if (e.name() != name) {
    std::cout << "???? name mismatch for " << name << " <--> " 
    					<< e.name() << "\n";
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

template <class E, class D1, class D2>
int checkSharingDistributions(D1 & d1, D2 & d2, int n1, int n2) {
  int stat = 0;
  output << "checkSharingDistribution with: \n" 
  	    << d1.name() << " using " << d1.engine().name() << " and\n"
  	    << d2.name() << " using " << d2.engine().name() << "\n";
  double r=0; 
  r = d1();
  r += d2();
  double kv11,kv12,kv13,kv14;
  double kv21,kv22,kv23,kv24;
  for (int i=0; i<n1; i++) r += d1();
  for (int j=0; j<n2; j++) r += d2();
  {std::ofstream os ("shared.save1"); os << d1.engine() << d1 << d2;}
  kv11 = d1();
  kv21 = d2();
  kv12 = d1();
  kv22 = d2();
  r += d1() + d2();
  // A second capture will test non-cached if first tested cached case:
  {std::ofstream os ("shared.save2"); os << d1.engine() << d1 << d2;}
  kv13 = d1();
  kv23 = d2();
  kv14 = d1();
  kv24 = d2();
#ifdef VERBOSER2
  int pr = output.precision(20);
  output << "kv11 = " << kv11 <<
             "  kv21 = " << kv21 << "\n";
  output << "kv12 = " << kv12 <<
             "  kv22 = " << kv22 << "\n";
  output << "kv13 = " << kv13 <<
             "  kv23 = " << kv23 << "\n";
  output << "kv14 = " << kv14 <<
             "  kv24 = " << kv24 << "\n";
  output.precision(pr);
#endif
  E e;
  D1 d1r(e);   
  D2 d2r(e);   
  { std::ifstream is ("shared.save1"); is >> e >> d1r >> d2r;}
  double k11 = d1r();
  double k21 = d2r();
  double k12 = d1r();
  double k22 = d2r();
  { std::ifstream is ("shared.save2"); is >> e >> d1r >> d2r;}
  double k13 = d1r();
  double k23 = d2r();
  double k14 = d1r();
  double k24 = d2r();
#ifdef VERBOSER2
  pr = output.precision(20);
  output << "k11 = " << k11 <<
             "  k21 = " << k21 << "\n";
  output << "k12 = " << k12 <<
             "  k22 = " << k22 << "\n";
  output << "k13 = " << k13 <<
             "  k23 = " << k23 << "\n";
  output << "k14 = " << k14 <<
             "  k24 = " << k24 << "\n";
  output.precision(pr);
#endif
  if ( !equals(k11,kv11) || !equals(k21,kv21) ||
       !equals(k12,kv12) || !equals(k22,kv22) ||
       !equals(k13,kv13) || !equals(k23,kv23) ||
       !equals(k14,kv14) || !equals(k24,kv24) ) {
    std::cout << "???? Incorrect restored value for distributions " 
    			<< d1.name() << " " << d2.name() << "\n"; 
    stat |= 4096;
  }
//  if (stat) exit(-1);
  return stat;
}



template <class E>
int checkSharing() {
  int stat = 0;
  E e1(98746);
  RandGauss g1(e1,50.0,4.0);
  RandPoissonQ p1(e1, 112.0);
  RandGauss g2(e1,5.0,44.0);
  RandPoissonQ p2(e1, 212.0);
  stat |= checkSharingDistributions<E, RandGauss, RandPoissonQ>(g1,p1,5,4);
  stat |= checkSharingDistributions<E, RandGauss, RandPoissonQ>(g1,p2,6,6);
  stat |= checkSharingDistributions<E, RandGauss, RandPoissonQ>(g2,p1,8,9);
  stat |= checkSharingDistributions<E, RandGauss, RandPoissonQ>(g1,p1,7,5);
  stat |= checkSharingDistributions<E, RandPoissonQ, RandGauss>(p1,g2,5,4);
  stat |= checkSharingDistributions<E, RandPoissonQ, RandGauss>(p2,g1,6,6);
  stat |= checkSharingDistributions<E, RandPoissonQ, RandGauss>(p1,g1,8,9);
  stat |= checkSharingDistributions<E, RandPoissonQ, RandGauss>(p2,g1,7,5);     
  return stat;
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

// ----------- Tests for static methods -----------

template <class D>
int staticSave(int n) {
  int stat = 0;
  int i;
  output << "staticSave for distribution " << D::distributionName() << "\n";
  double r = 0;
  double v1, v2, k1, k2;
  for (i=0; i < n; i++) r += D::shoot();
  {
    std::ofstream file ("distribution.save1"); 
    D::saveFullState(file);
    v1 = D::shoot();
    D::saveFullState(file);
    v2 = D::shoot();
#ifdef VERBOSER2
    int pr = output.precision(20);
    output << "v1 = " << v1 << "  v2 = " << v2 << "\n";
    output.precision(pr);
#endif
  }
  for (i=0; i < n; i++) r += D::shoot();
  {
    std::ifstream file ("distribution.save1"); 
    D::restoreFullState(file);
    k1 = D::shoot();
    for (i=0; i < n; i++) r += D::shoot();
    D::restoreFullState(file);
    k2 = D::shoot();
#ifdef VERBOSER2
    int pr = output.precision(20);
    output << "k1 = " << k1 << "  k2 = " << k2 << "\n";
    output.precision(pr);
#endif
   }
  if ( (k1 != v1) || (k2 != v2) ) {
    std::cout << "???? restoreFullState failed for " << D::distributionName() << "\n";
    stat |= 8192;
  }

  for (i=0; i < n; i++) r += D::shoot();
  {
    std::ofstream file ("distribution.save2"); 
    D::saveDistState(file) << *D::getTheEngine();
    v1 = D::shoot();
    D::saveDistState(file) << *D::getTheEngine();
    v2 = D::shoot();
#ifdef VERBOSER2
    int pr = output.precision(20);
    output << "v1 = " << v1 << "  v2 = " << v2 << "\n";
    output.precision(pr);
#endif
  }
  for (i=0; i < n; i++) r += D::shoot();
  {
    std::ifstream file ("distribution.save2"); 
    D::restoreDistState(file) >> *D::getTheEngine();
    k1 = D::shoot();
    for (i=0; i < n; i++) r += D::shoot();
    D::restoreDistState(file) >> *D::getTheEngine();
    k2 = D::shoot();
#ifdef VERBOSER2
    int pr = output.precision(20);
    output << "k1 = " << k1 << "  k2 = " << k2 << "\n";
    output.precision(pr);
#endif
  }
  if ( (k1 != v1) || (k2 != v2) ) {
    std::cout << "???? restoreDistState failed for " << D::distributionName() << "\n";
    stat |= 16384;
  }

  return stat;
}

template <class D>
int staticSaveShootBit(int n) {
  int stat = 0;
  int i;
  output << "staticSaveShootBit for " << D::distributionName() << "\n";
  double r = 0;
  int bit = 0;
  int v1, v2, k1, k2;
  for (i=0; i < n; i++) r += D::shoot();
  for (i=0; i < n; i++) bit |= D::shootBit();
  {
    std::ofstream file ("distribution.save1"); 
    D::saveFullState(file);
    v1=0;
    for (i=0; i<25; i++) {
      v1 <<=1;
      v1 += D::shootBit();
    }
    for (i=0; i < n; i++) bit |= D::shootBit();
    D::saveFullState(file);
    v2=0;
    for (i=0; i<25; i++) {
      v2 <<=1;
      v2 += D::shootBit();
    }
#ifdef VERBOSER2
    int pr = output.precision(20);
    output << std::hex << "v1 = " << v1 << "  v2 = " << v2 << std::dec << "\n";
    output.precision(pr);
#endif
  }
  for (i=0; i < n; i++) r += D::shoot();
  {
    std::ifstream file ("distribution.save1"); 
    D::restoreFullState(file);
    k1=0;
    for (i=0; i<25; i++) {
      k1 <<=1;
      k1 += D::shootBit();
    }
    for (i=0; i < n; i++) r += D::shoot();
    D::restoreFullState(file);
    k2=0;
    for (i=0; i<25; i++) {
      k2 <<=1;
      k2 += D::shootBit();
    }
#ifdef VERBOSER2
    int pr = output.precision(20);
    output << std::hex << "k1 = " << k1 << "  k2 = " << k2 << std::dec << "\n";
    output.precision(pr);
#endif
   }
  if ( (k1 != v1) || (k2 != v2) ) {
    std::cout << "???? restoreFullState failed for D shootBit()\n";
    stat |= 32768;
  }

  for (i=0; i < n; i++) r += D::shoot();
  for (i=0; i < n; i++) bit |= D::shootBit();
  {
    std::ofstream file ("distribution.save2"); 
    D::saveDistState(file) << *D::getTheEngine();
    v1=0;
    for (i=0; i<25; i++) {
      v1 <<=1;
      v1 += D::shootBit();
    }
    for (i=0; i < n; i++) bit |= D::shootBit();
    D::saveDistState(file) << *D::getTheEngine();
    v2=0;
    for (i=0; i<25; i++) {
      v2 <<=1;
      v2 += D::shootBit();
    }
#ifdef VERBOSER2
    int pr = output.precision(20);
    output << std::hex << "v1 = " << v1 << "  v2 = " << v2 << std::dec << "\n";
    output.precision(pr);
#endif
  }
  for (i=0; i < n; i++) r += D::shoot();
  {
    std::ifstream file ("distribution.save2"); 
    D::restoreDistState(file) >> *D::getTheEngine();
    k1=0;
    for (i=0; i<25; i++) {
      k1 <<=1;
      k1 += D::shootBit();
    }
    for (i=0; i < n; i++) r += D::shoot();
    for (i=0; i < n; i++) r += D::shootBit();
    D::restoreDistState(file) >> *D::getTheEngine();
    k2=0;
    for (i=0; i<25; i++) {
      k2 <<=1;
      k2 += D::shootBit();
    }
#ifdef VERBOSER2
    int pr = output.precision(20);
    output << std::hex << "k1 = " << k1 << "  k2 = " << k2 << std::dec << "\n";
    output.precision(pr);
#endif
  }
  if ( (k1 != v1) || (k2 != v2) ) {
    std::cout << "???? restoreDistState failed for RnadFlat::shootBit()\n";
    stat |= 65536;
  }

  return stat;
}

// ----------- Tests saving all statics together -----------

void randomizeStatics(int n) {
  for (int i=0; i<n; i++) {
    RandGauss::shoot();
    RandGaussQ::shoot();
    RandGaussT::shoot();
    RandFlat::shoot();
    RandBit::shoot();
    RandFlat::shootBit();
    RandBit::shootBit();
    RandPoisson::shoot();
    RandPoissonQ::shoot();
    RandPoissonT::shoot();
    RandBinomial::shoot();
    RandBreitWigner::shoot();
    RandChiSquare::shoot();
    RandExponential::shoot();
    RandGamma::shoot();
    RandLandau::shoot();
    RandStudentT::shoot();
  }
}

std::vector<double> captureStatics() {
  std::vector<double> c;
  c.push_back( RandGauss::shoot() );
  c.push_back( RandGaussQ::shoot() );
  c.push_back( RandGaussT::shoot() );
  c.push_back( RandFlat::shoot() );
  c.push_back( RandBit::shoot() );
  for (int i=0; i<20; i++)  {
    c.push_back( RandFlat::shootBit() );
    c.push_back( RandBit::shootBit() );
  }
  c.push_back( RandPoisson::shoot() );      
  c.push_back( RandPoissonQ::shoot() );     
  c.push_back( RandPoissonT::shoot() );     
  c.push_back( RandBinomial::shoot() );     
  c.push_back( RandBreitWigner::shoot() );  
  c.push_back( RandChiSquare::shoot() );    
  c.push_back( RandExponential::shoot() );  
  c.push_back( RandGamma::shoot() );	     
  c.push_back( RandLandau::shoot() );       
  c.push_back( RandStudentT::shoot() );
  return c;     
}

void saveStatics(std::string filename) {
  std::ofstream os(filename.c_str());
  RandGeneral::saveStaticRandomStates(os);
  // It should be possible to call this from HepRandom, or any distribution.
  // RandGeneral, which is meaningless as a static distribution, should be the
  // toughest test, so we use that here.
}

void restoreStatics(std::string filename) {
  std::ifstream is(filename.c_str());
  RandLandau::restoreStaticRandomStates(is);
}

// ----------- Anonymous restore of engines -----------

template <class E>
void anonymousRestore1(int n, std::vector<double> & v) {
  output << "Anonymous restore for " << E::engineName() << "\n";
  E e(12349876);				    
  double r=0;					    
  for (int i=0; i<n; i++) r += e.flat();	    
  std::ofstream os("anonymous.save");		    
  os << e;					    
  for (int j=0; j<25; j++) v.push_back(e.flat());   
#ifdef VERBOSER2
  output << "First four of v are: " 
    	<< v[0] << ",  " << v[1] << ",  " << v[2] << ",  " << v[3] << "\n";
#endif
  return;
}

template <>
void anonymousRestore1<NonRandomEngine> (int n, std::vector<double> & v) {
#ifdef VERBOSER
  output << "Anonymous restore for " << NonRandomEngine::engineName() << "\n";
#endif
  std::vector<double> nonRand = aSequence(500);
  NonRandomEngine e; 
  e.setRandomSequence(&nonRand[0], nonRand.size());
  double r=0;
  for (int i=0; i<n; i++) r += e.flat();
  std::ofstream os("anonymous.save");
  os << e;
  for (int j=0; j<25; j++) v.push_back(e.flat()); 
#ifdef VERBOSER2
  output << "First four of v are: " 
    	<< v[0] << ",  " << v[1] << ",  " << v[2] << ",  " << v[3] << "\n";
#endif
  return;
}

template <class E>
int anonymousRestore2(const std::vector<double> & v) {
  int stat = 0;
  std::vector<double> k;
  std::ifstream is("anonymous.save");
  HepRandomEngine * a;
  a = HepRandomEngine::newEngine(is);
  for (int j=0; j<25; j++) k.push_back(a->flat()); 
  delete a;
#ifdef VERBOSER2
  output << "First four of k are: " 
    	<< k[0] << ",  " << k[1] << ",  " << k[2] << ",  " << k[3] << "\n";
#endif
  for (int m=0; m<25; m++) {
    if ( v[m] != k[m] ) {
      std::cout << "???? Incorrect restored value for anonymous engine" 
    		<< E::engineName() << "\n"; 
      stat |= 262144;
      return stat;
    }
  }
  return stat;       
}


template <class E>
int anonymousRestore(int n) {
  std::vector<double> v;
  anonymousRestore1<E>(n,v);
  return anonymousRestore2<E>(v);  
}

// ----------- Anonymous restore of all static distributions -----------

template <class E>
int anonymousRestoreStatics1() {
  int stat = 0;
  HepRandomEngine *e = new E(12456);
  HepRandom::setTheEngine(e);
  randomizeStatics(15);
  output << "\nRandomized, with theEngine = " << e->name() << "\n";
  saveStatics("distribution.save");
  output << "Saved all static distributions\n";
  std::vector<double> c = captureStatics();
  output << "Captured output of all static distributions\n";
  randomizeStatics(11);
  output << "Randomized all static distributions\n";
  restoreStatics("distribution.save");
  output << "Restored all static distributions to saved state\n";
  std::vector<double> d = captureStatics();
  output << "Captured output of all static distributions\n";
  for (unsigned int iv=0; iv<c.size(); iv++) {
    if (c[iv] != d[iv]) {
      std::cout << "???? restoreStaticRandomStates failed at random " 
                << iv <<"\n";
      stat |= 131072;
    }
  }
  if (stat & 131072 == 0) {
    output << "All captured output agrees with earlier values\n";
  }
  return stat;
}



template <class E1, class E2>
int anonymousRestoreStatics() {
  int stat = 0;
  if ( E1::engineName() == E2::engineName() ) {
    return anonymousRestoreStatics1<E1>();
  }
  HepRandomEngine *e1 = new E1(12456);
  HepRandom::setTheEngine(e1);
  randomizeStatics(15);
  output << "\nRandomized, with theEngine = " << e1->name() << "\n";
  saveStatics("distribution.save");
#ifdef VERBOSER2
  output << "Saved all static distributions\n";
#endif
  std::vector<double> c = captureStatics();
#ifdef VERBOSER2
  output << "Captured output of all static distributions\n";
#endif
  delete e1;
  HepRandomEngine *e2 = new E2(24653);
  HepRandom::setTheEngine(e2);
  output << "Switched to theEngine = " << e2->name() << "\n";
  randomizeStatics(19);
  { std::ofstream os("engine.save"); os << *e2; }
  double v1 = e2->flat();
  double v2 = e2->flat();
  { std::ifstream is("engine.save"); is >> *e2; }
#ifdef VERBOSER2
  output << "Saved the "  << e2->name() << " engine: \n"
         << "Next randoms to be " << v1 << " " << v2 << "\n"
	 << "Restored the " << e2->name() << " engine to that state\n";
#endif
  restoreStatics("distribution.save");
#ifdef VERBOSER2
  output << "Restored all static distributions to saved state\n"
         << "This changes the engine type back to " << E1::engineName() << "\n";
#endif
  std::vector<double> d = captureStatics();
#ifdef VERBOSER2
  output << "Captured output of all static distributions\n";
#endif
  for (unsigned int iv=0; iv<c.size(); iv++) {
    if (c[iv] != d[iv]) {
      std::cout << "???? restoreStaticRandomStates failed at random " 
                << iv <<"\n";
      stat |= 524288;
    }
  }
  if (stat & 524288 == 0) {
    output << "All captured output agrees with earlier values\n";
  }
  double k1 = e2->flat();
  double k2 = e2->flat();
#ifdef VERBOSER2
  output << "The "  << e2->name() << " engine should not have been affected: \n"
         << "Next randoms  are  " << k1 << " " << k2 << "\n";
#endif
  if ( !equals(v1,k1) || !equals(v2,k2) ) {
    std::cout << "???? Engine used as theEngine was affected by restoring \n"
              << "     static distributions to use engine of a different type.\n";    
    stat |= 1048576; 
  }
  return stat;  
}

// ----------- Vector restore of engines -----------

template <class E>
std::vector<unsigned long> vectorRestore1(int n, std::vector<double> & v) {
  output << "Vector restore for " << E::engineName() << "\n";
  E e(97538466);				    
  double r=0;					    
  for (int i=0; i<n; i++) r += e.flat();	    
  std::vector<unsigned long> state = e.put();	    
  for (int j=0; j<25; j++) v.push_back(e.flat());   
#ifdef VERBOSER2
  output << "First four of v are: " 
    	<< v[0] << ",  " << v[1] << ",  " << v[2] << ",  " << v[3] << "\n";
#endif
  return state;
}

template <>
std::vector<unsigned long>
vectorRestore1<NonRandomEngine> (int n, std::vector<double> & v) {
#ifdef VERBOSER2
  output << "Vector restore for " << NonRandomEngine::engineName() << "\n";
#endif
  std::vector<double> nonRand = aSequence(500);
  NonRandomEngine e; 
  e.setRandomSequence(&nonRand[0], nonRand.size());
  double r=0;
  for (int i=0; i<n; i++) r += e.flat();
  std::vector<unsigned long> state = e.put();	    
  for (int j=0; j<25; j++) v.push_back(e.flat()); 
#ifdef VERBOSER2
  output << "First four of v are: " 
    	<< v[0] << ",  " << v[1] << ",  " << v[2] << ",  " << v[3] << "\n";
#endif
  return state;
}

template <class E>
int vectorRestore2(const std::vector<unsigned long> state,
		   const std::vector<double> & v) {
  int stat = 0;
  std::vector<double> k;
  HepRandomEngine * a;
  a = HepRandomEngine::newEngine(state);
  if (!a) {
      std::cout << "???? could not restore engine state from vector for " 
    		<< E::engineName() << "\n"; 
      stat |= 1048576;
      return stat;
  }
  if (a->name() != E::engineName()) {
      std::cout << "???? restored engine state from vector for " 
    		<< E::engineName() << "to different type of engine: "
		<< a->name() << "\n"
	<< "There is probably a clash in CRC hashes for these two names!\n"; 
      stat |= 1048576;
      return stat;
  }
  for (int j=0; j<25; j++) k.push_back(a->flat());
  delete a;
#ifdef VERBOSER2
  output << "First four of k are: " 
    	<< k[0] << ",  " << k[1] << ",  " << k[2] << ",  " << k[3] << "\n";
#endif
  for (int m=0; m<25; m++) {
    if ( v[m] != k[m] ) {
      std::cout << "???? Incorrect vector restored value for anonymous engine: " 
    		<< E::engineName() << "\n"; 
      stat |= 1048576;
      return stat;
    }
  }
  return stat;       
}


template <class E>
int vectorRestore(int n) {
  std::vector<double> v;
  std::vector<unsigned long> state = vectorRestore1<E>(n,v);
  return vectorRestore2<E>(state, v);  
}



// ---------------------------------------------
// ---------------------------------------------
// ---------------------------------------------


int main() {
  int stat = 0;

#ifdef TEST_ORIGINAL_SAVE
  output << "=====================================\n";
  output << "             Part I \n";
  output << "Original tests of static save/restore\n";
  output << "=====================================\n\n";
  
  output << "Using old method or HepRandom::saveEngineStatus:\n";
  output << "All these tests should have a chance of failure.\n";

  output << RandGauss:: getTheEngine()->name();  
  output << RandGaussQ::getTheEngine()->name();  

  stat |= saveStepX();
  stat |= restoreStepX();
  stat |= BsaveStepX();
  stat |= BrestoreStepX();
  
  output << "Using the class-specific RandGauss::saveEngineStatus:\n";
  output << "All these tests should work properly.\n";

  stat |= saveStep();
  stat |= restoreStep();
  stat |= BsaveStep();
  stat |= BrestoreStep();
#endif
  
#ifdef TEST_MISSING_FILES
  output << "\n=======================================\n";
  output << "             Part Ia \n";
  output << "Test of behavior when a file is missing \n";
  output << "=======================================\n\n";

  output << "Testing restoreEngineStatus with missing file:\n";
  output << "Expect a number of <Failure to find or open> messages!\n";
  stat |= missingFile();
#endif

#ifdef CREATE_OLD_SAVES
  stat |= saveEngine<DRand48Engine, RandPoisson>("DRand48Engine.oldsav");
  stat |= saveEngine<DualRand,      RandPoisson>("DualRand.oldsav");
  stat |= saveEngine<Hurd160Engine, RandPoisson>("Hurd160Engine.oldsav");
  stat |= saveEngine<Hurd288Engine, RandPoisson>("Hurd288Engine.oldsav");
  stat |= saveEngine<HepJamesRandom,RandPoisson>("HepJamesRandom.oldsav");
  stat |= saveEngine<MTwistEngine,  RandPoisson>("MTwistEngine.oldsav");
  stat |= saveEngine<RanecuEngine,  RandPoisson>("RanecuEngine.oldsav");
  stat |= saveEngine<Ranlux64Engine,RandPoisson>("Ranlux64Engine.oldsav");
  stat |= saveEngine<RanluxEngine,  RandPoisson>("RanluxEngine.oldsav");
  stat |= saveEngine<RanshiEngine,  RandPoisson>("RanshiEngine.oldsav");
  stat |= saveEngine<TripleRand,    RandPoisson>("TripleRand.oldsav");
#endif

#ifdef VERIFY_OLD_SAVES
  output << "\n==============================================\n";
  output << "               Part Ib \n";
  output << "  Verification that changes wont invalidate \n";
  output << "invalidate engine saves from previous versions \n";
  output << "==============================================\n\n";

  stat |= checkSaveEngine<DRand48Engine, RandPoisson>("DRand48Engine.oldsav");
  stat |= checkSaveEngine<DualRand,      RandPoisson>("DualRand.oldsav");
  stat |= checkSaveEngine<Hurd160Engine, RandPoisson>("Hurd160Engine.oldsav");
  stat |= checkSaveEngine<Hurd288Engine, RandPoisson>("Hurd288Engine.oldsav");
  stat |= checkSaveEngine<HepJamesRandom,RandPoisson>("HepJamesRandom.oldsav");
  stat |= checkSaveEngine<MTwistEngine,  RandPoisson>("MTwistEngine.oldsav");
  stat |= checkSaveEngine<Ranlux64Engine,RandPoisson>("Ranlux64Engine.oldsav");
  stat |= checkSaveEngine<RanluxEngine,  RandPoisson>("RanluxEngine.oldsav");
  stat |= checkSaveEngine<RanshiEngine,  RandPoisson>("RanshiEngine.oldsav");
  stat |= checkSaveEngine<TripleRand,    RandPoisson>("TripleRand.oldsav");
  stat |= checkSaveEngine<RanecuEngine,  RandPoisson>("RanecuEngine.oldsav");
#endif

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

  {DualRand e(234);		stat |= checkEngineInstanceSave(e);}
  {Hurd160Engine e(234);	stat |= checkEngineInstanceSave(e);}
  {Hurd288Engine e(234);	stat |= checkEngineInstanceSave(e);}
  {HepJamesRandom e(234);	stat |= checkEngineInstanceSave(e);}
  {MTwistEngine e(234);		stat |= checkEngineInstanceSave(e);}
  {RandEngine e(234);		stat |= checkEngineInstanceSave(e);}
  {RanecuEngine e(234);		stat |= checkEngineInstanceSave(e);}
  {Ranlux64Engine e(234);	stat |= checkEngineInstanceSave(e);}
  {RanluxEngine e(234);		stat |= checkEngineInstanceSave(e);}
  {RanshiEngine e(234);		stat |= checkEngineInstanceSave(e);}
  {TripleRand e(234);		stat |= checkEngineInstanceSave(e);}
  
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

#ifdef TEST_SHARED_ENGINES
  output << "\n=============================================\n";
  output << "              Part IV \n";
  output << "Check behavior when engines are shared \n";
  output << "=============================================\n\n";
  
  stat |= checkSharing<DualRand>();
  stat |= checkSharing<Hurd160Engine>();
  stat |= checkSharing<Hurd288Engine>();
  stat |= checkSharing<HepJamesRandom>();
  stat |= checkSharing<MTwistEngine>();
  stat |= checkSharing<Ranlux64Engine>();
  stat |= checkSharing<RanluxEngine>();
  stat |= checkSharing<RanshiEngine>();
  stat |= checkSharing<TripleRand>();
#endif

#ifdef TEST_STATIC_SAVE
  output << "\n=========================================\n";
  output << "              Part V \n";
  output << "Static Save/restore to/from streams \n";
  output << "=========================================\n\n";
 
  stat |= staticSave <RandGauss>(7);
  stat |= staticSave <RandFlat>(7);
  stat |= staticSaveShootBit<RandFlat> (19);
  stat |= staticSaveShootBit<RandBit> (23);
  for (int ibinom=0; ibinom<15; ibinom++) {
    stat |= staticSave <RandBinomial>(7+3*ibinom);
  }
  stat |= staticSave <RandBreitWigner>(7);
  stat |= staticSave <RandChiSquare>(7);
  stat |= staticSave <RandExponential>(7);
  stat |= staticSave <RandGamma>(7);
  stat |= staticSave <RandGaussQ>(7);
  stat |= staticSave <RandGaussT>(7);
  stat |= staticSave <RandLandau>(7);
  stat |= staticSave <RandPoisson>(7);
  stat |= staticSave <RandPoissonQ>(7);
  stat |= staticSave <RandPoissonT>(7);
  stat |= staticSave <RandStudentT>(7);
#endif

#ifdef TEST_SAVE_STATIC_STATES
  output << "\n==============================================\n";
  output << "                 Part VI  \n";
  output << "Save/restore all static states to/from streams \n";
  output << "==============================================\n\n";
 
  randomizeStatics(15);
  saveStatics("distribution.save");
  output << "Saved all static distributions\n";
  std::vector<double> c = captureStatics();
  output << "Captured output of all static distributions\n";
  randomizeStatics(11);
  output << "Randomized all static distributions\n";
  restoreStatics("distribution.save");
  output << "Restored all static distributions to saved state\n";
  std::vector<double> d = captureStatics();
  output << "Captured output of all static distributions\n";
  for (unsigned int iv=0; iv<c.size(); iv++) {
    if (c[iv] != d[iv]) {
      std::cout << "???? restoreStaticRandomStates failed at random " 
                << iv <<"\n";
      stat |= 131072;
    }
  }
  if (stat & 131072 == 0) {
    output << "All captured output agrees with earlier values\n";
  }
#endif
  
#ifdef TEST_ANONYMOUS_ENGINE_RESTORE
  output << "\n=================================\n";
  output << "         Part VII \n";
  output << "Anonymous restore of engines \n";
  output << "=================================\n\n";

  stat |= anonymousRestore<DualRand>(13);
  stat |= anonymousRestore<DRand48Engine>(14);
  stat |= anonymousRestore<Hurd160Engine>(15);
  stat |= anonymousRestore<Hurd288Engine>(16);
  stat |= anonymousRestore<HepJamesRandom>(17);
  stat |= anonymousRestore<MTwistEngine>(18);
  stat |= anonymousRestore<RandEngine>(29);
  stat |= anonymousRestore<RanecuEngine>(39);
  stat |= anonymousRestore<Ranlux64Engine>(19);
  stat |= anonymousRestore<RanluxEngine>(20);
  stat |= anonymousRestore<RanshiEngine>(21);
  stat |= anonymousRestore<TripleRand>(22);
  stat |= anonymousRestore<NonRandomEngine>(22);
#endif

#ifdef TEST_ANONYMOUS_RESTORE_STATICS
  output << "\n======================================\n";
  output << "             Part VIII \n";
  output << "Anonymous restore static Distributions \n";
  output << "======================================\n\n";

  stat |= anonymousRestoreStatics<DualRand,       Ranlux64Engine> ( );
  stat |= anonymousRestoreStatics<DRand48Engine,  TripleRand>     ( );
  stat |= anonymousRestoreStatics<RandEngine,     Ranlux64Engine> ( );
  stat |= anonymousRestoreStatics<MTwistEngine,   Hurd288Engine>  ( );
  stat |= anonymousRestoreStatics<RanecuEngine,   MTwistEngine>   ( );
  stat |= anonymousRestoreStatics<HepJamesRandom, RanshiEngine>   ( );
  stat |= anonymousRestoreStatics<RanecuEngine,   RandEngine>     ( );
  stat |= anonymousRestoreStatics<RanshiEngine,   Hurd160Engine>  ( );
  stat |= anonymousRestoreStatics<TripleRand,     DualRand>       ( );
  stat |= anonymousRestoreStatics<Hurd160Engine,  HepJamesRandom> ( );
  stat |= anonymousRestoreStatics<Hurd288Engine,  RanecuEngine>   ( );
  stat |= anonymousRestoreStatics<HepJamesRandom, Ranlux64Engine> ( ); 
  stat |= anonymousRestoreStatics<TripleRand,     TripleRand>     ( );
  stat |= anonymousRestoreStatics<HepJamesRandom, HepJamesRandom> ( );
#endif

#ifdef TEST_VECTOR_ENGINE_RESTORE
  output << "\n=================================\n";
  output << "         Part IX \n";
  output << "Save/restore of engines to vectors\n";
  output << "=================================\n\n";

  stat |= vectorRestore<DualRand>(113);
  stat |= vectorRestore<DRand48Engine>(114);
  stat |= vectorRestore<Hurd160Engine>(115);
  stat |= vectorRestore<Hurd288Engine>(116);
  stat |= vectorRestore<HepJamesRandom>(117);
  stat |= vectorRestore<MTwistEngine>(118);
  stat |= vectorRestore<RanecuEngine>(139);
  stat |= vectorRestore<Ranlux64Engine>(119);
  stat |= vectorRestore<RanluxEngine>(120);
  stat |= vectorRestore<RanshiEngine>(121);
  stat |= vectorRestore<TripleRand>(122);
  stat |= vectorRestore<NonRandomEngine>(123);
  stat |= vectorRestore<RandEngine>(129);
#endif



 
  output << "\n=============================================\n\n";

  if (stat != 0) {
     std::cout << "One or more problems detected: stat = " << stat << "\n";
  }  else {
     output << "ranRestoreTest passed with no problems detected.\n";    
  }

  return stat;
}	

