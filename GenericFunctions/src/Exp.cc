// -*- C++ -*-
// $Id: Exp.cc,v 1.4 2003/10/10 17:40:39 garren Exp $ 
#include "CLHEP/GenericFunctions/Exp.hh"
#include <assert.h>
#include <cmath>      // for exp()

namespace Genfun {
FUNCTION_OBJECT_IMP(Exp)

Exp::Exp()
{}

Exp::Exp(const Exp & right) : AbsFunction(right)
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
