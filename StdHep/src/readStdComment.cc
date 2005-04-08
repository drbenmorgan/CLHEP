// ----------------------------------------------------------------------
//
// readStdComment.cc
// Author: Lynn Garren
//
// read from an ascii file
// process a single event - do not combine events
// use explicit namespaces
// ----------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include "CLHEP/StdHep/defs.h"
#include "CLHEP/StdHep/ReadStdHep.hh"

std::string StdHep::readStdComment( std::istream & is )
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
