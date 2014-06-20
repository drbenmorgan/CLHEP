#ifndef _StepDoublingRKStepper_hh_
#define _StepDoublingRKStepper_hh_
#include "CLHEP/GenericFunctions/AdaptiveRKStepper.hh"
#include "CLHEP/GenericFunctions/ButcherTableau.hh"
//
// Class StepDoublingRK stepper is a class at that implements
// Fehlberg algorithms, or embedded Runge-Kutta Algorithms.  
//
namespace Genfun {

  class StepDoublingRKStepper: public AdaptiveRKStepper::EEStepper {

  public:
    
    // Constructor:
    StepDoublingRKStepper(const ButcherTableau & tableau);
    
    // Destructor:
    virtual ~StepDoublingRKStepper();
    
    // Take a single step with error estimate:
    virtual void step   (const RKIntegrator::RKData       * data, 
			 const RKIntegrator::RKData::Data & sdata, 
			 RKIntegrator::RKData::Data       & ddata, 
			 std::vector<double>              & errors) const;
    // Clone self:
    virtual StepDoublingRKStepper *clone() const;
    
    void doStep(const RKIntegrator::RKData       * data, 
		const RKIntegrator::RKData::Data & s, 
		RKIntegrator::RKData::Data       & d) const;

    virtual unsigned int order() const;

  private:
    ButcherTableau tableau;

  };
}
#endif
