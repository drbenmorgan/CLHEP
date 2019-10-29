// -*- C++ -*-
// $Id: 

#include "CLHEP/GenericFunctions/GammaDistribution.hh"
#include <assert.h>
#include <cmath>
using namespace std;

namespace Genfun {
FUNCTION_OBJECT_IMP(GammaDistribution)


GammaDistribution::GammaDistribution():
  _alpha("a",    2.0, 1.0, 100),
  _beta ("beta", 0.0, 0,   100)
{}

GammaDistribution::GammaDistribution(const GammaDistribution & right):
AbsFunction(right),
_alpha(right._alpha),
_beta (right._beta) 
{
}

GammaDistribution::~GammaDistribution() {
}

double GammaDistribution::operator() (double x) const {
  return std::pow(x,_alpha.getValue()-1)*
    exp(-x/_beta.getValue())/std::pow(_beta.getValue(),(_alpha.getValue()))/
    exp(_logGamma(_alpha.getValue()));

}

Parameter & GammaDistribution::alpha() {
  return _alpha;
}


Parameter & GammaDistribution::beta() {
  return _beta;
}



} // namespace Genfun
