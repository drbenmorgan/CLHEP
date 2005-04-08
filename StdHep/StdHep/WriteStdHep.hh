// ----------------------------------------------------------------------
//
// WriteStdHep.h
// Author: Lynn Garren
//
// write to an ostream in ascii format
// ----------------------------------------------------------------------
#ifndef WRITESTDHEP_HH
#define WRITESTDHEP_HH

#include <iostream>
#include <string>

#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/StdHep/StdRunInfo.hh"

namespace StdHep  {

std::ostream & writeComment( std::ostream & os, std::string const comment );
std::ostream & writeLegend( std::ostream & os );
std::ostream & writeStdEvent( std::ostream & os, StdEvent const * evt );
std::ostream & operator << ( std::ostream & os, StdEvent const * evt );
std::ostream & writeRunInfo( std::ostream & os, StdRunInfo const * run );
std::ostream & operator << ( std::ostream & os, StdRunInfo const * run );

}	// StdHep

#endif // WRITESTDHEP_HH

