// $Id: 
// -*- C++ -*-
//
//----------------------Abs---------- --------------------------------------//
//                                                                          //
//  Class Abs                                                               //
//  Joe Boudreau, Petar Maksimovic, Nov. 1999                               //
//                                                                          //
//  Abs is a function that returns the absolute value of its argument       //
//--------------------------------------------------------------------------//
#ifndef Abs_h
#define Abs_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {
  class Abs : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Abs)
  
      public:

    // Constructor
    Abs();
  
    // Copy constructor
    Abs(const Abs &right);
  
    // Destructor
    virtual ~Abs();
  
    // Retrieve function value
    virtual double operator ()(double argument) const; 
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
  private:

    // It is illegal to assign a fixed constant
    const Abs & operator=(const Abs &right);

  };
}

#endif
