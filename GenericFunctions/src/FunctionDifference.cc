// -*- C++ -*-
// $Id: FunctionDifference.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/FunctionDifference.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(FunctionDifference)

FunctionDifference::FunctionDifference(const AbsFunction *arg1, const AbsFunction *arg2):
  _arg1(arg1->clone()),
  _arg2(arg2->clone())
{
  if (arg1->dimensionality()!=arg2->dimensionality()) {
    std::cout
      << "Warning:  dimension mismatch in function difference"
      << std::endl;
    assert(0);
  }
}


FunctionDifference::FunctionDifference(const FunctionDifference & right):
  _arg1(right._arg1->clone()),
  _arg2(right._arg2->clone())
{
}


unsigned int FunctionDifference::dimensionality() const {
  return _arg1->dimensionality();
}

FunctionDifference::~FunctionDifference()
{
  delete _arg1;
  delete _arg2;
}



double FunctionDifference::operator ()(double x) const
{
  return (*_arg1)(x)-(*_arg2)(x);
}

double FunctionDifference::operator ()(const Argument & x) const
{
  return (*_arg1)(x)-(*_arg2)(x);
}


Derivative FunctionDifference::partial(unsigned int index) const {
  const AbsFunction & fPrime = _arg1->partial(index) - _arg2->partial(index);
  return Derivative(&fPrime);
}



} // namespace Genfun
