//////////////////////////////////////////////////////////////////////////
// 
// particleListDescendants.cc
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"
#include <vector> 

namespace HepMC {

std::vector<GenParticle*> GenParticle::listDescendants() const
{
   // return an empty vector if there are no childs
   std::vector<GenParticle*> child;
   if( m_end_vertex ) {
       GenVertex::particle_iterator p;
       GenVertex::particle_iterator start = 
             m_end_vertex->particles_begin(descendants);
       GenVertex::particle_iterator end = 
             m_end_vertex->particles_end(descendants);
       for ( p = start; p != end; ++p ) {
	  child.push_back(*p);
       }
   }
   return child;
}

} // HepMC

