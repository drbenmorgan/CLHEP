// $Id: ReadHepMCFindBlock.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// ReadHepMCFindBlock.cc
// Author: Lynn Garren
//
// read from an ascii file
// ----------------------------------------------------------------------

#include "HepMC/defs.h"
#include <iostream>
#include <fstream>
#include <string>

#include "CLHEP/HepMC/ReadHepMC.h"

namespace HepMC  {

bool  findBlockType( std::istream & is, std::string & type )
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

}	// HepMC
