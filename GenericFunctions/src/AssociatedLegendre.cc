// -*- C++ -*-
// $Id: AssociatedLegendre.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/AssociatedLegendre.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include "CLHEP/GenericFunctions/Power.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(AssociatedLegendre)

// This is the product n (n-2) (n-4)... 
inline double dfactorial (int n) {
  if (n<=1) return 1.0;
  else return n*dfactorial(n-2);
}
//
AssociatedLegendre::AssociatedLegendre(unsigned int l, unsigned int m):
  _l(l),
  _m(m)
{
  assert(m<=l);
  create();
}

AssociatedLegendre::~AssociatedLegendre() {
  delete _function;
}

AssociatedLegendre::AssociatedLegendre(const AssociatedLegendre & right):
_l(right._l),
_m(right._m)
{
  create();
}

double AssociatedLegendre::operator() (double x) const {
  return (*_function)(x);
}

unsigned int AssociatedLegendre::l() const {
  return _l;
}

unsigned int AssociatedLegendre::m() const {
  return _m;
}


void AssociatedLegendre::create() {
  Variable     x;
  if (_l==_m) {
    Power powerMOverTwo(_m/2.0),PowerM(_m);
    _function = (PowerM(-1)*dfactorial(2*_m-1)*powerMOverTwo((1-x)*(1+x))).clone();
  }
  else if (_l==_m+1) {
    _function = (x*(2*_m+1)*AssociatedLegendre(_m,_m)).clone();
  }
  else {
    _function = ((1.0/(_l-_m)) * (x*(2*_l-1)*AssociatedLegendre(_l-1,_m) -(_l+_m-1)*AssociatedLegendre(_l-2,_m))).clone();
  }
}
} // namespace Genfun
