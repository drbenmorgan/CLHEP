// -*- C++ -*-
// $Id: BivariateGaussian.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------BivariateGaussian------------------------------------//
//                                                                          //
// Class BivariateGaussian                                                  //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef BivariateGaussian_h
#define BivariateGaussian_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class BivariateGaussian : public AbsFunction  {

    FUNCTION_OBJECT_DEF(BivariateGaussian)

      public:

    // Constructor
    BivariateGaussian();

    // Copy constructor
    BivariateGaussian(const BivariateGaussian &right);
  
    // Destructor
    virtual ~BivariateGaussian();
  
    // Retreive function value
    virtual double operator ()(double argument) const;    // Gives an error.
    virtual double operator ()(const Argument & a) const; // Must use this one

    // Dimensionality
    virtual unsigned int dimensionality() const;

    // Get the mean of the BivariateGaussian
    Parameter & mean0(); 
    const Parameter & mean0() const; 
    Parameter & mean1(); 
    const Parameter & mean1() const; 

    // Get the sigma of the BivariateGaussian
    Parameter & sigma0();
    const Parameter & sigma0() const;
    Parameter & sigma1();
    const Parameter & sigma1() const;
  
    // Get the correlation coefficient:
    Parameter & corr01();
    const Parameter & corr01() const;
    

  private:

    // It is illegal to assign an adjustable constant
    const BivariateGaussian & operator=(const BivariateGaussian &right);

    // Here is the decay constant
    Parameter _mean0;
    Parameter _mean1;
    
    // Here is the sigma
    Parameter _sigma0;
    Parameter _sigma1;

    // Here is the correlation coefficient:
    Parameter _corr01;

  };
} // namespace Genfun

#endif
