#include "CLHEP/GenericFunctions/PhaseSpace.hh"
#include <vector>

// Three classes are defined here:

// 1) Classical::PhaseSpace::Component::Clockwork
// 2) Classical::PhaseSpace::Component
// 2) Classical::PhaseSpace


namespace Classical {

  //------------------------------------------------//
  //                                                //
  // 1. Classical::PhaseSpace::Component::Clockwork //
  // This class just holds variables:               //
  //                                                //
  //------------------------------------------------//
  class PhaseSpace::Component::Clockwork {
 
  public:
    
    // Constructor:
    Clockwork(){};

    // Destructor 
    ~Clockwork () { for (size_t i=0;i<functions.size();i++) delete functions [i];}

    //
    std::vector<const Genfun::Variable *> functions;
    
  };

  //------------------------------------------------//
  //                                                //
  // 2. Classical::PhaseSpace::Component            //
  // This class gives access to the variables that  //
  // make up the coordinates and momenta.           //
  //                                                //
  //------------------------------------------------//

  PhaseSpace::Component::Component(unsigned int NDIM, bool isMomenta) : c(new Clockwork()) {
    for (unsigned int i=0;i<NDIM;i++) {
      int offset= isMomenta ? NDIM:0;
      c->functions.push_back(new Genfun::Variable(i+offset, 2*NDIM));
    }
  }
  
  PhaseSpace::Component::~Component() {
    delete c;
  }
  
  Genfun::Variable PhaseSpace::Component::operator[] (unsigned int i) const {
    return *(c->functions[i]);
  }
  
  PhaseSpace::PhaseSpace(unsigned int NDIM):
    _coordinates(NDIM,false),_momenta(NDIM,true),_q0(NDIM),_p0(NDIM),DIM(NDIM)
  {
  }

  PhaseSpace::~PhaseSpace()
  {
  }
  
  const PhaseSpace::Component & PhaseSpace::coordinates() const {
    return _coordinates;
  }

  const PhaseSpace::Component & PhaseSpace::momenta() const {
    return _momenta;
  }


  void PhaseSpace::start (const Genfun::Variable & v, double value){
    unsigned int index =v.index();
    if (index<DIM) {
      _q0[index] = value;
    }
    else 
    {
      _p0[index-DIM] = value;
    }
  }


  double PhaseSpace::startValue(const Genfun::Variable & v) const {
    unsigned int index =v.index();
    if (index<DIM) {
      return _q0[index];
    }
    else 
    {
      return _p0[index-DIM];
    }
  }

  unsigned int PhaseSpace::dim() const {
    return DIM;
  }
}
