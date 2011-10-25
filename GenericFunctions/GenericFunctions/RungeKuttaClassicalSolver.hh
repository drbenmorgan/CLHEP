// This is a class the creates an N-Dimensional Phase Space     //

// It is for use in computing the time development of classical //
// Hamiltonian Systems.                                         //

// Joe Boudreau October 2011                                    //

//--------------------------------------------------------------//

#ifndef _RKClassicalSolver_h__
#define _RKClassicalSolver_h__
#include "CLHEP/GenericFunctions/PhaseSpace.hh"
#include "CLHEP/GenericFunctions/ClassicalSolver.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include <vector>

namespace Classical {
  
  class RungeKuttaSolver : public Solver {
    
  public:
    //
    // Constructor--takes a hamiltonian and a point in p-space: 
    //
    RungeKuttaSolver(Genfun::GENFUNCTION H, const PhaseSpace & phaseSpace);
    //
    // Destructor:
    //
    ~RungeKuttaSolver();
    //
    // Returns the time evolution for a variable (q_i or p_i)
    //
    virtual Genfun::GENFUNCTION equationOf(const Genfun::Variable & v) const; 
    //
    // Returns the phase space 
    //
    virtual const PhaseSpace & phaseSpace() const;
    //
    // Returns the Hamiltonian (function of the 2N phase space variables). 
    //
    virtual Genfun::GENFUNCTION hamiltonian() const;
    //
    // Returns the energy (function of time).
    //
    virtual Genfun::GENFUNCTION energy() const;
    //
    // This is in the rare case that the user needs to edit starting values.
    // or parameterize the Hamiltonian.  Most users:  can ignore.  
    virtual Genfun::Parameter *takeQ0(unsigned int index);
    virtual Genfun::Parameter *takeP0(unsigned int index);
    virtual Genfun::Parameter *createControlParameter(const std::string & variableName="anon",
						      double defStartingValue=0.0,
						      double startingValueMin=0.0,
						      double startingValueMax=0.0) const;
    


  private:
    
    // Illegal Operations:
    RungeKuttaSolver (const RungeKuttaSolver &);
    RungeKuttaSolver & operator=(const RungeKuttaSolver &);
    
    // Clockwork 
    class Clockwork;
    Clockwork *c;
  };
  
}

#endif
