//////////////////////////////////////////////////////////////////////////
// 
// vertexListDescendants.cc
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"
#include <vector> 

namespace HepMC {


std::vector<GenParticle*> GenVertex::listDescendants()
{
   // return an empty vector if there are no children
   std::vector<GenParticle*> child;
   for ( particle_iterator p = particles_begin(descendants);
	                   p != particles_end(descendants); ++p ) {
      child.push_back(*p);
   }
   return child;
}

} // HepMC

