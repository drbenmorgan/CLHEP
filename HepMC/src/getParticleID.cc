// ----------------------------------------------------------------------
//
// getParticleID.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepMC  {

HepPDT::ParticleID   GenParticle::particleID()   const
{
    return HepPDT::ParticleID( m_pdg_id);
}

}  // HepMC
