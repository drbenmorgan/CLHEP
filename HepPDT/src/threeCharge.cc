// ----------------------------------------------------------------------
//
// threeCharge.cc
// Author: Lynn Garren
//
//  return the total spin as 2J+1
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int ParticleID::threeCharge( ) const
{
    int charge=0;
    int ida, sid;
    unsigned short q1, q2, q3;
    static int ch100[100] = { -1, 2,-1, 2,-1, 2,-1, 2, 0, 0,
                       -3, 0,-3, 0,-3, 0,-3, 0, 0, 0,
                        0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 3, 0, 0, 3, 0, 0, 0,
                        0, -1, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 6, 3, 6, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    q1 = digit(nq1);
    q2 = digit(nq2);
    q3 = digit(nq3);
    ida = abspid();
    sid = fundamentalID();
    if( ida == 0 || extraBits() > 0 ) {      // ion or illegal
        return 0;
    } else if( sid > 0 && sid <= 100 ) {	// use table
        charge = ch100[sid-1];
        if(ida==1000017 || ida==1000018) { charge = 0; }
        if(ida==1000034 || ida==1000052) { charge = 0; }
        if(ida==1000053 || ida==1000054) { charge = 0; }
        if(ida==5100061 || ida==5100062) { charge = 6; }
    } else if( digit(nj) == 0 ) { 		// KL, Ks, or undefined
        return 0;
    } else if( q1 == 0 ) {			// mesons
            if( q2 == 3 || q2 == 5 ) {
                charge = ch100[q3-1] - ch100[q2-1];
            } else {
                charge = ch100[q2-1] - ch100[q3-1];
            }
    } else if( q3 == 0 ) {			// diquarks
        charge = ch100[q2-1] + ch100[q1-1];
    } else { 					// baryons
        charge = ch100[q3-1] + ch100[q2-1] + ch100[q1-1];
    }
    if( charge == 0 ) {
        return 0;
    } else if( pid() < 0 ) {
        charge = -charge; 
    }
    return charge;
}

} // HepPDT
