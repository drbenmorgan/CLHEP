// -*- C++ -*-
// $Id: FunctionSum.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionSum-------------------------------------//
//                                                                          //
// FunctionSum, result of addition of two functions.                        //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef FunctionSum_h
#define FunctionSum_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionSum : public AbsFunction  {

    FUNCTION_OBJECT_DEF(FunctionSum)
  
      public:
  
    // Constructor
    FunctionSum(const AbsFunction *arg1, const AbsFunction *arg2);
  
    // Copy constructor
    FunctionSum(const FunctionSum &right);

    // Destructor
    virtual ~FunctionSum();
  
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

    // It is illegal to assign a FunctionSum
    const FunctionSum & operator=(const FunctionSum &right);

    const AbsFunction *_arg1;
    const AbsFunction *_arg2;
  };
} // namespace Genfun
#endif
