// ----------------------------------------------------------------------
//
// parseStdEventLine.cc
// Author: Lynn Garren
//
// parse the "S" line
// use explicit namespaces
// ----------------------------------------------------------------------

#include <sstream>
#include <fstream>
#include <string>

#include "CLHEP/StdHep/defs.h"
#include "CLHEP/StdHep/ReadStdHep.hh"

void  StdHep::Detail::parseStdEventLine( std::string & evline, int & evnum, int & ncol )
{
    std::string key;
    std::istringstream evstr( evline.c_str() );
    ncol=0;
    evnum=0;
    evstr >> key 
	  >> evnum
	  >> ncol;
}
