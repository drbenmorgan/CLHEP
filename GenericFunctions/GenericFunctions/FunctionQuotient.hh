// -*- C++ -*-
// $Id: FunctionQuotient.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionQuotient--------------------------------//
//                                                                          //
// FunctionProduct, result of multiplication of two functions.              //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef FunctionQuotient_h
#define FunctionQuotient_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionQuotient : public AbsFunction {

    FUNCTION_OBJECT_DEF(FunctionQuotient)

      public:

    // Constructor
    FunctionQuotient(const AbsFunction *arg1, const AbsFunction *arg2);

    // Copy constructor
    FunctionQuotient(const FunctionQuotient &right);
  
    // Destructor
    virtual ~FunctionQuotient();
  
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
  
    // It is illegal to assign a FunctionQuotient
    const FunctionQuotient & operator=(const FunctionQuotient &right);
  
    const AbsFunction *_arg1;
    const AbsFunction *_arg2;
  };
} // namespace Genfun
#endif
