// -*- C++ -*-
// $Id: FunctionPlusParameter.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/FunctionPlusParameter.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {
FUNCTION_OBJECT_IMP(FunctionPlusParameter)

FunctionPlusParameter::FunctionPlusParameter(const AbsParameter *parameter, const AbsFunction *function):
  _function(function->clone()),
  _parameter(parameter->clone())
{
  if (parameter->parameter() && _parameter->parameter()) {
    _parameter->parameter()->connectFrom(parameter->parameter());
  }
}

FunctionPlusParameter::FunctionPlusParameter(const FunctionPlusParameter & right) :
  _function(right._function->clone()),
  _parameter(right._parameter->clone())
{}

unsigned int FunctionPlusParameter::dimensionality() const {
  return _function->dimensionality();
}

FunctionPlusParameter::~FunctionPlusParameter()
{
  delete _function;
  delete _parameter;
}


double FunctionPlusParameter::operator ()(double x) const
{
  return _parameter->getValue() + (*_function)(x);
}


double FunctionPlusParameter::operator ()(const Argument & x) const
{
  return _parameter->getValue() + (*_function)(x);
}

Derivative FunctionPlusParameter::partial(unsigned int index) const {
  return _function->partial(index);
}

} // namespace Genfun
