// -*- C++ -*-
// $Id: Sqrt.cc,v 1.2 2003/07/16 12:35:41 garren Exp $
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/Sqrt.hh"
#include <assert.h>
#include <cmath>

namespace Genfun {
FUNCTION_OBJECT_IMP(Sqrt)

Sqrt::Sqrt()
{}

Sqrt::Sqrt(const Sqrt & right)
{
}

Sqrt::~Sqrt() {
}

double Sqrt::operator() (double x) const {
  return sqrt(x);
}


Derivative Sqrt::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime = (0.5)/Sqrt();
  return Derivative(&fPrime);
}


} // namespace Genfun
