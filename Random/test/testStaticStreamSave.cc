// ----------------------------------------------------------------------
#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "CLHEP/Random/defs.h"
#include <iostream>
#include <iomanip>
#include <vector>

#define CLEAN_OUTPUT
#ifdef CLEAN_OUTPUT
  std::ofstream output("testStaticStreamSave.cout");  
#else
  std::ostream & output = std::cout;
#endif

// Normally on  for routine validation:

#ifdef TURNOFF
#endif

#define TEST_STATIC_SAVE
#define TEST_SAVE_STATIC_STATES


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
    #ifdef CLEAN_OUTPUT
    output << "???? restoreFullState failed for " << D::distributionName() << "\n";
    #endif
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
    #ifdef CLEAN_OUTPUT
    output << "???? restoreDistState failed for " << D::distributionName() << "\n";
    #endif
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
    #ifdef CLEAN_OUTPUT
    output << "???? restoreFullState failed for D shootBit()\n";
    #endif
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
    #ifdef CLEAN_OUTPUT
    output << "???? restoreDistState failed for RnadFlat::shootBit()\n";
    #endif
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

// ---------------------------------------------
// ---------------------------------------------
// ---------------------------------------------


int main() {
  int stat = 0;

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
#endif
  
  output << "\n=============================================\n\n";

  if (stat != 0) {
     std::cout << "One or more problems detected: stat = " << stat << "\n";
     output << "One or more problems detected: stat = " << stat << "\n";
  }  else {
     output << "testStaticStreamSave passed with no problems detected.\n";    
  }

  if (stat == 0) return 0;
  if (stat > 0) return -(stat|1);
  return stat|1;
}	

