// ----------------------------------------------------------------------
// DefaultConfig.hh
// ----------------------------------------------------------------------

#ifndef DEFAULTCONFIG_HH
#define DEFAULTCONFIG_HH

#include <list>

#include "CLHEP/HepPDT/CommonParticleData.hh"
#include "CLHEP/HepPDT/SimpleParticle.hh"
#include "CLHEP/HepPDT/ParticleDataTableT.hh"
#include "CLHEP/HepPDT/ParticleDataT.hh"
#include "CLHEP/HepPDT/DecayDataT.hh"
#include "CLHEP/HepPDT/DecayChannelT.hh"

/**
 * @author
 * @ingroup heppdt
 */
struct  DefaultConfig  {

  typedef  HepPDT::CommonParticleData             CPD;
  typedef  SimpleParticle                         PT;

  typedef  HepPDT::ParticleDataTableT<DefaultConfig> ParticleDataTable;
  typedef  HepPDT::ParticleDataT<DefaultConfig>      ParticleData;
  typedef  HepPDT::DecayDataT<DefaultConfig>         DecayData;
  typedef  HepPDT::DecayChannelT<DefaultConfig>      DecayChannel;

  typedef  std::list<CPD>                         CPDlist;
  typedef  std::list<DecayData>                   DDlist;

  typedef  CPDlist::const_iterator                CPDID;
  typedef  DDlist::const_iterator                 DDID;

};  // DefaultConfig


#endif  // DEFAULTCONFIG_HH
