// $Id: WriteHepMC.cc,v 1.2.2.1 2005/03/03 23:25:58 garren Exp $
// ----------------------------------------------------------------------
//
// WriteHepMC.cc
// Author: Lynn Garren, Matt.Dobbs
//
// write to an ostream in ascii format
// ----------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "CLHEP/HepMC/defs.h"
#include "CLHEP/HepMC/WriteHepMC.h"
#include "CLHEP/HepMC/GenEvent.h"

using namespace HepMC;

namespace HepMC  {

std::ostream & writeGenEvent( std::ostream & os, GenEvent const * evt )
{ 
    // make sure both event and os are valid
    if ( !evt || !os ) return os;
    // set precision
    os.precision(16);
    os.setf(HepIOS::dec,HepIOS::basefield);		// integer
    os.setf(HepIOS::scientific,HepIOS::floatfield);	// floating
    //
    // output the event data including the number of primary vertices
    //  and the total number of vertices
    std::vector<unsigned long> random = evt->random_states();
    os << "BlockType GenEvent" << std::endl;
    os << "E" << " " << evt->event_number();
    Detail::output( os, evt->event_scale() );
    Detail::output( os, evt->alphaQCD() );
    Detail::output( os, evt->alphaQED() );
    os << " " << evt->signal_process_id();
    os << " " << (evt->signal_process_vertex() ?
	      evt->signal_process_vertex()->barcode() : 0);
    os << " " << evt->vertices_size()	// total number of vertices.
       << " " << (int)random.size();
    for ( std::vector<unsigned long>::iterator rs = random.begin(); 
	  rs != random.end(); ++rs ) {
        os << " " << *rs;
    }
    os << " " << (int)evt->weights().size();
    for ( WeightContainer::const_iterator w = evt->weights().begin(); 
	  w != evt->weights().end(); ++w ) {
        os << " " << *w;
    }
    os << std::endl;
    //
    // loop over all vertices to get remaining vertex and particle info
    for ( GenEvent::vertex_const_iterator v = evt->vertices_begin();
	  v != evt->vertices_end(); ++v ) {
	Detail::writeVertex( os, *v );
    }
    return os;
}

std::ostream & operator << ( std::ostream & os, GenEvent const * evt )
{
    return writeGenEvent( os, evt);
}

std::ostream & writeLegend( std::ostream & os )
{
    os << "BlockType Legend" << std::endl;
    os << " Event line begins with E and contains" << std::endl;
    os << "   event_number event_scale alphaQCD alphaQED"
       << " signal_process_id signal_process_vertex num_vertices"
       << " random_size random_info" << std::endl;
    os << " Vertex line begins with V and contains" << std::endl;
    os << "   barcode id x y z t num_orphans_in"
       << " particles_out_size num_wgt weight_info" << std::endl;
    os << " Particle line begins with P and contains" << std::endl;
    os << "   barcode pdg_id px py pz E status theta phi"
       << " end_vertex flow" << std::endl;
    os << std::endl;
    return os;
}

std::ostream & flushOutput( std::ostream & os )
{ 
    os << std::flush;
    return os;
}

}	// HepMC
