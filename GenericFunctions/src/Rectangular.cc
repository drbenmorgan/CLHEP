// -*- C++ -*-
// $Id: Rectangular.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/Rectangular.hh"
#include "CLHEP/GenericFunctions/FixedConstant.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(Rectangular)

Rectangular::Rectangular():
  _x0("x0", -1.0, -10, 0),
  _x1("x1",  1.0, 0,  10),
  _baseline("baseline", 0,-10, 10),
  _height("height",1, -10, 10)
{}

Rectangular::Rectangular(const Rectangular & right) :
_x0(right._x0),
_x1(right._x1),
_baseline(right._baseline),
_height(right._height)
{
}

Rectangular::~Rectangular() {
}

double Rectangular::operator() (double x) const {
  if (x<_x0.getValue()) {
    return _baseline.getValue();
  }
  else if (x<_x1.getValue()) {
    return _height.getValue();
  }
  else {
    return _baseline.getValue();
  }
}

Parameter & Rectangular::x0() {
  return _x0;
}

Parameter & Rectangular::x1() {
  return _x1;
}

Parameter & Rectangular::baseline() {
  return _baseline;
}

Parameter & Rectangular::height() {
  return _height;
}

const Parameter & Rectangular::x0() const {
  return _x0;
}

const Parameter & Rectangular::x1() const {
  return _x1;
}

const Parameter & Rectangular::baseline() const {
  return _baseline;
}

const Parameter & Rectangular::height() const{
  return _height;
}


Derivative Rectangular::partial(unsigned int index) const {
  assert(index==0);
  const AbsFunction & fPrime  = FixedConstant(0);;
  return Derivative(&fPrime);
}

} // namespace Genfun
