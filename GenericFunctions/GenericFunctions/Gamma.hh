// -*- C++ -*-
// $Id: 
//---------------------Gamma------------------------------------------------//
//                                                                          //
// The                   //
// Joe Boudreau, Jan 2007                                                   //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Gamma_h
#define Gamma_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/LogGamma.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Gamma : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(Gamma)
      
      public:
    
    // Constructor
    Gamma();
    
    // Copy constructor
    Gamma(const Gamma &right);
    
    // Destructor
    virtual ~Gamma();
    
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
    
  private:
    
    // It is illegal to assign an adjustable constant
    const Gamma & operator=(const Gamma &right);
    
    // This function has a LogGamma Function;
    LogGamma _logGamma;

    
  };
} // namespace Genfun
#endif
