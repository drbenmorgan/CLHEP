// -*- C++ -*-
// $Id: PeriodicRectangular.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/PeriodicRectangular.hh"
#include "CLHEP/GenericFunctions/FixedConstant.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(PeriodicRectangular)

PeriodicRectangular::PeriodicRectangular():
  _a("Size-of-valley (a)", 1.0, 1.0, 10),
  _b("Size-of-plateau (b)",  1.0, 1.0, 10),
  _height("height",1, 0,10)
{}

PeriodicRectangular::PeriodicRectangular(const PeriodicRectangular & right):
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



Derivative PeriodicRectangular::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime  = FixedConstant(0);
  return Derivative(&fPrime);
}

} // namespace Genfun
