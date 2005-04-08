// ----------------------------------------------------------------------
//
// isLepton.cc
// Author: Lynn Garren
//
//  check to see if this is a valid meson
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

bool ParticleID::isLepton( ) const
{
    if( extraBits() > 0 ) { return false; }
    if( fundamentalID() >= 11 && fundamentalID() <= 18 ) { return true; }
    return false;
}

} // HepPDT
