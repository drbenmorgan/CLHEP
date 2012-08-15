#include "CLHEP/GenericFunctions/EmbeddedRKStepper.hh"
#include "CLHEP/GenericFunctions/ExtendedButcherTableau.hh"
#include <stdexcept>
namespace Genfun {

  
  EmbeddedRKStepper::EmbeddedRKStepper(const ExtendedButcherTableau & mtableau):
    tableau(mtableau){
  }

  EmbeddedRKStepper::~EmbeddedRKStepper() {
  }

  void EmbeddedRKStepper::step   (const RKIntegrator::RKData       * data, 
				  const RKIntegrator::RKData::Data & s, 
				  RKIntegrator::RKData::Data       & d, 
				  std::vector<double>              & errors) const {

    // First step:
    double h = d.time - s.time;
    if (h<=0) throw std::runtime_error ("Runtime error in RKIntegrator (zero or negative stepsize)");
    unsigned int nvar = s.variable.size();

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
    // 
    // 
    //
    errors.resize(nvar);
    for (unsigned int v=0;v<nvar;v++) errors[v] = 0;
    for (unsigned int i=0;i<tableau.nSteps();i++) {
      for (unsigned int v=0;v<nvar;v++) errors[v] += (h*(tableau.bHat(i)-tableau.b(i))*k[i][v]);
    }
    return;
  }

  EmbeddedRKStepper *EmbeddedRKStepper::clone() const {
    return new EmbeddedRKStepper(*this);
  }

  unsigned int EmbeddedRKStepper::order() const {
    return tableau.order();
  }
}
