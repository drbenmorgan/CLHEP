// read the output of examPythiaToStdHep
//

#include "CLHEP/StdHep/defs.h"
#include <fstream>

#include "CLHEP/StdHep/StdHep.hh"
#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/StdHep/ReadStdHep.hh"
#include "CLHEP/StdHep/ConversionMethods.hh"
#include "analyzeEvent.hh"

extern "C" {
    void bookhist_ ( );
    void houtpu_ ( int * iun );
    void histdo_ ( );
}

int main()
{
    static char infile2[] = "examPythiaToStdHep.dat";	// pythia
    int iun=6;

    // open input strings
    std::ifstream is( infile2 );
    if( !is ) {
        std::cout << " cannot open " << infile2 << std::endl;
        exit(1);
    }

    // print version
    StdHep::printVersion();

    //  Initialize HBOOK
    bookhist_ ();

    // loop until we run out of data
    int iev=0, nblk=0;
    std::string block("first");
    std::string empty(" "), etype("StdEvent"), rtype("StdRunInfo");
    while( is && (block != empty) ) {
        // get the block type
	block = StdHep::readBlockType( is );
	++nblk;
	if( block == rtype ) {
	    // run
	    StdHep::StdRunInfo * run = StdHep::readStdRun( is );
	    std::cout << "Run " << run->runIdentifier() << std::endl;
	} else if ( block == etype ) {
	    // event
            StdHep::StdEvent* event = StdHep::readStdEvent( is );
	    // print the first event
            if( iev == 0 )  event->print();
	    analyzeEvent( event );
	    ++iev;
	}
    }
    std::cout << iev << " events and " << nblk << " blocks read" << std::endl;

    // write histograms
    houtpu_ ( & iun );
    histdo_ ();
    return 0;
}

