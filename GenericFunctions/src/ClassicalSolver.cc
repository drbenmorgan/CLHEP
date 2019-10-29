// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/ClassicalSolver.hh"
#include "CLHEP/GenericFunctions/PhaseSpace.hh"
#include <cmath>

namespace Genfun {
  
  FUNCTION_OBJECT_IMP(EnergyFunction)

  EnergyFunction::EnergyFunction(const Classical::Solver & xsolver):
  solver(xsolver)
  {}
  
  EnergyFunction::~EnergyFunction() {
  }
  
  EnergyFunction::EnergyFunction(const EnergyFunction & right) 
    :AbsFunction(right), solver(right.solver)
  {  }
  
  
  double EnergyFunction::operator() (double t) const {
    const Classical::PhaseSpace & phaseSpace=solver.phaseSpace();
    const unsigned int DIM=phaseSpace.dim();
    Genfun::Argument arg(2*DIM);
    for (unsigned int i=0;i<phaseSpace.dim();i++) {
      arg[i]    =solver.equationOf(phaseSpace.coordinates()[i])(t);
      arg[i+DIM]=solver.equationOf(phaseSpace.momenta()[i])(t);
    }
    Genfun::GENFUNCTION H = solver.hamiltonian(); 
    return H(arg);
  }


} // namespace Genfun
