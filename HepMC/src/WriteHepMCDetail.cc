// ----------------------------------------------------------------------
//
// WriteHepMC.cc
// Author: Lynn Garren, Matt.Dobbs
//
// internal methods needed to write to an ostream in ascii format
// don't use implicit namespace, since this seems to confuse old compilers
// ----------------------------------------------------------------------

#include <iostream>
#include <fstream>

#include "CLHEP/HepMC/defs.h"
#include "CLHEP/HepMC/WriteHepMC.h"
#include "CLHEP/HepMC/GenEvent.h"

namespace HepMC  {

std::ostream & HepMC::Detail::writeVertex( std::ostream & os, HepMC::GenVertex const * v )
{ 
    if ( !v  ) {
	std::cerr << "WriteHepMC::writeVertex !v, v="
		  << v << " setting badbit" << std::endl;
	os.clear(HepIOS::badbit); 
	return os;
    }
    // count the number of orphan particles going into v
    int numOrphan = 0;
    for ( HepMC::GenVertex::particles_in_const_iterator p = v->particles_in_const_begin();
	  p != v->particles_in_const_end(); ++p ) {
	if ( !(*p)->production_vertex() ) ++numOrphan;
    }
    //
    os << 'V' << " " << v->barcode()
              << " " << v->id();
    HepMC::Detail::output( os, v->position().x() );
    HepMC::Detail::output( os, v->position().y() );
    HepMC::Detail::output( os, v->position().z() );
    HepMC::Detail::output( os, v->position().t() );
    os        << " " << numOrphan
              << " " << (int)v->particles_out_size()
              << " " << (int)v->weights().size();
    for ( HepMC::WeightContainer::const_iterator w = v->weights().begin(); 
	  w != v->weights().end(); ++w ) {
       os << " " << *w;
    }
    os << std::endl;
    for ( HepMC::GenVertex::particles_in_const_iterator p = v->particles_in_const_begin();
	  p != v->particles_in_const_end(); ++p ) {
	if ( !(*p)->production_vertex() ) {
	    HepMC::Detail::writeParticle( os, *p );
	}
    }
    for ( HepMC::GenVertex::particles_out_const_iterator p 
	      = v->particles_out_const_begin();
	  p != v->particles_out_const_end(); ++p ) {
	HepMC::Detail::writeParticle( os, *p );
    }
    return os;
}

std::ostream & HepMC::Detail::writeParticle( std::ostream & os, HepMC::GenParticle const * p )
{
    if ( !p ) {
	std::cerr << "WriteHepMC::writeParticle !p, p="
		  << p << " setting badbit" << std::endl;
	os.clear(HepIOS::badbit); 
	return os;
    }
    os << 'P' << " " << p->barcode()
              << " " << p->pdg_id();
    HepMC::Detail::output( os, p->momentum().px() );
    HepMC::Detail::output( os, p->momentum().py() );
    HepMC::Detail::output( os, p->momentum().pz() );
    HepMC::Detail::output( os, p->momentum().e() );
    HepMC::Detail::output( os, p->generatedMass() );
    os        << " " << p->status();
    HepMC::Detail::output( os, p->polarization().theta() );
    HepMC::Detail::output( os, p->polarization().phi() );
    os        << " " << ( p->end_vertex() ? p->end_vertex()->barcode() : 0 )
              << " " << p->flow() << std::endl;
    return os;
} 

std::ostream & HepMC::Detail::output( std::ostream & os, const double& d )
{ 
    if ( d == 0. ) {
	os << ' ' << (int)0;
    } else {
	os << ' ' << d;
    }
    return os;
}

}	// HepMC::Detail
