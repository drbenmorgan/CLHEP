// -*- C++ -*-
// $Id: Tan.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Tan--------------------------------------------------//
//                                                                          //
// Class Tan                                                                //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Tan_h
#define Tan_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Tan : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Tan)

      public:

    // Constructor
    Tan();

    // Destructor
    virtual ~Tan();
  
    // Copy constructor
    Tan(const Tan &right);
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}
  
  
  private:

    // It is illegal to assign a Tan
    const Tan & operator=(const Tan &right);

  };
} // namespace Genfun

#endif
