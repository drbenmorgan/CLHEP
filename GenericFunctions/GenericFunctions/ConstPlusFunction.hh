// -*- C++ -*-
// $Id: ConstPlusFunction.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ConstPlusFunction-------------------------------//
//                                                                          //
// ConstPlusFunction, result of adding a function and a constant            //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ConstPlusFunction_h
#define ConstPlusFunction_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ConstPlusFunction : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ConstPlusFunction)
  
      public:
  
    // Constructor
    ConstPlusFunction(double constant, const AbsFunction *arg);
  
    // Copy constructor
    ConstPlusFunction(const ConstPlusFunction &right);

    // Destructor
    virtual ~ConstPlusFunction();
  
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

    // It is illegal to assign a ConstPlusFunction
    const ConstPlusFunction & operator=(const ConstPlusFunction &right);

    double             _constant;
    const AbsFunction *_arg;
  };
} // namespace Genfun
#endif
