// ----------------------------------------------------------------------
#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "CLHEP/Random/defs.h"
#include <iostream>
#include <iomanip>
#include <vector>

#define CLEAN_OUTPUT
#ifdef CLEAN_OUTPUT
  std::ofstream output("testAnonymousEngineRestore.cout");  
#else
  std::ostream & output = std::cout;
#endif

// Normally on  for routine validation:

#ifdef TURNOFF
#endif

#define TEST_ANONYMOUS_ENGINE_RESTORE
#define TEST_ANONYMOUS_RESTORE_STATICS

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
      #ifdef CLEAN_OUTPUT
      output << "???? Incorrect restored value for anonymous engine" 
    		<< E::engineName() << "\n"; 
      #endif
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
      #ifdef CLEAN_OUTPUT
      output << "???? restoreStaticRandomStates failed at random " 
                << iv <<"\n";
      #endif
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
      #ifdef CLEAN_OUTPUT
      output << "???? restoreStaticRandomStates failed at random " 
                << iv <<"\n";
      #endif
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
    #ifdef CLEAN_OUTPUT
    output << "???? Engine used as theEngine was affected by restoring \n"
              << "     static distributions to use engine of a different type.\n";    
    #endif
    stat |= 1048576; 
  }
  return stat;  
}

// ---------------------------------------------
// ---------------------------------------------
// ---------------------------------------------


int main() {
  int stat = 0;

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


  output << "\n=============================================\n\n";

  if (stat != 0) {
     std::cout << "One or more problems detected: stat = " << stat << "\n";
     output << "One or more problems detected: stat = " << stat << "\n";
  }  else {
     output << "testAnonymousEngineRestore passed with no problems detected.\n";    
  }

  if (stat == 0) return 0;
  if (stat > 0) return -(stat|1);
  return stat|1;
}	

