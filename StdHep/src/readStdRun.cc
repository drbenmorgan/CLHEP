// $Id: readStdRun.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// readStdRun.cc
// Author: Lynn Garren
//
// read from an ascii file
// ----------------------------------------------------------------------

#include "StdHep/defs.h"
#include <iostream>
#include <fstream>
#include <string>

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
