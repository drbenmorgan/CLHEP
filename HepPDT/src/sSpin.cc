// ----------------------------------------------------------------------
//
// sSpin.cc
// Author: Lynn Garren
//
//  return the spin - valid for mesons only
//
// ----------------------------------------------------------------------

#include <stdlib.h>

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int ParticleID::sSpin( ) const
{
    int nl, tent, js;
    if( !isMeson() ) { return 0; }
    nl = (abspid()/10000)%10;
    tent = (abspid()/1000000)%10;
    js = abspid()%10;
    if( tent == 9 ) { return 0; }	// tentative assignment
    if( nl == 0 && js >= 3 ) { 
        return 1;
    } else if( nl == 0  && js == 1 ) {
        return 0;
    } else if( nl == 1  && js >= 3 ) {
        return 0;
    } else if( nl == 2  && js >= 3 ) {
        return 1;
    } else if( nl == 1  && js == 1 ) {
        return 1;
    } else if( nl == 3  && js >= 3 ) {
        return 1;
    }
    // default to zero
    return 0;
}

} // HepPDT
