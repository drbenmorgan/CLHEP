// -*- C++ -*-
// $Id: Exp.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Exp--------------------------------------------------//
//                                                                          //
// Class Exp                                                                //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Exp_h
#define Exp_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Exp : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Exp)

      public:

    // Constructor
    Exp();

    // Copy constructor
    Exp(const Exp &right);
  
    // Destructor
    virtual ~Exp();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}

  private:

    // It is illegal to assign an adjustable constant
    const Exp & operator=(const Exp &right);

  };
} // namespace Genfun
#endif
