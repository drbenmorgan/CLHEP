// -*- C++ -*-
// $Id: Exp.cc,v 1.2 2003/08/13 20:00:10 garren Exp $ 
#include "CLHEP/GenericFunctions/defs.h"
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
