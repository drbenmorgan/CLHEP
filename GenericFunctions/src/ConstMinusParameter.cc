// -*- C++ -*-
// $Id: ConstMinusParameter.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/ConstMinusParameter.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {
PARAMETER_OBJECT_IMP(ConstMinusParameter)


ConstMinusParameter::ConstMinusParameter(double xconstant, const AbsParameter *aparm):
  _constant(xconstant),
  _parameter(aparm->clone())
{
  if (aparm->parameter() && _parameter->parameter()) _parameter->parameter()->connectFrom(aparm->parameter());
}

ConstMinusParameter::ConstMinusParameter(const ConstMinusParameter & right) :
AbsParameter(right),
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
