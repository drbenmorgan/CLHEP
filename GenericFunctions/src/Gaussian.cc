// -*- C++ -*-
// $Id: Gaussian.cc,v 1.3 2003/08/13 20:00:10 garren Exp $
#include "CLHEP/GenericFunctions/defs.h"
#include "CLHEP/GenericFunctions/Gaussian.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include <assert.h>
#include <cmath>	// for exp()

namespace Genfun {

FUNCTION_OBJECT_IMP(Gaussian)

Gaussian::Gaussian():
  _mean("Mean", 0.0,-10,10),
  _sigma("Sigma",1.0,0, 10)
{}

Gaussian::~Gaussian() {
}

Gaussian::Gaussian(const Gaussian & right):
_mean(right._mean),
_sigma(right._sigma)
{
}

double Gaussian::operator() (double x) const {
  double s   = _sigma.getValue();
  double x0  = _mean.getValue();
  return (1.0/(sqrt(CLHEP::twopi)*s))*
	  exp(-(x-x0)*(x-x0)/(2.0*s*s));
}

Parameter & Gaussian::mean() {
  return _mean;
}

Parameter & Gaussian::sigma() {
  return _sigma;
}

const Parameter & Gaussian::mean() const {
  return _mean;
}

const Parameter & Gaussian::sigma() const {
  return _sigma;
}



Derivative Gaussian::partial(unsigned int index) const {
  assert(index==0);
  Variable x;
  const AbsFunction & fPrime  = (*this)*(_mean-x)/_sigma/_sigma;
  return Derivative(&fPrime);
}

} // namespace Genfun
