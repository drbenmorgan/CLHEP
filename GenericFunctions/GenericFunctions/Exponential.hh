// -*- C++ -*-
// $Id: Exponential.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Exponential------------------------------------------//
//                                                                          //
// Class Exponential                                                        //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Exponential_h
#define Exponential_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Exponential : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Exponential)

      public:

    // Constructor
    Exponential();

    // Copy constructor
    Exponential(const Exponential &right);
  
    // Destructor
    virtual ~Exponential();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Get the decay constant
    Parameter & decayConstant(); 
    const Parameter & decayConstant() const; 
  
    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}

  private:

    // It is illegal to assign an adjustable constant
    const Exponential & operator=(const Exponential &right);

    // Here is the decay constant
    Parameter _decayConstant;

  };
} // namespace Genfun
#endif
