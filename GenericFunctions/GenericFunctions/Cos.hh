// -*- C++ -*-
// $Id: Cos.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Cos--------------------------------------------------//
//                                                                          //
// Class Cos                                                                //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Cos_h
#define Cos_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Cos : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Cos)

      public:

    // Constructor
    Cos();

    // Destructor
    virtual ~Cos();
  
    // Copy constructor
    Cos(const Cos &right);
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}
  
  private:

    // It is illegal to assign a Cosine
    const Cos & operator=(const Cos &right);

  };
} // namespace Genfun
#endif
