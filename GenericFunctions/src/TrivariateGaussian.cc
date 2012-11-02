// -*- C++ -*-
// $Id: TrivariateGaussian.cc,v 1.8 2010/06/16 18:22:01 garren Exp $
// ---------------------------------------------------------------------------

#include "CLHEP/GenericFunctions/defs.h"
#include "CLHEP/GenericFunctions/TrivariateGaussian.hh"
#include <assert.h>
#include <cmath>      // for exp()

#if (defined __STRICT_ANSI__) || (defined _WIN32)
#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif // M_PI
#endif // __STRICT_ANSI__

namespace Genfun {
FUNCTION_OBJECT_IMP(TrivariateGaussian)

TrivariateGaussian::TrivariateGaussian():
  _mean0("Mean0", 0.0,-10,10),
  _mean1("Mean1", 0.0,-10,10),
  _mean2("Mean2", 0.0,-10,10),
  _sigma0("Sigma0",1.0,0, 10),
  _sigma1("Sigma1",1.0,0, 10),
  _sigma2("Sigma2",1.0,0, 10),
  _corr01("Corr01", 0.0, -1.0, 1.0),
  _corr02("Corr02", 0.0, -1.0, 1.0),
  _corr12("Corr12", 0.0, -1.0, 1.0)
{}

TrivariateGaussian::~TrivariateGaussian() {
}

TrivariateGaussian::TrivariateGaussian(const TrivariateGaussian & right):
  AbsFunction(right),
  _mean0(right._mean0),
  _mean1(right._mean1),
  _mean2(right._mean2),
  _sigma0(right._sigma0),
  _sigma1(right._sigma1),
  _sigma2(right._sigma2),
  _corr01(right._corr01),
  _corr02(right._corr02),
  _corr12(right._corr12)
{
}


double TrivariateGaussian::operator() (const Argument & a) const {
  assert (a.dimension()==3);
  double x = a[0];
  double y = a[1];
  double z = a[2];


  double x0   = _mean0.getValue();
  double y0   = _mean1.getValue();
  double z0   = _mean2.getValue();

  double dx   = x-x0;
  double dy   = y-y0;
  double dz   = z-z0;

  double sx     = _sigma0.getValue();
  double sy     = _sigma1.getValue();
  double sz     = _sigma2.getValue();


  double sxs    = sx*sx;
  double sys    = sy*sy;
  double szs    = sz*sz;


  double rho1    = _corr01.getValue();
  double rho2    = _corr12.getValue();
  double rho3    = _corr02.getValue();

  double dt     = (1.0+rho1*rho2*rho3-rho1*rho1-rho2*rho2-rho3*rho3);
  double tmp1 ,tmp2;
 
  tmp1= 1.0/((2*M_PI)*sqrt(2*M_PI)*sx*sy*sz*sqrt(dt));
  tmp2= exp(-0.5/dt*(dx*dx*(1.0-rho2*rho2)/sxs+dy*dy*(1.0-rho3*rho3)/sys+dz*dz*(1.0-rho1*rho1)/szs+2.0*dx*dy*(rho2*rho3-rho1)/sx/sy+2.0*dy*dz*(rho1*rho3-rho2)/sy/sz+2.0*dx*dz*(rho1*rho2-rho3)/sx/sz));
  

  return tmp1*tmp2; 
  
 
}

Parameter & TrivariateGaussian::mean0() {
  return _mean0;
}

Parameter & TrivariateGaussian::sigma0() {
  return _sigma0;
}

const Parameter & TrivariateGaussian::mean0() const {
  return _mean0;
}

const Parameter & TrivariateGaussian::sigma0() const {
  return _sigma0;
}

Parameter & TrivariateGaussian::mean1() {
  return _mean1;
}

Parameter & TrivariateGaussian::sigma1() {
  return _sigma1;
}

const Parameter & TrivariateGaussian::mean1() const {
  return _mean1;
}

const Parameter & TrivariateGaussian::sigma1() const {
  return _sigma1;
}

Parameter & TrivariateGaussian::mean2() {
  return _mean2;
}


Parameter & TrivariateGaussian::sigma2() {
  return _sigma2;
}

const Parameter & TrivariateGaussian::mean2() const {
  return _mean2;
}

const Parameter & TrivariateGaussian::sigma2() const {
  return _sigma2;
}



Parameter & TrivariateGaussian::corr01() {
  return _corr01;
}

const Parameter & TrivariateGaussian::corr01() const {
  return _corr01;
}

Parameter & TrivariateGaussian::corr02() {
  return _corr02;
}

const Parameter & TrivariateGaussian::corr02() const {
  return _corr02;
}

Parameter & TrivariateGaussian::corr12() {
  return _corr12;
}

const Parameter & TrivariateGaussian::corr12() const {
  return _corr12;
}


unsigned int TrivariateGaussian::dimensionality() const {
  return 3;
}

double TrivariateGaussian::operator ()(double) const
{
  std::cerr
    << "Warning.  trivariate Gaussian called with scalar argument"
    << std::endl;
  assert(0);
  return 0;
}

} // namespace Genfun
