// -*- C++ -*-
// $Id: ATan.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
//---------------------ATan-------------------------------------------------//
//                                                                          //
// Class ATan                                                               //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef ATan_h
#define ATan_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {
  class ATan : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ATan)

      public:

    // Constructor
    ATan();

    // Destructor
    virtual ~ATan();
  
    // Copy constructor
    ATan(const ATan &right);
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}
  
  
  private:

    // It is illegal to assign a ATan
    const ATan & operator=(const ATan &right);

  };
} // end namespace Genfun

#endif
