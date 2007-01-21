// -*- C++ -*-
// $Id: 
// Legendre Functions P_l(x)
#ifndef Legendre_h
#define Legendre_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Legendre : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Legendre)

      public:

    // Constructor:  
    Legendre (unsigned int order);

    // Copy constructor
    Legendre(const Legendre &right);
  
    // Destructor
    virtual ~Legendre();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
  private:

    // It is illegal to assign an adjustable constant
    const Legendre & operator=(const Legendre &right);

    // The type and order of the Legendre function
    unsigned int      _order;
  
  };

} // namespace Genfun


#include "CLHEP/GenericFunctions/Legendre.icc"
#endif
