// ----------------------------------------------------------------------
//
// isDiQuark.cc
// Author: Lynn Garren
//
//  check to see if this is a valid meson
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

bool ParticleID::isDiQuark( ) const
{
    if( extraBits() > 0 ) { return false; }
    if( abspid() <= 100 ) { return false; }
    if( fundamentalID() <= 100 && fundamentalID() > 0 ) { return false; }
    if( digit(nj) > 0 && digit(nq3) == 0 && digit(nq2) > 0 && digit(nq1) > 0 ) {  // diquark signature
       if( digit(nj) == 1 && digit(nq2) == digit(nq1) ) { 	// illegal
          return false; 
       } else {
          return true;
       }
    }
    return false;
}

} // HepPDT
