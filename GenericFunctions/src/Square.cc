// -*- C++ -*-
// $Id: Square.cc,v 1.2 2003/08/13 20:00:10 garren Exp $
#include "CLHEP/GenericFunctions/defs.h"
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
