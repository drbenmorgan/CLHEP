// ----------------------------------------------------------------------
//
// ParticleDataTable.hh
// Author: Walter Brown
///
// ----------------------------------------------------------------------
#ifndef PARTICLEDATATABLE_HH
#define PARTICLEDATATABLE_HH

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/ParticleDataTableT.hh"

namespace HepPDT {

typedef  ParticleDataTableT<DefaultConfig>  ParticleDataTable;
  
}	// HepPDT

#endif // PARTICLEDATATABLE_HH
