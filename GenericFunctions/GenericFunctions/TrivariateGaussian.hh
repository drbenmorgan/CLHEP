// -*- C++ -*-
// $Id: TrivariateGaussian.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------TrivariateGaussian-----------------------------------//
//                                                                          //
// Class TrivariateGaussian                                                 //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef TrivariateGaussian_h
#define TrivariateGaussian_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class TrivariateGaussian : public AbsFunction  {

    FUNCTION_OBJECT_DEF(TrivariateGaussian)

      public:

    // Constructor
    TrivariateGaussian();

    // Copy constructor
    TrivariateGaussian(const TrivariateGaussian &right);
  
    // Destructor
    virtual ~TrivariateGaussian();
  
    // Retreive function value
    virtual double operator ()(double argument) const;    // Gives an error.
    virtual double operator ()(const Argument & a) const; // Must use this one

    // Dimensionality
    virtual unsigned int dimensionality() const;

    // Get the mean of the TrivariateGaussian
    Parameter & mean0(); 
    const Parameter & mean0() const; 
    Parameter & mean1(); 
    const Parameter & mean1() const; 
    Parameter & mean2(); 
    const Parameter & mean2() const; 

    // Get the sigma of the TrivariateGaussian
    Parameter & sigma0();
    const Parameter & sigma0() const;
    Parameter & sigma1();
    const Parameter & sigma1() const;
    Parameter & sigma2();
    const Parameter & sigma2() const;
  
    // Get the correlation coefficient:
    Parameter & corr01();
    const Parameter & corr01() const;
    Parameter & corr02();
    const Parameter & corr02() const;
    Parameter & corr12();
    const Parameter & corr12() const;
    

  private:

    // It is illegal to assign an adjustable constant
    const TrivariateGaussian & operator=(const TrivariateGaussian &right);

    // Here is the decay constant
    Parameter _mean0;
    Parameter _mean1;
    Parameter _mean2;
    
    // Here is the sigma
    Parameter _sigma0;
    Parameter _sigma1;
    Parameter _sigma2;

    // Here is the correlation coefficient:
    Parameter _corr01;
    Parameter _corr02;
    Parameter _corr12;

  };
} // namespace Genfun

#endif
