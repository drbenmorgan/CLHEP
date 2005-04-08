// ----------------------------------------------------------------------
//
// translateEvtGentoPDT.cc
// Author: Lynn Garren
//
// translate a EvtGen ID number to the standard numbering scheme
//
// ----------------------------------------------------------------------

#include <iostream>

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int translateEvtGentoPDT( const int id )
{

    ParticleID pid(id);
    if( pid.extraBits() > 0 ) {
 	std::cout << "EVTGEN_TRANSLATE 1: illegal number " << id << std::endl;
        return 0;
    }

    // quarks, Higgs, etc.
    if( pid.fundamentalID() > 0 ) {
        if( id == 28 ) { return 110; }
        if( id == 29 ) { return 990; }
        if( id == 40 ) { return 41; }
        if( id == -40 ) { return -41; }
        if( id == 41 ) { return 61; }
        if( id == 42 ) { return 62; }
        if( id == -42 ) { return -62; }
        return id;
    }

    // diquarks
    if( pid.isDiQuark() ) { return id; }
    // bad diquark numbers
    if( pid.abspid() == 1101 || pid.abspid() == 2201 ||
        pid.abspid() == 3301 || pid.abspid() == 4401 || 
        pid.abspid() == 5501 ) { return id; }

    //special particles
    if( pid.digit(nj) == 0 ) {
        if( id == 110 ) { return 9910113; }
        if( id == 210 ) { return 9910211; }
        if( id == -210 ) { return -9910211; }
        if( id == 220 ) { return 9910223; }
        if( id == 330 ) { return 9910333; }
        if( id == 440 ) { return 9910443; }
        if( id == 2110 ) { return 9912112; }
        if( id == -2110 ) { return -9912112; }
        if( id == 2210 ) { return 9912212; }
        if( id == -2210 ) { return -9912212; }
        return id;
    }

    // Nucleus
    if( pid.digit(nq2) == 0 && pid.digit(nq1) == 1 ) {
        if( id == 1011 ) { return 1002001001; }
        if( id == -1011 ) { return -1002001001; }
        if( id == 1021 ) { return 1003001001; }
        if( id == -1021 ) { return -1003001001; }
        if( id == 1012 ) { return 1003002001; }
        if( id == -1012 ) { return -1003002001; }
        if( id == 1022 ) { return 1004002001; }
        if( id == -1022 ) { return -1004002001; }
        // unknown - leave it alone
        return id;
    }

    // baryons
    if( pid.isBaryon() ) { return id; }

    // mesons
    if( pid.isMeson() ) {
        if( id == 10111 ) { return 9000111; }
        if( id == 10211 ) { return 9000211; }
        if( id == -10211 ) { return -9000211; }
        if( id == 20111 ) { return 100111; }
        if( id == 20211 ) { return 100211; }
        if( id == -20211 ) { return -100211; }
        if( id == 30113 ) { return 100113; }
        if( id == 30213 ) { return 100213; }
        if( id == -30213 ) { return -100213; }
        if( id == 40113 ) { return 30113; }
        if( id == 40213 ) { return 30213; }
        if( id == -40213 ) { return -30213; }
        if( id == 10221 ) { return 9010221; }
        if( id == 20221 ) { return 100221; }
        if( id == 10331 ) { return 10221; }
        if( id == 50221 ) { return 9020221; }
        if( id == 30223 ) { return 100223; }
        if( id == 30411 ) { return 100411; }
        if( id == -30411 ) { return -100411; }
        if( id == 30421 ) { return 100421; }
        if( id == -30421 ) { return -100421; }
        if( id == 30413 ) { return 100413; }
        if( id == -30413 ) { return -100413; }
        if( id == 30423 ) { return 100423; }
        if( id == -30423 ) { return -100423; }
        if( id == 30343 ) { return 9010311; }
        if( id == -30343 ) { return -9010311; }
        if( id == 30353 ) { return 9020321; }
        if( id == -30353 ) { return -9020321; }
        if( id == 30363 ) { return 9000331; }
        if( id == -30363 ) { return -9000331; }
        if( id == 20441 ) { return 100441; }
        if( id == 30443 ) { return 100443; }
        if( id == 40443 ) { return 30443; }
        if( id == 50443 ) { return 9000443; }
        if( id == 60443 ) { return 9010443; }
        if( id == 70443 ) { return 9030443; }
        if( id == 20551 ) { return 100551; }
        if( id == 30551 ) { return 110551; }
        if( id == 40551 ) { return 200551; }
        if( id == 50551 ) { return 210551; }
        if( id == 120553 ) { return 30553; }
        if( id == 30553 ) { return 100553; }
        if( id == 40553 ) { return 110553; }
        if( id == 50553 ) { return 120553; }
        if( id == 60553 ) { return 200553; }
        if( id == 100553 ) { return 210553; }
        if( id == 110553 ) { return 220553; }
        if( id == 70553 ) { return 300553; }
        if( id == 80553 ) { return 9000553; }
        if( id == 40555 ) { return 10555; }
        if( id == 30555 ) { return 20555; }
        if( id == 10555 ) { return 100555; }
        if( id == 60555 ) { return 110555; }
        if( id == 50555 ) { return 120555; }
        if( id == 20555 ) { return 200555; }
        if( id == 10557 ) { return 100557; }
        return id;
    }

    // undefined
    return 0;
}

}	// HepPDT
