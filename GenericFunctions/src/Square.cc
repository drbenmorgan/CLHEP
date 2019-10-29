// -*- C++ -*-
// $Id: Square.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/Square.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(Square)

Square::Square()
{}

Square::Square(const Square & right) : AbsFunction(right)
{
}

Square::~Square() {
}

double Square::operator() (double x) const {
  return x*x;
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
Derivative Square::partial(unsigned int index) const {
  assert(index==0);
  Variable x;
  const AbsFunction & fPrime = 2*x;
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
