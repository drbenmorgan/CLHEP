#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "Random/defs.h"
#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
//#ifndef _WIN32
//using std::exp;
//#endif


// ---------
// RandGauss
// ---------

int main() {

  cout << "\n--------------------------------------------\n";
  cout << "Test of Gauss distribution at small r \n\n";

  cout << "\nInstantiating distribution utilizing NonRandomEngine...\n";
  NonRandomEngine eng;
  RandGauss dist (eng);

  double r;
  while (true) {
    cout << "r -- ";
    cin  >> r;
    eng.setNextRandom(r);
    double x = dist.fire();
    cout << "                " << std::setprecision(16) << x << "\n";
    if ( x > 1.0e15 ) break;
  }
  return 0;
}
