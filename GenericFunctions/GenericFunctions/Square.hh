// -*- C++ -*-
// $Id: Square.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//----------------------Square------- --------------------------------------//
//                                                                          //
//  Class Square                                                            //
//  Joe Boudreau, Petar Maksimovic, Nov. 1999                               //
//                                                                          //
//  Square(x) returns x*x.                                                  //
//--------------------------------------------------------------------------//
#ifndef Square_h
#define Square_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Square : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Square)
  
      public:

    // Constructor
    Square();
  
    // Copy constructor
    Square(const Square &right);
  
    // Destructor
    virtual ~Square();
  
    // Retrieve function value
    virtual double operator ()(double argument) const; 
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}

  private:

    // It is illegal to assign a fixed constant
    const Square & operator=(const Square &right);

  };
} // namespace Genfun
#endif
