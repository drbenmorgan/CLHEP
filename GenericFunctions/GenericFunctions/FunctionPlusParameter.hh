// -*- C++ -*-
// $Id: FunctionPlusParameter.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
//--------------------------FunctionPlusParameter---------------------------//
//                                                                          //
// ConstOverFunction, result of adding a function and a parameter           //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef FunctionPlusParameter_h
#define FunctionPlusParameter_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {
  
  /**
   * @author
   * @ingroup genfun
   */
  class FunctionPlusParameter : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(FunctionPlusParameter)
      
      public:
    
    // Constructor
    FunctionPlusParameter(const AbsParameter *parameter, const AbsFunction *function);
  
    // Copy constructor
    FunctionPlusParameter(const FunctionPlusParameter &right);

    // Destructor
    virtual ~FunctionPlusParameter();
  
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

    // It is illegal to assign a FunctionPlusParameter
    const FunctionPlusParameter & operator=(const FunctionPlusParameter &right);

    const AbsFunction  *_function;
    AbsParameter       *_parameter;

  };
} // namespace Genfun
#endif
