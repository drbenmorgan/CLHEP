// $Id: StdEventVertex.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// ----------------------------------------------------------------------
// StdEventVertex.cc
// L. Garren
// get a specific GenVertex
//  Treat the aggregate vertices as one big collection
//  Reference by barcode within collision
// ----------------------------------------------------------------------

#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep  {

HepMC::GenVertex* StdEvent::vertex( int iv ) const 
{
    if( iv == 0 ) return NULL;
    int vnum = abs(iv);
    int itot = 0;
    int iold, j;
    // loop over Collisions
    CollisionList::const_iterator cit(itsCollisionList.begin()), e(itsCollisionList.end());
    while(cit!=e) {
	iold = itot;		
	itot += (*cit)->vertices_size();
	// is vertex in this Collision?
	if( vnum <= itot && vnum > iold ) { 
	    // index relative to this Collision
	    // vertex barcodes are negative and never zero
            j = -(vnum - iold);	
	    return (*cit)->barcode_to_vertex(j);
	}
	++cit;
    }
    return NULL;
}

HepMC::GenVertex* StdEvent::vertex( int iv, int icol ) const 
{
    // if this is a valid collision, get the requested vertex
    HepMC::GenEvent* col = collision( icol );
    if( col ) return col->barcode_to_vertex(iv);
    return NULL;
}

}  // StdHep
