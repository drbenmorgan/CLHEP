//////////////////////////////////////////////////////////////////////////
// 
// vertexHas.cc
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"
#include <vector> 

namespace HepMC {

bool GenVertex::hasParents() const
{
    if( particles_in_size() < 1 ) return false;
    return true;
}

bool GenVertex::hasChildren() const
{
    if( particles_out_size() < 1 ) return false;
    return true;
}

} // HepMC

