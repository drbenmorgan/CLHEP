// -*- C++ -*-
// $Id: ASin.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/ASin.hh"
#include "CLHEP/GenericFunctions/Sqrt.hh"
#include "CLHEP/GenericFunctions/Square.hh"
#include <iostream>
#include <assert.h>
#include <cmath>	// for asin()

namespace Genfun {
FUNCTION_OBJECT_IMP(ASin)

ASin::ASin()
{}

ASin::~ASin() {
}

ASin::ASin(const ASin & right) 
{  }


double ASin::operator() (double x) const {
  return asin(x);
}



Derivative ASin::partial(unsigned int index) const {
  assert(index==0);

  Square square;
  Sqrt   root;

  const AbsFunction & fPrime =  1.0/root(1.0-square) ;
  return Derivative(& fPrime);
}

} // end namespace Genfun 
