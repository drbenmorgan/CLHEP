// $Id: vertexPointers.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// vertexPointers.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepMC/GenVertex.h"
#include "CLHEP/HepMC/GenParticle.h"

namespace HepMC  {

GenParticle *      GenVertex::mother()          const
{
    if( particles_in_size() < 1 ) return NULL;
    return *m_particles_in.begin();
}

GenParticle *      GenVertex::secondMother()    const
{
    if( particles_in_size() < 1 ) return NULL;
    particles_in_const_iterator iv = particles_in_const_end();
    --iv;
    return *iv;
}

GenParticle *      GenVertex::beginDaughters()  const
{
    if( particles_out_size() < 1 ) return NULL;
    return *m_particles_out.begin();
}

GenParticle *      GenVertex::endDaughters()    const
{
    if( particles_out_size() < 1 ) return NULL;
    particles_out_const_iterator iv = particles_in_const_end();
    --iv;
    return *iv;
}


}  // HepMC
