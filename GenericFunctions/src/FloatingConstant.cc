// -*- C++ -*-
// $Id: FloatingConstant.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/FloatingConstant.hh"
#include "CLHEP/GenericFunctions/FixedConstant.hh"
#include <assert.h>
namespace Genfun {
FUNCTION_OBJECT_IMP(FloatingConstant)

FloatingConstant::FloatingConstant(const AbsParameter & p):
  _value(p.clone())
{
  if (_value->parameter() && p.parameter()) _value->parameter()->connectFrom(&p);
}

FloatingConstant::FloatingConstant(const FloatingConstant & right):
  _value(right._value->clone()) {
}

FloatingConstant::~FloatingConstant()
{
}

AbsParameter & FloatingConstant::value() {
  return *_value;
}

double FloatingConstant::operator ()(double argument) const
{
  return _value->getValue();
}

Derivative FloatingConstant::partial(unsigned int index) const {
  assert(index==0);
  FixedConstant fPrime(0.0);
  return Derivative(&fPrime);
}
} // namespace Genfun
