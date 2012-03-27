#ifndef _LEGENDRECOEFFICIENTSET_H_
#define _LEGENDRECOEFFICIENTSET_H_
#include <complex>
namespace Genfun {

  class LegendreCoefficientSet {
    
  public:
    
    
    // Constructor:
    LegendreCoefficientSet(unsigned int LMAX);
    
    // Copy Constructor:
    LegendreCoefficientSet(const LegendreCoefficientSet &);
    
    // Destructor:
    ~LegendreCoefficientSet();
    
    
    // Get the size of the set:
    unsigned int getLMax() const;
    
    // Readonly access to a specific coefficient:
    const std::complex<double> & operator () (unsigned int l) const;
    
    // Read/write access to a specific coefficient:
    std::complex<double> & operator () (unsigned int l);
    
    LegendreCoefficientSet & operator= (const LegendreCoefficientSet & );

  private:
    
    
    class Clockwork;
    Clockwork *c;
    
    
  };
  
  std::ostream & operator<< ( std::ostream & o, const LegendreCoefficientSet & c); 
}

#include "CLHEP/GenericFunctions/LegendreCoefficientSet.icc"

#endif


