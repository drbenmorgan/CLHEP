// ----------------------------------------------------------------------
//
// quarks.cc
//
//  returns a list of charged quarks
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

Quarks ParticleID::quarks( ) const
{
    struct Quarks q;
    q.nq1 = q.nq2 = q.nq3 = 0;
    if( abspid() <= 100 || extraBits() > 0 ) { return q; }
    if( fundamentalID() <= 100 && fundamentalID() > 0 ) { return q; }
    q.nq1 = digit(nq1);
    q.nq2 = digit(nq2);
    q.nq3 = digit(nq3);
    int js = abspid()%10;
    if( abspid() == 130 || abspid() == 310 ) {	// Ks and KL
        if ( itsPID < 0 ) {
	    q.nq3=-q.nq3; 
	} else {
	    q.nq2=-q.nq2;
	}
	return q;
    }
    if( js == 0 ) { return q; }
    if( q.nq3 > 0 && q.nq2 > 0 && q.nq1 == 0 ) {		// meson
        if( q.nq2 == 3 || q.nq2 == 5 ) {		// strange and beauty
            if ( itsPID < 0 ) {
		q.nq3=-q.nq3; 
	    } else {
		q.nq2=-q.nq2;
	    }
	} else {
            if ( itsPID < 0 ) {
		q.nq2=-q.nq2; 
	    } else {
		q.nq3=-q.nq3;
	    }
	}
	return q;
    } else if( q.nq3 == 0 && q.nq2 > 0 && q.nq1 > 0 ) {	// diquark
        if ( itsPID < 0 ) {
	    q.nq2=-q.nq2;
	    q.nq1=-q.nq1; 
	}
	return q;
    } else if( q.nq1 > 0 && q.nq2 > 0 && q.nq3 > 0 ) {	// baryon
        if ( itsPID < 0 ) {
	    q.nq1=-q.nq1;
	    q.nq2=-q.nq2;
	    q.nq3=-q.nq3; 
	}
    }
    return q;
}

} // HepPDT
