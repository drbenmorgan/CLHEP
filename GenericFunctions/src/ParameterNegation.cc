// -*- C++ -*-
// $Id: ParameterNegation.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/ParameterNegation.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {
PARAMETER_OBJECT_IMP(ParameterNegation)

ParameterNegation::ParameterNegation(const AbsParameter *arg1):
  _arg1(arg1->clone())
{
  if (arg1->parameter() && _arg1->parameter()) _arg1->parameter()->connectFrom(arg1->parameter());
}

ParameterNegation::ParameterNegation(const ParameterNegation & right) :
_arg1(right._arg1->clone())
{}


ParameterNegation::~ParameterNegation()
{
  delete _arg1;
}


double ParameterNegation::getValue() const {
  return - _arg1->getValue();
}

} // namespace Genfun
