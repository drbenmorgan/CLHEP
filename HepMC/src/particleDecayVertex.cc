// ----------------------------------------------------------------------
//
// particleDecayVertex.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"

namespace HepMC  {

CLHEP::HepLorentzVector   GenParticle::decayVertex() const	
{
   // empty if there is no vertex
   CLHEP::HepLorentzVector dv(0,0,0,0);
   if( m_end_vertex ) {
       dv = m_end_vertex->position();
   }
   return dv;
}

}  // HepMC
