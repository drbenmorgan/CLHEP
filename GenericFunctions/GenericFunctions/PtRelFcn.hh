// -*- C++ -*-
// $Id: 
//---------------------PtRelFcn---------------------------------------------//
//                                                                          //
// Class PtRelFcn                                                           //
//                                                                          //
// This class is a parameterization of ptrel distributions measured at      //
// CDF.  It has 6 parameters, and is normalized.  Alternate descriptions,   //
// in the past, have used 7 parameters but without normalization.           // 
//                                                                          //
// Joe Boudreau, Azizur Rahaman, March 2003                                 //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef PtRelFcn_h
#define PtRelFcn_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/LogGamma.hh"
#include "CLHEP/GenericFunctions/Erf.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class PtRelFcn : public AbsFunction  {

    FUNCTION_OBJECT_DEF(PtRelFcn)

      public:

    // Constructor
    PtRelFcn();

    // Copy constructor
    PtRelFcn(const PtRelFcn &right);
  
    // Destructor
    virtual ~PtRelFcn();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Parameter P0:
    Parameter & P0(); 
    const Parameter & P0() const; 

    // Parameter P1:
    Parameter & P1(); 
    const Parameter & P1() const; 

    // Parameter P2:
    Parameter & P2(); 
    const Parameter & P2() const; 

    // Parameter P3:
    Parameter & P3(); 
    const Parameter & P3() const; 

    // Parameter P4:
    Parameter & P4(); 
    const Parameter & P4() const; 

    // Parameter P5:
    Parameter & P5(); 
    const Parameter & P5() const; 

  private:

    // It is illegal to assign an adjustable constant
    const PtRelFcn & operator=(const PtRelFcn &right);

    // Here are the parameters:
    Parameter _p0,_p1,_p2,_p3,_p4,_p5;
    LogGamma  _logGamma;
    Erf       _erf;
  };
} // namespace Genfun

#endif
