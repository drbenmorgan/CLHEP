// $Id: readStdRun.cc,v 1.2 2003/08/13 20:00:13 garren Exp $
// ----------------------------------------------------------------------
//
// readStdRun.cc
// Author: Lynn Garren
//
// read from an ascii file
// ----------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include "CLHEP/StdHep/defs.h"
#include "CLHEP/StdHep/ReadStdHep.hh"
#include "CLHEP/StdHep/StdRunInfo.hh"

namespace StdHep  {

StdRunInfo * readStdRun( std::istream & is )
{
    // check the state of the input stream
    if ( !is ) return NULL;
    //
    // read the run
    //
    std::string evline, com;
    std::getline( is, evline);
    if( evline.find("RunID ") == 0 ) {
	StdRunInfo * run = Detail::readRunInfo( is, evline );
        return run;
    }
    // no event has been found
    return NULL;
}

}	// StdHep
