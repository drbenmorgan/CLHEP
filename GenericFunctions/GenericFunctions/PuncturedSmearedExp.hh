// -*- C++ -*-
// $Id: PuncturedSmearedExp.hh,v 1.1.4.1 2004/04/29 00:20:36 garren Exp $
// ------------------------------------------------------------------------------//
// This function-object makes an exponential with acceptance holes ("punctures") //
// smeared by a resolution function.                                             //
//                                                                               //
//                                                                               //
// Joe Boudreau.                                                                 //
//                                                                               //
// ------------------------------------------------------------------------------//
#ifndef _PuncturedSmearedExp_h_
#define _PuncturedSmearedExp_h_ 
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
 
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class PuncturedSmearedExp: public AbsFunction {

    FUNCTION_OBJECT_DEF(PuncturedSmearedExp)

      public:

    // Constructor
    PuncturedSmearedExp();

    // Copy constructor
    PuncturedSmearedExp(const PuncturedSmearedExp &right);
  
    // Destructor:
    virtual ~PuncturedSmearedExp();

    // Retreive function value
    virtual double operator ()(double argument) const;
    virtual double operator ()(const Argument & a) const {return operator() (a[0]);}
  
    // Lifetime of exponential:
    Parameter & lifetime();
    const Parameter & lifetime() const;

    // Width of the gaussian:
    Parameter & sigma();
    const Parameter & sigma() const;

    // Puncture this thing:
    void puncture(double min, double max);

    // Get the puncture parameters:
    Parameter & min(unsigned int i);
    Parameter & max(unsigned int i);
    const Parameter & min(unsigned int i) const;
    const Parameter & max(unsigned int i) const;
    

  private:
  
    // These are for calculating mixing terms.
    double pow(double x, int n) const ;
    double erfc(double x) const ;

    // It is illegal to assign an adjustable constant
    const PuncturedSmearedExp & operator=(const PuncturedSmearedExp &right);

    Parameter              _lifetime;
    Parameter              _sigma;
    std::vector<Parameter> _punctures;

  };
} // namespace Genfun
#endif
