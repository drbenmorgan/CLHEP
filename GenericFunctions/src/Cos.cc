// -*- C++ -*-
// $Id: Cos.cc,v 1.2 2003/07/16 12:35:41 garren Exp $
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/Cos.hh"
#include "CLHEP/GenericFunctions/Sin.hh"
#include <iostream>
#include <cmath>

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
