//////////////////////////////////////////////////////////////////////////
// 
// vertexListChildren.cc
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/GenVertex.h"
#include <vector> 

namespace HepMC {

std::vector<GenParticle*> GenVertex::listChildren() const
{
   // return an empty vector if there are no children
   std::vector<GenParticle*> child;
   for ( particles_out_const_iterator p = particles_out_const_begin();
	                   p != particles_out_const_end(); ++p ) {
      child.push_back(*p);
   }
   return child;
}

} // HepMC

