// ----------------------------------------------------------------------
//
// particleCollision.cc
//
// ----------------------------------------------------------------------

#include "CLHEP/HepMC/GenParticle.h"

namespace HepMC  {

int     GenParticle::collisionNumber() const
{
    return itsCollisionNumber;
}

void GenParticle::setCollisionNumber ( int coll )
{
    itsCollisionNumber = coll;
}

}  // HepMC
