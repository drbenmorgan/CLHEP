// -*- C++ -*-
// $Id: AbsFunction.hh,v 1.3 2007/01/21 20:20:40 boudreau Exp $
//------------------------AbsFunction-----------------------------------//
//                                                                      //
//  AbsFunction, base class for function objects                        //
//  Joe Boudreau, Petar Maksimovic                                      //
//  Nov 1999                                                            //
//                                                                      //
//----------------------------------------------------------------------//
#ifndef AbsFunction_h
#define AbsFunction_h 1
#include "CLHEP/GenericFunctions/Argument.hh"

namespace Genfun {

  class AbsParameter;

  //-----------------------------------------------------------------------//
  // Exact return type of arithmentic operations.  To the user, the return //
  // type is GENFUNCTION, or const AbsFunction &.                          //
  //-----------------------------------------------------------------------//

  class FunctionProduct;
  class FunctionSum;
  class FunctionDifference;
  class FunctionQuotient;
  class FunctionNegation;
  class FunctionConvolution;
  class FunctionDirectProduct;
  class FunctionComposition;
  class ConstPlusFunction;
  class ConstTimesFunction;
  class ConstMinusFunction;
  class ConstOverFunction;
  class FunctionPlusParameter;
  class FunctionTimesParameter;
  class FunctionNumDeriv;
  class Variable;
  class FunctionNoop;
  class ParameterComposition;

  typedef FunctionNoop Derivative;

  /**
   * @author
   * @ingroup genfun
   */
  class AbsFunction {
  
  public:
  
    // Default Constructor
    AbsFunction();
  
    // Copy Constructor:
    AbsFunction(const AbsFunction &right);
  
    // Destructor
    virtual ~AbsFunction();
  
    // Function value:  N-dimensional functions must override these:
    virtual unsigned int dimensionality() const;      // returns 1;

    // Function value
    virtual double operator() (double argument)          const=0;   
    virtual double operator() (const Argument &argument) const=0; 

    // Every function must override this:
    virtual AbsFunction * clone() const=0;
  
    // Function composition.  Do not attempt to override:
    virtual FunctionComposition operator () (const AbsFunction &f) const;
    
    // Parameter composition.  Do not attempt to override:
    virtual ParameterComposition operator() ( const AbsParameter &p) const;

    // Derivative, (All functions)  (do not override)
    Derivative derivative(const Variable &v) const;

    // Derivative (1D functions only) (do not override)
    Derivative prime() const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return false;}

    // Derivative.  Overriders may be provided, numerical method by default!
    virtual Derivative partial(unsigned int) const;
  
  private:

    // It is illegal to assign a function.
    const AbsFunction & operator=(const AbsFunction &right);
  
  };

FunctionProduct           operator * (const AbsFunction &op1, const AbsFunction &op2);
FunctionSum               operator + (const AbsFunction &op1, const AbsFunction &op2);
FunctionDifference        operator - (const AbsFunction &op1, const AbsFunction &op2);
FunctionQuotient          operator / (const AbsFunction &op1, const AbsFunction &op2);
FunctionNegation          operator - (const AbsFunction &op1);

ConstTimesFunction        operator * (double c, const AbsFunction &op2);
ConstPlusFunction         operator + (double c, const AbsFunction &op2);
ConstMinusFunction        operator - (double c, const AbsFunction &op2);
ConstOverFunction         operator / (double c, const AbsFunction &op2);

ConstTimesFunction        operator * (const AbsFunction &op2, double c);
ConstPlusFunction         operator + (const AbsFunction &op2, double c);
ConstPlusFunction         operator - (const AbsFunction &op2, double c);
ConstTimesFunction        operator / (const AbsFunction &op2, double c);

FunctionTimesParameter    operator * (const AbsFunction &op1, const AbsParameter &op2);
FunctionPlusParameter     operator + (const AbsFunction &op1, const AbsParameter &op2);
FunctionPlusParameter     operator - (const AbsFunction &op1, const AbsParameter &op2);
FunctionTimesParameter    operator / (const AbsFunction &op1, const AbsParameter &op2);

FunctionTimesParameter    operator * (const AbsParameter   &op1, const AbsFunction &op2);
FunctionPlusParameter     operator + (const AbsParameter   &op1, const AbsFunction &op2);
FunctionPlusParameter     operator - (const AbsParameter   &op1, const AbsFunction &op2);
FunctionTimesParameter    operator / (const AbsParameter   &op1, const AbsFunction &op2);

FunctionConvolution       convolve   (const AbsFunction &op1, const AbsFunction &op2, double x0, double x1);
FunctionDirectProduct     operator % (const AbsFunction &op1, const AbsFunction &op2);

typedef const AbsFunction & GENFUNCTION;

} // namespace Genfun


//----------------------------------------------------------------------------
//
// These macros do all the ugly boilerplate.  
//
//----------------------------------------------------------------------------






// A more modern way to accomplish this, which is slicker:

#define FUNCTION_OBJECT_DEF(classname) \
public:                                \
 using Genfun::AbsFunction::operator();			\
 virtual classname *clone() const override;		\
private:                               

#define FUNCTION_OBJECT_IMP(classname)       \
inline classname *classname::clone() const          \
{                                            \
  return new classname(*this);               \
}


//----------------------------------------------------------------------------


#include "CLHEP/GenericFunctions/FunctionProduct.hh"
#include "CLHEP/GenericFunctions/FunctionSum.hh"
#include "CLHEP/GenericFunctions/FunctionDifference.hh"
#include "CLHEP/GenericFunctions/FunctionQuotient.hh"
#include "CLHEP/GenericFunctions/FunctionConvolution.hh"
#include "CLHEP/GenericFunctions/FunctionNegation.hh"
#include "CLHEP/GenericFunctions/FunctionDirectProduct.hh"
#include "CLHEP/GenericFunctions/FunctionComposition.hh"
#include "CLHEP/GenericFunctions/ConstPlusFunction.hh"
#include "CLHEP/GenericFunctions/ConstTimesFunction.hh"
#include "CLHEP/GenericFunctions/ConstMinusFunction.hh"
#include "CLHEP/GenericFunctions/ConstOverFunction.hh"
#include "CLHEP/GenericFunctions/FunctionPlusParameter.hh"
#include "CLHEP/GenericFunctions/FunctionTimesParameter.hh"
#include "CLHEP/GenericFunctions/FunctionNoop.hh"
#include "CLHEP/GenericFunctions/ParameterComposition.hh"

#endif
