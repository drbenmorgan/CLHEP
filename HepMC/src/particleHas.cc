// $Id: particleHas.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// particleHas.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepMC/GenVertex.h"
#include "CLHEP/HepMC/GenParticle.h"

namespace HepMC  {

bool GenParticle::hasParents() const
{
    if( !m_production_vertex ) return false;
    if( m_production_vertex->particles_in_size() < 1 ) return false;
    return true;
}

bool GenParticle::hasChildren() const
{
    if( !m_end_vertex ) return false;
    if( m_end_vertex->particles_out_size() < 1 ) return false;
    return true;
}

}  // HepMC
