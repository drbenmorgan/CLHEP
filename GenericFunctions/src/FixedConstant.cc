// -*- C++ -*-
// $Id: FixedConstant.cc,v 1.2 2003/08/13 20:00:10 garren Exp $
#include "CLHEP/GenericFunctions/defs.h"
#include "CLHEP/GenericFunctions/FixedConstant.hh"
#include <assert.h>

namespace Genfun {

FUNCTION_OBJECT_IMP(FixedConstant)

FixedConstant::FixedConstant(double value):
_value(value)
{
}

FixedConstant::FixedConstant(const FixedConstant & right):
_value(right._value) {
}

FixedConstant::~FixedConstant()
{
}

double FixedConstant::operator ()(double argument) const
{
  return _value;
}

Derivative FixedConstant::partial(unsigned int index) const {
  assert(index==0);
  FixedConstant fPrime(0.0);
  return Derivative(&fPrime);
}

} // namespace Genfun
