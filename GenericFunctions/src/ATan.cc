// -*- C++ -*-
// $Id: ATan.cc,v 1.4 2003/10/10 17:40:39 garren Exp $ 
#include "CLHEP/GenericFunctions/ATan.hh"
#include "CLHEP/GenericFunctions/Square.hh"
#include <assert.h>
#include <cmath>      // for atan()

namespace Genfun {
FUNCTION_OBJECT_IMP(ATan)

ATan::ATan()
{}

ATan::~ATan() {
}

ATan::ATan(const ATan & right) : AbsFunction(right)
{  }


double ATan::operator() (double x) const {
  return atan(x);
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
Derivative ATan::partial(unsigned int index) const {
  assert(index==0);

  Square square;
  
  const AbsFunction & fPrime=1.0/(1.0+square);;
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
