// -*- C++ -*-
// $Id: testUnits.cc,v 1.4 2011/07/20 23:00:04 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a small program for testing the Units module
//

#include <assert.h>
#include "CLHEP/Units/defs.h"
#include "CLHEP/Units/PhysicalConstants.h"
#include <iostream>
#include <iomanip>
#include <sstream>

int main() {

  // Check that local m does not interfere with global m

  double m=0;
  for (int i=0; i<7; i++, m++) { assert(m == double(i)); } 
  assert(m != CLHEP::meter);  

  //std::cout << "Speed of light is " << std::setw(10) << std::setprecision(8)
  //	    << CLHEP::c_light << std::endl;
  //output: Speed of light is  299.79246

  std::ostringstream os1, os2;
  os1 << std::setprecision(8) << CLHEP::c_light;
  os2 << "299.79246";
  if( os1.str() == os2.str() ) {
    return 0;
  } else {
    std::cout << "compare --" << os1.str() << "-- to --" << os2.str() << "--" << std::endl;
    return 1;
  }
}
