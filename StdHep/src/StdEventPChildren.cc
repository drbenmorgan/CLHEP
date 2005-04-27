// -*- C++ -*-
//
// ----------------------------------------------------------------------
// StdEventPChildren.cc
// L. Garren
// get children of a specific GenParticle
// ----------------------------------------------------------------------

#include <vector>

#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/HepMC/GenParticle.h"

namespace StdHep  {

std::vector<HepMC::GenParticle*> StdEvent::children(HepMC::GenParticle* par) const
{
    // if this particle is valid, get the children
    if( par ) return par->listChildren();
    // otherwise, return an empty vector
    std::vector<HepMC::GenParticle*> v;
    return v;
}

}  // StdHep
