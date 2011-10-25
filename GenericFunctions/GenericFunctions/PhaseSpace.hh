// This is a class the creates an N-Dimensional Phase Space     //

// It is for use in computing the time development of classical //
// Hamiltonian Systems.                                         //

// Joe Boudreau October 2011                                    //

//--------------------------------------------------------------//

#ifndef _PHASE_SPACE_
#define _PHASE_SPACE_
#include "CLHEP/GenericFunctions/Variable.hh"
#include <vector>

namespace Classical {

  class PhaseSpace {


  public:

    // A component is like a vector: of coordinates or momenta:
    class Component;

    // constructor
    PhaseSpace(unsigned int NDIM);

    // Destructor
    ~PhaseSpace();

    // Get the dimensionality:
    unsigned int dim() const;

    // Get the coordinates:
    const Component & coordinates() const;

    // Get the momenta:
    const Component & momenta()     const; 
    
    // Set starting values for the coordinates or momenta:
    void   start (const Genfun::Variable & variable, double value);

    // Get starting values for the coordinates or momenta:
    double startValue(const Genfun::Variable & component) const ;


    // Each component has N-dimensions:
    class Component {
      
    public:
      
      // Access to the ith element;
      Genfun::Variable operator [] (unsigned int i) const; 
     
    private:

      // Constructor:
      Component(unsigned int NDIM, bool isMomentum);

      // Destructor:
      ~Component();
      
      // Illegal operations:
      Component (const Component &);
      Component & operator=(const Component &);

      // Internal clockwork;
      class Clockwork;
      Clockwork *c;
      friend class PhaseSpace; 

    };
      
  private:

    Component _coordinates; 
    Component _momenta;
    std::vector<double> _q0;
    std::vector<double> _p0;
    unsigned int DIM;
  };

}
#endif

