// -*- C++ -*-
// $Id: Sqrt.cc,v 1.6 2004/04/29 02:47:30 garren Exp $
#include "CLHEP/GenericFunctions/Sqrt.hh"
#include <assert.h>
#include <cmath>	// for sqrt
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
