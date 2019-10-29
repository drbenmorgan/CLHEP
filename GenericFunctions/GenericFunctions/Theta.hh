// -*- C++ -*-
// $Id: 
//---------------------Theta------------------------------------------------//
//                                                                          //
// Class Theta                                                              //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Theta_h
#define Theta_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Theta : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Theta)

      public:

    // Constructor
    Theta();

    // Destructor
    virtual ~Theta();
  
    // Copy constructor
    Theta(const Theta &right);
  
    // Retreive function value
    virtual double operator ()(double argument) const override;
    virtual double operator ()(const Argument & a) const override {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}
  
  
  private:

    // It is illegal to assign a Theta
    const Theta & operator=(const Theta &right);

  };
} // namespace Genfun

#endif
