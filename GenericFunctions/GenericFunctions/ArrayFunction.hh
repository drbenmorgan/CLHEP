// -*- C++ -*-
// $Id: 
#ifndef _ArrayFunction_h_
#define _ArrayFunction_h_
//-------------------------------------------------------//
// This one dimensional function takes its values from   //
// an array..which it copies in.                         //
//-------------------------------------------------------//


#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include <vector>
namespace Genfun {
class ArrayFunction : public AbsFunction  {
  
  FUNCTION_OBJECT_DEF(ArrayFunction)
    
    public:
  
  // Constructor
  ArrayFunction(const double *begin, const double *end);
  
  // Destructor
  virtual ~ArrayFunction();
  
  // Copy constructor
  ArrayFunction(const ArrayFunction &right);
  
  // Retreive function value
  virtual double operator ()(double argument) const;
  virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
 private:
  
  // It is illegal to assign a ArrayFunction
  const ArrayFunction & operator=(const ArrayFunction &right);

  std::vector<double> _values;
};
}
#endif
