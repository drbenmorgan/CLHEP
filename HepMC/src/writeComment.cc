// $Id: writeComment.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// writeComment.cc
// Author: Lynn Garren
//
// write a comment
// ----------------------------------------------------------------------

#include "HepMC/defs.h"
#include <iostream>
#include <string>

#include "CLHEP/HepMC/WriteHepMC.h"

namespace HepMC  {

std::ostream & writeComment( std::ostream & os, std::string const comment )
{
    os << "BlockType Comment" << std::endl;
    os << comment << std::endl;
    return os;
}

}	// HepMC
