// $Id: listPythiaTranslation.cc,v 1.1.4.2 2004/05/18 23:38:07 garren Exp $
// ----------------------------------------------------------------------
//
// listPythiaTranslation.cc
// Author:  Lynn Garren
//
// list translations for pythia input 
// DO NOT mix these functions with the addXXXParticles functions
// These functions will read a table file and write a translation list
//
// ----------------------------------------------------------------------

#include <iostream>
#include <string>

#include "CLHEP/HepPDT/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include "CLHEP/HepPDT/ParticleTranslation.hh"

namespace HepPDT {


/**
 * @author
 * @ingroup heppdt
 */

bool getPythiaid( int & id, const std::string & pdline );

ParticleTranslation parsePythiaLine( int & anti, std::string & aname, const std::string & pdline )
{
    // this line defines a particle
    std::string name1;
    int kf, kc, chg, col, decay, blank;
    double mass, width, wcut, lifet;
    
    // check for valid TempParticleData
    anti = 0;
    int sl = pdline.length();
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

   // now add appropriate properties
   std::string mc = std::string("Pythia");
   ParticleID pid( translatePythiatoPDT( kf ) );
   return ParticleTranslation( pid, kf, name1, mc );
}

ParticleTranslation getPythiaAntiParticle( int & anti, 
                    std::string & aname, ParticleTranslation & pt )
{
   std::string mc = std::string("Pythia");
   int ap = -pt.oid();
   ParticleID pid( translatePythiatoPDT( ap ) );
   return ParticleTranslation( pid, ap, aname, mc );
}

bool  listPythiaTranslation ( std::istream & pdfile, std::ostream & os )
{
  std::string pdline, aname;
  int id, kf;
  int anti=0;
  // read and parse each line
  while( std::getline( pdfile, pdline) ) {
    if( getPythiaid( kf, pdline ) ) {
      if( kf != 0 ) {
        // this is a new particle definition
          ParticleTranslation pt = parsePythiaLine( anti, aname, pdline );
	  pt.write( os );       
	  if( anti > 0 ) {
	      // code here to define antiparticles
	      ParticleTranslation apt = getPythiaAntiParticle( anti, aname, pt );
	      apt.write( os );       
	  }
      }
    }
  }
  return true;
}

}  // namespace HepPDT
