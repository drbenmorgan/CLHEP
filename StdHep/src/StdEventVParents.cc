// -*- C++ -*-
//
// ----------------------------------------------------------------------
// StdEventVParents.cc
// L. Garren
// get parents of a specific GenVertex
// ----------------------------------------------------------------------

#include <vector>

#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"

namespace StdHep  {

std::vector<HepMC::GenParticle*> StdEvent::parents(HepMC::GenVertex* gv) const
{
    // if this vertex is valid, get the parents
    if( gv ) return gv->listParents();
    // otherwise, return an empty vector
    std::vector<HepMC::GenParticle*> v;
    return v;
}

}  // StdHep
