// 
// Generating herwig events and look at them with C++ code
// generate herwig - convert to hepevt common block - convert to c++ class
//
// main program must be in C++

#include "CLHEP/config/CLHEP.h"
#include "CLHEP/config/fstream.h"

#include "CLHEP/StdHep/StdHep.hh"
#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/StdHep/WriteStdHep.hh"
#include "CLHEP/StdHep/ConversionMethods.hh"
#include "analyzeEvent.hh"

extern "C" {
    void stdhwgcxxinit_ ( int * nevt );
    void stdhwgcxx_ ( );
    void stdhwgcxx_xsec_ ( );
    void stdhwgcxxend_ ( );
    void hwghep_ ( int * idir );
}

int main()
{
    int nevt=20;
    int idir=1;
    int i;
    static char outfile[] = "examHerwigtoStdHep.dat";
    std::string title = "StdHep/Herwig example";

    // print version
    StdHep::printVersion();

    // initialize herwig and stdhep
    stdhwgcxxinit_ ( & nevt );

    // get conversion object
    StdHep::ConvertStdHep conv;
    // turn off mother/daughter consistency checking for Herwig
    conv.setInconsitencyErrors( false );

    // open the output stream
    std::ofstream os( outfile );
    if( !os ) {
        HepStd::cout << "error opening output file"  << HepStd::endl;
        exit(1);
    }
    StdHep::printVersion( os );
    // write legend
    StdHep::writeLegend( os );
    // write title as comment
    StdHep::writeComment( os, title );

    // loop over events
    for (i = 0; i < nevt; i++) {
        stdhwgcxx_();
	hwghep_ ( & idir );
        StdHep::StdEvent* event = conv.getStdEvent(i);
	if ( event ) {
	    // print the first event
            if( i == 0 )  event->print();
            HepStd::cout << "at event "  << event->eventNumber() << HepStd::endl;
	    analyzeEvent( event );
	    // write the event
	    os << event;
	}
	delete event; 		// done with the event - clean up
    }

    // end run
    stdhwgcxxend_ ();
    
    return 0;
}

