// -*- C++ -*-
// $Id: FunctionComposition.cc,v 1.2 2003/08/13 20:00:10 garren Exp $
#include "CLHEP/GenericFunctions/defs.h"
#include "CLHEP/GenericFunctions/FunctionComposition.hh"
#include <iostream>
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(FunctionComposition)

FunctionComposition::FunctionComposition(const AbsFunction *arg1, const AbsFunction *arg2):_arg1(arg1->clone()),_arg2(arg2->clone())
{
  if (arg1->dimensionality()!=1) {
    std::cout
      << "Warning: dimension mismatch in function convolution"
      << std::endl;
    assert(0);
  }
}

FunctionComposition::FunctionComposition(const FunctionComposition & right):
_arg1(right._arg1->clone()),
_arg2(right._arg2->clone())
{}

FunctionComposition::~FunctionComposition()
{
  delete _arg1;
  delete _arg2;
}

unsigned int FunctionComposition::dimensionality() const {
  return _arg2->dimensionality();
}

double FunctionComposition::operator ()(double argument) const {
  if (dimensionality()!=1) {
    std::cerr
      << "Warning: LifetimeResolutionConvolution function/argument "
      << "dimension mismatch"
      << std::endl;
    assert(0);
    return 0;
  }
  else {
    return (*_arg1)((*_arg2)(argument));
  }
}

double FunctionComposition::operator() (const Argument &  v) const {
  if (v.dimension()!=_arg2->dimensionality()) {
    std::cerr
      << "Warning: FunctionComposition function/argument dimension mismatch"
      <<  std::endl;
    assert(0);
    return 0;
  }
  else {
    return (*_arg1)((*_arg2)(v));
  }
}


Derivative FunctionComposition::partial(unsigned int index) const {
  const AbsFunction & fPrime = (_arg1->partial(0))(*_arg2)*_arg2->partial(index);
  return Derivative(&fPrime);
}


} // namespace Genfun
