// -*- C++ -*-
// $Id: LegendreFit.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------LegendreFit------------------------------------------//
//                                                                          //
// Class LegendreFit.  This is a fitting function consisting of a super     //
// position of N legendre polynomials.  Cascading fractions and phases are  //
// the input parameters. Function is normalized to one (on [-1,1])          //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef LegendreFit_h
#define LegendreFit_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/LegendreCoefficientSet.hh"
#include "CLHEP/GenericFunctions/ClebschGordanCoefficientSet.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class LegendreFit : public AbsFunction  {

    FUNCTION_OBJECT_DEF(LegendreFit)

      public:

    // Constructor
    LegendreFit(unsigned int N);

    // Copy constructor
    LegendreFit(const LegendreFit &right);
  
    // Destructor
    virtual ~LegendreFit();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    unsigned int order() const;

    Parameter *getFraction(unsigned int i);
    const Parameter *getFraction(unsigned int i) const;

    Parameter *getPhase(unsigned int i);
    const Parameter *getPhase(unsigned int i) const;

    // Gets the coefficients the coefficients of the function which is
    // Squared to obtain a probability distribution (amplitude)
    const LegendreCoefficientSet & coefficientsA() const;

    // Gets the coefficients the coefficients of the function which is
    // Squared to obtain a probability distribution: 
    const LegendreCoefficientSet & coefficientsASq() const;

    // Recompute coefficients from the parameters:
    void recomputeCoefficients() const;


  private:

    // It is illegal to assign an adjustable constant
    const LegendreFit & operator=(const LegendreFit &right);

    // 
    const unsigned   int                      N;
    std::vector <Genfun::Parameter *>         fraction;
    std::vector <Genfun::Parameter *>         phase;
    mutable LegendreCoefficientSet            coefA;
    mutable LegendreCoefficientSet            coefASq;
    mutable ClebschGordanCoefficientSet       ClebschGordan;

  };
} // namespace Genfun
#include "CLHEP/GenericFunctions/LegendreFit.icc"
#endif
