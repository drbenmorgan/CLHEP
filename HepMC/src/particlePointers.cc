// $Id: particlePointers.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// particlePointers.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepMC/GenVertex.h"
#include "CLHEP/HepMC/GenParticle.h"

namespace HepMC  {

GenParticle *      GenParticle::mother()          const
{
    if( !m_production_vertex ) {
        return NULL;
    }
    return m_production_vertex->mother();
}

GenParticle *      GenParticle::secondMother()    const
{
    if( !m_production_vertex ) {
        return NULL;
    }
    return m_production_vertex->secondMother();
}

GenParticle *      GenParticle::beginDaughters()  const
{
    if( !m_end_vertex ) {
        return NULL;
    }
    return m_end_vertex->beginDaughters();
}

GenParticle *      GenParticle::endDaughters()    const
{
    if( !m_end_vertex ) {
        return NULL;
    }
    return m_end_vertex->endDaughters();
}


}  // HepMC
