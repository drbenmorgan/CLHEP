// test for bug https://savannah.cern.ch/bugs/?104262
// problem reported when using g++ -D_GLIBCXX_DEBUG flag

#include "CLHEP/Matrix/Vector.h"

int main(int, char **) {

CLHEP::HepVector fXVector;
fXVector = CLHEP::HepVector(32);
std::cout << "fXVector, 1, 2 : " << fXVector(1) << ", " << fXVector(2) << std::endl;

fXVector(1)=99;
fXVector(31)=199;

std::cout << "fXVector, 1, 31 : " << fXVector(1) << ", " << fXVector(31) << std::endl;

return 0;
} 

