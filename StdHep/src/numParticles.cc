// $Id: numParticles.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// ----------------------------------------------------------------------
// numParticles.cc
// add a Collision
// ----------------------------------------------------------------------

#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep  {

int  StdEvent::numParticles( ) const
{ 
    int num=0;
    // loop over Collisions
    CollisionList::const_iterator cit(itsCollisionList.begin()), e(itsCollisionList.end());
    while(cit!=e) {
        num += (*cit)->particles_size();
        ++cit;
    }
    return num;
}

}  // StdHep
