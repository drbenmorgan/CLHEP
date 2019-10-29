// -*- C++ -*-
// $Id: Ln.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
// ---------------------------------------------------------------------------

#include "CLHEP/GenericFunctions/Ln.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <assert.h>
#include <cmath>      // for log()

namespace Genfun {
FUNCTION_OBJECT_IMP(Ln)

Ln::Ln()
{}

Ln::~Ln() {
}

Ln::Ln(const Ln & right) : AbsFunction(right)
{  }


double Ln::operator() (double x) const {
  return log(x);
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
Derivative Ln::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime = 1.0/Variable();
  return Derivative(& fPrime);
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
