// -*- C++ -*-
// $Id: ConstTimesParameter.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/ConstTimesParameter.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {
PARAMETER_OBJECT_IMP(ConstTimesParameter)

ConstTimesParameter::ConstTimesParameter(double constant, const AbsParameter *parameter):
  _constant(constant),
  _parameter(parameter->clone())
{
  if (parameter->parameter() && _parameter->parameter()) _parameter->parameter()->connectFrom(parameter->parameter());
}

ConstTimesParameter::ConstTimesParameter(const ConstTimesParameter & right) :
_constant(right._constant),
_parameter(right._parameter->clone())
{}


ConstTimesParameter::~ConstTimesParameter()
{
  delete _parameter;
}


double ConstTimesParameter::getValue() const {
  return _constant * _parameter->getValue();
}


} // namespace Genfun
