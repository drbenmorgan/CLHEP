// -*- C++ -*-
// $Id: ParameterSum.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/ParameterSum.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {
PARAMETER_OBJECT_IMP(ParameterSum)

ParameterSum::ParameterSum(const AbsParameter *arg1, const AbsParameter *arg2):
  _arg1(arg1->clone()),
  _arg2(arg2->clone())
{
  if (arg1->parameter() && _arg1->parameter()) _arg1->parameter()->connectFrom(arg1->parameter());
  if (arg2->parameter() && _arg2->parameter()) _arg2->parameter()->connectFrom(arg2->parameter());
}

ParameterSum::ParameterSum(const ParameterSum & right) :
AbsParameter(),
_arg1(right._arg1->clone()),
_arg2(right._arg2->clone())
{}


ParameterSum::~ParameterSum()
{
  delete _arg1;
  delete _arg2;
}


double ParameterSum::getValue() const {
  return _arg1->getValue()+_arg2->getValue();
}

} // namespace Genfun
