// -*- C++ -*-
// $Id: ATan.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $ 
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/ATan.hh"
#include "CLHEP/GenericFunctions/Square.hh"

#include <iostream>
#include <assert.h>
#include <cmath>	// for atan()

namespace Genfun {
FUNCTION_OBJECT_IMP(ATan)

ATan::ATan()
{}

ATan::~ATan() {
}

ATan::ATan(const ATan & right) 
{  }


double ATan::operator() (double x) const {
  return atan(x);
}



Derivative ATan::partial(unsigned int index) const {
  assert(index==0);

  Square square;
  
  const AbsFunction & fPrime=1.0/(1.0+square);;
  return Derivative(& fPrime);
}

} // end namespace Genfun 
