// -*- C++ -*-
// $Id: SphericalNeumann.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------SphericalNeumann-------------------------------------//
//                                                                          //
// Class SphericalNeumann.  An spherical neumann function of integral order //
// Joe Boudreau, Petar Maksimovic, January 2000                             //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef SphericalNeumann_h
#define SphericalNeumann_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class SphericalNeumann : public AbsFunction  {

    FUNCTION_OBJECT_DEF(SphericalNeumann)

      public:

    // Constructor
    SphericalNeumann(unsigned int l);

    // Copy constructor
    SphericalNeumann(const SphericalNeumann &right);
  
    // Destructor
    virtual ~SphericalNeumann();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Get the integer variable l
    unsigned int l() const;

  private:

    // It is illegal to assign an adjustable constant
    const SphericalNeumann & operator=(const SphericalNeumann &right);

    // Here is the decay constant
    unsigned int _l;
  
    // Here is the "work function"
    const AbsFunction *_function;

    // This function is needed in all constructors:
    void create(); 

  };
} // namespace Genfun
#include "CLHEP/GenericFunctions/SphericalNeumann.icc"
#endif
