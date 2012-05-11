
#include <iostream>
#include <cmath>
#include <float.h>

#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Vector/ThreeVector.h"

typedef HepGeom::Point3D<double> HepPoint3D;

int main(int, char **) {

  CLHEP::Hep3Vector d(10,0,0);
  HepPoint3D a(0,0,0);
  HepPoint3D pv(1,1,1);
  
  float expected = 1.41421;
  int numbad = 0;

  CLHEP::Hep3Vector dist = a-pv; // this does not compile anymore 
  CLHEP::Hep3Vector Cross = dist.cross(d.unit()); 
  std::cout << Cross.mag() << std::endl;
  
  float result = Cross.mag();
  float eps = 1.0e-5;
  if( std::fabs(result - expected) >  eps ) {
    ++numbad;
    std::cout << "Expected " << expected << " got " << result << std::endl;
  }
  return numbad;

}
