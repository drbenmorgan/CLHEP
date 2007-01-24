// -*- C++ -*-
// $Id: 
//---------------------GammaDistribution------------------------------------//
//                                                                          //
// Class Gamma, x^a * e(-x/b) / (b^(a+1) Gamma(Alpha+1));                   //
// Joe Boudreau, Jan 2007                                                   //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef GammaDistribution_h
#define GammaDistribution_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/LogGamma.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class GammaDistribution : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(GammaDistribution)
      
      public:
    
    // Constructor
    GammaDistribution();
    
    // Copy constructor
    GammaDistribution(const GammaDistribution &right);
    
    // Destructor
    virtual ~GammaDistribution();
    
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
    
    // Get the paramter alpha
    Parameter & alpha(); 

    // Get the paramter alpha
    Parameter & beta(); 
    
  private:
    
    // It is illegal to assign an adjustable constant
    const GammaDistribution & operator=(const GammaDistribution &right);
    
    // Here are the two parameters alpha and beta:

    Parameter _alpha;
    Parameter _beta;


    // This function has a LogGamma Function;
    LogGamma _logGamma;

    
  };
} // namespace Genfun
#endif
