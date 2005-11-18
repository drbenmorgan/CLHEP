// ----------------------------------------------------------------------
//
// findBlockType.cc
// Author: Lynn Garren
//
// read from an ascii file
// find a block with the specified type
// ----------------------------------------------------------------------

#include <iostream>
#include <sstream>
#include <string>

#include "CLHEP/StdHep/defs.h"
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
