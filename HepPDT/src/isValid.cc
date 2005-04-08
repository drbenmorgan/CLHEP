// ----------------------------------------------------------------------
//
// isValid.cc
// Author: Lynn Garren
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
    // pentaquark
    if( isPentaquark() ) { return true; }
    // don't recognize this number
    return false;
}

} // HepPDT
