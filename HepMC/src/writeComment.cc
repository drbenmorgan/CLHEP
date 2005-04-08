// ----------------------------------------------------------------------
//
// writeComment.cc
// Author: Lynn Garren
//
// write a comment
// ----------------------------------------------------------------------

#include <iostream>
#include <string>

#include "CLHEP/HepMC/defs.h"
#include "CLHEP/HepMC/WriteHepMC.h"

namespace HepMC  {

std::ostream & writeComment( std::ostream & os, std::string const comment )
{
    os << "BlockType Comment" << std::endl;
    os << comment << std::endl;
    return os;
}

}	// HepMC
