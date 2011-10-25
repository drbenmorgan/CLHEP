// -*- C++ -*-
// $Id: 
// ------------------------------------------------------------------------------//
// Lagrange's Interpolating Polynomial                                           //
//                                                                               //
//                                                                               //
// Joe Boudreau.                                                                 //
//                                                                               //
// ------------------------------------------------------------------------------//
#ifndef _InterpolatingPolynomial_h_
#define _InterpolatingPolynomial_h_ 
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include <vector>
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class InterpolatingPolynomial: public AbsFunction {

    FUNCTION_OBJECT_DEF(InterpolatingPolynomial)

      public:

    // Constructor
    InterpolatingPolynomial();

    // Copy constructor
    InterpolatingPolynomial(const InterpolatingPolynomial &right);
  
    // Destructor:
    virtual ~InterpolatingPolynomial();

    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Puncture this thing:
    void addPoint(double x, double y);

    // Get the range:
    void getRange(double & min, double & max) const;

  private:
  
    // It is illegal to assign an adjustable constant
    const InterpolatingPolynomial & operator=(const InterpolatingPolynomial &right);

    std::vector<std::pair<double,double> > xPoints;
  };
} // namespace Genfun
#endif
