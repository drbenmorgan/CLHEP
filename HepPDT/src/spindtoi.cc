// $Id: spindtoi.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// spindtoi.cc

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int spindtoi( double spin )
{
    int is = (int)(spin*2.0);
    return abs(is)+1;
}

} // HepPDT
