// ----------------------------------------------------------------------
//
// addEvtGenParticles.cc
// Author: Lynn Garren
//
// this has the functions used by addEvtGenParticles
//
// ----------------------------------------------------------------------

#include <string>
#include <algorithm>	// min()
#include <iostream>

#include "CLHEP/HepPDT/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include "CLHEP/HepPDT/TempParticleData.hh"

namespace HepPDT {

bool getEvtGenLineType( std::string & ltype, int & id, std::string & name, const std::string & pdline );
void parseEvtGenLine( TempParticleData & tpd, const std::string & pdline );
void parseEvtGenAlias( TempAliasData & tad, const std::string & pdline );
bool parseEvtGenDecayLine( TempParticleData & tpd, const std::string & pdline );
bool parseEvtGenAliasDecayLine( TempAliasData & tad, const std::string & pdline );
TempDecayData getEvtGenDecay( const std::string & pdline );
void parseEvtGenConj( std::string & cname, const std::string & pdline );
void parseEvtGenDefinition( std::string & def, double & val, const std::string & pdline );

bool getEvtGenLineType( std::string & ltype, int & id, std::string & name, const std::string & pdline )
{
    std::string s1, s2;
    int sl = pdline.length();
    std::string firstc = pdline.substr(0,1);
    id = 0;
    name = "";
    ltype = "";
    // check for comments
    if( firstc == "*" || firstc == "#" ) { return false; }
    // a # may be anywhere on the line
    // check for empty lines
    if( sl > 5 ){
	std::istringstream thisline( pdline.substr(0,sl).c_str() );
	thisline >> ltype;
	if( ltype == "add" ) {
            thisline >> s1 >> s2 >> name >> id;
        } else if( ltype=="Alias" ) {
            thisline >> name;
        } else if( ltype=="ChargeConj" ) {
            thisline >> name;
	} else if( ltype == "Decay" ) {
            thisline >> name;
	} else if( ltype == "CDecay" ) {
            thisline >> name;
	}
	return true;
    } else {
        return false;
    }
}

void parseEvtGenLine( TempParticleData & tpd, const std::string & pdline )
{
    // this line defines a particle
    std::string s1, s2, ltype, name;
    int id, chg, spin, lid;
    double mass, width, wcut, lifet, dspin;
    
    // check for valid TempParticleData
    if( tpd.tempID.pid() == 0 ) { return; }
    // have a valid PID, so proceed
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> s1 >> s2 >> name >> id >> mass >> width >> wcut 
             >> chg >> spin >> lifet >> lid;
    // std::cout << ltype << " " << s1 << " " << s2 << " " << id << " " << name 
    //      << " " << chg << " " << spin <<  " " << mass << " " << width << " " 
    //      << wcut << " " << lifet <<  " " << lid << std::endl;
    if( ltype != "add" ) { 
        std::cout << "called parseEvtGenLine with wrong line type" << std::endl;
        return; 
    }
    tpd.tempParticleName = name;
    tpd.tempCharge = double(chg)/3.0;
    tpd.tempMass = Measurement( mass, 0.0 );
    tpd.tempHighCutoff = wcut;
    tpd.tempWidth = Measurement( calculateWidthFromLifetime( lifet ), 0.0 );
    dspin = double(spin)/2.;
    if( tpd.tempSpin.totalSpin() != dspin ) {
        // std::cout << "EvtGen spin " << dspin << " does not match ParticleID spin " 
	//      << tpd.tempSpin.totalSpin() << std::endl;
	tpd.tempSpin.setTotalSpin( dspin );
    }
}

bool parseEvtGenDecayLine( TempParticleData & tpd, const std::string & pdline )
{
    std::string ltype;
    // check for valid TempParticleData
    if( tpd.tempID.pid() == 0 ) { return false; }
    // have a valid PID, so proceed
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    // better check for comments and blank lines.....
    std::string firstc = pdline.substr(0,1);
    if( firstc == "*" || firstc == "#" ) { return true; }
    // check line type
    thisline >> ltype;
    if( ltype == "Decay" ) {
        // begin decay
	return true;
    } else if( ltype == "Enddecay" ) {
        // end decay
	return false;
    }
    // this is a good decay line
    TempDecayData tempdd = getEvtGenDecay( pdline );
    tpd.tempDecayList.push_back( tempdd );
    return true;
}

TempDecayData getEvtGenDecay( const std::string & pdline )
{
    std::string dname = "";
    TempDecayData tdd;
    // unpack decay type and brancing fraction
    int sl = pdline.length();
    int semicol = pdline.find(';');
    if( semicol > 0 ) { sl = std::min( sl, semicol ); }
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> tdd.tempBranchingFraction;
    while ( !thisline.eof() ) {
        thisline >> dname; 
        // this list will be parsed later for decay model and decay parameters
        tdd.tempDaughterList.push_back( dname );
	// std::cout << dname << " " ;
    }
    // std::cout << std::endl;
    return tdd;
}

bool parseEvtGenAliasDecayLine( TempAliasData & tad, const std::string & pdline )
{
    std::string ltype;
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    // better check for comments and blank lines.....
    std::string firstc = pdline.substr(0,1);
    if( firstc == "*" || firstc == "#" ) { return true; }
    // check line type
    thisline >> ltype;
    if( ltype == "Decay" ) {
        // begin decay
	return true;
    } else if( ltype == "Enddecay" ) {
        // end decay
	return false;
    }
    // this is a good decay line
    TempDecayData tempdd = getEvtGenDecay( pdline );
    tad.tempAliasDecayList.push_back( tempdd );
    return true;
}

void parseEvtGenAlias( TempAliasData & tad, const std::string & pdline )
{
    // this line defines a particle alias
    std::string ltype, alias, name;
    
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> alias >> name;
    // std::cout << ltype << " " << alias << " " << name << std::endl;
    if( ltype != "Alias" ) { 
        std::cout << "called parseEvtGenAlias with wrong line type: " << ltype << std::endl;
        return; 
    }
    tad.tempAlias = alias;
    tad.tempAliasedParticle = name;
}

void parseEvtGenConj( std::string & cname, const std::string & pdline )
{
    std::string ltype, alias;
    
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> alias >> cname;
    // std::cout << ltype << " " << alias << " " << cname << std::endl;
    if( ltype != "ChargeConj" ) { 
        std::cout << "called parseEvtGenConj with wrong line type: " << ltype << std::endl;
        cname = "";
        return; 
    }
}

void parseEvtGenDefinition( std::string & def, double & val, const std::string & pdline )
{
    std::string ltype;
    
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> def >> val;
    // std::cout << ltype << " " << def << " " << val << std::endl;
    if( ltype != "Define" ) { 
        std::cout << "called parseEvtGenDefinition with wrong line type: " << ltype << std::endl;
        val = 0.0;
	def = "";
    }
}

}	// HepPDT
