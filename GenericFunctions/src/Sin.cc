// -*- C++ -*-
// $Id: Sin.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/Sin.hh"
#include "CLHEP/GenericFunctions/Cos.hh"
#include <iostream>
#include <assert.h>

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
