// $Id: Version.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// Version.hh
//
//  for now, this is a free function
//
// ----------------------------------------------------------------------
#ifndef HEPPDTVERSION_HH
#define HEPPDTVERSION_HH

#include <string>

namespace HepPDT {

void version( );		// print version
std::string versionName( );	// return version

}	// HepPDT

#endif // HEPPDTVERSION_HH
