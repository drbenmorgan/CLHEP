// $Id: getParticleID.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
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
