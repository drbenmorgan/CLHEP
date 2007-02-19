// ----------------------------------------------------------------------
//
// addIsajetParticles.cc
// Author: Lynn Garren
//
// this has the functions used by addIsajetParticles
//
// ----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "CLHEP/HepPDT/defs.h"
#include "CLHEP/HepPDT/TempParticleData.hh"

namespace HepPDT {

bool getIsajetID( int & id, const std::string & pdline );
void parseIsajetLine( TempParticleData & tpd, const std::string & pdline );

void parseIsajetLine( TempParticleData & tpd, const std::string & pdline )
{
    // this line defines a particle
    std::string isaname;
    int isaid, fl1, fl2, fl3, spin, idx, blank;
    double mass, chg;
    
    // check for valid TempParticleData
    int sl = pdline.length();
    if( tpd.tempID.pid() == 0 ) { return; }
    // have a valid PID, so proceed
    std::istringstream pids( pdline.substr(0,17).c_str() );
    pids >> isaid ;		// must access this before getting another stream
    // unfortunately, the istrstream trick does not work with strings in KCC
    //std::istringstream pnames( pdline.substr(21,32).c_str() );
    //pnames >> isaname >> aname;
    blank = pdline.substr(11,10).find(" ");
    isaname = pdline.substr(11,blank);
    std::istringstream particle( pdline.substr(21,sl-20).c_str() );
    particle >> mass >> chg >> fl1 >> fl2 >> fl3 >> spin >> idx ;
    // std::cout << isaid << " " << tpd.tempID.pid() << " " 
    // 	    << isaname << " " << chg 
    // 	    << " " << mass << " " << fl1 << " " << fl2 << " " << fl3
    //	    << " " << spin << " " << idx << std::endl; 
    tpd.tempParticleName = isaname;
    tpd.tempCharge = chg;
    tpd.tempSpin = SpinState(0.,double(spin),0.);
    tpd.tempMass = Measurement( mass, 0.0 );
}

}	// HepPDT
