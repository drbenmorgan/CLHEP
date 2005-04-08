// ----------------------------------------------------------------------
//
// writeLegend.cc
// Author: Lynn Garren, Matt.Dobbs
//
// write to an ostream in ascii format
// ----------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "CLHEP/StdHep/defs.h"
#include "CLHEP/StdHep/WriteStdHep.hh"
#include "CLHEP/StdHep/StdEvent.hh"

using namespace StdHep;

namespace StdHep  {

std::ostream & writeLegend( std::ostream & os )
{
    os << "BlockType Legend" << std::endl;
    os << " StdHep Event line begins with S and contains" << std::endl;
    os << "   event_number number_collisions" << std::endl;
    os << " Collision line begins with E and contains" << std::endl;
    os << "   event_number event_scale alphaQCD alphaQED"
       << " signal_process_id signal_process_vertex num_vertices"
       << " random_size random_info" << std::endl;
    os << " Vertex line begins with V and contains" << std::endl;
    os << "   barcode id x y z t num_orphans_in"
       << " particles_out_size num_wgt weight_info" << std::endl;
    os << " Particle line begins with P and contains" << std::endl;
    os << "   barcode pdg_id px py pz E status theta phi"
       << " end_vertex flow" << std::endl;
    return os;
}

}	// StdHep
