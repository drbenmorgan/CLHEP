// -*- C++ -*-
// $Id: X.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
#include "GenericFunctions/defs.h"

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
