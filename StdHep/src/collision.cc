// $Id: collision.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// ----------------------------------------------------------------------
// collision.cc
// treat the aggregate collisions as one big collection
// much better to use pointers
// ----------------------------------------------------------------------

#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/HepMC/GenEvent.h"

namespace StdHep  {

HepMC::GenEvent* StdEvent::collision( int ic ) const  
{
    if( ic < 0 ) return NULL;
    if( (unsigned)ic < itsCollisionList.size() ) return itsCollisionList[ic];
    return NULL;
}

}  // StdHep
