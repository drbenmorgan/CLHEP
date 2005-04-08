// -*- C++ -*-
//
// ----------------------------------------------------------------------
// printVersion.cc
// Author: Lynn Garren
//
// fill and print the StdHep version information
// must be accessable by C, so use string.h
// ----------------------------------------------------------------------

#include "CLHEP/StdHep/defs.h"
#include <iostream>
#include <string.h>		// for strcpy

#include "CLHEP/StdHep/StdHep.hh"
#include "CLHEP/StdHep/StdHepVersion.h"

namespace StdHep  {

void printVersion( std::ostream & os )
{
//   static int ncalls=0;
//   if( ncalls == 0 ) {
//      ncalls++;
      strcpy( StdHepVersion.version , "5.01     ");
      strcpy( StdHepVersion.date , "April 15, 2002    ");
      os << std::endl;
      os << "*************************************************************" << std::endl;
      os << "*    StdHep version " << StdHepVersion.version 
         << " - " << StdHepVersion.date << "          *" << std::endl;
      os << "*************************************************************" << std::endl;
      os << std::endl;
//   }

}

}	// StdHep
