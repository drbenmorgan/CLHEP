// -*- C++ -*-
// $Id: DoubleParamToArgAdaptor.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//-----------------------Class ParaToArgAdaptor-----------------------------//
//                                                                          //
//  Joe Boudreau                                                            //
//  January 2000                                                            //
//                                                                          //
//  This class changes the interpretation of two  PARAMETERs to a function  //
//  connects them to a single argument, with scale factors controlling how  //
//  the argument is increased before it is used to adjust the parameter.    //
//  In other words it makes a function like     //
//                                                                          //
//  F(a_0, a_1, a_2; x)                                                     //
//                                                                          //
//  and reinterprets it as                                                  //
//                                                                          //
//  F(a_0; x, a_1)                                                          //
//                                                                          //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef DoubleParamToArgAdaptor_h_
#define DoubleParamToArgAdaptor_h_

#include <functional>
#include <iostream>
#include <string>
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  template <class F> 
  class DoubleParamToArgAdaptor : public AbsFunction  {

    FUNCTION_OBJECT_DEF(DoubleParamToArgAdaptor)

      public:

    // ScopedMethodName
    typedef Parameter & (F::*ScopedMethodPtr) ();

    // Constructor
    DoubleParamToArgAdaptor(const F & function,
		     ScopedMethodPtr parameterFetchMethod0,
                     ScopedMethodPtr paraemterFetchMethod1);

    // Copy constructor
    DoubleParamToArgAdaptor(const DoubleParamToArgAdaptor &right);
  
    // Destructor
    virtual ~DoubleParamToArgAdaptor();
  
    // Retreive function value
    virtual double operator ()(double argument) const;    // Gives an error.
    virtual double operator ()(const Argument & a) const; // Must use this one

    // Dimensionality
    virtual unsigned int dimensionality() const;

    // Get the mean of the DoubleParamToArgAdaptor
    Parameter & scaleFactor0(); 
    const Parameter & scaleFactor0() const; 

    // Get the mean of the DoubleParamToArgAdaptor
    Parameter & scaleFactor1(); 
    const Parameter & scaleFactor1() const; 

  
  private:

    // It is illegal to assign an adjustable constant
    const DoubleParamToArgAdaptor & operator=(const DoubleParamToArgAdaptor &right);

    // Here is the scale:
    Parameter _scaleFactor0;
    Parameter _scaleFactor1;

    // Here is the function being adapted;
    F *_function;

    // Here is the recipe for fetching the parameter from the function:
    std::mem_fun_ref_t<Parameter &, F> _parameterFetchMethod0;
    std::mem_fun_ref_t<Parameter &, F> _parameterFetchMethod1;

  };
} // namespace Genfun
  #include "CLHEP/GenericFunctions/DoubleParamToArgAdaptor.icc"
#endif
