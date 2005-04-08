// ----------------------------------------------------------------------
//
// isHadron.cc
// Author: Lynn Garren
//
//  check to see if this is a valid meson
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

bool ParticleID::isHadron( ) const
{
    if( extraBits() > 0 ) { return false; }
    if( isMeson() )   { return true; }
    if( isBaryon() )  { return true; }
    if( isPentaquark() ) { return true; }
    return false;
}

} // HepPDT
