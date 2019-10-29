// -*- C++ -*-
// $Id: FunctionNegation.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/FunctionNegation.hh"

namespace Genfun {
FUNCTION_OBJECT_IMP(FunctionNegation)

FunctionNegation::FunctionNegation(const AbsFunction *arg1):
  _arg1(arg1->clone())
{
}

FunctionNegation::FunctionNegation(const FunctionNegation & right):
  AbsFunction(right),
  _arg1(right._arg1->clone())
{
}


FunctionNegation::~FunctionNegation()
{
  delete _arg1;
}

unsigned int FunctionNegation::dimensionality() const {
  return _arg1->dimensionality();
}


double FunctionNegation::operator ()(double x) const
{
  return -((*_arg1)(x));
}

double FunctionNegation::operator ()(const Argument & x) const
{
  return -((*_arg1)(x));
}


Derivative FunctionNegation::partial(unsigned int index) const {
  const AbsFunction & fPrime  = -(_arg1->partial(index));
  return Derivative(&fPrime);
}

  
} // namespace Genfun
