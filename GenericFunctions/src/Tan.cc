// -*- C++ -*-
// $Id: Tan.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
// ---------------------------------------------------------------------------
 
#include "CLHEP/GenericFunctions/Tan.hh"
#include "CLHEP/GenericFunctions/Cos.hh"
#include <assert.h>

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
