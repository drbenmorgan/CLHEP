// -*- C++ -*-
// $Id: FunctionDifference.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionDifference------------------------------//
//                                                                          //
// FunctionDifference, result of subtraction of two functions               //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef FunctionDifference_h
#define FunctionDifference_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionDifference : public AbsFunction {

    FUNCTION_OBJECT_DEF(FunctionDifference)
  
      public:

    // Constructor
    FunctionDifference(const AbsFunction* arg1, const AbsFunction *arg2);
  
    // Copy constructor
    FunctionDifference(const FunctionDifference &right);
  
    // Destructor
    virtual ~FunctionDifference();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const;
  
    // Dimensionality 
    virtual unsigned int dimensionality() const;

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}

  private:
  
    // It is illegal to assign a FunctionDifference
    const FunctionDifference & operator=(const FunctionDifference &right);

    const AbsFunction *_arg1;
    const AbsFunction *_arg2;

  };
} // namespace Genfun
#endif
