// $Id: ParticleData.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// ParticleData.hh
//
// ----------------------------------------------------------------------
#ifndef PARTICLEDATA_HH
#define PARTICLEDATA_HH

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/ParticleDataT.hh"

namespace HepPDT {

typedef  ParticleDataT<DefaultConfig>  ParticleData;

}	// HepPDT

#endif // PARTICLEDATA_HH
