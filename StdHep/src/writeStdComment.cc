// $Id: writeStdComment.cc,v 1.2 2003/08/13 20:00:13 garren Exp $
// ----------------------------------------------------------------------
//
// writeComment.cc
// Author: Lynn Garren
//
// write a comment
// ----------------------------------------------------------------------

#include <iostream>
#include <string>

#include "CLHEP/StdHep/defs.h"
#include "CLHEP/StdHep/WriteStdHep.hh"

namespace StdHep  {

std::ostream & writeComment( std::ostream & os, std::string const comment )
{
    os << "BlockType Comment" << std::endl;
    os << comment << std::endl;
    return os;
}

}	// StdHep
