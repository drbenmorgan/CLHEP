// ----------------------------------------------------------------------
//
// version.cc
// Author: Lynn Garren
//
//  for now, this is a free function
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/Version.hh"

namespace HepPDT {

std::string versionName( )
{
    return "1.02.02";
}

void version( )
{
    std::cout << " --------------- HepPDT Version " << versionName()
              << " --------------- " << std::endl;
}

void writeVersion( std::ostream & os )
{
    os << "             HepPDT Version: " << versionName() << std::endl;
}

}	// HepPDT
