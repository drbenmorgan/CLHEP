// 
// generate pythia events and look at them with C++ code
// generate pythia - convert to hepevt common block - convert to c++ class
//
// main program must be in C++

#include "CLHEP/StdHep/defs.h"
#include <fstream>

#include "CLHEP/StdHep/StdHep.hh"
#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/StdHep/StdRunInfo.hh"
#include "CLHEP/StdHep/WriteStdHep.hh"
#include "CLHEP/StdHep/ConversionMethods.hh"
#include "analyzeEvent.hh"

extern "C" {
    void stdpytcxxinit_ ( int * nevt );
    void stdflpyxsec_ ( int * nevt );
    void pyevnt_ ( );
    void pystat_ ( int * stat );
    void pylist_ ( int * il );
    void lunhep_ ( int * idir );
    void stdpytcxx_xsec_ ( int * nevt );
    void stdpytcxxend_ ( );
}

int main()
{
    int nevt=100;
    int idir=1, mstat=1, prt=2;
    int i;
    static char outfile[] = "examPythiaToStdHep.dat";
    std::string title = "StdHep/Pythia example";

    // print version
    StdHep::printVersion();
    
    // initialize pythia
    stdpytcxxinit_ ( & nevt );

    // open the output stream
    std::ofstream os( outfile );
    if( !os ) {
        std::cout << "error opening output file"  << std::endl;
        exit(1);
    }
    StdHep::printVersion( os );

    // get conversion object
    StdHep::ConvertStdHep conv;

    // setup run header
    stdflpyxsec_ ( & nevt );
    StdHep::StdRunInfo * run = StdHep::getRunInfoFromSTDCM( 101 );
    run->setRunIdentifier( title );
    
    // write legend
    StdHep::writeLegend( os );
    // write title as comment
    StdHep::writeComment( os, title );
    // write run header
    StdHep::writeRunInfo( os, run );

    // loop over events
    for (i = 0; i < nevt; ++i) {
        pyevnt_ ();
	lunhep_ ( & idir );
        StdHep::StdEvent* event = conv.getStdEvent(i);
	// print the first event
        if( i == 0 ) {
	    pylist_( & prt );
	    if ( event ) event->print();
	}
	if ( event ) {
            std::cout << "at event "  << event->eventNumber() << std::endl;
	    analyzeEvent( event );
	    // write the event
	    os << event;
        }
	delete event; 		// done with the event - clean up
    }

    // get end of run statistics
    pystat_( & mstat );

    // write end of run information
    stdflpyxsec_ ( & nevt );
    run = StdHep::getRunInfoFromSTDCM( 101 );
    run->setRunIdentifier( title );
    StdHep::writeRunInfo( os, run );
    
    // end run
    stdpytcxxend_ ( );
    
    return 0;
}
