//////////////////////////////////////////////////////////////////////////
// 
// vertexListParents.cc
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"
#include <vector> 

namespace HepMC {

std::vector<GenParticle*> GenVertex::listParents() const
{
   // return an empty vector if there are no parents
   std::vector<GenParticle*> parent;
   for ( particles_in_const_iterator p = particles_in_const_begin();
	                   p != particles_in_const_end(); ++p ) {
      parent.push_back(*p);
   }
   return parent;
}

} // HepMC

