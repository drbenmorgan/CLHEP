//////////////////////////////////////////////////////////////////////////
// 
// vertexListAncestors.cc
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"
#include <vector> 

namespace HepMC {

std::vector<GenParticle*> GenVertex::listAncestors()
{
   // return an empty vector if there are no parents
   std::vector<GenParticle*> parent;
   for ( particle_iterator p = particles_begin(ancestors);
	                   p != particles_end(ancestors); ++p ) {
      parent.push_back(*p);
   }
   return parent;
}

} // HepMC

