// ----------------------------------------------------------------------
//
// extraBits.cc
// Author: Lynn Garren
//
// returns everything beyond the 7th digit (e.g. outside the numbering scheme)
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int ParticleID::extraBits( ) const
{
    return abspid()/10000000;
}

} // HepPDT
