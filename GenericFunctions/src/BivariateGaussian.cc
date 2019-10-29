// -*- C++ -*-
// $Id: BivariateGaussian.cc,v 1.8 2010/06/16 18:22:01 garren Exp $
#include "CLHEP/GenericFunctions/defs.h"
#include "CLHEP/GenericFunctions/BivariateGaussian.hh"
#include <assert.h>
#include <cmath>      // for exp()

#if (defined __STRICT_ANSI__) || (defined _WIN32)
#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif // M_PI
#endif // __STRICT_ANSI__

namespace Genfun {
FUNCTION_OBJECT_IMP(BivariateGaussian)

BivariateGaussian::BivariateGaussian():
  _mean0("Mean0", 0.0,-10,10),
  _mean1("Mean1", 0.0,-10,10),
  _sigma0("Sigma0",1.0,0, 10),
  _sigma1("Sigma1",1.0,0, 10),
  _corr01("Corr01", 0.0, -1.0, 1.0)
{}

BivariateGaussian::~BivariateGaussian() {
}

BivariateGaussian::BivariateGaussian(const BivariateGaussian & right):
  AbsFunction(right),
  _mean0(right._mean0),
  _mean1(right._mean1),
  _sigma0(right._sigma0),
  _sigma1(right._sigma1),
  _corr01(right._corr01)
{
}

double BivariateGaussian::operator() (const Argument & a) const {
  assert (a.dimension()==2);
  double x = a[0];
  double y = a[1];

  double x0   = _mean0.getValue();
  double y0   = _mean1.getValue();
  double dx   = x-x0;
  double dy   = y-y0;
  
  double sx     = _sigma0.getValue();
  double sy     = _sigma1.getValue();

  double sxs    = sx*sx;
  double sys    = sy*sy;
  double rho    = _corr01.getValue();
  double dt     = (1.0+rho)*(1.0-rho);

  return (1.0/(2*M_PI*sx*sy*sqrt(dt))) * 
	       exp(-1.0/(2.0*dt)*(dx*dx/sxs+dy*dy/sys-2.0*rho*dx*dy/sx/sy));
}

Parameter & BivariateGaussian::mean0() {
  return _mean0;
}

Parameter & BivariateGaussian::sigma0() {
  return _sigma0;
}

const Parameter & BivariateGaussian::mean0() const {
  return _mean0;
}

const Parameter & BivariateGaussian::sigma0() const {
  return _sigma0;
}

Parameter & BivariateGaussian::mean1() {
  return _mean1;
}

Parameter & BivariateGaussian::sigma1() {
  return _sigma1;
}

const Parameter & BivariateGaussian::mean1() const {
  return _mean1;
}

const Parameter & BivariateGaussian::sigma1() const {
  return _sigma1;
}



Parameter & BivariateGaussian::corr01() {
  return _corr01;
}

const Parameter & BivariateGaussian::corr01() const {
  return _corr01;
}


unsigned int BivariateGaussian::dimensionality() const {
  return 2;
}

double BivariateGaussian::operator ()(double) const
{
  std::cerr
    << "Warning.  bivariate Gaussian called with scalar argument"
    << std::endl;
  assert(0);
  return 0;
}

} // namespace Genfun
