
#include <iostream>

#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Vector/ThreeVector.h"

typedef HepGeom::Point3D<double> HepPoint3D;

int main(int, char **) {

  CLHEP::Hep3Vector d(10,0,0);
  HepPoint3D a(0,0,0);
  HepPoint3D pv(1,1,1);

  CLHEP::Hep3Vector dist = a-pv; // this does not compile anymore 
  CLHEP::Hep3Vector Cross = dist.cross(d.unit()); 
  std::cout << Cross.mag() << std::endl;

}
