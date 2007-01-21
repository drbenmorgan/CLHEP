// -*- C++ -*-
// $Id: 
//-----------------------Class ParaToArgAdaptor-----------------------------//
//                                                                          //
//  Joe Boudreau                                                            //
//  June 2004                                                               //
//                                                                          //
// The purpose of this adaptor is to be able to create, starting FROM       //
// a function F of several variables and controlled by several parameters:  //
//                                                                          //
// F(alpha, beta, gamma....; x, y, z)                                       //
//                                                                          //
// a new function of several variables in which the parameter values are    //
// set by some of the variables.  Application:  event-per-event errors.     //
//                                                                          //
// Arguments to the adaptor:                                                //
// 1) The original generic function to adapt.                               //
// 2) The symbolic expression to apply it to.                               //
// 3) The name of a parameter to tweak.                                     //
// 4) The symbolic expression to tweak it with                              //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef _SYMTOARGADAPTOR_
#define _SYMTOARGADAPTOR_
#include <functional>
#include <iostream>
#include <string>
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  template <class F> 
  class SymToArgAdaptor : public AbsFunction  {

    FUNCTION_OBJECT_DEF(SymToArgAdaptor)

      public:

    // ScopedMethodName
    typedef Parameter & (F::*ScopedMethodPtr) ();

    // Constructor
    SymToArgAdaptor( F & function,                     // A function.
		    const AbsFunction &  f_expression,                // An expression to apply it to
		    ScopedMethodPtr      parameterFetchMethod,        // A parameter.
		    const AbsFunction *  p_expression);               // An expression for the parameter

    // Copy constructor
    SymToArgAdaptor(const SymToArgAdaptor &right);
  
    // Destructor
    virtual ~SymToArgAdaptor();

    // Retreive function value
    virtual double operator ()(double argument) const;    // Gives an error.
    virtual double operator ()(const Argument & a) const; // Must use this one

    // Dimensionality
    virtual unsigned int dimensionality() const;

  private:

    // It is illegal to assign an adjustable constant
    const SymToArgAdaptor & operator=(const SymToArgAdaptor &right);

    // Here is the function being adapted;
    F *_function;

    // A Variable (int an argument) to which the function is going to apply:
    const AbsFunction *_f_expression;

    // Here is the recipe for fetching the parameter from the function:
    std::mem_fun_ref_t<Parameter &, F> _parameterFetchMethod;

    // Here is the symbol to be connect to the parameter:
    const AbsFunction *_p_expression;

  };
} // namespace Genfun
  #include "CLHEP/GenericFunctions/SymToArgAdaptor.icc"
#endif

