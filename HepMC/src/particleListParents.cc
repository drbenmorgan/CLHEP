//////////////////////////////////////////////////////////////////////////
// 
// particleListParents.cc
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"
#include <vector> 

namespace HepMC {

std::vector<GenParticle*> GenParticle::listParents() const
{
   // return an empty vector if there are no parents
   std::vector<GenParticle*> parent;
   if( m_production_vertex ) {
       GenVertex::particles_in_const_iterator p;
       GenVertex::particles_in_const_iterator start = 
             m_production_vertex->particles_in_const_begin();
       GenVertex::particles_in_const_iterator end = 
             m_production_vertex->particles_in_const_end();
       for ( p = start; p != end; ++p ) {
	  parent.push_back(*p);
       }
   }
   return parent;
}

} // HepMC

