// -*- C++ -*-
// $Id: ReverseExponential.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------ReverseExponential-----------------------------------//
//                                                                          //
// Class ReverseExponential..like Exponential but appropriate for describing//
// negative lifetime tails.                                                 //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef ReverseExponential_h
#define ReverseExponential_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ReverseExponential : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ReverseExponential)

      public:

    // Constructor
    ReverseExponential();

    // Copy constructor
    ReverseExponential(const ReverseExponential &right);
  
    // Destructor
    virtual ~ReverseExponential();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Get the decay constant
    Parameter & decayConstant(); 
  
    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}

  private:

    // It is illegal to assign an adjustable constant
    const ReverseExponential & operator=(const ReverseExponential &right);

    // Here is the decay constant
    Parameter _decayConstant;

  };
} // namespace Genfun

#endif
