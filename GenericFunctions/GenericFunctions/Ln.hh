// -*- C++ -*-
// $Id: Ln.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Ln---------------------------------------------------//
//                                                                          //
// Class Ln                                                                 //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Ln_h
#define Ln_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Ln : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Ln)

      public:

    // Constructor
    Ln();

    // Destructor
    virtual ~Ln();
  
    // Copy constructor
    Ln(const Ln &right);
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}
  
  
  private:

    // It is illegal to assign a Ln
    const Ln & operator=(const Ln &right);

  };
} // namespace Genfun

#endif
