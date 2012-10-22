// -*- C++ -*-
// $Id: DefiniteIntegral.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//-------------------------------------------------------------//
//                                                             //
// This functional performs Romberg integration on a function  //
// between lower bound and upper bound b.                      //
//                                                             //
// Two types:  OPEN: use open quadrature formula               //
//                   for improper integrals                    //
//             CLOSED (default) use closed quadrature          //
//                   formula.                                  //
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
  
    // Type definition:
    typedef enum {CLOSED, OPEN} Type;

    // Constructor:
    DefiniteIntegral(double a, double b, Type=CLOSED);

    // Copy Constructor:
    DefiniteIntegral(const DefiniteIntegral &);

    // Assignment Operator:
    DefiniteIntegral & operator=(const DefiniteIntegral &) ;

    // Destructor:
    ~DefiniteIntegral();

    // Take the definite integral of a function between the bounds:
    virtual double operator [] (const AbsFunction & function) const;

    // Retrieve the number of function calls for the last operation:
    unsigned int numFunctionCalls() const;

    // Algorithmic parameters:
    
    // Desired precision (default 1.0E-06)
    void setEpsilon(double eps);

    // Maximum number of iterations (default 20(closed) 14 (open))
    void setMaxIter (unsigned int maxIter);

    // Minimum order:
    void setMinOrder (unsigned int order);


  private:

    class Clockwork;
    Clockwork *c;

  };
} // namespace Genfun
#endif
