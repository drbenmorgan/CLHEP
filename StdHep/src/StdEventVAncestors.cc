// $Id: StdEventVAncestors.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// ----------------------------------------------------------------------
// StdEventVAncestors.cc
// L. Garren
// get ancestors a specific GenVertex
// ----------------------------------------------------------------------

#include <vector>

#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"

namespace StdHep  {

std::vector<HepMC::GenParticle*> StdEvent::ancestors(HepMC::GenVertex* gv) const
{
    // if this vertex is valid, get the ancestors
    if( gv ) return gv->listAncestors();
    // otherwise, return an empty vector
    std::vector<HepMC::GenParticle*> v;
    return v;
}

}  // StdHep
