// -*- C++ -*-
// $Id: FunctionConvolution.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/FunctionConvolution.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(FunctionConvolution)

FunctionConvolution::FunctionConvolution(const AbsFunction *arg1, const AbsFunction *arg2, double x0, double x1):_arg1(arg1->clone()),_arg2(arg2->clone()),_x0(x0), _x1(x1)
{
  if ((arg1->dimensionality()!=1) || arg2->dimensionality()!=1) {
    std::cout
      << "Warning:  dimension mismatch in function convolution"
      << std::endl;
    assert(0);
  }
}

FunctionConvolution::FunctionConvolution(const FunctionConvolution & right):
_arg1(right._arg1->clone()),
_arg2(right._arg2->clone()),
_x0(right._x0),
_x1(right._x1)
{}

FunctionConvolution::~FunctionConvolution()
{
  delete _arg1;
  delete _arg2;
}



double FunctionConvolution::operator ()(double argument) const
{
  const double NDIVISIONS=200.0;
  double dx = (_x1-_x0)/NDIVISIONS;
  double result=0.0;
  for (double x=_x0; x<_x1; x+=dx) {
    result += (*_arg1)(argument-x)*(*_arg2)(x);
  }
  result/=NDIVISIONS;
  return result;
}

} // namespace Genfun
