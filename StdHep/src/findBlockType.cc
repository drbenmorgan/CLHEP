// $Id: findBlockType.cc,v 1.2 2003/08/13 20:00:13 garren Exp $
// ----------------------------------------------------------------------
//
// findBlockType.cc
// Author: Lynn Garren
//
// read from an ascii file
// find a block with the specified type
// ----------------------------------------------------------------------

#include "CLHEP/StdHep/defs.h"
#include <iostream>
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include <string>

#include "CLHEP/StdHep/ReadStdHep.hh"

namespace StdHep  {

bool findBlockType( std::istream & is, std::string & type )
{
    // check the state of the input stream
    if ( !is ) return false;
    //
    // look for the proper type
    std::string inputline;
    int pos;
    while( is ) {
        std::getline( is, inputline);
	if( inputline.find("BlockType ") == 0 ) {
	    pos = inputline.find(type);
	    if( pos > 0 ) return true;
	}
    }
    // no BlockType
    return false;
}

}	// StdHep
