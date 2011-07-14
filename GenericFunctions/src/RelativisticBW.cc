#include "CLHEP/GenericFunctions/RelativisticBW.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <assert.h>
#include <cmath>

#if (defined __STRICT_ANSI__) || (defined _WIN32)
#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif // M_PI
#endif // __STRICT_ANSI__

using namespace std;

namespace Genfun {
FUNCTION_OBJECT_IMP(RelativisticBWDistribution)


RelativisticBWDistribution::RelativisticBWDistribution():
  _mass("mass",    50, 10, 90),
  _width ("width", 5, 0,   100)
{}

  RelativisticBWDistribution::RelativisticBWDistribution(const RelativisticBWDistribution & right):
    AbsFunction(),
    _mass(right._mass),
    _width (right._width)
{
}

RelativisticBWDistribution::~RelativisticBWDistribution() {
}

double RelativisticBWDistribution::operator() (double x) const {
  double M=_mass.getValue();
  double G=_width.getValue();
  double g=sqrt(M*M*(M*M+G*G));
  double k = 2.0*sqrt(2.0)*M*G*g/M_PI/sqrt(M*M+g);
  double f = k/((x-M)*(x-M)*(x+M)*(x+M)+M*M*G*G);
  return f;

}

Parameter & RelativisticBWDistribution::mass() {
  return _mass;
}


Parameter & RelativisticBWDistribution::width() {
  return _width;
}


} // namespace Genfun
