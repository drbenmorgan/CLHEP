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
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}
  
  
  private:

    // It is illegal to assign a Theta
    const Theta & operator=(const Theta &right);

  };
} // namespace Genfun

#endif
