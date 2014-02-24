// -*- C++ -*-
// $Id: ACos.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
#include "CLHEP/GenericFunctions/ACos.hh"
#include "CLHEP/GenericFunctions/Sqrt.hh"
#include "CLHEP/GenericFunctions/Square.hh"
#include <assert.h>
#include <cmath>      // for acos()

namespace Genfun {
FUNCTION_OBJECT_IMP(ACos)

ACos::ACos()
{}

ACos::~ACos() {
}

ACos::ACos(const ACos & right) : AbsFunction(right)
{  }


double ACos::operator() (double x) const {
  return acos(x);
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
Derivative ACos::partial(unsigned int index) const {
  assert(index==0);

  Square square;
  Sqrt   root;

  const AbsFunction & fPrime = - 1.0/root(1.0-square) ;
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

} // end namespace Genfun 


