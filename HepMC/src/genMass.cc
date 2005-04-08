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
