// -*- C++ -*-
// $Id: Exponential.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/Exponential.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(Exponential)

Exponential::Exponential():
  _decayConstant("Decay Constant", 1.0, 0,10)
{}

Exponential::Exponential(const Exponential & right):
  _decayConstant(right._decayConstant)
{
}

Exponential::~Exponential() {
}

double Exponential::operator() (double x) const {
  if (x<0) return 0;
  return exp(-x/_decayConstant.getValue())/_decayConstant.getValue();
}

Parameter & Exponential::decayConstant() {
  return _decayConstant;
}

const Parameter & Exponential::decayConstant() const {
  return _decayConstant;
}


Derivative Exponential::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime = -_decayConstant*(*this);
  return Derivative(&fPrime);
}


} // namespace Genfun
