// $Id: 
// -*- C++ -*-
//
#include "CLHEP/GenericFunctions/Abs.hh"
#include <math.h>

namespace Genfun {

FUNCTION_OBJECT_IMP(Abs)

Abs::Abs()
{}

Abs::Abs(const Abs & right)
{
}

Abs::~Abs() {
}

double Abs::operator() (double x) const {
  return fabs(x);
}

}

