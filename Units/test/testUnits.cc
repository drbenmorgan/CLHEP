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
#include <cmath>

int main() {

  int nbad=0;

  // Check that local m does not interfere with global m

  double m=0;
  for (int i=0; i<7; i++, m++) { assert(m == double(i)); } 
  assert(m != CLHEP::meter);  

  //std::cout << "Speed of light is " << std::setw(10) << std::setprecision(8)
  //	    << CLHEP::c_light << std::endl;
  //output: Speed of light is  299.79246

  std::ostringstream os1, os2, os3, os4;
  os1 << std::setprecision(8) << CLHEP::c_light;
  os2 << "299.79246";
  if( os1.str() != os2.str() ) {
    std::cout << "compare --" << os1.str() << "-- to --" << os2.str() << "--" << std::endl;
    nbad++;
  }
  os3 << std::setprecision(16) << CLHEP::pi ;
  os4 << "3.141592653589793";
  if( os3.str() != os4.str() ) {
    nbad++;
    std::cout << "compare --" << os3.str() << "--" << std::endl;
    std::cout << "     to --" << os4.str() << "--" << std::endl;
#ifndef USING_VISUAL
    std::cout << "M_PI    --" << std::setprecision(16) << M_PI << "--" << std::endl;
#endif
  }
  
  return nbad;
  
}
