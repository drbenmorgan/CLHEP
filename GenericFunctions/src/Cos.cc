// -*- C++ -*-
// $Id: Cos.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/Cos.hh"
#include "CLHEP/GenericFunctions/Sin.hh"
#include <iostream>

namespace Genfun {
FUNCTION_OBJECT_IMP(Cos)

Cos::Cos()
{}

Cos::~Cos() {
}

Cos::Cos(const Cos & right) 
{  }


double Cos::operator() (double x) const {
  return cos(x);
}


Derivative Cos::partial(unsigned int index) const {
  const AbsFunction & fPrime = -Sin();
  return Derivative(& fPrime);
}


} // namespace Genfun
