// $Id: translatePDTtoEvtGen.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// translatePDTtoEvtGen.cc
//
// translate a EvtGen ID number to the standard numbering scheme
//
// ----------------------------------------------------------------------

#include <iostream>

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int translatePDTtoEvtGen( const int id )
{

    ParticleID pid(id);

    // Nucleus
    if( pid.isNucleus() ) {
        if( id == 1002001001 ) { return 1011; }
        if( id == -1002001001 ) { return -1011; }
        if( id == 1003001001 ) { return 1021; }
        if( id == -1003001001 ) { return -1021; }
        if( id == 1003002001 ) { return 1012; }
        if( id == -1003002001 ) { return -1012; }
        if( id == 1004002001 ) { return 1022; }
        if( id == -1004002001 ) { return -1022; }
        // unknown 
        return 0;
    }

    if( pid.extraBits() > 0 ) {
 	std::cout << "EVTGEN_TRANSLATE 1: illegal number " << id << std::endl;
        return 0;
    }

    // quarks, Higgs, etc.
    if( pid.fundamentalID() > 0 ) {
        if( id == 110 ) { return 28; }
        if( id == 990 ) { return 29; }
        if( id == 41 ) { return 40; }
        if( id == -41 ) { return -40; }
        if( id == 61 ) { return 41; }
        if( id == 62 ) { return 42; }
        if( id == -62 ) { return -42; }
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
        if( id == 9910113 ) { return 110; }
        if( id == 9910211 ) { return 210; }
        if( id == -9910211 ) { return -210; }
        if( id == 9910223 ) { return 220; }
        if( id == 9910333 ) { return 330; }
        if( id == 9910443 ) { return 440; }
        if( id == 9912112 ) { return 2110; }
        if( id == -9912112 ) { return -2110; }
        if( id == 9912212 ) { return 2210; }
        if( id == -9912212 ) { return -2210; }
        return id;
    }

    // mesons
    if( pid.isMeson() ) {
        if( id == 9000111 ) { return 10111; }
        if( id == 9000211 ) { return 10211; }
        if( id == -9000211 ) { return -10211; }
        if( id == 100111 ) { return 20111; }
        if( id == 100211 ) { return 20211; }
        if( id == -100211 ) { return -20211; }
        if( id == 100113 ) { return 30113; }
        if( id ==  100213) { return 30213; }
        if( id == -100213 ) { return -30213; }
        if( id == 30113 ) { return 40113; }
        if( id == 30213 ) { return 40213; }
        if( id == -30213 ) { return -40213; }
        if( id == 9010221 ) { return 10221; }
        if( id == 100221 ) { return 20221; }
        if( id == 10221 ) { return 10331; }
        if( id == 9020221 ) { return 50221; }
        if( id == 100223 ) { return 30223; }
        if( id == 100411 ) { return 30411; }
        if( id == -100411 ) { return -30411; }
        if( id == 100421 ) { return 30421; }
        if( id == -100421 ) { return -30421; }
        if( id == 100413 ) { return 30413; }
        if( id == -100413 ) { return -30413; }
        if( id == 100423 ) { return 30423; }
        if( id == -100423 ) { return -30423; }
        if( id == 9010311 ) { return 30343; }
        if( id == -9010311 ) { return -30343; }
        if( id == 9020321 ) { return 30353; }
        if( id == -9020321 ) { return -30353; }
        if( id == 9000331 ) { return 30363; }
        if( id == -9000331 ) { return -30363; }
        if( id == 100441 ) { return 20441; }
        if( id == 100443 ) { return 30443; }
        if( id == 30443 ) { return 40443; }
        if( id == 9000443 ) { return 50443; }
        if( id == 9010443 ) { return 60443; }
        if( id == 9030443 ) { return 70443; }
        if( id == 100551 ) { return 20551; }
        if( id == 110551 ) { return 30551; }
        if( id == 200551 ) { return 40551; }
        if( id == 210551 ) { return 50551; }
        if( id == 30553 ) { return 120553; }
        if( id == 100553 ) { return 30553; }
        if( id == 110553 ) { return 40553; }
        if( id == 120553 ) { return 50553; }
        if( id == 200553 ) { return 60553; }
        if( id == 210553 ) { return 100553; }
        if( id == 220553 ) { return 110553; }
        if( id == 300553 ) { return 70553; }
        if( id == 9000553 ) { return 80553; }
        if( id == 10555 ) { return 40555; }
        if( id == 20555 ) { return 30555; }
        if( id == 100555 ) { return 10555; }
        if( id == 110555 ) { return 60555; }
        if( id == 120555 ) { return 50555; }
        if( id == 200555 ) { return 20555; }
        if( id == 100557 ) { return 10557; }
        return id;
    }

    // baryons
    if( pid.isBaryon() ) { return id; }

    // undefined
    return 0;
}

}	// HepPDT
