// $Id: calculateWidthFromLifetime.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// TempParticleData.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/TempParticleData.hh"

namespace HepPDT {

double calculateWidthFromLifetime( double lt )
{
    // totalwidth = hbar / lifetime
    static double epsilon = 1.0e-20;
    static double hbar = 6.58211889e-25; // in GeV s
    if( lt < epsilon ) { return 0.; }
    return hbar/lt;
}

}	// HepPDT
