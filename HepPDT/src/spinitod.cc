// $Id: spinitod.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// spinitod.cc

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
