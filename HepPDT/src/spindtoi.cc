// ----------------------------------------------------------------------
//
// spindtoi.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int spindtoi( double spin )
{
    int is = (int)(spin*2.0);
    return abs(is)+1;
}

} // HepPDT
