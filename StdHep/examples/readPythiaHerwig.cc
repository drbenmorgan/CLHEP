// read and combine the output of examPythiaToStdHep and examHerwigToStdHep
//

#include "CLHEP/StdHep/defs.h"
#include <fstream>

#include "CLHEP/StdHep/StdHep.hh"
#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/StdHep/ReadStdHep.hh"
#include "CLHEP/StdHep/ConversionMethods.hh"
#include "analyzeEvent.hh"

void analyzeEvent( const StdHep::StdEvent * event );
void fill_1D_histo ( int ih, float x );

extern "C" {
    void bookhist_ ( );
    void hfill_ ( int * ih, float * x, float * y, float * wt);
    void houtpu_ ( int * iun );
    void histdo_ ( );
}

int main()
{
    static char infile1[] = "examHerwigtoStdHep.dat";	// herwig
    static char infile2[] = "examPythiaToStdHep.dat";	// pythia
    int iun=6;

    // print version
    StdHep::printVersion();

    // open input streams
    std::ifstream is1( infile1 );
    if( !is1 ) {
        std::cout << " cannot open " << infile1 << std::endl;
        exit(1);
    }
    std::ifstream is2( infile2 );
    if( !is2 ) {
        std::cout << " cannot open " << infile2 << std::endl;
        exit(1);
    }

    //  Initialize HBOOK
    bookhist_ ();

    // loop until we run out of events
    int i=0;
    StdHep::StdEvent* evt1 = StdHep::findNextStdEvent( is1 );
    StdHep::StdEvent* evt2 = StdHep::findNextStdEvent( is2 );
    while ( is1 && is2 ) {
        StdHep::StdEvent* event = combineEvents( evt1, evt2 );
	if(event ) {
	    ++i;
            event->setEventNumber(i);
            if( i == 1 )  event->print();
	    analyzeEvent( event );
	}
	delete event;		// cleanup
	// look for next events
	evt1 = StdHep::findNextStdEvent( is1 );
	evt2 = StdHep::findNextStdEvent( is2 );
    }
    std::cout << i << " events created" << std::endl;

    // write histograms
    houtpu_ ( & iun );
    histdo_ ();
    return 0;
}

