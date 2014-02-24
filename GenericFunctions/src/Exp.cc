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

// don't generate warnings about unused parameter inside assert
#if defined __GNUC__ 
  #if __GNUC__ > 3 && __GNUC_MINOR__ > 6
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
  #endif
#endif
#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wunused-parameter"
#endif
Derivative Exp::partial(unsigned int index) const {
  assert(index==0);
  return Derivative(this);
}
#if defined __GNUC__ 
  #if __GNUC__ > 3 && __GNUC_MINOR__ > 6
    #pragma GCC diagnostic pop
  #endif
#endif
#ifdef __clang__
  #pragma clang diagnostic pop
#endif


} // namespace Genfun
