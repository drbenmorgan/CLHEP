// $Id: writeComment.cc,v 1.2 2003/08/13 20:00:11 garren Exp $
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
