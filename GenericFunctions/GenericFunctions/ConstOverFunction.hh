// -*- C++ -*-
// $Id: ConstOverFunction.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ConstOverFunction-------------------------------//
//                                                                          //
// ConstOverFunction, result of dividing a constant by a function           //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ConstOverFunction_h
#define ConstOverFunction_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ConstOverFunction : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ConstOverFunction)
  
      public:
  
    // Constructor
    ConstOverFunction(double constant, const AbsFunction *arg);
  
    // Copy constructor
    ConstOverFunction(const ConstOverFunction &right);

    // Destructor
    virtual ~ConstOverFunction();
  
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

    // It is illegal to assign a ConstOverFunction
    const ConstOverFunction & operator=(const ConstOverFunction &right);

    double             _constant;
    const AbsFunction *_arg;
  };
} // namespace Genfun

#endif


