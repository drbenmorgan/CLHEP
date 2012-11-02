// -*- C++ -*-
// $Id: ATan.cc,v 1.4 2003/10/10 17:40:39 garren Exp $ 
#include "CLHEP/GenericFunctions/ATan.hh"
#include "CLHEP/GenericFunctions/Square.hh"
#include <assert.h>
#include <cmath>      // for atan()

namespace Genfun {
FUNCTION_OBJECT_IMP(ATan)

ATan::ATan()
{}

ATan::~ATan() {
}

ATan::ATan(const ATan & right) : AbsFunction(right)
{  }


double ATan::operator() (double x) const {
  return atan(x);
}



Derivative ATan::partial(unsigned int index) const {
  assert(index==0);

  Square square;
  
  const AbsFunction & fPrime=1.0/(1.0+square);;
  return Derivative(& fPrime);
}

} // end namespace Genfun 
