// $Id: lifetime.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// lifetime.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ResonanceStructure.hh"

namespace HepPDT {

Measurement ResonanceStructure::lifetime(  )
{
    // width = hbar / lifetime
    static double epsilon = 1.0e-25;
    static double hbar = 6.58211889e-25; // in GeV s
    double life, err;
    if( itsTotalWidth.value() < epsilon ) {
        // this should actually be infinity
        return Measurement( 0., 0.);
    }
    life = hbar / itsTotalWidth.value();
    if( itsTotalWidth.sigma() < epsilon ) {
        err = 0.;
    } else {
        err = ( itsTotalWidth.sigma()/ itsTotalWidth.value() ) * life;
    }
    return Measurement( life, err );
}

}	// HepPDT
