// -*- C++ -*-
// $Id: ConstOverFunction.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/ConstOverFunction.hh"

namespace Genfun {
FUNCTION_OBJECT_IMP(ConstOverFunction)

ConstOverFunction::ConstOverFunction(double constant, const AbsFunction *arg):
  _constant(constant),
  _arg(arg->clone())
{
}

ConstOverFunction::ConstOverFunction(const ConstOverFunction & right) :
_constant(right._constant),
_arg(right._arg->clone())
{}

unsigned int ConstOverFunction::dimensionality() const {
  return _arg->dimensionality();
}

ConstOverFunction::~ConstOverFunction()
{
  delete _arg;
}



double ConstOverFunction::operator ()(double x) const
{
  return _constant / (*_arg)(x);
}


double ConstOverFunction::operator ()(const Argument & x) const
{
  return _constant / (*_arg)(x);
}


Derivative ConstOverFunction::partial(unsigned int index) const {
  // d/dx (k/f) = -(k/f^2)(df/dx)
  const AbsFunction & fPrime = -_constant/(*_arg)/(*_arg)*(_arg->partial(index));
  return Derivative(& fPrime);
}


} // namespace Genfun
