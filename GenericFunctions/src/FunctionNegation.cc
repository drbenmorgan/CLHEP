// -*- C++ -*-
// $Id: FunctionNegation.cc,v 1.2 2003/08/13 20:00:10 garren Exp $
#include "CLHEP/GenericFunctions/defs.h"
#include "CLHEP/GenericFunctions/FunctionNegation.hh"

namespace Genfun {

FUNCTION_OBJECT_IMP(FunctionNegation)

FunctionNegation::FunctionNegation(const AbsFunction *arg1):
  _arg1(arg1->clone())
{
}

FunctionNegation::FunctionNegation(const FunctionNegation & right):
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
