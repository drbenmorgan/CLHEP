// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/ArrayFunction.hh"

namespace Genfun {

FUNCTION_OBJECT_IMP(ArrayFunction)
  
// Constructor
ArrayFunction::ArrayFunction(const double *begin, const double *end) :
  _values(begin,end) {}
  
// Destructor
ArrayFunction::~ArrayFunction(){}
  
// Copy constructor
ArrayFunction::ArrayFunction(const ArrayFunction &right):
  _values(right._values) {}
  
  // Retreive function value
double ArrayFunction::operator ()(double argument) const {
  int i =  int (argument+0.5);
  if (i<0 || i>=int(_values.size())) return 0;
  else return _values[i];
}

}
