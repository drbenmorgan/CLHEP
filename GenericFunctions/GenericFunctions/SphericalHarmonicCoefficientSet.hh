#ifndef _SPHERICALHARMONICCOEFFICIENTSET_H_
#define _SPHERICALHARMONICCOEFFICIENTSET_H_
#include <complex>
namespace Genfun {

  class SphericalHarmonicCoefficientSet {
    
  public:
    
    
    // Constructor:
    SphericalHarmonicCoefficientSet(unsigned int LMAX);
    
    // Copy Constructor:
    SphericalHarmonicCoefficientSet(const SphericalHarmonicCoefficientSet &);
    
    // Destructor:
    ~SphericalHarmonicCoefficientSet();
    
    
    // Get the size of the set:
    unsigned int getLMax() const;
    
    // Readonly access to a specific coefficient:
    const std::complex<double> & operator () (unsigned int l, int m) const;
    
    // Read/write access to a specific coefficient:
    std::complex<double> & operator () (unsigned int l, int m);
    
    // Assignement
    SphericalHarmonicCoefficientSet & operator= (const SphericalHarmonicCoefficientSet & );

    // Scale:
    SphericalHarmonicCoefficientSet & operator*= (const std::complex<double> & s );

    // Addition:
    SphericalHarmonicCoefficientSet & operator+= (const SphericalHarmonicCoefficientSet & );

    // Subtraction:
    SphericalHarmonicCoefficientSet & operator-= (const SphericalHarmonicCoefficientSet & );
    
    
  private:
    
    
    class Clockwork;
    Clockwork *c;
    
    
  };
  
  // Dump:
  std::ostream & operator<< ( std::ostream & o, const SphericalHarmonicCoefficientSet & c); 
  
  // Take the dot product:
  std::complex<double>  dot(const SphericalHarmonicCoefficientSet &, 
			    const SphericalHarmonicCoefficientSet &) ;

  // If an expansion in Spherical Harmonics is squared, another expansion in Spherical
  // harmonics is the result:
  SphericalHarmonicCoefficientSet squareExpansionCoefficients(const SphericalHarmonicCoefficientSet &);


}

#include "CLHEP/GenericFunctions/SphericalHarmonicCoefficientSet.icc"

#endif


