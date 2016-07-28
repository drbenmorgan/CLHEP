// -*- C++ -*-
// $Id: FunctionNoop.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionNoop------------------------------------//
//                                                                          //
// Class FunctionNoop, output of the unary + operator:                      //
// Joe Boudreau, February 2001                                              //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef FunctionNoop_h
#define FunctionNoop_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */ 
 class FunctionNoop : public AbsFunction {
  
    FUNCTION_OBJECT_DEF(FunctionNoop)

      public:

    // Constructor
    FunctionNoop(const AbsFunction *arg1);
  
    // Copy constructor.
    FunctionNoop(const FunctionNoop &right);
  
    // Destructor
    virtual ~FunctionNoop();
  
    // Retreive function value
    virtual double operator ()(double argument) const override;
    virtual double operator ()(const Argument & a) const override;
  
    // Dimensionality 
    virtual unsigned int dimensionality() const override;

    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}

  private:
  
    // It is illegal to assign a FunctionNoop
    const FunctionNoop & operator=(const FunctionNoop &right);

    // The function we're negating.  
    const AbsFunction *_arg1;
  };
} // namespace Genfun
#endif
