// $Id: ReadHepMCComment.cc,v 1.2 2003/08/13 20:00:11 garren Exp $
// ----------------------------------------------------------------------
//
// ReadHepMCComment.cc
// Author: Lynn Garren
//
// read from an ascii file
// ----------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include "CLHEP/HepMC/defs.h"
#include "CLHEP/HepMC/ReadHepMC.h"

namespace HepMC  {

std::string readComment( std::istream & is )
{
    std::string comment = " ";
    // check the state of the input stream
    if ( !is ) return comment;
    std::getline( is, comment);
    std::cout << "------------------------------------------------------"
              << std::endl;
    std::cout << comment << std::endl;
    std::cout << "------------------------------------------------------"
              << std::endl;
    return comment;
}

}	// HepMC
