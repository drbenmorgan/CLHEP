// -*- C++ -*-
// $Id: Sin.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
//---------------------Sin--------------------------------------------------//
//                                                                          //
// Class Sin                                                                //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Sin_h
#define Sin_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Sin : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Sin)

      public:

    // Constructor
    Sin();

    // Destructor
    virtual ~Sin();
  
    // Copy constructor
    Sin(const Sin &right);
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}
  
  
  private:

    // It is illegal to assign a Sin
    const Sin & operator=(const Sin &right);

  };
} // namespace Genfun

#endif
