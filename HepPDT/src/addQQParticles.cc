// $Id: addQQParticles.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// addQQParticles.cc
//
// this has the functions used by addQQParticles
//
// ----------------------------------------------------------------------

#include <iostream>

#include "CLHEP/HepPDT/TempParticleData.hh"
#include "CLHEP/HepPDT/QQStructs.hh"
#include "CLHEP/HepPDT/QQDecay.hh"

namespace HepPDT {

void parseQQParticle( TempParticleData & tpd, PARTICLE p );
void parseQQDecay( TempParticleData & tpd, QQDecay dcy );
TempDecayData getQQChannel( QQChannel ch );

void parseQQParticle( TempParticleData & tpd, PARTICLE p )
{
    // check for valid TempParticleData
    if( tpd.tempID.pid() == 0 ) { return; }
    // have a valid PID, so proceed
    tpd.tempParticleName = p.name;
    tpd.tempCharge = p.charge;
    tpd.tempMass = Measurement( p.mass, 0.0 );
    tpd.tempHighCutoff = p.maxMass;
    tpd.tempLowCutoff = p.minMass;
    if( p.width > 0. ) {	// by default, only lifetime is specified
        tpd.tempWidth = Measurement( p.width, 0.0 );
    } else {
        tpd.tempWidth = Measurement( calculateWidthFromLifetime(p.lifetime), 0.0 );
    }
    if( tpd.tempSpin.totalSpin() != p.spin ) {
        std::cout << "QQ spin " << p.spin << " does not match ParticleID spin " 
	          << tpd.tempSpin.totalSpin() 
                  << " for particle " << p.name << std::endl;
	tpd.tempSpin.setTotalSpin( p.spin );
    }
}

void parseQQDecay( TempParticleData & tpd, QQDecay dcy )
{
    // check for valid TempParticleData
    if( tpd.tempID.pid() == 0 ) { return; }
    // have a valid PID, so proceed
    // loop over channels
    int i;
    int endit = dcy.size();
    for( i=0; i < endit; ++i ) {
	TempDecayData tempdd = getQQChannel( dcy.channel(i) );
	tpd.tempDecayList.push_back( tempdd );
    }
}

TempDecayData getQQChannel( QQChannel ch )
{
    TempDecayData tdd;
    // decay type and brancing fraction
    tdd.tempDecayName = ch.matrixCode();
    tdd.tempBranchingFraction = ch.branchingFraction();
    int i, end = ch.sizeDtr();
    for( i=0; i < end; ++i ) {
        tdd.tempDaughterList.push_back( ch.daughter(i) );
    }
    // have to add helicity, angular helicity, etc here
    return tdd;
}

}	// HepPDT
