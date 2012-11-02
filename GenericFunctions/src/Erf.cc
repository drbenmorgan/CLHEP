// -*- C++ -*-
// $Id: Erf.cc,v 1.6 2010/06/16 18:22:01 garren Exp $

#include <cmath>

#include "CLHEP/GenericFunctions/Erf.hh"
#include "CLHEP/GenericFunctions/Gaussian.hh"
#include <assert.h>
namespace Genfun {
FUNCTION_OBJECT_IMP(Erf)

Erf::Erf()
{
  _incompleteGamma.a().setValue(0.5);
}

Erf::Erf(const Erf & right):
  AbsFunction(right), _incompleteGamma(right._incompleteGamma)
{
}

Erf::~Erf() {
}

double Erf::operator() (double x) const {
  return x<0 ? -_incompleteGamma(x*x): _incompleteGamma(x*x);
}



Derivative Erf::partial(unsigned int index) const {
  assert(index==0);
  Gaussian gauss = Gaussian();
  gauss.sigma().setValue(sqrt(2.0));
  const AbsFunction & fPrime = 2.0*gauss;
  return Derivative(& fPrime);
}

} // namespace Genfun
