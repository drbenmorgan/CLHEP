// -*- C++ -*-
// $Id: ConstMinusFunction.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/ConstMinusFunction.hh"
#include <iostream>

namespace Genfun {
FUNCTION_OBJECT_IMP(ConstMinusFunction)

ConstMinusFunction::ConstMinusFunction(double constant, const AbsFunction *arg):
  _constant(constant),
  _arg(arg->clone())
{
}

ConstMinusFunction::ConstMinusFunction(const ConstMinusFunction & right) :
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
