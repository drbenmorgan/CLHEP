// $Id: tree.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// ----------------------------------------------------------------------
// tree.cc
// print an event tree to the specified output stream (default is std::cout)
// start with signal vertex
// if no signal vertex, just loop over all vertices
//
//  place holder for now - just do simple print
// ----------------------------------------------------------------------

#include "StdHep/defs.h"
#include <iostream>

#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep  {

void StdEvent::tree( std::ostream & os ) const
{
    os << " -------------------------------------------------------- " << std::endl;
    os << "           StdEvent " << itsEventNumber << " tree " << std::endl;
    os << " -------------------------------------------------------- " << std::endl;
    // loop over Collisions
    CollisionList::const_iterator cit(itsCollisionList.begin()), e(itsCollisionList.end());
    while(cit!=e) {
        os << "Collision " << (*cit)->event_number() << std::endl;
	// loop over vertices
	for ( HepMC::GenEvent::vertex_const_iterator vtx = (*cit)->vertices_begin();
	      vtx != (*cit)->vertices_end(); ++vtx ) {
	    (*vtx)->print(os); 
	}
        ++cit;
    }
}

}  // StdHep
