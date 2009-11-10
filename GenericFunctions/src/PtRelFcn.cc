// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/defs.h"
#include "CLHEP/GenericFunctions/PtRelFcn.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <assert.h>
#include <cmath>	// for pow() and exp()
#include <float.h>

#if (defined __STRICT_ANSI__) || (defined _WIN32)
#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif // M_PI
#endif // __STRICT_ANSI__

namespace Genfun {
FUNCTION_OBJECT_IMP(PtRelFcn)

PtRelFcn::PtRelFcn():
  _p0("P0", 0, 0, 1),
  _p1("P1", 0, 0, 2),
  _p2("P2", 1, 0, 10),
  _p3("P3", 0, 0, 10),
  _p4("P4", 1.0, 0.1, 5.0),
  _p5("P5", 0.0, 0, 50)
{}

PtRelFcn::~PtRelFcn() {
}

PtRelFcn::PtRelFcn(const PtRelFcn & right):
_p0(right._p0),
_p1(right._p1),
_p2(right._p2),
_p3(right._p3),
_p4(right._p4),
_p5(right._p5)
{
}

double PtRelFcn::operator() (double x) const {
  
  double p0   = _p0.getValue();
  double p1   = _p1.getValue();
  double p2   = _p2.getValue();
  double p3   = _p3.getValue();
  double p4   = _p4.getValue();
  double p5   = _p5.getValue();

  //assert ((p0>=0.0) && (p0<=1.0));
  if (p0<0.0) p0=FLT_MIN;
  if (p0>1.0) p0=1.0-FLT_MIN;

  if (x<=0.0) return 1.0E-10;

  double n = (1+p1)/p3;
  double a = (1/p3)*pow(p2,-n);
  
  double norm = 1.0/(a*exp(_logGamma(n)));
  static const double s2 = sqrt(2.0);
  double retVal= 
    norm*p0*pow(x,p1)*exp(-p2*pow(x,p3)) +
    (2.0/(1+_erf(p5/p4/s2))*(1.0-p0)/(sqrt(2*M_PI)*p4))*exp(-(x-p5)*(x-p5)/(2.0*p4*p4));

  //if (!finite(retVal)) return 1.0E-10;

  return std::max(retVal,1.0E-10);  
}

Parameter & PtRelFcn::P0() {
  return _p0;
}

const Parameter & PtRelFcn::P0() const {
  return _p0;
}

Parameter & PtRelFcn::P1() {
  return _p1;
}

const Parameter & PtRelFcn::P1() const {
  return _p1;
}

Parameter & PtRelFcn::P2() {
  return _p2;
}

const Parameter & PtRelFcn::P2() const {
  return _p2;
}

Parameter & PtRelFcn::P3() {
  return _p3;
}

const Parameter & PtRelFcn::P3() const {
  return _p3;
}

Parameter & PtRelFcn::P4() {
  return _p4;
}

const Parameter & PtRelFcn::P4() const {
  return _p4;
}

Parameter & PtRelFcn::P5() {
  return _p5;
}

const Parameter & PtRelFcn::P5() const {
  return _p5;
}





} // namespace Genfun
