// $Id: WriteStdHep.cc,v 1.2 2003/08/13 20:00:13 garren Exp $
// ----------------------------------------------------------------------
//
// WriteStdHep.cc
// Author: Lynn Garren, Matt.Dobbs
//
// write to an ostream in ascii format
// ----------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "CLHEP/StdHep/defs.h"
#include "CLHEP/StdHep/StdEvent.hh"
#include "CLHEP/StdHep/WriteStdHep.hh"
#include "CLHEP/HepMC/WriteHepMC.h"

using namespace StdHep;

namespace StdHep  {

std::ostream & writeStdEvent( std::ostream & os, StdEvent const * evt )
{ 
    int i;
    // make sure both event and os are valid
    if ( !evt || !os ) return os;
    // set precision
    os.precision(16);
    os.setf(HepIOS::dec,HepIOS::basefield);		// integer
    os.setf(HepIOS::scientific,HepIOS::floatfield);	// floating
    // output StdEvent data
    os << "BlockType StdEvent" << std::endl;
    int ncol = evt->size();
    os << "S" << " " << evt->eventNumber() << " " << ncol << std::endl;
    // loop over collisions
    for( i=0; i<ncol; ++i) {
        HepMC::GenEvent* col = evt->collision(i);
	//
	// output the GenEvent data including the number of primary vertices
	//  and the total number of vertices
	std::vector<double> random = col->random_states();
	os << "E" << " " << col->event_number();
	HepMC::Detail::output( os, col->event_scale() );
	HepMC::Detail::output( os, col->alphaQCD() );
	HepMC::Detail::output( os, col->alphaQED() );
	os << " " << col->signal_process_id();
	os << " " << (col->signal_process_vertex() ?
		  col->signal_process_vertex()->barcode() : 0);
	os << " " << col->vertices_size()	// total number of vertices.
	   << " " << (int)random.size();
	for ( std::vector<double>::iterator rs = random.begin(); 
	      rs != random.end(); ++rs ) {
            os << " " << *rs;
	}
	os << " " << (int)col->weights().size();
	for ( HepMC::WeightContainer::const_iterator w = col->weights().begin(); 
	      w != col->weights().end(); ++w ) {
            os << " " << *w;
	}
	os << std::endl;
	//
	// loop over all vertices to get remaining vertex and particle info
	for ( HepMC::GenEvent::vertex_const_iterator v = col->vertices_begin();
	      v != col->vertices_end(); ++v ) {
	    HepMC::Detail::writeVertex( os, *v );
	}
    }
    return os;
}

std::ostream & operator << ( std::ostream & os, StdEvent const * evt )
{
    return writeStdEvent( os, evt);
}

}	// StdHep
