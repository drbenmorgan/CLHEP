// -*- C++ -*-
// $Id: FunctionComposition.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionComposition-----------------------------//
//                                                                          //
// FunctionComposition, result of composition of two functions.             //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef FunctionComposition_h
#define FunctionComposition_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionComposition : public AbsFunction {

    FUNCTION_OBJECT_DEF(FunctionComposition)

      public:

    // Constructor
    FunctionComposition(const AbsFunction *arg1, const AbsFunction *arg2);

    // Copy constructor
    FunctionComposition(const FunctionComposition &right);
  
    // Destructor
    virtual ~FunctionComposition();

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

    // It is illegal to assign a FunctionComposition
    const FunctionComposition & operator=(const FunctionComposition &right);

    const AbsFunction *_arg1;
    const AbsFunction *_arg2;  
  };
} // namespace Genfun
#endif
