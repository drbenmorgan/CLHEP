// -*- C++ -*-
// $Id: ConstTimesFunction.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ConstOverFunction-------------------------------//
//                                                                          //
// ConstOverFunction, result of multiplying a constant and a function       //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ConstTimesFunction_h
#define ConstTimesFunction_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ConstTimesFunction : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ConstTimesFunction)
  
      public:
  
    // Constructor
    ConstTimesFunction(double constant, const AbsFunction *arg);
  
    // Copy constructor
    ConstTimesFunction(const ConstTimesFunction &right);

    // Destructor
    virtual ~ConstTimesFunction();
  
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

    // It is illegal to assign a ConstTimesFunction
    const ConstTimesFunction & operator=(const ConstTimesFunction &right);

    double             _constant;
    const AbsFunction *_arg;
  };
} // namespace Genfun
#endif
