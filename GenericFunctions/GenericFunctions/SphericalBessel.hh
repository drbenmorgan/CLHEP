// -*- C++ -*-
// $Id: SphericalBessel.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------SphericalBessel--------------------------------------//
//                                                                          //
// Class SphericalBessel.  An spherical bessel function of integral order   //
// Joe Boudreau, Petar Maksimovic, January 2000                             //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef SphericalBessel_h
#define SphericalBessel_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class SphericalBessel : public AbsFunction  {

    FUNCTION_OBJECT_DEF(SphericalBessel)

      public:

    // Constructor
    SphericalBessel(unsigned int l);

    // Copy constructor
    SphericalBessel(const SphericalBessel &right);
  
    // Destructor
    virtual ~SphericalBessel();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Get the integer variable l
    unsigned int l() const;

  private:

    // It is illegal to assign an adjustable constant
    const SphericalBessel & operator=(const SphericalBessel &right);

    // Here is the decay constant
    unsigned int _l;
  
    // Here is the "work function"
    const AbsFunction *_function;

    // This function is needed in all constructors:
    void create(); 

  };
} // namespace Genfun
#include "CLHEP/GenericFunctions/SphericalBessel.icc"
#endif
