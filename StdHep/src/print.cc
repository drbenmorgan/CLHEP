// $Id: print.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// ----------------------------------------------------------------------
// print.cc
// print an event to the specified output stream (default is std::cout)
// ----------------------------------------------------------------------

#include "StdHep/defs.h"
#include <iostream>

#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep  {

void StdEvent::print( std::ostream & os ) const
{
    os << " -------------------------------------------------------- " << std::endl;
    os << "           StdEvent " << itsEventNumber << " with " 
       << numCollisions() << " collisions" << std::endl;
    os << " -------------------------------------------------------- " << std::endl;
    // loop over Collisions
    CollisionList::const_iterator cit(itsCollisionList.begin()), e(itsCollisionList.end());
    while(cit!=e) {
        os << "Begin Collision " << (*cit)->event_number() << std::endl;
        (*cit)->print( os );
        ++cit;
    }
}

}  // StdHep
