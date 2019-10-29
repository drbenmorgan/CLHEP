// -*- C++ -*-
// $Id: ConstTimesParameter.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/ConstTimesParameter.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {
PARAMETER_OBJECT_IMP(ConstTimesParameter)

ConstTimesParameter::ConstTimesParameter(double xconstant, const AbsParameter *aparm):
  _constant(xconstant),
  _parameter(aparm->clone())
{
  if (aparm->parameter() && _parameter->parameter()) _parameter->parameter()->connectFrom(aparm->parameter());
}

ConstTimesParameter::ConstTimesParameter(const ConstTimesParameter & right) :
AbsParameter(),
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
