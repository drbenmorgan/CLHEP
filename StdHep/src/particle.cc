// $Id: particle.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// ----------------------------------------------------------------------
// particle.cc
// treat the aggregate particles as one big collection
//  Reference by barcode within collision
// ----------------------------------------------------------------------

#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep  {

HepMC::GenParticle* StdEvent::particle( int pnum ) const  
{
    int itot = 0;
    int iold, j;
    // loop over Collisions
    CollisionList::const_iterator cit(itsCollisionList.begin()), e(itsCollisionList.end());
    while(cit!=e) {
	iold = itot;		
	itot += (*cit)->particles_size();
	// is particle in this Collision?
	if( pnum < itot && pnum >= iold ) { 
	    // index relative to this Collision
	    // GenEvent particle(i) begins with index 1, not index 0
            j = pnum - iold + 1;	
	    return (*cit)->particle(j);
	}
	++cit;
    }
    return NULL;
}

HepMC::GenParticle* StdEvent::particle( int pnum, int icol ) const  
{
    // if this is a valid collision, get the requested particle
    HepMC::GenEvent* col = collision( icol );
    if( col ) return col->particle(pnum);
    return NULL;
}

}  // StdHep
