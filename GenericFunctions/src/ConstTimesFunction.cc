// -*- C++ -*-
// $Id: ConstTimesFunction.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/ConstTimesFunction.hh"

namespace Genfun {
FUNCTION_OBJECT_IMP(ConstTimesFunction)

ConstTimesFunction::ConstTimesFunction(double constant, const AbsFunction *arg):
  _constant(constant),
  _arg(arg->clone())
{
}

ConstTimesFunction::ConstTimesFunction(const ConstTimesFunction & right) :
AbsFunction(right),
_constant(right._constant),
_arg(right._arg->clone())
{}

unsigned int ConstTimesFunction::dimensionality() const {
  return _arg->dimensionality();
}

ConstTimesFunction::~ConstTimesFunction()
{
  delete _arg;
}



double ConstTimesFunction::operator ()(double x) const
{
  return _constant * (*_arg)(x);
}


double ConstTimesFunction::operator ()(const Argument & x) const
{
  return _constant * (*_arg)(x);
}

Derivative ConstTimesFunction::partial(unsigned int index) const {
  // d/dx (k*f) = k*(df/dx)
  const AbsFunction & fPrime = _constant*(_arg->partial(index));
  return Derivative(& fPrime);
}

} // namespace Genfun
