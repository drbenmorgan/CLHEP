// -*- C++ -*-
// $Id: LogGamma.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
//---------------------Logarithm of Gamma Function--------------------------//
//                                                                          //
// Class LogGamma                                                           //
// Joe Boudreau October 2K                                                  //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef LogGamma_h
#define LogGamma_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class LogGamma : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(LogGamma)
      
      public:
    
    // Constructor
    LogGamma();
    
    // Copy constructor
    LogGamma(const LogGamma &right);
    
    // Destructor
    virtual ~LogGamma();
    
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
    
    // Get the sigma
    Parameter & sigma(); 
    
  private:
    
    // It is illegal to assign an adjustable constant
    const LogGamma & operator=(const LogGamma &right);

    // Constants used in evaluating the function call:
    static const double _coefficient[6];
    
  };
} // namespace Genfun
#endif