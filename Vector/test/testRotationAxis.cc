#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/Rotation.h"
#include <assert.h>
#include <cmath>
#include <iostream>

bool equal(double a, double b) {
  const double eps = 1e-9;
  return (std::abs(a - b) < eps);
}

bool equal(const CLHEP::Hep3Vector& a, const CLHEP::Hep3Vector& b) {
  const double eps = 1e-10;
  return (std::abs(a.x() - b.x()) < eps &&
          std::abs(a.y() - b.y()) < eps &&
          std::abs(a.z() - b.z()) < eps);
}

using namespace CLHEP;

int main()
{
  std::cout << "\n=== Check rotation around specified axes" << std::endl; 

  HepRotation rot;
  Hep3Vector axis;

  std::cout << "Zero rotation - OK" << std::endl;
  axis.set(0,0,1); 
  rot.set(HepRep3x3( 1, 0, 0,
                     0, 1, 0,
                     0, 0, 1 ));
  assert(equal(rot.delta(),0));
  assert(equal(rot.axis(),axis));

  std::cout << "Rotation by 180 degrees around X  - OK" << std::endl;
  axis.set(1,0,0); 
  rot.set(HepRep3x3( 1, 0, 0,
                     0,-1, 0,
                     0, 0,-1 ));
  assert(equal(rot.delta(),pi));
  assert(equal(rot.axis(),axis) || equal(rot.axis(),-axis));

  std::cout << "Rotation by 180 degrees around Y  - OK" << std::endl;
  axis.set(0,1,0); 
  rot.set(HepRep3x3(-1, 0, 0,
                     0, 1, 0,
		     0, 0,-1 ));
  assert(equal(rot.delta(),pi));
  assert(equal(rot.axis(),axis) || equal(rot.axis(),-axis));

  std::cout << "Rotation by 180 degrees around Z  - OK" << std::endl;
  axis.set(0,0,1); 
  rot.set(HepRep3x3(-1, 0, 0,
                     0,-1, 0,
		     0, 0, 1 ));
  assert(equal(rot.delta(),pi));
  assert(equal(rot.axis(),axis) || equal(rot.axis(),-axis));

  std::cout << "Rotation by 180 degrees around XY - OK" << std::endl;
  axis = Hep3Vector(1,1,0).unit(); 
  rot.set(HepRep3x3( 0, 1, 0,
                     1, 0, 0,
		     0, 0,-1 ));
  assert(equal(rot.delta(),pi));
  assert(equal(rot.axis(),axis) || equal(rot.axis(),-axis));

  std::cout << "Rotation by 180 degrees around YZ - OK" << std::endl;
  axis = Hep3Vector(0,1,1).unit(); 
  rot.set(HepRep3x3(-1, 0, 0,
                     0, 0, 1,
		     0, 1, 0 ));
  assert(equal(rot.delta(),pi));
  assert(equal(rot.axis(),axis) || equal(rot.axis(),-axis));

  std::cout << "Rotation by 180 degrees around ZX - OK" << std::endl;
  axis = Hep3Vector(1,0,1).unit(); 
  rot.set(HepRep3x3( 0, 0, 1,
                     0,-1, 0,
		     1, 0, 0 ));
  assert(equal(rot.delta(),pi));
  assert(equal(rot.axis(),axis) || equal(rot.axis(),-axis));

  //-------------------------------------------------------
  //
  CLHEP::HepRotation matrix;
  CLHEP::Hep3Vector vinput, voutput;

  int step = 1;
  std::cout << "\n=== Check all possible axes and angles (step = " << step << " degree)" << std::endl; 

  for (    int the =  0; the <= 180; the += step) {
    for (  int phi =  0; phi <  360; phi += step) {
      for (int a   =  0; a   <  360; a   += step) {
        double z = std::cos(the*deg);
        double y = std::sin(the*deg)*sin(phi*deg);
        double x = std::sin(the*deg)*cos(phi*deg);
        double ang = a*deg;

        // Set rotation matrix
        vinput.set(x, y, z);
        matrix.set(vinput, ang);

        // Get axis/angle
        voutput = matrix.axis();
	double del = matrix.delta();
        if (a > 180) {
          del = CLHEP::twopi - del; 
          voutput = -voutput;
	}

        // Check angle
        if (a != 180) assert( equal(ang,del) ); // at 180, precision can be less than eps  

        // Check axis
        if (a == 0) continue; // no check, any axis is good
        if (a == 180 ) {
	  assert( equal(vinput,voutput) || equal(-vinput,voutput));
        } else {
	  assert( equal(vinput,voutput) );
	}
      }
    }
  }
  std::cout << "OK" << std::endl;

  //-------------------------------------------------------
  //
  int istep = 10000;
  std::cout << "\n=== Check angles near 0 (step = 1/" << istep << " degree)" << std::endl; 

  for (    int the =      0; the <=   180; the += 5) {
    for (  int phi =      0; phi <    360; phi += 5) {
      for (int a   = -istep; a   <= istep; a   += 1) {
        double z = std::cos(the*deg);
        double y = std::sin(the*deg)*sin(phi*deg);
        double x = std::sin(the*deg)*cos(phi*deg);
        double ang = 0. + a * (deg/istep);

        // Set rotation matrix
        vinput.set(x, y, z);
        matrix.set(vinput, ang);

        // Get axis/angle
        voutput = matrix.axis();
	double del = matrix.delta();
        if (a < 0) {
          del = -del; 
          voutput = -voutput;
	}

        // Check angle
        assert( equal(ang,del) );

        // Check axis
        if (a == 0) continue; // no check, any axis is good
	assert( equal(vinput,voutput) );
      }
    }
  }
  std::cout << "OK" << std::endl;

  //-------------------------------------------------------
  //
  istep = 10000;
  std::cout << "\n=== Check angles near 180 (step = 1/" << istep << " degree)" << std::endl; 

  for (    int the =      0; the <=   180; the += 5) {
    for (  int phi =      0; phi <    360; phi += 5) {
      for (int a   = -istep; a   <= istep; a   += 1) {
        double z = std::cos(the*deg);
        double y = std::sin(the*deg)*sin(phi*deg);
        double x = std::sin(the*deg)*cos(phi*deg);
        double ang = pi + a * (deg/istep);

        // Set rotation matrix
        vinput.set(x, y, z);
        matrix.set(vinput, ang);

        // Get axis/angle
        voutput = matrix.axis();
	double del = matrix.delta();
        if (a > 0) {
          del = CLHEP::twopi - del; 
          voutput = -voutput;
	}

        // Check angle
        if (a != 0) assert( equal(ang,del) ); // at 180, precision can be less than eps  

        // Check axis
        if (a == 0 ) {
	  assert( equal(vinput,voutput) || equal(-vinput,voutput));
        } else {
	  assert( equal(vinput,voutput) );
	}
      }
    }
  }
  std::cout << "OK" << std::endl;

  std::cout << std::endl;
  return 0 ;
}
