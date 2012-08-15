#include "CLHEP/GenericFunctions/SimpleRKStepper.hh"
#include <cmath>
#include <stdexcept>
namespace Genfun {
  SimpleRKStepper::SimpleRKStepper(const ButcherTableau & mtableau,double xstepsize):
    tableau(mtableau),
    stepsize(xstepsize) 
  {
  }

  void SimpleRKStepper::step(const RKIntegrator::RKData       * data, 
			     const RKIntegrator::RKData::Data & s, 
			     RKIntegrator::RKData::Data       & d, 
			     double                             timeLimit ) const {
    const double h = timeLimit==0 ? stepsize : timeLimit - s.time;
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
    d.time = timeLimit==0 ? s.time + h : timeLimit;
    
  }
  
  SimpleRKStepper::~SimpleRKStepper(){}
  
  SimpleRKStepper *SimpleRKStepper::clone() const {
    return new SimpleRKStepper(*this);
  }
}
