// -*- C++ -*-
// $Id: 
//---------------------VoigtProfile----------------------------------------//
//                                                                          //
//                                                                          //
// Joe Boudreau, June 2011                                                  //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef VoigtProfile_h
#define VoigtProfile_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/IncompleteGamma.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class VoigtProfile : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(VoigtProfile)
      
      public:
    
    // Constructor
    VoigtProfile();
    
    // Copy constructor
    VoigtProfile(const VoigtProfile &right);
    
    // Destructor
    virtual ~VoigtProfile();
    
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
    
    // Get the paramter alpha
    Parameter & mass(); 

    // Get the parameter beta
    Parameter & width(); 

    // Get the parameter beta
    Parameter & sigma(); 

    
  private:
    
    // It is illegal to assign an adjustable constant
    const VoigtProfile & operator=(const VoigtProfile &right);
    
    // Here are the two parameters alpha and beta:

    Parameter       _mass;
    Parameter       _width;
    Parameter       _sigma;


  };
} // namespace Genfun
#endif
