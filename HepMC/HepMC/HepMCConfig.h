// $Id: HepMCConfig.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
// HepMCConfig.h
// ----------------------------------------------------------------------

#ifndef HEPMCCONFIG_H
#define HEPMCCONFIG_H

#include <list>

#include "CLHEP/HepPDT/CommonParticleData.hh"
#include "CLHEP/HepPDT/ParticleDataT.hh"
#include "CLHEP/HepPDT/DecayDataT.hh"

// forward template declarations to avoid large object files
// Note that the ParticleDataTable is never used by HepMC
// Users create their own ParticleDataTable 
// ParticleDataTableConfig.h is provided to properly instantiate the PDT templates.
//
namespace HepPDT {

template< class Config > class ParticleDataTableT;
template< class Config > class TableBuilderT;

} // HepPDT

// forward declaration of GenParticle to avoid compiler confusion
namespace HepMC {

class GenParticle;

} // HepMC

/**
 * @author
 * @ingroup hepmc
 */
struct  HepMCConfig  {

  typedef  HepPDT::CommonParticleData             CPD;
  typedef  HepMC::GenParticle                     PT;

  typedef  HepPDT::ParticleDataTableT<HepMCConfig> ParticleDataTable;
  typedef  HepPDT::ParticleDataT<HepMCConfig>      ParticleData;
  typedef  HepPDT::DecayDataT<HepMCConfig>         DecayData;
  typedef  HepPDT::DecayChannelT<HepMCConfig>      DecayChannel;
  typedef  HepPDT::TableBuilderT<HepMCConfig>      TableBuilder;

  typedef  std::list<CPD>                         CPDlist;
  typedef  std::list<DecayData>                   DDlist;

  typedef  CPDlist::const_iterator                CPDID;
  typedef  DDlist::const_iterator                 DDID;

};  // HepMCConfig

#endif  // HEPMCCONFIG_H
