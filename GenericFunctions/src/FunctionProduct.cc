// -*- C++ -*-
// $Id: FunctionProduct.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/FunctionProduct.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(FunctionProduct)

FunctionProduct::FunctionProduct(const AbsFunction *arg1, const AbsFunction *arg2):
_arg1(arg1->clone()),
_arg2(arg2->clone())
{
  if (arg1->dimensionality()!=arg2->dimensionality()) {
    std::cout
      << "Warning:  dimension mismatch in function product"
      << std::endl;
    assert(0);
  }
}

FunctionProduct::FunctionProduct(const FunctionProduct & right) :
  _arg1(right._arg1->clone()),
  _arg2(right._arg2->clone())
{
}

FunctionProduct::~FunctionProduct()
{
  delete _arg1;
  delete _arg2;
}


unsigned int FunctionProduct::dimensionality() const {
  return _arg1->dimensionality();
}

double FunctionProduct::operator ()(double x) const
{
  return (*_arg1)(x)*(*_arg2)(x);
}

double FunctionProduct::operator ()(const Argument & x) const
{
  return (*_arg1)(x)*(*_arg2)(x);
}

Derivative FunctionProduct::partial(unsigned int index) const {
  const AbsFunction & fPrime = 
    (*_arg1)*(_arg2->partial(index)) + (_arg1->partial(index))*(*_arg2);
  return Derivative(&fPrime);
}

} // namespace Genfun
