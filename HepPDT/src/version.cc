// $Id: version.cc,v 1.1.1.1.4.2 2005/03/18 22:26:44 garren Exp $
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
    return "1.01.00";
}

void version( )
{
    std::cout << " --------------- HepPDT Version " << versionName()
              << " --------------- " << std::endl;
}

}	// HepPDT
