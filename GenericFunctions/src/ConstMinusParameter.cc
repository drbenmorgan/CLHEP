// -*- C++ -*-
// $Id: ConstMinusParameter.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/ConstMinusParameter.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {
PARAMETER_OBJECT_IMP(ConstMinusParameter)


ConstMinusParameter::ConstMinusParameter(double constant, const AbsParameter *parameter):
  _constant(constant),
  _parameter(parameter->clone())
{
  if (parameter->parameter() && _parameter->parameter()) _parameter->parameter()->connectFrom(parameter->parameter());
}

ConstMinusParameter::ConstMinusParameter(const ConstMinusParameter & right) :
_constant(right._constant),
_parameter(right._parameter->clone())
{}


ConstMinusParameter::~ConstMinusParameter()
{
  delete _parameter;
}


double ConstMinusParameter::getValue() const {
  return _constant - _parameter->getValue();
}



} // namespace Genfun
