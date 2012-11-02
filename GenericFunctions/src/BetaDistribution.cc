// -*- C++ -*-
// $Id: 

#include "CLHEP/GenericFunctions/BetaDistribution.hh"
#include <assert.h>
#include <cmath>
using namespace std;

namespace Genfun {
FUNCTION_OBJECT_IMP(BetaDistribution)


BetaDistribution::BetaDistribution():
  _alpha("a",    1.0, 0.0, 100),
  _beta ("beta", 1.0, 0.0, 100)
{}

BetaDistribution::BetaDistribution(const BetaDistribution & right):
AbsFunction( right ),
_alpha(right._alpha),
_beta (right._beta) 
{
}

BetaDistribution::~BetaDistribution() {
}

double BetaDistribution::operator() (double x) const {
  double a = _alpha.getValue(),b=_beta.getValue();
  return pow(x,a-1)*pow((1-x),b-1)*
    exp(_logGamma(a+b)-_logGamma(a)-_logGamma(b));
  
}

Parameter & BetaDistribution::alpha() {
  return _alpha;
}


Parameter & BetaDistribution::beta() {
  return _beta;
}



} // namespace Genfun
