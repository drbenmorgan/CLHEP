#include "CLHEP/GenericFunctions/AdaptiveRKStepper.hh"
#include "CLHEP/GenericFunctions/EmbeddedRKStepper.hh"
#include <cmath>
#include <stdexcept>
namespace Genfun {

  AdaptiveRKStepper::AdaptiveRKStepper(double startingStepsize, const EEStepper *stepper):
    startingStepsize(startingStepsize),
    stepsize(startingStepsize),
    eeStepper(stepper ? stepper->clone():new EmbeddedRKStepper())
  {
  }

  AdaptiveRKStepper::AdaptiveRKStepper(const AdaptiveRKStepper & right):
    startingStepsize(right.startingStepsize),
    stepsize(right.startingStepsize),
    eeStepper(right.eeStepper->clone())
  {
  }


  void AdaptiveRKStepper::step(const RKIntegrator::RKData       * data, 
			      const RKIntegrator::RKData::Data & s, 
			      RKIntegrator::RKData::Data       & d,
			      double                             timeLimit) const {
    //
    // Adaptive stepsize control
    //
    if (s.time==0.0) {
      stepsize=startingStepsize;
    }
    const unsigned int p = eeStepper->order();  // Order of the stepper
    const double       T    = 1.0E-6;           // This is the tolerance:
    const double       S    = 0.9;              // Safety factor;
    const double       Rmax = 5;                // Maximum growth factor
    const double       Rmin = 0.0;              // Minimum growth factor
    const double deltaMax = T*pow(S/Rmax, p+1); // Maximum error 4 adjustment.
    const double TINY   = 1.0E-30;              // Denominator regularization
    double hnext;
    //
    // Time limited step ? 
    // 
    d.time= timeLimit==0? s.time+stepsize : timeLimit;

    //--------------------------------------//
    // Take one step, from s to d:    //
    //--------------------------------------//
    double h = d.time-s.time;
    while (1) {
      std::vector<double> errors;
      eeStepper->step(data, s, d, errors);
      if (timeLimit!=0.0) return;
      
      // Take absolute value:
      for (size_t e=0;e<errors.size();e++) errors[e] = fabs(errors[e]);
    
      // Select the largest:
      double delta = (*std::max_element(errors.begin(),errors.end()));
      if (delta > 1) {
	//
	// Bail out and try a smaller step.
	//
	h = std::max(S*h*pow(T/(delta + TINY), 1.0/(p+1)),Rmin*h);
	if  (!(((float) s.time+h - (float) s.time) > 0) ) {
	  std::cerr << "Warning, RK Integrator step underflow" << std::endl;
	}
	d.time = s.time+h;
	hnext=h;
	continue;
      }
      else {
	if (delta > deltaMax) {
	  hnext = S*h*pow(T/(delta + TINY),1.0/(p+1));
	}
	else {
	  hnext = Rmax*h;
	}
      }
      break;
    }
    stepsize=hnext;
    return;
  }
  


  AdaptiveRKStepper::~AdaptiveRKStepper(){
    delete eeStepper;
  }
  
  AdaptiveRKStepper *AdaptiveRKStepper::clone() const {
    return new AdaptiveRKStepper(*this);
  }

  AdaptiveRKStepper::EEStepper::~EEStepper() {
  }
}
