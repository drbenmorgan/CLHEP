// ----------------------------------------------------------------------
//
// fundamentalID.cc
// Author: Lynn Garren
//
//  return the first two digits if this is a "fundamental" particle
//  ID = 100 is a special case (internal generator ID's are 81-100)
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {


int ParticleID::fundamentalID( ) const
{
    if( digit(nq2) == 0 && digit(nq1) == 0) {
        return abspid()%10000;
    } else if( abspid() <= 100 ) {
        return abspid();
    } else {
        return 0;
    }
}

} // HepPDT
