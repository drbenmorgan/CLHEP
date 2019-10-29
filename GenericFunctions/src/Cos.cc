// -*- C++ -*-
// $Id: Cos.cc,v 1.5 2003/10/10 17:40:39 garren Exp $
#include "CLHEP/GenericFunctions/Cos.hh"
#include "CLHEP/GenericFunctions/Sin.hh"
#include <cmath>

namespace Genfun {
FUNCTION_OBJECT_IMP(Cos)

Cos::Cos()
{}

Cos::~Cos() {
}

Cos::Cos(const Cos & right) : AbsFunction(right)
{  }


double Cos::operator() (double x) const {
  return cos(x);
}


Derivative Cos::partial(unsigned int) const {
  const AbsFunction & fPrime = -Sin();
  return Derivative(& fPrime);
}


} // namespace Genfun
