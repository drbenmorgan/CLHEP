// -*- C++ -*-
// $Id: LikelihoodFunctional.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
#include "GenericFunctions/defs.h"

#include "CLHEP/GenericFunctions/LikelihoodFunctional.hh"
#include "CLHEP/GenericFunctions/Argument.hh"
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include <iostream>
#include <cmath>	// for log()

namespace Genfun {
LikelihoodFunctional::LikelihoodFunctional(const ArgumentList & aList):
_aList(aList)
{}

LikelihoodFunctional::~LikelihoodFunctional() {
}

double LikelihoodFunctional::operator [] (const AbsFunction & function) const {
  double logLikelihood(0);
  for (unsigned int i=0; i<_aList.size();i++) {
    Argument a = _aList[i];
    double f = function(a);
    if (f<0)
      std::cerr
	<< "Warning.. negative likelihood arg[" << i << "]=" << a 
	<< std::endl;
    logLikelihood -= log(f);
  }
  return 2.0*logLikelihood;
}
} // namespace Genfun
