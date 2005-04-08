// ----------------------------------------------------------------------
// ParticleDataTableConfig.h
// L. Garren
//
// Use this header if you are going to build a Particle Data Table
// ----------------------------------------------------------------------

#ifndef PARTICLEDATATABLECONFIG_H
#define PARTICLEDATATABLECONFIG_H

#include "CLHEP/HepPDT/ParticleDataTableT.hh"
#include "CLHEP/HepPDT/DecayChannelT.hh"
#include "CLHEP/HepPDT/TableBuilderT.hh"

#include "CLHEP/HepMC/HepMCConfig.h"

#ifdef __osf__
// kludge so linker can find HepPDT::DMFactory<HepMCConfig>::_inst
template class HepPDT::DMFactory<HepMCConfig>;
#endif

#endif  // PARTICLEDATATABLECONFIG_H
