// $Id: isValid.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// isValid.cc
//
//  check to see if this is a valid PID
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

bool ParticleID::isValid( ) const
{
    if( extraBits() > 0 ) {
        if( isNucleus() )   { return true; }
        return false; 
    }
    // Meson signature
    if( isMeson() )   { return true; }
    // Baryon signature
    if( isBaryon() )  { return true; }
    // DiQuark signature
    if( isDiQuark() ) { return true; }
    // fundamental particle
    if( fundamentalID() > 0 ) { return true; }
    return false;
}

} // HepPDT
