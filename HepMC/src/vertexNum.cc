//////////////////////////////////////////////////////////////////////////
// 
// vertexNum.cc
//
//  These methods are for consistency with GenParticle, 
//  which has no particles_xxx_size() methods
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"
#include <vector> 

namespace HepMC {

int  GenVertex::numParents() const
{
    return particles_in_size();
}

int  GenVertex::numChildren() const
{
    return particles_out_size();
}

} // HepMC

