// ----------------------------------------------------------------------
//
// particleMomentum.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/Vector/LorentzVector.h"

namespace HepMC  {

void GenParticle::setMomentum( double px, double py, double pz, double E )
{
   m_momentum = CLHEP::HepLorentzVector( px, py, pz, E); 
}

}  // HepMC
