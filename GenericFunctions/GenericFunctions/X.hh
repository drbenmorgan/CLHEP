// -*- C++ -*-
// $Id: X.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
//----------------------X------------ --------------------------------------//
//                                                                          //
//  Class X_                                                                //
//  Joe Boudreau, Petar Maksimovic, Nov. 1999                               //
//                                                                          //
//  X_ is a function that returns the variable itself.                      //
//--------------------------------------------------------------------------//
#ifndef X__h
#define X__h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class X_ : public AbsFunction  {

    FUNCTION_OBJECT_DEF(X_)
  
      public:

    // Constructor
    X_();
  
    // Copy constructor
    X_(const X_ &right);
  
    // Destructor
    virtual ~X_();
  
    // Retrieve function value
    virtual double operator ()(double argument) const; 
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
  private:

    // It is illegal to assign a fixed constant
    const X_ & operator=(const X_ &right);

  };
} // namespace Genfun
#endif
