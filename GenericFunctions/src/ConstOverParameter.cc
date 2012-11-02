// -*- C++ -*-
// $Id: ConstOverParameter.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/ConstOverParameter.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {
PARAMETER_OBJECT_IMP(ConstOverParameter)

ConstOverParameter::ConstOverParameter(double xconstant, const AbsParameter *aparm):
  _constant(xconstant),
  _parameter(aparm->clone())
{
  if (aparm->parameter() && _parameter->parameter()) _parameter->parameter()->connectFrom(aparm->parameter());
}

ConstOverParameter::ConstOverParameter(const ConstOverParameter & right) :
AbsParameter(right),
_constant(right._constant),
_parameter(right._parameter->clone())
{}


ConstOverParameter::~ConstOverParameter()
{
  delete _parameter;
}


double ConstOverParameter::getValue() const {
  return _constant / _parameter->getValue();
}

} // namespace Genfun
