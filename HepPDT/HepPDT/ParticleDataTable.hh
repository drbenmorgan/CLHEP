// $Id: ParticleDataTable.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
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
