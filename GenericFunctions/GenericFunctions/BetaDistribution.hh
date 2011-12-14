// -*- C++ -*-
// $Id: 
//---------------------BetaDistribution-------------------------------------//
//                                                                          //
// Class Beta, x^(a-1)(1-x)^beta-1 Gamma(a+b)/Gamma(a)/Gamma(b);            //
// Joe Boudreau, Jan 2007                                                   //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef BetaDistribution_h
#define BetaDistribution_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/LogGamma.hh"
#define _BETADISTRIBUTION_REVISED_ 1
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class BetaDistribution : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(BetaDistribution)
      
      public:
    
    // Constructor
    BetaDistribution();
    
    // Copy constructor
    BetaDistribution(const BetaDistribution &right);
    
    // Destructor
    virtual ~BetaDistribution();
    
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
    
    // Get the paramter alpha
    Parameter & alpha(); 

    // Get the paramter alpha
    Parameter & beta(); 
    
  private:
    
    // It is illegal to assign an adjustable constant
    const BetaDistribution & operator=(const BetaDistribution &right);
    
    // Here are the two parameters alpha and beta:

    Parameter _alpha;
    Parameter _beta;


    // This function has a LogGamma Function;
    LogGamma _logGamma;

    
  };
} // namespace Genfun
#endif
