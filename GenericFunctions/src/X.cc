// -*- C++ -*-
// $Id: X.cc,v 1.2 2003/08/13 20:00:10 garren Exp $
#include "CLHEP/GenericFunctions/defs.h"
#include "CLHEP/GenericFunctions/X.hh"

namespace Genfun {
FUNCTION_OBJECT_IMP(X_)

X_::X_()
{}

X_::X_(const X_ & right)
{
}

X_::~X_() {
}

double X_::operator() (double x) const {
  return x;
}

} // namespace Genfun
