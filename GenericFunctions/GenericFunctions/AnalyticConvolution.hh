// -*- C++ -*-
// $Id: AnalyticConvolution.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
// ---------------------------------------------------------------------------//
// This function-object makes analytic convolutions of a gaussian plus either //
// an exponential, or else the function exp * (1+/-cos)                       //
// The choice depends on which constructor is used to build the analytic      //
// convolution and which arguments are used.                                  //
//                                                                            //
// Joe Boudreau, Petar Maksimovic, Hongquan Niu, Craig Blocker                //
//                                                                            //
// ---------------------------------------------------------------------------//
#ifndef _AnalyticConvolution_h_
#define _AnalyticConvolution_h_ 
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include <complex>
namespace Genfun {

  class Gaussian;
  class Exponential;
  class Cosine;

  /**
   * @author
   * @ingroup genfun
   */
  class AnalyticConvolution: public AbsFunction {

    FUNCTION_OBJECT_DEF(AnalyticConvolution)

      public:

    // Flag for mixed or unmixed:
    enum Type       {MIXED          =0,  // PDF for mixed events 
		     UNMIXED        =1,  // PDF for unmixed events
		     SMEARED_EXP    =2,  // Exponential (convolve) Gaussian
		     SMEARED_COS_EXP=3,  // Exponential * Cosine (convolve) Gaussian
                     SMEARED_SIN_EXP=4,  // Exponential * Sine   (convolve) Gaussian
                     SMEARED_NEG_EXP=5}; // Negative exponential (convolve) Gaussian
    // Constructor
    AnalyticConvolution(Type=SMEARED_EXP);

    // Copy constructor
    AnalyticConvolution(const AnalyticConvolution &right);
  
    // Destructor:
    virtual ~AnalyticConvolution();

    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Frequency of oscillation
    Parameter & frequency();
    const Parameter & frequency() const;

    // Lifetime of exponential:
    Parameter & lifetime();
    const Parameter & lifetime() const;

    // Width of the gaussian:
    Parameter & sigma();
    const Parameter & sigma() const;

    // The mean of the gaussian:
    Parameter & offset();
    const Parameter & offset() const;

  private:
  
    // These are for calculating mixing terms.
    double pow(double x, int n) const ;
    double erfc(double x) const ;
    std::complex<double> nwwerf(std::complex<double> z) const;

    // It is illegal to assign an adjustable constant
    const AnalyticConvolution & operator=(const AnalyticConvolution &right);

    Parameter          _lifetime;
    Parameter          _frequency;
    Parameter          _sigma;
    Parameter          _offset;
    Type               _type;

  };
} // namespace Genfun
#endif
