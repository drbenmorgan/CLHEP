// -*- C++ -*-
// $Id: FunctionProduct.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
//--------------------------FunctionProduct---------------------------------//
//                                                                          //
// FunctionProduct, result of multiplication of two functions.              //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef FunctionProduct_h
#define FunctionProduct_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionProduct : public AbsFunction {

    FUNCTION_OBJECT_DEF(FunctionProduct)

      public:

    // Constructor
    FunctionProduct(const AbsFunction *arg1, const AbsFunction *arg2);

    // Copy constructor
    FunctionProduct(const FunctionProduct &right);
  
    // Destructor
    virtual ~FunctionProduct();

    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const;

    // Dimensionality 
    virtual unsigned int dimensionality() const;

    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}

  private:

    // It is illegal to assign a FunctionProduct
    const FunctionProduct & operator=(const FunctionProduct &right);

    const AbsFunction *_arg1;
    const AbsFunction *_arg2;  
  };
} // namespace Genfun

#endif
