// -*- C++ -*-
//
// ----------------------------------------------------------------------
// StdEventVDescendants.cc
// L. Garren
// get descendants a specific GenVertex
// ----------------------------------------------------------------------

#include <vector>

#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"

namespace StdHep  {

std::vector<HepMC::GenParticle*> StdEvent::descendants(HepMC::GenVertex* gv) const
{
    // if this vertex is valid, get the descendants
    if( gv ) return gv->listDescendants();
    // otherwise, return an empty vector
    std::vector<HepMC::GenParticle*> v;
    return v;
}

}  // StdHep
