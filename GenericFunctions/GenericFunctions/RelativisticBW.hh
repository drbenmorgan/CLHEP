// -*- C++ -*-
// $Id: 
//---------------------RelativisticBWDistribution---------------------------//
//                                                                          //
//                                                                          //
// Joe Boudreau, June 2011                                                  //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef RelativisticBWDistribution_h
#define RelativisticBWDistribution_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/IncompleteGamma.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class RelativisticBWDistribution : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(RelativisticBWDistribution)
      
      public:
    
    // Constructor
    RelativisticBWDistribution();
    
    // Copy constructor
    RelativisticBWDistribution(const RelativisticBWDistribution &right);
    
    // Destructor
    virtual ~RelativisticBWDistribution();
    
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
    
    // Get the paramter alpha
    Parameter & mass(); 

    // Get the parameter beta
    Parameter & width(); 

    
  private:
    
    // It is illegal to assign an adjustable constant
    const RelativisticBWDistribution & operator=(const RelativisticBWDistribution &right);
    
    // Here are the two parameters alpha and beta:

    Parameter       _mass;
    Parameter       _width;



  };
} // namespace Genfun
#endif
