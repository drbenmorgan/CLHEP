// -*- C++ -*-
// $Id: FunctionNumDeriv.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionNumDeriv--------------------------------//
//                                                                          //
// Class FunctionNumDeriv, providing numerical derivatives                  //
// Joe Boudreau, Mark Fischler, February 2001                               //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef FunctionNumDeriv_h
#define FunctionNumDeriv_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionNumDeriv : public AbsFunction {
  
    FUNCTION_OBJECT_DEF(FunctionNumDeriv)

      public:

    // Constructor
    FunctionNumDeriv(const AbsFunction *arg1, unsigned int index=0);
  
    // Copy constructor.
    FunctionNumDeriv(const FunctionNumDeriv &right);
  
    // Destructor
    virtual ~FunctionNumDeriv();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const;
  
    // Dimensionality 
    virtual unsigned int dimensionality() const;

  private:
  
    // It is illegal to assign a FunctionNumDeriv
    const FunctionNumDeriv & operator=(const FunctionNumDeriv &right);

    // The function we're differntiating.
    const AbsFunction        *_arg1;
    const unsigned int       _wrtIndex;

    // helper data and methods to let us code Argument and double similarly
    double numericalDerivative 
	( double (FunctionNumDeriv::*f)(double)const, double x ) const;
    double f_x   (double x) const;
    double f_Arg (double x) const;
    mutable Argument 	    _xArg;

  };
} // namespace Genfun
#endif
