// -*- C++ -*-
// $Id: Exp.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $ 
#include "CLHEP/GenericFunctions/Exp.hh"
#include <assert.h>
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
