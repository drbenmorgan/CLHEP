// $Id: ReadHepMC.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// ReadHepMC.cc
// Author: Lynn Garren
//
// read from an ascii file
// ----------------------------------------------------------------------

#include "HepMC/defs.h"
#include <iostream>
#include <fstream>
#include <string>

#include "CLHEP/HepMC/ReadHepMC.h"
#include "CLHEP/HepMC/GenEvent.h"

namespace HepMC  {

GenEvent * readGenEvent( std::istream & is )
{
    // check the state of the input stream
    if ( !is ) return NULL;
    // create empty event
    GenEvent * evt = new GenEvent();
    //
    // an event starts with "E" in the first column
    // a comment is flagged by "HepMC-COMMENT"
    // ignore everything else
    //
    std::string evline, com;
    while( is ) {
        std::getline( is, evline);
	if( evline.find("E ") == 0 ) {
	    Detail::fillEvent( is, evline, evt );
            return evt;
	}
    }
    // no event has been found
    delete evt;
    return NULL;
}

}	// HepMC
