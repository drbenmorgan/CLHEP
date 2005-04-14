// ----------------------------------------------------------------------
#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "CLHEP/Random/defs.h"
#include <iostream>
#include <iomanip>
#include <vector>

#define CLEAN_OUTPUT
#ifdef CLEAN_OUTPUT
  std::ofstream output("testSaveSharedEngines.cout");  
#else
  std::ostream & output = std::cout;
#endif

// Normally on  for routine validation:

#ifdef TURNOFF
#endif

#define TEST_SHARED_ENGINES

// Normally off for routine validation:

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
    #ifdef CLEAN_OUTPUT
    output << "???? Incorrect restored value for distributions " 
    			<< d1.name() << " " << d2.name() << "\n"; 
    #endif
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


// ---------------------------------------------
// ---------------------------------------------
// ---------------------------------------------


int main() {
  int stat = 0;

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

 output << "\n=============================================\n\n";

  if (stat != 0) {
     std::cout << "One or more problems detected: stat = " << stat << "\n";
     output << "One or more problems detected: stat = " << stat << "\n";
  }  else {
     output << "testSaveSharedEngines passed with no problems detected.\n";    
  }

  if (stat == 0) return 0;
  if (stat > 0) return -(stat|1);
  return stat|1;
  return stat > 0 ? -stat : stat;
}	

