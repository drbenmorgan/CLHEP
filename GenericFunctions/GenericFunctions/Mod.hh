// -*- C++ -*-
// $Id: 
//----------------------Mod-----------------------------------------------//
//                                                                        //
//  Class Mod   (Modulo)                                                  //
//  Joe Boudreau, Petar Maksimovic, Nov. 2002                             //
//                                                                        //
//  Mod(x) returns x%y                                                    //
//------------------------------------------------------------------------//
#ifndef Mod_h
#define Mod_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Mod : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Mod)
  
      public:

    // Constructor
    Mod(double y);
  
    // Copy constructor
    Mod(const Mod &right);
  
    // Destructor
    virtual ~Mod();
  
    // Retrieve function value

    virtual double operator ()(double argument) const; 
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
  private:

    // It is illegal to assign a fixed constant
    const Mod & operator=(const Mod &right);

    double _y; // mod (as a double)

  };
} // namespace Genfun
#endif
