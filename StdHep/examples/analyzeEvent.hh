// ----------------------------------------------------------------------
// analyzeEvent.hh
// ----------------------------------------------------------------------

#ifndef ANALYZEEVENT_HH
#define ANALYZEEVENT_HH

#include "CLHEP/StdHep/StdEvent.hh"

void analyzeEvent( const StdHep::StdEvent * event );
void fill1DHist ( int ih, float x );

extern "C" {
    void hfill_ ( int * ih, float * x, float * y, float * wt);
}


#endif // ANALYZEEVENT_HH
