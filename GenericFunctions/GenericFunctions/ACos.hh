// -*- C++ -*-
// $Id: ACos.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------ACos-------------------------------------------------//
//                                                                          //
// Class ACos                                                               //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef ACos_h
#define ACos_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  class ACos : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ACos)

      public:

    // Constructor
    ACos();

    // Destructor
    virtual ~ACos();
  
    // Copy constructor
    ACos(const ACos &right);
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}
  
  private:

    // It is illegal to assign a ACosine
    const ACos & operator=(const ACos &right);

  };

} // end namespace Genfun

#endif
