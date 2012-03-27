// -*- C++ -*-
// $Id: 
//---------------------SphericalHarmonicFit------------------------------------------//
//                                                                          //
// Class SphericalHarmonicFit.  This is a fitting function consisting of a super     //
// position of N legendre polynomials.  Cascading fractions and phases are  //
// the input parameters. Function is normalized to one (on [-1,1])          //
// Joe Boudreau, Petar Maksimovic, January 2000                             //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef SphericalHarmonicFit_h
#define SphericalHarmonicFit_h 
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/SphericalHarmonicCoefficientSet.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class SphericalHarmonicFit : public AbsFunction  {

    FUNCTION_OBJECT_DEF(SphericalHarmonicFit)

      public:

     // Constructor.  Builds all the 
    SphericalHarmonicFit(unsigned int LMAX);

    // Copy constructor
    SphericalHarmonicFit(const SphericalHarmonicFit &right);
  
    // Destructor
    virtual ~SphericalHarmonicFit();
  
    // Dimensionality=2.  They are; cosTheta (not theta) and phi
    virtual unsigned int dimensionality() const {return 2;}

    // Retreive function value
    virtual double operator ()(double argument) const;    // Gives an error.
    virtual double operator ()(const Argument & a) const; // Must use this one

    // Total number of parameters
    unsigned int numComponents() const;
    
    // Max L ("angular momentum")
    unsigned int lMax() const;
    
    // MINUIT-SAFE PARAMETERIZATION: Fractions vary on the range 0,1, 
    // Phases need not be bounded:

    // The fraction of amplitude sq which is L OR HIGHER:
    Parameter *getFractionLOrHigher(unsigned int L);
    const Parameter *getFractionLOrHigher(unsigned int L) const;

    // The phase of coefficient L, M=0;
    Parameter *getPhaseLM0(unsigned int L);
    const Parameter *getPhaseLM0(unsigned int L) const;

    // The fraction of amplitude sq which is L which is +- M OR HIGHER
    Parameter *getFractionAbsMOrHigher(unsigned int L, unsigned int M);
    const Parameter *getFractionAbsMOrHigher(unsigned int L, unsigned int M) const;

    // The fraction of amplitude sq which is +- M, which is positive
    Parameter *getFractionMPositive(unsigned int L, unsigned int M);
    const Parameter *getFractionMPositive(unsigned int L, unsigned int M) const;

    // The phase of the positive M coefficient
    Parameter *getPhaseMPlus(unsigned int L, unsigned int M);
    const Parameter *getPhaseMPlus(unsigned int L, unsigned int M) const;

    // The phase of the negative M coefficient
    Parameter *getPhaseMMinus(unsigned int L, unsigned int M);
    const Parameter *getPhaseMMinus(unsigned int L, unsigned int M) const;

    // Gets the coefficients the coefficients of the function which is
    // Squared to obtain a probability distribution (amplitude)
    const SphericalHarmonicCoefficientSet & coefficientsA() const;

    // Gets the coefficients the coefficients of the function which is
    // Squared to obtain a probability distribution: 
    const SphericalHarmonicCoefficientSet & coefficientsASq() const;

    // Recompute coefficients from the parameters:
    void recomputeCoefficients() const;

  private:

    // It is illegal to assign an adjustable constant
    const SphericalHarmonicFit & operator=(const SphericalHarmonicFit &right);
    
    
    class Clockwork;
    Clockwork *c;

  };
} // namespace Genfun



#include "CLHEP/GenericFunctions/SphericalHarmonicFit.icc"
#endif
