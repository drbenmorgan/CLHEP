// -*- C++ -*-
//
// ----------------------------------------------------------------------
// StdEventPDescendants.cc
// L. Garren
// get descendants a specific GenParticle
// ----------------------------------------------------------------------

#include <vector>

#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/HepMC/GenParticle.h"

namespace StdHep  {

std::vector<HepMC::GenParticle*> StdEvent::descendants(HepMC::GenParticle* par) const
{
    // if this particle is valid, get the descendants
    if( par ) return par->listDescendants();
    // otherwise, return an empty vector
    std::vector<HepMC::GenParticle*> v;
    return v;
}

}  // StdHep
