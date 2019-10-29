// -*- C++ -*-
// $Id: Erf.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Erf--------------------------------------------------//
//                                                                          //
// Class Erf                                                                //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Erf_h
#define Erf_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/IncompleteGamma.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Erf : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(Erf)
      
      public:
    
    // Constructor
    Erf();
    
    // Copy constructor
    Erf(const Erf &right);
    
    // Destructor
    virtual ~Erf();
    
    // Retreive function value
    virtual double operator ()(double argument) const override;
    virtual double operator ()(const Argument & a) const override {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}
    
  private:
    
    // It is illegal to assign an adjustable constant
    const Erf & operator=(const Erf &right);
    
    IncompleteGamma _incompleteGamma;
    
  };
} // namespace Genfun
#endif
