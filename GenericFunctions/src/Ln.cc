// -*- C++ -*-
// $Id: Ln.cc,v 1.2 2003/08/13 20:00:10 garren Exp $
// ---------------------------------------------------------------------------
#include "CLHEP/GenericFunctions/defs.h"
#include "CLHEP/GenericFunctions/Ln.hh"
#include "CLHEP/GenericFunctions/Variable.hh"

#include <iostream>
#include <assert.h>
#include <cmath>	// for log()

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
