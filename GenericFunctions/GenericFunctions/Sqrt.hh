// -*- C++ -*-
// $Id: Sqrt.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//----------------------Sqrt--------- --------------------------------------//
//                                                                          //
//  Class Sqrt                                                              //
//  Joe Boudreau, Petar Maksimovic, Nov. 1999                               //
//                                                                          //
//  Sqrt is a function that returns the square root of the argument         //
//--------------------------------------------------------------------------//
#ifndef Sqrt_h
#define Sqrt_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Sqrt : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Sqrt)
  
      public:

    // Constructor
    Sqrt();
  
    // Copy constructor
    Sqrt(const Sqrt &right);
  
    // Destructor
    virtual ~Sqrt();
  
    // Retrieve function value
    virtual double operator ()(double argument) const override; 
    virtual double operator ()(const Argument & a) const override {return operator() (a[0]);}
  
    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}

  private:

    // It is illegal to assign a fixed constant
    const Sqrt & operator=(const Sqrt &right);

  };
} // namespace Genfun
#endif


