// ----------------------------------------------------------------------
//
// getPDGpid.cc
// Author:  Lynn Garren
//
// parse a line in the PDG table and return the particle ID numbers
//
// ----------------------------------------------------------------------

#include <string>
#include <vector>

#include "CLHEP/HepPDT/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif

namespace HepPDT {

void getPDGpid( std::vector<int> & idlist,  std::string & pdline )
{
    int sl, cl, id1, id2, id3, id4;
    sl = pdline.length();
    cl = pdline.find('*');
    // make sure the vector is empty
    idlist.clear();
    if( cl != 0 && sl > 60 ){
      // this is a valid line, so parse it
      // initialize possible ID's to zero
      id1 = id2 = id3 = id4 = 0;
      std::istringstream idnet( pdline.substr(1,32).c_str() );
      idnet >> id1 >> id2 >> id3 >> id4;
      if( id1 > 0 ) { idlist.push_back( id1 ); }
      if( id2 > 0 ) { idlist.push_back( id2 ); }
      if( id3 > 0 ) { idlist.push_back( id3 ); }
      if( id4 > 0 ) { idlist.push_back( id4 ); }
    }
}

} // namespace HepPDT

