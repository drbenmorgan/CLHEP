// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/EfficiencyFunctional.hh"
#include "CLHEP/GenericFunctions/Argument.hh"
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include <iostream>
#include <cmath>      // for log()

namespace Genfun {
EfficiencyFunctional::EfficiencyFunctional(const ArgumentList & aList):
_aList(aList)
{}

EfficiencyFunctional::~EfficiencyFunctional() {
}

double EfficiencyFunctional::operator [] (const AbsFunction & function) const {
  double logEfficiency(0);
  for (unsigned int i=0; i<_aList.size()-1;i++) {
    Argument a = _aList[i];
    Argument b(a.dimension()-1);
    for (unsigned int j=0;j<b.dimension();j++) b[j]=a[j];
    double f = function(b);
    if (f<0 || f>1) {
      std::cerr
	<< "Warning.. negative likelihood arg[" << i << "]=" << a << "f=" << f	<< std::endl;
    }
    logEfficiency -= (a[a.dimension()-1]>0.5) ?  log(f):log(1-f);
  }
  return 2.0*logEfficiency;
}
} // namespace Genfun
