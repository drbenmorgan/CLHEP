// -*- C++ -*-
// $Id: FunctionDirectProduct.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/FunctionDirectProduct.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(FunctionDirectProduct)

FunctionDirectProduct::FunctionDirectProduct(const AbsFunction *arg1, const AbsFunction *arg2):
_arg1(arg1->clone()),
_arg2(arg2->clone()),
_m(arg1->dimensionality()),
_n(arg2->dimensionality())
{
}

FunctionDirectProduct::FunctionDirectProduct(const FunctionDirectProduct & right):
_arg1(right._arg1->clone()),
_arg2(right._arg2->clone()),
_m(right._m),
_n(right._n)
{
}


FunctionDirectProduct::~FunctionDirectProduct()
{
  delete _arg1;
  delete _arg2;
}


double FunctionDirectProduct::operator() (const Argument & a) const {
  unsigned int P = a.dimension();
  Argument x1(_m);
  Argument x2(_n);
  if (_m+_n != P) {
    std::cerr
      << "Warning: Direct product function/argument dimension mismatch"
      <<  std::endl;
    assert(0);
    return 0;
  }
  for (unsigned int i = 0; i<_m;i++) {
    x1[i]=a[i];
  }
  for (unsigned int j = 0;j<_n;j++) {
    x2[j]=a[j+_m];
  }
  return (*_arg1)(x1) * (*_arg2)(x2);
}

unsigned int FunctionDirectProduct::dimensionality() const {
  return _m+_n;
}

double FunctionDirectProduct::operator ()(double x) const
{
  std::cerr
    << "Warning.  direct product called with scalar argument"
    << std::endl;
  assert(0);
  return 0;
}



Derivative FunctionDirectProduct::partial(unsigned int index) const {
  assert (index<(_m+_n));
  if (index<_m) {
    const AbsFunction & fPrime = (_arg1->partial(index))%(*_arg2);
    return Derivative(&fPrime);
  }
  else {
    const AbsFunction & fPrime = (*_arg1)%(_arg2->partial(index-_m));
    return Derivative(&fPrime);
  }
}


} // namespace Genfun
