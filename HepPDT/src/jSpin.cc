// ----------------------------------------------------------------------
//
// jSpin.cc
// Author: Lynn Garren
//
//  return the total spin as 2J+1
//
// ----------------------------------------------------------------------

#include <stdlib.h>

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int ParticleID::jSpin( ) const
{
    if( fundamentalID() > 0 && fundamentalID() <= 100 ) { 
	// some of these are known
	int fund = fundamentalID();
	if( fund > 0 && fund < 7 ) return 2;
	if( fund == 9 ) return 3; 
	if( fund > 10 && fund < 17 ) return 2;
	if( fund > 20 && fund < 25 ) return 3;
        return 0; 
    } else if( extraBits() > 0 && !isNucleus() ) { 
        return 0; 
    }
    return abspid()%10;
}

} // HepPDT
