// -*- C++ -*-
// $Id: IncompleteGamma.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------IncompleteGamma--------------------------------------//
//                                                                          //
// Class IncompleteGamma, the incomplete Gamma function                     //
// Joe Boudreau, October 2000                                               //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef IncompleteGamma_h
#define IncompleteGamma_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/LogGamma.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class IncompleteGamma : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(IncompleteGamma)
      
      public:
    
    // Constructor
    IncompleteGamma();
    
    // Copy constructor
    IncompleteGamma(const IncompleteGamma &right);
    
    // Destructor
    virtual ~IncompleteGamma();
    
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
    
    // Get the paramter a
    Parameter & a(); 
    
  private:
    
    // It is illegal to assign an adjustable constant
    const IncompleteGamma & operator=(const IncompleteGamma &right);
    
    // Here is the parameter of the Incomplete Gamma Function
    Parameter _a;

    // Compute via series representation:
    double  _gamser(double a, double x, double logGamma) const;
    
    // Compute via continued fraction representation:
    double  _gammcf(double a, double x, double logGamma) const;

    // This function has a LogGamma Function;
    LogGamma _logGamma;

    static const int          ITMAX;
    static const double       EPS;
    static const double       FPMIN;
    
  };
} // namespace Genfun
#endif
