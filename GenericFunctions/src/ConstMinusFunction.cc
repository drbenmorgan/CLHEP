// -*- C++ -*-
// $Id: ConstMinusFunction.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/ConstMinusFunction.hh"


namespace Genfun {
FUNCTION_OBJECT_IMP(ConstMinusFunction)

ConstMinusFunction::ConstMinusFunction(double constant, const AbsFunction *arg):
  _constant(constant),
  _arg(arg->clone())
{
}

ConstMinusFunction::ConstMinusFunction(const ConstMinusFunction & right) :
AbsFunction(right),
_constant(right._constant),
_arg(right._arg->clone())
{}

unsigned int ConstMinusFunction::dimensionality() const {
  return _arg->dimensionality();
}

ConstMinusFunction::~ConstMinusFunction()
{
  delete _arg;
}



double ConstMinusFunction::operator ()(double x) const
{
  return _constant - (*_arg)(x);
}


double ConstMinusFunction::operator ()(const Argument & x) const
{
  return _constant - (*_arg)(x);
}


Derivative ConstMinusFunction::partial(unsigned int index) const {
  const AbsFunction & fPrime = -_arg->partial(index);
  return Derivative(& fPrime);
}


} // namespace Genfun
