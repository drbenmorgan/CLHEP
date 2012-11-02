// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/Sigma.hh"
#include <assert.h>

namespace Genfun {
FUNCTION_OBJECT_IMP(Sigma)

void Sigma::accumulate( const AbsFunction & fcn) {
  _fcn.push_back(fcn.clone());
}

Sigma::Sigma()
{
}

Sigma::Sigma(const Sigma & right) : AbsFunction(right)
{
  for (size_t i=0; i<right._fcn.size();i++) {
    _fcn.push_back(right._fcn[i]->clone());
  }
}

unsigned int Sigma::dimensionality() const {
  assert (_fcn.size()!=0);
  return _fcn[0]->dimensionality();
}

Sigma::~Sigma()
{
  for (size_t i=0; i<_fcn.size();i++) {
    delete _fcn[i];
  }
}

double Sigma::operator ()(double x) const
{
  double retVal=0.0;
  for (size_t i=0;i<_fcn.size();i++) retVal += (*_fcn[i])(x);
  return retVal;
}


double Sigma::operator ()(const Argument & x) const
{
  double retVal=0.0;
  for (size_t i=0;i<_fcn.size();i++) retVal += (*_fcn[i])(x);
  return retVal;
}



Derivative Sigma::partial(unsigned int index) const {
  Sigma fPrime;
  for (size_t i=0;i<_fcn.size();i++) {
    fPrime.accumulate(_fcn[i]->partial(index));
  }
  return Derivative(&fPrime);
}



} // namespace Genfun
