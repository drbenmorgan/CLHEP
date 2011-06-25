// -*- C++ -*-
// $Id: 
//---------------------NonrelativisticBWDistribution------------------------//
//                                                                          //
//                                                                          //
// Joe Boudreau, June 2011                                                  //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef NonrelativisticBWDistribution_h
#define NonrelativisticBWDistribution_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/IncompleteGamma.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class NonrelativisticBWDistribution : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(NonrelativisticBWDistribution)
      
      public:
    
    // Constructor
    NonrelativisticBWDistribution();
    
    // Copy constructor
    NonrelativisticBWDistribution(const NonrelativisticBWDistribution &right);
    
    // Destructor
    virtual ~NonrelativisticBWDistribution();
    
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
    
    // Get the paramter alpha
    Parameter & mass(); 

    // Get the parameter beta
    Parameter & width(); 

    
  private:
    
    // It is illegal to assign an adjustable constant
    const NonrelativisticBWDistribution & operator=(const NonrelativisticBWDistribution &right);
    
    // Here are the two parameters alpha and beta:

    Parameter       _mass;
    Parameter       _width;



  };
} // namespace Genfun
#endif
