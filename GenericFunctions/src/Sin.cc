// -*- C++ -*-
// $Id: Sin.cc,v 1.2 2003/07/16 12:35:41 garren Exp $
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/Sin.hh"
#include "CLHEP/GenericFunctions/Cos.hh"
#include <iostream>
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
