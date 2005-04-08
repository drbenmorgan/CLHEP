// ----------------------------------------------------------------------
//
// spinitod.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

double spinitod( int js )
{
    int spin = abs(js);
    if( spin == 0 ) {
        return 0;
    } else {
        return double(spin-1)/2.0;
    }
}

} // HepPDT
