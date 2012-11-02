// -*- C++ -*-
// $Id: ConstPlusParameter.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/ConstPlusParameter.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {
PARAMETER_OBJECT_IMP(ConstPlusParameter)

ConstPlusParameter::ConstPlusParameter(double xconstant, const AbsParameter *aparm):
  _constant(xconstant),
  _parameter(aparm->clone())
{
  if (aparm->parameter() && _parameter->parameter()) _parameter->parameter()->connectFrom(aparm->parameter());
}

ConstPlusParameter::ConstPlusParameter(const ConstPlusParameter & right) :
AbsParameter(),
_constant(right._constant),
_parameter(right._parameter->clone())
{}


ConstPlusParameter::~ConstPlusParameter()
{
  delete _parameter;
}


double ConstPlusParameter::getValue() const {
  return _constant + _parameter->getValue();
}

} // namespace Genfun
