// $Id: genMass.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
// genMass.cc
// ----------------------------------------------------------------------
#include "CLHEP/HepMC/GenParticle.h"

namespace HepMC {

double  GenParticle::generatedMass() const {
    return itsGeneratedMass;
}

void   GenParticle::setGeneratedMass( const double & m ) {
    itsGeneratedMass = m;
}

} // HepMC
