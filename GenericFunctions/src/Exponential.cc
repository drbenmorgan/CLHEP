// -*- C++ -*-
// $Id: Exponential.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
#include "CLHEP/GenericFunctions/Exponential.hh"
#include <assert.h>
#include <cmath>      // for exp()

namespace Genfun {
FUNCTION_OBJECT_IMP(Exponential)

Exponential::Exponential():
  _decayConstant("Decay Constant", 1.0, 0,10)
{}

Exponential::Exponential(const Exponential & right):
  AbsFunction(right),
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

// don't generate warnings about unused parameter inside assert
#if defined __GNUC__ 
  #if __GNUC__ > 3 && __GNUC_MINOR__ > 6
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
  #endif
#endif
#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wunused-parameter"
#endif
Derivative Exponential::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime = -_decayConstant*(*this);
  return Derivative(&fPrime);
}
#if defined __GNUC__ 
  #if __GNUC__ > 3 && __GNUC_MINOR__ > 6
    #pragma GCC diagnostic pop
  #endif
#endif
#ifdef __clang__
  #pragma clang diagnostic pop
#endif


} // namespace Genfun
