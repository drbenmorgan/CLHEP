//////////////////////////////////////////////////////////////////////////
// 
// particleListAncestors.cc
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"
#include <vector> 

namespace HepMC {

std::vector<GenParticle*> GenParticle::listAncestors() const
{
   // return an empty vector if there are no parents
   std::vector<GenParticle*> parent;
   if( m_production_vertex ) {
       GenVertex::particle_iterator p;
       GenVertex::particle_iterator start = 
             m_production_vertex->particles_begin(ancestors);
       GenVertex::particle_iterator end = 
             m_production_vertex->particles_end(ancestors);
       for ( p = start; p != end; ++p ) {
	  parent.push_back(*p);
       }
   }
   return parent;
}

} // HepMC

