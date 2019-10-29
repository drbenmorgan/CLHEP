// -*- C++ -*-
// $Id: AssociatedLaguerre.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/AssociatedLaguerre.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include "CLHEP/GenericFunctions/FixedConstant.hh"

namespace Genfun {
FUNCTION_OBJECT_IMP(AssociatedLaguerre)

// This is the product n (n-2) (n-4)... 
inline double factorial (int n) {
  if (n<=1) return 1.0;
  else return n*factorial(n-1);
}

AssociatedLaguerre::AssociatedLaguerre(unsigned int xn, unsigned int xk):
  _n(xn),
  _k(xk)
{
  create();
}

AssociatedLaguerre::~AssociatedLaguerre() {
  delete _function;
}

AssociatedLaguerre::AssociatedLaguerre(const AssociatedLaguerre & right):
AbsFunction(right),
_n(right._n),
_k(right._k)
{
  create();
}

double AssociatedLaguerre::operator() (double x) const {
  return (*_function)(x);
}

unsigned int AssociatedLaguerre::n() const {
  return _n;
}

unsigned int AssociatedLaguerre::k() const {
  return _k;
}


void AssociatedLaguerre::create() {
  Variable     x;
  if (_n==0) {
    _function = FixedConstant(1.0).clone();
  }
  else if (_n==1) {
    _function = (-x + _k + 1).clone();
  }
  else {
    _function = ((1.0/_n)*((2*_n -1 +_k -x)*AssociatedLaguerre(_n-1,_k)
			 -  (_n+_k-1)*AssociatedLaguerre(_n-2,_k))).clone();
  }
}
} // namespace Genfun
