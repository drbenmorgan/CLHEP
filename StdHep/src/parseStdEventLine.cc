// $Id: parseStdEventLine.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// parseStdEventLine.cc
// Author: Lynn Garren
//
// parse the "S" line
// use explicit namespaces
// ----------------------------------------------------------------------

#include "StdHep/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include <fstream>
#include <string>

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
