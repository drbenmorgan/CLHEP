// -*- C++ -*-
// $Id: Ln.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
// ---------------------------------------------------------------------------

#include "CLHEP/GenericFunctions/Ln.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(Ln)

Ln::Ln()
{}

Ln::~Ln() {
}

Ln::Ln(const Ln & right) 
{  }


double Ln::operator() (double x) const {
  return log(x);
}



Derivative Ln::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime = 1.0/Variable();
  return Derivative(& fPrime);
}

} // namespace Genfun
