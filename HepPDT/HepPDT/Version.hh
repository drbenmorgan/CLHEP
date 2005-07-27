// ----------------------------------------------------------------------
//
// Version.hh
// Author:  Lynn Garren
//
//  for now, this is a free function
//
// ----------------------------------------------------------------------
#ifndef HEPPDTVERSION_HH
#define HEPPDTVERSION_HH

#include <string>
#include <iostream>

namespace HepPDT {

void version( );			// print version
void writeVersion( std::ostream & os );	// write version to os
std::string versionName( );	// return version

}	// HepPDT

#endif // HEPPDTVERSION_HH
