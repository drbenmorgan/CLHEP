// $Id: readStdEventInfo.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// readStdEventInfo.cc
// Author: Lynn Garren
//
// read from an ascii file
// process a single event - do not combine events
// use explicit namespaces
// ----------------------------------------------------------------------

#include "StdHep/defs.h"
#include <iostream>
#include <fstream>
#include <string>

#include "CLHEP/StdHep/ReadStdHep.hh"
#include "CLHEP/HepMC/ReadHepMC.h"
#include "CLHEP/StdHep/StdEvent.hh"

StdHep::StdEvent * StdHep::Detail::readStdEventInfo( std::istream & is, std::string & evline )
{
    int ncol=0, evnum=0;
    std::string newline;
    Detail::parseStdEventLine( evline, evnum,  ncol );
    int ic=0;
    StdHep::StdEvent::CollisionList cvect;
    while( is && ic<ncol ) {
        std::getline( is, newline);
        ++ic;
	if( newline.find("E ") == 0 ) {
            HepMC::GenEvent * col = new HepMC::GenEvent();
	    HepMC::Detail::fillEvent( is, newline, col );
	    cvect.push_back( col );
	} else {
	    std::cout << "readStdEventInfo: PROBLEM " 
	              << "event logic has failed at line " << std::endl;
            std::cout << newline << std::endl;
	    std::cout << "readStdEventInfo: stop reading this StdEvent" << std::endl;
            return NULL;
	}
    }
    return new StdHep::StdEvent( evnum, cvect );
}
