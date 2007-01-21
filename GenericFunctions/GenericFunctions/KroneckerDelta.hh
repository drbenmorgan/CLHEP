// -*- C++ -*-
// $Id: KroneckerDelta.hh,v 1.1 2007/01/21 20:54:33 boudreau Exp $
//---------------------Rectangular------------------------------------------//
//                                                                          //
// Class KroneckerDelta by Joe Boudreau                                     //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef KroneckerDelta_h
#define KroneckerDelta_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class KroneckerDelta : public AbsFunction  {

    FUNCTION_OBJECT_DEF(KroneckerDelta)

      public:

    // Constructor
    KroneckerDelta();

    // Copy constructor
    KroneckerDelta(const KroneckerDelta &right);
  
    // Destructor
    virtual ~KroneckerDelta();
  
    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Derivative.  
    Derivative partial (unsigned int) const;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const {return true;}

  private:

    // It is illegal to assign an adjustable constant
    const KroneckerDelta & operator=(const KroneckerDelta &right);

 
  };
} // namespace Genfun
#endif
