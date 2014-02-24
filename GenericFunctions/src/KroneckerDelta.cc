// -*- C++ -*-
// $Id: KroneckerDelta.cc,v 1.1 2007/01/21 20:54:34 boudreau Exp $
#include "CLHEP/GenericFunctions/KroneckerDelta.hh"
#include "CLHEP/GenericFunctions/FixedConstant.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(KroneckerDelta)

KroneckerDelta::KroneckerDelta()
{}

KroneckerDelta::KroneckerDelta(const KroneckerDelta & right) : AbsFunction(right)
{
}

KroneckerDelta::~KroneckerDelta() {
}

double KroneckerDelta::operator() (double x) const {
  if (x < 0.5 && x > -0.5) return 1;
  return 0;
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
Derivative KroneckerDelta::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime  = FixedConstant(0);;
  return Derivative(&fPrime);
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
