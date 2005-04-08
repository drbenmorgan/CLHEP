// ----------------------------------------------------------------------
//
// ReadStdHep.hh
// Author: Lynn Garren
//
// read from an ascii file
// ----------------------------------------------------------------------
#ifndef READSTDHEP_HH
#define READSTDHEP_HH

#include <iostream>
#include <string>
#include <map>

#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/StdHep/StdRunInfo.hh"

namespace StdHep  {

std::string readBlockType( std::istream & is );
bool findBlockType( std::istream & is, std::string & type );
StdEvent * readStdEvent( std::istream & is );
StdEvent * findNextStdEvent( std::istream & is );
StdRunInfo * readStdRun( std::istream & is );
std::string readStdComment( std::istream & is );

  namespace Detail {

     StdEvent * readStdEventInfo( std::istream & is, std::string & evline );
     StdRunInfo * readRunInfo( std::istream & is, std::string & evline );
     void  parseStdEventLine( std::string & evline, int & evnum, int & ncol );

  }	// Detail

}	// StdHep

#endif // READSTDHEP_HH
