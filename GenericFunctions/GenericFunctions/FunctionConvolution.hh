// -*- C++ -*-
// $Id: FunctionConvolution.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//------------------------------FunctionConvolution-------------------------//
//                                                                          //
// FunctionConvolution:  output of the Convolve[f,g] operation              //
//                                                                          //
// Petar Maksimovic, Joe Boudreau, November 1999                            //
//                                                                          //
//  Warning!  This is not a very good convolution algorithm!  Does anybody  //
//  out there really know how to perform a reasonable numerical convolution //
//  ? Wanna help the Generic Functions Project?                             //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef FunctionConvolution_h
#define FunctionConvolution_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionConvolution : public AbsFunction  {

    FUNCTION_OBJECT_DEF(FunctionConvolution)

      public:

    // Constructor
    FunctionConvolution(const AbsFunction *arg1, const AbsFunction *arg2, double x0, double x1);
  
    // Copy Constructor
    FunctionConvolution(const FunctionConvolution &right);
  
    // Destructor
    virtual ~FunctionConvolution();
  
    // Retrieve function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
  private:

    // It is illegal to assign a convolution
    const FunctionConvolution & operator=(const FunctionConvolution &right);

    // Input functions to convolution
    const AbsFunction *_arg1;
    const AbsFunction *_arg2;
    double _x0;
    double _x1;

  };
} // namespace Genfun
#endif
