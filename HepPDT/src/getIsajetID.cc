// ----------------------------------------------------------------------
//
// getIsajetID.cc
// Author: Lynn Garren
//
// return Isajet particle ID from a line in the table
//
// ----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>

namespace HepPDT {

bool getIsajetID( int & id, const std::string & pdline )
{
    int sl = pdline.length();
    id = 0;
    // line is too short
    if( sl < 30 ) return false;
    // now check for various comments to avoid problems with Solaris
    std::string header  = pdline.substr(17,8);
    std::string labels = pdline.substr(11,8);
    if( header == "PARTICLE" || labels == "PARTICLE" ) return false;
    // try to read the ID number
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
