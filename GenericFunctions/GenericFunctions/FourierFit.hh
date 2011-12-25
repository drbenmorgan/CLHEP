// -*- C++ -*-
// $Id: 
//---------------------FourierFit-------------------------------------------//
//                                                                          //
// Class FourierFit.  This is a fitting function consisting of a super      //
// position of N legendre polynomials.  Cascading fractions and phases are  //
// the input parameters. Function is normalized to one (on [0,2PI])         //
// Joe Boudreau, Petar Maksimovic, January 2000                             //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef FourierFit_h
#define FourierFit_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FourierFit : public AbsFunction  {

    FUNCTION_OBJECT_DEF(FourierFit)

      public:

    // Constructor
    FourierFit(unsigned int N);

    // Copy constructor
    FourierFit(const FourierFit &right);
  
    // Destructor
    virtual ~FourierFit();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    unsigned int order() const;

    Parameter *getFraction(unsigned int i);
    const Parameter *getFraction(unsigned int i) const;

    Parameter *getPhase(unsigned int i);
    const Parameter *getPhase(unsigned int i) const;


  private:

    // It is illegal to assign an adjustable constant
    const FourierFit & operator=(const FourierFit &right);

    // 
    const unsigned   int                    N;
    std::vector <Genfun::Parameter *> fraction;
    std::vector <Genfun::Parameter *> phase;


  };
} // namespace Genfun
#include "CLHEP/GenericFunctions/FourierFit.icc"
#endif
