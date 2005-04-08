// -*- C++ -*-
//
// ----------------------------------------------------------------------
// StdEventPAncestors.cc
// L. Garren
// get ancestors a specific GenParticle
// ----------------------------------------------------------------------

#include <vector>

#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/HepMC/GenParticle.h"

namespace StdHep  {

std::vector<HepMC::GenParticle*> StdEvent::ancestors(HepMC::GenParticle* par) const
{
    // if this particle is valid, get the ancestors
    if( par ) return par->listAncestors();
    // otherwise, return an empty vector
    std::vector<HepMC::GenParticle*> v;
    return v;
}

}  // StdHep
