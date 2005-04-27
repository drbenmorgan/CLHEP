// ----------------------------------------------------------------------
//
// particleMotherDaughter.cc
// return the barcode for the appropriate particle
//
// ----------------------------------------------------------------------

#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepMC  {

int  GenParticle::Mother()   const
{
    if( ! mother() ) return 0;
    return mother()->barcode();
}

int  GenParticle::SecondMother()    const
{
    if( ! secondMother() ) return 0;
    return secondMother()->barcode();
}

int  GenParticle::BeginDaughters()  const
{
    if( ! beginDaughters() ) return 0;
    return beginDaughters()->barcode();
}

int  GenParticle::EndDaughters()    const
{
    if( ! endDaughters() ) return 0;
    return endDaughters()->barcode();
}


}  // HepMC
