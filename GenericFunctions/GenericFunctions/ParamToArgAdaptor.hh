// -*- C++ -*-
// $Id: ParamToArgAdaptor.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//-----------------------Class ParaToArgAdaptor-----------------------------//
//                                                                          //
//  Joe Boudreau                                                            //
//  January 2000                                                            //
//                                                                          //
//  This class changes the interpretation of a function's PARAMETER and     //
//  turns it into an argument.  In other words it makes a function like     //
//                                                                          //
//  F(a_0, a_1, a_2; x)                                                     //
//                                                                          //
//  and reinterprets it as                                                  //
//                                                                          //
//  F(a_0, a_2; x, a_1)                                                     //
//                                                                          //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef ParamToArgAdaptor_h_
#define ParamToArgAdaptor_h_

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
  class ParamToArgAdaptor : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ParamToArgAdaptor)

      public:

    // ScopedMethodName
    typedef Parameter & (F::*ScopedMethodPtr) ();

    // Constructor
    ParamToArgAdaptor(const F & function,
		     ScopedMethodPtr parameterFetchMethod);

    // Copy constructor
    ParamToArgAdaptor(const ParamToArgAdaptor &right);
  
    // Destructor
    virtual ~ParamToArgAdaptor();
  
    // Retreive function value
    virtual double operator ()(double argument) const;    // Gives an error.
    virtual double operator ()(const Argument & a) const; // Must use this one

    // Dimensionality
    virtual unsigned int dimensionality() const;

    // Get the mean of the ParamToArgAdaptor
    Parameter & scaleFactor(); 
    const Parameter & scaleFactor() const; 

  
  private:

    // It is illegal to assign an adjustable constant
    const ParamToArgAdaptor & operator=(const ParamToArgAdaptor &right);

    // Here is the sigma
    Parameter _scaleFactor;

    // Here is the function being adapted;
    F *_function;

    // Here is the recipe for fetching the parameter from the function:
    std::mem_fun_ref_t<Parameter &, F> _parameterFetchMethod;

  };
} // namespace Genfun
  #include "CLHEP/GenericFunctions/ParamToArgAdaptor.icc"
#endif
