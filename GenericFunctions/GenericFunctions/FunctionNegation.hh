// -*- C++ -*-
// $Id: FunctionNegation.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionNegation--------------------------------//
//                                                                          //
// Class FunctionNegation, output of the unary - operator                   //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef FunctionNegation_h
#define FunctionNegation_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionNegation : public AbsFunction {
  
    FUNCTION_OBJECT_DEF(FunctionNegation)

      public:

    // Constructor
    FunctionNegation(const AbsFunction *arg1);
  
    // Copy constructor.
    FunctionNegation(const FunctionNegation &right);
  
    // Destructor
    virtual ~FunctionNegation();
  
    // Retreive function value
    virtual double operator ()(double argument) const override;
    virtual double operator ()(const Argument & argument) const override;
  
    // Dimensionality 
    virtual unsigned int dimensionality() const override;

    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}

  private:
  
    // It is illegal to assign a FunctionNegation
    const FunctionNegation & operator=(const FunctionNegation &right);

    // The function we're negating.  
    const AbsFunction *_arg1;
  };
} // namespace Genfun
#endif
