// -*- C++ -*-
// $Id: FunctionDirectProduct.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionDirectProduct---------------------------//
//                                                                          //
// FunctionDirectProduct, result of multiplication of taking the direct     //
// product of two functions:  f(x)*g(y)= h(x,y).  The direct product always //
// gives a function taking an argument of higher dimensionality than the    //
// arguments.                                                               //
//                                                                          //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef FunctionDirectProduct_h
#define FunctionDirectProduct_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionDirectProduct : public AbsFunction {

    FUNCTION_OBJECT_DEF(FunctionDirectProduct)

      public:

    // Constructor
    FunctionDirectProduct(const AbsFunction *arg1, const AbsFunction *arg2);

    // Copy constructor
    FunctionDirectProduct(const FunctionDirectProduct &right);
  
    // Destructor
    virtual ~FunctionDirectProduct();

    // Retreive function value
    virtual double operator ()(double argument) const;    // Gives an error.
    virtual double operator ()(const Argument & a) const; // Must use this one

    // Dimensionality
    virtual unsigned int dimensionality() const;

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}

  private:

    // It is illegal to assign a FunctionDirectProduct
    const FunctionDirectProduct & operator=(const FunctionDirectProduct &right);

    AbsFunction *_arg1;
    AbsFunction *_arg2;
    unsigned int _m;  // dimension of arg1
    unsigned int _n;  // dimension of arg2

  };
} // namespace Genfun
#endif
