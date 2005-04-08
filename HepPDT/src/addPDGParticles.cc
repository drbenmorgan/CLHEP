// ----------------------------------------------------------------------
//
// addPDGParticles.cc
// Author:  Lynn Garren
//
// this has the functions used by addPDGParticles
//
// ----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "CLHEP/HepPDT/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include "CLHEP/HepPDT/TempParticleData.hh"

namespace HepPDT {

void getPDGpid( std::vector<int> & idlist,  std::string & pdline );
void parsePDGline( TempParticleData & tpd,  std::string & pdline );
bool CheckPDGEntry( TempParticleData & tpd, const std::string &, 
                       const std::string &, double, double );

void parsePDGline( TempParticleData & tpd,  std::string & pdline )
{
   double v, e1, e2, err;
   std::string name, ckey, charges, bigname;
   //int sl = pdline.length() - 1;		// <cr> at ends of lines
   // we already know that this is a valid line
   ckey = pdline.substr(0,1);
   name = charges = "";
   v = e1 = e2 = 0.0;
   std::istringstream val( pdline.substr(34,33).c_str() );
   val >> v >> e1 >> e2;
   err = sqrt( (e1*e1 + e2*e2)/2.0 );
   bigname = pdline.substr(68,21);
   int blank = bigname.find(" ");
   name = bigname.substr(0,blank);
   // really should strip out leading blanks 
   // unfortunately, the istrstream trick does not work with strings in KCC
   charges = bigname.substr(blank+1,20-blank);
   //std::cout << blank << " -- " << pdline.substr(68,21) << std::endl;
   //std::istringstream namelist( pdline.substr(68,21).c_str() );
   //namelist >> name >> charges;
   // std::cout << ckey << " " << tpd.tempID.pid() << " "  
   //      << v << " " << e1 << " " << e2 << " " << name << " " << charges << std::endl;
   CheckPDGEntry( tpd, ckey, name, v, err );
}

bool CheckPDGEntry( TempParticleData & tpd, const std::string & ckey, 
                    const std::string & name, double val, double err  )
{
   // now add appropriate properties
   tpd.tempParticleName = name;
   if( ckey.find("M") == 0 ) {
      tpd.tempMass = Measurement( val, err );
   } else if( ckey.find("W") == 0 ) {
      tpd.tempWidth = Measurement( val, err );
   } else {
     std::cout << "unrecognized key " << ckey << std::endl;
     return false;
   }
   return true;
}

}	// HepPDT
