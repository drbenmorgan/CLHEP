// -*- C++ -*-
// $Id: Exp.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $ 
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/Exp.hh"
#include <assert.h>
#include <cmath>	// for exp()

namespace Genfun {
FUNCTION_OBJECT_IMP(Exp)

Exp::Exp()
{}

Exp::Exp(const Exp & right)
{}

Exp::~Exp() {
}

double Exp::operator() (double x) const {
  return exp(x);
}


Derivative Exp::partial(unsigned int index) const {
  assert(index==0);
  return Derivative(this);
}


} // namespace Genfun
