// -*- C++ -*-
// $Id: LikelihoodFunctional.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/LikelihoodFunctional.hh"
#include "CLHEP/GenericFunctions/Argument.hh"
#include "CLHEP/GenericFunctions/AbsFunction.hh"

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
