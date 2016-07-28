// -*- C++ -*-
// $Id: Gaussian.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Gaussian---------------------------------------------//
//                                                                          //
// Class Gaussian                                                           //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Gaussian_h
#define Gaussian_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Gaussian : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Gaussian)

      public:

    // Constructor
    Gaussian();

    // Copy constructor
    Gaussian(const Gaussian &right);
  
    // Destructor
    virtual ~Gaussian();
  
    // Retreive function value
    virtual double operator ()(double argument) const override;
    virtual double operator ()(const Argument & a) const override {return operator() (a[0]);}
  
    // Get the mean of the Gaussian
    Parameter & mean(); 
    const Parameter & mean() const; 

    // Get the sigma of the Gaussian
    Parameter & sigma();
    const Parameter & sigma() const;

    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}

  
  private:

    // It is illegal to assign an adjustable constant
    const Gaussian & operator=(const Gaussian &right);

    // Here is the decay constant
    Parameter _mean;

    // Here is the sigma
    Parameter _sigma;
  };
} // namespace Genfun

#endif
