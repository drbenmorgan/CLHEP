// $Id: combineEvents.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// combineEvents.cc
// Author: Lynn Garren
//
// combine 2 StdHep events into a single event
// ----------------------------------------------------------------------
#include "StdHep/defs.h"
#include <iostream>
#include <fstream>
#include <string>

#include "CLHEP/StdHep/StdHep.hh"
#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep  {

StdEvent * combineEvents( StdEvent * evt1, StdEvent * evt2, int evnum )
{
    if( !evt1 && !evt2 ) return NULL;
    if( !evt1 && evt2 ) return evt2;
    if( evt1 && !evt2 ) return evt1;
    // create base event
    StdEvent * evt = evt1;
    // set new event number
    if( evnum > 0 ) evt->setEventNumber( evnum );
    // now add the collisions from evt2
    // loop over Collisions
    StdEvent::CollisionList::const_iterator cit(evt2->begin()), e(evt2->end());
    while(cit!=e) {
	evt->appendCollision( (*cit) );
        ++cit;
    }
    return evt;
}

}	// StdHep
