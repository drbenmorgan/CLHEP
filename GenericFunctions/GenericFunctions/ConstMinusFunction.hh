// -*- C++ -*-
// $Id: ConstMinusFunction.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ConstMinusFunction------------------------------//
//                                                                          //
// ConstMinusFunction, result of subtracting a function from constant       //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ConstMinusFunction_h
#define ConstMinusFunction_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ConstMinusFunction : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ConstMinusFunction)
  
      public:
  
    // Constructor
    ConstMinusFunction(double constant, const AbsFunction *arg);
  
    // Copy constructor
    ConstMinusFunction(const ConstMinusFunction &right);

    // Destructor
    virtual ~ConstMinusFunction();
  
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

    // It is illegal to assign a ConstMinusFunction
    const ConstMinusFunction & operator=(const ConstMinusFunction &right);

    double             _constant;
    const AbsFunction *_arg;
  };
} // namespace Genfun
#endif
