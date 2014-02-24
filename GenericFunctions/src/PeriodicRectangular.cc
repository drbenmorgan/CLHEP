// -*- C++ -*-
// $Id: PeriodicRectangular.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
#include "CLHEP/GenericFunctions/PeriodicRectangular.hh"
#include "CLHEP/GenericFunctions/FixedConstant.hh"
#include <assert.h>
#include <cmath>      // for floor()

namespace Genfun {
FUNCTION_OBJECT_IMP(PeriodicRectangular)

PeriodicRectangular::PeriodicRectangular():
  _a("Size-of-valley (a)", 1.0, 1.0, 10),
  _b("Size-of-plateau (b)",  1.0, 1.0, 10),
  _height("height",1, 0,10)
{}

PeriodicRectangular::PeriodicRectangular(const PeriodicRectangular & right):
AbsFunction(right),
_a(right._a),
_b(right._b),
_height(right._height)
{
}

PeriodicRectangular::~PeriodicRectangular() {
}

double PeriodicRectangular::operator() (double x) const {
  double xx = x/(_a.getValue()+_b.getValue());
  xx = xx - floor(xx);
  if (xx < _a.getValue()/(_a.getValue()+_b.getValue())) {
    return 0;
  }
  else {
    return _height.getValue();
  }
}

Parameter & PeriodicRectangular::a() {
  return _a;
}

Parameter & PeriodicRectangular::b() {
  return _b;
}


Parameter & PeriodicRectangular::height() {
  return _height;
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
Derivative PeriodicRectangular::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime  = FixedConstant(0);
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
