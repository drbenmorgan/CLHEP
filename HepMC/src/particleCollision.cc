// $Id: particleCollision.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
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
