// -*- C++ -*-
// $Id: 

#include "CLHEP/GenericFunctions/GammaDistribution.hh"
#include <assert.h>
#include <cmath>
using namespace std;

namespace Genfun {
FUNCTION_OBJECT_IMP(GammaDistribution)


GammaDistribution::GammaDistribution():
  _alpha("a",    1.0, 1.0, 100),
  _beta ("beta", 0.0, 0,   100)
{}

GammaDistribution::GammaDistribution(const GammaDistribution & right):
_alpha(right._alpha),
_beta (right._beta) 
{
}

GammaDistribution::~GammaDistribution() {
}

double GammaDistribution::operator() (double x) const {
  return pow(x,_alpha.getValue())*
    exp(-x/_beta.getValue())/pow(_beta.getValue(),(_alpha.getValue()+1))/
    exp(_logGamma(_alpha.getValue()+1));

}

Parameter & GammaDistribution::alpha() {
  return _alpha;
}


Parameter & GammaDistribution::beta() {
  return _beta;
}



} // namespace Genfun
