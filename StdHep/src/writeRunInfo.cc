// $Id: writeRunInfo.cc,v 1.2.2.1 2005/03/07 18:30:27 garren Exp $
// ----------------------------------------------------------------------
//
// writeRunInfo.cc
// Author: Lynn Garren
//
// write to an ostream in ascii format
// ----------------------------------------------------------------------

#include <iostream>

#include "CLHEP/StdHep/defs.h"
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
    os << "BlockType StdRunInfo" << std::endl;
    os << "RunID " << run->runIdentifier() << std::endl;
    os << "R " << run->runNumber() << " " 
       << run->eventsToGenerate() << " " 
       << run->eventsGenerated() << " " 
       << run->eventsWritten() << " " 
       << run->CoMEnergy() << " "
       << run->crossSection() << std::endl;
    // write seeds on a separate line
    os << "SeedList " << run->seedStream() << std::endl;
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
