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

    unsigned int numComponents() const {
      return (LMAX+1)*(LMAX+1)-1;
    }
    
     Parameter *getFraction(unsigned int i);
    const Parameter *getFraction(unsigned int i) const;

    Parameter *getPhase(unsigned int i);
    const Parameter *getPhase(unsigned int i) const;


  private:

    // It is illegal to assign an adjustable constant
    const SphericalHarmonicFit & operator=(const SphericalHarmonicFit &right);

    // 
    const unsigned   int              LMAX;
    std::vector <Genfun::Parameter *> fraction;
    std::vector <Genfun::Parameter *> phase;


  };
} // namespace Genfun
#include "CLHEP/GenericFunctions/SphericalHarmonicFit.icc"
#endif
