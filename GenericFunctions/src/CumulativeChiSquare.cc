// -*- C++ -*-
// $Id: CumulativeChiSquare.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
// ---------------------------------------------------------------------------

#include "CLHEP/GenericFunctions/CumulativeChiSquare.hh"
#include "CLHEP/GenericFunctions/IncompleteGamma.hh"
#include "CLHEP/GenericFunctions/Variable.hh"

namespace Genfun {
FUNCTION_OBJECT_IMP(CumulativeChiSquare)

//---------------------------------------------------------------------------------//
// Implementation notes:  The Cumulative Chi Square function is implemented in     //
// terms of the incomplete gamma function.                                         //
//---------------------------------------------------------------------------------//

CumulativeChiSquare::CumulativeChiSquare(unsigned int ndf):
  _nDof(ndf)
{
  create();
}

CumulativeChiSquare::~CumulativeChiSquare() {
  delete _function;
}

CumulativeChiSquare::CumulativeChiSquare(const CumulativeChiSquare & right):
AbsFunction(right),
_nDof(right._nDof)
{
  create();
}

double CumulativeChiSquare::operator() (double x) const {
  return (*_function)(x);
}

unsigned int CumulativeChiSquare::nDof() const {
  return _nDof;
}

void CumulativeChiSquare::create() {
  Variable x;
  IncompleteGamma incompleteGamma;
  incompleteGamma.a().setValue(_nDof/2.0);
  _function = (incompleteGamma(x/2.0)).clone();
} 
} // namespace Genfun
