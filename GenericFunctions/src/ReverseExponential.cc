// -*- C++ -*-
// $Id: ReverseExponential.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
#include "CLHEP/GenericFunctions/ReverseExponential.hh"
#include <assert.h>
#include <cmath>      // for exp()

namespace Genfun {
FUNCTION_OBJECT_IMP(ReverseExponential)

ReverseExponential::ReverseExponential():
  _decayConstant("Decay Constant", 1.0, 0,10)
{}

ReverseExponential::ReverseExponential(const ReverseExponential & right) :
_decayConstant(right._decayConstant)
{
}

ReverseExponential::~ReverseExponential() {
}

double ReverseExponential::operator() (double x) const {
  if (x>0) return 0;
  return exp(x/_decayConstant.getValue())/_decayConstant.getValue();
}

Parameter & ReverseExponential::decayConstant() {
  return _decayConstant;
}


Derivative ReverseExponential::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime = _decayConstant*(*this);
  return Derivative(&fPrime);
}


} // namespace Genfun
