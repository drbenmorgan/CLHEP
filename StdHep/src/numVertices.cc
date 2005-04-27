// -*- C++ -*-
//
// ----------------------------------------------------------------------
// numVertices.cc
// ----------------------------------------------------------------------

#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep  {

int  StdEvent::numVertices( ) const
{ 
    int num=0;
    // loop over Collisions
    CollisionList::const_iterator cit(itsCollisionList.begin()), e(itsCollisionList.end());
    while(cit!=e) {
        num += (*cit)->vertices_size();
        ++cit;
    }
    return num;
}

}  // StdHep
