// -*- C++ -*-
// $Id: Cos.cc,v 1.4 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/Cos.hh"
#include "CLHEP/GenericFunctions/Sin.hh"

namespace Genfun {
FUNCTION_OBJECT_IMP(Cos)

Cos::Cos()
{}

Cos::~Cos() {
}

Cos::Cos(const Cos & right) 
{  }


double Cos::operator() (double x) const {
  return cos(x);
}


Derivative Cos::partial(unsigned int index) const {
  const AbsFunction & fPrime = -Sin();
  return Derivative(& fPrime);
}


} // namespace Genfun
