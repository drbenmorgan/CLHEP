// -*- C++ -*-
// $Id: testUnits.cc,v 1.1 2003/07/22 16:38:04 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a small program for testing the Units module
//

#include <assert.h>
#include "Units/defs.h"
#include "CLHEP/Units/PhysicalConstants.h"
#include <iostream>
#include <iomanip>

int main() {

  // Check that local m does not interfere with global m

  double m=0;
  for (int i=0; i<7; i++, m++) { assert(m == double(i)); } 
  assert(m != meter);  

  std::cout << "Speed of light is " << std::setw(10) << std::setprecision(8)
	    << c_light << std::endl;
  return 0;
}
