// ----------------------------------------------------------------------
//
// isMeson.cc
// Author: Lynn Garren
//
//  check to see if this is a valid meson
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

bool ParticleID::isMeson( ) const
{
    if( extraBits() > 0 ) { return false; }
    if( abspid() <= 100 ) { return false; }
    if( fundamentalID() <= 100 && fundamentalID() > 0 ) { return false; }
    int aid = abspid();
    int id = pid();
    if( aid == 130 || aid == 310 || aid == 210 ) { return true; }
    if( id == 110 || id == 220 || id == 330 || id == 440 ) { return true; }
    if( digit(nj) > 0 && digit(nq3) > 0 && digit(nq2) > 0 && digit(nq1) == 0 ) {
        // check for illegal antiparticles
        if( digit(nq3) == digit(nq2) && pid() < 0 ) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

} // HepPDT
