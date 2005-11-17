// ----------------------------------------------------------------------
//
// readRunInfo.cc
// Author: Lynn Garren
//
// read from an ascii file
// use explicit namespaces
// ----------------------------------------------------------------------

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "CLHEP/StdHep/defs.h"
#include "CLHEP/StdHep/ReadStdHep.hh"
#include "CLHEP/HepMC/ReadHepMC.h"
#include "CLHEP/StdHep/StdRunInfo.hh"

StdHep::StdRunInfo * StdHep::Detail::readRunInfo( std::istream & is, std::string & evline )
{
    int runno=0, ntogen=0, ngen=0, nwrt=0, nseed=0;
    double com=0., cross=0., seed=0.;
    std::string key;
    std::string runid;
    std::string newline;
    runid = evline.substr(6,(evline.length()-6));
    if( is ) {
        std::getline( is, newline);
	if( newline.find("R ") == 0 ) {
            std::istringstream rstr( newline.c_str() );
	    rstr >> key 
		  >> runno
		  >> ntogen
		  >> ngen
		  >> nwrt
		  >> com
		  >> cross
		  >> nseed;
        }
    }
    StdHep::StdRunInfo * run = 
             new StdHep::StdRunInfo( runno, ntogen, ngen, nwrt, com, cross );
    run->setRunIdentifier( runid );
    if( is && (nseed > 0 ) ) {
        std::getline( is, newline);
	if( newline.find("SeedList ") == 0 ) {
            std::istringstream sstr( newline.c_str() );
            sstr >> key;
            for( int i=0; i<nseed; ++i ) {
                sstr >> seed;
                run->appendSeed( seed );
            }
	} else {
	    std::cout << "readRunInfo: PROBLEM " 
	              << "expected random state line" << std::endl;
            std::cout << "  instead found " << newline << std::endl;
	}
    }
    if( is ) {
        std::getline( is, newline);
	if( newline.find("RunInfo ") == 0 ) {
            std::istringstream sstr( newline.c_str() );
            std::string gname, pname;
            sstr >> key >> gname >> pname;
            run->setGeneratorName( gname );
            run->setPdfName( pname );
	} else {
	    std::cout << "readRunInfo: PROBLEM " 
	              << "expected RunInfo line" << std::endl;
            std::cout << "  instead found " << newline << std::endl;
	}
    }
    return run;
}
