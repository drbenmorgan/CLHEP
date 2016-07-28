// -*- C++ -*-
// $Id: 
//---------------------Hermite----------------------------------------------//
//                                                                          //
// Class HermitePolynomial.  (Hermite polynomials)                          //
// Joe Boudreau, October 2012                                               //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef HermitePolynomial_h_
#define HermitePolynomial_h_ 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class HermitePolynomial : public AbsFunction  {
  
    FUNCTION_OBJECT_DEF(HermitePolynomial)

      public:

    // Constructor
    HermitePolynomial(unsigned int N);

    // Copy constructor
    HermitePolynomial(const HermitePolynomial &right);
  
    // Destructor
    virtual ~HermitePolynomial();
  
    // Retreive function value
    virtual double operator ()(double argument) const override;
    virtual double operator ()(const Argument & a) const override {return operator() (a[0]);}
  
    // Get the integer variable N
    unsigned int N() const;

    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}
  

  private:

    // It is illegal to assign a Hermite Polynomial
    const HermitePolynomial & operator=(const HermitePolynomial &right);

    // Here is the sigma
    unsigned int _N;

  };

} // namespace Genfun


#endif


