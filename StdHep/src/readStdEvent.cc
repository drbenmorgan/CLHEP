// $Id: readStdEvent.cc,v 1.2 2003/08/13 20:00:13 garren Exp $
// ----------------------------------------------------------------------
//
// readStdEvent.cc
// Author: Lynn Garren
//
// read from an ascii file
// process a single event - do not combine events
// ----------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include "CLHEP/StdHep/defs.h"
#include "CLHEP/StdHep/ReadStdHep.hh"
#include "CLHEP/HepMC/ReadHepMC.h"
#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep  {

StdEvent * readStdEvent( std::istream & is )
{
    // check the state of the input stream
    if ( !is ) return NULL;
    //
    // read the event
    std::string evline;
    std::getline( is, evline);
    if( evline.find("S ") == 0 ) {
	StdEvent * evt = Detail::readStdEventInfo( is, evline );
        return evt;
    }
    // no event has been found
    return NULL;
}

}	// StdHep
