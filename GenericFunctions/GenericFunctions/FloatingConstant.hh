// -*- C++ -*-
// $Id: FloatingConstant.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//----------------------FloatingConstant -----------------------------------//
//                                                                          //
//  Class FloatingConstant                                                  //
//  Joe Boudreau, Petar Maksimovic, Nov. 1999                               //
//                                                                          //
//  FloatingConstant allows use to treat constants as floating-constant     //
//  functions so that they automatically will inherit all the algebraic     //
//  operations we have so painstakingly defined for functions.              //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef FloatingConstant_h
#define FloatingConstant_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FloatingConstant : public AbsFunction  {

    FUNCTION_OBJECT_DEF(FloatingConstant)
  
      public:

    // Constructor
    FloatingConstant(const AbsParameter & p);
  
    // Copy constructor
    FloatingConstant(const FloatingConstant &right);
  
    // Destructor
    virtual ~FloatingConstant();
  
    // Retrieve the parameter:
    AbsParameter & value();

    // Retrieve function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}

  private:

    // It is illegal to assign a fixed constant
    const FloatingConstant & operator=(const FloatingConstant &right);

    // The value of the constant:
    AbsParameter *_value;
  };
} // namespace Genfun
#endif
