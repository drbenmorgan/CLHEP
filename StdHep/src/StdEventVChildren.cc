// -*- C++ -*-
//
// ----------------------------------------------------------------------
// StdEventVChildren.cc
// L. Garren
// get children of a specific GenVertex
// ----------------------------------------------------------------------

#include <vector>

#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"

namespace StdHep  {

std::vector<HepMC::GenParticle*> StdEvent::children(HepMC::GenVertex* gv) const
{
    // if this vertex is valid, get the children
    if( gv ) return gv->listChildren();
    // otherwise, return an empty vector
    std::vector<HepMC::GenParticle*> v;
    return v;
}

}  // StdHep
