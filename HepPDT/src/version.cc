// $Id: version.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// version.cc
//
//  for now, this is a free function
//
// ----------------------------------------------------------------------

#include <iostream>

#include "CLHEP/HepPDT/Version.hh"

namespace HepPDT {

std::string versionName( )
{
    return "1.00.01";
}

void version( )
{
    std::cout << " --------------- HepPDT Version " << versionName()
              << " --------------- " << std::endl;
}

}	// HepPDT
