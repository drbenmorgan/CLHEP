// $Id: readBlockType.cc,v 1.2 2003/08/13 20:00:13 garren Exp $
// ----------------------------------------------------------------------
//
// readBlockType.cc
// Author: Lynn Garren
//
// read from an ascii file
// find the block identifier lines and return the type
// ----------------------------------------------------------------------

#include "CLHEP/StdHep/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include <fstream>
#include <string>

#include "CLHEP/StdHep/ReadStdHep.hh"

namespace StdHep  {

std::string readBlockType( std::istream & is )
{
    std::string type = " ";
    // check the state of the input stream
    if ( !is ) return type;
    //
    //
    std::string inputline, key;
    while( is ) {
        std::getline( is, inputline);
	if( inputline.find("BlockType ") == 0 ) {
            std::istringstream instr( inputline.c_str() );
	    instr >> key >> type;
            return type;
	}
    }
    // no BlockType
    return type;
}

}	// StdHep
