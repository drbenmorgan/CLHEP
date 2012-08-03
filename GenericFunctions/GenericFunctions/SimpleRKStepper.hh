#ifndef _SimpleRKStepper_h_
#define _SimpleRKStepper_h_
#include "CLHEP/GenericFunctions/RKIntegrator.hh"
//
// This is a stepper that steps with stepsize h using an
// Explicit Runge-Kutte method determined by a Butcher
// tableau. 
//
// The stepsize is therefore not adaptively determined;
// so this type of stepper is mostly useful in attempting
// to categorize the different explicit RK Algorithms
// and probably not for real-life problems unless one has
// some a priori knowledge about how to set the stepsize.
//
#include "CLHEP/GenericFunctions/ButcherTableau.hh"
namespace Genfun {
  class SimpleRKStepper:public RKIntegrator::RKStepper{
    
  public:
    
    // Constructor:
    SimpleRKStepper(const ButcherTableau & tableau,
		    double stepsize);

    // Destructor:
    virtual ~SimpleRKStepper();

    // Take a step:
    virtual void step (const RKIntegrator::RKData       * data,  // functions 
		       const RKIntegrator::RKData::Data & sdata, // start point
		       RKIntegrator::RKData::Data       & ddata, // end point
		       double                         timeLimit  // time limit 
		       ) const ;
    // Clone:
    virtual SimpleRKStepper *clone() const;
    
private:

  ButcherTableau tableau;
  double stepsize;

  };
}

#endif
