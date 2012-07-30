#ifndef _AdaptiveRKStepper_h_
#define _AdaptiveRKStepper_h_
#include "CLHEP/GenericFunctions/RKIntegrator.hh"
//
// This is the default RKStepper routine, used within the RKIntegrator
// when no other stepper is provided.  
//
namespace Genfun {

  class AdaptiveRKStepper:public RKIntegrator::RKStepper {
    
  public:
    
    class EEStepper;

    // Constructor:
    AdaptiveRKStepper(double stepsize=0.01, const EEStepper *eeStepper=NULL);

    // Copy constructor:
    AdaptiveRKStepper(const AdaptiveRKStepper & right);

    // Destructor:
    virtual ~AdaptiveRKStepper();

    // Takes *multiple* steps if needed up to or exceeding the
    // specified time:
    virtual void step (const RKIntegrator::RKData       * data, 
		       const RKIntegrator::RKData::Data & sdata, 
		       RKIntegrator::RKData::Data       & ddata, 
		       double                             timeLimit) const ;
    // Clone
    virtual AdaptiveRKStepper *clone() const;
    
  private:
    
    // It is illegal to assign an AdaptiveRKStepper:
    AdaptiveRKStepper & operator=(const AdaptiveRKStepper & right);

    const double              startingStepsize;
    mutable      double       stepsize;
    const        EEStepper   *eeStepper;
  };


  // 
  // An abstract base class for steppers that return an error
  // estimate at each step:
  //
  class AdaptiveRKStepper::EEStepper {
  public:
    
    virtual ~EEStepper();
    virtual void step   (const RKIntegrator::RKData       * data, 
			 const RKIntegrator::RKData::Data & sdata, 
			 RKIntegrator::RKData::Data       & ddata, 
			 std::vector<double> & errors) const = 0;
    virtual EEStepper *clone() const=0;
    virtual unsigned int order() const=0;
  };
}

#endif
