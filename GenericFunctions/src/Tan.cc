// -*- C++ -*-
// $Id: Tan.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ---------------------------------------------------------------------------
#include "GenericFunctions/defs.h"
 
#include "CLHEP/GenericFunctions/Tan.hh"
#include "CLHEP/GenericFunctions/Cos.hh"
#include <iostream>
#include <assert.h>
#include <cmath>	// for tan()

namespace Genfun {
FUNCTION_OBJECT_IMP(Tan)

Tan::Tan()
{}

Tan::~Tan() {
}

Tan::Tan(const Tan & right) 
{  }


double Tan::operator() (double x) const {
  return tan(x);
}



Derivative Tan::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime = 1.0/Cos()/Cos();
  return Derivative(& fPrime);
}

} // namespace Genfun
