// $Id: getPythiaid.cc,v 1.3 2004/05/19 23:29:54 garren Exp $
// ----------------------------------------------------------------------
//
// getPythiaid.cc
//
// return pythia particle ID from a line in the table
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

namespace HepPDT {

bool getPythiaid( int & id, const std::string & pdline )
{
    int sl = pdline.length();
    id = 0;
    // line is too short
    if( sl < 30 ) return false;
    // now check for various comments to avoid problems with Solaris
    std::string stars  = pdline.substr(1,2);
    std::string kfline = pdline.substr(0,10);
    if( stars == "**" || kfline == "        KF" ) return false;
    // try to read the kf number
    std::string firstc = pdline.substr(0,1);
    if( firstc == " " ){
      std::istringstream var1( pdline.substr(0,10).c_str() );
      var1 >> id;		// if var1 is blank, id is not changed
      return true;
    } else {
        return false;
    }
}

}	// HepPDT
