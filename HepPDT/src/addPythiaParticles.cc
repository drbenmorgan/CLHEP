// ----------------------------------------------------------------------
//
// addPythiaParticles.cc
// Author: Lynn Garren
//
// this has the functions used by addPythiaParticles
//
// ----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>

#include "CLHEP/HepPDT/defs.h"
#include "CLHEP/HepPDT/TempParticleData.hh"

namespace HepPDT {

bool getPythiaid( int & id, const std::string & pdline );
void parsePythiaLine( TempParticleData & tpd, int & anti, std::string & aname, const std::string & pdline );
void parsePythiaDecayLine( TempParticleData & tpd, const std::string & pdline );
TempDecayData getPythiaDecay( const std::string & pdline );

void parsePythiaLine( TempParticleData & tpd, int & anti, std::string & aname, const std::string & pdline )
{
    // this line defines a particle
    std::string name1;
    int kf, kc, chg, col, decay, blank;
    double mass, width, wcut, lifet;
    
    // check for valid TempParticleData
    anti = 0;
    int sl = pdline.length();
    if( tpd.tempID.pid() == 0 ) { return; }
    // have a valid PID, so proceed
    std::istringstream pids( pdline.substr(0,17).c_str() );
    pids >> kf >> kc;		// must access this before getting another stream
    // unfortunately, the istrstream trick does not work with strings in KCC
    aname = "";
    //std::istringstream pnames( pdline.substr(21,32).c_str() );
    //pnames >> name1 >> aname;
    blank = pdline.substr(21,16).find(" ");
    name1 = pdline.substr(21,blank);
    blank = pdline.substr(37,16).find(" ");
    aname = pdline.substr(37,blank);
    std::istringstream particle( pdline.substr(54,sl-53).c_str() );
    particle >> chg >> col >> anti >> mass >> width >> wcut >> lifet >> decay ;
    // std::cout << kf << " " << kc << " " << tpd.tempID.pid() << " " 
    // 	    << name1 << " " << aname << " " << chg 
    // 	    << " " << mass << " " << width << std::endl; 
    tpd.tempParticleName = name1;
    tpd.tempCharge = double(chg)/3.0;
    tpd.tempColorCharge = col;
    tpd.tempMass = Measurement( mass, 0.0 );
    tpd.tempHighCutoff = wcut;
    // either width or lifetime is defined - not both
    if( width > 0. ) {
        tpd.tempWidth = Measurement( width, 0.0 );
    } else if( lifet > 0. ) { 
        tpd.tempWidth = Measurement( calculateWidthFromLifetime( lifet ), 0.0 );
    }
}

void parsePythiaDecayLine( TempParticleData & tpd, const std::string & pdline )
{
    // check for valid TempParticleData
    if( tpd.tempID.pid() == 0 ) { return; }
    TempDecayData tempdd = getPythiaDecay( pdline );
    tpd.tempDecayList.push_back( tempdd );
}

TempDecayData getPythiaDecay( const std::string & pdline )
{
    int idc, onoff;
    int i, blank;
    std::string dname;
    TempDecayData tdd;
    // unpack decay type and brancing fraction
    std::istringstream decayparams( pdline.substr(0,36).c_str() );
    decayparams >> idc >> onoff >> tdd.tempDecayName >> tdd.tempBranchingFraction;
    //std::cout << " decay parameters " << idc << " " << onoff << " " << tdd.tempDecayName
    //     << " " << tdd.tempBranchingFraction << std::endl;
    // get the list of particle names
    i = 40;
    while( i < 110) {
	//std::istringstream part( pdline.substr(i,16).c_str() );
	blank = pdline.substr(i,16).find(" ");
	dname = "";
	//part >> dname;
	dname = pdline.substr(i,blank);
	tdd.tempDaughterList.push_back( dname );
	i = i + 16;
    }
    // std::cout << "  decay " << tdd.tempDecayMode << " " << tdd.tempBranchingFraction ;
    // for( i = 0; i < tdd.tempDaughterList.size(); i++ ) {
    //    std::cout << " " << tdd.tempDaughterList[i] ;
    // }
    // std::cout << std::endl;
    return tdd;
}

}	// HepPDT
