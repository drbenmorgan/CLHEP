// -*- C++ -*-
// $Id: Sin.cc,v 1.5 2003/10/10 17:40:39 garren Exp $
#include "CLHEP/GenericFunctions/Sin.hh"
#include "CLHEP/GenericFunctions/Cos.hh"
#include <assert.h>
#include <cmath>

namespace Genfun {
FUNCTION_OBJECT_IMP(Sin)

Sin::Sin()
{}

Sin::~Sin() {
}

Sin::Sin(const Sin & right) 
{  }


double Sin::operator() (double x) const {
  return sin(x);
}



Derivative Sin::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime = Cos();
  return Derivative(& fPrime);
}

} // namespace Genfun
