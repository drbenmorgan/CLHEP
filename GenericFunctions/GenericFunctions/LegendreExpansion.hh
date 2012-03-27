// -*- C++ -*-
// $Id: 
//---------------------SphericalHarmonicExpansion---------------------------//
//                                                                          //
// Class LegendreExpansion  This is an expansion in terms of  a super       //
// position of N legendre polynomials.                                      //
//--------------------------------------------------------------------------//
#ifndef LegendreExpansion_h
#define LegendreExpansion_h 
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/LegendreCoefficientSet.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class LegendreExpansion : public AbsFunction  {

    FUNCTION_OBJECT_DEF(LegendreExpansion)

      public:

    enum Type {REAL,IMAG,MAG, MAGSQ};

     // Constructor.  Builds all the 
    LegendreExpansion(Type type, const LegendreCoefficientSet & coefficients);

    // Copy constructor
    LegendreExpansion(const LegendreExpansion &right);
  
    // Destructor
    virtual ~LegendreExpansion();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
    // Get the expansion coefficients:
    const LegendreCoefficientSet & coefficientSet() const;
    
  private:

    // It is illegal to assign an adjustable constant
    const LegendreExpansion & operator=(const LegendreExpansion &right);
    
    
    class Clockwork;
    Clockwork *c;

  };
} // namespace Genfun



#include "CLHEP/GenericFunctions/LegendreExpansion.icc"
#endif
