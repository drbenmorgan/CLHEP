// -*- C++ -*-
// $Id: Variable.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/Variable.hh"
#include "CLHEP/GenericFunctions/FixedConstant.hh"
#include <assert.h>
namespace Genfun {
FUNCTION_OBJECT_IMP(Variable)

Variable::Variable(unsigned int selectionIndex, unsigned int dimensionality):
  _selectionIndex(selectionIndex),
  _dimensionality(dimensionality)
{}

Variable::Variable(const Variable & right):
  _selectionIndex(right._selectionIndex),
  _dimensionality(right._dimensionality)
{
}

Variable::~Variable() {
}

double Variable::operator() (double x) const {
  assert (_selectionIndex==0);
  return x;
}

double Variable::operator () (const Argument & a) const {
  assert (_selectionIndex<a.dimension());
  return a[_selectionIndex];
}

unsigned int Variable::index() const {
  return _selectionIndex;
}


Derivative Variable::partial(unsigned int index) const {
  int kroneckerDelta = index==_selectionIndex ? 1 : 0;
  const AbsFunction & fPrime = FixedConstant(kroneckerDelta);
  return Derivative(&fPrime);
}

unsigned int Variable::dimensionality() const {
  return _dimensionality;
} 

} // namespace Genfun
