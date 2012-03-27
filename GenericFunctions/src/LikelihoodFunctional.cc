// -*- C++ -*-
// $Id: LikelihoodFunctional.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
#include "CLHEP/GenericFunctions/LikelihoodFunctional.hh"
#include "CLHEP/GenericFunctions/Argument.hh"
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>      // for log()

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
    if (f<=0.0) {
      std::ostringstream stream;
      stream <<  "Negative likelihood arg[" << i << "]=" << a;
      throw std::runtime_error(stream.str());
    }
    logLikelihood -= log(f);
  }
  return 2.0*logLikelihood;
}
} // namespace Genfun
