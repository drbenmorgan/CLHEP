// -*- C++ -*-
// $Id: Tan.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
// ---------------------------------------------------------------------------
 
#include "CLHEP/GenericFunctions/Tan.hh"
#include "CLHEP/GenericFunctions/Cos.hh"
#include <assert.h>
#include <cmath>

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
