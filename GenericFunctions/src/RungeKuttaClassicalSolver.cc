#include "CLHEP/GenericFunctions/RungeKuttaClassicalSolver.hh"
#include "CLHEP/GenericFunctions/RKIntegrator.hh"
namespace Classical {
  //
  // This is the private innards of RungeKuttaSolver
  //
  class RungeKuttaSolver::Clockwork {
  public:
    Clockwork(Genfun::GENFUNCTION gH, const PhaseSpace & mphaseSpace):H(gH),phaseSpace(mphaseSpace){}
    Genfun::GENFUNCTION H;
    const Classical::PhaseSpace & phaseSpace;
    Genfun::RKIntegrator          integrator;
    std::vector<Genfun::Parameter*> startingQ;
    std::vector<Genfun::Parameter*> startingP;
    Genfun::EnergyFunction          *energy;
  };

  RungeKuttaSolver::RungeKuttaSolver(Genfun::GENFUNCTION gH, const PhaseSpace & mphaseSpace):c(new Clockwork(gH,mphaseSpace)){
    //
    // Dimension (of coords, or phase space)
    //
    const unsigned int DIM=c->phaseSpace.dim();
    //
    // Equations of motion via hamilton's equations: 
    //
    const Classical::PhaseSpace::Component & X=c->phaseSpace.coordinates();
    const Classical::PhaseSpace::Component & P=c->phaseSpace.momenta();
    
    for (unsigned int i=0;i<DIM;i++) {
      Genfun::GENFUNCTION DXDT  =  c->H.partial(P[i].index());
      c->startingQ.push_back(c->integrator.addDiffEquation(&DXDT,"X",c->phaseSpace.startValue(X[i])));
    }
    for (unsigned int i=0;i<DIM;i++) {
      Genfun::GENFUNCTION DPDT  = -c->H.partial(X[i].index());
      c->startingP.push_back(c->integrator.addDiffEquation(&DPDT,"P",c->phaseSpace.startValue(P[i])));
    }
    c->energy=NULL;
    
  }
  RungeKuttaSolver::~RungeKuttaSolver(){
    delete c->energy;
    delete c;
  }

  Genfun::GENFUNCTION RungeKuttaSolver::equationOf(const Genfun::Variable & v) const {
    return *c->integrator.getFunction(v.index());
  }
  Genfun::GENFUNCTION RungeKuttaSolver::hamiltonian() const {
    return c->H;
  }
  const Classical::PhaseSpace & RungeKuttaSolver::phaseSpace() const {
    return c->phaseSpace;
  }
  Genfun::GENFUNCTION RungeKuttaSolver::energy() const {
    if (!c->energy) c->energy=new Genfun::EnergyFunction(*this);
    return *c->energy;
  }

  Genfun::Parameter *RungeKuttaSolver::createControlParameter(const std::string & variableName,
								      double defStartingValue,
								      double startingValueMin,
								      double startingValueMax) const {
    return c->integrator.createControlParameter(variableName, defStartingValue, startingValueMin, startingValueMax) ;
  }
      
  Genfun::Parameter *RungeKuttaSolver::takeQ0(unsigned int index) {
    return c->startingQ[index];
  }
  Genfun::Parameter *RungeKuttaSolver::takeP0(unsigned int index) {
    return c->startingP[index];
  }

}
