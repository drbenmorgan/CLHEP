// $Id: writeRunInfo.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// writeRunInfo.cc
// Author: Lynn Garren
//
// write to an ostream in ascii format
// ----------------------------------------------------------------------

#include "StdHep/defs.h"
#include <iostream>

#include "CLHEP/StdHep/StdRunInfo.hh"
#include "CLHEP/StdHep/WriteStdHep.hh"

using namespace StdHep;

namespace StdHep  {

std::ostream & writeRunInfo( std::ostream & os, StdRunInfo const * run )
{ 
    // make sure both run and os are valid
    if ( !run || !os ) return os;
    // set precision
    os.precision(16);
    os.setf(HepIOS::dec,HepIOS::basefield);		// integer
    os.setf(HepIOS::scientific,HepIOS::floatfield);	// floating
    // output StdRunInfo data
    int nseed = (int)run->size();
    os << "BlockType StdRunInfo" << std::endl;
    os << "RunID " << run->runIdentifier() << std::endl;
    os << "R " << run->runNumber() << " " 
       << run->eventsToGenerate() << " " 
       << run->eventsGenerated() << " " 
       << run->eventsWritten() << " " 
       << run->CoMEnergy() << " "
       << run->crossSection() << " "
       << nseed << std::endl;
    // write seeds on a separate line
    os << "SeedList " ;
    for( int i=0; i<nseed; ++i ) {
        os << " " << run->seed( i );
    }
    os << std::endl;
    // write strings
    os << "RunInfo " << run->generatorName() 
       << " " << run->pdfName() << std::endl;
    return os;
}

std::ostream & operator << ( std::ostream & os, StdRunInfo const * run )
{
    return writeRunInfo( os, run);
}

}	// StdHep
