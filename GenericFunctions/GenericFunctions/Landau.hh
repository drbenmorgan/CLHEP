// -*- C++ -*-
// $Id: Landau.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Landau-----------------------------------------------//
//                                                                          //
// Class Landau                                                             //
// Joe Boudreau,  November 1999                                             //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Landau_h
#define Landau_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Landau : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Landau)

      public:

    // Constructor
    Landau();

    // Copy constructor
    Landau(const Landau &right);
  
    // Destructor
    virtual ~Landau();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Get the mean of the Landau
    Parameter & peak(); 
    const Parameter & peak() const; 

    // Get the sigma of the Landau
    Parameter & width();
    const Parameter & width() const;

  
  private:

    // It is illegal to assign an adjustable constant
    const Landau & operator=(const Landau &right);

    // Here is the decay constant
    Parameter _peak;

    // Here is the sigma
    Parameter _width;

    // The old cernlib routine does the work:
    double _denlan(double x) const;

  };
} // namespace Genfun

#endif
