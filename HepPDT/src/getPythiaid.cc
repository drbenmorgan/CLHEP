// $Id: getPythiaid.cc,v 1.1.4.1 2004/04/21 23:06:33 garren Exp $
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
    std::string firstc = pdline.substr(0,1);
    id = 0;
    if( sl > 30 && firstc == " " ){
      std::istringstream var1( pdline.substr(0,10).c_str() );
      var1 >> id;		// if var1 is blank, id is not changed
      return true;
    } else {
        return false;
    }
}

}	// HepPDT
