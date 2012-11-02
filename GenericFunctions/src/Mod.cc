// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/Mod.hh"
#include <cmath>
#include <limits.h>
namespace Genfun {
FUNCTION_OBJECT_IMP(Mod)

Mod::Mod(double y):
    _y(y)
{}

Mod::Mod(const Mod & right)
  : AbsFunction(right), _y(right._y)
{}

Mod::~Mod() {
}


// HAD BEEN:
// double Mod::operator() (double x) const {
//  return drem_local(x-_y/2.0,_y) + _y/2.0;
//}

double Mod::operator() (double x) const {
  return (x - _y*floor(x/_y));
}

} // namespace Genfun
