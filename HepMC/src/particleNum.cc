// $Id: particleNum.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// particleNum.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepMC/GenVertex.h"
#include "CLHEP/HepMC/GenParticle.h"

namespace HepMC  {

int  GenParticle::numParents() const
{
    if( !m_production_vertex ) return 0;
    return m_production_vertex->particles_in_size();
}

int  GenParticle::numChildren() const
{
    if( !m_end_vertex ) return 0;
    return m_end_vertex->particles_out_size();
}

}  // HepMC
