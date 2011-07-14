#include "CLHEP/GenericFunctions/NonrelativisticBW.hh"
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
FUNCTION_OBJECT_IMP(NonrelativisticBWDistribution)


NonrelativisticBWDistribution::NonrelativisticBWDistribution():
  _mass("mass",    50, 10, 90),
  _width ("width", 5, 0,   100)
{}

  NonrelativisticBWDistribution::NonrelativisticBWDistribution(const NonrelativisticBWDistribution & right):
    AbsFunction(),
    _mass(right._mass),
    _width (right._width)
{
}

NonrelativisticBWDistribution::~NonrelativisticBWDistribution() {
}

double NonrelativisticBWDistribution::operator() (double x) const {
  double M=_mass.getValue();
  double G=_width.getValue()/2.0;
  double f = (1.0/M_PI)*G/((x-M)*(x-M) +G*G);
  return f;

}

Parameter & NonrelativisticBWDistribution::mass() {
  return _mass;
}


Parameter & NonrelativisticBWDistribution::width() {
  return _width;
}


} // namespace Genfun
