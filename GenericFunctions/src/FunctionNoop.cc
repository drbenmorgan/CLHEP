// -*- C++ -*-
// $Id: FunctionNoop.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
// ---------------------------------------------------------------------------

#include "CLHEP/GenericFunctions/FunctionNoop.hh"

namespace Genfun {
FUNCTION_OBJECT_IMP(FunctionNoop)

FunctionNoop::FunctionNoop(const AbsFunction *arg1):
  _arg1(arg1->clone())
{
}

FunctionNoop::FunctionNoop(const FunctionNoop & right):
  AbsFunction(right), _arg1(right._arg1->clone())
{
}


FunctionNoop::~FunctionNoop()
{
  delete _arg1;
}

unsigned int FunctionNoop::dimensionality() const {
  return _arg1->dimensionality();
}


double FunctionNoop::operator ()(double x) const
{
  return +((*_arg1)(x));
}

double FunctionNoop::operator ()(const Argument & x) const
{
  return +((*_arg1)(x));
}


Derivative FunctionNoop::partial(unsigned int index) const {
  return _arg1->partial(index);
}

} // namespace Genfun
