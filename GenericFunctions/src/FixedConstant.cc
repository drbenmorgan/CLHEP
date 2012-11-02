// -*- C++ -*-
// $Id: FixedConstant.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/FixedConstant.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(FixedConstant)

FixedConstant::FixedConstant(double value):
_value(value)
{
}

FixedConstant::FixedConstant(const FixedConstant & right):
AbsFunction(right), _value(right._value) {
}

FixedConstant::~FixedConstant()
{
}

double FixedConstant::operator ()(double) const
{
  return _value;
}

Derivative FixedConstant::partial(unsigned int index) const {
  assert(index==0);
  FixedConstant fPrime(0.0);
  return Derivative(&fPrime);
}

} // namespace Genfun
