// -*- C++ -*-
// $Id: ParameterNegation.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
#include "GenericFunctions/defs.h"

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
