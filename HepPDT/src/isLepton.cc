// $Id: isLepton.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// isLepton.cc
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
