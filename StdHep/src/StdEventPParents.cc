// -*- C++ -*-
//
// ----------------------------------------------------------------------
// StdEventPParents.cc
// L. Garren
// get parents of a specific GenParticle
// ----------------------------------------------------------------------

#include <vector>

#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/HepMC/GenParticle.h"

namespace StdHep  {

std::vector<HepMC::GenParticle*> StdEvent::parents(HepMC::GenParticle* par) const
{
    // if this particle is valid, get the parents
    if( par ) return par->listParents();
    // otherwise, return an empty vector
    std::vector<HepMC::GenParticle*> v;
    return v;
}

}  // StdHep
