// -*- C++ -*-
// $Id: FunctionTimesParameter.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionTimesParameter--------------------------//
//                                                                          //
// ConstOverFunction, result of multiplying a function and a parameter      //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef FunctionTimesParameter_h
#define FunctionTimesParameter_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionTimesParameter : public AbsFunction  {

    FUNCTION_OBJECT_DEF(FunctionTimesParameter)
  
      public:
  
    // Constructor
    FunctionTimesParameter(const AbsParameter *parameter, const AbsFunction *function);
  
    // Copy constructor
    FunctionTimesParameter(const FunctionTimesParameter &right);

    // Destructor
    virtual ~FunctionTimesParameter();
  
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

    // It is illegal to assign a FunctionTimesParameter
    const FunctionTimesParameter & operator=(const FunctionTimesParameter &right);

    const AbsFunction  *_function;
    AbsParameter       *_parameter;

  };
} // namespace Genfun
#endif
