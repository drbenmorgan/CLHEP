#ifndef _EmbeddedRKStepper_hh_
#define _EmbeddedRKStepper_hh_
#include "CLHEP/GenericFunctions/AdaptiveRKStepper.hh"
#include "CLHEP/GenericFunctions/ExtendedButcherTableau.hh"
//
// Class EmbeddedRK stepper is a class at that implements
// Fehlberg algorithms, or embedded Runge-Kutta Algorithms.  
//
namespace Genfun {

  class EmbeddedRKStepper: public AdaptiveRKStepper::EEStepper {

  public:
    
    // Constructor:
    EmbeddedRKStepper(const ExtendedButcherTableau & tableau=CashKarpXtTableau());
    
    // Destructor:
    virtual ~EmbeddedRKStepper();
    
    // Take a single step with error estimate:
    virtual void step   (const RKIntegrator::RKData       * data, 
			 const RKIntegrator::RKData::Data & sdata, 
			 RKIntegrator::RKData::Data       & ddata, 
			 std::vector<double>              & errors) const;
    // Clone self:
    virtual EmbeddedRKStepper *clone() const;

    // Return the order:
    virtual unsigned int order() const;
  private:
    ExtendedButcherTableau tableau;
  };
}
#endif
