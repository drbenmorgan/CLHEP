// $Id: isHadron.cc,v 1.1.1.1.2.1 2005/03/17 22:42:53 garren Exp $
// ----------------------------------------------------------------------
//
// isHadron.cc
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
