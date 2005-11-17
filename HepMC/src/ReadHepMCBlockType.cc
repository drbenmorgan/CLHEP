// ----------------------------------------------------------------------
//
// ReadHepMCBlockType.cc
// Author: Lynn Garren
//
// read from an ascii file
// ----------------------------------------------------------------------

#include <sstream>
#include <fstream>
#include <string>

#include "CLHEP/HepMC/defs.h"
#include "CLHEP/HepMC/ReadHepMC.h"

namespace HepMC  {

std::string readBlockType    ( std::istream & is )
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

}	// HepMC
