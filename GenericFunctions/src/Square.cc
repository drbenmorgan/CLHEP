// -*- C++ -*-
// $Id: Square.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/Square.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(Square)

Square::Square()
{}

Square::Square(const Square & right)
{
}

Square::~Square() {
}

double Square::operator() (double x) const {
  return x*x;
}



Derivative Square::partial(unsigned int index) const {
  assert(index==0);
  Variable x;
  const AbsFunction & fPrime = 2*x;
  return Derivative(&fPrime);
}


} // namespace Genfun
