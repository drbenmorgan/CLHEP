#include "CLHEP/GenericFunctions/StepDoublingRKStepper.hh"
#include <stdexcept>
#include <cmath>
namespace Genfun {

  
  StepDoublingRKStepper::StepDoublingRKStepper(const ButcherTableau & xtableau):tableau(xtableau) {
  }

  StepDoublingRKStepper::~StepDoublingRKStepper() {
  }

  void StepDoublingRKStepper::step   (const RKIntegrator::RKData       * data, 
				      const RKIntegrator::RKData::Data & s, 
				      RKIntegrator::RKData::Data       & d, 
				      std::vector<double>              & errors) const {
    const unsigned int nvar = s.variable.size();
    RKIntegrator::RKData::Data d1(nvar),d2(nvar);

    doStep(data,s,d);
    double dt = (d.time - s.time);
    d1.time = s.time + dt/2.0;
    d2.time = d.time;

    doStep(data, s,d1);
    doStep(data,d1,d2);

    // Error estimate:
    errors.resize(nvar);
    for (size_t v=0;v<nvar;v++) errors[v]=fabs(d2.variable[v]-d.variable[v]);

    // Final correction:
    for (size_t v=0;v<nvar;v++) d.variable[v] = d2.variable[v] + ((d2.variable[v]-d.variable[v])/double(std::pow(2.,(int)(tableau.order())-1)));

  }
  
  void StepDoublingRKStepper::doStep(const RKIntegrator::RKData       * data, 
				     const RKIntegrator::RKData::Data & s, 
				     RKIntegrator::RKData::Data       & d) const {
    // First step:
    double h = (d.time - s.time);
    
    
    if (h<=0) throw std::runtime_error ("SimpleRKStepper:  negative stepsize");
    const unsigned int nvar = s.variable.size();
    // Compute all of the k's..:
    //
    std::vector<std::vector<double> >k(tableau.nSteps());
    for (unsigned int i=0;i<tableau.nSteps();i++) {
      k[i].resize(nvar,0);
      Argument arg(nvar);
      for (unsigned int v=0;v<nvar;v++) arg[v]=s.variable[v];
      for (unsigned int j=0;j<i;j++) {
	for (unsigned int v=0;v<nvar;v++) arg[v] += h*tableau.A(i,j)*k[j][v];
      }
      for (unsigned int v=0;v<nvar;v++) k[i][v]=(*data->_diffEqn[v])(arg);
    }
    //
    // Final result.
    //
    for (unsigned int v=0;v<nvar;v++) d.firstDerivative[v] = 0;
    for (unsigned int i=0;i<tableau.nSteps();i++) {
      for (unsigned int v=0;v<nvar;v++) d.firstDerivative[v] += tableau.b(i)*k[i][v];
    }
    for (unsigned int v=0;v<nvar;v++)   d.variable[v] =s.variable[v]+h*d.firstDerivative[v];
				         
  }




  StepDoublingRKStepper *StepDoublingRKStepper::clone() const {
    return new StepDoublingRKStepper(*this);
  }

  unsigned int StepDoublingRKStepper::order() const {
    return tableau.order();
  }


}
