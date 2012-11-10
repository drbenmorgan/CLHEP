// -*- C++ -*-
// $Id: 
// ------------------------------------------------------------------------------//
// Natural cubic spline function, used for interpolation                         //
//                                                                               //
//                                                                               //
// Joe Boudreau.                                                                 //
//                                                                               //
// ------------------------------------------------------------------------------//
#ifndef _CubicSplinePolynomial_h_
#define _CubicSplinePolynomial_h_ 
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include <vector>
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class CubicSplinePolynomial: public AbsFunction {

    FUNCTION_OBJECT_DEF(CubicSplinePolynomial)

      public:

    // Constructor
    CubicSplinePolynomial();

    // Copy constructor
    CubicSplinePolynomial(const CubicSplinePolynomial &right);
  
    // Destructor:
    virtual ~CubicSplinePolynomial();

    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Puncture this thing:
    void addPoint(double x, double y);

    // Get the range:
    void getRange(double & min, double & max) const;

  private:
  
    // It is illegal to assign an adjustable constant
    const CubicSplinePolynomial & operator=(const CubicSplinePolynomial &right);

    class Clockwork;
    Clockwork *c;

  };
} // namespace Genfun
#include "CLHEP/GenericFunctions/CubicSplinePolynomial.icc"
#endif
