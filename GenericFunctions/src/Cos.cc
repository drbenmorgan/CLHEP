// -*- C++ -*-
// $Id: Cos.cc,v 1.3 2003/08/13 20:00:10 garren Exp $
#include "CLHEP/GenericFunctions/defs.h"
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
