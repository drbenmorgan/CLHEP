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
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}
    
  private:
    
    // It is illegal to assign an adjustable constant
    const Erf & operator=(const Erf &right);
    
    IncompleteGamma _incompleteGamma;
    
  };
} // namespace Genfun
#endif
