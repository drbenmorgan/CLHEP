// ----------------------------------------------------------------------
//
// readQQstream.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>

#include "CLHEP/HepPDT/defs.h"
#include "CLHEP/HepPDT/QQDecayTable.hh"

#ifdef __KCC
// kai implements getline with a third argument......
template std::istream& std::getline( std::istream&, std::string&);
template std::istream& std::getline( std::istream&, std::string&, char);
#endif

namespace HepPDT {

void QQDecayTable::readQQstream( std::istream & pdfile )
{
  std::string pdline;
  std::string ltype, name;
  // read and parse each line
  while( std::getline( pdfile, pdline ) ) {
    if( getQQLineType( ltype, name, pdline ) ) {
      if( ltype == "VERSION" ) {
          itsVersion = getQQversion( pdline );
      } else if( ltype == "PARTICLE" ) {
          PARTICLE pqq = parseParticle( pdline );
	  addParticle( name, pqq );
      } else if( ltype=="QQBAR" ) {
          QQBAR qqb;
	  qqb.name = name;
	  qqb.qqid = getQQbar( pdline );
	  addQQbar( name, qqb );
      } else if( ltype=="PDG" ) {
          addPDG( pdline );
      } else if( ltype=="PARITY " ) {
          addParity( pdline );
      } else if( ltype=="CPARITY " ) {
          addCParity( pdline );
      } else if( ltype=="MIXING" ) {
          addMixing( pdline );
      } else if( ltype=="HIDE" ) {
          itsParticleMap[name].hide = true;
      } else if( ltype=="DECAY" ) {
          QQDecay dcy;
          QQChannel ch;		// create an empty channel
	  // read lines until we reach an ENDDECAY
	  while( parseQQDecayLine( dcy, ch, pdline ) ) {
              std::getline( pdfile, pdline);
	  }
	  // now add this decay to the table
	  itsDecayMap[name] = dcy;
      }
    }
  }
  std::cout << "QQDecayTable::readQQstream: found " << itsParticleMap.size() 
            << " particles and " << itsDecayMap.size() 
            << " decay definitions" << std::endl;
  return;
}

bool QQDecayTable::getQQLineType( std::string & ltype, std::string & name, const std::string & pdline )
{
    int sl = pdline.length();
    std::string firstc = pdline.substr(0,1);
    ltype = "";
    name = "";
    // check for comments
    if( firstc == ";" ) { return false; }
    // check for empty lines
    if( sl > 6 ){
	std::istringstream thisline( pdline.substr(0,sl).c_str() );
	thisline >> ltype >> name;
	if( ltype != "" ) { return true; }
    }
    return false;
}

int QQDecayTable::getQQversion( const std::string & pdline )
{
    int ver = 0;
    std::string ltype;
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> ver;
    return ver;
}

int QQDecayTable::getQQbar( const std::string & pdline )
{
    int id = 0;
    std::string ltype, nm;
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> nm >> id;
    return id;
}

PARTICLE QQDecayTable::parseParticle( const std::string & pdline )
{
    // this line defines a particle
    PARTICLE tpd;
    std::string ltype, name;
    int id, sid;
    double chg, spin;
    double mass, width, mmax, lifet, mmin;
    
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> name >> id >> sid >> mass >> chg >> spin >> lifet;
    width = mmin = mmax = 0.;
    if( !thisline.eof() ) {
        thisline >> width >> mmin >> mmax; 
    }
    tpd.name = name;
    tpd.qqid = id;
    tpd.stableid = sid;
    tpd.pdgid = 0;
    tpd.mass = mass;
    tpd.charge = chg;
    tpd.spin = spin;
    tpd.lifetime = lifet;
    tpd.width = width;
    tpd.minMass = mmin;
    tpd.maxMass = mmax;
    tpd.parity = 0;
    tpd.cparity = 0;
    tpd.hide = false;
    return tpd;
}

void QQDecayTable::addPDG( const std::string & pdline )
{
    int id;
    std::string ltype, name;
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> name >> id;
    itsParticleMap[name].pdgid = id;
}

void QQDecayTable::addParity( const std::string & pdline )
{
    int par;
    std::string ltype, name;
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> name >> par;
    itsParticleMap[name].parity = par;
}

void QQDecayTable::addCParity( const std::string & pdline )
{
    int par;
    std::string ltype, name;
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> name >> par;
    itsParticleMap[name].cparity = par;
}

void QQDecayTable::addMixing( const std::string & pdline )
{
    MIXING mx;
    std::string ltype, name, aname;
    double m;
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    thisline >> ltype >> name >> aname >> m;
    mx.name = name;
    mx.antiname = aname;
    mx.mix = m;
    itsParticleMap[name].mixing = mx;
}

bool QQDecayTable::parseQQDecayLine( QQDecay & dcy, QQChannel & ch, const std::string & pdline )
{
    // note that HELICITY, etc. are all defined BEFORE CHANNEL
    std::string ltype = "";
    std::string name = "";
    int sl = pdline.length();
    std::istringstream thisline( pdline.substr(0,sl).c_str() );
    // better check for comments and blank lines.....
    std::string firstc = pdline.substr(0,1);
    if( firstc == ";" ) { return true; }
    // check line type
    thisline >> ltype;
    if( ltype == "DECAY" ) {
        // begin decay
	return true;
    } else if( ltype == "ENDDECAY" ) {
        // end decay
	return false;
    } else if( ltype == "CHANNEL" ) {
        ch.parse( thisline );		// parse the remaining line
	dcy.addChannel( ch );		// copy this channel to decay
	ch.clear();			// clear out for new input
    } else if( ltype == "HELICITY" ) {
        ch.addHelicity( thisline );
    } else if( ltype == "ANGULAR_HELICITY" ) {
        ch.addAngHelicity( thisline );
    } else if( ltype == "MATRIX " ) {
        QQmatrix mx;
	thisline >> mx.a >> mx.b >> mx.c;
	ch.setMatrix( mx );
    } else if( ltype == "STABLE" ) {
        // probably the wrong thing to do.......
        dcy.makeStable();
    } else if( ltype == "CPEIGENSTATE" ) {
        double sp = 0;
	thisline >> sp;
	ch.setSinPhi( sp );
    } else if( ltype == "CPTAG" ) {
        ch.setCPTag();
    }
    return true;
}

}	// HepPDT
