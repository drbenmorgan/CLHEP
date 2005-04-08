// ----------------------------------------------------------------------
//
// TempParticleData.cc
// Author: Lynn Garren
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
