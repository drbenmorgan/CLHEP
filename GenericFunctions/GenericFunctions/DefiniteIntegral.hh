// -*- C++ -*-
// $Id: DefiniteIntegral.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//-------------------------------------------------------------//
//                                                             //
// This functional returns the definite integral of a function //
// between lower bound and upper bound b.                      //
//                                                             //
//-------------------------------------------------------------//

#ifndef _DefiniteIntegral_h_
#define _DefiniteIntegral_h_
#include "CLHEP/GenericFunctions/AbsFunctional.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class DefiniteIntegral:public AbsFunctional {

  public:
  
    // Constructor:
    DefiniteIntegral(double a, double b);

    // Destructor:
    ~DefiniteIntegral();

    // Take the definite integral of a function between the bounds:
    virtual double operator [] (const AbsFunction & function) const;


  private:

    // Trapezoid calculation:
    double _trapzd( const AbsFunction & function, double a, double b, int j) const;

    // Polynomial interpolation:
    void _polint(double *xArray, double *yArray, double x, double & y, double & deltay) const;

    double _a;                          // lower limit of integration
    double _b;                          // upper limit of integration

    static const int _K;                // Order
    static const int _KP;               // Const dim of certain arrays.
  
    // buffered value for _trapzd calculation:
    mutable double _sTrap;

  };
} // namespace Genfun
#endif
