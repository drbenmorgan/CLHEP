//////////////////////////////////////////////////////////////////////////
// 
// particleListChildren.cc
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"
#include <vector> 

namespace HepMC {

std::vector<GenParticle*> GenParticle::listChildren() const
{
   // return an empty vector if there are no childs
   std::vector<GenParticle*> child;
   if( m_end_vertex ) {
       GenVertex::particles_out_const_iterator p;
       GenVertex::particles_out_const_iterator start = 
             m_end_vertex->particles_out_const_begin();
       GenVertex::particles_out_const_iterator end = 
             m_end_vertex->particles_out_const_end();
       for ( p = start; p != end; ++p ) {
	  child.push_back(*p);
       }
   }
   return child;
}

} // HepMC

