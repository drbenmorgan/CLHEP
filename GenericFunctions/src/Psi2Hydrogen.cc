// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/Psi2Hydrogen.hh"
#include "CLHEP/GenericFunctions/AssociatedLegendre.hh"
#include "CLHEP/GenericFunctions/AssociatedLaguerre.hh"
#include "CLHEP/GenericFunctions/Power.hh"
#include "CLHEP/GenericFunctions/Exponential.hh"
#include "CLHEP/GenericFunctions/FixedConstant.hh"
#include "CLHEP/GenericFunctions/Psi2Hydrogen.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include "CLHEP/GenericFunctions/Power.hh"
#include <assert.h>
#include <cmath>      // for pow()

namespace Genfun {
FUNCTION_OBJECT_IMP(Psi2Hydrogen)

// This is the product n (n-1) (n-1)... 
inline double factorial (int n) {
  if (n<=1) return 1.0;
  else return n*factorial(n-1);
}

//
Psi2Hydrogen::Psi2Hydrogen(unsigned int n, unsigned int l, unsigned int m):
  _n(n),
  _l(l),
  _m(m)
{
  assert(m<=l);
  create();
}

Psi2Hydrogen::~Psi2Hydrogen() {
  delete _function;
}

Psi2Hydrogen::Psi2Hydrogen(const Psi2Hydrogen & right):
_n(right._n),
_l(right._l),
_m(right._m)
{
  create();
}


double Psi2Hydrogen::operator() (const Argument & a) const {
  assert (a.dimension()==3);
  return (*_function)(a);
}


double Psi2Hydrogen::operator() (double x) const {
  std::cerr
    << "Warning. Psi2Hydrogen called with scalar argument"
    << std::endl;
  assert(0);
  return 0;
}

unsigned int Psi2Hydrogen::n() const {
  return _n;
} 

unsigned int Psi2Hydrogen::l() const {
  return _l;
}

unsigned int Psi2Hydrogen::m() const {
  return _m;
}


void Psi2Hydrogen::create() {
  FixedConstant I(1.0);
  Variable r;
  double asq = pow(2.0/_n, 3.0)*factorial(_n-_l-1)/(2.0*_n*factorial(_n+1));
  GENFUNCTION ar = (2.0/_n)*r;
  AssociatedLegendre P(_l, _m);
  AssociatedLaguerre L(_n-_l-1, 2*_l+1);
  Exponential exp;
  Power pow2L(2*_l);
  
  _function = (asq*exp(ar)*pow2L(ar)*L(ar)*L(ar)%(P*P)%(I*I)).clone();

}
}
