#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/defs.h"
#include <iostream>

#include "CLHEP/Random/RandGaussQ.h"
#include "CLHEP/Random/RandGaussT.h"
#include "CLHEP/Random/RandPoissonQ.h"
#include "CLHEP/Random/RandPoissonT.h"
#include "CLHEP/Random/RandBit.h"
#include "CLHEP/Units/PhysicalConstants.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using namespace CLHEP;
//#ifndef _WIN32
//using std::exp;
//#endif


// ---------
// RandGauss
//
// mf 12/13/04	Correction in way engines are supplied to RandBit() ctor
//   		(gcc3.3.1 exposed previously innocuous mistake)
// ---------

double gammln1(double xx) {

// Returns the value ln(Gamma(xx) for xx > 0.  Full accuracy is obtained for 
// xx > 1. For 0 < xx < 1. the reflection formula (6.1.4) can be used first.
// (Adapted from Numerical Recipes in C)

  static double cof[6] = {76.18009172947146,-86.50532032941677,
                             24.01409824083091, -1.231739572450155,
                             0.1208650973866179e-2, -0.5395239384953e-5};
  int j;
  double x = xx - 1.0;
  double tmp = x + 5.5;
  tmp -= (x + 0.5) * log(tmp);
  double ser = 1.000000000190015;

  for ( j = 0; j <= 5; j++ ) {
    x += 1.0;
    ser += cof[j]/x;
  }
  return -tmp + log(2.5066282746310005*ser);
}

double gammln2(double xx) {

// Returns the value ln(Gamma(xx) for xx > 0.  Full accuracy is obtained for 
// xx > 1. For 0 < xx < 1. the reflection formula (6.1.4) can be used first.
// (Adapted from Numerical Recipes in C)

  static double cof[6] = {76.18009172947146,-86.50532032941677,
                             24.01409824083091, -1.231739572450155,
                             0.1208650973866179e-2, -0.5395239384953e-5};
  int j;
  double x = xx - 0.0;
  double tmp = x + 5.5;
  tmp -= (x + 0.5) * log(tmp);
  double ser = 1.000000000190015;

  for ( j = 0; j <= 5; j++ ) {
    x += 1.0;
    ser += cof[j]/x;
  }
  return -tmp + log(2.5066282746310005*ser/xx);
}
#include <iomanip>



int main() {

  cout << "Enter 1 for RandGauss, 2 for RandGaussQ, 3 for DualRand flat: ";
  int choice;
  cin >> choice;

if (choice==1) {
  cout << "\n--------------------------------------------\n";
  cout << "Test of Gauss distribution speed\n\n";

  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed;

  int nNumbers;
  cout << "How many numbers should we generate: ";
  cin >> nNumbers;

  cout << "\nInstantiating distribution utilizing DualRand engine...\n";
  DualRand eng (seed);
  RandGauss dist (eng);

  double sum = 0;


  for (int i=0; i < nNumbers; i++) {
    sum += dist.fire();
  }

  cout << "\n Finished:  sum is " << sum << " \n";
}

if (choice==2) {
  cout << "\n--------------------------------------------\n";
  cout << "Test of RandGaussQ distribution speed\n\n";

  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed;

  int nNumbers;
  cout << "How many numbers should we generate: ";
  cin >> nNumbers;

  cout << "\nInstantiating distribution utilizing DualRand engine...\n";
  DualRand eng (seed);
  RandGaussQ dist (eng);

  double sum = 0;


  for (int i=0; i < nNumbers; i++) {
    sum += dist.fire();
  }

  cout << "\n Finished:  sum is " << sum << " \n";
}

if (choice==3) {
  cout << "\n--------------------------------------------\n";
  cout << "Test of DualRand flat speed\n\n";

  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed;

  int nNumbers;
  cout << "How many numbers should we generate: ";
  cin >> nNumbers;

  cout << "\nInstantiating distribution utilizing DualRand engine...\n";
  DualRand eng (seed);

  double sum = 0;


  for (int i=0; i < nNumbers; i++) {
    sum += eng.flat();
  }

  cout << "\n Finished:  sum is " << sum << " \n";
}


#ifdef GAMMA
  cout << "\nNow we will compute the first 20 gammas, using gammln:\n";

  double x;
  for (x=1; x <= 20; x+=1) {
    cout << x << std::setprecision(20) << "    " << exp(gammln1(x)) 
	<< "    " << exp(gammln2(x)) << " difference in gammln2 = " << 
	gammln1(x)-gammln2(x) << "\n";
  }


  cout << "\nNow we will compute gamma of small numbers: \n";

  for ( x=1; x > .000000001; x *= .9 ) {
    cout << x << std::setprecision(20) << "    " <<
    1 - exp(gammln1(x)) * exp(gammln1(2-x)) * sin(CLHEP::pi*(1-x)) / (CLHEP::pi*(1-x)) <<
    "    " <<
    1 - exp(gammln2(x)) * exp(gammln1(2-x)) * sin(CLHEP::pi*(1-x)) / (CLHEP::pi*(1-x)) <<
    "\n";
  }
#endif // GAMMA

#ifdef POISSON
  cout << "\n--------------------------------------------\n";
  cout << "Test of Poisson distribution speed\n\n";

  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed;

  double mu;
  cout << "Please enter mu:        ";
  cin >> mu;

  int nNumbers;
  cout << "How many numbers should we generate: ";
  cin >> nNumbers;

  cout << "\nInstantiating distribution utilizing DualRand engine...\n";
  DualRand eng (seed);
  RandPoisson dist (eng, mu);
  // RandFlat dist (eng);
 
  double sum = 0;


  for (int i=0; i < nNumbers; i++) {
    sum += dist.fire();	
//    sum += dist.quick();
//    sum += dist.fire(mu);
//    sum += dist.quick(mu);

  }

  cout << "\n Finished:  sum is " << sum << " \n";
#endif // POISSON


#define MISC
#ifdef MISC

  DualRand e;

  // RandGauss usage modes

  cout << "testing RandGaussT::shoot():  "  << RandGaussT::shoot()  << "\n";
  cout << "testing RandGaussT::shoot(&e): "  << RandGaussT::shoot(&e) << "\n";
  cout << "testing RandGaussT::shoot(100,10): " << 
			RandGaussT::shoot(100,10) << "\n";
  cout << "testing RandGaussT::shoot(&e,100,10): " << 
			RandGaussT::shoot(&e,100,10) << "\n";
  RandGaussT gt (e, 50,2);
  cout << "testing gt.fire(): " << gt.fire() << "\n";
  cout << "testing gt.fire(200,2): " << gt.fire(200,2) << "\n";

  cout << "testing RandGaussQ::shoot():  "  << RandGaussQ::shoot()  << "\n";
  cout << "testing RandGaussQ::shoot(&e): "  << RandGaussQ::shoot(&e) << "\n";
  cout << "testing RandGaussQ::shoot(100,10): " << 
			RandGaussQ::shoot(100,10) << "\n";
  cout << "testing RandGaussQ::shoot(&e,100,10): " << 
			RandGaussQ::shoot(&e,100,10) << "\n";
  RandGaussQ qt (e, 50,2);
  cout << "testing qt.fire(): " << qt.fire() << "\n";
  cout << "testing qt.fire(200,2): " << qt.fire(200,2) << "\n";

  // RandPoisson usage modes

  cout << "testing RandPoissonT::shoot():  "  << RandPoissonT::shoot()  << "\n";
  cout << "testing RandPoissonT::shoot(&e): "  
  					<< RandPoissonT::shoot(&e) << "\n";
  cout << "testing RandPoissonT::shoot(90): " << 
			RandPoissonT::shoot(90) << "\n";
  cout << "testing RandPoissonT::shoot(&e,90): " << 
			RandPoissonT::shoot(&e,90) << "\n";
  RandPoissonT pgt (e,50);
  cout << "testing pgt.fire(): " << pgt.fire() << "\n";
  cout << "testing pgt.fire(20): " << pgt.fire(20) << "\n";

  cout << "testing RandPoissonQ::shoot():  "  << RandPoissonQ::shoot()  << "\n";
  cout << "testing RandPoissonQ::shoot(&e): " << RandPoissonQ::shoot(&e) << "\n";
  cout << "testing RandPoissonQ::shoot(90): " << 
			RandPoissonQ::shoot(90) << "\n";
  cout << "testing RandPoissonQ::shoot(&e,90): " << 
			RandPoissonQ::shoot(&e,90) << "\n";
  RandPoissonQ pqt (e,50);
  cout << "testing pqt.fire(): " << pqt.fire() << "\n";
  cout << "testing pqt.fire(20): " << pqt.fire(20) << "\n";

  // RandBit modes coming from RandFlat and bit modes

  cout << "testing RandBit::shoot():  " << RandBit::shoot()  << "\n";
  cout << "testing RandBit::shoot(&e): " << RandBit::shoot(&e) << "\n";
  cout << "testing RandBit::shoot(10,20): "  << RandBit::shoot(10,20)   << "\n";
  cout << "testing RandBit::shoot(&e,10,20): "<< 
  					RandBit::shoot(&e,10,20) << "\n";
  RandBit b ( e, 1000, 1100 );
  cout << "testing b.fire(): " << b.fire() << "\n";
  cout << "testing b.fire(10,20): " << b.fire(10,20) << "\n";
  int i;
  cout << "testing RandBit::shootBit():  "; 
  for (i=0; i<40; i++) {
    cout << RandBit::shootBit();
  } cout << "\n";
  cout << "testing RandBit::shootBit(&e):  "; 
  for (i=0; i<40; i++) {
    cout << RandBit::shootBit(&e);
  } cout << "\n";
  cout << "testing RandBit::fireBit():  ";
  for (i=0; i<40; i++) {
    cout << b.fireBit();
  } cout << "\n";

  // Timing for RandBit:

  cout << "Timing RandFlat::shootBit():  Enter N: ";
  int N;
  cin >> N;
  int sum=0;
  for (i=0; i<N; i++) {
    sum+= RandFlat::shootBit();
  }
  cout << "--------- Done.............. Sum = " << sum <<  "\n";
  cout << "Timing RandBit::shootBit():  Enter N: ";
  cin >>  N;
  sum = 0;
  for (i=0; i<N; i++) {
    sum += RandBit::shootBit();
  }
  cout << "--------- Done.............. Sum = " << sum <<  "\n";

#endif // MISC

  return 0;
}

