// -*- C++ -*-
// $Id: LogGamma.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
// ---------------------------------------------------------------------------

#include "CLHEP/GenericFunctions/LogGamma.hh"
#include <cmath>      // for log()

namespace Genfun {
FUNCTION_OBJECT_IMP(LogGamma)

const double LogGamma::_coefficient[6]={
  +76.18009172947146,
  -86.50532032941677,
  +24.01409824083091,
  -1.231739572450155,
  0.1208650973866179E-2,
  -0.5395239384953E-5};

LogGamma::LogGamma()
{}

LogGamma::LogGamma(const LogGamma & right) : AbsFunction(right)
{}

LogGamma::~LogGamma() {
}

double LogGamma::operator() (double x) const {
  double y=x,tmp=x+5.5,ser=1.000000000190015,c=2.5066282746310005;
  tmp -= (x+0.5)*log(tmp);
  for (int j=0;j<6;j++) ser += _coefficient[j]/++y;
  return -tmp+log(c*ser/x);
}

} // namespace Genfun
