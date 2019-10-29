// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/LogisticFunction.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <assert.h>
#define MAXRANGE 1000

namespace Genfun {
FUNCTION_OBJECT_IMP(LogisticFunction)

LogisticFunction::LogisticFunction():
  _x0("X0", 0.0,0.0,1.0),
  _a("A",2.0,1.0, 4.0)
{}

LogisticFunction::~LogisticFunction() {
}

LogisticFunction::LogisticFunction(const LogisticFunction & right):
AbsFunction(right),
_x0(right._x0),
_a(right._a)
{
}

double LogisticFunction::operator() (double x) const {
  int i  = (int) (x+0.5), &back = i, end=back+1;

  if (i<0 || i>MAXRANGE) {
    return 0;
  }
  else {
    // Is the vector of values stale?
    if (__a!=_a.getValue() || __x0!=_x0.getValue()) {

      // Empty the vector
      fx.erase(fx.begin(),fx.end());

      // And update the cache.
      __a  = _a.getValue(); 
      __x0 = _x0.getValue();
      
    }
    

    if (fx.empty()) fx.push_back(__x0);

    while (fx.size()<size_t(end)) {
      double v = fx.back();
      fx.push_back(__a*v*(1.0-v));
    }
    
    return fx[i];
  }

  
}

Parameter & LogisticFunction::x0() {
  return _x0;
}

Parameter & LogisticFunction::a() {
  return _a;
}

const Parameter & LogisticFunction::x0() const {
  return _x0;
}

const Parameter & LogisticFunction::a() const {
  return _a;
}


} // namespace Genfun
